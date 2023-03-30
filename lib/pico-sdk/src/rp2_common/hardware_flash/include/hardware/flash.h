/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_FLASH_H
#define _HARDWARE_FLASH_H

#include "pico.h"

/** \file flash.h
 *  \defgroup hardware_flash hardware_flash
 *
 * Low level flash programming and erase API
 *
 * Note these functions are *unsafe* if you are using both cores, and the other 
 * is executing from flash concurrently with the operation. In this could be the 
 * case, you must perform your own synchronisation to make sure that no XIP
 * accesses take place during flash programming. One option is to use the
 * \ref multicore_lockout functions.
 *
 * Likewise they are *unsafe* if you have interrupt handlers or an interrupt
 * vector table in flash, so you must disable interrupts before calling in
 * this case.
 *
 * If PICO_NO_FLASH=1 is not defined (i.e. if the program is built to run from
 * flash) then these functions will make a static copy of the second stage
 * bootloader in SRAM, and use this to reenter execute-in-place mode after
 * programming or erasing flash, so that they can safely be called from
 * flash-resident code.
 *
 * \subsection flash_example Example
 * \include flash_program.c
 */

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_FLASH, Enable/disable assertions in the flash module, type=bool, default=0, group=hardware_flash
#ifndef PARAM_ASSERTIONS_ENABLED_FLASH
#define PARAM_ASSERTIONS_ENABLED_FLASH 0
#endif

#define FLASH_PAGE_SIZE (1u << 8)
#define FLASH_SECTOR_SIZE (1u << 12)
#define FLASH_BLOCK_SIZE (1u << 16)

#define FLASH_UNIQUE_ID_SIZE_BYTES 8

// PICO_CONFIG: PICO_FLASH_SIZE_BYTES, size of primary flash in bytes, type=int, group=hardware_flash

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief  Erase areas of flash
 *  \ingroup hardware_flash
 *
 * \param flash_offs Offset into flash, in bytes, to start the erase. Must be aligned to a 4096-byte flash sector.
 * \param count Number of bytes to be erased. Must be a multiple of 4096 bytes (one sector).
 */
void flash_range_erase(uint32_t flash_offs, size_t count);

/*! \brief  Program flash
 *  \ingroup hardware_flash
 *
 * \param flash_offs Flash address of the first byte to be programmed. Must be aligned to a 256-byte flash page.
 * \param data Pointer to the data to program into flash
 * \param count Number of bytes to program. Must be a multiple of 256 bytes (one page).
 */

void flash_range_program(uint32_t flash_offs, const uint8_t *data, size_t count);

/*! \brief Get flash unique 64 bit identifier
 *  \ingroup hardware_flash
 *
 * Use a standard 4Bh RUID instruction to retrieve the 64 bit unique
 * identifier from a flash device attached to the QSPI interface. Since there
 * is a 1:1 association between the MCU and this flash, this also serves as a
 * unique identifier for the board.
 *
 *  \param id_out Pointer to an 8-byte buffer to which the ID will be written
 */
void flash_get_unique_id(uint8_t *id_out);

/*! \brief Execute bidirectional flash command
 *  \ingroup hardware_flash
 *
 * Low-level function to execute a serial command on a flash device attached
 * to the QSPI interface. Bytes are simultaneously transmitted and received
 * from txbuf and to rxbuf. Therefore, both buffers must be the same length,
 * count, which is the length of the overall transaction. This is useful for
 * reading metadata from the flash chip, such as device ID or SFDP
 * parameters.
 *
 * The XIP cache is flushed following each command, in case flash state
 * has been modified. Like other hardware_flash functions, the flash is not
 * accessible for execute-in-place transfers whilst the command is in
 * progress, so entering a flash-resident interrupt handler or executing flash
 * code on the second core concurrently will be fatal. To avoid these pitfalls
 * it is recommended that this function only be used to extract flash metadata
 * during startup, before the main application begins to run: see the
 * implementation of pico_get_unique_id() for an example of this.
 *
 *  \param txbuf Pointer to a byte buffer which will be transmitted to the flash
 *  \param rxbuf Pointer to a byte buffer where data received from the flash will be written. txbuf and rxbuf may be the same buffer.
 *  \param count Length in bytes of txbuf and of rxbuf
 */
void flash_do_cmd(const uint8_t *txbuf, uint8_t *rxbuf, size_t count);


#ifdef __cplusplus
}
#endif

#endif
