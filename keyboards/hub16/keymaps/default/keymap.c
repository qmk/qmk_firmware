/* Copyright 2019 Josh Johnson
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

// Allow reading of encoder switch
#define readInput(port, pin) (((*(&port - 2)) & (1 << pin)) ? 1 : 0)
#define SWITCH_1 PF7
#define SWITCH_1_PORT PORTF
#define SWITCH_2 PD7
#define SWITCH_2_PORT PORTD

// Function key we are 'wrapping' usual key presses in
#define KC_WRAP KC_F24

// Tap Dance Declarations
enum { TD_TO_LED = 0, TD_TO_DEFAULT = 1 };

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for HID, twice to toggle layer 1
    [TD_TO_LED]     = ACTION_TAP_DANCE_DUAL_ROLE(_______, 1),
    [TD_TO_DEFAULT] = ACTION_TAP_DANCE_DUAL_ROLE(_______, 0)};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_A, KC_B, KC_C, KC_D, \
    KC_E, KC_F, KC_G, KC_H, \
    KC_I, KC_J, KC_K, KC_L, \
    KC_M, KC_N, KC_O, TD(TD_TO_LED) \
  ),

  [1] = LAYOUT( /* LED Control */
    _______, RGB_MOD, RGB_RMOD, RGB_TOG, \
    RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, \
    RGB_SAD, RGB_SAI, _______, _______, \
    _______, _______, RESET, TD(TD_TO_DEFAULT) \
  ),
};

// Keyboard is setup to 'warp' the pressed key with F24,
// allowing for easy differentiation from a real keyboard.
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left Encoder */
        if (clockwise) {
            register_code(KC_WRAP);
            tap_code(KC_R);
            unregister_code(KC_WRAP);
        } else {
            register_code(KC_WRAP);
            tap_code(KC_Q);
            unregister_code(KC_WRAP);
        }
    } else if (index == 1) { /* Right Encoder */
        if (clockwise) {
            register_code(KC_WRAP);
            tap_code(KC_U);
            unregister_code(KC_WRAP);
        } else {
            register_code(KC_WRAP);
            tap_code(KC_T);
            unregister_code(KC_WRAP);
        }
    }
}

// Below stolen from TaranVH (https://github.com/TaranVH/2nd-keyboard/blob/master/HASU_USB/F24/keymap.c)
// Shoutout to drashna on the QMK discord for basically writing this for me.... :P

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t f24_tracker;
    switch (keycode) {
        case KC_A ... KC_F23:
        case KC_EXECUTE ... KC_EXSEL:
            if (record->event.pressed) {
                register_code(KC_WRAP);
                f24_tracker++;
                register_code(keycode);
            } else {
                unregister_code(keycode);
                f24_tracker--;
                if (!f24_tracker) {
                    unregister_code(KC_WRAP);
                }
            }
            return false;
            break;
    }
    return true;
}

void matrix_init_user(void) {
    // Set encoder switches as inputs
    setPinInput(SWITCH_1);
    setPinInput(SWITCH_2);
}

void matrix_scan_user(void) {
    /* Below is a hack to make up for a mistake in hardware.
     * I did not connect the encoder buttons in the matrix, and could not
     * get it working as a DIRECT_PINS in conjunction with the matrix.
     * readPin from quantum.h also didn't work, so implemented my own read macro
     * Not proud or happy with the below, but it works.
     */

    // Debounce the encoder buttons using a shift register
    static uint8_t btn_1_array;
    static uint8_t btn_2_array;
    uint8_t        btn_1_rising;
    uint8_t        btn_2_rising;
    btn_1_array <<= 1;
    btn_2_array <<= 1;
    btn_1_array |= readInput(SWITCH_1_PORT, SWITCH_1);
    btn_2_array |= readInput(SWITCH_2_PORT, SWITCH_2);
    (btn_1_array == 0b01111111) ? (btn_1_rising = 1) : (btn_1_rising = 0);
    (btn_2_array == 0b01111111) ? (btn_2_rising = 1) : (btn_2_rising = 0);

    // Act upon button press
    if (btn_1_rising) {
        btn_1_rising = 0;
        register_code(KC_WRAP);
        tap_code(KC_S);
        unregister_code(KC_WRAP);
    }

    if (btn_2_rising) {
        btn_2_rising = 0;
        register_code(KC_WRAP);
        tap_code(KC_V);
        unregister_code(KC_WRAP);
    }
}

void led_set_user(uint8_t usb_led) {}