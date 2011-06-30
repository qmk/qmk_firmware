/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for AndroidAccessoryCommands.c.
 */

#ifndef _ANDROID_ACCESSORY_COMMANDS_H_
#define _ANDROID_ACCESSORY_COMMANDS_H_

	/* Includes: */
		#include <stdint.h>
		#include <stdbool.h>

		#include <LUFA/Drivers/USB/USB.h>

	/* Enums: */
		enum Android_Requests_t
		{
			ANDROID_Req_GetAccessoryProtocol    = 51,
			ANDROID_Req_SendString              = 52,
			ANDROID_Req_StartAccessoryMode      = 53,
		};

		enum Android_Strings_t
		{
			ANDROID_STRING_Manufacturer         = 0,
			ANDROID_STRING_Model                = 1,
			ANDROID_STRING_Description          = 2,
			ANDROID_STRING_Version              = 3,
			ANDROID_STRING_URI                  = 4,
			ANDROID_STRING_Serial               = 5,
		};
		
		enum Android_Protocols_t
		{
			ANDROID_PROTOCOL_Accessory          = 0x0001,
		};
	
	/* Function Prototypes: */
		uint8_t Android_GetAccessoryProtocol(uint16_t* const Protocol);
		uint8_t Android_SendString(const uint8_t StringIndex,
		                           char* String);
		uint8_t Android_StartAccessoryMode(void);	
	
#endif
