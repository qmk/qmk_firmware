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

const struct
{
	uint8_t  Header;
	uint32_t Data;
} PROGMEM SDP_Attribute_ServiceHandle = {(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_32Bit), SWAPENDIAN_32(0x00010000)};

const struct
{
	uint8_t     Header;
	uint16_t    Size;
	ClassUUID_t UUIDList[];
} PROGMEM SDP_Attribute_ServiceClassIDs =
	{
		.Header = (SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable16Bit),
		.Size   = SWAPENDIAN_16(sizeof(ClassUUID_t) * 1),
		.UUIDList =
			{
				{.Header = (SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit), .UUID = {BASE_96BIT_UUID, 0x00, 0x10, 0x00, 0x00}}
			}
	};

const struct
{
	uint8_t     Header;
	uint8_t     Size;
	Item16Bit_t VersionList[];
} PROGMEM SDP_Attribute_Version =
	{
		.Header = (SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
		.Size   = (sizeof(Item16Bit_t) * 1),
		.VersionList =
			{
				{.Header = (SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_16Bit), .Value = SWAPENDIAN_16(0x0100)}
			}
	};

const struct
{
	uint8_t     Header;
	uint8_t     Size;
	Item16Bit_t OffsetList[];
} PROGMEM SDP_Attribute_LangOffset =
	{
		.Header = (SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
		.Size   = (sizeof(Item16Bit_t) * 1),
		.OffsetList =
			{
				{.Header = (SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_16Bit), .Value = SWAPENDIAN_16(0x0100)}
			}
	};

const struct
{
	uint8_t     Header;
	uint8_t     Size;
	char        Text[];
} PROGMEM SDP_Attribute_ServiceName =
	{
		.Header = (SDP_DATATYPE_String | SDP_DATASIZE_Variable8Bit),
		.Size   = sizeof("SDP") - 1,
		.Text   = "SDP",
	};

const struct
{
	uint8_t     Header;
	uint8_t     Size;
	char        Text[];
} PROGMEM SDP_Attribute_ServiceDescription =
	{
		.Header = (SDP_DATATYPE_String | SDP_DATASIZE_Variable8Bit),
		.Size   = sizeof("Service Discovery Protocol Server") - 1,
		.Text   = "Service Discovery Protocol Server",
	};

/** Service Discovery Protocol attribute table, listing all supported attributes of the service. */
const ServiceAttributeTable_t SDP_Attribute_Table[] PROGMEM =
	{
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE, .Data = &SDP_Attribute_ServiceHandle      },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICECLASSIDS,     .Data = &SDP_Attribute_ServiceClassIDs    },
		{.AttributeID = SDP_ATTRIBUTE_ID_VERSION,             .Data = &SDP_Attribute_Version            },
		{.AttributeID = SDP_ATTRIBUTE_ID_LANGIDOFFSET,        .Data = &SDP_Attribute_LangOffset         },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICENAME,         .Data = &SDP_Attribute_ServiceName        },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICEDESCRIPTION,  .Data = &SDP_Attribute_ServiceDescription },

		SERVICE_ATTRIBUTE_TABLE_TERMINATOR
	};

const struct
{
	uint8_t  Header;
	uint32_t Data;
} PROGMEM RFCOMM_Attribute_ServiceHandle = {(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_32Bit), SWAPENDIAN_32(0x00010001)};

const struct
{
	uint8_t     Header;
	uint16_t    Size;
	ClassUUID_t UUIDList[];
} PROGMEM RFCOMM_Attribute_ServiceClassIDs =
	{
		.Header = (SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable16Bit),
		.Size   = SWAPENDIAN_16(sizeof(ClassUUID_t) * 1),
		.UUIDList =
			{
				{.Header = (SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit), .UUID = {BASE_96BIT_UUID, 0x01, 0x11, 0x00, 0x00}}
			}
	};

const struct
{
	uint8_t     Header;
	uint8_t     Size;
	char        Text[];
} PROGMEM RFCOMM_Attribute_ServiceName =
	{
		.Header = (SDP_DATATYPE_String | SDP_DATASIZE_Variable8Bit),
		.Size   = sizeof("Serial Port") - 1,
		.Text   = "Serial Port",
	};

const struct
{
	uint8_t     Header;
	uint8_t     Size;
	char        Text[];
} PROGMEM RFCOMM_Attribute_ServiceDescription =
	{
		.Header = (SDP_DATATYPE_String | SDP_DATASIZE_Variable8Bit),
		.Size   = sizeof("Wireless Serial Port Service") - 1,
		.Text   = "Wireless Serial Port Service",
	};

const ServiceAttributeTable_t RFCOMM_Attribute_Table[] PROGMEM =
	{
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE, .Data = &RFCOMM_Attribute_ServiceHandle      },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICECLASSIDS,     .Data = &RFCOMM_Attribute_ServiceClassIDs    },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICENAME,         .Data = &RFCOMM_Attribute_ServiceName        },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICEDESCRIPTION,  .Data = &RFCOMM_Attribute_ServiceDescription },

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
		{   // 128-bit UUID for the RFCOMM service
			.UUID  = {BASE_96BIT_UUID, 0x03, 0x00, 0x00, 0x00},
			.AttributeTable = RFCOMM_Attribute_Table,
		},
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
void SDP_ProcessPacket(void* Data, Bluetooth_Channel_t* Channel)
{
	SDP_PDUHeader_t* SDPHeader = (SDP_PDUHeader_t*)Data;
	SDPHeader->ParameterLength = SwapEndian_16(SDPHeader->ParameterLength);

	BT_SDP_DEBUG(1, "SDP Packet Received");
	BT_SDP_DEBUG(2, "-- PDU ID: 0x%02X", SDPHeader->PDU);
	BT_SDP_DEBUG(2, "-- Param Length: 0x%04X", SDPHeader->ParameterLength);

	switch (SDPHeader->PDU)
	{
		case SDP_PDU_SERVICESEARCHREQUEST:
			SDP_ProcessServiceSearch(SDPHeader, Channel);
			break;		
		case SDP_PDU_SERVICEATTRIBUTEREQUEST:
			SDP_ProcessServiceAttribute(SDPHeader, Channel);
			break;
		case SDP_PDU_SERVICESEARCHATTRIBUTEREQUEST:
			SDP_ProcessServiceSearchAttribute(SDPHeader, Channel);
			break;
	}
}

/** Internal processing routine for SDP Service Search Requests.
 *
 *  \param[in] SDPHeader  Pointer to the start of the issued SDP request
 *  \param[in] Channel    Pointer to the Bluetooth channel structure the request was issued to
 */
static void SDP_ProcessServiceSearch(const SDP_PDUHeader_t* const SDPHeader, Bluetooth_Channel_t* const Channel)
{
	const void* CurrentParameter = ((void*)SDPHeader + sizeof(SDP_PDUHeader_t));

	BT_SDP_DEBUG(1, "<< Service Search");

	/* Retrieve the list of search UUIDs from the request */
	uint8_t UUIDList[12][UUID_SIZE_BYTES];
	uint8_t TotalUUIDs = SDP_GetUUIDList(UUIDList, &CurrentParameter);
	BT_SDP_DEBUG(2, "-- Total UUIDs: %d", TotalUUIDs);
	
	/* Retrieve the maximum service record reponse count from the request */
	uint16_t MaxServiceRecordCount = SwapEndian_16(*((uint16_t*)CurrentParameter));
	CurrentParameter += sizeof(uint16_t);
	BT_SDP_DEBUG(2, "-- Max Return Service Count: 0x%04X", MaxServiceRecordCount);
	
	struct
	{
		SDP_PDUHeader_t SDPHeader;
		uint16_t        TotalServiceRecordCount;
		uint16_t        CurrentServiceRecordCount;
		uint8_t         ResponseData[100];
	} ResponsePacket;

	/* Create a pointer to the buffer to indicate the current location for response data to be added */
	void* CurrResponsePos = ResponsePacket.ResponseData;
	
	uint8_t AddedServiceHandles = 0;

	/* Search through the list of UUIDs one at a time looking for matching search Attributes */
	for (uint8_t CurrUUIDItem = 0; CurrUUIDItem < TotalUUIDs; CurrUUIDItem++)
	{
		/* Retrieve the attribute table of the current search UUID from the global UUID table if it exists */
		ServiceAttributeTable_t* AttributeTable = SDP_GetAttributeTable(UUIDList[CurrUUIDItem]);
		
		/* If the UUID does not exist in the global UUID table, continue on to the next search UUID */
		if (AttributeTable == NULL)
		  continue;
		  
		BT_SDP_DEBUG(2, " -- Found UUID %d in table", CurrUUIDItem);

		/* Retrieve a PROGMEM pointer to the value of the service's record handle */
		const void* AttributeValue = SDP_GetAttributeValue(AttributeTable, SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE);

		/* Copy over the service record handle to the response list */
		uint8_t AttrHeaderSize;
		SDP_GetLocalAttributeContainerSize(AttributeValue, &AttrHeaderSize);
		memcpy_P(CurrResponsePos, AttributeValue + AttrHeaderSize, sizeof(uint32_t));
		CurrResponsePos += AttrHeaderSize + sizeof(uint32_t);
		
		/* Increment the total number of service records added to the list */
		AddedServiceHandles++;
	}

	/* Continuation state - always zero */
	*((uint8_t*)CurrResponsePos) = 0;

	/* Fill out the service record count values in the returned packet */
	ResponsePacket.TotalServiceRecordCount   = SwapEndian_16(AddedServiceHandles);
	ResponsePacket.CurrentServiceRecordCount = ResponsePacket.TotalServiceRecordCount;

	/* Calculate the total parameter length that is to be sent, including the fixed return parameters, the created service
	   handle list and the SDP continuation state */
	uint16_t ParamLength = (ResponsePacket.CurrentServiceRecordCount << 2) +
	                        sizeof(ResponsePacket.CurrentServiceRecordCount) +
	                        sizeof(ResponsePacket.TotalServiceRecordCount) +
	                        sizeof(uint8_t);

	/* Fill in the response packet's header */
	ResponsePacket.SDPHeader.PDU             = SDP_PDU_SERVICESEARCHRESPONSE;
	ResponsePacket.SDPHeader.TransactionID   = SDPHeader->TransactionID;
	ResponsePacket.SDPHeader.ParameterLength = SwapEndian_16(ParamLength);

	BT_SDP_DEBUG(1, ">> Service Search Response");

	/* Send the completed response packet to the sender */
	Bluetooth_SendPacket(&ResponsePacket, (sizeof(ResponsePacket.SDPHeader) + ParamLength), Channel);
}

/** Internal processing routine for SDP Service Attribute Requests.
 *
 *  \param[in] SDPHeader  Pointer to the start of the issued SDP request
 *  \param[in] Channel    Pointer to the Bluetooth channel structure the request was issued to
 */
static void SDP_ProcessServiceAttribute(const SDP_PDUHeader_t* const SDPHeader, Bluetooth_Channel_t* const Channel)
{
	BT_SDP_DEBUG(1, "<< Service Attribute");
}

/** Internal processing routine for SDP Service Search Attribute Requests.
 *
 *  \param[in] SDPHeader  Pointer to the start of the issued SDP request
 *  \param[in] Channel    Pointer to the Bluetooth channel structure the request was issued to
 */
static void SDP_ProcessServiceSearchAttribute(const SDP_PDUHeader_t* const SDPHeader, Bluetooth_Channel_t* const Channel)
{
	const void* CurrentParameter = ((void*)SDPHeader + sizeof(SDP_PDUHeader_t));
	
	BT_SDP_DEBUG(1, "<< Service Search Attribute");

	/* Retrieve the list of search UUIDs from the request */
	uint8_t UUIDList[12][UUID_SIZE_BYTES];
	uint8_t TotalUUIDs = SDP_GetUUIDList(UUIDList, &CurrentParameter);
	BT_SDP_DEBUG(2, "-- Total UUIDs: %d", TotalUUIDs);
	
	/* Retrieve the maximum Attribute reponse size from the request */
	uint16_t MaxAttributeSize = SwapEndian_16(*((uint16_t*)CurrentParameter));
	CurrentParameter += sizeof(uint16_t);
	BT_SDP_DEBUG(2, "-- Max Return Attribute Bytes: 0x%04X", MaxAttributeSize);
	
	/* Retrieve the list of Attributes from the request */
	uint16_t AttributeList[15][2];
	uint8_t  TotalAttributes = SDP_GetAttributeList(AttributeList, &CurrentParameter);
	BT_SDP_DEBUG(2, "-- Total Attributes: %d", TotalAttributes);
	
	struct
	{
		SDP_PDUHeader_t SDPHeader;
		uint16_t        AttributeListByteCount;
		uint8_t         ResponseData[100];
	} ResponsePacket;
	
	/* Create a pointer to the buffer to indicate the current location for response data to be added */
	void* CurrResponsePos = ResponsePacket.ResponseData;

	/* Clamp the maximum attribute size to the size of the allocated buffer */
	if (MaxAttributeSize > sizeof(ResponsePacket.ResponseData))
	  MaxAttributeSize = sizeof(ResponsePacket.ResponseData);

	/* Add the outer Data Element Sequence header for all of the retrieved Attributes */
	uint16_t* TotalResponseSize = SDP_AddDataElementHeader16(&CurrResponsePos, SDP_DATATYPE_Sequence);
	
	/* Search through the list of UUIDs one at a time looking for matching search Attributes */
	for (uint8_t CurrUUIDItem = 0; CurrUUIDItem < TotalUUIDs; CurrUUIDItem++)
	{
		/* Retrieve the attribute table of the current search UUID from the global UUID table if it exists */
		ServiceAttributeTable_t* AttributeTable = SDP_GetAttributeTable(UUIDList[CurrUUIDItem]);
		
		/* If the UUID does not exist in the global UUID table, continue on to the next search UUID */
		if (AttributeTable == NULL)
		  continue;
		  
		BT_SDP_DEBUG(2, " -- Found UUID %d in table", CurrUUIDItem);

		/* Add an inner Data Element Sequence header for the current UUID's found Attributes */
		uint16_t* CurrentUUIDResponseSize = SDP_AddDataElementHeader16(&CurrResponsePos, SDP_DATATYPE_Sequence);
		
		/* Search through the list of Attributes one at a time looking for values in the current UUID's Attribute table */
		for (uint8_t CurrAttribute = 0; CurrAttribute < TotalAttributes; CurrAttribute++)
		{
			uint16_t* AttributeIDRange = AttributeList[CurrAttribute];
		
			/* Look in the current Attribute Range for a matching Attribute ID in the UUID's Attribute table */
			for (uint32_t CurrAttributeID = AttributeIDRange[0]; CurrAttributeID <= AttributeIDRange[1]; CurrAttributeID++)
			{
				/* Retrieve a PROGMEM pointer to the value of the current Attribute ID, if it exists in the UUID's Attribute table */
				const void* AttributeValue = SDP_GetAttributeValue(AttributeTable, CurrAttributeID);
				
				/* If the Attribute does not exist in the current UUID's Attribute table, continue to the next Attribute ID */
				if (AttributeValue == NULL)
				  continue;
				
				BT_SDP_DEBUG(2, " -- Add Attribute 0x%04X", CurrAttributeID);

				/* Increment the current UUID's returned Attribute container size by the number of added bytes */
				*CurrentUUIDResponseSize += SDP_AddAttributeToResponse(CurrAttributeID, AttributeValue, &CurrResponsePos);
			}

			/* Increment the outer container size by the number of added bytes */
			*TotalResponseSize += 3 + *CurrentUUIDResponseSize;
		}

		/* Flip the endianness of the container's size */
		*CurrentUUIDResponseSize = SwapEndian_16(*CurrentUUIDResponseSize);
	}
	
	/* Continuation state - always zero */
	*((uint8_t*)CurrResponsePos) = 0;

	/* Set the total response list size to the size of the outer container plus its header size and continuation state */
	ResponsePacket.AttributeListByteCount    = SwapEndian_16(3 + *TotalResponseSize);

	/* Calculate the total parameter length that is to be sent, including the fixed return parameters, the created attribute
	   value list and the SDP continuation state */
	uint16_t ParamLength = (sizeof(ResponsePacket.AttributeListByteCount) + 
	                        (3 + *TotalResponseSize) +
	                        sizeof(uint8_t));

	/* Fill in the response packet's header */
	ResponsePacket.SDPHeader.PDU             = SDP_PDU_SERVICESEARCHATTRIBUTERESPONSE;
	ResponsePacket.SDPHeader.TransactionID   = SDPHeader->TransactionID;
	ResponsePacket.SDPHeader.ParameterLength = SwapEndian_16(ParamLength);

	/* Flip the endianness of the container's size */
	*TotalResponseSize = SwapEndian_16(*TotalResponseSize);

	BT_SDP_DEBUG(1, ">> Service Search Attribute Response");
	BT_SDP_DEBUG(2, "-- Param Len 0x%04X", ParamLength);

	/* Send the completed response packet to the sender */
	Bluetooth_SendPacket(&ResponsePacket, (sizeof(ResponsePacket.SDPHeader) + ParamLength), Channel);
}

/** Adds the given attribute ID and value to the reponse buffer, and advances the response buffer pointer past the added data.
 *
 *  \param[in] AttributeID          Attribute ID to add to the response buffer
 *  \param[in] AttributeValue       Pointer to the start of the Attribute's value, located in PROGMEM
 *  \param[in, out] ResponseBuffer  Pointer to a buffer where the Attribute and Attribute Value is to be added
 *
 *  \return Number of bytes added to the response buffer
 */
static uint16_t SDP_AddAttributeToResponse(const uint16_t AttributeID, const void* AttributeValue, void** ResponseBuffer)
{
	/* Retrieve the size of the attribute value from its container header */
	uint8_t  AttributeHeaderLength;
	uint32_t AttributeValueLength = SDP_GetLocalAttributeContainerSize(AttributeValue, &AttributeHeaderLength);
	
	/* Add a Data Element header to the response for the Attribute ID */
	*((uint8_t*)*ResponseBuffer) = (SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_16Bit);
	*ResponseBuffer += sizeof(uint8_t);
	
	/* Add the Attribute ID to the created Data Element */
	*((uint16_t*)*ResponseBuffer) = SwapEndian_16(AttributeID);
	*ResponseBuffer += sizeof(uint16_t);
	
	/* Copy over the Attribute value Data Element container to the response */
	memcpy_P(*ResponseBuffer, AttributeValue, AttributeHeaderLength + AttributeValueLength);
	*ResponseBuffer += AttributeHeaderLength + AttributeValueLength;
	
	return (sizeof(uint8_t) + sizeof(uint16_t) + AttributeHeaderLength + AttributeValueLength);
}

/** Retrieves a pointer to the value of the given Attribute ID from the given Attribute table.
 *
 *  \param[in] AttributeTable  Pointer to the Attribute table to search in
 *  \param[in] AttributeID     Attribute ID to search for within the table
 *
 *  \return Pointer to the start of the Attribute's value if found within the table, NULL otherwise
 */
static void* SDP_GetAttributeValue(const ServiceAttributeTable_t* AttributeTable, const uint16_t AttributeID)
{
	void* CurrTableItemData;
	
	/* Search through the current Attribute table, abort when the terminator item has been reached */
	while ((CurrTableItemData = (void*)pgm_read_word(&AttributeTable->Data)) != NULL)
	{
		/* Check if the current Attribute ID matches the search ID - if so return a pointer to it */
		if (pgm_read_word(&AttributeTable->AttributeID) == AttributeID)
		  return CurrTableItemData;
		
		AttributeTable++;
	}
			
	return NULL;
}

/** Retrieves the Attribute table for the given UUID if it exists.
 *
 *  \param[in] UUID  UUID to search for
 *
 *  \return Pointer to the UUID's associated Attribute table if found in the global UUID table, NULL otherwise
 */
static ServiceAttributeTable_t* SDP_GetAttributeTable(const uint8_t* const UUID)
{
	/* Search through the global UUID list an item at a time */
	for (uint8_t CurrTableItem = 0; CurrTableItem < (sizeof(SDP_Services_Table) / sizeof(ServiceTable_t)); CurrTableItem++)
	{
		/* Read in a pointer to the current UUID table entry's Attribute table */
		ServiceAttributeTable_t* CurrAttributeTable = (ServiceAttributeTable_t*)pgm_read_word(&SDP_Services_Table[CurrTableItem].AttributeTable);
	
		/* If the current table item's UUID matches the search UUID, return a pointer the table item's Attribute table */
		if (!(memcmp_P(UUID, SDP_Services_Table[CurrTableItem].UUID, UUID_SIZE_BYTES)))
		  return CurrAttributeTable;
		
		/* Retrieve the list of the service's Class UUIDs from its Attribute table */
		void* ClassUUIDs = SDP_GetAttributeValue(CurrAttributeTable, SDP_ATTRIBUTE_ID_SERVICECLASSIDS);
		
		/* Go to the next UUID in the table if the current item does not have a list of Class UUIDs */
		if (ClassUUIDs == NULL)
		  continue;
		  
		/* Retrieve the size of the Class UUID list and skip past the header to the first Class UUID in the list */ 
		uint8_t  ClassUUIDListHeaderSize;
		uint32_t ClassUUIDListSize = SDP_GetLocalAttributeContainerSize(ClassUUIDs, &ClassUUIDListHeaderSize);
		ClassUUIDs += ClassUUIDListHeaderSize;
		
		/* Check each class UUID in turn for a match */
		while (ClassUUIDListSize)
		{
			/* Current Service UUID's Class UUID list has a matching entry, return the Attribute table */
			if (!(memcmp_P(UUID, &((ClassUUID_t*)ClassUUIDs)->UUID, UUID_SIZE_BYTES)))
			  return CurrAttributeTable;
		
			ClassUUIDListSize -= sizeof(ClassUUID_t);
			ClassUUIDs        += sizeof(ClassUUID_t);
		}	
	}
	
	return NULL;
}

/** Reads in the collection of Attribute ranges from the input buffer's Data Element Sequence container, into the given 
 *  Attribute list for later use. Once complete, the input buffer pointer is advanced to the end of the Attribute container.
 *
 *  \param[out] AttributeList     Pointer to a buffer where the list of Attribute ranges are to be stored
 *  \param[in]  CurrentParameter  Pointer to a Buffer containing a Data Element Sequence of Attribute and Attribute Range elements
 *
 *  \return Total number of Attribute ranges stored in the Data Element Sequence
 */
static uint8_t SDP_GetAttributeList(uint16_t AttributeList[][2], const void** const CurrentParameter)
{
	uint8_t ElementHeaderSize;
	uint8_t TotalAttributes = 0;

	/* Retrieve the total size of the Attribute container, and unwrap the outer Data Element Sequence container */
	uint16_t AttributeIDListLength = SDP_GetDataElementSize(CurrentParameter, &ElementHeaderSize);
	BT_SDP_DEBUG(2, "-- Total Attribute Length: 0x%04X", AttributeIDListLength);
	while (AttributeIDListLength)
	{
		/* Retrieve the size of the next Attribute in the container and get a pointer to the next free Attribute element in the list */
		uint16_t* CurrentAttributeRange = AttributeList[TotalAttributes++];
		uint8_t   AttributeLength       = SDP_GetDataElementSize(CurrentParameter, &ElementHeaderSize);
		
		/* Copy over the starting Attribute ID and (if it the current element is a range) the ending Attribute ID */
		memcpy(&CurrentAttributeRange[0], *CurrentParameter, AttributeLength);
		
		/* If the element is not an Attribute Range, copy over the starting ID to the ending ID to make a range of 1 */
		if (AttributeLength == 2)
		  CurrentAttributeRange[1] = CurrentAttributeRange[0];

		/* Swap the endianness of the attribute range values */
		CurrentAttributeRange[0] = SwapEndian_16(CurrentAttributeRange[0]);
		CurrentAttributeRange[1] = SwapEndian_16(CurrentAttributeRange[1]);

		BT_SDP_DEBUG(2, "-- Attribute: 0x%04X-0x%04X", CurrentAttributeRange[0], CurrentAttributeRange[1]);
		
		AttributeIDListLength -= (AttributeLength + ElementHeaderSize);
		*CurrentParameter     += AttributeLength;
	}
	
	return TotalAttributes;
}

/** Reads in the collection of UUIDs from the input buffer's Data Element Sequence container, into the given 
 *  UUID list for later use. Once complete, the input buffer pointer is advanced to the end of the UUID container.
 *
 *  \param[out] UUIDList          Pointer to a buffer where the list of UUIDs are to be stored
 *  \param[in]  CurrentParameter  Pointer to a Buffer containing a Data Element Sequence of UUID elements
 *
 *  \return Total number of UUIDs stored in the Data Element Sequence
 */
static uint8_t SDP_GetUUIDList(uint8_t UUIDList[][UUID_SIZE_BYTES], const void** const CurrentParameter)
{
	uint8_t ElementHeaderSize;
	uint8_t TotalUUIDs = 0;

	/* Retrieve the total size of the UUID container, and unwrap the outer Data Element Sequence container */
	uint16_t ServicePatternLength = SDP_GetDataElementSize(CurrentParameter, &ElementHeaderSize);
	BT_SDP_DEBUG(2, "-- Total UUID Length: 0x%04X", ServicePatternLength);
	while (ServicePatternLength)
	{
		/* Retrieve the size of the next UUID in the container and get a pointer to the next free UUID element in the list */
		uint8_t* CurrentUUID = UUIDList[TotalUUIDs++];
		uint8_t  UUIDLength  = SDP_GetDataElementSize(CurrentParameter, &ElementHeaderSize);
		
		/* Copy over the base UUID value to the free UUID slot in the list */
		memcpy_P(CurrentUUID, BaseUUID, sizeof(BaseUUID));

		/* Copy over UUID from the container to the free slot - if a short UUID (<= 4 bytes) it replaces the lower
		   4 bytes of the base UUID, otherwise it replaces the UUID completely */
		if (UUIDLength <= 4)
		{
			memcpy(&CurrentUUID[UUID_SIZE_BYTES - 4], *CurrentParameter, UUIDLength);
			SwapEndian_n(&CurrentUUID[UUID_SIZE_BYTES - 4], UUIDLength);				
		}
		else
		{
			memcpy(&CurrentUUID[0], *CurrentParameter, UUIDLength);		
		}
		
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

/** Retrieves the total size of the given locally stored (in PROGMEM) attribute Data Element container.
 *
 *  \param[in] AttributeData  Pointer to the start of the Attribute container, located in PROGMEM
 *
 *  \return Size in bytes of the entire attribute container, including the header
 */
static uint32_t SDP_GetLocalAttributeContainerSize(const void* const AttributeData, uint8_t* const HeaderSize)
{
	/* Fetch the size of the Data Element structure from the header */
	uint8_t SizeIndex = (pgm_read_byte(AttributeData) & 0x07);
	
	/* Convert the Data Element size index into a size in bytes */
	switch (SizeIndex)
	{
		case SDP_DATASIZE_Variable8Bit:
			*HeaderSize = (1 + sizeof(uint8_t));
			return pgm_read_byte(AttributeData + 1);
		case SDP_DATASIZE_Variable16Bit:
			*HeaderSize = (1 + sizeof(uint16_t));
			return SwapEndian_16(pgm_read_word(AttributeData + 1));
		case SDP_DATASIZE_Variable32Bit:
			*HeaderSize = (1 + sizeof(uint32_t));
			return SwapEndian_32(pgm_read_dword(AttributeData + 1));
		default:
			*HeaderSize = 1;
			return (1 << SizeIndex);
	}

	return 0;
}

/** Retrieves the size of a Data Element container from the current input buffer, and advances the input buffer
 *  pointer to the start of the Data Element's contents.
 *
 *  \param[in, out] DataElementHeader  Pointer to the start of a Data Element header
 *  \param[out]     ElementHeaderSize  Size in bytes of the header that was skipped
 *
 *  \return Size in bytes of the Data Element container's contents, minus the header
 */
static uint32_t SDP_GetDataElementSize(const void** const DataElementHeader, uint8_t* const ElementHeaderSize)
{
	/* Fetch the size of the Data Element structure from the header, increment the current buffer pos */
	uint8_t SizeIndex = (*((uint8_t*)*DataElementHeader) & 0x07);
	*DataElementHeader += sizeof(uint8_t);
	
	uint32_t ElementValueSize;

	/* Convert the Data Element size index into a size in bytes */
	switch (SizeIndex)
	{
		case SDP_DATASIZE_Variable8Bit:
			ElementValueSize    = *((uint8_t*)*DataElementHeader);
			*DataElementHeader += sizeof(uint8_t);
			*ElementHeaderSize  = (1 + sizeof(uint8_t));
			break;
		case SDP_DATASIZE_Variable16Bit:
			ElementValueSize    = SwapEndian_16(*((uint16_t*)*DataElementHeader));
			*DataElementHeader += sizeof(uint16_t);
			*ElementHeaderSize  = (1 + sizeof(uint16_t));
			break;
		case SDP_DATASIZE_Variable32Bit:
			ElementValueSize    = SwapEndian_32(*((uint32_t*)*DataElementHeader));
			*DataElementHeader += sizeof(uint32_t);
			*ElementHeaderSize  = (1 + sizeof(uint32_t));
			break;
		default:
			ElementValueSize    = (1 << SizeIndex);
			*ElementHeaderSize  = 1;
			break;
	}
	
	return ElementValueSize;
}
