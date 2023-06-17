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
/* Blank-ish
 * ,----------------------------------. * ,----------------------------------.
 * | TRNS | TRNS | TRNS | TRNS | TRNS | * | xxxx | xxxx | xxxx | xxxx | xxxx |
 * `----------------------------------' * `----------------------------------'
 * ,----------------------------------. * ,----------------------------------.
 * | LGUI | LALT | LCTL | LSFT | TRNS | * | TRNS | RSFT | RCTL | LALT | RGUI |
 * `----------------------------------' * `----------------------------------'
*/
#define __BLANK____________________________________ _______, _______, _______, _______, _______
#define __BLANK_NOOP_______________________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define __BLANK_W_GACS_____________________________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______
#define __BLANK_W_SCAG_____________________________ _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI

/* Adjust LH
 * ,----------------------------------. ,----------------------------------.
 * |Reset |Debug | xxxx |Term+ |Term- | | xxxx |AGNORM|AGSWAP| xxxx | xxxx |
 * |------+------+------+------+------| |------+------+------+------+------|
 * |RgbTog| Hue+ | Sat+ | Val+ |RgbMod| | xxxx |CLMKDH|QWERTY| xxxx | xxxx |
 * |------+------+------+------+------| |------+------+------+------+------|
 * | xxxx | Hue- | Sat- | Val- | xxxx | | xxxx | xxxx | xxxx | xxxx | xxxx |
 * `----------------------------------' `----------------------------------'
 */
 // NOTE: The "BACKLIT" keycode is planck specific
#define __ADJUST_L1________________________________ QK_BOOT, DB_TOGG, XXXXXXX, XXXXXXX, XXXXXXX
#define __ADJUST_L2________________________________ RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD
#define __ADJUST_L3________________________________ XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX

#define __ADJUST_R1________________________________ XXXXXXX, AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX
#define __ADJUST_R2________________________________ XXXXXXX, CLMK_DH, QWERTY,  XXXXXXX, XXXXXXX
#define __ADJUST_R3________________________________ __BLANK_NOOP_______________________________

/* Colemak mod-DH
 * ,----------------------------------. ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  | |   J  |   L  |   U  |   Y  |   ;ˆ |
 * |------+------+------+------+------| |------+------+------+------+------|
 * |   A  |   R  |   S  |   T  |   G  | |   M  |   N  |   E  |   I  |   O  |
 * |------+------+------+------+------| |------+------+------+------+------|
 * |   Z  |   X  |   C  |   D  |   V˜ | |   K  |   H  |   ,  |   .  |   /  |
 * `----------------------------------' `----------------------------------'
 *      ˆ Alternate: KC_QUOT
 *      ° Alternate: Home row mods (GASC, SCAG)
 *      ˜ Alternate: Hold for shift
 *
 * Colemak mod-DH (alt and alt+shift)
 * ,----------------------------------. ,----------------------------------.
 * | œ  Œ | ∑  „ |      | π  ∏ |    ı | | ∆  Ô |      |      | ¥  Á | æ  Æ |
 * |------+------+------+------+------| |------+------+------+------+------|
 * | å  Å | ®  ‰ | ß  Í | †  ˇ | ©  ˝ | | µ  Â | ˜  ˜ | ´  ´ | ˆ  ˆ |    Ø |
 * |------+------+------+------+------| |------+------+------+------+------|
 * | Ω  ¸ | ≈  ˛ | ç  Ç |    Î | √  ◊ | | ˚   |    Ó | ≤  ¯ | ≥  ˘ | ÷  ¿ |
 * `----------------------------------' `----------------------------------'
 */
#define __COLEMAK_MOD_DH_L1________________________ KC_Q,    KC_W,    KC_F,     KC_P,   KC_B
#define __COLEMAK_MOD_DH_L2_W_GACS_________________ HR_A,    HR_R,    HR_S,     HR_T,   KC_G
#define __COLEMAK_MOD_DH_L3________________________ KC_Z,    KC_X,    KC_C,     KC_D,   KC_V
#define __COLEMAK_MOD_DH_L3_W_SFTV_________________ KC_Z,    KC_X,    KC_C,     KC_D,   TM_VSFT

#define __COLEMAK_MOD_DH_R1_W_QUOT_________________ KC_J,    KC_L,    KC_U,     KC_Y,   KC_QUOT
#define __COLEMAK_MOD_DH_R1________________________ KC_J,    KC_L,    KC_U,     KC_Y,   KC_SCLN
#define __COLEMAK_MOD_DH_R2_W_SCAG_________________ KC_M,    HR_N,    HR_E,     HR_I,   HR_O
#define __COLEMAK_MOD_DH_R3________________________ KC_K,    KC_H,    KC_COMM,  KC_DOT, KC_SLASH

/* Function (4 columns)
 * ,---------------------------.
 * |  F1  |  F2  |  F3  |  F4  |
 * |------+------+------+------|
 * |  F5  |  F6  |  F7  |  F8  |
 * |------+------+------+------|
 * |  F9  |  F10 |  F11 |  F12 |
 * `---------------------------'
 */
#define __FUNC_X1_________________________ KC_F1,   KC_F2,   KC_F3,   KC_F4
#define __FUNC_X2_________________________ KC_F5,   KC_F6,   KC_F7,   KC_F8
#define __FUNC_X3_________________________ KC_F9,   KC_F10,  KC_F11,  KC_F12

/* Game
 */
#define __GAME_L1__________________________________ KC_BTN3, KC_BTN2, KC_UP,   KC_BTN1, KC_BTN5
#define __GAME_L2__________________________________ KC_BTN4, KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX
#define __GAME_L3__________________________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define __GAME_R1__________________________________ KC_Q, KC_1, KC_2, KC_3, XXXXXXX
#define __GAME_R2__________________________________ XXXXXXX, KC_4, KC_5, KC_6, XXXXXXX
#define __GAME_R3__________________________________ XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX


/* Guitar
 * ,----------------------------------. ,----------------------------------.
 * |  E   |  F   |• F♯  |  G   |• G♯  | |  A   |• A♯  |  B   |• C   |  C♯  |
 * |  A   |  A♯  |• B   |  C   |• C♯  | |  D   |• D♯  |  E   |• F   |  F♯  |
 * |  D   |  D♯  |• E   |  F   |• F♯  | |  G   |• G♯  |  A   |• A♯  |  B   |
 * |  G   |  G♯  |• A   |  A♯  |• B   | |  C   |• C♯  |  D   |• D♯  |  E   |
 * |  B   |  C   |• C♯  |  D   |• D♯  | |  E   |• F   |  F♯  |• G   |  G♯  |
 * |  E   |  F   |• F♯  |  G   |• G♯  | |  A   |• A♯  |  B   |• C   |  C♯  |
 * `----------------------------------' `----------------------------------'
 */
// Not sure why, but this does not work (possibly due to the lowercase 's'?)
// #ifdef MIDI_ADVANCED
// #define __GUITAR_1E_L______________________________ MI_E1,  MI_F1,  MI_Fs1, MI_G1,  MI_Gs1
// #define __GUITAR_2A_L______________________________ MI_A1,  MI_As1, MI_B1,  MI_C2,  MI_Cs2
// #define __GUITAR_3D_L______________________________ MI_D2,  MI_Ds2, MI_E2,  MI_F2,  MI_Fs2
// #define __GUITAR_4G_L______________________________ MI_G2,  MI_Gs2, MI_A2,  MI_As2, MI_B2
// #define __GUITAR_5B_L______________________________ MI_B2,  MI_C3,  MI_Cs3, MI_D3,  MI_Ds3
// #define __GUITAR_6E_L______________________________ MI_E3,  MI_F3,  MI_Fs3, MI_G3,  MI_Gs3
//
// #define __GUITAR_1E_R______________________________ MI_A1,  MI_As1, MI_B1,  MI_C2,  MI_Cs2
// #define __GUITAR_2A_R______________________________ MI_D2,  MI_Ds2, MI_E2,  MI_F2,  MI_Fs2
// #define __GUITAR_3D_R______________________________ MI_G2,  MI_Gs2, MI_A2,  MI_As2, MI_B2
// #define __GUITAR_4G_R______________________________ MI_C3,  MI_Cs3, MI_D3,  MI_Ds3, MI_E3
// #define __GUITAR_5B_R______________________________ MI_E3,  MI_F3,  MI_Fs3, MI_G3,  MI_Gs3
// #define __GUITAR_6E_R______________________________ MI_A3,  MI_As3, MI_B3,  MI_C4,  MI_Cs4
// #endif


/* MEDIA
 * ,----------------------------------.
 * | AuOn | MiOn | MuOn | Brm+ | Vol+ |
 * |------+------+------+------+------|
 * | AuOff| MiOff| MuOff| Brm- | Vol- |
 * |------+------+------+------+------|
 * | Play | Stop | Next | Prev | Mute |
 * `----------------------------------'
 */
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

/* NUMPAD * (alt, alt+shift)
 * ,----------------------------------. * ,----------------------------------.
 * | Del  |  7 & |  8 * |  9 ( |  \ | | * |      | ¶  ‡ | •  ° | ª  · | «  » |
 * |------+------+------+------+------| * |------+------+------+------+------|
 * |  - _ |  4 $ |  5 % |  6 ^ |  *   | * | –  — | ¢  › | ∞  ﬁ | §  ﬂ | °  ° |
 * |------+------+------+------+------| * |------+------+------+------+------|
 * |  = + |  1 ! |  2 @ |  3 # |  ,   | * | ≠  ± | ¡  ⁄ | ™  € | £  ‹ | ≤  ¯ |
 * |------+------+------+------+------| * |------+------+------+------+------|
 * |      |  0 ) |  . > |      |      | * |      |      | º  ‚ |      |      |
 * `----------------------------------' * `----------------------------------'
 */
#define __NUMPAD_R1________________________________ KC_GRV,  KC_7,    KC_8,    KC_9,    KC_BSLS
#define __NUMPAD_R2________________________________ KC_MINS, HR_4,    HR_5,    HR_6,    KC_COMM
#define __NUMPAD_R3________________________________ KC_EQL,  KC_1,    KC_2,    KC_3,    KC_DOT
#define __NUMPAD_R4________________________________ _______, KC_0,    KC_DOT,  _______, _______

#define __NUMPAD_R3_ALT____________________________ KC_0,    KC_1,    KC_2,    KC_3,    KC_EQ

/* Qwerty
 * ,----------------------------------. ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  | |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------| |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  | |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------| |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  | |   N  |   M  |   ,  |   .  |   /  |
 * `----------------------------------' `----------------------------------'
 */
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

#define __SYMBOLS_R1_______________________________ KC_TILD, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX
#define __SYMBOLS_R2_______________________________ KC_UNDS, HR_LBRC, HR_RBRC, XXXXXXX, XXXXXXX
#define __SYMBOLS_R3_______________________________ KC_PLUS, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX

/* VIM
 * -- Roll through ":wq" via transparency
 * ,----------------------------------.
 * |   Q  |   W  |   :  |      |      |
 * `----------------------------------'
 */
#define __VIM_L1___________________________________ _______, _______, KC_COLN, _______, _______

// clang-format on
// __END__
