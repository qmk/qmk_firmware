/* Copyright 2021 Qiaowei Tang
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


 /*
 * LED ranges for Think6.5v2 2U
 * These values were derived from manual testing. Derived from keymaps/rys.
 * ┌───────┬───────┬─────────────┬───────────────────────────────────────────┐
 * │ 00 01 │ 02 03 │ 04 05 06 07 │ 08 09 10 11 12 13 14 15 16 17 18 19 20 21 │
 * │ badge │ badge │    (?)      │              underglow (?)                │
 * │  bar  │ icon  │             │                                           │
 * └───────┴───────┴─────────────┴───────────────────────────────────────────┘
 */

// Define the LED ranges                  start, end
#define THINK65_LED_RANGE_OFF                 0, 0
#define THINK65_LED_RANGE_CAPS                0, 2
#define THINK65_LED_RANGE_BADGE               0, 4
#define THINK65_LED_RANGE_UNDERGLOW           4, 22
#define THINK65_LED_RANGE_ALL                 0, 22

// Turn the LEDs off by setting HSV to 0, 0, 0
#define THINK65_LEDS_OFF                      0, 0, 0

// Caps Lock indicator LED
#define THINK65_LEDS_CAPS                    0, 0, 255

#define THINK65_LED_STATE_OFF                 0x0 // 0b00000000
#define THINK65_LED_STATE_CAPS                0x1 // 0b00000001
#define THINK65_LED_STATE_BADGE               0x2 // 0b00000010
#define THINK65_LED_STATE_CAPS_AND_BADGE      0x3 // 0b00000011

// Define each LED range as a bit flag
#define THINK65_LED_CAPS_RANGE_BIT            0
#define THINK65_LED_BADGE_RANGE_BIT           1

// Setup some keycodes to control cycling and range toggling
enum {
    KVM_SW1 = SAFE_RANGE,
    KVM_SW2,
    CYC_LED,
    TOG_BDG
};

// setup the user EEPROM space we need
typedef union {
    uint8_t raw;
    struct {
        uint8_t current_led_state:8;
    };
} user_config_t;

user_config_t user_config;

// toggle one of the range flag bits
void toggle_led_state(unsigned int led_range) {
    if (led_range >= THINK65_LED_CAPS_RANGE_BIT && led_range <= THINK65_LED_BADGE_RANGE_BIT) {
        user_config.current_led_state ^= 1 << led_range;
    }
}

// set one of the range flag bits
void set_led_state(unsigned int led_range) {
    if (led_range >= THINK65_LED_CAPS_RANGE_BIT && led_range <= THINK65_LED_BADGE_RANGE_BIT) {
        user_config.current_led_state |= 1 << led_range;
    }
}

// clear one of the range flag bits
void clear_led_state(unsigned int led_range) {
    if (led_range >= THINK65_LED_CAPS_RANGE_BIT && led_range <= THINK65_LED_BADGE_RANGE_BIT) {
        user_config.current_led_state &= ~(1 << led_range);
    }
}

// cycle LED states: Off -> Esc -> Badge -> Underglow -> Esc+Badge -> Esc+Underglow -> Badge+Underglow -> All
void cycle_led_state(void) {
    switch(user_config.current_led_state) {
        case THINK65_LED_STATE_OFF:
            user_config.current_led_state = THINK65_LED_STATE_CAPS;
            break;
        case THINK65_LED_STATE_CAPS:
            user_config.current_led_state = THINK65_LED_STATE_BADGE;
            break;
        case THINK65_LED_STATE_BADGE:
            user_config.current_led_state = THINK65_LED_STATE_CAPS_AND_BADGE;
            break;
        case THINK65_LED_STATE_CAPS_AND_BADGE:
            user_config.current_led_state = THINK65_LED_STATE_OFF;
            break;
        default:
            break;
    }
}

void apply_led_state(void) {
    uint8_t h = rgblight_get_hue();
    uint8_t s = rgblight_get_sat();
    uint8_t v = rgblight_get_val();

    // Set the RGB ranges based on the current state
    switch(user_config.current_led_state) {
        case THINK65_LED_STATE_OFF:
            rgblight_sethsv_range(THINK65_LEDS_OFF,     THINK65_LED_RANGE_ALL);
            break;
        case THINK65_LED_STATE_CAPS:
            rgblight_sethsv_range(THINK65_LEDS_OFF,     THINK65_LED_RANGE_BADGE);
            rgblight_sethsv_range(THINK65_LEDS_CAPS,    THINK65_LED_RANGE_CAPS);
            break;
        case THINK65_LED_STATE_BADGE:
            rgblight_sethsv_range(THINK65_LEDS_OFF,     THINK65_LED_RANGE_CAPS);
            rgblight_sethsv_range(h, s, v,              THINK65_LED_RANGE_BADGE);
            break;
        case THINK65_LED_STATE_CAPS_AND_BADGE:
            rgblight_sethsv_range(h, s, v,              THINK65_LED_RANGE_BADGE);
            rgblight_sethsv_range(THINK65_LEDS_CAPS,    THINK65_LED_RANGE_CAPS);
            break;
        default:
            break;
    }
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();

    if (user_config.current_led_state >= THINK65_LED_STATE_OFF && user_config.current_led_state <= THINK65_LED_STATE_CAPS_AND_BADGE) {
        // If the current state read from user EEPROM is valid, apply it
        apply_led_state();
    } else {
        // Setup a new default state of off
        user_config.current_led_state = THINK65_LED_STATE_OFF;
        apply_led_state();
        eeconfig_update_user(user_config.raw);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KVM_SW1:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_RCTL) SS_TAP(X_RCTL) "1");
            } else {}
            break;
        case KVM_SW2:
            if(record->event.pressed) {
                SEND_STRING(SS_TAP(X_RCTL) SS_TAP(X_RCTL) "2");
            } else {}
            break;
        case CYC_LED:
            if (record->event.pressed) {
                cycle_led_state();
                apply_led_state();
                eeconfig_update_user(user_config.raw);
            }
            break;
        case TOG_BDG:
            if (record->event.pressed) {
                toggle_led_state(THINK65_LED_BADGE_RANGE_BIT);
                apply_led_state();
                eeconfig_update_user(user_config.raw);
            }
            break;
        case KC_CAPS:
            if (!record->event.pressed) {
                // connect capslock LED control to the badge LEDs
                host_keyboard_led_state().caps_lock ? set_led_state(THINK65_LED_CAPS_RANGE_BIT) : clear_led_state(THINK65_LED_CAPS_RANGE_BIT);
                apply_led_state();
                eeconfig_update_user(user_config.raw);
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer
    * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
    * │Esc│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ Bckspc│` ~│
    * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
    * │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│|   \│Del│
    * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
    * │HyCaps│ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│   Enter│   │
    * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤   │
    * │Shift   │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│ Shift│ Up│   │
    * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
    * │Ctrl│ Opt│ Cmd│          Space         │Cmd │FnPy│ │Lef│Dow│Rig│
    * └────┴────┴────┴────────────────────────┴────┴────┴─┴───┴───┴───┘
    */
    [0] = LAYOUT_65_ansi_blocker(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           XXXXXXX,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   XXXXXXX,
        KC_LCTL, KC_LGUI, KC_LALT,                      KC_SPC,                          MO(1),   KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────────┬───┐
     * │RST│ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│        │SW1│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┼───┤
     * │ TOG │PLN│MOD│HU+│HU-│SA+│SA-│VA+│VA-│   │   │Hom│End│      │SW2│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴──────┼───┤
     * │      │CYC│BDG│UGL│CAP│   │   │   │   │   │   │   │         │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬────┤   │
     * │        │   │   │   │   │   │   │   │   │   │   │      │Vol+│   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼────┼───┤
     * │    │    │    │                        │    │    │ │   │Vol-│   │
     * └────┴────┴────┴────────────────────────┴────┴────┴─┴───┴────┴───┘
     */
    [1] = LAYOUT_65_ansi_blocker(
        RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KVM_SW1,
        TOG_BDG, RGB_M_P, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, KC_HOME, KC_END,  _______, KVM_SW2,
        _______, CYC_LED, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_VOLU, _______,
        _______, _______, _______,                      _______,                         _______, _______,          _______, KC_VOLD, _______
    ),

};

