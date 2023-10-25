 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

#include "oled.c"

// Base layer is the number of layers CYCLE selects from.
#define BASE_LAYERS 2

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,  // can always be here (4 bytes)
    CYCLE                      // cycle through first BASE_LAYERS (62 bytes)
};

enum custom_layers {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE
};

//Default keymap. This can be changed in Via. Use oled.c to change beavior that Via cannot change.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |-------.  E  ,-------|   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------| VolUp |< N >| Pg Up |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |-------.  C  ,-------|   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------| Mute  |< O >|       |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.  D  ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| VolDn |< E >| Pg Dn |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|  R  |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /        \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
   KC_GRV, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                         KC_6    , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,
   KC_ESC, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                         KC_Y    , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
   KC_TAB, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                         KC_H    , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_MUTE, KC_NO,         KC_N    , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                  KC_LGUI,KC_LALT ,KC_LCTL,MO(_LOWER), KC_ENT ,           KC_SPC  ,MO(_RAISE),KC_RCTL, KC_RALT, KC_RGUI
),
/*
 * COLEMAK - Vanilla
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |-------.  E  ,-------|   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------| VolUp |< N >| Pg Up |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   G  |-------.  C  ,-------|   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------| Mute  |< O >|       |------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   D  |-------.  D  ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------| VolDn |< E >| Pg Dn |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|  R  |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /        \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */
/*
[_COLEMAK] = LAYOUT(
  KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                          KC_6    , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,
  KC_ESC , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_VOLU,       KC_PGUP,  KC_J    , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
  KC_TAB , KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_MUTE,       KC_NO  ,  KC_H    , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
  KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_VOLD,       KC_PGDN,  KC_N    , KC_M   , KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
                  KC_LGUI, KC_LALT,KC_LCTL,MO(_LOWER), KC_ENT ,           KC_SPC ,MO(_RAISE),KC_RCTL, KC_RALT, KC_RGUI
),
*/

/*
 * COLEMAK-DH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |-------.  E  ,-------|   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------| VolUp |< N >| Pg Up |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   B  |-------.  C  ,-------|   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------| Mute  |< O >|       |------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   G  |-------.  D  ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------| VolDn |< E >| Pg Dn |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   D  |   V  |-------|  R  |-------|   K  |   H  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /        \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */
[_COLEMAK] = LAYOUT(
  KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                          KC_6    , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,
  KC_ESC , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,                          KC_J    , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
  KC_TAB , KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,                          KC_M    , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
  KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   , _______, _______,        KC_K    , KC_H   , KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
                  KC_LGUI, KC_LALT,KC_LCTL,MO(_LOWER), KC_ENT ,           KC_SPC ,MO(_RAISE),KC_RCTL, KC_RALT, KC_RGUI
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |-------.  E  ,-------|  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|       |< N >|       |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |-------.  C  ,-------|   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|       |< O >|       |------+------+------+------+------+------|
 * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.  D  ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|       |< E >|       |------+------+------+------+------+------|
 * | Shift|  =   |  -   |  +   |   {  |   }  |-------|  R  |-------|   [  |   ]  |   ;  |   :  |   \  |      |
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /        \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                         KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
  KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                         KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_F12 ,
  _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
  _______, KC_EQL , KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR,  _______,   _______,    KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                  _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______
),
/* RAISE
 * ,----------------------------------------.                      ,-----------------------------------------.
 * |Cycle |      |      |      |      |      |-------.  E  ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |< N >|       |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |-------.  C  ,-------|      |      |  Up  |      | DLine| Bspc |
 * |------+------+------+------+------+------|       |< O >|       |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.  D  ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|       |< E >|       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|  R  |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/      /       \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter /         \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/      /           \      \ |      |      |      |      |
 *            `----------------------------------'             '------''---------------------------'
 */
[_RAISE] = LAYOUT(
    CYCLE, _______, _______, _______, _______ , _______,                       _______, _______, _______, _______, _______, _______,
  _______, KC_INS , KC_PSCR, KC_APP , XXXXXXX , XXXXXXX,                       KC_PGUP, _______, KC_UP  , _______, _______, KC_BSPC,
  _______, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX , KC_CAPS,                       KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , KC_BSPC,
  _______, KC_UNDO, KC_CUT , KC_COPY, KC_PASTE, XXXXXXX, _______, _______,      XXXXXXX, _______, XXXXXXX, _______, XXXXXXX, _______,
                   _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______
)
};

// Custom keycode handling.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // handling this once instead of in each keycode uses less program memory.
    if ((keycode >= SAFE_RANGE) && !(record->event.pressed)) {
        return false;
    }

    switch (keycode) {
        case CYCLE:
            set_single_persistent_default_layer((1+get_highest_layer(default_layer_state)) % BASE_LAYERS);
            break;
    }

    // this uses less memory than returning in each case.
    return keycode < SAFE_RANGE;
};

 #ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_BSPC, KC_DEL),  ENCODER_CCW_CW(KC_PGDN, KC_PGUP)  },
    [1] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [2] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [3] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  }
};
#endif
