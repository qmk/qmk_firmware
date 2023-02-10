/* Copyright 2021 Christoph Jabs (BifbofII)
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

/* ====== Unicode ====== */
/* Character names */
enum unicode_names {
    SAE,
    BAE,
    SUE,
    BUE,
    SOE,
    BOE,
    SS,
    EUR,
    CPR
};

/* Unicode map */
const uint32_t PROGMEM unicode_map[] = {
    [SAE] = 0x00E4, // ä
    [BAE] = 0x00C4, // Ä
    [SUE] = 0x00FC, // ü
    [BUE] = 0x00DC, // Ü
    [SOE] = 0x00F6, // ü
    [BOE] = 0x00D6, // Ü
    [SS]  = 0x00DF, // ß
    [EUR] = 0x20AC, // €
    [CPR] = 0x00A9  // ©
};

// ====== Layers ======
// Layer numbers
enum layer_names {
    QWERTY = 0,
    RAISE,
    LOWER,
    FUNCTIONS,
    UNICODE,
    SPECIALS,
};

#define L_LOW  MO(LOWER)
#define L_RAIS MO(RAISE)
#define L_SPEC MO(SPECIALS)
#define L_FNC  LT(FUNCTIONS, KC_SPC)
#define L_UNI  LT(UNICODE, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * | Tab |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  | Bsp |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * | Esc |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |Shift|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Ret |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |Ctrl |Super|     | Alt |Lower|    Spc    |Raise| Alt |Super|Ctrl |Spec |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 */
[QWERTY] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    L_UNI,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
    KC_LCTL, KC_LGUI, XXXXXXX, KC_LALT, L_LOW,   L_FNC,   L_FNC,   L_RAIS,  KC_RALT, KC_RGUI, KC_RCTL, L_SPEC
),

/* Raise
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | Bsp |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     | F1  | F2  | F3  | F4  | F5  | F6  |  -  |  =  |  [  |  ]  |  \  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     | F7  | F8  | F9  | F10 | F11 | F12 |     |     |     |     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 */
[RAISE] = LAYOUT_ortho_4x12(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Lower
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |  ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  | Bsp |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |     |     |     |     |  _  |  +  |  {  |  }  |  |  |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |     |     |     |     |     |     |     |     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |     |     |           |     |     |     |     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 */
[LOWER] = LAYOUT_ortho_4x12(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Functions Layer 1
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |     |     |Mute |Prev |Vol- |Vol+ |Next |Play | Del |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |Caps |     |  <  |     |     |  >  |Left |Down | Up  |Right|     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |     |     |     |Home |PgDn |PgUp | End |     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |     |     |           |     |     |     |     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 */
[FUNCTIONS] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______, KC_MUTE, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MEDIA_PLAY_PAUSE, KC_DEL,
    KC_CAPS, _______, KC_WBAK, _______, _______, KC_WFWD, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,             _______,
    _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,             _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______
),

/* Unicode Layer
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |  €  |     |     |     |  Ü  |     |  Ö  |     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |  Ä  |  ß  |     |     |     |     |     |     |     |     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |  ©  |     |     |     |     |     |     |     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * |     |     |     |     |     |           |     |     |     |     |     |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 */
[UNICODE] = LAYOUT_ortho_4x12(
    _______, _______,      _______, X(EUR),  _______, _______, _______, XP(SUE, BUE), _______, XP(SOE, BOE), _______, _______,
    _______, XP(SAE, BAE), X(SS),   _______, _______, _______, _______, _______,      _______, _______,      _______, _______,
    _______, _______,      _______, X(CPR),  _______, _______, _______, _______,      _______, _______,      _______, _______,
    _______, _______,      _______, _______, _______, _______, _______, _______,      _______, _______,      _______, _______
),

/* Specials Layer
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * | XXX | XXX | Win | XXX | XXX | XXX | XXX | XXX | XXX | OSX | XXX | XXX |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * | XXX | XXX | XXX | XXX | XXX | XXX | XXX | XXX | XXX | Lnx | XXX | XXX |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * | XXX | XXX | XXX | XXX | XXX |QK_BOOT| XXX | XXX | XXX | XXX | XXX | XXX |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * | XXX | XXX | XXX | XXX | XXX |    XXX    | XXX | XXX | XXX | XXX | XXX |
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 */
[SPECIALS] = LAYOUT_ortho_4x12(
    XXXXXXX, XXXXXXX, UC_WINC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UC_MAC,  XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UC_LINX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)

};
