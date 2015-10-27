/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
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
 *
 * Contribution by Nitin Bhaskar(nitin.bhaskar.27.09@gmail.com)
 */
#include "ethernet_api.h"

#include <string.h>
#include "cmsis.h"
#include "mbed_interface.h"
#include "toolchain.h"
#include "mbed_error.h"
#include "pinmap.h"

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

/*  Descriptors Fields bits       */
#define TRDES_OWN_BIT		(1U<<31)	/*  Own bit in RDES0 & TDES0              */
#define RX_END_RING		(1<<15)		/*  Receive End of Ring bit in RDES1      */
#define RX_NXTDESC_FLAG		(1<<14)		/*  Second Address Chained bit in RDES1   */
#define TX_LAST_SEGM		(1<<29)		/*  Last Segment bit in TDES0             */
#define TX_FIRST_SEGM		(1<<28)		/*  First Segment bit in TDES0            */
#define TX_END_RING		(1<<21)		/*  Transmit End of Ring bit in TDES0     */
#define TX_NXTDESC_FLAG		(1<<20)		/*  Second Address Chained bit in TDES0   */

PACKED struct RX_DESC_TypeDef {                        /* RX Descriptor struct              */
    unsigned int Status;
    unsigned int Ctrl;
    unsigned int BufAddr1;
    unsigned int NextDescAddr;
};
typedef struct RX_DESC_TypeDef RX_DESC_TypeDef;

PACKED struct TX_DESC_TypeDef {                        /* TX Descriptor struct              */
    unsigned int Status;
    unsigned int Ctrl;
    unsigned int BufAddr1;
    unsigned int NextDescAddr;
};
typedef struct TX_DESC_TypeDef TX_DESC_TypeDef;

/* ETHMODE RMII SELECT */
#define RMII_SELECT			0x04
/* define to tell PHY about write operation */
#define MII_WRITE		(1 << 1)
/* define to tell PHY about read operation */
#define MII_READ		(0 << 1)
/* define to enable duplex mode */
#define MAC_DUPLEX_MODE (1 << 11)

/* MAC_FRAME_FILTER register bit defines */
#define MAC_FRAME_FILTER_PR      (1 << 0)		/* Promiscuous Mode */
#define MAC_FRAME_FILTER_RA      (1UL << 31)	/* Receive all */

/* MAC_CONFIG register bit defines */
#define MAC_CONFIG_RE     (1 << 2)		/* Receiver enable */
#define MAC_CONFIG_TE     (1 << 3)		/* Transmitter Enable */

/* DMA_OP_MODE register bit defines */
#define DMA_OP_MODE_SSR      (1 << 1)		/* Start/stop receive */
#define DMA_OP_MODE_SST      (1 << 13)	/* Start/Stop Transmission Command */

/* DMA_INT_EN register bit defines */
#define DMA_INT_EN_TIE     (1 << 0)		/* Transmit interrupt enable */
#define DMA_INT_EN_TSE     (1 << 1)		/* Transmit stopped enable */
#define DMA_INT_EN_TUE     (1 << 2)		/* Transmit buffer unavailable enable */
#define DMA_INT_EN_TJE     (1 << 3)		/* Transmit jabber timeout enable */
#define DMA_INT_EN_OVE     (1 << 4)		/* Overflow interrupt enable */
#define DMA_INT_EN_UNE     (1 << 5)		/* Underflow interrupt enable */
#define DMA_INT_EN_RIE     (1 << 6)		/* Receive interrupt enable */
#define DMA_INT_EN_RUE     (1 << 7)		/* Receive buffer unavailable enable */
#define DMA_INT_EN_RSE     (1 << 8)		/* Received stopped enable */
#define DMA_INT_EN_RWE     (1 << 9)		/* Receive watchdog timeout enable */
#define DMA_INT_EN_ETE     (1 << 10)	/* Early transmit interrupt enable */
#define DMA_INT_EN_FBE     (1 << 13)	/* Fatal bus error enable */
#define DMA_INT_EN_ERE     (1 << 14)	/* Early receive interrupt enable */
#define DMA_INT_EN_AIE     (1 << 15)	/* Abnormal interrupt summary enable */
#define DMA_INT_EN_NIE     (1 << 16)	/* Normal interrupt summary enable */



/* PHY Support Register */
#define SUPP_SPEED          0x00004000  /* Reduced MII Logic Current Speed   */
//#define SUPP_RES_RMII       0x00000800  /* Reset Reduced MII Logic           */
#define SUPP_RES_RMII       0x00000000  /* Reset Reduced MII Logic           */

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
#define PHY_AUTO_NEG        0x1000      /* Select Auto Negotiation           */

#define DP83848C_DEF_ADR    0x01      /* Default PHY device address        */
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
AHBSRAM1 volatile TX_DESC_TypeDef txdesc[NUM_TX_FRAG];

#ifndef min
#define min(x, y) (((x)<(y))?(x):(y))
#endif

static uint32_t phy_id = 0;
static uint32_t TxDescIndex = 0;
static uint32_t RxDescIndex = 0;
static uint32_t RxOffset = 0;

/*----------------------------------------------------------------------------
  Ethernet Device initialize
 *----------------------------------------------------------------------------*/
int ethernet_init()
{
    int regv, tout;
    char mac[ETHERNET_ADDR_SIZE];

    pin_function(PC_0, (SCU_MODE_INACT | FUNC3)); 	/* Enable ENET RX CLK */
    pin_function(P1_19, (SCU_MODE_INACT | FUNC0)); 	/* Enable ENET TX CLK */

    /* Ethernet pinmuxing	*/
    pin_function(P2_0, SCU_PINIO_FAST | FUNC7); 	/* ENET_MDC */
    pin_function(P1_17, SCU_PINIO_FAST | FUNC3); 	/* ENET_MDIO */
    pin_function(P1_18, SCU_PINIO_FAST | FUNC3); 	/* ENET_TXD0 */
    pin_function(P1_20, SCU_PINIO_FAST | FUNC3); 	/* ENET_TXD1 */
    pin_function(P1_19, SCU_PINIO_FAST | FUNC0); 	/* ENET_REF */
    pin_function(P0_1, SCU_PINIO_FAST | FUNC6); 	/* ENET_TX_EN */
    pin_function(P1_15, SCU_PINIO_FAST | FUNC3); 	/* ENET_RXD0 */
    pin_function(P0_0, SCU_PINIO_FAST | FUNC2); 	/* ENET_RXD1 */
    pin_function(P1_16, SCU_PINIO_FAST | FUNC3); 	/* ENET_CRS */
    pin_function(PC_9, SCU_PINIO_FAST | FUNC3); 	/* ENET_RX_ER */
    pin_function(P1_16, SCU_PINIO_FAST | FUNC7); 	/* ENET_RXDV */

    LPC_CREG->CREG6 |= RMII_SELECT;

    /* perform RGU soft reset */
    LPC_RGU->RESET_CTRL0 = 1 << 22;
    LPC_RGU->RESET_CTRL0 = 0;

    /* Wait until reset is performed */
    while(1) {
        if (LPC_RGU->RESET_ACTIVE_STATUS0 & (1 << 22))
            break;
    }

    /* Reset MAC DMA Controller */
    LPC_ETHERNET->DMA_BUS_MODE |= 0x01;
    while(LPC_ETHERNET->DMA_BUS_MODE & 0x01);

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
    LPC_ETHERNET->MAC_ADDR0_HIGH = (mac[5] << 8) | mac[4];
    LPC_ETHERNET->MAC_ADDR0_LOW =	(mac[3] << 24) | (mac[2] << 16) | (mac[1] << 8) | mac[0];

    txdscr_init();                                      /* initialize DMA TX Descriptor */
    rxdscr_init();                                      /* initialize DMA RX Descriptor */

    /* Configure Filter */
    LPC_ETHERNET->MAC_FRAME_FILTER = MAC_FRAME_FILTER_PR | MAC_FRAME_FILTER_RA;

    /* Enable Receiver and Transmitter */
    LPC_ETHERNET->MAC_CONFIG |= (MAC_CONFIG_RE | MAC_CONFIG_TE);

    //LPC_ETHERNET->DMA_INT_EN =  DMA_INT_EN_NIE | DMA_INT_EN_RIE | DMA_INT_EN_TJE;	/* Enable EMAC interrupts. */

    /* Start Transmission & Receive processes   */
    LPC_ETHERNET->DMA_OP_MODE |= (DMA_OP_MODE_SST | DMA_OP_MODE_SSR);

    return 0;
}

/*----------------------------------------------------------------------------
  Ethernet Device Uninitialize
 *----------------------------------------------------------------------------*/
void ethernet_free()
{
}

/*----------------------------------------------------------------------------
  Ethernet write
 *----------------------------------------------------------------------------*/
int ethernet_write(const char *data, int slen)
{
    if (slen > ETH_FRAG_SIZE)
        return -1;

    txdesc[TxDescIndex].Ctrl = slen;
    memcpy((void *)txdesc[TxDescIndex].BufAddr1, data, slen);
    return slen;
}

/*----------------------------------------------------------------------------
  Ethernet Send
 *----------------------------------------------------------------------------*/
int ethernet_send()
{
    int s = txdesc[TxDescIndex].Ctrl;
    txdesc[TxDescIndex].Status |= TRDES_OWN_BIT;
    LPC_ETHERNET->DMA_TRANS_POLL_DEMAND = 1;   //  Wake Up the DMA if it's in Suspended Mode
    TxDescIndex++;
    if (TxDescIndex == NUM_TX_FRAG)
        TxDescIndex = 0;

    return s;
}

/*----------------------------------------------------------------------------
  Ethernet receive
 *----------------------------------------------------------------------------*/
int ethernet_receive()
{
    int i, slen = 0;
    for (i = RxDescIndex;; i++) {
        if (rxdesc[i].Status & TRDES_OWN_BIT)
            return (slen - RxOffset);
        else
            slen += (rxdesc[i].Status >> 16) & 0x03FFF;
    }
    return 0;
}


/*----------------------------------------------------------------------------
  Ethernet read
 *----------------------------------------------------------------------------*/
int ethernet_read(char *data, int dlen)
{
    int copylen;
    uint32_t *pSrc = (uint32_t *)rxdesc[RxDescIndex].BufAddr1;
    copylen = (rxdesc[RxDescIndex].Status >> 16) & 0x03FFF;
    if (rxdesc[RxDescIndex].Status & TRDES_OWN_BIT || (dlen + RxOffset) > copylen)
        return -1;

    if ((dlen + RxOffset) == copylen) {
        memcpy(&pSrc[RxOffset], data, copylen);
        rxdesc[RxDescIndex].Status = TRDES_OWN_BIT;
        RxDescIndex++;
        RxOffset = 0;
        if (RxDescIndex == NUM_RX_FRAG)
            RxDescIndex = 0;
    } else if ((dlen + RxOffset) < copylen) {
        copylen = dlen;
        memcpy(&pSrc[RxOffset], data, copylen);
        RxOffset += dlen;
    }
    return copylen;
}

int ethernet_link(void)
{

    if (phy_id == DP83848C_ID) {
        return (phy_read(PHY_REG_STS) & PHY_STS_LINK);
    } else { // LAN8720_ID
        return (phy_read(PHY_REG_BMSR) & PHY_BMSR_LINK);
    }
}

static int phy_write(unsigned int PhyReg, unsigned short Data)
{
    unsigned int timeOut;

    while(LPC_ETHERNET->MAC_MII_ADDR & MIND_BUSY);
    LPC_ETHERNET->MAC_MII_ADDR = (DP83848C_DEF_ADR<<11) | (PhyReg<<6) | MII_WRITE;
    LPC_ETHERNET->MAC_MII_DATA = Data;
    LPC_ETHERNET->MAC_MII_ADDR |= MIND_BUSY;				// Start PHY Write Cycle

    /* Wait utill operation completed */
    for (timeOut = 0; timeOut < MII_WR_TOUT; timeOut++) {
        if ((LPC_ETHERNET->MAC_MII_ADDR & MIND_BUSY) == 0) {
            break;
        }
    }

    return -1;
}

static int phy_read(unsigned int PhyReg)
{
    unsigned int timeOut;

    while(LPC_ETHERNET->MAC_MII_ADDR & MIND_BUSY);
    LPC_ETHERNET->MAC_MII_ADDR = (DP83848C_DEF_ADR<<11) | (PhyReg<<6) | MII_READ;
    LPC_ETHERNET->MAC_MII_ADDR |= MIND_BUSY;

    for(timeOut = 0; timeOut < MII_RD_TOUT; timeOut++) {     /* Wait until operation completed */
        if((LPC_ETHERNET->MAC_MII_ADDR & MIND_BUSY) == 0) {
            return LPC_ETHERNET->MAC_MII_DATA;               /* Return a 16-bit value. */
        }
    }

    return -1;
}

static void txdscr_init()
{
    int i;

    for(i = 0; i < NUM_TX_FRAG; i++) {
        txdesc[i].Status = TX_LAST_SEGM | TX_FIRST_SEGM;;
        txdesc[i].Ctrl   = 0;
        txdesc[i].BufAddr1   = (uint32_t)&txbuf[i];
        if (i == (NUM_RX_FRAG - 1)) {
            txdesc[i].Status |= TX_END_RING;
        }
    }

    LPC_ETHERNET->DMA_TRANS_DES_ADDR = (uint32_t)txdesc;         /* Set EMAC Transmit Descriptor Registers. */
}


static void rxdscr_init()
{
    int i;

    for(i = 0; i < NUM_RX_FRAG; i++) {
        rxdesc[i].Status  = TRDES_OWN_BIT;
        rxdesc[i].Ctrl    = ETH_FRAG_SIZE;
        rxdesc[i].BufAddr1  = (uint32_t)&rxbuf[i];
        if (i == (NUM_RX_FRAG - 1)) {
            rxdesc[i].Ctrl |= RX_END_RING;
        }
    }

    LPC_ETHERNET->DMA_REC_DES_ADDR = (uint32_t)rxdesc;        /* Set EMAC Receive Descriptor Registers. */
}

void ethernet_address(char *mac)
{
    mbed_mac_address(mac);
}

void ethernet_set_link(int speed, int duplex)
{
    volatile unsigned short phy_data;
    int tout;

    if((speed < 0) || (speed > 1)) {

        phy_data = PHY_AUTO_NEG;

    } else {

        phy_data = (((unsigned short) speed << 13) |
                    ((unsigned short) duplex << 8));
    }

    phy_write(PHY_REG_BMCR, phy_data);

    for(tout = 100; tout; tout--) {
        __NOP();    /* A short delay */
    }

    switch(phy_id) {
        case DP83848C_ID:

            phy_data = phy_read(PHY_REG_STS);

            if(phy_data & PHY_STS_DUPLEX) {
                /* Full duplex is enabled. */
                LPC_ETHERNET->MAC_CONFIG |= MAC_DUPLEX_MODE;
            } else {
                LPC_ETHERNET->MAC_CONFIG &= ~MAC_DUPLEX_MODE;
            }

            if(phy_data & PHY_STS_SPEED) {
                LPC_ETHERNET->MAC_CONFIG &= ~SUPP_SPEED;
            } else {
                LPC_ETHERNET->MAC_CONFIG |= SUPP_SPEED;
            }
            break;

        case LAN8720_ID:

            for(tout = 100; tout; tout--) {
                phy_data = phy_read(PHY_REG_BMSR);
                if (phy_data & PHY_STS_DUPLEX)
                    break;
            }

            if (phy_data & PHY_STS_DUPLEX) {
                /* Full duplex is enabled. */
                LPC_ETHERNET->MAC_CONFIG |= MAC_DUPLEX_MODE;
            } else {
                LPC_ETHERNET->MAC_CONFIG &= ~MAC_DUPLEX_MODE;
            }

            if(phy_data & PHY_STS_SPEED) {
                LPC_ETHERNET->MAC_CONFIG &= ~SUPP_SPEED;
            } else {
                LPC_ETHERNET->MAC_CONFIG |= SUPP_SPEED;
            }
            break;
    }
}

