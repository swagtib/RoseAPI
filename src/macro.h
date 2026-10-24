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

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)

#define CONCAT_HELPER(x, y) x##y
#define CONCAT(x, y) CONCAT_HELPER(x, y)

#define escapeyellow "\x1b[33m"
#define escapebold "\x1b[1m"
#define escapereset "\x1b[0m"
#define roseapi escapeyellow escapebold "[RoseAPI] " escapereset escapebold

#define LOG(text, ...) fprintf(stdout, roseapi text escapereset , ##__VA_ARGS__)
#define LOG_ERROR(text, ...) fprintf(stderr, roseapi text escapereset , ##__VA_ARGS__)


#endif