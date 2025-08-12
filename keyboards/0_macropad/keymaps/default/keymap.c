// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "midi.h"
#include "quantum.h"
// Eigene Keycodes definieren
enum custom_keycodes {
    KC_MC1 = SAFE_RANGE,
    KC_MD1,
    KC_ME1,
    KC_MF1,
    KC_MG1
};

void keyboard_post_init_user(void) {
	eeconfig_init();
    rgblight_enable(); 
}

uint32_t blink_timer = 0;
bool led_on = false;

void matrix_scan_user(void) {
    if (timer_elapsed32(blink_timer) > 500) {  // alle 500ms
        blink_timer = timer_read32();
        led_on = !led_on;

        if (led_on) {
            rgblight_sethsv_at(0, 255, 255, 0);  // LED 0: Rot an
        } else {
            rgblight_sethsv_at(0, 0, 0, 0);      // LED 0: aus
        }
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
    KC_MC1,   KC_MD1,   KC_ME1,   KC_MF1,   KC_MG1
  )
};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MC1:
            if (record->event.pressed) {
                midi_send_noteon(0, 0, 64, 127);  // E4
				rgblight_sethsv_at(0, 0, 255, 1);
            } else {
                midi_send_noteoff(0, 0, 64, 0);
				rgblight_sethsv_at(0, 0, 0, 1);
            }
            return false;
        case KC_MD1:
            if (record->event.pressed) {
                midi_send_noteon(0, 0, 64, 127);  // E4
            } else {
                midi_send_noteoff(0, 0, 64, 0);
            }
            return false;
        case KC_ME1:
            if (record->event.pressed) {
                midi_send_noteon(0, 0, 64, 127);  // E4
            } else {
                midi_send_noteoff(0, 0, 64, 0);
            }
            return false;
        case KC_MF1:
            if (record->event.pressed) {
                midi_send_noteon(0, 0, 65, 127);  // F4
            } else {
                midi_send_noteoff(0, 0, 65, 0);
            }
            return false;
        case KC_MG1:
            if (record->event.pressed) {
                midi_send_noteon(0, 0, 67, 127);  // G4
            } else {
                midi_send_noteoff(0, 0, 67, 0);
            }
            return false;
    }
    return true;