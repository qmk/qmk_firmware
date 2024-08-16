/*
Copyright 2024 Said Mrini (smrini)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Define the keycodes for the numpad keys
enum custom_keycodes {
    NUMPAD_1 = SAFE_RANGE,
    NUMPAD_2,
    NUMPAD_3,
    NUMPAD_4,
    // Add more here as needed
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4,
    KC_P7,    KC_P8,    KC_P9,    KC_PSLS,
    KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
    KC_P1,    KC_P2,    KC_P3,    KC_PMNS,
    KC_BSPC,  KC_P0,    KC_PDOT,  KC_ENT
  ),
  [1] = LAYOUT(
    NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4,
    KC_CUT,   KC_PSTE,  KC_UP,    KC_VOLD,
    KC_COPY,  KC_LEFT,  KC_RSFT,  KC_RGHT,
    KC_UNDO,  KC_AGIN,  KC_DOWN,  KC_DEL,
    KC_LCTL,  KC_LSFT,  KC_LALT,  KC_SPC
  ),
  [2] = LAYOUT(
    NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4,
    KC_F13,   KC_F14,   KC_F15,   KC_F16,
    KC_F17,   KC_F18,   KC_F19,   KC_F20,
    KC_F21,   KC_F22,   KC_F23,   KC_F24,
    KC_LCTL,  KC_LSFT,  KC_LALT,  KC_SPC
  )
};

void keyboard_post_init_user(void) {
    // Set RGB light when connected to computer
    rgblight_enable();
    rgblight_sethsv(HSV_RED);
    wait_ms(700);
    rgblight_setrgb(32, 58, 69);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Update RGB color when layer changes
    uint8_t current_layer = biton32(state);
    switch (current_layer) {
        case 0:
            rgblight_setrgb(32, 58, 69);
            break;
        case 1:
            rgblight_setrgb(92, 87, 1);
            break;
        case 2:
            rgblight_setrgb(87, 11, 87);
            break;
        // Add more cases for additional layers
        default:
            rgblight_setrgb(32, 58, 69);
            break;
    }
    return state;
}

// Variables to keep track of key press duration
static uint16_t key_timer;
static bool was_key_held;

// Handle custom keycodes on the keymap layers
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

//NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4 are custom keycodes for performing actions on hold or tap.
        case NUMPAD_1:
            if (record->event.pressed) {
                key_timer = timer_read();
                was_key_held = false;
            } else {
                if (was_key_held) {
                    layer_move(0);
                } else {
                    if (layer_state_is(0)) {
                        tap_code(KC_CALC);
                    };
                    if (layer_state_is(1)) {
                        tap_code(KC_MPLY);
                    };
                    if (layer_state_is(2)) {
                        if (rgblight_is_enabled()) {
                            rgblight_disable();
                        } else {
                            rgblight_enable();
                            rgblight_setrgb(87, 11, 87);
                        };
                    };
                }
            }
            return false;

        case NUMPAD_2:
            if (record->event.pressed) {
                key_timer = timer_read();
                was_key_held = false;
            } else {
                if (was_key_held) {
                    layer_move(1);
                } else {
                    if (layer_state_is(0)) {
                        register_code(KC_LSFT);
                        tap_code(KC_9);
                        unregister_code(KC_LSFT);
                    };
                    if (layer_state_is(1)) {
                        tap_code(KC_MPRV);
                    };
                    if (layer_state_is(2)) {
                        SEND_STRING(SS_LGUI("d")); // This simulates pressing the Windows key and typing "D" to show the desktop                    
                    };
                }
            }
            return false;

        case NUMPAD_3:
            if (record->event.pressed) {
                key_timer = timer_read();
                was_key_held = false;
            } else {
                if (was_key_held) {
                    layer_move(2);
                } else {
                    if (layer_state_is(0)) {
                        register_code(KC_LSFT);
                        tap_code(KC_0);
                        unregister_code(KC_LSFT);
                    } else if (layer_state_is(1)) {
                        tap_code(KC_MNXT);
                    } else if (layer_state_is(2)) {
                        SEND_STRING(SS_LGUI("l")); // This simulates pressing the Windows key and typing "l" to lock the computer
                    }
                }
            }
            return false;

        case NUMPAD_4:
            if (record->event.pressed) {
                key_timer = timer_read();
                was_key_held = false;
            } else {
                if (was_key_held) {
                    tap_code(KC_PSCR);
                } else {
                    if (layer_state_is(0)) {
                        tap_code(KC_PAST);
                    } else if (layer_state_is(1)) {
                        tap_code(KC_VOLU);
                    } else if (layer_state_is(2)) {
                        for (int i = 0; i < 6; i++) {
                            rgblight_toggle();
                            wait_ms(500);
                        }
                        bootloader_jump();
                    }
                }
            }
            return false;


//custom keycodes located on layer 1 for shortcuts, copy, paste, cut, undo, redo, and redo.
        case KC_COPY:
        if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c"));  // Sends Ctrl+c
      }
      return false;

      case KC_PSTE:
        if (record->event.pressed) {
        SEND_STRING(SS_LCTL("v"));  // Sends Ctrl+v
      }
      return false;

      case KC_CUT:
        if (record->event.pressed) {
        SEND_STRING(SS_LCTL("x"));  // Sends Ctrl+x
      }
      return false;

      case KC_UNDO:
        if (record->event.pressed) {
        SEND_STRING(SS_LCTL("z"));  // Sends Ctrl+z
      }
      return false;

      case KC_AGIN:
        if (record->event.pressed) {
        SEND_STRING(SS_LCTL(SS_LSFT("z")));  // Sends Ctrl+Shift+z
      }
      return false;

            // Handle more keycodes here as needed

        default:
            return true;
    }
}


void matrix_scan_user(void) {
    if (timer_elapsed(key_timer) > TAPPING_TERM && !was_key_held) {
        was_key_held = true;
    }
}