/*
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or
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

#ifdef OS_DETECTION_ENABLE
  #include "os_detection.h"
#endif

enum layers {
    _DEFAULT,
    _NAV,
    _FN,
    _GAME,
    _NUM,
    _LAYERS
};

enum keycodes {
    KC_NEXT_LAYER = QK_USER,
};

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END (_LAYERS - 1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(_NAV),  KC_NEXT_LAYER, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH, KC_RCTL,
                                   KC_LGUI, KC_LALT, MO(_NUM), KC_ENT,             KC_SPACE, KC_BSPC, KC_RALT, KC_RGUI
    ),

    [_FN] = LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                       BL_TOGG, BL_STEP, BL_ON,   BL_UP,   KC_NO,   KC_NO,
        KC_NO,   RGB_HUD, RGB_SAD, RGB_VAD, KC_NO,   KC_NO,                         BL_BRTG, BL_OFF,  BL_DOWN, KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   MO(_NAV),    KC_NEXT_LAYER,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                    KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_NAV] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NEXT_LAYER,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                    KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_GAME] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    MO(_NAV),  KC_NEXT_LAYER, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH, KC_RCTL,
                                   KC_LGUI, KC_LALT, MO(_NUM), KC_SPACE,             KC_ENT, KC_BSPC, KC_RALT, KC_RGUI
    ),

    [_NUM] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_BSPC,    KC_EQUAL,   KC_SLASH,   KC_KP_ASTERISK,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_7,       KC_8,       KC_9,       KC_KP_MINUS,    KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_4,       KC_5,       KC_6,       KC_KP_PLUS,     KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NEXT_LAYER,   KC_1,   KC_2,   KC_3,   KC_KP_ENTER,   KC_NO,   KC_NO,
                                    KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_ENTER,   KC_0,   KC_KP_DOT,   KC_NO
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_NEXT_LAYER:
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) {
        // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
        return false;
      }

      uint8_t current_layer = get_highest_layer(layer_state);

      // Check if we are within the range, if not quit
      if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
        return false;
      }

      uint8_t next_layer = current_layer + 1;
      if (next_layer > LAYER_CYCLE_END) {
          next_layer = LAYER_CYCLE_START;
      }
      layer_move(next_layer);
      return false;

    // Process other keycodes normally
    default:
      return true;
  }
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_RED); // sets the color to red without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing w/o saving
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
        switch (get_highest_layer(layer_state)) {
            case _DEFAULT:
                // Control volume on the default layer
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case _NAV:
                // Cycle through desktops on the NAV layer
                if (clockwise) {
                    tap_code16(G(KC_TAB)); // Switch to next desktop
                } else {
                    tap_code16(S(G(KC_TAB))); // Switch to previous desktop
                }
                break;
            case _FN:
                // Add and switch to a new desktop
                if (clockwise) {
                    tap_code16(G(KC_D)); // Windows: Create a new virtual desktop
                } else {
                    tap_code16(G(S(KC_D))); // macOS/Windows: Close current desktop
                }
                break;
        }
    return true;
}
#endif



#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
};

bool oled_task_user(void) {

    if (is_keyboard_master()) {
        oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
            case _DEFAULT:
                oled_write_P(PSTR("Default\n"), false);
                break;
            case _FN:
                oled_write_P(PSTR("FN\n"), false);
                break ;
            case _NAV:
                oled_write_P(PSTR("NAV\n"), false);
                break;
            case _GAME:
                oled_write_P(PSTR("GAME\n"), false);
                break;
            case _NUM:
                oled_write_P(PSTR("NUM\n"), false);
                break;
            default:
                // Or use the write_ln shortcut over adding '\n' to the end of your string
                oled_write_ln_P(PSTR("Undefined"), false);
        }
    } else {

    #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_UNSURE:
                oled_write_P(PSTR("OS_UNSURE"), false);
                break;
            case OS_LINUX:
                oled_write_P(PSTR("OS_LINUX"), false);
                break;
            case OS_WINDOWS:
                oled_write_P(PSTR("OS_WINDOWS"), false);
                break;
            case OS_MACOS:
                oled_write_P(PSTR("OS_MACOS"), false);
                break;
            case OS_IOS:
                oled_write_P(PSTR("OS_IOS"), false);
                break;
            default:
                oled_write_P(PSTR("Unknown"), false);
            }
    #endif
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif
