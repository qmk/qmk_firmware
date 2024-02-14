// Copyright 2022 Jay Greco
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// Indication LED settings
#define LED_ON          2
#define LED_DIM         1
#define LED_OFF         0

#define GPIO_STATE_LOW  0
#define GPIO_STATE_HIGH 1

#define PIN_LED         B2

void set_scramble_LED(uint8_t mode);
