/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)

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

#include "ergodox_ez.h"
#include "gpio.h"

keyboard_config_t keyboard_config;

__attribute__((weak)) void keyboard_post_init_sub(void) {
    gpio_set_pin_output(ERGODOX_LED_1_PIN);
    gpio_set_pin_output(ERGODOX_LED_2_PIN);
    gpio_set_pin_output(ERGODOX_LED_3_PIN);
}

void keyboard_post_init_kb(void) {
    keyboard_post_init_sub();
#ifdef ERGODOX_LED_SHUTOFF_PIN
    gpio_set_pin_output(ERGODOX_LED_SHUTOFF_PIN);
#endif

    keyboard_config.raw = eeconfig_read_kb();
    ergodox_led_all_set((uint8_t)keyboard_config.led_level * 255 / 4);
    ergodox_blink_all_leds();
#if defined(RGB_MATRIX_ENABLE)
    if (rgb_matrix_get_mode() >= RGB_MATRIX_EFFECT_MAX) {
        rgb_matrix_mode(RGB_MATRIX_NONE);
    }
#endif

    keyboard_post_init_user();
}

void ergodox_board_led_on(void) {
#ifdef ERGODOX_LED_SHUTOFF_PIN
    gpio_write_pin_high(ERGODOX_LED_SHUTOFF_PIN);
#endif
}

__attribute__((weak)) void ergodox_right_led_1_on(void) {
    gpio_set_pin_output(ERGODOX_LED_1_PIN);
    gpio_write_pin_high(ERGODOX_LED_1_PIN);
}

__attribute__((weak)) void ergodox_right_led_2_on(void) {
    gpio_set_pin_output(ERGODOX_LED_2_PIN);
    gpio_write_pin_high(ERGODOX_LED_2_PIN);
}

__attribute__((weak)) void ergodox_right_led_3_on(void) {
    gpio_set_pin_output(ERGODOX_LED_3_PIN);
    gpio_write_pin_high(ERGODOX_LED_3_PIN);
}

void ergodox_board_led_off(void) {
#ifdef ERGODOX_LED_SHUTOFF_PIN
    gpio_write_pin_low(ERGODOX_LED_SHUTOFF_PIN);
#else
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
#endif
}

__attribute__((weak)) void ergodox_right_led_1_off(void) {
    gpio_set_pin_input(ERGODOX_LED_1_PIN);
    gpio_write_pin_low(ERGODOX_LED_1_PIN);
}

__attribute__((weak)) void ergodox_right_led_2_off(void) {
    gpio_set_pin_input(ERGODOX_LED_2_PIN);
    gpio_write_pin_low(ERGODOX_LED_2_PIN);
}

__attribute__((weak)) void ergodox_right_led_3_off(void) {
    gpio_set_pin_input(ERGODOX_LED_3_PIN);
    gpio_write_pin_low(ERGODOX_LED_3_PIN);
}

void ergodox_right_led_on(uint8_t led) {
    if (led == 1) {
        ergodox_right_led_1_on();
    } else if (led == 2) {
        ergodox_right_led_2_on();
    } else if (led == 3) {
        ergodox_right_led_3_on();
    }
}

void ergodox_right_led_off(uint8_t led) {
    if (led == 1) {
        ergodox_right_led_1_off();
    } else if (led == 2) {
        ergodox_right_led_2_off();
    } else if (led == 3) {
        ergodox_right_led_3_off();
    }
}

void ergodox_right_led_set(uint8_t led, uint8_t n) {
    if (led == 1) {
        ergodox_right_led_1_set(n);
    } else if (led == 2) {
        ergodox_right_led_2_set(n);
    } else if (led == 3) {
        ergodox_right_led_3_set(n);
    }
}

void ergodox_led_all_on(void) {
    ergodox_board_led_on();
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
}

void ergodox_led_all_off(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

void ergodox_led_all_set(uint8_t n) {
    ergodox_right_led_1_set(n);
    ergodox_right_led_2_set(n);
    ergodox_right_led_3_set(n);
}

void ergodox_blink_all_leds(void) {
    ergodox_led_all_off();
    ergodox_led_all_set(LED_BRIGHTNESS_DEFAULT);
    ergodox_right_led_1_on();
    wait_ms(50);
    ergodox_right_led_2_on();
    wait_ms(50);
    ergodox_right_led_3_on();
    wait_ms(50);

    ergodox_right_led_1_off();
    wait_ms(50);
    ergodox_right_led_2_off();
    wait_ms(50);
    ergodox_right_led_3_off();

    // ergodox_led_all_on();
    //_delay_ms(333);
    ergodox_led_all_set((uint8_t)keyboard_config.led_level * 255 / 4);

    ergodox_led_all_off();
}

#ifdef SWAP_HANDS_ENABLE
__attribute__((weak))
// swap-hands action needs a matrix to define the swap
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0, 13}, {1, 13}, {2, 13}, {3, 13}, {4, 13}, {5, 13}},
    {{0, 12}, {1, 12}, {2, 12}, {3, 12}, {4, 12}, {5, 12}},
    {{0, 11}, {1, 11}, {2, 11}, {3, 11}, {4, 11}, {5, 11}},
    {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}},
    {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}},
    {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
    /* Right hand, matrix positions */
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
};
#endif

layer_state_t layer_state_set_kb(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (get_highest_layer(state)) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
    }

    return layer_state_set_user(state);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LED_LEVEL:
            if (record->event.pressed) {
                keyboard_config.led_level++;
                if (keyboard_config.led_level > 4) {
                    keyboard_config.led_level = 0;
                }
                ergodox_led_all_set((uint8_t)keyboard_config.led_level * 255 / 4);
                eeconfig_update_kb(keyboard_config.raw);
                layer_state_set_kb(layer_state);
            }
            break;
#ifdef RGB_MATRIX_ENABLE
        case TOGGLE_LAYER_COLOR:
            if (record->event.pressed) {
                keyboard_config.disable_layer_led ^= 1;
                if (keyboard_config.disable_layer_led) rgb_matrix_set_color_all(0, 0, 0);
                eeconfig_update_kb(keyboard_config.raw);
            }
            break;
        case RM_TOGG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            return false;
#endif
    }
    return process_record_user(keycode, record);
}

void eeconfig_init_kb(void) { // EEPROM is getting reset!
    keyboard_config.raw       = 0;
    keyboard_config.led_level = 4;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

#ifdef DYNAMIC_MACRO_ENABLE
static bool     is_dynamic_recording = false;
static uint16_t dynamic_loop_timer;

void dynamic_macro_record_start_user(int8_t direction) {
    is_dynamic_recording = true;
    dynamic_loop_timer   = timer_read();
    ergodox_right_led_1_on();
}

void dynamic_macro_record_end_user(int8_t direction) {
    is_dynamic_recording = false;
    layer_state_set_user(layer_state);
}
#endif

void housekeeping_task_kb(void) {
#ifdef DYNAMIC_MACRO_ENABLE
    if (is_dynamic_recording) {
        ergodox_right_led_1_off();
        // if (timer_elapsed(dynamic_loop_timer) > 5)
        {
            static uint8_t counter;
            counter++;
            if (counter > 100) ergodox_right_led_1_on();
            dynamic_loop_timer = timer_read();
        }
    }
#endif

#ifdef CAPS_LOCK_STATUS
    led_t led_state = host_keyboard_led_state();
    if (led_state.caps_lock) {
        ergodox_right_led_3_on();
    } else {
        uint8_t layer = get_highest_layer(layer_state);
        if (layer != 3) {
            ergodox_right_led_3_off();
        }
    }
#endif
}

#ifdef BOOTMAGIC_ENABLE
#    include "bootmagic.h"
// Add custom check for should reset since we're not a "split keyboard" but we want bootmagic to work on both halves
__attribute__((weak)) bool bootmagic_should_reset(void) {
    uint8_t row_left = BOOTMAGIC_ROW;
    uint8_t col_left = BOOTMAGIC_COLUMN;

#    if defined(BOOTMAGIC_ROW_RIGHT) && defined(BOOTMAGIC_COLUMN_RIGHT)
    uint8_t row_right = BOOTMAGIC_ROW_RIGHT;
    uint8_t col_right = BOOTMAGIC_COLUMN_RIGHT;
#    endif

    return matrix_get_row(row_left) & (1 << col_left) || matrix_get_row(row_right) & (1 << col_right);
}
#endif
