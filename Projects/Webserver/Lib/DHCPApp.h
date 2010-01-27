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
 *  Header file for DHCPApp.c.
 */

#ifndef _DHCP_APP_H_
#define _DHCP_APP_H_

	/* Includes: */
		#include <stdio.h>
		
		#include <uip.h>
		
		#include "../Webserver.h"
		
	/* Macros: */
		#define DHCPC_SERVER_PORT         67
		#define DHCPC_CLIENT_PORT         68

		#define DHCP_OP_BOOTREQUEST       0x01
		#define DHCP_OP_BOOTREPLY         0x02

		#define BOOTP_BROADCAST           0x8000
		
		#define DHCP_MAGIC_COOKIE         0x63538263
		
		#define DHCP_TRANSACTION_ID       0x13245466

		#define DHCP_DISCOVER             1
		#define DHCP_OFFER                2
		#define DHCP_REQUEST              3
		#define DHCP_DECLINE              4
		#define DHCP_ACK                  5
		#define DHCP_NAK                  6
		#define DHCP_RELEASE              7

		#define DHCP_HTYPE_ETHERNET       1

		#define DHCP_OPTION_SUBNET_MASK   1
		#define DHCP_OPTION_ROUTER        3
		#define DHCP_OPTION_DNS_SERVER    6
		#define DHCP_OPTION_REQ_IPADDR    50
		#define DHCP_OPTION_LEASE_TIME    51
		#define DHCP_OPTION_MSG_TYPE      53
		#define DHCP_OPTION_SERVER_ID     54
		#define DHCP_OPTION_REQ_LIST      55
		#define DHCP_OPTION_END           255

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
			
			uip_ipaddr_t ClientIP; /**< Client IP address, if already leased an IP */
			uip_ipaddr_t YourIP; /**< Client IP address */
			uip_ipaddr_t NextServerIP; /**< Legacy BOOTP protocol field, unused for DHCP */
			uip_ipaddr_t RelayAgentIP; /**< Legacy BOOTP protocol field, unused for DHCP */
			
			uint8_t ClientHardwareAddress[16]; /**< Hardware (MAC) address of the client making a request to the DHCP server */
			uint8_t ServerHostnameString[64]; /**< Legacy BOOTP protocol field, unused for DHCP */
			uint8_t BootFileName[128]; /**< Legacy BOOTP protocol field, unused for DHCP */
			
			uint32_t Cookie; /**< Magic BOOTP protocol cookie to indicate a valid packet */
			
			uint8_t  Options[]; /** DHCP message options */
		} DHCP_Header_t;

	/* Enums: */
		enum DHCP_States_t
		{
			DHCP_STATE_SendDiscover,
			DHCP_STATE_WaitForResponse,
			DHCP_STATE_SendRequest,
			DHCP_STATE_WaitForACK,
			DHCP_STATE_AddressLeased,
		};

	/* Function Prototypes: */
		void DHCPApp_Init(void);
		void DHCPApp_Callback(void);
		
		uint16_t DHCPApp_FillDHCPHeader(DHCP_Header_t* DHCPHeader, uint8_t DHCPMessageType, uip_udp_appstate_t* AppState);
		uint8_t  DHCPApp_SetOption(uint8_t* DHCPOptionList, uint8_t Option, uint8_t DataLen, void* Source);
		bool     DHCPApp_GetOption(uint8_t* DHCPOptionList, uint8_t Option, void* Destination);
		
#endif
