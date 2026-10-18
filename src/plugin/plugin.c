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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "macro.h"
#include <dirent.h>

// could still warrant some work but it works as is

static int mkdirplugins(void)
{
    int status = mkdir("plugins", 0755);
    if ((status == 0) || (status != 0 && errno == EEXIST))
    {
        return 1;
    }
    return 0;
}

static int createpluginstxt(void)
{
    FILE* file = fopen("enabledplugins.txt", "a+");
    if (!file) return 0;
    rewind(file);
    if (fgetc(file) == EOF && !ferror(file))
    {
        DIR* dir = opendir("plugins");
        if (!dir)
        {
            fclose(file);
            return 0;
        }
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] == '.') continue;
            char* ext = strrchr(entry->d_name, '.');
            if (!ext) continue;
            if (strcmp(ext, ".c") == 0)
            {
                fprintf(file, "%s\n", entry->d_name);
            }
        }
        closedir(dir);
    }
    fclose(file);
    return 1;
}

void checkpluginfiles()
{
    if (!mkdirplugins() || !createpluginstxt())
    {
        LOG_ERROR("failed checking plugins folder or txt\n");
        _exit(1);
    }
}

