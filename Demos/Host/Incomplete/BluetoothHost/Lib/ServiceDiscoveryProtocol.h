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
		#define SDP_ATTRIBUTE_ID_NAME                  (0x0000 + SDP_ATTRIBUTE_LANGOFFSET)
		#define SDP_ATTRIBUTE_ID_DESCRIPTION           (0x0001 + SDP_ATTRIBUTE_LANGOFFSET)
		
		/** Attribute ID offset for localised language string attributes. */
		#define SDP_ATTRIBUTE_LANGOFFSET                0x0100

		/** Size of a full 128 bit UUID, in bytes. */
		#define UUID_SIZE_BYTES                         16
		
		/** First 96 bits common to all standadized Bluetooth services. */
		#define BASE_96BIT_UUID                         0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00
		
		/** Terminator for a service attribute table of type \ref ServiceAttributeTable_t. */
		#define SERVICE_ATTRIBUTE_TABLE_TERMINATOR      {.Data = NULL}
		
	/* Enums: */
		enum ServiceDiscovery_DataTypes_t
		{
			SDP_DATATYPE_Nill        = (0 << 3),
			SDP_DATATYPE_UnsignedInt = (1 << 3),
			SDP_DATATYPE_SignedInt   = (2 << 3),
			SDP_DATATYPE_UUID        = (3 << 3),
			SDP_DATATYPE_String      = (4 << 3),
			SDP_DATATYPE_Boolean     = (5 << 3),
			SDP_DATATYPE_Sequence    = (6 << 3),
			SDP_DATATYPE_Alternative = (7 << 3),
			SDP_DATATYPE_URL         = (8 << 3),
		};

	/* Type Defines: */
		typedef struct
		{
			uint8_t  PDU;
			uint16_t TransactionID;
			uint16_t ParameterLength;
		} SDP_PDUHeader_t;
		
		typedef struct
		{
			uint16_t    AttributeID;
			const void* Data;
		} ServiceAttributeTable_t;

		typedef struct
		{
			uint8_t UUID[16];
			const void* AttributeTable;
		} ServiceTable_t;

		typedef struct
		{
			uint8_t  Header;
			uint8_t  Size;
			uint16_t UUID[UUID_SIZE_BYTES];
		} ClassUUID_t;

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
		static inline uint16_t* SDP_AddDataElementHeader16(uint8_t** BufferPos, const uint8_t Type)
		{
			**BufferPos = (6 | Type);	

			uint16_t* SizePos = (uint16_t*)*(BufferPos + 1);
			*SizePos = 0;

			*BufferPos += 3;			
			return SizePos;
		}
		
	/* Function Prototypes: */
		void SDP_ProcessPacket(void* Data, Bluetooth_Channel_t* Channel);

		#if defined(INCLUDE_FROM_SERVICEDISCOVERYPROTOCOL_C)
			static void SDP_ProcessServiceSearch(const SDP_PDUHeader_t* const SDPHeader, Bluetooth_Channel_t* const Channel);
			static void SDP_ProcessServiceAttribute(const SDP_PDUHeader_t* const SDPHeader, Bluetooth_Channel_t* const Channel);
			static void SDP_ProcessServiceSearchAttribute(const SDP_PDUHeader_t* const SDPHeader, Bluetooth_Channel_t* const Channel);

			static void* SDP_GetAttributeValue(const ServiceAttributeTable_t* AttributeTable, const uint16_t AttributeID);
			static ServiceAttributeTable_t* SDP_GetAttributeTable(const uint8_t* const UUID);
			static uint8_t SDP_GetAttributeList(uint16_t AttributeList[][2], const void** const CurrentParameter);
			static uint8_t SDP_GetUUIDList(uint8_t UUIDList[][UUID_SIZE_BYTES], const void** const CurrentParameter);
			static uint32_t SDP_GetLocalAttributeContainerSize(const void* const AttributeData);
			static uint32_t SDP_GetDataElementSize(const void** const AttributeHeader, uint8_t* const ElementHeaderSize);
		#endif

#endif
