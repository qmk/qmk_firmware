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
#include "can_api.h"

#include "cmsis.h"
#include "mbed_error.h"

#include <math.h>
#include <string.h>

/* Handy defines */
#define MSG_OBJ_MAX      32
#define DLC_MAX          8

#define ID_STD_MASK      0x07FF
#define ID_EXT_MASK      0x1FFFFFFF
#define DLC_MASK         0x0F

static uint32_t can_irq_id = 0;
static can_irq_handler irq_handler;

static uint32_t can_disable(can_t *obj) {
    uint32_t sm = LPC_CAN->CNTL;
    LPC_CAN->CNTL |= CANCNTL_INIT;
    return sm;
}

static inline void can_enable(can_t *obj) {
    if (LPC_CAN->CNTL & CANCNTL_INIT) {
        LPC_CAN->CNTL &= ~CANCNTL_INIT;
    }
}

int can_mode(can_t *obj, CanMode mode) {
    return 0; // not implemented
}

int can_filter(can_t *obj, uint32_t id, uint32_t mask, CANFormat format, int32_t handle) {
    uint16_t i;

    // Find first free message object
    if(handle == 0) {
        uint32_t msgval = LPC_CAN->MSGV1 | (LPC_CAN->MSGV2 << 16);
        // Find first free messagebox
        for(i = 0; i < 32; i++) {
            if((msgval & (1 << i)) == 0) {
                handle = i+1;
                break;
            }
        }
    }
    
    if(handle > 0 && handle < 32) {
        if(format == CANExtended) {
            // Mark message valid, Direction = TX, Extended Frame, Set Identifier and mask everything
            LPC_CAN->IF1_ARB1 = BFN_PREP(id, CANIFn_ARB1_ID);
            LPC_CAN->IF1_ARB2 = CANIFn_ARB2_MSGVAL | CANIFn_ARB2_XTD | BFN_PREP(id >> 16, CANIFn_ARB2_ID);
            LPC_CAN->IF1_MSK1 = BFN_PREP(mask, CANIFn_MSK1_MSK);
            LPC_CAN->IF1_MSK2 = CANIFn_MSK2_MXTD /* | CANIFn_MSK2_MDIR */ | BFN_PREP(mask >> 16, CANIFn_MSK2_MSK);
        }
        else {
            // Mark message valid, Direction = TX, Set Identifier and mask everything
            LPC_CAN->IF1_ARB2 = CANIFn_ARB2_MSGVAL | BFN_PREP(id << 2, CANIFn_ARB2_ID);
            LPC_CAN->IF1_MSK2 = /* CANIFn_MSK2_MDIR | */ BFN_PREP(mask << 2, CANIFn_MSK2_MSK);
        }
        
        // Use mask, single message object and set DLC
        LPC_CAN->IF1_MCTRL = CANIFn_MCTRL_UMASK | CANIFn_MCTRL_EOB | CANIFn_MCTRL_RXIE | BFN_PREP(DLC_MAX, CANIFn_MCTRL_DLC);

        // Transfer all fields to message object
        LPC_CAN->IF1_CMDMSK = CANIFn_CMDMSK_WR | CANIFn_CMDMSK_MASK | CANIFn_CMDMSK_ARB | CANIFn_CMDMSK_CTRL;
        
        // Start Transfer to given message number
        LPC_CAN->IF1_CMDREQ = BFN_PREP(handle, CANIFn_CMDREQ_MN);
        
        // Wait until transfer to message ram complete - TODO: maybe not block??
        while( LPC_CAN->IF1_CMDREQ & CANIFn_CMDREQ_BUSY );
    }
    
    return handle;
}

static inline void can_irq() {
    irq_handler(can_irq_id, IRQ_RX);
}

// Register CAN object's irq handler
void can_irq_init(can_t *obj, can_irq_handler handler, uint32_t id) {
    irq_handler = handler;
    can_irq_id = id;
}

// Unregister CAN object's irq handler
void can_irq_free(can_t *obj) {
        LPC_CAN->CNTL &= ~CANCNTL_IE; // Disable Interrupts :)

    can_irq_id = 0;
    NVIC_DisableIRQ(CAN_IRQn);
}

// Clear or set a irq
void can_irq_set(can_t *obj, CanIrqType type, uint32_t enable) {
    // Put CAN in Reset Mode and enable interrupt
    can_disable(obj);
    if(enable == 0) {
        LPC_CAN->CNTL &= ~(CANCNTL_IE | CANCNTL_SIE);
    }
    else {
        LPC_CAN->CNTL |= CANCNTL_IE | CANCNTL_SIE;
    }
    // Take it out of reset...
    can_enable(obj);
    
    // Enable NVIC if at least 1 interrupt is active
    NVIC_SetVector(CAN_IRQn, (uint32_t) &can_irq);
    NVIC_EnableIRQ(CAN_IRQn);
}

// This table has the sampling points as close to 75% as possible. The first
// value is TSEG1, the second TSEG2.
static const int timing_pts[23][2] = {
    {0x0, 0x0},      // 2,  50%
    {0x1, 0x0},      // 3,  67%
    {0x2, 0x0},      // 4,  75%
    {0x3, 0x0},      // 5,  80%
    {0x3, 0x1},      // 6,  67%
    {0x4, 0x1},      // 7,  71%
    {0x5, 0x1},      // 8,  75%
    {0x6, 0x1},      // 9,  78%
    {0x6, 0x2},      // 10, 70%
    {0x7, 0x2},      // 11, 73%
    {0x8, 0x2},      // 12, 75%
    {0x9, 0x2},      // 13, 77%
    {0x9, 0x3},      // 14, 71%
    {0xA, 0x3},      // 15, 73%
    {0xB, 0x3},      // 16, 75%
    {0xC, 0x3},      // 17, 76%
    {0xD, 0x3},      // 18, 78%
    {0xD, 0x4},      // 19, 74%
    {0xE, 0x4},      // 20, 75%
    {0xF, 0x4},      // 21, 76%
    {0xF, 0x5},      // 22, 73%
    {0xF, 0x6},      // 23, 70%
    {0xF, 0x7},      // 24, 67%
};

static unsigned int can_speed(unsigned int sclk, unsigned int cclk, unsigned char psjw) {
    uint32_t    btr;
    uint32_t    clkdiv = 1;
    uint16_t    brp = 0;
    uint32_t    calcbit;
    uint32_t    bitwidth;
    int         hit = 0;
    int         bits = 0;
    
    bitwidth = sclk / cclk;
    
    brp = bitwidth / 0x18;
    while ((!hit) && (brp < bitwidth / 4)) {
        brp++;
        for (bits = 22; bits > 0; bits--) {
            calcbit = (bits + 3) * (brp + 1);
            if (calcbit == bitwidth) {
                hit = 1;
                break;
            }
        }
    }
    
    /* This might be funky
    while(btr > 63 && clkdiv < 16) {
        btr = btr / 2;
        clkdiv = clkdiv * 2;
    }
    */
    clkdiv = clkdiv - 1;
        
    if (hit) {
        btr = BFN_PREP(timing_pts[bits][1], CANBT_TSEG2)
            | BFN_PREP(timing_pts[bits][0], CANBT_TSEG1)
            | BFN_PREP(psjw, CANBT_SJW)
            | BFN_PREP(brp, CANBT_BRP);
        btr = btr | (clkdiv << 16);
                
    } else {
        btr = 0;
    }
    
    return btr;
}


int can_config_rxmsgobj(can_t *obj) {
    uint16_t i = 0;

    // Make sure the interface is available
    //while( LPC_CAN->IF1_CMDREQ & CANIFn_CMDREQ_BUSY );

    // Mark message valid, Direction = RX, Don't care about anything else
    LPC_CAN->IF1_ARB1 = 0;
    LPC_CAN->IF1_ARB2 = 0;
    LPC_CAN->IF1_MCTRL = 0;

    for ( i = 0; i < MSG_OBJ_MAX; i++ )
    {
        // Transfer arb and control fields to message object
        LPC_CAN->IF1_CMDMSK = CANIFn_CMDMSK_WR | CANIFn_CMDMSK_ARB | CANIFn_CMDMSK_CTRL | CANIFn_CMDMSK_TXRQST;
        
        // Start Transfer to given message number
        LPC_CAN->IF1_CMDREQ = BFN_PREP(i, CANIFn_CMDREQ_MN);
        
        // Wait until transfer to message ram complete - TODO: maybe not block??
        while( LPC_CAN->IF1_CMDREQ & CANIFn_CMDREQ_BUSY );
    }
    
    // Accept all messages
    can_filter(obj, 0, 0, CANStandard, 1);
    
    return 1;
}


void can_init(can_t *obj, PinName rd, PinName td) {
    // Enable power and clock
    LPC_SYSCON->PRESETCTRL |= PRESETCTRL_CAN_RST_N;
    LPC_SYSCON->SYSAHBCLKCTRL |= SYSAHBCLKCTRL_CAN;
    
    // Enable Initialization mode
    if (!(LPC_CAN->CNTL & CANCNTL_INIT)) {
        LPC_CAN->CNTL |= CANCNTL_INIT;
    }
    
    can_frequency(obj, 125000);
    
    // Resume operation
    LPC_CAN->CNTL &= ~CANCNTL_INIT;
    while ( LPC_CAN->CNTL & CANCNTL_INIT );
    
    // Initialize RX message object
    can_config_rxmsgobj(obj);
}

void can_free(can_t *obj) {
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(SYSAHBCLKCTRL_CAN);
    LPC_SYSCON->PRESETCTRL &= ~(PRESETCTRL_CAN_RST_N);
}

int can_frequency(can_t *obj, int f) {
    int btr = can_speed(SystemCoreClock, (unsigned int)f, 1);
    int clkdiv = (btr >> 16) & 0x0F;
    btr = btr & 0xFFFF;
    
    if (btr > 0) {
        uint32_t cntl_init = LPC_CAN->CNTL | CANCNTL_INIT;
        // Set the bit clock
        LPC_CAN->CNTL |= CANCNTL_CCE | CANCNTL_INIT;
        LPC_CAN->CLKDIV = clkdiv;
        LPC_CAN->BT = btr;
        LPC_CAN->BRPE = 0x0000;
        LPC_CAN->CNTL &= ~(CANCNTL_CCE | CANCNTL_INIT);
        LPC_CAN->CNTL |= cntl_init;
        return 1;
    }
    return 0;
}

int can_write(can_t *obj, CAN_Message msg, int cc) {
    uint16_t msgnum = 0;
    
    // Make sure controller is enabled
    can_enable(obj);
    
    // Make sure the interface is available
    while( LPC_CAN->IF1_CMDREQ & CANIFn_CMDREQ_BUSY );

    // Set the direction bit based on the message type
    uint32_t direction = 0;
    if (msg.type == CANData) {
        direction = CANIFn_ARB2_DIR;
    }

    if(msg.format == CANExtended)    {
        // Mark message valid, Extended Frame, Set Identifier and mask everything
        LPC_CAN->IF1_ARB1 = BFN_PREP(msg.id, CANIFn_ARB1_ID);
        LPC_CAN->IF1_ARB2 = CANIFn_ARB2_MSGVAL | CANIFn_ARB2_XTD | direction | BFN_PREP(msg.id >> 16, CANIFn_ARB2_ID);
        LPC_CAN->IF1_MSK1 = BFN_PREP(ID_EXT_MASK, CANIFn_MSK1_MSK);
        LPC_CAN->IF1_MSK2 = CANIFn_MSK2_MXTD | CANIFn_MSK2_MDIR | BFN_PREP(ID_EXT_MASK >> 16, CANIFn_MSK2_MSK);
    }
    else {
        // Mark message valid, Set Identifier and mask everything
        LPC_CAN->IF1_ARB2 = CANIFn_ARB2_MSGVAL | direction | BFN_PREP(msg.id << 2, CANIFn_ARB2_ID);
        LPC_CAN->IF1_MSK2 = CANIFn_MSK2_MDIR | BFN_PREP(ID_STD_MASK << 2, CANIFn_MSK2_MSK);
    }
    
    // Use mask, request transmission, single message object and set DLC
    LPC_CAN->IF1_MCTRL = CANIFn_MCTRL_UMASK | CANIFn_MCTRL_TXRQST | CANIFn_MCTRL_EOB | BFN_PREP(msg.len, CANIFn_MCTRL_DLC);

    LPC_CAN->IF1_DA1 = BFN_PREP(msg.data[1], CANIFn_DA1_DATA1) | BFN_PREP(msg.data[0], CANIFn_DA1_DATA0);
    LPC_CAN->IF1_DA2 = BFN_PREP(msg.data[3], CANIFn_DA2_DATA3) | BFN_PREP(msg.data[2], CANIFn_DA2_DATA2);
    LPC_CAN->IF1_DB1 = BFN_PREP(msg.data[5], CANIFn_DB1_DATA5) | BFN_PREP(msg.data[4], CANIFn_DB1_DATA4);
    LPC_CAN->IF1_DB2 = BFN_PREP(msg.data[7], CANIFn_DB2_DATA7) | BFN_PREP(msg.data[6], CANIFn_DB2_DATA6);

    // Transfer all fields to message object
    LPC_CAN->IF1_CMDMSK = CANIFn_CMDMSK_WR | CANIFn_CMDMSK_MASK | CANIFn_CMDMSK_ARB | CANIFn_CMDMSK_CTRL | CANIFn_CMDMSK_TXRQST | CANIFn_CMDMSK_DATA_A | CANIFn_CMDMSK_DATA_B;
    
    // Start Transfer to given message number
    LPC_CAN->IF1_CMDREQ = BFN_PREP(msgnum, CANIFn_CMDREQ_MN);
    
    // Wait until transfer to message ram complete - TODO: maybe not block??
    while( LPC_CAN->IF1_CMDREQ & CANIFn_CMDREQ_BUSY);
    
    // Wait until TXOK is set, then clear it - TODO: maybe not block
    //while( !(LPC_CAN->STAT & CANSTAT_TXOK) );
    LPC_CAN->STAT &= ~(CANSTAT_TXOK);
    
    return 1;
}

int can_read(can_t *obj, CAN_Message *msg, int handle) {
    uint16_t i;
    
    // Make sure controller is enabled
    can_enable(obj);
    
    // Find first message object with new data
    if(handle == 0) {
        uint32_t newdata = LPC_CAN->ND1 | (LPC_CAN->ND2 << 16);
        // Find first free messagebox
        for(i = 0; i < 32; i++) {
            if(newdata & (1 << i)) {
                handle = i+1;
                break;
            }
        }
    }
    
    if(handle > 0 && handle < 32) {
        // Wait until message interface is free
        while( LPC_CAN->IF2_CMDREQ & CANIFn_CMDREQ_BUSY );

        // Transfer all fields to message object
        LPC_CAN->IF2_CMDMSK = CANIFn_CMDMSK_RD | CANIFn_CMDMSK_MASK | CANIFn_CMDMSK_ARB | CANIFn_CMDMSK_CTRL | CANIFn_CMDMSK_CLRINTPND | CANIFn_CMDMSK_TXRQST | CANIFn_CMDMSK_DATA_A | CANIFn_CMDMSK_DATA_B;
        
        // Start Transfer from given message number
        LPC_CAN->IF2_CMDREQ = BFN_PREP(handle, CANIFn_CMDREQ_MN);
        
        // Wait until transfer to message ram complete
        while( LPC_CAN->IF2_CMDREQ & CANIFn_CMDREQ_BUSY );
                    
        if (LPC_CAN->IF2_ARB2 & CANIFn_ARB2_XTD) {
            msg->format = CANExtended;
            msg->id = (LPC_CAN->IF2_ARB1 & CANIFn_ARB2_ID_MASK) << 16;
            msg->id |= (LPC_CAN->IF2_ARB2 & CANIFn_ARB2_ID_MASK);
        }
        else {
            msg->format = CANStandard;
            msg->id = (LPC_CAN->IF2_ARB2 & CANIFn_ARB2_ID_MASK) >> 2;
        }

        if (LPC_CAN->IF2_ARB2 & CANIFn_ARB2_DIR) {
            msg->type   = CANRemote;
        }
        else {
            msg->type   = CANData;
        }

        msg->len        = BFN_GET(LPC_CAN->IF2_MCTRL, CANIFn_MCTRL_DLC); // TODO: If > 8, len = 8
        msg->data[0]    = BFN_GET(LPC_CAN->IF2_DA1, CANIFn_DA1_DATA0);
        msg->data[1]    = BFN_GET(LPC_CAN->IF2_DA1, CANIFn_DA1_DATA1);
        msg->data[2]    = BFN_GET(LPC_CAN->IF2_DA2, CANIFn_DA2_DATA2);
        msg->data[3]    = BFN_GET(LPC_CAN->IF2_DA2, CANIFn_DA2_DATA3);
        msg->data[4]    = BFN_GET(LPC_CAN->IF2_DB1, CANIFn_DB1_DATA4);
        msg->data[5]    = BFN_GET(LPC_CAN->IF2_DB1, CANIFn_DB1_DATA5);
        msg->data[6]    = BFN_GET(LPC_CAN->IF2_DB2, CANIFn_DB2_DATA6);
        msg->data[7]    = BFN_GET(LPC_CAN->IF2_DB2, CANIFn_DB2_DATA7);
        
        LPC_CAN->STAT &= ~(CANSTAT_RXOK);
        return 1;
    }

    return 0;
}

void can_reset(can_t *obj) {
    LPC_SYSCON->PRESETCTRL &= ~PRESETCTRL_CAN_RST_N;
    LPC_CAN->STAT = 0;
    
    can_config_rxmsgobj(obj);
}

unsigned char can_rderror(can_t *obj) {
    return BFN_GET(LPC_CAN->EC, CANEC_REC);
}

unsigned char can_tderror(can_t *obj) {
    return BFN_GET(LPC_CAN->EC, CANEC_TEC);
}

void can_monitor(can_t *obj, int silent) {
    if (silent) {
        LPC_CAN->CNTL |= CANCNTL_TEST;
        LPC_CAN->TEST |= CANTEST_SILENT;
    } else {
        LPC_CAN->CNTL &= ~(CANCNTL_TEST);
        LPC_CAN->TEST &= ~CANTEST_SILENT;
    }

    if (!(LPC_CAN->CNTL & CANCNTL_INIT)) {
        LPC_CAN->CNTL |= CANCNTL_INIT;
    }
}
