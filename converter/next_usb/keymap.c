/*
NeXT non-ADB Keyboard USB Converter
 
Copyright 2013, Benjamin Gould (bgould@github.com)

Based on:
---------
* TMK firmware code Copyright 2011,2012 Jun WAKO <wakojun@gmail.com>
* Arduino code by "Ladyada" Limor Fried (http://ladyada.net/, http://adafruit.com/) \
    released under BSD license \
    https://github.com/adafruit/USB-NeXT-Keyboard

Timing reference thanks to http://m0115.web.fc2.com/ (dead link), http://cfile7.uf.tistory.com/image/14448E464F410BF22380BB
Pinouts thanks to http://www.68k.org/~degs/nextkeyboard.html
Keycodes from http://ftp.netbsd.org/pub/NetBSD/NetBSD-release-6/src/sys/arch/next68k/dev/

This software is licensed with a Modified BSD License.
All of this is supposed to be Free Software, Open Source, DFSG-free,
GPL-compatible, and OK to use in both free and proprietary applications.
Additions and corrections to this file are welcome.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in
  the documentation and/or other materials provided with the
  distribution.

* Neither the name of the copyright holders nor the names of
  contributors may be used to endorse or promote products derived
  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"
#include "keycode.h"

// 32*8(256) byte array which converts PS/2 code into USB code
static const uint16_t PROGMEM fn_actions[] = {
    ACTION_LAYER_MOMENTARY(1),                  // FN0 - left command key
    ACTION_LAYER_MOMENTARY(1),                  // FN1 - right command key
    ACTION_KEY(KC_BSLS),                        // FN2 - number pad slash & backslash
    ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),         // FN3 - number pad equals & pipe
    ACTION_MODS_KEY(MOD_LCTL, KC_Z),            // FN4 - cmd+undo  on layer 1
    ACTION_MODS_KEY(MOD_LCTL, KC_X),            // FN5 - cmd+cut   on layer 1
    ACTION_MODS_KEY(MOD_LCTL, KC_C),            // FN6 - cmd+copy  on layer 1
    ACTION_MODS_KEY(MOD_LCTL, KC_V),            // FN7 - cmd+paste on layer 1
};

/* This is the physical layout that I am starting with:
 *   Note: there is some strangeness on the number pad; 
 *         the equal sign shifts to pipe and forward slash shifts to backslash
 * ,-----------------------------------------------------------. ,-----------. ,---------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   BS  | |VUp|Pwr|BrU| |`  |  =|  /|  *|
 * |-----------------------------------------------------------| |-----------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     | |VDn|   |BrD| |  7|  8|  9|  -|
 * |------------------------------------------------------     | `---'   `---' |-----------|---|
 * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return|               |  4|  5|  6|  +|
 * |-----------------------------------------------------------|     ,---.     |---------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |     |Up |     |  1|  2|  3|   |
 * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
 * |Alt  |Cmd  |              Space                |Cmd  |Alt  | |Lef|Dow|Rig| |      0|  .|   |
 * `-----------------------------------------------------------' `-----------' `---------------'
 *
 * Keymap array:
 *     8 bytes
 *   +---------+
 *  0|         |
 *  :|         | 0x00-0x87
 *  ;|         |
 * 11|         |
 *   +---------+
 */
#define KEYMAP( \
    K49,K4A,K4B,K4C,K4D,K50,K4F,K4E,K1E,K1F,K20,K1D,K1C,K1B,  K1A,K58,K19,  K26,K27,K28,K25, \
    K41,K42,K43,K44,K45,K48,K47,K46,K06,K07,K08,K05,K04,K03,  K02,    K01,  K21,K22,K23,K24, \
    K57,K39,K3A,K3B,K3C,K3D,K40,K3F,K3E,K2D,K2C,K2B,    K2A,                K12,K18,K13,K15, \
    K56,    K31,K32,K33,K34,K35,K37,K36,K2E,K2F,K30,    K55,      K16,      K11,K17,K14,     \
    K52,K54,                  K38,                  K53,K51,  K09,K0F,K10,  K0B,    K0C,K0D  \
) { \
    { KC_NO,    KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_##K10, KC_##K0B, KC_##K0C, KC_##K0D, KC_NO,    KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_NO,    KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, \
    { KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
}


static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    /* Layer 0: default
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|   BS  | |Ins|Ref|Hom| |`  |  =|  /|  *|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     | |Del|   |End| |  7|  8|  9|  -|
     * |-----------------------------------------------------'     | `---'   `---' |-----------|---|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return|               |  4|  5|  6|  +|
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Fn0  |Alt  |              Space                |LGui |Fn1  | |Lef|Dow|Rig| |      0|  .|   |
     * `-----------------------------------------------------------' `-----------' `---------------'
     */
    KEYMAP(
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,  INS, WREF,HOME,  GRV, FN3, FN2, PAST,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,NO,    DEL,      END,   P7,  P8,  P9,  PMNS,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                    P4,  P5,  P6,  PPLS,
    LSFT,     Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT,       UP,         P1,  P2,  P3,  
    FN0, LALT,                    SPC,                          LGUI,FN1,  LEFT,DOWN,RGHT,  P0,       PDOT,PENT
    
    ),

    /* Layer 1: extra keys
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |Grv| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   BS  | |VUp|VMu|PgU| |`  |  =|  /|  *|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |Pau|  W|  E|  R|  T|  Y|  U|  I|  O|PSc|  \|  ]|     | |VDn|   |PgD| |  7|  8|  9|  -|
     * |-----------------------------------------------------'     | `---'   `---' |-----------|---|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  Return|               |  4|  5|  6|  +|
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shift   |UND|CUT|COP|PST|  B|  N|  M|  ,|  .|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Fn0  |Alt  |              Space                |RGui |Fn1  | |Lef|Dow|Rig| |      0|  .|   |
     * `-----------------------------------------------------------' `-----------' `---------------'
     */
    KEYMAP(
    
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,  VOLU,MUTE,PGUP,  TRNS,TRNS,TRNS,TRNS,
    TRNS,PAUS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,FN3, BSLS,TRNS,  VOLD,     PGDN,  BTN1,MS_U,BTN2,WH_U,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,                   MS_L,MS_D,MS_R,WH_D,
    TRNS,     FN4, FN5, FN6, FN7, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,       TRNS,       TRNS,TRNS,TRNS,  
    TRNS,RALT,                    TRNS,                         RGUI,TRNS,  TRNS,TRNS,TRNS,  TRNS,     TRNS,TRNS
    
    )
};

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, key_t key)
{
    return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    return (action_t){ .code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]) };
}
