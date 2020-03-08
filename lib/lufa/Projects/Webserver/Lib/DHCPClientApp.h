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
 *  Header file for DHCPClientApp.c.
 */

#ifndef _DHCPCLIENT_APP_H_
#define _DHCPCLIENT_APP_H_

	/* Includes: */
		#include <stdio.h>

		#include <uip.h>

		#include "Config/AppConfig.h"
		#include "../Webserver.h"
		#include "DHCPCommon.h"

	/* Enums: */
		/** States for each DHCP connection to a DHCP client. */
		enum DHCP_Client_States_t
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
			static uint16_t DHCPClientApp_FillDHCPHeader(DHCP_Header_t* const DHCPHeader,
			                                             const uint8_t DHCPMessageType,
			                                             uip_udp_appstate_t* const AppState);
		#endif
#endif

