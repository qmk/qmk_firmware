// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/* WS2812/SK6812 driver for the 3Think SK32F077 "serial LED" (SLED)
 * controller.
 *
 * The SK32F077 embeds a SLED peripheral that serializes a raw color byte
 * stream on its output pads (no CPU bit packing): the driver feeds it with
 * the packed ws2812_leds[] buffer through the native SK32 SLED low level
 * driver (hal_sled_lld.c).  The hardware drives WS2812-style LEDs with the
 * T0H/T1H/TRST time codes programmed in the SLED TCR register.
 */

#include "ws2812.h"

#if defined(HAL_USE_SLED) && defined(SK32F077)

#    include "hal.h"
#    include "hal_sled_lld.h"

/*
 * Configuration overrides, define them in config.h to change the default.
 */

// SLED group used by the LED string (SLED1 or SLED2).
#    ifndef WS2812_SLED_GROUP
#        define WS2812_SLED_GROUP SLED1
#    endif

// Output pad: 3Think mechanical RGB reference uses PB8 in alternate
// function 14 for the SLED1 output.
#    ifndef WS2812_SLED_PORT
#        define WS2812_SLED_PORT GPIOB
#    endif
#    ifndef WS2812_SLED_PIN
#        define WS2812_SLED_PIN 8U
#    endif
#    ifndef WS2812_SLED_AF
#        define WS2812_SLED_AF 14U
#    endif

// Complete PAL mode applied to the output pad.
#    ifndef WS2812_SLED_PAL_MODE
#        define WS2812_SLED_PAL_MODE (PAL_MODE_ALTERNATE(WS2812_SLED_AF) | PAL_SK32_OSPEED_HIGHEST)
#    endif

// Vendor reference timings (RGBKeyboardSTK): T0H=4, T1H=15, TRST=80 time
// code cycles, clock /4, baud /32.  They can be overridden per board.
#    ifndef WS2812_SLED_T0H
#        define WS2812_SLED_T0H 4U
#    endif
#    ifndef WS2812_SLED_T1H
#        define WS2812_SLED_T1H 15U
#    endif
#    ifndef WS2812_SLED_TRST
#        define WS2812_SLED_TRST 80U
#    endif
#    ifndef WS2812_SLED_PSC
#        define WS2812_SLED_PSC 3U
#    endif
#    ifndef WS2812_SLED_BRD
#        define WS2812_SLED_BRD 31U
#    endif

static const SLEDConfig ws2812_sled_config = {
    .t0h_cycles     = WS2812_SLED_T0H,
    .t1h_cycles     = WS2812_SLED_T1H,
    .trst_cycles    = WS2812_SLED_TRST,
    .prescaler      = WS2812_SLED_PSC,
    .baud_prescaler = WS2812_SLED_BRD,
    .idle_polarity  = SLED_POLARITY_LOW,
    .reset_polarity = SLED_POLARITY_LOW,
};

void ws2812_init(void) {
    // Route the pad to the SLED output (alternate function).
    palSetPadMode(WS2812_SLED_PORT, WS2812_SLED_PIN, WS2812_SLED_PAL_MODE);

    sled_lld_init();
    sled_lld_start(&ws2812_sled_config);
}

ws2812_led_t ws2812_leds[WS2812_LED_COUNT];

void ws2812_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    ws2812_leds[index].r = red;
    ws2812_leds[index].g = green;
    ws2812_leds[index].b = blue;
#    if defined(WS2812_RGBW)
    ws2812_rgb_to_rgbw(&ws2812_leds[index]);
#    endif
}

void ws2812_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < WS2812_LED_COUNT; i++) {
        ws2812_set_color(i, red, green, blue);
    }
}

void ws2812_flush(void) {
    // The packed ws2812_led_t layout is the wire byte order (GRB, GRBW...),
    // so the whole array is one contiguous color byte stream for the SLED.
    sled_lld_send_bytes(WS2812_SLED_GROUP, (const uint8_t *)ws2812_leds, sizeof(ws2812_leds));
}

#else
#    error "WS2812_DRIVER=sled is only supported on the SK32F077 (SK32F0xx) MCU with the ChibiOS platform"
#endif
