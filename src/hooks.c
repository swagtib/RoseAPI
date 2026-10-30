/*
RoseAPI - A modding API for Sub Rosa.
Copyright (C) 2026 swagtib
 
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.
 
You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <frida-gum.h>
#include <stdlib.h>
#include "hooks.h"
#include "cli.h"
#include "engine.h"
#include "plugin/plugin.h"
#include "roseapi.h"
#include "bootstrap.h"

GumInterceptor* g_interceptor = NULL;

Hook hooks[HOOK_COUNT];

static HookScope* current_scope = NULL;

int addhook(PluginContext ctx, int h, unsigned int flags, void *callback)
{
    if (!plugincheckcontext(ctx)) return 0;
    if (current_scope != NULL) {plugin_error(ctx, "cannot create hook while a hook is active"); return 0;}
    if (!pthread_equal(pthread_self(), gamethread)) {plugin_error(ctx, "cannot create hook from other threads"); return 0;}
    if (!callback) {plugin_error(ctx, "provide a hook callback"); return 0;}
    if (!ISINRANGE(h, HOOK_COUNT)) { plugin_error(ctx, "invalid hook index"); return 0; }
    if ((flags & FLAG_HOOK_PRE) && flags & (FLAG_HOOK_POST))
    {
        plugin_error(ctx, "cannot place hook on both pre & post");
        return 0;
    }
    if (!(flags & (FLAG_HOOK_PRE | FLAG_HOOK_POST)))
    {
        flags |= FLAG_HOOK_PRE;
    }
    Hook* hook = &hooks[h];
    GPtrArray* array = NULL;
    if (flags & FLAG_HOOK_PRE) array = hook->pre;
    if (flags & FLAG_HOOK_POST) array = hook->post;
    if (!array) return 0;
    HookCallback* hcall = malloc(sizeof(HookCallback));
    if (!hcall) {roseapi_error("failed allocation of hcall"); return 0;};
    hcall->callback = callback;
    hcall->plugin = ctx;
    if (flags & FLAG_HOOK_PRIORITY)
    {
        g_ptr_array_insert(array, 0, hcall);
    } else g_ptr_array_add(array, hcall);
    return 1;
}

static void pushscope(HookScope *scope, int hookidx)
{
    scope->hook = &hooks[hookidx];
    scope->hook->occupied = 1;
    scope->veto = 0;
    scope->previous = current_scope;
    current_scope = scope;
}

static void popscope(void)
{
    if (current_scope)
    {
        current_scope->hook->occupied = 0;
        current_scope = current_scope->previous;
    }
}

void freepluginhooks(Plugin* ptr)
{
    for (int i = 0; i < HOOK_COUNT; i++)
    {
        Hook* curhook = &hooks[i];
        for (int j = curhook->pre->len - 1; j >= 0; j--)
        {
            HookCallback* hcall = g_ptr_array_index(curhook->pre, j);
            if (hcall && hcall->plugin == ptr)
            {
                g_ptr_array_remove_index(curhook->pre, j);
            }
        }

        for (int j = curhook->post->len - 1; j >= 0; j--)
        {
            HookCallback* hcall = g_ptr_array_index(curhook->post, j);
            if (hcall && hcall->plugin == ptr)
            {
                g_ptr_array_remove_index(curhook->post, j);
            }
        }
    }
}



static void logichook(void)
{
    ExecutedCommand* exec;
    while ((exec = g_async_queue_try_pop(commandqueue)) != NULL)
    {
        if (g_hash_table_contains(commands, exec->argv[0]))
        {
            Command* cmd = g_hash_table_lookup(commands, exec->argv[0]);
            cmd->callback(exec->argc - 1, &exec->argv[1]);
        } else roseapi_ferror("command '%s' doesn't exist", exec->argv[0]);
        g_strfreev(exec->argv);
        free(exec);
    }
    HookScope scope;
    pushscope(&scope, HOOK_LOGIC);
    Hook* hook = scope.hook;
    for (int i = 0; i < hook->pre->len; i++)
    {
        HookCallback* hcall = g_ptr_array_index(hook->pre, i);
        if (!hcall) continue;
        logicSimulation_ft func = hcall->callback;
        func();
    }
    if (!scope.veto)
    {
        logicSimulation_ft trampoline = hook->trampoline;
        trampoline();
        for (int i = 0; i < hook->post->len; i++)
        {
            HookCallback* hcall = g_ptr_array_index(hook->post, i);
            if (!hcall) continue;
            logicSimulation_ft func = hcall->callback;
            func();
        }
    }
    popscope();
    return;
}

static void physicshook(void)
{
    HookScope scope;
    pushscope(&scope, HOOK_PHYSICS);
    Hook* hook = scope.hook;
    for (int i = 0; i < hook->pre->len; i++)
    {
        HookCallback* hcall = g_ptr_array_index(hook->pre, i);
        if (!hcall) continue;
        physicsSimulation_ft func = hcall->callback;
        func();
    }
    if (!scope.veto)
    {
        physicsSimulation_ft tramp = hook->trampoline;
        tramp();
        for (int i = 0; i < hook->post->len; i++)
        {
            HookCallback* hcall = g_ptr_array_index(hook->post, i);
            if (!hcall) continue;
            physicsSimulation_ft func = hcall->callback;
            func();
        }
    }
    popscope();
}

static void bulletsimhook(void)
{
    HookScope scope;
    pushscope(&scope, HOOK_BULLETSIM);
    Hook* hook = scope.hook;
    for (int i = 0; i < hook->pre->len; i++)
    {
        HookCallback* hcall = g_ptr_array_index(hook->pre, i);
        if (!hcall) continue;
        bulletSimulation_ft func = hcall->callback;
        func();
    }
    if (!scope.veto)
    {
        bulletSimulation_ft tramp = hook->trampoline;
        tramp();
        for (int i = 0; i < hook->post->len; i++)
        {
            HookCallback* hcall = g_ptr_array_index(hook->post, i);
            if (!hcall) continue;
            bulletSimulation_ft func = hcall->callback;
            func();
        }
    }
    popscope();
}

static void limbanimationhook(int arg1, int arg2, int arg3, Vector * arg4, RotMatrix * arg5, Vector * arg6, float arg7, float arg8, float arg9, float * arg10, Vector * arg11, Vector * arg12, Vector * arg13, char arg14)
{
    HookScope scope;
    pushscope(&scope, HOOK_LIMBANIM);
    Hook* hook = scope.hook;
    for (int i = 0; i < hook->pre->len; i++)
    {
        HookCallback* hcall = g_ptr_array_index(hook->pre, i);
        if (!hcall) continue;
        void (*func)(void) = hcall->callback;
        func();
    }
    if (!scope.veto)
    {
        humanLimbInverseKinematics_ft tramp = hook->trampoline;
        tramp(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14);
        for (int i = 0; i < hook->post->len; i++)
        {
            HookCallback* hcall = g_ptr_array_index(hook->post, i);
            if (!hcall) continue;
            void (*func)(void) = hcall->callback; // theres no reason to give this any sort of meaning considering all of the args are ??????
            func();
        }
    }
    popscope();
}

static int linkitemhook(int itm, int child, int human, int slot)
{
    if (ISOCCUPIED(HOOK_ITEMLINK)) return linkItem_game(itm, child, human, slot);
    HookScope scope;
    pushscope(&scope, HOOK_ITEMLINK);
    Hook* hook = scope.hook;
    for (int i = 0; i < hook->pre->len; i++)
    {
        HookCallback* hcall = g_ptr_array_index(hook->pre, i);
        if (!hcall) continue;
        void (*func)(int i, int c, int h, int s) = hcall->callback;
        func(itm, child, human, slot);
    }
    int retval = -1;
    if (!scope.veto)
    {
        linkItem_ft tramp = hook->trampoline;
        retval = tramp(itm, child, human, slot);
        for (int i = 0; i < hook->post->len; i++)
        {
            HookCallback* hcall = g_ptr_array_index(hook->post, i);
            if (!hcall) continue;
            void (*func)(int i, int c, int h, int s, int result) = hcall->callback;
            func(itm, child, human, slot, retval);
        }
    }
    popscope();
    return retval;
}



int setuphooks(void)
{
    for (int i = 0; i < HOOK_COUNT; i++)
    {
        hooks[i].pre = g_ptr_array_new_with_free_func(free);
        hooks[i].post = g_ptr_array_new_with_free_func(free);
    }
    int gumerror = 0;
    INTERCEPT(HOOK_LOGIC, logicSimulation_game, logichook, gumerror)
    INTERCEPT(HOOK_PHYSICS, physicsSimulation_game, physicshook, gumerror)
    INTERCEPT(HOOK_BULLETSIM, bulletSimulation_game, bulletsimhook, gumerror)
    INTERCEPT(HOOK_LIMBANIM, humanLimbInverseKinematics_game, limbanimationhook, gumerror)
    return 1;
}