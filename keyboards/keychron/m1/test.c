/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

#include "test.h"

#define _FN1 1

static void timer_3000ms_task(void);
static void timer_250ms_task(void);

#define KEY_PRESS_FN    (0x1<<0)
#define KEY_PRESS_J     (0x1<<1)
#define KEY_PRESS_Z     (0x1<<2)
#define KEY_PRESS_RIGHT (0x1<<3)
#define KEY_PRESS_HOME  (0x1<<4)
#define KEY_PRESS_FACTORY_RESET (KEY_PRESS_FN | KEY_PRESS_J | KEY_PRESS_Z)
#define KEY_PRESS_LED_TEST (KEY_PRESS_FN | KEY_PRESS_RIGHT | KEY_PRESS_HOME)

enum {
    LED_TEST_MODE_OFF,
    LED_TEST_MODE_WHITE,
    LED_TEST_MODE_RED,
    LED_TEST_MODE_GREEN,
    LED_TEST_MODE_BLUE,
    LED_TEST_MODE_MAX
}led_test_mode;

enum {
    FACTORY_TEST_CMD_BACKLIGHT = 0x01,
    FACTORY_TEST_CMD_OS_SWITCH,
    FACTORY_TEST_CMD_JUMP_TO_BL,
};

enum {
    OS_SWITCH = 0x01,
};

uint16_t key_press_status = 0;
uint32_t timer_3000ms_buffer = 0;
uint32_t timer_250ms_buffer1 = 0;
uint8_t factory_reset_count1 = 0;
bool report_os_sw_state = false;

void process_other_record(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_BTN1:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_FN;
            } else {
                key_press_status &= ~KEY_PRESS_FN;
                timer_3000ms_buffer = 0;
            }
            break;
        case KC_BTN2:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_J;
                if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    timer_3000ms_buffer = sync_timer_read32() | 1;
                }
            } else {
                key_press_status &= ~KEY_PRESS_J;
                timer_3000ms_buffer = 0;
            }
            break;
        case KC_BTN3:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_Z;
                if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    timer_3000ms_buffer = sync_timer_read32() | 1;
                }
            } else {
                key_press_status &= ~KEY_PRESS_Z;
                timer_3000ms_buffer = 0;
            }
            break;
        case KC_MPLY:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_RIGHT;
                if (led_test_mode) {
                    if (++led_test_mode >= LED_TEST_MODE_MAX) {
                        led_test_mode = LED_TEST_MODE_WHITE;
                    }
                } else if (key_press_status == KEY_PRESS_LED_TEST) {
                    timer_3000ms_buffer = sync_timer_read32() | 1;
                }
            } else {
                key_press_status &= ~KEY_PRESS_RIGHT;
                timer_3000ms_buffer = 0;
            }
            break;
        case KC_DEL:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_HOME;
                if (led_test_mode) {
                    led_test_mode = LED_TEST_MODE_OFF;
                } else if (key_press_status == KEY_PRESS_LED_TEST) {
                    timer_3000ms_buffer = sync_timer_read32() | 1;
                }
            } else {
                key_press_status &= ~KEY_PRESS_HOME;
                timer_3000ms_buffer = 0;
            }
            break;
    }
}

void timer_task_start(void) {
    if (timer_3000ms_buffer) {
        timer_3000ms_task();
    } else if (timer_250ms_buffer1) {
        timer_250ms_task();
    }
}

static void timer_3000ms_task(void) {
    if (sync_timer_elapsed32(timer_3000ms_buffer) > 3000) {
        timer_3000ms_buffer = 0;
        if (key_press_status == KEY_PRESS_FACTORY_RESET) {
            timer_250ms_buffer1 = sync_timer_read32() | 1;
            factory_reset_count1++;
            layer_state_t default_layer_tmp = default_layer_state;
            eeconfig_init();
            default_layer_set(default_layer_tmp);
#ifdef LED_MATRIX_ENABLE
            if (!led_matrix_is_enabled()) led_matrix_enable();
            led_matrix_init();
#endif
#ifdef RGB_MATRIX_ENABLE
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_enable();
            }
            rgb_matrix_init();
#endif
        } else if (key_press_status == KEY_PRESS_LED_TEST) {
            led_test_mode = LED_TEST_MODE_WHITE;
#ifdef RGB_MATRIX_ENABLE
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_enable();
            }
#endif
        }
        key_press_status = 0;
    }
}

static void timer_250ms_task(void) {
    if (timer_250ms_buffer1 && sync_timer_elapsed32(timer_250ms_buffer1) > 250) {
        if (factory_reset_count1++ > 6) {
            timer_250ms_buffer1 = 0;
            factory_reset_count1 = 0;
        } else {
            timer_250ms_buffer1 = sync_timer_read32() | 1;
        }
    }
}

#if LED_MATRIX_ENABLE

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (factory_reset_count1) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            led_matrix_set_value(i, factory_reset_count1 % 2 ? 0 : UINT8_MAX);
        }
    }
}

#endif

#if RGB_MATRIX_ENABLE

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (factory_reset_count1) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            rgb_matrix_set_color(i, factory_reset_count1 % 2 ? 0 : RGB_RED);
        }
    } else if (led_test_mode) {
        switch (led_test_mode) {
            case LED_TEST_MODE_WHITE:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_WHITE);
                }
                break;
            case LED_TEST_MODE_RED:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_RED);
                }
                break;
            case LED_TEST_MODE_GREEN:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_GREEN);
                }
                break;
            case LED_TEST_MODE_BLUE:
                for (uint8_t i = led_min; i <= led_max; i++) {
                    rgb_matrix_set_color(i, RGB_BLUE);
                }
                break;
            default:
                break;
        }
    }
}

#endif

/* To solve the problem that keyboard can not wakeup the host */
void restart_usb_driver(USBDriver *usbp) {
    // Do nothing here.
}
