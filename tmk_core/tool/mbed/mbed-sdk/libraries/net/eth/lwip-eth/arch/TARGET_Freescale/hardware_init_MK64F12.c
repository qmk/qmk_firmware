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
#include "fsl_clock_manager.h"
#include "fsl_device_registers.h"
#include "fsl_sim_hal.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
void k64f_init_eth_hardware(void)
{
    uint8_t count;

    /* Disable the mpu*/
    BW_MPU_CESR_VLD(MPU_BASE, 0);
    
    /* Open POTR clock gate*/
    for (count = 0; count < HW_PORT_INSTANCE_COUNT; count++)
    {
        CLOCK_SYS_EnablePortClock(count);
    }

    /* Configure gpio*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 12, kPortMuxAlt4);  /*!< ENET RMII0_RXD1/MII0_RXD1*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 13, kPortMuxAlt4);  /*!< ENET RMII0_RXD0/MII0_RXD0*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 14, kPortMuxAlt4);  /*!< ENET RMII0_CRS_DV/MII0_RXDV*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 15, kPortMuxAlt4);  /*!< ENET RMII0_TXEN/MII0_TXEN*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 16, kPortMuxAlt4);  /*!< ENET RMII0_TXD0/MII0_TXD0*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 17, kPortMuxAlt4);  /*!< ENET RMII0_TXD01/MII0_TXD1*/
    PORT_HAL_SetMuxMode(PORTB_BASE, 0, kPortMuxAlt4);   /*!< ENET RMII0_MDIO/MII0_MDIO*/
    PORT_HAL_SetOpenDrainCmd(PORTB_BASE,0, true);   /*!< ENET RMII0_MDC/MII0_MDC*/

    // Added for FRDM-K64F
    PORT_HAL_SetPullMode(PORTB_BASE, 0, kPortPullUp);
    PORT_HAL_SetPullCmd(PORTB_BASE, 0, true);
  
    PORT_HAL_SetMuxMode(PORTB_BASE, 1, kPortMuxAlt4);
    /* Configure GPIO for MII interface */
    PORT_HAL_SetMuxMode(PORTA_BASE, 9, kPortMuxAlt4);   /*!< ENET MII0_RXD3*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 10, kPortMuxAlt4);   /*!< ENET MII0_RXD2*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 11, kPortMuxAlt4);   /*!< ENET MII0_RXCLK*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 24, kPortMuxAlt4);   /*!< ENET MII0_TXD2*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 25, kPortMuxAlt4);   /*!< ENET MII0_TXCLK*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 26, kPortMuxAlt4);   /*!< ENET MII0_TXD3*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 27, kPortMuxAlt4);   /*!< ENET MII0_CRS*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 28, kPortMuxAlt4);   /*!< ENET MII0_TXER*/
    PORT_HAL_SetMuxMode(PORTA_BASE, 29, kPortMuxAlt4);   /*!< ENET MII0_COL*/
#if FSL_FEATURE_ENET_SUPPORT_PTP
    PORT_HAL_SetMuxMode(PORTC_BASE, (16 + ENET_TIMER_CHANNEL_NUM), kPortMuxAlt4); /* ENET ENET0_1588_TMR0*/
    PORT_HAL_SetDriveStrengthMode(PORTC_BASE, (16 + ENET_TIMER_CHANNEL_NUM), kPortHighDriveStrength);
#endif

    /* Open ENET clock gate*/
    CLOCK_SYS_EnableEnetClock( 0U);

    /* Select the ptp timer  outclk*/
    CLOCK_HAL_SetSource(g_simBaseAddr[0], kClockTimeSrc, 2);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/


