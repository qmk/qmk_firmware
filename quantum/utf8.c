/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "utf8.h"

// Borrowed from https://nullprogram.com/blog/2017/10/06/
const char *decode_utf8(const char *str, int32_t *code_point) {
    const char *next;

    if (str[0] < 0x80) { // U+0000-007F
        *code_point = str[0];
        next        = str + 1;
    } else if ((str[0] & 0xE0) == 0xC0) { // U+0080-07FF
        *code_point = ((int32_t)(str[0] & 0x1F) << 6) | ((int32_t)(str[1] & 0x3F) << 0);
        next        = str + 2;
    } else if ((str[0] & 0xF0) == 0xE0) { // U+0800-FFFF
        *code_point = ((int32_t)(str[0] & 0x0F) << 12) | ((int32_t)(str[1] & 0x3F) << 6) | ((int32_t)(str[2] & 0x3F) << 0);
        next        = str + 3;
    } else if ((str[0] & 0xF8) == 0xF0 && (str[0] <= 0xF4)) { // U+10000-10FFFF
        *code_point = ((int32_t)(str[0] & 0x07) << 18) | ((int32_t)(str[1] & 0x3F) << 12) | ((int32_t)(str[2] & 0x3F) << 6) | ((int32_t)(str[3] & 0x3F) << 0);
        next        = str + 4;
    } else {
        *code_point = -1;
        next        = str + 1;
    }

    // part of a UTF-16 surrogate pair - invalid
    if (*code_point >= 0xD800 && *code_point <= 0xDFFF) {
        *code_point = -1;
    }

    return next;
}
