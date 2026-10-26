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

GumInterceptor* g_interceptor = NULL;
GHashTable* hooks = NULL;
unsigned int veto_hook = 0;

CREATE_TRAMPOLINE(Logic);
static void GET_CALLBACK(Logic)(void)
{
    ExecutedCommand* exec;
    while ((exec = g_async_queue_pop(executedcmd)) != NULL)
    {
        if (g_hash_table_contains(commands, exec->name))
        {
            Command* cmd = g_hash_table_lookup(commands, exec->name);
            cmd->callback(exec->argc - 1, &exec->argv[1]);
        }
        free(exec->name);
        g_strfreev(exec->argv);
        free(exec);
    }
    RUN_VOID_HOOK(Logic, logicSimulation_ft, ())
    if (!veto_hook)
    {
        RUN_VOID_TRAMPOLINE(Logic, logicSimulation_ft, ())
        RUN_VOID_HOOK(PostLogic, logicSimulation_ft, ())
    }
    veto_hook = 0;
}

int setupHooks(void)
{
    hooks = g_hash_table_new_full(g_str_hash, _frida_g_str_equal, NULL, NULL);
    CREATE_HOOK(Logic, logicSimulation)
    return 1;
}