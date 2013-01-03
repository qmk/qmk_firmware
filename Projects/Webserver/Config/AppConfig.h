/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Application Configuration Header File
 *
 *  This is a header file which is be used to configure some of
 *  the application's compile time options, as an alternative to
 *  specifying the compile time constants supplied through a 
 *  makefile or build system.
 *
 *  For information on what each token does, refer to the 
 *  \ref Sec_Options section of the application documentation.
 */

#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

	#define ENABLE_DHCP_CLIENT
	#define ENABLE_DHCP_SERVER
	#define ENABLE_TELNET_SERVER
	#define MAX_URI_LENGTH                50

	#define DEVICE_IP_ADDRESS             (uint8_t[]){ 10,   0,   0,   2}
	#define DEVICE_NETMASK                (uint8_t[]){255, 255, 255,   0}
	#define DEVICE_GATEWAY                (uint8_t[]){ 10,   0,   0,   1}
	#define SERVER_MAC_ADDRESS            (uint8_t[]){  1,   0,   1,   0,   1,   0}
	
	#define UIP_CONF_UDP                  (defined(ENABLE_DHCP_CLIENT) || defined(ENABLE_DHCP_SERVER))
	#define UIP_CONF_BROADCAST            1
	#define UIP_CONF_TCP                  1
	#define UIP_CONF_UDP_CONNS            1
	#define UIP_CONF_MAX_CONNECTIONS      3
	#define UIP_CONF_MAX_LISTENPORTS      5
	#define UIP_CONF_BUFFER_SIZE          1514
	#define UIP_CONF_LL_802154            0
	#define UIP_CONF_LL_80211             0
	#define UIP_CONF_ROUTER               0
	#define UIP_CONF_ICMP6                0
	#define UIP_CONF_ICMP_DEST_UNREACH    1
	#define UIP_URGDATA                   0
	#define UIP_ARCH_CHKSUM               0
	#define UIP_ARCH_ADD32                0
	#define UIP_NEIGHBOR_CONF_ADDRTYPE    0

#endif