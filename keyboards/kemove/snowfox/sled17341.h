// Copyright 2020 Yaotian Feng / Codetector
// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

// Two SLED1734x LED drivers on SPI1, as a custom RGB Matrix driver.

#pragma once

#include <stdint.h>

void sled_init(void);
void sled_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void sled_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void sled_flush(void);
void sled_on(void);
void sled_off(void);

#ifdef SNOWFOX_TEST
void sled_test_write_register(uint8_t reg, uint8_t value);
#endif
