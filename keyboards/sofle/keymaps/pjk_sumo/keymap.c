
 /* Copyright 2021 Dane Evans
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
  // SOFLE RGB
  #include <stdio.h>

  #include QMK_KEYBOARD_H

  enum sofle_layers {
      _DEFAULTS = 0,
      _QWERTY = 0,
      _LOWER,
      _RAISE,
      _ADJUST,
  };

  enum custom_keycodes {
      KC_QWERTY = SAFE_RANGE,
      KC_LOWER,
      KC_RAISE,
      KC_ADJUST,
      KC_D_MUTE
  };

  const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY */
      [_QWERTY] = LAYOUT(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,KC_8, KC_9, KC_0, KC_MINS,
      KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_EQL,
      KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, RGB_TOG, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
      KC_LCTL, KC_LGUI, KC_SPC, KC_LOWER, KC_TAB, KC_ENT, KC_RAISE, KC_BSPC, KC_LALT ,KC_BSPC
    ),
    /* LOWER */
    [_LOWER] = LAYOUT(
      KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
      KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_LBRC), LSFT(KC_RBRC),
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /* RAISE */
    [_RAISE] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ,KC_TRNS,
      KC_TRNS, RGB_SPI, RGB_VAI, RGB_SAI, RGB_HUI, RGB_MOD, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, RGB_SPD, RGB_VAD, RGB_SAD, RGB_HUD, RGB_RMOD, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /* ADJUST */
      [_ADJUST] = LAYOUT(
      HF_RST, EE_CLR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT,KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    };

  bool process_record_user(uint16_t keycode, keyrecord_t *record) {
      switch (keycode) {
          case KC_LOWER:
              if (record->event.pressed) {
                  layer_on(_LOWER);
                  update_tri_layer(_LOWER, _RAISE, _ADJUST);
              } else {
                  layer_off(_LOWER);
                  update_tri_layer(_LOWER, _RAISE, _ADJUST);
              }
              return false;
          case KC_RAISE:
              if (record->event.pressed) {
                  layer_on(_RAISE);
                  update_tri_layer(_LOWER, _RAISE, _ADJUST);
              } else {
                  layer_off(_RAISE);
                  update_tri_layer(_LOWER, _RAISE, _ADJUST);
              }
              return false;
          case KC_ADJUST:
              if (record->event.pressed) {
                  layer_on(_ADJUST);
              } else {
                  layer_off(_ADJUST);
              }
              return false;
          case KC_D_MUTE:
              if (record->event.pressed) {
                  register_mods(mod_config(MOD_MEH));
                  register_code(KC_UP);
              } else {
                  unregister_mods(mod_config(MOD_MEH));
                  unregister_code(KC_UP);
              }
      }
      return true;
  }

  #ifdef ENCODER_ENABLE

  bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
	} else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
  }

  #endif
