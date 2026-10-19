/* Copyright (C) 2024 koosikus
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

#ifdef WIRELESS_ENABLE
#    include "wireless.h"
#endif
#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |     R location
 *   |     |          G location
 *   |     |          |          B location
 *   |     |          |          | */
    {1, CB1_CA1,   CB2_CA1,   CB3_CA1},
    {1, CB1_CA2,   CB2_CA2,   CB3_CA2},
    {1, CB1_CA3,   CB2_CA3,   CB3_CA3},
    {1, CB1_CA4,   CB2_CA4,   CB3_CA4},
    {1, CB1_CA5,   CB2_CA5,   CB3_CA5},
    {1, CB1_CA6,   CB2_CA6,   CB3_CA6},
    {1, CB1_CA7,   CB2_CA7,   CB3_CA7},
    {1, CB1_CA8,   CB2_CA8,   CB3_CA8},
    {1, CB1_CA9,   CB2_CA9,   CB3_CA9},
    {1, CB1_CA10,  CB2_CA10,  CB3_CA10},
    {1, CB1_CA11,  CB2_CA11,  CB3_CA11},
    {1, CB1_CA12,  CB2_CA12,  CB3_CA12},
    {1, CB1_CA13,  CB2_CA13,  CB3_CA13},
    {1, CB1_CA14,  CB2_CA14,  CB3_CA14},
    {1, CB1_CA15,  CB2_CA15,  CB3_CA15},
    {1, CB1_CA16,  CB2_CA16,  CB3_CA16},

    {0, CB1_CA1,   CB2_CA1,   CB3_CA1},
    {0, CB1_CA2,   CB2_CA2,   CB3_CA2},
    {0, CB1_CA3,   CB2_CA3,   CB3_CA3},
    {0, CB1_CA4,   CB2_CA4,   CB3_CA4},
    {0, CB1_CA5,   CB2_CA5,   CB3_CA5},
    {0, CB1_CA6,   CB2_CA6,   CB3_CA6},
    {0, CB1_CA7,   CB2_CA7,   CB3_CA7},
    {0, CB1_CA8,   CB2_CA8,   CB3_CA8},
    {0, CB1_CA9,   CB2_CA9,   CB3_CA9},
    {0, CB1_CA10,  CB2_CA10,  CB3_CA10},
    {0, CB1_CA11,  CB2_CA11,  CB3_CA11},
    {0, CB1_CA12,  CB2_CA12,  CB3_CA12},
    {0, CB1_CA13,  CB2_CA13,  CB3_CA13},
    {0, CB1_CA14,  CB2_CA14,  CB3_CA14},
    {1, CB4_CA1,   CB5_CA1,   CB6_CA1},
    {1, CB4_CA3,   CB5_CA3,   CB6_CA3},
    {1, CB4_CA5,   CB5_CA5,   CB6_CA5},

    {0, CB4_CA1,   CB5_CA1,   CB6_CA1},
    {0, CB4_CA2,   CB5_CA2,   CB6_CA2},
    {0, CB4_CA3,   CB5_CA3,   CB6_CA3},
    {0, CB4_CA4,   CB5_CA4,   CB6_CA4},
    {0, CB4_CA5,   CB5_CA5,   CB6_CA5},
    {0, CB4_CA6,   CB5_CA6,   CB6_CA6},
    {0, CB4_CA7,   CB5_CA7,   CB6_CA7},
    {0, CB4_CA8,   CB5_CA8,   CB6_CA8},
    {0, CB4_CA9,   CB5_CA9,   CB6_CA9},
    {0, CB4_CA10,  CB5_CA10,  CB6_CA10},
    {0, CB4_CA11,  CB5_CA11,  CB6_CA11},
    {0, CB4_CA12,  CB5_CA12,  CB6_CA12},
    {0, CB4_CA13,  CB5_CA13,  CB6_CA13},
    {0, CB4_CA14,  CB5_CA14,  CB6_CA14},
    {1, CB4_CA2,   CB5_CA2,   CB6_CA2},
    {1, CB4_CA4,   CB5_CA4,   CB6_CA4},
    {1, CB4_CA6,   CB5_CA6,   CB6_CA6},

    {0, CB7_CA1,   CB8_CA1,   CB9_CA1},
    {0, CB7_CA2,   CB8_CA2,   CB9_CA2},
    {0, CB7_CA3,   CB8_CA3,   CB9_CA3},
    {0, CB7_CA4,   CB8_CA4,   CB9_CA4},
    {0, CB7_CA5,   CB8_CA5,   CB9_CA5},
    {0, CB7_CA6,   CB8_CA6,   CB9_CA6},
    {0, CB7_CA7,   CB8_CA7,   CB9_CA7},
    {0, CB7_CA8,   CB8_CA8,   CB9_CA8},
    {0, CB7_CA9,   CB8_CA9,   CB9_CA9},
    {0, CB7_CA10,  CB8_CA10,  CB9_CA10},
    {0, CB7_CA11,  CB8_CA11,  CB9_CA11},
    {0, CB7_CA12,  CB8_CA12,  CB9_CA12},
    {0, CB1_CA15,  CB2_CA15,  CB3_CA15},
    {0, CB7_CA13,  CB8_CA13,  CB9_CA13},

    {0, CB10_CA1,   CB11_CA1,   CB12_CA1},
    {0, CB1_CA16,  CB2_CA16,  CB3_CA16},
    {0, CB10_CA2,   CB11_CA2,   CB12_CA2},
    {0, CB10_CA3,   CB11_CA3,   CB12_CA3},
    {0, CB10_CA4,   CB11_CA4,   CB12_CA4},
    {0, CB10_CA5,   CB11_CA5,   CB12_CA5},
    {0, CB10_CA6,   CB11_CA6,   CB12_CA6},
    {0, CB10_CA7,   CB11_CA7,   CB12_CA7},
    {0, CB10_CA8,   CB11_CA8,   CB12_CA8},
    {0, CB10_CA9,   CB11_CA9,   CB12_CA9},
    {0, CB10_CA10,  CB11_CA10,  CB12_CA10},
    {0, CB10_CA11,  CB11_CA11,  CB12_CA11},
    {0, CB10_CA12,  CB11_CA12,  CB12_CA12},
    {1, CB4_CA9,   CB5_CA9,   CB6_CA9},

    {0, CB10_CA13,  CB11_CA13,  CB12_CA13},
    {0, CB10_CA14,  CB11_CA14,  CB12_CA14},
    {0, CB10_CA15,  CB11_CA15,  CB12_CA15},
    {0, CB10_CA16,  CB11_CA16,  CB12_CA16},

    {0, CB7_CA14,  CB8_CA14,  CB9_CA14},
    {0, CB7_CA15,  CB8_CA15,  CB9_CA15},
    {0, CB7_CA16,  CB8_CA16,  CB9_CA16},
    {0, CB4_CA16,  CB5_CA16,  CB6_CA16},

    {0, CB4_CA15,  CB5_CA15,  CB6_CA15},
    {1, CB4_CA8,   CB5_CA8,   CB6_CA8},
    {1, CB4_CA7,   CB5_CA7,   CB6_CA7},

    {1, CB4_CA10,   CB5_CA10,   CB6_CA10},
    {1, CB4_CA11,   CB5_CA11,   CB6_CA11},
};
#endif

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1;
        uint8_t devs : 3;
        uint8_t BTdevs : 3;
    };
} confinfo_t;
confinfo_t confinfo;

uint32_t post_init_timer = 0x00;

void eeconfig_confinfo_update(uint32_t raw) {

    eeconfig_update_kb(raw);
}

uint32_t eeconfig_confinfo_read(void) {

    return eeconfig_read_kb();
}

void eeconfig_confinfo_default(void) {

    confinfo.flag = true;
#ifdef WIRELESS_ENABLE
    confinfo.devs = DEVS_USB;
    confinfo.BTdevs = DEVS_BT1;
#endif

    eeconfig_confinfo_update(confinfo.raw);
}

void eeconfig_confinfo_init(void) {

    confinfo.raw = eeconfig_confinfo_read();
    if (!confinfo.raw) {
        eeconfig_confinfo_default();
    }
}
static void bt_scan_mode(void) {
#ifdef BT_MODE_SW_PIN
    if (readPin(RF_MODE_SW_PIN) && !readPin(BT_MODE_SW_PIN)) {
        if ((wireless_get_current_devs() == DEVS_USB) || (wireless_get_current_devs() == DEVS_2G4)) {
            wireless_devs_change(wireless_get_current_devs(), confinfo.BTdevs, false);
        }
    }
    if (readPin(BT_MODE_SW_PIN) && !readPin(RF_MODE_SW_PIN)) {
        if (wireless_get_current_devs() != DEVS_2G4) {
            wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, false); // 2_CA4G mode

        }
    }
    if (readPin(BT_MODE_SW_PIN) && readPin(RF_MODE_SW_PIN)) {
        if (wireless_get_current_devs() != DEVS_USB) wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false); // usb mode
    }
#endif
}

void keyboard_post_init_kb(void) {

#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif

    eeconfig_confinfo_init();

#ifdef LED_POWER_EN_PIN
    gpio_set_pin_output(LED_POWER_EN_PIN);
    gpio_write_pin_high(LED_POWER_EN_PIN);
#endif
#ifdef LED_SCROLL_LOCK_PIN_G
    gpio_set_pin_output(LED_SCROLL_LOCK_PIN_G);
    gpio_set_pin_output(LED_SCROLL_LOCK_PIN_B);
    gpio_set_pin_output(LED_SCROLL_LOCK_PIN_R);
    gpio_write_pin_high(LED_SCROLL_LOCK_PIN_G);
    gpio_write_pin_high(LED_SCROLL_LOCK_PIN_B);
    gpio_write_pin_high(LED_SCROLL_LOCK_PIN_R);
#endif

#ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
    gpio_set_pin_output(USB_POWER_EN_PIN);
#endif
#ifdef BT_MODE_SW_PIN
    gpio_set_pin_input_high(BT_MODE_SW_PIN);
    gpio_set_pin_input_high(RF_MODE_SW_PIN);
#endif
#ifdef BT_CABLE_PIN
    gpio_set_pin_input(BT_CABLE_PIN);
    gpio_set_pin_input(BT_CHARGE_PIN);
#endif

#ifdef WIRELESS_ENABLE
    wireless_init();
    wireless_devs_change(!confinfo.devs, confinfo.devs, false);
    post_init_timer = timer_read32();
#endif

    keyboard_post_init_user();
}

#ifdef WIRELESS_ENABLE


void usb_power_connect(void) {

#    ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
#    endif
}

void usb_power_disconnect(void) {

#    ifdef USB_POWER_EN_PIN
    gpio_write_pin_high(USB_POWER_EN_PIN);
#    endif
}

void suspend_power_down_kb(void) {

#    ifdef LED_POWER_EN_PIN
    gpio_write_pin_low(LED_POWER_EN_PIN);
#    endif
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {

#    ifdef LED_POWER_EN_PIN
    gpio_write_pin_high(LED_POWER_EN_PIN);
#    endif

    wireless_devs_change(wireless_get_current_devs(), wireless_get_current_devs(), false);
    suspend_wakeup_init_user();
}
void matrix_scan_kb(void) {
#ifdef LED_SCROLL_LOCK_PIN_G
    gpio_write_pin(LED_SCROLL_LOCK_PIN_G, !host_keyboard_led_state().scroll_lock);
    gpio_write_pin(LED_SCROLL_LOCK_PIN_B, !host_keyboard_led_state().scroll_lock);
    gpio_write_pin(LED_SCROLL_LOCK_PIN_R, !host_keyboard_led_state().scroll_lock);
#endif
    bt_scan_mode();
    matrix_scan_user();
}
void wireless_post_task(void) {

    // auto switching devs
    if (post_init_timer && timer_elapsed32(post_init_timer) >= 100) {
        md_send_devctrl(MD_SND_CMD_DEVCTRL_FW_VERSION);   // get the module fw version.
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_EN);  // timeout 30min to sleep in bt mode, enable
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_2G4_EN); // timeout 30min to sleep in 2.4g mode, enable
        wireless_devs_change(!confinfo.devs, confinfo.devs, false);
        post_init_timer = 0x00;
    }
}

uint32_t wls_process_long_press(uint32_t trigger_time, void *cb_arg) {
    uint16_t keycode = *((uint16_t *)cb_arg);

    switch (keycode) {
        case KC_BT1: {
            if(wireless_get_current_devs() == DEVS_BT1)
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT1, true);
        } break;
        case KC_BT2: {
            if(wireless_get_current_devs() == DEVS_BT2)
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, true);
        } break;
        case KC_BT3: {
            if(wireless_get_current_devs() == DEVS_BT3)
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT3, true);
        } break;
        case KC_2G4: {
            if(wireless_get_current_devs() == DEVS_2G4)
                wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, true);
        } break;
        default:
            break;
    }

    return 0;
}

bool process_record_wls(uint16_t keycode, keyrecord_t *record) {
    static uint16_t keycode_shadow                     = 0x00;
    static deferred_token wls_process_long_press_token = INVALID_DEFERRED_TOKEN;

    keycode_shadow = keycode;

#    ifndef WLS_KEYCODE_PAIR_TIME
#        define WLS_KEYCODE_PAIR_TIME 3000
#    endif

#    define WLS_KEYCODE_EXEC(wls_dev)                                                                                          \
        do {                                                                                                                   \
            if (record->event.pressed) {                                                                                       \
                wireless_devs_change(wireless_get_current_devs(), wls_dev, false);                                             \
                if (wls_process_long_press_token == INVALID_DEFERRED_TOKEN) {                                                  \
                    wls_process_long_press_token = defer_exec(WLS_KEYCODE_PAIR_TIME, wls_process_long_press, &keycode_shadow); \
                }                                                                                                              \
            } else {                                                                                                           \
                cancel_deferred_exec(wls_process_long_press_token);                                                            \
                wls_process_long_press_token = INVALID_DEFERRED_TOKEN;                                                         \
            }                                                                                                                  \
        } while (false)

    switch (keycode) {
        case KC_BT1: {
            if ((wireless_get_current_devs() != DEVS_USB) && (wireless_get_current_devs() != DEVS_2G4)) {
                WLS_KEYCODE_EXEC(DEVS_BT1);
            }
        } break;
        case KC_BT2: {
            if ((wireless_get_current_devs() != DEVS_USB) && (wireless_get_current_devs() != DEVS_2G4)) {
                WLS_KEYCODE_EXEC(DEVS_BT2);
            }
        } break;
        case KC_BT3: {
            if ((wireless_get_current_devs() != DEVS_USB) && (wireless_get_current_devs() != DEVS_2G4)) {
                WLS_KEYCODE_EXEC(DEVS_BT3);
            }
        } break;
        case KC_2G4: {
            if (wireless_get_current_devs() == DEVS_2G4) {
                WLS_KEYCODE_EXEC(DEVS_2G4);
            }
        } break;
        case KC_USB: {
            if (record->event.pressed) {
                // wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);
            }
        } break;
        default:
            return true;
    }

    return false;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if (process_record_user(keycode, record) != true) {
        return false;
    }

#ifdef WIRELESS_ENABLE
    if (process_record_wls(keycode, record) != true) {
        return false;
    }
#endif

    switch (keycode) {
        default:
            return true;
    }

    return false;
}

#ifdef RGB_MATRIX_ENABLE

#    ifdef WIRELESS_ENABLE
bool wls_rgb_indicator_reset        = false;
uint32_t wls_rgb_indicator_timer    = 0x00;
uint32_t wls_rgb_indicator_interval = 0;
uint32_t wls_rgb_indicator_times    = 0;
uint32_t wls_rgb_indicator_index    = 0;
RGB wls_rgb_indicator_rgb           = {0};

void rgb_matrix_wls_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times) {

    wls_rgb_indicator_timer = timer_read32();

    wls_rgb_indicator_index    = index;
    wls_rgb_indicator_interval = interval;
    wls_rgb_indicator_times    = times * 2;
    wls_rgb_indicator_rgb      = rgb;
}

void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset) {

    wls_rgb_indicator_reset = reset;

    if (confinfo.devs != wireless_get_current_devs()) {
        confinfo.devs = wireless_get_current_devs();
        if ((wireless_get_current_devs() != DEVS_USB) && (wireless_get_current_devs() != DEVS_2G4)) {
            confinfo.BTdevs = wireless_get_current_devs();
        }
        eeconfig_confinfo_update(confinfo.raw);
    }

    switch (new_devs) {
        case DEVS_BT1: {
            if (reset) {
                rgb_matrix_wls_indicator_set(17, (RGB){.r = 0, .g = 0, .b = 255}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(17, (RGB){.r = 0, .g = 0, .b = 255}, 500, 1);
            }
        } break;
        case DEVS_BT2: {
            if (reset) {
                rgb_matrix_wls_indicator_set(18, (RGB){.r = 0, .g = 0, .b = 255}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(18, (RGB){.r = 0, .g = 0, .b = 255}, 500, 1);
            }
        } break;
        case DEVS_BT3: {
            if (reset) {
                rgb_matrix_wls_indicator_set(19, (RGB){.r = 0, .g = 0, .b = 255}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(19, (RGB){.r = 0, .g = 0, .b = 255}, 500, 1);
            }
        } break;
        case DEVS_2G4: {
            if (reset) {
                rgb_matrix_wls_indicator_set(20, (RGB){.r = 0, .g = 255, .b = 0}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(20, (RGB){.r = 0, .g = 255, .b = 0}, 500, 1);
            }
        } break;
        default:
            break;
    }
}

bool rgb_matrix_wls_indicator_cb(void) {

    if (*md_getp_state() != MD_STATE_CONNECTED) {
        wireless_devs_change_kb(wireless_get_current_devs(), wireless_get_current_devs(), wls_rgb_indicator_reset);
        return true;
    }

    // refresh led
    led_wakeup();

    return false;
}

void rgb_matrix_wls_indicator(void) {

    if (wls_rgb_indicator_timer) {

        if (timer_elapsed32(wls_rgb_indicator_timer) >= wls_rgb_indicator_interval) {
            wls_rgb_indicator_timer = timer_read32();

            if (wls_rgb_indicator_times) {
                wls_rgb_indicator_times--;
            }

            if (wls_rgb_indicator_times <= 0) {
                wls_rgb_indicator_timer = 0x00;
                if (rgb_matrix_wls_indicator_cb() != true) {
                    return;
                }
            }
        }

        if (wls_rgb_indicator_times % 2) {
            rgb_matrix_set_color(wls_rgb_indicator_index, wls_rgb_indicator_rgb.r, wls_rgb_indicator_rgb.g, wls_rgb_indicator_rgb.b);
        } else {
            rgb_matrix_set_color(wls_rgb_indicator_index, 0x00, 0x00, 0x00);
        }
    }
}
#    endif

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {

    if (rgb_matrix_indicators_advanced_user(led_min, led_max) != true) {
        return false;
    }

#    ifdef WIRELESS_ENABLE
    rgb_matrix_wls_indicator();
#    endif
#    if defined(BT_CABLE_PIN) && defined(BT_CHARGE_PIN)
    // Charging access
    static uint16_t charging_time;
    static uint16_t full_time;
    if (readPin(BT_CABLE_PIN)) {
        if (!readPin(BT_CHARGE_PIN)) {
            // Charging
            if (timer_elapsed(charging_time) >= 500) {
                rgb_matrix_set_color(90, 100, 0, 0);
            } else {
                rgb_matrix_set_color(90, 0, 0, 0);
            }
            full_time = timer_read32();
        } else {
            // full
            charging_time = timer_read32();
            if (timer_elapsed(full_time) >= 500) {
                rgb_matrix_set_color(90, 0, 100, 0);
            } else {
                rgb_matrix_set_color(90, 0, 0, 0);
            }
        }
    } else {
        if(*md_getp_bat()>5){
            rgb_matrix_set_color(90, 0, 0, 0);
        } else {
            static bool     Low_power_bink;
            static uint16_t Low_power_time;
            if (timer_elapsed(Low_power_time) >= 300) {
                Low_power_bink = !Low_power_bink;
                Low_power_time = timer_read32();
            }
            if (Low_power_bink) {
                rgb_matrix_set_color(90, 100, 0, 0);
            } else {
                rgb_matrix_set_color(90, 0, 0, 0);
            }
        }
    }
#    endif
    // caps lock red
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(89, 100, 100, 100);
    } else {
        rgb_matrix_set_color(89, 0, 0, 0);
    }
    // scroll lock red
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(14, 100, 0, 0);
    }
    // GUI lock red
    if (keymap_config.no_gui) {
        rgb_matrix_set_color(79, 100, 0, 0);
    }
    return true;
}


void md_devs_change(uint8_t devs, bool reset) {

    switch (devs) {
        case DEVS_USB: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
        } break;
        case DEVS_2G4: {
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            } else {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_2G4);
            }
        } break;
        case DEVS_BT1: {
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            } else {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_BT1);
            }
        } break;
        case DEVS_BT2: {
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            } else {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_BT2);
            }
        } break;
        case DEVS_BT3: {
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            } else {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_BT3);
            }
        } break;
        default:
            break;
    }
}

#endif
void wireless_send_nkro(report_nkro_t *report) {
    static report_keyboard_t temp_report_keyboard = {0};
    uint8_t wls_report_nkro[MD_SND_CMD_NKRO_LEN]  = {0};

#ifdef NKRO_ENABLE

    if (report != NULL) {
        report_nkro_t temp_report_nkro = *report;
        uint8_t key_count              = 0;

        temp_report_keyboard.mods = temp_report_nkro.mods;
        for (uint8_t i = 0; i < NKRO_REPORT_BITS; i++) {
            key_count += __builtin_popcount(temp_report_nkro.bits[i]);
        }

        /*
         * Use NKRO for sending when more than 6 keys are pressed
         * to solve the issue of the lack of a protocol flag in wireless mode.
         */

        for (uint8_t i = 0; i < key_count; i++) {
            uint8_t usageid;
            uint8_t idx, n = 0;

            for (n = 0; n < NKRO_REPORT_BITS && !temp_report_nkro.bits[n]; n++) {}
            usageid = (n << 3) | biton(temp_report_nkro.bits[n]);
            del_key_bit(&temp_report_nkro, usageid);

            for (idx = 0; idx < WLS_KEYBOARD_REPORT_KEYS; idx++) {
                if (temp_report_keyboard.keys[idx] == usageid) {
                    goto next;
                }
            }

            for (idx = 0; idx < WLS_KEYBOARD_REPORT_KEYS; idx++) {
                if (temp_report_keyboard.keys[idx] == 0x00) {
                    temp_report_keyboard.keys[idx] = usageid;
                    break;
                }
            }
        next:
            if (idx == WLS_KEYBOARD_REPORT_KEYS && (usageid < (MD_SND_CMD_NKRO_LEN * 8))) {
                wls_report_nkro[usageid / 8] |= 0x01 << (usageid % 8);
            }
        }

        temp_report_nkro = *report;

         // find key up and del it.
        uint8_t nkro_keys = key_count;
        for (uint8_t i = 0; i < WLS_KEYBOARD_REPORT_KEYS; i++) {
            report_nkro_t found_report_nkro;
            uint8_t usageid = 0x00;
            uint8_t n;

            found_report_nkro = temp_report_nkro;

            for (uint8_t c = 0; c < nkro_keys; c++) {
                for (n = 0; n < NKRO_REPORT_BITS && !found_report_nkro.bits[n]; n++) {}
                usageid = (n << 3) | biton(found_report_nkro.bits[n]);
                del_key_bit(&found_report_nkro, usageid);
                if (usageid == temp_report_keyboard.keys[i]) {
                    del_key_bit(&temp_report_nkro, usageid);
                    nkro_keys--;
                    break;
                }
            }

            if (usageid != temp_report_keyboard.keys[i]) {
                temp_report_keyboard.keys[i] = 0x00;
            }
        }
    } else {
        memset(&temp_report_keyboard, 0, sizeof(temp_report_keyboard));
    }
#endif
    void wireless_task(void);
    bool smsg_is_busy(void);
    while(smsg_is_busy()) {
        wireless_task();
    }
    extern host_driver_t wireless_driver;
    wireless_driver.send_keyboard(&temp_report_keyboard);
    md_send_nkro(wls_report_nkro);
}
