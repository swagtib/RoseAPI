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
#include "plugin/plugin.h"
#include "roseapi.h"
#include <pthread.h>
#include <frida-gum.h>
#include <editline/readline.h>
#include <stdlib.h>
#include <string.h>
#include "bootstrap.h"

GAsyncQueue* commandqueue;
GHashTable* commands;

static void* clihandler(void *arg)
{
    char* line = NULL;
    while (1)
    {
        char **argv;
        int argc;
        line = readline("roseapi> ");
        if (line == NULL) exit(EXIT_SUCCESS);
        g_strchomp(line);
        if (line[0] != '\0')
        {
            add_history(line);
            if (g_shell_parse_argv(line, &argc, &argv, NULL))
            {
                ExecutedCommand* cmd = malloc(sizeof(ExecutedCommand));
                if (cmd)
                {
                    cmd->argc = argc;
                    cmd->argv = argv;
                    g_async_queue_push(commandqueue, cmd);
                } else g_strfreev(argv);
            }
        }
        free(line);
    }
    return NULL;
}

void freeplugincommands(Plugin* ptr)
{
    if (!ptr) return;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, commands);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Command* cmd = value;
        if (cmd->plugin == ptr)
        {
            g_hash_table_iter_remove(&iter);
        }
    }
}

int addclicommand(PluginContext ctx, const char *name, CLICallback callback)
{
    if (!ctx || !name || !callback) return 0;
    if (strchr(name, ' ') != NULL) return 0;
    if (g_hash_table_contains(commands, name)) return 0;
    if (!pthread_equal(pthread_self(), gamethread)) return 0;
    if (!pluginisregistered(ctx)) return 0;
    Command* cmd = malloc(sizeof(Command));
    if (!cmd) return 0;
    char *key = strdup(name);
    if (!key)
    {
        free(cmd);
        return 0;
    }
    cmd->callback = callback;
    cmd->plugin = ctx;
    g_hash_table_insert(commands, key, cmd);
    return 1;
}

int setupcli(void)
{
    commandqueue = g_async_queue_new();
    commands = g_hash_table_new_full(g_str_hash, _frida_g_str_equal, free, free);
    pthread_t clithread;
    if (pthread_create(&clithread, NULL, clihandler, NULL) != 0) return 0;
    if (pthread_detach(clithread) != 0) return 0;
    return 1;
}