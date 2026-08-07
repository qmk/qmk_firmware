// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief The status of a flash operation.
 */
enum {
    FLASH_STATUS_SUCCESS     = 0,  //< The operation completed successfully.
    FLASH_STATUS_ERROR       = -1, //< An error occurred during the operation.
    FLASH_STATUS_TIMEOUT     = -2, //< The operation timed out.
    FLASH_STATUS_BAD_ADDRESS = -3, //< The address is out of bounds.
    FLASH_STATUS_BUSY        = -4, //< The flash is busy.
};

/**
 * @brief The status of a flash operation.
 */
typedef int16_t flash_status_t;

/**
 * @brief Initializes the flash driver.
 *
 * This function initializes the flash driver and prepares it for use.
 * It should be called before any other flash-related functions are used.
 */
void flash_init(void);

/**
 * @brief Checks if the flash is busy.
 *
 * This function checks if the flash is currently busy with an operation.
 *
 * @return FLASH_STATUS_SUCCESS if the flash is not busy, FLASH_STATUS_BUSY if the flash is busy, or FLASH_STATUS_ERROR if an error occurred.
 */
flash_status_t flash_is_busy(void);

/**
 * @brief Initiates a chip erase operation.
 *
 * This function does not wait for the flash to become ready.
 *
 * @return FLASH_STATUS_SUCCESS if the erase command was successfully sent, FLASH_STATUS_TIMEOUT if the flash is busy, or FLASH_STATUS_ERROR if an error occurred.
 */
flash_status_t flash_begin_erase_chip(void);

/**
 * @brief Waits for the chip erase operation to complete.
 *
 * This function waits for the chip erase operation to complete.
 *
 * @return FLASH_STATUS_SUCCESS if the chip erase operation completed successfully, FLASH_STATUS_TIMEOUT if the flash was still busy, or FLASH_STATUS_ERROR if an error occurred.
 */
flash_status_t flash_wait_erase_chip(void);

/**
 * @brief Erases the entire flash memory chip.
 *
 * This function initiates an erase operation to erase the entire flash memory chip.
 * It waits for the operation to complete.
 *
 * @return FLASH_STATUS_SUCCESS if the erase was successfully executed, FLASH_STATUS_TIMEOUT if the flash is busy, or FLASH_STATUS_ERROR if an error occurred.
 */
flash_status_t flash_erase_chip(void);

/**
 * @brief Erases a block of flash memory.
 *
 * This function initiates an erase operation to erase a block of flash memory.
 * It waits for the operation to complete.
 *
 * @param addr The address of the block to erase.
 *
 * @return FLASH_STATUS_SUCCESS if the erase was successfully executed, FLASH_STATUS_TIMEOUT if the flash is busy, or FLASH_STATUS_ERROR if an error occurred.
 */
flash_status_t flash_erase_block(uint32_t addr);

/**
 * @brief Erases a sector of flash memory.
 *
 * This function initiates an erase operation to erase a sector of flash memory.
 * It waits for the operation to complete.
 *
 * @param addr The address of the sector to erase.
 *
 * @return FLASH_STATUS_SUCCESS if the erase was successfully executed, FLASH_STATUS_TIMEOUT if the flash is busy, or FLASH_STATUS_ERROR if an error occurred.
 */
flash_status_t flash_erase_sector(uint32_t addr);

/**
 * @brief Reads a range of flash memory.
 *
 * This function reads a range of flash memory into a buffer.
 *
 * @param addr The address of the range to read.
 * @param buf A pointer to the buffer to read the range into.
 * @param len The length of the range to read.
 *
 * @return FLASH_STATUS_SUCCESS if the range was successfully read, FLASH_STATUS_BAD_ADDRESS if the address is out of bounds, FLASH_STATUS_TIMEOUT if the flash is busy, or FLASH_STATUS_ERROR if an error occurred.
 */
flash_status_t flash_read_range(uint32_t addr, void *buf, size_t len);

/**
 * @brief Writes a range of flash memory.
 *
 * This function writes a range of flash memory from a buffer.
 *
 * @param addr The address of the range to write.
 * @param buf A pointer to the buffer to write to the range.
 * @param len The length of the range to write.
 *
 * @return FLASH_STATUS_SUCCESS if the range was successfully written, FLASH_STATUS_BAD_ADDRESS if the address is out of bounds, FLASH_STATUS_TIMEOUT if the flash is busy, or FLASH_STATUS_ERROR if an error occurred.
 */
flash_status_t flash_write_range(uint32_t addr, const void *buf, size_t len);

#ifdef __cplusplus
}
#endif
