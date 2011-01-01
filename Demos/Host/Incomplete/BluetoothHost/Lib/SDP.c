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
 *
 *  SDP layer module. This module implements a simple Service Discovery
 *  Protocol server, which can broadcast the device's supported services
 *  to other Bluetooth devices upon request, so that they can determine
 *  what services are available.
 */

/*
	TODO: Honor remote device's buffer size constraints via continuation state
 */

#define  INCLUDE_FROM_SERVICEDISCOVERYPROTOCOL_C
#include "SDP.h"

/** Service attribute table list, containing a pointer to each service attribute table the device contains */
const ServiceAttributeTable_t* SDP_Services_Table[] PROGMEM =
	{
		SerialPort_Attribute_Table,
	};

/** Base UUID value common to all standardized Bluetooth services */
const UUID_t BaseUUID PROGMEM = {0x00000000, BASE_80BIT_UUID};

/** Main Service Discovery Protocol packet processing routine. This function processes incoming SDP packets from
 *  a connected Bluetooth device, and sends back appropriate responses to allow other devices to determine the
 *  services the local device exposes.
 *
 *  \param[in] Data     Incoming packet data containing the SDP request
 *  \param[in] Channel  ACL channel the request was issued to by the remote device
 */
void SDP_ProcessPacket(void* Data, Bluetooth_Channel_t* const Channel)
{
	SDP_PDUHeader_t* SDPHeader = (SDP_PDUHeader_t*)Data;
	SDPHeader->ParameterLength = SwapEndian_16(SDPHeader->ParameterLength);

	BT_SDP_DEBUG(1, "SDP Packet Received");
	BT_SDP_DEBUG(2, "-- PDU ID: 0x%02X", SDPHeader->PDU);
	BT_SDP_DEBUG(2, "-- Param Length: 0x%04X", SDPHeader->ParameterLength);

	/* Dispatch to the correct processing routine for the given SDP packet type */
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
static void SDP_ProcessServiceSearch(const SDP_PDUHeader_t* const SDPHeader,
                                     Bluetooth_Channel_t* const Channel)
{
	const void* CurrentParameter = ((const void*)SDPHeader + sizeof(SDP_PDUHeader_t));

	BT_SDP_DEBUG(1, "<< Service Search");

	/* Retrieve the list of search UUIDs from the request */
	uint8_t UUIDList[12][UUID_SIZE_BYTES];
	uint8_t TotalUUIDs = SDP_GetUUIDList(UUIDList, &CurrentParameter);
	BT_SDP_DEBUG(2, "-- Total UUIDs: %d", TotalUUIDs);

	/* Retrieve the maximum service record response count from the request */
	uint16_t MaxServiceRecordCount = SDP_ReadData16(&CurrentParameter);
	BT_SDP_DEBUG(2, "-- Max Return Service Count: 0x%04X", MaxServiceRecordCount);

	struct
	{
		SDP_PDUHeader_t SDPHeader;
		uint16_t        TotalServiceRecordCount;
		uint16_t        CurrentServiceRecordCount;
		uint8_t         ResponseData[100];
	} ResponsePacket;

	uint8_t AddedServiceHandles = 0;

	/* Create a pointer to the buffer to indicate the current location for response data to be added */
	void* CurrResponsePos = ResponsePacket.ResponseData;

	/* Search through the global service list an item at a time */
	for (uint8_t CurrTableItem = 0; CurrTableItem < (sizeof(SDP_Services_Table) / sizeof(void*)); CurrTableItem++)
	{
		/* Read in a pointer to the current UUID table entry's Attribute table */
		ServiceAttributeTable_t* CurrAttributeTable = pgm_read_ptr(&SDP_Services_Table[CurrTableItem]);

		if (!(SDP_SearchServiceTable(UUIDList, TotalUUIDs, CurrAttributeTable)))
		  continue;

		BT_SDP_DEBUG(2, " -- Found search match in table");

		/* Retrieve a PROGMEM pointer to the value of the service's record handle */
		const void* AttributeValue = SDP_GetAttributeValue(CurrAttributeTable, SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE);

		/* Copy over the service record handle to the response list */
		uint8_t AttrHeaderSize;
		uint8_t AttrSize = SDP_GetLocalAttributeContainerSize(AttributeValue, &AttrHeaderSize);
		memcpy_P(CurrResponsePos, AttributeValue + AttrHeaderSize, AttrSize);
		CurrResponsePos += AttrHeaderSize + AttrSize;

		AddedServiceHandles++;
	}

	/* Continuation state - always zero */
	SDP_WriteData8(&CurrResponsePos, 0);

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
static void SDP_ProcessServiceAttribute(const SDP_PDUHeader_t* const SDPHeader,
                                        Bluetooth_Channel_t* const Channel)
{
	const void* CurrentParameter = ((const void*)SDPHeader + sizeof(SDP_PDUHeader_t));

	BT_SDP_DEBUG(1, "<< Service Attribute");

	/* Retrieve the service handle whose attributes are to be examined */
	uint32_t ServiceHandle = SDP_ReadData32(&CurrentParameter);
	BT_SDP_DEBUG(2, "-- Service Handle: 0x%08lX", ServiceHandle);

	/* Retrieve the maximum Attribute response size from the request */
	uint16_t MaxAttributeSize = SDP_ReadData16(&CurrentParameter);
	BT_SDP_DEBUG(2, "-- Max Return Attribute Bytes: 0x%04X", MaxAttributeSize);

	/* Retrieve the list of Attributes from the request */
	uint16_t AttributeList[8][2];
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

	uint16_t TotalResponseSize = 0;

	/* Search through the global UUID list an item at a time */
	for (uint8_t CurrTableItem = 0; CurrTableItem < (sizeof(SDP_Services_Table) / sizeof(void*)); CurrTableItem++)
	{
		/* Read in a pointer to the current UUID table entry's Attribute table */
		ServiceAttributeTable_t* CurrAttributeTable = pgm_read_ptr(&SDP_Services_Table[CurrTableItem]);

		/* Retrieve a PROGMEM pointer to the value of the Service Record Handle */
		const void* ServiceRecord = SDP_GetAttributeValue(CurrAttributeTable, SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE);

		/* Get the size of the header for the Service Record Handle */
		uint8_t AttrHeaderSize;
		SDP_GetLocalAttributeContainerSize(ServiceRecord, &AttrHeaderSize);

		/* Retrieve the endian-swapped service handle of the current service being examined */
		uint32_t CurrServiceHandle = SwapEndian_32(pgm_read_dword(ServiceRecord + AttrHeaderSize));

		/* Check if the current service in the service table has the requested service handle */
		if (ServiceHandle == CurrServiceHandle)
		{
			/* Add the listed attributes for the found UUID to the response */
			TotalResponseSize = SDP_AddListedAttributesToResponse(CurrAttributeTable, AttributeList, TotalAttributes,
		                                                          &CurrResponsePos);

			/* Requested service found, abort the search through the service table */
			break;
		}
	}

	/* Continuation state - always zero */
	SDP_WriteData8(&CurrResponsePos, 0);

	/* Set the total response list size to the size of the outer container plus its header size and continuation state */
	ResponsePacket.AttributeListByteCount    = SwapEndian_16(TotalResponseSize);

	/* Calculate the total parameter length that is to be sent, including the fixed return parameters, the created attribute
	   value list and the SDP continuation state */
	uint16_t ParamLength = (sizeof(ResponsePacket.AttributeListByteCount) + TotalResponseSize + sizeof(uint8_t));

	/* Fill in the response packet's header */
	ResponsePacket.SDPHeader.PDU             = SDP_PDU_SERVICEATTRIBUTERESPONSE;
	ResponsePacket.SDPHeader.TransactionID   = SDPHeader->TransactionID;
	ResponsePacket.SDPHeader.ParameterLength = SwapEndian_16(ParamLength);

	BT_SDP_DEBUG(1, ">> Service Attribute Response");
	BT_SDP_DEBUG(2, "-- Param Len 0x%04X", ParamLength);

	/* Send the completed response packet to the sender */
	Bluetooth_SendPacket(&ResponsePacket, (sizeof(ResponsePacket.SDPHeader) + ParamLength), Channel);
}

/** Internal processing routine for SDP Service Search Attribute Requests.
 *
 *  \param[in] SDPHeader  Pointer to the start of the issued SDP request
 *  \param[in] Channel    Pointer to the Bluetooth channel structure the request was issued to
 */
static void SDP_ProcessServiceSearchAttribute(const SDP_PDUHeader_t* const SDPHeader,
                                              Bluetooth_Channel_t* const Channel)
{
	const void* CurrentParameter = ((const void*)SDPHeader + sizeof(SDP_PDUHeader_t));

	BT_SDP_DEBUG(1, "<< Service Search Attribute");

	/* Retrieve the list of search UUIDs from the request */
	uint8_t UUIDList[12][UUID_SIZE_BYTES];
	uint8_t TotalUUIDs = SDP_GetUUIDList(UUIDList, &CurrentParameter);
	BT_SDP_DEBUG(2, "-- Total UUIDs: %d", TotalUUIDs);

	/* Retrieve the maximum Attribute response size from the request */
	uint16_t MaxAttributeSize = SDP_ReadData16(&CurrentParameter);
	BT_SDP_DEBUG(2, "-- Max Return Attribute Bytes: 0x%04X", MaxAttributeSize);

	/* Retrieve the list of Attributes from the request */
	uint16_t AttributeList[8][2];
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
	uint16_t* TotalResponseSize = SDP_AddSequence16(&CurrResponsePos);

	/* Search through the global service list an item at a time */
	for (uint8_t CurrTableItem = 0; CurrTableItem < (sizeof(SDP_Services_Table) / sizeof(void*)); CurrTableItem++)
	{
		/* Read in a pointer to the current UUID table entry's Attribute table */
		ServiceAttributeTable_t* CurrAttributeTable = pgm_read_ptr(&SDP_Services_Table[CurrTableItem]);

		if (!(SDP_SearchServiceTable(UUIDList, TotalUUIDs, CurrAttributeTable)))
		  continue;

		BT_SDP_DEBUG(2, " -- Found search match in table");

		/* Add the listed attributes for the found UUID to the response */
		*TotalResponseSize += SDP_AddListedAttributesToResponse(CurrAttributeTable, AttributeList, TotalAttributes,
		                                                        &CurrResponsePos);
	}

	/* Continuation state - always zero */
	SDP_WriteData8(&CurrResponsePos, 0);

	/* Set the total response list size to the size of the outer container plus its header size and continuation state */
	ResponsePacket.AttributeListByteCount    = SwapEndian_16(3 + *TotalResponseSize);

	/* Calculate the total parameter length that is to be sent, including the fixed return parameters, the created attribute
	   value list and the SDP continuation state */
	uint16_t ParamLength = (sizeof(ResponsePacket.AttributeListByteCount) +
	                        (3 + *TotalResponseSize) +
	                        sizeof(uint8_t));

	/* Flip the endianness of the container's size */
	*TotalResponseSize = SwapEndian_16(*TotalResponseSize);

	/* Fill in the response packet's header */
	ResponsePacket.SDPHeader.PDU             = SDP_PDU_SERVICESEARCHATTRIBUTERESPONSE;
	ResponsePacket.SDPHeader.TransactionID   = SDPHeader->TransactionID;
	ResponsePacket.SDPHeader.ParameterLength = SwapEndian_16(ParamLength);

	BT_SDP_DEBUG(1, ">> Service Search Attribute Response");
	BT_SDP_DEBUG(2, "-- Param Len 0x%04X", ParamLength);

	/* Send the completed response packet to the sender */
	Bluetooth_SendPacket(&ResponsePacket, (sizeof(ResponsePacket.SDPHeader) + ParamLength), Channel);
}

/** Adds all the Attributes in the given service table to the response that appear in the Attribute table.
 *
 *  \param[in]  AttributeTable   Pointer to an Attribute table for the service to examine
 *  \param[in]  AttributeList    Pointer to a list of Attribute ranges
 *  \param[in]  TotalAttributes  Number of Attributes stored in the Attribute list
 *  \param[out] BufferPos       Pointer to the output buffer position where the retrieved attributes are to be stored
 *
 *  \return Number of bytes added to the output buffer
 */
static uint16_t SDP_AddListedAttributesToResponse(const ServiceAttributeTable_t* AttributeTable,
                                                  uint16_t AttributeList[][2],
                                                  const uint8_t TotalAttributes,
                                                  void** const BufferPos)
{
	uint16_t TotalResponseSize;

	/* Add an inner Data Element Sequence header for the current services's found Attributes */
	uint16_t* AttributeListSize = SDP_AddSequence16(BufferPos);

	/* Search through the list of Attributes one at a time looking for values in the current UUID's Attribute table */
	for (uint8_t CurrAttribute = 0; CurrAttribute < TotalAttributes; CurrAttribute++)
	{
		uint16_t* AttributeIDRange = AttributeList[CurrAttribute];
		void*     AttributeValue;

		/* Look through the current service's attribute list, examining all the attributes */
		while ((AttributeValue = pgm_read_ptr(&AttributeTable->Data)) != NULL)
		{
			/* Get the current Attribute's ID from the current attribute table entry */
			uint16_t CurrAttributeID = pgm_read_word(&AttributeTable->AttributeID);

			/* Check if the current Attribute's ID is within the current Attribute range */
			if ((CurrAttributeID >= AttributeIDRange[0]) && (CurrAttributeID <= AttributeIDRange[1]))
			{
				/* Increment the current UUID's returned Attribute container size by the number of added bytes */
				*AttributeListSize += SDP_AddAttributeToResponse(CurrAttributeID, AttributeValue, BufferPos);
			}

			AttributeTable++;
		}
	}

	/* Record the total number of added bytes to the buffer */
	TotalResponseSize = 3 + *AttributeListSize;

	/* Fix endianness of the added attribute data element sequence */
	*AttributeListSize = SwapEndian_16(*AttributeListSize);

	return TotalResponseSize;
}

/** Adds the given attribute ID and value to the response buffer, and advances the response buffer pointer past the added data.
 *
 *  \param[in] AttributeID          Attribute ID to add to the response buffer
 *  \param[in] AttributeValue       Pointer to the start of the Attribute's value, located in PROGMEM
 *  \param[in, out] ResponseBuffer  Pointer to a buffer where the Attribute and Attribute Value is to be added
 *
 *  \return Number of bytes added to the response buffer
 */
static uint16_t SDP_AddAttributeToResponse(const uint16_t AttributeID,
                                           const void* AttributeValue,
                                           void** ResponseBuffer)
{
	/* Retrieve the size of the attribute value from its container header */
	uint8_t  AttributeHeaderLength;
	uint16_t AttributeValueLength = SDP_GetLocalAttributeContainerSize(AttributeValue, &AttributeHeaderLength);

	BT_SDP_DEBUG(2, " -- Add Attribute (0x%04X) 0x%04X", (AttributeHeaderLength + AttributeValueLength), AttributeID);

	/* Add a Data Element header to the response for the Attribute ID */
	SDP_WriteData8(ResponseBuffer, (SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_16Bit));

	/* Add the Attribute ID to the created Data Element */
	SDP_WriteData16(ResponseBuffer, AttributeID);

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
static void* SDP_GetAttributeValue(const ServiceAttributeTable_t* AttributeTable,
                                   const uint16_t AttributeID)
{
	void* CurrTableItemData;

	/* Search through the current Attribute table, abort when the terminator item has been reached */
	while ((CurrTableItemData = pgm_read_ptr(&AttributeTable->Data)) != NULL)
	{
		/* Check if the current Attribute ID matches the search ID - if so return a pointer to it */
		if (pgm_read_word(&AttributeTable->AttributeID) == AttributeID)
		  return CurrTableItemData;

		AttributeTable++;
	}

	return NULL;
}

/** Retrieves the Attribute table for the given UUID list if it exists.
 *
 *  \param[in] UUIDList            List of UUIDs which must be matched within the service attribute table
 *  \param[in] TotalUUIDs          Total number of UUIDs stored in the UUID list
 *  \param[in] CurrAttributeTable  Pointer to the service attribute table to search through
 *
 *  \return True if all the UUIDs given in the UUID list appear in the given attribute table, false otherwise
 */
static bool SDP_SearchServiceTable(uint8_t UUIDList[][UUID_SIZE_BYTES],
                                   const uint8_t TotalUUIDs,
			                       const ServiceAttributeTable_t* CurrAttributeTable)
{
	const void* CurrAttribute;
	uint16_t    UUIDMatchFlags = 0;

	/* Search through the current attribute table, checking each attribute value for UUID matches */
	while ((CurrAttribute = pgm_read_ptr(&CurrAttributeTable->Data)) != NULL)
	{
		SDP_CheckUUIDMatch(UUIDList, TotalUUIDs, &UUIDMatchFlags, CurrAttribute);
		CurrAttributeTable++;
	}

	/* Determine how many UUID matches in the list we have found */
	uint8_t UUIDMatches;
	for (UUIDMatches = 0; UUIDMatchFlags; UUIDMatches++)
	  UUIDMatchFlags &= (UUIDMatchFlags - 1);

	/* If all UUIDs have been matched to the current service, return true */
	return (UUIDMatches == TotalUUIDs);
}

/** Recursively unwraps the given locally stored attribute (in PROGMEM space), searching for UUIDs to match against
 *  the given UUID list. As matches are found, they are indicated in the UUIDMatch flag list.
 *
 *  \param[in]      UUIDList        List of UUIDs which must be matched within the service attribute table
 *  \param[in]      TotalUUIDs      Total number of UUIDs stored in the UUID list
 *  \param[in, out] UUIDMatchFlags  Array of flags indicating which UUIDs in the list have already been matched
 *  \param[in]      CurrAttribute   Pointer to the current attribute to search through
 *
 *  \return True if all the UUIDs given in the UUID list appear in the given attribute table, false otherwise
 */
static void SDP_CheckUUIDMatch(uint8_t UUIDList[][UUID_SIZE_BYTES],
                               const uint8_t TotalUUIDs,
                               uint16_t* const UUIDMatchFlags,
                               const void* CurrAttribute)
{
	uint8_t CurrAttributeType = (pgm_read_byte(CurrAttribute) & ~0x07);

	/* Check the data type of the current attribute value - if UUID, compare, if Sequence, unwrap and recurse */
	if (CurrAttributeType == SDP_DATATYPE_UUID)
	{
		uint16_t CurrUUIDMatchMask = (1 << 0);

		/* Look for matches in the UUID list against the current attribute UUID value */
		for (uint8_t i = 0; i < TotalUUIDs; i++)
		{
			/* Check if the current unmatched UUID is identical to the search UUID */
			if (!(*UUIDMatchFlags & CurrUUIDMatchMask) && !(memcmp_P(UUIDList[i], (CurrAttribute + 1), UUID_SIZE_BYTES)))
			{
				/* Indicate match found for the current attribute UUID and early-abort */
				*UUIDMatchFlags |= CurrUUIDMatchMask;
				break;
			}

			CurrUUIDMatchMask <<= 1;
		}
	}
	else if (CurrAttributeType == SDP_DATATYPE_Sequence)
	{
		uint8_t  SequenceHeaderSize;
		uint16_t SequenceSize = SDP_GetLocalAttributeContainerSize(CurrAttribute, &SequenceHeaderSize);

		CurrAttribute += SequenceHeaderSize;

		/* Recursively unwrap the sequence container, and re-search its contents for UUIDs */
		while (SequenceSize)
		{
			uint8_t  InnerHeaderSize;
			uint16_t InnerSize = SDP_GetLocalAttributeContainerSize(CurrAttribute, &InnerHeaderSize);

			/* Recursively search of the next element in the sequence, trying to match UUIDs with the UUID list */
			SDP_CheckUUIDMatch(UUIDList, TotalUUIDs, UUIDMatchFlags, CurrAttribute);

			/* Skip to the next element in the sequence */
			SequenceSize  -= InnerHeaderSize + InnerSize;
			CurrAttribute += InnerHeaderSize + InnerSize;
		}
	}
}

/** Reads in the collection of Attribute ranges from the input buffer's Data Element Sequence container, into the given
 *  Attribute list for later use. Once complete, the input buffer pointer is advanced to the end of the Attribute container.
 *
 *  \param[out] AttributeList     Pointer to a buffer where the list of Attribute ranges are to be stored
 *  \param[in]  CurrentParameter  Pointer to a Buffer containing a Data Element Sequence of Attribute and Attribute Range elements
 *
 *  \return Total number of Attribute ranges stored in the Data Element Sequence
 */
static uint8_t SDP_GetAttributeList(uint16_t AttributeList[][2],
                                    const void** const CurrentParameter)
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
static uint8_t SDP_GetUUIDList(uint8_t UUIDList[][UUID_SIZE_BYTES],
                               const void** const CurrentParameter)
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

		/* Copy over UUID from the container to the free slot */
		if (UUIDLength <= 4)
		{
			/* Copy over the base UUID value to the free UUID slot in the list */
			memcpy_P(CurrentUUID, &BaseUUID, sizeof(BaseUUID));

			/* Copy over short UUID */
			memcpy(CurrentUUID + (4 - UUIDLength), *CurrentParameter, UUIDLength);
		}
		else
		{
			/* Copy over full UUID */
			memcpy(CurrentUUID, *CurrentParameter, UUIDLength);
		}

		BT_SDP_DEBUG(2, "-- UUID (%d): %02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		                UUIDLength,
		                CurrentUUID[0], CurrentUUID[1], CurrentUUID[2], CurrentUUID[3],
		                CurrentUUID[4], CurrentUUID[5],
						CurrentUUID[6], CurrentUUID[7],
		                CurrentUUID[8], CurrentUUID[9],
						CurrentUUID[10], CurrentUUID[11], CurrentUUID[12],  CurrentUUID[13],  CurrentUUID[14],  CurrentUUID[15]);

		ServicePatternLength -= (UUIDLength + ElementHeaderSize);
		*CurrentParameter    += UUIDLength;
	}

	return TotalUUIDs;
}

/** Retrieves the total size of the given locally stored (in PROGMEM) attribute Data Element container.
 *
 *  \param[in]  AttributeData  Pointer to the start of the Attribute container, located in PROGMEM
 *  \param[out] HeaderSize     Pointer to a location where the header size of the data element is to be stored
 *
 *  \return Size in bytes of the entire attribute container, including the header
 */
static uint32_t SDP_GetLocalAttributeContainerSize(const void* const AttributeData,
                                                   uint8_t* const HeaderSize)
{
	/* Fetch the size of the Data Element structure from the header */
	uint8_t SizeIndex = (pgm_read_byte(AttributeData) & 0x07);

	uint32_t ElementValueSize;

	/* Convert the Data Element size index into a size in bytes */
	switch (SizeIndex)
	{
		case SDP_DATASIZE_Variable8Bit:
			*HeaderSize = (1 + sizeof(uint8_t));
			ElementValueSize = pgm_read_byte(AttributeData + 1);
			break;
		case SDP_DATASIZE_Variable16Bit:
			*HeaderSize = (1 + sizeof(uint16_t));
			ElementValueSize = SwapEndian_16(pgm_read_word(AttributeData + 1));
			break;
		case SDP_DATASIZE_Variable32Bit:
			*HeaderSize = (1 + sizeof(uint32_t));
			ElementValueSize = SwapEndian_32(pgm_read_dword(AttributeData + 1));
			break;
		default:
			*HeaderSize = 1;
			ElementValueSize = (1 << SizeIndex);
			break;
	}

	return ElementValueSize;
}

/** Retrieves the size of a Data Element container from the current input buffer, and advances the input buffer
 *  pointer to the start of the Data Element's contents.
 *
 *  \param[in, out] DataElementHeader  Pointer to the start of a Data Element header
 *  \param[out]     ElementHeaderSize  Size in bytes of the header that was skipped
 *
 *  \return Size in bytes of the Data Element container's contents, minus the header
 */
static uint32_t SDP_GetDataElementSize(const void** const DataElementHeader,
                                       uint8_t* const ElementHeaderSize)
{
	/* Fetch the size of the Data Element structure from the header, increment the current buffer pos */
	uint8_t  SizeIndex = (SDP_ReadData8(DataElementHeader) & 0x07);

	uint32_t ElementValueSize;

	/* Convert the Data Element size index into a size in bytes */
	switch (SizeIndex)
	{
		case SDP_DATASIZE_Variable8Bit:
			*ElementHeaderSize  = (1 + sizeof(uint8_t));
			ElementValueSize    = SDP_ReadData8(DataElementHeader);
			break;
		case SDP_DATASIZE_Variable16Bit:
			*ElementHeaderSize  = (1 + sizeof(uint16_t));
			ElementValueSize    = SDP_ReadData16(DataElementHeader);
			break;
		case SDP_DATASIZE_Variable32Bit:
			*ElementHeaderSize  = (1 + sizeof(uint32_t));
			ElementValueSize    = SDP_ReadData32(DataElementHeader);
			break;
		default:
			*ElementHeaderSize  = 1;
			ElementValueSize    = (1 << SizeIndex);
			break;
	}

	return ElementValueSize;
}

