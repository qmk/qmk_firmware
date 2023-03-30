/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_BINARY_INFO_STRUCTURE_H
#define _PICO_BINARY_INFO_STRUCTURE_H

// NOTE: This file may be included by non SDK code, so does not use SDK includes

// NOTE: ALL CHANGES MUST BE BACKWARDS COMPATIBLE

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef __packed
#define __packed __attribute__((packed))
#endif

typedef struct _binary_info_core binary_info_t;

#define BINARY_INFO_TYPE_RAW_DATA 1
#define BINARY_INFO_TYPE_SIZED_DATA 2
#define BINARY_INFO_TYPE_BINARY_INFO_LIST_ZERO_TERMINATED 3
#define BINARY_INFO_TYPE_BSON 4
#define BINARY_INFO_TYPE_ID_AND_INT 5
#define BINARY_INFO_TYPE_ID_AND_STRING 6
// traditional block device
#define BINARY_INFO_TYPE_BLOCK_DEVICE 7
#define BINARY_INFO_TYPE_PINS_WITH_FUNC 8
#define BINARY_INFO_TYPE_PINS_WITH_NAME 9
#define BINARY_INFO_TYPE_PINS_WITH_NAMES 9
#define BINARY_INFO_TYPE_NAMED_GROUP 10

// note plan is to reserve c1 = 0->31 for "collision tags"; i.e.
// for which you should always use random IDs with the binary_info,
// giving you 4 + 8 + 32 = 44 bits to avoid collisions
#define BINARY_INFO_MAKE_TAG(c1, c2) ((((uint)c2&0xffu)<<8u)|((uint)c1&0xffu))

// Raspberry Pi defined. do not use
#define BINARY_INFO_TAG_RASPBERRY_PI BINARY_INFO_MAKE_TAG('R','P')

#define BINARY_INFO_ID_RP_PROGRAM_NAME 0x02031c86
#define BINARY_INFO_ID_RP_PROGRAM_VERSION_STRING 0x11a9bc3a
#define BINARY_INFO_ID_RP_PROGRAM_BUILD_DATE_STRING 0x9da22254
#define BINARY_INFO_ID_RP_BINARY_END 0x68f465de
#define BINARY_INFO_ID_RP_PROGRAM_URL 0x1856239a
#define BINARY_INFO_ID_RP_PROGRAM_DESCRIPTION 0xb6a07c19
#define BINARY_INFO_ID_RP_PROGRAM_FEATURE 0xa1f4b453
#define BINARY_INFO_ID_RP_PROGRAM_BUILD_ATTRIBUTE 0x4275f0d3
#define BINARY_INFO_ID_RP_SDK_VERSION 0x5360b3ab
#define BINARY_INFO_ID_RP_PICO_BOARD 0xb63cffbb
#define BINARY_INFO_ID_RP_BOOT2_NAME 0x7f8882e1

#if PICO_ON_DEVICE
#define bi_ptr_of(x) x *
#else
#define bi_ptr_of(x) uint32_t
#endif
typedef struct __packed _binary_info_core {
        uint16_t type;
        uint16_t tag;
} binary_info_core_t;

typedef struct __packed _binary_info_raw_data {
        struct _binary_info_core core;
        uint8_t bytes[1];
} binary_info_raw_data_t;

typedef struct __packed _binary_info_sized_data {
        struct _binary_info_core core;
        uint32_t length;
        uint8_t bytes[1];
} binary_info_sized_data_t;

typedef struct __packed _binary_info_list_zero_terminated {
        struct _binary_info_core core;
        bi_ptr_of(binary_info_t) list;
} binary_info_list_zero_terminated_t;

typedef struct __packed _binary_info_id_and_int {
        struct _binary_info_core core;
        uint32_t id;
        int32_t value;
} binary_info_id_and_int_t;

typedef struct __packed _binary_info_id_and_string {
        struct _binary_info_core core;
        uint32_t id;
        bi_ptr_of(const char) value;
} binary_info_id_and_string_t;

typedef struct __packed _binary_info_block_device {
        struct _binary_info_core core;
        bi_ptr_of(const char) name; // optional static name (independent of what is formatted)
        uint32_t address;
        uint32_t size;
        bi_ptr_of(binary_info_t) extra; // additional info
        uint16_t flags;
} binary_info_block_device_t;

#define BI_PINS_ENCODING_RANGE 1
#define BI_PINS_ENCODING_MULTI 2

typedef struct __packed _binary_info_pins_with_func {
    struct _binary_info_core core;
    // p4_5 : p3_5 : p2_5 : p1_5 : p0_5 : func_4 : 010_3 //individual pins p0,p1,p2,p3,p4 ... if fewer than 5 then duplicate p
    //                    phi_5 : plo_5 : func_4 : 001_3 // pin range plo-phi inclusive
    uint32_t pin_encoding;
} binary_info_pins_with_func_t;

typedef struct __packed _binary_info_pins_with_name {
    struct _binary_info_core core;
    uint32_t pin_mask;
    bi_ptr_of(const char) label;
} binary_info_pins_with_name_t;

#define BI_NAMED_GROUP_SHOW_IF_EMPTY   0x0001  // default is to hide
#define BI_NAMED_GROUP_SEPARATE_COMMAS 0x0002  // default is newlines
#define BI_NAMED_GROUP_SORT_ALPHA      0x0004  // default is no sort
#define BI_NAMED_GROUP_ADVANCED        0x0008  // if set, then only shown in say info -a

typedef struct __packed _binary_info_named_group {
    struct _binary_info_core core;
    uint32_t parent_id;
    uint16_t flags;
    uint16_t group_tag;
    uint32_t group_id;
    bi_ptr_of(const char) label;
} binary_info_named_group_t;

enum {
    BINARY_INFO_BLOCK_DEV_FLAG_READ =
    1 << 0, // if not readable, then it is basically hidden, but tools may choose to avoid overwriting it
    BINARY_INFO_BLOCK_DEV_FLAG_WRITE = 1 << 1,
    BINARY_INFO_BLOCK_DEV_FLAG_REFORMAT = 1 << 2, // may be reformatted..

    BINARY_INFO_BLOCK_DEV_FLAG_PT_UNKNOWN = 0 << 4, // unknown free to look
    BINARY_INFO_BLOCK_DEV_FLAG_PT_MBR = 1 << 4, // expect MBR
    BINARY_INFO_BLOCK_DEV_FLAG_PT_GPT = 2 << 4, // expect GPT
    BINARY_INFO_BLOCK_DEV_FLAG_PT_NONE = 3 << 4, // no partition table
};

#ifdef __cplusplus
}
#endif
#endif
