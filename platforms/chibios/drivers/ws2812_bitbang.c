#include "ws2812.h"

#include "gpio.h"
#include "chibios_config.h"

// DEPRECATED - DO NOT USE
#if defined(NOP_FUDGE)
#    define WS2812_BITBANG_NOP_FUDGE NOP_FUDGE
#endif

/* Adapted from https://github.com/bigjosh/SimpleNeoPixelDemo/ */

#ifndef WS2812_BITBANG_NOP_FUDGE
#    if defined(STM32F0XX) || defined(STM32F1XX) || defined(GD32VF103) || defined(STM32F3XX) || defined(STM32F4XX) || defined(STM32L0XX) || defined(WB32F3G71xx) || defined(WB32FQ95xx) || defined(AT32F415)
#        define WS2812_BITBANG_NOP_FUDGE 0.4
#    else
#        if defined(RP2040)
#            error "Please use `vendor` WS2812 driver for RP2040"
#        else
#            error "WS2812_BITBANG_NOP_FUDGE configuration required"
#        endif
#        define WS2812_BITBANG_NOP_FUDGE 1 // this just pleases the compile so the above error is easier to spot
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
#define CYCLES_PER_SEC (CPU_CLOCK / NUMBER_NOPS * WS2812_BITBANG_NOP_FUDGE)
#define NS_PER_SEC (1000000000L) // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives
#define NS_PER_CYCLE (NS_PER_SEC / CYCLES_PER_SEC)
#define NS_TO_CYCLES(n) ((n) / NS_PER_CYCLE)

// NS_TO_CYCLES(n) rounded up, as the former C loop counted it
#define NS_TO_PASSES(n) ((int)NS_TO_CYCLES(n) + ((int)NS_TO_CYCLES(n) < NS_TO_CYCLES(n)))
#define NOPS "nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"
#if defined(__riscv)
#    define COUNT_DOWN "addi %0, %0, -1\n\tbnez %0, 1b"
#    define COUNTER "+r"
#elif defined(__thumb2__)
#    define COUNT_DOWN "subs %0, %0, #1\n\tbne 1b"
#    define COUNTER "+l"
#else // Thumb-1: divided syntax, and the cmp GCC emits
#    define COUNT_DOWN "sub %0, #1\n\tcmp %0, #0\n\tbne 1b"
#    define COUNTER "+l"
#endif

// In assembly so the timing does not depend on the compiler: up to two passes unrolled as GCC 14 did, more in a loop
#define wait_ns(x)                                                                              \
    do {                                                                                        \
        if (NS_TO_PASSES(x) <= 2) {                                                             \
            __asm__ volatile(".rept %c0\n\t" NOPS ".endr" : : "i"(NS_TO_PASSES(x)) : "memory"); \
        } else {                                                                                \
            uint32_t passes = NS_TO_PASSES(x);                                                  \
            __asm__ volatile("1:\n\t" NOPS COUNT_DOWN : COUNTER(passes) : : "cc", "memory");    \
        }                                                                                       \
    } while (0)

void sendByte(uint8_t byte) {
    // WS2812 protocol wants most significant bits first
    for (unsigned char bit = 0; bit < 8; bit++) {
        bool is_one = byte & (1 << (7 - bit));
        // using something like wait_ns(is_one ? T1L : T0L) here throws off timings
        if (is_one) {
            // 1
            gpio_write_pin_high(WS2812_DI_PIN);
            wait_ns(WS2812_T1H);
            gpio_write_pin_low(WS2812_DI_PIN);
            wait_ns(WS2812_T1L);
        } else {
            // 0
            gpio_write_pin_high(WS2812_DI_PIN);
            wait_ns(WS2812_T0H);
            gpio_write_pin_low(WS2812_DI_PIN);
            wait_ns(WS2812_T0L);
        }
    }
}

ws2812_led_t ws2812_leds[WS2812_LED_COUNT];

void ws2812_init(void) {
    palSetLineMode(WS2812_DI_PIN, WS2812_OUTPUT_MODE);
}

void ws2812_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    ws2812_leds[index].r = red;
    ws2812_leds[index].g = green;
    ws2812_leds[index].b = blue;
#if defined(WS2812_RGBW)
    ws2812_rgb_to_rgbw(&ws2812_leds[index]);
#endif
}

void ws2812_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < WS2812_LED_COUNT; i++) {
        ws2812_set_color(i, red, green, blue);
    }
}

void ws2812_flush(void) {
    // this code is very time dependent, so we need to disable interrupts
    chSysLock();

    for (int i = 0; i < WS2812_LED_COUNT; i++) {
        // WS2812 protocol dictates grb order
#if (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_GRB)
        sendByte(ws2812_leds[i].g);
        sendByte(ws2812_leds[i].r);
        sendByte(ws2812_leds[i].b);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_RGB)
        sendByte(ws2812_leds[i].r);
        sendByte(ws2812_leds[i].g);
        sendByte(ws2812_leds[i].b);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_BGR)
        sendByte(ws2812_leds[i].b);
        sendByte(ws2812_leds[i].g);
        sendByte(ws2812_leds[i].r);
#endif

#ifdef WS2812_RGBW
        sendByte(ws2812_leds[i].w);
#endif
    }

    wait_ns(WS2812_RES);

    chSysUnlock();
}
