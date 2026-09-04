// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "wls.h"
#include "usb_main.h"

static ioline_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
extern bool state;
bool hs_modeio_detection(bool update, uint8_t *mode, uint8_t lsat_btdev) {
    static uint32_t scan_timer = 0x00;

    if ((update != true) && (timer_elapsed32(scan_timer) <= (HS_MODEIO_DETECTION_TIME))) {
        return false;
    }
    scan_timer = timer_read32();

#if defined(HS_BT_DEF_PIN) && defined(HS_2G4_DEF_PIN)
    uint8_t now_mode         = 0x00;
    uint8_t hs_mode          = 0x00;
    static uint8_t last_mode = 0x00;
    bool sw_mode             = false;
    now_mode                 = (HS_GET_MODE_PIN(HS_USB_PIN_STATE) ? 3 : (HS_GET_MODE_PIN(HS_BT_PIN_STATE) ? 1 : ((HS_GET_MODE_PIN(HS_2G4_PIN_STATE) ? 2 : 0))));
    hs_mode                  = (*mode >= DEVS_BT1 && *mode <= DEVS_BT5) ? 1 : ((*mode == DEVS_2G4) ? 2 : ((*mode == DEVS_USB) ? 3 : 0));
    sw_mode                  = ((update || (last_mode == now_mode)) && (hs_mode != now_mode)) ? true : false;
    last_mode                = now_mode;

    switch (now_mode) {
        case 1:
            *mode = hs_bt;
            if (sw_mode) {
                wireless_devs_change(wireless_get_current_devs(), lsat_btdev, false);
            }
            break;
        case 2:
            *mode = hs_2g4;
            if (sw_mode) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, false);
            }
            break;
        case 3:
            *mode = hs_usb;
            if (sw_mode)
                wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);

            break;
        default:
            break;
    }

    if (sw_mode) {
        hs_rgb_blink_set_timer(timer_read32());
        suspend_wakeup_init();
        return true;
    }
#else
    *mode = hs_none;
#endif

    return false;
}

static uint32_t hs_linker_rgb_timer = 0x00;

bool hs_mode_scan(bool update, uint8_t moude, uint8_t lsat_btdev) {

    if (hs_modeio_detection(update, &moude, lsat_btdev)) {

        return true;
    }
    hs_rgb_blink_hook();
    return false;
}

void hs_rgb_blink_set_timer(uint32_t time) {
    hs_linker_rgb_timer = time;
}

uint32_t hs_rgb_blink_get_timer(void) {
    return hs_linker_rgb_timer;
}

bool hs_rgb_blink_hook() {
    static uint8_t last_status;
    uint32_t timeout = 0;
    static bool hs_connect = false;

    if (last_status != *md_getp_state()) {
        last_status = *md_getp_state();
        hs_rgb_blink_set_timer(0x00);
    }

    switch (hs_get_sleep_timeout()) {
        case hs_sleep_timeout_none: {
            timeout = 0;
        } break;
        case hs_sleep_timeout_1min: {
            timeout = 1 * 60000;
        } break;
        case hs_sleep_timeout_3min: {
            timeout = 3 * 60000;
        } break;
        case hs_sleep_timeout_5min: {
            timeout = 5 * 60000;
        } break;
        case hs_sleep_timeout_10min: {
            timeout = 10 * 60000;
        } break;
        case hs_sleep_timeout_20min: {
            timeout = 20 * 60000;
        } break;
        case hs_sleep_timeout_30min: {
            timeout = 30 * 60000;
        } break;
        case hs_sleep_timeout_vendor: {
            timeout = HS_SLEEP_TIMEOUT;
        } break;
    }

    if (wireless_get_current_devs() == DEVS_USB && USB_DRIVER.state == USB_ACTIVE) {
        hs_rgb_blink_set_timer(0x00);
        return true;
    }

    switch (*md_getp_state()) {
        case MD_STATE_NONE: {
            hs_rgb_blink_set_timer(0x00);
        } break;

        case MD_STATE_DISCONNECTED:{
            if (hs_rgb_blink_get_timer() == 0x00) {
                hs_rgb_blink_set_timer(timer_read32());
                if (hs_connect) {
                    hs_connect = false;
                    extern void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset);
                    wireless_devs_change_kb(wireless_get_current_devs(), wireless_get_current_devs(), false);
                }
            } else {
                if (!state){
                    if ((timer_elapsed32(hs_rgb_blink_get_timer()) >= HS_LBACK_TIMEOUT) && !rgbrec_is_started()) {
                        hs_rgb_blink_set_timer(timer_read32());
                        md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
                        wait_ms(200);
                        lpwr_set_timeout_manual(true);
                    }
                }
                else{
                    if ((timer_elapsed32(hs_rgb_blink_get_timer()) >= HS_PAIR_TIMEOUT) && !rgbrec_is_started()) {
                        hs_rgb_blink_set_timer(timer_read32());
                        md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
                        wait_ms(200);
                        lpwr_set_timeout_manual(true);
                    }
                }
            }
        } break;
        case MD_STATE_CONNECTED:{
            hs_connect = true;
            if (hs_rgb_blink_get_timer() == 0x00) {
                hs_rgb_blink_set_timer(timer_read32());
            } else {
                if (timer_elapsed32(hs_rgb_blink_get_timer()) >= timeout && !rgbrec_is_started()) {
                    hs_rgb_blink_set_timer(timer_read32());
                    // clear_keyboard();
                    lpwr_set_timeout_manual(true);
                }
            }
        } break;

        case MD_STATE_PAIRING:{
            if (hs_rgb_blink_get_timer() == 0x00) {
                hs_rgb_blink_set_timer(timer_read32());

            } else {
                uint32_t hs_pair_timer = HS_PAIR_TIMEOUT;
                if (wireless_get_current_devs() == DEVS_2G4) {
                    hs_pair_timer = HS_PAIR_TIMEOUT1;
                } else if (wireless_get_current_devs() == DEVS_BT1 || wireless_get_current_devs() == DEVS_BT2 || wireless_get_current_devs() == DEVS_BT3){
                    hs_pair_timer = HS_PAIR_TIMEOUT;
                }

                if (timer_elapsed32(hs_rgb_blink_get_timer()) >= hs_pair_timer && !rgbrec_is_started()) {
                    hs_rgb_blink_set_timer(timer_read32());
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
                    wait_ms(200);
                    lpwr_set_timeout_manual(true);
                }
            }
        } break;
        default:break;
    }
    return true;
}

void lpwr_exti_init_hook(void) {

#ifdef HS_BT_DEF_PIN
    gpio_set_pin_input_high(HS_BT_DEF_PIN);
    waitInputPinDelay();
    palEnableLineEvent(HS_BT_DEF_PIN, PAL_EVENT_MODE_BOTH_EDGES);
#endif

#ifdef HS_2G4_DEF_PIN
    gpio_set_pin_input_high(HS_2G4_DEF_PIN);
    waitInputPinDelay();
    palEnableLineEvent(HS_2G4_DEF_PIN, PAL_EVENT_MODE_BOTH_EDGES);
#endif

#ifdef BAT_FULL_PIN
    gpio_set_pin_input_high(BAT_FULL_PIN);
    waitInputPinDelay();
    palEnableLineEvent(BAT_FULL_PIN, PAL_EVENT_MODE_FALLING_EDGE);
#endif

    if (lower_sleep) {
#if DIODE_DIRECTION == ROW2COL
        for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); i++) {
            if (col_pins[i] != NO_PIN) {
                gpio_set_pin_output(col_pins[i]);
                gpio_write_pin_high(col_pins[i]);
            }
        }
#endif
    }

    gpio_set_pin_input(HS_BAT_CABLE_PIN);
    waitInputPinDelay();
    palEnableLineEvent(HS_BAT_CABLE_PIN, PAL_EVENT_MODE_RISING_EDGE);
    palEnableLineEvent(A12,PAL_EVENT_MODE_RISING_EDGE);
    nvicEnableVector(USBP_WKUP_IRQn,6);
}

void palcallback_cb(uint8_t line) {
    switch (line) {
        case(18):{
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_USB);
        }break;
        case PAL_PAD(HS_BAT_CABLE_PIN): {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_CABLE);
        } break;
#ifdef HS_BT_DEF_PIN
        case PAL_PAD(HS_2G4_DEF_PIN): {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_SWITCH);
        } break;
#endif

#ifdef HS_2G4_DEF_PIN
        case PAL_PAD(HS_BT_DEF_PIN): {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_SWITCH);
        } break;
#endif
        default: {

        } break;
    }
}

void lpwr_stop_hook_pre(void) { // wireless sleep

#ifdef LED_POWER_EN_PIN
    gpio_write_pin_low(LED_POWER_EN_PIN);
#endif

#ifdef HS_LED_BOOSTING_PIN
    gpio_write_pin_low(HS_LED_BOOSTING_PIN);
#endif

#ifdef LED_WIN_PIN
    gpio_write_pin_low(LED_WIN_PIN);
#endif

#ifdef LED_CAPS_PIN
    gpio_write_pin_low(LED_CAPS_PIN);
#endif


    state = false;
    if (lower_sleep) {
        md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
        wait_ms(200);
        lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_UART);
    }
}

void lpwr_stop_hook_post(void) {
    if (lower_sleep) {
        switch (lpwr_get_sleep_wakeupcd()) {
            case LPWR_WAKEUP_USB:
            case LPWR_WAKEUP_CABLE: {
                lower_sleep = false;
                lpwr_set_state(LPWR_WAKEUP);
            } break;
            default: {
                lpwr_set_state(LPWR_STOP);
            } break;
        }
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id = &(data[0]);
    uint8_t *value_id   = &(data[2]);
    uint8_t *value_data = &(data[3]);

    hs_rgb_blink_set_timer(timer_read32());

    switch (*command_id) {
        case id_custom_get_value: {
            switch (*value_id) {
                case id_sleep_timeout: {
                    value_data[0] = hs_get_sleep_timeout();
                } break;
                case id_rgbrec_channel: {
                    value_data[0] = (uint8_t)RGBREC_CHANNEL_NUM;
                } break;
                case id_rgbrec_hs_data: {
                    uint16_t hs = rgbrec_get_hs_data(value_data[0], value_data[1], value_data[2]);
                    value_data[3] = hs & 0xFF;
                    value_data[4] = hs >> 8;
                } break;
                case id_rgbrec_hs_buffer: {
                    uint16_t offset = (value_data[0] << 8) | value_data[1];
                    uint16_t size   = value_data[2]; // size <= 26
                    rgbrec_get_hs_buffer(offset, size, &value_data[3]);
                } break;
                default:{
                    *command_id = id_unhandled;
                }break;
            }
        } break;
        case id_custom_set_value:{
            switch (*value_id) {
                case id_sleep_timeout: {
                    if (value_data[0] <= hs_sleep_timeout_vendor) {
                        hs_set_sleep_timeout(value_data[0]);
                        eeconfig_confinfo_update();
                    }
                } break;
                case id_rgbrec_channel: {
                    rgbrec_switch_channel(value_data[0]);
                } break;
                case id_rgbrec_hs_data: {
                    rgbrec_set_hs_data(value_data[0], value_data[1], value_data[2], value_data[3] | value_data[4] << 8);
                } break;
                case id_rgbrec_hs_buffer: {
                    uint16_t offset = (value_data[0] << 8) | value_data[1];
                    uint16_t size   = value_data[2]; // size <= 26
                    rgbrec_set_hs_buffer(offset, size, &value_data[3]);
                } break;
                default:{
                    *command_id = id_unhandled;
                }break;
            }
        } break;
        case id_eeprom_reset: {
            hs_reset_settings();
        } break;
        default:{
            *command_id = id_unhandled;
        }break;
    }
}

bool via_command_kb(uint8_t *data, uint8_t length) {

    hs_rgb_blink_set_timer(timer_read32());

    // if (hs_via_custom_value_command_kb(data, length) != false){
    //     replaced_hid_send(data, length);
    //     return true;
    // }
    uint8_t *command_id = &(data[0]);
    if (*command_id == id_eeprom_reset) {
        hs_reset_settings();
    }
    return false;
}
