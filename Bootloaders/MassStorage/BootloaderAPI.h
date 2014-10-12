/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for BootloaderAPI.c.
 */

#ifndef _BOOTLOADER_API_H_
#define _BOOTLOADER_API_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/boot.h>
		#include <stdbool.h>

		#include <LUFA/Common/Common.h>

	/* Macros: */
		#if AUX_BOOT_SECTION_SIZE > 0
			#define AUX_BOOT_SECTION       __attribute__((section(".boot_aux")))
		#else
			#define AUX_BOOT_SECTION
		#endif

	/* User Application API: */
		/** [User Application API] */
		#define BOOTLOADER_API_TABLE_SIZE          32
		#define BOOTLOADER_API_TABLE_START         ((FLASHEND + 1UL) - BOOTLOADER_API_TABLE_SIZE)
		#define BOOTLOADER_API_CALL(Index)         (void*)((BOOTLOADER_API_TABLE_START + (Index * 2)) / 2)

		void    (*BootAPI_ErasePage)(uint32_t Address)               = BOOTLOADER_API_CALL(0);
		void    (*BootAPI_WritePage)(uint32_t Address)               = BOOTLOADER_API_CALL(1);
		void    (*BootAPI_FillWord)(uint32_t Address, uint16_t Word) = BOOTLOADER_API_CALL(2);
		uint8_t (*BootAPI_ReadSignature)(uint16_t Address)           = BOOTLOADER_API_CALL(3);
		uint8_t (*BootAPI_ReadFuse)(uint16_t Address)                = BOOTLOADER_API_CALL(4);
		uint8_t (*BootAPI_ReadLock)(void)                            = BOOTLOADER_API_CALL(5);
		void    (*BootAPI_WriteLock)(uint8_t LockBits)               = BOOTLOADER_API_CALL(6);

		#define BOOTLOADER_MAGIC_SIGNATURE_START   (BOOTLOADER_API_TABLE_START + (BOOTLOADER_API_TABLE_SIZE - 2))
		#define BOOTLOADER_MAGIC_SIGNATURE         0xDCFB

		#define BOOTLOADER_CLASS_SIGNATURE_START   (BOOTLOADER_API_TABLE_START + (BOOTLOADER_API_TABLE_SIZE - 4))
		#define BOOTLOADER_CDC_SIGNATURE           0xDF30

		#define BOOTLOADER_ADDRESS_START           (BOOTLOADER_API_TABLE_START + (BOOTLOADER_API_TABLE_SIZE - 8))
		#define BOOTLOADER_ADDRESS_LENGTH          4
		/** [User Application API] */

	/* Function Prototypes: */
		void    BootloaderAPI_ErasePage(const uint32_t Address);
		void    BootloaderAPI_WritePage(const uint32_t Address);
		void    BootloaderAPI_FillWord(const uint32_t Address, const uint16_t Word);
		uint8_t BootloaderAPI_ReadSignature(const uint16_t Address);
		uint8_t BootloaderAPI_ReadFuse(const uint16_t Address);
		uint8_t BootloaderAPI_ReadLock(void);
		void    BootloaderAPI_WriteLock(const uint8_t LockBits);

#endif

