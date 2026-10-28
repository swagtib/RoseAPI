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

#include "plugin.h"
#include "cli.h"
#include "hooks.h"
#include <frida-gum.h>
#include <stdlib.h>
#include <libtcc.h>

GHashTable* plugins;

Plugin* constructplugin(void)
{
    Plugin* plugin = malloc(sizeof(Plugin));
    memset(plugin, 0x0, sizeof(Plugin));
    return plugin;
}

void destructplugin(void *ptr)
{
    if (!ptr) return;
    Plugin* plugin = ptr;
    for (int i = 0; i < HOOK_COUNT; i++)
    {
        Hook* currenthook = &hooks[i];
        for (int j = (int)currenthook->pre->len - 1; j >= 0; j--)
        {
            HookCallback* hcall = g_ptr_array_index(currenthook->pre, j);
            if (hcall && hcall->plugin == plugin)
            {
                g_ptr_array_remove_index(currenthook->pre, j);
            }
        }
        for (int j = (int)currenthook->post->len - 1; j >= 0; j--)
        {
            HookCallback* hcall = g_ptr_array_index(currenthook->post, j);
            if (hcall && hcall->plugin == plugin)
            {
                g_ptr_array_remove_index(currenthook->post, j);
            }
        }
    }
    GHashTableIter iter;
    gpointer key, val;
    g_hash_table_iter_init(&iter, commands);
    while (g_hash_table_iter_next(&iter, &key, &val))
    {
        Command* cmd = val;
        if (cmd && cmd->plugin == plugin)
        {
            g_hash_table_iter_remove(&iter);
        }
    }
    free(ptr);
}

int setupPlugins(void)
{
    plugins = g_hash_table_new_full(g_str_hash, _frida_g_str_equal, free, destructplugin);
    return 1;
}