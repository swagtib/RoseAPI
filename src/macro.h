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
#include <stdio.h>

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)

#define CONCAT_HELPER(x, y) x##y
#define CONCAT(x, y) CONCAT_HELPER(x, y)
#define ragequit exit(EXIT_FAILURE)

void pretty_log(int log, const char* fmt, ...);

enum {
    LOG_INFO,
    LOG_ERROR
};

#endif