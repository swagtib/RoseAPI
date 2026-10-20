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
#include "frida-gum.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "plugin/cplugin.h"
#include <sys/stat.h>
#include <errno.h>

static GHashTable *plugins;

Plugin* createplugin(void)
{
    Plugin* plugin = malloc(sizeof(Plugin));
    if (!plugin) return NULL;
    memset(plugin, 0x0, sizeof(Plugin));
    plugin->ptype = -1;
    return plugin;
}

void destroyplugin(Plugin* ptr)
{
    if (!ptr) return;
    free(ptr);
}

static int loadplugin(const char *name)
{
    if (g_hash_table_contains(plugins, name)) return 0;
    char *ext = strrchr(name, '.');
    if (!ext) return 0;
    char *path;
    if (asprintf(&path, "plugins/%s", name) == -1) return 0;
    if (access(path, R_OK | F_OK) != 0)
    {
        free(path);
        return 0;
    }
    Plugin* plugin;
    if (strcmp(ext, ".c") == 0) plugin = createCPlugin(path);
    free(path);
    if (!plugin) return 0;
    g_hash_table_insert(plugins, (gpointer)name, plugin);
    return 1;
}

static int mkdirplugins(void)
{
    int status = mkdir("plugins", 0755);
    if ((status == 0) || (status == -1 && errno == EEXIST)) return 1;
    return 0;
}

static void populateTxt(void)
{
    FILE* file = fopen("enabledplugins.txt", "a+");
    if (!file) return;
    rewind(file);
    if (fgetc(file) == EOF && !ferror(file)) 
    {
        DIR* dir = opendir("plugins");
        if (!dir)
        {
            fclose(file);
            return;
        }
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] == '.') continue;
            fprintf(file, "%s\n", entry->d_name);
        }
        closedir(dir);
    }
    fclose(file);
}

int setupPlugins(void)
{
    plugins = g_hash_table_new(g_str_hash, _frida_g_str_equal);
    if (!plugins) return 0;
    if (!mkdirplugins()) return 0;
    populateTxt();
    return 1;
}