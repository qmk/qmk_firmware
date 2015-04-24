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
 
#include "fsl_enet_driver.h"
#include "fsl_clock_manager.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/


/* Internal irq number*/
typedef enum _enet_irq_number
{
    kEnetTsTimerNumber = 0,     /*!< ENET ts_timer irq number*/
    kEnetReceiveNumber = 1,     /*!< ENET receive irq number*/
    kEnetTransmitNumber = 2,    /*!< ENET transmit irq number*/
    kEnetMiiErrorNumber = 3     /*!< ENET mii error irq number*/
}enet_irq_number_t;

#if FSL_FEATURE_ENET_SUPPORT_PTP
extern enet_ptp_master_time_data_t g_ptpMasterTime;
#if FSL_FEATURE_ENET_PTP_TIMER_CHANNEL_INTERRUPT
#define ENET_TIMER_CHANNEL_NUM      2
#endif
#endif

#if defined (K64F12_SERIES) || defined (K70F12_SERIES)
IRQn_Type enet_irq_ids[HW_ENET_INSTANCE_COUNT][FSL_FEATURE_ENET_INTERRUPT_COUNT] = 
{
    { ENET_1588_Timer_IRQn, ENET_Receive_IRQn, ENET_Transmit_IRQn, ENET_Error_IRQn}            
};

uint8_t enetIntMap[kEnetIntNum] = 
{ 
    kEnetTsTimerNumber, 
    kEnetTsTimerNumber,
    kEnetMiiErrorNumber,
    kEnetMiiErrorNumber,
    kEnetMiiErrorNumber,
    kEnetMiiErrorNumber,
    kEnetMiiErrorNumber,
    kEnetMiiErrorNumber,
    kEnetMiiErrorNumber,
    kEnetReceiveNumber,
    kEnetReceiveNumber,
    kEnetTransmitNumber,
    kEnetTransmitNumber,
    kEnetMiiErrorNumber,
    kEnetMiiErrorNumber,
    kEnetMiiErrorNumber
};
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
/* The code was moved to k64f mac file (eth) */

/*******************************************************************************
 * EOF
 ******************************************************************************/

