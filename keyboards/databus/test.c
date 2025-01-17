// Created/amended by OleVoip 2024.
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>

__flash const uint32_t i32 = 1;
volatile uint8_t j8;

int main(void) {
  j8 = (uint8_t)i32;
}
