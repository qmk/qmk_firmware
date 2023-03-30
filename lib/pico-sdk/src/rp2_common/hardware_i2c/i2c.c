/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/i2c.h"
#include "hardware/resets.h"
#include "hardware/clocks.h"
#include "pico/timeout_helper.h"

check_hw_layout(i2c_hw_t, enable, I2C_IC_ENABLE_OFFSET);
check_hw_layout(i2c_hw_t, clr_restart_det, I2C_IC_CLR_RESTART_DET_OFFSET);

i2c_inst_t i2c0_inst = {i2c0_hw, false};
i2c_inst_t i2c1_inst = {i2c1_hw, false};

static inline void i2c_reset(i2c_inst_t *i2c) {
    invalid_params_if(I2C, i2c != i2c0 && i2c != i2c1);
    reset_block(i2c == i2c0 ? RESETS_RESET_I2C0_BITS : RESETS_RESET_I2C1_BITS);
}

static inline void i2c_unreset(i2c_inst_t *i2c) {
    invalid_params_if(I2C, i2c != i2c0 && i2c != i2c1);
    unreset_block_wait(i2c == i2c0 ? RESETS_RESET_I2C0_BITS : RESETS_RESET_I2C1_BITS);
}

// Addresses of the form 000 0xxx or 111 1xxx are reserved. No slave should
// have these addresses.
static inline bool i2c_reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

uint i2c_init(i2c_inst_t *i2c, uint baudrate) {
    i2c_reset(i2c);
    i2c_unreset(i2c);
    i2c->restart_on_next = false;

    i2c->hw->enable = 0;

    // Configure as a fast-mode master with RepStart support, 7-bit addresses
    i2c->hw->con =
            I2C_IC_CON_SPEED_VALUE_FAST << I2C_IC_CON_SPEED_LSB |
            I2C_IC_CON_MASTER_MODE_BITS |
            I2C_IC_CON_IC_SLAVE_DISABLE_BITS |
            I2C_IC_CON_IC_RESTART_EN_BITS |
            I2C_IC_CON_TX_EMPTY_CTRL_BITS;

    // Set FIFO watermarks to 1 to make things simpler. This is encoded by a register value of 0.
    i2c->hw->tx_tl = 0;
    i2c->hw->rx_tl = 0;

    // Always enable the DREQ signalling -- harmless if DMA isn't listening
    i2c->hw->dma_cr = I2C_IC_DMA_CR_TDMAE_BITS | I2C_IC_DMA_CR_RDMAE_BITS;

    // Re-sets i2c->hw->enable upon returning:
    return i2c_set_baudrate(i2c, baudrate);
}

void i2c_deinit(i2c_inst_t *i2c) {
    i2c_reset(i2c);
}

uint i2c_set_baudrate(i2c_inst_t *i2c, uint baudrate) {
    invalid_params_if(I2C, baudrate == 0);
    // I2C is synchronous design that runs from clk_sys
    uint freq_in = clock_get_hz(clk_sys);

    // TODO there are some subtleties to I2C timing which we are completely ignoring here
    uint period = (freq_in + baudrate / 2) / baudrate;
    uint lcnt = period * 3 / 5; // oof this one hurts
    uint hcnt = period - lcnt;
    // Check for out-of-range divisors:
    invalid_params_if(I2C, hcnt > I2C_IC_FS_SCL_HCNT_IC_FS_SCL_HCNT_BITS);
    invalid_params_if(I2C, lcnt > I2C_IC_FS_SCL_LCNT_IC_FS_SCL_LCNT_BITS);
    invalid_params_if(I2C, hcnt < 8);
    invalid_params_if(I2C, lcnt < 8);

    // Per I2C-bus specification a device in standard or fast mode must
    // internally provide a hold time of at least 300ns for the SDA signal to
    // bridge the undefined region of the falling edge of SCL. A smaller hold
    // time of 120ns is used for fast mode plus.
    uint sda_tx_hold_count;
    if (baudrate < 1000000) {
        // sda_tx_hold_count = freq_in [cycles/s] * 300ns * (1s / 1e9ns)
        // Reduce 300/1e9 to 3/1e7 to avoid numbers that don't fit in uint.
        // Add 1 to avoid division truncation.
        sda_tx_hold_count = ((freq_in * 3) / 10000000) + 1;
    } else {
        // sda_tx_hold_count = freq_in [cycles/s] * 120ns * (1s / 1e9ns)
        // Reduce 120/1e9 to 3/25e6 to avoid numbers that don't fit in uint.
        // Add 1 to avoid division truncation.
        sda_tx_hold_count = ((freq_in * 3) / 25000000) + 1;
    }
    assert(sda_tx_hold_count <= lcnt - 2);

    i2c->hw->enable = 0;
    // Always use "fast" mode (<= 400 kHz, works fine for standard mode too)
    hw_write_masked(&i2c->hw->con,
                   I2C_IC_CON_SPEED_VALUE_FAST << I2C_IC_CON_SPEED_LSB,
                   I2C_IC_CON_SPEED_BITS
    );
    i2c->hw->fs_scl_hcnt = hcnt;
    i2c->hw->fs_scl_lcnt = lcnt;
    i2c->hw->fs_spklen = lcnt < 16 ? 1 : lcnt / 16;
    hw_write_masked(&i2c->hw->sda_hold,
                    sda_tx_hold_count << I2C_IC_SDA_HOLD_IC_SDA_TX_HOLD_LSB,
                    I2C_IC_SDA_HOLD_IC_SDA_TX_HOLD_BITS);

    i2c->hw->enable = 1;
    return freq_in / period;
}

void i2c_set_slave_mode(i2c_inst_t *i2c, bool slave, uint8_t addr) {
    invalid_params_if(I2C, addr >= 0x80); // 7-bit addresses
    invalid_params_if(I2C, i2c_reserved_addr(addr));
    i2c->hw->enable = 0;
    uint32_t ctrl_set_if_master = I2C_IC_CON_MASTER_MODE_BITS | I2C_IC_CON_IC_SLAVE_DISABLE_BITS;
    uint32_t ctrl_set_if_slave = I2C_IC_CON_RX_FIFO_FULL_HLD_CTRL_BITS;
    if (slave) {
        hw_write_masked(&i2c->hw->con,
            ctrl_set_if_slave,
            ctrl_set_if_master | ctrl_set_if_slave
        );
        i2c->hw->sar = addr;
    } else {
        hw_write_masked(&i2c->hw->con,
            ctrl_set_if_master,
            ctrl_set_if_master | ctrl_set_if_slave
        );
    }
    i2c->hw->enable = 1;
}

static int i2c_write_blocking_internal(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop,
                                       check_timeout_fn timeout_check, struct timeout_state *ts) {
    invalid_params_if(I2C, addr >= 0x80); // 7-bit addresses
    invalid_params_if(I2C, i2c_reserved_addr(addr));
    // Synopsys hw accepts start/stop flags alongside data items in the same
    // FIFO word, so no 0 byte transfers.
    invalid_params_if(I2C, len == 0);
    invalid_params_if(I2C, ((int)len) < 0);

    i2c->hw->enable = 0;
    i2c->hw->tar = addr;
    i2c->hw->enable = 1;

    bool abort = false;
    bool timeout = false;

    uint32_t abort_reason = 0;
    int byte_ctr;

    int ilen = (int)len;
    for (byte_ctr = 0; byte_ctr < ilen; ++byte_ctr) {
        bool first = byte_ctr == 0;
        bool last = byte_ctr == ilen - 1;

        i2c->hw->data_cmd =
                bool_to_bit(first && i2c->restart_on_next) << I2C_IC_DATA_CMD_RESTART_LSB |
                bool_to_bit(last && !nostop) << I2C_IC_DATA_CMD_STOP_LSB |
                *src++;

        // Wait until the transmission of the address/data from the internal
        // shift register has completed. For this to function correctly, the
        // TX_EMPTY_CTRL flag in IC_CON must be set. The TX_EMPTY_CTRL flag
        // was set in i2c_init.
        do {
            if (timeout_check) {
                timeout = timeout_check(ts);
                abort |= timeout;
            }
            tight_loop_contents();
        } while (!timeout && !(i2c->hw->raw_intr_stat & I2C_IC_RAW_INTR_STAT_TX_EMPTY_BITS));

        // If there was a timeout, don't attempt to do anything else.
        if (!timeout) {
            abort_reason = i2c->hw->tx_abrt_source;
            if (abort_reason) {
                // Note clearing the abort flag also clears the reason, and
                // this instance of flag is clear-on-read! Note also the
                // IC_CLR_TX_ABRT register always reads as 0.
                i2c->hw->clr_tx_abrt;
                abort = true;
            }

            if (abort || (last && !nostop)) {
                // If the transaction was aborted or if it completed
                // successfully wait until the STOP condition has occured.

                // TODO Could there be an abort while waiting for the STOP
                // condition here? If so, additional code would be needed here
                // to take care of the abort.
                do {
                    if (timeout_check) {
                        timeout = timeout_check(ts);
                        abort |= timeout;
                    }
                    tight_loop_contents();
                } while (!timeout && !(i2c->hw->raw_intr_stat & I2C_IC_RAW_INTR_STAT_STOP_DET_BITS));

                // If there was a timeout, don't attempt to do anything else.
                if (!timeout) {
                    i2c->hw->clr_stop_det;
                }
            }
        }

        // Note the hardware issues a STOP automatically on an abort condition.
        // Note also the hardware clears RX FIFO as well as TX on abort,
        // because we set hwparam IC_AVOID_RX_FIFO_FLUSH_ON_TX_ABRT to 0.
        if (abort)
            break;
    }

    int rval;

    // A lot of things could have just happened due to the ingenious and
    // creative design of I2C. Try to figure things out.
    if (abort) {
        if (timeout)
            rval = PICO_ERROR_TIMEOUT;
        else if (!abort_reason || abort_reason & I2C_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_BITS) {
            // No reported errors - seems to happen if there is nothing connected to the bus.
            // Address byte not acknowledged
            rval = PICO_ERROR_GENERIC;
        } else if (abort_reason & I2C_IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK_BITS) {
            // Address acknowledged, some data not acknowledged
            rval = byte_ctr;
        } else {
            //panic("Unknown abort from I2C instance @%08x: %08x\n", (uint32_t) i2c->hw, abort_reason);
            rval = PICO_ERROR_GENERIC;
        }
    } else {
        rval = byte_ctr;
    }

    // nostop means we are now at the end of a *message* but not the end of a *transfer*
    i2c->restart_on_next = nostop;
    return rval;
}

int i2c_write_blocking(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop) {
    return i2c_write_blocking_internal(i2c, addr, src, len, nostop, NULL, NULL);
}

int i2c_write_blocking_until(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop,
                             absolute_time_t until) {
    timeout_state_t ts;
    return i2c_write_blocking_internal(i2c, addr, src, len, nostop, init_single_timeout_until(&ts, until), &ts);
}

int i2c_write_timeout_per_char_us(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src, size_t len, bool nostop,
                                  uint timeout_per_char_us) {
    timeout_state_t ts;
    return i2c_write_blocking_internal(i2c, addr, src, len, nostop,
                                       init_per_iteration_timeout_us(&ts, timeout_per_char_us), &ts);
}

static int i2c_read_blocking_internal(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, size_t len, bool nostop,
                               check_timeout_fn timeout_check, timeout_state_t *ts) {
    invalid_params_if(I2C, addr >= 0x80); // 7-bit addresses
    invalid_params_if(I2C, i2c_reserved_addr(addr));
    invalid_params_if(I2C, len == 0);
    invalid_params_if(I2C, ((int)len) < 0);

    i2c->hw->enable = 0;
    i2c->hw->tar = addr;
    i2c->hw->enable = 1;

    bool abort = false;
    bool timeout = false;
    uint32_t abort_reason;
    int byte_ctr;
    int ilen = (int)len;
    for (byte_ctr = 0; byte_ctr < ilen; ++byte_ctr) {
        bool first = byte_ctr == 0;
        bool last = byte_ctr == ilen - 1;
        while (!i2c_get_write_available(i2c))
            tight_loop_contents();

        i2c->hw->data_cmd =
                bool_to_bit(first && i2c->restart_on_next) << I2C_IC_DATA_CMD_RESTART_LSB |
                bool_to_bit(last && !nostop) << I2C_IC_DATA_CMD_STOP_LSB |
                I2C_IC_DATA_CMD_CMD_BITS; // -> 1 for read

        do {
            abort_reason = i2c->hw->tx_abrt_source;
            abort = (bool) i2c->hw->clr_tx_abrt;
            if (timeout_check) {
                timeout = timeout_check(ts);
                abort |= timeout;
            }
        } while (!abort && !i2c_get_read_available(i2c));

        if (abort)
            break;

        *dst++ = (uint8_t) i2c->hw->data_cmd;
    }

    int rval;

    if (abort) {
        if (timeout)
            rval = PICO_ERROR_TIMEOUT;
        else if (!abort_reason || abort_reason & I2C_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK_BITS) {
            // No reported errors - seems to happen if there is nothing connected to the bus.
            // Address byte not acknowledged
            rval = PICO_ERROR_GENERIC;
        } else {
//            panic("Unknown abort from I2C instance @%08x: %08x\n", (uint32_t) i2c->hw, abort_reason);
            rval = PICO_ERROR_GENERIC;
        }
    } else {
        rval = byte_ctr;
    }

    i2c->restart_on_next = nostop;
    return rval;
}

int i2c_read_blocking(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, size_t len, bool nostop) {
    return i2c_read_blocking_internal(i2c, addr, dst, len, nostop, NULL, NULL);
}

int i2c_read_blocking_until(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, size_t len, bool nostop, absolute_time_t until) {
    timeout_state_t ts;
    return i2c_read_blocking_internal(i2c, addr, dst, len, nostop, init_single_timeout_until(&ts, until), &ts);
}

int i2c_read_timeout_per_char_us(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, size_t len, bool nostop,
                                 uint timeout_per_char_us) {
    timeout_state_t ts;
    return i2c_read_blocking_internal(i2c, addr, dst, len, nostop,
                                      init_per_iteration_timeout_us(&ts, timeout_per_char_us), &ts);
}
