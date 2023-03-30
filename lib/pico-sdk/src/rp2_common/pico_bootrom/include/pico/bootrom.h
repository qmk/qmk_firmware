/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_BOOTROM_H
#define _PICO_BOOTROM_H

#include "pico.h"

/** \file bootrom.h
 * \defgroup pico_bootrom pico_bootrom
 * Access to functions and data in the RP2040 bootrom
 *
 * This header may be included by assembly code
 */

// ROM FUNCTIONS

#define ROM_FUNC_POPCOUNT32             ROM_TABLE_CODE('P', '3')
#define ROM_FUNC_REVERSE32              ROM_TABLE_CODE('R', '3')
#define ROM_FUNC_CLZ32                  ROM_TABLE_CODE('L', '3')
#define ROM_FUNC_CTZ32                  ROM_TABLE_CODE('T', '3')
#define ROM_FUNC_MEMSET                 ROM_TABLE_CODE('M', 'S')
#define ROM_FUNC_MEMSET4                ROM_TABLE_CODE('S', '4')
#define ROM_FUNC_MEMCPY                 ROM_TABLE_CODE('M', 'C')
#define ROM_FUNC_MEMCPY44               ROM_TABLE_CODE('C', '4')
#define ROM_FUNC_RESET_USB_BOOT         ROM_TABLE_CODE('U', 'B')
#define ROM_FUNC_CONNECT_INTERNAL_FLASH ROM_TABLE_CODE('I', 'F')
#define ROM_FUNC_FLASH_EXIT_XIP         ROM_TABLE_CODE('E', 'X')
#define ROM_FUNC_FLASH_RANGE_ERASE      ROM_TABLE_CODE('R', 'E')
#define ROM_FUNC_FLASH_RANGE_PROGRAM    ROM_TABLE_CODE('R', 'P')
#define ROM_FUNC_FLASH_FLUSH_CACHE      ROM_TABLE_CODE('F', 'C')
#define ROM_FUNC_FLASH_ENTER_CMD_XIP    ROM_TABLE_CODE('C', 'X')

/*! \brief Return a bootrom lookup code based on two ASCII characters
 * \ingroup pico_bootrom
 *
 * These codes are uses to lookup data or function addresses in the bootrom
 *
 * \param c1 the first character
 * \param c2 the second character
 * \return the 'code' to use in rom_func_lookup() or rom_data_lookup()
 */
#define ROM_TABLE_CODE(c1, c2) ((c1) | ((c2) << 8))

#ifndef __ASSEMBLER__

// ROM FUNCTION SIGNATURES

typedef uint32_t (*rom_popcount32_fn)(uint32_t);
typedef uint32_t (*rom_reverse32_fn)(uint32_t);
typedef uint32_t (*rom_clz32_fn)(uint32_t);
typedef uint32_t (*rom_ctz32_fn)(uint32_t);
typedef uint8_t *(*rom_memset_fn)(uint8_t *, uint8_t, uint32_t);
typedef uint32_t *(*rom_memset4_fn)(uint32_t *, uint8_t, uint32_t);
typedef uint32_t *(*rom_memcpy_fn)(uint8_t *, const uint8_t *, uint32_t);
typedef uint32_t *(*rom_memcpy44_fn)(uint32_t *, const uint32_t *, uint32_t);
typedef void __attribute__((noreturn)) (*rom_reset_usb_boot_fn)(uint32_t, uint32_t);
typedef rom_reset_usb_boot_fn reset_usb_boot_fn; // kept for backwards compatibility
typedef void (*rom_connect_internal_flash_fn)(void);
typedef void (*rom_flash_exit_xip_fn)(void);
typedef void (*rom_flash_range_erase_fn)(uint32_t, size_t, uint32_t, uint8_t);
typedef void (*rom_flash_range_program_fn)(uint32_t, const uint8_t*, size_t);
typedef void (*rom_flash_flush_cache_fn)(void);
typedef void (*rom_flash_enter_cmd_xip_fn)(void);

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Return a bootrom lookup code based on two ASCII characters
 * \ingroup pico_bootrom
 *
 * These codes are uses to lookup data or function addresses in the bootrom
 *
 * \param c1 the first character
 * \param c2 the second character
 * \return the 'code' to use in rom_func_lookup() or rom_data_lookup()
 */
static inline uint32_t rom_table_code(uint8_t c1, uint8_t c2) {
    return ROM_TABLE_CODE((uint32_t) c1, (uint32_t) c2);
}

/*!
 * \brief Lookup a bootrom function by code
 * \ingroup pico_bootrom
 * \param code the code
 * \return a pointer to the function, or NULL if the code does not match any bootrom function
 */
void *rom_func_lookup(uint32_t code);

/*!
 * \brief Lookup a bootrom address by code
 * \ingroup pico_bootrom
 * \param code the code
 * \return a pointer to the data, or NULL if the code does not match any bootrom function
 */
void *rom_data_lookup(uint32_t code);

/*!
 * \brief Helper function to lookup the addresses of multiple bootrom functions
 * \ingroup pico_bootrom
 *
 * This method looks up the 'codes' in the table, and convert each table entry to the looked up
 * function pointer, if there is a function for that code in the bootrom.
 *
 * \param table an IN/OUT array, elements are codes on input, function pointers on success.
 * \param count the number of elements in the table
 * \return true if all the codes were found, and converted to function pointers, false otherwise
 */
bool rom_funcs_lookup(uint32_t *table, unsigned int count);

// Bootrom function: rom_table_lookup
// Returns the 32 bit pointer into the ROM if found or NULL otherwise.
typedef void *(*rom_table_lookup_fn)(uint16_t *table, uint32_t code);

#if defined(__GNUC__) && (__GNUC__ >= 12)
// Convert a 16 bit pointer stored at the given rom address into a 32 bit pointer
static inline void *rom_hword_as_ptr(uint16_t rom_address) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
    return (void *)(uintptr_t)*(uint16_t *)(uintptr_t)rom_address;
#pragma GCC diagnostic pop
}
#else
// Convert a 16 bit pointer stored at the given rom address into a 32 bit pointer
#define rom_hword_as_ptr(rom_address) (void *)(uintptr_t)(*(uint16_t *)(uintptr_t)(rom_address))
#endif

/*!
 * \brief Lookup a bootrom function by code. This method is forcibly inlined into the caller for FLASH/RAM sensitive code usage
 * \ingroup pico_bootrom
 * \param code the code
 * \return a pointer to the function, or NULL if the code does not match any bootrom function
 */
static __force_inline void *rom_func_lookup_inline(uint32_t code) {
    rom_table_lookup_fn rom_table_lookup = (rom_table_lookup_fn) rom_hword_as_ptr(0x18);
    uint16_t *func_table = (uint16_t *) rom_hword_as_ptr(0x14);
    return rom_table_lookup(func_table, code);
}

/*!
 * \brief Reboot the device into BOOTSEL mode
 * \ingroup pico_bootrom
 *
 * This function reboots the device into the BOOTSEL mode ('usb boot").
 *
 * Facilities are provided to enable an "activity light" via GPIO attached LED for the USB Mass Storage Device,
 * and to limit the USB interfaces exposed.
 *
 * \param usb_activity_gpio_pin_mask 0 No pins are used as per a cold boot. Otherwise a single bit set indicating which
 *                               GPIO pin should be set to output and raised whenever there is mass storage activity
 *                               from the host.
 * \param disable_interface_mask value to control exposed interfaces
 *  - 0 To enable both interfaces (as per a cold boot)
 *  - 1 To disable the USB Mass Storage Interface
 *  - 2 To disable the USB PICOBOOT Interface
 */
static inline void __attribute__((noreturn)) reset_usb_boot(uint32_t usb_activity_gpio_pin_mask,
                                                            uint32_t disable_interface_mask) {
    rom_reset_usb_boot_fn func = (rom_reset_usb_boot_fn) rom_func_lookup(ROM_FUNC_RESET_USB_BOOT);
    func(usb_activity_gpio_pin_mask, disable_interface_mask);
}

#ifdef __cplusplus
}
#endif

#endif // !__ASSEMBLER__
#endif
