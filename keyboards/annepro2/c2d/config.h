/*
 * Copyright 2026 BHE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include "pin_defs.h"

#define LINE_BT_UART_TX A4 // Master TX, BLE RX
#define LINE_BT_UART_RX A5 // Master RX, BLE TX

/*
 * AP2D KEY 3.08 writes 0x0000FAB2 to the final word of its 16 KiB RAM
 * before resetting into IAP.
 */
#define ANNEPRO2_IAP_MAGIC_LOCATION 0x20003ffc

/* AP2D always ships with the BLE 2.13 transport. */
#define ANNEPRO2_BLE_PROFILE ANNEPRO2_BLE_PROFILE_AP2D_213

#define PERMISSIVE_HOLD

// External SPI flash configuration retained from the HT32F52352 platform.
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A0
#define SPI_MOSI_PIN A1
#define SPI_MISO_PIN A2

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN A3
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 16
#define EXTERNAL_FLASH_PAGE_SIZE 256
#define EXTERNAL_FLASH_SECTOR_SIZE 4096
#define EXTERNAL_FLASH_BLOCK_SIZE 4096
#define EXTERNAL_FLASH_SIZE (256 * 1024)
