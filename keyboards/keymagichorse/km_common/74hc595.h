/* Copyright 2024 keymagichorse
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
#include <stdbool.h>

// 有多少个 74hc595
#ifndef I_595_NUM
#   define I_595_NUM 1
#endif

#if I_595_NUM == 1
    typedef uint8_t shift595_data_t;   // 8位，1个74HC595
#elif I_595_NUM == 2
    typedef uint16_t shift595_data_t;  // 16位，2个74HC595
#else
    #error "Unsupported I_595_NUM value"
#endif

#ifndef DS_PIN_74HC595
    #error "DS_PIN_74HC595 is not defined. Please define the pin connected to DS of 74HC595."
#endif

#ifndef SHCP_PIN_74HC595
    #error "SHCP_PIN_74HC595 is not defined. Please define the pin connected to SH_CP of 74HC595."
#endif

#ifndef STCP_PIN_74HC595
    #error "STCP_PIN_74HC595 is not defined. Please define the pin connected to ST_CP of 74HC595."
#endif

#define _1_595_Q0 0
#define _1_595_Q1 1
#define _1_595_Q2 2
#define _1_595_Q3 3
#define _1_595_Q4 4
#define _1_595_Q5 5
#define _1_595_Q6 6
#define _1_595_Q7 7

#define _2_595_Q0 8
#define _2_595_Q1 9
#define _2_595_Q2 10
#define _2_595_Q3 11
#define _2_595_Q4 12
#define _2_595_Q5 13
#define _2_595_Q6 14
#define _2_595_Q7 15

void shift595_pin_init(void);
void shift595_pin_sleep(void);
void shift595_write_all(shift595_data_t data);
void shift595_write_pin_ex(uint8_t pin_index, uint8_t level, uint8_t other_level);
void shift595_write_all_high(void);
void shift595_write_all_low(void);