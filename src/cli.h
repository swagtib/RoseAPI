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

#ifndef CLI_H
#define CLI_H

#include "plugin/plugin.h"
#include "roseapi.h"
#include <frida-gum.h>

int setupcli(void);

extern GHashTable* commands;

typedef struct {
    CLICallback callback;
    Plugin* owner;
} Command;

typedef struct {
    char *name;
    char **argv;
    int argc;
} ExecutedCommand;

extern GAsyncQueue* executedcmd;

#endif