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

SERVICE_ATTRIBUTE_TEXT(SDP_Attribute_Name,             "SDP");
SERVICE_ATTRIBUTE_TEXT(SDP_Attribute_Description,      "BT Service Discovery");
SERVICE_ATTRIBUTE_8BIT_LEN(SDP_Attribute_Availability, SDP_DATATYPE_UNSIGNED_INT, 1, {0xFF});
const ServiceAttributeTable_t SDP_Attribute_Table[] PROGMEM =
	{
		{.AttributeID = SDP_ATTRIBUTE_NAME        , .AttributeData = &SDP_Attribute_Name},
		{.AttributeID = SDP_ATTRIBUTE_DESCRIPTION , .AttributeData = &SDP_Attribute_Description},
		{.AttributeID = SDP_ATTRIBUTE_AVAILABILITY, .AttributeData = &SDP_Attribute_Availability},
		SERVICE_ATTRIBUTE_TABLE_TERMINATOR
	};

SERVICE_ATTRIBUTE_TEXT(RFCOMM_Attribute_Name,             "RFCOMM");
SERVICE_ATTRIBUTE_TEXT(RFCOMM_Attribute_Description,      "Virtual Serial");
SERVICE_ATTRIBUTE_8BIT_LEN(RFCOMM_Attribute_Availability, SDP_DATATYPE_UNSIGNED_INT, 1, {0xFF});
const ServiceAttributeTable_t RFCOMM_Attribute_Table[] PROGMEM =
	{
		{.AttributeID = SDP_ATTRIBUTE_NAME        , .AttributeData = &RFCOMM_Attribute_Name},
		{.AttributeID = SDP_ATTRIBUTE_DESCRIPTION , .AttributeData = &RFCOMM_Attribute_Description},
		{.AttributeID = SDP_ATTRIBUTE_AVAILABILITY, .AttributeData = &RFCOMM_Attribute_Availability},
		SERVICE_ATTRIBUTE_TABLE_TERMINATOR
	};
	
const ServiceTable_t SDP_Services_Table[] =
	{
		{   // 128-bit UUID for the SDP service
			.UUID  = {BASE_96BIT_UUID, 0x01, 0x00, 0x00, 0x00},
			.AttributeTable = &SDP_Attribute_Table,
		},
		{   // 128-bit UUID for the RFCOMM service
			.UUID  = {BASE_96BIT_UUID, 0x03, 0x00, 0x00, 0x00},
			.AttributeTable = &RFCOMM_Attribute_Table,
		},
	};


void ServiceDiscovery_ProcessPacket(void* Data, Bluetooth_Channel_t* Channel)
{
	SDP_PDUHeader_t* SDPHeader = (SDP_PDUHeader_t*)Data;
	SDPHeader->ParameterLength = SwapEndian_16(SDPHeader->ParameterLength);

	BT_SDP_DEBUG(1, "SDP Packet Received");
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
	BT_SDP_DEBUG(1, "<< Service Search");
}

static void ServiceDiscovery_ProcessServiceAttribute(SDP_PDUHeader_t* SDPHeader)
{
	BT_SDP_DEBUG(1, "<< Service Attribute");
}

static void ServiceDiscovery_ProcessServiceSearchAttribute(SDP_PDUHeader_t* SDPHeader)
{
	void* CurrentParameter = ((void*)SDPHeader + sizeof(SDP_PDUHeader_t));
	
	BT_SDP_DEBUG(1, "<< Service Search Attribute");
	
	uint8_t ElementHeaderSize;

	uint16_t ServicePatternLength = ServiceDiscovery_GetDataElementSize(&CurrentParameter, &ElementHeaderSize);
	BT_SDP_DEBUG(2, "-- Total UUID Length: 0x%04X", ServicePatternLength);
	while (ServicePatternLength)
	{
		uint8_t UUIDLength = ServiceDiscovery_GetDataElementSize(&CurrentParameter, &ElementHeaderSize);
		uint8_t UUID[16] = {BASE_96BIT_UUID, 0x00, 0x00, 0x00, 0x00};

		if (UUIDLength <= 32)
		  memcpy(&UUID[sizeof(UUID) - sizeof(uint32_t)], CurrentParameter, UUIDLength);
		else
		  memcpy(UUID, CurrentParameter, UUIDLength);
		
		CurrentParameter += UUIDLength;
		
		BT_SDP_DEBUG(2, "-- UUID (%d): 0x%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
						UUIDLength,
		                UUID[15], UUID[14], UUID[13], UUID[12], UUID[11], UUID[10], UUID[9], UUID[8],
						UUID[7],  UUID[6],  UUID[5],  UUID[4],  UUID[3],  UUID[2],  UUID[1], UUID[0]);
	
		ServicePatternLength -= (UUIDLength + ElementHeaderSize);
	}
	
	uint16_t MaxAttributeSize = ServiceDiscovery_Read16BitParameter(&CurrentParameter);
	BT_SDP_DEBUG(2, "-- Max Return Attribute Bytes: 0x%04X", MaxAttributeSize);

	uint16_t AttributeIDListLength = ServiceDiscovery_GetDataElementSize(&CurrentParameter, &ElementHeaderSize);
	BT_SDP_DEBUG(2, "-- Total Attribute Length: 0x%04X", AttributeIDListLength);
	while (AttributeIDListLength)
	{
		uint8_t  AttributeLength = ServiceDiscovery_GetDataElementSize(&CurrentParameter, &ElementHeaderSize);
		uint32_t Attribute = 0;
		
		memcpy(&Attribute, CurrentParameter, AttributeLength);
		CurrentParameter += AttributeLength;
		
		BT_SDP_DEBUG(2, "-- Attribute(%d): 0x%08lX", AttributeLength, Attribute);
	
		AttributeIDListLength -= (AttributeLength + ElementHeaderSize);
	}
}

static uint32_t ServiceDiscovery_GetDataElementSize(void** DataElementHeader, uint8_t* ElementHeaderSize)
{
	uint8_t SizeIndex = (*((uint8_t*)*DataElementHeader) & 0x07);
	*DataElementHeader += sizeof(uint8_t);
	
	*ElementHeaderSize = 1;
	
	uint32_t ElementValue;
	
	switch (SizeIndex)
	{
		case 0:
			ElementValue = 1;
			break;
		case 1:
			ElementValue = 2;
			break;
		case 2:
			ElementValue = 4;
			break;
		case 3:
			ElementValue = 8;
			break;
		case 4:
			ElementValue = 16;
			break;
		case 5:
			ElementValue = *((uint8_t*)*DataElementHeader);
			*DataElementHeader += sizeof(uint8_t);
			*ElementHeaderSize  = (1 + sizeof(uint8_t));
			break;
		case 6:
			ElementValue = *((uint16_t*)*DataElementHeader);
			*DataElementHeader += sizeof(uint16_t);
			*ElementHeaderSize  = (1 + sizeof(uint16_t));
			break;
		default:
			ElementValue = *((uint32_t*)*DataElementHeader);
			*DataElementHeader += sizeof(uint32_t);
			*ElementHeaderSize  = (1 + sizeof(uint32_t));
			break;
	}
	
	return ElementValue;
}
