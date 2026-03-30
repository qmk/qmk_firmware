// Copyright 2023 Persama (@Persama)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include "color.h"

// WS2812 side LED driver interface
void side_send_byte(uint8_t byte);
void side_ws2812_setleds(rgb_led_t *ledarray, uint16_t leds);
