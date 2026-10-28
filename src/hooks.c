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
#include "hooks.h"
#include "cli.h"
#include "engine.h"

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

static void logichook(void)
{
    ExecutedCommand* exec;
    while ((exec = g_async_queue_try_pop(commandqueue)) != NULL)
    {
        if (g_hash_table_contains(commands, exec->argv[0]))
        {
            Command* cmd = g_hash_table_lookup(commands, exec->argv[0]);
            cmd->callback(exec->argc - 1, &exec->argv[1]);
        }
        executedcmd_free(exec);
    }
    HookScope scope;
    pushscope(&scope, HOOK_LOGIC);

    popscope();
    return;
}

int setuphooks(void)
{
    for (int i = 0; i < HOOK_COUNT; i++)
    {
        hooks[i].pre = g_ptr_array_new_with_free_func(free);
        hooks[i].post = g_ptr_array_new_with_free_func(free);
    }
    INTERCEPT(HOOK_LOGIC, logicSimulation, logichook); // fix  when i make program more verbose
    return 1;
}