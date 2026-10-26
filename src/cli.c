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
#include "macro.h"
#include "plugin/plugin.h"
#include "roseapi.h"
#include <pthread.h>
#include <frida-gum.h>
#include <stdio.h>
#include <stdlib.h>

GHashTable* commands;
GAsyncQueue* executedcmd;

int addclicommand(PluginContext ctx, const char *name, CLICallback callback)
{
    if (!ctx || !name || !callback) return 0;
    char *key = strdup(name);
    if (!key) return 0;
    g_strchomp(key);
    if (strchr(key, ' ') != NULL)
    {
        free(key);
        return 0;
    }
    if (g_hash_table_contains(commands, name))
    {
        LOG_ERROR("command '%s' is already registered\n", key);
        free(key);
        return 0;
    }
    Command* cmd = malloc(sizeof(Command));
    if (!cmd)
    {
        free(key);
        return 0;
    }
    cmd->callback = callback;
    cmd->owner = ctx;
    g_hash_table_insert(commands, key, cmd);
    return 1;
}

static void* handle_cli(void* arg)
{
    char *line = NULL;
    size_t size = 0;
    while (1)
    {
        printf("> ");
        fflush(stdout);
        if (getline(&line, &size, stdin) == -1 ) break;

        int argc;
        char **argv;
        if (!g_shell_parse_argv(line, &argc, &argv, NULL)) continue;
        if (argc > 0 && g_hash_table_contains(commands, argv[0]))
        {
            ExecutedCommand* cmd = malloc(sizeof(ExecutedCommand));
            if (!cmd)
            {
                g_strfreev(argv);
                continue;
            }
            cmd->argc = argc;
            cmd->argv = argv;
            cmd->name = strdup(argv[0]);
            if (!cmd->name)
            {
                g_strfreev(argv);
                free(cmd);
                continue;
            }
            g_async_queue_push(executedcmd, cmd);
        } else {
            g_strfreev(argv);
        }
    }
    free(line);
    return NULL;
}

int setupcli(void)
{
    commands = g_hash_table_new_full(g_str_hash, _frida_g_str_equal, free, free);
    executedcmd = g_async_queue_new();
    pthread_t thread;
    Command* enable = malloc(sizeof(Command));
    Command* disable = malloc(sizeof(Command));
    if (!enable || !disable) return 0;
    enable->callback = enableplugin;
    enable->owner = NULL;
    disable->callback = disableplugin;
    disable->owner = NULL;
    g_hash_table_insert(commands, "enableplugin", enable);
    g_hash_table_insert(commands, "disableplugin", disable);
    if (pthread_create(&thread, NULL, handle_cli, NULL) != 0) return 0;
    if (pthread_detach(thread) != 0) return 0;
    return 1;
}