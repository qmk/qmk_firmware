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
 *  Header file for IP.c.
 */
 
#ifndef _IP_H_
#define _IP_H_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>
		
		#include "EthernetProtocols.h"
		#include "Ethernet.h"
		#include "ProtocolDecoders.h"
	
	/* Macros: */
		/** Protocol IP address of the host (client) machine, once assigned by DHCP */
		#define CLIENT_IP_ADDRESS                { 10,     0,    0,    1}

		/** Protocol IP address of the virtual server machine */
		#define SERVER_IP_ADDRESS                { 10,     0,    0,    2}

		/** Protocol IP address of the broadcase address */
		#define BROADCAST_IP_ADDRESS             {0xFF, 0xFF, 0xFF, 0xFF}

		/** Default Time To Live (TTL) value for sent packets, indicating the maximum allowable hops until their destination is reached */
		#define DEFAULT_TTL                      128
		
		/** Performs a comparison between two IP addresses, indicating if they are identical.
		 *  
		 *  \param IP1  First IP address
		 *  \param IP2  Second IP address
		 *
		 *  \return True if the addresses match, false otherwise
		 */
		#define IP_COMPARE(IP1, IP2)             (memcmp(IP1, IP2, sizeof(IP_Address_t)) == 0)
		
	/* Type Defines: */
		/** Type define of an IP packet header. */
		typedef struct
		{
			unsigned int  HeaderLength   : 4; /**< Total length of the packet header, in 4-byte blocks */
			unsigned int  Version        : 4; /**< IP protocol version */
			unsigned int  TypeOfService  : 8; /**< Special service type identifier, indicating delay/throughput/reliability levels */
			unsigned int  TotalLength    : 16; /**< Total length of the IP packet, in bytes */

			unsigned int  Identification : 16; /**< Idenfication value for identifying fragmented packets */
			unsigned int  FragmentOffset : 13; /**< Offset of this IP fragment */
			unsigned int  Flags          : 3; /**< Fragment flags, to indicate if a packet is fragmented */

			unsigned int  TTL            : 8; /**< Maximum allowable number of hops to reach the packet destination */
			unsigned int  Protocol       : 8; /**< Encapsulated protocol type */
			unsigned int  HeaderChecksum : 16; /**< Ethernet checksum of the IP header */
			
			IP_Address_t  SourceAddress; /**< Source protocol IP address of the packet */
			IP_Address_t  DestinationAddress; /**< Destination protocol IP address of the packet */
		} IP_Header_t;
		
	/* Function Prototypes: */
		int16_t IP_ProcessIPPacket(void* InDataStart, void* OutDataStart);

#endif
