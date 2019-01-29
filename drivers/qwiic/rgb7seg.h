/* Copyright 2017 Jason Williams
 * Copyright 2017 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2019 Clueboard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "is31fl3235a.h"

#ifndef BACKLIGHT_ENABLE
  #error You must define BACKLIGHT_ENABLE with LED_MATRIX_ENABLE
#endif


void rgb7seg_task(void);
void rgb7seg_init(void);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void rgb7seg_flush(void);

uint32_t rgb7seg_get_tick(void);

void rgb7seg_off(void);
void rgb7seg_set_index_value(int index, uint8_t value);
void rgb7seg_set_index_value_all(uint8_t value);

void rgb7seg_toggle(void);
void rgb7seg_enable(void);
void rgb7seg_disable(void);
void rgb7seg_increase_val(void);
void rgb7seg_decrease_val(void);

typedef struct rgb7seg_led {
  uint8_t driver;
  uint8_t r;
  uint8_t g;
  uint8_t b;
} __attribute__((packed)) rgb7seg_led;

extern const rgb7seg_led g_rgb7seg_leds[IS31FL3235A_COUNT * 8];

#endif
