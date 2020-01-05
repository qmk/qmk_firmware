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
#define KC_WRAP KC_24

// Tap Dance Declarations
enum { TD_TO_LED = 0, TD_TO_DEFAULT = 1 };

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for HID, twice to toggle layer 1
    [TD_TO_LED]     = ACTION_TAP_DANCE_DUAL_ROLE(_______, 1),
    [TD_TO_DEFAULT] = ACTION_TAP_DANCE_DUAL_ROLE(_______, 0)};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_0, KC_1, KC_2, KC_3, \
    KC_4, KC_5, KC_6, KC_7, \
    KC_8, KC_9, KC_A, KC_B, \
    KC_C, KC_D, KC_E, KC_F \
  )
};

// Keyboard is setup to 'warp' the pressed key with F24,
// allowing for easy differentiation from a real keyboard.
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left encoder */
        if (clockwise) {
            tap_code(KC_I);
        } else {
            tap_code(KC_J);
        }
    } else if (index == 1) { /* Right encoder */
        if (clockwise) {
            tap_code(KC_K);
        } else {
            tap_code(KC_L);
        }
    }
}

// Below stolen from TaranVH (https://github.com/TaranVH/2nd-keyboard/blob/master/HASU_USB/F24/keymap.c)
// Shoutout to drashna on the QMK discord for basically writing this for me.... :P

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {}
    return true;
}

void matrix_init_user(void) {
    // Set encoder switches as inputs
    (DDRF) &= ~(SWITCH_1);
    (DDRD) &= ~(SWITCH_2);
}

void matrix_scan_user(void) {
    /* Below is a hack to make up for a mistake in hardware.
     * Ideally the buttons would be dealt with as normal keys on the
     * keyboard, but without a hardware revision I don't believe it is possible.
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
        tap_code(KC_G);
    }

    if (btn_2_rising) {
        btn_2_rising = 0;
        tap_code(KC_H);
    }
}

void led_set_user(uint8_t usb_led) {}