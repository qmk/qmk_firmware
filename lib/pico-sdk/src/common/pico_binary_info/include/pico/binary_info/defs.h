/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_BINARY_INFO_DEFS_H
#define _PICO_BINARY_INFO_DEFS_H

// this file is for pre-processor definitions only

// should be found within the first 256 bytes of the real binary (i.e. after the flash second stage if a flash binary)
//
// Note the layout is:
//
// addr      : BINARY_INFO_MARKER_START
// addr+0x04 : __binary_info_start
// addr+0x08 : __binary_info_end
// addr+0x0c : __address_mapping_table
// addr+0x10 | BINARY_INFO_MARKER_END
//
// __binary_info_start to __binary_info_end are the start, end (non inclusive) of an array
// of pointers to binary_info_t structures
//
// __address_mapping_table is an array of the following items:
//
// uint32_t source_addr_start
// uint32_t dest_addr_start
// uint32_t dest_addr_end
//
// representing a mapping from the stored address in the binary/flash to addresses at runtime.
// The linker will store pointers within the binary using their runtime values, however because of
// "AT" mapping in the link script these addresses actually correspond to a different address in the binary
// image. This mapping (which in the case of crt0.S is simply the data copy table used at initialization
// to copy data into it's runtime location) can be used by picotool or others to reverse the mapping to find data
// within the binary.
//
// Note the above array is terminated with a NULL source_addr_start

#define BINARY_INFO_MARKER_START 0x7188ebf2
#define BINARY_INFO_MARKER_END 0xe71aa390

#endif