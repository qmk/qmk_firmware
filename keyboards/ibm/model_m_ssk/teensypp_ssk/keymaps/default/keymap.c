/* Copyright 2019-2021 iw0rm3r, tiltowait
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

enum custom_layers {
    _BASE,
    _NUMPAD,
};

enum custom_keycodes {
  NUM_SCRL = SAFE_RANGE
};

void toggle_numpad_layer(int set_state);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Base layer */
    KC_ESC,           KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_PSCR, NUM_SCRL, KC_PAUS,
    KC_GRV,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME,  KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,   KC_PGDN,
    KC_CAPS, KC_A,    KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
    KC_LSFT, KC_NUBS, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,            KC_UP,
    KC_LCTL,          KC_LALT,                           KC_SPC,                                      KC_RALT,          KC_RCTL,   KC_LEFT, KC_DOWN,  KC_RGHT
  ),
  [_NUMPAD] = LAYOUT( /* Numpad Layer */
     KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,     KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,

     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_TRNS,        KC_KP_MINUS, KC_KP_PLUS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6, KC_TRNS,        KC_TRNS,     KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ASTERISK, KC_TRNS,     KC_TRNS,    KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_0, KC_TRNS, KC_KP_DOT,      KC_KP_SLASH,             KC_TRNS,            KC_TRNS,
     KC_TRNS,          KC_TRNS,                            KC_TRNS,                                            KC_TRNS,                 KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t last_num_scroll = 0; /* For unregistering the proper key */

  switch (keycode) {
    case NUM_SCRL: /* Numlock / Scroll Lock */
    if (record->event.pressed) {
      if (get_mods() & MOD_MASK_SHIFT) {
        /* Remove the shift modifiers */
        uint8_t shift_mods = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
        del_mods(MOD_MASK_SHIFT);

        last_num_scroll = KC_NUM_LOCK;
        register_code(last_num_scroll);
        toggle_numpad_layer(-1);

        /* Reset the shift modifiers */
        set_mods(shift_mods);
      } else {
        last_num_scroll = KC_SCROLL_LOCK;
        register_code(last_num_scroll);
      }
    } else {
      unregister_code(last_num_scroll);
    }
    break;
  }
  return true;
}

void toggle_numpad_layer(int set_state) {
  static uint8_t numlock_enabled = 0;

  /* set_state allows us to explicitly change the numlock state
     rather than merely toggling it. */
  if (set_state == -1) {
    numlock_enabled = !numlock_enabled;
  } else {
    numlock_enabled = set_state;
  }

  if (numlock_enabled) {
    layer_on(_NUMPAD);
  }
  else {
    layer_off(_NUMPAD);
  }
}

bool led_update_user(led_t led_state) {
  /* In rare and unlikely conditions, it's possible for numlock
     state to change externally from the keyboard. If this happens,
     we want to match the new state.

     On Windows and Linux, this means that the keyboard will technically
     toggle the numpad layer twice.
  */

  static int8_t numlock_state = -1; /* Unknown state at default */

  if (led_state.num_lock != numlock_state) {
    numlock_state = led_state.num_lock;
    toggle_numpad_layer(led_state.num_lock);
  }
  return true;
}

