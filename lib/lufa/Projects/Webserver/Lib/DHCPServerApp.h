/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for DHCPServerApp.c.
 */

#ifndef _DHCPSERVER_APP_H_
#define _DHCPSERVER_APP_H_

	/* Includes: */
		#include <stdio.h>

		#include <uip.h>

		#include "Config/AppConfig.h"
		#include "../Webserver.h"
		#include "DHCPCommon.h"

	/* Function Prototypes: */
		void DHCPServerApp_Init(void);
		void DHCPServerApp_Callback(void);

		#if defined(INCLUDE_FROM_DHCPSERVERAPP_C)
		static uint16_t DHCPServerApp_FillDHCPHeader(DHCP_Header_t* const DHCPHeader,
		                                             const uint8_t DHCPMessageType,
		                                             const struct uip_eth_addr* const ClientHardwareAddress,
		                                             const uip_ipaddr_t* const PreferredClientIP,
		                                             const uint32_t TransactionID);
		static bool DHCPServerApp_CheckIfIPLeased(const uip_ipaddr_t* const IPAddress);
		static void DHCPServerApp_GetUnleasedIP(uip_ipaddr_t* const NewIPAddress);
		static void DHCPServerApp_LeaseIP(const uip_ipaddr_t* const IPAddress);
		static void DHCPServerApp_UnleaseIP(const uip_ipaddr_t* const IPAddress);
		#endif
#endif

