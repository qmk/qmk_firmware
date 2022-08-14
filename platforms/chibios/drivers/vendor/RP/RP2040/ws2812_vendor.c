// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "ws2812.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#if !defined(MCU_RP)
#    error PIO Driver is only available for Raspberry Pi 2040 MCUs!
#endif

#if defined(WS2812_PIO_USE_PIO1)
static const PIO pio = pio1;
#else
static const PIO pio = pio0;
#endif

#if !defined(RP_DMA_PRIORITY_WS2812)
#    define RP_DMA_PRIORITY_WS2812 12
#endif

static int state_machine = -1;

#define WS2812_WRAP_TARGET 0
#define WS2812_WRAP 3

#define WS2812_T1 2
#define WS2812_T2 5
#define WS2812_T3 3

#if defined(WS2812_EXTERNAL_PULLUP)

#    pragma message "The GPIOs of the RP2040 are NOT 5V tolerant! Make sure to NOT apply any voltage over 3.3V to the RGB data pin."

// clang-format off
static const uint16_t ws2812_program_instructions[] = {
            //     .wrap_target
    0x7221, //  0: out    x, 1            side 1 [2]
    0x0123, //  1: jmp    !x, 3           side 0 [1]
    0x0400, //  2: jmp    0               side 0 [4]
    0xb442, //  3: nop                    side 1 [4]
            //     .wrap
};

#else

static const uint16_t ws2812_program_instructions[] = {
             //     .wrap_target
    0x6221,  //  0: out    x, 1            side 0 [2]
    0x1123,  //  1: jmp    !x, 3           side 1 [1]
    0x1400,  //  2: jmp    0               side 1 [4]
    0xa442,  //  3: nop                    side 0 [4]
             //     .wrap
};
// clang-format on
#endif

static const pio_program_t ws2812_program = {
    .instructions = ws2812_program_instructions,
    .length       = 4,
    .origin       = -1,
};

static uint32_t                WS2812_BUFFER[WS2812_LED_COUNT];
static const rp_dma_channel_t* WS2812_DMA_CHANNEL;

bool ws2812_init(void) {
    uint pio_idx = pio_get_index(pio);
    /* Get PIOx peripheral out of reset state. */
    hal_lld_peripheral_unreset(pio_idx == 0 ? RESETS_ALLREG_PIO0 : RESETS_ALLREG_PIO1);

    // clang-format off
    iomode_t rgb_pin_mode = PAL_RP_PAD_SLEWFAST |
                            PAL_RP_GPIO_OE |
                            (pio_idx == 0 ? PAL_MODE_ALTERNATE_PIO0 : PAL_MODE_ALTERNATE_PIO1);
    // clang-format on

    palSetLineMode(RGB_DI_PIN, rgb_pin_mode);

    state_machine = pio_claim_unused_sm(pio, true);
    if (state_machine < 0) {
        dprintln("ERROR: Failed to acquire state machine for WS2812 output!");
        return false;
    }

    uint offset = pio_add_program(pio, &ws2812_program);

    pio_sm_set_consecutive_pindirs(pio, state_machine, RGB_DI_PIN, 1, true);

    pio_sm_config config = pio_get_default_sm_config();
    sm_config_set_wrap(&config, offset + WS2812_WRAP_TARGET, offset + WS2812_WRAP);
    sm_config_set_sideset_pins(&config, RGB_DI_PIN);
    sm_config_set_fifo_join(&config, PIO_FIFO_JOIN_TX);

#if defined(WS2812_EXTERNAL_PULLUP)
    /* Instruct side-set to change the pin-directions instead of outputting
     * a logic level. We generate our levels the following way:
     *
     * 1: Set RGB data pin to high impedance input and let the pull-up drive the
     * signal high.
     *
     * 0: Set RGB data pin to low impedance output and drive the pin low.
     */
    sm_config_set_sideset(&config, 1, false, true);
#else
    sm_config_set_sideset(&config, 1, false, false);
#endif

#if defined(RGBW)
    sm_config_set_out_shift(&config, false, true, 32);
#else
    sm_config_set_out_shift(&config, false, true, 24);
#endif

    int   cycles_per_bit = WS2812_T1 + WS2812_T2 + WS2812_T3;
    float div            = clock_get_hz(clk_sys) / (800.0f * KHZ * cycles_per_bit);
    sm_config_set_clkdiv(&config, div);

    pio_sm_init(pio, state_machine, offset, &config);
    pio_sm_set_enabled(pio, state_machine, true);

    WS2812_DMA_CHANNEL = dmaChannelAlloc(RP_DMA_CHANNEL_ID_ANY, RP_DMA_PRIORITY_WS2812, NULL, NULL);

    // clang-format off
    uint32_t mode = DMA_CTRL_TRIG_INCR_READ |
                    DMA_CTRL_TRIG_DATA_SIZE_WORD |
                    DMA_CTRL_TRIG_IRQ_QUIET |
                    DMA_CTRL_TRIG_TREQ_SEL(pio_idx == 0 ? state_machine : state_machine + 8);
    // clang-format on

    dmaChannelSetModeX(WS2812_DMA_CHANNEL, mode);
    dmaChannelSetDestinationX(WS2812_DMA_CHANNEL, (uint32_t)&pio->txf[state_machine]);
    return true;
}

/**
 * @brief Convert RGBW value into WS2812 compatible 32-bit data word.
 */
__always_inline static uint32_t rgbw8888_to_u32(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
#if (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_GRB)
    return ((uint32_t)green << 24) | ((uint32_t)red << 16) | ((uint32_t)blue << 8) | ((uint32_t)white);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_RGB)
    return ((uint32_t)red << 24) | ((uint32_t)green << 16) | ((uint32_t)blue << 8) | ((uint32_t)white);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_BGR)
    return ((uint32_t)blue << 24) | ((uint32_t)green << 16) | ((uint32_t)red << 8) | ((uint32_t)white);
#endif
}

static inline void sync_ws2812_transfer(void) {
    if (unlikely(dmaChannelIsBusyX(WS2812_DMA_CHANNEL) || !pio_sm_is_tx_fifo_empty(pio, state_machine))) {
        fast_timer_t start = timer_read_fast();
        do {
            // Abort the synchronization if we have to wait longer than the total
            // count of LEDs in millisecounds. This is safely much longer than it
            // would take to push all the data out.
            if (unlikely(timer_elapsed_fast(start) > WS2812_LED_COUNT)) {
                dprintln("ERROR: WS2812 DMA transfer has stalled, aborting!");
                dmaChannelDisableX(WS2812_DMA_CHANNEL);
                return;
            }

        } while (dmaChannelIsBusyX(WS2812_DMA_CHANNEL) || !pio_sm_is_tx_fifo_empty(pio, state_machine));
        // We wait for the WS2812 chain to reset after all data has been pushed
        // out.
        wait_us(WS2812_TRST_US);
    }
}

void ws2812_setleds(LED_TYPE* ledarray, uint16_t leds) {
    static bool is_initialized = false;
    if (unlikely(!is_initialized)) {
        is_initialized = ws2812_init();
    }

    sync_ws2812_transfer();

    for (int i = 0; i < leds; i++) {
#if defined(RGBW)
        WS2812_BUFFER[i] = rgbw8888_to_u32(ledarray[i].r, ledarray[i].g, ledarray[i].b, ledarray[i].w);
#else
        WS2812_BUFFER[i] = rgbw8888_to_u32(ledarray[i].r, ledarray[i].g, ledarray[i].b, 0);
#endif
    }

    dmaChannelSetSourceX(WS2812_DMA_CHANNEL, (uint32_t)WS2812_BUFFER);
    dmaChannelSetCounterX(WS2812_DMA_CHANNEL, leds);
    dmaChannelEnableX(WS2812_DMA_CHANNEL);
}
