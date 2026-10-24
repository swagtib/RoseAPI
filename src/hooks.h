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
#include <frida-gum.h>
#include "plugin/plugin.h"
#include "macro.h"

extern GumInterceptor *interceptor;

typedef struct {
    void* callback;
    Plugin* owner;
} Hook;

int setuphooks(void);
void destroypluginhooks(Plugin* ptr);

#define GET_TRAMPOLINE(x) CONCAT(x, Tramp)
#define CREATE_TRAMPOLINE(x) static gpointer GET_TRAMPOLINE(x)
#define GET_CALLBACK(x) CONCAT(x, Hook)

#define CREATE_HOOK(name, func) \
g_hash_table_insert(hooks, STRINGIFY(name), NULL); \
g_hash_table_insert(hooks, STRINGIFY(CONCAT(Post, name)), NULL); \
gum_interceptor_replace(interceptor, func, GET_CALLBACK(name), &GET_TRAMPOLINE(name), NULL);

// void hooks
#define RUN_VOID_HOOK(name, cast, args) \
GSList* list = g_hash_table_lookup(hooks, STRINGIFY(name)); \
if (list) \
{ \
    for (GSList* entry = list; entry != NULL; entry = entry->next) \
    { \
        if (entry->data) \
        { \
            Hook* hook = entry->data; \
            cast callback = hook->callback; \
            callback args; \
        } \
    } \
}

#define RUN_VOID_TRAMPOLINE(x, cast, args) \
cast trampoline = GET_TRAMPOLINE(x); \
trampoline args;

// return vals
#define RUN_TRAMPOLINE(x, cast, args, storein) \
cast trampoline = GET_TRAMPOLINE(x); \
storein = trampoline args;

#define RUN_HOOK(name, cast, args, storein) \
GSList* list = g_hash_table_lookup(hooks, STRINGIFY(name)); \
if (list) \
{ \
    for (GSList* entry = list; entry != NULL; entry = entry->next) \
    { \
        if (entry->data) \
        { \
            Hook* hook = entry->data; \
            cast callback = hook->callback; \
            storein = callback args; \
        } \
    } \
}

// callbacks
#define CREATE_VOID_STD_CALLBACK(name, sig, cast, args) \
CREATE_TRAMPOLINE(name); \
static void GET_CALLBACK(name) sig \
{ \
    pthread_mutex_lock(&hookmutex); \
    RUN_VOID_HOOK(name, cast, args) \
    if (!vetoed) \
    { \
        RUN_VOID_TRAMPOLINE(name, cast, args) \
        RUN_VOID_HOOK(CONCAT(Post, name), cast, args) \
    } \
    vetoed = 0; \
    pthread_mutex_unlock(&hookmutex); \
}

#define CREATE_STD_CALLBACK(name, sig, cast, args, returntype) \
CREATE_TRAMPOLINE(name); \
static returntype GET_CALLBACK(name) sig \
{ \
    pthread_mutex_lock(&hookmutex); \
    returntype returnval = 0x0; \
    RUN_HOOK(name, cast, args, returnval) \
    if (!vetoed) \
    { \
        RUN_TRAMPOLINE(name, cast, args, returnval) \
        RUN_HOOK(CONCAT(Post, name), cast, args, returnval) \
    } \
    vetoed = 0; \
    pthread_mutex_unlock(&hookmutex); \
    return returnval; \
}

#endif