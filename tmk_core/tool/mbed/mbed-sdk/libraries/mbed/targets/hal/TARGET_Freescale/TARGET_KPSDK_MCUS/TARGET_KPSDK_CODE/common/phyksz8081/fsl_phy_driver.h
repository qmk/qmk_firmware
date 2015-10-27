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
#ifndef __FSL_PHY_DRIVER_H__
#define __FSL_PHY_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_enet_driver.h"

#ifndef MBED_NO_ENET

/*!
 * @addtogroup phy_driver
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Defines the PHY return status. */
typedef enum _phy_status
{
    kStatus_PHY_Success = 0, /*!< Success*/
    kStatus_PHY_InvaildInput = 1, /*!< Invalid PHY input parameter*/
    kStatus_PHY_TimeOut = 2,  /*!< PHY timeout*/
    kStatus_PHY_Fail = 3  /*!< PHY fail*/	
} phy_status_t;

/*! @brief Defines the ENET timeout.*/
typedef enum _phy_timeout
{
    kPhyTimeout = 0x10000, /*!< ENET resets timeout.*/
} phy_timeout_t;

/*! @brief Defines the PHY register.*/
typedef enum _enet_phy_register
{
    kEnetPhyCR = 0, /*!< PHY control register */
    kEnetPhySR = 1, /*!< PHY status register*/
    kEnetPhyId1 = 2, /*!< PHY identification register 1*/
    kEnetPhyId2 = 3, /*!< PHY identification register 2*/
    kEnetPhyCt2 = 0x1e /*!< PHY control2 register*/
} enet_phy_register_t;

/*! @brief Defines the control flag.*/
typedef enum _enet_phy_control
{
    kEnetPhyAutoNeg = 0x1000,/*!< ENET PHY auto negotiation control*/
    kEnetPhySpeed = 0x2000, /*! ENET PHY speed control*/
    kEnetPhyLoop = 0x4000, /*!< ENET PHY loop control*/
    kEnetPhyReset = 0x8000, /*!< ENET PHY reset control*/
    kEnetPhy10HalfDuplex = 0x01, /*!< ENET PHY 10 M half duplex*/
    kEnetPhy100HalfDuplex = 0x02,/*!< ENET PHY 100 M half duplex*/
    kEnetPhy10FullDuplex = 0x05,/*!< ENET PHY 10 M full duplex*/
    kEnetPhy100FullDuplex = 0x06/*!< ENET PHY 100 M full duplex*/
} enet_phy_control_t;

/*! @brief Defines the PHY link speed. */
typedef enum _enet_phy_speed
{
    kEnetSpeed10M = 0,   /*!< ENET PHY 10 M speed*/
    kEnetSpeed100M = 1  /*!< ENET PHY 100 M speed*/
} enet_phy_speed_t;

/*! @brief Defines the PHY link duplex.*/
typedef enum _enet_phy_duplex
{
    kEnetHalfDuplex = 0, /*!< ENET PHY half duplex*/
    kEnetFullDuplex = 1  /*!< ENET PHY full duplex*/
} enet_phy_duplex_t;

/*! @brief Defines the PHY status.*/
typedef enum _enet_phy_status
{
    kEnetPhyLinkStatus = 0x4,  /*!< ENET PHY link status bit*/
    kEnetPhyAutoNegAble = 0x08, /*!< ENET PHY auto negotiation ability*/
    kEnetPhyAutoNegComplete = 0x20, /*!< ENET PHY auto negotiation complete*/
    kEnetPhySpeedDulpexMask = 0x07 /*!< ENET PHY speed mask on status register 2*/
} enet_phy_status_t;

/*! @brief Defines the basic PHY application.*/
typedef struct ENETPhyApi
{
    uint32_t (* phy_auto_discover)(enet_dev_if_t * enetIfPtr);/*!< PHY auto discover*/
    uint32_t (* phy_init)(enet_dev_if_t * enetIfPtr);/*!< PHY initialize*/
    uint32_t (* phy_get_link_speed)(enet_dev_if_t * enetIfPtr, enet_phy_speed_t *speed);/*!< Get PHY speed*/
    uint32_t (* phy_get_link_status)(enet_dev_if_t * enetIfPtr, bool *status);/*! Get PHY link status*/
    uint32_t (* phy_get_link_duplex)(enet_dev_if_t * enetIfPtr, enet_phy_duplex_t *duplex);/*!< Get PHY link duplex*/
} enet_phy_api_t;

/*******************************************************************************
 * Global variables
 ******************************************************************************/
extern const enet_phy_api_t g_enetPhyApi;

/*******************************************************************************
 * API 
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
  * @name PHY Driver
  * @{
  */

/*!
 * @brief Initializes PHY.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
uint32_t phy_init(enet_dev_if_t * enetIfPtr);

/*!
 * @brief PHY address auto discover.
 *
 * @param enetIfPtr The ENET context structure.
 * @return The execution status.
 */
uint32_t phy_auto_discover(enet_dev_if_t * enetIfPtr);

/*!
 * @brief Gets the PHY link speed.
 *
 * @param enetIfPtr The ENET context structure.
 * @param status The link speed of PHY.
 * @return The execution status.
 */
uint32_t phy_get_link_speed(enet_dev_if_t * enetIfPtr, enet_phy_speed_t *status);

/*!
 * @brief Gets the PHY link status.
 *
 * @param enetIfPtr The ENET context structure.
 * @param status The link on or down status of the PHY.
 * @return The execution status.
 */
uint32_t phy_get_link_status(enet_dev_if_t * enetIfPtr, bool *status);

/*!
 * @brief Gets the PHY link duplex.
 *
 * @param enetIfPtr The ENET context structure.
 * @param status The link duplex status of PHY.
 * @return The execution status.
 */
uint32_t phy_get_link_duplex(enet_dev_if_t * enetIfPtr, enet_phy_duplex_t *status);

/* @} */

#if defined(__cplusplus)
}
#endif

#endif

/*! @}*/

#endif /* __FSL_PHY_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

