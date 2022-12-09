/*
Copyright 2022 Jeff Shufelt <jshuf@puppyfish.com> @jshuf

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

#include QMK_KEYBOARD_H

/* Matrix compression for the usb_usb converter - a brief primer

   First, a quick look at how the converter works.
   Instead of looking for connected I/O pins on the PCB's MCU
   to set/unset cells in the scan matrix, the usb_usb converter uses
   USB HID codes coming from the keyboard as indices into the
   scan matrix - specifically, a 16x16 scan matrix, where the first
   4 bits of the USB HID code are used as a row index into the scan
   matrix, and the second 4 bits index are used as a column index.
   This is the default implementation in usb_usb/custom_matrix.cpp.

   However, using a scan matrix of this size will be limiting in VIA,
   which stores its dynamic keymap in EEPROM.  The Atmega32U4
   used by the usb_usb converter has 1K=1024 bytes of EEPROM storage.
   Each cell of a scan matrix is 2 bytes wide, so a single keymap layer
   for a 16x16 scan matrix consumes 16x16x2 = 512 bytes.
   Taking VIA as an example dynamic keymap implementation:
   since VIA needs a small additional amount of EEPROM for its
   own internal state, above and beyond the dynamic keymaps,
   the use of a 16x16 scan matrix would mean that we only have
   enough room for one keymap layer in VIA.

   We can improve upon this by observing that only 142 USB HID codes
   are actually handled by the converter in the LAYOUT macro, leaving
   256-142=114 unused entries (228 bytes) in the scan matrix.  So, if we
   can somehow use the 142 codes to index into a smaller scan matrix,
   say a 9x16=144 (288 byte) scan matrix, then we can pack up to three
   dynamic keymap layers into the EEPROM.

   To do that, we just need to establish a mapping from USB HID
   hex codes to row,col indices into the 9x16 scan matrix, and use
   that mapping whenever we need to index into the scan matrix using
   a USB HID code.  Since this mapping is fixed, it doesn't need
   to reside in EEPROM, and can instead be stored in flash.
   That mapping (and its inverse) are defined as PROGMEM in
   usb_usb/custom_matrix.cpp.
*/

/* This layout macro uses 9x16 scan matrix, for use
   only when COMPRESS_MATRIX is defined, so it is placed here
   to avoid confusion with the standard set of LAYOUT macros
   in usb_usb.h. */
#define LAYOUT_via( \
            K01,K02,K03,K04,K05,K06,K07,K08,K09,K0A,K0B,K0C,                                              \
    K00,    K0D,K0E,K0F,K10,K11,K12,K13,K14,K15,K16,K17,K18,      K19,K1A,K1B,  K1C,K1D,K1E,K1F, K20,     \
    K21,K22,K23,K24,K25,K26,K27,K28,K29,K2A,K2B,K2C,K2D,K2E,K2F,  K30,K31,K32,  K33,K34,K35,K36, K37,K38, \
    K39,K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,    K46,  K47,K48,K49,  K4A,K4B,K4C,K4D, K4E,K4F, \
    K50,K51,K52,K53,K54,K55,K56,K57,K58,K59,K5A,K5B,    K5C,K5D,                K5E,K5F,K60,K61, K62,K63, \
    K81,K64,K65,K66,K67,K68,K69,K6A,K6B,K6C,K6D,K6E,    K6F,K85,      K70,      K71,K72,K73,K74, K75,K76, \
    K80,K83,K82,K77,K78,    K79,    K7A,K7B,K7C,K86,K87,K7D,K84,  K7E,K7F,K88,  K89,    K8A,K8B, K8C,K8D  \
) { \
   { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F}, \
   { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F}, \
   { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F}, \
   { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F}, \
   { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E, K4F}, \
   { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C, K5D, K5E, K5F}, \
   { K60, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6A, K6B, K6C, K6D, K6E, K6F}, \
   { K70, K71, K72, K73, K74, K75, K76, K77, K78, K79, K7A, K7B, K7C, K7D, K7E, K7F}, \
   { K80, K81, K82, K83, K84, K85, K86, K87, K88, K89, K8A, K8B, K8C, K8D, XXX, XXX}, \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: plain Qwerty without layer switching
     *         ,---------------. ,---------------. ,---------------.
     *         |F13|F14|F15|F16| |F17|F18|F19|F20| |F21|F22|F23|F24|
     * ,---.   |---------------| |---------------| |---------------| ,-----------. ,---------------. ,-------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau| |VDn|VUp|Mut|Pwr| | Help  |
     * `---'   `---------------' `---------------' `---------------' `-----------' `---------------' `-------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------. ,-------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|JPY|Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -| |Stp|Agn|
     * |-----------------------------------------------------------| |-----------| |---------------| |-------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |Del|End|PgD| |  7|  8|  9|  +| |Mnu|Und|
     * |-----------------------------------------------------------| `-----------' |---------------| |-------|
     * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  :|  #|Retn|               |  4|  5|  6|KP,| |Sel|Cpy|
     * |-----------------------------------------------------------|     ,---.     |---------------| |-------|
     * |Shft|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /| RO|Shift |     |Up |     |  1|  2|  3|KP=| |Exe|Pst|
     * |-----------------------------------------------------------| ,-----------. |---------------| |-------|
     * |Ctl|Gui|Alt|MHEN|HNJ| Space  |H/E|HENK|KANA|Alt|Gui|App|Ctl| |Lef|Dow|Rig| |  0    |  .|Ent| |Fnd|Cut|
     * `-----------------------------------------------------------' `-----------' `---------------' `-------'
     */
    [0] = LAYOUT_via(
                      KC_F13,  KC_F14,  KC_F15,  KC_F16, KC_F17, KC_F18, KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
    KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,               KC_PSCR, KC_SCRL, KC_PAUS,    KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR,     KC_HELP,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_INT3, KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,    KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,    KC_STOP, KC_AGIN,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,     KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,    KC_MENU, KC_UNDO,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_NUHS, KC_ENT,                                    KC_P4,   KC_P5,   KC_P6,   KC_PCMM,    KC_SLCT, KC_COPY,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_INT1,   KC_RSFT,              KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PEQL,    KC_EXEC, KC_PSTE,
    KC_LCTL, KC_LGUI, KC_LALT, KC_INT5, KC_LNG2,         KC_SPC,         KC_LNG1, KC_INT4, KC_INT2, KC_RALT, KC_RGUI, MO(1),   KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT, KC_PENT,    KC_FIND, KC_CUT
    ),
    [1] = LAYOUT_via(
                      ______,  ______,  ______,  ______, ______, ______, ______,  ______,  ______,  ______,  ______,  ______,
    ______,           ______,  ______,  ______,  ______, ______, ______, ______,  ______,  ______,  ______,  ______,  ______,               ______,  ______,  ______,     ______,  ______,  ______,  ______,     ______,
    ______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ______,  ______,      ______,  ______,  ______,     ______,  ______,  ______,  ______,     ______,  ______,
    ______,  ______,  KC_UP,   ______,  ______,  ______, ______, ______, ______,  ______,  ______,  ______,  ______,           ______,      ______,  ______,  ______,     ______,  ______,  ______,  ______,     ______,  ______,
    ______,  KC_LEFT, KC_DOWN, KC_RGHT, ______,  ______, ______, ______, ______,  ______,  ______,  ______,           ______,  ______,                                    ______,  ______,  ______,  ______,     ______,  ______,
    ______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______,  ______,  ______,  ______,           ______,  ______,               ______,              ______,  ______,  ______,  ______,     ______,  ______,
    ______,  ______,  ______,  ______,  ______,          ______,         ______,  ______,  ______,  ______,   MO(2),  ______,  ______,      ______,  ______,  ______,     ______,           ______,  ______,     ______,  ______
    ),
    [2] = LAYOUT_via(
                      ______,  ______,  ______,  ______, ______, ______, ______,  ______,  ______,  ______,  ______,  ______,
     QK_BOOT,           ______,  ______,  ______,  ______, ______, ______, ______,  ______,  ______,  ______,  ______,  ______,               ______,  ______,  ______,     ______,  ______,  ______,  ______,     ______,
    ______,  ______,  ______,  ______,  ______, ______, ______, ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,      ______,  ______,  ______,     ______,  ______,  ______,  ______,     ______,  ______,
    ______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______,  ______, EE_CLR,  ______,  ______,           ______,      ______,  ______,  ______,     ______,  ______,  ______,  ______,     ______,  ______,
    ______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______,  ______,  ______,  ______,           ______,  ______,                                    ______,  ______,  ______,  ______,     ______,  ______,
    ______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______,  ______,  ______,  ______,           ______,  ______,               ______,              ______,  ______,  ______,  ______,     ______,  ______,
     DB_TOGG,  ______,  ______,  ______,  ______,          ______,         ______,  ______,  ______,  ______,  ______,  ______,  ______,      ______,  ______,  ______,     ______,           ______,  ______,     ______,  ______
    )
};

