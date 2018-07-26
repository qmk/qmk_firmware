/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for DHCP.c.
 */

#ifndef _DHCP_H_
#define _DHCP_H_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>

		#include "EthernetProtocols.h"
		#include "Ethernet.h"
		#include "ProtocolDecoders.h"

	/* Macros: */
		/** DHCP operation constant, indicating a request from a host to a DHCP server. */
		#define DHCP_OP_BOOTREQUEST       0x01

		/** DHCP operation constant, indicating a reply from a DHCP server to a host. */
		#define DHCP_OP_BOOTREPLY         0x02

		/** Hardware type constant, indicating Ethernet as a carrier. */
		#define DHCP_HTYPE_ETHERNET       0x01

		/** Magic boot protocol "cookie", inserted into all BOOTP packets (BOOTP is the carrier of DHCP). */
		#define DHCP_MAGIC_COOKIE         0x63825363

		/** DHCP option list entry header, indicating that a subnet mask will follow. */
		#define DHCP_OPTION_SUBNETMASK    1

		/** DHCP option list entry header, indicating that the Lease Time will follow. */
		#define DHCP_OPTION_LEASETIME     51

		/** DHCP option list entry header, indicating that the DHCP message type constant will follow. */
		#define DHCP_OPTION_MESSAGETYPE   53

		/** DHCP option list entry header, indicating that the IP address of the DHCP server will follow. */
		#define DHCP_OPTION_DHCPSERVER    54

		/** DHCP option list entry header, used to pad out option data. */
		#define DHCP_OPTION_PAD           0

		/** DHCP option list entry header, indicating the end of option data. */
		#define DHCP_OPTION_END           255

		/** Message type constant, used in the DHCP option data field, requesting that a DHCP server offer an IP address. */
		#define DHCP_MESSAGETYPE_DISCOVER 1

		/** Message type constant, used in the DHCP option data field, indicating that a DHCP server is offering an IP address. */
		#define DHCP_MESSAGETYPE_OFFER    2

		/** Message type constant, used in the DHCP option data field, requesting that a DHCP server lease a given IP address. */
		#define DHCP_MESSAGETYPE_REQUEST  3

		/** Message type constant, used in the DHCP option data field, declining an offered DHCP server IP address lease. */
		#define DHCP_MESSAGETYPE_DECLINE  4

		/** Message type constant, used in the DHCP option data field, ACKing a host IP lease request. */
		#define DHCP_MESSAGETYPE_ACK      5

		/** Message type constant, used in the DHCP option data field, NACKing a host IP lease request. */
		#define DHCP_MESSAGETYPE_NACK     6

		/** Message type constant, used in the DHCP option data field, indicating that a host is releasing a leased IP address. */
		#define DHCP_MESSAGETYPE_RELEASE  7

	/* Type Defines: */
		/** Type define for a DHCP packet inside an Ethernet frame. */
		typedef struct
		{
			uint8_t  Operation; /**< DHCP operation, either DHCP_OP_BOOTREQUEST or DHCP_OP_BOOTREPLY */
			uint8_t  HardwareType; /**< Hardware carrier type constant */
			uint8_t  HardwareAddressLength;  /**< Length in bytes of a hardware (MAC) address on the network */
			uint8_t  Hops; /**< Number of hops required to reach the server, unused */

			uint32_t TransactionID; /**< Unique ID of the DHCP packet, for positive matching between sent and received packets */

			uint16_t ElapsedSeconds; /**< Elapsed seconds since the request was made */
			uint16_t Flags; /**< BOOTP packet flags */

			IP_Address_t ClientIP; /**< Client IP address, if already leased an IP */
			IP_Address_t YourIP; /**< Client IP address */
			IP_Address_t NextServerIP; /**< Legacy BOOTP protocol field, unused for DHCP */
			IP_Address_t RelayAgentIP; /**< Legacy BOOTP protocol field, unused for DHCP */

			uint8_t ClientHardwareAddress[16]; /**< Hardware (MAC) address of the client making a request to the DHCP server */
			uint8_t ServerHostnameString[64]; /**< Legacy BOOTP protocol field, unused for DHCP */
			uint8_t BootFileName[128]; /**< Legacy BOOTP protocol field, unused for DHCP */

			uint32_t Cookie; /**< Magic BOOTP protocol cookie to indicate a valid packet */
		} DHCP_Header_t;

	/* Function Prototypes: */
		int16_t DHCP_ProcessDHCPPacket(void* IPHeaderInStart,
		                               void* DHCPHeaderInStart,
		                               void* DHCPHeaderOutStart);

#endif

