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
 *  Special application to extract an EEPROM image stored in FLASH memory, and
 *  copy it to the device EEPROM. This application is designed to be used with
 *  the HID build system module of LUFA to program the EEPROM of a target device
 *  that uses the HID bootloader protocol, which does not have native EEPROM
 *  programming support.
 */

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

/* References to the binary EEPROM data linked in the AVR's FLASH memory space */
extern const char _binary_InputEEData_bin_start[];
extern const char _binary_InputEEData_bin_end[];
extern const char _binary_InputEEData_bin_size[];

/* Friendly names for the embedded binary data stored in FLASH memory space */
#define InputEEData       _binary_InputEEData_bin_start
#define InputEEData_size  ((int)_binary_InputEEData_bin_size)

int main(void)
{
	/* Copy out the embedded EEPROM data from FLASH to EEPROM memory space */
	for (uint16_t i = 0; i < InputEEData_size; i++)
	  eeprom_update_byte((uint8_t*)i, pgm_read_byte(&InputEEData[i]));

	/* Infinite loop once complete */
	for (;;);
}
