/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "arm_atsam_protocol.h"

#if !defined(MD_BOOTLOADER) && defined(RGB_MATRIX_ENABLE)

#    include <string.h>

// From keyboard
#    include "config.h"
#    include "config_led.h"
#    include "matrix.h"

#    define I2C_LED_USE_DMA 1  // Set 1 to use background DMA transfers for leds, Set 0 to use inline software transfers

DmacDescriptor dmac_desc;
DmacDescriptor dmac_desc_wb;

static uint8_t i2c_led_q[I2C_Q_SIZE];  // I2C queue circular buffer
static uint8_t i2c_led_q_s;            // Start of circular buffer
static uint8_t i2c_led_q_e;            // End of circular buffer
static uint8_t i2c_led_q_full;         // Queue full counter for reset

static uint8_t dma_sendbuf[I2C_DMA_MAX_SEND];  // Data being written to I2C

volatile uint8_t i2c_led_q_running;

#endif  // !defined(MD_BOOTLOADER) && defined(RGB_MATRIX_ENABLE)

void i2c0_init(void) {
    DBGC(DC_I2C0_INIT_BEGIN);

    CLK_set_i2c0_freq(CHAN_SERCOM_I2C0, FREQ_I2C0_DEFAULT);

    // MCU
    PORT->Group[0].PMUX[4].bit.PMUXE    = 2;
    PORT->Group[0].PMUX[4].bit.PMUXO    = 2;
    PORT->Group[0].PINCFG[8].bit.PMUXEN = 1;
    PORT->Group[0].PINCFG[9].bit.PMUXEN = 1;

    // I2C
    // Note: SW Reset handled in CLK_set_i2c0_freq clks.c

    SERCOM0->I2CM.CTRLA.bit.MODE = 5;  // Set master mode

    SERCOM0->I2CM.CTRLA.bit.SPEED    = 0;  // Set to 1 for Fast-mode Plus (FM+) up to 1 MHz
    SERCOM0->I2CM.CTRLA.bit.RUNSTDBY = 1;  // Enabled

    SERCOM0->I2CM.CTRLA.bit.ENABLE = 1;  // Enable the device
    while (SERCOM0->I2CM.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_I2C0_INIT_SYNC_ENABLING);
    }  // Wait for SYNCBUSY.ENABLE to clear

    SERCOM0->I2CM.STATUS.bit.BUSSTATE = 1;  // Force into IDLE state
    while (SERCOM0->I2CM.SYNCBUSY.bit.SYSOP) {
        DBGC(DC_I2C0_INIT_SYNC_SYSOP);
    }
    while (SERCOM0->I2CM.STATUS.bit.BUSSTATE != 1) {
        DBGC(DC_I2C0_INIT_WAIT_IDLE);
    }  // Wait while not idle

    DBGC(DC_I2C0_INIT_COMPLETE);
}

uint8_t i2c0_start(uint8_t address) {
    SERCOM0->I2CM.ADDR.bit.ADDR = address;
    while (SERCOM0->I2CM.SYNCBUSY.bit.SYSOP) {
    }
    while (SERCOM0->I2CM.INTFLAG.bit.MB == 0) {
    }
    while (SERCOM0->I2CM.STATUS.bit.RXNACK) {
    }

    return 1;
}

uint8_t i2c0_transmit(uint8_t address, uint8_t *data, uint16_t length, uint16_t timeout) {
    if (!length) return 0;

    i2c0_start(address);

    while (length) {
        SERCOM0->I2CM.DATA.bit.DATA = *data;
        while (SERCOM0->I2CM.INTFLAG.bit.MB == 0) {
        }
        while (SERCOM0->I2CM.STATUS.bit.RXNACK) {
        }

        data++;
        length--;
    }

    i2c0_stop();

    return 1;
}

void i2c0_stop(void) {
    if (SERCOM0->I2CM.STATUS.bit.CLKHOLD || SERCOM0->I2CM.INTFLAG.bit.MB == 1 || SERCOM0->I2CM.STATUS.bit.BUSSTATE != 1) {
        SERCOM0->I2CM.CTRLB.bit.CMD = 3;
        while (SERCOM0->I2CM.SYNCBUSY.bit.SYSOP)
            ;
        while (SERCOM0->I2CM.STATUS.bit.CLKHOLD)
            ;
        while (SERCOM0->I2CM.INTFLAG.bit.MB)
            ;
        while (SERCOM0->I2CM.STATUS.bit.BUSSTATE != 1)
            ;
    }
}

#if !defined(MD_BOOTLOADER) && defined(RGB_MATRIX_ENABLE)
void i2c1_init(void) {
    DBGC(DC_I2C1_INIT_BEGIN);

    CLK_set_i2c1_freq(CHAN_SERCOM_I2C1, FREQ_I2C1_DEFAULT);

    /* MCU */
    PORT->Group[0].PMUX[8].bit.PMUXE     = 2;
    PORT->Group[0].PMUX[8].bit.PMUXO     = 2;
    PORT->Group[0].PINCFG[16].bit.PMUXEN = 1;
    PORT->Group[0].PINCFG[17].bit.PMUXEN = 1;

    /* I2C */
    // Note: SW Reset handled in CLK_set_i2c1_freq clks.c

    SERCOM1->I2CM.CTRLA.bit.MODE     = 5;  // MODE: Set master mode (No sync)
    SERCOM1->I2CM.CTRLA.bit.SPEED    = 1;  // SPEED: Fm+ up to 1MHz (No sync)
    SERCOM1->I2CM.CTRLA.bit.RUNSTDBY = 1;  // RUNSTBY: Enabled (No sync)

    SERCOM1->I2CM.CTRLB.bit.SMEN = 1;  // SMEN: Smart mode enabled (For DMA)(No sync)

    NVIC_EnableIRQ(SERCOM1_0_IRQn);
    SERCOM1->I2CM.INTENSET.bit.ERROR = 1;

    SERCOM1->I2CM.CTRLA.bit.ENABLE = 1;  // ENABLE: Enable the device (sync SYNCBUSY.ENABLE)
    while (SERCOM1->I2CM.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_I2C1_INIT_SYNC_ENABLING);
    }  // Wait for SYNCBUSY.ENABLE to clear

    SERCOM1->I2CM.STATUS.bit.BUSSTATE = 1;  // BUSSTATE: Force into IDLE state (sync SYNCBUSY.SYSOP)
    while (SERCOM1->I2CM.SYNCBUSY.bit.SYSOP) {
        DBGC(DC_I2C1_INIT_SYNC_SYSOP);
    }
    while (SERCOM1->I2CM.STATUS.bit.BUSSTATE != 1) {
        DBGC(DC_I2C1_INIT_WAIT_IDLE);
    }  // Wait while not idle

    DBGC(DC_I2C1_INIT_COMPLETE);
}

uint8_t i2c1_start(uint8_t address) {
    SERCOM1->I2CM.ADDR.bit.ADDR = address;
    while (SERCOM1->I2CM.SYNCBUSY.bit.SYSOP) {
    }
    while (SERCOM1->I2CM.INTFLAG.bit.MB == 0) {
    }
    while (SERCOM1->I2CM.STATUS.bit.RXNACK) {
    }

    return 1;
}

uint8_t i2c1_transmit(uint8_t address, uint8_t *data, uint16_t length, uint16_t timeout) {
    if (!length) return 0;

    i2c1_start(address);

    while (length) {
        SERCOM1->I2CM.DATA.bit.DATA = *data;
        while (SERCOM1->I2CM.INTFLAG.bit.MB == 0) {
        }
        while (SERCOM1->I2CM.STATUS.bit.RXNACK) {
        }

        data++;
        length--;
    }

    i2c1_stop();

    return 1;
}

void i2c1_stop(void) {
    if (SERCOM1->I2CM.STATUS.bit.CLKHOLD || SERCOM1->I2CM.INTFLAG.bit.MB == 1 || SERCOM1->I2CM.STATUS.bit.BUSSTATE != 1) {
        SERCOM1->I2CM.CTRLB.bit.CMD = 3;
        while (SERCOM1->I2CM.SYNCBUSY.bit.SYSOP)
            ;
        while (SERCOM1->I2CM.STATUS.bit.CLKHOLD)
            ;
        while (SERCOM1->I2CM.INTFLAG.bit.MB)
            ;
        while (SERCOM1->I2CM.STATUS.bit.BUSSTATE != 1)
            ;
    }
}

void i2c_led_send_CRWL(uint8_t drvid) {
    uint8_t i2cdata[] = {ISSI3733_CMDRWL, ISSI3733_CMDRWL_WRITE_ENABLE_ONCE};
    i2c1_transmit(issidrv[drvid].addr, i2cdata, sizeof(i2cdata), 0);
}

void i2c_led_select_page(uint8_t drvid, uint8_t pageno) {
    uint8_t i2cdata[] = {ISSI3733_CMDR, pageno};
    i2c1_transmit(issidrv[drvid].addr, i2cdata, sizeof(i2cdata), 0);
}

void i2c_led_send_GCR(uint8_t drvid) {
    uint8_t i2cdata[] = {ISSI3733_GCCR, 0x00};

    if (gcr_actual > LED_GCR_MAX) gcr_actual = LED_GCR_MAX;
    i2cdata[1] = gcr_actual;

    i2c1_transmit(issidrv[drvid].addr, i2cdata, sizeof(i2cdata), 0);
}

void i2c_led_send_onoff(uint8_t drvid) {
#    if I2C_LED_USE_DMA != 1
    if (!i2c_led_q_running) {
#    endif
        i2c_led_send_CRWL(drvid);
        i2c_led_select_page(drvid, 0);
#    if I2C_LED_USE_DMA != 1
    }
#    endif

    *issidrv[drvid].onoff = 0;  // Force start location offset to zero
    i2c1_transmit(issidrv[drvid].addr, issidrv[drvid].onoff, ISSI3733_PG0_BYTES, 0);
}

void i2c_led_send_mode_op_gcr(uint8_t drvid, uint8_t mode, uint8_t operation) {
    uint8_t i2cdata[] = {ISSI3733_CR, mode | operation, gcr_actual};
    i2c1_transmit(issidrv[drvid].addr, i2cdata, sizeof(i2cdata), 0);
}

void i2c_led_send_pur_pdr(uint8_t drvid, uint8_t pur, uint8_t pdr) {
    uint8_t i2cdata[] = {ISSI3733_SWYR_PUR, pur, pdr};

    i2c1_transmit(issidrv[drvid].addr, i2cdata, sizeof(i2cdata), 0);
}

void i2c_led_send_pwm(uint8_t drvid) {
#    if I2C_LED_USE_DMA != 1
    if (!i2c_led_q_running) {
#    endif
        i2c_led_send_CRWL(drvid);
        i2c_led_select_page(drvid, 0);
#    if I2C_LED_USE_DMA != 1
    }
#    endif

    *issidrv[drvid].pwm = 0;  // Force start location offset to zero
    i2c1_transmit(issidrv[drvid].addr, issidrv[drvid].pwm, ISSI3733_PG1_BYTES, 0);
}

uint8_t I2C3733_Init_Control(void) {
    DBGC(DC_I2C3733_INIT_CONTROL_BEGIN);

    // Hardware state shutdown on boot
    // USB state machine will enable driver when communication is ready
    I2C3733_Control_Set(0);

    wait_ms(1);

    sr_exp_data.bit.IRST = 0;
    SR_EXP_WriteData();

    wait_ms(1);

    DBGC(DC_I2C3733_INIT_CONTROL_COMPLETE);

    return 1;
}

uint8_t I2C3733_Init_Drivers(void) {
    DBGC(DC_I2C3733_INIT_DRIVERS_BEGIN);

    gcr_actual      = ISSI3733_GCR_DEFAULT;
    gcr_actual_last = gcr_actual;

    if (gcr_actual > LED_GCR_MAX) gcr_actual = LED_GCR_MAX;
    gcr_desired = gcr_actual;

    // Set up master device
    i2c_led_send_CRWL(0);
    i2c_led_select_page(0, 3);
    i2c_led_send_mode_op_gcr(0, 0, ISSI3733_CR_SSD_NORMAL);  // No SYNC due to brightness mismatch with second driver

    // Set up slave device
    i2c_led_send_CRWL(1);
    i2c_led_select_page(1, 3);
    i2c_led_send_mode_op_gcr(1, 0, ISSI3733_CR_SSD_NORMAL);  // No SYNC due to brightness mismatch with first driver and slight flicker at rgb values 1,2

    i2c_led_send_CRWL(0);
    i2c_led_select_page(0, 3);
    i2c_led_send_pur_pdr(0, ISSI3733_SWYR_PUR_8000, ISSI3733_CSXR_PDR_8000);

    i2c_led_send_CRWL(1);
    i2c_led_select_page(1, 3);
    i2c_led_send_pur_pdr(1, ISSI3733_SWYR_PUR_8000, ISSI3733_CSXR_PDR_8000);

    DBGC(DC_I2C3733_INIT_DRIVERS_COMPLETE);

    return 1;
}

void I2C_DMAC_LED_Init(void) {
    Dmac *dmac = DMAC;

    DBGC(DC_I2C_DMAC_LED_INIT_BEGIN);

    // Disable device
    dmac->CTRL.bit.DMAENABLE = 0;  // Disable DMAC
    while (dmac->CTRL.bit.DMAENABLE) {
    }                          // Wait for disabled state in case of ongoing transfers
    dmac->CTRL.bit.SWRST = 1;  // Software Reset DMAC
    while (dmac->CTRL.bit.SWRST) {
    }  // Wait for software reset to complete

    // Configure device
    dmac->BASEADDR.reg = (uint32_t)&dmac_desc;     // Set descriptor base address
    dmac->WRBADDR.reg  = (uint32_t)&dmac_desc_wb;  // Set descriptor write back address
    dmac->CTRL.reg |= 0x0f00;                      // Handle all priorities (LVL0-3)

    // Disable channel
    dmac->Channel[0].CHCTRLA.bit.ENABLE = 0;  // Disable the channel
    while (dmac->Channel[0].CHCTRLA.bit.ENABLE) {
    }                                        // Wait for disabled state in case of ongoing transfers
    dmac->Channel[0].CHCTRLA.bit.SWRST = 1;  // Software Reset the channel
    while (dmac->Channel[0].CHCTRLA.bit.SWRST) {
    }  // Wait for software reset to complete

    // Configure channel
    dmac->Channel[0].CHCTRLA.bit.THRESHOLD = 0;                   // 1BEAT
    dmac->Channel[0].CHCTRLA.bit.BURSTLEN  = 0;                   // SINGLE
    dmac->Channel[0].CHCTRLA.bit.TRIGACT   = 2;                   // BURST
    dmac->Channel[0].CHCTRLA.bit.TRIGSRC   = SERCOM1_DMAC_ID_TX;  // Trigger source
    dmac->Channel[0].CHCTRLA.bit.RUNSTDBY  = 1;                   // Run in standby

    NVIC_EnableIRQ(DMAC_0_IRQn);
    dmac->Channel[0].CHINTENSET.bit.TCMPL = 1;
    dmac->Channel[0].CHINTENSET.bit.TERR  = 1;

    // Enable device
    dmac->CTRL.bit.DMAENABLE = 1;  // Enable DMAC
    while (dmac->CTRL.bit.DMAENABLE == 0) {
    }  // Wait for enable state

    DBGC(DC_I2C_DMAC_LED_INIT_COMPLETE);
}

// state = 1 enable
// state = 0 disable
void I2C3733_Control_Set(uint8_t state) {
    DBGC(DC_I2C3733_CONTROL_SET_BEGIN);

    sr_exp_data.bit.SDB_N = (state == 1 ? 1 : 0);
    SR_EXP_WriteData();

    DBGC(DC_I2C3733_CONTROL_SET_COMPLETE);
}

void i2c_led_desc_defaults(void) {
    dmac_desc.BTCTRL.bit.STEPSIZE = 0;  // SRCINC used in favor for auto 1 inc
    dmac_desc.BTCTRL.bit.STEPSEL  = 0;  // SRCINC used in favor for auto 1 inc
    dmac_desc.BTCTRL.bit.DSTINC   = 0;  // The Destination Address Increment is disabled
    dmac_desc.BTCTRL.bit.SRCINC   = 1;  // The Source Address Increment is enabled (Inc by 1)
    dmac_desc.BTCTRL.bit.BEATSIZE = 0;  // 8-bit bus transfer
    dmac_desc.BTCTRL.bit.BLOCKACT = 0;  // Channel will be disabled if it is the last block transfer in the transaction
    dmac_desc.BTCTRL.bit.EVOSEL   = 0;  // Event generation disabled
    dmac_desc.BTCTRL.bit.VALID    = 1;  // Set dmac valid
}

void i2c_led_prepare_send_dma(uint8_t *data, uint8_t len) {
    i2c_led_desc_defaults();

    dmac_desc.BTCNT.reg    = len;
    dmac_desc.SRCADDR.reg  = (uint32_t)data + len;
    dmac_desc.DSTADDR.reg  = (uint32_t)&SERCOM1->I2CM.DATA.reg;
    dmac_desc.DESCADDR.reg = 0;
}

void i2c_led_begin_dma(uint8_t drvid) {
    DMAC->Channel[0].CHCTRLA.bit.ENABLE = 1;  // Enable the channel

    SERCOM1->I2CM.ADDR.reg = (dmac_desc.BTCNT.reg << 16) | 0x2000 | issidrv[drvid].addr;  // Begin transfer
}

void i2c_led_send_CRWL_dma(uint8_t drvid) {
    *(dma_sendbuf + 0) = ISSI3733_CMDRWL;
    *(dma_sendbuf + 1) = ISSI3733_CMDRWL_WRITE_ENABLE_ONCE;
    i2c_led_prepare_send_dma(dma_sendbuf, 2);

    i2c_led_begin_dma(drvid);
}

void i2c_led_select_page_dma(uint8_t drvid, uint8_t pageno) {
    *(dma_sendbuf + 0) = ISSI3733_CMDR;
    *(dma_sendbuf + 1) = pageno;
    i2c_led_prepare_send_dma(dma_sendbuf, 2);

    i2c_led_begin_dma(drvid);
}

void i2c_led_send_GCR_dma(uint8_t drvid) {
    *(dma_sendbuf + 0) = ISSI3733_GCCR;
    *(dma_sendbuf + 1) = gcr_actual;
    i2c_led_prepare_send_dma(dma_sendbuf, 2);

    i2c_led_begin_dma(drvid);
}

void i2c_led_send_pwm_dma(uint8_t drvid) {
    // Note: This copies the CURRENT pwm buffer, which may be getting modified
    memcpy(dma_sendbuf, issidrv[drvid].pwm, ISSI3733_PG1_BYTES);
    *dma_sendbuf = 0;  // Force start location offset to zero
    i2c_led_prepare_send_dma(dma_sendbuf, ISSI3733_PG1_BYTES);

    i2c_led_begin_dma(drvid);
}

void i2c_led_send_onoff_dma(uint8_t drvid) {
    // Note: This copies the CURRENT onoff buffer, which may be getting modified
    memcpy(dma_sendbuf, issidrv[drvid].onoff, ISSI3733_PG0_BYTES);
    *dma_sendbuf = 0;  // Force start location offset to zero
    i2c_led_prepare_send_dma(dma_sendbuf, ISSI3733_PG0_BYTES);

    i2c_led_begin_dma(drvid);
}

void i2c_led_q_init(void) {
    memset(i2c_led_q, 0, I2C_Q_SIZE);
    i2c_led_q_s       = 0;
    i2c_led_q_e       = 0;
    i2c_led_q_running = 0;
    i2c_led_q_full    = 0;
}

uint8_t i2c_led_q_isempty(void) { return i2c_led_q_s == i2c_led_q_e; }

uint8_t i2c_led_q_size(void) { return (i2c_led_q_e - i2c_led_q_s) % I2C_Q_SIZE; }

uint8_t i2c_led_q_available(void) {
    return I2C_Q_SIZE - i2c_led_q_size() - 1;  // Never allow end to meet start
}

void i2c_led_q_add(uint8_t cmd) {
    // WARNING: Always request room before adding commands!

    // Assign command
    i2c_led_q[i2c_led_q_e] = cmd;

    i2c_led_q_e = (i2c_led_q_e + 1) % I2C_Q_SIZE;  // Move end up one or wrap
}

void i2c_led_q_s_advance(void) {
    i2c_led_q_s = (i2c_led_q_s + 1) % I2C_Q_SIZE;  // Move start up one or wrap
}

// Always request room before adding commands
// PS: In case the queue somehow gets filled, it will reset if it can not clear up
// PS: Could only get this to happen through unrealistic timings to overload the I2C bus
uint8_t i2c_led_q_request_room(uint8_t request_size) {
    if (request_size > i2c_led_q_available()) {
        i2c_led_q_full++;

        if (i2c_led_q_full >= 100)  // Give the queue a chance to clear up
        {
            DBG_LED_ON;
            I2C_DMAC_LED_Init();
            i2c_led_q_init();
            return 1;
        }

        return 0;
    }

    i2c_led_q_full = 0;

    return 1;
}

uint8_t i2c_led_q_run(void) {
    if (i2c_led_q_isempty()) {
        i2c_led_q_running = 0;
        return 0;
    }

    if (i2c_led_q_running) return 1;

    i2c_led_q_running = 1;

#    if I2C_LED_USE_DMA != 1
    while (!i2c_led_q_isempty()) {
#    endif
        // run command
        if (i2c_led_q[i2c_led_q_s] == I2C_Q_CRWL) {
            i2c_led_q_s_advance();
            uint8_t drvid = i2c_led_q[i2c_led_q_s];
#    if I2C_LED_USE_DMA == 1
            i2c_led_send_CRWL_dma(drvid);
#    else
        i2c_led_send_CRWL(drvid);
#    endif
        } else if (i2c_led_q[i2c_led_q_s] == I2C_Q_PAGE_SELECT) {
            i2c_led_q_s_advance();
            uint8_t drvid = i2c_led_q[i2c_led_q_s];
            i2c_led_q_s_advance();
            uint8_t page = i2c_led_q[i2c_led_q_s];
#    if I2C_LED_USE_DMA == 1
            i2c_led_select_page_dma(drvid, page);
#    else
        i2c_led_select_page(drvid, page);
#    endif
        } else if (i2c_led_q[i2c_led_q_s] == I2C_Q_PWM) {
            i2c_led_q_s_advance();
            uint8_t drvid = i2c_led_q[i2c_led_q_s];
#    if I2C_LED_USE_DMA == 1
            i2c_led_send_pwm_dma(drvid);
#    else
        i2c_led_send_pwm(drvid);
#    endif
        } else if (i2c_led_q[i2c_led_q_s] == I2C_Q_GCR) {
            i2c_led_q_s_advance();
            uint8_t drvid = i2c_led_q[i2c_led_q_s];
#    if I2C_LED_USE_DMA == 1
            i2c_led_send_GCR_dma(drvid);
#    else
        i2c_led_send_GCR(drvid);
#    endif
        } else if (i2c_led_q[i2c_led_q_s] == I2C_Q_ONOFF) {
            i2c_led_q_s_advance();
            uint8_t drvid = i2c_led_q[i2c_led_q_s];
#    if I2C_LED_USE_DMA == 1
            i2c_led_send_onoff_dma(drvid);
#    else
        i2c_led_send_onoff(drvid);
#    endif
        }

        i2c_led_q_s_advance();  // Advance last run command or if the command byte was not serviced

#    if I2C_LED_USE_DMA != 1
    }

    i2c_led_q_running = 0;
#    endif

    return 1;
}
#endif  // !defined(MD_BOOTLOADER) && defined(RGB_MATRIX_ENABLE)
