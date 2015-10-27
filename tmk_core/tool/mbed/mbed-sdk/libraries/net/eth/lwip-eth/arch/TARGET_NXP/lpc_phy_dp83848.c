/**********************************************************************
* $Id$		lpc_phy_dp83848.c			2011-11-20
*//**
* @file		lpc_phy_dp83848.c
* @brief	DP83848C PHY status and control.
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

#include "lwip/opt.h"
#include "lwip/err.h"
#include "lwip/tcpip.h"
#include "lwip/snmp.h"
#include "lpc_emac_config.h"
#include "lpc_phy.h"
#include "lpc17xx_emac.h"

/** @defgroup dp83848_phy	PHY status and control for the DP83848.
 * @ingroup lwip_phy
 *
 * Various functions for controlling and monitoring the status of the
 * DP83848 PHY. In polled (standalone) systems, the PHY state must be
 * monitored as part of the application. In a threaded (RTOS) system,
 * the PHY state is monitored by the PHY handler thread. The MAC
 * driver will not transmit unless the PHY link is active.
 * @{
 */

/** \brief  DP83848 PHY register offsets */
#define DP8_BMCR_REG        0x0  /**< Basic Mode Control Register */
#define DP8_BMSR_REG        0x1  /**< Basic Mode Status Reg */
#define DP8_IDR1_REG        0x2  /**< Basic Mode Status Reg */
#define DP8_IDR2_REG        0x3  /**< Basic Mode Status Reg */
#define DP8_ANADV_REG       0x4  /**< Auto_Neg Advt Reg  */
#define DP8_ANLPA_REG       0x5  /**< Auto_neg Link Partner Ability Reg */
#define DP8_ANEEXP_REG      0x6  /**< Auto-neg Expansion Reg  */
#define DP8_PHY_STAT_REG    0x10 /**< PHY Status Register  */
#define DP8_PHY_INT_CTL_REG 0x11 /**< PHY Interrupt Control Register */
#define DP8_PHY_RBR_REG     0x17 /**< PHY RMII and Bypass Register  */
#define DP8_PHY_STS_REG     0x19 /**< PHY Status Register  */

#define DP8_PHY_SCSR_REG    0x1f /**< PHY Special Control/Status Register (LAN8720)  */

/** \brief DP83848 Control register definitions */
#define DP8_RESET          (1 << 15)  /**< 1= S/W Reset */
#define DP8_LOOPBACK       (1 << 14)  /**< 1=loopback Enabled */
#define DP8_SPEED_SELECT   (1 << 13)  /**< 1=Select 100MBps */
#define DP8_AUTONEG        (1 << 12)  /**< 1=Enable auto-negotiation */
#define DP8_POWER_DOWN     (1 << 11)  /**< 1=Power down PHY */
#define DP8_ISOLATE        (1 << 10)  /**< 1=Isolate PHY */
#define DP8_RESTART_AUTONEG (1 << 9)  /**< 1=Restart auto-negoatiation */
#define DP8_DUPLEX_MODE    (1 << 8)   /**< 1=Full duplex mode */
#define DP8_COLLISION_TEST (1 << 7)   /**< 1=Perform collsion test */

/** \brief DP83848 Status register definitions */
#define DP8_100BASE_T4     (1 << 15)  /**< T4 mode */
#define DP8_100BASE_TX_FD  (1 << 14)  /**< 100MBps full duplex */
#define DP8_100BASE_TX_HD  (1 << 13)  /**< 100MBps half duplex */
#define DP8_10BASE_T_FD    (1 << 12)  /**< 100Bps full duplex */
#define DP8_10BASE_T_HD    (1 << 11)  /**< 10MBps half duplex */
#define DP8_MF_PREAMB_SUPPR (1 << 6)  /**< Preamble suppress */
#define DP8_AUTONEG_COMP   (1 << 5)   /**< Auto-negotation complete */
#define DP8_RMT_FAULT      (1 << 4)   /**< Fault */
#define DP8_AUTONEG_ABILITY (1 << 3)  /**< Auto-negotation supported */
#define DP8_LINK_STATUS    (1 << 2)   /**< 1=Link active */
#define DP8_JABBER_DETECT  (1 << 1)   /**< Jabber detect */
#define DP8_EXTEND_CAPAB   (1 << 0)   /**< Supports extended capabilities */

/** \brief DP83848 PHY RBR MII dode definitions */
#define DP8_RBR_RMII_MODE  (1 << 5)   /**< Use RMII mode */

/** \brief DP83848 PHY status definitions */
#define DP8_REMOTEFAULT    (1 << 6)   /**< Remote fault */
#define DP8_FULLDUPLEX     (1 << 2)   /**< 1=full duplex */
#define DP8_SPEED10MBPS    (1 << 1)   /**< 1=10MBps speed */
#define DP8_VALID_LINK     (1 << 0)   /**< 1=Link active */

/** \brief DP83848 PHY ID register definitions */
#define DP8_PHYID1_OUI     0x2000     /**< Expected PHY ID1 */
#define DP8_PHYID2_OUI     0x5c90     /**< Expected PHY ID2 */

/** \brief LAN8720 PHY Special Control/Status Register */
#define PHY_SCSR_100MBIT    0x0008    /**< Speed: 1=100 MBit, 0=10Mbit */
#define PHY_SCSR_DUPLEX     0x0010    /**< PHY Duplex Mask             */

/** \brief Link status bits */
#define LNK_STAT_VALID       0x01 
#define LNK_STAT_FULLDUPLEX  0x02
#define LNK_STAT_SPEED10MPS  0x04

/** \brief PHY ID definitions */
#define DP83848C_ID         0x20005C90  /**< PHY Identifier - DP83848C */
#define LAN8720_ID          0x0007C0F0  /**< PHY Identifier - LAN8720  */

/** \brief PHY status structure used to indicate current status of PHY.
 */
typedef struct {
	u32_t     phy_speed_100mbs:1; /**< 10/100 MBS connection speed flag. */
	u32_t     phy_full_duplex:1;  /**< Half/full duplex connection speed flag. */
	u32_t     phy_link_active:1;  /**< Phy link active flag. */
} PHY_STATUS_TYPE;

/** \brief  PHY update flags */
static PHY_STATUS_TYPE physts;

/** \brief  Last PHY update flags, used for determing if something has changed */
static PHY_STATUS_TYPE olddphysts;

/** \brief  PHY update counter for state machine */
static s32_t phyustate;

/** \brief  Holds the PHY ID */
static u32_t phy_id;

/** \brief  Temporary holder of link status for LAN7420 */
static u32_t phy_lan7420_sts_tmp;

/* Write a value via the MII link (non-blocking) */
void lpc_mii_write_noblock(u32_t PhyReg, u32_t Value)
{
	/* Write value at PHY address and register */
	LPC_EMAC->MADR = (LPC_PHYDEF_PHYADDR << 8) | PhyReg;
	LPC_EMAC->MWTD = Value;
}

/* Write a value via the MII link (blocking) */
err_t lpc_mii_write(u32_t PhyReg, u32_t Value)
{
	u32_t mst = 250;
	err_t sts = ERR_OK;

	/* Write value at PHY address and register */
	lpc_mii_write_noblock(PhyReg, Value);

	/* Wait for unbusy status */
	while (mst > 0) {
		sts = LPC_EMAC->MIND;
		if ((sts & EMAC_MIND_BUSY) == 0)
			mst = 0;
		else {
			mst--;
			osDelay(1);
		}
	}

	if (sts != 0)
		sts = ERR_TIMEOUT;

	return sts;
}

/* Reads current MII link busy status */
u32_t lpc_mii_is_busy(void)
{
	return (u32_t) (LPC_EMAC->MIND & EMAC_MIND_BUSY);
}

/* Starts a read operation via the MII link (non-blocking) */
u32_t lpc_mii_read_data(void)
{
	u32_t data = LPC_EMAC->MRDD;
	LPC_EMAC->MCMD = 0;

	return data;
}

/* Starts a read operation via the MII link (non-blocking) */
void lpc_mii_read_noblock(u32_t PhyReg)
{
	/* Read value at PHY address and register */
	LPC_EMAC->MADR = (LPC_PHYDEF_PHYADDR << 8) | PhyReg;
	LPC_EMAC->MCMD = EMAC_MCMD_READ;
}

/* Read a value via the MII link (blocking) */
err_t lpc_mii_read(u32_t PhyReg, u32_t *data)
{
	u32_t mst = 250;
	err_t sts = ERR_OK;

	/* Read value at PHY address and register */
	lpc_mii_read_noblock(PhyReg);

	/* Wait for unbusy status */
	while (mst > 0) {
		sts = LPC_EMAC->MIND & ~EMAC_MIND_MII_LINK_FAIL;
		if ((sts & EMAC_MIND_BUSY) == 0) {
			mst = 0;
			*data = LPC_EMAC->MRDD;
		} else {
			mst--;
			osDelay(1);
		}
	}

	LPC_EMAC->MCMD = 0;

	if (sts != 0)
		sts = ERR_TIMEOUT;

	return sts;
}



/** \brief  Update PHY status from passed value
 *
 *  This function updates the current PHY status based on the
 *  passed PHY status word. The PHY status indicate if the link
 *  is active, the connection speed, and duplex.
 *
 *  \param[in]    netif   NETIF structure
 *  \param[in]    linksts Status word from PHY
 *  \return        1 if the status has changed, otherwise 0
 */
static s32_t lpc_update_phy_sts(struct netif *netif, u32_t linksts)
{
	s32_t changed = 0;

	/* Update link active status */
	if (linksts & LNK_STAT_VALID)
		physts.phy_link_active = 1;
	else
		physts.phy_link_active = 0;

	/* Full or half duplex */
	if (linksts & LNK_STAT_FULLDUPLEX)
		physts.phy_full_duplex = 1;
	else
		physts.phy_full_duplex = 0;

	/* Configure 100MBit/10MBit mode. */
	if (linksts & LNK_STAT_SPEED10MPS)
		physts.phy_speed_100mbs = 0;
	else
		physts.phy_speed_100mbs = 1;

	if (physts.phy_speed_100mbs != olddphysts.phy_speed_100mbs) {
		changed = 1;
		if (physts.phy_speed_100mbs) {
			/* 100MBit mode. */
			lpc_emac_set_speed(1);

			NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 100000000);
		}
		else {
			/* 10MBit mode. */
			lpc_emac_set_speed(0);

			NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 10000000);
		}

		olddphysts.phy_speed_100mbs = physts.phy_speed_100mbs;
	}

	if (physts.phy_full_duplex != olddphysts.phy_full_duplex) {
		changed = 1;
		if (physts.phy_full_duplex)
			lpc_emac_set_duplex(1);
		else
			lpc_emac_set_duplex(0);

		olddphysts.phy_full_duplex = physts.phy_full_duplex;
	}

	if (physts.phy_link_active != olddphysts.phy_link_active) {
		changed = 1;
#if NO_SYS == 1
		if (physts.phy_link_active)
			netif_set_link_up(netif);
		else
			netif_set_link_down(netif);
#else
        if (physts.phy_link_active)
            tcpip_callback_with_block((tcpip_callback_fn) netif_set_link_up,
                (void*) netif, 1);
         else
            tcpip_callback_with_block((tcpip_callback_fn) netif_set_link_down,
                (void*) netif, 1);
#endif

		olddphysts.phy_link_active = physts.phy_link_active;
	}

	return changed;
}

/** \brief  Initialize the DP83848 PHY.
 *
 *  This function initializes the DP83848 PHY. It will block until
 *  complete. This function is called as part of the EMAC driver
 *  initialization. Configuration of the PHY at startup is
 *  controlled by setting up configuration defines in lpc_phy.h.
 *
 *  \param[in]     netif   NETIF structure
 *  \param[in]     rmii    If set, configures the PHY for RMII mode
 *  \return         ERR_OK if the setup was successful, otherwise ERR_TIMEOUT
 */
err_t lpc_phy_init(struct netif *netif, int rmii)
{
	u32_t tmp;
	s32_t i;

	physts.phy_speed_100mbs = olddphysts.phy_speed_100mbs = 0;
	physts.phy_full_duplex = olddphysts.phy_full_duplex = 0;
	physts.phy_link_active = olddphysts.phy_link_active = 0;
	phyustate = 0;

	/* Only first read and write are checked for failure */
	/* Put the DP83848C in reset mode and wait for completion */
	if (lpc_mii_write(DP8_BMCR_REG, DP8_RESET) != 0)
		return ERR_TIMEOUT;
	i = 400;
	while (i > 0) {
	    osDelay(1);   /* 1 ms */
		if (lpc_mii_read(DP8_BMCR_REG, &tmp) != 0)
			return ERR_TIMEOUT;

		if (!(tmp & (DP8_RESET | DP8_POWER_DOWN)))
			i = -1;
		else
			i--;
	}
	/* Timeout? */
	if (i == 0)
		return ERR_TIMEOUT;

	// read PHY ID
	lpc_mii_read(DP8_IDR1_REG, &tmp);
	phy_id = (tmp << 16);
	lpc_mii_read(DP8_IDR2_REG, &tmp);    
	phy_id |= (tmp & 0XFFF0);    

	/* Setup link based on configuration options */
#if PHY_USE_AUTONEG==1
	tmp = DP8_AUTONEG;
#else
	tmp = 0;
#endif
#if PHY_USE_100MBS==1
	tmp |= DP8_SPEED_SELECT;
#endif
#if PHY_USE_FULL_DUPLEX==1
	tmp |= DP8_DUPLEX_MODE;
#endif
	lpc_mii_write(DP8_BMCR_REG, tmp);

    /* Enable RMII mode for PHY */
    if (rmii)
        lpc_mii_write(DP8_PHY_RBR_REG, DP8_RBR_RMII_MODE);

	/* The link is not set active at this point, but will be detected
       later */

	return ERR_OK;
}

/* Phy status update state machine */
s32_t lpc_phy_sts_sm(struct netif *netif)
{
	s32_t changed = 0;
	u32_t data = 0;
	u32_t tmp;

	switch (phyustate) {
		default:
		case 0:
			if (phy_id == DP83848C_ID) {    
				lpc_mii_read_noblock(DP8_PHY_STAT_REG);
				phyustate = 2;
			}
			else if (phy_id == LAN8720_ID) {
				lpc_mii_read_noblock(DP8_PHY_SCSR_REG);
				phyustate = 1;        
			}
			break;

		case 1:
			if (phy_id == LAN8720_ID) {
				tmp = lpc_mii_read_data();
				// we get speed and duplex here. 
				phy_lan7420_sts_tmp =  (tmp & PHY_SCSR_DUPLEX)  ? LNK_STAT_FULLDUPLEX : 0;
				phy_lan7420_sts_tmp |= (tmp & PHY_SCSR_100MBIT) ? 0 : LNK_STAT_SPEED10MPS;

				//read the status register to get link status 
				lpc_mii_read_noblock(DP8_BMSR_REG);
				phyustate = 2;        
			}
			break;

		case 2:
			/* Wait for read status state */
			if (!lpc_mii_is_busy()) {
				/* Update PHY status */
				tmp = lpc_mii_read_data();

				if (phy_id == DP83848C_ID) {
					// STS register contains all needed status bits
					data  = (tmp & DP8_VALID_LINK) ? LNK_STAT_VALID : 0;
					data |= (tmp & DP8_FULLDUPLEX) ? LNK_STAT_FULLDUPLEX : 0;
					data |= (tmp & DP8_SPEED10MBPS) ? LNK_STAT_SPEED10MPS : 0;
				}
				else if (phy_id == LAN8720_ID) {    
					// we only get the link status here.
					phy_lan7420_sts_tmp |= (tmp & DP8_LINK_STATUS) ? LNK_STAT_VALID : 0;
					data = phy_lan7420_sts_tmp;          
				}

				changed = lpc_update_phy_sts(netif, data);        
				phyustate = 0;                
			}
			break;
	}

	return changed;
}

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
