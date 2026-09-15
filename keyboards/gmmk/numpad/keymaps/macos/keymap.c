
#include QMK_KEYBOARD_H
#include "analog.h"
#include "qmk_midi.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Changed KC_CALC -> KC_MUTE for MacOS as the KC_CALC command doesn't serve a purpose in MacOS
//      NUM      /       *       -
//      7        8       9       +
//      4        5       6       MUTE
//      1        2       3       RET
//      0                        .

  [0] = LAYOUT(
    MO(1),   KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,   KC_P8,     KC_P9,     KC_PPLS,
    KC_P4,   KC_P5,     KC_P6,     KC_MUTE,
    KC_P1,   KC_P2,     KC_P3,     KC_PENT,
    KC_P0,                         KC_PDOT
  ),
  [1] = LAYOUT(
    _______,   KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,     RM_VALU,   KC_P9,     KC_PPLS,
    RM_PREV,   KC_P5,     RM_NEXT,   KC_MUTE,
    KC_P1,     RM_VALD,   KC_P3,     KC_PENT,
    RM_TOGG,                         QK_BOOT
  )
};

// Potentiometer Slider, MIDI Control

#define SLIDER_HYSTERESIS 6 // raw ADC counts of noise to ignore before accepting a new reading

uint8_t divisor      = 0;
int16_t settled_raw  = -1;   // last accepted raw ADC reading, -1 means "not read yet"
uint8_t last_slider_value = 0xFF; // force the first read to always send

// Auto-calibration: the slider's real electrical range doesn't reach the ADC's
// 0-1023 limits, so track the extremes actually seen and stretch them to 0-127.
int16_t slider_min = 1023;
int16_t slider_max = 0;

void slider(void) {
    if (divisor++) { /* only run the slider function 1/256 times it's called */
        return;
    }
    int16_t raw  = analogReadPin(SLIDER_PIN);
    int16_t diff = raw - settled_raw;
    if (settled_raw < 0 || diff > SLIDER_HYSTERESIS || diff < -SLIDER_HYSTERESIS) {
        settled_raw = raw;
    }

    if (settled_raw < slider_min) slider_min = settled_raw;
    if (settled_raw > slider_max) slider_max = settled_raw;

    uint8_t value = 0;
    if (slider_max > slider_min) {
        int32_t scaled = (int32_t)(settled_raw - slider_min) * 127 / (slider_max - slider_min);
        value = (uint8_t)scaled;
    }

    if (value != last_slider_value) {
        last_slider_value = value;
        midi_send_cc(&midi_device, 2, 0x3E, value);
    }
}

void housekeeping_task_user(void) {
    slider();
}

