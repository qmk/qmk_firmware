// Copyright 2023 Persama (@Persama)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "ansi.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case MAC_VOICE:
            if (record->event.pressed) {
                host_consumer_send(0xcf);
            } else {
                host_consumer_send(0);
            }
            return false;
        default:
            return true;
    }
}

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    switch (index) {
        case 0:
            if (active) {
                default_layer_set(1 << 2); // WIN
                keymap_config.nkro = 1;
            } else {
                default_layer_set(1 << 0); // MAC
                keymap_config.nkro = 0;
            }
            break;
    }
    return false;
}

void keyboard_post_init_kb(void) {
    setPinOutput(DRIVER_LED_CS_PIN);
    setPinOutput(DC_BOOST_PIN);
    writePinLow(DRIVER_LED_CS_PIN);
    writePinHigh(DC_BOOST_PIN);
    
    keyboard_post_init_user();
}
