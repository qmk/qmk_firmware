/* Copyright 2022 MIIIW <www.miiiw.com>
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

#include "quantum.h"
#include "ws2812.h"
#include <ch.h>
#include <hal.h>

/* Adapted from https://github.com/bigjosh/SimpleNeoPixelDemo/ */

#ifndef NOP_FUDGE
#    if defined(STM32F0XX) || defined(STM32F1XX) || defined(GD32VF103) || defined(STM32F3XX) || defined(STM32F4XX) || defined(STM32L0XX)
#        define NOP_FUDGE 0.4
#    else
#        error("NOP_FUDGE configuration required")
#        define NOP_FUDGE 1 // this just pleases the compile so the above error is easier to spot
#    endif
#endif

// Push Pull or Open Drain Configuration
// Default Push Pull
#ifndef WS2812_EXTERNAL_PULLUP
#    define WS2812_OUTPUT_MODE PAL_MODE_OUTPUT_PUSHPULL
#else
#    define WS2812_OUTPUT_MODE PAL_MODE_OUTPUT_OPENDRAIN
#endif

// The reset gap can be 6000 ns, but depending on the LED strip it may have to be increased
// to values like 600000 ns. If it is too small, the pixels will show nothing most of the time.
#ifndef WS2812_RES
#    define WS2812_RES (1000 * WS2812_TRST_US) // Width of the low gap between bits to cause a frame to latch
#endif

#define NUMBER_NOPS 6
#define CYCLES_PER_SEC (CPU_CLOCK / NUMBER_NOPS * NOP_FUDGE)
#define NS_PER_SEC (1000000000L) // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives
#define NS_PER_CYCLE (NS_PER_SEC / CYCLES_PER_SEC)
#define NS_TO_CYCLES(n) ((n) / NS_PER_CYCLE)

#define wait_ns(x)                                  \
    do {                                            \
        for (int i = 0; i < NS_TO_CYCLES(x); i++) { \
            __asm__ volatile("nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t");            \
        }                                           \
    } while (0)

static void sendByte(uint8_t byte) {
    // WS2812 protocol wants most significant bits first
    for (unsigned char bit = 0; bit < 8; bit++) {
        // using something like wait_ns(is_one ? T1L : T0L) here throws off timings
        if (byte & (0x80 >> bit)) {
            // 1
            writePinHigh(RGB_DI_PIN);
            wait_ns(WS2812_T1H);
            writePinLow(RGB_DI_PIN);
            wait_ns(WS2812_T1L);
        } else {
            // 0
            writePinHigh(RGB_DI_PIN);
            wait_ns(WS2812_T0H);
            writePinLow(RGB_DI_PIN);
            wait_ns(WS2812_T0L);
        }
    }
}

void ws2812_init(void) {
    palSetLineMode(RGB_DI_PIN, WS2812_OUTPUT_MODE);
}

static bool p_setup = false;
static bool s_init = false;
void ws2812_poweron(void) {
    if(p_setup) return;
    p_setup = true;
    s_init = false;
    setPinOutput(RGB_EN_PIN);
    writePinHigh(RGB_EN_PIN);
}

void ws2812_poweroff(void) {
    if(!p_setup) return;
    p_setup = false;
    setPinInputLow(RGB_DI_PIN);
    writePinLow(RGB_EN_PIN);
}

// Setleds for standard RGB
void ws2812_setleds(LED_TYPE *ledarray, uint16_t leds) {
    if(!p_setup) return;

    if (!s_init) {
        ws2812_init();
        s_init = true;
    }

    // this code is very time dependent, so we need to disable interrupts
    chSysLock();

    for (uint8_t i = 0; i < leds; i++) {
        // WS2812 protocol dictates grb order
#if (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_GRB)
        sendByte(ledarray[i].g);
        sendByte(ledarray[i].r);
        sendByte(ledarray[i].b);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_RGB)
        sendByte(ledarray[i].r);
        sendByte(ledarray[i].g);
        sendByte(ledarray[i].b);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_BGR)
        sendByte(ledarray[i].b);
        sendByte(ledarray[i].g);
        sendByte(ledarray[i].r);
#endif

#ifdef RGBW
        sendByte(ledarray[i].w);
#endif
    }

    wait_ns(WS2812_RES);

    chSysUnlock();
}
