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
#include <libtcc.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cli.h"
#include "hooks.h"
#include "macro.h"
#include "plugin/cplugin.h"
#include "roseapi.h"
#include <frida-gum.h>

static GHashTable* plugins = NULL;

Plugin* constructplugin(void)
{
    Plugin* plugin = malloc(sizeof(Plugin));
    if (!plugin) return NULL;
    memset(plugin, 0x0, sizeof(Plugin));
    plugin->ptype = -1;
    plugin->clicommands = g_ptr_array_new();
    return plugin;
}

void destructplugin(Plugin* ptr)
{
    if (!ptr) return;
    if (ptr->clicommands)
    {
        int size = ptr->clicommands->len;
        for (int i = 0; i < size; i++)
        {
            Command* cmd = g_ptr_array_index(ptr->clicommands, i);
            if (!cmd) continue;
            removeclibyname(cmd->name);
            free(cmd->name);
            free(cmd);
        }
        g_ptr_array_free(ptr->clicommands, 0);
    }
    destroypluginhooks(ptr);
    if (ptr->ptype != -1 && ptr->state)
    {
        if (ptr->ptype == C_PLUGIN_PTYPE) tcc_delete(ptr->state);
    }
    free(ptr);
    return;
}

static int loadplugin(const char *name)
{
    char *ext = strrchr(name, '.');
    if (!ext) return 0;
    char *path;
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
    g_hash_table_insert(plugins, strdup(name), plugin);
    return 1;
}

void enableplugin(ARGSCLI)
{
    if (argc < 1) return;
    g_strchomp(args[0]);
    if (g_hash_table_contains(plugins, args[0])) return;
    int status = loadplugin(args[0]);
    if (!status)
    {
        LOG_ERROR("failed to load plugin '%s'\n", args[0]);
    } else LOG("loaded plugin '%s'\n", args[0]);
    FILE* file = fopen("disabledplugins.txt", "r");
    if (!file) return;
    FILE* temp = fopen("tmpdplg", "w");
    if (!temp)
    {
        fclose(file);
        return;
    }
    char *buffer = NULL;
    size_t size = 0;
    while (getline(&buffer, &size, file) != -1)
    {
        if (strstr(buffer, args[0]) == NULL)
        {
            fputs(buffer, temp);
        }
    }
    free(buffer);
    fclose(temp);
    fclose(file);
    remove("disabledplugins.txt");
    rename("tmpdplg", "disabledplugins.txt");
}

void disableplugin(ARGSCLI)
{
    if (argc < 1) return;
    g_strchomp(args[0]);
    if (!g_hash_table_contains(plugins, args[0])) return;
    Plugin* plugin = g_hash_table_lookup(plugins, args[0]);
    g_hash_table_remove(plugins, args[0]);
    if (!plugin) return;
    destructplugin(plugin);
    LOG("unloaded plugin '%s'\n", args[0]);
    FILE* file = fopen("disabledplugins.txt", "a+");
    if (!file) return;
    int found = 0;
    char *buffer = NULL;
    size_t size = 0;
    rewind(file);
    while (getline(&buffer, &size, file) != -1)
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (strcmp(buffer, args[0]) == 0)
        {
            found = 1;
            break;
        }
    }
    free(buffer);
    fclose(file);
    return;
}

int setupPlugins(void)
{
    plugins = g_hash_table_new(g_str_hash, _frida_g_str_equal);
    FILE* file = fopen("disabledplugins.txt", "r");
    if (file)
    {
        char **disabled = NULL;
        int count = 0;
        char *buffer = NULL;
        size_t size = 0;
        while (getline(&buffer, &size, file) != -1)
        {
            buffer[strcspn(buffer, "\r\n")] = '\0';
            char **temp = realloc(disabled, (count + 1) * sizeof(char *));
            if (!temp) continue;
            disabled = temp;
            disabled[count] = strdup(buffer);
            count++;
        }
        fclose(file);
        free(buffer);
        DIR* dir = opendir("plugins");
        if (dir)
        {
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL)
            { 
                if (entry->d_name[0] == '.') continue;
                g_strchomp(entry->d_name);
                int isdisabled = 0;
                for (int i = 0; i < count; i++)
                {
                    if (strcmp(entry->d_name, disabled[i]) == 0) isdisabled = 1;
                }
                if (!isdisabled)
                {
                    int status = loadplugin(entry->d_name);
                    if (status) LOG("auto loaded '%s'\n", entry->d_name);
                }
            }
            closedir(dir);
        }
        for (int i = 0; i < count; i++)
        {
            if (disabled[i] != NULL)
            {
                free(disabled[i]);
            }
        }
        free(disabled);
    }
    return 1;
}