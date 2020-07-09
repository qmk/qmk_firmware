#include "quantum.h"
#include "ws2812.h"
#include "ch.h"
#include "hal.h"

/* Adapted from https://github.com/bigjosh/SimpleNeoPixelDemo/ */

#ifndef NOP_FUDGE
#    if defined(STM32F0XX) || defined(STM32F1XX) || defined(STM32F3XX) || defined(STM32F4XX) || defined(STM32L0XX)
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
#define CYCLES_PER_SEC (STM32_SYSCLK / NUMBER_NOPS * NOP_FUDGE)
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

// These are the timing constraints taken mostly from the WS2812 datasheets
// These are chosen to be conservative and avoid problems rather than for maximum throughput

#define T1H 900           // Width of a 1 bit in ns
#define T1L (1250 - T1H)  // Width of a 1 bit in ns

#define T0H 350           // Width of a 0 bit in ns
#define T0L (1250 - T0H)  // Width of a 0 bit in ns

// The reset gap can be 6000 ns, but depending on the LED strip it may have to be increased
// to values like 600000 ns. If it is too small, the pixels will show nothing most of the time.
#define RES (1000 * WS2812_TRST_US)  // Width of the low gap between bits to cause a frame to latch

void sendByte(uint8_t byte) {
    // WS2812 protocol wants most significant bits first
    for (unsigned char bit = 0; bit < 8; bit++) {
        bool is_one = byte & (1 << (7 - bit));
        // using something like wait_ns(is_one ? T1L : T0L) here throws off timings
        if (is_one) {
            // 1
            writePinHigh(RGB_DI_PIN);
            wait_ns(T1H);
            writePinLow(RGB_DI_PIN);
            wait_ns(T1L);
        } else {
            // 0
            writePinHigh(RGB_DI_PIN);
            wait_ns(T0H);
            writePinLow(RGB_DI_PIN);
            wait_ns(T0L);
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
        sendByte(ledarray[i].g);
        sendByte(ledarray[i].r);
        sendByte(ledarray[i].b);
#ifdef RGBW
        sendByte(ledarray[i].w);
#endif
    }

    wait_ns(RES);

    chSysUnlock();
}
