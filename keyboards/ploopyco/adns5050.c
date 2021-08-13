/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "adns5050.h"
#include "quantum.h"
#include "wait.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

#ifndef OPTIC_ROTATED
#    define OPTIC_ROTATED false
#endif

// Definitions for the ADNS serial line.
// These really ought to be defined in your config.h, but defaults are
// here if you're really lazy.
#ifndef ADNS_SCLK_PIN
#    define ADNS_SCLK_PIN B7
#endif

#ifndef ADNS_SDIO_PIN
#    define ADNS_SDIO_PIN C6
#endif

#ifndef ADNS_CS_PIN
#    define ADNS_CS_PIN B4
#endif

#ifdef CONSOLE_ENABLE
void print_byte(uint8_t byte) { dprintf("%c%c%c%c%c%c%c%c|", (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')); }
#endif

// Initialize the ADNS serial pins.
void adns_init(void) {
    setPinOutput(ADNS_SCLK_PIN);
    setPinOutput(ADNS_SDIO_PIN);
    setPinOutput(ADNS_CS_PIN);
}

// Perform a synchronization with the ADNS.
// Just as with the serial protocol, this is used by the slave to send a
// synchronization signal to the master.
void adns_sync(void) {
    writePinLow(ADNS_CS_PIN);
    wait_us(1);
    writePinHigh(ADNS_CS_PIN);
}

void adns_cs_select(void) {
    writePinLow(ADNS_CS_PIN);
}

void adns_cs_deselect(void) {
    writePinHigh(ADNS_CS_PIN);
}

uint8_t adns_serial_read(void) {
    setPinInput(ADNS_SDIO_PIN);
    uint8_t byte = 0;

    for (uint8_t i = 0; i < 8; ++i) {
        writePinLow(ADNS_SCLK_PIN);
        wait_us(1);

        byte = (byte << 1) | readPin(ADNS_SDIO_PIN);

        writePinHigh(ADNS_SCLK_PIN);
        wait_us(1);
    }

    return byte;
}

void adns_serial_write(uint8_t data) {
    setPinOutput(ADNS_SDIO_PIN);

    for (int8_t b = 7; b >= 0; b--) {
        writePinLow(ADNS_SCLK_PIN);

        if (data & (1 << b))
            writePinHigh(ADNS_SDIO_PIN);
        else
            writePinLow(ADNS_SDIO_PIN);

        wait_us(2);

        writePinHigh(ADNS_SCLK_PIN);
    }

    // tSWR. See page 15 of the ADNS spec sheet.
    // Technically, this is only necessary if the next operation is an SDIO
    // read. This is not guaranteed to be the case, but we're being lazy.
    wait_us(4);

    // Note that tSWW is never necessary. All write operations require at
    // least 32us, which exceeds tSWW, so there's never a need to wait for it.
}

// Read a byte of data from a register on the ADNS.
// Don't forget to use the register map (as defined in the header file).
uint8_t adns_read_reg(uint8_t reg_addr) {
    adns_cs_select();

    adns_serial_write(reg_addr);

    // We don't need a minimum tSRAD here. That's because a 4ms wait time is
    // already included in adns_serial_write(), so we're good.
    // See page 10 and 15 of the ADNS spec sheet.
    //wait_us(4);

    uint8_t byte = adns_serial_read();

    // tSRW & tSRR. See page 15 of the ADNS spec sheet.
    // Technically, this is only necessary if the next operation is an SDIO
    // read or write. This is not guaranteed to be the case.
    // Honestly, this wait could probably be removed.
    wait_us(1);

    adns_cs_deselect();

    return byte;
}

void adns_write_reg(uint8_t reg_addr, uint8_t data) {
    adns_cs_select();
    adns_serial_write( 0b10000000 | reg_addr );
    adns_serial_write(data);
    adns_cs_deselect();
}

report_adns_t adns_read_burst(void) {
    adns_cs_select();

    report_adns_t data;
    data.dx = 0;
    data.dy = 0;

    adns_serial_write(REG_MOTION_BURST);

    // We don't need a minimum tSRAD here. That's because a 4ms wait time is
    // already included in adns_serial_write(), so we're good.
    // See page 10 and 15 of the ADNS spec sheet.
    //wait_us(4);

    uint8_t x = adns_serial_read();
    uint8_t y = adns_serial_read();

    // Burst mode returns a bunch of other shit that we don't really need.
    // Setting CS to high ends burst mode early.
    adns_cs_deselect();

    data.dx = convert_twoscomp(x);
    data.dy = convert_twoscomp(y);

    return data;
}

// Convert a two's complement byte from an unsigned data type into a signed
// data type.
int8_t convert_twoscomp(uint8_t data) {
    if ((data & 0x80) == 0x80)
        return -128 + (data & 0x7F);
    else
        return data;
}

// Don't forget to use the definitions for CPI in the header file.
void adns_set_cpi(uint8_t cpi) {
    adns_write_reg(REG_MOUSE_CONTROL2, cpi);
}

bool adns_check_signature(void) {
    uint8_t pid = adns_read_reg(REG_PRODUCT_ID);
    uint8_t rid = adns_read_reg(REG_REVISION_ID);
    uint8_t pid2 = adns_read_reg(REG_PRODUCT_ID2);

    return (pid == 0x12 && rid == 0x01 && pid2 == 0x26);
}
