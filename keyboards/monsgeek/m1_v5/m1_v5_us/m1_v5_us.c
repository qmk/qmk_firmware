// Copyright 2024 yangzheng20003 (@yangzheng20003)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "module.h"
#include QMK_KEYBOARD_H
#include "wls/wls.h"

#ifdef WIRELESS_ENABLE
#    include "wireless.h"
#    include "usb_main.h"
#    include "lowpower.h"
#endif

// ============================================================================
// Battery and Connection Indicator Configuration
// ============================================================================

// Battery display LED indices (number row: 1-0)
static const uint8_t battery_led_indices[10] = RGB_MATRIX_BAT_INDEX_MAP;

// Wave PWM table for smooth charging animation
static const uint8_t Led_Wave_Pwm_Tab[128] = {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188, 192, 196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 240, 244, 248, 255, 255, 248, 244, 240, 236, 232, 228, 224, 220, 216, 212, 208, 204, 200, 196, 192, 188, 184, 180, 176, 172, 168, 164, 160, 156, 152, 148, 144, 140, 136, 132, 128, 124, 120, 116, 112, 108, 104, 100, 96, 92, 88, 84, 80, 76, 72, 68, 64, 60, 56, 52, 48, 44, 40, 36, 32, 28, 24, 20, 16, 12, 8, 4, 0,
};

// Animation state for battery wave
static uint8_t  battery_wave_offset = 0;
static uint32_t battery_wave_timer  = 0;

// Indicator flags (set by keymap)
bool hs_bat_req_flag = false;
bool hs_fn_key_held  = false;

// Track if status indicators forced LEDs on
static bool    status_indicators_forced_leds = false;
static bool    status_indicators_forced_rgb  = false;
static uint8_t saved_rgb_val                 = 0;

// Visual feedback blink timer
static uint32_t kb_blink_timer = 0;

void hs_kb_blink(void) {
    kb_blink_timer = timer_read32();
}

// EE_CLR deferred execution
static uint32_t ee_clr_timer_callback(uint32_t trigger_time, void *cb_arg) {
    eeconfig_init();
    hs_kb_blink();
    return 0;
}

// ============================================================================

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1; // used to make sure the eeprom has initialized at least once
        uint8_t current_dev : 3;
        uint8_t last_bt_dev : 3;
        uint8_t last_wireless_dev : 3; // Save last wireless device (BT or 2.4G)
    };
} confinfo_t;
confinfo_t confinfo;

typedef struct {
    bool     active;
    uint32_t timer;
    uint32_t interval;
    uint32_t times;
    uint8_t  index;
    RGB      rgb;
    void (*blink_cb)(uint8_t);
} hs_rgb_indicator_t;

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _FBL,
};

#define keymap_is_mac_system() ((get_highest_layer(default_layer_state) == _MBL) || (get_highest_layer(default_layer_state) == _MFL))
#define keymap_is_base_layer() ((get_highest_layer(default_layer_state) == _BL) || (get_highest_layer(default_layer_state) == _FL))

uint32_t post_init_timer   = 0x00;
bool     charging_state    = false;
bool     battery_full_flag = false;
HSV      start_hsv;
bool     lower_sleep = false;

void keyboard_post_init_kb(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif

    confinfo.raw = eeconfig_read_kb();
    if (!confinfo.raw) {
        confinfo.flag              = true;
        confinfo.last_bt_dev       = 1;
        confinfo.last_wireless_dev = 1; // Default to BT1

        eeconfig_init_user();
        eeconfig_update_kb(confinfo.raw);
    }
    // Initialize last_wireless_dev if not set
    if (confinfo.last_wireless_dev == 0) {
        confinfo.last_wireless_dev = (confinfo.current_dev == DEVS_2G4) ? DEVS_2G4 : confinfo.last_bt_dev;
        eeconfig_update_kb(confinfo.raw);
    }

#ifdef LED_POWER_EN_PIN
    gpio_set_pin_output(LED_POWER_EN_PIN);
    gpio_write_pin_high(LED_POWER_EN_PIN);

    gpio_set_pin_output(HS_LED_BOOSTING_PIN);
    gpio_write_pin_high(HS_LED_BOOSTING_PIN);
#endif

#ifdef MM_BT_DEF_PIN
    gpio_set_pin_input_high(MM_BT_DEF_PIN);
#endif

#ifdef MM_2G4_DEF_PIN
    gpio_set_pin_input_high(MM_2G4_DEF_PIN);
#endif

#ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
    gpio_set_pin_output(USB_POWER_EN_PIN);
#endif

#ifdef HS_BAT_CABLE_PIN
    gpio_set_pin_input(HS_BAT_CABLE_PIN);
#endif

#ifdef BAT_FULL_PIN
    gpio_set_pin_input_high(BAT_FULL_PIN);
#endif

    gpio_set_pin_input_high(SYSTEM_WIN_PIN);
    gpio_set_pin_input_high(SYSTEM_MAC_PIN);

#ifdef WIRELESS_ENABLE
    wireless_init();
#    if (!(defined(HS_BT_DEF_PIN) && defined(HS_2G4_DEF_PIN)))
    wireless_devs_change(!confinfo.current_dev, confinfo.current_dev, false);
#    endif
    post_init_timer = timer_read32();
#endif

    keyboard_post_init_user();

    start_hsv = rgb_matrix_get_hsv();
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
    hs_rgb_blink_set_timer(timer_read32());
}

bool lpwr_is_allow_timeout_hook(void) {
    if (wireless_get_current_devs() == DEVS_USB) {
        return false;
    }

    return true;
}

void wireless_post_task(void) {
    // auto switching devs
    if (post_init_timer && timer_elapsed32(post_init_timer) >= 100) {
        md_send_devctrl(MD_SND_CMD_DEVCTRL_FW_VERSION);   // get the module fw version.
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_EN);  // timeout 30min to sleep in bt mode, enable
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_2G4_EN); // timeout 30min to sleep in 2.4g mode, enable
        wireless_devs_change(!confinfo.current_dev, confinfo.current_dev, false);
        post_init_timer = 0x00;
    }

    hs_mode_scan(false, confinfo.current_dev, confinfo.last_bt_dev, confinfo.last_wireless_dev);
}

// i don't know what this does
void m1v5_bt_test(void) {
    md_send_devctrl(0x62);
}

static uint32_t wls_process_long_press(uint32_t trigger_time, void *cb_arg) {
    uint16_t keycode = *((uint16_t *)cb_arg);

    switch (keycode) {
        case KC_BT1: {
            uint8_t mode = hs_none;
            hs_modeio_detection(true, &mode, confinfo.last_bt_dev, confinfo.last_wireless_dev);
            // Allow BT1 pairing when physical switch is in any wireless position
            if ((mode == hs_mac_wireless) || (mode == hs_win_wireless) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT1, true);
            }

        } break;
        case KC_BT2: {
            uint8_t mode = hs_none;
            hs_modeio_detection(true, &mode, confinfo.last_bt_dev, confinfo.last_wireless_dev);
            // Allow BT2 pairing when physical switch is in any wireless position
            if ((mode == hs_mac_wireless) || (mode == hs_win_wireless) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, true);
            }
        } break;
        case KC_BT3: {
            uint8_t mode = hs_none;
            hs_modeio_detection(true, &mode, confinfo.last_bt_dev, confinfo.last_wireless_dev);
            // Allow BT3 pairing when physical switch is in any wireless position
            if ((mode == hs_mac_wireless) || (mode == hs_win_wireless) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT3, true);
            }
        } break;
        case KC_2G4: {
            uint8_t mode = hs_none;
            hs_modeio_detection(true, &mode, confinfo.last_bt_dev, confinfo.last_wireless_dev);
            // Allow 2.4G pairing when physical switch is in any wireless position
            if ((mode == hs_mac_wireless) || (mode == hs_win_wireless) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, true);
            }
        } break;
        default:
            break;
    }

    return 0;
}

static bool process_record_wls(uint16_t keycode, keyrecord_t *record) {
    static uint16_t       keycode_shadow               = 0x00;
    static deferred_token wls_process_long_press_token = INVALID_DEFERRED_TOKEN;

    keycode_shadow = keycode;

#    ifndef WLS_KEYCODE_PAIR_TIME
#        define WLS_KEYCODE_PAIR_TIME 3000
#    endif

#    define WLS_KEYCODE_EXEC(wls_dev)                                                                                          \
        do {                                                                                                                   \
            if (record->event.pressed) {                                                                                       \
                if (wireless_get_current_devs() != wls_dev) wireless_devs_change(wireless_get_current_devs(), wls_dev, false); \
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
            uint8_t mode = hs_none;
            hs_modeio_detection(true, &mode, confinfo.last_bt_dev, confinfo.last_wireless_dev);
            // Allow BT1 when physical switch is in any wireless position (Mac or Windows)
            if ((mode == hs_mac_wireless) || (mode == hs_win_wireless) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_BT1);
                hs_rgb_blink_set_timer(timer_read32());
            }

        } break;
        case KC_BT2: {
            uint8_t mode = hs_none;
            hs_modeio_detection(true, &mode, confinfo.last_bt_dev, confinfo.last_wireless_dev);
            // Allow BT2 when physical switch is in any wireless position (Mac or Windows)
            if ((mode == hs_mac_wireless) || (mode == hs_win_wireless) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_BT2);
                hs_rgb_blink_set_timer(timer_read32());
            }
        } break;
        case KC_BT3: {
            uint8_t mode = hs_none;
            hs_modeio_detection(true, &mode, confinfo.last_bt_dev, confinfo.last_wireless_dev);
            // Allow BT3 when physical switch is in any wireless position (Mac or Windows)
            if ((mode == hs_mac_wireless) || (mode == hs_win_wireless) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_BT3);
                hs_rgb_blink_set_timer(timer_read32());
            }
        } break;
        case KC_2G4: {
            uint8_t mode = hs_none;
            hs_modeio_detection(true, &mode, confinfo.last_bt_dev, confinfo.last_wireless_dev);
            // Allow 2.4G when physical switch is in any wireless position (Mac or Windows)
            if ((mode == hs_mac_wireless) || (mode == hs_win_wireless) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_2G4);
                hs_rgb_blink_set_timer(timer_read32());
            }
        } break;

        case KC_USB: {
            uint8_t mode = hs_none;
            hs_modeio_detection(true, &mode, confinfo.last_bt_dev, confinfo.last_wireless_dev);
            // Allow USB when physical switch is in USB position
            if ((mode == hs_usb) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_USB);
                hs_rgb_blink_set_timer(timer_read32());
            }
        } break;
        default:
            return true;
    }

    return false;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    static deferred_token ee_clr_token = INVALID_DEFERRED_TOKEN;

    // prevent timeout
    if (*md_getp_state() == MD_STATE_CONNECTED) {
        hs_rgb_blink_set_timer(timer_read32());
    }

    // Handle common keycodes at keyboard level
    switch (keycode) {
        case HS_BATQ:
            hs_bat_req_flag = record->event.pressed;
            return false;

        case MO(_FL):
        case MO(_MFL):
            hs_fn_key_held = record->event.pressed;
            break;

        case EE_CLR:
            if (record->event.pressed) {
                ee_clr_token = defer_exec(5000, ee_clr_timer_callback, NULL);
            } else if (ee_clr_token != INVALID_DEFERRED_TOKEN) {
                cancel_deferred_exec(ee_clr_token);
                ee_clr_token = INVALID_DEFERRED_TOKEN;
            }
            return false;

        case HS_SIRI:
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
                unregister_code(KC_LCMD);
            }
            return false;

        case KC_MCTL:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_UP);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_UP);
            }
            return false;

        case RM_SPDU:
            if (record->event.pressed && rgb_matrix_get_speed() >= (RGB_MATRIX_SPD_STEP * 5)) {
                hs_kb_blink();
            }
            break;

        case RM_SPDD:
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() <= RGB_MATRIX_SPD_STEP * 2) {
                    if (rgb_matrix_get_speed() != RGB_MATRIX_SPD_STEP) hs_kb_blink();
                    rgb_matrix_set_speed(RGB_MATRIX_SPD_STEP);
                    return false;
                }
                hs_kb_blink();
            }
            break;

        case RM_VALU:
            if (record->event.pressed) {
                rgb_matrix_enable();
                gpio_write_pin_high(LED_POWER_EN_PIN);
                if (rgb_matrix_get_val() == RGB_MATRIX_MAXIMUM_BRIGHTNESS) hs_kb_blink();
            }
            break;

        case RM_VALD:
            if (record->event.pressed) {
                if (rgb_matrix_get_val() <= RGB_MATRIX_VAL_STEP) {
                    gpio_write_pin_low(LED_POWER_EN_PIN);
                    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                        rgb_matrix_set_color(i, 0, 0, 0);
                    }
                }
                if (rgb_matrix_get_val() == 0) hs_kb_blink();
            }
            break;
    }

    if (process_record_user(keycode, record) != true) {
        return false;
    }

#ifdef WIRELESS_ENABLE
    if (process_record_wls(keycode, record) != true) {
        return false;
    }
#endif

    return true;
}

void housekeeping_task_kb(void) { // loop
#ifdef WIRELESS_ENABLE
    wireless_housekeeping_task();
#endif

    static uint32_t hs_current_time;

    charging_state    = gpio_read_pin(HS_BAT_CABLE_PIN);
    battery_full_flag = gpio_read_pin(BAT_FULL_PIN);

    // Manage LED power and RGB matrix for status indicators
    // Enable LEDs when showing connection or battery status, even if RGB is off
    bool status_indicators_active = hs_fn_key_held || hs_bat_req_flag;

    if (status_indicators_active && !status_indicators_forced_leds) {
        // Status indicators just became active
        status_indicators_forced_leds = true;

        // Save current RGB state and temporarily enable if needed
        if (!rgb_matrix_is_enabled() || rgb_matrix_get_val() == 0) {
            saved_rgb_val                = rgb_matrix_get_val();
            status_indicators_forced_rgb = true;
            rgb_matrix_enable_noeeprom();
            if (rgb_matrix_get_val() == 0) {
                rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), RGB_MATRIX_VAL_STEP);
            }
        }
        gpio_write_pin_high(LED_POWER_EN_PIN);
    } else if (!status_indicators_active && status_indicators_forced_leds) {
        // Status indicators just became inactive - restore previous state
        status_indicators_forced_leds = false;

        if (status_indicators_forced_rgb) {
            status_indicators_forced_rgb = false;
            // Restore previous RGB state
            if (saved_rgb_val == 0) {
                rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 0);
                gpio_write_pin_low(LED_POWER_EN_PIN);
            }
        }
    }

    if (!hs_current_time || timer_elapsed32(hs_current_time) > 1000) {
        uint8_t hs_now_mode;
        if (charging_state && battery_full_flag) {
            hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING_DONE;
        } else if (charging_state) {
            hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING;
        } else {
            hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING_STOP;
        }

        hs_current_time = timer_read32();
        md_send_devctrl(hs_now_mode);
        md_send_devctrl(MD_SND_CMD_DEVCTRL_INQVOL);
    }

    if (charging_state) {
        gpio_write_pin(HS_LED_BOOSTING_PIN, 0);

    } else {
        gpio_write_pin(HS_LED_BOOSTING_PIN, 1);
    }

    if ((gpio_read_pin(SYSTEM_WIN_PIN) != 0) && (gpio_read_pin(SYSTEM_MAC_PIN) == 0)) { // mac system
        if (!keymap_is_mac_system()) {
            set_single_persistent_default_layer(_MBL);
            layer_move(0);
        }
    } else { // win system
        if (keymap_is_mac_system()) {
            set_single_persistent_default_layer(_BL);
            layer_move(0);
        }
    }

    // converts device low power mode after 60 seconds at 0% battery
    static uint32_t battery_process_time = 0;
    if (*md_getp_bat() <= BATTERY_CAPACITY_STOP) {
        if (!battery_process_time) {
            battery_process_time = timer_read32();
        }

        if (battery_process_time && timer_elapsed32(battery_process_time) > 60000) {
            battery_process_time = 0;
            lower_sleep          = true;
            lpwr_set_timeout_manual(true);
        }
    } else {
        battery_process_time = 0;
    }

    housekeeping_task_user();
}

#ifdef RGB_MATRIX_ENABLE

#    ifdef WIRELESS_ENABLE
bool     wls_rgb_indicator_reset    = false;
uint32_t wls_rgb_indicator_timer    = 0x00;
uint32_t wls_rgb_indicator_interval = 0;
uint32_t wls_rgb_indicator_times    = 0;
uint32_t wls_rgb_indicator_index    = 0;
RGB      wls_rgb_indicator_rgb      = {0};

static void rgb_matrix_wls_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times) {
    wls_rgb_indicator_timer = timer_read32();

    wls_rgb_indicator_index    = index;
    wls_rgb_indicator_interval = interval;
    wls_rgb_indicator_times    = times * 2;
    wls_rgb_indicator_rgb      = rgb;
}

static void rgb_matrix_wls_indicator_wls(uint8_t devs) {
    uint32_t interval = wls_rgb_indicator_reset ? 200 : 500;

    switch (devs) {
        case DEVS_USB: {
            rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_USB, (RGB){HS_LBACK_COLOR_USB}, interval, 1);
        } break;
        case DEVS_BT1: {
            rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_BT1, (RGB){HS_LBACK_COLOR_BT1}, interval, 1);
        } break;
        case DEVS_BT2: {
            rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_BT2, (RGB){HS_LBACK_COLOR_BT2}, interval, 1);
        } break;
        case DEVS_BT3: {
            rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_BT3, (RGB){HS_LBACK_COLOR_BT3}, interval, 1);
        } break;
        case DEVS_2G4: {
            rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_2G4, (RGB){HS_LBACK_COLOR_2G4}, interval, 1);
        } break;
    }
}

void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset) {
    wls_rgb_indicator_reset = reset;

    if (confinfo.current_dev != wireless_get_current_devs()) {
        confinfo.current_dev = wireless_get_current_devs();
        if (confinfo.current_dev > 0 && confinfo.current_dev < 4) confinfo.last_bt_dev = confinfo.current_dev;
        // Save last wireless device (BT or 2.4G) for restoring when switching back to wireless
        if (confinfo.current_dev >= DEVS_BT1 && confinfo.current_dev <= DEVS_BT3) {
            confinfo.last_wireless_dev = confinfo.current_dev;
        } else if (confinfo.current_dev == DEVS_2G4) {
            confinfo.last_wireless_dev = DEVS_2G4;
        }
        eeconfig_update_kb(confinfo.raw);
    }

    rgb_matrix_wls_indicator_wls(new_devs);
}

static void rgb_matrix_wls_indicator(void) {
    if (wls_rgb_indicator_timer) {
        if (timer_elapsed32(wls_rgb_indicator_timer) >= wls_rgb_indicator_interval) {
            wls_rgb_indicator_timer = timer_read32();

            if (wls_rgb_indicator_times) {
                wls_rgb_indicator_times--;
            }

            if (wls_rgb_indicator_times <= 0) {
                wls_rgb_indicator_timer = 0x00;

                if (*md_getp_state() != MD_STATE_CONNECTED) {
                    if (!(wireless_get_current_devs() == DEVS_USB && USB_DRIVER.state == USB_ACTIVE)) {
                        rgb_matrix_wls_indicator_wls(wireless_get_current_devs());
                    }
                } else {
                    // refresh led
                    led_wakeup();

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

#endif

bool rgb_matrix_indicators_kb() {
    // Force LEDs on for status indicators even if RGB is disabled
    bool status_indicators_active = hs_fn_key_held || hs_bat_req_flag;

    // Visual feedback blink (white flash)
    if (kb_blink_timer) {
        if ((timer_elapsed32(kb_blink_timer) / 250) % 2 == 0) {
            rgb_matrix_set_color_all(0xFF, 0xFF, 0xFF);
        } else {
            rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        }
        if (timer_elapsed32(kb_blink_timer) > 1250) {
            kb_blink_timer = 0;
        }
        return false;
    }

    // Let user indicators run first (but don't block status indicators)
    bool user_result = rgb_matrix_indicators_user();

    // Only respect user return value if we're not showing status indicators
    if (!user_result && !status_indicators_active) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) rgb_matrix_set_color(HS_RGB_INDEX_CAPS, 0x20, 0x20, 0x20);
    if (!keymap_is_mac_system() && keymap_config.no_gui) rgb_matrix_set_color(HS_RGB_INDEX_WIN_LOCK, 0x20, 0x20, 0x20);

#ifdef WIRELESS_ENABLE
    rgb_matrix_wls_indicator();

    // Show current connection mode indicator when Fn is held
    // This works even if RGB is off
    if (hs_fn_key_held) {
        // Turn off all other LEDs when showing connection indicator (if RGB was forced on)
        if (status_indicators_forced_rgb) {
            rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        }

        uint8_t current_dev = wireless_get_current_devs();
        switch (current_dev) {
            case DEVS_USB:
                rgb_matrix_set_color(HS_RGB_BLINK_INDEX_USB, HS_LBACK_COLOR_USB);
                break;
            case DEVS_BT1:
                rgb_matrix_set_color(HS_RGB_BLINK_INDEX_BT1, HS_LBACK_COLOR_BT1);
                break;
            case DEVS_BT2:
                rgb_matrix_set_color(HS_RGB_BLINK_INDEX_BT2, HS_LBACK_COLOR_BT2);
                break;
            case DEVS_BT3:
                rgb_matrix_set_color(HS_RGB_BLINK_INDEX_BT3, HS_LBACK_COLOR_BT3);
                break;
            case DEVS_2G4:
                rgb_matrix_set_color(HS_RGB_BLINK_INDEX_2G4, HS_LBACK_COLOR_2G4);
                break;
        }
    }

    // Show battery status when HS_BATQ is held and NOT charging (wireless mode)
    // This works even if RGB is off
    if (hs_bat_req_flag && !charging_state) {
        // Turn off all other LEDs when showing battery indicator (if RGB was forced on)
        if (status_indicators_forced_rgb) {
            rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        }

        uint8_t battery_pct = *md_getp_bat();

        // Normal battery display with proportional LEDs and color thresholds
        uint8_t leds_to_light = (battery_pct / 10);
        if (leds_to_light < 1) leds_to_light = 1;
        if (leds_to_light > 10) leds_to_light = 10;

        // Get battery color: <=20% red, <=50% yellow, >50% green
        uint8_t bat_r, bat_g, bat_b;
        if (battery_pct <= 20) {
            bat_r = RGB_MATRIX_BAT_VAL;
            bat_g = 0x00;
            bat_b = 0x00;
        } else if (battery_pct <= 50) {
            bat_r = RGB_MATRIX_BAT_VAL;
            bat_g = RGB_MATRIX_BAT_VAL;
            bat_b = 0x00;
        } else {
            bat_r = 0x00;
            bat_g = RGB_MATRIX_BAT_VAL;
            bat_b = 0x00;
        }

        for (uint8_t i = 0; i < 10; i++) {
            if (i < leds_to_light) {
                rgb_matrix_set_color(battery_led_indices[i], bat_r, bat_g, bat_b);
            } else {
                rgb_matrix_set_color(battery_led_indices[i], 0x00, 0x00, 0x00);
            }
        }
    }
    // Show wave animation when HS_BATQ is held AND charging
    else if (hs_bat_req_flag && charging_state && !battery_full_flag) {
        // Turn off all other LEDs when showing battery indicator (if RGB was forced on)
        if (status_indicators_forced_rgb) {
            rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        }

        if (timer_elapsed32(battery_wave_timer) > 30) {
            battery_wave_timer  = timer_read32();
            battery_wave_offset = (battery_wave_offset > 3) ? (battery_wave_offset - 3) : 127;
        }

        uint8_t wave_pos = battery_wave_offset;
        for (uint8_t i = 0; i < 10; i++) {
            rgb_matrix_set_color(battery_led_indices[i], 0x00, Led_Wave_Pwm_Tab[wave_pos], 0x00);
            wave_pos = (wave_pos + 10) % 128;
        }
    }
    // Show solid green when HS_BATQ is held AND fully charged
    else if (hs_bat_req_flag && charging_state && battery_full_flag) {
        // Turn off all other LEDs when showing battery indicator (if RGB was forced on)
        if (status_indicators_forced_rgb) {
            rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        }

        for (uint8_t i = 0; i < 10; i++) {
            rgb_matrix_set_color(battery_led_indices[i], 0x00, RGB_MATRIX_BAT_VAL, 0x00);
        }
    }

    // Low battery warning - blinking red (always shown when battery is low)
    if (*md_getp_bat() <= BATTERY_CAPACITY_LOW && !hs_bat_req_flag) {
        static uint32_t battery_flash_timer;

        if (!battery_flash_timer || timer_elapsed32(battery_flash_timer) > 500) {
            battery_flash_timer = timer_read32();
        }

        if (timer_elapsed32(battery_flash_timer) <= 250) {
            rgb_matrix_set_color(HS_MATRIX_BLINK_INDEX_BAT, 0xFF, 0x00, 0x00);
        } else {
            rgb_matrix_set_color(HS_MATRIX_BLINK_INDEX_BAT, 0x00, 0x00, 0x00);
        }
    }
#endif

    return true;
}

void lpwr_wakeup_hook(void) {
    hs_mode_scan(false, confinfo.current_dev, confinfo.last_bt_dev, confinfo.last_wireless_dev);

    gpio_write_pin_high(LED_POWER_EN_PIN);
    gpio_write_pin_high(HS_LED_BOOSTING_PIN);
}
