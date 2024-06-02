/* Copyright 2023 RephlexZero (@RephlexZero) 2024 peepeetee (@peepeetee)
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
// const double a = 0.200347177016;
// const double b = 0.00955994866154;
// const double c = 6.01110636956;
// const double d = 1966.74076381;

/* Equation parameters for the sensor-magnet linearity mapping */
// const double a = 1;
// const double b = 0.0061787;
// const double c = 4.34;
// const double d = 1935.43;

const double a = 0.00609446727442;
const double b = 4.40340283615;
const double c = 2122.25923605;

uint16_t distance_to_adc(uint16_t distance) {
    // double intermediate = a * exp(b * distance + c) + d;
    double intermediate = ((-exp(a*distance + b)) + c);
    uint16_t adc = (uint16_t) MAX(0, MIN(intermediate, 4095));
    return adc;
}

uint16_t adc_to_distance(uint16_t adc) {
    // if (adc <= d) {
    //     return 0;
    // }

    // double intermediate = ((log((adc - d) / a)) - c) / b;

    double intermediate = ((log(c-adc)-b)/a);
    uint16_t distance = (uint16_t) MAX(0, MIN(intermediate, 255));
    return distance;
}

uint16_t lut[ADC_RESOLUTION_MAX] = {0};

void generate_lut(void) {
    for (uint16_t i = 0; i < ADC_RESOLUTION_MAX; i++) {
        lut[i] = adc_to_distance(i);
    }
}
