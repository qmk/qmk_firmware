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

#ifndef _SERVICEDISCOVERYPROTOCOL_H_
#define _SERVICEDISCOVERYPROTOCOL_H_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>
		#include <stdbool.h>
		#include <stdio.h>

		#include <LUFA/Common/Common.h>
		#include <LUFA/Drivers/Peripheral/SerialStream.h>

		#include "BluetoothStack.h"
		
	/* Macros: */
		#define BT_SDP_DEBUG(l, s, ...)                 do { if (SDP_DEBUG_LEVEL >= l) printf_P(PSTR("(SDP) " s "\r\n"), ##__VA_ARGS__); } while (0)
		#define SDP_DEBUG_LEVEL                         2
		
		#define SDP_PDU_ERRORRESPONSE                   0x01
		#define SDP_PDU_SERVICESEARCHREQUEST            0x02
		#define SDP_PDU_SERVICESEARCHRESPONSE           0x03
		#define SDP_PDU_SERVICEATTRIBUTEREQUEST         0x04
		#define SDP_PDU_SERVICEATTRIBUTERESPONSE        0x05
		#define SDP_PDU_SERVICESEARCHATTRIBUTEREQUEST   0x06
		#define SDP_PDU_SERVICESEARCHATTRIBUTERESPONSE  0x07

		#define SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE    0x0000
		#define SDP_ATTRIBUTE_ID_SERVICECLASSIDS        0x0001
		#define SDP_ATTRIBUTE_ID_LANGIDOFFSET           0x0006
		#define SDP_ATTRIBUTE_ID_AVAILABILITY           0x0008
		#define SDP_ATTRIBUTE_ID_VERSION                0x0200
		#define SDP_ATTRIBUTE_ID_SERVICENAME            0x0100
		#define SDP_ATTRIBUTE_ID_SERVICEDESCRIPTION     0x0101
		
		#define SWAPENDIAN_16(x)                        ((((x) & 0xFF00) >> 8) | (((x) & 0x00FF) << 8))
		#define SWAPENDIAN_32(x)                        (SWAPENDIAN_16(((x) & 0xFFFF0000) >> 16) | SWAPENDIAN_16(((x) & 0x0000FFFF) << 16))
		
		/** Size of a full 128 bit UUID, in bytes. */
		#define UUID_SIZE_BYTES                         16
		
		/** First 96 bits common to all standadized Bluetooth services. */
		#define BASE_96BIT_UUID                         0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00
		
		/** Terminator for a service attribute table of type \ref ServiceAttributeTable_t. */
		#define SERVICE_ATTRIBUTE_TABLE_TERMINATOR      {.Data = NULL}
		
	/* Enums: */
		/** Data sizes for SDP Data Element headers, to indicate the size of the data contained in the element. When creating
		 *  a Data Element, a value from this enum should be ORed with a value from the \ref ServiceDiscovery_DataTypes_t enum.
		 */
		enum ServiceDiscovery_DataSizes_t
		{
			SDP_DATASIZE_8Bit          = 0, /**< Contained data is 8 bits in length. */
			SDP_DATASIZE_16Bit         = 1, /**< Contained data is 16 bits in length. */
			SDP_DATASIZE_32Bit         = 2, /**< Contained data is 32 bits in length. */
			SDP_DATASIZE_64Bit         = 3, /**< Contained data is 64 bits in length. */
			SDP_DATASIZE_128Bit        = 4, /**< Contained data is 128 bits in length. */
			SDP_DATASIZE_Variable8Bit  = 5, /**< Contained data is encoded in an 8 bit size integer following the header. */
			SDP_DATASIZE_Variable16Bit = 6, /**< Contained data is encoded in an 16 bit size integer following the header. */
			SDP_DATASIZE_Variable32Bit = 7, /**< Contained data is encoded in an 32 bit size integer following the header. */
		};

		/** Data types for SDP Data Element headers, to indicate the type of data contained in the element. When creating
		 *  a Data Element, a value from this enum should be ORed with a value from the \ref ServiceDiscovery_DataSizes_t enum.
		 */
		enum ServiceDiscovery_DataTypes_t
		{
			SDP_DATATYPE_Nill        = (0 << 3), /**< Indicates the container data is a Nill (null) type. */
			SDP_DATATYPE_UnsignedInt = (1 << 3), /**< Indicates the container data is an unsigned integer. */
			SDP_DATATYPE_SignedInt   = (2 << 3), /**< Indicates the container data is a signed integer. */
			SDP_DATATYPE_UUID        = (3 << 3), /**< Indicates the container data is a UUID. */
			SDP_DATATYPE_String      = (4 << 3), /**< Indicates the container data is an ASCII string. */
			SDP_DATATYPE_Boolean     = (5 << 3), /**< Indicates the container data is a logical boolean. */
			SDP_DATATYPE_Sequence    = (6 << 3), /**< Indicates the container data is a sequence of containers. */
			SDP_DATATYPE_Alternative = (7 << 3), /**< Indicates the container data is a sequence of alternative containers. */
			SDP_DATATYPE_URL         = (8 << 3), /**< Indicates the container data is a URL. */
		};

	/* Type Defines: */
		/** Header for all SPD transaction packets. This header is sent at the start of all SDP packets sent to or from a SDP
		 *  server.
		 */
		typedef struct
		{
			uint8_t  PDU; /**< SDP packet type, a SDP_PDU_* mask value */
			uint16_t TransactionID; /**< Unique transaction ID number to associate requests and responses */
			uint16_t ParameterLength; /**< Length of the data following the SDP header */
		} SDP_PDUHeader_t;
		
		/** Structure for the association of attribute ID values to an attribute value in FLASH. A table of these
		 *  structures can then be built up for each supported UUID service within the device.
		 */
		typedef struct
		{
			uint16_t    AttributeID; /**< Attribute ID of the table element which the UUID service supports */
			const void* Data; /**< Pointer to the attribute data, located in PROGMEM memory space */
		} ServiceAttributeTable_t;

		/** Structure for the association of service UUID values to attribute tables stored in FLASH. A table of these
		 *  structures can then be built up for each supported UUID service within the device.
		 */
		typedef struct
		{
			uint8_t     UUID[UUID_SIZE_BYTES]; /**< UUID of a service supported by the device */
			const void* AttributeTable; /**< Pointer to the UUID's attribute table, located in PROGMEM memory space */
		} ServiceTable_t;

		/** Structure for a list of Data Elements containing UUIDs, for service attributes requiring UUID lists. */
		typedef struct
		{
			uint8_t Header; /**< Data Element header, should be (SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit) */
			uint8_t UUID[UUID_SIZE_BYTES]; /**< UUID to store in the list Data Element */
		} ClassUUID_t;

		/** Structure for a list of Data Elements containing 8-bit integers, for service attributes requiring such lists. */
		typedef struct
		{
			uint8_t  Header; /**< Data Element header, should be (SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_8Bit) */
			uint8_t Value; /**< Value to store in the list Data Element */
		} Item8Bit_t;

		/** Structure for a list of Data Elements containing 16-bit integers, for service attributes requiring such lists. */
		typedef struct
		{
			uint8_t  Header; /**< Data Element header, should be (SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_16Bit) */
			uint16_t Value; /**< Value to store in the list Data Element */
		} Item16Bit_t;

		/** Structure for a list of Data Elements containing 32-bit integers, for service attributes requiring such lists. */
		typedef struct
		{
			uint8_t  Header; /**< Data Element header, should be (SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_32Bit) */
			uint32_t Value; /**< Value to store in the list Data Element */
		} Item32Bit_t;
		
	/* Inline Functions: */
		/** Adds a new Data Element container of the given type with a 16-bit size header to the buffer. The
		 *  buffer pointer's position is advanced past the added header once the element has been added. The
		 *  returned size header value is pre-zeroed out so that it can be incremented as data is placed into
		 *  the Data Element container.
		 *
		 *  The total added size of the container header is three bytes, regardless of the size of its contents
		 *  as long as the contents' size in bytes fits into a 16-bit integer.
		 *
		 *  \param[in, out] BufferPos  Pointer to a buffer where the container header is to be placed
		 *  \param[in]      Type       Type of data the container is to store, a value from the \ref ServiceDiscovery_DataTypes_t enum
		 *
		 *  \return Pointer to the 16-bit size value of the contaner header, which has been pre-zeroed
		 */
		static inline uint16_t* SDP_AddDataElementHeader16(void** BufferPos, const uint8_t Type)
		{
			*((uint8_t*)*BufferPos) = (SDP_DATASIZE_Variable16Bit | Type);
			*BufferPos += sizeof(uint8_t);

			uint16_t* SizePos = (uint16_t*)*BufferPos;
			*BufferPos += sizeof(uint16_t);

			*SizePos = 0;
			return SizePos;
		}
		
	/* Function Prototypes: */
		void SDP_ProcessPacket(void* Data, Bluetooth_Channel_t* Channel);

		#if defined(INCLUDE_FROM_SERVICEDISCOVERYPROTOCOL_C)
			static void SDP_ProcessServiceSearch(const SDP_PDUHeader_t* const SDPHeader, Bluetooth_Channel_t* const Channel);
			static void SDP_ProcessServiceAttribute(const SDP_PDUHeader_t* const SDPHeader, Bluetooth_Channel_t* const Channel);
			static void SDP_ProcessServiceSearchAttribute(const SDP_PDUHeader_t* const SDPHeader, Bluetooth_Channel_t* const Channel);

			static uint16_t SDP_AddAttributeToResponse(const uint16_t AttributeID, const void* AttributeValue, void** ResponseBuffer);
			static void*    SDP_GetAttributeValue(const ServiceAttributeTable_t* AttributeTable, const uint16_t AttributeID);
			static ServiceAttributeTable_t* SDP_GetAttributeTable(const uint8_t* const UUID);
			static uint8_t  SDP_GetAttributeList(uint16_t AttributeList[][2], const void** const CurrentParameter);
			static uint8_t  SDP_GetUUIDList(uint8_t UUIDList[][UUID_SIZE_BYTES], const void** const CurrentParameter);
			static uint32_t SDP_GetLocalAttributeContainerSize(const void* const AttributeData, uint8_t* const HeaderSize);
			static uint32_t SDP_GetDataElementSize(const void** const AttributeHeader, uint8_t* const ElementHeaderSize);
		#endif

#endif
