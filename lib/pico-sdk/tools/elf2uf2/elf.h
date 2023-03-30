/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _ELF_H
#define _ELF_H

#include <stdint.h>

#define ELF_MAGIC 0x464c457fu

#define EM_ARM 0x28u

#define EF_ARM_ABI_FLOAT_HARD 0x00000400u

#define PT_LOAD 0x00000001u

#pragma pack(push, 1)
struct elf_header {
    uint32_t    magic;
    uint8_t     arch_class;
    uint8_t     endianness;
    uint8_t     version;
    uint8_t     abi;
    uint8_t     abi_version;
    uint8_t     _pad[7];
    uint16_t    type;
    uint16_t    machine;
    uint32_t    version2;
};

struct elf32_header {
    struct elf_header common;
    uint32_t    entry;
    uint32_t    ph_offset;
    uint32_t    sh_offset;
    uint32_t    flags;
    uint16_t    eh_size;
    uint16_t    ph_entry_size;
    uint16_t    ph_num;
    uint16_t    sh_entry_size;
    uint16_t    sh_num;
    uint16_t    sh_str_index;
};

struct elf32_ph_entry {
    uint32_t type;
    uint32_t offset;
    uint32_t vaddr;
    uint32_t paddr;
    uint32_t filez;
    uint32_t memsz;
    uint32_t flags;
    uint32_t align;
};
#pragma pack(pop)

#endif