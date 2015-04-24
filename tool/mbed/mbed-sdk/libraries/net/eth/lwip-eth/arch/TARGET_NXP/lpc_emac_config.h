/**********************************************************************
* $Id$		lpc_emac_config.h			2011-11-20
*//**
* @file		lpc_emac_config.h
* @brief	PHY and EMAC configuration file
* @version	1.0
* @date		20 Nov. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

#ifndef __LPC_EMAC_CONFIG_H
#define __LPC_EMAC_CONFIG_H

#include "lwip/opt.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @defgroup lwip_phy_config	LWIP PHY configuration
 * @ingroup lwip_phy
 *
 * Configuration options for the PHY connected to the LPC EMAC.
 * @{
 */

/** \brief  The PHY address connected the to MII/RMII
 */
#define LPC_PHYDEF_PHYADDR 1    /**< The PHY address on the PHY device. */

/** \brief  Enable autonegotiation mode.
 *          If this is enabled, the PHY will attempt to auto-negotiate the
 *          best link mode if the PHY supports it. If this is not enabled,
 *          the PHY_USE_FULL_DUPLEX and PHY_USE_100MBS defines will be
 *          used to select the link mode. Note that auto-negotiation may
 *          take a few seconds to complete.
 */
#define PHY_USE_AUTONEG 1 /**< Enables auto-negotiation mode. */

/** \brief  Sets up the PHY interface to either full duplex operation or
 *          half duplex operation if PHY_USE_AUTONEG is not enabled.
 */
#define PHY_USE_FULL_DUPLEX 1 /**< Sets duplex mode to full. */

/** \brief  Sets up the PHY interface to either 100MBS operation or 10MBS
 *          operation if PHY_USE_AUTONEG is not enabled.
 */
#define PHY_USE_100MBS 1 /**< Sets data rate to 100Mbps. */

/**		  
 * @}
 */

/** @defgroup lwip_emac_config	LWIP EMAC configuration
 * @ingroup lwip_emac
 *
 * Configuration options for the LPC EMAC.
 * @{
 */

/** \brief  Selects RMII or MII connection type in the EMAC peripheral
 */
#define LPC_EMAC_RMII 1         /**< Use the RMII or MII driver variant .*/

/** \brief  Defines the number of descriptors used for RX. This
 *          must be a minimum value of 2.
 */
#define LPC_NUM_BUFF_RXDESCS 3

/** \brief  Defines the number of descriptors used for TX. Must
 *          be a minimum value of 2.
 */
#define LPC_NUM_BUFF_TXDESCS (TCP_SND_QUEUELEN + 1)

/** \brief  Set this define to 1 to enable bounce buffers for transmit pbufs
 *          that cannot be sent via the zero-copy method. Some chained pbufs
 *          may have a payload address that links to an area of memory that
 *          cannot be used for transmit DMA operations. If this define is
 *          set to 1, an extra check will be made with the pbufs. If a buffer
 *          is determined to be non-usable for zero-copy, a temporary bounce
 *          buffer will be created and used instead.
 */
#define LPC_TX_PBUF_BOUNCE_EN 1

/**		  
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC_EMAC_CONFIG_H */

/* --------------------------------- End Of File ------------------------------ */
