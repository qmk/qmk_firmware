#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/tcpip.h"
#include "netif/etharp.h"
#include "netif/ppp_oe.h"

#include "eth_arch.h"
#include "sys_arch.h"

#include "fsl_enet_driver.h"
#include "fsl_enet_hal.h"
#include "fsl_device_registers.h"
#include "fsl_phy_driver.h"
#include "fsl_interrupt_manager.h"
#include "k64f_emac_config.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mbed_interface.h"

extern IRQn_Type enet_irq_ids[HW_ENET_INSTANCE_COUNT][FSL_FEATURE_ENET_INTERRUPT_COUNT];
extern uint8_t enetIntMap[kEnetIntNum];
extern void *enetIfHandle;

/********************************************************************************
 * Internal data
 ********************************************************************************/

extern void k64f_init_eth_hardware(void);

/* K64F EMAC driver data structure */
struct k64f_enetdata {
  struct netif *netif;  /**< Reference back to LWIP parent netif */
  sys_sem_t RxReadySem; /**< RX packet ready semaphore */
  sys_sem_t TxCleanSem; /**< TX cleanup thread wakeup semaphore */
  sys_mutex_t TXLockMutex; /**< TX critical section mutex */
  sys_sem_t xTXDCountSem; /**< TX free buffer counting semaphore */
  volatile u32_t rx_free_descs; /**< Count of free RX descriptors */
  struct pbuf *rxb[ENET_RX_RING_LEN]; /**< RX pbuf pointer list, zero-copy mode */
  uint8_t *rx_desc_start_addr; /**< RX descriptor start address */
  uint8_t *tx_desc_start_addr; /**< TX descriptor start address */
  uint8_t tx_consume_index, tx_produce_index; /**< TX buffers ring */
  uint8_t rx_fill_index; /**< RX ring fill index */
  struct pbuf *txb[ENET_TX_RING_LEN]; /**< TX pbuf pointer list, zero-copy mode */
  void *txb_aligned[ENET_TX_RING_LEN]; /**< TX aligned buffers (if needed) */
};

static struct k64f_enetdata k64f_enetdata;

static enet_dev_if_t enetDevIf[HW_ENET_INSTANCE_COUNT];
static enet_mac_config_t g_enetMacCfg[HW_ENET_INSTANCE_COUNT] = 
{
  {
    ENET_ETH_MAX_FLEN ,  /*!< enet receive buffer size*/
    ENET_RX_LARGE_BUFFER_NUM, /*!< enet large receive buffer number*/
    ENET_RX_RING_LEN,        /*!< enet receive bd number*/
    ENET_TX_RING_LEN,        /*!< enet transmit bd number*/
    {0},                /*!< enet mac address*/
    kEnetCfgRmii,       /*!< enet rmii interface*/
    kEnetCfgSpeed100M,  /*!< enet rmii 100M*/
    kEnetCfgFullDuplex, /*!< enet rmii Full- duplex*/
     /*!< enet mac control flag recommended to use enet_mac_control_flag_t
      we send frame with crc so receive crc forward for data length check test*/
    kEnetRxCrcFwdEnable | kEnetRxFlowControlEnable,
    true,         /*!< enet txaccelerator enabled*/
    true,        /*!< enet rxaccelerator enabled*/
    false,        /*!< enet store and forward*/
    {false, false, true, false, true},  /*!< enet rxaccelerator config*/
    {false, false, true},          /*!< enet txaccelerator config*/
    true,               /*!< vlan frame support*/
    true,               /*!< phy auto discover*/
    ENET_MII_CLOCK,     /*!< enet MDC clock*/
  },
};

static enet_phy_config_t g_enetPhyCfg[HW_ENET_INSTANCE_COUNT] =
{
  {0, false}
};

/** \brief  Driver transmit and receive thread priorities
 *
 * Thread priorities for receive thread and TX cleanup thread. Alter
 * to prioritize receive or transmit bandwidth. In a heavily loaded
 * system or with LEIP_DEBUG enabled, the priorities might be better
 * the same. */
#define RX_PRIORITY   (osPriorityNormal)
#define TX_PRIORITY   (osPriorityNormal)
#define PHY_PRIORITY  (osPriorityNormal)

/** \brief  Debug output formatter lock define
 *
 * When using FreeRTOS and with LWIP_DEBUG enabled, enabling this
 * define will allow RX debug messages to not interleave with the
 * TX messages (so they are actually readable). Not enabling this
 * define when the system is under load will cause the output to
 * be unreadable. There is a small tradeoff in performance for this
 * so use it only for debug. */
//#define LOCK_RX_THREAD

/** \brief  Signal used for ethernet ISR to signal packet_rx() thread.
 */
#define RX_SIGNAL  1

// K64F-specific macros
#define RX_PBUF_AUTO_INDEX    (-1)

/********************************************************************************
 * Buffer management
 ********************************************************************************/

/** \brief  Queues a pbuf into the RX descriptor list
 *
 *  \param[in] k64f_enet Pointer to the drvier data structure
 *  \param[in] p         Pointer to pbuf to queue
 *  \param[in] bidx      Index to queue into   
 */
static void k64f_rxqueue_pbuf(struct k64f_enetdata *k64f_enet, struct pbuf *p, int bidx)
{
  enet_bd_struct_t *start = (enet_bd_struct_t *)k64f_enet->rx_desc_start_addr;
  int idx;

  /* Get next free descriptor index */
  if (bidx == RX_PBUF_AUTO_INDEX)
    idx = k64f_enet->rx_fill_index;
  else
    idx = bidx;

  /* Setup descriptor and clear statuses */
  enet_hal_init_rxbds(start + idx, (uint8_t*)p->payload, idx == ENET_RX_RING_LEN - 1);

  /* Save pbuf pointer for push to network layer later */
  k64f_enet->rxb[idx] = p;

  /* Wrap at end of descriptor list */
  idx = (idx + 1) % ENET_RX_RING_LEN;

  /* Queue descriptor(s) */
  k64f_enet->rx_free_descs -= 1;

  if (bidx == RX_PBUF_AUTO_INDEX)
    k64f_enet->rx_fill_index = idx;

  enet_hal_active_rxbd(BOARD_DEBUG_ENET_INSTANCE_ADDR);

  LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
    ("k64f_rxqueue_pbuf: pbuf packet queued: %p (free desc=%d)\n", p,
      k64f_enet->rx_free_descs));
}

/** \brief  Attempt to allocate and requeue a new pbuf for RX
 *
 *  \param[in]     netif Pointer to the netif structure
 *  \returns       number of queued packets
 */
s32_t k64f_rx_queue(struct netif *netif, int idx)
{
  struct k64f_enetdata *k64f_enet = netif->state;
  enet_dev_if_t *enetIfPtr = (enet_dev_if_t *)&enetDevIf[BOARD_DEBUG_ENET_INSTANCE];
  struct pbuf *p;
  int queued = 0;

  /* Attempt to requeue as many packets as possible */
  while (k64f_enet->rx_free_descs > 0) {
    /* Allocate a pbuf from the pool. We need to allocate at the
       maximum size as we don't know the size of the yet to be
       received packet. */
    p = pbuf_alloc(PBUF_RAW, enetIfPtr->macCfgPtr->rxBufferSize + RX_BUF_ALIGNMENT, PBUF_RAM);
    if (p == NULL) {
      LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
        ("k64_rx_queue: could not allocate RX pbuf (free desc=%d)\n",
        k64f_enet->rx_free_descs));
      return queued;
    }
    /* K64F note: the next line ensures that the RX buffer is properly aligned for the K64F
       RX descriptors (16 bytes alignment). However, by doing so, we're effectively changing
       a data structure which is internal to lwIP. This might not prove to be a good idea
       in the long run, but a better fix would probably involve modifying lwIP itself */
    p->payload = (void*)ENET_ALIGN((uint32_t)p->payload, RX_BUF_ALIGNMENT);
    
    /* pbufs allocated from the RAM pool should be non-chained. */
    LWIP_ASSERT("k64f_rx_queue: pbuf is not contiguous (chained)", pbuf_clen(p) <= 1);

    /* Queue packet */
    k64f_rxqueue_pbuf(k64f_enet, p, idx);
    queued++;
  }

  return queued;
}

/** \brief  Sets up the RX descriptor ring buffers.
 *
 *  This function sets up the descriptor list used for receive packets.
 *
 *  \param[in]  netif  Pointer to driver data structure
 *  \returns           ERR_MEM if out of memory, ERR_OK otherwise
 */
static err_t k64f_rx_setup(struct netif *netif, enet_rxbd_config_t *rxbdCfg) {   
  struct k64f_enetdata *k64f_enet = netif->state;
  enet_dev_if_t *enetIfPtr = (enet_dev_if_t *)&enetDevIf[BOARD_DEBUG_ENET_INSTANCE];
  uint8_t *rxBdPtr;
  uint32_t rxBufferSizeAligned;

  // Allocate RX descriptors
  rxBdPtr = (uint8_t *)calloc(1, enet_hal_get_bd_size() * enetIfPtr->macCfgPtr->rxBdNumber + ENET_BD_ALIGNMENT);
  if(!rxBdPtr)
      return ERR_MEM;
  k64f_enet->rx_desc_start_addr = (uint8_t *)ENET_ALIGN((uint32_t)rxBdPtr, ENET_BD_ALIGNMENT);
  k64f_enet->rx_free_descs = enetIfPtr->macCfgPtr->rxBdNumber;
  k64f_enet->rx_fill_index = 0;

  rxBufferSizeAligned = ENET_ALIGN(enetIfPtr->macCfgPtr->rxBufferSize, ENET_RX_BUFFER_ALIGNMENT);
  enetIfPtr->macContextPtr->rxBufferSizeAligned = rxBufferSizeAligned;
  rxbdCfg->rxBdPtrAlign = k64f_enet->rx_desc_start_addr;
  rxbdCfg->rxBdNum = enetIfPtr->macCfgPtr->rxBdNumber;
  rxbdCfg->rxBufferNum = enetIfPtr->macCfgPtr->rxBdNumber;
  
  k64f_rx_queue(netif, RX_PBUF_AUTO_INDEX);
  return ERR_OK;
}

/** \brief  Sets up the TX descriptor ring buffers.
 *
 *  This function sets up the descriptor list used for transmit packets.
 *
 *  \param[in]      netif  Pointer to driver data structure
 *  \returns               ERR_MEM if out of memory, ERR_OK otherwise
 */
static err_t k64f_tx_setup(struct netif *netif, enet_txbd_config_t *txbdCfg) {
  struct k64f_enetdata *k64f_enet = netif->state;
  enet_dev_if_t *enetIfPtr = (enet_dev_if_t *)&enetDevIf[BOARD_DEBUG_ENET_INSTANCE];
  uint8_t *txBdPtr;

  // Allocate TX descriptors
  txBdPtr = (uint8_t *)calloc(1, enet_hal_get_bd_size() * enetIfPtr->macCfgPtr->txBdNumber + ENET_BD_ALIGNMENT);
  if(!txBdPtr)
    return ERR_MEM;

  k64f_enet->tx_desc_start_addr = (uint8_t *)ENET_ALIGN((uint32_t)txBdPtr, ENET_BD_ALIGNMENT);
  k64f_enet->tx_consume_index = k64f_enet->tx_produce_index = 0;

  txbdCfg->txBdPtrAlign = k64f_enet->tx_desc_start_addr;
  txbdCfg->txBufferNum = enetIfPtr->macCfgPtr->txBdNumber;
  txbdCfg->txBufferSizeAlign = ENET_ALIGN(enetIfPtr->maxFrameSize, ENET_TX_BUFFER_ALIGNMENT);

  // Make the TX descriptor ring circular
  enet_hal_init_txbds(k64f_enet->tx_desc_start_addr + enet_hal_get_bd_size() * (ENET_TX_RING_LEN - 1), 1);

  return ERR_OK;
}

/** \brief  Free TX buffers that are complete
 *
 *  \param[in] k64f_enet  Pointer to driver data structure
 */
static void k64f_tx_reclaim(struct k64f_enetdata *k64f_enet)
{
  uint8_t i;
  volatile enet_bd_struct_t * bdPtr = (enet_bd_struct_t *)k64f_enet->tx_desc_start_addr;

  /* Get exclusive access */
  sys_mutex_lock(&k64f_enet->TXLockMutex);

  // Traverse all descriptors, looking for the ones modified by the uDMA
  i = k64f_enet->tx_consume_index;
  while(i != k64f_enet->tx_produce_index && !(bdPtr[i].control & kEnetTxBdReady)) {
      if (k64f_enet->txb_aligned[i]) {
        free(k64f_enet->txb_aligned[i]);
        k64f_enet->txb_aligned[i] = NULL;
      } else if (k64f_enet->txb[i]) {
        pbuf_free(k64f_enet->txb[i]);
        k64f_enet->txb[i] = NULL;
      }
      osSemaphoreRelease(k64f_enet->xTXDCountSem.id);
      bdPtr[i].controlExtend2 &= ~TX_DESC_UPDATED_MASK;
      i = (i + 1) % ENET_TX_RING_LEN;
  }
  k64f_enet->tx_consume_index = i;

  /* Restore access */
  sys_mutex_unlock(&k64f_enet->TXLockMutex);
}

/** \brief  Low level init of the MAC and PHY.
 *
 *  \param[in]      netif  Pointer to LWIP netif structure
 */
static err_t low_level_init(struct netif *netif)
{
  enet_dev_if_t * enetIfPtr;
  uint32_t device = BOARD_DEBUG_ENET_INSTANCE_ADDR;
  enet_rxbd_config_t rxbdCfg;
  enet_txbd_config_t txbdCfg;
  enet_phy_speed_t phy_speed;
  enet_phy_duplex_t phy_duplex;

  k64f_init_eth_hardware();
  
  /* Initialize device*/
  enetIfPtr = (enet_dev_if_t *)&enetDevIf[BOARD_DEBUG_ENET_INSTANCE];
  enetIfPtr->deviceNumber = device;
  enetIfPtr->macCfgPtr = &g_enetMacCfg[BOARD_DEBUG_ENET_INSTANCE];
  enetIfPtr->phyCfgPtr = &g_enetPhyCfg[BOARD_DEBUG_ENET_INSTANCE];
  enetIfPtr->macApiPtr = &g_enetMacApi;
  enetIfPtr->phyApiPtr = (void *)&g_enetPhyApi;
  memcpy(enetIfPtr->macCfgPtr->macAddr, (char*)netif->hwaddr, kEnetMacAddrLen);

  /* Allocate buffer for ENET mac context*/
  enetIfPtr->macContextPtr = (enet_mac_context_t *)calloc(1, sizeof(enet_mac_context_t));
  if (!enetIfPtr->macContextPtr) {
    return ERR_BUF;
  }

  /* Initialize enet buffers*/
  if(k64f_rx_setup(netif, &rxbdCfg) != ERR_OK) {
    return ERR_BUF;
  }
  /* Initialize enet buffers*/
  if(k64f_tx_setup(netif, &txbdCfg) != ERR_OK) {
    return ERR_BUF;
  }
  /* Initialize enet module*/
  if (enet_mac_init(enetIfPtr, &rxbdCfg, &txbdCfg) == kStatus_ENET_Success)
  {
    /* Initialize PHY*/
    if (enetIfPtr->macCfgPtr->isPhyAutoDiscover) {
      if (((enet_phy_api_t *)(enetIfPtr->phyApiPtr))->phy_auto_discover(enetIfPtr) != kStatus_PHY_Success)
        return ERR_IF;
    }
    if (((enet_phy_api_t *)(enetIfPtr->phyApiPtr))->phy_init(enetIfPtr) != kStatus_PHY_Success)
      return ERR_IF;

    enetIfPtr->isInitialized = true;
  }
  else
  {
    // TODOETH: cleanup memory
    return ERR_IF;
  }

  /* Get link information from PHY */
  phy_get_link_speed(enetIfPtr, &phy_speed);
  phy_get_link_duplex(enetIfPtr, &phy_duplex);
  BW_ENET_RCR_RMII_10T(enetIfPtr->deviceNumber, phy_speed == kEnetSpeed10M ? kEnetCfgSpeed10M : kEnetCfgSpeed100M);
  BW_ENET_TCR_FDEN(enetIfPtr->deviceNumber, phy_duplex == kEnetFullDuplex ? kEnetCfgFullDuplex : kEnetCfgHalfDuplex);

  /* Enable Ethernet module*/
  enet_hal_config_ethernet(BOARD_DEBUG_ENET_INSTANCE_ADDR, true, true);

  /* Active Receive buffer descriptor must be done after module enable*/
  enet_hal_active_rxbd(enetIfPtr->deviceNumber);

  return ERR_OK;
}

/********************************************************************************
 * LWIP port
 ********************************************************************************/

/** \brief Ethernet receive interrupt handler
 *
 *  This function handles the receive interrupt of K64F.
 */
void enet_mac_rx_isr(void *enetIfPtr)
{
  /* Clear interrupt */
  enet_hal_clear_interrupt(((enet_dev_if_t *)enetIfPtr)->deviceNumber, kEnetRxFrameInterrupt);
  sys_sem_signal(&k64f_enetdata.RxReadySem);
}

void enet_mac_tx_isr(void *enetIfPtr)
{
  /*Clear interrupt*/
  enet_hal_clear_interrupt(((enet_dev_if_t *)enetIfPtr)->deviceNumber, kEnetTxFrameInterrupt);
  sys_sem_signal(&k64f_enetdata.TxCleanSem);
}

/**
 * This function is the ethernet packet send function. It calls
 * etharp_output after checking link status.
 *
 * \param[in] netif the lwip network interface structure for this enetif
 * \param[in] q Pointer to pbug to send
 * \param[in] ipaddr IP address
 * \return ERR_OK or error code
 */
err_t k64f_etharp_output(struct netif *netif, struct pbuf *q, ip_addr_t *ipaddr)
{
  /* Only send packet is link is up */
  if (netif->flags & NETIF_FLAG_LINK_UP)
    return etharp_output(netif, q, ipaddr);

  return ERR_CONN;
}

/** \brief  Allocates a pbuf and returns the data from the incoming packet.
 *
 *  \param[in] netif the lwip network interface structure
 *  \param[in] idx   index of packet to be read
 *  \return a pbuf filled with the received packet (including MAC header)
 */
static struct pbuf *k64f_low_level_input(struct netif *netif, int idx)
{
  struct k64f_enetdata *k64f_enet = netif->state;
  enet_bd_struct_t * bdPtr = (enet_bd_struct_t*)k64f_enet->rx_desc_start_addr;
  struct pbuf *p = NULL;
  u32_t length = 0, orig_length;
  const u16_t err_mask = kEnetRxBdTrunc | kEnetRxBdCrc | kEnetRxBdNoOctet | kEnetRxBdLengthViolation;

#ifdef LOCK_RX_THREAD
  /* Get exclusive access */
  sys_mutex_lock(&k64f_enet->TXLockMutex);
#endif

  /* Determine if a frame has been received */
  if ((bdPtr[idx].control & err_mask) != 0) {
#if LINK_STATS
    if ((bdPtr[idx].control & kEnetRxBdLengthViolation) != 0)
      LINK_STATS_INC(link.lenerr);
    else
      LINK_STATS_INC(link.chkerr);
#endif
    LINK_STATS_INC(link.drop);

    /* Re-queue the same buffer */
    k64f_enet->rx_free_descs++;
    p = k64f_enet->rxb[idx];
    k64f_enet->rxb[idx] = NULL;
    k64f_rxqueue_pbuf(k64f_enet, p, idx);
    p = NULL;
  } else {
    /* A packet is waiting, get length */
    length = enet_hal_get_bd_length(bdPtr + idx);

    /* Zero-copy */
    p = k64f_enet->rxb[idx];
    orig_length = p->len;
    p->len = (u16_t) length;

    /* Free pbuf from descriptor */
    k64f_enet->rxb[idx] = NULL;
    k64f_enet->rx_free_descs++;
    
    /* Attempt to queue new buffer */
    if (k64f_rx_queue(netif, idx) == 0) {
      /* Drop frame (out of memory) */
      LINK_STATS_INC(link.drop);

      /* Re-queue the same buffer */
      p->len = orig_length;
      k64f_rxqueue_pbuf(k64f_enet, p, idx);

      LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
        ("k64f_low_level_input: Packet index %d dropped for OOM\n",
        idx));
#ifdef LOCK_RX_THREAD
      sys_mutex_unlock(&k64f_enet->TXLockMutex);
#endif

      return NULL;
    }

    LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
      ("k64f_low_level_input: Packet received: %p, size %d (index=%d)\n",
      p, length, idx));

    /* Save size */
    p->tot_len = (u16_t) length;
    LINK_STATS_INC(link.recv);
  }

#ifdef LOCK_RX_THREAD
  sys_mutex_unlock(&k64f_enet->TXLockMutex);
#endif

  return p;
}

/** \brief  Attempt to read a packet from the EMAC interface.
 *
 *  \param[in] netif the lwip network interface structure
 *  \param[in] idx   index of packet to be read
 */
void k64f_enetif_input(struct netif *netif, int idx)
{
  struct eth_hdr *ethhdr;
  struct pbuf *p;

  /* move received packet into a new pbuf */
  p = k64f_low_level_input(netif, idx);
  if (p == NULL)
    return;

  /* points to packet payload, which starts with an Ethernet header */
  ethhdr = (struct eth_hdr*)p->payload;

  switch (htons(ethhdr->type)) {
    case ETHTYPE_IP:
    case ETHTYPE_ARP:
#if PPPOE_SUPPORT
    case ETHTYPE_PPPOEDISC:
    case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
      /* full packet send to tcpip_thread to process */
      if (netif->input(p, netif) != ERR_OK) {
        LWIP_DEBUGF(NETIF_DEBUG, ("k64f_enetif_input: IP input error\n"));
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

/** \brief  Packet reception task
 *
 * This task is called when a packet is received. It will
 * pass the packet to the LWIP core.
 *
 *  \param[in] pvParameters pointer to the interface data
 */
static void packet_rx(void* pvParameters) {
  struct k64f_enetdata *k64f_enet = pvParameters;
  volatile enet_bd_struct_t * bdPtr = (enet_bd_struct_t*)k64f_enet->rx_desc_start_addr;
  int idx = 0;

  while (1) {
    /* Wait for receive task to wakeup */
    sys_arch_sem_wait(&k64f_enet->RxReadySem, 0);

    if ((bdPtr[idx].control & kEnetRxBdEmpty) == 0) {
      k64f_enetif_input(k64f_enet->netif, idx);
      idx = (idx + 1) % ENET_RX_RING_LEN;
    }
  }
}

/** \brief  Transmit cleanup task
 *
 * This task is called when a transmit interrupt occurs and
 * reclaims the pbuf and descriptor used for the packet once
 * the packet has been transferred.
 *
 *  \param[in] pvParameters pointer to the interface data
 */
static void packet_tx(void* pvParameters) {
  struct k64f_enetdata *k64f_enet = pvParameters;

  while (1) {
    /* Wait for transmit cleanup task to wakeup */
    sys_arch_sem_wait(&k64f_enet->TxCleanSem, 0);
    // TODOETH: handle TX underrun?
    k64f_tx_reclaim(k64f_enet);
  }
}

 /** \brief  Polls if an available TX descriptor is ready. Can be used to
 *           determine if the low level transmit function will block.
 *
 *  \param[in] netif the lwip network interface structure
 *  \return 0 if no descriptors are read, or >0
 */
s32_t k64f_tx_ready(struct netif *netif)
{
  struct k64f_enetdata *k64f_enet = netif->state;
  s32_t fb;
  u32_t idx, cidx;

  cidx = k64f_enet->tx_consume_index;
  idx = k64f_enet->tx_produce_index;

  /* Determine number of free buffers */
  if (idx == cidx)
    fb = ENET_TX_RING_LEN;
  else if (cidx > idx)
    fb = (ENET_TX_RING_LEN - 1) -
      ((idx + ENET_TX_RING_LEN) - cidx);
  else
    fb = (ENET_TX_RING_LEN - 1) - (cidx - idx);

  return fb;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_hal_update_txbds
 * Description: Update ENET transmit buffer descriptors.
 *END*********************************************************************/
void k64f_update_txbds(struct k64f_enetdata *k64f_enet, int idx, uint8_t *buffer, uint16_t length, bool isLast)
{
  volatile enet_bd_struct_t * bdPtr = (enet_bd_struct_t *)(k64f_enet->tx_desc_start_addr + idx * enet_hal_get_bd_size());
    
  bdPtr->length = HTONS(length); /* Set data length*/
  bdPtr->buffer = (uint8_t *)HTONL((uint32_t)buffer); /* Set data buffer*/
  if (isLast)
    bdPtr->control |= kEnetTxBdLast;
  else
    bdPtr->control &= ~kEnetTxBdLast;
  bdPtr->controlExtend1 |= kEnetTxBdTxInterrupt;
  bdPtr->controlExtend2 &= ~TX_DESC_UPDATED_MASK; // descriptor not updated by DMA
  bdPtr->control |= kEnetTxBdTransmitCrc | kEnetTxBdReady;
}

/** \brief  Low level output of a packet. Never call this from an
 *          interrupt context, as it may block until TX descriptors
 *          become available.
 *
 *  \param[in] netif the lwip network interface structure for this netif
 *  \param[in] p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 *  \return ERR_OK if the packet could be sent or an err_t value if the packet couldn't be sent
 */
static err_t k64f_low_level_output(struct netif *netif, struct pbuf *p)
{
  struct k64f_enetdata *k64f_enet = netif->state;
  struct pbuf *q;
  u32_t idx;
  s32_t dn;
  uint8_t *psend = NULL, *dst;

  /* Get free TX buffer index */
  idx = k64f_enet->tx_produce_index;
  
  /* Check the pbuf chain for payloads that are not 8-byte aligned.
     If found, a new properly aligned buffer needs to be allocated
     and the data copied there */
  for (q = p; q != NULL; q = q->next)
    if (((u32_t)q->payload & (TX_BUF_ALIGNMENT - 1)) != 0)
      break;
  if (q != NULL) {
    // Allocate properly aligned buffer
    psend = (uint8_t*)malloc(p->tot_len);
    if (NULL == psend)
      return ERR_MEM;   
    LWIP_ASSERT("k64f_low_level_output: buffer not properly aligned", ((u32_t)psend & (TX_BUF_ALIGNMENT - 1)) == 0);
    for (q = p, dst = psend; q != NULL; q = q->next) {
      MEMCPY(dst, q->payload, q->len);
      dst += q->len;
    }
    k64f_enet->txb_aligned[idx] = psend;
    dn = 1;
  } else {
    k64f_enet->txb_aligned[idx] = NULL;
    dn = (s32_t) pbuf_clen(p);
    pbuf_ref(p);
  }

  /* Wait until enough descriptors are available for the transfer. */
  /* THIS WILL BLOCK UNTIL THERE ARE ENOUGH DESCRIPTORS AVAILABLE */
  while (dn > k64f_tx_ready(netif))
    osSemaphoreWait(k64f_enet->xTXDCountSem.id, osWaitForever);

  /* Get exclusive access */
  sys_mutex_lock(&k64f_enet->TXLockMutex);

  /* Setup transfers */
  q = p;
  while (dn > 0) {
    dn--;
    if (psend != NULL) {
      k64f_update_txbds(k64f_enet, idx, psend, p->tot_len, 1);
      k64f_enet->txb[idx] = NULL;
      
      LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
      ("k64f_low_level_output: aligned packet(%p) sent"
      " size = %d (index=%d)\n", psend, p->tot_len, idx));      
    } else {
      LWIP_ASSERT("k64f_low_level_output: buffer not properly aligned", ((u32_t)q->payload & 0x07) == 0);

      /* Only save pointer to free on last descriptor */
      if (dn == 0) {
        /* Save size of packet and signal it's ready */
        k64f_update_txbds(k64f_enet, idx, q->payload, q->len, 1);
        k64f_enet->txb[idx] = p;
      }
      else {
        /* Save size of packet, descriptor is not last */
        k64f_update_txbds(k64f_enet, idx, q->payload, q->len, 0);
        k64f_enet->txb[idx] = NULL;
      }
      
      LWIP_DEBUGF(UDP_LPC_EMAC | LWIP_DBG_TRACE,
      ("k64f_low_level_output: pbuf packet(%p) sent, chain#=%d,"
      " size = %d (index=%d)\n", q->payload, dn, q->len, idx));
    }

    q = q->next;

    idx = (idx + 1) % ENET_TX_RING_LEN;
  }

  k64f_enet->tx_produce_index = idx;
  enet_hal_active_txbd(BOARD_DEBUG_ENET_INSTANCE_ADDR);
  LINK_STATS_INC(link.xmit);

  /* Restore access */
  sys_mutex_unlock(&k64f_enet->TXLockMutex);

  return ERR_OK;
}

/*******************************************************************************
 * PHY task: monitor link
*******************************************************************************/

#define PHY_TASK_PERIOD_MS      200
#define STATE_UNKNOWN           (-1)

typedef struct {
    int connected;
    enet_phy_speed_t speed;
    enet_phy_duplex_t duplex;
} PHY_STATE;

int phy_link_status() {
    bool connection_status;
    enet_dev_if_t * enetIfPtr = (enet_dev_if_t*)&enetDevIf[BOARD_DEBUG_ENET_INSTANCE];
    phy_get_link_status(enetIfPtr, &connection_status);
    return (int)connection_status;
}

static void k64f_phy_task(void *data) {
  struct netif *netif = (struct netif*)data;
  bool connection_status;
  enet_dev_if_t * enetIfPtr = (enet_dev_if_t*)&enetDevIf[BOARD_DEBUG_ENET_INSTANCE];
  PHY_STATE crt_state = {STATE_UNKNOWN, (enet_phy_speed_t)STATE_UNKNOWN, (enet_phy_duplex_t)STATE_UNKNOWN};
  PHY_STATE prev_state;

  prev_state = crt_state;
  while (true) {
    // Get current status
    phy_get_link_status(enetIfPtr, &connection_status);
    crt_state.connected = connection_status ? 1 : 0;
    phy_get_link_speed(enetIfPtr, &crt_state.speed);
    phy_get_link_duplex(enetIfPtr, &crt_state.duplex);

    // Compare with previous state
    if (crt_state.connected != prev_state.connected) {
      if (crt_state.connected)
        tcpip_callback_with_block((tcpip_callback_fn)netif_set_link_up, (void*) netif, 1);
      else
        tcpip_callback_with_block((tcpip_callback_fn)netif_set_link_down, (void*) netif, 1);
    }

    if (crt_state.speed != prev_state.speed)
      BW_ENET_RCR_RMII_10T(enetIfPtr->deviceNumber, crt_state.speed == kEnetSpeed10M ? kEnetCfgSpeed10M : kEnetCfgSpeed100M);

    // TODO: duplex change requires disable/enable of Ethernet interface, to be implemented

    prev_state = crt_state;
    osDelay(PHY_TASK_PERIOD_MS);
  }
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param[in] netif the lwip network interface structure for this netif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t eth_arch_enetif_init(struct netif *netif)
{
  err_t err;

  LWIP_ASSERT("netif != NULL", (netif != NULL));

  k64f_enetdata.netif = netif;

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
  // TODOETH: check if the flags are correct below
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET | NETIF_FLAG_IGMP;

  /* Initialize the hardware */
  netif->state = &k64f_enetdata;
  err = low_level_init(netif);
  if (err != ERR_OK)
    return err;

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwipk64f";
#endif /* LWIP_NETIF_HOSTNAME */

  netif->name[0] = 'e';
  netif->name[1] = 'n';

  netif->output = k64f_etharp_output;
  netif->linkoutput = k64f_low_level_output;

  /* CMSIS-RTOS, start tasks */
#ifdef CMSIS_OS_RTX
  memset(k64f_enetdata.xTXDCountSem.data, 0, sizeof(k64f_enetdata.xTXDCountSem.data));
  k64f_enetdata.xTXDCountSem.def.semaphore = k64f_enetdata.xTXDCountSem.data;
#endif
  k64f_enetdata.xTXDCountSem.id = osSemaphoreCreate(&k64f_enetdata.xTXDCountSem.def, ENET_TX_RING_LEN);

  LWIP_ASSERT("xTXDCountSem creation error", (k64f_enetdata.xTXDCountSem.id != NULL));

  err = sys_mutex_new(&k64f_enetdata.TXLockMutex);
  LWIP_ASSERT("TXLockMutex creation error", (err == ERR_OK));

  /* Packet receive task */
  err = sys_sem_new(&k64f_enetdata.RxReadySem, 0);
  LWIP_ASSERT("RxReadySem creation error", (err == ERR_OK));
  sys_thread_new("receive_thread", packet_rx, netif->state, DEFAULT_THREAD_STACKSIZE, RX_PRIORITY);

  /* Transmit cleanup task */
  err = sys_sem_new(&k64f_enetdata.TxCleanSem, 0);
  LWIP_ASSERT("TxCleanSem creation error", (err == ERR_OK));
  sys_thread_new("txclean_thread", packet_tx, netif->state, DEFAULT_THREAD_STACKSIZE, TX_PRIORITY);

  /* PHY monitoring task */
  sys_thread_new("phy_thread", k64f_phy_task, netif, DEFAULT_THREAD_STACKSIZE, PHY_PRIORITY);

  /* Allow the PHY task to detect the initial link state and set up the proper flags */
  osDelay(10);

  return ERR_OK;
}

void eth_arch_enable_interrupts(void) {
  enet_hal_config_interrupt(BOARD_DEBUG_ENET_INSTANCE_ADDR, (kEnetTxFrameInterrupt | kEnetRxFrameInterrupt), true);
  INT_SYS_EnableIRQ(enet_irq_ids[BOARD_DEBUG_ENET_INSTANCE][enetIntMap[kEnetRxfInt]]);
  INT_SYS_EnableIRQ(enet_irq_ids[BOARD_DEBUG_ENET_INSTANCE][enetIntMap[kEnetTxfInt]]);
}

void eth_arch_disable_interrupts(void) {
  INT_SYS_DisableIRQ(enet_irq_ids[BOARD_DEBUG_ENET_INSTANCE][enetIntMap[kEnetRxfInt]]);
  INT_SYS_DisableIRQ(enet_irq_ids[BOARD_DEBUG_ENET_INSTANCE][enetIntMap[kEnetTxfInt]]);
}

void ENET_Transmit_IRQHandler(void)
{
     enet_mac_tx_isr(enetIfHandle);
}

void ENET_Receive_IRQHandler(void)
{
     enet_mac_rx_isr(enetIfHandle);
}

#if FSL_FEATURE_ENET_SUPPORT_PTP
void ENET_1588_Timer_IRQHandler(void)
{
     enet_mac_ts_isr(enetIfHandle);
}
#endif
/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

