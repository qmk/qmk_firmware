/*
Copyright 2023 RephlexZero (@RephlexZero)
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#include <math.h>
#include <stdint.h>
#include "config.h"
#include <stdlib.h>
#include "lut.h"
#include "util.h"
#include "printf.h"

lut_t luts[] = {
    [latenpow] = {.a = 0.200347233351, .b = 0.00609446727442, .c = 6.01110608723, .d = 1973.74076395},
    [KS_20]    = {.a = 5081.9120615, .b = -0.00594582173114, .c = -694.612151258, .d = 2959.65282546}
};

uint16_t distance_to_adc(uint8_t distance, switch_type_t sw) {
    double intermediate = luts[sw].a * exp(luts[sw].b * distance + luts[sw].c) + luts[sw].d;
    uint16_t adc = (uint16_t)MAX(0, MIN(intermediate, ADC_RESOLUTION_MAX));
    return adc;
}

uint16_t adc_to_distance(uint16_t adc, switch_type_t sw) {
    double intermediate = (log((adc - luts[sw].d) / luts[sw].a) - luts[sw].c) / luts[sw].b;
    uint16_t distance = (uint16_t) MAX(0, MIN(intermediate, switch_ranges[sw]));
    return distance;
}

void generate_lut(void) {
    //switch_type_t sw = KS_20;
    for(switch_type_t sw = latenpow; sw <= KS_20; sw++){
        //for (uint16_t i = 0; i <= abs(luts[sw].a - luts[sw].d) ; i++) {
        for (uint16_t i = 0; i < ADC_RESOLUTION_MAX; i++) {
            printf("%d ", adc_to_distance(i, sw));
            luts[sw].values[i] = adc_to_distance(i, sw);
        //}
        printf("/n/n/n");
    }
}
