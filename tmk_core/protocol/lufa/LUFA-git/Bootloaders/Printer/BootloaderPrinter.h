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
 *  Header file for BootloaderPrinter.c.
 */

#ifndef _BOOTLOADER_PRINTER_H_
#define _BOOTLOADER_PRINTER_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>

		#include "Descriptors.h"

		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Platform/Platform.h>

	/* Preprocessor Checks: */
		#if !defined(__OPTIMIZE_SIZE__)
			#error This bootloader requires that it be optimized for size, not speed, to fit into the target device. Change optimization settings and try again.
		#endif

	/* Macros: */
		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY       LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING   (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY         (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR         (LEDS_LED1 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is busy. */
		#define LEDMASK_USB_BUSY           LEDS_LED2

		/** Magic bootloader key to unlock forced application start mode. */
		#define MAGIC_BOOT_KEY             0xDC42

	/* Enums: */
		/** Intel HEX parser state machine states. */
		enum HEX_Parser_States_t
		{
			HEX_PARSE_STATE_WAIT_LINE,    /**< Parser is waiting for a HEX Start of Line character. */
			HEX_PARSE_STATE_BYTE_COUNT,   /**< Parser is waiting for a record byte count. */
			HEX_PARSE_STATE_ADDRESS_HIGH, /**< Parser is waiting for the MSB of a record address. */
			HEX_PARSE_STATE_ADDRESS_LOW,  /**< Parser is waiting for the LSB of a record address. */
			HEX_PARSE_STATE_RECORD_TYPE,  /**< Parser is waiting for the record type. */
			HEX_PARSE_STATE_READ_DATA,    /**< Parser is waiting for more data in the current record. */
			HEX_PARSE_STATE_CHECKSUM,     /**< Parser is waiting for the checksum of the current record. */
		};

		/** Intel HEX record types, used to indicate the type of record contained in a line of a HEX file. */
		enum HEX_Record_Types_t
		{
			HEX_RECORD_TYPE_Data                   = 0, /**< Record contains loadable data. */
			HEX_RECORD_TYPE_EndOfFile              = 1, /**< End of file record. */
			HEX_RECORD_TYPE_ExtendedSegmentAddress = 2, /**< Extended segment start record. */
			HEX_RECORD_TYPE_StartSegmentAddress    = 3, /**< Normal segment start record. */
			HEX_RECORD_TYPE_ExtendedLinearAddress  = 4, /**< Extended linear address start record. */
			HEX_RECORD_TYPE_StartLinearAddress     = 5, /**< Linear address start record. */
		};

	/* Function Prototypes: */
		static void SetupHardware(void);

		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_ControlRequest(void);

#endif

