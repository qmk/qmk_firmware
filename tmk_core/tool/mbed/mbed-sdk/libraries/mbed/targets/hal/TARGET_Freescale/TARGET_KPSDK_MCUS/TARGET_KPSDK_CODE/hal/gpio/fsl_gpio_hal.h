/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_GPIO_HAL_H__
#define __FSL_GPIO_HAL_H__
 
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_gpio_features.h"
#include "fsl_device_registers.h"
 
/*!
 * @addtogroup gpio_hal
 * @{
 */

/*!
 * @file fsl_gpio_hal.h
 *
 * @brief GPIO hardware driver configuration. Use these functions to set the GPIO input/output, 
 * set output logic or get input logic. Check the GPIO header file for base address. Each 
 * GPIO instance has 32 pins with numbers from 0 to 31.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief GPIO direction definition*/
typedef enum _gpio_pin_direction {
    kGpioDigitalInput  = 0, /*!< Set current pin as digital input*/
    kGpioDigitalOutput = 1  /*!< Set current pin as digital output*/
} gpio_pin_direction_t;

/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */

/*!
 * @brief Sets the individual GPIO pin to general input or output.
 * 
 * @param baseAddr  GPIO base address(HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.) 
 * @param pin  GPIO port pin number 
 * @param direction  GPIO directions
 *        - kGpioDigitalInput: set to input
 *        - kGpioDigitalOutput: set to output
 */
void GPIO_HAL_SetPinDir(uint32_t baseAddr, uint32_t pin,
                        gpio_pin_direction_t direction);

/*!
 * @brief Sets the GPIO port pins to general input or output.
 *
 * This function  operates all 32 port pins.
 * 
 * @param baseAddr  GPIO base address (HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.)
 * @param direction  GPIO directions
 *        - 0: set to input
 *        - 1: set to output
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void GPIO_HAL_SetPortDir(uint32_t baseAddr, uint32_t direction)
{
    HW_GPIO_PDDR_WR(baseAddr, direction);
}

/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the current direction of the individual GPIO pin.
 * 
 * @param baseAddr  GPIO base address(HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.)
 * @param pin  GPIO port pin number
 * @return GPIO directions
 *        - kGpioDigitalInput: corresponding pin is set to input.
 *        - kGpioDigitalOutput: corresponding pin is set to output.
 */
static inline gpio_pin_direction_t GPIO_HAL_GetPinDir(uint32_t baseAddr, uint32_t pin)
{
    assert(pin < 32);
    return (gpio_pin_direction_t)((HW_GPIO_PDDR_RD(baseAddr) >> pin) & 1U);
} 

/*!
 * @brief Gets the GPIO port pins direction.
 *
 * This function  gets all 32-pin directions as a 32-bit integer.
 * 
 * @param baseAddr  GPIO base address (HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.)
 * @return GPIO directions. Each bit represents one pin. For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline uint32_t GPIO_HAL_GetPortDir(uint32_t baseAddr)
{
    return HW_GPIO_PDDR_RD(baseAddr);
} 

/* @} */

/*!
 * @name Output Operation
 * @{
 */

/*!
 * @brief Sets the output level of the individual GPIO pin to logic 1 or 0.
 * 
 * @param baseAddr  GPIO base address(HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.)
 * @param pin  GPIO port pin number
 * @param output  pin output logic level
 */
void GPIO_HAL_WritePinOutput(uint32_t baseAddr, uint32_t pin, uint32_t output);

/*!
 * @brief Reads the current pin output.
 * 
 * @param baseAddr  GPIO base address (HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.)
 * @param pin  GPIO port pin number
 * @return current pin output status. 0 - Low logic, 1 - High logic
 */
static inline uint32_t GPIO_HAL_ReadPinOutput(uint32_t baseAddr, uint32_t pin)
{
    assert(pin < 32);
    return ((HW_GPIO_PDOR_RD(baseAddr) >> pin) & 0x1U);
}

/*!
 * @brief Sets the output level of the individual GPIO pin to logic 1.
 * 
 * @param baseAddr  GPIO base address(HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.)
 * @param pin  GPIO port pin number
 */
static inline void GPIO_HAL_SetPinOutput(uint32_t baseAddr, uint32_t pin)
{
    assert(pin < 32);
    HW_GPIO_PSOR_WR(baseAddr, 1U << pin);
}

/*!
 * @brief Clears the output level of the individual GPIO pin to logic 0.
 * 
 * @param baseAddr  GPIO base address(HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.)
 * @param pin  GPIO port pin number
 */
static inline void GPIO_HAL_ClearPinOutput(uint32_t baseAddr, uint32_t pin)
{
    assert(pin < 32);
    HW_GPIO_PCOR_WR(baseAddr, 1U << pin);
}

/*!
 * @brief Reverses the current output logic of the individual GPIO pin.
 * 
 * @param baseAddr  GPIO base address(HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.)
 * @param pin  GPIO port pin number
 */
static inline void GPIO_HAL_TogglePinOutput(uint32_t baseAddr, uint32_t pin)
{
    assert(pin < 32);
    HW_GPIO_PTOR_WR(baseAddr, 1U << pin);
}

/*!
 * @brief Sets the output of the GPIO port to a specific logic value.
 *
 * This function  operates all 32 port pins.
 * 
 * @param baseAddr  GPIO base address (HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.) 
 * @param portOutput  data to configure the GPIO output. Each bit represents one pin. For each bit:
 *        - 0: set logic level 0 to pin
 *        - 1: set logic level 1 to pin
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void GPIO_HAL_WritePortOutput(uint32_t baseAddr, uint32_t portOutput)
{
    HW_GPIO_PDOR_WR(baseAddr, portOutput);
}

/*!
 * @brief Reads out all pin output status of the current port.
 *
 * This function  operates all 32 port pins.
 * 
 * @param baseAddr  GPIO base address (HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.) 
 * @return current port output status. Each bit represents one pin. For each bit:
 *        - 0: corresponding pin is outputting logic level 0
 *        - 1: corresponding pin is outputting logic level 1
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline uint32_t GPIO_HAL_ReadPortOutput(uint32_t baseAddr)
{
    return HW_GPIO_PDOR_RD(baseAddr);
}

/* @} */

/*!
 * @name Input Operation
 * @{
 */

/*!
 * @brief Reads the current input value of the individual GPIO pin.
 * 
 * @param baseAddr  GPIO base address(HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.)
 * @param pin  GPIO port pin number
 * @return GPIO port input value
 *         - 0: Pin logic level is 0, or is not configured for use by digital function.
 *         - 1: Pin logic level is 1
 */
static inline uint32_t GPIO_HAL_ReadPinInput(uint32_t baseAddr, uint32_t pin)
{
    assert(pin < 32);
    return (HW_GPIO_PDIR_RD(baseAddr) >> pin) & 1U;
}

/*!
 * @brief Reads the current input value of a specific GPIO port.
 *
 * This function  gets all 32-pin input as a 32-bit integer.
 * 
 * @param baseAddr GPIO base address(HW_GPIOA, HW_GPIOB, HW_GPIOC, etc.)
 * @return GPIO port input data. Each bit represents one pin. For each bit:
 *         - 0: Pin logic level is 0, or is not configured for use by digital function.
 *         - 1: Pin logic level is 1.
 *         - LSB: pin 0
 *         - MSB: pin 31
 */
static inline uint32_t GPIO_HAL_ReadPortInput(uint32_t baseAddr)
{
    return HW_GPIO_PDIR_RD(baseAddr);
}

/* @} */

/*!
 * @name FGPIO Operation
 *
 * @note FGPIO (Fast GPIO) is only available in a few MCUs. FGPIO and GPIO share the same
 *       peripheral but use different registers. FGPIO is closer to the core than the regular GPIO
 *       and it's faster to read and write.
 * @{
 */

#if FSL_FEATURE_GPIO_HAS_FAST_GPIO

/*!
 * @name Output Operation
 * @{
 */

/*!
 * @brief Sets the output level of an individual FGPIO pin to logic 1.
 * 
 * @param baseAddr  GPIO base address(HW_FPTA, HW_FPTB, HW_FPTC, etc.)
 * @param pin  FGPIO port pin number
 */
static inline void FGPIO_HAL_SetPinOutput(uint32_t baseAddr, uint32_t pin)
{
    assert(pin < 32);
    HW_FGPIO_PSOR_WR(baseAddr, 1U << pin);
}

/*!
 * @brief Clears the output level of an individual FGPIO pin to logic 0.
 * 
 * @param baseAddr  GPIO base address(HW_FPTA, HW_FPTB, HW_FPTC, etc.)
 * @param pin  FGPIO port pin number
 */
static inline void FGPIO_HAL_ClearPinOutput(uint32_t baseAddr, uint32_t pin)
{
    assert(pin < 32);
    HW_FGPIO_PCOR_WR(baseAddr, 1U << pin);
}

/*!
 * @brief Reverses the current output logic of an individual FGPIO pin.
 * 
 * @param baseAddr  GPIO base address(HW_FPTA, HW_FPTB, HW_FPTC, etc.)
 * @param pin  FGPIO port pin number
 */
static inline void FGPIO_HAL_TogglePinOutput(uint32_t baseAddr, uint32_t pin)
{
    assert(pin < 32);
    HW_FGPIO_PTOR_WR(baseAddr, 1U << pin);
}

/*!
 * @brief Sets the output of the FGPIO port to a specific logic value. 
 *
 * This function  affects all 32 port pins.
 * 
 * @param baseAddr  GPIO base address(HW_FPTA, HW_FPTB, HW_FPTC, etc.)
 * @param portOutput  data to configure the GPIO output. Each bit represents one pin. For each bit:
 *        - 0: set logic level 0 to pin.
 *        - 1: set logic level 1 to pin.
 *        - LSB: pin 0
 *        - MSB: pin 31
 */
static inline void FGPIO_HAL_WritePortOutput(uint32_t baseAddr, uint32_t portOutput)
{
    HW_FGPIO_PDOR_WR(baseAddr, portOutput);
}

/* @} */

/*!
 * @name Input Operation
 * @{ 
 */

/*!
 * @brief Gets the current input value of an individual FGPIO pin.
 * 
 * @param baseAddr  GPIO base address(HW_FPTA, HW_FPTB, HW_FPTC, etc.)
 * @param pin  FGPIO port pin number
 * @return FGPIO port input data
 *         - 0: Pin logic level is 0, or is not configured for use by digital function.
 *         - 1: Pin logic level is 1.
 */
static inline uint32_t FGPIO_HAL_ReadPinInput(uint32_t baseAddr, uint32_t pin)
{
    assert(pin < 32);
    return (HW_FGPIO_PDIR_RD(baseAddr) >> pin) & 1U;
}

/*!
 * @brief Gets the current input value of a specific FGPIO port.
 *
 * This function  gets all 32-pin input as a 32-bit integer.
 * 
 * @param baseAddr  GPIO base address(HW_FPTA, HW_FPTB, HW_FPTC, etc.). 
 * @return FGPIO port input data. Each bit represents one pin. For each bit:
 *         - 0: Pin logic level is 0, or is not configured for use by digital function.
 *         - 1: Pin logic level is 1.
 *         - LSB: pin 0
 *         - MSB: pin 31
 */
static inline uint32_t FGPIO_HAL_ReadPortInput(uint32_t baseAddr)
{
    return HW_FGPIO_PDIR_RD(baseAddr);
}

/* @} */

#endif /* FSL_FEATURE_GPIO_HAS_FAST_GPIO*/

#if defined(__cplusplus)
}
#endif
 
/*! @} */
 
#endif /* __FSL_GPIO_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/


