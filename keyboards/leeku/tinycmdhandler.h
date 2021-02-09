/* Copyright 2015 LeeKu <https://github.com/leeku11>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TINYCMDHANDLER_H
#define TINYCMDHANDLER_H

#include "tinycmdpkt.h"

typedef uint8_t (*tinycmd_handler_func)(tinycmd_pkt_req_type *);

typedef struct {
    uint8_t cmd;
    tinycmd_handler_func p_func;
}tinycmd_handler_array_type;

#endif // TINYCMDHANDLER_H

