/* Copyright 2020 Worldspawn <mcmancuso@gmail.com>
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

enum cajal_layers {
    _QWERTY,
    _COLEMAK,
    _MEDIA,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum cajal_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    MEDIA,
    LOWER,
    RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
    * .------------------------------------------------------------------------------------------.   .------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bslsh| Bksp |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * | Ctrl | GUI  |Media | Alt  |Lower |Space | Bksp |Raise |      |      |      |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_QWERTY] = LAYOUT_ortho(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    KC_BSLS, KC_BSPC, RGB_TOG,
        KC_GESC, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  KC_UP,
        KC_LCTL, KC_LGUI, MEDIA,   KC_LALT, LOWER, KC_SPC, KC_BSPC, RAISE, KC_RALT, KC_RCTL, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Colemak
    * .------------------------------------------------------------------------------------------.   .------.
    * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bslsh| Bksp |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * | Ctrl | GUI  |Media | Alt  |Lower |Space | Bksp |Raise |      |      |      |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_COLEMAK] = LAYOUT_ortho(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,  KC_G,   KC_J,    KC_L,  KC_U,    KC_Y,    KC_SCLN,    KC_BSLS, KC_BSPC, RGB_TOG,
        KC_GESC, KC_A,    KC_R,    KC_S,    KC_T,  KC_D,   KC_H,    KC_N,  KC_E,    KC_I,    KC_O, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_K,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  KC_UP,
        KC_LCTL, KC_LGUI, MEDIA,   KC_LALT, LOWER, KC_SPC, KC_BSPC, RAISE, KC_RALT, KC_RCTL, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Media
    * .------------------------------------------------------------------------------------------.   .------.
    * |      |Volup |      |      |      |      |      |      |      |      |      |      |      |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * | Mute |Voldn | Prev | Next | Play |      |      |      |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * |      |      |      |      |      |      |      |      |      |      |      |      |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * |      |      |      |      |      |      |      |      |      |      |      |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_MEDIA] = LAYOUT_ortho(
        _______, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_MUTE, KC_VOLD, KC_MPRV, KC_MNXT, KC_MPLY, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Lower
    * .------------------------------------------------------------------------------------------.   .------.
    * |      |  !   |  @   |  #   |  $   |  %   |  ^   |  &   |  *   |  (   |   )  |      | Del  |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * |      |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * |      |  {   |  }   |  [   |  ]   |      |      |  -   |  _   |  =   |  +   |      |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * |      |      |      |      |      |      |      |      |      |      |      |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_LOWER] = LAYOUT_ortho(
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,  KC_DEL, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRAVE, _______,
        _______, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______, _______, KC_MINS, KC_UNDS, KC_EQL,  KC_PLUS, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______
    ),

    /* Raise
    * .------------------------------------------------------------------------------------------.   .------.
    * |      |  F1  |  F2  |  F3  |  F4  |      |      |Insert| Home | End  |Numlck|      |      |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * |      |  F5  |  F6  |  F7  |  F8  |      |      | PgUp | PgDn |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * |      |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |      |      |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * |      |      |      |      |      |      |      |      |      |      |      |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_RAISE] = LAYOUT_ortho(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_INS,    KC_HOME, KC_END,  KC_NUMLOCK, _______, _______, _______,
        _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, KC_PGUP,   KC_PGDN, _______, _______,    _______, _______,
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,   _______, _______, _______,    _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,    _______, _______, _______
    ),

    /* Adjust
    * .------------------------------------------------------------------------------------------.   .------.
    * |      |      |      |      |      |      |      |      |      |      |      |      |Reset |   | RGBT |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------|   '------'
    * |      |RGBMde|RGBHue|RGBSat|RGBVal|      |      |QWERTY|COLEMK|      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------+------'
    * |      |      |      |      |      |      |      |CpsLck|      |      |      |      |   .------.
    * |------+------+------+------+------+------+------+------+------+------+------+------'   |  Up  |
    * |      |      |      |      |      |      |      |      |      |      |      |   .------+------+------.
    * '----------------------------------------------------------------------------'   | Left | Down | Right|
                                                                                       '--------------------'
    */
    [_ADJUST] = LAYOUT_ortho(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,  _______,
        _______, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, QWERTY,  COLEMAK, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_CAPS, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
              layer_move(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            layer_move(_COLEMAK);
          }
          return false;
          break;
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
    	case MEDIA:
          if (record->event.pressed) {
            layer_on(_MEDIA);
          } else {
            layer_off(_MEDIA);
          }
          return false;
          break;
        }
    return true;
};

const rgblight_segment_t PROGMEM layer_lower[] = RGBLIGHT_LAYER_SEGMENTS({2, 1, HSV_CYAN});
const rgblight_segment_t PROGMEM layer_raise[] = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_PURPLE});
const rgblight_segment_t PROGMEM layer_media[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_CORAL});
const rgblight_segment_t PROGMEM layer_adjust[] = RGBLIGHT_LAYER_SEGMENTS({1, 2, HSV_SPRINGGREEN});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_lower,
    layer_raise,
    layer_media,
    layer_adjust
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
};

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 4));
    rgblight_set_layer_state(1, layer_state_cmp(state, 5));
    rgblight_set_layer_state(2, layer_state_cmp(state, 6));
    rgblight_set_layer_state(3, layer_state_cmp(state, 7));

    if (IS_LAYER_ON(_QWERTY)) {
        writePinLow(B6);
        writePinLow(B7);
        writePinHigh(B5);
    }
    else if (IS_LAYER_ON(_COLEMAK)) {
        writePinLow(B5);
        writePinLow(B7);
        writePinHigh(B6);
    }
    // else if (IS_LAYER_ON(_ADJUST)) {
    //     writePinLow(B5);
    //     writePinLow(B6);
    //     writePinHigh(B7);
    // }
    return state;
}

bool led_update_user(led_t led_state) {
    writePin(B7, led_state.caps_lock);
    return false;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if(IS_LAYER_ON(_RAISE)) {
        if (clockwise){
                tap_code(KC_WH_D);
            } else{
                tap_code(KC_WH_U);
            }
    } else if(IS_LAYER_ON(_LOWER)) {
            if (clockwise){
                tap_code(KC_VOLU);
            } else{
                tap_code(KC_VOLD);
            }
    }
    else{
        if (clockwise){
            tap_code(KC_PGDN);
        } else{
            tap_code(KC_PGUP);
        }
    }
}
