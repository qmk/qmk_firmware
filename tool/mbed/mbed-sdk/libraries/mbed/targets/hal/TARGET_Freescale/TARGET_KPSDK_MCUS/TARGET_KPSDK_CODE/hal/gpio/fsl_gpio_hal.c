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
 
#include "fsl_gpio_hal.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_HAL_SetPinDir
 * Description   : Set individual gpio pin to general input or output.
 *
 *END**************************************************************************/
void GPIO_HAL_SetPinDir(uint32_t baseAddr, uint32_t pin, gpio_pin_direction_t direction)
{
    assert(pin < 32);

    if (direction == kGpioDigitalOutput)
    {
        HW_GPIO_PDDR_SET(baseAddr, 1U << pin);
    }
    else
    {
        HW_GPIO_PDDR_CLR(baseAddr, 1U << pin);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : GPIO_HAL_WritePinOutput
 * Description   : Set output level of individual gpio pin to logic 1 or 0.
 *
 *END**************************************************************************/
void GPIO_HAL_WritePinOutput(uint32_t baseAddr, uint32_t pin, uint32_t output)
{
    assert(pin < 32);
    if (output != 0U)
    {
        HW_GPIO_PSOR_WR(baseAddr, 1U << pin); /* Set pin output to high level.*/
    }
    else
    {
        HW_GPIO_PCOR_WR(baseAddr, 1U << pin); /* Set pin output to low level.*/
    }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
