/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2014, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#include "mbed_assert.h"
#include "pinmap.h"
#include "PortNames.h"
#include "mbed_error.h"

// GPIO mode look-up table
// Warning: the elements order must be the same as the one defined in PinNames.h
static const uint32_t gpio_mode[13] = {
    GPIO_MODE_INPUT,              //  0 = STM_MODE_INPUT
    GPIO_MODE_OUTPUT_PP,          //  1 = STM_MODE_OUTPUT_PP
    GPIO_MODE_OUTPUT_OD,          //  2 = STM_MODE_OUTPUT_OD
    GPIO_MODE_AF_PP,              //  3 = STM_MODE_AF_PP
    GPIO_MODE_AF_OD,              //  4 = STM_MODE_AF_OD
    GPIO_MODE_ANALOG,             //  5 = STM_MODE_ANALOG
    GPIO_MODE_IT_RISING,          //  6 = STM_MODE_IT_RISING
    GPIO_MODE_IT_FALLING,         //  7 = STM_MODE_IT_FALLING
    GPIO_MODE_IT_RISING_FALLING,  //  8 = STM_MODE_IT_RISING_FALLING
    GPIO_MODE_EVT_RISING,         //  9 = STM_MODE_EVT_RISING
    GPIO_MODE_EVT_FALLING,        // 10 = STM_MODE_EVT_FALLING
    GPIO_MODE_EVT_RISING_FALLING, // 11 = STM_MODE_EVT_RISING_FALLING
    0x10000000                    // 12 = STM_MODE_IT_EVT_RESET (not in STM32Cube HAL)
};

// Enable GPIO clock and return GPIO base address
uint32_t Set_GPIO_Clock(uint32_t port_idx)
{
    uint32_t gpio_add = 0;
    switch (port_idx) {
        case PortA:
            gpio_add = GPIOA_BASE;
            __GPIOA_CLK_ENABLE();
            break;
        case PortB:
            gpio_add = GPIOB_BASE;
            __GPIOB_CLK_ENABLE();
            break;
        case PortC:
            gpio_add = GPIOC_BASE;
            __GPIOC_CLK_ENABLE();
            break;
        case PortD:
            gpio_add = GPIOD_BASE;
            __GPIOD_CLK_ENABLE();
            break;
        default:
            error("Pinmap error: wrong port number.");
            break;
    }
    return gpio_add;
}

/**
 * Configure pin (input, output, alternate function or analog) + output speed + AF
 */
void pin_function(PinName pin, int data)
{
    MBED_ASSERT(pin != (PinName)NC);
    // Get the pin informations
    uint32_t mode  = STM_PIN_MODE(data);
    uint32_t pupd  = STM_PIN_PUPD(data);
    uint32_t afnum = STM_PIN_AFNUM(data);

    uint32_t port_index = STM_PORT(pin);
    uint32_t pin_index  = STM_PIN(pin);

    // Enable GPIO clock
    uint32_t gpio_add = Set_GPIO_Clock(port_index);
    GPIO_TypeDef *gpio = (GPIO_TypeDef *)gpio_add;

    // Enable AFIO clock
    __HAL_RCC_AFIO_CLK_ENABLE();

    // Configure Alternate Function
    // Warning: Must be done before the GPIO is initialized
    if (afnum > 0) {
        switch (afnum) {
            case 1: // Remap SPI1
                __HAL_AFIO_REMAP_SPI1_ENABLE();
                break;
            case 2: // Remap I2C1
                __HAL_AFIO_REMAP_I2C1_ENABLE();
                break;
            case 3: // Remap USART1
                __HAL_AFIO_REMAP_USART1_ENABLE();
                break;
            case 4: // Remap USART2
                __HAL_AFIO_REMAP_USART2_ENABLE();
                break;
            case 5: // Partial Remap USART3
                __HAL_AFIO_REMAP_USART3_PARTIAL();
                break;
            case 6: // Partial Remap TIM1
                __HAL_AFIO_REMAP_TIM1_PARTIAL();
                break;
            case 7: // Partial Remap TIM3
                __HAL_AFIO_REMAP_TIM3_PARTIAL();
                break;
            case 8: // Full Remap TIM2
                __HAL_AFIO_REMAP_TIM2_ENABLE();
                break;
            case 9: // Full Remap TIM3
                __HAL_AFIO_REMAP_TIM3_ENABLE();
                break;
            default:
                break;
        }
    }

    // Configure GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin   = (uint32_t)(1 << pin_index);
    GPIO_InitStructure.Mode  = gpio_mode[mode];
    GPIO_InitStructure.Pull  = pupd;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(gpio, &GPIO_InitStructure);

    // Disconnect JTAG-DP + SW-DP signals.
    // Warning: Need to reconnect under reset
    if ((pin == PA_13) || (pin == PA_14)) {
        __HAL_AFIO_REMAP_SWJ_DISABLE(); // JTAG-DP Disabled and SW-DP Disabled
    }
    if ((pin == PA_15) || (pin == PB_3) || (pin == PB_4)) {
        __HAL_AFIO_REMAP_SWJ_NOJTAG(); // JTAG-DP Disabled and SW-DP enabled
    }
}

/**
 * Configure pin pull-up/pull-down
 */
void pin_mode(PinName pin, PinMode mode)
{
    MBED_ASSERT(pin != (PinName)NC);

    uint32_t port_index = STM_PORT(pin);
    uint32_t pin_index  = STM_PIN(pin);

    // Enable GPIO clock
    uint32_t gpio_add = Set_GPIO_Clock(port_index);
    GPIO_TypeDef *gpio = (GPIO_TypeDef *)gpio_add;

    // Configure open-drain and pull-up/down
    switch (mode) {
        case PullNone:
            break;
        case PullUp:
        case PullDown:
            // Set pull-up / pull-down for Input mode
            if (pin_index < 8) {
                if ((gpio->CRL & (0x03 << (pin_index * 4))) == 0) { // MODE bits = Input mode
                    gpio->CRL |= (0x08 << (pin_index * 4)); // Set pull-up / pull-down
                }
            } else {
                if ((gpio->CRH & (0x03 << ((pin_index % 8) * 4))) == 0) { // MODE bits = Input mode
                    gpio->CRH |= (0x08 << ((pin_index % 8) * 4)); // Set pull-up / pull-down
                }
            }
            break;
        case OpenDrain:
            // Set open-drain for Output mode (General Purpose or Alternate Function)
            if (pin_index < 8) {
                if ((gpio->CRL & (0x03 << (pin_index * 4))) > 0) { // MODE bits = Output mode
                    gpio->CRL |= (0x04 << (pin_index * 4)); // Set open-drain
                }
            } else {
                if ((gpio->CRH & (0x03 << ((pin_index % 8) * 4))) > 0) { // MODE bits = Output mode
                    gpio->CRH |= (0x04 << ((pin_index % 8) * 4)); // Set open-drain
                }
            }
            break;
        default:
            break;
    }
}
