/**********************************************************************
* $Id$		lpc_phy.h			2011-11-20
*//**
* @file		lpc_phy.h
* @brief	Common PHY definitions used with all PHYs
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

#ifndef __LPC_PHY_H_
#define __LPC_PHY_H_

#include "lwip/opt.h"
#include "lwip/err.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* These PHY functions are usually part of the EMAC driver */

/** \brief  Phy status update state machine
 *
 *  This function provides a state machine for maintaining the PHY
 *  status without blocking. It must be occasionally called for the
 *  PHY status to be maintained.
 *
 *  \param[in]     netif   NETIF structure
 */
s32_t lpc_phy_sts_sm(struct netif *netif);

/** \brief  Initialize the PHY
 *
 *  This function initializes the PHY. It will block until complete.
 *  This function is called as part of the EMAC driver
 *  initialization. Configuration of the PHY at startup is
 *  controlled by setting up configuration defines in lpc_phy.h.
 *
 *  \param[in]     netif   NETIF structure
 *  \param[in]     rmii    If set, configures the PHY for RMII mode
 *  \return         ERR_OK if the setup was successful, otherwise ERR_TIMEOUT
 */
err_t lpc_phy_init(struct netif *netif, int rmii);

/** \brief  Write a value via the MII link (non-blocking)
 *
 *  This function will write a value on the MII link interface to a PHY
 *  or a connected device. The function will return immediately without
 *  a status. Status needs to be polled later to determine if the write
 *  was successful.
 *
 *  \param[in]      PhyReg  PHY register to write to
 *  \param[in]      Value   Value to write
 */
void lpc_mii_write_noblock(u32_t PhyReg, u32_t Value);

/** \brief  Write a value via the MII link (blocking)
 *
 *  This function will write a value on the MII link interface to a PHY
 *  or a connected device. The function will block until complete.
 *
 *  \param[in]      PhyReg  PHY register to write to
 *  \param[in]      Value   Value to write
 * \returns         0 if the write was successful, otherwise !0
 */
err_t lpc_mii_write(u32_t PhyReg, u32_t Value);

/** \brief  Reads current MII link busy status
 *
 *  This function will return the current MII link busy status and is meant to
 *  be used with non-blocking functions for monitor PHY status such as
 *  connection state.
 *
 *  \returns         !0 if the MII link is busy, otherwise 0
 */
u32_t lpc_mii_is_busy(void);

/** \brief  Starts a read operation via the MII link (non-blocking)
 *
 *  This function returns the current value in the MII data register. It is
 *  meant to be used with the non-blocking oeprations. This value should
 *  only be read after a non-block read command has been issued and the
 *  MII status has been determined to be good.
 *
 *  \returns          The current value in the MII value register
 */
u32_t lpc_mii_read_data(void);

/** \brief  Starts a read operation via the MII link (non-blocking)
 *
 *  This function will start a read operation on the MII link interface
 *  from a PHY or a connected device. The function will not block and
 *  the status mist be polled until complete. Once complete, the data
 *  can be read.
 *
 *  \param[in]      PhyReg  PHY register to read from
 */
err_t lpc_mii_read(u32_t PhyReg, u32_t *data);

/** \brief  Read a value via the MII link (blocking)
 *
 *  This function will read a value on the MII link interface from a PHY
 *  or a connected device. The function will block until complete.
 * 
 *  \param[in]      PhyReg  PHY register to read from
 *  \param[in]      data    Pointer to where to save data read via MII
 *  \returns         0 if the read was successful, otherwise !0
 */
void lpc_mii_read_noblock(u32_t PhyReg);

/**
 * This function provides a method for the PHY to setup the EMAC
 * for the PHY negotiated duplex mode.
 *
 * @param[in] full_duplex 0 = half duplex, 1 = full duplex
 */
void lpc_emac_set_duplex(int full_duplex);

/**
 * This function provides a method for the PHY to setup the EMAC
 * for the PHY negotiated bit rate.
 *
 * @param[in] mbs_100     0 = 10mbs mode, 1 = 100mbs mode
 */
void lpc_emac_set_speed(int mbs_100);

#ifdef __cplusplus
}
#endif

#endif /* __LPC_PHY_H_ */

/* --------------------------------- End Of File ------------------------------ */
