#include "wls.h"

static ioline_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
// static ioline_t row_pins[MATRIX_COLS] = MATRIX_ROW_PINS;

bool hs_modeio_detection(bool update, uint8_t *mode, uint8_t lsat_btdev) {
    static uint32_t scan_timer = 0x00;

    if ((update != true) && (timer_elapsed32(scan_timer) <= (HS_MODEIO_DETECTION_TIME))) {
        return false;
    }
    scan_timer = timer_read32();

#ifdef HS_MODE_SW_PIN 
    
        uint8_t now_mode = false;
        uint8_t usb_sws  = false;
    
        now_mode = readPin(HS_MODE_SW_PIN);
        usb_sws  = !!(*mode) ? !now_mode : now_mode;
        dprintf("now_mode = %d\r\n",now_mode);
        if (now_mode) {
            *mode = hs_wireless;
            if (usb_sws){
                if (lsat_btdev) wireless_devs_change(wireless_get_current_devs(), lsat_btdev, false);
                else wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, false);
            }

        } else {
            *mode = hs_usb;
            if (usb_sws) wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);
        }
    
        if (usb_sws) {
            hs_rgb_blink_set_timer(timer_read32());
            suspend_wakeup_init();
            return true;
        }
#elif defined(HS_BT_DEF_PIN) && defined(HS_2G4_DEF_PIN)
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

extern bool state;

bool hs_rgb_blink_hook() {
    static uint8_t last_status;
    uint32_t timeout = 0;
  
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

    switch (*md_getp_state()) {
        case MD_STATE_NONE: {
            hs_rgb_blink_set_timer(0x00);
        } break;

        case MD_STATE_DISCONNECTED:{
            if (hs_rgb_blink_get_timer() == 0x00) {
                hs_rgb_blink_set_timer(timer_read32());
                extern void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset);
                wireless_devs_change_kb(wireless_get_current_devs(), wireless_get_current_devs(), false);
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
            if (hs_rgb_blink_get_timer() == 0x00) {
                hs_rgb_blink_set_timer(timer_read32());
                // extern uint32_t hs_usb_succeed_time;
                // hs_usb_succeed_time = timer_read32();
            } else {
                if (timer_elapsed32(hs_rgb_blink_get_timer()) >= timeout && !rgbrec_is_started()) {
                    hs_rgb_blink_set_timer(timer_read32());
                    clear_keyboard();
                    lpwr_set_timeout_manual(true);
                }
            }
        } break;

        case MD_STATE_PAIRING:{
            if (hs_rgb_blink_get_timer() == 0x00) {
                hs_rgb_blink_set_timer(timer_read32());
    
            } else {
                if (timer_elapsed32(hs_rgb_blink_get_timer()) >= HS_PAIR_TIMEOUT && !rgbrec_is_started()) {
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
    setPinInputHigh(HS_BT_DEF_PIN);
    waitInputPinDelay();
    palEnableLineEvent(HS_BT_DEF_PIN, PAL_EVENT_MODE_BOTH_EDGES);
#endif

#ifdef HS_2G4_DEF_PIN
    setPinInputHigh(HS_2G4_DEF_PIN);
    waitInputPinDelay();
    palEnableLineEvent(HS_2G4_DEF_PIN, PAL_EVENT_MODE_BOTH_EDGES);
#endif

    if (lower_sleep) {
#if DIODE_DIRECTION == ROW2COL
        for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); i++) {
            if (col_pins[i] != NO_PIN) {
                setPinOutput(col_pins[i]);
                writePinHigh(col_pins[i]);
            }
        }
#endif
    }

    setPinInput(HS_BAT_CABLE_PIN);
    waitInputPinDelay();
    palEnableLineEvent(HS_BAT_CABLE_PIN, PAL_EVENT_MODE_RISING_EDGE);
}

void palcallback_cb(uint8_t line) {
    switch (line) {
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

void lpwr_stop_hook_pre(void) { // SLEEP

    gpio_write_pin_low(LED_POWER_EN_PIN);
    gpio_write_pin_low(HS_LED_BOOSTING_PIN);
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
    return false;
}
