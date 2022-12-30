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
#    define WS2812_RES (WS2812_TRST_US) // Width of the low gap between bits to cause a frame to latch
#endif

#define wait_ns(x) { \
    for (int i = 0; i < x; i++) { \
        __asm__ volatile("nop\n\tnop\n\tnop\n\tnop\n\t" \
                         "nop\n\tnop\n\tnop\n\tnop\n\t" \
                         "nop\n\tnop\n\tnop\n\tnop\n\t" \
                         "nop\n\tnop\n\tnop\n\tnop\n\t" \
                         "nop\n\tnop\n\tnop\n\tnop\n\t"); \
    } \
}

#define wait_bit1H() { \
    __asm__ volatile("nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\tnop\n\tnop\n\t"); \
}
#define wait_bit1L() { \
    __asm__ volatile("nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\t"); }

#define wait_bit0H() { \
    __asm__ volatile("nop\n\tnop\n\tnop\n\tnop\n\t"); }
#define wait_bit0L() { \
    __asm__ volatile("nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\tnop\n\tnop\n\t" \
                     "nop\n\tnop\n\tnop\n\tnop\n\t"); \
}

static void sendByte(uint8_t byte, uint8_t start) {
    // WS2812 protocol wants most significant bits first
    for (unsigned char bit = start; bit < 8; bit++) {
        // using something like wait_ns(is_one ? T1L : T0L) here throws off timings
        if (byte & (0x80 >> bit)) {
            // 1
            writePinHigh(RGB_DI_PIN);
            wait_bit1H();
            writePinLow(RGB_DI_PIN);
            wait_bit1L();
        } else {
            // 0
            writePinHigh(RGB_DI_PIN);
            wait_bit0H();
            writePinLow(RGB_DI_PIN);
            wait_bit0L();
        }
    }
}

enum { DATA_HEADER = 0x00, CURRENT_HEADER = 0x02 };
enum { I_0_35mA = 0x00, I_0_7mA = 0x01, I_1_05mA = 0x02, I_1_4mA = 0x03, I_1_75mA = 0x04, I_2_1mA = 0x05, I_2_45mA = 0x06, I_2_8mA = 0x07, 
       I_3_15mA = 0x08, I_3_5mA = 0x09, I_3_85mA = 0x0A, I_4_2mA = 0x0B, I_4_55mA = 0x0C, I_4_9mA = 0x0D, I_5_25mA = 0x0E, I_5_5mA = 0x0F, };
static void set_led_current(uint8_t ri, uint8_t gi, uint8_t bi) {
    // this code is very time dependent, so we need to disable interrupts
    chSysLock();

    writePinLow(RGB_DI_PIN);
    wait_ns(WS2812_RES);
    sendByte(CURRENT_HEADER, 0);
    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        // WS2812 protocol dictates grb order
#if (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_GRB)
        sendByte(gi, 2);
        sendByte(ri, 2);
        sendByte(bi, 2);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_RGB)
        sendByte(ri, 2);
        sendByte(gi, 2);
        sendByte(bi, 2);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_BGR)
        sendByte(bi, 2);
        sendByte(gi, 2);
        sendByte(ri, 2);
#endif
    }

    writePinHigh(RGB_DI_PIN);
    wait_bit0H();
    writePinLow(RGB_DI_PIN);

    chSysUnlock();
}

void ws2812_init(void) {
    palSetLineMode(RGB_DI_PIN, WS2812_OUTPUT_MODE);
}

#ifndef GW6606_SETUP_COUNTS
#   define GW6606_SETUP_COUNTS 5
#endif

#ifndef GW6606_CURRENT
#   define GW6606_CURRENT I_2_1mA
#endif

#ifndef GW6606_SETUP_INTERVAL
#   define GW6606_SETUP_INTERVAL 1000
#endif

static bool p_setup = false;
static bool s_init = false;
static uint8_t c_init = GW6606_SETUP_COUNTS;
static uint32_t c_timer = 0;
void ws2812_poweron(void) {
    if(p_setup) return;
    p_setup = true;
    s_init = false;
    c_init = GW6606_SETUP_COUNTS;
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

    if(!c_init && timer_elapsed32(c_timer) > GW6606_SETUP_INTERVAL) {
        c_init = 2;
    }

    if(c_init) {
        c_init--;
        set_led_current(GW6606_CURRENT, GW6606_CURRENT, GW6606_CURRENT);
        c_timer = timer_read32();
    }

    // this code is very time dependent, so we need to disable interrupts
    chSysLock();

    writePinLow(RGB_DI_PIN);
    wait_ns(WS2812_RES);
    sendByte(DATA_HEADER, 0);
    for (uint8_t i = 0; i < leds; i++) {
        // WS2812 protocol dictates grb order
#if (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_GRB)
        sendByte(ledarray[i].g, 0);
        sendByte(0, 0);
        sendByte(ledarray[i].r, 0);
        sendByte(0, 0);
        sendByte(ledarray[i].b, 0);
        sendByte(0, 0);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_RGB)
        sendByte(ledarray[i].r, 0);
        sendByte(0, 0);
        sendByte(ledarray[i].g, 0);
        sendByte(0, 0);
        sendByte(ledarray[i].b, 0);
        sendByte(0, 0);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_BGR)
        sendByte(ledarray[i].b, 0);
        sendByte(0, 0);
        sendByte(ledarray[i].g, 0);
        sendByte(0, 0);
        sendByte(ledarray[i].r, 0);
        sendByte(0, 0);
#endif

#ifdef RGBW
        sendByte(ledarray[i].w, 0);
        sendByte(0, 0);
#endif
    }

    writePinHigh(RGB_DI_PIN);
    wait_bit0H();
    writePinLow(RGB_DI_PIN);

    chSysUnlock();
}
