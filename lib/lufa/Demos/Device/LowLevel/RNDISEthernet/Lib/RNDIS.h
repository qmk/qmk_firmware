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
 *  Header file for RNDIS.c.
 */

#ifndef _RNDIS_H_
#define _RNDIS_H_

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>

		#include "../RNDISEthernet.h"
		#include "Ethernet.h"

	/* External Variables: */
		extern uint8_t                 RNDISMessageBuffer[];
		extern RNDIS_Message_Header_t* MessageHeader;
		extern bool                    ResponseReady;
		extern uint8_t                 CurrRNDISState;

	/* Function Prototypes: */
		void ProcessRNDISControlMessage(void);

		#if defined(INCLUDE_FROM_RNDIS_C)
			static bool ProcessNDISQuery(const uint32_t OId,
			                             void* QueryData,
			                             uint16_t QuerySize,
			                             void* ResponseData,
			                             uint16_t* ResponseSize);
			static bool ProcessNDISSet(const uint32_t OId,
			                           void* SetData,
			                           uint16_t SetSize);
		#endif

#endif

