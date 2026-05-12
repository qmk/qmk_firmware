// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "matrix.h"

typedef enum { UNINITIALIZED, NONE, INVALID, UNKNOWN, SKB_SWITCHES, SKB_ENCODER, SKB_JOYSTICK } myriad_card_t;

bool          myriad_hook_matrix(matrix_row_t current_matrix[]);
uint8_t       myriad_hook_encoder(uint8_t index, bool pad_b);
myriad_card_t detect_myriad(void);

//// Elora-specific pinout

// Control signals
#define MYRIAD_PRESENT GP3
#define MYRIAD_MCU_OVERRIDE GP2

// General I/O
#define MYRIAD_ADC1 GP26
#define MYRIAD_ADC2 GP27
#define MYRIAD_ADC1_CHANNEL 0
#define MYRIAD_ADC2_CHANNEL 1
#define MYRIAD_PWM1 GP23
#define MYRIAD_PWM2 GP24
#define MYRIAD_GPIO1 GP4
#define MYRIAD_GPIO2 GP5
#define MYRIAD_GPIO3 GP6
#define MYRIAD_GPIO4 GP8

// UART
#define MYRIAD_RX GP17
#define MYRIAD_TX GP16
#define MYRIAD_CTS GP18
#define MYRIAD_RTS GP19

// SPI
#define MYRIAD_MISO GP12
#define MYRIAD_MOSI GP11
#define MYRIAD_SCK GP10
#define MYRIAD_MODULE_CS GP9
#define MYRIAD_MATRIX_CS GP13

// I2C
#define MYRIAD_SDA GP0
#define MYRIAD_SCL GP1

// RGB
#define MYRIAD_RGB GP15
