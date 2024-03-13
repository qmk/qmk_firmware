/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include "samd51j18a.h"

#include "pin_defs.h"

typedef uint8_t pin_t;

#define SAMD_PORT(pin) (((pin)&0x20) >> 5)
#define SAMD_PIN(pin) ((pin)&0x1f)
#define SAMD_PIN_MASK(pin) (1 << ((pin)&0x1f))

#define gpio_set_pin_input(pin)                                                          \
    do {                                                                                 \
        PORT->Group[SAMD_PORT(pin)].PINCFG[SAMD_PIN(pin)].bit.INEN = 1;                  \
        PORT->Group[SAMD_PORT(pin)].DIRCLR.reg                     = SAMD_PIN_MASK(pin); \
    } while (0)

#define gpio_set_pin_input_high(pin)                                                       \
    do {                                                                                   \
        PORT->Group[SAMD_PORT(pin)].DIRCLR.reg                       = SAMD_PIN_MASK(pin); \
        PORT->Group[SAMD_PORT(pin)].OUTSET.reg                       = SAMD_PIN_MASK(pin); \
        PORT->Group[SAMD_PORT(pin)].PINCFG[SAMD_PIN(pin)].bit.INEN   = 1;                  \
        PORT->Group[SAMD_PORT(pin)].PINCFG[SAMD_PIN(pin)].bit.PULLEN = 1;                  \
    } while (0)

#define gpio_set_pin_input_low(pin)                                                        \
    do {                                                                                   \
        PORT->Group[SAMD_PORT(pin)].DIRCLR.reg                       = SAMD_PIN_MASK(pin); \
        PORT->Group[SAMD_PORT(pin)].OUTCLR.reg                       = SAMD_PIN_MASK(pin); \
        PORT->Group[SAMD_PORT(pin)].PINCFG[SAMD_PIN(pin)].bit.INEN   = 1;                  \
        PORT->Group[SAMD_PORT(pin)].PINCFG[SAMD_PIN(pin)].bit.PULLEN = 1;                  \
    } while (0)

#define gpio_set_pin_output_push_pull(pin)                           \
    do {                                                             \
        PORT->Group[SAMD_PORT(pin)].DIRSET.reg = SAMD_PIN_MASK(pin); \
        PORT->Group[SAMD_PORT(pin)].OUTCLR.reg = SAMD_PIN_MASK(pin); \
    } while (0)

#define gpio_set_pin_output_open_drain(pin) _Static_assert(0, "Open-drain outputs are not available on ATSAM")

#define gpio_set_pin_output(pin) gpio_set_pin_output_push_pull(pin)

#define gpio_write_pin_high(pin)                                     \
    do {                                                             \
        PORT->Group[SAMD_PORT(pin)].OUTSET.reg = SAMD_PIN_MASK(pin); \
    } while (0)

#define gpio_write_pin_low(pin)                                      \
    do {                                                             \
        PORT->Group[SAMD_PORT(pin)].OUTCLR.reg = SAMD_PIN_MASK(pin); \
    } while (0)

#define gpio_write_pin(pin, level)                                       \
    do {                                                                 \
        if (level)                                                       \
            PORT->Group[SAMD_PORT(pin)].OUTSET.reg = SAMD_PIN_MASK(pin); \
        else                                                             \
            PORT->Group[SAMD_PORT(pin)].OUTCLR.reg = SAMD_PIN_MASK(pin); \
    } while (0)

#define gpio_read_pin(pin) ((PORT->Group[SAMD_PORT(pin)].IN.reg & SAMD_PIN_MASK(pin)) != 0)

#define gpio_toggle_pin(pin) (PORT->Group[SAMD_PORT(pin)].OUTTGL.reg = SAMD_PIN_MASK(pin))
