/* Copyright 2022 3araht
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    resl0, resl1,   l00, l01, l02, l03, l04, l05, l06, l07, l08, l09, l0a, l0b, \
      resl2, resl3,   l10, l11, l12, l13, l14, l15, l16, l17, l18, l19, l1a, l1b, \
        resl4, resl5,   l20, l21, l22, l23, l24, l25, l26, l27, l28, l29, l2a, l2b, \
          resl6, resl7,   l30, l31, l32, l33, l34, l35, l36, l37, l38, l39, l3a, l3b, \
            resl8, resl9,   l40, l41, l42, l43, l44, l45, l46, l47, l48, l49, l4a, l4b, \
    \
              r00, r01, r02, r03, r04, r05, r06, r07, r08, r09, r0a, r0b,      resr1, resr2,    \
            r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r1a, r1b, r1c,             resr3, \
              r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r2a, r2b,   renc,               \
            r30, r31, r32, r33, r34, r35, r36, r37, r38, r39, r3a, r3b, r3c,             resr4, \
    resr0,    r40, r41, r42, r43, r44, r45, r46, r47, r48, r49, r4a, r4b,      resr5, resr6     \
) { \
    { resl0, resl1,  l00, l01, l02, l03, l04, KC_NO }, \
    { resl2, resl3,  l10, l11, l12, l13, l14, KC_NO }, \
    { resl4, resl5,  l20, l21, l22, l23, l24, KC_NO }, \
    { resl6, resl7,  l30, l31, l32, l33, l34, KC_NO }, \
    { resl8, resl9,  l40, l41, l42, l43, l44, KC_NO }, \
    \
    { l0b,   l0a,    l09, l08, l07, l06, l05, KC_NO }, \
    { l1b,   l1a,    l19, l18, l17, l16, l15, KC_NO }, \
    { l2b,   l2a,    l29, l28, l27, l26, l25, KC_NO }, \
    { l3b,   l3a,    l39, l38, l37, l36, l35, KC_NO }, \
    { l4b,   l4a,    l49, l48, l47, l46, l45, KC_NO }, \
    \
    { r00,   r01,    r02, r03, r04, r05, r06, KC_NO }, \
    { r10,   r11,    r12, r13, r14, r15, r16, KC_NO }, \
    { r20,   r21,    r22, r23, r24, r25, r26, KC_NO }, \
    { r30,   r31,    r32, r33, r34, r35, r36, KC_NO }, \
    { resr0, r40,    r41, r42, r43, r44, r45, KC_NO }, \
    \
    { resr2, resr1,  r0b, r0a, r09, r08, r07, KC_NO }, \
    { resr3, r1c,    r1b, r1a, r19, r18, r17, KC_NO }, \
    { resr4, renc,   r2b, r2a, r29, r28, r27, KC_NO }, \
    { resr6, r3c,    r3b, r3a, r39, r38, r37, KC_NO }, \
    { resr5, r4b,    r4a, r49, r48, r47, r46, KC_NO }  \
}

extern MidiDevice midi_device;
void my_process_midi4Bass(uint8_t channel, keyrecord_t *record,
                          uint8_t *chord_status, uint8_t chord, uint16_t root_note, bool is_single_bass);

void my_process_midi4TriadChords(uint8_t channel, keyrecord_t *record,
                                 uint8_t *chord_status, uint8_t chord, uint16_t root_note,
                                 int8_t offset1, int8_t offset2, int8_t offset3);

void my_process_midi(uint8_t channel, uint16_t keycode, keyrecord_t *record, uint8_t *my_tone_status, int8_t offset, bool melody_unison_suppress);
