/* Copyright 2023 RephlexZero (@RephlexZero) 2024 peepeetee (@peepeetee) 2024 Jenna Fligor (@Ex-32)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <math.h>
#include <stdint.h>
// #include "scanfunctions.h"
// #include "util.h"

#if !defined(MIN)
#    define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

#if !defined(MAX)
#    define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif

// /* Equation parameters for the sensor-magnet linearity mapping */
// const double lut_a = 0.200347177016;
// const double lut_b = 0.00955994866154;
// const double lut_c = 6.01110636956;
// const double lut_d = 1966.74076381;

/* Equation parameters for the sensor-magnet linearity mapping */
// const double lut_a = 1;
// const double lut_b = 0.0061787;
// const double lut_c = 4.34;
// const double lut_d = 1935.43;

const double lut_a = 0.00609446727442;
const double lut_b = 4.40340283615;
const double lut_c = 2000;

uint16_t distance_to_adc(uint16_t distance) {
    // double intermediate = lut_a * exp(lut_b * distance + lut_c) + lut_d;
    double intermediate = ((-exp(lut_a*distance + lut_b)) + lut_c);
    uint16_t adc = (uint16_t) MAX(0, MIN(intermediate, ADC_RESOLUTION_MAX -1));
    return adc;
}

uint16_t adc_to_distance(uint16_t adc) {
    // if (adc <= lut_c) {
    //     return 0;
    // }

    // double intermediate = ((log((adc - lut_d) / lut_a)) - lut_c) / lut_b;

    double intermediate = ((log(lut_c-adc)-lut_b)/lut_a);
    uint16_t distance = (uint16_t) MAX(0, MIN(intermediate, 400));
    return distance;
}

uint16_t lut[ADC_RESOLUTION_MAX] = {0};

void generate_lut(void) {
    for (uint16_t i = 0; i < ADC_RESOLUTION_MAX; i++) {
        lut[i] = adc_to_distance(i);
    }
}
