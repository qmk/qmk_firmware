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
#include "ether_iodefine.h"
#include "ethernetext_api.h"

/* Descriptor info */
#define NUM_OF_TX_DESCRIPTOR    (16)
#define NUM_OF_RX_DESCRIPTOR    (16)
#define SIZE_OF_BUFFER          (1600)     /* Must be an integral multiple of 32 */
#define MAX_SEND_SIZE           (1514)
/* Ethernet Descriptor Value Define */
#define TD0_TFP_TOP_BOTTOM      (0x30000000)
#define TD0_TACT                (0x80000000)
#define TD0_TDLE                (0x40000000)
#define RD0_RACT                (0x80000000)
#define RD0_RDLE                (0x40000000)
#define RD0_RFE                 (0x08000000)
#define RD0_RCSE                (0x04000000)
#define RD0_RFS                 (0x03FF0000)
#define RD0_RCS                 (0x0000FFFF)
#define RD0_RFS_RFOF            (0x02000000)
#define RD0_RFS_RUAF            (0x00400000)
#define RD0_RFS_RRF             (0x00100000)
#define RD0_RFS_RTLF            (0x00080000)
#define RD0_RFS_RTSF            (0x00040000)
#define RD0_RFS_PRE             (0x00020000)
#define RD0_RFS_CERF            (0x00010000)
#define RD0_RFS_ERROR           (RD0_RFS_RFOF | RD0_RFS_RUAF | RD0_RFS_RRF | RD0_RFS_RTLF | \
                                 RD0_RFS_RTSF | RD0_RFS_PRE | RD0_RFS_CERF)
#define RD1_RDL_MSK             (0x0000FFFF)
/* PHY Register */
#define BASIC_MODE_CONTROL_REG  (0)
#define BASIC_MODE_STATUS_REG   (1)
#define PHY_IDENTIFIER1_REG     (2)
#define PHY_IDENTIFIER2_REG     (3)
#define PHY_SP_CTL_STS_REG      (31)
/* MII management interface access */
#define PHY_ADDR                (0)        /* Confirm the pin connection of the PHY-LSI */
#define PHY_ST                  (1)
#define PHY_WRITE               (1)
#define PHY_READ                (2)
#define MDC_WAIT                (6)        /* 400ns/4 */
#define BASIC_STS_MSK_LINK      (0x0004)   /* Link Status */
#define BASIC_STS_MSK_AUTO_CMP  (0x0010)   /* Auto-Negotiate Complete */
#define M_PHY_ID                (0xFFFFFFF0)
#define PHY_ID_LAN8710A         (0x0007C0F0)
/* ETHERPIR0 */
#define PIR0_MDI                (0x00000008)
#define PIR0_MDO                (0x00000004)
#define PIR0_MMD                (0x00000002)
#define PIR0_MDC                (0x00000001)
#define PIR0_MDC_HIGH           (0x00000001)
#define PIR0_MDC_LOW            (0x00000000)
/* ETHEREDRRR0 */
#define EDRRR0_RR               (0x00000001)
/* ETHEREDTRR0 */
#define EDTRR0_TR               (0x00000003)
/* software wait */
#define LOOP_100us              (6700)     /* Loop counter for software wait  6666=100us/((1/400MHz)*6cyc) */

#define EDMAC_EESIPR_INI_RECV   (0x0205001F)    /* 0x02000000 : Detect reception suspended */
                                                /* 0x00040000 : Detect frame reception */
                                                /* 0x00010000 : Receive FIFO overflow */
                                                /* 0x00000010 : Residual bit frame reception */
                                                /* 0x00000008 : Long frame reception */
                                                /* 0x00000004 : Short frame reception */
                                                /* 0x00000002 : PHY-LSI reception error */
                                                /* 0x00000001 : Receive frame CRC error */
#define EDMAC_EESIPR_INI_EtherC (0x00400000)    /* 0x00400000 : E-MAC status register */

/* Send descriptor */
typedef struct tag_edmac_send_desc {
    uint32_t    td0;
    uint32_t    td1;
    uint8_t     *td2;
    uint32_t    padding4;
} edmac_send_desc_t;

/* Receive descriptor */
typedef struct tag_edmac_recv_desc {
    uint32_t    rd0;
    uint32_t    rd1;
    uint8_t     *rd2;
    uint32_t    padding4;
} edmac_recv_desc_t;

/* memory */
/* The whole transmit/receive descriptors (must be allocated in 16-byte boundaries) */
/* Transmit/receive buffers (must be allocated in 16-byte boundaries) */
static uint8_t ehernet_nc_memory[(sizeof(edmac_send_desc_t) * NUM_OF_TX_DESCRIPTOR) +
                                 (sizeof(edmac_recv_desc_t) * NUM_OF_RX_DESCRIPTOR) +
                                 (NUM_OF_TX_DESCRIPTOR * SIZE_OF_BUFFER) +
                                 (NUM_OF_RX_DESCRIPTOR * SIZE_OF_BUFFER)]
                                 __attribute((section("NC_BSS"),aligned(16)));  //16 bytes aligned!
static int32_t            rx_read_offset;   /* read offset */
static int32_t            tx_wite_offset;   /* write offset */
static uint32_t           send_top_index;
static uint32_t           recv_top_index;
static int32_t            Interrupt_priority;
static edmac_send_desc_t  *p_eth_desc_dsend = NULL;
static edmac_recv_desc_t  *p_eth_desc_drecv = NULL;
static edmac_recv_desc_t  *p_recv_end_desc  = NULL;
static ethernetext_cb_fnc *p_recv_cb_fnc    = NULL;
static char               mac_addr[6]       = {0x00, 0x02, 0xF7, 0xF0, 0x00, 0x00}; /* MAC Address */
static uint32_t           phy_id            = 0;
static uint32_t           start_stop        = 1;  /* 0:stop  1:start */

/* function */
static void lan_reg_reset(void);
static void lan_desc_create(void);
static void lan_reg_set(int32_t link);
static uint16_t phy_reg_read(uint16_t reg_addr);
static void phy_reg_write(uint16_t reg_addr, uint16_t data);
static void mii_preamble(void);
static void mii_cmd(uint16_t reg_addr, uint32_t option);
static void mii_reg_read(uint16_t *data);
static void mii_reg_write(uint16_t data);
static void mii_z(void);
static void mii_write_1(void);
static void mii_write_0(void);
static void set_ether_pir(uint32_t set_data);
static void wait_100us(int32_t wait_cnt);


int ethernetext_init(ethernet_cfg_t *p_ethcfg) {
    int32_t  i;
    uint16_t val;

    CPGSTBCR7 &= ~(CPG_STBCR7_BIT_MSTP74);  /* enable ETHER clock */

    /* P4_2(PHY Reset) */
    GPIOP4      &= ~0x0004;         /* Outputs low level */
    GPIOPMC4    &= ~0x0004;         /* Port mode */
    GPIOPM4     &= ~0x0004;         /* Output mode */

    /* GPIO P1  P1_14(ET_COL) */
    GPIOPMC1    |=  0x4000;
    GPIOPFCAE1  &= ~0x4000;
    GPIOPFCE1   |=  0x4000;
    GPIOPFC1    |=  0x4000;

    /* P3_0(ET_TXCLK), P3_3(ET_MDIO), P3_4(ET_RXCLK), P3_5(ET_RXER), P3_6(ET_RXDV) */
    GPIOPMC3    |=  0x0079;
    GPIOPFCAE3  &= ~0x0079;
    GPIOPFCE3   &= ~0x0079;
    GPIOPFC3    |=  0x0079;
    GPIOPIPC3   |=  0x0079;

    /* P5_9(ET_MDC) */
    GPIOPMC5    |=  0x0200;
    GPIOPFCAE5  &= ~0x0200;
    GPIOPFCE5   &= ~0x0200;
    GPIOPFC5    |=  0x0200;
    GPIOPIPC5   |=  0x0200;

    /* P10_1(ET_TXER), P10_2(ET_TXEN), P10_3(ET_CRS), P10_4(ET_TXD0), P10_5(ET_TXD1) */
    /* P10_6(ET_TXD2), P10_7(ET_TXD3), P10_8(ET_RXD0), P10_9(ET_RXD1), P10_10(ET_RXD2), P10_11(ET_RXD3) */
    GPIOPMC10   |=  0x0FFE;
    GPIOPFCAE10 &= ~0x0FFE;
    GPIOPFCE10  |=  0x0FFE;
    GPIOPFC10   |=  0x0FFE;
    GPIOPIPC10  |=  0x0FFE;

    /* Resets the E-MAC,E-DMAC */
    lan_reg_reset();

    /* PHY Reset */
    GPIOP4      &= ~0x0004;         /* P4_2 Outputs low level */
    wait_100us(250);                /* 25msec */
    GPIOP4      |=  0x0004;         /* P4_2 Outputs high level */
    wait_100us(100);                /* 10msec */

    /* Resets the PHY-LSI */
    phy_reg_write(BASIC_MODE_CONTROL_REG, 0x8000);
    for (i = 10000; i > 0; i--) {
        val = phy_reg_read(BASIC_MODE_CONTROL_REG);
        if (((uint32_t)val & 0x8000uL) == 0) {
            break;                  /* Reset complete */
        }
    }

    phy_id = ((uint32_t)phy_reg_read(PHY_IDENTIFIER1_REG) << 16)
           |  (uint32_t)phy_reg_read(PHY_IDENTIFIER2_REG);

    Interrupt_priority = p_ethcfg->int_priority;
    p_recv_cb_fnc      = p_ethcfg->recv_cb;
    start_stop         = 1;

    if (p_ethcfg->ether_mac != NULL) {
        (void)memcpy(mac_addr, p_ethcfg->ether_mac, sizeof(mac_addr));
    } else {
		ethernet_address(mac_addr); /* Get MAC Address */
    }

    return 0;
}

void ethernetext_start_stop(int32_t mode) {
    if (mode == 1) {
        /* start */
        ETHEREDTRR0 |= EDTRR0_TR;
        ETHEREDRRR0 |= EDRRR0_RR;
        start_stop   = 1;
    } else {
        /* stop */
        ETHEREDTRR0 &= ~EDTRR0_TR;
        ETHEREDRRR0 &= ~EDRRR0_RR;
        start_stop   = 0;
    }
}

int ethernetext_chk_link_mode(void) {
    int32_t  link;
    uint16_t data;

    if ((phy_id & M_PHY_ID) == PHY_ID_LAN8710A) {
        data = phy_reg_read(PHY_SP_CTL_STS_REG);
        switch (((uint32_t)data >> 2) & 0x00000007) {
            case 0x0001:
                link = HALF_10M;
                break;
            case 0x0005:
                link = FULL_10M;
                break;
            case 0x0002:
                link = HALF_TX;
                break;
            case 0x0006:
                link = FULL_TX;
                break;
            default:
                link = NEGO_FAIL;
                break;
        }
    } else {
        link = NEGO_FAIL;
    }

    return link;
}

void ethernetext_set_link_mode(int32_t link) {
    lan_reg_reset();            /* Resets the E-MAC,E-DMAC */
    lan_desc_create();          /* Initialize of buffer memory */
    lan_reg_set(link);          /* E-DMAC, E-MAC initialization */
}

int ethernet_init() {
    ethernet_cfg_t ethcfg;

    ethcfg.int_priority = 5;
    ethcfg.recv_cb      = NULL;
    ethcfg.ether_mac    = NULL;
    ethernetext_init(&ethcfg);
    ethernet_set_link(-1, 0);   /* Auto-Negotiation */

    return 0;
}

void ethernet_free() {
    ETHERARSTR |= 0x00000001;            /* ETHER software reset */
    CPGSTBCR7  |= CPG_STBCR7_BIT_MSTP74; /* disable ETHER clock */
}

int ethernet_write(const char *data, int slen) {
    edmac_send_desc_t *p_send_desc;
    int32_t           copy_size;

    if ((p_eth_desc_dsend == NULL) || (data == NULL) || (slen < 0)
     || (tx_wite_offset < 0) || (tx_wite_offset >= MAX_SEND_SIZE)) {
        copy_size = 0;
    } else {
        p_send_desc = &p_eth_desc_dsend[send_top_index];   /* Current descriptor */
        if ((p_send_desc->td0 & TD0_TACT) != 0) {
            copy_size = 0;
        } else {
            copy_size = MAX_SEND_SIZE - tx_wite_offset;
            if (copy_size > slen) {
                copy_size = slen;
            }
            (void)memcpy(&p_send_desc->td2[tx_wite_offset], data, copy_size);
            tx_wite_offset += copy_size;
        }
    }

    return copy_size;
}

int ethernet_send() {
    edmac_send_desc_t *p_send_desc;
    int32_t           ret;

    if ((p_eth_desc_dsend == NULL) || (tx_wite_offset <= 0)) {
        ret = 0;
    } else {
        /* Transfer 1 frame */
        p_send_desc = &p_eth_desc_dsend[send_top_index];   /* Current descriptor */

        /* Sets the frame length */
        p_send_desc->td1 = ((uint32_t)tx_wite_offset << 16);
        tx_wite_offset   = 0;

        /* Sets the transmit descriptor to transmit again */
        p_send_desc->td0 &= (TD0_TACT | TD0_TDLE | TD0_TFP_TOP_BOTTOM);
        p_send_desc->td0 |= TD0_TACT;
        if ((start_stop == 1) && ((ETHEREDTRR0 & EDTRR0_TR) != EDTRR0_TR)) {
            ETHEREDTRR0 |= EDTRR0_TR;
        }

        /* Update the current descriptor */
        send_top_index++;
        if (send_top_index >= NUM_OF_TX_DESCRIPTOR) {
            send_top_index = 0;
        }
        ret = 1;
    }

    return ret;
}

int ethernet_receive() {
    edmac_recv_desc_t *p_recv_desc;
    int32_t           receive_size = 0;

    if (p_eth_desc_drecv != NULL) {
        if (p_recv_end_desc != NULL) {
            /* Sets the receive descriptor to receive again */
            p_recv_end_desc->rd0 &= (RD0_RACT | RD0_RDLE);
            p_recv_end_desc->rd0 |= RD0_RACT;
            if ((start_stop == 1) && ((ETHEREDRRR0 & EDRRR0_RR) == 0)) {
                ETHEREDRRR0 |= EDRRR0_RR;
            }
            p_recv_end_desc = NULL;
        }

        p_recv_desc = &p_eth_desc_drecv[recv_top_index];   /* Current descriptor */
        if ((p_recv_desc->rd0 & RD0_RACT) == 0) {
            /* Receives 1 frame */
            if (((p_recv_desc->rd0 & RD0_RFE) != 0) && ((p_recv_desc->rd0 & RD0_RFS_ERROR) != 0)) {
                /* Receive frame error */
                /* Sets the receive descriptor to receive again */
                p_recv_desc->rd0 &= (RD0_RACT | RD0_RDLE);
                p_recv_desc->rd0 |= RD0_RACT;
                if ((start_stop == 1) && ((ETHEREDRRR0 & EDRRR0_RR) == 0)) {
                    ETHEREDRRR0 |= EDRRR0_RR;
                }
            } else {
                /* Copies the received frame */
                rx_read_offset  = 0;
                p_recv_end_desc = p_recv_desc;
                receive_size    = (p_recv_desc->rd1 & RD1_RDL_MSK);    /* number of bytes received */
            }

            /* Update the current descriptor */
            recv_top_index++;
            if (recv_top_index >= NUM_OF_TX_DESCRIPTOR) {
                recv_top_index = 0;
            }
        }
    }

    return receive_size;
}

int ethernet_read(char *data, int dlen) {
    edmac_recv_desc_t *p_recv_desc = p_recv_end_desc;                   /* Read top descriptor */
    int32_t           copy_size;

    if ((data == NULL) || (dlen < 0) || (p_recv_desc == NULL)) {
        copy_size = 0;
    } else {
        copy_size = (p_recv_desc->rd1 & RD1_RDL_MSK) - rx_read_offset;
        if (copy_size > dlen) {
            copy_size = dlen;
        }
        (void)memcpy(data, &p_recv_desc->rd2[rx_read_offset], (size_t)copy_size);
        rx_read_offset += copy_size;
    }

    return copy_size;
}

void ethernet_address(char *mac) {
    if (mac != NULL) {
		mbed_mac_address(mac); /* Get MAC Address */
    }
}

int ethernet_link(void) {
    int32_t  ret;
    uint16_t data;

    data = phy_reg_read(BASIC_MODE_STATUS_REG);
    if (((uint32_t)data & BASIC_STS_MSK_LINK) != 0) {
        ret = 1;
    } else {
        ret = 0;
    }

    return ret;
}

void ethernet_set_link(int speed, int duplex) {
    uint16_t data;
    int32_t  i;
    int32_t  link;

    if ((speed < 0) || (speed > 1)) {
        data = 0x1000;      /* Auto-Negotiation Enable */
        phy_reg_write(BASIC_MODE_CONTROL_REG, data);
        data = phy_reg_read(BASIC_MODE_STATUS_REG);
        for (i = 0; i < 1000; i++) {
            if (((uint32_t)data & BASIC_STS_MSK_AUTO_CMP) != 0) {
                break;
            }
            wait_100us(10);
        }
    } else {
        data = (uint16_t)(((uint32_t)speed << 13) | ((uint32_t)duplex << 8));
        phy_reg_write(BASIC_MODE_CONTROL_REG, data);
        wait_100us(1);
    }

    link = ethernetext_chk_link_mode();
    ethernetext_set_link_mode(link);
}

void INT_Ether(void) {
    uint32_t stat_edmac;
    uint32_t stat_etherc;

    /* Clear the interrupt request flag */
    stat_edmac = (ETHEREESR0 & ETHEREESIPR0);       /* Targets are restricted to allowed interrupts */
    ETHEREESR0 = stat_edmac;
    /* Reception-related */
    if (stat_edmac & EDMAC_EESIPR_INI_RECV) {
        if (p_recv_cb_fnc != NULL) {
            p_recv_cb_fnc();
        }
    }
    /* E-MAC-related */
    if (stat_edmac & EDMAC_EESIPR_INI_EtherC) {
        /* Clear the interrupt request flag */
        stat_etherc = (ETHERECSR0 & ETHERECSIPR0);  /* Targets are restricted to allowed interrupts */
        ETHERECSR0  = stat_etherc;
    }
}

static void lan_reg_reset(void) {
    volatile int32_t j = 400;    /* Wait for B dia 256 cycles  ((I dia/B dia)*256)/6cyc = 8*256/6 = 342 */

    ETHERARSTR      |= 0x00000001;      /* ETHER software reset */
    while (j--) {
        /* Do Nothing */
    }

    ETHEREDSR0      |= 0x00000003;      /* E-DMAC software reset */
    ETHEREDMR0      |= 0x00000003;      /* Set SWRR and SWRT simultaneously */

    /* Check clear software reset */
    while ((ETHEREDMR0 & 0x00000003) != 0) {
        /* Do Nothing */
    }
}

static void lan_desc_create(void) {
    int32_t i;
    uint8_t *p_memory_top;

    (void)memset((void *)ehernet_nc_memory, 0, sizeof(ehernet_nc_memory));
    p_memory_top = ehernet_nc_memory;

    /* Descriptor area configuration */
    p_eth_desc_dsend  = (edmac_send_desc_t *)p_memory_top;
    p_memory_top     += (sizeof(edmac_send_desc_t) * NUM_OF_TX_DESCRIPTOR);
    p_eth_desc_drecv  = (edmac_recv_desc_t *)p_memory_top;
    p_memory_top     += (sizeof(edmac_recv_desc_t) * NUM_OF_RX_DESCRIPTOR);

    /* Transmit descriptor */
    for (i = 0; i < NUM_OF_TX_DESCRIPTOR; i++) {
        p_eth_desc_dsend[i].td2  = p_memory_top;                     /* TD2 TBA */
        p_memory_top            += SIZE_OF_BUFFER;
        p_eth_desc_dsend[i].td1  = 0;                                /* TD1 TDL */
        p_eth_desc_dsend[i].td0  = TD0_TFP_TOP_BOTTOM;               /* TD0:1frame/1buf1buf, transmission disabled */
    }
    p_eth_desc_dsend[i - 1].td0 |= TD0_TDLE;                         /* Set the last descriptor */

    /* Receive descriptor */
    for (i = 0; i < NUM_OF_RX_DESCRIPTOR; i++) {
        p_eth_desc_drecv[i].rd2  = p_memory_top;                     /* RD2 RBA */
        p_memory_top            += SIZE_OF_BUFFER;
        p_eth_desc_drecv[i].rd1  = ((uint32_t)SIZE_OF_BUFFER << 16); /* RD1 RBL */
        p_eth_desc_drecv[i].rd0  = RD0_RACT;                         /* RD0:reception enabled */
    }
    p_eth_desc_drecv[i - 1].rd0 |= RD0_RDLE;                         /* Set the last descriptor */

    /* Initialize descriptor management information */
    send_top_index  = 0;
    recv_top_index  = 0;
    rx_read_offset  = 0;
    tx_wite_offset  = 0;
    p_recv_end_desc = NULL;
}

static void lan_reg_set(int32_t link) {
    /* MAC address setting */
    ETHERMAHR0      = ((uint32_t)mac_addr[0] << 24)
                    | ((uint32_t)mac_addr[1] << 16)
                    | ((uint32_t)mac_addr[2] << 8)
                    |  (uint32_t)mac_addr[3];
    ETHERMALR0      = ((uint32_t)mac_addr[4] << 8)
                    |  (uint32_t)mac_addr[5];

    /* E-DMAC */
    ETHERTDLAR0     = (uint32_t)&p_eth_desc_dsend[0];
    ETHERRDLAR0     = (uint32_t)&p_eth_desc_drecv[0];
    ETHERTDFAR0     = (uint32_t)&p_eth_desc_dsend[0];
    ETHERRDFAR0     = (uint32_t)&p_eth_desc_drecv[0];
    ETHERTDFXR0     = (uint32_t)&p_eth_desc_dsend[NUM_OF_TX_DESCRIPTOR - 1];
    ETHERRDFXR0     = (uint32_t)&p_eth_desc_drecv[NUM_OF_RX_DESCRIPTOR - 1];
    ETHERTDFFR0    |=  0x00000001;      /* TDLF  Transmit Descriptor Queue Last Flag : Last descriptor (1) */
    ETHERRDFFR0    |=  0x00000001;      /* RDLF  Receive Descriptor Queue Last Flag : Last descriptor (1) */
    ETHEREDMR0     |=  0x00000040;      /* Little endian */
    ETHERTRSCER0   &= ~0x0003009F;      /* All clear */
    ETHERTFTR0     &= ~0x000007FF;      /* TFT[10:0]  Transmit FIFO Threshold : Store and forward modes (H'000) */
    ETHERFDR0      |=  0x00000707;      /* Transmit FIFO Size:2048 bytes, Receive FIFO Size:2048 bytes */
    ETHERRMCR0     |=  0x00000001;      /* RNC  Receive Enable Control : Continuous reception enabled (1) */
    ETHERFCFTR0    &= ~0x001F00FF;
    ETHERFCFTR0    |=  0x00070007;
    ETHERRPADIR0   &= ~0x001FFFFF;      /* Padding Size:No padding insertion, Padding Slot:Inserts at first byte */

    /* E-MAC */
    ETHERECMR0     &= ~0x04BF2063;      /* All clear */
    ETHERRFLR0     &= ~0x0003FFFF;      /* RFL[17:0]  Receive Frame Length : 1518 bytes (H'00000) */
    ETHERAPR0      &= ~0x0000FFFF;      /* AP[15:0]   Automatic PAUSE : Flow control is disabled (H'0000) */
    ETHERMPR0      &= ~0x0000FFFF;      /* MP[15:0]   Manual PAUSE : Flow control is disabled (H'0000) */
    ETHERTPAUSER0  &= ~0x0000FFFF;      /* Upper Limit for Automatic PAUSE Frame : Retransmit count is unlimited */
    ETHERCSMR      &= ~0xC000003F;      /* The result of checksum is not written back to the receive descriptor */
    if ((link == FULL_TX) || (link == FULL_10M) || (link == NEGO_FAIL)) {
        ETHERECMR0 |= 0x00000002;       /* Set to full-duplex mode */
    } else {
        ETHERECMR0 &= ~0x00000002;      /* Set to half-duplex mode */
    }

    /* Interrupt-related */
    if (p_recv_cb_fnc != NULL) {
        ETHEREESR0     |=  0xFF7F009F;                     /* Clear all status (by writing 1) */
        ETHEREESIPR0   |=  0x00040000;                     /* FR  Frame Reception (1) */
        ETHERECSR0     |=  0x00000011;                     /* Clear all status (clear by writing 1) */
        ETHERECSIPR0   &= ~0x00000011;                     /* PFROIP Disable, ICDIP Disable */
        InterruptHandlerRegister(ETHERI_IRQn, INT_Ether);  /* Ethernet interrupt handler registration */
        GIC_SetPriority(ETHERI_IRQn, Interrupt_priority);  /* Ethernet interrupt priority */
        GIC_EnableIRQ(ETHERI_IRQn);                        /* Enables the E-DMAC interrupt */
    }

    ETHERECMR0     |=  0x00000060;      /* RE Enable, TE Enable */

    /* Enable transmission/reception */
    if ((start_stop == 1) && ((ETHEREDRRR0 & 0x00000001) == 0)) {
        ETHEREDRRR0 |= 0x00000001;       /* RR */
    }
}

static uint16_t phy_reg_read(uint16_t reg_addr) {
    uint16_t data;

    mii_preamble();
    mii_cmd(reg_addr, PHY_READ);
    mii_z();
    mii_reg_read(&data);
    mii_z();

    return data;
}

static void phy_reg_write(uint16_t reg_addr, uint16_t data) {
    mii_preamble();
    mii_cmd(reg_addr, PHY_WRITE);
    mii_write_1();
    mii_write_0();
    mii_reg_write(data);
    mii_z();
}

static void mii_preamble(void) {
    int32_t i = 32;

    for (i = 32; i > 0; i--) {
        /* 1 is output via the MII (Media Independent Interface) block. */
        mii_write_1();
    }
}

static void mii_cmd(uint16_t reg_addr, uint32_t option) {
    int32_t  i;
    uint16_t data = 0;

    data |= (PHY_ST << 14);             /* ST code      */
    data |= (option << 12);             /* OP code      */
    data |= (PHY_ADDR << 7);            /* PHY Address  */
    data |= (uint16_t)(reg_addr << 2);  /* Reg Address  */
    for (i = 14; i > 0; i--) {
        if ((data & 0x8000) == 0) {
            mii_write_0();
        } else {
            mii_write_1();
        }
        data <<= 1;
    }
}

static void mii_reg_read(uint16_t *data) {
    int32_t  i;
    uint16_t reg_data = 0;

    /* Data are read in one bit at a time */
    for (i = 16; i > 0; i--) {
        set_ether_pir(PIR0_MDC_LOW);
        set_ether_pir(PIR0_MDC_HIGH);
        reg_data <<= 1;
        reg_data |= (uint16_t)((ETHERPIR0 & PIR0_MDI) >> 3);  /* MDI read */
        set_ether_pir(PIR0_MDC_HIGH);
        set_ether_pir(PIR0_MDC_LOW);
    }
    *data = reg_data;
}

static void mii_reg_write(uint16_t data) {
    int32_t i;

    /* Data are written one bit at a time */
    for (i = 16; i > 0; i--) {
        if ((data & 0x8000) == 0) {
            mii_write_0();
        } else {
            mii_write_1();
        }
        data <<= 1;
    }
}

static void mii_z(void) {
    set_ether_pir(PIR0_MDC_LOW);
    set_ether_pir(PIR0_MDC_HIGH);
    set_ether_pir(PIR0_MDC_HIGH);
    set_ether_pir(PIR0_MDC_LOW);
}

static void mii_write_1(void) {
    set_ether_pir(PIR0_MDO | PIR0_MMD);
    set_ether_pir(PIR0_MDO | PIR0_MMD | PIR0_MDC);
    set_ether_pir(PIR0_MDO | PIR0_MMD | PIR0_MDC);
    set_ether_pir(PIR0_MDO | PIR0_MMD);
}

static void mii_write_0(void) {
    set_ether_pir(PIR0_MMD);
    set_ether_pir(PIR0_MMD | PIR0_MDC);
    set_ether_pir(PIR0_MMD | PIR0_MDC);
    set_ether_pir(PIR0_MMD);
}

static void set_ether_pir(uint32_t set_data) {
    int32_t i;

    for (i = MDC_WAIT; i > 0; i--) {
        ETHERPIR0 = set_data;
    }
}

static void wait_100us(int32_t wait_cnt) {
    volatile int32_t j = LOOP_100us * wait_cnt;

    while (--j) {
        /* Do Nothing */
    }
}
