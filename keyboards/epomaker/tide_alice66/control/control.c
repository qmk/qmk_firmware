// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "control.h"

static ioline_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
extern bool lower_sleep;

bool hs_modeio_detection(bool update, uint8_t *mode,uint8_t lsat_btdev) {
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

    now_mode  = (HS_GET_MODE_PIN(HS_USB_PIN_STATE) ? 3 : (HS_GET_MODE_PIN(HS_BT_PIN_STATE) ? 1 : ((HS_GET_MODE_PIN(HS_2G4_PIN_STATE) ? 2 : 0))));
    hs_mode   = (*mode >= DEVS_BT1 && *mode <= DEVS_BT5) ? 1 : ((*mode == DEVS_2G4) ? 2 : ((*mode == DEVS_USB) ? 3 : 0));
    sw_mode   = ((update || (last_mode == now_mode)) && (hs_mode != now_mode)) ? true : false;
    last_mode = now_mode;

    switch (now_mode)
    {
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

bool hs_mode_scan(bool update,uint8_t moude,uint8_t lsat_btdev) {
   
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

bool hs_rgb_blink_hook(){
    static uint8_t last_status;

    if (last_status != *md_getp_state()){
        last_status = *md_getp_state();
        hs_rgb_blink_set_timer(0x00);
    }
    
    switch (*md_getp_state())
    {
        case MD_STATE_NONE: {
                hs_rgb_blink_set_timer(0x00);
        } break;
        
        case MD_STATE_DISCONNECTED:
            if (hs_rgb_blink_get_timer() == 0x00){
                hs_rgb_blink_set_timer(timer_read32());
                extern void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset);
                wireless_devs_change_kb(wireless_get_current_devs(),wireless_get_current_devs(),false);
            }
            else{
                if (timer_elapsed32(hs_rgb_blink_get_timer()) >= HS_LBACK_TIMEOUT) {
                    hs_rgb_blink_set_timer(timer_read32());
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
                    wait_ms(200);
                    lpwr_set_timeout_manual(true);
                    
                }
            }
        case MD_STATE_CONNECTED:
            if (hs_rgb_blink_get_timer() == 0x00){
                hs_rgb_blink_set_timer(timer_read32());
            }
            else{
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

void lpwr_exti_init_hook(void){

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

    if (lower_sleep){
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

void palcallback_cb(uint8_t line){
    switch (line) {
        case PAL_PAD(HS_BAT_CABLE_PIN): {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_CABLE);
        } break;
#ifdef HS_2G4_DEF_PIN
        case PAL_PAD(HS_2G4_DEF_PIN): {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_SWITCH);
        } break;
#endif

#ifdef HS_BT_DEF_PIN
        case PAL_PAD(HS_BT_DEF_PIN): {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_SWITCH);
        } break;
#endif
        default: {
            
        } break;
    }
}



void lpwr_stop_hook_post(void){
    if (lower_sleep){
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
