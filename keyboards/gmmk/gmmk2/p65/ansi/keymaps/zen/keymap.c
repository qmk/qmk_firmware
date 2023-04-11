/* Copyright 2023 zen <github@desultory>
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

// For debugging
#include "print.h"

// Config for this keyboard model
#include QMK_KEYBOARD_H

// Needed for caps lock animation https://github.com/filterpaper/qmk_userspace/blob/main/rgb/rgb-matrix.c#L72-L75
#include "lib/lib8tion/lib8tion.h"

// For random
#include <stdio.h> // for sprintf()
#include <stdlib.h> // for rand() and srand()
#include <time.h>   // for time()
#include "hal.h"  // for MCU access
#include "analog.h" // to read hardware for entropy

// For leader
#include <process_leader.h> // for leader

// Custom keys for rgb modes
enum custom_keycodes {
    RGB_RCT = SAFE_RANGE, // Set rgb to reactive mode
    RGB_HTM, // Set RGB to heatmap mode
    RGB_RBW, // Set RGB to rainbow mod
    CST_RCH,  // Print a random base64 character
    CST_RND,  // Generate random string
};

enum custom_layers {
    _BL,
    _FL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BL] = LAYOUT(
  QK_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,    KC_BSPC,  KC_DEL,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,   KC_BSLS,  KC_PGUP,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,             KC_ENT,   KC_PGDN,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,   KC_UP,    KC_END,
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,	  KC_RALT,  MO(_FL),  KC_LEFT,   KC_DOWN,  KC_RGHT),

[_FL] = LAYOUT(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,    _______,  KC_INS,
  CST_RND,  RGB_SAI,  RGB_VAI,  RGB_HUI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,   KC_MPLY,  KC_RCTL,
  CST_RCH,  RGB_RMOD, RGB_VAD,  RGB_MOD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,             KC_MUTE,  KC_RCTL,
  _______,  RGB_HTM,  RGB_RCT,  RGB_RBW,  _______,  QK_BOOT,  _______,  _______,  _______,  QK_LEAD,  KC_MPLY,            _______,   KC_VOLU,  KC_HOME,
  _______,  _______,  _______,                                 QK_RBT,	  _______,  _______,  KC_MPRV,   KC_VOLD,  KC_MNXT)};


// define the seed
uint32_t seed;
// Subtract these from 2^30 to get a prime
const uint16_t prime_diffs[] = {52061, 2847, 50181, 38901, 61595, 58931, 24761, 65433, 14471, 27731, 6461, 1361, 27977, 6815, 57441, 37505, 37761, 64353, 21021, 62753, 15431, 24485, 12617, 30543, 62345, 8963, 48887, 3471, 41363, 46455, 13887, 64005, 161, 1623, 49235, 2891, 5687, 61395, 48743, 747, 36881, 44561, 33795, 31833, 9317, 32787, 58541, 60785, 25403, 24273, 47063, 58637, 63327, 321, 56643, 8325, 54897, 35037, 55545, 22041, 37133, 25347, 38073, 12597};
const uint8_t num_prime_diffs = sizeof(prime_diffs)/sizeof(prime_diffs[0]);
// define the prime 2^30 - prime diff
// 1 shifted to the left 30 times is w ^ 31
// start with the first one
uint32_t prime = (1 << 30) - prime_diffs[0];
// Define the random mode
bool custom_random_mode;
// define default random string length
uint16_t random_string_length = 32;
// define the random string rekey interval
uint16_t rekey_interval = 4;
// define indicator speed
uint8_t indicator_speed = 128;

// Custom post init
void keyboard_post_init_user() {
    // Enable debugging by default
    debug_enable = false;
    // Define and set the random char mode
    // True enables the custom mode
    // false uses the qmk mode
    custom_random_mode = true;
    // Enable temp out
    ANCTL->BGCR2 |= ANCTL_BGCR2_TEMPOUTEN;
    // Wake up temp sensor
    ADC->CR2 |= ADC_CR2_TSVREFE;
    // Do initial seeding
    seed = prime * (chVTGetSystemTimeX() + adc_read(TO_MUX(ADC_CHANNEL_SENSOR, 0)));
    srand(seed);
}

void recalc_entropy(void) {
    // Recalculate a prime
    // subtracts a known prime diff from 2^30
    prime = (1 << 30) - prime_diffs[rand() % num_prime_diffs];
    dprintf("Set prime to: %ld\n", prime);
    // Generate new random seed, there is very little entropy on boot, derive the seed from the current temp/uptime/words per minute
    // Just add the values in case the seed is 0, otherwise, multiply
    seed = (seed == 0) ? get_current_wpm() + chVTGetSystemTimeX() + adc_read(TO_MUX(ADC_CHANNEL_SENSOR, 0)) + prime :
                         seed * (get_current_wpm() + chVTGetSystemTimeX() + adc_read(TO_MUX(ADC_CHANNEL_SENSOR, 0))) + prime;
    // Use the old random seed to determine how many times the new seed should cycle before returning
    uint8_t random_cycles = rand() % 255;
    // Reseed the random function
    srand(seed);
    dprintf("Seed set to: %ld\n", seed);
    // Cycle the new seed
    dprintf("Cycling this seed %d times\n", random_cycles);
    for (uint8_t i=0; i<random_cycles; i++) {
        rand();
    }
}

void send_random_str(void) {
    dprintf("Generating a random string with size: %d\n", random_string_length);
    // Checks iof the custom mode is enabled, theoretically more resource intensive, but pretty fast
    if (custom_random_mode) {
        // Define all allowed characters
        const char b64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        // Define parameters
        uint8_t position = 0;
        uint8_t allowed_mod = sizeof(b64_chars)-1;

        for(uint16_t i=0; i<random_string_length; i++) {
            // Recalc entropy every 32 characters, happens on first run as well
            if (i % rekey_interval == 0) {
                dprintf("At position %d of %d\n", i, random_string_length);
                recalc_entropy();
            }
            position = rand() % allowed_mod;
            char random_char = b64_chars[position];
            send_char(random_char);
        }
    } else {
        for(uint16_t i=0; i<random_string_length; i++) {
            tap_random_base64();
        }
    }
}

// Handle custom RGB mode keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CST_RCH:
            if (record->event.pressed) {
                tap_random_base64();
            }
            return false;
            break;
        case CST_RND:
            if (record->event.pressed) {
                send_random_str();
            }
            return false;
            break;
        case RGB_HTM:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
            }
            return false;
            break;
        case RGB_RBW:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_RAINBOW_BEACON);
            }
            return false;
            break;
        case RGB_RCT:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS);
            }
            return false;
    }

    return true;
}


// Override the advanced rgb matrix for caps indicator
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Define the red glow rgb
    HSV hsv = (HSV){HSV_WHITE};
    // Based on the breathing effect, uses globally defined speed
    hsv.v = scale8(abs8(sin8(scale16by8(g_rgb_timer, indicator_speed / 8)) - 128) * 2, hsv.v);
    // Defined on a function level so it can be used to indicate different modes
    RGB glow = hsv_to_rgb(hsv);

    if (host_keyboard_led_state().caps_lock) {
        const uint8_t caps_key_index = 30; // Based on the index of the KC_CAPS key in the keymaps
        const uint8_t c_key_index = 47; // c
        const uint8_t a_key_index = 31; // a
        const uint8_t p_key_index = 24; // p
        const uint8_t s_key_index = 32; // s
        const uint8_t l_key_index = 39; // l
        const uint8_t o_key_index = 25; // o
        const uint8_t k_key_index = 38; // k
        const uint8_t light_chars[] = {caps_key_index, c_key_index, a_key_index, p_key_index, s_key_index, l_key_index, o_key_index, k_key_index};
        for (uint8_t i=0 ; i<sizeof(light_chars)/sizeof(light_chars[0]); i++) {
            rgb_matrix_set_color(light_chars[i], glow.r, 0, 0);
        }

        // Loop through all keys, if the key is an underglow key, set the color
        for (uint8_t i = led_min; i < led_max; i++) {
            // If the light is an underglow light, just set it to glow
            if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW) {
                rgb_matrix_set_color(i, glow.r, 0, 0);
            // otherwise make all keys red when peaking
            } else if (glow.r > 224 && g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, glow.r, 0, 0);
            }
        }
    }

    if (debug_enable) {
        const uint8_t esc_key_index = 0; // Based on the index of the KC_ESC key in the keymaps
        const uint8_t d_key_index = 33; // d
        const uint8_t e_key_index = 18; // e
        const uint8_t b_key_index = 49; // b
        const uint8_t u_key_index = 22; // u
        const uint8_t g_key_index = 35; // g
        const uint8_t light_chars[] = {esc_key_index, d_key_index, e_key_index, b_key_index, u_key_index, g_key_index};
        for (uint8_t i=0 ; i<sizeof(light_chars)/sizeof(light_chars[0]); i++) {
            rgb_matrix_set_color(light_chars[i], 0, 0, glow.b);
        }
    }
    if (leading) {
        const uint8_t leader_key_index = 53;
        rgb_matrix_set_color(leader_key_index, 0, 255, 0);
    }
    return true;
}

// Leader config
// Simple override, mostly for debug
void leader_start(void) {
    dprint("Leader starting\n");
}

// Another debug override
void leader_end(void) {
    dprintf("Leader ending\n");
}



// leader
void leader_end_user(void) {
        leading = false;
        // Debug mode
        if (leader_sequence[0] == KC_D) {
            // If only d is pressed, toggle debugging
            if (leader_sequence_size == 1) {
                dprint("Debugging toggle triggered\n");
                if (debug_enable) {
                    print("Disabling debug mode\n");
                    debug_enable = false;
                } else {
                    print("Enabling debug mode\n");
                    debug_enable = true;
                }
            }
            // Enable debugging
            if (leader_sequence[1] == KC_1 || leader_sequence[1] == KC_E) {
                    print("Enabling debug mode\n");
                    debug_enable = true;
            }
            // Disable debugging
            if (leader_sequence[1] == KC_0 || leader_sequence[1] == KC_D) {
                    print("Disabling debug mode\n");
                    debug_enable = false;
            }
            // Print the RGB mode
            if (leader_sequence[1] == KC_M) {
                printf("Current RGB mode number: %d\n", rgb_matrix_get_mode());
                if (debug_enable) {
                    char out_str[8];
                    sprintf(out_str, "%d", rgb_matrix_get_mode());
                    SEND_STRING(out_str);
                }
            }
            // Print the system time
            if (leader_sequence[1] == KC_T) {
                printf("Current system time: %ld\n", chVTGetSystemTimeX());
                if (debug_enable) {
                    char out_str[16];
                    sprintf(out_str, "%ld", chVTGetSystemTimeX());
                    SEND_STRING(out_str);
                }
            }
            // Print the WPM
            if (leader_sequence[1] == KC_W) {
                printf("Current WPM: %d\n", get_current_wpm());
                if (debug_enable) {
                    char out_str[8];
                    sprintf(out_str, "%d", get_current_wpm());
                    SEND_STRING(out_str);
                }
            }
        }
        // Random mode
        if (leader_sequence[0] == KC_R) {
            if (leader_sequence[1] == KC_C) {
                custom_random_mode = true;
                dprint("Custom random mode enabled\n");
                return;
            } else if (leader_sequence[1] == KC_B) {
                custom_random_mode = false;
                dprint("Builtin random mode enabled\n");
                return;
            }
            // Print the RNG string rekey interval
            if (leader_sequence[1] == KC_K) {
                printf("Current RNG rekey inerval: %d\n", rekey_interval);
                if (debug_enable) {
                    char out_str[8];
                    sprintf(out_str, "%d", rekey_interval);
                    SEND_STRING(out_str);
                }
                return;
            }
            // Print the RNG string length
            if (leader_sequence[1] == KC_L) {
                printf("Current RNG string length: %d\n", random_string_length);
                if (debug_enable) {
                    char out_str[8];
                    sprintf(out_str, "%d", random_string_length);
                    SEND_STRING(out_str);
                }
                return;
            }
            // Print the RNG mode
            if (leader_sequence[1] == KC_M) {
                printf("Current RNG mode: %s\n", (custom_random_mode) ? "Random mode: Custom\n" : "Random mode: Builtin\n");
                if (debug_enable) {
                    char out_str[24];
                    sprintf(out_str, "%s", (custom_random_mode) ? "Random mode: Custom\n" : "Random mode: Builtin\n");
                    SEND_STRING(out_str);
                }
                return;
            }
            // Print the curent prime
            if (leader_sequence[1] == KC_P) {
                printf("Current prime: %ld\n", prime);
                if (debug_enable) {
                    char out_str[16];
                    sprintf(out_str, "%ld", prime);
                    SEND_STRING(out_str);
                }
                return;
            }
            // Print the current seed
            if (leader_sequence[1] == KC_S) {
                printf("Current RNG seed: %ld\n", seed);
                if (debug_enable) {
                    char out_str[8];
                    sprintf(out_str, "%ld", seed);
                    SEND_STRING(out_str);
                }
                return;
            }
            dprintf("Sequence size: %d\n", leader_sequence_size);

            // The number of digits to be processed
            uint8_t digits = leader_sequence_size - 1;
            dprintf("Digits: %d\n", digits);

            // Calculated random string length
            uint16_t calculated_number = 0;

            // Starting magnitude
            uint16_t magnitude = 1;

            // Iterate from the back of the leader to the front to calculate the input
            for (uint8_t i=digits; i>0; i--) {
                // The scaled value of the key being pressed
                uint16_t place_value = 0;
                // The integer value of a keypress
                uint8_t key_value = 0;
                // Name the key
                uint16_t key_code = leader_sequence[i];

                // 1-9, both because keycode 0 is greater than 9, and because nothing needs to be done in the case of 0
                if (key_code >= KC_1 && key_code <= KC_9) {
                    // Calculate key value by seeing the differnce between it and KC_1, with an offset of 1
                    key_value = 1 + key_code - KC_1;
                    // Calculate the value given the place
                    place_value = key_value * magnitude;
                    dprintf("i: %d\n", i);
                    dprintf("key value: %d\n", key_value);
                    dprintf("magnitude: %d\n", magnitude);
                    dprintf("place value: %d\n", place_value);
                    calculated_number += place_value;
                    magnitude *= 10;
                } else if (key_code == KC_0) {
                    // Still iterate magnitude in case of 0
                    magnitude *= 10;
                } else {
                    // Debug print
                    dprintf("Invalid character: %d\n", leader_sequence[i]);
                }
            }
            // update the random string as long as the calculated number is not 0
            random_string_length = (calculated_number == 0) ? random_string_length : calculated_number;
            send_random_str();
        }
        leader_end();
    }
}
