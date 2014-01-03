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
 *  General Ethernet protocol constants and type defines, for use by
 *  all network protocol portions of the TCP/IP stack.
 */

#ifndef _ETHERNET_PROTOCOLS_H_
#define _ETHERNET_PROTOCOLS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

	/* Macros: */
		#define ETHERTYPE_IPV4                   0x0800
		#define ETHERTYPE_ARP                    0x0806
		#define ETHERTYPE_RARP                   0x8035
		#define ETHERTYPE_APPLETALK              0x809b
		#define ETHERTYPE_APPLETALKARP           0x80f3
		#define ETHERTYPE_IEEE8021Q              0x8100
		#define ETHERTYPE_NOVELLIPX              0x8137
		#define ETHERTYPE_NOVELL                 0x8138
		#define ETHERTYPE_IPV6                   0x86DD
		#define ETHERTYPE_COBRANET               0x8819
		#define ETHERTYPE_PROVIDERBRIDGING       0x88a8
		#define ETHERTYPE_MPLSUNICAST            0x8847
		#define ETHERTYPE_MPLSMULTICAST          0x8848
		#define ETHERTYPE_PPPoEDISCOVERY         0x8863
		#define ETHERTYPE_PPPoESESSION           0x8864
		#define ETHERTYPE_EAPOVERLAN             0x888E
		#define ETHERTYPE_HYPERSCSI              0x889A
		#define ETHERTYPE_ATAOVERETHERNET        0x88A2
		#define ETHERTYPE_ETHERCAT               0x88A4
		#define ETHERTYPE_SERCOSIII              0x88CD
		#define ETHERTYPE_CESoE                  0x88D8
		#define ETHERTYPE_MACSECURITY            0x88E5
		#define ETHERTYPE_FIBRECHANNEL           0x8906
		#define ETHERTYPE_QINQ                   0x9100
		#define ETHERTYPE_VLLT                   0xCAFE

		#define PROTOCOL_ICMP                    1
		#define PROTOCOL_IGMP                    2
		#define PROTOCOL_TCP                     6
		#define PROTOCOL_UDP                     17
		#define PROTOCOL_OSPF                    89
		#define PROTOCOL_SCTP                    132

	/* Type Defines: */
		/** Type define for an Ethernet frame buffer data and information structure. */
		typedef struct
		{
			uint8_t  FrameData[ETHERNET_FRAME_SIZE_MAX]; /**< Ethernet frame contents. */
			uint16_t FrameLength; /**< Length in bytes of the Ethernet frame stored in the buffer. */
		} Ethernet_Frame_Info_t;

		/** Type define for a protocol IP address of a device on a network. */
		typedef struct
		{
			uint8_t  Octets[4]; /**< Individual bytes of an IP address */
		} IP_Address_t;

#endif

