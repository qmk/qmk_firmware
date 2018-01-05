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
 *  Header file for AndroidAccessoryCommands.c.
 */

#ifndef _ANDROID_ACCESSORY_COMMANDS_H_
#define _ANDROID_ACCESSORY_COMMANDS_H_

	/* Includes: */
		#include <stdint.h>
		#include <stdbool.h>

		#include <LUFA/Drivers/USB/USB.h>

	/* Function Prototypes: */
		uint8_t Android_GetAccessoryProtocol(uint16_t* const Protocol);
		uint8_t Android_SendString(const uint8_t StringIndex,
		                           const char* const String);
		uint8_t Android_StartAccessoryMode(void);

#endif

