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

/** Service Discovery Protocol attribute, indicationg the service's name. */
const struct
{
	uint8_t Header;
	uint8_t Length;
	uint8_t Data[];
} PROGMEM SDP_Attribute_Name = {(SDP_DATATYPE_String | 5), sizeof("SDP"), "SDP"};

/** Service Discovery Protocol attribute, indicationg the service's description. */
const struct
{
	uint8_t Header;
	uint8_t Length;
	uint8_t Data[];
} PROGMEM SDP_Attribute_Description = {(SDP_DATATYPE_String | 5), sizeof("BT Service Discovery"), "BT Service Discovery"};

/** Service Discovery Protocol attribute, indicationg the service's availability. */
const struct
{
	uint8_t Header;
	uint8_t Data;
} PROGMEM SDP_Attribute_Availability = {(SDP_DATATYPE_UnsignedInt | 0), 0xFF};

const struct
{
	uint8_t  Header;
	uint16_t Data;
} PROGMEM SDP_Attribute_LanguageOffset = {(SDP_DATATYPE_UnsignedInt | 1), 0x0100};

const struct
{
	uint8_t  Header;
	uint16_t Data;
} PROGMEM SDP_Attribute_ServiceHandle = {(SDP_DATATYPE_UnsignedInt | 1), 0x0001};

const struct
{
	uint8_t     Header;
	uint8_t     Size;
	ClassUUID_t UUIDList[];
} PROGMEM SDP_Attribute_ServiceClassIDs =
	{
		(SDP_DATATYPE_Sequence | 5), (sizeof(ClassUUID_t) * 1),
		{
			{.Header = (SDP_DATATYPE_UUID | 5), .Size = UUID_SIZE_BYTES, .UUID = {BASE_96BIT_UUID, 0x01, 0x00, 0x00, 0x00}}
		}
	};

/** Service Discovery Protocol attribute table, listing all supported attributes of the service. */
const ServiceAttributeTable_t SDP_Attribute_Table[] PROGMEM =
	{
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE,   .Data = &SDP_Attribute_ServiceHandle},
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICECLASSIDS,       .Data = &SDP_Attribute_ServiceClassIDs},
		{.AttributeID = SDP_ATTRIBUTE_ID_LANGIDOFFSET,          .Data = &SDP_Attribute_LanguageOffset},
		{.AttributeID = SDP_ATTRIBUTE_IDO_PROVIDER    | 0x0100, .Data = &SDP_Attribute_Name},
		{.AttributeID = SDP_ATTRIBUTE_IDO_DESCRIPTION | 0x0100, .Data = &SDP_Attribute_Description},

		SERVICE_ATTRIBUTE_TABLE_TERMINATOR
	};

/** Master service table, listing all supported services (and their attribute tables) of the device, including
 *  each service's UUID.
 */
const ServiceTable_t SDP_Services_Table[] PROGMEM =
	{
		{   // 128-bit UUID for the SDP service
			.UUID  = {BASE_96BIT_UUID, 0x01, 0x00, 0x00, 0x00},
			.AttributeTable = SDP_Attribute_Table,
		},
#if 0
		{   // 128-bit UUID for the RFCOMM service
			.UUID  = {BASE_96BIT_UUID, 0x03, 0x00, 0x00, 0x00},
			.AttributeTable = RFCOMM_Attribute_Table,
		},
#endif
	};

/** Base UUID value common to all standardized Bluetooth services */
const uint8_t BaseUUID[] PROGMEM = {BASE_96BIT_UUID, 0x00, 0x00, 0x00, 0x00};


/** Main Service Discovery Protocol packet processing routine. This function processes incomming SDP packets from
 *  a connected Bluetooth device, and sends back appropriate responses to allow other devices to determine the
 *  services the local device exposes.
 *
 *  \param[in]  Data     Incomming packet data containing the SDP request
 *  \param[in]  Channel  Channel the request was issued to by the remote device
 */
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
	
	uint16_t AttributeList[15][2];
	uint8_t  TotalAttributes = ServiceDiscovery_GetAttributeList(AttributeList, &CurrentParameter);
	BT_SDP_DEBUG(2, "-- Total Attributes: %d", TotalAttributes);
	
	struct
	{
		SDP_PDUHeader_t SDPHeader;
		uint16_t        AttributeListByteCount;
		uint8_t         ResponseData[100];
	} ResponsePacket;
	
	uint8_t* CurrResponsePos = ResponsePacket.ResponseData;

	if (MaxAttributeSize > sizeof(ResponsePacket.ResponseData))
	  MaxAttributeSize = sizeof(ResponsePacket.ResponseData);
	  
	uint16_t* TotalResponseSize = ServiceDiscovery_AddDataElementHeader(&CurrResponsePos, SDP_DATATYPE_Sequence);
	for (uint8_t CurrUUIDItem = 0; CurrUUIDItem < TotalUUIDs; CurrUUIDItem++)
	{
		ServiceAttributeTable_t* AttributeTable = ServiceDiscovery_GetAttributeTable(UUIDList[CurrUUIDItem]);
		
		if (AttributeTable == NULL)
		  continue;
		  
		uint16_t* CurrentUUIDResponseSize = ServiceDiscovery_AddDataElementHeader(&CurrResponsePos, SDP_DATATYPE_Sequence);
		for (uint8_t CurrAttribute = 0; CurrAttribute < TotalAttributes; CurrAttribute++)
		{
			uint16_t* AttributeIDRange = AttributeList[CurrAttribute];
		
			for (uint32_t CurrAttributeID = AttributeIDRange[0]; CurrAttributeID <= AttributeIDRange[1]; CurrAttributeID++)
			{
				const void* AttributeValue = ServiceDiscovery_GetAttributeValue(AttributeTable, CurrAttributeID);
				
				if (AttributeValue == NULL)
				  continue;

				uint32_t AttributeValueLength = ServiceDiscovery_GetLocalAttributeSize(AttributeValue);
				
				BT_SDP_DEBUG(2, " -- Add Attribute 0x%04X", CurrAttributeID);

				*((uint8_t*)CurrResponsePos) = (1 | SDP_DATATYPE_UnsignedInt);
				CurrResponsePos += sizeof(uint8_t);
				*((uint16_t*)CurrResponsePos) = CurrAttributeID;
				CurrResponsePos += sizeof(uint16_t);				
				memcpy_P(CurrResponsePos, AttributeValue, AttributeValueLength);
				CurrResponsePos += AttributeValueLength;
								
				*CurrentUUIDResponseSize += sizeof(uint8_t) + sizeof(uint16_t) + AttributeValueLength;
			}

			*TotalResponseSize += 3 + *CurrentUUIDResponseSize;
		}
	}

	ResponsePacket.AttributeListByteCount    = (*TotalResponseSize + 3);
	ResponsePacket.SDPHeader.PDU             = SDP_PDU_SERVICESEARCHATTRIBUTERESPONSE;
	ResponsePacket.SDPHeader.TransactionID   = SDPHeader->TransactionID;
	ResponsePacket.SDPHeader.ParameterLength = (ResponsePacket.AttributeListByteCount + sizeof(ResponsePacket.AttributeListByteCount));

	BT_SDP_DEBUG(1, ">> Service Search Attribute Response");
	BT_SDP_DEBUG(2, "-- Total Parameter Length: 0x%04X", ResponsePacket.SDPHeader.ParameterLength);

	Bluetooth_SendPacket(&ResponsePacket, (sizeof(ResponsePacket.SDPHeader) + ResponsePacket.SDPHeader.ParameterLength),
	                     Channel);
}

static void* ServiceDiscovery_GetAttributeValue(ServiceAttributeTable_t* AttributeTable, uint16_t AttributeID)
{
	void* CurrTableItemData;
	while ((CurrTableItemData = (void*)pgm_read_word(&AttributeTable->Data)) != NULL)
	{
		if (pgm_read_word(&AttributeTable->AttributeID) == AttributeID)
		  return CurrTableItemData;
		
		AttributeTable++;
	}
			
	return NULL;
}

static ServiceAttributeTable_t* ServiceDiscovery_GetAttributeTable(uint8_t* UUID)
{
	for (uint8_t CurrTableItem = 0; CurrTableItem < (sizeof(SDP_Services_Table) / sizeof(ServiceTable_t)); CurrTableItem++)
	{
		if (!(memcmp_P(UUID, SDP_Services_Table[CurrTableItem].UUID, UUID_SIZE_BYTES)))
		  return (ServiceAttributeTable_t*)pgm_read_word(&SDP_Services_Table[CurrTableItem].AttributeTable);
	}
	
	return NULL;
}

static uint8_t ServiceDiscovery_GetAttributeList(uint16_t AttributeList[][2], const void** CurrentParameter)
{
	uint8_t ElementHeaderSize;
	uint8_t TotalAttributes = 0;

	uint16_t AttributeIDListLength = ServiceDiscovery_GetDataElementSize(CurrentParameter, &ElementHeaderSize);
	BT_SDP_DEBUG(2, "-- Total Attribute Length: 0x%04X", AttributeIDListLength);
	while (AttributeIDListLength)
	{
		uint8_t AttributeLength = ServiceDiscovery_GetDataElementSize(CurrentParameter, &ElementHeaderSize);
		
		memcpy(&AttributeList[TotalAttributes][0], *CurrentParameter, AttributeLength);
		
		if (AttributeLength == 2)
		  memcpy(&AttributeList[TotalAttributes][1], *CurrentParameter, 2);

		BT_SDP_DEBUG(2, "-- Attribute: 0x%04X-0x%04X", AttributeList[TotalAttributes][0], AttributeList[TotalAttributes][1]);
		
		TotalAttributes++;
		
		AttributeIDListLength -= (AttributeLength + ElementHeaderSize);
		*CurrentParameter     += AttributeLength;
	}
	
	return TotalAttributes;
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
		
		memcpy_P(CurrentUUID, BaseUUID, sizeof(BaseUUID));
		memcpy(&CurrentUUID[(UUIDLength <= 4) ? (UUID_SIZE_BYTES - 4) : 0], *CurrentParameter, UUIDLength);
		
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

static uint32_t ServiceDiscovery_GetLocalAttributeSize(const void* AttributeData)
{
	/* Fetch the size of the Data Element structure from the header */
	uint8_t SizeIndex = (pgm_read_byte(AttributeData) & 0x07);
	
	/* Convert the Data Element size index into a size in bytes */
	switch (SizeIndex)
	{
		case 5:
			return (1 + sizeof(uint8_t)) + pgm_read_byte(AttributeData + 1);
		case 6:
			return (1 + sizeof(uint16_t)) + pgm_read_word(AttributeData + 1);
		case 7:
			return (1 + sizeof(uint32_t)) + pgm_read_dword(AttributeData + 1);
		default:
			return (1 + (1 << SizeIndex));
	}

	return 0;
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
