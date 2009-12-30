/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for IP.c.
 */

#ifndef _UDP_H_
#define _UDP_H_

	/* Includes: */
		#include <avr/io.h>
	
		#include "EthernetProtocols.h"
		#include "Ethernet.h"
		#include "ProtocolDecoders.h"
		#include "DHCP.h"
	
	/* Macros: */
		/** Source UDP port for a DHCP request */
		#define UDP_PORT_DHCP_REQUEST 67

		/** Destination UDP port for a DHCP reply */
		#define UDP_PORT_DHCP_REPLY   68

	/* Type Defines: */
		/** Type define for a UDP packet header */
		typedef struct
		{
			uint16_t SourcePort; /**< Packet source port */
			uint16_t DestinationPort; /**< Packet destination port */
			uint16_t Length; /**< Total packet length, in bytes */
			uint16_t Checksum; /**< Optional UDP packet checksum */
		} UDP_Header_t;
		
	/* Function Prototypes: */
		int16_t UDP_ProcessUDPPacket(void* IPHeaderInStart, void* UDPHeaderInStart, void* UDPHeaderOutStart);

#endif
