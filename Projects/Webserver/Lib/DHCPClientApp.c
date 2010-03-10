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

#if defined(ENABLE_DHCP_CLIENT) || defined(__DOXYGEN__)

/** \file
 *
 *  DHCP Client Application. When connected to the uIP stack, this will retrieve IP configuration settings from the
 *  DHCP server on the network.
 */

#define  INCLUDE_FROM_DHCPCLIENTAPP_C
#include "DHCPClientApp.h"

/** Initialization function for the DHCP client. */
void DHCPClientApp_Init(void)
{
	/* Create a new UDP connection to the DHCP server port for the DHCP solicitation */
	struct uip_udp_conn* Connection = uip_udp_new(&uip_broadcast_addr, HTONS(DHCPC_SERVER_PORT));
	
	/* If the connection was successfully created, bind it to the local DHCP client port */
	if (Connection != NULL)
	{
		uip_udp_appstate_t* const AppState = &Connection->appstate;
		uip_udp_bind(Connection, HTONS(DHCPC_CLIENT_PORT));
		
		/* Set the initial client state */
		AppState->DHCPClient.CurrentState = DHCP_STATE_SendDiscover;

		/* Set timeout period to half a second for a DHCP server to respond */
		timer_set(&AppState->DHCPClient.Timeout, CLOCK_SECOND / 2);
	}
}
 
/** uIP stack application callback for the DHCP client. This function must be called each time the TCP/IP stack 
 *  needs a UDP packet to be processed.
 */
void DHCPClientApp_Callback(void)
{
	uip_udp_appstate_t* const AppState    = &uip_udp_conn->appstate;
	DHCP_Header_t*      const AppData     = (DHCP_Header_t*)uip_appdata;
	uint16_t                  AppDataSize = 0;
	
	switch (AppState->DHCPClient.CurrentState)
	{
		case DHCP_STATE_SendDiscover:
			/* Clear all DHCP settings, reset client IP address */
			memset(&AppState->DHCPClient.DHCPOffer_Data, 0x00, sizeof(AppState->DHCPClient.DHCPOffer_Data));
			uip_sethostaddr((uip_ipaddr_t*)&AppState->DHCPClient.DHCPOffer_Data.AllocatedIP);

			/* Fill out the DHCP response header */
			AppDataSize += DHCPClientApp_FillDHCPHeader(AppData, DHCP_DISCOVER, AppState);
			
			/* Add the required DHCP options list to the packet */
			uint8_t RequiredOptionList[] = {DHCP_OPTION_SUBNET_MASK, DHCP_OPTION_ROUTER, DHCP_OPTION_DNS_SERVER};
			AppDataSize += DHCPClientApp_SetOption(AppData->Options, DHCP_OPTION_REQ_LIST, sizeof(RequiredOptionList),
			                                       RequiredOptionList);			
			
			/* Send the DHCP DISCOVER packet */
			uip_udp_send(AppDataSize);

			/* Reset the timeout timer, progress to next state */
			timer_reset(&AppState->DHCPClient.Timeout);
			AppState->DHCPClient.CurrentState = DHCP_STATE_WaitForOffer;			
			
			break;
		case DHCP_STATE_WaitForOffer:
			if (!(uip_newdata()))
			{
				/* Check if the DHCP timeout period has expired while waiting for a response */
				if (timer_expired(&AppState->DHCPClient.Timeout))
				  AppState->DHCPClient.CurrentState = DHCP_STATE_SendDiscover;
				
				break;
			}
			  
			uint8_t OfferResponse_MessageType;
			if ((AppData->TransactionID == DHCP_TRANSACTION_ID) &&
			    DHCPClientApp_GetOption(AppData->Options, DHCP_OPTION_MSG_TYPE, &OfferResponse_MessageType) &&
			    (OfferResponse_MessageType == DHCP_OFFER))
			{
				/* Received a DHCP offer for an IP address, copy over values for later request */
				memcpy(&AppState->DHCPClient.DHCPOffer_Data.AllocatedIP, &AppData->YourIP, sizeof(uip_ipaddr_t));
				DHCPClientApp_GetOption(AppData->Options, DHCP_OPTION_SUBNET_MASK, &AppState->DHCPClient.DHCPOffer_Data.Netmask);
				DHCPClientApp_GetOption(AppData->Options, DHCP_OPTION_ROUTER,      &AppState->DHCPClient.DHCPOffer_Data.GatewayIP);
				DHCPClientApp_GetOption(AppData->Options, DHCP_OPTION_SERVER_ID,   &AppState->DHCPClient.DHCPOffer_Data.ServerIP);
				
				timer_reset(&AppState->DHCPClient.Timeout);
				AppState->DHCPClient.CurrentState = DHCP_STATE_SendRequest;
			}

			break;
		case DHCP_STATE_SendRequest:
			/* Fill out the DHCP response header */
			AppDataSize += DHCPClientApp_FillDHCPHeader(AppData, DHCP_REQUEST, AppState);

			/* Add the DHCP REQUESTED IP ADDRESS option to the packet */
			AppDataSize += DHCPClientApp_SetOption(AppData->Options, DHCP_OPTION_REQ_IPADDR, sizeof(uip_ipaddr_t),
			                                       &AppState->DHCPClient.DHCPOffer_Data.AllocatedIP);

			/* Add the DHCP SERVER IP ADDRESS option to the packet */
			AppDataSize += DHCPClientApp_SetOption(AppData->Options, DHCP_OPTION_SERVER_ID, sizeof(uip_ipaddr_t),
			                                       &AppState->DHCPClient.DHCPOffer_Data.ServerIP);

			/* Send the DHCP REQUEST packet */
			uip_udp_send(AppDataSize);
			
			/* Reset the timeout timer, progress to next state */
			timer_reset(&AppState->DHCPClient.Timeout);
			AppState->DHCPClient.CurrentState = DHCP_STATE_WaitForACK;

			break;
		case DHCP_STATE_WaitForACK:
			if (!(uip_newdata()))
			{
				/* Check if the DHCP timeout period has expired while waiting for a response */
				if (timer_expired(&AppState->DHCPClient.Timeout))
				  AppState->DHCPClient.CurrentState = DHCP_STATE_SendDiscover;
				
				break;
			}
			
			uint8_t RequestResponse_MessageType;
			if ((AppData->TransactionID == DHCP_TRANSACTION_ID) &&
			    DHCPClientApp_GetOption(AppData->Options, DHCP_OPTION_MSG_TYPE, &RequestResponse_MessageType) &&
			    (RequestResponse_MessageType == DHCP_ACK))
			{
				/* Set the new network parameters from the DHCP server */
				uip_sethostaddr((uip_ipaddr_t*)&AppState->DHCPClient.DHCPOffer_Data.AllocatedIP);
				uip_setnetmask((uip_ipaddr_t*)&AppState->DHCPClient.DHCPOffer_Data.Netmask);
				uip_setdraddr((uip_ipaddr_t*)&AppState->DHCPClient.DHCPOffer_Data.GatewayIP);
			
				/* Indicate to the user that we now have a valid IP configuration */
				HaveIPConfiguration = true;

				AppState->DHCPClient.CurrentState = DHCP_STATE_AddressLeased;				
			}
			
			break;
	}
}

/** Fills the DHCP packet response with the appropriate BOOTP header for DHCP. This fills out all the required
 *  fields, leaving only the additional DHCP options to be added to the packet before it is sent to the DHCP server.
 *
 *  \param[out] DHCPHeader  Location in the packet buffer where the BOOTP header should be written to
 *  \param[in]  DHCPMessageType  DHCP Message type, such as DHCP_DISCOVER
 *  \param[in]  AppState    Application state of the current UDP connection
 *
 *  \return Size in bytes of the created DHCP packet
 */
static uint16_t DHCPClientApp_FillDHCPHeader(DHCP_Header_t* DHCPHeader, uint8_t DHCPMessageType, uip_udp_appstate_t* AppState)
{
	/* Erase existing packet data so that we start will all 0x00 DHCP header data */
 	memset(DHCPHeader, 0, sizeof(DHCP_Header_t));

	/* Fill out the DHCP packet header */
	DHCPHeader->Operation             = DHCP_OP_BOOTREQUEST;
	DHCPHeader->HardwareType          = DHCP_HTYPE_ETHERNET;
	DHCPHeader->HardwareAddressLength = sizeof(MACAddress);
	DHCPHeader->Hops                  = 0;
	DHCPHeader->TransactionID         = DHCP_TRANSACTION_ID;
	DHCPHeader->ElapsedSeconds        = 0;
	DHCPHeader->Flags                 = HTONS(BOOTP_BROADCAST);
	memcpy(&DHCPHeader->ClientIP,     &uip_hostaddr,        sizeof(uip_ipaddr_t));
	memcpy(&DHCPHeader->YourIP,       &AppState->DHCPClient.DHCPOffer_Data.AllocatedIP, sizeof(uip_ipaddr_t));
	memcpy(&DHCPHeader->NextServerIP, &AppState->DHCPClient.DHCPOffer_Data.ServerIP,    sizeof(uip_ipaddr_t));
	memcpy(&DHCPHeader->ClientHardwareAddress, &MACAddress, sizeof(struct uip_eth_addr));
	DHCPHeader->Cookie                = DHCP_MAGIC_COOKIE;
	
	/* Add a DHCP message type and terminator options to the start of the DHCP options field */
	DHCPHeader->Options[0]            = DHCP_OPTION_MSG_TYPE;
	DHCPHeader->Options[1]            = 1;
	DHCPHeader->Options[2]            = DHCPMessageType;
	DHCPHeader->Options[3]            = DHCP_OPTION_END;
	
	/* Calculate the total number of bytes added to the outgoing packet */
	return (sizeof(DHCP_Header_t) + 4);
}

/** Sets the given DHCP option in the DHCP packet's option list. This automatically moves the
 *  end of options terminator past the new option in the options list.
 *
 *  \param[in,out] DHCPOptionList  Pointer to the start of the DHCP packet's options list
 *  \param[in]     Option          DHCP option to add to the list
 *  \param[in]     DataLen         Size in bytes of the option data to add
 *  \param[in]     OptionData      Buffer where the option's data is to be sourced from
 *
 *  \return Number of bytes added to the DHCP packet
 */
static uint8_t DHCPClientApp_SetOption(uint8_t* DHCPOptionList, uint8_t Option, uint8_t DataLen, void* OptionData)
{
	/* Skip through the DHCP options list until the terminator option is found */
	while (*DHCPOptionList != DHCP_OPTION_END)
	  DHCPOptionList += (DHCPOptionList[1] + 2);

	/* Overwrite the existing terminator with the new option, add a new terminator at the end of the list */
	DHCPOptionList[0] = Option;
	DHCPOptionList[1] = DataLen;
	memcpy(&DHCPOptionList[2], OptionData, DataLen);
	DHCPOptionList[2 + DataLen] = DHCP_OPTION_END;
	
	/* Calculate the total number of bytes added to the outgoing packet */
	return (2 + DataLen);
}

/** Retrieves the given option's data (if present) from the DHCP packet's options list.
 *
 *  \param[in,out] DHCPOptionList  Pointer to the start of the DHCP packet's options list
 *  \param[in]     Option          DHCP option to retrieve to the list
 *  \param[out]    Destination     Buffer where the option's data is to be written to if found
 *
 *  \return Boolean true if the option was found in the DHCP packet's options list, false otherwise
 */
static bool DHCPClientApp_GetOption(uint8_t* DHCPOptionList, uint8_t Option, void* Destination)
{
	/* Look through the incoming DHCP packet's options list for the requested option */
	while (*DHCPOptionList != DHCP_OPTION_END)
	{
		/* Check if the current DHCP option in the packet is the one requested */
		if (DHCPOptionList[0] == Option)
		{
			/* Copy request option's data to the destination buffer */
			memcpy(Destination, &DHCPOptionList[2], DHCPOptionList[1]);
			
			/* Indicate that the requested option data was successfully retrieved */
			return true;
		}
		
		/* Skip to next DHCP option in the options list */
		DHCPOptionList += (DHCPOptionList[1] + 2);
	}
	
	/* Requested option not found in the incoming packet's DHCP options list */
	return false;
}
#endif
