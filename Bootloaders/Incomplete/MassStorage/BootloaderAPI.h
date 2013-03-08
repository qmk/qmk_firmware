/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

		#include "Config/AppConfig.h"

	/* Function Prototypes: */
		void    BootloaderAPI_ErasePage(const uint32_t Address);
		void    BootloaderAPI_WritePage(const uint32_t Address);
		void    BootloaderAPI_FillWord(const uint32_t Address, const uint16_t Word);
		uint8_t BootloaderAPI_ReadSignature(const uint16_t Address);
		uint8_t BootloaderAPI_ReadFuse(const uint16_t Address);
		uint8_t BootloaderAPI_ReadLock(void);
		void    BootloaderAPI_WriteLock(const uint8_t LockBits);

#endif

