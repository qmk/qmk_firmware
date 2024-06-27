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
#include "bootmagic.h"

keyboard_config_t keyboard_config;

__attribute__((weak)) void keyboard_post_init_sub(void) {
    setPinOutput(ERGODOX_LED_1_PIN);
    setPinOutput(ERGODOX_LED_2_PIN);
    setPinOutput(ERGODOX_LED_3_PIN);
}

void keyboard_post_init_kb(void) {
    keyboard_post_init_sub();
#ifdef ERGODOX_LED_SHUTOFF_PIN
    setPinOutput(ERGODOX_LED_SHUTOFF_PIN);
#endif

    keyboard_config.raw = eeconfig_read_kb();
    ergodox_led_all_set((uint8_t)keyboard_config.led_level * 255 / 4);
    ergodox_blink_all_leds();

    keyboard_post_init_user();
}

void ergodox_board_led_on(void) {
#ifdef ERGODOX_LED_SHUTOFF_PIN
    writePinHigh(ERGODOX_LED_SHUTOFF_PIN);
#endif
}

__attribute__((weak)) void ergodox_right_led_1_on(void) {
    writePinHigh(ERGODOX_LED_1_PIN);
}

__attribute__((weak)) void ergodox_right_led_2_on(void) {
    writePinHigh(ERGODOX_LED_2_PIN);
}

__attribute__((weak)) void ergodox_right_led_3_on(void) {
    writePinHigh(ERGODOX_LED_3_PIN);
}

void ergodox_board_led_off(void) {
#ifdef ERGODOX_LED_SHUTOFF_PIN
    writePinLow(ERGODOX_LED_SHUTOFF_PIN);
#else
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
#endif
}

__attribute__((weak)) void ergodox_right_led_1_off(void) {
    setPinInput(ERGODOX_LED_1_PIN);
}

__attribute__((weak)) void ergodox_right_led_2_off(void) {
    setPinInput(ERGODOX_LED_2_PIN);
}

__attribute__((weak)) void ergodox_right_led_3_off(void) {
    setPinInput(ERGODOX_LED_3_PIN);
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

#ifdef RGB_MATRIX_ENABLE
// clang-format off
__attribute__((weak)) const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/*   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C2_3,  C1_3,  C3_3}, // LED1 on right
    {0, C2_4,  C1_4,  C3_4}, // LED2
    {0, C2_5,  C1_5,  C3_5}, // LED3
    {0, C2_6,  C1_6,  C3_6}, // LED4
    {0, C2_7,  C1_7,  C3_7}, // LED5
    {0, C2_8,  C1_8,  C3_8}, // LED6
    {0, C8_1,  C7_1,  C9_1}, // LED7
    {0, C8_2,  C7_2,  C9_2}, // LED8
    {0, C8_3,  C7_3,  C9_3}, // LED9
    {0, C8_4,  C7_4,  C9_4}, // LED10
    {0, C8_5,  C7_5,  C9_5}, // LED11
    {0, C8_6,  C7_6,  C9_6}, // LED12
    {0, C2_11, C1_11, C3_11}, // LED13
    {0, C2_12, C1_12, C3_12}, // LED14
    {0, C2_13, C1_13, C3_13}, // LED15
    {0, C2_14, C1_14, C3_14}, // LED16
    {0, C2_15, C1_15, C3_15}, // LED17
    {0, C2_16, C1_16, C3_16}, // LED18

    {0, C8_9,  C7_9,  C9_9}, // LED19
    {0, C8_10, C7_10, C9_10}, // LED20
    {0, C8_11, C7_11, C9_11}, // LED21
    {0, C8_12, C7_12, C9_12}, // LED22
    {0, C8_13, C7_13, C9_13}, // LED23
    {0, C8_14, C7_14, C9_14}, // LED24

    {1, C3_1,  C2_1,  C4_1}, // LED1 on left
    {1, C6_1,  C5_1,  C7_1}, // LED2
    {1, C4_2,  C3_2,  C5_2}, // LED3
    {1, C7_2,  C6_2,  C8_2}, // LED4
    {1, C2_3,  C1_3,  C3_3}, // LED5
    {1, C5_3,  C4_3,  C6_3}, // LED6
    {1, C8_3,  C7_3,  C9_3}, // LED7
    {1, C2_4,  C1_4,  C3_4}, // LED8
    {1, C6_4,  C5_4,  C7_4}, // LED9
    {1, C2_5,  C1_5,  C3_5}, // LED10
    {1, C7_5,  C6_5,  C8_5}, // LED11
    {1, C2_6,  C1_6,  C3_6}, // LED12
    {1, C5_6,  C4_6,  C6_6}, // LED13
    {1, C8_6,  C7_6,  C9_6}, // LED14
    {1, C2_7,  C1_7,  C3_7}, // LED15
    {1, C5_7,  C4_7,  C6_7}, // LED16
    {1, C2_8,  C1_8,  C3_8}, // LED17
    {1, C5_8,  C4_8,  C6_8}, // LED18

    {1, C3_9,  C2_9,  C4_9}, // LED19
    {1, C6_9,  C5_9,  C7_9}, // LED20
    {1, C4_10, C3_10, C5_10}, // LED21
    {1, C7_10, C6_10, C8_10}, // LED22
    {1, C2_11, C1_11, C3_11}, // LED23
    {1, C5_11, C4_11, C6_11} // LED24
};
// clang-format on

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef ORYX_CONFIGURATOR
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
#    ifdef RGB_MATRIX_ENABLE
        case TOGGLE_LAYER_COLOR:
            if (record->event.pressed) {
                keyboard_config.disable_layer_led ^= 1;
                if (keyboard_config.disable_layer_led) rgb_matrix_set_color_all(0, 0, 0);
                eeconfig_update_kb(keyboard_config.raw);
            }
            break;
        case RGB_TOG:
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
#    endif
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

#ifdef BOOTMAGIC_LITE
__attribute__((weak)) void bootmagic_lite(void) {
    // We need multiple scans because debouncing can't be turned off.
    matrix_scan();
#    if defined(DEBOUNCE) && DEBOUNCE > 0
    wait_ms(DEBOUNCE * 2);
#    else
    wait_ms(30);
#    endif
    matrix_scan();

    // If the configured key (commonly Esc) is held down on power up,
    // reset the EEPROM valid state and jump to bootloader.
    // This isn't very generalized, but we need something that doesn't
    // rely on user's keymaps in firmware or EEPROM.
    uint8_t row_left = BOOTMAGIC_LITE_ROW;
    uint8_t col_left = BOOTMAGIC_LITE_COLUMN;

#    if defined(BOOTMAGIC_LITE_ROW_RIGHT) && defined(BOOTMAGIC_LITE_COLUMN_RIGHT)
    uint8_t row_right = BOOTMAGIC_LITE_ROW_RIGHT;
    uint8_t col_right = BOOTMAGIC_LITE_COLUMN_RIGHT;
#    endif

    if (matrix_get_row(row_left) & (1 << col_left) || matrix_get_row(row_right) & (1 << col_right)) {
        void bootmagic_lite_reset_eeprom(void);
        bootmagic_lite_reset_eeprom();

        // Jump to bootloader.
        reset_keyboard();
    }
}
#endif

void rgb_matrix_update_pwm_buffers(void);
