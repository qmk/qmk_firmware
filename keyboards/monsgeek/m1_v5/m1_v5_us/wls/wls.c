#include "wls.h"
#include QMK_KEYBOARD_H
#include "wireless.h"

#include "lowpower.h"
#include "module.h"

static ioline_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

bool hs_modeio_detection(bool update, uint8_t *mode, uint8_t lsat_btdev, uint8_t last_wireless_dev) {
    static uint32_t scan_timer = 0x00;

    if ((update != true) && (timer_elapsed32(scan_timer) <= (HS_MODEIO_DETECTION_TIME))) {
        return false;
    }
    scan_timer = timer_read32();
#if defined(HS_BT_DEF_PIN) && defined(HS_2G4_DEF_PIN)
    uint8_t        now_mode  = 0x00;
    uint8_t        hs_mode   = 0x00;
    static uint8_t last_mode = 0x00;
    bool           sw_mode   = false;
    // Read physical switch position
    now_mode = (HS_GET_MODE_PIN(HS_USB_PIN_STATE) ? 3 : (HS_GET_MODE_PIN(HS_BT_PIN_STATE) ? 1 : ((HS_GET_MODE_PIN(HS_2G4_PIN_STATE) ? 2 : 0))));
    // Get current active device mode from wireless system (not from *mode parameter which can be stale)
    uint8_t current_devs = wireless_get_current_devs();
    // Determine what type of mode we're in (Mac wireless=1, Windows wireless=2, USB=3)
    hs_mode = ((current_devs >= DEVS_BT1 && current_devs <= DEVS_BT5) || current_devs == DEVS_2G4) ? ((now_mode == 1) ? 1 : ((now_mode == 2) ? 2 : 3)) : ((current_devs == DEVS_USB) ? 3 : 0);
    // Detect mode change: physical switch changed position OR there's a mismatch between switch and current mode
    sw_mode   = ((update || (last_mode == now_mode)) && (hs_mode != now_mode)) ? true : false;
    last_mode = now_mode;

    switch (now_mode) {
        case 1:
            *mode = hs_mac_wireless; // Mac wireless mode (top position)
            // Switch to last wireless device when physical switch is in Mac wireless position
            // But only if this is a periodic scan (update=false), not a forced check from keypress
            if (sw_mode && !update) {
                // Restore last used wireless mode (passed as parameter)
                uint8_t target_dev = (last_wireless_dev == DEVS_2G4) ? DEVS_2G4 : lsat_btdev;
                wireless_devs_change(wireless_get_current_devs(), target_dev, false);
            }
            break;
        case 2:
            *mode = hs_win_wireless; // Windows wireless mode (bottom position)
            // Switch to last wireless device when physical switch is in Windows wireless position
            // But only if this is a periodic scan (update=false), not a forced check from keypress
            if (sw_mode && !update) {
                // Restore last used wireless mode (passed as parameter)
                uint8_t target_dev = (last_wireless_dev == DEVS_2G4) ? DEVS_2G4 : lsat_btdev;
                wireless_devs_change(wireless_get_current_devs(), target_dev, false);
            }
            break;
        case 3:
            *mode = hs_usb; // USB mode (middle position)
            // Switch to USB when physical switch is in USB position
            // But only if this is a periodic scan (update=false), not a forced check from keypress
            if (sw_mode && !update) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);
            }
            break;
        default:
            break;
    }

    if (sw_mode && !update) {
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

bool hs_mode_scan(bool update, uint8_t moude, uint8_t lsat_btdev, uint8_t last_wireless_dev) {
    if (hs_modeio_detection(update, &moude, lsat_btdev, last_wireless_dev)) {
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

    if (last_status != *md_getp_state()) {
        last_status = *md_getp_state();
        hs_rgb_blink_set_timer(0x00);
    }

    switch (*md_getp_state()) {
        case MD_STATE_NONE: {
            hs_rgb_blink_set_timer(0x00);
        } break;

        case MD_STATE_DISCONNECTED:
            if (hs_rgb_blink_get_timer() == 0x00) {
                hs_rgb_blink_set_timer(timer_read32());
                extern void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset);
                wireless_devs_change_kb(wireless_get_current_devs(), wireless_get_current_devs(), false);
            } else if (wireless_get_current_devs() != DEVS_USB) {
                if (timer_elapsed32(hs_rgb_blink_get_timer()) >= HS_LBACK_TIMEOUT) {
                    hs_rgb_blink_set_timer(timer_read32());
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
                    wait_ms(200);
                    lpwr_set_timeout_manual(true);
                }
            }
        case MD_STATE_CONNECTED:
            if (hs_rgb_blink_get_timer() == 0x00) {
                hs_rgb_blink_set_timer(timer_read32());
            } else {
                if (timer_elapsed32(hs_rgb_blink_get_timer()) >= HS_SLEEP_TIMEOUT) {
                    hs_rgb_blink_set_timer(timer_read32());
                    lpwr_set_timeout_manual(true);
                }
            }
        default:
            break;
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

    if (lower_sleep) {
#if DIODE_DIRECTION == ROW2COL
        for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); i++) {
            if (col_pins[i] != NO_PIN) {
                gpio_set_pin_output_push_pull(col_pins[i]);
                gpio_write_pin_high(col_pins[i]);
            }
        }
#endif
    }
    gpio_set_pin_input(HS_BAT_CABLE_PIN);
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

void lpwr_stop_hook_pre(void) {
    gpio_write_pin_low(LED_POWER_EN_PIN);
    gpio_write_pin_low(A9);
    gpio_write_pin_low(HS_LED_BOOSTING_PIN);

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

                // --- PATCH: Force matrix scan and send null report after wake ---
                matrix_scan();
                // Send a null keyboard report to sync modifiers
                send_keyboard_report();
                //  -------------------------------------------------------------
            } break;
            default: {
                lpwr_set_state(LPWR_STOP);
            } break;
        }
    }
}
