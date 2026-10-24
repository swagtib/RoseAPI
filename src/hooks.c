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
#include "hooks.h"
#include "cli.h"
#include "engine.h"
#include "plugin/plugin.h"
#include "roseapi.h"
#include <frida-gum.h>
#include <stdlib.h>

GumInterceptor *interceptor = NULL;
static GHashTable* hooks;
static unsigned int vetoed = 0;

int addhook(PluginContext ctx, const char* hookname, void* callback)
{
    if (!ctx || !hookname || !callback) return 0;
    if (!g_hash_table_contains(hooks, hookname)) return 0;
    Hook* hook = malloc(sizeof(Hook));
    if (!hook) return 0;
    hook->owner = ctx;
    hook->callback = callback;
    GSList* list = g_hash_table_lookup(hooks, hookname);
    list = g_slist_append(list, hook);
    g_hash_table_replace(hooks, (gpointer)hookname, list);
    return 1;
}

void destroypluginhooks(Plugin* ptr)
{
    if (!ptr) return;
    GHashTableIter iter;
    gpointer key, val;
    g_hash_table_iter_init(&iter, hooks);
    while (g_hash_table_iter_next(&iter, &key, &val))
    {
        GSList *list = val;
        GSList *entry = list;
        while (entry != NULL)
        {
            GSList* next = entry->next;
            Hook* hook = entry->data;
            if (hook && hook->owner == ptr)
            {
                free(hook);
                hook = NULL;
                list = g_slist_delete_link(list, entry);
            }
            entry = next;
        }
        g_hash_table_iter_replace(&iter, list);
    }
}

CREATE_TRAMPOLINE(Logic)
static void GET_CALLBACK(Logic)(void)
{
    ExecutedCommand* exec;
    while ((exec = g_async_queue_try_pop(commandstorun)) != NULL)
    {
        if (!clicommandexists(exec->name)) goto cleanup; // this is bad but i'm too lazy to make it any better
        if (exec->cmd && exec->cmd->callback)
        {
            exec->cmd->callback(exec->argc - 1, &exec->argv[1]);
        }
        cleanup:
        g_strfreev(exec->argv);
        free(exec->name);
        free(exec);
    }
    RUN_VOID_HOOK(Logic, logicSimulation_ft, ())
    if (!vetoed)
    {
        RUN_VOID_TRAMPOLINE(Logic, logicSimulation_ft, ())
        RUN_VOID_HOOK(PostLogic, logicSimulation_ft, ())
    }
    vetoed = 0;
}

int setuphooks(void)
{
    hooks = g_hash_table_new(g_str_hash, _frida_g_str_equal);
    CREATE_HOOK(Logic, logicSimulation);
    return 1;
}