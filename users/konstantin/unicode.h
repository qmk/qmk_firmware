/* Copyright 2019-2021 Konstantin Đorđević <vomindoraan@gmail.com>
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

#pragma once

#include "quantum.h"

#define FOREACH_UNICODE(M) \
    M(COMMA,   0x002C)     \
    M(L_PAREN, 0x0028)     \
    M(R_PAREN, 0x0029)     \
    M(EQUALS,  0x003D)     \
    M(TIMES,   0x00D7)     \
    M(DIVIDE,  0x00F7)     \
    M(MINUS,   0x2212)

#define UC_KEYCODE(name, code)  name = UC(code),

#define UCM_NAME(name, code)    UCM_ ## name,
#define UCM_ENTRY(name, code)   [UCM_ ## name] = code,
#define UCM_KEYCODE(name, code) name = X(UCM_ ## name),

#if defined(UNICODE_ENABLE)
enum unicode_keycodes {
    FOREACH_UNICODE(UC_KEYCODE)
};
#elif defined(UNICODEMAP_ENABLE)
enum unicode_names {
    FOREACH_UNICODE(UCM_NAME)
};

extern const uint32_t PROGMEM unicode_map[];

enum unicode_keycodes {
    FOREACH_UNICODE(UCM_KEYCODE)
};
#endif
