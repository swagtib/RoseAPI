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

#include "plugin/plugin.h"
#include <libtcc.h>
#include "plugin/cplugin.h"

Plugin* loadCPlugin(const char *path)
{
    TCCState* state = tcc_new();
    if (!state) return NULL;
    if (tcc_set_output_type(state, TCC_OUTPUT_MEMORY) == -1) goto cleanupstate;
    if (tcc_add_file(state, path) == -1) goto cleanupstate;
    if (tcc_relocate(state) == -1) goto cleanupstate;
    void (*plugin_init)(void) = tcc_get_symbol(state, "plugin_init");
    if (!plugin_init) goto cleanupstate;
    Plugin* plugin = constructplugin();
    if (!plugin) goto cleanupstate;
    plugin->ptype = C_PLUGIN_PTYPE;
    plugin->state = state;
    plugin_init();
    return plugin;
    cleanupstate:
    tcc_delete(state);
    return NULL;
}