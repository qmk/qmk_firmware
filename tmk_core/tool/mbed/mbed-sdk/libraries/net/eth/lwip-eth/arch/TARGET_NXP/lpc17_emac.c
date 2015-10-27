/**********************************************************************
* $Id$		lpc17_emac.c			2011-11-20
*//**
* @file		lpc17_emac.c
* @brief	LPC17 ethernet driver for LWIP
* @version	1.0
* @date		20. Nov. 2011
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
#include "lwip/sys.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "netif/etharp.h"
#include "netif/ppp_oe.h"

#include "lpc17xx_emac.h"
#include "eth_arch.h"
#include "lpc_emac_config.h"
#include "lpc_phy.h"
#include "sys_arch.h"

#include "mbed_interface.h"
#include <string.h>

#ifndef LPC_EMAC_RMII
#error LPC_EMAC_RMII is not defined!
#endif

#if LPC_NUM_BUFF_TXDESCS < 2
#error LPC_NUM_BUFF_TXDESCS must be at least 2
#endif

#if LPC_NUM_BUFF_RXDESCS < 3
#error LPC_NUM_BUFF_RXDESCS must be at least 3
#endif

/** @defgroup lwip17xx_emac_DRIVER	lpc17 EMAC driver for LWIP
 * @ingroup lwip_emac
 *
 * @{
 */

#if NO_SYS == 0
/** \brief  Driver transmit and receive thread priorities
 *
 * Thread priorities for receive thread and TX cleanup thread. Alter
 * to prioritize receive or transmit bandwidth. In a heavily loaded
 * system or with LEIP_DEBUG enabled, the priorities might be better
 * the same. */
#define RX_PRIORITY   (osPriorityNormal)
#define TX_PRIORITY   (osPriorityNormal)

/** \brief  Debug output formatter lock define
 *
 * When using FreeRTOS and with LWIP_DEBUG enabled, enabling this
 * define will allow RX debug messages to not interleave with the
 * TX messages (so they are actually readable). Not enabling this
 * define when the system is under load will cause the output to
 * be unreadable. There is a small tradeoff in performance for this
 * so use it only for debug. */
//#define LOCK_RX_THREAD

/** \brief  Receive group interrupts
 */
#define RXINTGROUP (EMAC_INT_RX_OVERRUN | EMAC_INT_RX_ERR | EMAC_INT_RX_DONE)

/** \brief  Transmit group interrupts
 */
#define TXINTGROUP (EMAC_INT_TX_UNDERRUN | EMAC_INT_TX_ERR | EMAC_INT_TX_DONE)

/** \brief  Signal used for ethernet ISR to signal packet_rx() thread.
 */
#define RX_SIGNAL  1

#else
#define RXINTGROUP 0
#define TXINTGROUP 0
#endif

 /** \brief  Structure of a TX/RX descriptor
 */
typedef struct
{
	volatile u32_t packet;        /**< Pointer to buffer */
	volatile u32_t control;       /**< Control word */
} LPC_TXRX_DESC_T;

/** \brief  Structure of a RX status entry
 */
typedef struct
{
	volatile u32_t statusinfo;   /**< RX status word */
	volatile u32_t statushashcrc; /**< RX hash CRC */
} LPC_TXRX_STATUS_T;

/* LPC EMAC driver data structure */
struct lpc_enetdata {
    /* prxs must be 8 byte aligned! */
	LPC_TXRX_STATUS_T prxs[LPC_NUM_BUFF_RXDESCS]; /**< Pointer to RX statuses */
	struct netif *netif;        /**< Reference back to LWIP parent netif */
	LPC_TXRX_DESC_T ptxd[LPC_NUM_BUFF_TXDESCS];   /**< Pointer to TX descriptor list */
	LPC_TXRX_STATUS_T ptxs[LPC_NUM_BUFF_TXDESCS]; /**< Pointer to TX statuses */
	LPC_TXRX_DESC_T prxd[LPC_NUM_BUFF_RXDESCS];   /**< Pointer to RX descriptor list */
	struct pbuf *rxb[LPC_NUM_BUFF_RXDESCS]; /**< RX pbuf pointer list, zero-copy mode */
	u32_t rx_fill_desc_index; /**< RX descriptor next available index */
	volatile u32_t rx_free_descs; /**< Count of free RX descriptors */
	struct pbuf *txb[LPC_NUM_BUFF_TXDESCS]; /**< TX pbuf pointer list, zero-copy mode */
	u32_t lpc_last_tx_idx; /**< TX last descriptor index, zero-copy mode */
#if NO_SYS == 0
	sys_thread_t RxThread; /**< RX receive thread data object pointer */
	sys_sem_t TxCleanSem; /**< TX cleanup thread wakeup semaphore */
	sys_mutex_t TXLockMutex; /**< TX critical section mutex */
	sys_sem_t xTXDCountSem; /**< TX free buffer counting semaphore */
#endif
};

#if defined(TARGET_LPC4088) || defined(TARGET_LPC4088_DM)
#  if defined (__ICCARM__)
#     define ETHMEM_SECTION
#  elif defined(TOOLCHAIN_GCC_CR)
#     define ETHMEM_SECTION __attribute__((section(".data.$RamPeriph32"), aligned))
#  else
#     define ETHMEM_SECTION __attribute__((section("AHBSRAM1"),aligned))
#  endif
#elif defined(TARGET_LPC1768)
#  if defined(TOOLCHAIN_GCC_ARM)
#     define ETHMEM_SECTION __attribute__((section("AHBSRAM1"),aligned))
#  endif
#endif

#ifndef ETHMEM_SECTION
#define ETHMEM_SECTION ALIGNED(8)
#endif

/** \brief  LPC EMAC driver work data
 */
ETHMEM_SECTION struct lpc_enetdata lpc_enetdata;

/** \brief  Queues a pbuf into the RX descriptor list
 *
 *  \param[in] lpc_enetif Pointer to the drvier data structure
 *  \param[in] p            Pointer to pbuf to queue
 */
static void lpc_rxqueue_pbuf(struct lpc_enetdata *lpc_enetif, struct pbuf *p)
{
	u32_t idx;

	/* Get next free descriptor index */
	idx = lpc_enetif->rx_fill_desc_index;

	/* Setup descriptor and clear statuses */
	lpc_enetif->prxd[idx].control = EMAC_RCTRL_INT | ((u32_t) (p->len - 1));
	lpc_enetif->prxd[idx].packet = (u32_t) p->payload;
	lpc_enetif->prxs[idx].statusinfo = 0xFFFFFFFF;
	lpc_enetif->prxs[idx].statushashcrc = 0xFFFFFFFF;

	/* Save pbuf pointer for push to network layer later */
	lpc_enetif->rxb[idx] = p;

	/* Wrap at end of descriptor list */
	idx++;
	if (idx >= LPC_NUM_BUFF_RXDESCS)
		idx = 0;

	/* Queue descriptor(s) */
	lpc_enetif->rx_free_descs -= 1;
	lpc_enetif->rx_fill_desc_index = idx;
	LPC_EMAC->RxConsumeIndex = idx;

	LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
		("lpc_rxqueue_pbuf: pbuf packet queued: %p (free desc=%d)\n", p,
			lpc_enetif->rx_free_descs));
}

/** \brief  Attempt to allocate and requeue a new pbuf for RX
 *
 *  \param[in]     netif Pointer to the netif structure
 *  \returns         1 if a packet was allocated and requeued, otherwise 0
 */
s32_t lpc_rx_queue(struct netif *netif)
{
	struct lpc_enetdata *lpc_enetif = netif->state;
	struct pbuf *p;
	s32_t queued = 0;

	/* Attempt to requeue as many packets as possible */
	while (lpc_enetif->rx_free_descs > 0) {
		/* Allocate a pbuf from the pool. We need to allocate at the
		   maximum size as we don't know the size of the yet to be
		   received packet. */
		p = pbuf_alloc(PBUF_RAW, (u16_t) EMAC_ETH_MAX_FLEN, PBUF_RAM);
		if (p == NULL) {
			LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
				("lpc_rx_queue: could not allocate RX pbuf (free desc=%d)\n",
				lpc_enetif->rx_free_descs));
			return queued;
		}

		/* pbufs allocated from the RAM pool should be non-chained. */
		LWIP_ASSERT("lpc_rx_queue: pbuf is not contiguous (chained)",
			pbuf_clen(p) <= 1);

		/* Queue packet */
		lpc_rxqueue_pbuf(lpc_enetif, p);

		/* Update queued count */
		queued++;
	}

	return queued;
}

/** \brief  Sets up the RX descriptor ring buffers.
 *
 *  This function sets up the descriptor list used for receive packets.
 *
 *  \param[in]  lpc_enetif  Pointer to driver data structure
 *  \returns                   Always returns ERR_OK
 */
static err_t lpc_rx_setup(struct lpc_enetdata *lpc_enetif)
{
	/* Setup pointers to RX structures */
	LPC_EMAC->RxDescriptor = (u32_t) &lpc_enetif->prxd[0];
	LPC_EMAC->RxStatus = (u32_t) &lpc_enetif->prxs[0];
	LPC_EMAC->RxDescriptorNumber = LPC_NUM_BUFF_RXDESCS - 1;

	lpc_enetif->rx_free_descs = LPC_NUM_BUFF_RXDESCS;
	lpc_enetif->rx_fill_desc_index = 0;

	/* Build RX buffer and descriptors */
	lpc_rx_queue(lpc_enetif->netif);

	return ERR_OK;
}

/** \brief  Allocates a pbuf and returns the data from the incoming packet.
 *
 *  \param[in] netif the lwip network interface structure for this lpc_enetif
 *  \return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *lpc_low_level_input(struct netif *netif)
{
	struct lpc_enetdata *lpc_enetif = netif->state;
	struct pbuf *p = NULL;
	u32_t idx, length;
	u16_t origLength;

#ifdef LOCK_RX_THREAD
#if NO_SYS == 0
	/* Get exclusive access */
	sys_mutex_lock(&lpc_enetif->TXLockMutex);
#endif
#endif

	/* Monitor RX overrun status. This should never happen unless
	   (possibly) the internal bus is behing held up by something.
	   Unless your system is running at a very low clock speed or
	   there are possibilities that the internal buses may be held
	   up for a long time, this can probably safely be removed. */
	if (LPC_EMAC->IntStatus & EMAC_INT_RX_OVERRUN) {
		LINK_STATS_INC(link.err);
		LINK_STATS_INC(link.drop);

		/* Temporarily disable RX */
		LPC_EMAC->MAC1 &= ~EMAC_MAC1_REC_EN;

		/* Reset the RX side */
		LPC_EMAC->MAC1 |= EMAC_MAC1_RES_RX;
		LPC_EMAC->IntClear = EMAC_INT_RX_OVERRUN;

		/* De-allocate all queued RX pbufs */
		for (idx = 0; idx < LPC_NUM_BUFF_RXDESCS; idx++) {
			if (lpc_enetif->rxb[idx] != NULL) {
				pbuf_free(lpc_enetif->rxb[idx]);
				lpc_enetif->rxb[idx] = NULL;
			}
		}

		/* Start RX side again */
		lpc_rx_setup(lpc_enetif);

		/* Re-enable RX */
		LPC_EMAC->MAC1 |= EMAC_MAC1_REC_EN;

#ifdef LOCK_RX_THREAD
#if NO_SYS == 0
		sys_mutex_unlock(&lpc_enetif->TXLockMutex);
#endif
#endif

		return NULL;
	}

	/* Determine if a frame has been received */
	length = 0;
	idx = LPC_EMAC->RxConsumeIndex;
	if (LPC_EMAC->RxProduceIndex != idx) {
		/* Handle errors */
		if (lpc_enetif->prxs[idx].statusinfo & (EMAC_RINFO_CRC_ERR |
			EMAC_RINFO_SYM_ERR | EMAC_RINFO_ALIGN_ERR | EMAC_RINFO_LEN_ERR)) {
#if LINK_STATS
			if (lpc_enetif->prxs[idx].statusinfo & (EMAC_RINFO_CRC_ERR |
				EMAC_RINFO_SYM_ERR | EMAC_RINFO_ALIGN_ERR))
				LINK_STATS_INC(link.chkerr);
			if (lpc_enetif->prxs[idx].statusinfo & EMAC_RINFO_LEN_ERR)
				LINK_STATS_INC(link.lenerr);
#endif

			/* Drop the frame */
			LINK_STATS_INC(link.drop);

			/* Re-queue the pbuf for receive */
			lpc_enetif->rx_free_descs++;
			p = lpc_enetif->rxb[idx];
			lpc_enetif->rxb[idx] = NULL;
			lpc_rxqueue_pbuf(lpc_enetif, p);

			LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
				("lpc_low_level_input: Packet dropped with errors (0x%x)\n",
				lpc_enetif->prxs[idx].statusinfo));

			p = NULL;
		} else {
			/* A packet is waiting, get length */
			length = (lpc_enetif->prxs[idx].statusinfo & 0x7FF) + 1;

			/* Zero-copy */
			p = lpc_enetif->rxb[idx];
			origLength = p->len;
			p->len = (u16_t) length;

			/* Free pbuf from descriptor */
			lpc_enetif->rxb[idx] = NULL;
			lpc_enetif->rx_free_descs++;

			/* Attempt to queue new buffer(s) */
			if (lpc_rx_queue(lpc_enetif->netif) == 0) {
    			/* Drop the frame due to OOM. */
    			LINK_STATS_INC(link.drop);

    			/* Re-queue the pbuf for receive */
    			p->len = origLength;
    			lpc_rxqueue_pbuf(lpc_enetif, p);

    			LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
    				("lpc_low_level_input: Packet index %d dropped for OOM\n",
    				idx));
			
#ifdef LOCK_RX_THREAD
#if NO_SYS == 0
        		sys_mutex_unlock(&lpc_enetif->TXLockMutex);
#endif
#endif

		        return NULL;
			}

			LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
				("lpc_low_level_input: Packet received: %p, size %d (index=%d)\n",
				p, length, idx));

			/* Save size */
			p->tot_len = (u16_t) length;
			LINK_STATS_INC(link.recv);
		}
	}

#ifdef LOCK_RX_THREAD
#if NO_SYS == 0
	sys_mutex_unlock(&lpc_enetif->TXLockMutex);
#endif
#endif

	return p;
}

/** \brief  Attempt to read a packet from the EMAC interface.
 *
 *  \param[in] netif the lwip network interface structure for this lpc_enetif
 */
void lpc_enetif_input(struct netif *netif)
{
	struct eth_hdr *ethhdr;
	struct pbuf *p;

	/* move received packet into a new pbuf */
	p = lpc_low_level_input(netif);
	if (p == NULL)
		return;

	/* points to packet payload, which starts with an Ethernet header */
	ethhdr = p->payload;

	switch (htons(ethhdr->type)) {
		case ETHTYPE_IP:
		case ETHTYPE_ARP:
#if PPPOE_SUPPORT
		case ETHTYPE_PPPOEDISC:
		case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
			/* full packet send to tcpip_thread to process */
			if (netif->input(p, netif) != ERR_OK) {
				LWIP_DEBUGF(NETIF_DEBUG, ("lpc_enetif_input: IP input error\n"));
				/* Free buffer */
				pbuf_free(p);
			}
			break;

		default:
			/* Return buffer */
			pbuf_free(p);
			break;
	}
}

/** \brief  Determine if the passed address is usable for the ethernet
 *          DMA controller.
 *
 *  \param[in] addr Address of packet to check for DMA safe operation
 *  \return          1 if the packet address is not safe, otherwise 0
 */
static s32_t lpc_packet_addr_notsafe(void *addr) {
	/* Check for legal address ranges */
#if defined(TARGET_LPC1768)
	if ((((u32_t) addr >= 0x2007C000) && ((u32_t) addr < 0x20083FFF))) {
#elif defined(TARGET_LPC4088) || defined(TARGET_LPC4088_DM)
	if ((((u32_t) addr >= 0x20000000) && ((u32_t) addr < 0x20007FFF))) {
#endif
	    return 0;
	}
	return 1;
}

/** \brief  Sets up the TX descriptor ring buffers.
 *
 *  This function sets up the descriptor list used for transmit packets.
 *
 *  \param[in]      lpc_enetif  Pointer to driver data structure
 */
static err_t lpc_tx_setup(struct lpc_enetdata *lpc_enetif)
{
	s32_t idx;

	/* Build TX descriptors for local buffers */
	for (idx = 0; idx < LPC_NUM_BUFF_TXDESCS; idx++) {
		lpc_enetif->ptxd[idx].control = 0;
		lpc_enetif->ptxs[idx].statusinfo = 0xFFFFFFFF;
	}

	/* Setup pointers to TX structures */
	LPC_EMAC->TxDescriptor = (u32_t) &lpc_enetif->ptxd[0];
	LPC_EMAC->TxStatus = (u32_t) &lpc_enetif->ptxs[0];
	LPC_EMAC->TxDescriptorNumber = LPC_NUM_BUFF_TXDESCS - 1;

	lpc_enetif->lpc_last_tx_idx = 0;

	return ERR_OK;
}

/** \brief  Free TX buffers that are complete
 *
 *  \param[in] lpc_enetif  Pointer to driver data structure
 *  \param[in] cidx  EMAC current descriptor comsumer index
 */
static void lpc_tx_reclaim_st(struct lpc_enetdata *lpc_enetif, u32_t cidx)
{
#if NO_SYS == 0
	/* Get exclusive access */
	sys_mutex_lock(&lpc_enetif->TXLockMutex);
#endif

	while (cidx != lpc_enetif->lpc_last_tx_idx) {
		if (lpc_enetif->txb[lpc_enetif->lpc_last_tx_idx] != NULL) {
			LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
				("lpc_tx_reclaim_st: Freeing packet %p (index %d)\n",
				lpc_enetif->txb[lpc_enetif->lpc_last_tx_idx],
				lpc_enetif->lpc_last_tx_idx));
			pbuf_free(lpc_enetif->txb[lpc_enetif->lpc_last_tx_idx]);
		 	lpc_enetif->txb[lpc_enetif->lpc_last_tx_idx] = NULL;
		}

#if NO_SYS == 0
		osSemaphoreRelease(lpc_enetif->xTXDCountSem.id);
#endif
		lpc_enetif->lpc_last_tx_idx++;
		if (lpc_enetif->lpc_last_tx_idx >= LPC_NUM_BUFF_TXDESCS)
			lpc_enetif->lpc_last_tx_idx = 0;
	}

#if NO_SYS == 0
	/* Restore access */
	sys_mutex_unlock(&lpc_enetif->TXLockMutex);
#endif
}

/** \brief  User call for freeingTX buffers that are complete
 *
 *  \param[in] netif the lwip network interface structure for this lpc_enetif
 */
void lpc_tx_reclaim(struct netif *netif)
{
	lpc_tx_reclaim_st((struct lpc_enetdata *) netif->state,
		LPC_EMAC->TxConsumeIndex);
}

 /** \brief  Polls if an available TX descriptor is ready. Can be used to
 *           determine if the low level transmit function will block.
 *
 *  \param[in] netif the lwip network interface structure for this lpc_enetif
 *  \return 0 if no descriptors are read, or >0
 */
s32_t lpc_tx_ready(struct netif *netif)
{
	s32_t fb;
	u32_t idx, cidx;

	cidx = LPC_EMAC->TxConsumeIndex;
	idx = LPC_EMAC->TxProduceIndex;

	/* Determine number of free buffers */
	if (idx == cidx)
		fb = LPC_NUM_BUFF_TXDESCS;
	else if (cidx > idx)
		fb = (LPC_NUM_BUFF_TXDESCS - 1) -
			((idx + LPC_NUM_BUFF_TXDESCS) - cidx);
	else
		fb = (LPC_NUM_BUFF_TXDESCS - 1) - (cidx - idx);

	return fb;
}

/** \brief  Low level output of a packet. Never call this from an
 *          interrupt context, as it may block until TX descriptors
 *          become available.
 *
 *  \param[in] netif the lwip network interface structure for this lpc_enetif
 *  \param[in] p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 *  \return ERR_OK if the packet could be sent or an err_t value if the packet couldn't be sent
 */
static err_t lpc_low_level_output(struct netif *netif, struct pbuf *p)
{
	struct lpc_enetdata *lpc_enetif = netif->state;
	struct pbuf *q;
	u8_t *dst;
    u32_t idx, notdmasafe = 0;
	struct pbuf *np;
	s32_t dn;

	/* Zero-copy TX buffers may be fragmented across mutliple payload
	   chains. Determine the number of descriptors needed for the
	   transfer. The pbuf chaining can be a mess! */
	dn = (s32_t) pbuf_clen(p);

	/* Test to make sure packet addresses are DMA safe. A DMA safe
	   address is once that uses external memory or periphheral RAM.
	   IRAM and FLASH are not safe! */
	for (q = p; q != NULL; q = q->next)
		notdmasafe += lpc_packet_addr_notsafe(q->payload);

#if LPC_TX_PBUF_BOUNCE_EN==1
	/* If the pbuf is not DMA safe, a new bounce buffer (pbuf) will be
	   created that will be used instead. This requires an copy from the
	   non-safe DMA region to the new pbuf */
	if (notdmasafe) {
		/* Allocate a pbuf in DMA memory */
		np = pbuf_alloc(PBUF_RAW, p->tot_len, PBUF_RAM);
		if (np == NULL)
			return ERR_MEM;

		/* This buffer better be contiguous! */
		LWIP_ASSERT("lpc_low_level_output: New transmit pbuf is chained",
			(pbuf_clen(np) == 1));

		/* Copy to DMA safe pbuf */
		dst = (u8_t *) np->payload;
	 	for(q = p; q != NULL; q = q->next) {
			/* Copy the buffer to the descriptor's buffer */
	  		MEMCPY(dst, (u8_t *) q->payload, q->len);
		  dst += q->len;
		}
		np->len = p->tot_len;

		LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
			("lpc_low_level_output: Switched to DMA safe buffer, old=%p, new=%p\n",
			q, np));

		/* use the new buffer for descrptor queueing. The original pbuf will
		   be de-allocated outsuide this driver. */
		p = np;
		dn = 1;
	}
#else
	if (notdmasafe)
		LWIP_ASSERT("lpc_low_level_output: Not a DMA safe pbuf",
			(notdmasafe == 0));
#endif

	/* Wait until enough descriptors are available for the transfer. */
	/* THIS WILL BLOCK UNTIL THERE ARE ENOUGH DESCRIPTORS AVAILABLE */
	while (dn > lpc_tx_ready(netif))
#if NO_SYS == 0
	    osSemaphoreWait(lpc_enetif->xTXDCountSem.id, osWaitForever);
#else
		osDelay(1);
#endif

	/* Get free TX buffer index */
	idx = LPC_EMAC->TxProduceIndex;

#if NO_SYS == 0
	/* Get exclusive access */
	sys_mutex_lock(&lpc_enetif->TXLockMutex);
#endif

	/* Prevent LWIP from de-allocating this pbuf. The driver will
	   free it once it's been transmitted. */
	if (!notdmasafe)
		pbuf_ref(p);

	/* Setup transfers */
	q = p;
	while (dn > 0) {
		dn--;

		/* Only save pointer to free on last descriptor */
		if (dn == 0) {
			/* Save size of packet and signal it's ready */
			lpc_enetif->ptxd[idx].control = (q->len - 1) | EMAC_TCTRL_INT |
				EMAC_TCTRL_LAST;
            lpc_enetif->txb[idx] = p;
		}
		else {
			/* Save size of packet, descriptor is not last */
			lpc_enetif->ptxd[idx].control = (q->len - 1) | EMAC_TCTRL_INT;
			lpc_enetif->txb[idx] = NULL;
		}

		LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
			("lpc_low_level_output: pbuf packet(%p) sent, chain#=%d,"
			" size = %d (index=%d)\n", q->payload, dn, q->len, idx));

		lpc_enetif->ptxd[idx].packet = (u32_t) q->payload;

		q = q->next;

		idx++;
		if (idx >= LPC_NUM_BUFF_TXDESCS)
			idx = 0;
	}

	LPC_EMAC->TxProduceIndex = idx;

	LINK_STATS_INC(link.xmit);

#if NO_SYS == 0
	/* Restore access */
	sys_mutex_unlock(&lpc_enetif->TXLockMutex);
#endif

	return ERR_OK;
}

/** \brief  LPC EMAC interrupt handler.
 *
 *  This function handles the transmit, receive, and error interrupt of
 *  the LPC177x_8x. This is meant to be used when NO_SYS=0.
 */
void ENET_IRQHandler(void)
{
#if NO_SYS == 1
	/* Interrupts are not used without an RTOS */
    NVIC_DisableIRQ(ENET_IRQn);
#else
	uint32_t ints;

	/* Interrupts are of 2 groups - transmit or receive. Based on the
	   interrupt, kick off the receive or transmit (cleanup) task */

	/* Get pending interrupts */
	ints = LPC_EMAC->IntStatus;

	if (ints & RXINTGROUP) {
        /* RX group interrupt(s): Give signal to wakeup RX receive task.*/
        osSignalSet(lpc_enetdata.RxThread->id, RX_SIGNAL);
    }

    if (ints & TXINTGROUP) {
        /* TX group interrupt(s): Give semaphore to wakeup TX cleanup task. */
        sys_sem_signal(&lpc_enetdata.TxCleanSem);
    }

	/* Clear pending interrupts */
	LPC_EMAC->IntClear = ints;
#endif
}

#if NO_SYS == 0
/** \brief  Packet reception task
 *
 * This task is called when a packet is received. It will
 * pass the packet to the LWIP core.
 *
 *  \param[in] pvParameters Not used yet
 */
static void packet_rx(void* pvParameters) {
    struct lpc_enetdata *lpc_enetif = pvParameters;

    while (1) {
        /* Wait for receive task to wakeup */
        osSignalWait(RX_SIGNAL, osWaitForever);

        /* Process packets until all empty */
        while (LPC_EMAC->RxConsumeIndex != LPC_EMAC->RxProduceIndex)
            lpc_enetif_input(lpc_enetif->netif);
    }
}

/** \brief  Transmit cleanup task
 *
 * This task is called when a transmit interrupt occurs and
 * reclaims the pbuf and descriptor used for the packet once
 * the packet has been transferred.
 *
 *  \param[in] pvParameters Not used yet
 */
static void packet_tx(void* pvParameters) {
    struct lpc_enetdata *lpc_enetif = pvParameters;
    s32_t idx;

    while (1) {
        /* Wait for transmit cleanup task to wakeup */
        sys_arch_sem_wait(&lpc_enetif->TxCleanSem, 0);

        /* Error handling for TX underruns. This should never happen unless
           something is holding the bus or the clocks are going too slow. It
            can probably be safely removed. */
        if (LPC_EMAC->IntStatus & EMAC_INT_TX_UNDERRUN) {
            LINK_STATS_INC(link.err);
            LINK_STATS_INC(link.drop);

#if NO_SYS == 0
            /* Get exclusive access */
            sys_mutex_lock(&lpc_enetif->TXLockMutex);
#endif
            /* Reset the TX side */
            LPC_EMAC->MAC1 |= EMAC_MAC1_RES_TX;
            LPC_EMAC->IntClear = EMAC_INT_TX_UNDERRUN;

            /* De-allocate all queued TX pbufs */
            for (idx = 0; idx < LPC_NUM_BUFF_TXDESCS; idx++) {
                if (lpc_enetif->txb[idx] != NULL) {
                    pbuf_free(lpc_enetif->txb[idx]);
                    lpc_enetif->txb[idx] = NULL;
                }
            }

#if NO_SYS == 0
            /* Restore access */
            sys_mutex_unlock(&lpc_enetif->TXLockMutex);
#endif
            /* Start TX side again */
            lpc_tx_setup(lpc_enetif);
        } else {
            /* Free TX buffers that are done sending */
            lpc_tx_reclaim(lpc_enetdata.netif);
        }
    }
}
#endif

/** \brief  Low level init of the MAC and PHY.
 *
 *  \param[in]      netif  Pointer to LWIP netif structure
 */
static err_t low_level_init(struct netif *netif)
{
	struct lpc_enetdata *lpc_enetif = netif->state;
	err_t err = ERR_OK;

	/* Enable MII clocking */
	LPC_SC->PCONP |= CLKPWR_PCONP_PCENET;

#if defined(TARGET_LPC1768)
	LPC_PINCON->PINSEL2 = 0x50150105;                  /* Enable P1 Ethernet Pins. */
	LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~0x0000000F) | 0x00000005;
#elif defined(TARGET_LPC4088) || defined(TARGET_LPC4088_DM)
  LPC_IOCON->P1_0  &= ~0x07;    /*  ENET I/O config */
  LPC_IOCON->P1_0  |= 0x01;     /* ENET_TXD0 */
  LPC_IOCON->P1_1  &= ~0x07;
  LPC_IOCON->P1_1  |= 0x01;     /* ENET_TXD1 */
  LPC_IOCON->P1_4  &= ~0x07;
  LPC_IOCON->P1_4  |= 0x01;     /* ENET_TXEN */
  LPC_IOCON->P1_8  &= ~0x07;
  LPC_IOCON->P1_8  |= 0x01;     /* ENET_CRS */
  LPC_IOCON->P1_9  &= ~0x07;
  LPC_IOCON->P1_9  |= 0x01;     /* ENET_RXD0 */
  LPC_IOCON->P1_10 &= ~0x07;
  LPC_IOCON->P1_10 |= 0x01;     /* ENET_RXD1 */
  LPC_IOCON->P1_14 &= ~0x07;
  LPC_IOCON->P1_14 |= 0x01;     /* ENET_RX_ER */
  LPC_IOCON->P1_15 &= ~0x07;
  LPC_IOCON->P1_15 |= 0x01;     /* ENET_REF_CLK */
  LPC_IOCON->P1_16 &= ~0x07;    /* ENET/PHY I/O config */
  LPC_IOCON->P1_16 |= 0x01;     /* ENET_MDC */
  LPC_IOCON->P1_17 &= ~0x07;
  LPC_IOCON->P1_17 |= 0x01;     /* ENET_MDIO */
#endif

	/* Reset all MAC logic */
	LPC_EMAC->MAC1 = EMAC_MAC1_RES_TX | EMAC_MAC1_RES_MCS_TX |
		EMAC_MAC1_RES_RX | EMAC_MAC1_RES_MCS_RX | EMAC_MAC1_SIM_RES |
		EMAC_MAC1_SOFT_RES;
	LPC_EMAC->Command = EMAC_CR_REG_RES | EMAC_CR_TX_RES | EMAC_CR_RX_RES |
		EMAC_CR_PASS_RUNT_FRM;
	osDelay(10);

	/* Initial MAC initialization */
	LPC_EMAC->MAC1 = EMAC_MAC1_PASS_ALL;
	LPC_EMAC->MAC2 = EMAC_MAC2_CRC_EN | EMAC_MAC2_PAD_EN |
		EMAC_MAC2_VLAN_PAD_EN;
	LPC_EMAC->MAXF = EMAC_ETH_MAX_FLEN;

	/* Set RMII management clock rate to lowest speed */
	LPC_EMAC->MCFG = EMAC_MCFG_CLK_SEL(11) | EMAC_MCFG_RES_MII;
	LPC_EMAC->MCFG &= ~EMAC_MCFG_RES_MII;

	/* Maximum number of retries, 0x37 collision window, gap */
	LPC_EMAC->CLRT = EMAC_CLRT_DEF;
	LPC_EMAC->IPGR = EMAC_IPGR_P1_DEF | EMAC_IPGR_P2_DEF;

#if LPC_EMAC_RMII
	/* RMII setup */
	LPC_EMAC->Command = EMAC_CR_PASS_RUNT_FRM | EMAC_CR_RMII;
#else
	/* MII setup */
	LPC_EMAC->CR = EMAC_CR_PASS_RUNT_FRM;
#endif

	/* Initialize the PHY and reset */
    err = lpc_phy_init(netif, LPC_EMAC_RMII);
	if (err != ERR_OK)
 		return err;

	/* Save station address */
	LPC_EMAC->SA2 = (u32_t) netif->hwaddr[0] |
		(((u32_t) netif->hwaddr[1]) << 8);
	LPC_EMAC->SA1 = (u32_t) netif->hwaddr[2] |
		(((u32_t) netif->hwaddr[3]) << 8);
	LPC_EMAC->SA0 = (u32_t) netif->hwaddr[4] |
		(((u32_t) netif->hwaddr[5]) << 8);

	/* Setup transmit and receive descriptors */
	if (lpc_tx_setup(lpc_enetif) != ERR_OK)
		return ERR_BUF;
	if (lpc_rx_setup(lpc_enetif) != ERR_OK)
		return ERR_BUF;

	/* Enable packet reception */
#if IP_SOF_BROADCAST_RECV
	LPC_EMAC->RxFilterCtrl = EMAC_RFC_PERFECT_EN | EMAC_RFC_BCAST_EN | EMAC_RFC_MCAST_EN;
#else
	LPC_EMAC->RxFilterCtrl = EMAC_RFC_PERFECT_EN;
#endif

	/* Clear and enable rx/tx interrupts */
	LPC_EMAC->IntClear = 0xFFFF;
	LPC_EMAC->IntEnable = RXINTGROUP | TXINTGROUP;

	/* Enable RX and TX */
	LPC_EMAC->Command |= EMAC_CR_RX_EN | EMAC_CR_TX_EN;
	LPC_EMAC->MAC1 |= EMAC_MAC1_REC_EN;

	return err;
}

/* This function provides a method for the PHY to setup the EMAC
   for the PHY negotiated duplex mode */
void lpc_emac_set_duplex(int full_duplex)
{
	if (full_duplex) {
		LPC_EMAC->MAC2    |= EMAC_MAC2_FULL_DUP;
		LPC_EMAC->Command |= EMAC_CR_FULL_DUP;
		LPC_EMAC->IPGT     = EMAC_IPGT_FULL_DUP;
	} else {
		LPC_EMAC->MAC2    &= ~EMAC_MAC2_FULL_DUP;
		LPC_EMAC->Command &= ~EMAC_CR_FULL_DUP;
		LPC_EMAC->IPGT = EMAC_IPGT_HALF_DUP;
	}
}

/* This function provides a method for the PHY to setup the EMAC
   for the PHY negotiated bit rate */
void lpc_emac_set_speed(int mbs_100)
{
	if (mbs_100)
		LPC_EMAC->SUPP = EMAC_SUPP_SPEED;
	else
		LPC_EMAC->SUPP = 0;
}

/**
 * This function is the ethernet packet send function. It calls
 * etharp_output after checking link status.
 *
 * \param[in] netif the lwip network interface structure for this lpc_enetif
 * \param[in] q Pointer to pbug to send
 * \param[in] ipaddr IP address
 * \return ERR_OK or error code
 */
err_t lpc_etharp_output(struct netif *netif, struct pbuf *q,
	ip_addr_t *ipaddr)
{
	/* Only send packet is link is up */
	if (netif->flags & NETIF_FLAG_LINK_UP)
		return etharp_output(netif, q, ipaddr);

	return ERR_CONN;
}

#if NO_SYS == 0
/* periodic PHY status update */
void phy_update(void const *nif) {
    lpc_phy_sts_sm((struct netif*)nif);
}
osTimerDef(phy_update, phy_update);
#endif

/**
 * Should be called at the beginning of the program to set up the
 * network interface.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param[in] netif the lwip network interface structure for this lpc_enetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t eth_arch_enetif_init(struct netif *netif)
{
	err_t err;

	LWIP_ASSERT("netif != NULL", (netif != NULL));

	lpc_enetdata.netif = netif;

	/* set MAC hardware address */
#if (MBED_MAC_ADDRESS_SUM != MBED_MAC_ADDR_INTERFACE)
	netif->hwaddr[0] = MBED_MAC_ADDR_0;
	netif->hwaddr[1] = MBED_MAC_ADDR_1;
	netif->hwaddr[2] = MBED_MAC_ADDR_2;
	netif->hwaddr[3] = MBED_MAC_ADDR_3;
	netif->hwaddr[4] = MBED_MAC_ADDR_4;
	netif->hwaddr[5] = MBED_MAC_ADDR_5;
#else
	mbed_mac_address((char *)netif->hwaddr);
#endif
	netif->hwaddr_len = ETHARP_HWADDR_LEN;

 	/* maximum transfer unit */
	netif->mtu = 1500;

	/* device capabilities */
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET | NETIF_FLAG_IGMP;

	/* Initialize the hardware */
	netif->state = &lpc_enetdata;
	err = low_level_init(netif);
	if (err != ERR_OK)
		return err;

#if LWIP_NETIF_HOSTNAME
	/* Initialize interface hostname */
	netif->hostname = "lwiplpc";
#endif /* LWIP_NETIF_HOSTNAME */

	netif->name[0] = 'e';
	netif->name[1] = 'n';

	netif->output = lpc_etharp_output;
	netif->linkoutput = lpc_low_level_output;

    /* CMSIS-RTOS, start tasks */
#if NO_SYS == 0
#ifdef CMSIS_OS_RTX
    memset(lpc_enetdata.xTXDCountSem.data, 0, sizeof(lpc_enetdata.xTXDCountSem.data));
    lpc_enetdata.xTXDCountSem.def.semaphore = lpc_enetdata.xTXDCountSem.data;
#endif
    lpc_enetdata.xTXDCountSem.id = osSemaphoreCreate(&lpc_enetdata.xTXDCountSem.def, LPC_NUM_BUFF_TXDESCS);
	LWIP_ASSERT("xTXDCountSem creation error", (lpc_enetdata.xTXDCountSem.id != NULL));

	err = sys_mutex_new(&lpc_enetdata.TXLockMutex);
	LWIP_ASSERT("TXLockMutex creation error", (err == ERR_OK));

	/* Packet receive task */
	lpc_enetdata.RxThread = sys_thread_new("receive_thread", packet_rx, netif->state, DEFAULT_THREAD_STACKSIZE, RX_PRIORITY);
	LWIP_ASSERT("RxThread creation error", (lpc_enetdata.RxThread));

	/* Transmit cleanup task */
	err = sys_sem_new(&lpc_enetdata.TxCleanSem, 0);
	LWIP_ASSERT("TxCleanSem creation error", (err == ERR_OK));
	sys_thread_new("txclean_thread", packet_tx, netif->state, DEFAULT_THREAD_STACKSIZE, TX_PRIORITY);

	/* periodic PHY status update */
	osTimerId phy_timer = osTimerCreate(osTimer(phy_update), osTimerPeriodic, (void *)netif);
	osTimerStart(phy_timer, 250);
#endif

    return ERR_OK;
}

void eth_arch_enable_interrupts(void) {
    NVIC_SetPriority(ENET_IRQn, ((0x01 << 3) | 0x01));
    NVIC_EnableIRQ(ENET_IRQn);
}

void eth_arch_disable_interrupts(void) {
    NVIC_DisableIRQ(ENET_IRQn);
}

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
