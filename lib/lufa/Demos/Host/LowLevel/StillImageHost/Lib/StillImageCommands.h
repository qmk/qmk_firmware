/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for StillImageCommands.c.
 */

#ifndef _STILL_IMAGE_COMMANDS_H_
#define _STILL_IMAGE_COMMANDS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include "PIMACodes.h"
		#include "../StillImageHost.h"

	/* Macros: */
		/** Timeout period between the issuing of a command to a device, and the reception of the first packet. */
		#define COMMAND_DATA_TIMEOUT_MS        10000

	/* External Variables: */
		extern PIMA_Container_t PIMA_SendBlock;
		extern PIMA_Container_t PIMA_ReceivedBlock;
		extern PIMA_Container_t PIMA_EventBlock;

	/* Function Prototypes: */
		void    SImage_SendBlockHeader(void);
		uint8_t SImage_ReceiveBlockHeader(void);
		uint8_t SImage_ReceiveEventHeader(void);
		uint8_t SImage_SendData(void* const Buffer,
		                        const uint16_t Bytes);
		uint8_t SImage_ReadData(void* const Buffer,
		                        const uint16_t Bytes);
		bool    SImage_IsEventReceived(void);

#endif

