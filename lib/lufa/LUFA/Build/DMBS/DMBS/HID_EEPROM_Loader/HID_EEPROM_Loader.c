/*
             DMBS Build System
      Released into the public domain.

   dean [at] fourwalledcubicle [dot] com
         www.fourwalledcubicle.com
 */

/** \file
 *
 *  Special application to extract an EEPROM image stored in FLASH memory, and
 *  copy it to the device EEPROM. This application is designed to be used with
 *  the HID build system module of DMBS to program the EEPROM of a target device
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
