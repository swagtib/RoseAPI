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
#include <pthread.h>
#include <frida-gum.h>

static void* clihandler(void *arg)
{
    char* line = NULL;
    while (1)
    {
    }
    return NULL;
}



int setupcli(void)
{
    pthread_t clithread;
    if (pthread_create(&clithread, NULL, clihandler, NULL) != 0) return 0;
    if (pthread_detach(clithread) != 0) return 0;
    return 1;
}