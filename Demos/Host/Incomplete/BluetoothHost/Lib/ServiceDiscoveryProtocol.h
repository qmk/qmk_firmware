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
		
		#define SDP_ATTRIBUTE_NAME                      0x0000

		#define SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE    0x0000
		#define SDP_ATTRIBUTE_ID_SERVICECLASSIDS        0x0001
		#define SDP_ATTRIBUTE_ID_LANGIDOFFSET           0x0006
		#define SDP_ATTRIBUTE_ID_AVAILABILITY           0x0008
		#define SDP_ATTRIBUTE_IDO_DESCRIPTION           0x0001
		#define SDP_ATTRIBUTE_IDO_PROVIDER              0x0002
		
		/** Size of a full 128 bit UUID, in bytes */
		#define UUID_SIZE_BYTES                         16
		
		/** First 96 bits common to all standadized Bluetooth services */
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
		static inline uint16_t* ServiceDiscovery_AddDataElementHeader(uint8_t** BufferPos, const uint8_t Type)
		{
			**BufferPos = (6 | Type);	
			*BufferPos += 1;

			uint16_t* SizePos = (uint16_t*)*BufferPos;				
			*SizePos = 0;

			**BufferPos += 2;
			
			return SizePos;
		}

		static inline uint16_t ServiceDiscovery_Read16BitParameter(const void** AttributeHeader)
		{
			uint16_t ParamValue = *((uint16_t*)*AttributeHeader);
			*AttributeHeader += sizeof(uint16_t);
			return ParamValue;
		}
		
	/* Function Prototypes: */
		void ServiceDiscovery_ProcessPacket(void* Data, Bluetooth_Channel_t* Channel);

		#if defined(INCLUDE_FROM_SERVICEDISCOVERYPROTOCOL_C)
			static void ServiceDiscovery_ProcessServiceSearch(SDP_PDUHeader_t* SDPHeader, Bluetooth_Channel_t* Channel);
			static void ServiceDiscovery_ProcessServiceAttribute(SDP_PDUHeader_t* SDPHeader, Bluetooth_Channel_t* Channel);
			static void ServiceDiscovery_ProcessServiceSearchAttribute(SDP_PDUHeader_t* SDPHeader, Bluetooth_Channel_t* Channel);

			static void* ServiceDiscovery_GetAttributeValue(ServiceAttributeTable_t* AttributeTable, uint16_t AttributeID);
			static ServiceAttributeTable_t* ServiceDiscovery_GetAttributeTable(uint8_t* UUID);
			static uint8_t ServiceDiscovery_GetAttributeList(uint16_t AttributeList[][2], const void** CurrentParameter);
			static uint8_t ServiceDiscovery_GetUUIDList(uint8_t UUIDList[][UUID_SIZE_BYTES], const void** CurrentParameter);
			static uint32_t ServiceDiscovery_GetLocalAttributeSize(const void* AttributeData);
			static uint32_t ServiceDiscovery_GetDataElementSize(const void** AttributeHeader, uint8_t* ElementHeaderSize);
		#endif

#endif
