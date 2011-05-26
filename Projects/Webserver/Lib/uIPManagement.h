/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for uIPManagement.c.
 */

#ifndef _UIP_MANAGEMENT_H_
#define _UIP_MANAGEMENT_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include <uip.h>
		#include <uip_arp.h>
		#include <uip-split.h>
		#include <timer.h>

		#include "Lib/DHCPClientApp.h"
		#include "Lib/DHCPServerApp.h"
		#include "Lib/HTTPServerApp.h"
		#include "Lib/TELNETServerApp.h"

	/* Macros: */
		/** IP address that the webserver should use once connected to a RNDIS device (when DHCP is disabled). */
		#define DEVICE_IP_ADDRESS         (uint8_t[]){10, 0, 0, 2}

		/** Netmask that the webserver should once connected to a RNDIS device (when DHCP is disabled). */
		#define DEVICE_NETMASK            (uint8_t[]){255, 255, 255, 0}

		/** IP address of the default gateway the webserver should use when routing outside the local subnet
		 *  (when DHCP is disabled).
		 */
		#define DEVICE_GATEWAY            (uint8_t[]){10, 0, 0, 1}
		
		/** Ethernet MAC address of the virtual webserver. When in device RNDIS mode, the virtual webserver requires
		 *  a unique MAC address that it can use when sending packets to the RNDIS adapter, which contains a seperate
		 *  MAC address as set in the RNDIS class driver configuration structure.
		 */
		#define SERVER_MAC_ADDRESS        (uint8_t[]){1, 0, 1, 0, 1, 0}

	/* External Variables: */
		extern struct uip_eth_addr MACAddress;

	/* Function Prototypes: */
		void uIPManagement_Init(void);
		void uIPManagement_ManageNetwork(void);
		void uIPManagement_TCPCallback(void);
		void uIPManagement_UDPCallback(void);

		#if defined(INCLUDE_FROM_UIPMANAGEMENT_C)
			static void uIPManagement_ProcessIncomingPacket(void);
			static void uIPManagement_ManageConnections(void);
		#endif

#endif

