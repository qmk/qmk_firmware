/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
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

#include_next <board.h>

// clang-format off

/* Set GPIOA_SWDIO to INPUT and NOT FLOATING */
#undef VAL_GPIOA_MODER
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_BUTTON) |         \
                                     PIN_MODE_INPUT(GPIOA_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN3) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_CS43L22_LRCK) |\
                                     PIN_MODE_ALTERNATE(GPIOA_L3GD20_SCL) | \
                                     PIN_MODE_ALTERNATE(GPIOA_L3GD20_SD0) | \
                                     PIN_MODE_ALTERNATE(GPIOA_L3GD20_SDI) | \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOA_VBUS_FS) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_ID) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DM) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DP) |  \
                                     PIN_MODE_INPUT(GPIOA_SWDIO) |          \
                                     PIN_MODE_INPUT(GPIOA_SWCLK) |          \
                                     PIN_MODE_INPUT(GPIOA_PIN15))

#undef VAL_GPIOA_PUPDR
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_BUTTON) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN3) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_CS43L22_LRCK) |\
                                     PIN_PUPDR_FLOATING(GPIOA_L3GD20_SCL) | \
                                     PIN_PUPDR_PULLUP(GPIOA_L3GD20_SD0) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_L3GD20_SDI) |   \
                                     PIN_PUPDR_PULLDOWN(GPIOA_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_VBUS_FS) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_ID) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DM) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DP) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLUP(GPIOA_SWCLK) |        \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN15))

#undef VAL_GPIOB_MODER
#define VAL_GPIOB_MODER             (PIN_MODE_INPUT(GPIOB_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOB_SWO) |            \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOB_LSM303DLHC_SCL) | \
                                     PIN_MODE_INPUT(GPIOB_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOB_LSM303DLHC_SDA) | \
                                     PIN_MODE_INPUT(GPIOB_MP45DT02_CLK_IN) |\
                                     PIN_MODE_INPUT(GPIOB_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN15))

#undef VAL_GPIOB_PUPDR
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOB_PIN0) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN1) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN2) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_SWO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN4) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN5) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_LSM303DLHC_SCL) |\
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN7) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN8) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOB_LSM303DLHC_SDA) |\
                                     PIN_PUPDR_PULLDOWN(GPIOB_MP45DT02_CLK_IN) |\
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN11) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN12) |      \
                                     PIN_PUPDR_PULLDOWN(GPIOB_PIN13) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN14) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN15))

#undef VAL_GPIOB_AFRL
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_SWO, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_LSM303DLHC_SCL, 0) | \
                                     PIN_AFIO_AF(GPIOB_PIN7, 0U))

#undef VAL_GPIOB_AFRH
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_LSM303DLHC_SDA, 0) | \
                                     PIN_AFIO_AF(GPIOB_MP45DT02_CLK_IN, 0U) |\
                                     PIN_AFIO_AF(GPIOB_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_PIN15, 0U))

/* C5 Need to be pulldown */
#undef VAL_GPIOC_MODER
#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_OTG_FS_POWER_ON) |\
                                     PIN_MODE_INPUT(GPIOC_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOC_CS43L22_AIN4x) |  \
                                     PIN_MODE_INPUT(GPIOC_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOC_CS43L22_MCLK) |   \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOC_CS43L22_SCLK) |   \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOC_CS43L22_SDIN) |   \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_INPUT(GPIOC_OSC32_OUT))

#undef VAL_GPIOC_PUPDR
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_OTG_FS_POWER_ON) |\
                                     PIN_PUPDR_PULLUP(GPIOC_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_CS43L22_AIN4x) |\
                                     PIN_PUPDR_PULLUP(GPIOC_PIN4) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN5) |       \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_CS43L22_MCLK) | \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN8) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOC_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_CS43L22_SCLK) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_CS43L22_SDIN) | \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_OSC32_IN) |     \
                                     PIN_PUPDR_PULLUP(GPIOC_OSC32_OUT))

/* Set all GPIOD pins to INPUT & PULLUP to avoid FLOATING */
#undef VAL_GPIOD_MODER
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_CS43L22_RESET) |  \
                                     PIN_MODE_INPUT(GPIOD_OverCurrent) |    \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_LED4) |           \
                                     PIN_MODE_INPUT(GPIOD_LED3) |           \
                                     PIN_MODE_INPUT(GPIOD_LED5) |           \
                                     PIN_MODE_INPUT(GPIOD_LED6))

#undef VAL_GPIOD_PUPDR
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_CS43L22_RESET) |\
                                     PIN_PUPDR_PULLUP(GPIOD_OverCurrent) |  \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_LED4) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_LED3) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_LED5) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_LED6))

/* Set all GPIOE pins to INPUT & PULLUP to avoid FLOATING */
#undef VAL_GPIOE_MODER
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_L3GD20_INT1) |    \
                                     PIN_MODE_INPUT(GPIOE_L3GD20_INT2) |    \
                                     PIN_MODE_INPUT(GPIOE_LSM303DLHC_DRDY) |\
                                     PIN_MODE_INPUT(GPIOE_L3GD20_CS) |      \
                                     PIN_MODE_INPUT(GPIOE_LSM303DLHC_INT1) |\
                                     PIN_MODE_INPUT(GPIOE_LSM303DLHC_INT2) |\
                                     PIN_MODE_INPUT(GPIOE_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN15))

#undef VAL_GPIOE_PUPDR
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_PULLUP(GPIOE_L3GD20_INT1) |  \
                                     PIN_PUPDR_PULLUP(GPIOE_L3GD20_INT2) |  \
                                     PIN_PUPDR_PULLUP(GPIOE_LSM303DLHC_DRDY) |\
                                     PIN_PUPDR_PULLUP(GPIOE_L3GD20_CS) |    \
                                     PIN_PUPDR_PULLUP(GPIOE_LSM303DLHC_INT1) |\
                                     PIN_PUPDR_PULLUP(GPIOE_LSM303DLHC_INT2) |\
                                     PIN_PUPDR_PULLUP(GPIOE_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN15))
