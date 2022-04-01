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

#define MAC_FN 1
#define WIN_FN 3

enum {
    WHITE,
    RED,
    GREEN,
    BLUE
}led_color_status;

enum {
    NONE,
    TEST_OR_CLEAR,
    LED_BLINK
}test_clear_blink;

enum {
    FACTORY_TEST_CMD_BACKLIGHT = 0x01,
    FACTORY_TEST_CMD_OS_SWITCH,
    FACTORY_TEST_CMD_JUMP_TO_BL,
};

enum {
    OS_SWITCH = 0x01,
};

static uint16_t current_time        = 0;
static uint16_t passed_time         = 0;
static bool     entry_led_test_flag = false;
static uint8_t  led_state           = 0;
static uint32_t led_blink_buffer    = 0;
static uint8_t  led_blink_count     = 0;
uint16_t        key_press_status    = 0;
bool            report_os_sw_state  = false;

#define KEY_PRESS_FN (0x1 << 0)
#define KEY_PRESS_J (0x1 << 1)
#define KEY_PRESS_Z (0x1 << 2)
#define KEY_PRESS_RIGHT (0x1 << 3)
#define KEY_PRESS_HOME (0x1 << 4)
#define KEY_PRESS_FACTORY_RESET (KEY_PRESS_FN | KEY_PRESS_J | KEY_PRESS_Z)
#define KEY_PRESS_LED_TEST (KEY_PRESS_FN | KEY_PRESS_RIGHT | KEY_PRESS_HOME)

HSV hsv;

static void led_test(uint8_t color);
static void  clear_eeprom(void);

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO(MAC_FN):
        case MO(WIN_FN):
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_FN;
            } else {
                key_press_status &= ~KEY_PRESS_FN;
            }
            return true;  // Process all other keycodes normally
        case KC_J:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_J;
                if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    current_time = timer_read();
                    test_clear_blink = TEST_OR_CLEAR;
                }
            } else {
                key_press_status &= ~KEY_PRESS_J;
            }
            return true;  // Process all other keycodes normally
        case KC_Z:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_Z;
                if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    current_time     = timer_read();
                    test_clear_blink = TEST_OR_CLEAR;
                }
            } else {
                key_press_status &= ~KEY_PRESS_Z;
            }
            return true;  // Process all other keycodes normally
        case KC_RGHT:
            if (record->event.pressed) {
                    key_press_status |= KEY_PRESS_RIGHT;
                    if (key_press_status == KEY_PRESS_LED_TEST) {
                        led_state        = rgb_matrix_get_mode();
                        hsv              = rgb_matrix_get_hsv();
                        test_clear_blink = TEST_OR_CLEAR;
                        current_time     = timer_read();
                    }
                    if (entry_led_test_flag) {
                        led_color_status += 1;
                        if (led_color_status > 3) {
                            led_color_status = WHITE;
                        }
                        led_test(led_color_status);
                    }
            } else {
                key_press_status &= ~KEY_PRESS_RIGHT;
            }
            return true;  // Process all other keycodes normally
        case KC_HOME:
            if (record->event.pressed) {
                key_press_status |= KEY_PRESS_HOME;
                if (key_press_status == KEY_PRESS_LED_TEST) {
                    led_state        = rgb_matrix_get_mode();
                    hsv              = rgb_matrix_get_hsv();
                    test_clear_blink = TEST_OR_CLEAR;
                    current_time     = timer_read();
                }
                if (entry_led_test_flag) {
                    entry_led_test_flag = false;
                    led_color_status    = 0;
                    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
                    rgb_matrix_mode_noeeprom(led_state);
                }
            } else {
                key_press_status &= ~KEY_PRESS_HOME;
            }
            return true;  // Process all other keycodes normally
        default:
            return process_record_user(keycode, record);
    }
}

void matrix_scan_kb(void) {
    switch (test_clear_blink) {
        case TEST_OR_CLEAR:
            passed_time = timer_elapsed(current_time);
            if (passed_time >= 3000) {
                test_clear_blink = NONE;
                if (key_press_status == KEY_PRESS_LED_TEST) {
                    led_test(led_color_status);
                } else if (key_press_status == KEY_PRESS_FACTORY_RESET) {
                    clear_eeprom();
                }
            }
            break;
        case LED_BLINK:
            if ((timer_elapsed(led_blink_buffer)) >= 300) {
                led_blink_buffer = timer_read();
                if (led_blink_count++ % 2 == 0) {
                    rgb_matrix_sethsv_noeeprom(HSV_RED);
                } else {
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                }
                if (led_blink_count >= 7) {
                    led_blink_count     = 0;
                    test_clear_blink    = NONE;
                    entry_led_test_flag = false;
                    led_color_status    = 0;
                    rgb_matrix_init();
                }
            }
            break;
        default:
            break;
    }
    matrix_scan_user();
}

static void led_test(uint8_t color) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    entry_led_test_flag = true;

    switch (color) {
        case WHITE:
            rgb_matrix_sethsv_noeeprom(HSV_WHITE);
            break;
        case RED:
            rgb_matrix_sethsv_noeeprom(HSV_RED);
            break;
        case GREEN:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            break;
        case BLUE:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            break;
    }
}

static void clear_eeprom(void) {
    layer_state_t default_layer_temp = default_layer_state;
    eeconfig_init();
    default_layer_set(default_layer_temp);
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
#endif
    led_blink_buffer  = timer_read();
    test_clear_blink = LED_BLINK;
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

#ifdef RAW_ENABLE

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    if ( data[0] == 0xAB ) {
        uint16_t checksum = 0;
        for (uint8_t i  = 1; i < RAW_EPSIZE-3; i++) {
            checksum += data[i];
        }
        /* Verify checksum */
        if ((checksum & 0xFF) != data[RAW_EPSIZE-2] || checksum >> 8 != data[RAW_EPSIZE-1]) {
            return;
        }
        switch (data[1]) {
            case FACTORY_TEST_CMD_BACKLIGHT:
                if (data[2]) {
                    led_color_status = data[2] - 1;
                    led_test(led_color_status);
                }
                break;
            case FACTORY_TEST_CMD_OS_SWITCH:
                report_os_sw_state = data[2];
                if (report_os_sw_state) {
                    // dip_switch_read(true);
                }
                break;
            case FACTORY_TEST_CMD_JUMP_TO_BL:
                if (memcmp(&data[2], "JumpToBootloader", strlen("JumpToBootloader")) == 0)
                    bootloader_jump();
                break;
        }
   }
}

static void factory_test_send(uint8_t *payload, uint8_t length) {
    uint16_t checksum = 0;
    uint8_t data[RAW_EPSIZE] = {0};
    uint8_t i = 0;
    data[i++] = 0xAB;
    memcpy(&data[i], payload, length);
    i += length;
    for (uint8_t i=1; i<RAW_EPSIZE-3; i++ ) {
        checksum += data[i];
    }
    data[RAW_EPSIZE-2] = checksum & 0xFF;
    data[RAW_EPSIZE-1] = (checksum >> 8) & 0xFF;
    raw_hid_send(data, RAW_EPSIZE);
}

void system_switch_state_report(uint8_t index, bool active) {
    if (report_os_sw_state) {
        uint8_t payload[3] = {FACTORY_TEST_CMD_OS_SWITCH, OS_SWITCH, active};
        factory_test_send(payload, 3);
    }
}

#endif

#if defined(KEYBOARD_keychron_q1_q1_ansi_atmega32u4)
#elif defined(KEYBOARD_keychron_q1_q1_ansi_atmega32u4_ec11)
#elif defined(KEYBOARD_keychron_q1_q1_iso_atmega32u4)
#elif defined(KEYBOARD_keychron_q1_q1_iso_atmega32u4_ec11)
    //There is nothing to do
#else
    /* To solve the problem that keyboard can not wakeup the host */
    void restart_usb_driver(USBDriver *usbp) {
        // Do nothing here.
    }
#endif
