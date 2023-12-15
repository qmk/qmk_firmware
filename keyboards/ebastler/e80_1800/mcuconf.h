/* Copyright 2022 Moritz Plattner
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include_next <mcuconf.h>

/* enable TIM1, used for backlight PWM */
#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1                  TRUE

/* enable I2C2, used for the OLED */
#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2                  TRUE

#undef STM32_I2C_USE_DMA
#define STM32_I2C_USE_DMA                   TRUE

#define STM32_I2C_I2C2_RX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 5)
#define STM32_I2C_I2C2_TX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 4)