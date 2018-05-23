/**
 * @file    ws2812.c
 * @author  Austin Glaser <austin.glaser@gmail.com>
 * @brief   WS2812 LED driver
 *
 * Copyright (C) 2016 Austin Glaser
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 * @todo    Put in names and descriptions of variables which need to be defined to use this file
 *
 * @addtogroup WS2812
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

// This Driver
#include "ws2812.h"

// Standard
#include <stdint.h>

// ChibiOS
#include "ch.h"
#include "hal.h"

// Application
#include "board.h"
#include "util.h"

/* --- CONFIGURATION CHECK -------------------------------------------------- */

#if !defined(WS2812_LED_N)
    #error WS2812 LED chain length not specified
#elif WS2812_LED_N <= 0
    #error WS2812 LED chain length set to invalid value
#endif

#if !defined(WS2812_TIM_N)
    #error WS2812 timer not specified
#endif
#if defined(STM32F2XX) || defined(STM32F3XX) || defined(STM32F4XX) || defined(STM32F7XX)
    #if WS2812_TIM_N <= 2
        #define WS2812_AF 1
    #elif WS2812_TIM_N <= 5
        #define WS2812_AF 2
    #elif WS2812_TIM_N <= 11
        #define WS2812_AF 3
    #endif
#elif !defined(WS2812_AF)
    #error WS2812_AF timer alternate function not specified
#endif

#if !defined(WS2812_TIM_CH)
    #error WS2812 timer channel not specified
#elif WS2812_TIM_CH >= 4
    #error WS2812 timer channel set to invalid value
#endif

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */

#define WS2812_PWM_FREQUENCY    (STM32_SYSCLK/2)                            /**< Clock frequency of PWM */
#define WS2812_PWM_PERIOD       (WS2812_PWM_FREQUENCY/800000)               /**< Clock period in ticks. 90/(72 MHz) = 1.25 uS (as per datasheet) */

/**
 * @brief   Number of bit-periods to hold the data line low at the end of a frame
 *
 * The reset period for each frame must be at least 50 uS; so we add in 50 bit-times
 * of zeroes at the end. (50 bits)*(1.25 uS/bit) = 62.5 uS, which gives us some
 * slack in the timing requirements
 */
#define WS2812_RESET_BIT_N      (50)
#define WS2812_COLOR_BIT_N      (WS2812_LED_N*24)                           /**< Number of data bits */
#define WS2812_BIT_N            (WS2812_COLOR_BIT_N + WS2812_RESET_BIT_N)   /**< Total number of bits in a frame */

/**
 * @brief   High period for a zero, in ticks
 *
 * Per the datasheet:
 * - T0H: 0.200 uS to 0.500 uS, inclusive
 * - T0L: 0.650 uS to 0.950 uS, inclusive
 *
 * With a duty cycle of 22 ticks, we have a high period of 22/(72 MHz) = 3.06 uS, and
 * a low period of (90 - 22)/(72 MHz) = 9.44 uS. These values are within the allowable
 * bounds, and intentionally skewed as far to the low duty-cycle side as possible
 */
#define WS2812_DUTYCYCLE_0      (WS2812_PWM_FREQUENCY/(1000000000/350))

/**
 * @brief   High period for a one, in ticks
 *
 * Per the datasheet:
 * - T0H: 0.550 uS to 0.850 uS, inclusive
 * - T0L: 0.450 uS to 0.750 uS, inclusive
 *
 * With a duty cycle of 56 ticks, we have a high period of 56/(72 MHz) = 7.68 uS, and
 * a low period of (90 - 56)/(72 MHz) = 4.72 uS. These values are within the allowable
 * bounds, and intentionally skewed as far to the high duty-cycle side as possible
 */
#define WS2812_DUTYCYCLE_1      (WS2812_PWM_FREQUENCY/(1000000000/800))

/* --- PRIVATE MACROS ------------------------------------------------------- */

/**
 * @brief   Generates a reference to a numbered PWM driver
 *
 * @param[in] n:            The driver (timer) number
 *
 * @return                  A reference to the driver
 */
#define PWMD(n)                             CONCAT_EXPANDED_SYMBOLS(PWMD, n)

#define WS2812_PWMD                         PWMD(WS2812_TIM_N)      /**< The PWM driver to use for the LED chain */

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given bit
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_N)
 * @param[in] byte:                 The byte number [0, 2]
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#define WS2812_BIT(led, byte, bit)          (24*(led) + 8*(byte) + (7 - (bit)))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given red bit
 *
 * @note    The red byte is the middle byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_N)
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#define WS2812_RED_BIT(led, bit)            WS2812_BIT((led), 1, (bit))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given green bit
 *
 * @note    The red byte is the first byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_N)
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#define WS2812_GREEN_BIT(led, bit)          WS2812_BIT((led), 0, (bit))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given blue bit
 *
 * @note    The red byte is the last byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_N)
 * @param[in] bit:                  The bit index [0, 7]
 *
 * @return                          The bit index
 */
#define WS2812_BLUE_BIT(led, bit)           WS2812_BIT((led), 2, (bit))

/* --- PRIVATE VARIABLES ---------------------------------------------------- */

static uint8_t ws2812_frame_buffer[WS2812_BIT_N];                             /**< Buffer for a frame */

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

void ws2812_init(void)
{
    // Initialize led frame buffer
    uint32_t i;
    for (i = 0; i < WS2812_COLOR_BIT_N; i++) ws2812_frame_buffer[i]                       = WS2812_DUTYCYCLE_0;   // All color bits are zero duty cycle
    for (i = 0; i < WS2812_RESET_BIT_N; i++) ws2812_frame_buffer[i + WS2812_COLOR_BIT_N]  = 0;                    // All reset bits are zero

    // Configure PA1 as AF output
#ifdef WS2812_EXTERNAL_PULLUP
    palSetPadMode(PORT_WS2812, PIN_WS2812, PAL_MODE_ALTERNATE(WS2812_AF) | PAL_STM32_OTYPE_OPENDRAIN);
#else
    palSetPadMode(PORT_WS2812, PIN_WS2812, PAL_MODE_ALTERNATE(WS2812_AF));
#endif

    // PWM Configuration
    #pragma GCC diagnostic ignored "-Woverride-init"                                        // Turn off override-init warning for this struct. We use the overriding ability to set a "default" channel config
    static const PWMConfig ws2812_pwm_config = {
        .frequency          = WS2812_PWM_FREQUENCY,
        .period             = WS2812_PWM_PERIOD,
        .callback           = NULL,
        .channels = {
            [0 ... 3]       = {.mode = PWM_OUTPUT_DISABLED,     .callback = NULL},          // Channels default to disabled
            [WS2812_TIM_CH] = {.mode = PWM_OUTPUT_ACTIVE_HIGH,  .callback = NULL},          // Turn on the channel we care about
        },
        .cr2                = 0,
        .dier               = TIM_DIER_UDE,                                                 // DMA on update event for next period
    };
    #pragma GCC diagnostic pop                                                              // Restore command-line warning options

    // Configure DMA
    dmaStreamAllocate(WS2812_DMA_STREAM, 10, NULL, NULL);
    dmaStreamSetPeripheral(WS2812_DMA_STREAM, &(WS2812_PWMD.tim->CCR[WS2812_TIM_CH]));
    dmaStreamSetMemory0(WS2812_DMA_STREAM, ws2812_frame_buffer);
    dmaStreamSetTransactionSize(WS2812_DMA_STREAM, WS2812_BIT_N);
    dmaStreamSetMode(WS2812_DMA_STREAM,
                     STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_BYTE |
                     STM32_DMA_CR_MINC | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));
      //STM32_DMA_CR_CHSEL(WS2812_DMA_CHANNEL) | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD |
      //STM32_DMA_CR_MINC | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));

    // Start DMA
    dmaStreamEnable(WS2812_DMA_STREAM);

    // Configure PWM
    // NOTE: It's required that preload be enabled on the timer channel CCR register. This is currently enabled in the
    // ChibiOS driver code, so we don't have to do anything special to the timer. If we did, we'd have to start the timer,
    // disable counting, enable the channel, and then make whatever configuration changes we need.
    pwmStart(&WS2812_PWMD, &ws2812_pwm_config);
    pwmEnableChannel(&WS2812_PWMD, WS2812_TIM_CH, 0);     // Initial period is 0; output will be low until first duty cycle is DMA'd in
}

ws2812_err_t ws2812_write_led(uint32_t led_number, uint8_t r, uint8_t g, uint8_t b)
{
    // Check for valid LED
    if (led_number >= WS2812_LED_N) return WS2812_LED_INVALID;

    // Write color to frame buffer
    uint32_t bit;
    for (bit = 0; bit < 8; bit++) {
        ws2812_frame_buffer[WS2812_RED_BIT(led_number, bit)]      = ((r >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
        ws2812_frame_buffer[WS2812_GREEN_BIT(led_number, bit)]    = ((g >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
        ws2812_frame_buffer[WS2812_BLUE_BIT(led_number, bit)]     = ((b >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
    }

    // Success
    return WS2812_SUCCESS;
}

/** @} addtogroup WS2812 */

void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds) {
  uint8_t i = 0;
  while (i < number_of_leds) {
    ws2812_write_led(i, ledarray[i].r, ledarray[i].g, ledarray[i].b);
    i++;
  }
}


void ws2812_setleds_rgbw(LED_TYPE *ledarray, uint16_t number_of_leds) {

}
