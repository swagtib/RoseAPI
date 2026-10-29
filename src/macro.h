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

#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>
#include <frida-gum.h>

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)

#define CONCAT_HELPER(x, y) x##y
#define CONCAT(x, y) CONCAT_HELPER(x, y)
#define ragequit exit(EXIT_FAILURE)

// logs a format with variadic arguments
void roseapi_log(const char *fmt, ...);

// behaves the same as perror
void roseapi_error(const char *msg);

// logs an error format
void roseapi_ferror(const char *fmt, ...);

// logs a gerror
void roseapi_gerror(GError *error);

void tcc_error(void *opaque, const char *msg);

#endif