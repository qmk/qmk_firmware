/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <math.h>
#include "scanfunctions.h"
#include "util.h"

/* Equation parameters for the sensor-magnet linearity mapping */
const double a = 16654600.6755;
const double b = -0.00955994866577;
const double c = -1278.75103145;
const double d = 16652478.4163;

uint16_t distance_to_adc(uint8_t distance) {
    distance = MIN(MAX(distance, 0), 255);
    return a * (1 - exp(-b * (distance + c))) - d;
}

uint8_t adc_to_distance(uint16_t adc) {
    return MIN(MAX(((log(1 - ((adc + d) / a)) / -b) - c), 0), 255);
}

uint8_t lut[4096] = {0};

void generate_lut(void) {
    for (uint16_t i = 0; i < a - d; i++) {
        lut[i] = adc_to_distance(i);
    }
}