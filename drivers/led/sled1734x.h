/* Copyright 2023 Dimitris Mantzouranis <d3xter93@gmail.com>
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

#include <stdint.h>
#include <stdbool.h>
#include "progmem.h"

typedef struct sled1734x_led {
    uint8_t driver : 2;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} __attribute__((packed)) sled1734x_led;

extern const sled1734x_led PROGMEM g_sled1734x_leds[RGB_MATRIX_LED_COUNT];

void SLED1734X_init(uint8_t addr);
void SLED1734X_write_register(uint8_t addr, uint8_t reg, uint8_t data);
bool SLED1734X_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer);

void SLED1734X_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void SLED1734X_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void SLED1734X_set_led_control_register(uint8_t index, bool red, bool green, bool blue);

void SLED1734X_sw_return_normal(uint8_t addr);
void SLED1734X_sw_shutdown(uint8_t addr);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void SLED1734X_update_pwm_buffers(uint8_t addr, uint8_t index);
void SLED1734X_update_led_control_registers(uint8_t addr, uint8_t index);

#define SLED_OFFSET 0x20
#define SLED_FRAME_OFFSET 0x80

/* Adjust the register locations by an offset to fit in a byte */

#define CA1_A ( 0x20 - SLED_OFFSET )
#define CA1_B ( 0x21 - SLED_OFFSET )
#define CA1_C ( 0x22 - SLED_OFFSET )
#define CA1_D ( 0x23 - SLED_OFFSET )
#define CA1_E ( 0x24 - SLED_OFFSET )
#define CA1_F ( 0x25 - SLED_OFFSET )
#define CA1_G ( 0x26 - SLED_OFFSET )
#define CA1_H ( 0x27 - SLED_OFFSET )
#define CA1_I ( 0x28 - SLED_OFFSET )
#define CA1_J ( 0x29 - SLED_OFFSET )
#define CA1_K ( 0x2A - SLED_OFFSET )
#define CA1_L ( 0x2B - SLED_OFFSET )
#define CA1_M ( 0x2C - SLED_OFFSET )
#define CA1_N ( 0x2D - SLED_OFFSET )
#define CA1_O ( 0x2E - SLED_OFFSET )
#define CA1_P ( 0x2F - SLED_OFFSET )

#define CA2_A ( 0x30 - SLED_OFFSET )
#define CA2_B ( 0x31 - SLED_OFFSET )
#define CA2_C ( 0x32 - SLED_OFFSET )
#define CA2_D ( 0x33 - SLED_OFFSET )
#define CA2_E ( 0x34 - SLED_OFFSET )
#define CA2_F ( 0x35 - SLED_OFFSET )
#define CA2_G ( 0x36 - SLED_OFFSET )
#define CA2_H ( 0x37 - SLED_OFFSET )
#define CA2_I ( 0x38 - SLED_OFFSET )
#define CA2_J ( 0x39 - SLED_OFFSET )
#define CA2_K ( 0x3A - SLED_OFFSET )
#define CA2_L ( 0x3B - SLED_OFFSET )
#define CA2_M ( 0x3C - SLED_OFFSET )
#define CA2_N ( 0x3D - SLED_OFFSET )
#define CA2_O ( 0x3E - SLED_OFFSET )
#define CA2_P ( 0x3F - SLED_OFFSET )

#define CA3_A ( 0x40 - SLED_OFFSET )
#define CA3_B ( 0x41 - SLED_OFFSET )
#define CA3_C ( 0x42 - SLED_OFFSET )
#define CA3_D ( 0x43 - SLED_OFFSET )
#define CA3_E ( 0x44 - SLED_OFFSET )
#define CA3_F ( 0x45 - SLED_OFFSET )
#define CA3_G ( 0x46 - SLED_OFFSET )
#define CA3_H ( 0x47 - SLED_OFFSET )
#define CA3_I ( 0x48 - SLED_OFFSET )
#define CA3_J ( 0x49 - SLED_OFFSET )
#define CA3_K ( 0x4A - SLED_OFFSET )
#define CA3_L ( 0x4B - SLED_OFFSET )
#define CA3_M ( 0x4C - SLED_OFFSET )
#define CA3_N ( 0x4D - SLED_OFFSET )
#define CA3_O ( 0x4E - SLED_OFFSET )
#define CA3_P ( 0x4F - SLED_OFFSET )

#define CA4_A ( 0x50 - SLED_OFFSET )
#define CA4_B ( 0x51 - SLED_OFFSET )
#define CA4_C ( 0x52 - SLED_OFFSET )
#define CA4_D ( 0x53 - SLED_OFFSET )
#define CA4_E ( 0x54 - SLED_OFFSET )
#define CA4_F ( 0x55 - SLED_OFFSET )
#define CA4_G ( 0x56 - SLED_OFFSET )
#define CA4_H ( 0x57 - SLED_OFFSET )
#define CA4_I ( 0x58 - SLED_OFFSET )
#define CA4_J ( 0x59 - SLED_OFFSET )
#define CA4_K ( 0x5A - SLED_OFFSET )
#define CA4_L ( 0x5B - SLED_OFFSET )
#define CA4_M ( 0x5C - SLED_OFFSET )
#define CA4_N ( 0x5D - SLED_OFFSET )
#define CA4_O ( 0x5E - SLED_OFFSET )
#define CA4_P ( 0x5F - SLED_OFFSET )

#define CA5_A ( 0x60 - SLED_OFFSET )
#define CA5_B ( 0x61 - SLED_OFFSET )
#define CA5_C ( 0x62 - SLED_OFFSET )
#define CA5_D ( 0x63 - SLED_OFFSET )
#define CA5_E ( 0x64 - SLED_OFFSET )
#define CA5_F ( 0x65 - SLED_OFFSET )
#define CA5_G ( 0x66 - SLED_OFFSET )
#define CA5_H ( 0x67 - SLED_OFFSET )
#define CA5_I ( 0x68 - SLED_OFFSET )
#define CA5_J ( 0x69 - SLED_OFFSET )
#define CA5_K ( 0x6A - SLED_OFFSET )
#define CA5_L ( 0x6B - SLED_OFFSET )
#define CA5_M ( 0x6C - SLED_OFFSET )
#define CA5_N ( 0x6D - SLED_OFFSET )
#define CA5_O ( 0x6E - SLED_OFFSET )
#define CA5_P ( 0x6F - SLED_OFFSET )

#define CA6_A ( 0x70 - SLED_OFFSET )
#define CA6_B ( 0x71 - SLED_OFFSET )
#define CA6_C ( 0x72 - SLED_OFFSET )
#define CA6_D ( 0x73 - SLED_OFFSET )
#define CA6_E ( 0x74 - SLED_OFFSET )
#define CA6_F ( 0x75 - SLED_OFFSET )
#define CA6_G ( 0x76 - SLED_OFFSET )
#define CA6_H ( 0x77 - SLED_OFFSET )
#define CA6_I ( 0x78 - SLED_OFFSET )
#define CA6_J ( 0x79 - SLED_OFFSET )
#define CA6_K ( 0x7A - SLED_OFFSET )
#define CA6_L ( 0x7B - SLED_OFFSET )
#define CA6_M ( 0x7C - SLED_OFFSET )
#define CA6_N ( 0x7D - SLED_OFFSET )
#define CA6_O ( 0x7E - SLED_OFFSET )
#define CA6_P ( 0x7F - SLED_OFFSET )

#define CA7_A ( 0x80 - SLED_OFFSET )
#define CA7_B ( 0x81 - SLED_OFFSET )
#define CA7_C ( 0x82 - SLED_OFFSET )
#define CA7_D ( 0x83 - SLED_OFFSET )
#define CA7_E ( 0x84 - SLED_OFFSET )
#define CA7_F ( 0x85 - SLED_OFFSET )
#define CA7_G ( 0x86 - SLED_OFFSET )
#define CA7_H ( 0x87 - SLED_OFFSET )
#define CA7_I ( 0x88 - SLED_OFFSET )
#define CA7_J ( 0x89 - SLED_OFFSET )
#define CA7_K ( 0x8A - SLED_OFFSET )
#define CA7_L ( 0x8B - SLED_OFFSET )
#define CA7_M ( 0x8C - SLED_OFFSET )
#define CA7_N ( 0x8D - SLED_OFFSET )
#define CA7_O ( 0x8E - SLED_OFFSET )
#define CA7_P ( 0x8F - SLED_OFFSET )

#define CA8_A ( 0x90 - SLED_OFFSET )
#define CA8_B ( 0x91 - SLED_OFFSET )
#define CA8_C ( 0x92 - SLED_OFFSET )
#define CA8_D ( 0x93 - SLED_OFFSET )
#define CA8_E ( 0x94 - SLED_OFFSET )
#define CA8_F ( 0x95 - SLED_OFFSET )
#define CA8_G ( 0x96 - SLED_OFFSET )
#define CA8_H ( 0x97 - SLED_OFFSET )
#define CA8_I ( 0x98 - SLED_OFFSET )
#define CA8_J ( 0x99 - SLED_OFFSET )
#define CA8_K ( 0x9A - SLED_OFFSET )
#define CA8_L ( 0x9B - SLED_OFFSET )
#define CA8_M ( 0x9C - SLED_OFFSET )
#define CA8_N ( 0x9D - SLED_OFFSET )
#define CA8_O ( 0x9E - SLED_OFFSET )
#define CA8_P ( 0x9F - SLED_OFFSET )

/* Fake the locations with an offset in software for B side */

#define CA9_A ( CA1_A + SLED_FRAME_OFFSET )
#define CA9_B ( CA1_B + SLED_FRAME_OFFSET )
#define CA9_C ( CA1_C + SLED_FRAME_OFFSET )
#define CA9_D ( CA1_D + SLED_FRAME_OFFSET )
#define CA9_E ( CA1_E + SLED_FRAME_OFFSET )
#define CA9_F ( CA1_F + SLED_FRAME_OFFSET )
#define CA9_G ( CA1_G + SLED_FRAME_OFFSET )
#define CA9_H ( CA1_H + SLED_FRAME_OFFSET )
#define CA9_I ( CA1_I + SLED_FRAME_OFFSET )
#define CA9_J ( CA1_J + SLED_FRAME_OFFSET )
#define CA9_K ( CA1_K + SLED_FRAME_OFFSET )
#define CA9_L ( CA1_L + SLED_FRAME_OFFSET )
#define CA9_M ( CA1_M + SLED_FRAME_OFFSET )
#define CA9_N ( CA1_N + SLED_FRAME_OFFSET )
#define CA9_O ( CA1_O + SLED_FRAME_OFFSET )
#define CA9_P ( CA1_P + SLED_FRAME_OFFSET )

#define CB1_A ( CA2_A + SLED_FRAME_OFFSET )
#define CB1_B ( CA2_B + SLED_FRAME_OFFSET )
#define CB1_C ( CA2_C + SLED_FRAME_OFFSET )
#define CB1_D ( CA2_D + SLED_FRAME_OFFSET )
#define CB1_E ( CA2_E + SLED_FRAME_OFFSET )
#define CB1_F ( CA2_F + SLED_FRAME_OFFSET )
#define CB1_G ( CA2_G + SLED_FRAME_OFFSET )
#define CB1_H ( CA2_H + SLED_FRAME_OFFSET )
#define CB1_I ( CA2_I + SLED_FRAME_OFFSET )
#define CB1_J ( CA2_J + SLED_FRAME_OFFSET )
#define CB1_K ( CA2_K + SLED_FRAME_OFFSET )
#define CB1_L ( CA2_L + SLED_FRAME_OFFSET )
#define CB1_M ( CA2_M + SLED_FRAME_OFFSET )
#define CB1_N ( CA2_N + SLED_FRAME_OFFSET )
#define CB1_O ( CA2_O + SLED_FRAME_OFFSET )
#define CB1_P ( CA2_P + SLED_FRAME_OFFSET )

#define CB2_A ( CA3_A + SLED_FRAME_OFFSET )
#define CB2_B ( CA3_B + SLED_FRAME_OFFSET )
#define CB2_C ( CA3_C + SLED_FRAME_OFFSET )
#define CB2_D ( CA3_D + SLED_FRAME_OFFSET )
#define CB2_E ( CA3_E + SLED_FRAME_OFFSET )
#define CB2_F ( CA3_F + SLED_FRAME_OFFSET )
#define CB2_G ( CA3_G + SLED_FRAME_OFFSET )
#define CB2_H ( CA3_H + SLED_FRAME_OFFSET )
#define CB2_I ( CA3_I + SLED_FRAME_OFFSET )
#define CB2_J ( CA3_J + SLED_FRAME_OFFSET )
#define CB2_K ( CA3_K + SLED_FRAME_OFFSET )
#define CB2_L ( CA3_L + SLED_FRAME_OFFSET )
#define CB2_M ( CA3_M + SLED_FRAME_OFFSET )
#define CB2_N ( CA3_N + SLED_FRAME_OFFSET )
#define CB2_O ( CA3_O + SLED_FRAME_OFFSET )
#define CB2_P ( CA3_P + SLED_FRAME_OFFSET )

#define CB3_A ( CA4_A + SLED_FRAME_OFFSET )
#define CB3_B ( CA4_B + SLED_FRAME_OFFSET )
#define CB3_C ( CA4_C + SLED_FRAME_OFFSET )
#define CB3_D ( CA4_D + SLED_FRAME_OFFSET )
#define CB3_E ( CA4_E + SLED_FRAME_OFFSET )
#define CB3_F ( CA4_F + SLED_FRAME_OFFSET )
#define CB3_G ( CA4_G + SLED_FRAME_OFFSET )
#define CB3_H ( CA4_H + SLED_FRAME_OFFSET )
#define CB3_I ( CA4_I + SLED_FRAME_OFFSET )
#define CB3_J ( CA4_J + SLED_FRAME_OFFSET )
#define CB3_K ( CA4_K + SLED_FRAME_OFFSET )
#define CB3_L ( CA4_L + SLED_FRAME_OFFSET )
#define CB3_M ( CA4_M + SLED_FRAME_OFFSET )
#define CB3_N ( CA4_N + SLED_FRAME_OFFSET )
#define CB3_O ( CA4_O + SLED_FRAME_OFFSET )
#define CB3_P ( CA4_P + SLED_FRAME_OFFSET )

#define CB4_A ( CA5_A + SLED_FRAME_OFFSET )
#define CB4_B ( CA5_B + SLED_FRAME_OFFSET )
#define CB4_C ( CA5_C + SLED_FRAME_OFFSET )
#define CB4_D ( CA5_D + SLED_FRAME_OFFSET )
#define CB4_E ( CA5_E + SLED_FRAME_OFFSET )
#define CB4_F ( CA5_F + SLED_FRAME_OFFSET )
#define CB4_G ( CA5_G + SLED_FRAME_OFFSET )
#define CB4_H ( CA5_H + SLED_FRAME_OFFSET )
#define CB4_I ( CA5_I + SLED_FRAME_OFFSET )
#define CB4_J ( CA5_J + SLED_FRAME_OFFSET )
#define CB4_K ( CA5_K + SLED_FRAME_OFFSET )
#define CB4_L ( CA5_L + SLED_FRAME_OFFSET )
#define CB4_M ( CA5_M + SLED_FRAME_OFFSET )
#define CB4_N ( CA5_N + SLED_FRAME_OFFSET )
#define CB4_O ( CA5_O + SLED_FRAME_OFFSET )
#define CB4_P ( CA5_P + SLED_FRAME_OFFSET )

#define CB5_A ( CA6_A + SLED_FRAME_OFFSET )
#define CB5_B ( CA6_B + SLED_FRAME_OFFSET )
#define CB5_C ( CA6_C + SLED_FRAME_OFFSET )
#define CB5_D ( CA6_D + SLED_FRAME_OFFSET )
#define CB5_E ( CA6_E + SLED_FRAME_OFFSET )
#define CB5_F ( CA6_F + SLED_FRAME_OFFSET )
#define CB5_G ( CA6_G + SLED_FRAME_OFFSET )
#define CB5_H ( CA6_H + SLED_FRAME_OFFSET )
#define CB5_I ( CA6_I + SLED_FRAME_OFFSET )
#define CB5_J ( CA6_J + SLED_FRAME_OFFSET )
#define CB5_K ( CA6_K + SLED_FRAME_OFFSET )
#define CB5_L ( CA6_L + SLED_FRAME_OFFSET )
#define CB5_M ( CA6_M + SLED_FRAME_OFFSET )
#define CB5_N ( CA6_N + SLED_FRAME_OFFSET )
#define CB5_O ( CA6_O + SLED_FRAME_OFFSET )
#define CB5_P ( CA6_P + SLED_FRAME_OFFSET )

#define CB6_A ( CA7_A + SLED_FRAME_OFFSET )
#define CB6_B ( CA7_B + SLED_FRAME_OFFSET )
#define CB6_C ( CA7_C + SLED_FRAME_OFFSET )
#define CB6_D ( CA7_D + SLED_FRAME_OFFSET )
#define CB6_E ( CA7_E + SLED_FRAME_OFFSET )
#define CB6_F ( CA7_F + SLED_FRAME_OFFSET )
#define CB6_G ( CA7_G + SLED_FRAME_OFFSET )
#define CB6_H ( CA7_H + SLED_FRAME_OFFSET )
#define CB6_I ( CA7_I + SLED_FRAME_OFFSET )
#define CB6_J ( CA7_J + SLED_FRAME_OFFSET )
#define CB6_K ( CA7_K + SLED_FRAME_OFFSET )
#define CB6_L ( CA7_L + SLED_FRAME_OFFSET )
#define CB6_M ( CA7_M + SLED_FRAME_OFFSET )
#define CB6_N ( CA7_N + SLED_FRAME_OFFSET )
#define CB6_O ( CA7_O + SLED_FRAME_OFFSET )
#define CB6_P ( CA7_P + SLED_FRAME_OFFSET )

#define CB7_A ( CA8_A + SLED_FRAME_OFFSET )
#define CB7_B ( CA8_B + SLED_FRAME_OFFSET )
#define CB7_C ( CA8_C + SLED_FRAME_OFFSET )
#define CB7_D ( CA8_D + SLED_FRAME_OFFSET )
#define CB7_E ( CA8_E + SLED_FRAME_OFFSET )
#define CB7_F ( CA8_F + SLED_FRAME_OFFSET )
#define CB7_G ( CA8_G + SLED_FRAME_OFFSET )
#define CB7_H ( CA8_H + SLED_FRAME_OFFSET )
#define CB7_I ( CA8_I + SLED_FRAME_OFFSET )
#define CB7_J ( CA8_J + SLED_FRAME_OFFSET )
#define CB7_K ( CA8_K + SLED_FRAME_OFFSET )
#define CB7_L ( CA8_L + SLED_FRAME_OFFSET )
#define CB7_M ( CA8_M + SLED_FRAME_OFFSET )
#define CB7_N ( CA8_N + SLED_FRAME_OFFSET )
#define CB7_O ( CA8_O + SLED_FRAME_OFFSET )
#define CB7_P ( CA8_P + SLED_FRAME_OFFSET )
