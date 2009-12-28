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
 *  Header file for PrinterCommands.c.
 */
 
#ifndef _PRINTER_COMMANDS_H_
#define _PRINTER_COMMANDS_H_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>

		#include <LUFA/Drivers/USB/USB.h>

	/* Macros: */
		/** Printer class-specific request to retrieve the printer's ID string */
		#define REQ_GetDeviceID              0

		/** Printer class-specific request to retrieve the printer's virtual port status flags */
		#define REQ_GetPortStatus            1

		/** Printer class-specific request to soft-reset the device */
		#define REQ_SoftReset                2

		/** Pipe number of the Printer data IN pipe */
		#define PRINTER_DATA_IN_PIPE         1

		/** Pipe number of the Printer data OUT pipe */
		#define PRINTER_DATA_OUT_PIPE        2
		
	/* Function Prototypes: */
		uint8_t Printer_SendData(void* PrinterCommands, uint16_t CommandSize);
		uint8_t Printer_GetDeviceID(char* DeviceIDString, uint16_t BufferSize);
		uint8_t Printer_GetPortStatus(uint8_t* PortStatus);
		uint8_t Printer_SoftReset(void);
	
#endif
