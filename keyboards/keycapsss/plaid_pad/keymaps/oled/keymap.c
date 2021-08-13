/* Copyright 2021 Ben Roesner (keycapsss.com)
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
#include <stdio.h>

enum layers {
    _NUMPAD,
    _NAVIGATION,
    _MEDIA
};

enum combos {
  COMBO1,
  COMBO2,
  COMBO3
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* NUMPAD layer
    * ,-----------------------,
    * |  7  |  8  |  9  |  /  |
    * |-----+-----+-----+-----|
    * |  4  |  5  |  6  |  *  |
    * |-----+-----+-----+-----|
    * |  1  |  2  |  3  |  -  |
    * |-----+-----+-----+-----|
    * |  0  |  .  |  =  |  +  |
    * `-----------------------'
    */
    [_NUMPAD] = LAYOUT_ortho_4x4(
        KC_P7, KC_P8,   KC_P9,    KC_PSLS,
        KC_P4, KC_P5,   KC_P6,    KC_PAST,
        KC_P1, KC_P2,   KC_P3,    KC_PMNS,
        KC_P0, KC_PDOT, KC_PEQL,  KC_PPLS
    ),
    /* Navigation layer
    */
    [_NAVIGATION] = LAYOUT_ortho_4x4(
        KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX,
        KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,
        XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX,
        KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX
    ),
    /* MEDIA layer
    */
    [_MEDIA] = LAYOUT_ortho_4x4(
        KC_SYSTEM_SLEEP,     XXXXXXX,             XXXXXXX,             KC_AUDIO_MUTE,
        XXXXXXX,             XXXXXXX,             XXXXXXX,             XXXXXXX,
        KC_AUDIO_VOL_DOWN,   KC_AUDIO_MUTE,       KC_AUDIO_VOL_UP,     XXXXXXX,
        KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, XXXXXXX
    ),

};

// Combos for switching layers
const uint16_t PROGMEM zeroDot_combo[] = {KC_P0, KC_PDOT, COMBO_END};
const uint16_t PROGMEM leftDown_combo[] = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM prevPlay_combo[] = {KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO1] = COMBO_ACTION(zeroDot_combo),
  [COMBO2] = COMBO_ACTION(leftDown_combo),
  [COMBO3] = COMBO_ACTION(prevPlay_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case COMBO1:
      if (pressed) {
        layer_move(_NAVIGATION);
      }
      break;
    case COMBO2:
      if (pressed) {
        layer_move(_MEDIA);
      }
      break;
    case COMBO3:
      if (pressed) {
        layer_move(_NUMPAD);
      }
      break;
  }
}

#ifdef OLED_DRIVER_ENABLE

void render_space(void) {
  oled_write_P(PSTR("     "), false);
}


void oled_render_layer_state(void) {
  oled_write_P(PSTR("Layer: "), false);
  if(layer_state_is(_MEDIA)) {
    oled_write_ln_P(PSTR("MEDIA"), false);
  } else if(layer_state_is(_NAVIGATION)) {
    oled_write_ln_P(PSTR("NAVIGATION"), false);
  } else {
    oled_write_ln_P(PSTR("NUMPAD"), false);
  }
}


void oled_task_user(void) {
  oled_write_ln_P(PSTR("Plaid-Pad ///////////"), false);
  oled_render_layer_state();
}

#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
/*
    ,-----------------------,
    |  E1 |  E2 |  E3 |  E4 |
    |-----+-----+-----+-----|
    |     |     |     |  E3 |
    |-----+-----+-----+-----|
    |     |     |     |  E2 |
    |-----+-----+-----+-----|
    |     |     |     |  E1 |
    `-----------------------'
 */

  // First encoder (E1)
  if (index == 0) {
    switch (get_highest_layer(layer_state)) {
      case _NAVIGATION:
        // Browser tab switching
        if (clockwise) {
          tap_code16(LCTL(KC_TAB));
        } else {
          tap_code16(LCTL(LSFT(KC_TAB)));
        }
        break;
      default:
        if (clockwise) {
          tap_code(KC_F17);
        } else {
          tap_code(KC_F18);
        }
        break;
    }
  // Second encoder (E2)
  } else if (index == 1) {
    switch (get_highest_layer(layer_state)) {
      case _NAVIGATION:
        // Page Down/Up
        if (clockwise) {
          tap_code16(KC_PGDOWN);
        } else {
          tap_code16(KC_PGUP);
        }
        break;
      default:
        if (clockwise) {
          tap_code(KC_F19);
        } else {
          tap_code(KC_F20);
        }
        break;
    }
  // Third encoder (E3)
  } else if (index == 2) {
    switch (get_highest_layer(layer_state)) {
      case _NAVIGATION:
        // Mouse wheel up/down
        if (clockwise) {
          tap_code(KC_MS_WH_DOWN);
        } else {
          tap_code(KC_MS_WH_UP);
        }
        break;
      case _MEDIA:
        // BRIGHTNESS Up/Down
        if (clockwise) {
          tap_code16(KC_BRIGHTNESS_UP);
        } else {
          tap_code16(KC_BRIGHTNESS_DOWN);
        }
        break;
      default:
        if (clockwise) {
          tap_code(KC_F21);
        } else {
          tap_code(KC_F22);
        }
        break;
    }
  // Forth encoder (E4)
  } else if (index == 3) {
    switch (get_highest_layer(layer_state)) {
      case _NAVIGATION:
      case _MEDIA:
        // Volume Up/Down
        if (clockwise) {
          tap_code16(KC_AUDIO_VOL_UP);
        } else {
          tap_code16(KC_AUDIO_VOL_DOWN);
        }
        break;
      default:
        if (clockwise) {
          tap_code(KC_F23);
        } else {
          tap_code(KC_F24);
        }
        break;
    }
  }
    return true;
}
#endif
