/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
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
 *  Header file for BootloaderCDC.c.
 */
 
#ifndef _CDC_H_
#define _CDC_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/boot.h>
		#include <avr/eeprom.h>
		#include <avr/power.h>
		#include <stdbool.h>

		#include "Descriptors.h"

		#include <LUFA/Drivers/USB/USB.h>

	/* Macros: */
		/** CDC Class Specific request to get the line encoding on a CDC-ACM virtual serial port, including the
		 *  baud rate, parity, stop bits and data bits.
		 */
		#define REQ_GetLineEncoding          0x21

		/** CDC Class Specific request to set the line encoding on a CDC-ACM virtual serial port, including the
		 *  baud rate, parity, stop bits and data bits.
		 */
		#define REQ_SetLineEncoding          0x20

		/** CDC Class Specific request to set the state of the serial handshake lines (such as DCD and RTS) on
		 *  a CDC-ACM virtual serial port.
		 */
		#define REQ_SetControlLineState      0x22
		
		/** Version major of the CDC bootloader. */
		#define BOOTLOADER_VERSION_MAJOR     0x01

		/** Version minor of the CDC bootloader. */
		#define BOOTLOADER_VERSION_MINOR     0x00
				
		/** Hardware version major of the CDC bootloader. */
		#define BOOTLOADER_HWVERSION_MAJOR   0x01

		/** Hardware version minor of the CDC bootloader. */
		#define BOOTLOADER_HWVERSION_MINOR   0x00

		/** Eight character bootloader firmware identifier reported to the host when requested */
		#define SOFTWARE_IDENTIFIER          "LUFACDC"
		
	/* Type Defines: */
		/** Type define for a non-returning pointer to the start of the loaded application in flash memory. */
		typedef void (*AppPtr_t)(void) ATTR_NO_RETURN;

		/** Type define for the CDC-ACM virtual serial port line encoding options, including baud rate, format, parity
		 *  and size of each data chunk in bits.
		 */
		typedef struct
		{
			uint32_t BaudRateBPS; /**< Baud rate in BPS */
			uint8_t  CharFormat; /**< Character format, an entry from the BootloaderCDC_CDC_LineCodingFormats_t enum */
			uint8_t  ParityType; /**< Parity mode, an entry from the BootloaderCDC_CDC_LineCodeingParity_t enum */
			uint8_t  DataBits; /**< Size of each data chunk, in bits */
		} CDC_Line_Coding_t;
		
	/* Enums: */
		/** Enum for the possible line encoding formats on a CDC-ACM virtual serial port */
		enum BootloaderCDC_CDC_LineCodingFormats_t
		{
			OneStopBit          = 0, /**< Single stop bit */
			OneAndAHalfStopBits = 1, /**< 1.5 stop bits */
			TwoStopBits         = 2, /**< Two stop bits */
		};
		
		/** Enum for the possible parity modes on a CDC-ACM virtual serial port */
		enum BootloaderCDC_CDC_LineCodeingParity_t
		{
			Parity_None         = 0, /**< No data parity checking */
			Parity_Odd          = 1, /**< Odd data parity checking */
			Parity_Even         = 2, /**< Even data parity checking */
			Parity_Mark         = 3, /**< Mark data parity checking */
			Parity_Space        = 4, /**< Space data parity checking */
		};
		
	/* Function Prototypes: */
		void CDC_Task(void);
		void SetupHardware(void);
		void ResetHardware(void);

		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_UnhandledControlRequest(void);

		#if defined(INCLUDE_FROM_BOOTLOADERCDC_C) || defined(__DOXYGEN__)
			static void    ReadWriteMemoryBlock(const uint8_t Command);
			static uint8_t FetchNextCommandByte(void);
			static void    WriteNextResponseByte(const uint8_t Response);
		#endif

#endif
