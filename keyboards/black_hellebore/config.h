/* Copyright 2023 MATTMCCA (@MATTMCCA)
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 1						//TIM1_CH1N (AF1)
#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM6
#define WS2812_PWM_DMA_CHANNEL 7						//7 works, CxS[3:0] 0111 = TIM1_UP on Channel 6? (RM0394.pdf pg.298)
