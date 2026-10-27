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
#include "roseapi.h"

GumInterceptor* g_interceptor = NULL;
Hook hooks[HOOK_COUNT];

static HookScope* current_scope = NULL;

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

static void LogicHook(void)
{
    HookScope scope;
    pushscope(&scope, HOOK_LOGIC);

    ExecutedCommand* exec;
    while ((exec = g_async_queue_try_pop(executedcmd)) != NULL)
    {
        if (g_hash_table_contains(commands, exec->name))
        {
            Command* cmd = g_hash_table_lookup(commands, exec->name);
            cmd->callback(exec->argc - 1, &exec->argv[1]);
        }
        g_strfreev(exec->argv);
        free(exec->name);
        free(exec);
    }
    Hook* hook = scope.hook;
    for (int i = 0; i < hook->pre->len; i++)
    {
        HookCallback* hcall = g_ptr_array_index(hook->pre, i);
        if (hcall)
        {
            logicSimulation_ft func = hcall->callback;
            func();
        }
    }
    if (!scope.veto)
    {
        logicSimulation_ft original = hook->trampoline;
        original();
        for (int i = 0; i < hook->post->len; i++)
        {
            HookCallback* hcall = g_ptr_array_index(hook->post, i);
            if (hcall)
            {
                logicSimulation_ft func = hcall->callback;
                func();
            }
        }
    }
    popscope();
    return;
}




int setupHooks(void)
{
    for (int i = 0; i < HOOK_COUNT; i++)
    {
        hooks[i].pre = g_ptr_array_new_with_free_func(free);
        hooks[i].post = g_ptr_array_new_with_free_func(free);
    }
    INTERCEPT(HOOK_LOGIC, logicSimulation, LogicHook);
    return 1;
}