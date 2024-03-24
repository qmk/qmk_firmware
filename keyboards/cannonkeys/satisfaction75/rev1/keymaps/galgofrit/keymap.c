#include QMK_KEYBOARD_H
#include "satisfaction_core.h"

extern MidiDevice midi_device;

// MIDI CC codes for generic on/off switches (80, 81, 82, 83)
// Off: 0-63
// On:  64-127

#define MIDI_CC_OFF 0
#define MIDI_CC_ON  127

#define MIDI_CHANNEL 0x1F
#define MIDI_HOP_SIZE 3

/* enum custom_keycodes { */
    /* MIDI_CC80 = SAFE_RANGE, */
/* }; */

int MIDI_POSITION = 0;

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
    /* switch (keycode) { */
        /* case MIDI_CC80: */
            /* if (record->event.pressed) { */
                /* midi_send_cc(&midi_device, midi_config.channel, 80, MIDI_CC_ON); */
            /* } else { */
                /* midi_send_cc(&midi_device, midi_config.channel, 80, MIDI_CC_OFF); */
            /* } */
            /* return true; */
    /* } */
    /* return true; */
/* }; */

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (encoder_mode != ENC_MODE_CUSTOM0)
        return true;

    if (index == 0) { // Assuming your encoder is at index 0
        if (clockwise) {
            if (MIDI_POSITION >= 127 - MIDI_HOP_SIZE) {
                MIDI_POSITION = 127;
            } else {
                MIDI_POSITION += MIDI_HOP_SIZE;
            }
            midi_send_cc(&midi_device, midi_config.channel, MIDI_CHANNEL, MIDI_POSITION);
        } else {
            if (MIDI_POSITION <= MIDI_HOP_SIZE) {
                MIDI_POSITION = 0;
            } else {
                MIDI_POSITION -= MIDI_HOP_SIZE;
            }
            midi_send_cc(&midi_device, midi_config.channel, MIDI_CHANNEL, MIDI_POSITION);
        }
        return true;
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_default(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  ENC_PRESS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENTER,           KC_PGUP,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_PGDN,
    KC_LCTL,  KC_LALT,  KC_LGUI,                      KC_SPC,                                 KC_RALT,  MO(1),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),
  [1] = LAYOUT_default(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, OLED_TOGG,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, CLOCK_SET,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    QK_BOOT, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______
  )
};
