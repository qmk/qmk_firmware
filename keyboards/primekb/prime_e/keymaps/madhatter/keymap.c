/* Copyright 2018 Holten Campbell
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

#define BLINK_DURATION 512
#define CAPS_LED_PIN B1
#define NUM_LED_PIN B2
#define SCROLL_LED_PIN B3

uint8_t CAPS;
uint16_t BLINK_TIMER = 0;
uint8_t CAPS_LED_STATE = 0;

// Init togg_indicator so the compiler doesn't complain when I declare it last.
static void togg_indicator(uint8_t *state, uint8_t pin);

enum ilpse_layers {
    _QWERTY,
    _LOWER,
    _RAISE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define GUBS RGUI_T(KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_GESC, KC_Q,  KC_W,  KC_E,  KC_R,   KC_T,    KC_Y,  KC_U,  KC_I,  KC_O,    KC_P,    KC_MINS, KC_BSPC,
    KC_TAB,  KC_A,  KC_S,  KC_D,  KC_F,   KC_G,    KC_H,  KC_J,  KC_K,  KC_L,    KC_SCLN, KC_ENT,
    KC_LSPO, KC_Z,  KC_X,  KC_C,  KC_V,   KC_B,    KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
    KC_LCTL, KC_LALT,          LOWER,  GUBS,      KC_SPC,  RAISE,          KC_RGUI, KC_RCTL
  ),

  [_LOWER] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, KC_QUOT,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS,
    KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS,          KC_TRNS, KC_TRNS
  ),

  [_RAISE] = LAYOUT(
    KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,  KC_DEL,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE, KC_ENT,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_UNDS, KC_PLUS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    QK_BOOT, KC_TRNS,                  KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS,          KC_TRNS, KC_TRNS
  )
};

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(CAPS_LED_PIN);
  writePinLow(CAPS_LED_PIN);
  // set NumLock LED to output and low
  setPinOutput(NUM_LED_PIN);
  writePinLow(NUM_LED_PIN);
  // set ScrollLock LED to output and low
  setPinOutput(SCROLL_LED_PIN);
  writePinLow(SCROLL_LED_PIN);
}

void matrix_scan_user(void) {
    if (CAPS == 1) {
        // Blink the first led when capslock is active
        if (BLINK_TIMER >= BLINK_DURATION) {
            togg_indicator(&CAPS_LED_STATE, CAPS_LED_PIN);
            BLINK_TIMER = 0;
        }
        BLINK_TIMER++;
    }
}

//function for layer indicator LED
layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(CAPS_LED_PIN, layer_state_cmp(state, 0));
    writePin(NUM_LED_PIN, layer_state_cmp(state, 1));
    writePin(SCROLL_LED_PIN, layer_state_cmp(state, 2));
    return state;
}

void led_set_user(uint8_t usb_led) {
    CAPS = IS_LED_ON(usb_led, USB_LED_CAPS_LOCK);
}

void togg_indicator(uint8_t *state, uint8_t pin) {
    // Toggles a pin based on the current state
    if (*state == 0){
        *state = 1;
        writePinHigh(pin);
    }
    else if (*state == 1){
        *state = 0;
        writePinLow(pin);
    }
}
