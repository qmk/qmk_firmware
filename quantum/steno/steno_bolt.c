// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "steno.h"
#include "progmem.h"
#ifdef VIRTSER_ENABLE
#    include "virtser.h"
#endif

#define TXB_NUL 0
#define TXB_S_L 0b00000001
#define TXB_T_L 0b00000010
#define TXB_K_L 0b00000100
#define TXB_P_L 0b00001000
#define TXB_W_L 0b00010000
#define TXB_H_L 0b00100000
#define TXB_R_L 0b01000001
#define TXB_A_L 0b01000010
#define TXB_O_L 0b01000100
#define TXB_STR 0b01001000
#define TXB_E_R 0b01010000
#define TXB_U_R 0b01100000
#define TXB_F_R 0b10000001
#define TXB_R_R 0b10000010
#define TXB_P_R 0b10000100
#define TXB_B_R 0b10001000
#define TXB_L_R 0b10010000
#define TXB_G_R 0b10100000
#define TXB_T_R 0b11000001
#define TXB_S_R 0b11000010
#define TXB_D_R 0b11000100
#define TXB_Z_R 0b11001000
#define TXB_NUM 0b11010000

#define TXB_GRP0 0b00000000
#define TXB_GRP1 0b01000000
#define TXB_GRP2 0b10000000
#define TXB_GRP3 0b11000000
#define TXB_GRPMASK 0b11000000

#define TXB_GET_GROUP(code) ((code & TXB_GRPMASK) >> 6)

// clang-format off
static const uint8_t boltmap[64] PROGMEM = {
    TXB_NUL,
    TXB_NUM,
    TXB_NUM,
    TXB_NUM,
    TXB_NUM,
    TXB_NUM,
    TXB_NUM,
    TXB_S_L,
    TXB_S_L,
    TXB_T_L,
    TXB_K_L,
    TXB_P_L,
    TXB_W_L,
    TXB_H_L,
    TXB_R_L,
    TXB_A_L,
    TXB_O_L,
    TXB_STR,
    TXB_STR,
    TXB_NUL,
    TXB_NUL,
    TXB_NUL,
    TXB_STR,
    TXB_STR,
    TXB_E_R,
    TXB_U_R,
    TXB_F_R,
    TXB_R_R,
    TXB_P_R,
    TXB_B_R,
    TXB_L_R,
    TXB_G_R,
    TXB_T_R,
    TXB_S_R,
    TXB_D_R,
    TXB_NUM,
    TXB_NUM,
    TXB_NUM,
    TXB_NUM,
    TXB_NUM,
    TXB_NUM,
    TXB_Z_R,
};
// clang-format on

void steno_add_key_to_chord_bolt(uint8_t chord[MAX_STROKE_SIZE], uint8_t key) {
    uint8_t boltcode = pgm_read_byte(boltmap + key);

    chord[TXB_GET_GROUP(boltcode)] |= boltcode;
}

#ifdef VIRTSER_ENABLE
void steno_send_chord_bolt(uint8_t chord[MAX_STROKE_SIZE]) {
    for (uint8_t i = 0; i < BOLT_STROKE_SIZE; ++i) {
        // TX Bolt uses variable length packets where each byte corresponds to a bit array of certain keys.
        // If a user chorded the keys of the first group with keys of the last group, for example, there
        // would be bytes of 0x00 in `chord` for the middle groups which we mustn't send.
        if (chord[i]) {
            virtser_send(chord[i]);
        }
    }
    // Sending a null packet is not always necessary, but it is simpler and more reliable
    // to unconditionally send it every time instead of keeping track of more states and
    // creating more branches in the execution of the program.
    virtser_send(0);
}
#else
#    pragma message "VIRTSER_ENABLE = yes is required for TX Bolt to work properly out of the box!"
#endif // VIRTSER_ENABLE
