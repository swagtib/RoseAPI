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

#include <stdint.h>
#include "engine.h"
#include <frida-gum.h>
#include "macro.h"
#include "hooks.h"

static int initialize(void)
{
    return 1;
}

static gpointer resetTrampoline;
static void resetsafetynet(void)
{
    resetGame_ft callback = resetTrampoline;
    callback();
    gum_interceptor_revert(g_interceptor, resetGame);
    pretty_log(LOG_INFO, "engine ready\n");
    if (!initialize()) ragequit;
}

void bootstrapapi(uintptr_t base)
{
    setup38offsets(base);
    g_interceptor = gum_interceptor_obtain(); //we cache it globally to avoid reference leaks
    if (!g_interceptor) ragequit;
    if (gum_interceptor_replace(g_interceptor, resetGame, resetsafetynet, &resetTrampoline, NULL) != GUM_REPLACE_OK) ragequit;
}