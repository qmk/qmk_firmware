/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
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
 *  Header file for BootloaderDFU.c.
 */

#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/boot.h>
		#include <avr/pgmspace.h>
		#include <avr/eeprom.h>
		#include <avr/power.h>
		#include <stdbool.h>
	
		#include "Descriptors.h"
		
		#include <LUFA/Drivers/USB/USB.h>
	
	/* Macros: */
		/** Configuration define. Define this token to true to case the bootloader to reject all memory commands
		 *  until a memory erase has been performed. When used in conjunction with the lockbits of the AVR, this
		 *  can protect the AVR's firmware from being dumped from a secured AVR. When false, memory operations are
		 *  allowed at any time.
		 */
		#define SECURE_MODE              false

		/** Major bootloader version number. */
		#define BOOTLOADER_VERSION_MINOR 2

		/** Minor bootloader version number. */
		#define BOOTLOADER_VERSION_REV   0

		/** Complete bootloader version number expressed as a packed byte, constructed from the 
		 *  two individual bootloader version macros.
		 */
		#define BOOTLOADER_VERSION       ((BOOTLOADER_VERSION_MINOR << 4) | BOOTLOADER_VERSION_REV)

		/** First byte of the bootloader identification bytes, used to identify a device's bootloader. */
		#define BOOTLOADER_ID_BYTE1      0xDC

		/** Second byte of the bootloader identification bytes, used to identify a device's bootloader. */
		#define BOOTLOADER_ID_BYTE2      0xFB
		
		/** Convenience macro, used to determine if the issued command is the given one-byte long command.
		 *
		 *  \param[in] dataarr  Command byte array to check against
		 *  \param[in] cb1      First command byte to check
		 */
		#define IS_ONEBYTE_COMMAND(dataarr, cb1)       (dataarr[0] == (cb1))

		/** Convenience macro, used to determine if the issued command is the given two-byte long command.
		 *
		 *  \param[in] dataarr  Command byte array to check against
		 *  \param[in] cb1      First command byte to check
		 *  \param[in] cb2      Second command byte to check
		 */
		#define IS_TWOBYTE_COMMAND(dataarr, cb1, cb2) ((dataarr[0] == (cb1)) && (dataarr[1] == (cb2)))
	
		/** Length of the DFU file suffix block, appended to the end of each complete memory write command.
		 *  The DFU file suffix is currently unused (but is designed to give extra file information, such as
		 *  a CRC of the complete firmware for error checking) and so is discarded.
		 */
		#define DFU_FILE_SUFFIX_SIZE     16

		/** Length of the DFU file filler block, appended to the start of each complete memory write command.
		 *  Filler bytes are added to the start of each complete memory write command, and must be discarded.
		 */
		#define DFU_FILLER_BYTES_SIZE    26
	
		/** DFU class command request to detach from the host. */
		#define DFU_DETATCH              0x00

		/** DFU class command request to send data from the host to the bootloader. */
		#define DFU_DNLOAD               0x01

		/** DFU class command request to send data from the bootloader to the host. */
		#define DFU_UPLOAD               0x02

		/** DFU class command request to get the current DFU status and state from the bootloader. */
		#define DFU_GETSTATUS            0x03

		/** DFU class command request to reset the current DFU status and state variables to their defaults. */
		#define DFU_CLRSTATUS            0x04

		/** DFU class command request to get the current DFU state of the bootloader. */
		#define DFU_GETSTATE             0x05

		/** DFU class command request to abort the current multi-request transfer and return to the dfuIDLE state. */
		#define DFU_ABORT                0x06

		/** DFU command to begin programming the device's memory. */
		#define COMMAND_PROG_START       0x01

		/** DFU command to begin reading the device's memory. */
		#define COMMAND_DISP_DATA        0x03

		/** DFU command to issue a write command. */
		#define COMMAND_WRITE            0x04

		/** DFU command to issue a read command. */
		#define COMMAND_READ             0x05

		/** DFU command to issue a memory base address change command, to set the current 64KB flash page
		 *  that subsequent flash operations should use. */
		#define COMMAND_CHANGE_BASE_ADDR 0x06

	/* Type Defines: */
		/** Type define for a non-returning function pointer to the loaded application. */
		typedef void (*AppPtr_t)(void) ATTR_NO_RETURN;
		
		/** Type define for a structure containing a complete DFU command issued by the host. */
		typedef struct
		{
			uint8_t  Command; /**< Single byte command to perform, one of the COMMAND_* macro values */
			uint8_t  Data[5]; /**< Command parameters */
			uint16_t DataSize; /**< Size of the command parameters */
		} DFU_Command_t;

	/* Enums: */
		/** DFU bootloader states. Refer to the DFU class specification for information on each state. */
		enum DFU_State_t
		{
			appIDLE                      = 0,
			appDETACH                    = 1,
			dfuIDLE                      = 2,
			dfuDNLOAD_SYNC               = 3,
			dfuDNBUSY                    = 4,
			dfuDNLOAD_IDLE               = 5,
			dfuMANIFEST_SYNC             = 6,
			dfuMANIFEST                  = 7,
			dfuMANIFEST_WAIT_RESET       = 8,
			dfuUPLOAD_IDLE               = 9,
			dfuERROR	                 = 10
		};

		/** DFU command status error codes. Refer to the DFU class specification for information on each error code. */
		enum DFU_Status_t
		{
			OK                           = 0,
			errTARGET                    = 1,
			errFILE                      = 2,
			errWRITE                     = 3,
			errERASE                     = 4,
			errCHECK_ERASED              = 5,
			errPROG                      = 6,
			errVERIFY                    = 7,
			errADDRESS                   = 8,
			errNOTDONE                   = 9,
			errFIRMWARE                  = 10,
			errVENDOR                    = 11,
			errUSBR                      = 12,
			errPOR                       = 13,
			errUNKNOWN                   = 14,
			errSTALLEDPKT	             = 15
		};
				
	/* Function Prototypes: */
		void SetupHardware(void);
		void ResetHardware(void);

		void EVENT_USB_Device_UnhandledControlRequest(void);

		#if defined(INCLUDE_FROM_BOOTLOADER_C)
			static void DiscardFillerBytes(uint8_t NumberOfBytes);
			static void ProcessBootloaderCommand(void);
			static void LoadStartEndAddresses(void);
			static void ProcessMemProgCommand(void);
			static void ProcessMemReadCommand(void);
			static void ProcessWriteCommand(void);
			static void ProcessReadCommand(void);
		#endif
		
#endif
