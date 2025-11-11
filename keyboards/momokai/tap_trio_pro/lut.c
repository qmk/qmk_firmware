/* Copyright 202 RephlexZero (@RephlexZero) 2024 peepeetee (@peepeetee) 2024 Jenna Fligor (@Ex-32)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <math.h>
#include <stdint.h>
#include "scanfunctions.h"
#include "util.h"

// /* Equation parameters for the sensor-magnet linearity mapping */

//https://www.desmos.com/calculator/qtbbjbsyvi

// These are values when there were 400 steps
// const double lut_a = -366.805673399;
// const double lut_b = 0.00617870508512;
// const double lut_c = -1.49468890703;
// const double lut_d = 2094.38794157;

//Values for 256 steps
const double lut_a = -0.203212;
const double lut_b = 0.00955995;
const double lut_c = 5.99691;
const double lut_d = 2122.25924;

uint16_t distance_to_adc(uint16_t distance) {
    double intermediate = lut_a * exp(lut_b * distance + lut_c) + lut_d;
    return (uint16_t) fmax(0, fmin(intermediate, 4095));
}

uint16_t adc_to_distance(uint16_t adc) {
    double check = (adc - lut_d) / lut_a;
    if (check <= 0) {
        return 0;
    }
    double intermediate = (log(check) - lut_c) / lut_b;
    return (uint16_t) fmax(0, fmin(intermediate, 255));
}

uint16_t lut[ADC_RESOLUTION_MAX] = {0};

void generate_lut(void) {
    for (uint16_t i = 0; i < ADC_RESOLUTION_MAX; i++) {
        lut[i] = adc_to_distance(i);
    }
}
