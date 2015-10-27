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
 *  Header file for RNDISCommands.c.
 */

#ifndef _RNDIS_COMMANDS_H_
#define _RNDIS_COMMANDS_H_

	/* Includes: */
		#include <avr/io.h>
		#include <stdio.h>
		#include <string.h>

		#include <LUFA/Drivers/USB/USB.h>

		#include "../RNDISEthernetHost.h"

	/* Macros: */
		/** Additional error code for RNDIS functions when a device returns a logical command failure. */
		#define RNDIS_COMMAND_FAILED                  0xC0

	/* Function Prototypes: */
		uint8_t RNDIS_SendEncapsulatedCommand(void* const Buffer,
		                                      const uint16_t Length);
		uint8_t RNDIS_GetEncapsulatedResponse(void* const Buffer,
		                                      const uint16_t Length);

		uint8_t RNDIS_SendKeepAlive(void);
		uint8_t RNDIS_InitializeDevice(const uint16_t HostMaxPacketSize,
		                               uint16_t* const DeviceMaxPacketSize);
		uint8_t RNDIS_SetRNDISProperty(const uint32_t Oid,
		                               void* Buffer,
		                               const uint16_t Length);
		uint8_t RNDIS_QueryRNDISProperty(const uint32_t Oid,
		                                 void* Buffer,
		                                 const uint16_t MaxLength);
		uint8_t RNDIS_GetPacketLength(uint16_t* const PacketLength);

#endif

