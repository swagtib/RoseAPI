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
#include <libtcc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "macro.h"
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

// this whole file needs a rewrite
// mostly POC code lol

static int mkdirplugins(void)
{
    int status = mkdir("plugins", 0755); // maybe reevaluate?
    if ((status == 0) || (status == -1 && errno == EEXIST))
    {
        LOG("found plugins folder\n");
        return 1;
    }
    LOG_ERROR("failed getting plugins folder, errno:%d\n", errno);
    return 0;
}

static int makepluginstxt(void)
{
    FILE* txt = fopen("enabledplugins.txt", "a+");
    if (!txt)
    {
        LOG_ERROR("failuare opening enabledplugins.txt\n");
        return 0;
    }
    rewind(txt);
    if (fgetc(txt) == EOF)
    {
        LOG("enabledplugins.txt empty, populating\n");
        DIR* plugins = opendir("plugins");
        if (!plugins)
        {
            fclose(txt);
            return 0;
        }
        struct dirent *entry;
        while ((entry = readdir(plugins)) != NULL)
        {
            if (entry->d_name[0] == '.')
            {
                continue;
            }
            if (fprintf(txt, "%s\n", entry->d_name) < 0)
            {
                LOG_ERROR("failed to write %s to enabledplugins.txt, attempting to continue\n", entry->d_name);
                continue;
            }
        }
        closedir(plugins);
    }
    fclose(txt);
    return 1;
}

void loadplugin(const char *name)
{
    LOG("attempting to load %s\n", name);
    char* path;
    int status = asprintf(&path, "plugins/%s", name);
    if (status == -1)
    {
        free(path);
        return;
    }
    TCCState* state = tcc_new();
    tcc_set_output_type(state, TCC_OUTPUT_MEMORY);
    tcc_add_file(state, path);
    if (tcc_relocate(state) == -1)
    {
        free(path);
        tcc_delete(state);
        return;
    }
    void (*plugin_start)(void) = tcc_get_symbol(state, "plugin_start");
    if (!plugin_start)
    {
        tcc_delete(state);
    } else plugin_start();
    free(path);
}

void loadenabled_plugins()
{
    FILE* plugins = fopen("enabledplugins.txt", "r");
    if (!plugins)
    {
        LOG_ERROR("failed to open enabledplugins.txt\n");
        return;
    }
    char filename[2048]; // this is so bad bro lol
    while (fgets(filename, sizeof(filename), plugins) != NULL)
    {
        filename[strcspn(filename, "\r\n")] = '\0'; // should probably use fgetc instead of fgets for this
        loadplugin(filename);
    }
}

void plugins_setup(void)
{
    if (!mkdirplugins() || !makepluginstxt())
    {
        LOG_ERROR("plugins setup failed\n");
        _exit(1);
    }
}