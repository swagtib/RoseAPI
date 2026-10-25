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

#include "cli.h"
#include <bits/pthreadtypes.h>
#include <frida-gum.h>
#include <stdio.h>
#include <stdlib.h>
#include "macro.h"
#include "plugin/plugin.h"
#include <roseapi.h>
#include <string.h>
#include <unistd.h>

static GHashTable *clitable;
GAsyncQueue* commandstorun;

int addclicommand(PluginContext ctx, const char *command, CLICallback callback)
{
    if (!ctx || !callback || !command) return 0;
    char *name = strdup(command);
    if (!name) return 0;
    g_strchomp(name);
    if (strchr(name, ' ') != NULL)
    {
        free(name);
        return 0;
    }
    if (g_hash_table_contains(clitable, name))
    {
        LOG_ERROR("command '%s' is already registered\n", name);
        free(name);
        return 0;
    }
    Command* cmd = malloc(sizeof(Command));
    if (!cmd)
    {
        free(name);
        return 0;
    }
    cmd->name = strdup(name);
    cmd->callback = callback;
    Plugin* plugin = ctx;
    g_ptr_array_add(plugin->clicommands, cmd);
    g_hash_table_insert(clitable, name, cmd);
    return 1;
}

void removeclibyname(const char *name)
{
    if (g_hash_table_contains(clitable, name))
    {
        g_hash_table_remove(clitable, name);
    }
}

int clicommandexists(const char *name) { return g_hash_table_contains(clitable, name); }

static void* handle_cli_input(void* arg)
{
    char* line = NULL;
    size_t len = 0;
    while (1) {
        printf("> ");
        fflush(stdout);

        if (getline(&line, &len, stdin) == -1) break;
        
        int argc;
        char **argv;
        if (!g_shell_parse_argv(line, &argc, &argv, NULL)) continue;

        if (argc > 0)
        {
            Command* cmd = g_hash_table_lookup(clitable, argv[0]);
            if (cmd != NULL && cmd->callback != NULL)
            {
                ExecutedCommand* torun = malloc(sizeof(ExecutedCommand));
                if (!torun)
                {
                    g_strfreev(argv);
                    continue;
                }
                torun->cmd = cmd;
                torun->argc = argc;
                torun->argv = argv;
                torun->name = strdup(cmd->name);
                g_async_queue_push(commandstorun, torun);
            } else
            {
                LOG_ERROR("command '%s' doesn't exist\n", argv[0]);
                g_strfreev(argv);
            }
        }
        //g_strfreev(argv);
    }
    free(line);
    return NULL;
}

int startCLI(void)
{
    commandstorun = g_async_queue_new();
    clitable = g_hash_table_new(g_str_hash, _frida_g_str_equal);
    Command* cmd = malloc(sizeof(Command));
    if (!cmd) return 0;
    cmd->callback = enableplugin;
    cmd->name = "enableplugin";
    g_hash_table_insert(clitable, "enableplugin", cmd);
    cmd = malloc(sizeof(Command));
    if (!cmd) return 0;
    cmd->callback = disableplugin;
    cmd->name = "disableplugin";
    g_hash_table_insert(clitable, "disableplugin", cmd);
    pthread_t thread;
    if (pthread_create(&thread, NULL, &handle_cli_input, NULL) != 0) return 0;
    if (pthread_detach(thread) != 0) return 0;
    return 1;
}