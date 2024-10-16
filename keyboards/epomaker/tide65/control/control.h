// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include <stdbool.h>
#include "wireless.h"

/* Use when there is a three-stage dial switch */
// #    define HS_BT_DEF_PIN  C14
// #    define HS_2G4_DEF_PIN C15
// #    define HS_BT_PIN_STATE 0, 1
// #    define HS_2G4_PIN_STATE 1, 0
// #    define HS_USB_PIN_STATE 1, 1

#    define HS_GET_MODE_PIN_(pin_bt, pin_2g4) ((((#pin_bt)[0] == 'x') || ((readPin(HS_BT_DEF_PIN) + 0x30) == ((#pin_bt)[0]))) && (((#pin_2g4)[0] == 'x') || ((readPin(HS_2G4_DEF_PIN) + 0x30) == ((#pin_2g4)[0]))))
#    define HS_GET_MODE_PIN(state)            HS_GET_MODE_PIN_(state)
#    define HS_MODEIO_DETECTION_TIME 50

/* Set the wireless device's reconnect timeout and connection usage sleep time */
#define HS_LBACK_TIMEOUT (30 * 1000)
#define HS_SLEEP_TIMEOUT (1 * 60000)

enum modeio_mode {
    hs_none = 0,
    hs_usb,
    hs_bt,
    hs_2g4,
    hs_wireless
};

bool hs_rgb_blink_hook(void);
bool hs_mode_scan(bool update,uint8_t moude,uint8_t lsat_btdev);
bool hs_modeio_detection(bool update, uint8_t *mode,uint8_t lsat_btdev);
void hs_rgb_blink_set_timer(uint32_t time);