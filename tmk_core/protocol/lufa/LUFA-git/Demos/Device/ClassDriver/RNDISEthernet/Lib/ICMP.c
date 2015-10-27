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
 *  Internet Control Message Protocol (ICMP) packet handling routines. This protocol handles
 *  Echo requests from the host, to indicate a successful network connection between the host
 *  and the virtual server.
 */

#include "ICMP.h"

/** Processes an ICMP packet inside an Ethernet frame, and writes the appropriate response
 *  to the output Ethernet frame if the host is issuing a ICMP ECHO request.
 *
 *  \param[in] FrameIN        Pointer to the incoming Ethernet frame information structure
 *  \param[in] InDataStart    Pointer to the start of the incoming packet's ICMP header
 *  \param[out] OutDataStart  Pointer to the start of the outgoing packet's ICMP header
 *
 *  \return The number of bytes written to the out Ethernet frame if any, NO_RESPONSE otherwise
 */
int16_t ICMP_ProcessICMPPacket(Ethernet_Frame_Info_t* const FrameIN,
                               void* InDataStart,
                               void* OutDataStart)
{
	ICMP_Header_t* ICMPHeaderIN  = (ICMP_Header_t*)InDataStart;
	ICMP_Header_t* ICMPHeaderOUT = (ICMP_Header_t*)OutDataStart;

	DecodeICMPHeader(InDataStart);

	/* Determine if the ICMP packet is an echo request (ping) */
	if (ICMPHeaderIN->Type == ICMP_TYPE_ECHOREQUEST)
	{
		/* Fill out the ICMP response packet */
		ICMPHeaderOUT->Type     = ICMP_TYPE_ECHOREPLY;
		ICMPHeaderOUT->Code     = 0;
		ICMPHeaderOUT->Checksum = 0;
		ICMPHeaderOUT->Id       = ICMPHeaderIN->Id;
		ICMPHeaderOUT->Sequence = ICMPHeaderIN->Sequence;

		intptr_t DataSize = FrameIN->FrameLength - ((((intptr_t)InDataStart + sizeof(ICMP_Header_t)) - (intptr_t)FrameIN->FrameData));

		/* Copy the remaining payload to the response - echo requests should echo back any sent data */
		memmove(&((uint8_t*)OutDataStart)[sizeof(ICMP_Header_t)],
		        &((uint8_t*)InDataStart)[sizeof(ICMP_Header_t)],
			    DataSize);

		ICMPHeaderOUT->Checksum = Ethernet_Checksum16(ICMPHeaderOUT, (DataSize + sizeof(ICMP_Header_t)));

		/* Return the size of the response so far */
		return (DataSize + sizeof(ICMP_Header_t));
	}

	return NO_RESPONSE;
}

