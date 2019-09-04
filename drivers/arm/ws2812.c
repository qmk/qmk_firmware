/**
 * Copyright (C) 2016 Austin Glaser, 2017 Joerg Wangemann
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "ws2812.h"
#include "quantum.h"
#include "hal.h"

// all boards are snowflakes. defaults to olkb board pinouts
#ifndef WS2812_TIM_N
	#define WS2812_TIM_N	2
#endif
#ifndef WS2812_TIM_CH
	#define WS2812_TIM_CH	1
#endif
#ifndef WS2812_AF
	#define WS2812_AF		1
#endif
#ifndef WS2812_DMA_STREAM
	#define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#endif
#ifndef WS2812_DMA_CHANNEL
	#define WS2812_DMA_CHANNEL 2
#endif 


#define WS2812_RESET_BIT_N      			(50)
#define WS2812_COLOR_BIT_N      			(RGBLED_NUM * 24)
#define WS2812_BIT_N            			(WS2812_COLOR_BIT_N + WS2812_RESET_BIT_N)

#define WS2812_BIT(led, byte, bit)          (24 * (led) + 8 * (byte) + (7 - (bit)))
#define WS2812_GREEN_BIT(led, bit)          WS2812_BIT((led), 0, (bit))
#define WS2812_RED_BIT(led, bit)            WS2812_BIT((led), 1, (bit))
#define WS2812_BLUE_BIT(led, bit)           WS2812_BIT((led), 2, (bit))

#define WS2812_PWM_FREQUENCY    			(STM32_SYSCLK / 2)
#define WS2812_PWM_PERIOD       			(WS2812_PWM_FREQUENCY / 80000)
#define WS2812_DUTYCYCLE_0					(WS2812_PWM_FREQUENCY / (1000000000/385))
#define WS2812_DUTYCYCLE_1					(WS2812_PWM_FREQUENCY /(1000000000/930))

#define PWMD(n)								CONCAT_EXPANDED_SYMBOLS(PWMD, n)
#define WS2812_PWMD                         PWMD(WS2812_TIM_N)

static uint32_t led_buf[WS2812_BIT_N];

#if !defined(LED_ARRAY) && defined(RGB_MATRIX_ENABLE)
	LED_TYPE led[DRIVER_LED_TOTAL];
  #define LED_ARRAY led 
#endif

void ws2812_init(void)
{
	uint32_t i = 0;
    for (i = 0; i < WS2812_COLOR_BIT_N; i++) 
		led_buf[i] = WS2812_DUTYCYCLE_0;
    for (i = 0; i < WS2812_RESET_BIT_N; i++) 
		led_buf[i + WS2812_COLOR_BIT_N]  = 0;

    palSetLineMode(RGB_DI_PIN, PAL_MODE_ALTERNATE(WS2812_AF) | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING);

    static const PWMConfig ws2812_pwm_config = {
        .frequency          = WS2812_PWM_FREQUENCY,
        .period             = WS2812_PWM_PERIOD,
        .callback           = NULL,
        .channels = {
            [0 ... 3]       = {.mode = PWM_OUTPUT_DISABLED,     .callback = NULL},
            [WS2812_TIM_CH] = {.mode = PWM_OUTPUT_ACTIVE_HIGH,  .callback = NULL},
        },
        .cr2                = 0,
        .dier               = TIM_DIER_UDE,                                      
    };

    dmaStreamAllocate(WS2812_DMA_STREAM, 10, NULL, NULL);
    dmaStreamSetPeripheral(WS2812_DMA_STREAM, &(WS2812_PWMD.tim->CCR[WS2812_TIM_CH]));
    dmaStreamSetMemory0(WS2812_DMA_STREAM, led_buf);
    dmaStreamSetTransactionSize(WS2812_DMA_STREAM, (uint32_t) WS2812_BIT_N);
    dmaStreamSetMode(WS2812_DMA_STREAM,
      STM32_DMA_CR_CHSEL(WS2812_DMA_CHANNEL) | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD |
      STM32_DMA_CR_MINC | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(2));

    dmaStreamEnable(WS2812_DMA_STREAM);

    pwmStart(&WS2812_PWMD, &ws2812_pwm_config);
    pwmEnableChannel(&WS2812_PWMD, WS2812_TIM_CH, 0);
}

void ws2812_write_led(int index, uint8_t r, uint8_t g, uint8_t b)
{

	if(index > RGBLED_NUM) {
		dprintf("ws2812_write_led() attempted to set led outside of range. (i:%d) (r:%d) (g:%d) (b:%d)\n", index, r, g, b);
		return;
	}

    uint8_t bit;
    for (bit = 0; bit < 8; bit++) {
        led_buf[WS2812_RED_BIT(index, bit)]      = ((r >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
        led_buf[WS2812_GREEN_BIT(index, bit)]    = ((g >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
        led_buf[WS2812_BLUE_BIT(index, bit)]     = ((b >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
    }
}

void ws2812_setled(int i, uint8_t r, uint8_t g, uint8_t b) {
	led[i].r = r;
	led[i].g = g;
	led[i].b = b;
}

void ws2812_setleds(LED_TYPE *led_colors, uint16_t num_leds) {
	for (uint16_t i = 0; i < num_leds; i++) {
		ws2812_write_led(i, led_colors[i].r, led_colors[i].g, led_colors[i].b);
	}
}

void ws2812_setleds_rgbw(LED_TYPE *led_colors, uint16_t num_leds) {
	dprint("ws2812_setleds_rgbw() stub called.\n");
}

void ws2812_setled_all(uint8_t r, uint8_t g, uint8_t b) {
	for (uint16_t i=0;i < sizeof(led) / sizeof(led[0]); i++) {
		led[i].r = r;
		led[i].g = g;
		led[i].b = b;
	}
}
