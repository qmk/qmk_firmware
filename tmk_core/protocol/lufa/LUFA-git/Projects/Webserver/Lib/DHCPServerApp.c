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
 *  DHCP Server Application. When connected to the uIP stack, this will send IP configuration settings to a
 *  DHCP client on the network.
 */

#define  INCLUDE_FROM_DHCPSERVERAPP_C
#include "DHCPServerApp.h"

#if defined(ENABLE_DHCP_SERVER) || defined(__DOXYGEN__)

struct uip_conn* BroadcastConnection;

uint8_t LeasedIPs[255 / 8];

/** Initialization function for the DHCP server. */
void DHCPServerApp_Init(void)
{
	/* Listen on port 67 for DHCP server connections from hosts */
	uip_listen(HTONS(DHCP_SERVER_PORT));

	/* Create a new UDP connection to the DHCP server port for the DHCP solicitation */
	struct uip_udp_conn* BroadcastConnection = uip_udp_new(&uip_broadcast_addr, HTONS(DHCP_CLIENT_PORT));

	/* If the connection was successfully created, bind it to the local DHCP client port */
	if (BroadcastConnection != NULL)
	  uip_udp_bind(BroadcastConnection, HTONS(DHCP_SERVER_PORT));

	/* Set all IP addresses as unleased */
	memset(LeasedIPs, 0x00, sizeof(LeasedIPs));
}

/** uIP stack application callback for the DHCP server. This function must be called each time the TCP/IP stack
 *  needs a UDP packet to be processed.
 */
void DHCPServerApp_Callback(void)
{
	DHCP_Header_t* const AppData     = (DHCP_Header_t*)uip_appdata;
	uint16_t             AppDataSize = 0;

	/* Only process when new data arrives - don't retransmit lost packets */
	if (uip_newdata())
	{
		/* Get the DHCP message type (if present), otherwise early-abort */
		uint8_t DHCPMessageType;
		if (!(DHCPCommon_GetOption(AppData->Options, DHCP_OPTION_MSG_TYPE, &DHCPMessageType)))
			return;

		uip_ipaddr_t        Netmask, GatewayIPAddress, PreferredClientIP;
		struct uip_eth_addr RemoteMACAddress;
		uint32_t            TransactionID;

		/* Get configured network mask, gateway IP and extract out DHCP transaction ID and remote IP */
		uip_getnetmask(&Netmask);
		uip_getdraddr(&GatewayIPAddress);
		memcpy(&RemoteMACAddress, &AppData->ClientHardwareAddress, sizeof(struct uip_eth_addr));
		TransactionID = AppData->TransactionID;

		/* Try to extract out the client's preferred IP address if it is indicated in the packet */
		if (!(DHCPCommon_GetOption(AppData->Options, DHCP_OPTION_REQ_IPADDR, &PreferredClientIP)))
		  memcpy(&PreferredClientIP, &uip_all_zeroes_addr, sizeof(uip_ipaddr_t));

		switch (DHCPMessageType)
		{
			case DHCP_DISCOVER:
				/* If no preference was made or the preferred IP is already taken, find a new address */
				if (DHCPServerApp_CheckIfIPLeased(&PreferredClientIP))
				  DHCPServerApp_GetUnleasedIP(&PreferredClientIP);

				/* Create a new DHCP OFFER packet with the offered IP address */
				AppDataSize += DHCPServerApp_FillDHCPHeader(AppData, DHCP_OFFER, &RemoteMACAddress, &PreferredClientIP, TransactionID);

				/* Add network mask and router information to the list of DHCP OFFER packet options */
				AppDataSize += DHCPCommon_SetOption(AppData->Options, DHCP_OPTION_SUBNET_MASK,
													sizeof(uip_ipaddr_t), &Netmask);
				AppDataSize += DHCPCommon_SetOption(AppData->Options, DHCP_OPTION_ROUTER,
					                                sizeof(uip_ipaddr_t), &GatewayIPAddress);

				/* Send the DHCP OFFER packet */
				uip_poll_conn(BroadcastConnection);
				memcpy(&uip_udp_conn->ripaddr, &uip_broadcast_addr, sizeof(uip_ipaddr_t));
				uip_udp_send(AppDataSize);

				break;
			case DHCP_REQUEST:
				/* Check to see if the requested IP address has already been leased to a client */
				if (!(DHCPServerApp_CheckIfIPLeased(&PreferredClientIP)))
				{
					/* Create a new DHCP ACK packet to accept the IP address lease */
					AppDataSize += DHCPServerApp_FillDHCPHeader(AppData, DHCP_ACK, &RemoteMACAddress, &PreferredClientIP, TransactionID);

					/* Add network mask and router information to the list of DHCP ACK packet options */
					AppDataSize += DHCPCommon_SetOption(AppData->Options, DHCP_OPTION_SUBNET_MASK,
														sizeof(uip_ipaddr_t), &Netmask);
					AppDataSize += DHCPCommon_SetOption(AppData->Options, DHCP_OPTION_ROUTER,
					                                    sizeof(uip_ipaddr_t), &GatewayIPAddress);

					/* Mark the requested IP as leased to a client */
					DHCPServerApp_LeaseIP(&PreferredClientIP);
				}
				else
				{
					/* Create a new DHCP NAK packet to reject the requested allocation */
					AppDataSize += DHCPServerApp_FillDHCPHeader(AppData, DHCP_NAK, &RemoteMACAddress, &uip_all_zeroes_addr, TransactionID);
				}

				/* Send the DHCP ACK or NAK packet */
				uip_poll_conn(BroadcastConnection);
				memcpy(&uip_udp_conn->ripaddr, &uip_broadcast_addr, sizeof(uip_ipaddr_t));
				uip_udp_send(AppDataSize);

				break;
			case DHCP_RELEASE:
				/* Mark the IP address as released in the allocation table */
				DHCPServerApp_UnleaseIP(&uip_udp_conn->ripaddr);
				break;
		}
	}
}

/** Fills the DHCP packet response with the appropriate BOOTP header for DHCP. This fills out all the required
 *  fields, leaving only the additional DHCP options to be added to the packet before it is sent to the DHCP client.
 *
 *  \param[out] DHCPHeader             Location in the packet buffer where the BOOTP header should be written to
 *  \param[in]  DHCPMessageType        DHCP Message type, such as DHCP_DISCOVER
 *  \param[in]  ClientHardwareAddress  Client MAC address the created transaction should be directed to
 *  \param[in]  PreferredClientIP      Preferred IP that should be given to the client if it is unallocated
 *  \param[in]  TransactionID          Transaction ID the created transaction should be associated with
 *
 *  \return Size in bytes of the created DHCP packet
 */
static uint16_t DHCPServerApp_FillDHCPHeader(DHCP_Header_t* const DHCPHeader,
                                             const uint8_t DHCPMessageType,
                                             const struct uip_eth_addr* const ClientHardwareAddress,
											 const uip_ipaddr_t* const PreferredClientIP,
                                             const uint32_t TransactionID)
{
	/* Erase existing packet data so that we start will all 0x00 DHCP header data */
 	memset(DHCPHeader, 0, sizeof(DHCP_Header_t));

	DHCPHeader->Operation             = DHCPMessageType;
	DHCPHeader->HardwareType          = DHCP_HTYPE_ETHERNET;
	DHCPHeader->HardwareAddressLength = sizeof(MACAddress);
	DHCPHeader->Hops                  = 0;
	DHCPHeader->TransactionID         = TransactionID;
	DHCPHeader->ElapsedSeconds        = 0;
	DHCPHeader->Flags                 = 0;
	memcpy(&DHCPHeader->NextServerIP, &uip_hostaddr, sizeof(uip_ipaddr_t));
	memcpy(&DHCPHeader->YourIP, PreferredClientIP, sizeof(uip_ipaddr_t));
	memcpy(&DHCPHeader->ClientHardwareAddress, ClientHardwareAddress, sizeof(struct uip_eth_addr));
	DHCPHeader->Cookie                = DHCP_MAGIC_COOKIE;

	/* Add a DHCP message type and terminator options to the start of the DHCP options field */
	DHCPHeader->Options[0]            = DHCP_OPTION_MSG_TYPE;
	DHCPHeader->Options[1]            = 1;
	DHCPHeader->Options[2]            = DHCPMessageType;
	DHCPHeader->Options[3]            = DHCP_OPTION_END;

	/* Calculate the total number of bytes added to the outgoing packet */
	return (sizeof(DHCP_Header_t) + 4);
}

/** Checks to see if the nominated IP address has already been allocated to a client.
 *
 *  \param[in] IPAddress  IP Address whose lease status should be checked
 *
 *  \pre The IP address must be within the same /24 subnet as the virtual webserver.
 *
 *  \return Boolean \c true if the IP has already been leased to a client, \c false otherwise.
 */
static bool DHCPServerApp_CheckIfIPLeased(const uip_ipaddr_t* const IPAddress)
{
	uint8_t Byte = (IPAddress->u8[3] / 8);
	uint8_t Mask = (1 << (IPAddress->u8[3] % 8));

	/* Make sure that the requested IP address isn't already leased to the virtual server or another client */
	if (IPAddress->u8[3] && !(IPAddress->u8[3] == uip_hostaddr.u8[3]) && !(LeasedIPs[Byte] & Mask))
	  return false;
	else
	  return true;
}

/** Retrieves the next unleased IP in the IP address pool.
 *
 *  \param[out] NewIPAddress  Location where the generated IP Address should be stored
 */
static void DHCPServerApp_GetUnleasedIP(uip_ipaddr_t* const NewIPAddress)
{
	uip_ipaddr_copy(NewIPAddress, &uip_hostaddr);

	/** Look through the current subnet, skipping the broadcast and zero IP addresses */
	for (uint8_t IP = 1; IP < 254; IP++)
	{
		/* Update new IP address to lease with the current IP address to test */
		NewIPAddress->u8[3] = IP;

		/* If we've found an unleased IP, abort with the updated IP stored for the called */
		if (!(DHCPServerApp_CheckIfIPLeased(NewIPAddress)))
		  return;
	}
}

/** Marks the given IP Address as leased in the address pool, so that it will not be
 *  allocated to another client unless it is first released.
 *
 *  \param[in] IPAddress  IP Address to mark as leased
 *
 *  \pre The IP address must be within the same /24 subnet as the virtual webserver.
 */
static void DHCPServerApp_LeaseIP(const uip_ipaddr_t* const IPAddress)
{
	uint8_t Byte = (IPAddress->u8[3] / 8);
	uint8_t Mask = (1 << (IPAddress->u8[3] % 8));

	/* Mark the IP address as leased in the allocation table */
	LeasedIPs[Byte] |= Mask;
}

/** Marks the given IP Address as not leased in the address pool, so that it can be
 *  allocated to another client upon request.
 *
 *  \param[in] IPAddress  IP Address to mark as not leased
 *
 *  \pre The IP address must be within the same /24 subnet as the virtual webserver.
 */
static void DHCPServerApp_UnleaseIP(const uip_ipaddr_t* const IPAddress)
{
	uint8_t Byte = (IPAddress->u8[3] / 8);
	uint8_t Mask = (1 << (IPAddress->u8[3] % 8));

	/* Mark the IP address as unleased in the allocation table */
	LeasedIPs[Byte] &= ~Mask;
}
#endif

