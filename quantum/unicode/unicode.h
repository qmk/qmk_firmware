/* Copyright 2022
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

#include <stdint.h>

#include "quantum.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t input_mode : 8;
    };
} unicode_config_t;

extern unicode_config_t unicode_config;

enum unicode_input_modes {
    UNICODE_MODE_MACOS,      // macOS using Unicode Hex Input
    UNICODE_MODE_LINUX,      // Linux using IBus
    UNICODE_MODE_WINDOWS,    // Windows using EnableHexNumpad
    UNICODE_MODE_BSD,        // BSD (not implemented)
    UNICODE_MODE_WINCOMPOSE, // Windows using WinCompose (https://github.com/samhocevar/wincompose)
    UNICODE_MODE_EMACS,      // Emacs is an operating system in search of a good text editor

    UNICODE_MODE_COUNT // Number of available input modes (always leave at the end)
};

void    unicode_input_mode_init(void);
uint8_t get_unicode_input_mode(void);
void    set_unicode_input_mode(uint8_t mode);
void    cycle_unicode_input_mode(int8_t offset);
void    persist_unicode_input_mode(void);

void unicode_input_mode_set_user(uint8_t input_mode);
void unicode_input_mode_set_kb(uint8_t input_mode);

void unicode_input_start(void);
void unicode_input_finish(void);
void unicode_input_cancel(void);

void register_hex(uint16_t hex);
void register_hex32(uint32_t hex);
void register_unicode(uint32_t code_point);

void send_unicode_string(const char *str);

// clang-format off

#define UC_BSPC UC(0x0008) // (backspace)

#define UC_SPC  UC(0x0020) // (space)
#define UC_EXLM UC(0x0021) // !
#define UC_DQUT UC(0x0022) // "
#define UC_HASH UC(0x0023) // #
#define UC_DLR  UC(0x0024) // $
#define UC_PERC UC(0x0025) // %
#define UC_AMPR UC(0x0026) // &
#define UC_QUOT UC(0x0027) // '
#define UC_LPRN UC(0x0028) // (
#define UC_RPRN UC(0x0029) // )
#define UC_ASTR UC(0x002A) // *
#define UC_PLUS UC(0x002B) // +
#define UC_COMM UC(0x002C) // ,
#define UC_DASH UC(0x002D) // -
#define UC_DOT  UC(0x002E) // .
#define UC_SLSH UC(0x002F) // /

#define UC_0    UC(0x0030) // 0
#define UC_1    UC(0x0031) // 1
#define UC_2    UC(0x0032) // 2
#define UC_3    UC(0x0033) // 3
#define UC_4    UC(0x0034) // 4
#define UC_5    UC(0x0035) // 5
#define UC_6    UC(0x0036) // 6
#define UC_7    UC(0x0037) // 7
#define UC_8    UC(0x0038) // 8
#define UC_9    UC(0x0039) // 9
#define UC_COLN UC(0x003A) // :
#define UC_SCLN UC(0x003B) // ;
#define UC_LT   UC(0x003C) // <
#define UC_EQL  UC(0x003D) // =
#define UC_GT   UC(0x003E) // >
#define UC_QUES UC(0x003F) // ?

#define UC_AT   UC(0x0040) // @
#define UC_A    UC(0x0041) // A
#define UC_B    UC(0x0042) // B
#define UC_C    UC(0x0043) // C
#define UC_D    UC(0x0044) // D
#define UC_E    UC(0x0045) // E
#define UC_F    UC(0x0046) // F
#define UC_G    UC(0x0047) // G
#define UC_H    UC(0x0048) // H
#define UC_I    UC(0x0049) // I
#define UC_J    UC(0x004A) // J
#define UC_K    UC(0x004B) // K
#define UC_L    UC(0x004C) // L
#define UC_M    UC(0x004D) // M
#define UC_N    UC(0x004E) // N
#define UC_O    UC(0x004F) // O

#define UC_P    UC(0x0050) // P
#define UC_Q    UC(0x0051) // Q
#define UC_R    UC(0x0052) // R
#define UC_S    UC(0x0053) // S
#define UC_T    UC(0x0054) // T
#define UC_U    UC(0x0055) // U
#define UC_V    UC(0x0056) // V
#define UC_W    UC(0x0057) // W
#define UC_X    UC(0x0058) // X
#define UC_Y    UC(0x0059) // Y
#define UC_Z    UC(0x005A) // Z
#define UC_LBRC UC(0x005B) // [
#define UC_BSLS UC(0x005C) // (backslash)
#define UC_RBRC UC(0x005D) // ]
#define UC_CIRM UC(0x005E) // ^
#define UC_UNDR UC(0x005F) // _

#define UC_GRV  UC(0x0060) // `
#define UC_a    UC(0x0061) // a
#define UC_b    UC(0x0062) // b
#define UC_c    UC(0x0063) // c
#define UC_d    UC(0x0064) // d
#define UC_e    UC(0x0065) // e
#define UC_f    UC(0x0066) // f
#define UC_g    UC(0x0067) // g
#define UC_h    UC(0x0068) // h
#define UC_i    UC(0x0069) // i
#define UC_j    UC(0x006A) // j
#define UC_k    UC(0x006B) // k
#define UC_l    UC(0x006C) // l
#define UC_m    UC(0x006D) // m
#define UC_n    UC(0x006E) // n
#define UC_o    UC(0x006F) // o

#define UC_p    UC(0x0070) // p
#define UC_q    UC(0x0071) // q
#define UC_r    UC(0x0072) // r
#define UC_s    UC(0x0073) // s
#define UC_t    UC(0x0074) // t
#define UC_u    UC(0x0075) // u
#define UC_v    UC(0x0076) // v
#define UC_w    UC(0x0077) // w
#define UC_x    UC(0x0078) // x
#define UC_y    UC(0x0079) // y
#define UC_z    UC(0x007A) // z
#define UC_LCBR UC(0x007B) // {
#define UC_PIPE UC(0x007C) // |
#define UC_RCBR UC(0x007D) // }
#define UC_TILD UC(0x007E) // ~
#define UC_DEL  UC(0x007F) // (delete)
