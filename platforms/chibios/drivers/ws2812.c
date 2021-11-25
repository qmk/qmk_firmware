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
#        define NOP_FUDGE 1  // this just pleases the compile so the above error is easier to spot
#    endif
#endif

// Push Pull or Open Drain Configuration
// Default Push Pull
#ifndef WS2812_EXTERNAL_PULLUP
#    define WS2812_OUTPUT_MODE PAL_MODE_OUTPUT_PUSHPULL
#else
#    define WS2812_OUTPUT_MODE PAL_MODE_OUTPUT_OPENDRAIN
#endif

#define NUMBER_NOPS 6
#define CYCLES_PER_SEC (CPU_CLOCK / NUMBER_NOPS * NOP_FUDGE)
#define NS_PER_SEC (1000000000L)  // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives
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

/* The WS2812 datasheets define T1H 900ns, T0H 350ns, T1L 350ns, T0L 900ns. Hence, by default, these are chosen to be conservative and avoid problems rather than for maximum throughput; in the code, this is done by default using a WS2812_TIMING parameter that accounts for the whole window (1250ns) and defining T1H and T0H; T1L and T0L are obtained by subtracting their low counterparts from the window.
However, there are certain "WS2812"-like LEDs, like the SK6812s, which work in a similar communication topology but use different timings for the window and the T1L, T1H, T0L and T0H. This means that, albeit the same driver being applicable, the timings must be adapted. The following defines are done such that the adjustment of these timings can be done in the keyboard's config.h; if nothing is said, the defines default to the WS2812 ones.
*/

#ifndef WS2812_TIMING
#    define WS2812_TIMING 1250
#endif

#ifndef WS2812_T1H
#    define WS2812_T1H 900  // Width of a 1 bit in ns
#endif

#ifndef WS2812_T1L
#    define WS2812_T1L (WS2812_TIMING - WS2812_T1H)  // Width of a 1 bit in ns
#endif

#ifndef WS2812_T0H
#    define WS2812_T0H 350  // Width of a 0 bit in ns
#endif

#ifndef WS2812_T0L
#    define WS2812_T0L (WS2812_TIMING - WS2812_T0H)  // Width of a 0 bit in ns
#endif

// The reset gap can be 6000 ns, but depending on the LED strip it may have to be increased
// to values like 600000 ns. If it is too small, the pixels will show nothing most of the time.
#ifndef WS2812_RES
#    define WS2812_RES (1000 * WS2812_TRST_US)  // Width of the low gap between bits to cause a frame to latch
#endif

void sendByte(uint8_t byte) {
    // WS2812 protocol wants most significant bits first
    for (unsigned char bit = 0; bit < 8; bit++) {
        bool is_one = byte & (1 << (7 - bit));
        // using something like wait_ns(is_one ? T1L : T0L) here throws off timings
        if (is_one) {
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

void ws2812_init(void) { palSetLineMode(RGB_DI_PIN, WS2812_OUTPUT_MODE); }

// Setleds for standard RGB
void ws2812_setleds(LED_TYPE *ledarray, uint16_t leds) {
    static bool s_init = false;
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
