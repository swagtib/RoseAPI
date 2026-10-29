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

#define _GNU_SOURCE
#include "plugin/plugin.h"
#include "macro.h"
#include "frida-gum.h"
#include <stdarg.h>
#include <stdio.h>
#include <libtcc.h>
#include <errno.h>
#include <string.h>
#include <roseapi.h>

#define ANSI_ESCAPE "\x1b"
#define ANSI_BOLD "[1;"
#define ANSI_YELLOW "33m"
#define ANSI_WHITE "97m"
#define ANSI_RED "31m"
#define ANSI_BLUE "34m"
#define ANSI_RESET ANSI_ESCAPE "[0m"

#define LOGCOLOR1 ANSI_ESCAPE ANSI_BOLD ANSI_YELLOW
#define LOGCOLOR2 ANSI_ESCAPE ANSI_BOLD ANSI_WHITE
#define PLUGINLOG ANSI_ESCAPE ANSI_BOLD ANSI_BLUE
#define ERRORCOLOR ANSI_ESCAPE ANSI_BOLD ANSI_RED

static void api_vlog(FILE* file, const char *color1, const char *prefix, int appenderr, const char *color2, const char *fmt, va_list args)
{
    flockfile(file);
    fputs(color1, file);
    if (appenderr)
    {
        fprintf(file, "[%s Error] ", prefix);
    } else fprintf(file, "[%s] ", prefix);
    fputs(ANSI_RESET, file);
    fputs(color2, file);
    vfprintf(file, fmt, args);
    fputs(ANSI_RESET "\n", file);
    funlockfile(file);
}

static void api_log(FILE* file, const char *color1, const char *prefix, int appenderr, const char *color2, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    api_vlog(file, color1, prefix, appenderr, color2, fmt, args);
    va_end(args);
}

void roseapi_log(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    api_vlog(stdout, LOGCOLOR1, "RoseAPI", 0, LOGCOLOR2, fmt, args);
    va_end(args);
}

void roseapi_error(const char *msg)
{
    int err = errno;
    char errmsg[1024];
    char *desc = strerror_r(err, errmsg, sizeof(errmsg));
    if (!desc) desc = "unk";
    api_log(stderr, ERRORCOLOR, "RoseAPI", 1, ERRORCOLOR, "%s::%s::errno:%d", msg, desc, err);
}

void roseapi_ferror(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    api_vlog(stderr, ERRORCOLOR, "RoseAPI", 1, ERRORCOLOR, fmt, args);
    va_end(args);
}

void roseapi_gerror(GError *error)
{
    if (!error) return;
    api_log(stderr, ERRORCOLOR, "RoseAPI GLib", 1, ERRORCOLOR, "domain:%u::code:%d::%s", error->domain, error->code, error->message);
}

void tcc_error(void *opaque, const char *msg)
{
    if (!msg) return;
    api_log(stderr, ERRORCOLOR, "TCC", 1,ERRORCOLOR, "%s", msg);
}

// public

void plugin_log(PluginContext ctx, const char *msg, ...)
{
    if (!plugincheckcontext(ctx)) return;
    Plugin* plugin = ctx;
    va_list args;
    va_start(args, msg);
    api_vlog(stderr, PLUGINLOG, plugin->name, 0, LOGCOLOR2, msg, args);
    va_end(args);
}

void plugin_error(PluginContext ctx, const char *msg, ...)
{
    if (!plugincheckcontext(ctx)) return;
    Plugin* plugin = ctx;
    va_list args;
    va_start(args, msg);
    api_vlog(stderr, ERRORCOLOR, plugin->name, 1, ERRORCOLOR, msg, args);
    va_end(args);
}