/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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

#ifndef _RNDIS_CLASS_H_
#define _RNDIS_CLASS_H_

	/* Includes: */
		#include <string.h>
	
		#include "../../USB.h"
		#include "RNDISConstants.h"
		
	/* Macros: */
		/** Implemented RNDIS Version Major */
		#define REMOTE_NDIS_VERSION_MAJOR             0x01

		/** Implemented RNDIS Version Minor */
		#define REMOTE_NDIS_VERSION_MINOR             0x00
	
		/** RNDIS request to issue a host-to-device NDIS command */
		#define REQ_SendEncapsulatedCommand           0x00

		/** RNDIS request to issue a device-to-host NDIS response */
		#define REQ_GetEncapsulatedResponse           0x01
		
		#define RNDIS_MESSAGE_BUFFER_SIZE             128

		#define ETHERNET_FRAME_SIZE_MAX               1500
		
		#define NOTIF_ResponseAvailable               1
		
	/* Enums: */
		/** Enum for the possible NDIS adapter states. */
		enum RNDIS_States_t
		{
			RNDIS_Uninitialized    = 0, /**< Adapter currently uninitialized */
			RNDIS_Initialized      = 1, /**< Adapter currently initialized but not ready for data transfers */
			RNDIS_Data_Initialized = 2, /**< Adapter currently initialized and ready for data transfers */
		};

		/** Enum for the NDIS hardware states */
		enum NDIS_Hardware_Status_t
		{
			NdisHardwareStatusReady, /**< Hardware Ready to accept commands from the host */
			NdisHardwareStatusInitializing, /**< Hardware busy initializing */
			NdisHardwareStatusReset, /**< Hardware reset */
			NdisHardwareStatusClosing, /**< Hardware currently closing */
			NdisHardwareStatusNotReady /**< Hardware not ready to accept commands from the host */
		};
		
	/* Type Defines: */
		/** Type define for a physical MAC address of a device on a network */
		typedef struct
		{
			uint8_t       Octets[6]; /**< Individual bytes of a MAC address */
		} MAC_Address_t;

		/** Type define for a RNDIS message header, sent before RNDIS messages */
		typedef struct
		{
			uint32_t MessageType; /**< RNDIS message type, a REMOTE_NDIS_*_MSG constant */
			uint32_t MessageLength; /**< Total length of the RNDIS message, in bytes */
		} RNDIS_Message_Header_t;

		/** Type define for an Ethernet frame buffer. */
		typedef struct
		{
			uint8_t       FrameData[ETHERNET_FRAME_SIZE_MAX]; /**< Ethernet frame contents */
			uint16_t      FrameLength; /**< Length in bytes of the Ethernet frame stored in the buffer */
			bool          FrameInBuffer; /**< Indicates if a frame is currently stored in the buffer */
		} Ethernet_Frame_Info_t;

		/** Type define for a RNDIS packet message, used to encapsulate Ethernet packets sent to and from the adapter */
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
		} RNDIS_PACKET_MSG_t;

		typedef struct
		{
			uint8_t  ControlInterfaceNumber; /**< Interface number of the CDC control interface within the device */

			uint8_t  DataINEndpointNumber; /**< Endpoint number of the CDC interface's IN data endpoint */
			uint16_t DataINEndpointSize; /**< Size in bytes of the CDC interface's IN data endpoint */

			uint8_t  DataOUTEndpointNumber; /**< Endpoint number of the CDC interface's OUT data endpoint */
			uint16_t DataOUTEndpointSize;  /**< Size in bytes of the CDC interface's OUT data endpoint */

			uint8_t  NotificationEndpointNumber; /**< Endpoint number of the CDC interface's IN notification endpoint, if used */
			uint16_t NotificationEndpointSize;  /**< Size in bytes of the CDC interface's IN notification endpoint, if used */
			
			char*         AdapterVendorDescription;
			MAC_Address_t AdapterMACAddress;

			uint8_t  RNDISMessageBuffer[RNDIS_MESSAGE_BUFFER_SIZE];
			bool     ResponseReady;
			uint8_t  CurrRNDISState;
			uint32_t CurrPacketFilter;
			Ethernet_Frame_Info_t FrameIN;
			Ethernet_Frame_Info_t FrameOUT;
		} USB_ClassInfo_RNDIS_t;
		
		/** Type define for a RNDIS Initialize command message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			
			uint32_t MajorVersion;
			uint32_t MinorVersion;
			uint32_t MaxTransferSize;
		} RNDIS_INITIALIZE_MSG_t;
		
		/** Type define for a RNDIS Initialize complete response message */
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
		} RNDIS_INITIALIZE_CMPLT_t;
		
		/** Type define for a RNDIS Keepalive command message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
		} RNDIS_KEEPALIVE_MSG_t;

		/** Type define for a RNDIS Keepalive complete message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;
		} RNDIS_KEEPALIVE_CMPLT_t;

		/** Type define for a RNDIS Reset complete message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t Status;

			uint32_t AddressingReset;
		} RNDIS_RESET_CMPLT_t;
		
		/** Type define for a RNDIS Set command message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			
			uint32_t Oid;
			uint32_t InformationBufferLength;
			uint32_t InformationBufferOffset;
			uint32_t DeviceVcHandle;
		} RNDIS_SET_MSG_t;

		/** Type define for a RNDIS Set complete response message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;
		} RNDIS_SET_CMPLT_t;
		
		/** Type define for a RNDIS Query command message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			
			uint32_t Oid;
			uint32_t InformationBufferLength;
			uint32_t InformationBufferOffset;
			uint32_t DeviceVcHandle;
		} RNDIS_QUERY_MSG_t;
		
		/** Type define for a RNDIS Query complete response message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;
			
			uint32_t InformationBufferLength;
			uint32_t InformationBufferOffset;
		} RNDIS_QUERY_CMPLT_t;
		
	/* Function Prototypes: */
		#if defined(INCLUDE_FROM_RNDIS_CLASS_C)
			static void USB_RNDIS_ProcessRNDISControlMessage(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo);
			static bool USB_RNDIS_ProcessNDISQuery(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo, 
			                                       uint32_t OId, void* QueryData, uint16_t QuerySize,
										           void* ResponseData, uint16_t* ResponseSize);
			static bool USB_RNDIS_ProcessNDISSet(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo, uint32_t OId,
			                                     void* SetData, uint16_t SetSize);	
		#endif

		void     USB_RNDIS_USBTask(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo);
		bool     USB_RNDIS_ConfigureEndpoints(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo);
		void     USB_RNDIS_ProcessControlPacket(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo);
		void     USB_RNDIS_USBTask(USB_ClassInfo_RNDIS_t* RNDISInterfaceInfo);
		
#endif
