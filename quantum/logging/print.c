/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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
#include <stddef.h>
#include "sendchar.h"

// bind lib/printf to console interface - sendchar

static int8_t null_sendchar_func(uint8_t c) {
    return 0;
}
static sendchar_func_t func = null_sendchar_func;

void print_set_sendchar(sendchar_func_t send) {
    func = send;
}

void putchar_(char character) {
    func(character);
}
