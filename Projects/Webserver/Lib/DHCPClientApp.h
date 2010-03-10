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
 *  Header file for DHCPClientApp.c.
 */

#ifndef _DHCPCLIENT_APP_H_
#define _DHCPCLIENT_APP_H_

	/* Includes: */
		#include <stdio.h>
		
		#include <uip.h>
		
		#include "../Webserver.h"
		
	/* Macros: */
		/** UDP listen port for a BOOTP server */
		#define DHCPC_SERVER_PORT         67

		/** UDP listen port for a BOOTP client */
		#define DHCPC_CLIENT_PORT         68

		/** BOOTP message type for a BOOTP REQUEST message */
		#define DHCP_OP_BOOTREQUEST       0x01

		/** BOOTP message type for a BOOTP REPLY message */
		#define DHCP_OP_BOOTREPLY         0x02

		/** BOOTP flag for a BOOTP broadcast message */
		#define BOOTP_BROADCAST           0x8000
		
		/** Magic DHCP cookie for a BOOTP message to identify it as a DHCP message */
		#define DHCP_MAGIC_COOKIE         0x63538263
		
		/** Unique transaction ID used to identify DHCP responses to the client */
		#define DHCP_TRANSACTION_ID       0x13245466

		/** DHCP message type for a DISCOVER message */
		#define DHCP_DISCOVER             1

		/** DHCP message type for an OFFER message */
		#define DHCP_OFFER                2

		/** DHCP message type for a REQUEST message */
		#define DHCP_REQUEST              3

		/** DHCP message type for a DECLINE message */
		#define DHCP_DECLINE              4

		/** DHCP message type for an ACK message */
		#define DHCP_ACK                  5

		/** DHCP message type for a NAK message */
		#define DHCP_NAK                  6

		/** DHCP message type for a RELEASE message */
		#define DHCP_RELEASE              7

		/** DHCP medium type for standard Ethernet */
		#define DHCP_HTYPE_ETHERNET       1

		/** DHCP message option for the network subnet mask */
		#define DHCP_OPTION_SUBNET_MASK   1

		/** DHCP message option for the network gateway IP */
		#define DHCP_OPTION_ROUTER        3

		/** DHCP message option for the network DNS server */
		#define DHCP_OPTION_DNS_SERVER    6

		/** DHCP message option for the requested client IP address */
		#define DHCP_OPTION_REQ_IPADDR    50

		/** DHCP message option for the IP address lease time */
		#define DHCP_OPTION_LEASE_TIME    51

		/** DHCP message option for the DHCP message type */
		#define DHCP_OPTION_MSG_TYPE      53
		
		/** DHCP message option for the DHCP server IP */		
		#define DHCP_OPTION_SERVER_ID     54

		/** DHCP message option for the list of required options from the server */
		#define DHCP_OPTION_REQ_LIST      55

		/** DHCP message option for the options list terminator */
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
		/** States for each DHCP connection to a DHCP client. */
		enum DHCP_States_t
		{
			DHCP_STATE_SendDiscover,  /**< Send DISCOVER packet to retrieve DHCP lease offers */
			DHCP_STATE_WaitForOffer,  /**< Waiting for OFFER packet giving available DHCP leases */
			DHCP_STATE_SendRequest,   /**< Send REQUEST packet to request a DHCP lease */
			DHCP_STATE_WaitForACK,    /**< Wait for ACK packet to complete the DHCP lease */
			DHCP_STATE_AddressLeased, /**< DHCP address has been leased from a DHCP server */
		};

	/* Function Prototypes: */
		void DHCPClientApp_Init(void);
		void DHCPClientApp_Callback(void);
		
		#if defined(INCLUDE_FROM_DHCPCLIENTAPP_C)
			static uint16_t DHCPClientApp_FillDHCPHeader(DHCP_Header_t* DHCPHeader, uint8_t DHCPMessageType,
			                                             uip_udp_appstate_t* AppState);
			static uint8_t  DHCPClientApp_SetOption(uint8_t* DHCPOptionList, uint8_t Option, uint8_t DataLen,
			                                        void* OptionData);
			static bool     DHCPClientApp_GetOption(uint8_t* DHCPOptionList, uint8_t Option, void* Destination);
		#endif
#endif
