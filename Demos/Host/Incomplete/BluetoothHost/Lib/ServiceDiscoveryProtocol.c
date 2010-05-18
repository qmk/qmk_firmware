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

SERVICE_ATTRIBUTE_TEXT(SDP_Attribute_Name,         "SDP");
SERVICE_ATTRIBUTE_TEXT(SDP_Attribute_Description,  "BT Service Discovery");
SERVICE_ATTRIBUTE_LEN8(SDP_Attribute_Availability, SDP_DATATYPE_UNSIGNED_INT, 1, {0xFF});
const ServiceAttributeTable_t SDP_Attribute_Table[] PROGMEM =
	{
		{.AttributeID = SDP_ATTRIBUTE_NAME        , .Data = &SDP_Attribute_Name},
		{.AttributeID = SDP_ATTRIBUTE_DESCRIPTION , .Data = &SDP_Attribute_Description},
		{.AttributeID = SDP_ATTRIBUTE_AVAILABILITY, .Data = &SDP_Attribute_Availability},
		SERVICE_ATTRIBUTE_TABLE_TERMINATOR
	};

SERVICE_ATTRIBUTE_TEXT(RFCOMM_Attribute_Name,         "RFCOMM");
SERVICE_ATTRIBUTE_TEXT(RFCOMM_Attribute_Description,  "Virtual Serial");
SERVICE_ATTRIBUTE_LEN8(RFCOMM_Attribute_Availability, SDP_DATATYPE_UNSIGNED_INT, 1, {0xFF});
const ServiceAttributeTable_t RFCOMM_Attribute_Table[] PROGMEM =
	{
		{.AttributeID = SDP_ATTRIBUTE_NAME        , .Data = &RFCOMM_Attribute_Name},
		{.AttributeID = SDP_ATTRIBUTE_DESCRIPTION , .Data = &RFCOMM_Attribute_Description},
		{.AttributeID = SDP_ATTRIBUTE_AVAILABILITY, .Data = &RFCOMM_Attribute_Availability},
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

const uint8_t BaseUUID[] = {BASE_96BIT_UUID, 0x00, 0x00, 0x00, 0x00};


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
			ServiceDiscovery_ProcessServiceSearch(SDPHeader, Channel);
			break;		
		case SDP_PDU_SERVICEATTRIBUTEREQUEST:
			ServiceDiscovery_ProcessServiceAttribute(SDPHeader, Channel);
			break;
		case SDP_PDU_SERVICESEARCHATTRIBUTEREQUEST:
			ServiceDiscovery_ProcessServiceSearchAttribute(SDPHeader, Channel);
			break;
	}
}

static void ServiceDiscovery_ProcessServiceSearch(SDP_PDUHeader_t* SDPHeader, Bluetooth_Channel_t* Channel)
{
	BT_SDP_DEBUG(1, "<< Service Search");
}

static void ServiceDiscovery_ProcessServiceAttribute(SDP_PDUHeader_t* SDPHeader, Bluetooth_Channel_t* Channel)
{
	BT_SDP_DEBUG(1, "<< Service Attribute");
}

static void ServiceDiscovery_ProcessServiceSearchAttribute(SDP_PDUHeader_t* SDPHeader, Bluetooth_Channel_t* Channel)
{
	const void* CurrentParameter = ((void*)SDPHeader + sizeof(SDP_PDUHeader_t));
	
	BT_SDP_DEBUG(1, "<< Service Search Attribute");

	uint8_t UUIDList[12][UUID_SIZE_BYTES];
	uint8_t TotalUUIDs = ServiceDiscovery_GetUUIDList(UUIDList, &CurrentParameter);
	BT_SDP_DEBUG(2, "-- Total UUIDs: %d", TotalUUIDs);
	
	uint16_t MaxAttributeSize = ServiceDiscovery_Read16BitParameter(&CurrentParameter);
	BT_SDP_DEBUG(2, "-- Max Return Attribute Bytes: 0x%04X", MaxAttributeSize);

	struct
	{
		SDP_PDUHeader_t SDPHeader;
		uint8_t         ResponseData[100];
	} ResponsePacket;
	
	ResponsePacket.SDPHeader.PDU           = SDP_PDU_SERVICESEARCHATTRIBUTERESPONSE;
	ResponsePacket.SDPHeader.TransactionID = SDPHeader->TransactionID;
	
	if (MaxAttributeSize > sizeof(ResponsePacket.ResponseData))
	  MaxAttributeSize = sizeof(ResponsePacket.ResponseData);
	  
	ResponsePacket.SDPHeader.ParameterLength = ServiceDiscovery_ProcessAttributes(UUIDList, TotalUUIDs,
	                                                                              ResponsePacket.ResponseData,
	                                                                              MaxAttributeSize, &CurrentParameter);

	Bluetooth_SendPacket(&ResponsePacket, (sizeof(ResponsePacket.SDPHeader) + ResponsePacket.SDPHeader.ParameterLength),
	                     Channel);
}

static uint8_t ServiceDiscovery_ProcessAttributes(uint8_t UUIDList[][UUID_SIZE_BYTES], const uint8_t TotalUUIDs, uint8_t* ResponseBuffer,
                                                  uint8_t MaxResponseSize, const void** CurrentParameter)
{
	uint8_t ElementHeaderSize;
	uint8_t TotalResponseSize = 0;

	uint16_t AttributeIDListLength = ServiceDiscovery_GetDataElementSize(CurrentParameter, &ElementHeaderSize);
	BT_SDP_DEBUG(2, "-- Total Attribute Length: 0x%04X", AttributeIDListLength);
	while (AttributeIDListLength)
	{
		uint8_t  AttributeLength = ServiceDiscovery_GetDataElementSize(CurrentParameter, &ElementHeaderSize);
		uint32_t Attribute       = 0;
		
		memcpy(&Attribute, CurrentParameter, AttributeLength);
		
		BT_SDP_DEBUG(2, "-- Attribute(%d): 0x%08lX", AttributeLength, Attribute);
		
		uint8_t TotalBytesAdded = ServiceDiscovery_GetAttribute(UUIDList, TotalUUIDs, Attribute, &ResponseBuffer,
		                                                        MaxResponseSize);
		TotalResponseSize += TotalBytesAdded;
		MaxResponseSize   -= TotalBytesAdded;
	
		AttributeIDListLength -= (AttributeLength + ElementHeaderSize);
		CurrentParameter      += AttributeLength;
	}
	
	return TotalResponseSize;
}

static uint8_t ServiceDiscovery_GetAttribute(uint8_t UUIDList[][UUID_SIZE_BYTES], const uint8_t TotalUUIDs, const uint32_t Attribute,
                                             uint8_t** DataBuffer, uint8_t BufferLen)
{
	for (uint8_t CurrTableItem = 0; CurrTableItem < (sizeof(SDP_Services_Table) / sizeof(ServiceTable_t)); CurrTableItem++)
	{
		for (uint8_t CurrUUIDIndex = 0; CurrUUIDIndex < TotalUUIDs; CurrUUIDIndex++)
		{
			if (!(memcmp(SDP_Services_Table[CurrTableItem].UUID, UUIDList[CurrUUIDIndex], UUID_SIZE_BYTES)))
			{
				const ServiceAttributeTable_t* AttributeTable = SDP_Services_Table[CurrTableItem].AttributeTable;

				// Process attribute table
				BT_SDP_DEBUG(2, "FOUND UUID IN TABLE");

				break;
			}
		}
	}
		
	return 0;
}

static uint8_t ServiceDiscovery_GetUUIDList(uint8_t UUIDList[][UUID_SIZE_BYTES], const void** CurrentParameter)
{
	uint8_t ElementHeaderSize;
	uint8_t TotalUUIDs = 0;

	uint16_t ServicePatternLength = ServiceDiscovery_GetDataElementSize(CurrentParameter, &ElementHeaderSize);
	BT_SDP_DEBUG(2, "-- Total UUID Length: 0x%04X", ServicePatternLength);
	while (ServicePatternLength)
	{
		uint8_t* CurrentUUID = UUIDList[TotalUUIDs++];
		uint8_t  UUIDLength  = ServiceDiscovery_GetDataElementSize(CurrentParameter, &ElementHeaderSize);
		
		memcpy(CurrentUUID, BaseUUID, sizeof(BaseUUID));
		memcpy(&CurrentUUID[(UUIDLength <= 32) ? (sizeof(BaseUUID) - 32) : 0], *CurrentParameter, UUIDLength);
		
		BT_SDP_DEBUG(2, "-- UUID (%d): 0x%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		                UUIDLength,
		                CurrentUUID[15], CurrentUUID[14], CurrentUUID[13], CurrentUUID[12],
		                CurrentUUID[11], CurrentUUID[10], CurrentUUID[9],  CurrentUUID[8],
		                CurrentUUID[7],  CurrentUUID[6],  CurrentUUID[5],  CurrentUUID[4],
		                CurrentUUID[3],  CurrentUUID[2],  CurrentUUID[1],  CurrentUUID[0]);

		ServicePatternLength -= (UUIDLength + ElementHeaderSize);
		*CurrentParameter    += UUIDLength;
	}
	
	return TotalUUIDs;
}

static uint32_t ServiceDiscovery_GetDataElementSize(const void** DataElementHeader, uint8_t* ElementHeaderSize)
{
	/* Fetch the size of the Data Element structure from the header, increment the current buffer pos */
	uint8_t SizeIndex = (*((uint8_t*)*DataElementHeader) & 0x07);
	*DataElementHeader += sizeof(uint8_t);
	
	uint32_t ElementValue;

	/* Convert the Data Element size index into a size in bytes */
	switch (SizeIndex)
	{
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
		case 7:
			ElementValue = *((uint32_t*)*DataElementHeader);
			*DataElementHeader += sizeof(uint32_t);
			*ElementHeaderSize  = (1 + sizeof(uint32_t));
			break;
		default:
			ElementValue = (1 << SizeIndex);
			*ElementHeaderSize = 1;
			break;
	}
	
	return ElementValue;
}
