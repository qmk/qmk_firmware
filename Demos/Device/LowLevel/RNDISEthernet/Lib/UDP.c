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
 *  User Datagram Protocol (UDP) packet handling routines. This protocol handles high throughput, low
 *  reliability packets which are typically used to encapsulate streaming data.
 */

#define  INCLUDE_FROM_UDP_C
#include "UDP.h"

/** Processes a UDP packet inside an Ethernet frame, and writes the appropriate response
 *  to the output Ethernet frame if a sub-protocol handler has created a response packet.
 *
 *  \param[in] IPHeaderInStart     Pointer to the start of the incoming packet's IP header
 *  \param[in] UDPHeaderInStart    Pointer to the start of the incoming packet's UDP header
 *  \param[out] UDPHeaderOutStart  Pointer to the start of the outgoing packet's UDP header
 *
 *  \return The number of bytes written to the out Ethernet frame if any, NO_RESPONSE otherwise
 */
int16_t UDP_ProcessUDPPacket(void* IPHeaderInStart,
                             void* UDPHeaderInStart,
                             void* UDPHeaderOutStart)
{
	UDP_Header_t* UDPHeaderIN  = (UDP_Header_t*)UDPHeaderInStart;
	UDP_Header_t* UDPHeaderOUT = (UDP_Header_t*)UDPHeaderOutStart;

	int16_t RetSize = NO_RESPONSE;

	DecodeUDPHeader(UDPHeaderInStart);

	switch (SwapEndian_16(UDPHeaderIN->DestinationPort))
	{
		case UDP_PORT_DHCP_REQUEST:
			RetSize = DHCP_ProcessDHCPPacket(IPHeaderInStart,
			                                 &((uint8_t*)UDPHeaderInStart)[sizeof(UDP_Header_t)],
		                                     &((uint8_t*)UDPHeaderOutStart)[sizeof(UDP_Header_t)]);
			break;
	}

	/* Check to see if the protocol processing routine has filled out a response */
	if (RetSize > 0)
	{
		/* Fill out the response UDP packet header */
		UDPHeaderOUT->SourcePort      = UDPHeaderIN->DestinationPort;
		UDPHeaderOUT->DestinationPort = UDPHeaderIN->SourcePort;
		UDPHeaderOUT->Checksum        = 0;
		UDPHeaderOUT->Length          = SwapEndian_16(sizeof(UDP_Header_t) + RetSize);

		/* Return the size of the response so far */
		return (sizeof(UDP_Header_t) + RetSize);
	}

	return NO_RESPONSE;
}

