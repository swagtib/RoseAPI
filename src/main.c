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

#include <frida-gum.h>
#include "macro.h"
#include "bootstrap.h"

void __attribute__((constructor)) start()
{
    gum_init_embedded();
    GumModule* module = gum_process_get_main_module();
    if (!module)
    {
        LOG_ERROR("failed obtaining module\n");
        ragequit;
    }
    const GumMemoryRange* range = gum_module_get_range(module);
    if (!range)
    {
        LOG_ERROR("failed obtaining range\n");
        ragequit;
    }
    LOG("base address: %#lx\n", range->base_address);
    bootstrapapi(range->base_address);
}