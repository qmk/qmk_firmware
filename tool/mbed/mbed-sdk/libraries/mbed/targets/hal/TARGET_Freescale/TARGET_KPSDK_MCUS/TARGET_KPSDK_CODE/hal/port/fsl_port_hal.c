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
 
#include "fsl_port_hal.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : PORT_HAL_SetLowGlobalPinCtrl
 * Description   : Configure low half of pin control register for the same settings, 
 *                 this function operates pin 0 -15 of one specific port.
 *
 *END**************************************************************************/
void PORT_HAL_SetLowGlobalPinCtrl(uint32_t baseAddr, uint16_t lowPinSelect, uint16_t config)
{
    uint32_t combine = lowPinSelect;
    combine = (combine << 16) + config;
    HW_PORT_GPCLR_WR(baseAddr, combine);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PORT_HAL_SetHighGlobalPinCtrl
 * Description   : Configure high half of pin control register for the same
 *                 settings, this function operates pin 16 -31 of one specific port.
 *
 *END**************************************************************************/
void PORT_HAL_SetHighGlobalPinCtrl(uint32_t baseAddr, uint16_t highPinSelect, uint16_t config)
{
    uint32_t combine = highPinSelect;
    combine = (combine << 16) + config;
    HW_PORT_GPCHR_WR(baseAddr, combine);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

