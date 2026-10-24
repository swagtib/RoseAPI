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
#include <frida-gum.h>
#include <stdio.h>
#include <stdlib.h>
#include "macro.h"
#include "plugin/plugin.h"
#include <unistd.h>

GHashTable *clitable;

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
                cmd->callback(argc - 1, &argv[1]);
            } else LOG_ERROR("command '%s' doesn't exist\n", argv[0]);
        }
        g_strfreev(argv);
    }
    free(line);
    return NULL;
}

int startCLI(void)
{
    clitable = g_hash_table_new(g_str_hash, _frida_g_str_equal);
    if (!clitable) return 0;
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