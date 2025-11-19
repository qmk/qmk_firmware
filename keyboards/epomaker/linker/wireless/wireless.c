
// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "wireless.h"

#ifndef WLS_INQUIRY_BAT_TIME
#    define WLS_INQUIRY_BAT_TIME 3000
#endif

static uint8_t wls_devs = DEVS_USB;
bool im_test_rate_flag;

void last_matrix_activity_trigger(void);

uint8_t wireless_keyboard_leds(void);
void wireless_send_keyboard(report_keyboard_t *report);
void wireless_send_nkro(report_nkro_t *report);
void wireless_send_mouse(report_mouse_t *report);
void wireless_send_extra(report_extra_t *report);

host_driver_t wireless_driver = {
    .keyboard_leds = wireless_keyboard_leds,
    .send_keyboard = wireless_send_keyboard,
    .send_nkro     = wireless_send_nkro,
    .send_mouse    = wireless_send_mouse,
    .send_extra    = wireless_send_extra,
};

void wireless_init(void) {

    md_init();
}

uint8_t wireless_keyboard_leds(void) {

    if (*md_getp_state() == MD_STATE_CONNECTED) {
        return *md_getp_indicator();
    }

    return 0;
}

void wireless_send_keyboard(report_keyboard_t *report) {
    if(MD_STATE_PAIRING == *md_getp_state()){
        return;
    }
    uint8_t wls_report_kb[MD_SND_CMD_KB_LEN] = {0};

    if (*md_getp_state() != MD_STATE_CONNECTED) {
        wireless_devs_change(wls_devs, wls_devs, false);
        return;
    }

    if (report != NULL) {
        memcpy(wls_report_kb, (uint8_t *)report, sizeof(wls_report_kb));
    }
    md_send_kb(wls_report_kb);
}

void wireless_send_nkro(report_nkro_t *report) {
    static report_keyboard_t temp_report_keyboard = {0};
    uint8_t wls_report_nkro[MD_SND_CMD_NKRO_LEN]  = {0};

    if(MD_STATE_PAIRING == *md_getp_state()){
        return;
    }

    if (*md_getp_state() != MD_STATE_CONNECTED) {
        wireless_devs_change(wls_devs, wls_devs, false);
        return;
    }

    if (report != NULL) {
        report_nkro_t temp_report_nkro = *report;
        uint8_t key_count              = 0;

        temp_report_keyboard.mods = temp_report_nkro.mods;
        for (uint8_t i = 0; i < NKRO_REPORT_BITS; i++) {
            key_count += __builtin_popcount(temp_report_nkro.bits[i]);
        }

        // find key up and del it.
        for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS && temp_report_keyboard.keys[i]; i++) {
            uint8_t usageid = 0x00;
            uint8_t n;

            for (uint8_t c = 0; c < key_count; c++) {
                for (n = 0; n < NKRO_REPORT_BITS && !temp_report_nkro.bits[n]; n++) {}
                usageid = (n << 3) | biton(temp_report_nkro.bits[n]);
#ifdef NKRO_ENABLE
                del_key_bit(&temp_report_nkro, usageid);
#endif
                if (usageid == temp_report_keyboard.keys[i]) {
                    break;
                }
            }

            if (usageid != temp_report_keyboard.keys[i]) {
                temp_report_keyboard.keys[i] = 0x00;
            }
        }

        /*
         * Use NKRO for sending when more than 6 keys are pressed
         * to solve the issue of the lack of a protocol flag in wireless mode.
         */

        temp_report_nkro = *report;

        for (uint8_t i = 0; i < key_count; i++) {
            uint8_t usageid;
            uint8_t idx, n = 0;

            for (n = 0; n < NKRO_REPORT_BITS && !temp_report_nkro.bits[n]; n++) {}
            usageid = (n << 3) | biton(temp_report_nkro.bits[n]);
#ifdef NKRO_ENABLE
            del_key_bit(&temp_report_nkro, usageid);
#endif

            for (idx = 0; idx < KEYBOARD_REPORT_KEYS; idx++) {
                if (temp_report_keyboard.keys[idx] == usageid) {
                    break;
                }
                if (temp_report_keyboard.keys[idx] == 0x00) {
                    temp_report_keyboard.keys[idx] = usageid;
                    break;
                }
            }

            if (idx == KEYBOARD_REPORT_KEYS && (usageid < (MD_SND_CMD_NKRO_LEN * 8))) {
                wls_report_nkro[usageid / 8] |= 0x01 << (usageid % 8);
            }
        }
    } else {
        memset(&temp_report_keyboard, 0, sizeof(temp_report_keyboard));
    }

    // wireless_driver.send_keyboard(&temp_report_keyboard);
    while(smsg_is_busy()) wireless_task();
    host_keyboard_send(&temp_report_keyboard);
    md_send_nkro(wls_report_nkro);
}

void wireless_send_mouse(report_mouse_t *report) {
    
    if(MD_STATE_PAIRING == *md_getp_state()){
        return;
    }

    typedef struct {
        uint8_t buttons;
        int8_t x;
        int8_t y;
        int8_t z;
        int8_t h;
    } __attribute__((packed)) wls_report_mouse_t;

    wls_report_mouse_t wls_report_mouse = {0};

    if (*md_getp_state() != MD_STATE_CONNECTED) {
        wireless_devs_change(wls_devs, wls_devs, false);
        return;
    }

    if (report != NULL) {
        wls_report_mouse.buttons = report->buttons;
        wls_report_mouse.x       = report->x;
        wls_report_mouse.y       = report->y;
        wls_report_mouse.z       = report->h;
        wls_report_mouse.h       = report->v;
    }

    md_send_mouse((uint8_t *)&wls_report_mouse);
}

void wireless_send_extra(report_extra_t *report) {
    if(MD_STATE_PAIRING == *md_getp_state()){
        return;
    }

    uint16_t usage = 0;

    if (*md_getp_state() != MD_STATE_CONNECTED) {
        wireless_devs_change(wls_devs, wls_devs, false);
        return;
    }

    if (report != NULL) {
        usage = report->usage;

        switch (usage) {
            case 0x81:
            case 0x82:
            case 0x83: { // system usage
                usage = 0x01 << (usage - 0x81);
                md_send_system((uint8_t *)&usage);
            } break;
            default: {
                md_send_consumer((uint8_t *)&usage);
            } break;
        }
    }
}

void wireless_devs_change_user(uint8_t old_devs, uint8_t new_devs, bool reset) __attribute__((weak));
void wireless_devs_change_user(uint8_t old_devs, uint8_t new_devs, bool reset) {}

void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset) __attribute__((weak));
void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset) {}

void wireless_devs_change(uint8_t old_devs, uint8_t new_devs, bool reset) {
    bool changed = (old_devs == DEVS_USB) ? (new_devs != DEVS_USB) : (new_devs == DEVS_USB);

    if (changed) {
        set_transport((new_devs != DEVS_USB) ? TRANSPORT_WLS : TRANSPORT_USB);
    }

    if ((wls_devs != new_devs) || reset) {
        *md_getp_state()     = MD_STATE_DISCONNECTED;
        *md_getp_indicator() = 0;
    }

    wls_devs = new_devs;
    last_matrix_activity_trigger();

    md_devs_change(new_devs, reset);
    wireless_devs_change_kb(old_devs, new_devs, reset);
    wireless_devs_change_user(old_devs, new_devs, reset);
}

uint8_t wireless_get_current_devs(void) {
    return wls_devs;
}

void usb_mode_test_report_task(void) {
    extern void host_mouse_send(report_mouse_t * report);

    static uint8_t flip                = 0;
    static report_mouse_t mouse_format = {0};

    switch (flip) {
        case 0: { 
            mouse_format.x = 10;
            mouse_format.y = 0;
            host_mouse_send(&mouse_format);
            flip = 1;
        } break;
        case 1: { 
            mouse_format.x = 0;
            mouse_format.y = -10;
            host_mouse_send(&mouse_format);
            flip = 2;
        } break;
        case 2: { 
            mouse_format.x = -10;
            mouse_format.y = 0;
            host_mouse_send(&mouse_format);
            flip = 3;
        } break;
        case 3: { 
            mouse_format.x = 0;
            mouse_format.y = 10;
            host_mouse_send(&mouse_format);
            flip = 0;
        } break;
        default: {
            flip = 0;
        } break;
    }
}

void wireless_pre_task(void) __attribute__((weak));
void wireless_pre_task(void) {}

void wireless_post_task(void) __attribute__((weak));
void wireless_post_task(void) {}

void wireless_task(void) {

    wireless_pre_task();
    lpwr_task();
    md_main_task();
    wireless_post_task();

    /* usb_remote_wakeup() should be invoked last so that we have chance
     * to switch to wireless after start-up when usb is not connected
     */
    if (get_transport() == TRANSPORT_USB) {
        usb_remote_wakeup();
    } else if (lpwr_get_state() == LPWR_NORMAL) {
        static uint32_t inqtimer = 0x00;

        if (sync_timer_elapsed32(inqtimer) >= (WLS_INQUIRY_BAT_TIME)) {
            if (md_inquire_bat()) {
                inqtimer = sync_timer_read32();
            }
        }
    }
}

void housekeeping_task_kb(void) {
    if (wireless_get_current_devs() == DEVS_USB && im_test_rate_flag) usb_mode_test_report_task();
    wireless_task();
}