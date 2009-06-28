/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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
 *  Header file for Ethernet.c.
 */
 
#ifndef _ETHERNET_H_
#define _ETHERNET_H_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>

		#include "EthernetProtocols.h"
		#include "ProtocolDecoders.h"
		#include "ICMP.h"
		#include "TCP.h"
		#include "UDP.h"
		#include "DHCP.h"
		#include "ARP.h"
		#include "IP.h"
		
	/* Macros: */
		/** Physical MAC address of the virtual server on the network */
		#define SERVER_MAC_ADDRESS               {0x00, 0x01, 0x00, 0x01, 0x00, 0x01}		

		/** Physical MAC address of the network broadcast address */
		#define BROADCAST_MAC_ADDRESS            {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
	
		/** Performs a comparison between two MAC addresses, indicating if they are identical.
		 *  
		 *  \param[in] MAC1  First MAC address
		 *  \param[in] MAC2  Second MAC address
		 *
		 *  \return True if the addresses match, false otherwise
		 */
		#define MAC_COMPARE(MAC1, MAC2)          (memcmp(MAC1, MAC2, sizeof(MAC_Address_t)) == 0)

		/** Maximum size of an incoming or outgoing Ethernet frame in bytes */
		#define ETHERNET_FRAME_SIZE_MAX          1500
		
		/** Minimum size of an Ethernet packet in bytes, to conform to the Ethernet V2 packet standard */
		#define ETHERNET_VER2_MINSIZE            0x0600
		
		/** Return value for all sub protocol handling routines, indicating that no response packet has been generated */
		#define NO_RESPONSE                      0		

		/** Return value for all sub protocol handling routines, indicating that the packet has not yet been handled */
		#define NO_PROCESS                       -1

	/* Type Defines: */
		/** Type define for an Ethernet frame buffer. */
		typedef struct
		{
			uint8_t       FrameData[ETHERNET_FRAME_SIZE_MAX]; /**< Ethernet frame contents */
			uint16_t      FrameLength; /**< Length in bytes of the Ethernet frame stored in the buffer */
			bool          FrameInBuffer; /**< Indicates if a frame is currently stored in the buffer */
		} Ethernet_Frame_Info_t;

		/** Type define for an Ethernet frame header */
		typedef struct
		{
			MAC_Address_t Destination; /**< Physical MAC address of the packet recipient */
			MAC_Address_t Source; /**< Physics MAC address of the packet source */
			
			union
			{
				uint16_t  EtherType; /**< Ethernet packet subprotocol type, for Ethernet V2 packets */
				uint16_t  Length; /**< Ethernet frame length, for Ethernet V1 packets */
			};
		} Ethernet_Frame_Header_t;
		
	/* External Variables: */
		extern Ethernet_Frame_Info_t FrameIN;
		extern Ethernet_Frame_Info_t FrameOUT;

		extern const MAC_Address_t ServerMACAddress;
		extern const IP_Address_t  ServerIPAddress;
		extern const MAC_Address_t BroadcastMACAddress;
		extern const IP_Address_t  BroadcastIPAddress;
		extern const IP_Address_t  ClientIPAddress;
		
	/* Function Prototypes: */
		void     Ethernet_ProcessPacket(void);
		uint16_t Ethernet_Checksum16(void* Data, uint16_t Bytes);
		
#endif
