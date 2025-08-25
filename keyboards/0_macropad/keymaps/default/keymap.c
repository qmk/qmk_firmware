// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "midi.h"
#include "midi_device.h"

#include QMK_KEYBOARD_H

#include "quantum.h"

extern MidiDevice midi_device;

// Eigene Keycodes definieren
enum custom_keycodes {
    KC_C1 = SAFE_RANGE, KC_D1, KC_E1, KC_A1, KC_G1, KC_H1,
    KC_C2, KC_D2, KC_E2, KC_A2, KC_G2, KC_H2,
    KC_C3, KC_D3, KC_E3, KC_A3, KC_G3, KC_H3,
    KC_C4, KC_D4, KC_E4, KC_A4, KC_G4, KC_H4,
    KC_C5, KC_D5, KC_E5, KC_A5, KC_G5, KC_H5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_6x5(
    KC_C1, KC_D1, KC_E1, KC_G1, KC_A1, KC_H1,
    KC_C2, KC_D2, KC_E2, KC_G2, KC_A2, KC_H2,
    KC_C3, KC_D3, KC_E3, KC_G3, KC_A3, KC_H3,
    KC_C4, KC_D4, KC_E4, KC_G4, KC_A4, KC_H4,
    KC_C5, KC_D5, KC_E5, KC_G5, KC_A5, KC_H5
  )
};

void keyboard_post_init_user(void) {
    rgblight_enable(); 
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t note = 0;

    switch (keycode) {
        case KC_C1: note = 0; break;  // C2
        case KC_D1: note = 1; break;
        case KC_E1: note = 2; break;
        case KC_A1: note = 3; break;
        case KC_G1: note = 4; break;
        case KC_H1: note = 5; break;

        case KC_C2: note = 6; break;  // C3
        case KC_D2: note = 7; break;
        case KC_E2: note = 8; break;
        case KC_A2: note = 9; break;
        case KC_G2: note = 10; break;
        case KC_H2: note = 11; break;

        case KC_C3: note = 12; break;  // C4
        case KC_D3: note = 13; break;
        case KC_E3: note = 14; break;
        case KC_A3: note = 15; break;
        case KC_G3: note = 16; break;
        case KC_H3: note = 17; break;

        case KC_C4: note = 18; break;  // C5
        case KC_D4: note = 19; break;
        case KC_E4: note = 20; break;
        case KC_A4: note = 21; break;
        case KC_G4: note = 22; break;
        case KC_H4: note = 23; break;

        case KC_C5: note = 24; break;  // C6
        case KC_D5: note = 25; break;
        case KC_E5: note = 26; break;
        case KC_A5: note = 27; break;
        case KC_G5: note = 28; break;
        case KC_H5: note = 29; break;

        default: return true;
    }

    if (record->event.pressed) {
        midi_send_noteon(&midi_device, midi_config.channel, note, 127);  // Velocity 127
    } else {
        midi_send_noteoff(&midi_device, midi_config.channel, note, 0);
    }

    return false;
}

void set_led_color_from_midi(uint8_t note, uint8_t velocity) {
    if (note < 30 || note > 129) return;

    uint8_t index = note - 30;
    uint8_t led = index / 3;
    uint8_t color = index % 3;

    // Velocity → Brightness (0–255)
    if (velocity < 1) velocity = 1;
    if (velocity > 127) velocity = 127;
    uint8_t brightness = (velocity * 255) / 127;

    uint8_t r = 0, g = 0, b = 0;
    switch (color) {
        case 0: r = brightness; break;
        case 1: g = brightness; break;
        case 2: b = brightness; break;
    }

    rgblight_setrgb_at(r, g, b, led);
}
void midi_consume_usb_midi_packet(midi_packet_t packet) {
    if ((packet.header & 0xF0) == MIDI_NOTEON && packet.velocity > 0) {
        set_led_color_from_midi(packet.note, packet.velocity);
    } else if ((packet.header & 0xF0) == MIDI_NOTEOFF || packet.velocity == 0) {
        uint8_t index = packet.note - 30;
        if (packet.note >= 30 && packet.note <= 129) {
            rgblight_setrgb_at(0, 0, 0, index / 3);
        }
    }
}