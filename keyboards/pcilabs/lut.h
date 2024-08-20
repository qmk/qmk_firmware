/*
Copyright 2023 RephlexZero (@RephlexZero)
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <stdint.h>

#include "analogkeys.h"

typedef struct {
    const double a;
    const double b;
    const double c;
    const double d;
    uint16_t      values[ADC_RESOLUTION_MAX];
} lut_t;

extern lut_t luts[];

uint16_t distance_to_adc(uint8_t distance, switch_type_t sw);

uint16_t adc_to_distance(uint16_t adc, switch_type_t sw);

void generate_lut(void);
