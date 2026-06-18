// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "steno.h"
#ifdef VIRTSER_ENABLE
#    include "virtser.h"
#endif

void steno_add_key_to_chord_gemini(uint8_t chord[MAX_STROKE_SIZE], uint8_t key) {
    // Although each group of the packet is 8 bits long, the MSB is reserved
    // to indicate whether that byte is the first byte of the packet (MSB=1)
    // or one of the remaining five bytes of the packet (MSB=0).
    // As a consequence, only 7 out of the 8 bits are left to be used as a bit array
    // for the steno keys of that group.
    const int group_idx       = key / 7;
    const int intra_group_idx = key - group_idx * 7;
    // The 0th steno key of the group has bit=0b01000000, the 1st has bit=0b00100000, etc.
    const uint8_t bit = 1 << (6 - intra_group_idx);
    chord[group_idx] |= bit;
}

#ifdef VIRTSER_ENABLE
void steno_send_chord_gemini(uint8_t chord[MAX_STROKE_SIZE]) {
    // Set MSB to 1 to indicate the start of packet
    chord[0] |= 0x80;
    for (uint8_t i = 0; i < GEMINI_STROKE_SIZE; ++i) {
        virtser_send(chord[i]);
    }
}
#else
#    pragma message "VIRTSER_ENABLE = yes is required for Gemini PR to work properly out of the box!"
#endif // VIRTSER_ENABLE
