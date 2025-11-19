// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "control/control.h"
#include "rgb_record/rgb_record.h"
#include "rgb_record/rgb_rgblight.h"


#ifdef WIRELESS_ENABLE
#    include "wireless.h"
#    include "usb_main.h"
#    include "lowpower.h"
#endif

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1;
        uint8_t devs : 3;
        uint8_t record_channel : 4;
        uint8_t record_last_mode;
        uint8_t last_btdevs : 3;
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
    _DEFA
};

hs_rgb_indicator_t hs_rgb_indicators[HS_RGB_INDICATOR_COUNT];
hs_rgb_indicator_t hs_rgb_bat[HS_RGB_BAT_COUNT];

void rgb_blink_dir(void);
void hs_reset_settings(void);
void rgb_matrix_hs_indicator(void);
void rgb_matrix_hs_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times);
void rgb_matrix_hs_set_remain_time(uint8_t index, uint8_t remain_time);


#define keymap_is_mac_system() (get_highest_layer(default_layer_state) == _MBL)

uint32_t post_init_timer = 0x00;
bool inqbat_flag         = false;
bool mac_status          = false;
bool charging_state      = false;
bool bat_full_flag       = false;
bool enable_bat_indicators = true;
uint32_t bat_indicator_cnt = true;
static uint32_t ee_clr_timer = 0;
static uint32_t rec_time;
static bool rec_filp;
bool test_white_light_flag = false;
HSV start_hsv;
bool no_record_fg;
bool lower_sleep = false;
uint8_t buff[] = {14, 8, 2, 1, 1, 1, 1, 1, 1, 1, 0};

void eeconfig_confinfo_update(uint32_t raw) {

    eeconfig_update_kb(raw);
}

uint32_t eeconfig_confinfo_read(void) {

    return eeconfig_read_kb();
}

void eeconfig_confinfo_default(void) {

    confinfo.flag             = true;
    confinfo.record_channel   = 0;
    confinfo.record_last_mode = 0xff;
    confinfo.last_btdevs = 1;
#ifdef WIRELESS_ENABLE
    confinfo.devs = DEVS_USB;
#endif

    eeconfig_init_user_datablock();
    eeconfig_confinfo_update(confinfo.raw);
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

void lpwr_stop_hook_pre(void){

    gpio_write_pin_low(LED_POWER_EN_PIN);

#ifdef HS_LED_BOOSTING_PIN
    gpio_write_pin_low(HS_LED_BOOSTING_PIN);
#endif

    if (lower_sleep){
        md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
        wait_ms(200);
        lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_UART);
    }
}

void lpwr_wakeup_hook(void){
    hs_mode_scan(false,confinfo.devs,confinfo.last_btdevs);

    gpio_write_pin_high(LED_POWER_EN_PIN);
#ifdef HS_LED_BOOSTING_PIN
    gpio_write_pin_high(HS_LED_BOOSTING_PIN);
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

#ifdef HS_LED_BOOSTING_PIN
    gpio_set_pin_output(HS_LED_BOOSTING_PIN);
    gpio_write_pin_high(HS_LED_BOOSTING_PIN);
#endif

#ifdef MM_BT_DEF_PIN
    setPinInputHigh(MM_BT_DEF_PIN);
#endif

#ifdef MM_2G4_DEF_PIN
    setPinInputHigh(MM_2G4_DEF_PIN);
#endif

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

#ifdef WIRELESS_ENABLE
    wireless_init();
#if !(defined(MM_BT_DEF_PIN) && defined(MM_2G4_DEF_PIN))
    wireless_devs_change(!confinfo.devs, confinfo.devs, false);
#endif
    post_init_timer = timer_read32();
#endif

    keyboard_post_init_user();

    rgbrec_init(confinfo.record_channel);

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
        wireless_devs_change(!confinfo.devs, confinfo.devs, false);
        post_init_timer = 0x00;
    }
    hs_mode_scan(false,confinfo.devs,confinfo.last_btdevs);
}

uint32_t wls_process_long_press(uint32_t trigger_time, void *cb_arg) {
    uint16_t keycode = *((uint16_t *)cb_arg);

    switch (keycode) {
        case KC_BT1: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode,confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT1, true);
            }
        } break;
        case KC_BT2: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode,confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, true);
            }
        } break;
        case KC_BT3: {
             uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode,confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT3, true);
            }
        } break;
        case KC_2G4: {
             uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode,confinfo.last_btdevs);
            if ((mode == hs_2g4) || (mode == hs_wireless) || (mode == hs_none)) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, true);
            }
        } break;
        case EE_CLR: {

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

	#    define WLS_KEYCODE_EXEC(wls_dev)                                                                                      \
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
        case KC_BT1: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode,confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_BT1);
                hs_rgb_blink_set_timer(timer_read32());
            }

        } break;
        case KC_BT2: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode,confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_BT2);
                hs_rgb_blink_set_timer(timer_read32());
            }
        } break;
        case KC_BT3: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode,confinfo.last_btdevs);
            if ((mode == hs_bt) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_BT3);
                hs_rgb_blink_set_timer(timer_read32());
            }
        } break;
        case KC_2G4: {
            uint8_t mode = confinfo.devs;
            hs_modeio_detection(true, &mode,confinfo.last_btdevs);
            if ((mode == hs_2g4) || (mode == hs_wireless) || (mode == hs_none)) {
                WLS_KEYCODE_EXEC(DEVS_2G4);
                hs_rgb_blink_set_timer(timer_read32());
            }
        } break;
        case KC_USB: {
            if (record->event.pressed) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);
            }
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

    if (*md_getp_state() == MD_STATE_CONNECTED){
        hs_rgb_blink_set_timer(timer_read32());
    }

    switch (keycode) {
        case MO(_FL):
        case MO(_MFL): {
            if (!record->event.pressed && rgbrec_is_started()) {
                if (no_record_fg == true) {
                    no_record_fg = false;
                    rgbrec_register_record(keycode, record);
                }
                no_record_fg = true;
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
    HSV rgb = rgblight_get_hsv();
    uint8_t mode = rgblight_get_mode();
    static uint8_t current_mode = 0;

    if (mode == 1) {
        current_mode = (rgb.h == 0 && rgb.s != 0) ? 3 : 9;

        switch (rgb.h) {
            case 40: current_mode = 4; break;
            case 80: current_mode = 5; break;
            case 120: current_mode = 6; break;
            case 160: current_mode = 7; break;
            case 200: current_mode = 8; break;
            default: break;
        }
    }

    current_mode = (current_mode + 1) % 11;

    if (current_mode == 10) {
        rgblight_sethsv(0, 255, rgb.v);
        rgblight_disable();
    } else {
        rgblight_enable();
        rgblight_mode(buff[current_mode]);
    }

    switch (current_mode) {
        case 3:  rgblight_sethsv(0, 255, rgb.v); break;
        case 4:  rgblight_sethsv(40, 255, rgb.v); break;
        case 5:  rgblight_sethsv(80, 255, rgb.v); break;
        case 6:  rgblight_sethsv(120, 255, rgb.v); break;
        case 7:  rgblight_sethsv(160, 255, rgb.v); break;
        case 8:  rgblight_sethsv(200, 255, rgb.v); break;
        case 9:  rgblight_sethsv(0, 0, rgb.v); break;
        case 0:  rgblight_set_speed(255); break;
        default: rgblight_set_speed(200); break;
    }
}


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
        case KC_TILD:{
            if (record->event.pressed){
                register_code(KC_LSFT);
                register_code(KC_GRV);
            }else{
                unregister_code(KC_LSFT);
                unregister_code(KC_GRV);
            }
            return false;
            break;
        }
        case QK_BOOT: {
            if (record->event.pressed) {
                dprintf("into boot!!!\r\n");
                eeconfig_disable();
                bootloader_jump();
            }
        } break;
        case KC_TEST: {
            if (rgbrec_is_started()) {

                return false;
            }
            if (record->event.pressed) {
                test_white_light_flag = true;
            }
            return false;
        } break;
        case NK_TOGG: {
            if (rgbrec_is_started()) {

                return false;
            }
            if (record->event.pressed) {
                rgb_matrix_hs_indicator_set(0xFF, (RGB){0x00, 0x6E, 0x00}, 250, 1);
            }
        } break;
        case RL_MOD: {
            if (rgbrec_is_started()) {

                return false;
            }
            if (record->event.pressed) {
                im_rgblight_increase();
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
                if (rgb_matrix_get_speed() >= (RGB_MATRIX_SPD_STEP * 5)) {
                    rgb_blink_dir();
                }
            }
        } break;
        case RM_SPDD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() <= RGB_MATRIX_SPD_STEP) {
                    rgb_blink_dir();
                    rgb_matrix_set_speed(RGB_MATRIX_SPD_STEP);

                    return false;
                }
            }
        } break;
        case RM_VALU: {
            if (record->event.pressed) {
                if (rgb_matrix_get_val() >= (RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP)) {
                    rgb_blink_dir();
                    start_hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                }
                else{
                    start_hsv.v = rgb_matrix_get_val() + RGB_MATRIX_VAL_STEP;
                }
            }
        } break;
        case RM_VALD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_val() <= RGB_MATRIX_VAL_STEP) {
                    rgb_blink_dir();
                    for(uint8_t i = 0; i < RGB_MATRIX_LED_COUNT - RGBLED_NUM;i++){
                        rgb_matrix_set_color(i,0,0,0);
                    }
                    start_hsv.v = 0;
                }
                else{
                    start_hsv.v = rgb_matrix_get_val() - RGB_MATRIX_VAL_STEP;
                }
            }
        } break;
        case TO(_BL): {
            if (record->event.pressed) {
                rgb_matrix_hs_set_remain_time(HS_RGB_BLINK_INDEX_MAC, 0);
                rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_WIN, (RGB){RGB_WHITE}, 250, 3);
                if (keymap_is_mac_system()) {
                    set_single_persistent_default_layer(_BL);
                    layer_move(0);
                }
            }

            return false;
        } break;
        case TO(_MBL): {
            if (record->event.pressed) {
                rgb_matrix_hs_set_remain_time(HS_RGB_BLINK_INDEX_WIN, 0);
                rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_MAC, (RGB){RGB_WHITE}, 250, 3);
                if (!keymap_is_mac_system()) {
                    set_single_persistent_default_layer(_MBL);
                    layer_move(0);
                }
            }

            return false;
        } break;
        case RP_P0: {
            if (record->event.pressed) {
                confinfo.record_channel = 0;
                rgbrec_read_current_channel(confinfo.record_channel);
                rgbrec_end(confinfo.record_channel);
                eeconfig_confinfo_update(confinfo.raw);
                rgbrec_show(confinfo.record_channel);
                dprintf("confinfo.record_last_mode = %d\r\n", confinfo.record_last_mode);
            }

            return false;
        } break;
        case RP_P1: {
            if (record->event.pressed) {
                confinfo.record_channel = 1;
                rgbrec_read_current_channel(confinfo.record_channel);
                rgbrec_end(confinfo.record_channel);
                eeconfig_confinfo_update(confinfo.raw);
                rgbrec_show(confinfo.record_channel);
            }

            return false;
        } break;
        case RP_P2: {
            if (record->event.pressed) {
                confinfo.record_channel = 2;
                rgbrec_read_current_channel(confinfo.record_channel);
                rgbrec_end(confinfo.record_channel);
                eeconfig_confinfo_update(confinfo.raw);
                rgbrec_show(confinfo.record_channel);
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
                    rec_time     = timer_read32();
                    rgbrec_set_close_all(HSV_BLACK);
                } else {
                    rec_time = 0;
                    rgbrec_end(confinfo.record_channel);
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
                    eeconfig_confinfo_update(confinfo.raw);
                    dprintf("confinfo.record_last_mode = %d\r\n", confinfo.record_last_mode);
                    start_hsv = rgb_matrix_get_hsv();
                    return false;
                }
                record_rgbmatrix_increase(&(confinfo.record_last_mode));
                eeconfig_confinfo_update(confinfo.raw);
                start_hsv = rgb_matrix_get_hsv();
            }

            return false;
        } break;
        case RM_HUEU: {
            if (record->event.pressed) {
                record_color_hsv(true);
                start_hsv = rgb_matrix_get_hsv();
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
            rk_bat_req_flag = (confinfo.devs != DEVS_USB) && record->event.pressed;
            return false;
        } break;
        default:
            break;
    }

    return true;
}

void housekeeping_task_user(void) {
    uint8_t hs_now_mode;
    static uint32_t hs_current_time;
    static bool val_value = false;

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

    if (charging_state){
#ifdef HS_LED_BOOSTING_PIN
         writePin(HS_LED_BOOSTING_PIN,0);
#endif
         if(!val_value){
            rgb_matrix_sethsv_noeeprom(start_hsv.h,start_hsv.s,150);
         }
         val_value = true;

    }
    else{
#ifdef HS_LED_BOOSTING_PIN
        writePin(HS_LED_BOOSTING_PIN,1);
#endif
        if(val_value){
            rgb_matrix_sethsv(start_hsv.h,start_hsv.s,start_hsv.v);
        }
        val_value = false;
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
        eeconfig_confinfo_update(confinfo.raw);
    }

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
        case DEVS_2G4: {
            if (reset) {
                rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_2G4, (RGB){HS_LBACK_COLOR_2G4}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(HS_RGB_BLINK_INDEX_2G4, (RGB){HS_LBACK_COLOR_2G4}, 500, 1);
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

void rgb_matrix_hs_bat_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times) {
    for (int i = 0; i < HS_RGB_BAT_COUNT; i++) {
        if (!hs_rgb_bat[i].active) {
            hs_rgb_bat[i].active = true;
            hs_rgb_bat[i].timer = timer_read32();
            hs_rgb_bat[i].interval = interval;
            hs_rgb_bat[i].times = times * 2;
            hs_rgb_bat[i].index = index;
            hs_rgb_bat[i].rgb = rgb;
            break;
        }
    }
}

void rgb_matrix_hs_bat(void) {
    for (int i = 0; i < HS_RGB_BAT_COUNT; i++) {
        if (hs_rgb_bat[i].active) {
            if (timer_elapsed32(hs_rgb_bat[i].timer) >= hs_rgb_bat[i].interval) {
                hs_rgb_bat[i].timer = timer_read32();

                if (hs_rgb_bat[i].times) {
                    hs_rgb_bat[i].times--;
                }

                if (hs_rgb_bat[i].times <= 0) {
                    hs_rgb_bat[i].active = false;
                    hs_rgb_bat[i].timer = 0x00;
                }
            }

            if (hs_rgb_bat[i].times % 2) {
                rgb_matrix_set_color(hs_rgb_bat[i].index, hs_rgb_bat[i].rgb.r, hs_rgb_bat[i].rgb.g, hs_rgb_bat[i].rgb.b);
            } else {
                rgb_matrix_set_color(hs_rgb_bat[i].index, 0x00, 0x00, 0x00);
            }
        }
    }
}

void bat_indicators(void) {
    static uint32_t battery_process_time = 0;

    if (charging_state && (bat_full_flag)) {

        battery_process_time = 0;
    } else if (charging_state) {

        battery_process_time = 0;
        rgb_matrix_set_color(HS_MATRIX_BLINK_INDEX_BAT, RGB_RED);
    } else if (*md_getp_bat() <= BATTERY_CAPACITY_LOW) {

        rgb_matrix_hs_bat_set(HS_MATRIX_BLINK_INDEX_BAT, (RGB){RGB_RED}, 250, 1);

        if (*md_getp_bat() <= BATTERY_CAPACITY_STOP) {
            if (!battery_process_time) {
                battery_process_time = timer_read32();
            }

            if (battery_process_time && timer_elapsed32(battery_process_time) > 20000) {
                battery_process_time = 0;
                lower_sleep = true;
                lpwr_set_timeout_manual(false);
            }
        }
    } else {
        battery_process_time = 0;
    }
}

#    endif

#endif

void rgb_blink_dir(void) {

    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_VAI, (RGB){WIITE_B, WIITE_B, WIITE_B}, 250, 3);
    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_VAD, (RGB){WIITE_B, WIITE_B, WIITE_B}, 250, 3);
    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_SPI, (RGB){WIITE_B, WIITE_B, WIITE_B}, 250, 3);
    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_SPD, (RGB){WIITE_B, WIITE_B, WIITE_B}, 250, 3);
}

bool hs_reset_settings_user(void) {

    rgb_matrix_hs_indicator_set(0xFF, (RGB){WIITE_B,WIITE_B,WIITE_B}, 250, 3);

    return true;
}

void nkr_indicators_hook(uint8_t index) {

    if ((hs_rgb_indicators[index].rgb.r == WIITE_B) && (hs_rgb_indicators[index].rgb.g == 0x00) && (hs_rgb_indicators[index].rgb.b == 0x00)) {

        rgb_matrix_hs_indicator_set(0xFF, (RGB){WIITE_B, 0x00, 0x00}, 250, 1);

    } else if ((hs_rgb_indicators[index].rgb.r == 0x00) && (hs_rgb_indicators[index].rgb.g == 0x6E) && (hs_rgb_indicators[index].rgb.b == 0x00)) {

        rgb_matrix_hs_indicator_set(0xFF, (RGB){0x00, 0x00, WIITE_B}, 250, 1);
    }
}

void rgb_matrix_hs_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times) {

    for (int i = 0; i < HS_RGB_INDICATOR_COUNT; i++) {
        if (!hs_rgb_indicators[i].active) {
            hs_rgb_indicators[i].active   = true;
            hs_rgb_indicators[i].timer    = timer_read32();
            hs_rgb_indicators[i].interval = interval;
            hs_rgb_indicators[i].times    = times * 2;
            hs_rgb_indicators[i].index    = index;
            hs_rgb_indicators[i].rgb      = rgb;
            if (index != 0xFF)
                hs_rgb_indicators[i].blink_cb = NULL;
            else {
                hs_rgb_indicators[i].blink_cb = nkr_indicators_hook;
            }
            break;
        }
    }
}

void rgb_matrix_hs_set_remain_time(uint8_t index, uint8_t remain_time) {

    for (int i = 0; i < HS_RGB_INDICATOR_COUNT; i++) {
        if (hs_rgb_indicators[i].index == index) {
            hs_rgb_indicators[i].times  = 0;
            hs_rgb_indicators[i].active = false;
            break;
        }
    }
}

void rgb_matrix_hs_indicator(void) {

    for (int i = 0; i < HS_RGB_INDICATOR_COUNT; i++) {
        if (hs_rgb_indicators[i].active) {
            if (timer_elapsed32(hs_rgb_indicators[i].timer) >= hs_rgb_indicators[i].interval) {
                hs_rgb_indicators[i].timer = timer_read32();

                if (hs_rgb_indicators[i].times) {
                    hs_rgb_indicators[i].times--;
                }

                if (hs_rgb_indicators[i].times <= 0) {
                    hs_rgb_indicators[i].active = false;
                    hs_rgb_indicators[i].timer  = 0x00;
                    if (hs_rgb_indicators[i].blink_cb != NULL)
                        hs_rgb_indicators[i].blink_cb(i);
                    continue;
                }
            }

            if (!(hs_rgb_indicators[i].times % 2)) {
                if (hs_rgb_indicators[i].index == 0xFF) {
                    rgb_matrix_set_color_all(hs_rgb_indicators[i].rgb.r, hs_rgb_indicators[i].rgb.g, hs_rgb_indicators[i].rgb.b);
                } else {
                    rgb_matrix_set_color(hs_rgb_indicators[i].index, hs_rgb_indicators[i].rgb.r, hs_rgb_indicators[i].rgb.g, hs_rgb_indicators[i].rgb.b);
                }
            } else {
                if (hs_rgb_indicators[i].index == 0xFF) {
                    rgb_matrix_set_color_all(0x00, 0x00, 0x00);
                } else {
                    rgb_matrix_set_color(hs_rgb_indicators[i].index, 0x00, 0x00, 0x00);
                }
            }
        }
    }
}

void rgb_matrix_start_rec(void) {

    if (rgbrec_is_started()) {
        if (!rec_time || timer_elapsed32(rec_time) > 250) {
            rec_time = timer_read32();
            rec_filp = !rec_filp;
        }
        if (rec_filp) {
            rgb_matrix_set_color(0, WIITE_B, WIITE_B, WIITE_B);
            rgb_matrix_set_color(1, WIITE_B, WIITE_B, WIITE_B);
            rgb_matrix_set_color(2, WIITE_B, WIITE_B, WIITE_B);
        } else {
            rgb_matrix_set_color(0, 0x00, 0x00, 0x00);
            rgb_matrix_set_color(1, 0x00, 0x00, 0x00);
            rgb_matrix_set_color(2, 0x00, 0x00, 0x00);
        }
    } else {
        rec_time = 0;
        rec_filp = false;
    }
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    // Use default color values since rgb_matrix_ws2812_array is no longer available
    uint8_t r = 255, g = 255, b = 255;
    rgb_matrix_set_color(82, r, g, b);

    if (test_white_light_flag) {
        RGB rgb_test_open = hsv_to_rgb((HSV){.h = 0, .s = 0, .v = RGB_MATRIX_VAL_STEP * 5});
        rgb_matrix_set_color_all(rgb_test_open.r, rgb_test_open.g, rgb_test_open.b);

        return false;
    }

    if (rgb_matrix_indicators_advanced_user(led_min, led_max) != true) {

        return false;
    }

    if (ee_clr_timer && timer_elapsed32(ee_clr_timer) > 3000) {
        hs_reset_settings();
        ee_clr_timer = 0;
    }

    if ((*md_getp_state() == MD_STATE_CONNECTED) || USB_DRIVER.state == USB_ACTIVE)
    {
        if (host_keyboard_led_state().caps_lock)
            rgb_matrix_set_color(HS_RGB_INDEX_CAPS, RGB_WHITE);

        if (!keymap_is_mac_system() && keymap_config.no_gui)
            rgb_matrix_set_color(HS_RGB_INDEX_WIN_LOCK, RGB_WHITE);
    }

#ifdef RGBLIGHT_ENABLE
    if (rgb_matrix_indicators_advanced_rgblight(led_min, led_max) != true) {

        return false;
    }
#endif

    #    ifdef WIRELESS_ENABLE
    rgb_matrix_wls_indicator();

    if (enable_bat_indicators && !inqbat_flag && !rgbrec_is_started()) {
        rgb_matrix_hs_bat();
        bat_indicators();
        bat_indicator_cnt = timer_read32();
    }

    if (!enable_bat_indicators) {
        if (timer_elapsed32(bat_indicator_cnt) > 2000){
            enable_bat_indicators = true;
            bat_indicator_cnt = timer_read32();
        }
    }

    if (confinfo.devs == DEVS_USB){
        if (USB_DRIVER.state != USB_ACTIVE) {
            if(enable_bat_indicators){
                rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_USB, (RGB){HS_LBACK_COLOR_USB}, 500, 1);
            }
        }
    }

#    endif

    rgb_matrix_hs_indicator();

    query();
    return true;
}

void hs_reset_settings(void) {
    enable_bat_indicators = false;
    eeconfig_init();

#ifdef RGBLIGHT_ENABLE
    extern void rgblight_init(void);
    is_rgblight_initialized = false;
    rgblight_init();
    eeconfig_update_rgblight_default();
    rgblight_enable();
#endif

    eeconfig_update_rgb_matrix_default();
    eeconfig_read_keymap(&keymap_config);

#if defined(NKRO_ENABLE) && defined(FORCE_NKRO)
    keymap_config.nkro = 0;
    eeconfig_update_keymap(&keymap_config);
#endif

#if defined(WIRELESS_ENABLE)
    wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);
#endif

    if (hs_reset_settings_user() != true) {

        return;
    }
    hs_rgb_blink_set_timer(timer_read32());
    keyboard_post_init_kb();
}
