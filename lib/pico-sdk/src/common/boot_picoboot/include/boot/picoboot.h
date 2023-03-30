/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOOT_PICOBOOT_H
#define _BOOT_PICOBOOT_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#ifndef NO_PICO_PLATFORM
#include "pico/platform.h"
#endif

/** \file picoboot.h
*  \defgroup boot_picoboot boot_picoboot
*
* Header file for the PICOBOOT USB interface exposed by an RP2040 in BOOTSEL mode.
*/

#define PICOBOOT_MAGIC 0x431fd10bu

// --------------------------------------------
// CONTROL REQUESTS FOR THE PICOBOOT INTERFACE
// --------------------------------------------

// size 0 OUT - unstall EPs and reset
#define PICOBOOT_IF_RESET 0x41

// size 16 IN - return the status of the last command
#define PICOBOOT_IF_CMD_STATUS 0x42

// --------------------------------------------------
// COMMAND REQUESTS SENT TO THE PICOBOOT OUT ENDPOINT
// --------------------------------------------------
//
// picoboot_cmd structure of size 32 is sent to OUT endpoint
// transfer_length bytes are transferred via IN/OUT
// device responds on success with 0 length ACK packet set via OUT/IN
// device may stall the transferring endpoint in case of error

enum picoboot_cmd_id {
    PC_EXCLUSIVE_ACCESS = 0x1,
    PC_REBOOT = 0x2,
    PC_FLASH_ERASE = 0x3,
    PC_READ = 0x84, // either RAM or FLASH
    PC_WRITE = 5, // either RAM or FLASH (does no erase)
    PC_EXIT_XIP = 0x6,
    PC_ENTER_CMD_XIP = 0x7,
    PC_EXEC = 0x8,
    PC_VECTORIZE_FLASH = 0x9
};

enum picoboot_status {
    PICOBOOT_OK = 0,
    PICOBOOT_UNKNOWN_CMD = 1,
    PICOBOOT_INVALID_CMD_LENGTH = 2,
    PICOBOOT_INVALID_TRANSFER_LENGTH = 3,
    PICOBOOT_INVALID_ADDRESS = 4,
    PICOBOOT_BAD_ALIGNMENT = 5,
    PICOBOOT_INTERLEAVED_WRITE = 6,
    PICOBOOT_REBOOTING = 7,
    PICOBOOT_UNKNOWN_ERROR = 8,
};

struct __packed picoboot_reboot_cmd {
    uint32_t dPC; // 0 means reset into bootrom
    uint32_t dSP;
    uint32_t dDelayMS;
};

// used for EXEC, VECTORIZE_FLASH
struct __packed picoboot_address_only_cmd {
    uint32_t dAddr;
};

// used for READ, WRITE, FLASH_ERASE
struct __packed picoboot_range_cmd {
    uint32_t dAddr;
    uint32_t dSize;
};

enum picoboot_exclusive_type {
    NOT_EXCLUSIVE = 0,
    EXCLUSIVE,
    EXCLUSIVE_AND_EJECT
};

struct __packed picoboot_exclusive_cmd {
    uint8_t bExclusive;
};

// little endian
struct __packed __aligned(4) picoboot_cmd {
    uint32_t dMagic;
    uint32_t dToken; // an identifier for this token to correlate with a status response
    uint8_t bCmdId; // top bit set for IN
    uint8_t bCmdSize; // bytes of actual data in the arg part of this structure
    uint16_t _unused;
    uint32_t dTransferLength; // length of IN/OUT transfer (or 0) if none
    union {
        uint8_t args[16];
        struct picoboot_reboot_cmd reboot_cmd;
        struct picoboot_range_cmd range_cmd;
        struct picoboot_address_only_cmd address_only_cmd;
        struct picoboot_exclusive_cmd exclusive_cmd;
    };
};

static_assert(32 == sizeof(struct picoboot_cmd), "picoboot_cmd must be 32 bytes big");

struct __packed __aligned(4) picoboot_cmd_status {
    uint32_t dToken;
    uint32_t dStatusCode;
    uint8_t bCmdId;
    uint8_t bInProgress;
    uint8_t _pad[6];
};

static_assert(16 == sizeof(struct picoboot_cmd_status), "picoboot_cmd_status must be 16 bytes big");
#endif
