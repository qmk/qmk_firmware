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

#include "SDPServices.h"

const struct
{
	uint8_t  Header;
	uint32_t Data;
} PROGMEM SDP_Attribute_ServiceHandle =
	{
		(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_32Bit),
		SWAPENDIAN_32(0x00010000),
	};

const struct
{
	uint8_t    Header;
	uint16_t   Size;
	ItemUUID_t UUIDList[];
} PROGMEM SDP_Attribute_ServiceClassIDs =
	{
		(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable16Bit),
		SWAPENDIAN_16(sizeof(ItemUUID_t) * 1),
		{
			{(SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit), {BASE_80BIT_UUID, {0x00, 0x00, 0x00, 0x00, 0x10, 0x00}}}
		}
	};

const struct
{
	uint8_t        Header;
	uint16_t       Size;
	ItemProtocol_t ProtocolList[];
} PROGMEM SDP_Attribute_ProtocolDescriptor =
	{
		(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable16Bit),
		SWAPENDIAN_16(sizeof(ItemProtocol_t) * 1),
		{
			{
				(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
				sizeof(UUID_t),
				{(SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit), {BASE_80BIT_UUID, {0x00, 0x00, 0x00, 0x00, 0x01, 0x00}}},
			}
		}
	};

const struct
{
	uint8_t     Header;
	uint8_t     Size;
	Item16Bit_t VersionList[];
} PROGMEM SDP_Attribute_Version =
	{
		(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
		(sizeof(Item16Bit_t) * 1),
		{
			{(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_16Bit), SWAPENDIAN_16(0x0100)}
		}
	};

const struct
{
	uint8_t Header;
	uint8_t Size;
	char    Text[];
} PROGMEM SDP_Attribute_ServiceName =
	{
		(SDP_DATATYPE_String | SDP_DATASIZE_Variable8Bit),
		(sizeof("SDP") - 1),
		"SDP",
	};

const struct
{
	uint8_t Header;
	uint8_t Size;
	char    Text[];
} PROGMEM SDP_Attribute_ServiceDescription =
	{
		(SDP_DATATYPE_String | SDP_DATASIZE_Variable8Bit),
		(sizeof("Service Discovery Protocol Server") - 1),
		"Service Discovery Protocol Server",
	};

/** Service Discovery Protocol attribute table, listing all supported attributes of the service. */
const ServiceAttributeTable_t SDP_Attribute_Table[] PROGMEM =
	{
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE,    .Data = &SDP_Attribute_ServiceHandle      },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICECLASSIDS,        .Data = &SDP_Attribute_ServiceClassIDs    },
//		{.AttributeID = SDP_ATTRIBUTE_ID_PROTOCOLDESCRIPTORLIST, .Data = &SDP_Attribute_ProtocolDescriptor },
		{.AttributeID = SDP_ATTRIBUTE_ID_VERSION,                .Data = &SDP_Attribute_Version            },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICENAME,            .Data = &SDP_Attribute_ServiceName        },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICEDESCRIPTION,     .Data = &SDP_Attribute_ServiceDescription },

		SERVICE_ATTRIBUTE_TABLE_TERMINATOR
	};

const struct
{
	uint8_t  Header;
	uint32_t Data;
} PROGMEM RFCOMM_Attribute_ServiceHandle =
	{
		(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_32Bit),
		SWAPENDIAN_32(0x00010001),
	};

const struct
{
	uint8_t    Header;
	uint16_t   Size;
	ItemUUID_t UUIDList[];
} PROGMEM RFCOMM_Attribute_ServiceClassIDs =
	{
		(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable16Bit),
		SWAPENDIAN_16(sizeof(ItemUUID_t) * 1),
		{
			{(SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit), {BASE_80BIT_UUID, {0x00, 0x00, 0x00, 0x00, 0x11, 0x01}}}
		}
	};

const struct
{
	uint8_t     Header;
	uint8_t     Size;
	Item16Bit_t OffsetList[];
} PROGMEM RFCOMM_Attribute_LangOffset =
	{
		(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
		(sizeof(Item16Bit_t) * 1),
		{
			{(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_16Bit), SWAPENDIAN_16(0x0100)}
		}
	};

const struct
{
	uint8_t Header;
	uint8_t Size;
	char    Text[];
} PROGMEM RFCOMM_Attribute_ServiceName =
	{
		(SDP_DATATYPE_String | SDP_DATASIZE_Variable8Bit),
		sizeof("Serial Port") - 1,
		"Serial Port",
	};

const struct
{
	uint8_t Header;
	uint8_t Size;
	char    Text[];
} PROGMEM RFCOMM_Attribute_ServiceDescription =
	{
		(SDP_DATATYPE_String | SDP_DATASIZE_Variable8Bit),
		sizeof("Wireless Serial Port Service") - 1,
		"Wireless Serial Port Service",
	};

const ServiceAttributeTable_t RFCOMM_Attribute_Table[] PROGMEM =
	{
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE,    .Data = &RFCOMM_Attribute_ServiceHandle      },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICECLASSIDS,        .Data = &RFCOMM_Attribute_ServiceClassIDs    },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICENAME,            .Data = &RFCOMM_Attribute_ServiceName        },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICEDESCRIPTION,     .Data = &RFCOMM_Attribute_ServiceDescription },

		SERVICE_ATTRIBUTE_TABLE_TERMINATOR
	};
