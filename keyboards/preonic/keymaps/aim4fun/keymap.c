/* Copyright 2015-2021 Jack Humbert
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

#include QMK_KEYBOARD_H
#include "keymap_functions.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab* |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl*|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | HYPR |Accent| GUI  | Alt  | Lower|    Space*   | Raise|Accent|      |      |MEH   |
 * `-----------------------------------------------------------------------------------'
 *
 * - Tap dance Ctrl/Esc
 * - Tap dance MOV/Space
 * - Tap dance NUM/Tab
 */
[_QWERTY] = LAYOUT_preonic_1x2uC(
  KC_GRV,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  TABNUM,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  LCTL_T(KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_HYPR,         ACCENT,  KC_LGUI, KC_LALT,  LOWER,      SPCMOV     ,  RAISE,   ACCENT2, XXXXXXX, XXXXXXX, KC_MEH
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab* |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl*|   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | HYPR |Accent| GUI  | Alt  | Lower|    Space*   | Raise|Accent|      |      |MEH   |
 * `-----------------------------------------------------------------------------------'
 *
 * - Tap dance Ctrl/Esc
 * - Tap dance MOV/Space "SPCMOV"
 * - Tap dance NUM/Tab "TABNUM"
 */
[_COLEMAK] = LAYOUT_preonic_1x2uC(
  KC_GRV,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  TABNUM,          KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
  LCTL_T(KC_ESC),  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_HYPR,         ACCENT,  KC_LGUI, KC_LALT,  LOWER,      SPCMOV     ,  RAISE,   ACCENT2, XXXXXXX, XXXXXXX, KC_MEH
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab* |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl*|   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | HYPR |Accent| GUI  | Alt  | Lower|    Space*   | Raise|Accent|      |      |MEH   |
 * `-----------------------------------------------------------------------------------'
 *
 * - Tap dance Ctrl/Esc
 * - Tap dance MOV/Space
 * - Tap dance NUM/Tab
 */
[_DVORAK] = LAYOUT_preonic_1x2uC(
  KC_GRV,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  TABNUM,         KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL,
  LCTL_T(KC_ESC), KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
  KC_LSFT,        KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT,
  KC_HYPR,        ACCENT,  KC_LGUI, KC_LALT,  LOWER,      SPCMOV     ,  RAISE,   ACCENT2, XXXXXXX, XXXXXXX, KC_MEH
),

/* Game
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  /   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |Accent| GUI  | Alt  | Lower|    Space    | Raise| Ralt | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = LAYOUT_preonic_1x2uC(
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLSH,
  KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT,
  KC_LCTL,  ACCENT,  KC_LGUI, KC_LALT,  LOWER,      KC_SPC     ,  RAISE,   KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Space Engineers
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  /   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  | PDown|Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |Accent| GUI  | Alt  | Lower|    Space    | Raise|Insert| Home |Delete|  End |
 * `-----------------------------------------------------------------------------------'
 */
[_SPACEING] = LAYOUT_preonic_1x2uC(
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLSH,
  KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_PGDN, KC_ENT,
  KC_LCTL,  ACCENT,  KC_LGUI, KC_LALT,  LOWER,      KC_SPC     ,  RAISE,   KC_INS, KC_HOME,  KC_DEL, KC_END
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | **** |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | **** |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |   \  |   -  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | **** |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | **** |    *****    | **** |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_1x2uC(
  XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,     _______     , _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |      |      |      |      |      |      |      |      | **** |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | **** |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |  |   _  |   +  |   {  |   }  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | **** |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | **** |    *****    | **** |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_1x2uC(
  KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,     _______     , _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* MOV
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |      |      |      |      | PgUp | CIns |      |      |      | SIns |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp | Home | End  | Shift| Ctrl |PgDown| Left | Down |  Up  | Right| Del  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | **** |      |      |      |      |      |      |      |      |      |      | **** |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | **** | **** | **** | **** | Bksp |    *****    | Enter| **** | **** | **** | **** |
 * `-----------------------------------------------------------------------------------'
 *
 * - Y outputs Control + Insert
 * - P outputs Shift + Insert
 */
[_MOV] = LAYOUT_preonic_1x2uC(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,
  KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, C(KC_INS), XXXXXXX, XXXXXXX, XXXXXXX, S(KC_INS), XXXXXXX,
  KC_BSPC, KC_HOME,  KC_END, KC_LSFT, KC_LCTL, KC_PGDN, KC_LEFT,   KC_DOWN,   KC_UP, KC_RGHT,    KC_DEL, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, _______,
  _______, _______, _______, _______, KC_BSPC,     _______     ,    KC_ENT, _______, _______,   _______, _______
),

/* NUM
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |      |Nulock|   /  |   *  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | **** |  F5  |  F6  |  F7  |  F8  | Mo01 | MoUp | Mo02 |   7  |   8  |   9  |   +  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |MoLeft|MoDown|MoRght|   4  |   5  |   6  |   +  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |MoAcl0|MoAcl1|MoAcl2|   1  |   2  |   3  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Bksp |    Space    | Enter|   0  |   .  |   ,  | Enter|
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_preonic_1x2uC(
  XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX, XXXXXXX, XXXXXXX, KC_NUM_LOCK, KC_PSLS, KC_PAST, KC_PMNS,
  _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_BTN1, KC_MS_U, KC_BTN2,       KC_P7,   KC_P8,   KC_P9, KC_PPLS,
  XXXXXXX,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_MS_L, KC_MS_D, KC_MS_R,       KC_P4,   KC_P5,   KC_P6, KC_PPLS,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2,       KC_P1,   KC_P2,   KC_P3, KC_PENT,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,      KC_SPC     ,  KC_ENT,       KC_P0, KC_PDOT, KC_COMM, KC_PENT
),

/* Accent
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | **** |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |   É  |      |      |      |   Ú  |   Í  |   Ó  |      | **** |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   Á  |      |      |      |      |      |   Ü  |      |      |   Ç  |   Ñ  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | **** |      |      |   Ç  |      |      |   Ñ  |      |      |      |      | **** |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Bksp |    Space    | Enter|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ACCENT] = LAYOUT_preonic_1x2uC(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, XXXXXXX,   EACCD, XXXXXXX, XXXXXXX, XXXXXXX,   UACCD,   IACCD,   OACCD, XXXXXXX, _______,
  XXXXXXX,   AACCD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   UDIER, XXXXXXX, XXXXXXX,   CTRAN,   NTILT,
  _______, XXXXXXX, XXXXXXX,   CTRAN, XXXXXXX, XXXXXXX,   NTILT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,      KC_SPC     ,  KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Accent 2
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | **** |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |   È  |      |      |      |   Ù  |   Ì  |   Ò  |      | **** |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   À  |      |      |      |      |      |   Ü  |      |      |   Ç  |   Ñ  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | **** |      |      |   Ç  |      |      |   Ñ  |      |      |      |      | **** |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Bksp |    Space    | Enter|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ACCENT2] = LAYOUT_preonic_1x2uC(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, XXXXXXX,   EACCI, XXXXXXX, XXXXXXX, XXXXXXX,   UACCI,   IACCI,   OACCI, XXXXXXX, _______,
  XXXXXXX,   AACCI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   UDIER, XXXXXXX, XXXXXXX,   CTRAN,   NTILT,
  _______, XXXXXXX, XXXXXXX,   CTRAN, XXXXXXX, XXXXXXX,   NTILT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,      KC_SPC     ,  KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Reset|      |      |      |      |      |      |      |      |      |      |EEPROM|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Qwerty|UNIWIN|      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Dvorak|      | Game |      |      |      |UNILIN|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |Colemk|      |      |      |      |      |      |       |     |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |BLtogg|BLstep|      | **** |             | **** | RGB+ | RGB  | Bri+ | Bri- |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_1x2uC(
  QK_BOOT, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,
  XXXXXXX,  QWERTY,   UNIWIN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, SPACEING,  DVORAK, XXXXXXX, GAME,    XXXXXXX, XXXXXXX, XXXXXXX,  UNILIN, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,  XXXXXXX, COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, RGB_TOG,  RGB_MOD, XXXXXXX, _______,     XXXXXXX     , _______, RGB_HUI, RGB_HUD, RGB_VAI, RGB_VAD
)

};
