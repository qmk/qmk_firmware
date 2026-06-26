// SPDX-License-Identifier: BSD-2-Clause

#pragma once

// The STM32F103C8 flash-size register lies and reports 64KB instead of the
// actual 128KB physical flash. Without this override, wear_leveling_efl reads
// the hardware register and places the backing store inside the app code,
// causing a HardFault on first boot when it erases those pages.
//
// NOTE: it seems this is not needed for QMK (which respects the
// defined flash size from the code), but it IS needed for VIAL-QMK
// (which reads the [wrong] flash size from the register).
#define WEAR_LEVELING_EFL_FLASH_SIZE (128 * 1024)


// WS2812 PWM driver via TIM4_CH4 (PB9) + DMA1_CH7 (TIM4_UP)
#define WS2812_PWM_DRIVER       PWMD4
#define WS2812_PWM_CHANNEL      4
#define WS2812_PWM_DMA_STREAM   STM32_DMA1_STREAM7
#define WS2812_PWM_DMA_CHANNEL  7

