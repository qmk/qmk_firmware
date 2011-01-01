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
 *  SDP Service Attribute definitions. This file contains the attributes
 *  and attribute tables of all the services the device supports, which can
 *  then be retrieved by a connected Bluetooth device via the SDP server.
 */

#include "SDPServices.h"

/** Serial Port Profile attribute, listing the unique service handle of the Serial Port service
 *  within the device. This handle can then be requested by the SDP client in future transactions
 *  in lieu of a search UUID list.
 */
const struct
{
	uint8_t  Header;
	uint32_t Data;
} PROGMEM SerialPort_Attribute_ServiceHandle =
	{
		(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_32Bit),
		SWAPENDIAN_32(0x00010001),
	};

/** Serial Port Profile attribute, listing the implemented Service Class UUIDs of the Serial Port service
 *  within the device. This list indicates all the class UUIDs that apply to the Serial Port service, so that
 *  a SDP client can search by a generalized class rather than a specific UUID to determine supported services.
 */
const struct
{
	uint8_t    Header;
	uint8_t    Size;
	ItemUUID_t UUIDList[];
} PROGMEM SerialPort_Attribute_ServiceClassIDs =
	{
		(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
		(sizeof(ItemUUID_t) * 1),
		{
			{(SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit), SP_CLASS_UUID},
		},
	};

/** Serial Port Profile attribute, listing the Protocols (and their attributes) of the Serial Port service
 *  within the device. This list indicates what protocols the service is layered on top of, as well as any
 *  configuration information for each layer.
 */
const struct
{
	uint8_t                  Header;
	uint8_t                  Size;

	ItemProtocol_t           L2CAP;
	ItemProtocol_8BitParam_t RFCOMM;
} PROGMEM SerialPort_Attribute_ProtocolDescriptor =
	{
		(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
		(sizeof(ItemProtocol_t) + sizeof(ItemProtocol_8BitParam_t)),
		{
			(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
			sizeof(ItemUUID_t),
			{
				{(SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit), L2CAP_UUID},
			},
		},
		{
			(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
			(sizeof(ItemUUID_t) + sizeof(Item8Bit_t)),
			{
				{(SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit), RFCOMM_UUID},
				{(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_8Bit), 0x03},
			},
		},
	};

/** Serial Port Profile attribute, listing the Browse Group List UUIDs which this service is a member of.
 *  Browse Group UUIDs give a way to group together services within a device in a simple hierarchy, so that
 *  a SDP client can progressively narrow down an general browse to a specific service which it requires.
 */
const struct
{
	uint8_t    Header;
	uint8_t    Size;
	ItemUUID_t UUIDList[];
} PROGMEM SerialPort_Attribute_BrowseGroupList =
	{
		(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
		(sizeof(ItemUUID_t) * 1),
		{
			{(SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit), PUBLICBROWSEGROUP_CLASS_UUID},
		},
	};

/** Serial Port Profile attribute, listing the languages (and their encodings) supported
 *  by the Serial Port service in its text string attributes.
 */
const struct
{
	uint8_t            Header;
	uint8_t            Size;
	ItemLangEncoding_t LanguageEncodings[];
} PROGMEM SerialPort_Attribute_LanguageBaseIDOffset =
	{
		(SDP_DATATYPE_Sequence | SDP_DATASIZE_Variable8Bit),
		(sizeof(ItemLangEncoding_t) * 1),
		{
			{
				{(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_16Bit), SWAPENDIAN_16(0x454E)},
				{(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_16Bit), SWAPENDIAN_16(0x006A)},
				{(SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_16Bit), SWAPENDIAN_16(0x0100)},
			},
		},
	};

/** Serial Port Profile attribute, listing a human readable name of the service. */
const struct
{
	uint8_t Header;
	uint8_t Size;
	char    Text[];
} PROGMEM SerialPort_Attribute_ServiceName =
	{
		(SDP_DATATYPE_String | SDP_DATASIZE_Variable8Bit),
		sizeof("Wireless Serial Port") - 1,
		"Wireless Serial Port",
	};

/** Serial Port Profile attribute, listing a human readable description of the service. */
const struct
{
	uint8_t Header;
	uint8_t Size;
	char    Text[];
} PROGMEM SerialPort_Attribute_ServiceDescription =
	{
		(SDP_DATATYPE_String | SDP_DATASIZE_Variable8Bit),
		sizeof("Wireless Serial Port Service") - 1,
		"Wireless Serial Port Service",
	};

/** Service Attribute Table for the Serial Port service, linking each supported attribute ID to its data, so that
 *  the SDP server can retrieve it for transmission back to a SDP client upon request.
 */
const ServiceAttributeTable_t PROGMEM SerialPort_Attribute_Table[] =
	{
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE,    .Data = &SerialPort_Attribute_ServiceHandle       },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICECLASSIDS,        .Data = &SerialPort_Attribute_ServiceClassIDs     },
		{.AttributeID = SDP_ATTRIBUTE_ID_PROTOCOLDESCRIPTORLIST, .Data = &SerialPort_Attribute_ProtocolDescriptor  },
		{.AttributeID = SDP_ATTRIBUTE_ID_BROWSEGROUPLIST,        .Data = &SerialPort_Attribute_BrowseGroupList     },
		{.AttributeID = SDP_ATTRIBUTE_ID_LANGUAGEBASEATTROFFSET, .Data = &SerialPort_Attribute_LanguageBaseIDOffset},
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICENAME,            .Data = &SerialPort_Attribute_ServiceName         },
		{.AttributeID = SDP_ATTRIBUTE_ID_SERVICEDESCRIPTION,     .Data = &SerialPort_Attribute_ServiceDescription  },

		SERVICE_ATTRIBUTE_TABLE_TERMINATOR
	};

