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
 *  Header file for ICMP.c.
 */

#ifndef _ICMP_H_
#define _ICMP_H_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>

		#include "EthernetProtocols.h"
		#include "Ethernet.h"
		#include "ProtocolDecoders.h"

	/* Macros: */
		/** ICMP message type constant, indicating an ICMP ECHO Reply message. */
		#define ICMP_TYPE_ECHOREPLY              0

		/** ICMP message type constant, indicating a packet destination is unreachable. */
		#define ICMP_TYPE_DESTINATIONUNREACHABLE 3

		/** ICMP message type constant, indicating an ICMP Source Quench message. */
		#define ICMP_TYPE_SOURCEQUENCH           4

		/** ICMP message type constant, indicating an ICMP Redirect message. */
		#define ICMP_TYPE_REDIRECTMESSAGE        5

		/** ICMP message type constant, indicating an ICMP ECHO Request message. */
		#define ICMP_TYPE_ECHOREQUEST            8

		/** ICMP message type constant, indicating an ICMP Time Exceeded message. */
		#define ICMP_TYPE_TIMEEXCEEDED           11

	/* Type Defines: */
		/** Type define for an ICMP message header. */
		typedef struct
		{
			uint8_t       Type; /**< ICMP message type, an \c ICMP_TYPE_* constant */
			uint8_t       Code; /**< ICMP message code, indicating the message value */
			uint16_t      Checksum; /**< Ethernet checksum of the ICMP message */
			uint16_t      Id; /**< Id of the ICMP message */
			uint16_t      Sequence; /**< Sequence number of the ICMP message, to link together message responses */
		} ICMP_Header_t;

	/* Function Prototypes: */
		int16_t ICMP_ProcessICMPPacket(void* InDataStart,
		                               void* OutDataStart);

#endif

