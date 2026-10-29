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
#include <frida-gum.h>
#include <libtcc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "hooks.h"
#include "macro.h"
#include "roseapi.h"

GHashTable* plugins;

Plugin* constructplugin(const char *name)
{
    Plugin* plugin = malloc(sizeof(Plugin));
    if (!plugin) {roseapi_error("failed allocation of plugin"); return NULL;}
    memset(plugin, 0x0, sizeof(Plugin));
    plugin->name = strdup(name);
    if (!plugin->name)
    {
        roseapi_error("failed allocation of plugin name");
        free(plugin);
        return NULL;
    }
    return plugin;
}

void destroyplugin(void* ptr)
{
    if (!ptr) return;
    Plugin* plugin = ptr;
    freepluginhooks(ptr);
    freeplugincommands(ptr);
    if (plugin->unload) plugin->unload(plugin->state);
    free(plugin->name);
    free(plugin);
}

static void destroycstate(void *state)
{
    if (state) tcc_delete(state);
    return;
}

static int loadCPlugin(Plugin* ptr, const char *path)
{
    if (!ptr || !path) return 0;
    TCCState* state = tcc_new();
    if (!state) return 0;
    tcc_set_error_func(state, NULL, tcc_error);
    if (tcc_set_output_type(state, TCC_OUTPUT_MEMORY) != 0) goto cleanup;
    if (tcc_add_file(state, path) != 0) goto cleanup;
    if (tcc_relocate(state) != 0) goto cleanup;
    void *entry = tcc_get_symbol(state, "plugin_init");
    if (!entry) goto cleanup;
    ptr->entry = entry;
    ptr->state = state;
    ptr->unload = destroycstate;
    return 1;
    cleanup:
    tcc_delete(state);
    return 0;
}

static int loadplugin(const char *name)
{
    if (g_hash_table_contains(plugins, name)) {roseapi_ferror("plugin '%s' already loaded", name); return 0;};
    const char *ext = strrchr(name, '.');
    if (!ext) return 0;
    Plugin* plugin = constructplugin(name);
    if (!plugin) return 0;
    char *path;
    if (asprintf(&path, "plugins/%s", name) == -1)
    {
        destroyplugin(plugin);
        return 0;
    }

    int ok = 0;
    if (strcmp(ext, ".c") == 0) ok = loadCPlugin(plugin, path);

    free(path);
    if (!ok)
    {
        destroyplugin(plugin);
        return 0;
    }
    g_hash_table_insert(plugins, plugin->name, plugin);
    plugin->entry(plugin);
    return 1;
}



static void enableplugin(ARGSCLI)
{
    if (argc <= 0) return;
    int ok = loadplugin(args[0]);
    if (ok)
    {
        roseapi_log("successfully loaded plugin '%s'", args[0]);
        FILE* file = fopen("disabledplugins.txt", "r");
        if (!file) {roseapi_error("failed open"); return;};
        FILE* tmp = fopen("tmp_disabled", "w");
        if (!tmp) 
        {
            roseapi_error("failed open"); 
            fclose(file); 
            return;
        }
        char *buf = NULL;
        size_t size = 0;
        while (getline(&buf, &size, file) != -1)
        {
            buf[strcspn(buf, "\r\n")] = '\0';
            if (strcmp(buf, args[0]) == 0) continue;
            fputs(buf, tmp);
            fputc('\n', tmp);
        }
        free(buf);
        fclose(file);
        fclose(tmp);
        rename("tmp_disabled", "disabledplugins.txt");
    } else roseapi_ferror("failed enabling plugin '%s'", args[0]);
}

static void disableplugin(ARGSCLI)
{
    if (argc <= 0) return;
    if (!g_hash_table_contains(plugins, args[0])) {roseapi_ferror("plugin '%s' not loaded", args[0]); return;}
    g_hash_table_remove(plugins, args[0]);
    roseapi_log("unloaded plugin '%s'", args[0]);
    FILE* file = fopen("disabledplugins.txt", "a+");
    if (!file)
    {
        roseapi_error("failed open");
        return;
    }
    rewind(file);
    char *buf = NULL;
    size_t size = 0;
    int found = 0;
    while (getline(&buf, &size, file) != -1)
    {
        buf[strcspn(buf, "\r\n")] = '\0';
        if (strcmp(buf, args[0]) == 0) { found = 1; break; }
    }
    free(buf);
    if (!found)
    {
        fprintf(file, "%s\n", args[0]);
    }
    fclose(file);
}



int pluginisregistered(Plugin* plugin)
{
    GHashTableIter iter;
    gpointer val;
    g_hash_table_iter_init(&iter, plugins);
    while (g_hash_table_iter_next(&iter, NULL, &val))
    {
        if (val == plugin)
        {
            return 1;
        }
    }
    return 0;
}

int plugincheckcontext(PluginContext ctx)
{
    if (!ctx)
    {
        roseapi_ferror("must provide context");
        return 0;
    }
    if (!pluginisregistered(ctx))
    {
        roseapi_ferror("invalid context");
        return 0;
    }
    return 1;
}

int setupPlugins(void)
{
    plugins = g_hash_table_new_full(g_str_hash, _frida_g_str_equal, NULL, destroyplugin);
    Command* cmd1 = malloc(sizeof(Command));
    Command* cmd2 = malloc(sizeof(Command));
    if (!cmd1 || !cmd2) return 0;
    cmd1->callback = enableplugin;
    cmd2->callback = disableplugin;
    g_hash_table_insert(commands, "enableplugin", cmd1);
    g_hash_table_insert(commands, "disableplugin", cmd2);

    char **disabled = NULL;
    int count = 0;
    FILE* file = fopen("disabledplugins.txt", "r");
    if (file)
    {
        char *buf = NULL;
        size_t size = 0;
        while (getline(&buf, &size, file) != -1)
        {
            g_strchomp(buf);
            char *str = strdup(buf);
            if (!str) continue;
            char **tmp = realloc(disabled, (count + 1) * sizeof(char *));
            if (!tmp) {roseapi_error("failed allocation"); free(str); continue;}
            disabled = tmp;
            disabled[count] = str;
            count++;
        }
        fclose(file);
        free(buf);
    } else roseapi_error("failed open");
    DIR* dir = opendir("plugins");
    if (dir)
    {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] == '.') continue;
            int isdisabled = 0;
            if (disabled && count > 0)
            {
                for (int i = 0; i < count; i++)
                {
                    if (strcmp(entry->d_name, disabled[i]) == 0) {isdisabled = 1; break;}
                }
            }
            if (!isdisabled)
            {
                roseapi_log("attempting to auto load '%s'", entry->d_name);
                int status = loadplugin(entry->d_name);
                if (!status)
                {
                    roseapi_ferror("failed to auto load '%s'", entry->d_name);
                } else roseapi_log("auto loaded '%s'", entry->d_name);
            }
        }
        closedir(dir);
    } else roseapi_error("failed open");
    if (disabled && count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            if (disabled[i]) free(disabled[i]);
        }
        free(disabled);
    }
    return 1;
}