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
#if !defined(__FSL_RCM_HAL_H__)
#define __FSL_RCM_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_rcm_features.h"

/*! @addtogroup rcm_hal*/
/*! @{*/

/*! @file fsl_rcm_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief System Reset Source Name definitions */
typedef enum _rcm_source_names {
    kRcmWakeup,                     /* low-leakage wakeup reset */
    kRcmLowVoltDetect,              /* low voltage detect reset */
    kRcmLossOfClk,                  /* loss of clock reset */
    kRcmLossOfLock,                 /* loss of lock reset */
    kRcmWatchDog,                   /* watch dog reset */
    kRcmExternalPin,                /* external pin reset */
    kRcmPowerOn,                    /* power on reset */
    kRcmJtag,                       /* JTAG generated reset */
    kRcmCoreLockup,                 /* core lockup reset */
    kRcmSoftware,                   /* software reset */
    kRcmSystem,                     /* system reset request bit set reset */
    kRcmEzport,                     /* EzPort reset */
    kRcmStopModeAckErr,             /* stop mode ack error reset */
    kRcmSrcNameMax
} rcm_source_names_t;

/*! @brief Reset pin filter select in Run and Wait modes */
typedef enum _rcm_filter_run_wait_modes {
    kRcmFilterDisabled,          /* all filtering disabled */
    kRcmFilterBusClk,            /* Bus clock filter enabled */
    kRcmFilterLpoClk,            /* LPO clock filter enabled */
    kRcmFilterReserverd          /* reserved setting */
} rcm_filter_run_wait_modes_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Gets the reset source status.
 *
 * This function gets the current reset source status for a specified source.
 *
 * @param baseAddr     Register base address of RCM
 * @param srcName      reset source name
 * @return status      true or false for specified reset source
 */
bool RCM_HAL_GetSrcStatusCmd(uint32_t baseAddr, rcm_source_names_t srcName);

/*!
 * @brief Sets the reset pin filter in stop mode.
 *
 * This function  sets the reset pin filter enable setting in stop mode.
 *
 * @param baseAddr     Register base address of RCM
 * @param enable      enable or disable the filter in stop mode
 */
static inline void RCM_HAL_SetFilterStopModeCmd(uint32_t baseAddr, bool enable)
{
    BW_RCM_RPFC_RSTFLTSS(baseAddr, enable);
}

/*!
 * @brief Gets the reset pin filter in stop mode.
 *
 * This function gets the reset pin filter enable setting in stop mode.
 *
 * @param baseAddr     Register base address of RCM
 * @return enable      true/false to enable or disable the filter in stop mode
 */
static inline bool RCM_HAL_GetFilterStopModeCmd(uint32_t baseAddr)
{
    return (bool)BR_RCM_RPFC_RSTFLTSS(baseAddr);
}

/*!
 * @brief Sets the reset pin filter in run and wait mode.
 *
 * This function sets the reset pin filter enable setting in run/wait mode.
 *
 * @param baseAddr     Register base address of RCM
 * @param mode  to be set for reset filter in run/wait mode
 */
static inline void RCM_HAL_SetFilterRunWaitMode(uint32_t baseAddr, rcm_filter_run_wait_modes_t mode)
{
    BW_RCM_RPFC_RSTFLTSRW(baseAddr, mode);
}

/*!
 * @brief Gets the reset pin filter for stop mode.
 *
 * This function gets the reset pin filter enable setting for stop mode.
 *
 * @param baseAddr     Register base address of RCM
 * @return mode  for reset filter in run/wait mode
 */
static inline rcm_filter_run_wait_modes_t RCM_HAL_GetFilterRunWaitMode(uint32_t baseAddr)
{
    return (rcm_filter_run_wait_modes_t)BR_RCM_RPFC_RSTFLTSRW(baseAddr);
}

/*!
 * @brief Sets the reset pin filter width.
 *
 * This function sets the reset pin filter width.
 *
 * @param baseAddr     Register base address of RCM
 * @param width  to be set for reset filter width
 */
static inline void RCM_HAL_SetFilterWidth(uint32_t baseAddr, uint32_t width)
{
    BW_RCM_RPFW_RSTFLTSEL(baseAddr, width);
}

/*!
 * @brief Gets the reset pin filter for stop mode.
 *
 * This function gets the reset pin filter width.
 *
 * @param baseAddr     Register base address of RCM
 * @return width reset filter width
 */
static inline uint32_t RCM_HAL_GetFilterWidth(uint32_t baseAddr)
{
    return (uint32_t)BR_RCM_RPFW_RSTFLTSEL(baseAddr);
}

/*!
 * @brief Gets the EZP_MS_B pin assert status.
 *
 * This function gets the easy port mode status (EZP_MS_B) pin assert status.
 *
 * @param baseAddr     Register base address of RCM
 * @return status  true - asserted, false - reasserted
 */
static inline bool RCM_HAL_GetEasyPortModeStatusCmd(uint32_t baseAddr)
{
    return (bool)BR_RCM_MR_EZP_MS(baseAddr);
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name Reset Control Module APIs*/
/*@{*/

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_RCM_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

