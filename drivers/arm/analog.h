/* Copyright 2019 Drew Mills
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

#pragma once

#include <stdint.h>
#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t input;
    uint8_t  adc;
} adc_mux;
#define TO_MUX(i, a) \
    (adc_mux) { i, a }

int16_t analogReadPin(pin_t pin);
int16_t analogReadPinAdc(pin_t pin, uint8_t adc);
adc_mux pinToMux(pin_t pin);

int16_t adc_read(adc_mux mux);

#ifdef __cplusplus
}
#endif
