#include "eeconfig.h"

#define _FN1 2
#define _FN2 3

enum colors { WHITE, RED, GREEN, BLUE };

enum colors led_color_status = WHITE;

enum mode { NONE, TEST_OR_CLEAR, LED_BLINK };

enum mode       test_clear_blink    = NONE;
static uint8_t  key_press           = 0;
static uint32_t key_count           = 0;
static bool     key_count_flag      = false;
static uint16_t current_time        = 0;
static uint16_t passed_time         = 0;
static bool     entry_led_test_flag = false;
static uint8_t  led_state           = 0;
static uint32_t led_time_buffer     = 0;
static uint8_t  time_200ms          = 0;

HSV hsv;

void led_test(uint8_t color);
void clear_eeprom(void);

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case MO(_FN1):
        case MO(_FN2):
            if (record->event.pressed) {
                key_press += 1;
                key_count += 1;
                key_count_flag = true;
            } else {
                key_press      = 0;
                key_count      = 0;
                key_count_flag = false;
            }

            return true;

        case KC_J:
        case KC_Z:
            if (key_count_flag && record->event.pressed) {
                key_count += 1;

                if (key_count == 3) {
                    key_count_flag   = false;
                    test_clear_blink = TEST_OR_CLEAR;
                    current_time     = timer_read();
                }
            } else {
                key_count = 0;
            }

            return true;

        case KC_RGHT:
            if (record->event.pressed) {
                if (key_count_flag) {
                    key_press += 1;

                    if (key_press == 3) {
                        key_count_flag   = false;
                        led_state        = rgb_matrix_get_mode();
                        hsv              = rgb_matrix_get_hsv();
                        test_clear_blink = TEST_OR_CLEAR;
                        current_time     = timer_read();
                    }
                }

                if (entry_led_test_flag) {
                    led_color_status += 1;

                    if (led_color_status > 3) {
                        led_color_status = WHITE;
                    }

                    led_test(led_color_status);
                }
            } else {
                key_press = 0;
            }

            return true;

        case KC_HOME:
            if (record->event.pressed) {
                if (key_count_flag) {
                    key_press += 1;

                    if (key_press == 3) {
                        key_count_flag   = false;
                        led_state        = rgb_matrix_get_mode();
                        hsv              = rgb_matrix_get_hsv();
                        test_clear_blink = TEST_OR_CLEAR;
                        current_time     = timer_read();
                    }
                }

                if (entry_led_test_flag) {
                    entry_led_test_flag = false;
                    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
                    rgb_matrix_mode_noeeprom(led_state);
                }
            } else {
                key_press = 0;
            }

            return true;

        default:
            // return true;
            return process_record_user(keycode, record);
    }
}

void matrix_scan_kb(void) {
    switch (test_clear_blink) {
        case TEST_OR_CLEAR:
            passed_time = timer_elapsed(current_time);

            if (passed_time >= 3000) {
                test_clear_blink = NONE;

                if (key_press == 3) {
                    led_test(led_color_status);
                } else if (key_count == 3) {
                    clear_eeprom();
                }
            }

            break;

        case LED_BLINK:
            if ((timer_elapsed(led_time_buffer)) >= 300) {
                led_time_buffer = timer_read();

                if (time_200ms++ % 2 == 0) {
                    rgb_matrix_sethsv_noeeprom(HSV_RED);
                } else {
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                }

                if (time_200ms >= 7) {
                    time_200ms          = 0;
                    test_clear_blink    = NONE;
                    entry_led_test_flag = false;
                    rgb_matrix_init();
                }
            }

            break;

        default:
            break;
    }
    matrix_scan_user();
}

void led_test(uint8_t color) {
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

void clear_eeprom(void) {
    layer_state_t default_layer_tmp = default_layer_state;
    eeconfig_init();
    default_layer_set(default_layer_tmp);

#ifdef VIA_ENABLE
    // This resets the layout options
    via_set_layout_options(VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT);

    // This resets the keymaps in EEPROM to what is in flash.
    dynamic_keymap_reset();

    // This resets the macros in EEPROM to nothing.
    dynamic_keymap_macro_reset();
#endif
    rgb_matrix_enable_noeeprom();
    led_time_buffer  = timer_read();
    test_clear_blink = LED_BLINK;
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

void restart_usb_driver(USBDriver *usbp) {
}

