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
uint32_t sf_table[SF_TABLE_V2_SIZE / 2];
void __attribute__((weak)) *sf_clz_func;

#if !(PICO_FLOAT_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED)
static __attribute__((noreturn)) void missing_float_func_shim(void) {
    panic("");
}
#endif

void __aeabi_float_init(void) {
    int rom_version = rp2040_rom_version();
    void *rom_table = rom_data_lookup(rom_table_code('S', 'F'));
#if PICO_FLOAT_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
    if (rom_version == 1) {
        memcpy(&sf_table, rom_table, SF_TABLE_V1_SIZE);
        extern void float_table_shim_on_use_helper(void);
        // todo replace NDEBUG with a more exclusive assertion guard
#ifndef NDEBUG
        if (*(uint16_t *)0x29ee != 0x0fc4 || // this is packx
            *(uint16_t *)0x29c0 != 0x0dc2 || // this is upackx
            *(uint16_t *)0x2b96 != 0xb5c0 || // this is cordic_vec
            *(uint16_t *)0x2b18 != 0x2500 || // this is packretns
            *(uint16_t *)0x2acc != 0xb510 || // this is float2fix
            *(uint32_t *)0x2cfc != 0x6487ed51 // pi_q29
        ) {
            panic("");
        }
#endif

        // this is a little tricky.. we only want to pull in a shim if the corresponding function
        // is called. to that end we include a SVC instruction with the table offset as the call number
        // followed by the shim function pointer inside the actual wrapper function. that way if the wrapper
        // function is garbage collected, so is the shim function.
        //
        // float_table_shim_on_use_helper expects this SVC instruction in the calling code soon after the address
        // pointed to by IP and patches the float_table entry with the real shim the first time the function is called.

        for(uint i=SF_TABLE_V1_SIZE/4; i<SF_TABLE_V2_SIZE/4; i++) {
            sf_table[i] = (uintptr_t)float_table_shim_on_use_helper;
        }
        // we shim these for -0 and -denormal handling
        sf_table[SF_TABLE_FLOAT2INT/4] = sf_table[SF_TABLE_FLOAT2FIX/4] = (uintptr_t)float_table_shim_on_use_helper;
    }
#else
    if (rom_version == 1) {
        memcpy(&sf_table, rom_table, SF_TABLE_V1_SIZE);
        // opting for soft failure for now - you'll get a panic at runtime if you call any of the missing methods
        for(uint i=0;i<SF_TABLE_V2_SIZE/4;i++) {
            if (!sf_table[i]) sf_table[i] = (uintptr_t)missing_float_func_shim;
        }
    }
#endif
    if (rom_version >= 2) {
        assert(*((uint8_t *)(rom_table-2)) * 4 >= SF_TABLE_V2_SIZE);
        memcpy(&sf_table, rom_table, SF_TABLE_V2_SIZE);
    }
    sf_clz_func = rom_func_lookup(ROM_FUNC_CLZ32);
}
