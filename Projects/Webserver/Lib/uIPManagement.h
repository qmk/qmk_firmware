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
 *  Header file for uIPManagement.c.
 */

#ifndef _UIPMANAGEMENT_H_
#define _UIPMANAGEMENT_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/Class/RNDIS.h>

		#include <uip.h>
		#include <uip_arp.h>
		#include <timer.h>
		
		#include "Lib/DHCPApp.h"
		#include "Lib/HTTPServerApp.h"
		
	/* Macros: */
		/** IP address that the webserver should use once connected to a RNDIS device (when DHCP is disabled). */
		#define DEVICE_IP_ADDRESS         (uint8_t[]){192, 168, 1, 10}
		
		/** Netmask that the webserver should once connected to a RNDIS device (when DHCP is disabled). */
		#define DEVICE_NETMASK            (uint8_t[]){255, 255, 255, 0}
		
		/** IP address of the default gateway the webserver should use when routing outside the local subnet
		 *  (when DHCP is disabled).
		 */
		#define DEVICE_GATEWAY            (uint8_t[]){192, 168, 1, 1}

	/* External Variables: */
		extern struct uip_eth_addr MACAddress;
		
	/* Function Prototypes: */
		void uIPManagement_Init(void);
		void uIPManagement_ManageNetwork(void);
		
		#if defined(INCLUDE_FROM_UIPMANAGEMENT_C)
			static void uIPManagement_ProcessIncommingPacket(void);
			static void uIPManagement_ManageConnections(void);
		#endif
		
#endif
