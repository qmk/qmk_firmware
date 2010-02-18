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
 *  uIP Management functions. This file contains the functions and globals needed to maintain the uIP
 *  stack once an RNDIS device has been attached to the system.
 */

#define  INCLUDE_FROM_UIPMANAGEMENT_C
#include "uIPManagement.h"

/** Connection timer, to retain the time elapsed since the last time the uIP connections were managed. */
struct timer ConnectionTimer;

/** ARP timer, to retain the time elapsed since the ARP cache was last updated. */
struct timer ARPTimer;

/** MAC address of the RNDIS device, when enumerated */
struct uip_eth_addr MACAddress;


/** Configures the uIP stack ready for network traffic. */
void uIPManagement_Init(void)
{
	/* uIP Timing Initialization */
	clock_init();
	timer_set(&ConnectionTimer, CLOCK_SECOND / 2);
	timer_set(&ARPTimer, CLOCK_SECOND * 10);	

	/* uIP Stack Initialization */
	uip_init();
	uip_arp_init();
	uip_setethaddr(MACAddress);

	/* DHCP/Server IP Settings Initialization */
	#if defined(ENABLE_DHCP_CLIENT)
	DHCPClientApp_Init();
	#else
	uip_ipaddr_t IPAddress, Netmask, GatewayIPAddress;
	uip_ipaddr(&IPAddress,        DEVICE_IP_ADDRESS[0], DEVICE_IP_ADDRESS[1], DEVICE_IP_ADDRESS[2], DEVICE_IP_ADDRESS[3]);
	uip_ipaddr(&Netmask,          DEVICE_NETMASK[0],    DEVICE_NETMASK[1],    DEVICE_NETMASK[2],    DEVICE_NETMASK[3]);
	uip_ipaddr(&GatewayIPAddress, DEVICE_GATEWAY[0],    DEVICE_GATEWAY[1],    DEVICE_GATEWAY[2],    DEVICE_GATEWAY[3]);
	uip_sethostaddr(&IPAddress);
	uip_setnetmask(&Netmask);
	uip_setdraddr(&GatewayIPAddress);
	#endif
	
	/* HTTP Webserver Initialization */
	HTTPServerApp_Init();
	
	/* TELNET Server Initialization */
	TELNETServerApp_Init();
}

/** uIP Management function. This function manages the uIP stack when called while an RNDIS device has been
 *  attached to the system.
 */
void uIPManagement_ManageNetwork(void)
{
	if ((USB_CurrentMode == USB_MODE_HOST) && (USB_HostState == HOST_STATE_Configured))
	{
		uIPManagement_ProcessIncomingPacket();
		uIPManagement_ManageConnections();
	}
}

/** uIP TCP/IP network stack callback function for the processing of a given TCP connection. This routine dispatches
 *  to the appropriate TCP protocol application based on the connection's listen port number.
 */
void uIPManagement_TCPCallback(void)
{
	/* Call the correct TCP application based on the port number the connection is listening on */
	switch (uip_conn->lport)
	{
		case HTONS(HTTP_SERVER_PORT):
			HTTPServerApp_Callback();
			break;
		case HTONS(TELNET_SERVER_PORT):
			TELNETServerApp_Callback();
			break;
	}
}

/** uIP TCP/IP network stack callback function for the processing of a given UDP connection. This routine dispatches
 *  to the appropriate UDP protocol application based on the connection's listen port number.
 */
void uIPManagement_UDPCallback(void)
{
	/* Call the correct UDP application based on the port number the connection is listening on */
	switch (uip_udp_conn->lport)
	{
		case HTONS(DHCPC_CLIENT_PORT):
			DHCPClientApp_Callback();
			break;
	}
}

/** Processes Incoming packets to the server from the connected RNDIS device, creating responses as needed. */
static void uIPManagement_ProcessIncomingPacket(void)
{
	/* If no packet received, exit processing routine */
	if (!(RNDIS_Host_IsPacketReceived(&Ethernet_RNDIS_Interface)))
	  return;
	  
	LEDs_SetAllLEDs(LEDMASK_USB_BUSY);

	/* Read the Incoming packet straight into the UIP packet buffer */
	RNDIS_Host_ReadPacket(&Ethernet_RNDIS_Interface, uip_buf, &uip_len);

	/* If the packet contains an Ethernet frame, process it */
	if (uip_len > 0)
	{
		switch (((struct uip_eth_hdr*)uip_buf)->type)
		{
			case HTONS(UIP_ETHTYPE_IP):
				/* Filter packet by MAC destination */
				uip_arp_ipin();

				/* Process Incoming packet */
				uip_input();

				/* If a response was generated, send it */
				if (uip_len > 0)
				{
					/* Add destination MAC to outgoing packet */
					uip_arp_out();

					uip_split_output();
				}
				
				break;
			case HTONS(UIP_ETHTYPE_ARP):
				/* Process ARP packet */
				uip_arp_arpin();
				
				/* If a response was generated, send it */
				if (uip_len > 0)
				  uip_split_output();
				
				break;
		}
	}

	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Manages the currently open network connections, including TCP and (if enabled) UDP. */
static void uIPManagement_ManageConnections(void)
{
	/* Poll TCP connections for more data to send back to the host */
	for (uint8_t i = 0; i < UIP_CONNS; i++)
	{
		uip_poll_conn(&uip_conns[i]);

		/* If a response was generated, send it */
		if (uip_len > 0)
		{
			/* Add destination MAC to outgoing packet */
			uip_arp_out();

			/* Split and send the outgoing packet */
			uip_split_output();
		}
	}

	/* Manage open connections for timeouts */
	if (timer_expired(&ConnectionTimer))
	{
		timer_reset(&ConnectionTimer);

		LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
		
		for (uint8_t i = 0; i < UIP_CONNS; i++)
		{
			/* Run periodic connection management for each TCP connection */
			uip_periodic(i);

			/* If a response was generated, send it */
			if (uip_len > 0)
			{
				/* Add destination MAC to outgoing packet */
				uip_arp_out();

				/* Split and send the outgoing packet */
				uip_split_output();
			}
		}
		
		#if defined(ENABLE_DHCP_CLIENT)
		for (uint8_t i = 0; i < UIP_UDP_CONNS; i++)
		{
			/* Run periodic connection management for each UDP connection */
			uip_udp_periodic(i);

			/* If a response was generated, send it */
			if (uip_len > 0)
			{
				/* Add destination MAC to outgoing packet */
				uip_arp_out();

				/* Split and send the outgoing packet */
				uip_split_output();
			}
		}
		#endif

		LEDs_SetAllLEDs(LEDMASK_USB_READY);
	}

	/* Manage ARP cache refreshing */
	if (timer_expired(&ARPTimer))
	{
		timer_reset(&ARPTimer);
		uip_arp_timer();
	}
}
