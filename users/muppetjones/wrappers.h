/* Copyright 2020 Stephen Bush
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
#include "muppetjones.h"
#include "tapmods.h"

/*  Pattern adapted from users/drashna/wrapper.h
    Define per-layout keymap sections. Also requires a wrapper.

    Example:

        #define LAYOUT_:name_wrapper(...)            LAYOUT_:name(__VA_ARGS__)

        const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_MODS] = LAYOUT_:name _wrapper(
            _______, ___________________BLANK___________________, ...
            ...
        ),
        }
*/

#ifdef MOUSEKEY_ENABLE
#    define MK_WH_D KC_WH_D
#    define MK_WH_U KC_WH_U
#else
#    define MK_WH_D XXXXXXX
#    define MK_WH_U XXXXXXX
#endif

// clang-format off
/* Blank-ish */
#define __BLANK____________________________________ _______, _______, _______, _______, _______
#define __BLANK_NOOP_______________________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define __BLANK_W_GACS_____________________________ KC_LGUI, KC_LALT, KC_LALT, KC_LSFT, _______
#define __BLANK_W_SCAG_____________________________ _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI

/* Adjust */
// NOTE: The "BACKLIT" keycode is planck specific
#define __ADJUST_L1________________________________ RESET,   DEBUG,   XXXXXXX, TERM_ON, TERM_OFF
#define __ADJUST_L2________________________________ RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD
#define __ADJUST_L3________________________________ XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX

#define __ADJUST_R1________________________________ XXXXXXX, AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX
#define __ADJUST_R2________________________________ XXXXXXX, CLMK_DH, QWERTY,  XXXXXXX, XXXXXXX
#define __ADJUST_R3________________________________ __BLANK_NOOP_______________________________

/* COLEMAK mod-DH */
#define __COLEMAK_MOD_DH_L1________________________ KC_Q,    KC_W,    KC_F,     KC_P,   KC_B
#define __COLEMAK_MOD_DH_L2_W_GACS_________________ HR_A,    HR_R,    HR_S,     HR_T,   KC_G
#define __COLEMAK_MOD_DH_L3________________________ KC_Z,    KC_X,    KC_C,     KC_D,   KC_V
#define __COLEMAK_MOD_DH_L3_W_SFTV_________________ KC_Z,    KC_X,    KC_C,     KC_D,   TM_VSFT

#define __COLEMAK_MOD_DH_R1_W_QUOT_________________ KC_J,    KC_L,    KC_U,     KC_Y,   KC_QUOT
#define __COLEMAK_MOD_DH_R1________________________ KC_J,    KC_L,    KC_U,     KC_Y,   KC_SCLN
#define __COLEMAK_MOD_DH_R2_W_SCAG_________________ KC_M,    HR_N,    HR_E,     HR_I,   HR_O
#define __COLEMAK_MOD_DH_R3________________________ KC_K,    KC_H,    KC_COMM,  KC_DOT, KC_SLASH

/* Guitar
 * ,----------------------------------.
 * | Pg Up| Next | Prev | Brm+ | Vol+ |
 * |------+------+------+------+------|
 * | Pg Dn| Play | Stop | Brm- | Vol- |
 * |------+------+------+------+------|
 * | xxxx | xxxx | xxxx | xxxx | xxxx |
 * `----------------------------------'
 */
//      _______, _______, _______, _______, _______, _______
// Not sure why, but this does not work
// #ifdef MIDI_ADVANCED
// #define __GUITAR_1E_L______________________________ MI_E_1,  MI_F_1,  MI_Fs_1, MI_G_1,  MI_Gs_1
// #define __GUITAR_2A_L______________________________ MI_A_1,  MI_As_1, MI_B_1,  MI_C_2,  MI_Cs_2
// #define __GUITAR_3D_L______________________________ MI_D_2,  MI_Ds_2, MI_E_2,  MI_F_2,  MI_Fs_2
// #define __GUITAR_4G_L______________________________ MI_G_2,  MI_Gs_2, MI_A_2,  MI_As_2, MI_B_2
// #define __GUITAR_5B_L______________________________ MI_B_2,  MI_C_3,  MI_Cs_3, MI_D_3,  MI_Ds_3
// #define __GUITAR_6E_L______________________________ MI_E_3,  MI_F_3,  MI_Fs_3, MI_G_3,  MI_Gs_3
//
// #define __GUITAR_1E_R______________________________ MI_A_1,  MI_As_1, MI_B_1,  MI_C_2,  MI_Cs_2
// #define __GUITAR_2A_R______________________________ MI_D_2,  MI_Ds_2, MI_E_2,  MI_F_2,  MI_Fs_2
// #define __GUITAR_3D_R______________________________ MI_G_2,  MI_Gs_2, MI_A_2,  MI_As_2, MI_B_2
// #define __GUITAR_4G_R______________________________ MI_C_3,  MI_Cs_3, MI_D_3,  MI_Ds_3, MI_E_3
// #define __GUITAR_5B_R______________________________ MI_E_3,  MI_F_3,  MI_Fs_3, MI_G_3,  MI_Gs_3
// #define __GUITAR_6E_R______________________________ MI_A_3,  MI_As_3, MI_B_3,  MI_C_4,  MI_Cs_4
// #endif


/* MEDIA
 * ,----------------------------------.
 * | Pg Up| Next | Prev | Brm+ | Vol+ |
 * |------+------+------+------+------|
 * | Pg Dn| Play | Stop | Brm- | Vol- |
 * |------+------+------+------+------|
 * | xxxx | xxxx | xxxx | xxxx | xxxx |
 * `----------------------------------'
 */
// What it MUV_IN and MUV_DE (5C2A and B)?
// https://github.com/qmk/qmk_firmware/blob/7e832e46de26989b81f2fbf58a0f391b2b0c1aaf/quantum/quantum_keycodes.h#L135
#define __MEDIA_R1_________________________________ AU_ON,   MI_ON,   MU_ON,   KC_BRMU, KC_VOLU
#define __MEDIA_R2_________________________________ AU_OFF,  MI_OFF,  MU_OFF,  KC_BRMD, KC_VOLD
#define __MEDIA_R3_________________________________ KC_MPLY, KC_MSTP, KC_MNXT, KC_MPRV, KC_MUTE


/* NAV
 * ,----------------------------------.
 * | Pg Up| Home | Wh Dn| Wh Up|  End |
 * |------+------+------+------+------|
 * | Pg Dn| Left | Down |  Up  | Right|
 * |------+------+------+------+------|
 * | xxxx | xxxx | xxxx | xxxx | xxxx |
 * `----------------------------------'
 */
#define __NAV_R1___________________________________ KC_PGUP, KC_HOME, KC_WH_D, KC_WH_U, KC_END
#define __NAV_R2___________________________________ KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
#define __NAV_R3___________________________________ __BLANK_NOOP_______________________________

/* NUMPAD
 * ,----------------------------------.
 * | Bksp |  7 & |  8 * |  9 ( |  \ | |
 * |------+------+------+------+------|
 * |  - _ |  4 $ |  5 % |  6 ^ |  *   |
 * |------+------+------+------+------|
 * |  = + |  1 ! |  2 @ |  3 # |  |   |
 * |------+------+------+------+------|
 * |      |  0 ) |  . > |      |      |
 * `----------------------------------'
 */
#define __NUMPAD_R1________________________________ KC_BSPC, KC_7,    KC_8,    KC_9,    KC_BSLS
#define __NUMPAD_R2________________________________ KC_MINS, HR_4,    HR_5,    HR_6,    KC_ASTR
#define __NUMPAD_R3________________________________ KC_EQL,  KC_1,    KC_2,    KC_3,    KC_PIPE
#define __NUMPAD_R4________________________________ _______, KC_0,    KC_DOT,  _______, _______

#define __NUMPAD_R3_ALT____________________________ KC_0,    KC_1,    KC_2,    KC_3,    KC_EQ

/* QWERTY */
#define __QWERTY_L1________________________________ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define __QWERTY_L2________________________________ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define __QWERTY_L3________________________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define __QWERTY_R1________________________________ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define __QWERTY_R2________________________________ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define __QWERTY_R3________________________________ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

/* SYMBOLS
 * ,----------------------------------.
 * |  ~   |  `   |  (   |  )   |      |
 * |------+------+------+------+------|
 * | LGUI | LALT |LCTL [|LSFT ]|  _ - |
 * |------+------+------+------+------|
 * | xxxx | xxxx |  {   |  }   | LSFT |
 * `----------------------------------'
 */
 #define __SYMBOLS_L1_______________________________ KC_TILD, KC_GRV,  KC_LPRN, KC_RPRN, XXXXXXX
 #define __SYMBOLS_L2_______________________________ KC_LGUI, KC_LALT, HR_LBRC, HR_RBRC, KC_UNDS
 #define __SYMBOLS_L3_______________________________ XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_LSFT

// clang-format on
// __END__
