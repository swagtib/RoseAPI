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

#include "plugin/plugin.h"
#include "cli.h"
#include "hooks.h"
#include "roseapi.h"
#include <frida-gum.h>
#include <libtcc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"

GHashTable* plugins;

Plugin* constructplugin(void)
{
    Plugin* plugin = malloc(sizeof(Plugin));
    if (!plugin) return NULL;
    memset(plugin, 0x0, sizeof(Plugin));
    plugin->ptype = -1;
    return plugin;
}

void destructplugin(void* ptr) // g_hash_table_new_full's value destruct function expects a void(*)(void*) and it's ugly casting it..
{
    if (!ptr) return;
    Plugin* plugin = ptr;
    if (plugin->state)
    {
        if (plugin->ptype == C_PLUGIN_PTYPE)
        {
            tcc_delete(plugin->state);
        }
    }
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, commands);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Command* cmd = value;
        if (cmd->owner == plugin)
        {
            g_hash_table_iter_remove(&iter);
        }
    }
    g_hash_table_iter_init(&iter, hooks);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        GSList* hooklist = value;
        GSList* entry = hooklist;
        while (entry != NULL)
        {
            GSList* next = entry->next;
            Hook* hook = entry->data;
            if (hook)
            {
                if (hook->owner == plugin)
                {
                    free(hook);
                    hook = NULL;
                    hooklist = g_slist_delete_link(hooklist, entry);
                }
            }
            entry = next;
        }
        g_hash_table_iter_replace(&iter, hooklist);
    }
    free(plugin);
    return;
}

static Plugin* loadCPlugin(const char *path)
{
    TCCState* state = tcc_new();
    if (!state) return NULL;
    if (tcc_set_output_type(state, TCC_OUTPUT_MEMORY) == -1) goto cleanupstate;
    if (tcc_add_include_path(state, "api") == -1) goto cleanupstate;
    if (tcc_add_file(state, path) == -1) goto cleanupstate;
    if (tcc_relocate(state) == -1) goto cleanupstate;
    PluginEntry entry = tcc_get_symbol(state, "plugin_init");
    if (!entry) goto cleanupstate;
    Plugin* plugin = malloc(sizeof(Plugin));
    if (!plugin) goto cleanupstate;
    plugin->state = state;
    plugin->ptype = C_PLUGIN_PTYPE;
    plugin->entry = entry;
    return plugin;

    cleanupstate:
    tcc_delete(state);
    return NULL;
}

static int loadplugin(const char *name)
{
    char *ext = strrchr(name, '.');
    if (!ext) return 0;
    char* path;
    if (asprintf(&path, "plugins/%s", name) == -1) return 0;
    FILE* file = fopen(path, "r");
    if (!file)
    {
        free(path);
        return 0;
    }
    fclose(file);
    Plugin* plugin = NULL;
    if (strcmp(ext, ".c") == 0) plugin = loadCPlugin(path);
    free(path);
    if (!plugin) return 0;
    char *key = strdup(name);
    if (!key)
    {
        destructplugin(plugin);
        return 0;
    }
    g_hash_table_insert(plugins, key, plugin);
    plugin->entry(plugin);
    return 1;
}

void enableplugin(ARGSCLI)
{
    if (argc < 1) return;
    g_strchomp(args[0]);
    if (g_hash_table_contains(plugins, args[0])) return;
    int status = loadplugin(args[0]);
    if (status)
    {
        LOG("loaded plugin '%s'\n", args[0]);
        FILE* file = fopen("disabledplugins.txt", "r");
        if (!file) return;
        FILE* tmp = fopen("temp_disabled", "w");
        if (!tmp)
        {
            fclose(file);
            return;
        }
        char* buffer = NULL;
        size_t size = 0;
        while (getline(&buffer, &size, file) != -1)
        {
            buffer[strcspn(buffer, "\r\n")] = '\0';
            if (buffer[0] == '\0') continue;
            if (strcmp(buffer, args[0]) != 0)
            {
                fputs(buffer, tmp);
                fputc('\n', tmp);
            }
        }
        free(buffer);
        fclose(tmp);
        fclose(file);
        rename("temp_disabled", "disabledplugins.txt");
    } else {
        LOG_ERROR("failed loading plugin '%s'\n", args[0]);
    }
}

void disableplugin(ARGSCLI)
{
    if (argc < 1) return;;
    g_strchomp(args[0]);
    if (!g_hash_table_contains(plugins, args[0])) return;
    g_hash_table_remove(plugins, args[0]);
    FILE* file = fopen("disabledplugins.txt", "a+");
    if (!file) return;
    rewind(file);
    char *buffer = NULL;
    size_t size = 0;
    int found = 0;
    while (getline(&buffer, &size, file) != -1)
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (strcmp(buffer, args[0]) == 0)
        {
            found = 1;
            break;
        }
    }
    if (!found)
    {
        fprintf(file, "%s\n", args[0]);
    }
    free(buffer);
    fclose(file);
    LOG("disabled plugin '%s'\n", args[0]);
}

int setupPlugins(void)
{
    plugins = g_hash_table_new_full(g_str_hash, _frida_g_str_equal, free, destructplugin);
    return 1;
}