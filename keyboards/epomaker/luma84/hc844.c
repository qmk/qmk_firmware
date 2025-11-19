// Copyright 2024 sdk66 (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "wls/wls.h"
#include "rgb_record/rgb_record.h"
#include "rgb_record/rgb_rgblight.h"

#ifdef WIRELESS_ENABLE
#    include "wireless.h"
#    include "usb_main.h"
#    include "lowpower.h"
#    include "rgb_matrix_blink.h"
#endif

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1;
        uint8_t devs : 3;
        uint8_t record_channel : 4;
        uint8_t record_last_mode;
        uint8_t last_btdevs : 3;
        uint8_t dir_flag : 1;
        uint8_t ctrl_app_flag : 1;
        uint8_t rgb_enable : 1;
        uint8_t rgblight_flag: 1;
        uint8_t hs_RM_TOGG : 1;
        uint8_t sleep_timeout : 3;
    };
} confinfo_t;
confinfo_t confinfo;

typedef struct {
    bool active;
    uint32_t timer;
    uint32_t interval;
    uint32_t times;
    uint8_t index;
    RGB rgb;
    void (*blink_cb)(uint8_t);
} hs_rgb_indicator_t;

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _FBL,
};

void hs_reset_settings(void);
void matrix_init_user(void);

#define keymap_is_mac_system() ((get_highest_layer(default_layer_state) == _MBL) || (get_highest_layer(default_layer_state) == _MFL))
#define keymap_is_base_layer() ((get_highest_layer(default_layer_state) == _BL) || (get_highest_layer(default_layer_state) == _FL))

uint32_t post_init_timer     = 0x00;
bool inqbat_flag             = false;
bool charging_state          = false;
bool bat_full_flag           = false;
static uint32_t ee_clr_timer = 0;
bool test_white_light_flag = false;
HSV start_hsv;
bool no_record_fg;
bool lower_sleep = false;
bool hs_color_test;
bool hs_frequency_test;
bool Mode_Query              = false;
bool hs_RM_TOGG_flag         = false;
uint8_t buff[]   = {14, 8, 2, 1, 1, 1, 1, 1, 1, 1, 0};

void bat_indicators_hook(uint8_t index);
void ind_indicators_hook(uint8_t index);
void nkr_indicators_hook(uint8_t index);
blink_rgb_t blink_rgbs[RGB_MATRIX_BLINK_COUNT] = {
    {.index = HS_RGB_BLINK_INDEX_USB, .interval = 250, .times = 3, .color = {.r = 0xFF, .g = 0xFF, .b = 0xFF}, .blink_cb = NULL},
    {.index = HS_RGB_BLINK_INDEX_WIN, .interval = 250, .times = 1, .color = {.r = 0xFF, .g = 0xFF, .b = 0xFF}, .blink_cb = NULL},
    {.index = HS_RGB_BLINK_INDEX_MAC, .interval = 250, .times = 1, .color = {.r = 0xFF, .g = 0xFF, .b = 0xFF}, .blink_cb = NULL},
    {.index = RGB_MATRIX_BLINK_INDEX_BAT, .interval = 250, .times = 3, .color = {.r = 0x00, .g = 0x00, .b = 0x00}, .blink_cb = bat_indicators_hook},
    {.index = RGB_MATRIX_BLINK_INDEX_IND, .interval = 250, .times = 3, .color = {.r = 0x00, .g = 0x00, .b = 0x00}, .blink_cb = ind_indicators_hook},
    {.index = RGB_MATRIX_BLINK_INDEX_ALL, .interval = 250, .times = 3, .color = {.r = WIITE_B, .g = 0x00, .b = 0x00}, .blink_cb = nkr_indicators_hook},
};

void nkr_indicators_hook(uint8_t index) {
    if (index == RGB_MATRIX_BLINK_INDEX_ALL) {
        if ((blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.r == WIITE_B) && (blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.g == 0x00) && (blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.b == 0x00)) {
            if (rgb_matrix_blink_set_color(index, 0x00, 0x00, WIITE_B) != true) {
                dprintf("RGB_BLUE again\n");
            }
            rgb_matrix_blink_set_times(index, 1);
            rgb_matrix_blink_set(index);
            dprintf("GREEM\r\n");
        } else if ((blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.r == 0x00) && (blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.g == 0x00) && (blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.b == WIITE_B)) {
            if (rgb_matrix_blink_set_color(index, 0x00, WIITE_B, 0x00) != true) {
                dprintf("RGB_GREEN again\n");
            }
            rgb_matrix_blink_set_times(index, 1);
            rgb_matrix_blink_set(index);
            dprintf("BLUE\r\n");
        }
    }
}

void bat_indicators_hook(uint8_t index) {
    static uint32_t battery_process_time = 0;
    static bool bat_flip = true;
    static uint32_t low_power_time = 0;
    static uint32_t charge_time = 0;
    bool low_power_flag = true;
    bool charge_flag = true;

    if (charging_state && ( (bat_full_flag))) { // power full
        low_power_time = timer_read32();
        charge_time = timer_read32();
        charge_flag = true;
        low_power_flag = true;
        battery_process_time = 0;
        bat_flip = true;
        rgb_matrix_blink_set_color(index, 0x00, 0x00, 0x00);
        rgb_matrix_blink_set_interval_times(index, 300, 0xFF);
    } else if (charging_state) { // charing...
        low_power_time = timer_read32();
        low_power_flag = true;
        battery_process_time = 0;
        bat_flip = true;
        if (charge_flag == true) {
           if (timer_elapsed32(charge_time) > 5000) {
                charge_flag = false;
                rgb_matrix_blink_set_color(index, 0x00, 0x00, 0x00);
                rgb_matrix_blink_set_interval_times(index, 300, 0xFF);
            } else {
                rgb_matrix_blink_set_color(index, 0xFF, 0x00, 0x00);
                rgb_matrix_blink_set_interval_times(index, 300, 0xFF);
            }
        } else {
            rgb_matrix_blink_set_color(index, 0x00, 0x00, 0x00);
            rgb_matrix_blink_set_interval_times(index, 300, 0xFF);
        }

    } else if (*md_getp_bat() <= BATTERY_CAPACITY_LOW) { // low power
        charge_time = timer_read32();
        charge_flag = true;
        if (low_power_flag == true) {
            if (timer_elapsed32(low_power_time) > 5000) {
                low_power_flag = false;
                rgb_matrix_blink_set_color(index, 0x00, 0x00, 0x00);
                rgb_matrix_blink_set_interval_times(index, 300, 0xFF);
            } else {
                if (bat_flip) {
                    rgb_matrix_blink_set_color(index, 0xFF, 0x00, 0x00);
                    rgb_matrix_blink_set_interval_times(index, 500, 1);
                } else {
                    rgb_matrix_blink_set_color(index, 0x00, 0x00, 0x00);
                    rgb_matrix_blink_set_interval_times(index, 500, 0xFF);
                }
            }
        } else {
            rgb_matrix_blink_set_color(index, 0x00, 0x00, 0x00);
            rgb_matrix_blink_set_interval_times(index, 300, 0xFF);
        }

        // bat_flip = !bat_flip;

        if (*md_getp_bat() <= BATTERY_CAPACITY_STOP) {
            if (!battery_process_time) {
                battery_process_time = timer_read32();
            }

            if (battery_process_time && timer_elapsed32(battery_process_time) > 20000) {
                battery_process_time = 0;
                lower_sleep = true;
                md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
                lpwr_set_timeout_manual(true);
            }
        }
    } else {
        charge_time = timer_read32();
        low_power_time = timer_read32();
        charge_flag = true;
        low_power_flag = true;
        battery_process_time = 0;
        bat_flip = true;
        rgb_matrix_blink_set_color(index, 0x00, 0x00, 0x00);
        rgb_matrix_blink_set_interval_times(index, 300, 0xFF);
    }

    rgb_matrix_blink_set(index);
}

typedef enum {
    ind_state_none = 0,
    ind_state_exec,
    ind_state_blink3,
    ind_state_blinkon,
    ind_state_blinkoff,
} ind_status_t;

ind_status_t ind_status = ind_state_none;

void ind_indicators_hook(uint8_t index) {

    switch(ind_status) {
        case ind_state_none: {
            rgb_matrix_blink_set_color(index, host_keyboard_led_state().caps_lock, !keymap_is_mac_system() ? keymap_config.no_gui : 0 , 0x00);
            rgb_matrix_blink_set_interval_times(index, 50, 0xFF);
        } break;
        case ind_state_blink3: {
            rgb_matrix_blink_set_color(index, 0xFF, 0xFF, 0xFF);
            rgb_matrix_blink_set_interval_times(index, 200, 3);
            ind_status = ind_state_exec;
        } break;
        case ind_state_blinkon: {
            rgb_matrix_blink_set_color(index, 0xFF, 0xFF, 0xFF);
            rgb_matrix_blink_set_interval_times(index, 200, 1);
        } break;
        case ind_state_blinkoff: {
            ind_status = ind_state_none;
            ind_indicators_hook(index);
        } break;
        case ind_state_exec: {
            ind_status = ind_state_none;
            ind_indicators_hook(index);
        } break;
        default: break;
    }

    rgb_matrix_blink_set(index);
}

void ind_set_blink(ind_status_t status) {
    ind_status = status;
    rgb_matrix_blink_set_remain_time(RGB_MATRIX_BLINK_INDEX_IND, 0x00);
    ind_indicators_hook(RGB_MATRIX_BLINK_INDEX_IND);
}

bool rgb_matrix_blink_user(blink_rgb_t *blink_rgb) {
   static uint32_t test_breath_time = 0;
    static uint8_t test_breath  = 0;
    static bool test_breath_flag  = false;
    switch (blink_rgb->index) {
        case RGB_MATRIX_BLINK_INDEX_BAT: {
            if(test_white_light_flag == true){
                return false;
            }

            if (blink_rgb->flip) {
                if(blink_rgb->color.r){
                    if (!test_breath_flag) {
                        if (timer_elapsed32(test_breath_time) > 2) {
                            test_breath_time = timer_read32();
                            test_breath++;
                        }
                        if (test_breath >= 200) {
                            test_breath_flag = true;
                        }
                    } else {
                        if (timer_elapsed32(test_breath_time) > 2) {
                            test_breath_time = timer_read32();
                            test_breath--;
                        }
                        if (test_breath <= 0) {
                            test_breath_flag = false;
                        }
                    }
                    rgb_matrix_set_color(HS_MATRIX_BLINK_INDEX_BAT, test_breath, 0x00,0x00);
                }
            }else {
                rgb_matrix_set_color(HS_MATRIX_BLINK_INDEX_BAT, 0x00, 0x00, 0x00);
            }
            return false;
        } break;

        case RGB_MATRIX_BLINK_INDEX_IND: {

            switch(ind_status) {
                case ind_state_none: {
                    return false;
                } break;
                case ind_state_blinkon:
                case ind_state_blinkoff: {
                    if (!blink_rgb->flip) {
                        // rgb_matrix_set_color(HS_RGB_BLINK_INDEX_REC, blink_rgb->color.r, blink_rgb->color.g, blink_rgb->color.b);
                    }
                } break;
                case ind_state_exec: {
                    if (rgbrec_is_started()) {
                        return false;
                    }

                    if (blink_rgb->flip) {
                        rgb_matrix_set_color(HS_RGB_BLINK_INDEX_VAI, blink_rgb->color.r, blink_rgb->color.g, blink_rgb->color.b);
                        rgb_matrix_set_color(HS_RGB_BLINK_INDEX_VAD, blink_rgb->color.r, blink_rgb->color.g, blink_rgb->color.b);
                        rgb_matrix_set_color(HS_RGB_BLINK_INDEX_SPI, blink_rgb->color.r, blink_rgb->color.g, blink_rgb->color.b);
                        rgb_matrix_set_color(HS_RGB_BLINK_INDEX_SPD, blink_rgb->color.r, blink_rgb->color.g, blink_rgb->color.b);
                    } else {
                        rgb_matrix_set_color(HS_RGB_BLINK_INDEX_VAI, 0x00, 0x00, 0x00);
                        rgb_matrix_set_color(HS_RGB_BLINK_INDEX_VAD, 0x00, 0x00, 0x00);
                        rgb_matrix_set_color(HS_RGB_BLINK_INDEX_SPI, 0x00, 0x00, 0x00);
                        rgb_matrix_set_color(HS_RGB_BLINK_INDEX_SPD, 0x00, 0x00, 0x00);
                    }
                } break;
                default: break;
            }

            return false;
        } break;
#undef HS_RGB_BLINK_INDEX_REC
#ifdef HS_RGB_BLINK_INDEX_REC
        case HS_RGB_BLINK_INDEX_REC: {
        } break;
#endif
        default: {
            if (test_white_light_flag) {
                return false;
            }
            if (rgbrec_is_started()) {
                return false;
            }
        } break;
    }

    return true;
}

void eeconfig_confinfo_update(void) {

    eeconfig_update_kb(confinfo.raw);
}

uint32_t eeconfig_confinfo_read(void) {

    return eeconfig_read_kb();
}

uint8_t hs_get_sleep_timeout(void){
    return confinfo.sleep_timeout;
}

void hs_set_sleep_timeout(uint8_t sleep_timeout){
    confinfo.sleep_timeout = sleep_timeout;
}

bool hs_get_rgb_enable(void) {
#ifdef RGBLIGHT_ENABLE
    return confinfo.rgb_enable;
#else
    return rgb_matrix_config.enable;
#endif
}

void hs_set_rgb_enable(bool state) {
#ifdef RGBLIGHT_ENABLE
    confinfo.rgb_enable = state;
    if (confinfo.rgb_enable)
        rgblight_enable();
    else
        rgblight_disable();
    eeconfig_confinfo_update();
#else
    rgb_matrix_config.enable = state;
#endif
}

void eeconfig_confinfo_default(void) {

    confinfo.flag             = true;
    confinfo.record_channel   = 0;
    confinfo.record_last_mode = 0xff;
    confinfo.last_btdevs      = 1;
    confinfo.dir_flag         = 0;
    confinfo.ctrl_app_flag    = 0;
    confinfo.sleep_timeout    = 7;
    confinfo.rgb_enable       = true;
    confinfo.rgblight_flag    = true;
    confinfo.hs_RM_TOGG       = true;
    #ifdef WIRELESS_ENABLE
        confinfo.devs = DEVS_USB;
    #endif

    confinfo.devs = wireless_get_current_devs();
    eeconfig_init_user_datablock();
    eeconfig_confinfo_update();

#if defined(NKRO_ENABLE) && defined(FORCE_NKRO)
    keymap_config.nkro = 1;
    eeconfig_update_keymap(keymap_config.raw);
#endif

#ifdef RGBLIGHT_ENABLE
    rgblight_mode(buff[0]);
#endif
}

void eeconfig_confinfo_init(void) {

    confinfo.raw = eeconfig_confinfo_read();

    if (!confinfo.raw) {
        eeconfig_confinfo_default();
    }

}
static uint8_t mode = 0;
void keyboard_post_init_kb(void) {

#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif

    eeconfig_confinfo_init();

#ifdef LED_POWER_EN_PIN
    gpio_set_pin_output(LED_POWER_EN_PIN);
    if (rgb_matrix_get_val() != 0 && hs_get_rgb_enable()) gpio_write_pin_high(LED_POWER_EN_PIN);

    gpio_set_pin_output(HS_LED_BOOSTING_PIN);
    gpio_write_pin_high(HS_LED_BOOSTING_PIN);
#endif

#ifdef HS_BT_DEF_PIN
    setPinInputHigh(HS_BT_DEF_PIN);
#endif

#ifdef HS_2G4_DEF_PIN
    setPinInputHigh(HS_2G4_DEF_PIN);
#endif

#ifdef HS_MODE_SW_PIN
    setPinInputHigh(HS_MODE_SW_PIN);
#endif

#ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
    gpio_set_pin_output(USB_POWER_EN_PIN);
#endif

#ifdef HS_BAT_CABLE_PIN
    setPinInput(HS_BAT_CABLE_PIN);
#endif

#ifdef BAT_FULL_PIN
    setPinInputHigh(BAT_FULL_PIN);
#endif

#ifdef RGB_MATRIX_BLINK_INDEX_BAT
    rgb_matrix_blink_set_interval_times(RGB_MATRIX_BLINK_INDEX_BAT, 200, 0xFF);
    rgb_matrix_blink_set(RGB_MATRIX_BLINK_INDEX_BAT);
#endif

#ifdef RGB_MATRIX_BLINK_INDEX_IND
    rgb_matrix_blink_set_interval_times(RGB_MATRIX_BLINK_INDEX_IND, 200, 0xFF);
    rgb_matrix_blink_set(RGB_MATRIX_BLINK_INDEX_IND);
#endif

#ifdef HS_RGB_BLINK_INDEX_REC
    rgb_matrix_blink_set_interval_times(HS_RGB_BLINK_INDEX_REC, 200, 0xFF);
    rgb_matrix_blink_set(HS_RGB_BLINK_INDEX_REC);
#endif

#ifdef WIRELESS_ENABLE
    wireless_init();
#    if (!(defined(HS_BT_DEF_PIN) && defined(HS_2G4_DEF_PIN)))

    wireless_devs_change(!DEVS_USB, confinfo.devs, false);

#    endif

    post_init_timer = timer_read32();
#endif

    keyboard_post_init_user();

    rgbrec_init(confinfo.record_channel);

#ifdef RGB_MATRIX_ENABLE
#    if defined(RGBLIGHT_ENABLE) && defined(LED_POWER_EN_PIN)
    if ((rgblight_is_enabled() != true) && (hs_get_rgb_enable() != true)) {
        rgb_matrix_disable();
        gpio_write_pin_low(LED_POWER_EN_PIN);

    } else {
        gpio_write_pin_high(LED_POWER_EN_PIN);

    }
#    elif defined(LED_POWER_EN_PIN)
    if (rgb_matrix_is_enabled() != true) {
        rgb_matrix_disable();
        gpio_write_pin_low(LED_POWER_EN_PIN);

    } else {
        gpio_write_pin_high(LED_POWER_EN_PIN);
    }
#    endif
#endif
    start_hsv = rgb_matrix_get_hsv();
    if (!rgblight_is_enabled()) mode = 10;
    matrix_init_user();
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
bool temp = false;
void suspend_power_down_kb(void) {

#    ifdef LED_POWER_EN_PIN
    gpio_write_pin_low(LED_POWER_EN_PIN);
#    endif

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {

#    ifdef LED_POWER_EN_PIN
    if (rgb_matrix_get_val() != 0 && hs_get_rgb_enable()) gpio_write_pin_high(LED_POWER_EN_PIN);
#    endif

    wireless_devs_change(wireless_get_current_devs(), wireless_get_current_devs(), false);
    suspend_wakeup_init_user();
    hs_rgb_blink_set_timer(timer_read32());
    temp = false;
}

bool lpwr_is_allow_timeout_hook(void) {

    // if (wireless_get_current_devs() == DEVS_USB) {
    //     return false;
    // }

    return true;
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

    hs_mode_scan(false, confinfo.devs, confinfo.last_btdevs);

}
bool state = false;
uint32_t wls_process_long_press(uint32_t trigger_time, void *cb_arg) {
    uint16_t keycode = *((uint16_t *)cb_arg);

    switch (keycode) {
        case KC_BT1: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT1, true);
                // if (wireless_get_current_devs() != DEVS_BT1) {
                    state = true;
                    hs_rgb_blink_set_timer(timer_read32());
                // }
            }

        } break;
        case KC_BT2: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, true);
                // if (wireless_get_current_devs() != DEVS_BT1) {
                    state = true;
                    hs_rgb_blink_set_timer(timer_read32());
                // }
            }
        } break;
        case KC_BT3: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT3, true);
                // if (wireless_get_current_devs() != DEVS_BT1) {
                    state = true;
                    hs_rgb_blink_set_timer(timer_read32());
                // }
            }
        } break;
        case KC_2G4: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_2g4) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, true);
                // if (wireless_get_current_devs() != DEVS_BT1) {
                    state = true;
                    hs_rgb_blink_set_timer(timer_read32());
                // }
            }
        } break;
        case BT_TEST: {
            // md_send_devctrl(0x62);
            // wait_ms(30);
            // wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, true);
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
                if (wireless_get_current_devs() != wls_dev)                                                                    \
                    wireless_devs_change(wireless_get_current_devs(), wls_dev, false);                                         \
                if (wls_process_long_press_token == INVALID_DEFERRED_TOKEN) {                                                  \
                    wls_process_long_press_token = defer_exec(WLS_KEYCODE_PAIR_TIME, wls_process_long_press, &keycode_shadow); \
                }                                                                                                              \
            } else {                                                                                                           \
                cancel_deferred_exec(wls_process_long_press_token);                                                            \
                wls_process_long_press_token = INVALID_DEFERRED_TOKEN;                                                         \
            }                                                                                                                  \
        } while (false)

    switch (keycode) {
        case BT_TEST:{
            // WLS_KEYCODE_EXEC(wireless_get_current_devs());
        }break;

        case KC_BT1: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_BT1);
                if (record->event.pressed) {suspend_wakeup_init();state = false;
                hs_rgb_blink_set_timer(timer_read32());}
            }

        } break;
        case KC_BT2: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {

                WLS_KEYCODE_EXEC(DEVS_BT2);
                if (record->event.pressed) {suspend_wakeup_init();state = false;
                hs_rgb_blink_set_timer(timer_read32());}
            }
        } break;
        case KC_BT3: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {

                WLS_KEYCODE_EXEC(DEVS_BT3);
                if (record->event.pressed) {suspend_wakeup_init();state = false;
                hs_rgb_blink_set_timer(timer_read32());}
            }
        } break;
        case KC_2G4: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_2g4) || (mode == hs_wireless) || (mode == hs_none)) {

                WLS_KEYCODE_EXEC(DEVS_2G4);
                if (record->event.pressed) {suspend_wakeup_init();state = false;
                hs_rgb_blink_set_timer(timer_read32());}
            }
        } break;

        case KC_USB: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode, confinfo.last_btdevs);
            if ((mode == hs_2g4) || (mode == hs_wireless) || (mode == hs_none)) {

                WLS_KEYCODE_EXEC(DEVS_USB);
                state = false;
                hs_rgb_blink_set_timer(timer_read32());
            }
            rgb_matrix_blink_set_remain_time(HS_RGB_BLINK_INDEX_USB, 0);
            rgb_matrix_blink_set_interval_times(HS_RGB_BLINK_INDEX_USB, 250, 3);
            rgb_matrix_blink_set(HS_RGB_BLINK_INDEX_USB);
        } break;
        default:
            return true;
    }

    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (test_white_light_flag && record->event.pressed) {
        test_white_light_flag = false;
        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
    }

    if (*md_getp_state() == MD_STATE_CONNECTED && record->event.pressed) {
        hs_rgb_blink_set_timer(timer_read32());
    }

    switch (keycode) {
        case MO(_FL):
        case MO(_MFL): {
            if (!record->event.pressed) {
                if (rgbrec_is_started()) {
                    if (no_record_fg == true) {
                        no_record_fg = false;
                        rgbrec_register_record(keycode, record);
                    }
                    no_record_fg = true;
                }
                Mode_Query = false;
                hs_RM_TOGG_flag = false;
                if (!confinfo.hs_RM_TOGG) {
                    rgb_matrix_disable();
                    writePin(LED_POWER_EN_PIN, !RGB_DRIVER_EN_STATE);
                }
            } else {
                rgb_matrix_enable();
                writePin(LED_POWER_EN_PIN, RGB_DRIVER_EN_STATE);
                if (!confinfo.hs_RM_TOGG) {
                    hs_RM_TOGG_flag = true;
                }
                Mode_Query = true;
            }
            break;
        }
        case RP_END:
        case RP_P0:
        case RP_P1:
        case RP_P2:
        case RM_NEXT:
            break;
        default: {
            if (rgbrec_is_started()) {
                if (!IS_QK_MOMENTARY(keycode) && record->event.pressed) {
                    rgbrec_register_record(keycode, record);

                    return false;
                }
            }
        } break;
    }

    if (rgbrec_is_started() && (!(keycode == RP_P0 || keycode == RP_P1 || keycode == RP_P2 || keycode == RP_END || keycode == RM_NEXT || keycode == MO(_FL) || keycode == MO(_MFL)))) {

        return false;
    }

    return true;
}

void im_rgblight_increase(void) {
    HSV rgb;
    uint8_t moude;
    moude = rgblight_get_mode();

    if (moude == 1){
        rgb = rgblight_get_hsv();
        if (rgb.h == 0 && rgb.s != 0) mode = 3;
        else mode = 9;
        switch (rgb.h){
            case 40:mode = 4;break;
            case 80:mode = 5;break;
            case 120:mode = 6;break;
            case 160:mode = 7;break;
            case 200:mode = 8;break;
            default :break;
        }
    }
    mode++;
    dprintf("mode = %d\r\n",mode);
    if(mode == 11) mode=0;
    if (mode == 10) {rgb = rgblight_get_hsv();rgblight_sethsv(0,255,rgb.v);rgblight_disable();confinfo.rgblight_flag = false;}
    else
    {
        rgblight_enable();

        rgblight_mode(buff[mode]);
        confinfo.rgblight_flag = true;
    }
    rgb = rgblight_get_hsv();
    switch (mode){
        case 3: rgblight_sethsv(0,255,rgb.v);break;
        case 4: rgblight_sethsv(40,255,rgb.v);break;
        case 5: rgblight_sethsv(80,255,rgb.v);break;
        case 6: rgblight_sethsv(120,255,rgb.v);break;
        case 7: rgblight_sethsv(160,255,rgb.v);break;
        case 8: rgblight_sethsv(200,255,rgb.v);break;
        case 9: rgblight_sethsv(0,0,rgb.v);break;
        case 0: rgblight_set_speed(255);break;
        default:rgblight_set_speed(200);break;
    }
}

RGB rgb_test_open;
bool im_test_rate_flag;
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if (process_record_user(keycode, record) != true) {
        return false;
    }

#ifdef WIRELESS_ENABLE
    if (process_record_wls(keycode, record) != true) {
        return false;
    }
#endif

    if ((confinfo.devs != DEVS_USB && *md_getp_state() == MD_STATE_DISCONNECTED)){
        if(IS_BASIC_KEYCODE(keycode) || IS_MODIFIER_KEYCODE(keycode)){
            return false;
        }
    }

    if (hs_frequency_test && hs_color_test){
        if (!(keycode >= KC_1 && keycode <= KC_4))
            return false;
    }

    switch (keycode) {
        case EX_RATE: {
            if (record->event.pressed) {
                im_test_rate_flag = true;
            } else {
                im_test_rate_flag = false;
            }
            return false;
        } break;
        case KC_CUT: {
            if(record->event.pressed) {
                register_code16(KC_LCTL);
                register_code16(KC_X);
            } else {
                unregister_code16(KC_LCTL);
                unregister_code16(KC_X);
            }
            return false;
        } break;
        case KC_COPY: {
            if(record->event.pressed) {
                register_code16(KC_LCTL);
                register_code16(KC_C);
            } else {
                unregister_code16(KC_LCTL);
                unregister_code16(KC_C);
            }
            return false;
        } break;
        case KC_PASTE: {
            if(record->event.pressed) {
                register_code16(KC_LCTL);
                register_code16(KC_V);
            } else {
                unregister_code16(KC_LCTL);
                unregister_code16(KC_V);
            }
            return false;
        } break;
        case KC_FIND: {
            if(record->event.pressed) {
                register_code16(KC_LCTL);
                register_code16(KC_F);
            } else {
                unregister_code16(KC_LCTL);
                unregister_code16(KC_F);
            }
            return false;
        } break;
        case KC_1: {
            if(hs_frequency_test && hs_color_test){
                if (record->event.pressed) {
                    md_send_devctrl(0x60);
                    md_rf_send_carrier(0, 5, 0x01);

                }
                return false;
            }
        } break;
        case KC_2: {
            if(hs_frequency_test && hs_color_test){
                if (record->event.pressed) {
                    md_send_devctrl(0x60);
                    md_rf_send_carrier(19, 5, 0x01);

                }
                return false;
            }
        } break;
        case KC_3: {
            if(hs_frequency_test && hs_color_test){
                if (record->event.pressed) {
                    md_send_devctrl(0x60);
                    md_rf_send_carrier(38, 5, 0x01);

                }
                return false;
            }
        } break;
        case KC_4: {
            if(hs_frequency_test && hs_color_test){
                if (record->event.pressed) {
                    md_rf_send_stop();
                }
                return false;
            }
        } break;

        case KC_ENCW: {
            if (record->event.pressed) {
                test_white_light_flag = !test_white_light_flag;

            }
            return false;

        } break;
        case QK_BOOT: {
            if (record->event.pressed) {
                dprintf("into boot!!!\r\n");
                eeconfig_disable();
                bootloader_jump();
            }
        } break;
        case BT_TEST: {
            if (record->event.pressed) {
                md_send_devctrl(0x62);
            }
            return false;
        } break;
        case NK_TOGG: {
            if (record->event.pressed) {
                rgb_matrix_blink_set_color(RGB_MATRIX_BLINK_INDEX_ALL, WIITE_B, 0x00, 0x00);
                rgb_matrix_blink_set_times(RGB_MATRIX_BLINK_INDEX_ALL, 1);
                rgb_matrix_blink_set(RGB_MATRIX_BLINK_INDEX_ALL);
            }
        } break;
        case RL_MOD: {
            if (record->event.pressed) {
                if (confinfo.rgblight_flag == false) {
                    mode = 10;
                }
                im_rgblight_increase();
                eeconfig_confinfo_update();
            }

            return false;
        } break;
        case EE_CLR: {
            if (record->event.pressed) {
                ee_clr_timer = timer_read32();
            } else {
                ee_clr_timer = 0;
            }

            return false;
        } break;
        case RM_SPDU: {
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() >= (255 - RGB_MATRIX_SPD_STEP)) {
                    ind_set_blink(ind_state_blink3);
                }
            }
        } break;
        case RM_SPDD: {
            dprintf("rgb_matrix_get_speed = %d\r\n",rgb_matrix_get_speed());
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() <= 102) {
                    ind_set_blink(ind_state_blink3);
                    rgb_matrix_set_speed(51);

                    return false;
                }
            } else {
                if (rgb_matrix_get_speed() == 51)
                    return false;
            }
        } break;
        case RM_VALU: {
            if (record->event.pressed) {
                if(rgb_matrix_is_enabled()) gpio_write_pin_high(LED_POWER_EN_PIN);
                if (rgb_matrix_get_val() >= (RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP)) {
                    ind_set_blink(ind_state_blink3);
                }
            }
        } break;
        case RM_VALD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_val() <= RGB_MATRIX_VAL_STEP) {
                    gpio_write_pin_high(LED_POWER_EN_PIN);
                    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                        rgb_matrix_set_color(i, 0, 0, 0);
                    }
                    ind_set_blink(ind_state_blink3);
                }
            }
        } break;
        case TO(_BL): {
            if (record->event.pressed) {
                if (keymap_is_mac_system()) {
                    rgb_matrix_blink_set_remain_time(HS_RGB_BLINK_INDEX_MAC, 0);
                    rgb_matrix_blink_set_interval_times(HS_RGB_BLINK_INDEX_WIN, 250, 3);
                    rgb_matrix_blink_set(HS_RGB_BLINK_INDEX_WIN);
                    set_single_persistent_default_layer(_BL);
                    layer_move(0);
                }
            }

            return false;
        } break;
        case TO(_MBL): {
            if (record->event.pressed) {
                if (!keymap_is_mac_system()) {
                    rgb_matrix_blink_set_remain_time(HS_RGB_BLINK_INDEX_WIN, 0);
                    rgb_matrix_blink_set_interval_times(HS_RGB_BLINK_INDEX_MAC, 250, 3);
                    rgb_matrix_blink_set(HS_RGB_BLINK_INDEX_MAC);
                    set_single_persistent_default_layer(_MBL);
                    layer_move(0);
                }
            }

            return false;
        } break;
        case RP_P1: {
            if (record->event.pressed) {
                rgbrec_end(confinfo.record_channel);
                confinfo.record_channel = 1;
                rgbrec_read_current_channel(confinfo.record_channel);
                eeconfig_confinfo_update();
                rgbrec_show(confinfo.record_channel);
                ind_set_blink(ind_state_none);
            }

            return false;
        } break;
        case RP_P2: {
            if (record->event.pressed) {
                rgbrec_end(confinfo.record_channel);
                confinfo.record_channel = 2;
                rgbrec_read_current_channel(confinfo.record_channel);
                eeconfig_confinfo_update();
                rgbrec_show(confinfo.record_channel);
                ind_set_blink(ind_state_none);
            }

            return false;
        } break;
        case RP_END: {
            if (record->event.pressed) {
                if (rgb_matrix_get_mode() != RGB_MATRIX_CUSTOM_RGBR_PLAY) {

                    return false;
                }
                if (!rgbrec_is_started()) {
                    rgbrec_start(confinfo.record_channel);
                    no_record_fg = false;
                    rgbrec_set_close_all(HSV_BLACK);
                    ind_set_blink(ind_state_blinkon);
                } else {
                    rgbrec_end(confinfo.record_channel);
                    ind_set_blink(ind_state_none);
                }
                dprintf("confinfo.record_last_mode = %d\r\n", confinfo.record_last_mode);
            }

            return false;
        } break;
        case RM_NEXT: {
            if (record->event.pressed) {
                if (rgb_matrix_get_mode() == RGB_MATRIX_CUSTOM_RGBR_PLAY) {
                    if (rgbrec_is_started()) {
                        rgbrec_read_current_channel(confinfo.record_channel);
                        rgbrec_end(confinfo.record_channel);
                        no_record_fg = false;
                    }
                    if (confinfo.record_last_mode != 0xFF)
                        rgb_matrix_mode(confinfo.record_last_mode);
                    else
                        rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
                    eeconfig_confinfo_update();
                    dprintf("confinfo.record_last_mode = %d\r\n", confinfo.record_last_mode);
                    start_hsv = rgb_matrix_get_hsv();
                    return false;
                }
                record_rgbmatrix_increase(&(confinfo.record_last_mode));
                eeconfig_confinfo_update();
                start_hsv = rgb_matrix_get_hsv();
            }

            return false;
        } break;
        case RM_HUEU: {
            if (record->event.pressed) {
                record_color_hsv(true);
            }

            return false;
        } break;
        case KC_LCMD: {
            if (keymap_is_mac_system()) {
                if (keymap_config.no_gui && !rgbrec_is_started()) {
                    if (record->event.pressed) {
                        register_code16(KC_LCMD);
                    } else {
                        unregister_code16(KC_LCMD);
                    }
                }
            }

            return true;
        } break;
        case KC_RCMD: {
            if (keymap_is_mac_system()) {
                if (keymap_config.no_gui && !rgbrec_is_started()) {
                    if (record->event.pressed) {
                        register_code16(KC_RCMD);
                    } else {
                        unregister_code16(KC_RCMD);
                    }
                }
            }

            return true;
        } break;

        case HS_BATQ: {
            extern bool rk_bat_req_flag;
            if (record->event.pressed) {
                rk_bat_req_flag = record->event.pressed;
                rgb_matrix_enable();
                writePin(LED_POWER_EN_PIN, RGB_DRIVER_EN_STATE);
            } else {
                rk_bat_req_flag = record->event.pressed;
                if (!confinfo.hs_RM_TOGG) {
                    rgb_matrix_disable();
                    writePin(LED_POWER_EN_PIN, !RGB_DRIVER_EN_STATE);
                }
            }
            return false;
        } break;
        case HS_SIRI: {
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_SPC);
                wait_ms(20);
            } else {
                unregister_code(KC_SPC);
                unregister_code(KC_LCMD);
            }
            return false;
        } break;
        case HS_TASK: {
            if (record->event.pressed) {
                register_code16(KC_LALT);
                register_code16(KC_TAB);
            } else {
                unregister_code16(KC_LALT);
                unregister_code16(KC_TAB);
            }
            return false;
        } break;
        case HS_VOICE: {
            if (record->event.pressed) {
                register_code16(KC_LGUI);
                register_code16(KC_H);
            } else {
                unregister_code16(KC_LGUI);
                unregister_code16(KC_H);
            }
            return false;
        } break;
        case HS_DKT: {
            if (record->event.pressed) {
                register_code16(KC_LGUI);
                register_code16(KC_D);
            } else {
                unregister_code16(KC_LGUI);
                unregister_code16(KC_D);
            }
            return false;
        } break;
        case KC_MCTL: {
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_UP);

            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_UP);
            }
            return false;
        } break;
        case KC_APP:{
            if ((!keymap_is_mac_system() && keymap_config.no_gui)) return false;
        }break;
        case RM_TOGG: {
            if (record->event.pressed) {
                confinfo.hs_RM_TOGG = !confinfo.hs_RM_TOGG;
                if (confinfo.hs_RM_TOGG) {
                    hs_RM_TOGG_flag = false;
                    writePin(LED_POWER_EN_PIN, RGB_DRIVER_EN_STATE);
                    rgb_matrix_enable();
                } else {
                    rgb_matrix_disable();
                    writePin(LED_POWER_EN_PIN, !RGB_DRIVER_EN_STATE);
                }
                eeconfig_confinfo_update();
            }
            return false;
        } break;

        default:
            break;
    }

    return true;
}

void housekeeping_task_user(void) { // loop
    uint8_t hs_now_mode;
    static uint32_t hs_current_time;

    charging_state = readPin(HS_BAT_CABLE_PIN);

    bat_full_flag = readPin(BAT_FULL_PIN);

    if (charging_state && (bat_full_flag)) {
        hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING_DONE;
    } else if (charging_state) {
        hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING;
    } else {
        hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING_STOP;
    }

    if (!hs_current_time || timer_elapsed32(hs_current_time) > 1000) {

        hs_current_time = timer_read32();
        md_send_devctrl(hs_now_mode);
        md_send_devctrl(MD_SND_CMD_DEVCTRL_INQVOL);
    }

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
        if (confinfo.devs > 0 && confinfo.devs < 4) confinfo.last_btdevs = confinfo.devs;
        if (new_devs == DEVS_2G4) confinfo.last_btdevs = 0;
        eeconfig_confinfo_update();
    }

    if (!reset && (wireless_get_current_devs() == new_devs &&  *md_getp_state() == MD_STATE_CONNECTED)) return;

    switch (new_devs) {
        case DEVS_BT1: {
            if (reset) {
                rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_BT1, (RGB){HS_LBACK_COLOR_BT1}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_BT1, (RGB){HS_PAIR_COLOR_BT1}, 500, 1);
            }
        } break;
        case DEVS_BT2: {
            if (reset) {
                rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_BT2, (RGB){HS_LBACK_COLOR_BT2}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_BT2, (RGB){HS_PAIR_COLOR_BT2}, 500, 1);
            }
        } break;
        case DEVS_BT3: {
            if (reset) {
                rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_BT3, (RGB){HS_LBACK_COLOR_BT3}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_BT3, (RGB){HS_PAIR_COLOR_BT3}, 500, 1);
            }
        } break;
        case DEVS_BT4: {
            if (reset) {
                rgb_matrix_wls_indicator_set(41, (RGB){RGB_BLUE}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(41, (RGB){RGB_BLUE}, 500, 1);
            }
        } break;
        case DEVS_BT5: {
            if (reset) {
                rgb_matrix_wls_indicator_set(42, (RGB){RGB_BLUE}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(42, (RGB){RGB_BLUE}, 500, 1);
            }
        } break;
        case DEVS_2G4: {
            if (reset) {
                rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_2G4, (RGB){HS_LBACK_COLOR_2G4}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_2G4, (RGB){HS_PAIR_COLOR_2G4}, 500, 1);
            }
        } break;
        default:
            break;
    }
}

bool rgb_matrix_wls_indicator_cb(void) {

    if (*md_getp_state() != MD_STATE_CONNECTED) {
        if (!(wireless_get_current_devs() == DEVS_USB && USB_DRIVER.state == USB_ACTIVE)) wireless_devs_change_kb(wireless_get_current_devs(), wireless_get_current_devs(), wls_rgb_indicator_reset);
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
            rgb_matrix_set_color(wls_rgb_indicator_index, wls_rgb_indicator_rgb.g, wls_rgb_indicator_rgb.r, wls_rgb_indicator_rgb.b);
        } else {
            rgb_matrix_set_color(wls_rgb_indicator_index, 0x00, 0x00, 0x00);
        }
    }
}
#    endif

#endif

bool hs_reset_settings_user(void) {
    rgb_matrix_blink_set_color(RGB_MATRIX_BLINK_INDEX_ALL, WIITE_B, WIITE_B, WIITE_B);
    rgb_matrix_blink_set_interval_times(RGB_MATRIX_BLINK_INDEX_ALL, 250, 3);
    rgb_matrix_blink_set(RGB_MATRIX_BLINK_INDEX_ALL);

    return true;
}

uint8_t hs_color_flag;
uint32_t hs_color_time;

void hs_blink_rgb_matrix(uint8_t r, uint8_t g, uint8_t b) {
    int i;
    for(i = 0;i < RGB_MATRIX_LED_COUNT;i++){
        rgb_matrix_set_color(i, r,g,b);
    }
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {

    if (test_white_light_flag) {
        RGB rgb_test_open = hsv_to_rgb((HSV){.h = 0, .s = 0, .v = RGB_MATRIX_VAL_STEP * 5});
        rgb_matrix_set_color_all(rgb_test_open.r, rgb_test_open.g, rgb_test_open.b);

        return false;
    }

    if (Mode_Query) {
        if (hs_RM_TOGG_flag) {
            rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        }
        if (wireless_get_current_devs() == DEVS_BT1) {
            rgb_matrix_set_color(HS_RGB_BLINK_INDEX_BT1, 0xff,0xff,0xff);
        } else if (wireless_get_current_devs() == DEVS_BT2) {
            rgb_matrix_set_color(HS_RGB_BLINK_INDEX_BT2, 0xff,0xff,0xff);
        } else if (wireless_get_current_devs() == DEVS_BT3) {
            rgb_matrix_set_color(HS_RGB_BLINK_INDEX_BT3, 0xff,0xff,0xff);
        } else if (wireless_get_current_devs() == DEVS_2G4) {
            rgb_matrix_set_color(HS_RGB_BLINK_INDEX_2G4, 0xff,0xff,0xff);
        } else if (wireless_get_current_devs() == DEVS_USB) {
            rgb_matrix_set_color(HS_RGB_BLINK_INDEX_USB, 0xff,0xff,0xff);
        }

        if (keymap_is_mac_system()) {
            rgb_matrix_set_color(HS_RGB_BLINK_INDEX_MAC, 0xff,0xff,0xff);
        } else {
            rgb_matrix_set_color(HS_RGB_BLINK_INDEX_WIN, 0xff,0xff,0xff);
        }

        if (!rgbrec_is_started() && host_keyboard_led_state().caps_lock){
            rgb_matrix_set_color(HS_RGB_INDEX_CAP_LOCK, 0xff,0xff,0xff);
        }

        if (!rgbrec_is_started() && !keymap_is_mac_system() && keymap_config.no_gui)
            rgb_matrix_set_color(HS_RGB_INDEX_WIN_LOCK, 0xff,0xff,0xff);

        query();
    } else {
        if (rgb_matrix_get_val() >= RGB_MATRIX_VAL_STEP) {
            if (!rgbrec_is_started() && host_keyboard_led_state().caps_lock){
                rgb_matrix_set_color(HS_RGB_INDEX_CAP_LOCK, 0xff,0xff,0xff);
            }

            if (!rgbrec_is_started() && !keymap_is_mac_system() && keymap_config.no_gui)
                rgb_matrix_set_color(HS_RGB_INDEX_WIN_LOCK, 0xff,0xff,0xff);
        }
    }

    if (ee_clr_timer && timer_elapsed32(ee_clr_timer) > 3000) {
        hs_reset_settings();
        ee_clr_timer = 0;
    }

#ifdef RGBLIGHT_ENABLE
    if (rgb_matrix_indicators_advanced_rgblight(led_min, led_max) != true) {

        return false;
    }
#endif

#ifdef WIRELESS_ENABLE
    rgb_matrix_wls_indicator();

#endif

    if(hs_color_test == true && hs_frequency_test == false) {
        if ((timer_elapsed32(hs_color_time) > 4000)) {
            hs_color_time = timer_read32();
            hs_color_flag ++;
        }

        switch (hs_color_flag)
        {
            case 0:
                hs_blink_rgb_matrix(WIITE_B, 0x00, 0x00);
                break;
            case 1:
                hs_blink_rgb_matrix(0x00, WIITE_B, 0x00);
                break;
            case 2:
                hs_blink_rgb_matrix(0x00, 0x00, WIITE_B);
                break;
            case 3:
                hs_blink_rgb_matrix(WIITE_B, WIITE_B, WIITE_B);
                break;

            default:
                hs_color_test = false;
                break;
        }
    }
    rgb_matrix_blink_task(led_min, led_max);

    return true;
}

void hs_reset_settings(void) {
    eeconfig_init();
    eeconfig_update_rgb_matrix_default();
    extern uint32_t suspend_timer;
    suspend_timer = 0;
#ifdef RGBLIGHT_ENABLE
    extern void rgblight_init(void);
    is_rgblight_initialized = false;
    rgblight_init();
    eeconfig_update_rgblight_default();
    rgblight_enable();
#endif

    keymap_config.raw = eeconfig_read_keymap();

    #if defined(WIRELESS_ENABLE)
        wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);
    #endif

    if (hs_reset_settings_user() != true) {

        return;
    }
    hs_rgb_blink_set_timer(timer_read32());
    keyboard_post_init_kb();
}

void lpwr_wakeup_hook(void) { // WAKEUP
    hs_mode_scan(false, confinfo.devs, confinfo.last_btdevs);

    if (rgb_matrix_get_val() != 0 && hs_get_rgb_enable())
        gpio_write_pin_high(LED_POWER_EN_PIN);
    else
        gpio_write_pin_low(LED_POWER_EN_PIN);

    gpio_write_pin_high(HS_LED_BOOSTING_PIN);

    if (confinfo.hs_RM_TOGG) {
        hs_RM_TOGG_flag = false;
        writePin(LED_POWER_EN_PIN, RGB_DRIVER_EN_STATE);
    } else {
        writePin(LED_POWER_EN_PIN, !RGB_DRIVER_EN_STATE);
    }
}

void matrix_init_user(void) {

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (matrix_is_on(row, col)) {

	            if (row == 5 && col == 0) {
                    hs_color_test = true;
                }

                if (row == 0 && col == 0) {

                    hs_frequency_test = true;
                }
            }
        }
    }
}
