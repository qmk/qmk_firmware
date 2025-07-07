/* Copyright (C) 2025 jonylee@hfd
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

// clang-format off
#ifdef RGB_MATRIX_ENABLE
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |   R location
 *   |   |          G location
 *   |   |          |          B location
 *   |   |          |          | */
    {1, SW3_CS1,   SW2_CS1,   SW1_CS1},
    {1, SW3_CS2,   SW2_CS2,   SW1_CS2},
    {1, SW3_CS3,   SW2_CS3,   SW1_CS3},
    {1, SW3_CS4,   SW2_CS4,   SW1_CS4},
    {1, SW3_CS5,   SW2_CS5,   SW1_CS5},
    {1, SW3_CS6,   SW2_CS6,   SW1_CS6},
    {1, SW3_CS7,   SW2_CS7,   SW1_CS7},
    {1, SW3_CS8,   SW2_CS8,   SW1_CS8},
    {1, SW3_CS9,   SW2_CS9,   SW1_CS9},
    {1, SW3_CS10,  SW2_CS10,  SW1_CS10},
    {1, SW3_CS11,  SW2_CS11,  SW1_CS11},
    {1, SW3_CS12,  SW2_CS12,  SW1_CS12},
    {1, SW3_CS13,  SW2_CS13,  SW1_CS13},
    {1, SW3_CS14,  SW2_CS14,  SW1_CS14},
    {1, SW3_CS15,  SW2_CS15,  SW1_CS15},
    {1, SW3_CS16,  SW2_CS16,  SW1_CS16},

    {0, SW6_CS1,   SW5_CS1,   SW4_CS1},
    {0, SW6_CS2,   SW5_CS2,   SW4_CS2},
    {0, SW6_CS3,   SW5_CS3,   SW4_CS3},
    {0, SW6_CS4,   SW5_CS4,   SW4_CS4},
    {0, SW6_CS5,   SW5_CS5,   SW4_CS5},
    {0, SW6_CS6,   SW5_CS6,   SW4_CS6},
    {0, SW6_CS7,   SW5_CS7,   SW4_CS7},
    {0, SW6_CS8,   SW5_CS8,   SW4_CS8},
    {0, SW6_CS9,   SW5_CS9,   SW4_CS9},
    {0, SW6_CS10,  SW5_CS10,  SW4_CS10},
    {0, SW6_CS11,  SW5_CS11,  SW4_CS11},
    {0, SW6_CS12,  SW5_CS12,  SW4_CS12},
    {0, SW6_CS13,  SW5_CS13,  SW4_CS13},
    {1, SW6_CS1,   SW5_CS1,   SW4_CS1},

    {0, SW9_CS1,   SW8_CS1,   SW7_CS1},
    {0, SW9_CS2,   SW8_CS2,   SW7_CS2},
    {0, SW9_CS3,   SW8_CS3,   SW7_CS3},
    {0, SW9_CS4,   SW8_CS4,   SW7_CS4},
    {0, SW9_CS5,   SW8_CS5,   SW7_CS5},
    {0, SW9_CS6,   SW8_CS6,   SW7_CS6},
    {0, SW9_CS7,   SW8_CS7,   SW7_CS7},
    {0, SW9_CS8,   SW8_CS8,   SW7_CS8},
    {0, SW9_CS9,   SW8_CS9,   SW7_CS9},
    {0, SW9_CS10,  SW8_CS10,  SW7_CS10},
    {0, SW9_CS11,  SW8_CS11,  SW7_CS11},
    {0, SW9_CS12,  SW8_CS12,  SW7_CS12},
    {0, SW9_CS13,  SW8_CS13,  SW7_CS13},
    {1, SW6_CS5,   SW5_CS5,   SW4_CS5},
    {1, SW6_CS2,   SW5_CS2,   SW4_CS2},

    {0, SW12_CS1,  SW11_CS1,  SW10_CS1},
    {0, SW12_CS3,  SW11_CS3,  SW10_CS3},
    {0, SW12_CS4,  SW11_CS4,  SW10_CS4},
    {0, SW12_CS5,  SW11_CS5,  SW10_CS5},
    {0, SW12_CS6,  SW11_CS6,  SW10_CS6},
    {0, SW12_CS7,  SW11_CS7,  SW10_CS7},
    {0, SW12_CS8,  SW11_CS8,  SW10_CS8},
    {0, SW12_CS9,  SW11_CS9,  SW10_CS9},
    {0, SW12_CS10, SW11_CS10, SW10_CS10},
    {0, SW12_CS11, SW11_CS11, SW10_CS11},
    {0, SW12_CS12, SW11_CS12, SW10_CS12},
    {1, SW6_CS9,   SW5_CS9,   SW4_CS9},
    {1, SW6_CS8,   SW5_CS8,   SW4_CS8},
    {1, SW6_CS6,   SW5_CS6,   SW4_CS6},
    {1, SW6_CS3,   SW5_CS3,   SW4_CS3},

    {0, SW12_CS13, SW11_CS13, SW10_CS13},
    {0, SW12_CS14, SW11_CS14, SW10_CS14},
    {0, SW12_CS15, SW11_CS15, SW10_CS15},
    {0, SW12_CS16, SW11_CS16, SW10_CS16},
    {0, SW9_CS14,  SW8_CS14,  SW7_CS14},
    {0, SW9_CS15,  SW8_CS15,  SW7_CS15},
    {0, SW9_CS16,  SW8_CS16,  SW7_CS16},
    {0, SW6_CS14,  SW5_CS14,  SW4_CS14},
    {0, SW6_CS15,  SW5_CS15,  SW4_CS15},
    {0, SW6_CS16,  SW5_CS16,  SW4_CS16},
    {1, SW6_CS7,   SW5_CS7,   SW4_CS7},
    {1, SW6_CS4,   SW5_CS4,   SW4_CS4},

    {0, SW12_CS2,  SW11_CS2,  SW10_CS2},
    {1, SW4_CS10,  SW5_CS10,  SW6_CS10},
    {1, SW4_CS11,  SW5_CS11,  SW6_CS11},
};
#endif

// clang-format on
typedef union {
    uint32_t raw;
    struct {
        uint8_t rgb_mode;
    };
} keyboard_config_t;
keyboard_config_t keyboard_config;

static uint32_t long_pressed_time;
static uint16_t long_pressed_keycode;
static uint8_t  all_blink_cnt;
static uint32_t all_blink_time;
static RGB      all_blink_color;
static uint8_t  single_blink_cnt;
static uint8_t  single_blink_index;
static RGB      single_blink_color;
static uint32_t single_blink_time;
static uint8_t  EE_CLR_blink_cnt;
static RGB      EE_CLR_blink_color;
static uint32_t EE_CLR_blink_time;

// clang-format off
static uint8_t rgb_matrix_effects_table[] = {
    RGB_MATRIX_BREATHING,
    RGB_MATRIX_SOLID_COLOR,
    RGB_MATRIX_CYCLE_LEFT_RIGHT,
    RGB_MATRIX_RAINBOW_MOVING_CHEVRON,
    RGB_MATRIX_CYCLE_OUT_IN_DUAL,
    RGB_MATRIX_DUAL_BEACON,
    RGB_MATRIX_RAINBOW_BEACON,
    RGB_MATRIX_RAINDROPS,
    RGB_MATRIX_SOLID_REACTIVE,
};

#define RGB_MATRIX_EFFECTS_COUNT (sizeof(rgb_matrix_effects_table) / sizeof(rgb_matrix_effects_table[0]))

// clang-format on
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (process_record_user(keycode, record) != true) {
        return false;
    }
    switch (keycode) {
        case SW_OS1:
            if (record->event.pressed) {
                long_pressed_time    = timer_read32();
                long_pressed_keycode = SW_OS1;
            } else {
                long_pressed_time = 0;
            }
            break;
        case NK_TOGG:
            if (record->event.pressed) {
                long_pressed_time    = timer_read32();
                long_pressed_keycode = NK_TOGG;
            } else {
                long_pressed_time = 0;
            }
            return false;
        case EE_CLR:
            if (record->event.pressed) {
                long_pressed_time    = timer_read32();
                long_pressed_keycode = EE_CLR;
            } else {
                long_pressed_time = 0;
            }
            return false;
        case RM_SPDU:
            if (record->event.pressed) {
                rgb_matrix_increase_speed();
                if (rgb_matrix_get_speed() >= 255) {
                    rgb_matrix_config.speed = 255;
                }
            }
            return false;
        case RM_SPDD:
            if (record->event.pressed) {
                rgb_matrix_decrease_speed();
                if (rgb_matrix_get_speed() <= 27) {
                    rgb_matrix_config.speed = 27;
                }
            }
            return false;
        case RM_NEXT:
            if (record->event.pressed) {
                keyboard_config.rgb_mode++;
                if (keyboard_config.rgb_mode > RGB_MATRIX_EFFECTS_COUNT) {
                    keyboard_config.rgb_mode = 0;
                }
                eeconfig_update_user(keyboard_config.raw);
                if (keyboard_config.rgb_mode == RGB_MATRIX_EFFECTS_COUNT) {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_set_color_all(0, 0, 0);
                } else {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_mode(rgb_matrix_effects_table[keyboard_config.rgb_mode]);
                }
            }
            return false;
        case QK_RGB_MATRIX_TOGGLE:
            if (record->event.pressed) {
                if (keyboard_config.rgb_mode == RGB_MATRIX_EFFECTS_COUNT) {
                    return false;
                }
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
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_enable();
            }
            return false;
        default:
            break;
    }
    return true;
}

void eeconfig_init_kb() {
    keyboard_config.raw     = 0;
    eeconfig_update_user(keyboard_config.raw);

    eeconfig_init_user();
}

void keyboard_pre_init_kb(void) {
#ifdef RGB_DRIVER_SDB_PIN
    gpio_set_pin_output_open_drain(RGB_DRIVER_SDB_PIN);
    gpio_write_pin_high(RGB_DRIVER_SDB_PIN);
#endif
    keyboard_pre_init_user();
}

void keyboard_post_init_kb() {
    keyboard_config.raw = eeconfig_read_user();
    rgb_matrix_mode(rgb_matrix_effects_table[keyboard_config.rgb_mode]);
    if (keyboard_config.rgb_mode == RGB_MATRIX_EFFECTS_COUNT) {
        rgb_matrix_set_flags(LED_FLAG_NONE);
        rgb_matrix_set_color_all(0, 0, 0);
    }
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    if ((timer_elapsed32(long_pressed_time) > 2000) && (long_pressed_time)) {
        long_pressed_time = 0;
        switch (long_pressed_keycode) {
            case SW_OS1:
                if (get_highest_layer(default_layer_state) == 0) {
                    set_single_persistent_default_layer(2);
                    keymap_config.no_gui = 0;
                    eeconfig_update_keymap(&keymap_config);
                    single_blink_time  = timer_read32();
                    single_blink_cnt   = 2;
                    single_blink_index = 73;
                    single_blink_color = (RGB){100, 100, 100};
                } else if (get_highest_layer(default_layer_state) == 2) {
                    set_single_persistent_default_layer(0);
                    single_blink_time  = timer_read32();
                    single_blink_cnt   = 2;
                    single_blink_index = 73;
                    single_blink_color = (RGB){.r = 0, .g = 0, .b = 100};
                }
                break;
            case NK_TOGG:
                keymap_config.nkro = !keymap_config.nkro;
                eeconfig_update_keymap(&keymap_config);
                single_blink_time  = timer_read32();
                single_blink_cnt   = 6;
                single_blink_index = 13;
                single_blink_color = (RGB){100, 100, 100};
                break;
            case EE_CLR:
                EE_CLR_blink_time  = timer_read32();
                EE_CLR_blink_cnt   = 6;
                EE_CLR_blink_color = (RGB){.r = 100, .g = 100, .b = 100};
                break;
            default:
                break;
        }
    }

    housekeeping_task_user();
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_indicators_advanced_user(led_min, led_max) != true) {
        return false;
    }

    if (all_blink_cnt) {
        rgb_matrix_set_color_all(0, 0, 0);
        if (timer_elapsed32(all_blink_time) > 300) {
            all_blink_time = timer_read32();
            all_blink_cnt--;
        }
        if (all_blink_cnt & 0x1) {
            rgb_matrix_set_color_all(all_blink_color.r, all_blink_color.g, all_blink_color.b);
        }
    }

    if (single_blink_cnt) {
        if (timer_elapsed32(single_blink_time) > 300) {
            single_blink_time = timer_read32();
            single_blink_cnt--;
        }
        if (single_blink_cnt % 2) {
            rgb_matrix_set_color(single_blink_index, single_blink_color.r, single_blink_color.g, single_blink_color.b);
        } else {
            rgb_matrix_set_color(single_blink_index, 0, 0, 0);
        }
    }

    if (EE_CLR_blink_cnt) {
        if (EE_CLR_blink_cnt % 2) {
            rgb_matrix_set_color(73, EE_CLR_blink_color.r, EE_CLR_blink_color.g, EE_CLR_blink_color.b);
            rgb_matrix_set_color(74, EE_CLR_blink_color.r, EE_CLR_blink_color.g, EE_CLR_blink_color.b);
        } else {
            rgb_matrix_set_color(73, 0, 0, 0);
            rgb_matrix_set_color(74, 0, 0, 0);
        }
        if (timer_elapsed32(EE_CLR_blink_time) > 300) {
            if (EE_CLR_blink_cnt > 0) {
                EE_CLR_blink_time = timer_read32();
                EE_CLR_blink_cnt--;
            }
            if (!EE_CLR_blink_cnt) {
                eeconfig_init();
                eeconfig_update_rgb_matrix_default();
                keyboard_config.rgb_mode = 0;
                rgb_matrix_mode(rgb_matrix_effects_table[keyboard_config.rgb_mode]);
                rgb_matrix_config.hsv.h = 170;
                eeconfig_update_user(keyboard_config.raw);
                keymap_config.no_gui = 0;
                keymap_config.nkro   = 1;
                eeconfig_update_keymap(&keymap_config);
            }
        }
    }

    // caps lock red
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(72, 100, 100, 100);
    } else {
        rgb_matrix_set_color(72, 0, 0, 0);
    }

    // GUI lock white
    if (keymap_config.no_gui) {
        rgb_matrix_set_color(61, 100, 100, 100);
    } else {
        if (!rgb_matrix_get_flags()) {
            rgb_matrix_set_color(61, 0, 0, 0);
        }
    }

    return true;
}
