/* Copyright 2024 peepeetee (@peepeetee) 2024 minisbett (@minisbett)
SPDX-License-Identifier: GPL-2.0-or-later */

#include <stdint.h>
#include "analogkeys.h"



void initialize_SMA_filter(hybrid_key_t key, uint8_t samplesExponent) {
    key.SMA_samplesExponent = samplesExponent;
    key.SMA_samples = 1 << samplesExponent;
    key.SMA_buffer = malloc(key.SMA_samples*sizeof(uint16_t));
    printf("%s\n", "SMA_buffer test print");
    key.SMA_sum = 0;
    key.SMA_index = 0;
}

uint16_t SMA_filter(hybrid_key_t key, uint16_t value) {
    key.SMA_sum = key.SMA_sum - key.SMA_buffer[key.SMA_index] + value;
    key.SMA_buffer[key.SMA_index] = value;
    key.SMA_index = (key.SMA_index + 1) % key.SMA_samples;
    printf("%s\n", "SMA_filter test print");
    printf("%s\n", "SMA_sum and SMA_index:");
    printf("%lu\n", key.SMA_sum);
    printf("%x\n", key.SMA_index);
    for(int i = 0; i < key.SMA_samples; i++) {
        printf("%u\n", key.SMA_buffer[i]);
    }
    printf("%s\n", "current value:");
    printf("%x\n", key.SMA_buffer[key.SMA_index]);
    return key.SMA_sum >> key.SMA_samplesExponent;
}




