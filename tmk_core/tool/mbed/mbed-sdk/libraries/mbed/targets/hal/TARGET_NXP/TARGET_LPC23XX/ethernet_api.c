/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <string.h>

#include "ethernet_api.h"
#include "cmsis.h"
#include "mbed_interface.h"
#include "toolchain.h"
#include "mbed_error.h"

#define NEW_LOGIC       0
#define NEW_ETH_BUFFER  0

#if NEW_ETH_BUFFER

#define NUM_RX_FRAG         4           // Number of Rx Fragments (== packets)
#define NUM_TX_FRAG         3           // Number of Tx Fragments (== packets)

#define ETH_MAX_FLEN        1536         // Maximum Ethernet Frame Size
#define ETH_FRAG_SIZE       ETH_MAX_FLEN // Packet Fragment size (same as packet length)

#else

// Memfree calculation:
// (16 * 1024) - ((2 * 4 * NUM_RX) + (2 * 4 * NUM_RX) + (0x300 * NUM_RX) +
//                (2 * 4 * NUM_TX) + (1 * 4 * NUM_TX) + (0x300 * NUM_TX)) = 8556
/* EMAC Memory Buffer configuration for 16K Ethernet RAM. */
#define NUM_RX_FRAG         4           /* Num.of RX Fragments 4*1536= 6.0kB */
#define NUM_TX_FRAG         3           /* Num.of TX Fragments 3*1536= 4.6kB */
//#define ETH_FRAG_SIZE       1536        /* Packet Fragment size 1536 Bytes   */

//#define ETH_MAX_FLEN        1536        /* Max. Ethernet Frame Size          */
#define ETH_FRAG_SIZE       0x300       /* Packet Fragment size 1536/2 Bytes   */
#define ETH_MAX_FLEN        0x300       /* Max. Ethernet Frame Size          */

const int ethernet_MTU_SIZE  = 0x300;

#endif

#define ETHERNET_ADDR_SIZE 6

PACKED struct RX_DESC_TypeDef {                        /* RX Descriptor struct              */
   unsigned int Packet;
   unsigned int Ctrl;
};
typedef struct RX_DESC_TypeDef RX_DESC_TypeDef;

PACKED struct RX_STAT_TypeDef {                        /* RX Status struct                  */
   unsigned int Info;
   unsigned int HashCRC;
};
typedef struct RX_STAT_TypeDef RX_STAT_TypeDef;

PACKED struct TX_DESC_TypeDef {                        /* TX Descriptor struct              */
   unsigned int Packet;
   unsigned int Ctrl;
};
typedef struct TX_DESC_TypeDef TX_DESC_TypeDef;

PACKED struct TX_STAT_TypeDef {                        /* TX Status struct                  */
   unsigned int Info;
};
typedef struct TX_STAT_TypeDef TX_STAT_TypeDef;

/* MAC Configuration Register 1 */
#define MAC1_REC_EN         0x00000001  /* Receive Enable                    */
#define MAC1_PASS_ALL       0x00000002  /* Pass All Receive Frames           */
#define MAC1_RX_FLOWC       0x00000004  /* RX Flow Control                   */
#define MAC1_TX_FLOWC       0x00000008  /* TX Flow Control                   */
#define MAC1_LOOPB          0x00000010  /* Loop Back Mode                    */
#define MAC1_RES_TX         0x00000100  /* Reset TX Logic                    */
#define MAC1_RES_MCS_TX     0x00000200  /* Reset MAC TX Control Sublayer     */
#define MAC1_RES_RX         0x00000400  /* Reset RX Logic                    */
#define MAC1_RES_MCS_RX     0x00000800  /* Reset MAC RX Control Sublayer     */
#define MAC1_SIM_RES        0x00004000  /* Simulation Reset                  */
#define MAC1_SOFT_RES       0x00008000  /* Soft Reset MAC                    */

/* MAC Configuration Register 2 */
#define MAC2_FULL_DUP       0x00000001  /* Full Duplex Mode                  */
#define MAC2_FRM_LEN_CHK    0x00000002  /* Frame Length Checking             */
#define MAC2_HUGE_FRM_EN    0x00000004  /* Huge Frame Enable                 */
#define MAC2_DLY_CRC        0x00000008  /* Delayed CRC Mode                  */
#define MAC2_CRC_EN         0x00000010  /* Append CRC to every Frame         */
#define MAC2_PAD_EN         0x00000020  /* Pad all Short Frames              */
#define MAC2_VLAN_PAD_EN    0x00000040  /* VLAN Pad Enable                   */
#define MAC2_ADET_PAD_EN    0x00000080  /* Auto Detect Pad Enable            */
#define MAC2_PPREAM_ENF     0x00000100  /* Pure Preamble Enforcement         */
#define MAC2_LPREAM_ENF     0x00000200  /* Long Preamble Enforcement         */
#define MAC2_NO_BACKOFF     0x00001000  /* No Backoff Algorithm              */
#define MAC2_BACK_PRESSURE  0x00002000  /* Backoff Presurre / No Backoff     */
#define MAC2_EXCESS_DEF     0x00004000  /* Excess Defer                      */

/* Back-to-Back Inter-Packet-Gap Register */
#define IPGT_FULL_DUP       0x00000015  /* Recommended value for Full Duplex */
#define IPGT_HALF_DUP       0x00000012  /* Recommended value for Half Duplex */

/* Non Back-to-Back Inter-Packet-Gap Register */
#define IPGR_DEF            0x00000012  /* Recommended value                 */

/* Collision Window/Retry Register */
#define CLRT_DEF            0x0000370F  /* Default value                     */

/* PHY Support Register */
#define SUPP_SPEED          0x00000100  /* Reduced MII Logic Current Speed   */
//#define SUPP_RES_RMII       0x00000800  /* Reset Reduced MII Logic           */
#define SUPP_RES_RMII       0x00000000  /* Reset Reduced MII Logic           */

/* Test Register */
#define TEST_SHCUT_PQUANTA  0x00000001  /* Shortcut Pause Quanta             */
#define TEST_TST_PAUSE      0x00000002  /* Test Pause                        */
#define TEST_TST_BACKP      0x00000004  /* Test Back Pressure                */

/* MII Management Configuration Register */
#define MCFG_SCAN_INC       0x00000001  /* Scan Increment PHY Address        */
#define MCFG_SUPP_PREAM     0x00000002  /* Suppress Preamble                 */
#define MCFG_CLK_SEL        0x0000003C  /* Clock Select Mask                 */
#define MCFG_RES_MII        0x00008000  /* Reset MII Management Hardware     */

/* MII Management Command Register */
#define MCMD_READ           0x00000001  /* MII Read                          */
#define MCMD_SCAN           0x00000002  /* MII Scan continuously             */

#define MII_WR_TOUT         0x00050000  /* MII Write timeout count           */
#define MII_RD_TOUT         0x00050000  /* MII Read timeout count            */

/* MII Management Address Register */
#define MADR_REG_ADR        0x0000001F  /* MII Register Address Mask         */
#define MADR_PHY_ADR        0x00001F00  /* PHY Address Mask                  */

/* MII Management Indicators Register */
#define MIND_BUSY           0x00000001  /* MII is Busy                       */
#define MIND_SCAN           0x00000002  /* MII Scanning in Progress          */
#define MIND_NOT_VAL        0x00000004  /* MII Read Data not valid           */
#define MIND_MII_LINK_FAIL  0x00000008  /* MII Link Failed                   */

/* Command Register */
#define CR_RX_EN            0x00000001  /* Enable Receive                    */
#define CR_TX_EN            0x00000002  /* Enable Transmit                   */
#define CR_REG_RES          0x00000008  /* Reset Host Registers              */
#define CR_TX_RES           0x00000010  /* Reset Transmit Datapath           */
#define CR_RX_RES           0x00000020  /* Reset Receive Datapath            */
#define CR_PASS_RUNT_FRM    0x00000040  /* Pass Runt Frames                  */
#define CR_PASS_RX_FILT     0x00000080  /* Pass RX Filter                    */
#define CR_TX_FLOW_CTRL     0x00000100  /* TX Flow Control                   */
#define CR_RMII             0x00000200  /* Reduced MII Interface             */
#define CR_FULL_DUP         0x00000400  /* Full Duplex                       */

/* Status Register */
#define SR_RX_EN            0x00000001  /* Enable Receive                    */
#define SR_TX_EN            0x00000002  /* Enable Transmit                   */

/* Transmit Status Vector 0 Register */
#define TSV0_CRC_ERR        0x00000001  /* CRC error                         */
#define TSV0_LEN_CHKERR     0x00000002  /* Length Check Error                */
#define TSV0_LEN_OUTRNG     0x00000004  /* Length Out of Range               */
#define TSV0_DONE           0x00000008  /* Tramsmission Completed            */
#define TSV0_MCAST          0x00000010  /* Multicast Destination             */
#define TSV0_BCAST          0x00000020  /* Broadcast Destination             */
#define TSV0_PKT_DEFER      0x00000040  /* Packet Deferred                   */
#define TSV0_EXC_DEFER      0x00000080  /* Excessive Packet Deferral         */
#define TSV0_EXC_COLL       0x00000100  /* Excessive Collision               */
#define TSV0_LATE_COLL      0x00000200  /* Late Collision Occured            */
#define TSV0_GIANT          0x00000400  /* Giant Frame                       */
#define TSV0_UNDERRUN       0x00000800  /* Buffer Underrun                   */
#define TSV0_BYTES          0x0FFFF000  /* Total Bytes Transferred           */
#define TSV0_CTRL_FRAME     0x10000000  /* Control Frame                     */
#define TSV0_PAUSE          0x20000000  /* Pause Frame                       */
#define TSV0_BACK_PRESS     0x40000000  /* Backpressure Method Applied       */
#define TSV0_VLAN           0x80000000  /* VLAN Frame                        */

/* Transmit Status Vector 1 Register */
#define TSV1_BYTE_CNT       0x0000FFFF  /* Transmit Byte Count               */
#define TSV1_COLL_CNT       0x000F0000  /* Transmit Collision Count          */

/* Receive Status Vector Register */
#define RSV_BYTE_CNT        0x0000FFFF  /* Receive Byte Count                */
#define RSV_PKT_IGNORED     0x00010000  /* Packet Previously Ignored         */
#define RSV_RXDV_SEEN       0x00020000  /* RXDV Event Previously Seen        */
#define RSV_CARR_SEEN       0x00040000  /* Carrier Event Previously Seen     */
#define RSV_REC_CODEV       0x00080000  /* Receive Code Violation            */
#define RSV_CRC_ERR         0x00100000  /* CRC Error                         */
#define RSV_LEN_CHKERR      0x00200000  /* Length Check Error                */
#define RSV_LEN_OUTRNG      0x00400000  /* Length Out of Range               */
#define RSV_REC_OK          0x00800000  /* Frame Received OK                 */
#define RSV_MCAST           0x01000000  /* Multicast Frame                   */
#define RSV_BCAST           0x02000000  /* Broadcast Frame                   */
#define RSV_DRIB_NIBB       0x04000000  /* Dribble Nibble                    */
#define RSV_CTRL_FRAME      0x08000000  /* Control Frame                     */
#define RSV_PAUSE           0x10000000  /* Pause Frame                       */
#define RSV_UNSUPP_OPC      0x20000000  /* Unsupported Opcode                */
#define RSV_VLAN            0x40000000  /* VLAN Frame                        */

/* Flow Control Counter Register */
#define FCC_MIRR_CNT        0x0000FFFF  /* Mirror Counter                    */
#define FCC_PAUSE_TIM       0xFFFF0000  /* Pause Timer                       */

/* Flow Control Status Register */
#define FCS_MIRR_CNT        0x0000FFFF  /* Mirror Counter Current            */

/* Receive Filter Control Register */
#define RFC_UCAST_EN        0x00000001  /* Accept Unicast Frames Enable      */
#define RFC_BCAST_EN        0x00000002  /* Accept Broadcast Frames Enable    */
#define RFC_MCAST_EN        0x00000004  /* Accept Multicast Frames Enable    */
#define RFC_UCAST_HASH_EN   0x00000008  /* Accept Unicast Hash Filter Frames */
#define RFC_MCAST_HASH_EN   0x00000010  /* Accept Multicast Hash Filter Fram.*/
#define RFC_PERFECT_EN      0x00000020  /* Accept Perfect Match Enable       */
#define RFC_MAGP_WOL_EN     0x00001000  /* Magic Packet Filter WoL Enable    */
#define RFC_PFILT_WOL_EN    0x00002000  /* Perfect Filter WoL Enable         */

/* Receive Filter WoL Status/Clear Registers */
#define WOL_UCAST           0x00000001  /* Unicast Frame caused WoL          */
#define WOL_BCAST           0x00000002  /* Broadcast Frame caused WoL        */
#define WOL_MCAST           0x00000004  /* Multicast Frame caused WoL        */
#define WOL_UCAST_HASH      0x00000008  /* Unicast Hash Filter Frame WoL     */
#define WOL_MCAST_HASH      0x00000010  /* Multicast Hash Filter Frame WoL   */
#define WOL_PERFECT         0x00000020  /* Perfect Filter WoL                */
#define WOL_RX_FILTER       0x00000080  /* RX Filter caused WoL              */
#define WOL_MAG_PACKET      0x00000100  /* Magic Packet Filter caused WoL    */

/* Interrupt Status/Enable/Clear/Set Registers */
#define INT_RX_OVERRUN      0x00000001  /* Overrun Error in RX Queue         */
#define INT_RX_ERR          0x00000002  /* Receive Error                     */
#define INT_RX_FIN          0x00000004  /* RX Finished Process Descriptors   */
#define INT_RX_DONE         0x00000008  /* Receive Done                      */
#define INT_TX_UNDERRUN     0x00000010  /* Transmit Underrun                 */
#define INT_TX_ERR          0x00000020  /* Transmit Error                    */
#define INT_TX_FIN          0x00000040  /* TX Finished Process Descriptors   */
#define INT_TX_DONE         0x00000080  /* Transmit Done                     */
#define INT_SOFT_INT        0x00001000  /* Software Triggered Interrupt      */
#define INT_WAKEUP          0x00002000  /* Wakeup Event Interrupt            */

/* Power Down Register */
#define PD_POWER_DOWN       0x80000000  /* Power Down MAC                    */

/* RX Descriptor Control Word */
#define RCTRL_SIZE          0x000007FF  /* Buffer size mask                  */
#define RCTRL_INT           0x80000000  /* Generate RxDone Interrupt         */

/* RX Status Hash CRC Word */
#define RHASH_SA            0x000001FF  /* Hash CRC for Source Address       */
#define RHASH_DA            0x001FF000  /* Hash CRC for Destination Address  */

/* RX Status Information Word */
#define RINFO_SIZE          0x000007FF  /* Data size in bytes                */
#define RINFO_CTRL_FRAME    0x00040000  /* Control Frame                     */
#define RINFO_VLAN          0x00080000  /* VLAN Frame                        */
#define RINFO_FAIL_FILT     0x00100000  /* RX Filter Failed                  */
#define RINFO_MCAST         0x00200000  /* Multicast Frame                   */
#define RINFO_BCAST         0x00400000  /* Broadcast Frame                   */
#define RINFO_CRC_ERR       0x00800000  /* CRC Error in Frame                */
#define RINFO_SYM_ERR       0x01000000  /* Symbol Error from PHY             */
#define RINFO_LEN_ERR       0x02000000  /* Length Error                      */
#define RINFO_RANGE_ERR     0x04000000  /* Range Error (exceeded max. size)  */
#define RINFO_ALIGN_ERR     0x08000000  /* Alignment Error                   */
#define RINFO_OVERRUN       0x10000000  /* Receive overrun                   */
#define RINFO_NO_DESCR      0x20000000  /* No new Descriptor available       */
#define RINFO_LAST_FLAG     0x40000000  /* Last Fragment in Frame            */
#define RINFO_ERR           0x80000000  /* Error Occured (OR of all errors)  */

//#define RINFO_ERR_MASK     (RINFO_FAIL_FILT | RINFO_CRC_ERR   | RINFO_SYM_ERR | RINFO_LEN_ERR   | RINFO_ALIGN_ERR | RINFO_OVERRUN)
#define RINFO_ERR_MASK     (RINFO_FAIL_FILT | RINFO_SYM_ERR | \
                            RINFO_LEN_ERR   | RINFO_ALIGN_ERR | RINFO_OVERRUN)


/* TX Descriptor Control Word */
#define TCTRL_SIZE          0x000007FF  /* Size of data buffer in bytes      */
#define TCTRL_OVERRIDE      0x04000000  /* Override Default MAC Registers    */
#define TCTRL_HUGE          0x08000000  /* Enable Huge Frame                 */
#define TCTRL_PAD           0x10000000  /* Pad short Frames to 64 bytes      */
#define TCTRL_CRC           0x20000000  /* Append a hardware CRC to Frame    */
#define TCTRL_LAST          0x40000000  /* Last Descriptor for TX Frame      */
#define TCTRL_INT           0x80000000  /* Generate TxDone Interrupt         */

/* TX Status Information Word */
#define TINFO_COL_CNT       0x01E00000  /* Collision Count                   */
#define TINFO_DEFER         0x02000000  /* Packet Deferred (not an error)    */
#define TINFO_EXCESS_DEF    0x04000000  /* Excessive Deferral                */
#define TINFO_EXCESS_COL    0x08000000  /* Excessive Collision               */
#define TINFO_LATE_COL      0x10000000  /* Late Collision Occured            */
#define TINFO_UNDERRUN      0x20000000  /* Transmit Underrun                 */
#define TINFO_NO_DESCR      0x40000000  /* No new Descriptor available       */
#define TINFO_ERR           0x80000000  /* Error Occured (OR of all errors)  */

/* ENET Device Revision ID */
#define OLD_EMAC_MODULE_ID  0x39022000  /* Rev. ID for first rev '-'         */

/* DP83848C PHY Registers */
#define PHY_REG_BMCR        0x00        /* Basic Mode Control Register       */
#define PHY_REG_BMSR        0x01        /* Basic Mode Status Register        */
#define PHY_REG_IDR1        0x02        /* PHY Identifier 1                  */
#define PHY_REG_IDR2        0x03        /* PHY Identifier 2                  */
#define PHY_REG_ANAR        0x04        /* Auto-Negotiation Advertisement    */
#define PHY_REG_ANLPAR      0x05        /* Auto-Neg. Link Partner Abitily    */
#define PHY_REG_ANER        0x06        /* Auto-Neg. Expansion Register      */
#define PHY_REG_ANNPTR      0x07        /* Auto-Neg. Next Page TX            */

/* PHY Extended Registers */
#define PHY_REG_STS         0x10        /* Status Register                   */
#define PHY_REG_MICR        0x11        /* MII Interrupt Control Register    */
#define PHY_REG_MISR        0x12        /* MII Interrupt Status Register     */
#define PHY_REG_FCSCR       0x14        /* False Carrier Sense Counter       */
#define PHY_REG_RECR        0x15        /* Receive Error Counter             */
#define PHY_REG_PCSR        0x16        /* PCS Sublayer Config. and Status   */
#define PHY_REG_RBR         0x17        /* RMII and Bypass Register          */
#define PHY_REG_LEDCR       0x18        /* LED Direct Control Register       */
#define PHY_REG_PHYCR       0x19        /* PHY Control Register              */
#define PHY_REG_10BTSCR     0x1A        /* 10Base-T Status/Control Register  */
#define PHY_REG_CDCTRL1     0x1B        /* CD Test Control and BIST Extens.  */
#define PHY_REG_EDCR        0x1D        /* Energy Detect Control Register    */

#define PHY_REG_SCSR        0x1F        /* PHY Special Control/Status Register */

#define PHY_FULLD_100M      0x2100      /* Full Duplex 100Mbit               */
#define PHY_HALFD_100M      0x2000      /* Half Duplex 100Mbit               */
#define PHY_FULLD_10M       0x0100      /* Full Duplex 10Mbit                */
#define PHY_HALFD_10M       0x0000      /* Half Duplex 10MBit                */
#define PHY_AUTO_NEG        0x3000      /* Select Auto Negotiation           */

#define DP83848C_DEF_ADR    0x0100      /* Default PHY device address        */
#define DP83848C_ID         0x20005C90  /* PHY Identifier - DP83848C         */

#define LAN8720_ID          0x0007C0F0  /* PHY Identifier - LAN8720          */

#define PHY_STS_LINK        0x0001      /* PHY Status Link Mask              */
#define PHY_STS_SPEED       0x0002      /* PHY Status Speed Mask             */
#define PHY_STS_DUPLEX      0x0004      /* PHY Status Duplex Mask            */

#define PHY_BMCR_RESET      0x8000      /* PHY Reset                         */

#define PHY_BMSR_LINK       0x0004      /* PHY BMSR Link valid               */

#define PHY_SCSR_100MBIT    0x0008      /* Speed: 1=100 MBit, 0=10Mbit       */
#define PHY_SCSR_DUPLEX     0x0010      /* PHY Duplex Mask                   */


static int phy_read(unsigned int PhyReg);
static int phy_write(unsigned int PhyReg, unsigned short Data);

static void txdscr_init(void);
static void rxdscr_init(void);

#if defined (__ICCARM__)
#   define AHBSRAM1
#elif defined(TOOLCHAIN_GCC_CR)
#   define AHBSRAM1 __attribute__((section(".data.$RamPeriph32")))
#else
#   define AHBSRAM1     __attribute__((section("AHBSRAM1"),aligned))
#endif

AHBSRAM1 volatile uint8_t rxbuf[NUM_RX_FRAG][ETH_FRAG_SIZE];
AHBSRAM1 volatile uint8_t txbuf[NUM_TX_FRAG][ETH_FRAG_SIZE];
AHBSRAM1 volatile RX_DESC_TypeDef rxdesc[NUM_RX_FRAG];
AHBSRAM1 volatile RX_STAT_TypeDef rxstat[NUM_RX_FRAG];
AHBSRAM1 volatile TX_DESC_TypeDef txdesc[NUM_TX_FRAG];
AHBSRAM1 volatile TX_STAT_TypeDef txstat[NUM_TX_FRAG];


#if NEW_LOGIC
static int rx_consume_offset = -1;
static int tx_produce_offset = -1;
#else
static int send_doff =  0;
static int send_idx  = -1;
static int send_size =  0;

static int receive_soff =  0;
static int receive_idx  = -1;
#endif

static uint32_t phy_id = 0;

static inline int rinc(int idx, int mod) {
  ++idx;
  idx %= mod;
  return idx;
}

//extern unsigned int SystemFrequency;
static inline unsigned int clockselect() {
  if(SystemCoreClock < 10000000) {
    return 1;
  } else if(SystemCoreClock <  15000000) {
    return 2;
  } else if(SystemCoreClock <  20000000) {
    return 3;
  } else if(SystemCoreClock <  25000000) {
    return 4;
  } else if(SystemCoreClock <  35000000) {
    return 5;
  } else if(SystemCoreClock <  50000000) {
    return 6;
  } else if(SystemCoreClock <  70000000) {
    return 7;
  } else if(SystemCoreClock <  80000000) {
    return 8;
  } else if(SystemCoreClock <  90000000) {
    return 9;
  } else if(SystemCoreClock < 100000000) {
    return 10;
  } else if(SystemCoreClock < 120000000) {
    return 11;
  } else if(SystemCoreClock < 130000000) {
    return 12;
  } else if(SystemCoreClock < 140000000) {
    return 13;
  } else if(SystemCoreClock < 150000000) {
    return 15;
  } else if(SystemCoreClock < 160000000) {
    return 16;
  } else {
    return 0;
  }
}

#ifndef min
#define min(x, y) (((x)<(y))?(x):(y))
#endif

/*----------------------------------------------------------------------------
  Ethernet Device initialize
 *----------------------------------------------------------------------------*/
int ethernet_init() {
  int regv, tout;
  char mac[ETHERNET_ADDR_SIZE];
  unsigned int clock = clockselect();
  
  LPC_SC->PCONP |= 0x40000000;                       /* Power Up the EMAC controller. */
  
  LPC_PINCON->PINSEL2 = 0x50150105;                  /* Enable P1 Ethernet Pins. */
  LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~0x0000000F) | 0x00000005;
  
   /* Reset all EMAC internal modules. */
  LPC_EMAC->MAC1    = MAC1_RES_TX | MAC1_RES_MCS_TX | MAC1_RES_RX |
                      MAC1_RES_MCS_RX | MAC1_SIM_RES | MAC1_SOFT_RES;
  LPC_EMAC->Command = CR_REG_RES | CR_TX_RES | CR_RX_RES | CR_PASS_RUNT_FRM;

  for(tout = 100; tout; tout--) __NOP();             /* A short delay after reset. */

  LPC_EMAC->MAC1 = MAC1_PASS_ALL;                    /* Initialize MAC control registers. */
  LPC_EMAC->MAC2 = MAC2_CRC_EN | MAC2_PAD_EN;
  LPC_EMAC->MAXF = ETH_MAX_FLEN;
  LPC_EMAC->CLRT = CLRT_DEF;
  LPC_EMAC->IPGR = IPGR_DEF;

  LPC_EMAC->Command = CR_RMII | CR_PASS_RUNT_FRM;    /* Enable Reduced MII interface. */

  LPC_EMAC->MCFG = (clock << 0x2) & MCFG_CLK_SEL;    /* Set clock */
  LPC_EMAC->MCFG |= MCFG_RES_MII;                    /* and reset */

  for(tout = 100; tout; tout--) __NOP();             /* A short delay */

  LPC_EMAC->MCFG = (clock << 0x2) & MCFG_CLK_SEL;
  LPC_EMAC->MCMD = 0;

  LPC_EMAC->SUPP = SUPP_RES_RMII;                    /* Reset Reduced MII Logic. */

  for (tout = 100; tout; tout--) __NOP();            /* A short delay */

  LPC_EMAC->SUPP = 0;

  phy_write(PHY_REG_BMCR, PHY_BMCR_RESET);           /* perform PHY reset */
  for(tout = 0x20000; ; tout--) {                    /* Wait for hardware reset to end. */
    regv = phy_read(PHY_REG_BMCR);
    if(regv < 0 || tout == 0) {
       return -1;                                    /* Error */
    }
    if(!(regv & PHY_BMCR_RESET)) {
       break;                                        /* Reset complete. */
    }
  }

  phy_id =  (phy_read(PHY_REG_IDR1) << 16);
  phy_id |= (phy_read(PHY_REG_IDR2) & 0XFFF0);

  if (phy_id != DP83848C_ID && phy_id != LAN8720_ID) {
      error("Unknown Ethernet PHY (%x)", (unsigned int)phy_id);
  }

  ethernet_set_link(-1, 0);

  /* Set the Ethernet MAC Address registers */
  ethernet_address(mac);
  LPC_EMAC->SA0 = ((uint32_t)mac[5] << 8) | (uint32_t)mac[4];
  LPC_EMAC->SA1 = ((uint32_t)mac[3] << 8) | (uint32_t)mac[2];
  LPC_EMAC->SA2 = ((uint32_t)mac[1] << 8) | (uint32_t)mac[0];

  txdscr_init();                                      /* initialize DMA TX Descriptor */
  rxdscr_init();                                      /* initialize DMA RX Descriptor */

  LPC_EMAC->RxFilterCtrl = RFC_UCAST_EN | RFC_MCAST_EN | RFC_BCAST_EN | RFC_PERFECT_EN;
                                                      /* Receive Broadcast, Perfect Match Packets */

  LPC_EMAC->IntEnable = INT_RX_DONE | INT_TX_DONE;    /* Enable EMAC interrupts. */
  LPC_EMAC->IntClear  = 0xFFFF;                       /* Reset all interrupts */


  LPC_EMAC->Command  |= (CR_RX_EN | CR_TX_EN);        /* Enable receive and transmit mode of MAC Ethernet core */
  LPC_EMAC->MAC1     |= MAC1_REC_EN;

#if NEW_LOGIC
  rx_consume_offset = -1;
  tx_produce_offset = -1;
#else
  send_doff =  0;
  send_idx  = -1;
  send_size =  0;

  receive_soff =  0;
  receive_idx  = -1;
#endif

  return 0;
}

/*----------------------------------------------------------------------------
  Ethernet Device Uninitialize
 *----------------------------------------------------------------------------*/
void ethernet_free() {
  LPC_EMAC->IntEnable &= ~(INT_RX_DONE | INT_TX_DONE);
  LPC_EMAC->IntClear   =  0xFFFF;
  
  LPC_SC->PCONP   &= ~0x40000000;       /* Power down the EMAC controller. */
  
  LPC_PINCON->PINSEL2 &= ~0x50150105;   /* Disable P1 ethernet pins. */
  LPC_PINCON->PINSEL3  = (LPC_PINCON->PINSEL3 & ~0x0000000F) | 0x00000000;
}

// if(TxProduceIndex == TxConsumeIndex) buffer array is empty
// if(TxProduceIndex == TxConsumeIndex - 1) buffer is full, should not fill
// TxProduceIndex - The buffer that will/is being fileld by driver, s/w increment
// TxConsumeIndex - The buffer that will/is beign sent by hardware

int ethernet_write(const char *data, int slen) {

#if NEW_LOGIC

   if(tx_produce_offset < 0) { // mark as active if not already
     tx_produce_offset = 0;
   }

   int index = LPC_EMAC->TxProduceIndex;

   int remaining = ETH_MAX_FLEN - tx_produce_offset - 4; // bytes written plus checksum
   int requested = slen;
   int ncopy = min(remaining, requested);

   void *pdst = (void *)(txdesc[index].Packet + tx_produce_offset);
   void *psrc = (void *)(data);

   if(ncopy > 0 ){
     if(data != NULL) {
       memcpy(pdst, psrc, ncopy);
     } else {
       memset(pdst, 0, ncopy);
     }
   }

   tx_produce_offset += ncopy;

   return ncopy;

#else
    void       *pdst, *psrc;
    const int   dlen = ETH_FRAG_SIZE;
    int         copy = 0;
    int         soff = 0;

    if(send_idx == -1) {
        send_idx = LPC_EMAC->TxProduceIndex;
    }

    if(slen + send_doff > ethernet_MTU_SIZE) {
       return -1;
    }

    do {
        copy = min(slen - soff, dlen - send_doff);
        pdst = (void *)(txdesc[send_idx].Packet + send_doff);
        psrc = (void *)(data + soff);
        if(send_doff + copy > ETH_FRAG_SIZE) {
            txdesc[send_idx].Ctrl = (send_doff-1) | (TCTRL_INT);
            send_idx = rinc(send_idx, NUM_TX_FRAG);
            send_doff = 0;
        }

        if(data != NULL) {
            memcpy(pdst, psrc, copy);
        } else {
            memset(pdst, 0, copy);
        }

        soff += copy;
        send_doff += copy;
        send_size += copy;
    } while(soff != slen);

    return soff;
#endif
}

int ethernet_send() {

#if NEW_LOGIC
  if(tx_produce_offset < 0) { // no buffer active
    return -1;
  }

  // ensure there is a link
  if(!ethernet_link()) {
    return -2;
  }

  // we have been writing in to a buffer, so finalise it
  int size = tx_produce_offset;
  int index = LPC_EMAC->TxProduceIndex;
  txdesc[index].Ctrl = (tx_produce_offset-1) | (TCTRL_INT | TCTRL_LAST);

  // Increment ProduceIndex to allow it to be sent
  // We can only do this if the next slot is free
  int next = rinc(index, NUM_TX_FRAG);
  while(next == LPC_EMAC->TxConsumeIndex) {
    for(int i=0; i<1000; i++) { __NOP(); }
  }

  LPC_EMAC->TxProduceIndex = next;
  tx_produce_offset = -1;
  return size;

#else
    int s = send_size;
    txdesc[send_idx].Ctrl = (send_doff-1) | (TCTRL_INT | TCTRL_LAST);
    send_idx  = rinc(send_idx, NUM_TX_FRAG);
    LPC_EMAC->TxProduceIndex = send_idx;
    send_doff =  0;
    send_idx  = -1;
    send_size =  0;
    return s;
#endif
}

// RxConsmeIndex - The index of buffer the driver will/is reading from. Driver should inc once read
// RxProduceIndex - The index of buffer that will/is being filled by MAC. H/w will inc once rxd
//
// if(RxConsumeIndex == RxProduceIndex) buffer array is empty
// if(RxConsumeIndex == RxProduceIndex + 1) buffer array is full

// Recevies an arrived ethernet packet.
// Receiving an ethernet packet will drop the last received ethernet packet
// and make a new ethernet packet ready to read.
// Returns size of packet, else 0 if nothing to receive

// We read from RxConsumeIndex from position rx_consume_offset
// if rx_consume_offset < 0, then we have not recieved the RxConsumeIndex packet for reading
// rx_consume_offset = -1 // no frame
// rx_consume_offset = 0  // start of frame
// Assumption: A fragment should alway be a whole frame

int ethernet_receive() {
#if NEW_LOGIC

  // if we are currently reading a valid RxConsume buffer, increment to the next one
  if(rx_consume_offset >= 0) {
    LPC_EMAC->RxConsumeIndex = rinc(LPC_EMAC->RxConsumeIndex, NUM_RX_FRAG);
  }

  // if the buffer is empty, mark it as no valid buffer
  if(LPC_EMAC->RxConsumeIndex == LPC_EMAC->RxProduceIndex) {
    rx_consume_offset = -1;
    return 0;
  }

  uint32_t info = rxstat[LPC_EMAC->RxConsumeIndex].Info;
  rx_consume_offset = 0;

  // check if it is not marked as last or for errors
  if(!(info & RINFO_LAST_FLAG) || (info & RINFO_ERR_MASK)) {
    return -1;
  }

  int size = (info & RINFO_SIZE) + 1;
  return size - 4; // don't include checksum bytes

#else
    if(receive_idx == -1) {
      receive_idx = LPC_EMAC->RxConsumeIndex;
    } else {
        while(!(rxstat[receive_idx].Info & RINFO_LAST_FLAG) && ((uint32_t)receive_idx != LPC_EMAC->RxProduceIndex)) {
            receive_idx  = rinc(receive_idx, NUM_RX_FRAG);
        }
        unsigned int info =   rxstat[receive_idx].Info;
        int slen =  (info & RINFO_SIZE) + 1;

        if(slen > ethernet_MTU_SIZE || (info & RINFO_ERR_MASK)) {
            /* Invalid frame, ignore it and free buffer. */
            receive_idx = rinc(receive_idx, NUM_RX_FRAG);
        }
        receive_idx = rinc(receive_idx, NUM_RX_FRAG);
        receive_soff = 0;
        
        LPC_EMAC->RxConsumeIndex = receive_idx;
    }
    
    if((uint32_t)receive_idx == LPC_EMAC->RxProduceIndex) {
        receive_idx = -1;
        return 0;
    }
    
    return (rxstat[receive_idx].Info & RINFO_SIZE) - 3;
#endif
}

// Read from an recevied ethernet packet.
// After receive returnd a number bigger than 0 it is
// possible to read bytes from this packet.
// Read will write up to size bytes into data.
// It is possible to use read multible times.
// Each time read will start reading after the last read byte before.

int ethernet_read(char *data, int dlen) {
#if NEW_LOGIC
  // Check we have a valid buffer to read
  if(rx_consume_offset < 0) {
    return 0;
  }

  // Assume 1 fragment block
  uint32_t info = rxstat[LPC_EMAC->RxConsumeIndex].Info;
  int size = (info & RINFO_SIZE) + 1 - 4; // exclude checksum

  int remaining = size - rx_consume_offset;
  int requested = dlen;
  int ncopy = min(remaining, requested);

  void *psrc = (void *)(rxdesc[LPC_EMAC->RxConsumeIndex].Packet + rx_consume_offset);
  void *pdst = (void *)(data);

  if(data != NULL && ncopy > 0) {
    memcpy(pdst, psrc, ncopy);
  }

  rx_consume_offset += ncopy;

  return ncopy;
#else
    int          slen;
    int          copy   = 0;
    unsigned int more;
    unsigned int info;
    void        *pdst, *psrc;
    int          doff = 0;
    
    if((uint32_t)receive_idx == LPC_EMAC->RxProduceIndex || receive_idx == -1) {
        return 0;
    }
    
    do {
        info =   rxstat[receive_idx].Info;
        more = !(info & RINFO_LAST_FLAG);
        slen =  (info & RINFO_SIZE) + 1;
        
        if(slen > ethernet_MTU_SIZE || (info & RINFO_ERR_MASK)) {
            /* Invalid frame, ignore it and free buffer. */
            receive_idx = rinc(receive_idx, NUM_RX_FRAG);
        } else {
            
            copy = min(slen - receive_soff, dlen - doff);
            psrc = (void *)(rxdesc[receive_idx].Packet + receive_soff);
            pdst = (void *)(data + doff);
            
            if(data != NULL) {
                /* check if Buffer available */
                memcpy(pdst, psrc, copy);
            }
            
            receive_soff += copy;
            doff += copy;
            
            if((more && (receive_soff == slen))) {
                receive_idx = rinc(receive_idx, NUM_RX_FRAG);
                receive_soff = 0;
            }
        }
    } while(more && !(doff == dlen) && !receive_soff);
    
    return doff;
#endif
}

int ethernet_link(void) {
    if (phy_id == DP83848C_ID) {
      return (phy_read(PHY_REG_STS) & PHY_STS_LINK);
    }
    else { // LAN8720_ID
      return (phy_read(PHY_REG_BMSR) & PHY_BMSR_LINK);
    }
}

static int phy_write(unsigned int PhyReg, unsigned short Data) {
    unsigned int timeOut;
    
    LPC_EMAC->MADR = DP83848C_DEF_ADR | PhyReg;
    LPC_EMAC->MWTD = Data;
    
    for(timeOut = 0; timeOut < MII_WR_TOUT; timeOut++) {     /* Wait until operation completed */
        if((LPC_EMAC->MIND & MIND_BUSY) == 0) {
            return 0;
        }
    }
    
    return -1;
}

static int phy_read(unsigned int PhyReg) {
    unsigned int timeOut;
    
    LPC_EMAC->MADR = DP83848C_DEF_ADR | PhyReg;
    LPC_EMAC->MCMD = MCMD_READ;
    
    for(timeOut = 0; timeOut < MII_RD_TOUT; timeOut++) {     /* Wait until operation completed */
        if((LPC_EMAC->MIND & MIND_BUSY) == 0) {
            LPC_EMAC->MCMD = 0;
            return LPC_EMAC->MRDD;                           /* Return a 16-bit value. */
        }
    }
    
    return -1;
}


static void txdscr_init() {
    int i;
    
    for(i = 0; i < NUM_TX_FRAG; i++) {
        txdesc[i].Packet = (uint32_t)&txbuf[i];
        txdesc[i].Ctrl   = 0;
        txstat[i].Info   = 0;
    }
    
    LPC_EMAC->TxDescriptor       = (uint32_t)txdesc;         /* Set EMAC Transmit Descriptor Registers. */
    LPC_EMAC->TxStatus           = (uint32_t)txstat;
    LPC_EMAC->TxDescriptorNumber = NUM_TX_FRAG-1;
    
    LPC_EMAC->TxProduceIndex  = 0;                           /* Tx Descriptors Point to 0 */
}

static void rxdscr_init() {
    int i;
    
    for(i = 0; i < NUM_RX_FRAG; i++) {
        rxdesc[i].Packet  = (uint32_t)&rxbuf[i];
        rxdesc[i].Ctrl    = RCTRL_INT | (ETH_FRAG_SIZE-1);
        rxstat[i].Info    = 0;
        rxstat[i].HashCRC = 0;
    }
    
    LPC_EMAC->RxDescriptor       = (uint32_t)rxdesc;        /* Set EMAC Receive Descriptor Registers. */
    LPC_EMAC->RxStatus           = (uint32_t)rxstat;
    LPC_EMAC->RxDescriptorNumber = NUM_RX_FRAG-1;
    
    LPC_EMAC->RxConsumeIndex  = 0;                          /* Rx Descriptors Point to 0 */
}

void ethernet_address(char *mac) {
    mbed_mac_address(mac);
}

void ethernet_set_link(int speed, int duplex) {
    unsigned short phy_data;
    int tout;
    
    if((speed < 0) || (speed > 1)) {
        phy_data = PHY_AUTO_NEG;
    } else {
        phy_data = (((unsigned short) speed << 13) |
                    ((unsigned short) duplex << 8));
    }
    
    phy_write(PHY_REG_BMCR, phy_data);
    
    for(tout = 100; tout; tout--) { __NOP(); }     /* A short delay */
    
    switch(phy_id) {
        case DP83848C_ID:
            phy_data = phy_read(PHY_REG_STS);
            
            if(phy_data & PHY_STS_DUPLEX) {
                LPC_EMAC->MAC2 |= MAC2_FULL_DUP;
                LPC_EMAC->Command |= CR_FULL_DUP;
                LPC_EMAC->IPGT = IPGT_FULL_DUP;
            } else {
            LPC_EMAC->MAC2 &= ~MAC2_FULL_DUP;
                LPC_EMAC->Command &= ~CR_FULL_DUP;
                LPC_EMAC->IPGT = IPGT_HALF_DUP;
            }
            
            if(phy_data & PHY_STS_SPEED) {
                LPC_EMAC->SUPP &= ~SUPP_SPEED;
            } else {
                LPC_EMAC->SUPP |= SUPP_SPEED;
            }
            break;
        
        case LAN8720_ID:
            phy_data = phy_read(PHY_REG_SCSR);
            
            if (phy_data & PHY_SCSR_DUPLEX) {
                LPC_EMAC->MAC2 |= MAC2_FULL_DUP;
                LPC_EMAC->Command |= CR_FULL_DUP;
                LPC_EMAC->IPGT = IPGT_FULL_DUP;
            } else {
                LPC_EMAC->Command &= ~CR_FULL_DUP;
                LPC_EMAC->IPGT = IPGT_HALF_DUP;
            }
            
            if(phy_data & PHY_SCSR_100MBIT) {
                LPC_EMAC->SUPP |= SUPP_SPEED;
            } else {
                LPC_EMAC->SUPP &= ~SUPP_SPEED;
            }
            break;
    }
}
