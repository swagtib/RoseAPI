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
#include "macro.h"
#include <stdio.h>
#include <stdarg.h>

#define ANSI_ESCAPE "\x1b"
#define ANSI_BOLD "[1;"
#define ANSI_YELLOW "33m"
#define ANSI_WHITE "97m"
#define ANSI_RED "31m"
#define ANSI_RESET ANSI_ESCAPE "[0m"

#define TITLE "[RoseAPI] "
#define ANSI_TITLE ANSI_ESCAPE ANSI_BOLD ANSI_YELLOW TITLE ANSI_RESET


void pretty_log(int log, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    switch (log) {
        case LOG_INFO:
        fputs(ANSI_TITLE ANSI_ESCAPE ANSI_BOLD ANSI_WHITE, stdout);
        vfprintf(stdout, fmt, args);
        fputs(ANSI_RESET, stdout);
        break;

        case LOG_ERROR:
        fputs(ANSI_TITLE ANSI_ESCAPE ANSI_BOLD ANSI_RED, stderr);
        vfprintf(stderr, fmt, args);
        fputs(ANSI_RESET, stderr);
        break;
    }
    va_end(args);
}