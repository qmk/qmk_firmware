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
		#define SDP_ATTRIBUTE_DESCRIPTION               0x0001
		#define SDP_ATTRIBUTE_PROVIDER                  0x0002
		#define SDP_ATTRIBUTE_AVAILABILITY              0x0008
		
		#define SDP_DATATYPE_NIL                        (0x00 << 3)
		#define SDP_DATATYPE_UNSIGNED_INT               (0x01 << 3)
		#define SDP_DATATYPE_SIGNED_INT                 (0x02 << 3)
		#define SDP_DATATYPE_UUID                       (0x03 << 3)
		#define SDP_DATATYPE_TEXT                       (0x04 << 3)
		#define SDP_DATATYPE_BOOLEAN                    (0x05 << 3)
		#define SDP_DATATYPE_ELEMENT_SEQUENCE           (0x06 << 3)
		#define SDP_DATATYPE_ELEMENT_ALTERNATIVE        (0x07 << 3)
		#define SDP_DATATYPE_URL                        (0x08 << 3)
		
		#define UUID_SIZE_BYTES                         16
		#define BASE_96BIT_UUID                         0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00
		
		#define SERVICE_ATTRIBUTE_TEXT(name, string)    SERVICE_ATTRIBUTE_LEN8(name, SDP_DATATYPE_TEXT, sizeof(string), string)
		#define SERVICE_ATTRIBUTE_LEN8(name, type, size, ...)  const ServiceAttributeData8Bit_t  name PROGMEM = \
		                                                {.Header = (type | 5), .Size = size, .Data = __VA_ARGS__}
		#define SERVICE_ATTRIBUTE_LEN16(name, type, size, ...) const ServiceAttributeData16Bit_t name PROGMEM = \
		                                                {.Header = (type | 6), .Size = size, .Data = __VA_ARGS__}
		#define SERVICE_ATTRIBUTE_LEN32(name, type, size, ...) const ServiceAttributeData32Bit_t name PROGMEM = \
		                                                {.Header = (type | 7), .Size = size, .Data = __VA_ARGS__}
		#define SERVICE_ATTRIBUTE_TABLE_TERMINATOR      {.Data = NULL}

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
			uint32_t Size;
			uint8_t  Data[];
		} ServiceAttributeData32Bit_t;

		typedef struct
		{
			uint8_t  Header;
			uint16_t Size;
			uint8_t  Data[];
		} ServiceAttributeData16Bit_t;

		typedef struct
		{
			uint8_t Header;
			uint8_t Size;
			uint8_t Data[];
		} ServiceAttributeData8Bit_t;

		typedef struct
		{
			uint8_t Header;
			uint8_t Data[];
		} ServiceAttributeData_t;
		
	/* Function Prototypes: */
		void ServiceDiscovery_ProcessPacket(void* Data, Bluetooth_Channel_t* Channel);

		#if defined(INCLUDE_FROM_SERVICEDISCOVERYPROTOCOL_C)
			static void ServiceDiscovery_ProcessServiceSearch(SDP_PDUHeader_t* SDPHeader, Bluetooth_Channel_t* Channel);
			static void ServiceDiscovery_ProcessServiceAttribute(SDP_PDUHeader_t* SDPHeader, Bluetooth_Channel_t* Channel);
			static void ServiceDiscovery_ProcessServiceSearchAttribute(SDP_PDUHeader_t* SDPHeader, Bluetooth_Channel_t* Channel);
			
			static inline uint16_t ServiceDiscovery_Read16BitParameter(const void** AttributeHeader)
			{
				uint16_t ParamValue = *((uint16_t*)*AttributeHeader);
				*AttributeHeader += sizeof(uint16_t);
				return ParamValue;
			}

			static uint8_t ServiceDiscovery_ProcessAttributes(uint8_t UUIDList[][UUID_SIZE_BYTES], const uint8_t TotalUUIDs, 
			                                                  uint8_t* ResponseBuffer, uint8_t MaxResponseSize,
			                                                  const void** CurrentParameter);
			static uint8_t ServiceDiscovery_GetAttribute(uint8_t UUIDList[][UUID_SIZE_BYTES], const uint8_t TotalUUIDs,
			                                             const uint32_t Attribute, uint8_t** DataBuffer, uint8_t BufferLen);
			static uint8_t ServiceDiscovery_GetUUIDList(uint8_t UUIDList[][UUID_SIZE_BYTES], const void** CurrentParameter);
			static uint32_t ServiceDiscovery_GetDataElementSize(const void** AttributeHeader, uint8_t* ElementHeaderSize);
		#endif

#endif
