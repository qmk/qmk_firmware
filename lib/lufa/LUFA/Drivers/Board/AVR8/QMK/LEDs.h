/*
Copyright 2017 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/** \file
 *  \brief General driver header for QMK-powered keyboards.
 *  \copydetails Group_LEDs_QMK
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_QMK QMK
 *  \brief General driver header for QMK-powered keyboards.
 *
 *  General driver header for QMK-powered keyboards (http://qmk.fm).
 *
 *  <b>QMK</b>:
 *  <table>
 *    <tr><th>Name</th><th>Color</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>LEDS_LED1</td><td>Green</td><td>General Indicator</td><td>High</td><td>PORT(QMK_LED).6</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __LEDS_QMK_H__
#define __LEDS_QMK_H__

    /* Includes: */
        #include "../../../../Common/Common.h"

    /* Enable C linkage for C++ Compilers: */
        #if defined(__cplusplus)
            extern "C" {
        #endif

    /* Preprocessor Checks: */
        #if !defined(__INCLUDE_FROM_LEDS_H)
            #error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
        #endif

        #define B0 0x30
        #define B1 0x31
        #define B2 0x32
        #define B3 0x33
        #define B4 0x34
        #define B5 0x35
        #define B6 0x36
        #define B7 0x37
        #define C0 0x60
        #define C1 0x61
        #define C2 0x62
        #define C3 0x63
        #define C4 0x64
        #define C5 0x65
        #define C6 0x66
        #define C7 0x67
        #define D0 0x90
        #define D1 0x91
        #define D2 0x92
        #define D3 0x93
        #define D4 0x94
        #define D5 0x95
        #define D6 0x96
        #define D7 0x97
        #define E0 0xC0
        #define E1 0xC1
        #define E2 0xC2
        #define E3 0xC3
        #define E4 0xC4
        #define E5 0xC5
        #define E6 0xC6
        #define E7 0xC7
        #define F0 0xF0
        #define F1 0xF1
        #define F2 0xF2
        #define F3 0xF3
        #define F4 0xF4
        #define F5 0xF5
        #define F6 0xF6
        #define F7 0xF7
        #define A0 0x00
        #define A1 0x01
        #define A2 0x02
        #define A3 0x03
        #define A4 0x04
        #define A5 0x05
        #define A6 0x06
        #define A7 0x07

        #define QMK_ESC_COL F1
        #define QMK_ESC_ROW D5
        #define QMK_LED     E6
        #define QMK_SPEAKER C6

        #define DDR(pin) _SFR_IO8(((pin) >> 4) + 1)
        #define PORT(pin) _SFR_IO8(((pin) >> 4) + 2)
        #define PIN(pin) _SFR_IO8((pin) >> 4)
        #define NUM(pin) _BV((pin) & 0xF)

    /* Public Interface - May be used in end-application: */
        /* Macros: */
            /** LED mask for the first LED on the board. */
            #define LEDS_LED1        NUM(QMK_LED)
            #define LEDS_LED2        NUM(QMK_SPEAKER)

            /** LED mask for all the LEDs on the board. */
            #define LEDS_ALL_LEDS    LEDS_LED1 | LEDS_LED2

            /** LED mask for none of the board LEDs. */
            #define LEDS_NO_LEDS     0

        /* Inline Functions: */
        #if !defined(__DOXYGEN__)
            static inline void LEDs_Init(void)
            {
                DDR(QMK_LED)  |= LEDS_LED1;
                PORT(QMK_LED) |= LEDS_LED1;

                DDR(QMK_SPEAKER)  |= LEDS_LED2;
                PORT(QMK_SPEAKER) |= LEDS_LED2;
            }

            static inline void LEDs_Disable(void)
            {
                DDR(QMK_LED)  &= ~LEDS_LED1;
                PORT(QMK_LED) &= ~LEDS_LED2;

                DDR(QMK_SPEAKER)  &= ~LEDS_LED1;
                PORT(QMK_SPEAKER) &= ~LEDS_LED2;
            }

            static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
            {
                PORT(QMK_LED) &= (LEDS_LED1 & ~LEDMask);
                PORT(QMK_SPEAKER) &= (LEDS_LED2 & ~LEDMask);
            }

            static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
            {
                PORT(QMK_LED) |=  (LEDS_LED1 & LEDMask);
                PORT(QMK_SPEAKER) |=  (LEDS_LED2 & LEDMask);
            }

            static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
            {
                PORT(QMK_LED) = ((PORT(QMK_LED) | LEDS_LED1) & ~LEDMask);
                PORT(QMK_SPEAKER) = ((PORT(QMK_SPEAKER) | LEDS_LED2) & ~LEDMask);
            }

            static inline void LEDs_ChangeLEDs(const uint8_t LEDMask,
                                               const uint8_t ActiveMask)
            {
                PORT(QMK_LED) = ((PORT(QMK_LED) | (LEDS_LED1 & LEDMask)) & ~ActiveMask);
                PORT(QMK_SPEAKER) = ((PORT(QMK_SPEAKER) | (LEDS_LED1 & LEDMask)) & ~ActiveMask);
            }

            static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
            {
                PIN(QMK_LED)  = (LEDS_LED1 & LEDMask);
                PIN(QMK_SPEAKER)  = (LEDS_LED2 & LEDMask);
            }

            static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
            static inline uint8_t LEDs_GetLEDs(void)
            {
                return (~PORT(QMK_LED) & LEDS_LED1) | (~(PORT(QMK_SPEAKER) & LEDS_LED2));
            }
        #endif

    /* Disable C linkage for C++ Compilers: */
        #if defined(__cplusplus)
            }
        #endif

#endif

/** @} */

