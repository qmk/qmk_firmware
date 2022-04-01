/* Copyright 2021 TW59420 <https://github.com/TW59420>
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

typedef union {
  uint32_t raw;
  struct {
    bool top_rgb_change :1;
    bool bottom_rgb_change :1;
  };
} user_config_t;

user_config_t user_config;

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
	  KC_ESC,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12,  RGB_TOG,
	  KC_GRV,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  KC_DEL,
	  KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,  KC_PGUP,
	  KC_CAPS, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,   KC_PGDN,
	  KC_LSFT,        KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,    KC_END,
	  KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPACE,                     KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RIGHT
    ),

	[1] = LAYOUT(
      _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, USER00,  USER01,  _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUI,
      RGB_TOG, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_SAI,
      _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI, RGB_SAD,
      _______, _______, _______,                   _______,                                     RGB_MOD, _______, RGB_SPD, RGB_VAD, RGB_SPI
    ),

	[2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

	[3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};


void keyboard_post_init_user(void) {
  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case USER00:
      if (record->event.pressed) {
        // Do something when pressed
        user_config.top_rgb_change ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    case USER01:
      if (record->event.pressed) {
        // Do something when pressed
        user_config.bottom_rgb_change ^= 1; // Toggles the status
        eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

#ifdef ENCODER_ENABLE
#define ENCODERS 1
static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS] = {{3, 5}};
static keypos_t encoder_ccw[ENCODERS] = {{4, 5}};


void encoder_action_unregister(void) {
#ifdef ENCODERS
    for (uint8_t index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
    }
#endif
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void matrix_scan_user(void) {
    encoder_action_unregister();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return true;
};
#endif


void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (user_config.top_rgb_change)
    {
        for (size_t i = 14; i < 18; i++)
        {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
        }
    }
    if (host_keyboard_led_state().caps_lock) {
        for (size_t i = 14; i < 18; i++)
        {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 255, 255); // assuming caps lock is at led #5
        }
    }
    if (user_config.bottom_rgb_change)
    {
        for (size_t i = 0; i < 21; i++)
        {
            if (i >= 14 && i <18)
                continue;

            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
        }
    }
}
