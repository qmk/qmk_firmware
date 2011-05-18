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
 *  \brief Common definitions and declarations for the library USB RNDIS Class driver.
 *
 *  Common definitions and declarations for the library USB RNDIS Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassRNDIS
 *  \defgroup Group_USBClassRNDISCommon  Common Class Definitions
 *
 *  \section Sec_ModDescription Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  RNDIS Class.
 *
 *  @{
 */

#ifndef _RNDIS_CLASS_COMMON_H_
#define _RNDIS_CLASS_COMMON_H_

	/* Macros: */
		#define __INCLUDE_FROM_CDC_DRIVER

	/* Includes: */
		#include "../../Core/StdDescriptors.h"
		#include "CDC.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_RNDIS_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Macros: */
		/** Additional error code for RNDIS functions when a device returns a logical command failure. */
		#define RNDIS_ERROR_LOGICAL_CMD_FAILED        0x80

		/** Implemented RNDIS Version Major. */
		#define REMOTE_NDIS_VERSION_MAJOR             0x01

		/** Implemented RNDIS Version Minor. */
		#define REMOTE_NDIS_VERSION_MINOR             0x00

		/** \name RNDIS Message Values */
		//@{
		#define REMOTE_NDIS_PACKET_MSG                0x00000001UL
		#define REMOTE_NDIS_INITIALIZE_MSG            0x00000002UL
		#define REMOTE_NDIS_HALT_MSG                  0x00000003UL
		#define REMOTE_NDIS_QUERY_MSG                 0x00000004UL
		#define REMOTE_NDIS_SET_MSG                   0x00000005UL
		#define REMOTE_NDIS_RESET_MSG                 0x00000006UL
		#define REMOTE_NDIS_INDICATE_STATUS_MSG       0x00000007UL
		#define REMOTE_NDIS_KEEPALIVE_MSG             0x00000008UL
		//@}

		/** \name RNDIS Response Values */
		//@{
		#define REMOTE_NDIS_INITIALIZE_CMPLT          0x80000002UL
		#define REMOTE_NDIS_QUERY_CMPLT               0x80000004UL
		#define REMOTE_NDIS_SET_CMPLT                 0x80000005UL
		#define REMOTE_NDIS_RESET_CMPLT               0x80000006UL
		#define REMOTE_NDIS_KEEPALIVE_CMPLT           0x80000008UL
		//@}

		/** \name RNDIS Status Values */
		//@{
		#define REMOTE_NDIS_STATUS_SUCCESS            0x00000000UL
		#define REMOTE_NDIS_STATUS_FAILURE            0xC0000001UL
		#define REMOTE_NDIS_STATUS_INVALID_DATA       0xC0010015UL
		#define REMOTE_NDIS_STATUS_NOT_SUPPORTED      0xC00000BBUL
		#define REMOTE_NDIS_STATUS_MEDIA_CONNECT      0x4001000BUL
		#define REMOTE_NDIS_STATUS_MEDIA_DISCONNECT   0x4001000CUL
		//@}

		/** \name RNDIS Media States */
		//@{
		#define REMOTE_NDIS_MEDIA_STATE_CONNECTED     0x00000000UL
		#define REMOTE_NDIS_MEDIA_STATE_DISCONNECTED  0x00000001UL
		//@}
		
		#define REMOTE_NDIS_MEDIUM_802_3              0x00000000UL

		/** \name RNDIS Connection Types */
		//@{
		#define REMOTE_NDIS_DF_CONNECTIONLESS	      0x00000001UL
		#define REMOTE_NDIS_DF_CONNECTION_ORIENTED    0x00000002UL
		//@}
		
		/** \name RNDIS Packet Types */
		//@{
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
		//@}
		
		/** \name RNDIS OID Values */
		//@{
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
		//@}

		/** Maximum size in bytes of a RNDIS control message which can be sent or received. */
		#define RNDIS_MESSAGE_BUFFER_SIZE             128

		/** Maximum size in bytes of an Ethernet frame according to the Ethernet standard. */
		#define ETHERNET_FRAME_SIZE_MAX               1500

	/* Enums: */
		/** Enum for the RNDIS class specific control requests that can be issued by the USB bus host. */
		enum RNDIS_ClassRequests_t
		{
			RNDIS_REQ_SendEncapsulatedCommand = 0x00, /**< RNDIS request to issue a host-to-device NDIS command. */
			RNDIS_REQ_GetEncapsulatedResponse = 0x01, /**< RNDIS request to issue a device-to-host NDIS response. */
		};

		/** Enum for the possible NDIS adapter states. */
		enum RNDIS_States_t
		{
			RNDIS_Uninitialized    = 0, /**< Adapter currently uninitialized. */
			RNDIS_Initialized      = 1, /**< Adapter currently initialized but not ready for data transfers. */
			RNDIS_Data_Initialized = 2, /**< Adapter currently initialized and ready for data transfers. */
		};

		/** Enum for the RNDIS class specific notification requests that can be issued by a RNDIS device to a host. */
		enum RNDIS_ClassNotifications_t
		{
			RNDIS_NOTIF_ResponseAvailable = 0x01, /**< Notification request value for a RNDIS Response Available notification. */
		};

		/** Enum for the NDIS hardware states. */
		enum NDIS_Hardware_Status_t
		{
			NDIS_HardwareStatus_Ready, /**< Hardware Ready to accept commands from the host. */
			NDIS_HardwareStatus_Initializing, /**< Hardware busy initializing. */
			NDIS_HardwareStatus_Reset, /**< Hardware reset. */
			NDIS_HardwareStatus_Closing, /**< Hardware currently closing. */
			NDIS_HardwareStatus_NotReady /**< Hardware not ready to accept commands from the host. */
		};

	/* Type Defines: */
		/** \brief Ethernet Frame Packet Information Structure.
		 *
		 *  Type define for an Ethernet frame buffer data and information structure. This can be used to conveniently
		 *  store both the size and data in an Ethernet frame.
		 */
		typedef struct
		{
			uint8_t  FrameData[ETHERNET_FRAME_SIZE_MAX]; /**< Ethernet frame contents. */
			uint16_t FrameLength; /**< Length in bytes of the Ethernet frame stored in the buffer. */
		} Ethernet_Frame_Info_t;

		/** \brief MAC Address Structure.
		 *
		 *  Type define for a physical MAC address of a device on a network.
		 */
		typedef struct
		{
			uint8_t Octets[6]; /**< Individual bytes of a MAC address */
		} ATTR_PACKED MAC_Address_t;

		/** \brief RNDIS Common Message Header Structure.
		 *
		 *  Type define for a RNDIS message header, sent before RNDIS messages.
		 */
		typedef struct
		{
			uint32_t MessageType; /**< RNDIS message type, a \c REMOTE_NDIS_*_MSG constant */
			uint32_t MessageLength; /**< Total length of the RNDIS message, in bytes */
		} ATTR_PACKED RNDIS_Message_Header_t;

		/** \brief RNDIS Message Structure.
		 *
		 *  Type define for a RNDIS packet message, used to encapsulate Ethernet packets sent to and from the adapter.
		 */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t DataOffset;
			uint32_t DataLength;
			uint32_t OOBDataOffset;
			uint32_t OOBDataLength;
			uint32_t NumOOBDataElements;
			uint32_t PerPacketInfoOffset;
			uint32_t PerPacketInfoLength;
			uint32_t VcHandle;
			uint32_t Reserved;
		} ATTR_PACKED RNDIS_Packet_Message_t;

		/** \brief RNDIS Initialization Message Structure.
		 *
		 *  Type define for a RNDIS Initialize command message.
		 */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;

			uint32_t MajorVersion;
			uint32_t MinorVersion;
			uint32_t MaxTransferSize;
		} ATTR_PACKED RNDIS_Initialize_Message_t;

		/** \brief RNDIS Initialize Complete Message Structure.
		 *
		 *  Type define for a RNDIS Initialize Complete response message.
		 */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;

			uint32_t MajorVersion;
			uint32_t MinorVersion;
			uint32_t DeviceFlags;
			uint32_t Medium;
			uint32_t MaxPacketsPerTransfer;
			uint32_t MaxTransferSize;
			uint32_t PacketAlignmentFactor;
			uint32_t AFListOffset;
			uint32_t AFListSize;
		} ATTR_PACKED RNDIS_Initialize_Complete_t;

		/** \brief RNDIS Keep Alive Message Structure.
		 *
		 *  Type define for a RNDIS Keep Alive command message.
		 */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
		} ATTR_PACKED RNDIS_KeepAlive_Message_t;

		/** \brief RNDIS Keep Alive Complete Message Structure.
		 *
		 *  Type define for a RNDIS Keep Alive Complete response message.
		 */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;
		} ATTR_PACKED RNDIS_KeepAlive_Complete_t;

		/** \brief RNDIS Reset Complete Message Structure.
		 *
		 *  Type define for a RNDIS Reset Complete response message.
		 */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t Status;

			uint32_t AddressingReset;
		} ATTR_PACKED RNDIS_Reset_Complete_t;

		/** \brief RNDIS OID Property Set Message Structure.
		 *
		 *  Type define for a RNDIS OID Property Set command message.
		 */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;

			uint32_t Oid;
			uint32_t InformationBufferLength;
			uint32_t InformationBufferOffset;
			uint32_t DeviceVcHandle;
		} ATTR_PACKED RNDIS_Set_Message_t;

		/** \brief RNDIS OID Property Set Complete Message Structure.
		 *
		 *  Type define for a RNDIS OID Property Set Complete response message.
		 */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;
		} ATTR_PACKED RNDIS_Set_Complete_t;

		/** \brief RNDIS OID Property Query Message Structure.
		 *
		 *  Type define for a RNDIS OID Property Query command message.
		 */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;

			uint32_t Oid;
			uint32_t InformationBufferLength;
			uint32_t InformationBufferOffset;
			uint32_t DeviceVcHandle;
		} ATTR_PACKED RNDIS_Query_Message_t;

		/** \brief RNDIS OID Property Query Complete Message Structure.
		 *
		 *  Type define for a RNDIS OID Property Query Complete response message.
		 */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;

			uint32_t InformationBufferLength;
			uint32_t InformationBufferOffset;
		} ATTR_PACKED RNDIS_Query_Complete_t;

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

