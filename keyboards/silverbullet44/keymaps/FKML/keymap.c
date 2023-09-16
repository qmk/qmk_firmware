/* Copyright 2020 FKML
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

enum layer {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |Shift |   A  |   S  |   D  |   F  |   G  |                                  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | CMD  |   Z  |   X  |   C  |   V  |   B  |-------.-------.  ,---------------|   N  |   M  |   ,  |   .  |   /  |  -   |
 * `-----------------------------------------/       /       /   \       \      \-----------------------------------------'
 *                            | CAPS  | LOWER| Space/  Bcsp /     \    .  \ Ent | RAISE|LEDOff|
 *                            `----------------------------'       '--------------------------'
 */
  [_QWERTY] = LAYOUT(
     KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                      KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    KC_EQL,
    KC_LSFT,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                      KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LCMD,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                      KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
                            KC_CAPS,  LOWER, KC_SPC, KC_BSPC,    KC_DOT,  KC_ENT,  RAISE, RGB_TOG
  ),

/* LOWER
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |   `  |   !  |   @  |   #  |   $  |   %  |                                  |   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  |   1  |   2  |   3  |   4  |   5  |      |
 * |------+------+------+------+------+------+                                  +------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.-------.  ,---------------|   6  |   7  |   8  |   9  |   0  |      |
 * `-----------------------------------------/       /       /   \       \      \-----------------------------------------'
 *                             |      |      |      /       /     \       \     |      |      |
 *                             `---------------------------'       '--------------------------'
 */
  [_LOWER] = LAYOUT(
    KC_GRV , KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN, KC_RPRN, KC_PIPE,
    _______, _______, _______, _______, _______, _______,                     KC_1,     KC_2,     KC_3,     KC_4,    KC_5, _______,
    _______, _______, _______, _______, _______, _______,                     KC_6,     KC_7,     KC_8,     KC_9,    KC_0, _______,
                               _______, _______, _______, _______,  _______, _______, _______, _______
  ),

/* RAISE
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |      |      |      |      |  -   |   +  |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |                                  |      |      |      |      |  [   |   ]  |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |  F11 |  F12 |      |      |      |-------.-------.  ,---------------|      |      | Left |  Up  | Down |Right |
 * `-----------------------------------------/       /       /   \       \      \-----------------------------------------'
 *                            |      |      |      /       /     \       \     |      |      |
 *                             `---------------------------'       '--------------------------'
 */
  [_RAISE] = LAYOUT(
    _______,   KC_F1,   KC_F2,    KC_F3,   KC_F4,  KC_F5,                     _______, _______, _______, _______,  KC_MINS, KC_PLUS,
    _______,   KC_F6,   KC_F7,    KC_F8,   KC_F9,  KC_F10,                    _______, _______, _______, _______,  KC_LBRC, KC_RBRC,
    _______,  KC_F11,   KC_F12, _______, _______, _______,                    _______, _______, KC_LEFT,   KC_UP,  KC_DOWN, KC_RGHT,
                                _______, _______, _______, _______,  _______, _______, _______, _______
  ),

/*   ADJUST
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |      |      |      |FrqRst|      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |Music |FrqUp |Sound |      |                                  | SPD+ | MOD+ | VAL+ | SAD+ | HUE+ |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |Scale |FrqDwn|      |      |-------.-------.  ,---------------| SPD- | SPD- | VAL- | SAD- | HUE- |      |
 * `-----------------------------------------/       /       /   \       \      \-----------------------------------------'
 *                             |      |      |      /       /     \       \     |      |      |
 *                             `---------------------------'       '--------------------------'
 */

 [_ADJUST] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, CK_RST,  XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
    XXXXXXX, XXXXXXX, MU_TOGG, CK_UP,   AU_TOGG, XXXXXXX,                      RGB_SPI, RGB_MOD,  RGB_VAI, RGB_SAI, RGB_HUI, XXXXXXX,
    XXXXXXX, XXXXXXX, MU_NEXT, CK_DOWN, XXXXXXX, XXXXXXX,                      RGB_SPD, RGB_RMOD, RGB_VAD, RGB_SAD, RGB_HUD, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

int RGB_current_mode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
    }
    return true;
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}
