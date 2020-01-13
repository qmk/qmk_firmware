/**
 * @file    ws2812.h
 * @author  Austin Glaser <austin.glaser@gmail.com>
 * @brief   Interface to WS2812 LED driver
 *
 * Copyright (C) 2016 Austin Glaser
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 * @todo    Put in names and descriptions of variables which need to be defined to use this file
 */

#ifndef WS2812_H_
#define WS2812_H_

/**
 * @defgroup WS2812 WS2812 Driver
 * @{
 *
 * @brief   DMA-based WS2812 LED driver
 *
 * A driver for WS2812 LEDs
 */

/* --- PUBLIC DEPENDENCIES -------------------------------------------------- */

// Standard
#include <stdint.h>
#include "color.h"

/* --- PUBLIC MACROS -------------------------------------------------------- */

/**
 * @brief   Concatenates two symbols s1 and s2 exactly, without expanding either
 *
 * @param[in] s1:       The first symbol to concatenate
 * @param[in] s2:       The second symbol to concatenate
 *
 * @return              A single symbol containing s1 and s2 concatenated without expansion
 */
#define CONCAT_SYMBOLS(s1, s2) s1##s2

/**
 * @brief  Concatenate the symbols s1 and s2, expanding both of them
 *
 * This is important because simply applying s1##s2 doesn't expand them if they're
 * preprocessor tokens themselves
 *
 * @param[in] s1:       The first symbol to concatenate
 * @param[in] s2:       The second symbol to concatenate
 *
 * @return              A single symbol containing s1 expanded followed by s2 expanded
 */
#define CONCAT_EXPANDED_SYMBOLS(s1, s2) CONCAT_SYMBOLS(s1, s2)

/* --- PUBLIC CONSTANTS ----------------------------------------------------- */

/**
 * @brief   Return codes from ws2812 interface functions
 */
typedef enum {
    WS2812_SUCCESS = 0x00, /**< Operation completeed successfully */
    WS2812_LED_INVALID,    /**< Attempted to index an invalid LED (@ref WS2812_N_LEDS) */
    MAX_WS2812_ERR,        /**< Total number of possible error codes */
    WS2812_ERR_INVALID     /**< Invalid error value */
} ws2812_err_t;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */

/**
 * @brief   Initialize the driver
 *
 * After this function is called, all necessary background tasks will be started.
 * The frame is initially dark.
 */
void ws2812_init(void);

/**
 * @brief   Write the value of a single LED in the chain
 *
 * The color value is written to a frame buffer, and will not
 * be updated until the next frame is written. Frames are written
 * at the maximum possible speed -- the longest latency between a
 * call to this function and the value being displayed is
 * 1.25uS*(24*@ref WS2812_LED_N + 50)
 *
 * @param[in] led_number:           The index of the LED to be written. Must be strictly less than
 *                                  @ref WS2812_N_LEDS
 * @param[in] r:                    The red level of the LED
 * @param[in] g:                    The green level of the LED
 * @param[in] b:                    The blue level of the LED
 *
 * @retval WS2812_SUCCESS:          The write was successful
 * @retval WS2812_LED_INVALID:      The write was to an invalid LED index
 */
ws2812_err_t ws2812_write_led(uint32_t led_number, uint8_t r, uint8_t g, uint8_t b);

void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds);
/** @} defgroup WS2812 */

#endif  // ifndef WS2812_H_
