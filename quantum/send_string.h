/* Copyright 2021
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

#include <stdint.h>

#include "progmem.h"
#include "send_string_keycodes.h"

#define SEND_STRING(string) send_string_P(PSTR(string))
#define SEND_STRING_DELAY(string, interval) send_string_with_delay_P(PSTR(string), interval)

// Look-Up Tables (LUTs) to convert ASCII character to keycode sequence.
extern const uint8_t ascii_to_keycode_lut[128];
extern const uint8_t ascii_to_shift_lut[16];
extern const uint8_t ascii_to_altgr_lut[16];
extern const uint8_t ascii_to_dead_lut[16];

// clang-format off
#define KCLUT_ENTRY(a, b, c, d, e, f, g, h) \
    ( ((a) ? 1 : 0) << 0 \
    | ((b) ? 1 : 0) << 1 \
    | ((c) ? 1 : 0) << 2 \
    | ((d) ? 1 : 0) << 3 \
    | ((e) ? 1 : 0) << 4 \
    | ((f) ? 1 : 0) << 5 \
    | ((g) ? 1 : 0) << 6 \
    | ((h) ? 1 : 0) << 7 )
// clang-format on

void send_string(const char *str);
void send_string_with_delay(const char *str, uint8_t interval);
void send_string_P(const char *str);
void send_string_with_delay_P(const char *str, uint8_t interval);
void send_char(char ascii_code);
