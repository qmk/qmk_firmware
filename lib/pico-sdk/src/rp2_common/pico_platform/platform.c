/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico.h"
#include "hardware/address_mapped.h"
#include "hardware/regs/tbman.h"
#include "hardware/regs/sysinfo.h"

// Note we leave the FPGA check in by default so that we can run bug repro
// binaries coming in from the wild on the FPGA platform. It takes up around
// 48 bytes if you include all the calls, so you can pass PICO_NO_FPGA_CHECK=1
// to remove it. The FPGA check is used to skip initialisation of hardware
// (mainly clock generators and oscillators) that aren't present on FPGA.

#if !PICO_NO_FPGA_CHECK
// Inline stub provided in header if this code is unused (so folding can be
// done in each TU instead of relying on LTO)
bool running_on_fpga() {
    return !!((*(io_ro_32 *)TBMAN_BASE) & TBMAN_PLATFORM_FPGA_BITS);
}
#endif

#define MANUFACTURER_RPI 0x927
#define PART_RP2 0x2

uint8_t rp2040_chip_version() {
    // First register of sysinfo is chip id
    uint32_t chip_id = *((io_ro_32*)(SYSINFO_BASE + SYSINFO_CHIP_ID_OFFSET));
    uint32_t __unused manufacturer = chip_id & SYSINFO_CHIP_ID_MANUFACTURER_BITS;
    uint32_t __unused part = (chip_id & SYSINFO_CHIP_ID_PART_BITS) >> SYSINFO_CHIP_ID_PART_LSB;
    assert(manufacturer == MANUFACTURER_RPI);
    assert(part == PART_RP2);
    // Version 1 == B0/B1
    uint version = (chip_id & SYSINFO_CHIP_ID_REVISION_BITS) >> SYSINFO_CHIP_ID_REVISION_LSB;
    return (uint8_t)version;
}