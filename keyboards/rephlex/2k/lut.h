/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once
#include <stdint.h>

extern uint8_t lut[4096];

uint16_t distance_to_adc(uint8_t distance);

uint8_t adc_to_distance(uint16_t adc);

void generate_lut(void);
