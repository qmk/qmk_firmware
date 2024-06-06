// Copyright 2023 peepeetee (@peepeetee) RephlexZero (@RephlexZero)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 1

#define EECONFIG_KB_DATA_SIZE 6
#define DEBUG_ENABLE
// #define DEBUG_MATRIX_SCAN_RATE

#define ADC_RESOLUTION      12
#define ADC_RESOLUTION_MAX  4096 //1 << 12

#define CALIBRATION_RANGE 255

#define DEBOUNCE 16

//this configuration for the SMA filter, default is 4 for 2^4 = 16 samples
#define SMA_FILTER_SAMPLE_EXPONENT 4

#define I2C1_SCL_PIN GP19
#define I2C1_SDA_PIN GP18
#define OLED_BRIGHTNESS 128
#define OLED_UPDATE_INTERVAL 1000
