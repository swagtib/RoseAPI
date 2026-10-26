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

#ifndef HOOKS_H
#define HOOKS_H

#include "plugin/plugin.h"
#include <frida-gum.h>

extern GumInterceptor* g_interceptor;
int setupHooks(void);

#define INTERCEPT(idx, func, replace) gum_interceptor_replace(g_interceptor, func, replace, &hooks[idx].trampoline, NULL)

typedef struct {
    void* callback;
    Plugin* owner;
} HookCallback;

typedef struct {
    gpointer trampoline;
    GPtrArray* pre;
    GPtrArray* post;
    int occupied;
} Hook;

typedef struct HookScope {
    Hook *hook;
    int veto;
    struct HookScope *previous;
} HookScope;

enum {
    HOOK_EXAMPLE,
    HOOK_COUNT
} Hooks;

extern Hook hooks[HOOK_COUNT];

#endif