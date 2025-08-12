// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "midi.h"

void midi_rx_callback(uint8_t port, midi_packet_t *packet) {
    if (packet->header == MIDI_HEADER_CC) {
        switch (packet->data1) {
            case 80:  // CC-Nummer von DMXControl
                if (packet->data2 > 64) {
                    rgblight_enable();
                    rgblight_sethsv_noeeprom(HSV_RED);
                } else {
                    rgblight_disable();
                }
                break;
            case 81:
                rgblight_sethsv_noeeprom(HSV_BLUE);
                break;
            case 82:
                rgblight_sethsv_noeeprom(HSV_GREEN);
                break;
        }
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_5x4(
        KC_F4,   KC_F5, KC_F6, KC_F7,
        KC_F4,   KC_F5, KC_F6, KC_F7,
        KC_F4,   KC_F5, KC_F6, KC_F7,
        KC_F4,   KC_F5, KC_F6, KC_F7,
        KC_F4,   KC_F5, KC_F6, KC_F7
    )
};
