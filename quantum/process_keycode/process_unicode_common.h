/* Copyright 2017 Jack Humbert
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

#if defined(UNICODE_ENABLE) + defined(UNICODEMAP_ENABLE) + defined(UCIS_ENABLE) > 1
#    error "Cannot enable more than one Unicode method (UNICODE, UNICODEMAP, UCIS) at the same time"
#endif

// Keycodes used for starting Unicode input on different platforms
#ifndef UNICODE_KEY_MAC
#    define UNICODE_KEY_MAC KC_LEFT_ALT
#endif
#ifndef UNICODE_KEY_LNX
#    define UNICODE_KEY_LNX LCTL(LSFT(KC_U))
#endif
#ifndef UNICODE_KEY_WINC
#    define UNICODE_KEY_WINC KC_RIGHT_ALT
#endif

// Comma-delimited, ordered list of input modes selected for use (e.g. in cycle)
// Example: #define UNICODE_SELECTED_MODES UC_WINC, UC_LNX
#ifndef UNICODE_SELECTED_MODES
#    define UNICODE_SELECTED_MODES -1
#endif

// Whether input mode changes in cycle should be written to EEPROM
#ifndef UNICODE_CYCLE_PERSIST
#    define UNICODE_CYCLE_PERSIST true
#endif

// Delay between starting Unicode input and sending a sequence, in ms
#ifndef UNICODE_TYPE_DELAY
#    define UNICODE_TYPE_DELAY 10
#endif

// Deprecated aliases
#if !defined(UNICODE_KEY_MAC) && defined(UNICODE_KEY_OSX)
#    define UNICODE_KEY_MAC UNICODE_KEY_OSX
#endif
#if !defined(UNICODE_SONG_MAC) && defined(UNICODE_SONG_OSX)
#    define UNICODE_SONG_MAC UNICODE_SONG_OSX
#endif
#define UC_OSX UC_MAC

enum unicode_input_modes {
    UC_MAC,   // macOS using Unicode Hex Input
    UC_LNX,   // Linux using IBus
    UC_WIN,   // Windows using EnableHexNumpad
    UC_BSD,   // BSD (not implemented)
    UC_WINC,  // Windows using WinCompose (https://github.com/samhocevar/wincompose)
    UC_EMACS, // Emacs is an operating system in search of a good text editor
    UC__COUNT // Number of available input modes (always leave at the end)
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t input_mode : 8;
    };
} unicode_config_t;

extern unicode_config_t unicode_config;

void    unicode_input_mode_init(void);
uint8_t get_unicode_input_mode(void);
void    set_unicode_input_mode(uint8_t mode);
void    cycle_unicode_input_mode(int8_t offset);
void    persist_unicode_input_mode(void);

void unicode_input_start(void);
void unicode_input_finish(void);
void unicode_input_cancel(void);

void register_hex(uint16_t hex);
void register_hex32(uint32_t hex);
void register_unicode(uint32_t code_point);

void send_unicode_string(const char *str);

bool process_unicode_common(uint16_t keycode, keyrecord_t *record);

#define UC_BSPC UC(0x0008)
#define UC_SPC UC(0x0020)

#define UC_EXLM UC(0x0021)
#define UC_DQUT UC(0x0022)
#define UC_HASH UC(0x0023)
#define UC_DLR UC(0x0024)
#define UC_PERC UC(0x0025)
#define UC_AMPR UC(0x0026)
#define UC_QUOT UC(0x0027)
#define UC_LPRN UC(0x0028)
#define UC_RPRN UC(0x0029)
#define UC_ASTR UC(0x002A)
#define UC_PLUS UC(0x002B)
#define UC_COMM UC(0x002C)
#define UC_DASH UC(0x002D)
#define UC_DOT UC(0x002E)
#define UC_SLSH UC(0x002F)

#define UC_0 UC(0x0030)
#define UC_1 UC(0x0031)
#define UC_2 UC(0x0032)
#define UC_3 UC(0x0033)
#define UC_4 UC(0x0034)
#define UC_5 UC(0x0035)
#define UC_6 UC(0x0036)
#define UC_7 UC(0x0037)
#define UC_8 UC(0x0038)
#define UC_9 UC(0x0039)

#define UC_COLN UC(0x003A)
#define UC_SCLN UC(0x003B)
#define UC_LT UC(0x003C)
#define UC_EQL UC(0x003D)
#define UC_GT UC(0x003E)
#define UC_QUES UC(0x003F)
#define UC_AT UC(0x0040)

#define UC_A UC(0x0041)
#define UC_B UC(0x0042)
#define UC_C UC(0x0043)
#define UC_D UC(0x0044)
#define UC_E UC(0x0045)
#define UC_F UC(0x0046)
#define UC_G UC(0x0047)
#define UC_H UC(0x0048)
#define UC_I UC(0x0049)
#define UC_J UC(0x004A)
#define UC_K UC(0x004B)
#define UC_L UC(0x004C)
#define UC_M UC(0x004D)
#define UC_N UC(0x004E)
#define UC_O UC(0x004F)
#define UC_P UC(0x0050)
#define UC_Q UC(0x0051)
#define UC_R UC(0x0052)
#define UC_S UC(0x0053)
#define UC_T UC(0x0054)
#define UC_U UC(0x0055)
#define UC_V UC(0x0056)
#define UC_W UC(0x0057)
#define UC_X UC(0x0058)
#define UC_Y UC(0x0059)
#define UC_Z UC(0x005A)

#define UC_LBRC UC(0x005B)
#define UC_BSLS UC(0x005C)
#define UC_RBRC UC(0x005D)
#define UC_CIRM UC(0x005E)
#define UC_UNDR UC(0x005F)

#define UC_GRV UC(0x0060)

#define UC_a UC(0x0061)
#define UC_b UC(0x0062)
#define UC_c UC(0x0063)
#define UC_d UC(0x0064)
#define UC_e UC(0x0065)
#define UC_f UC(0x0066)
#define UC_g UC(0x0067)
#define UC_h UC(0x0068)
#define UC_i UC(0x0069)
#define UC_j UC(0x006A)
#define UC_k UC(0x006B)
#define UC_l UC(0x006C)
#define UC_m UC(0x006D)
#define UC_n UC(0x006E)
#define UC_o UC(0x006F)
#define UC_p UC(0x0070)
#define UC_q UC(0x0071)
#define UC_r UC(0x0072)
#define UC_s UC(0x0073)
#define UC_t UC(0x0074)
#define UC_u UC(0x0075)
#define UC_v UC(0x0076)
#define UC_w UC(0x0077)
#define UC_x UC(0x0078)
#define UC_y UC(0x0079)
#define UC_z UC(0x007A)

#define UC_LCBR UC(0x007B)
#define UC_PIPE UC(0x007C)
#define UC_RCBR UC(0x007D)
#define UC_TILD UC(0x007E)
#define UC_DEL UC(0x007F)
