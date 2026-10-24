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

#ifndef PLUGIN_H
#define PLUGIN_H
#include "cli.h"

typedef struct {
    unsigned int ptype;
    void* state;
} Plugin;

Plugin* constructplugin(void);
void destructplugin(Plugin* ptr);
void enableplugin(ARGSCLI);
void disableplugin(ARGSCLI);
int setupPlugins(void);

#endif