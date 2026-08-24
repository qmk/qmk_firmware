// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "steno.h"
#include "progmem.h"
#include "host.h"

typedef enum {
    PLV_BIT_S1,
    PLV_BIT_TL,
    PLV_BIT_KL,
    PLV_BIT_PL,
    PLV_BIT_WL,
    PLV_BIT_HL,
    PLV_BIT_RL,
    PLV_BIT_A,
    PLV_BIT_O,
    PLV_BIT_ST1,
    PLV_BIT_E,
    PLV_BIT_U,
    PLV_BIT_FR,
    PLV_BIT_RR,
    PLV_BIT_PR,
    PLV_BIT_BR,
    PLV_BIT_LR,
    PLV_BIT_GR,
    PLV_BIT_TR,
    PLV_BIT_SR,
    PLV_BIT_DR,
    PLV_BIT_ZR,
    PLV_BIT_N1,
    PLV_BIT_S2,
    PLV_BIT_ST2,
    PLV_BIT_ST3,
    PLV_BIT_ST4,
    PLV_BIT_N2,
    PLV_BIT_N3,
    PLV_BIT_N4,
    PLV_BIT_N5,
    PLV_BIT_N6,
    PLV_BIT_N7,
    PLV_BIT_N8,
    PLV_BIT_N9,
    PLV_BIT_NA,
    PLV_BIT_NB,
    PLV_BIT_NC,
    PLV_BIT_X1,
    PLV_BIT_X2,
    PLV_BIT_X3,
    PLV_BIT_X4,
    PLV_BIT_X5,
    PLV_BIT_X6,
    PLV_BIT_X7,
    PLV_BIT_X8,
    PLV_BIT_X9,
    PLV_BIT_X10,
    PLV_BIT_X11,
    PLV_BIT_X12,
    PLV_BIT_X13,
    PLV_BIT_X14,
    PLV_BIT_X15,
    PLV_BIT_X16,
    PLV_BIT_X17,
    PLV_BIT_X18,
    PLV_BIT_X19,
    PLV_BIT_X20,
    PLV_BIT_X21,
    PLV_BIT_X22,
    PLV_BIT_X23,
    PLV_BIT_X24,
    PLV_BIT_X25,
    PLV_BIT_X26,
} plover_hid_bits_t;

#define PLV_INVALID 0xFF

// clang-format off
static const uint8_t key_to_plover_hid[] PROGMEM = {
    PLV_INVALID, // QK_STENO_FUNCTION - Ignore
    PLV_BIT_N1,  // QK_STENO_N1
    PLV_BIT_N2,  // QK_STENO_N2
    PLV_BIT_N3,  // QK_STENO_N3
    PLV_BIT_N4,  // QK_STENO_N4
    PLV_BIT_N5,  // QK_STENO_N5
    PLV_BIT_N6,  // QK_STENO_N6
    PLV_BIT_S1,  // QK_STENO_S1
    PLV_BIT_S2,  // QK_STENO_S2
    PLV_BIT_TL,  // QK_STENO_TL
    PLV_BIT_KL,  // QK_STENO_KL
    PLV_BIT_PL,  // QK_STENO_PL
    PLV_BIT_WL,  // QK_STENO_WL
    PLV_BIT_HL,  // QK_STENO_HL
    PLV_BIT_RL,  // QK_STENO_RL
    PLV_BIT_A,   // QK_STENO_A
    PLV_BIT_O,   // QK_STENO_O
    PLV_BIT_ST1, // QK_STENO_ST1
    PLV_BIT_ST2, // QK_STENO_ST2
    PLV_INVALID, // QK_STENO_RESET1 - Ignore
    PLV_INVALID, // QK_STENO_RESET2 - Ignore
    PLV_INVALID, // QK_STENO_POWER - Ignore
    PLV_BIT_ST3, // QK_STENO_ST3
    PLV_BIT_ST4, // QK_STENO_ST4
    PLV_BIT_E,   // QK_STENO_E
    PLV_BIT_U,   // QK_STENO_U
    PLV_BIT_FR,  // QK_STENO_FR
    PLV_BIT_RR,  // QK_STENO_RR
    PLV_BIT_PR,  // QK_STENO_PR
    PLV_BIT_BR,  // QK_STENO_BR
    PLV_BIT_LR,  // QK_STENO_LR
    PLV_BIT_GR,  // QK_STENO_GR
    PLV_BIT_TR,  // QK_STENO_TR
    PLV_BIT_SR,  // QK_STENO_SR
    PLV_BIT_DR,  // QK_STENO_DR
    PLV_BIT_N7,  // QK_STENO_N7
    PLV_BIT_N8,  // QK_STENO_N8
    PLV_BIT_N9,  // QK_STENO_N9
    PLV_BIT_NA,  // QK_STENO_NA
    PLV_BIT_NB,  // QK_STENO_NB
    PLV_BIT_NC,  // QK_STENO_NC
    PLV_BIT_ZR,  // QK_STENO_ZR
    PLV_BIT_X1,  // QK_STENO_X1
    PLV_BIT_X2,  // QK_STENO_X2
    PLV_BIT_X3,  // QK_STENO_X3
    PLV_BIT_X4,  // QK_STENO_X4
    PLV_BIT_X5,  // QK_STENO_X5
    PLV_BIT_X6,  // QK_STENO_X6
    PLV_BIT_X7,  // QK_STENO_X7
    PLV_BIT_X8,  // QK_STENO_X8
    PLV_BIT_X9,  // QK_STENO_X9
    PLV_BIT_X10, // QK_STENO_X10
    PLV_BIT_X11, // QK_STENO_X11
    PLV_BIT_X12, // QK_STENO_X12
    PLV_BIT_X13, // QK_STENO_X13
    PLV_BIT_X14, // QK_STENO_X14
    PLV_BIT_X15, // QK_STENO_X15
    PLV_BIT_X16, // QK_STENO_X16
    PLV_BIT_X17, // QK_STENO_X17
    PLV_BIT_X18, // QK_STENO_X18
    PLV_BIT_X19, // QK_STENO_X19
    PLV_BIT_X20, // QK_STENO_X20
    PLV_BIT_X21, // QK_STENO_X21
    PLV_BIT_X22, // QK_STENO_X22
    PLV_BIT_X23, // QK_STENO_X23
    PLV_BIT_X24, // QK_STENO_X24
    PLV_BIT_X25, // QK_STENO_X25
    PLV_BIT_X26, // QK_STENO_X26
};
// clang-format on

void steno_add_key_to_chord_plover_hid(uint8_t chord[MAX_STROKE_SIZE], uint8_t key) {
    uint8_t button = pgm_read_byte(&key_to_plover_hid[key]);
    if (button == PLV_INVALID) {
        return;
    }

    chord[button / 8] |= (1 << (7 - (button % 8)));
}

void steno_send_chord_plover_hid(uint8_t chord[MAX_STROKE_SIZE]) {
    static report_plover_hid_t plover_hid_report = {.report_id = REPORT_ID_PLOVER_HID};
    for (uint8_t i = 0; i < PLOVER_HID_STROKE_SIZE; ++i) {
        plover_hid_report.data[i] = chord[i];
    }
    host_plover_hid_send(&plover_hid_report);

    // Sending a null packet so that the chord registers
    for (uint8_t i = 0; i < PLOVER_HID_STROKE_SIZE; ++i) {
        plover_hid_report.data[i] = 0;
    }
    host_plover_hid_send(&plover_hid_report);
}
