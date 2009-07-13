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

#ifndef _PRINTER_COMMANDS_H_
#define _PRINTER_COMMANDS_H_

	/* Includes: */
		#include <avr/io.h>

		#include <LUFA/Drivers/USB/USB.h>

	/* Macros: */
		#define PROTOCOL_UNIDIRECTIONAL      0x01
		#define PROTOCOL_BIDIRECTIONAL       0x02
		#define PROTOCOL_IEEE1284            0x03
		
		#define GET_DEVICE_ID                0
		#define GET_PORT_STATUS              1
		#define SOFT_RESET                   2

	/* Type Defines: */
		typedef struct
		{
			uint16_t Length;
			uint8_t  String[128];
		} Device_ID_String_t;
		
	/* Function Prototypes: */
		uint8_t Printer_GetDeviceID(Device_ID_String_t* DeviceIDString);
		uint8_t Printer_GetPortStatus(uint8_t* PortStatus);
		uint8_t Printer_SoftReset(void);
	
#endif
