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

		#include "Config/AppConfig.h"

		#include "DHCPClientApp.h"
		#include "DHCPServerApp.h"
		#include "HTTPServerApp.h"
		#include "TELNETServerApp.h"

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

