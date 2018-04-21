/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Bootloader user application API functions.
 */

#include "BootloaderAPI.h"

void BootloaderAPI_ErasePage(const uint32_t Address)
{
	boot_page_erase_safe(Address);
	boot_spm_busy_wait();
	boot_rww_enable();
}

void BootloaderAPI_WritePage(const uint32_t Address)
{
	boot_page_write_safe(Address);
	boot_spm_busy_wait();
	boot_rww_enable();
}

void BootloaderAPI_FillWord(const uint32_t Address, const uint16_t Word)
{
	boot_page_fill_safe(Address, Word);
}

uint8_t BootloaderAPI_ReadSignature(const uint16_t Address)
{
	return boot_signature_byte_get(Address);
}

uint8_t BootloaderAPI_ReadFuse(const uint16_t Address)
{
	return boot_lock_fuse_bits_get(Address);
}

uint8_t BootloaderAPI_ReadLock(void)
{
	return boot_lock_fuse_bits_get(GET_LOCK_BITS);
}

void BootloaderAPI_WriteLock(const uint8_t LockBits)
{
	boot_lock_bits_set_safe(LockBits);
}
