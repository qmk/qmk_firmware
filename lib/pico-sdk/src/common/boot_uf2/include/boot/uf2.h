/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOOT_UF2_H
#define _BOOT_UF2_H

#include <stdint.h>
#include <assert.h>

/** \file uf2.h
*  \defgroup boot_uf2 boot_uf2
*
* Header file for the UF2 format supported by an RP2040 in BOOTSEL mode.
*/

#define UF2_MAGIC_START0 0x0A324655u
#define UF2_MAGIC_START1 0x9E5D5157u
#define UF2_MAGIC_END    0x0AB16F30u

#define UF2_FLAG_NOT_MAIN_FLASH     0x00000001u
#define UF2_FLAG_FILE_CONTAINER     0x00001000u
#define UF2_FLAG_FAMILY_ID_PRESENT  0x00002000u
#define UF2_FLAG_MD5_PRESENT        0x00004000u

#define RP2040_FAMILY_ID 0xe48bff56

struct uf2_block {
    // 32 byte header
    uint32_t magic_start0;
    uint32_t magic_start1;
    uint32_t flags;
    uint32_t target_addr;
    uint32_t payload_size;
    uint32_t block_no;
    uint32_t num_blocks;
    uint32_t file_size; // or familyID;
    uint8_t  data[476];
    uint32_t magic_end;
};

static_assert(sizeof(struct uf2_block) == 512, "uf2_block not sector sized");

#endif
