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

/** \file
 *
 *  RNDIS command handler functions. This handles RNDIS commands according to
 *  the Microsoft RNDIS specification, creating a USB Ethernet network adapter.
 */
 
#define  INCLUDE_FROM_RNDIS_C
#include "RNDIS.h"

/* Global Variables: */
/** Physical MAC address of the network adapter, which becomes the MAC address of the host for packets sent to the adapter. */
static MAC_Address_t  PROGMEM AdapterMACAddress          = {ADAPTER_MAC_ADDRESS};

/** Vendor description of the adapter. This is overridden by the INF file required to install the appropriate RNDIS drivers for
 *  the device, but may still be used by the OS in some circumstances.
 */
static char           PROGMEM AdapterVendorDescription[] = "LUFA RNDIS Adapter";

/** List of RNDIS OID commands supported by this adapter. */
static const uint32_t PROGMEM AdapterSupportedOIDList[]  =
							{
								OID_GEN_SUPPORTED_LIST,
								OID_GEN_PHYSICAL_MEDIUM,
								OID_GEN_HARDWARE_STATUS,
								OID_GEN_MEDIA_SUPPORTED,
								OID_GEN_MEDIA_IN_USE,
								OID_GEN_MAXIMUM_FRAME_SIZE,
								OID_GEN_MAXIMUM_TOTAL_SIZE,
								OID_GEN_LINK_SPEED,
								OID_GEN_TRANSMIT_BLOCK_SIZE,
								OID_GEN_RECEIVE_BLOCK_SIZE,
								OID_GEN_VENDOR_ID,
								OID_GEN_VENDOR_DESCRIPTION,
								OID_GEN_CURRENT_PACKET_FILTER,
								OID_GEN_MAXIMUM_TOTAL_SIZE,
								OID_GEN_MEDIA_CONNECT_STATUS,
								OID_GEN_XMIT_OK,
								OID_GEN_RCV_OK,
								OID_GEN_XMIT_ERROR,
								OID_GEN_RCV_ERROR,
								OID_GEN_RCV_NO_BUFFER,
								OID_802_3_PERMANENT_ADDRESS,
								OID_802_3_CURRENT_ADDRESS,
								OID_802_3_MULTICAST_LIST,
								OID_802_3_MAXIMUM_LIST_SIZE,
								OID_802_3_RCV_ERROR_ALIGNMENT,
								OID_802_3_XMIT_ONE_COLLISION,
								OID_802_3_XMIT_MORE_COLLISIONS,
							};

/** Buffer for RNDIS messages (as distinct from Ethernet frames sent through the adapter. This must be big enough to hold the entire
 *  Supported OID list, plus the response header. The buffer is half-duplex, and is written to as it is read to save on SRAM - for this
 *  reason, care must be taken when constructing RNDIS responses that unread data is not overwritten when writing in responses.
 */
uint8_t                 RNDISMessageBuffer[sizeof(AdapterSupportedOIDList) + sizeof(RNDIS_QUERY_CMPLT_t)];

/** Pointer to the RNDIS message header at the top of the RNDIS message buffer, for convenience. */
RNDIS_Message_Header_t* MessageHeader = (RNDIS_Message_Header_t*)&RNDISMessageBuffer;

/** Indicates if a RNDIS message response is ready to be sent back to the host. */
bool                    ResponseReady               = false;

/** Current RNDIS adapter state, a value from the RNDIS_States_t enum. */
uint8_t                 CurrRNDISState              = RNDIS_Uninitialized;

/** Current Ethernet packet filter mask. This is non-zero when the adapter is initialized, or zero when disabled. */
uint32_t                CurrPacketFilter            = 0;							


/** Processes the RNDIS message received by the host and stored in the RNDISMessageBuffer global buffer. If a response is
 *  created, the ResponseReady global is updated so that the response is written back to the host upon request.
 */
void ProcessRNDISControlMessage(void)
{
	/* Note: Only a single buffer is used for both the received message and its response to save SRAM. Because of
	         this, response bytes should be filled in order so that they do not clobber unread data in the buffer. */

	switch (MessageHeader->MessageType)
	{
		case REMOTE_NDIS_INITIALIZE_MSG:
			/* Initialize the adapter - return information about the supported RNDIS version and buffer sizes */

			ResponseReady = true;
			
			RNDIS_INITIALIZE_MSG_t*   INITIALIZE_Message  = (RNDIS_INITIALIZE_MSG_t*)&RNDISMessageBuffer;
			RNDIS_INITIALIZE_CMPLT_t* INITIALIZE_Response = (RNDIS_INITIALIZE_CMPLT_t*)&RNDISMessageBuffer;
			
			INITIALIZE_Response->MessageType           = REMOTE_NDIS_INITIALIZE_CMPLT;
			INITIALIZE_Response->MessageLength         = sizeof(RNDIS_INITIALIZE_CMPLT_t);
			INITIALIZE_Response->RequestId             = INITIALIZE_Message->RequestId;
			INITIALIZE_Response->Status                = REMOTE_NDIS_STATUS_SUCCESS;
			
			INITIALIZE_Response->MajorVersion          = REMOTE_NDIS_VERSION_MAJOR;
			INITIALIZE_Response->MinorVersion          = REMOTE_NDIS_VERSION_MINOR;			
			INITIALIZE_Response->DeviceFlags           = REMOTE_NDIS_DF_CONNECTIONLESS;
			INITIALIZE_Response->Medium                = REMOTE_NDIS_MEDIUM_802_3;
			INITIALIZE_Response->MaxPacketsPerTransfer = 1;
			INITIALIZE_Response->MaxTransferSize       = (sizeof(RNDIS_PACKET_MSG_t) + ETHERNET_FRAME_SIZE_MAX);
			INITIALIZE_Response->PacketAlignmentFactor = 0;
			INITIALIZE_Response->AFListOffset          = 0;
			INITIALIZE_Response->AFListSize            = 0;
			
			CurrRNDISState = RNDIS_Initialized;
		
			break;
		case REMOTE_NDIS_HALT_MSG:
			/* Halt the adapter, reset the adapter state - note that no response should be returned when completed */

			ResponseReady = false;
			MessageHeader->MessageLength = 0;

			CurrRNDISState = RNDIS_Uninitialized;

			break;
		case REMOTE_NDIS_QUERY_MSG:
			/* Request for information about a parameter about the adapter, specified as an OID token */

			ResponseReady = true;
						
			RNDIS_QUERY_MSG_t*   QUERY_Message  = (RNDIS_QUERY_MSG_t*)&RNDISMessageBuffer;
			RNDIS_QUERY_CMPLT_t* QUERY_Response = (RNDIS_QUERY_CMPLT_t*)&RNDISMessageBuffer;
			uint32_t             Query_Oid      = QUERY_Message->Oid;
						
			void*     QueryData                 = &RNDISMessageBuffer[sizeof(RNDIS_Message_Header_t) +
			                                                          QUERY_Message->InformationBufferOffset];
			void*     ResponseData              = &RNDISMessageBuffer[sizeof(RNDIS_QUERY_CMPLT_t)];		
			uint16_t  ResponseSize;

			QUERY_Response->MessageType         = REMOTE_NDIS_QUERY_CMPLT;
			QUERY_Response->MessageLength       = sizeof(RNDIS_QUERY_CMPLT_t);
						
			if (ProcessNDISQuery(Query_Oid, QueryData, QUERY_Message->InformationBufferLength,
			                     ResponseData, &ResponseSize))
			{
				QUERY_Response->Status                  = REMOTE_NDIS_STATUS_SUCCESS;
				QUERY_Response->MessageLength          += ResponseSize;
							
				QUERY_Response->InformationBufferLength = ResponseSize;
				QUERY_Response->InformationBufferOffset = (sizeof(RNDIS_QUERY_CMPLT_t) - sizeof(RNDIS_Message_Header_t));
			}
			else
			{				
				QUERY_Response->Status                  = REMOTE_NDIS_STATUS_NOT_SUPPORTED;

				QUERY_Response->InformationBufferLength = 0;
				QUERY_Response->InformationBufferOffset = 0;
			}
			
			break;
		case REMOTE_NDIS_SET_MSG:
			/* Request to set a parameter of the adapter, specified as an OID token */
		
			ResponseReady = true;
			
			RNDIS_SET_MSG_t*   SET_Message  = (RNDIS_SET_MSG_t*)&RNDISMessageBuffer;
			RNDIS_SET_CMPLT_t* SET_Response = (RNDIS_SET_CMPLT_t*)&RNDISMessageBuffer;
			uint32_t           SET_Oid      = SET_Message->Oid;

			SET_Response->MessageType       = REMOTE_NDIS_SET_CMPLT;
			SET_Response->MessageLength     = sizeof(RNDIS_SET_CMPLT_t);
			SET_Response->RequestId         = SET_Message->RequestId;

			void* SetData                   = &RNDISMessageBuffer[sizeof(RNDIS_Message_Header_t) +
			                                                      SET_Message->InformationBufferOffset];
						
			if (ProcessNDISSet(SET_Oid, SetData, SET_Message->InformationBufferLength))
			  SET_Response->Status        = REMOTE_NDIS_STATUS_SUCCESS;
			else
			  SET_Response->Status        = REMOTE_NDIS_STATUS_NOT_SUPPORTED;

			break;
		case REMOTE_NDIS_RESET_MSG:
			/* Soft reset the adapter */
		
			ResponseReady = true;
			
			RNDIS_RESET_CMPLT_t* RESET_Response = (RNDIS_RESET_CMPLT_t*)&RNDISMessageBuffer;

			RESET_Response->MessageType         = REMOTE_NDIS_RESET_CMPLT;
			RESET_Response->MessageLength       = sizeof(RNDIS_RESET_CMPLT_t);
			RESET_Response->Status              = REMOTE_NDIS_STATUS_SUCCESS;
			RESET_Response->AddressingReset     = 0;

			break;
		case REMOTE_NDIS_KEEPALIVE_MSG:
			/* Keep alive message sent to the adapter every 5 seconds when idle to ensure it is still responding */
		
			ResponseReady = true;
			
			RNDIS_KEEPALIVE_MSG_t*   KEEPALIVE_Message  = (RNDIS_KEEPALIVE_MSG_t*)&RNDISMessageBuffer;
			RNDIS_KEEPALIVE_CMPLT_t* KEEPALIVE_Response = (RNDIS_KEEPALIVE_CMPLT_t*)&RNDISMessageBuffer;

			KEEPALIVE_Response->MessageType     = REMOTE_NDIS_KEEPALIVE_CMPLT;
			KEEPALIVE_Response->MessageLength   = sizeof(RNDIS_KEEPALIVE_CMPLT_t);
			KEEPALIVE_Response->RequestId       = KEEPALIVE_Message->RequestId;
			KEEPALIVE_Response->Status          = REMOTE_NDIS_STATUS_SUCCESS;
			
			break;
	}
}

/** Processes RNDIS query commands, retrieving information from the adapter and reporting it back to the host. The requested
 *  parameter is given as an OID value.
 *
 *  \param OId           OId value of the parameter being queried
 *  \param QueryData     Pointer to any extra query data being sent by the host to the device inside the RNDIS message buffer
 *  \param QuerySize     Size in bytes of the extra query data being sent by the host
 *  \param ResponseData  Pointer to the start of the query response inside the RNDIS message buffer
 *  \param ResponseSize  Pointer to the size in bytes of the response data being sent to the host
 *
 *  \return Boolean true if the query was handled, false otherwise
 */
static bool ProcessNDISQuery(uint32_t OId, void* QueryData, uint16_t QuerySize,
                             void* ResponseData, uint16_t* ResponseSize)
{
	/* Handler for REMOTE_NDIS_QUERY_MSG messages */

	switch (OId)
	{
		case OID_GEN_SUPPORTED_LIST:
			*ResponseSize = sizeof(AdapterSupportedOIDList);
			
			/* Copy the list of supported NDIS OID tokens to the response buffer */
			memcpy_P(ResponseData, AdapterSupportedOIDList, sizeof(AdapterSupportedOIDList));
			
			return true;
		case OID_GEN_PHYSICAL_MEDIUM:
			*ResponseSize = sizeof(uint32_t);
			
			/* Indicate that the device is a true ethernet link */
			*((uint32_t*)ResponseData) = 0;
			
			return true;
		case OID_GEN_HARDWARE_STATUS:
			*ResponseSize = sizeof(uint32_t);
			
			/* Always indicate hardware ready */
			*((uint32_t*)ResponseData) = NdisHardwareStatusReady;
			
			return true;
		case OID_GEN_MEDIA_SUPPORTED:
		case OID_GEN_MEDIA_IN_USE:
			*ResponseSize = sizeof(uint32_t);
			
			/* Indicate 802.3 (Ethernet) supported by the adapter */
			*((uint32_t*)ResponseData) = REMOTE_NDIS_MEDIUM_802_3;
			
			return true;
		case OID_GEN_VENDOR_ID:
			*ResponseSize = sizeof(uint32_t);
			
			/* Vendor ID 0x0xFFFFFF is reserved for vendors who have not purchased a NDIS VID */
			*((uint32_t*)ResponseData) = 0x00FFFFFF;
			
			return true;
		case OID_GEN_MAXIMUM_FRAME_SIZE:
		case OID_GEN_TRANSMIT_BLOCK_SIZE:
		case OID_GEN_RECEIVE_BLOCK_SIZE:
			*ResponseSize = sizeof(uint32_t);
			
			/* Indicate that the maximum frame size is the size of the ethernet frame buffer */
			*((uint32_t*)ResponseData) = ETHERNET_FRAME_SIZE_MAX;
			
			return true;
		case OID_GEN_VENDOR_DESCRIPTION:
			*ResponseSize = sizeof(AdapterVendorDescription);
			
			/* Copy vendor description string to the response buffer */
			memcpy_P(ResponseData, AdapterVendorDescription, sizeof(AdapterVendorDescription));
			
			return true;
		case OID_GEN_MEDIA_CONNECT_STATUS:
			*ResponseSize = sizeof(uint32_t);
			
			/* Always indicate that the adapter is connected to a network */
			*((uint32_t*)ResponseData) = REMOTE_NDIS_MEDIA_STATE_CONNECTED;
			
			return true;
		case OID_GEN_LINK_SPEED:
			*ResponseSize = sizeof(uint32_t);
			
			/* Indicate 10Mb/s link speed */
			*((uint32_t*)ResponseData) = 100000;

			return true;
		case OID_802_3_PERMANENT_ADDRESS:
		case OID_802_3_CURRENT_ADDRESS:
			*ResponseSize = sizeof(MAC_Address_t);
			
			/* Copy over the fixed adapter MAC to the response buffer */
			memcpy_P(ResponseData, &AdapterMACAddress, sizeof(MAC_Address_t));

			return true;
		case OID_802_3_MAXIMUM_LIST_SIZE:
			*ResponseSize = sizeof(uint32_t);
			
			/* Indicate only one multicast address supported */
			*((uint32_t*)ResponseData) = 1;
		
			return true;
		case OID_GEN_CURRENT_PACKET_FILTER:
			*ResponseSize = sizeof(uint32_t);
			
			/* Indicate the current packet filter mask */
			*((uint32_t*)ResponseData) = CurrPacketFilter;
		
			return true;			
		case OID_GEN_XMIT_OK:
		case OID_GEN_RCV_OK:
		case OID_GEN_XMIT_ERROR:
		case OID_GEN_RCV_ERROR:
		case OID_GEN_RCV_NO_BUFFER:
		case OID_802_3_RCV_ERROR_ALIGNMENT:
		case OID_802_3_XMIT_ONE_COLLISION:
		case OID_802_3_XMIT_MORE_COLLISIONS:
			*ResponseSize = sizeof(uint32_t);
			
			/* Unused statistic OIDs - always return 0 for each */
			*((uint32_t*)ResponseData) = 0;
		
			return true;
		case OID_GEN_MAXIMUM_TOTAL_SIZE:
			*ResponseSize = sizeof(uint32_t);
			
			/* Indicate maximum overall buffer (Ethernet frame and RNDIS header) the adapter can handle */
			*((uint32_t*)ResponseData) = (sizeof(RNDISMessageBuffer) + ETHERNET_FRAME_SIZE_MAX);
		
			return true;
		default:
			return false;
	}
}

/** Processes RNDIS set commands, setting adapter parameters to values given by the host. The requested parameter is given 
 *  as an OID value.
 *
 *  \param OId      OId value of the parameter being set
 *  \param SetData  Pointer to the parameter value in the RNDIS message buffer
 *  \param SetSize  Size in bytes of the parameter value being sent by the host
 *
 *  \return Boolean true if the set was handled, false otherwise
 */
static bool ProcessNDISSet(uint32_t OId, void* SetData, uint16_t SetSize)
{
	/* Handler for REMOTE_NDIS_SET_MSG messages */

	switch (OId)
	{
		case OID_GEN_CURRENT_PACKET_FILTER:
			/* Save the packet filter mask in case the host queries it again later */
			CurrPacketFilter = *((uint32_t*)SetData);
		
			/* Set the RNDIS state to initialized if the packet filter is non-zero */
			CurrRNDISState = ((CurrPacketFilter) ? RNDIS_Data_Initialized : RNDIS_Data_Initialized);
			
			return true;
		case OID_802_3_MULTICAST_LIST:
			/* Do nothing - throw away the value from the host as it is unused */
		
			return true;
		default:
			return false;
	}
}
