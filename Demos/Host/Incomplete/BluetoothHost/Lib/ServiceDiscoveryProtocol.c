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

#define  INCLUDE_FROM_SERVICEDISCOVERYPROTOCOL_C
#include "ServiceDiscoveryProtocol.h"

void ServiceDiscovery_ProcessPacket(void* Data, Bluetooth_Channel_t* Channel)
{
	SDP_PDUHeader_t* SDPHeader = (SDP_PDUHeader_t*)Data;
	SDPHeader->ParameterLength = SwapEndian_16(SDPHeader->ParameterLength);

	BT_SDP_DEBUG(1, "SDP Packet Received", NULL);
	BT_SDP_DEBUG(2, "-- PDU ID: 0x%02X", SDPHeader->PDU);
	BT_SDP_DEBUG(2, "-- Param Length: 0x%04X", SDPHeader->ParameterLength);
	
	switch (SDPHeader->PDU)
	{
		case SDP_PDU_SERVICESEARCHREQUEST:
			ServiceDiscovery_ProcessServiceSearch(SDPHeader);
			break;		
		case SDP_PDU_SERVICEATTRIBUTEREQUEST:
			ServiceDiscovery_ProcessServiceAttribute(SDPHeader);
			break;
		case SDP_PDU_SERVICESEARCHATTRIBUTEREQUEST:
			ServiceDiscovery_ProcessServiceSearchAttribute(SDPHeader);
			break;
	}
}

static void ServiceDiscovery_ProcessServiceSearch(SDP_PDUHeader_t* SDPHeader)
{
	BT_SDP_DEBUG(1, "<< Service Search", NULL);
}

static void ServiceDiscovery_ProcessServiceAttribute(SDP_PDUHeader_t* SDPHeader)
{
	BT_SDP_DEBUG(1, "<< Service Attribute", NULL);
}

static void ServiceDiscovery_ProcessServiceSearchAttribute(SDP_PDUHeader_t* SDPHeader)
{
	uint8_t* CurrentParameter = ((uint8_t*)SDPHeader + sizeof(SDP_PDUHeader_t));
	
	BT_SDP_DEBUG(1, "<< Service Search Attribute", NULL);

	uint8_t ServicePatternLength = ServiceDiscovery_GetDataElementSize(CurrentParameter);
	while (ServicePatternLength)
	{
		uint8_t UUIDLength = ServiceDiscovery_GetDataElementSize(CurrentParameter);
		uint8_t UUID[16];
		
		memset(UUID, 0x00, sizeof(UUID));
		memcpy(&UUID[sizeof(UUID) - UUIDLength], CurrentParameter, UUIDLength);
		
		BT_SDP_DEBUG(2, "-- UUID: 0x%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
		                UUID[0], UUID[1], UUID[2], UUID[3], UUID[4], UUID[5], UUID[6], UUID[7],
						UUID[8], UUID[9], UUID[10], UUID[11], UUID[12], UUID[13], UUID[14], UUID[15]);
	
		ServicePatternLength -= UUIDLength;
	}
	
	uint16_t MaxAttributeSize = ServiceDiscovery_Read16BitParameter(CurrentParameter);

	uint8_t AttributeIDListLength = ServiceDiscovery_GetDataElementSize(CurrentParameter);
	while (AttributeIDListLength)
	{
		uint8_t AttributeLength = ServiceDiscovery_GetDataElementSize(CurrentParameter);
		
		BT_SDP_DEBUG(2, "-- Attribute Length: 0x%04X", AttributeLength);
	
		AttributeIDListLength -= AttributeLength;
	}
}

static uint32_t ServiceDiscovery_GetDataElementSize(void* DataElementHeader)
{
	uint8_t SizeIndex = (*((uint8_t*)DataElementHeader++) & 0x07);

	switch (SizeIndex)
	{
		case 0:
			return 1;
		case 1:
			return 2;
		case 2:
			return 4;
		case 3:
			return 8;
		case 4:
			return 16;
		case 5:
			return *((uint8_t*)DataElementHeader++);
		case 6:
			return *((uint16_t*)DataElementHeader++);
		default:
			return *((uint32_t*)DataElementHeader++);
	}
}
