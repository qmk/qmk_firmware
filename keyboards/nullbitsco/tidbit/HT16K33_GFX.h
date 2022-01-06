/* Copyright 2021 Jay Greco
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

#include "HT16K33.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

static const uint16_t char_ASCII[96] = {
  0b0000000000000000, //  
  0b0000000000000110, // !
  0b0000001000100000, // "
  0b0001001011001110, // #
  0b0001001011101101, // $
  0b0000110000100100, // %
  0b0010001101011101, // &
  0b0000010000000000, // '
  0b0010010000000000, // (
  0b0000100100000000, // )
  0b0011111111000000, // *
  0b0001001011000000, // +
  0b0000100000000000, // ,
  0b0000000011000000, // -
  0b0100000000000000, // .
  0b0000110000000000, // /
  0b0000110000111111, // 0
  0b0000000000000110, // 1
  0b0000000011011011, // 2
  0b0000000010001111, // 3
  0b0000000011100110, // 4
  0b0010000001101001, // 5
  0b0000000011111101, // 6
  0b0000000000000111, // 7
  0b0000000011111111, // 8
  0b0000000011101111, // 9
  0b0001001000000000, // :
  0b0000101000000000, // ;
  0b0010010000000000, // <
  0b0000000011001000, // =
  0b0000100100000000, // >
  0b0001000010000011, // ?
  0b0000001010111011, // @
  0b0000000011110111, // A
  0b0001001010001111, // B
  0b0000000000111001, // C
  0b0001001000001111, // D
  0b0000000011111001, // E
  0b0000000001110001, // F
  0b0000000010111101, // G
  0b0000000011110110, // H
  0b0001001000000000, // I
  0b0000000000011110, // J
  0b0010010001110000, // K
  0b0000000000111000, // L
  0b0000010100110110, // M
  0b0010000100110110, // N
  0b0000000000111111, // O
  0b0000000011110011, // P
  0b0010000000111111, // Q
  0b0010000011110011, // R
  0b0000000011101101, // S
  0b0001001000000001, // T
  0b0000000000111110, // U
  0b0000110000110000, // V
  0b0010100000110110, // W
  0b0010110100000000, // X
  0b0001010100000000, // Y
  0b0000110000001001, // Z
  0b0000000000111001, // [
  0b0010000100000000, // 
  0b0000000000001111, // ]
  0b0000110000000011, // ^
  0b0000000000001000, // _
  0b0000000100000000, // `
  0b0001000001011000, // a
  0b0010000001111000, // b
  0b0000000011011000, // c
  0b0000100010001110, // d
  0b0000100001011000, // e
  0b0000000001110001, // f
  0b0000010010001110, // g
  0b0001000001110000, // h
  0b0001000000000000, // i
  0b0000000000001110, // j
  0b0011011000000000, // k
  0b0000000000110000, // l
  0b0001000011010100, // m
  0b0001000001010000, // n
  0b0000000011011100, // o
  0b0000000101110000, // p
  0b0000010010000110, // q
  0b0000000001010000, // r
  0b0010000010001000, // s
  0b0000000001111000, // t
  0b0000000000011100, // u
  0b0010000000000100, // v
  0b0010100000010100, // w
  0b0010100011000000, // x
  0b0010000000001100, // y
  0b0000100001001000, // z
  0b0000100101001001, // {
  0b0001001000000000, // |
  0b0010010010001001, // }
  0b0000010100100000, // ~
  0b0011111111111111,
};

typedef struct HT16K33 {
    uint8_t addr;
    uint16_t *buf;
    uint8_t size;
} HT16K33;

HT16K33 *newHT16K33 (uint8_t sz, uint8_t addr);
void HT16K33_init(HT16K33 *disp),
  HT16K33_clear(HT16K33 *disp),
  HT16K33_dispASCII(HT16K33 *disp, uint8_t n, uint8_t a),
  HT16K33_dispRaw(HT16K33 *disp, uint8_t n, uint16_t bmp),
  HT16K33_refresh(HT16K33 *disp),
  HT16K33_printBuffer(HT16K33 *disp);

HT16K33 *newHT16K33 (uint8_t size, uint8_t addr) {
  HT16K33 *disp = malloc (sizeof(HT16K33));
  if (disp == NULL)
      return NULL;

  disp->buf = calloc(size, sizeof(uint16_t));
  if (disp->buf == NULL) {
      free (disp);
      return NULL;
  }

  disp->addr = addr;
  disp->size = size;

  HT16K33_init(disp);

  return disp;
}

void HT16K33_init(HT16K33 *disp) {
  ht16K33_init(disp->addr);
  HT16K33_clear(disp);
  HT16K33_refresh(disp);
}

void HT16K33_clear(HT16K33 *disp) {
  for(uint8_t i = 0; i < disp->size; i++) {
    disp->buf[i] = 0;
  }
}

void HT16K33_dispASCII(HT16K33 *disp, uint8_t n, uint8_t a) {
  disp->buf[n] = char_ASCII[a-32];
}

void HT16K33_dispRaw(HT16K33 *disp, uint8_t n, uint16_t bmp) {
  disp->buf[n] = bmp;
}

void HT16K33_refresh(HT16K33 *disp) {
  ht16K33_refresh(disp->addr, disp->buf, disp->size);
}

void HT16K33_printBuffer(HT16K33 *disp) {
  for (uint8_t i=0; i<disp->size; i++) {
    dprintf("%d:", i);
    dprintf(" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
    BYTE_TO_BINARY(disp->buf[i] >> 8), BYTE_TO_BINARY(disp->buf[i] & 0xFF));
  }
}