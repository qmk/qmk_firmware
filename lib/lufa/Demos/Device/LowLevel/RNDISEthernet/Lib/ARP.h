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
 *  Header file for ARP.c.
 */

#ifndef _ARP_H_
#define _ARP_H_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>

		#include <LUFA/Drivers/USB/USB.h>

		#include "EthernetProtocols.h"
		#include "Ethernet.h"
		#include "ProtocolDecoders.h"

	/* Macros: */
		/** ARP header operation constant, indicating a request from a host for an address translation. */
		#define ARP_OPERATION_REQUEST            1

		/** ARP header operation constant, indicating a reply from a host giving an address translation. */
		#define ARP_OPERATION_REPLY              2

	/* Type Defines: */
		/** Type define for an ARP packet inside an Ethernet frame. */
		typedef struct
		{
			uint16_t      HardwareType; /**< Hardware type constant, indicating the hardware used */
			uint16_t      ProtocolType; /**< Protocol being resolved, usually ETHERTYPE_IPV4 */

			uint8_t       HLEN; /**< Length in bytes of the source/destination hardware addresses */
			uint8_t       PLEN; /**< Length in bytes of the source/destination protocol addresses */
			uint16_t      Operation; /**< Type of operation, either ARP_OPERATION_REQUEST or ARP_OPERATION_REPLY */

			MAC_Address_t SHA; /**< Sender's hardware address */
			IP_Address_t  SPA; /**< Sender's protocol address */
			MAC_Address_t THA; /**< Target's hardware address */
			IP_Address_t  TPA; /**< Target's protocol address */
		} ARP_Header_t;

	/* Function Prototypes: */
		int16_t ARP_ProcessARPPacket(void* InDataStart,
		                             void* OutDataStart);

#endif

