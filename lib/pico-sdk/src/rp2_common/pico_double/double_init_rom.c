/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include "pico/bootrom.h"
#include "pico/bootrom/sf_table.h"

// NOTE THIS FUNCTION TABLE IS NOT PUBLIC OR NECESSARILY COMPLETE...
// IT IS ***NOT*** SAFE TO CALL THESE FUNCTION POINTERS FROM ARBITRARY CODE
uint32_t sd_table[SF_TABLE_V2_SIZE / 2];

#if !(PICO_DOUBLE_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED)
static __attribute__((noreturn)) void missing_double_func_shim(void) {
    panic("missing double function");
}
#endif
extern void double_table_shim_on_use_helper(void);

void __attribute__((weak)) *sf_clz_func;

void __aeabi_double_init(void) {
    int rom_version = rp2040_rom_version();
#if PICO_DOUBLE_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
    if (rom_version == 1) {

        // this is a little tricky.. we only want to pull in a shim if the corresponding function
        // is called. to that end we include a SVC instruction with the table offset as the call number
        // followed by the shim function pointer inside the actual wrapper function. that way if the wrapper
        // function is garbage collected, so is the shim function.
        //
        // double_table_shim_on_use_helper expects this SVC instruction in the calling code soon after the address
        // pointed to by IP and patches the double_table entry with the real shim the first time the function is called.
        for(uint i=0; i<SF_TABLE_V2_SIZE/4; i++) {
            sd_table[i] = (uintptr_t)double_table_shim_on_use_helper;
        }
    }
#else
    if (rom_version == 1) {
        // opting for soft failure for now - you'll get a panic at runtime if you call any of the missing methods
        for(uint i=0;i<SF_TABLE_V2_SIZE/4;i++) {
            sd_table[i] = (uintptr_t)missing_double_func_shim;
        }
    }
#endif
    if (rom_version >= 2) {
        void *rom_table = rom_data_lookup(rom_table_code('S', 'D'));
        assert(*((uint8_t *)(((void *)rom_data_lookup(rom_table_code('S', 'F')))-2)) * 4 >= SF_TABLE_V2_SIZE);
        memcpy(&sd_table, rom_table, SF_TABLE_V2_SIZE);
        if (rom_version == 2) {
#ifndef NDEBUG
            if (*(uint16_t *)0x3854 != 0xb500 || // this is dsincos(_internal)

                *(uint16_t *)0x38d8 != 0x4649 || // this is dsin_finish
                *(uint16_t *)0x389c != 0x4659  // this is dcos_finish
                    ) {
                panic(NULL);
            }
#endif
        }
    }
    if (rom_version < 3) {
        // we use the unused entry for SINCOS
        sd_table[SF_TABLE_V3_FSINCOS / 4] = (uintptr_t) double_table_shim_on_use_helper;
    }

    sf_clz_func = rom_func_lookup(ROM_FUNC_CLZ32);
}
