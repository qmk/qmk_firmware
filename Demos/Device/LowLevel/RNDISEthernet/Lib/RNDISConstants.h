/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  RNDIS specification related constants. For more information on these
 *  constants, please refer to the Microsoft RNDIS specification.
 */
 
#ifndef _RNDIS_CONSTANTS_DEVICE_H_
#define _RNDIS_CONSTANTS_DEVICE_H_

	/* Macros: */
		#define REMOTE_NDIS_PACKET_MSG                0x00000001UL
		#define REMOTE_NDIS_INITIALIZE_MSG            0x00000002UL
		#define REMOTE_NDIS_HALT_MSG                  0x00000003UL
		#define REMOTE_NDIS_QUERY_MSG                 0x00000004UL
		#define REMOTE_NDIS_SET_MSG                   0x00000005UL
		#define REMOTE_NDIS_RESET_MSG                 0x00000006UL
		#define REMOTE_NDIS_INDICATE_STATUS_MSG       0x00000007UL
		#define REMOTE_NDIS_KEEPALIVE_MSG             0x00000008UL

		#define REMOTE_NDIS_INITIALIZE_CMPLT          0x80000002UL
		#define REMOTE_NDIS_QUERY_CMPLT               0x80000004UL
		#define REMOTE_NDIS_SET_CMPLT                 0x80000005UL
		#define REMOTE_NDIS_RESET_CMPLT               0x80000006UL
		#define REMOTE_NDIS_KEEPALIVE_CMPLT           0x80000008UL
		
		#define REMOTE_NDIS_STATUS_SUCCESS            0x00000000UL
		#define REMOTE_NDIS_STATUS_FAILURE            0xC0000001UL
		#define REMOTE_NDIS_STATUS_INVALID_DATA       0xC0010015UL
		#define REMOTE_NDIS_STATUS_NOT_SUPPORTED      0xC00000BBUL
		#define REMOTE_NDIS_STATUS_MEDIA_CONNECT      0x4001000BUL
		#define REMOTE_NDIS_STATUS_MEDIA_DISCONNECT   0x4001000CUL
		
		#define REMOTE_NDIS_MEDIA_STATE_CONNECTED     0x00000000UL
		#define REMOTE_NDIS_MEDIA_STATE_DISCONNECTED  0x00000001UL
		
		#define REMOTE_NDIS_MEDIUM_802_3              0x00000000UL
		
		#define REMOTE_NDIS_DF_CONNECTIONLESS	      0x00000001UL
		#define REMOTE_NDIS_DF_CONNECTION_ORIENTED    0x00000002UL

		#define REMOTE_NDIS_PACKET_DIRECTED           0x00000001UL
		#define REMOTE_NDIS_PACKET_MULTICAST          0x00000002UL
		#define REMOTE_NDIS_PACKET_ALL_MULTICAST      0x00000004UL
		#define REMOTE_NDIS_PACKET_BROADCAST          0x00000008UL
		#define REMOTE_NDIS_PACKET_SOURCE_ROUTING     0x00000010UL
		#define REMOTE_NDIS_PACKET_PROMISCUOUS        0x00000020UL
		#define REMOTE_NDIS_PACKET_SMT                0x00000040UL
		#define REMOTE_NDIS_PACKET_ALL_LOCAL          0x00000080UL
		#define REMOTE_NDIS_PACKET_GROUP              0x00001000UL
		#define REMOTE_NDIS_PACKET_ALL_FUNCTIONAL     0x00002000UL
		#define REMOTE_NDIS_PACKET_FUNCTIONAL         0x00004000UL
		#define REMOTE_NDIS_PACKET_MAC_FRAME          0x00008000UL	
		
		#define OID_GEN_SUPPORTED_LIST                0x00010101UL
		#define OID_GEN_HARDWARE_STATUS               0x00010102UL
		#define OID_GEN_MEDIA_SUPPORTED               0x00010103UL
		#define OID_GEN_MEDIA_IN_USE                  0x00010104UL
		#define OID_GEN_MAXIMUM_FRAME_SIZE            0x00010106UL
		#define OID_GEN_MAXIMUM_TOTAL_SIZE            0x00010111UL
		#define OID_GEN_LINK_SPEED                    0x00010107UL
		#define OID_GEN_TRANSMIT_BLOCK_SIZE           0x0001010AUL
		#define OID_GEN_RECEIVE_BLOCK_SIZE            0x0001010BUL
		#define OID_GEN_VENDOR_ID                     0x0001010CUL
		#define OID_GEN_VENDOR_DESCRIPTION            0x0001010DUL
		#define OID_GEN_CURRENT_PACKET_FILTER         0x0001010EUL
		#define OID_GEN_MAXIMUM_TOTAL_SIZE            0x00010111UL
		#define OID_GEN_MEDIA_CONNECT_STATUS          0x00010114UL
		#define OID_GEN_PHYSICAL_MEDIUM               0x00010202UL
		#define OID_GEN_XMIT_OK                       0x00020101UL
		#define OID_GEN_RCV_OK                        0x00020102UL
		#define OID_GEN_XMIT_ERROR                    0x00020103UL
		#define OID_GEN_RCV_ERROR                     0x00020104UL
		#define OID_GEN_RCV_NO_BUFFER                 0x00020105UL
		#define OID_802_3_PERMANENT_ADDRESS           0x01010101UL
		#define OID_802_3_CURRENT_ADDRESS             0x01010102UL
		#define OID_802_3_MULTICAST_LIST              0x01010103UL
		#define OID_802_3_MAXIMUM_LIST_SIZE           0x01010104UL
		#define OID_802_3_RCV_ERROR_ALIGNMENT         0x01020101UL
		#define OID_802_3_XMIT_ONE_COLLISION          0x01020102UL
		#define OID_802_3_XMIT_MORE_COLLISIONS        0x01020103UL

#endif
