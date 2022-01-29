/* Copyright 2022 SevenLiang(@skyjun)
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

#define PRODUCT_ID   0x0001
#define DEVICE_VER   0x0001

#define MATRIX_ROW_PINS { B0, D1, D3 }
#define MATRIX_COL_PINS { D4, D6, D7, B4, B5, F6, F7, B1, B2, B3, B7, D0 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define RGB_DI_PIN          F0
#define RGBLED_NUM          32

// animations enable
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

#define RGBLIGHT_SLEEP

#define LED_PIN_ON_STATE    0
#define LED_CAPS_LOCK_PIN   F5
#define LED_NUM_LOCK_PIN    F4
// 按键灯，按下任意键都会亮一下
// press any key will turn on the light diode
#define LED_KEY_PRESS_PIN   F1

// trackpoint pin
#define PS2_CLOCK_PIN   D5
#define PS2_DATA_PIN    D2

// UART 方式
#ifdef PS2_USE_USART
#define PS2_USART_INIT() do {                   \
    PS2_CLOCK_DDR   &= ~(1 << PS2_CLOCK_BIT);   \
    PS2_DATA_DDR    &= ~(1 << PS2_DATA_BIT);    \
    UCSR1C          = ((1 << UMSEL10) |         \
                        (3 << UPM10) |          \
                        (0 << USBS1) |          \
                        (3 << UCSZ10) |         \
                        (0 << UCPOL1));         \
    UCSR1A          = 0;                        \
    UBRR1H          = 0;                        \
    UBRR1L          = 0;                        \
} while (0)
#define PS2_USART_RX_INT_ON() do {              \
    UCSR1B          = ((1 << RXCIE1) |          \
                        (1 << RXEN1));          \
} while (0)
#define PS2_USART_RX_POLL_ON() do {             \
    UCSR1B          = (1 << RXEN1);             \
} while (0)
#define PS2_USART_OFF() do {                    \
    UCSR1C          = 0;                        \
    UCSR1B          &= ~((1 << RXEN1) |         \
                        (1 << TXEN1));          \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1 << RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1 << FE1) | (1 << DOR1) | (1 << UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect
#endif

// 中断方式
#ifdef PS2_USE_INT
#define PS2_INT_INIT() do {                     \
    EICRA           |= ((1 << ISC21) |          \
                        (0 << ISC20));          \
} while (0)
#define PS2_INT_ON() do {                       \
    EIMSK           |= (1 << INT2);             \
} while (0)
#define PS2_INT_OFF() do {                      \
    EIMSK           &= ~(1 << INT2);            \
} while (0)
#define PS2_INT_VECT    INT2_vect
#endif
