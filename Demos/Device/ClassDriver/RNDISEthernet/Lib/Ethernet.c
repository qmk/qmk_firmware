/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Ethernet frame packet handling routines. This protocol handles the processing of raw Ethernet
 *  frames sent and received, deferring the processing of subpacket protocols to the appropriate
 *  protocol handlers, such as DHCP or ARP.
 */
 
#include "Ethernet.h"

/** Constant for convenience when checking against or setting a MAC address to the virtual server MAC address. */
const MAC_Address_t ServerMACAddress    = {SERVER_MAC_ADDRESS};

/** Constant for convenience when checking against or setting an IP address to the virtual server IP address. */
const IP_Address_t  ServerIPAddress     = {SERVER_IP_ADDRESS};

/** Constant for convenience when checking against or setting a MAC address to the broadcast MAC address. */
const MAC_Address_t BroadcastMACAddress = {BROADCAST_MAC_ADDRESS};

/** Constant for convenience when checking against or setting a IP address to the broadcast IP address. */
const IP_Address_t  BroadcastIPAddress  = {BROADCAST_IP_ADDRESS};

/** Constant for convenience when checking against or setting an IP address to the client (host) IP address. */
const IP_Address_t  ClientIPAddress     = {CLIENT_IP_ADDRESS};


/** Processes an incoming Ethernet frame, and writes the appropriate response to the output Ethernet
 *  frame buffer if the sub protocol handlers create a valid response.
 */
void Ethernet_ProcessPacket(Ethernet_Frame_Info_t* FrameIN, Ethernet_Frame_Info_t* FrameOUT)
{
	DecodeEthernetFrameHeader(FrameIN);

	/* Cast the incoming Ethernet frame to the Ethernet header type */
	Ethernet_Frame_Header_t* FrameINHeader  = (Ethernet_Frame_Header_t*)&FrameIN->FrameData;
	Ethernet_Frame_Header_t* FrameOUTHeader = (Ethernet_Frame_Header_t*)&FrameOUT->FrameData;
	
	int16_t                  RetSize        = NO_RESPONSE;
	
	/* Ensure frame is addressed to either all (broadcast) or the virtual webserver, and is a type II frame */
	if ((MAC_COMPARE(&FrameINHeader->Destination, &ServerMACAddress) ||
	     MAC_COMPARE(&FrameINHeader->Destination, &BroadcastMACAddress)) &&
		 (SwapEndian_16(FrameIN->FrameLength) > ETHERNET_VER2_MINSIZE))
	{
		/* Process the packet depending on its protocol */
		switch (SwapEndian_16(FrameINHeader->EtherType))
		{
			case ETHERTYPE_ARP:
				RetSize = ARP_ProcessARPPacket(&FrameIN->FrameData[sizeof(Ethernet_Frame_Header_t)],
				                               &FrameOUT->FrameData[sizeof(Ethernet_Frame_Header_t)]);
				break;		
			case ETHERTYPE_IPV4:
				RetSize = IP_ProcessIPPacket(FrameIN,
				                             &FrameIN->FrameData[sizeof(Ethernet_Frame_Header_t)],
				                             &FrameOUT->FrameData[sizeof(Ethernet_Frame_Header_t)]);
				break;
		}
		
		/* Protocol processing routine has filled a response, complete the ethernet frame header */
		if (RetSize > 0)
		{
			/* Fill out the response Ethernet frame header */
			FrameOUTHeader->Source          = ServerMACAddress;
			FrameOUTHeader->Destination     = FrameINHeader->Source;
			FrameOUTHeader->EtherType       = FrameINHeader->EtherType;
			
			/* Set the response length in the buffer and indicate that a response is ready to be sent */
			FrameOUT->FrameLength           = (sizeof(Ethernet_Frame_Header_t) + RetSize);
			FrameOUT->FrameInBuffer         = true;
		}
	}

	/* Check if the packet was processed */
	if (RetSize != NO_PROCESS)
	{
		/* Clear the frame buffer */
		FrameIN->FrameInBuffer = false;
	}
}

/** Calculates the appropriate ethernet checksum, consisting of the addition of the one's
 *  compliment of each word, complimented.
 *
 *  \param[in] Data   Pointer to the packet buffer data whose checksum must be calculated
 *  \param[in] Bytes  Number of bytes in the data buffer to process
 *
 *  \return A 16-bit Ethernet checksum value
 */
uint16_t Ethernet_Checksum16(void* Data, uint16_t Bytes)
{
	uint16_t* Words    = (uint16_t*)Data;
	uint32_t  Checksum = 0;

	for (uint8_t CurrWord = 0; CurrWord < (Bytes >> 1); CurrWord++)
	  Checksum += Words[CurrWord];
	  
	while (Checksum & 0xFFFF0000)
	  Checksum = ((Checksum & 0xFFFF) + (Checksum >> 16));
	
	return ~Checksum;
}
