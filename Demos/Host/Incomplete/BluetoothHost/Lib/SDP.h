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
 *  Header file for ServiceDiscoveryProtocol.c.
 */

#ifndef _SERVICEDISCOVERYPROTOCOL_H_
#define _SERVICEDISCOVERYPROTOCOL_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>
		#include <string.h>
		#include <stdbool.h>
		#include <stdio.h>

		#include <LUFA/Common/Common.h>
		#include <LUFA/Drivers/Peripheral/Serial.h>

		#include "BluetoothStack.h"
		#include "SDPServices.h"

	/* Macros: */
		#define BT_SDP_DEBUG(l, s, ...)                 do { if (SDP_DEBUG_LEVEL >= l) printf_P(PSTR("(SDP) " s "\r\n"), ##__VA_ARGS__); } while (0)
		#define SDP_DEBUG_LEVEL                         0

		#define SDP_PDU_ERRORRESPONSE                   0x01
		#define SDP_PDU_SERVICESEARCHREQUEST            0x02
		#define SDP_PDU_SERVICESEARCHRESPONSE           0x03
		#define SDP_PDU_SERVICEATTRIBUTEREQUEST         0x04
		#define SDP_PDU_SERVICEATTRIBUTERESPONSE        0x05
		#define SDP_PDU_SERVICESEARCHATTRIBUTEREQUEST   0x06
		#define SDP_PDU_SERVICESEARCHATTRIBUTERESPONSE  0x07

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

	/* Inline Functions: */
		/** Writes 8 bits of raw data to the given buffer, incrementing the buffer position afterwards.
		 *
		 *  \param[in, out] BufferPos  Current position in the buffer where the data is to be written to
		 *  \param[in]      Data       Data to write to the buffer
		 */
		static inline void SDP_WriteData8(void** BufferPos,
		                                  const uint8_t Data)
		{
			*((uint8_t*)*BufferPos) = Data;
			*BufferPos += sizeof(uint8_t);
		}

		/** Writes 16 bits of raw data to the given buffer, incrementing the buffer position afterwards.
		 *
		 *  \param[in, out] BufferPos  Current position in the buffer where the data is to be written to
		 *  \param[in]      Data       Data to write to the buffer
		 */
		static inline void SDP_WriteData16(void** BufferPos,
		                                   const uint16_t Data)
		{
			*((uint16_t*)*BufferPos) = SwapEndian_16(Data);
			*BufferPos += sizeof(uint16_t);
		}

		/** Writes 32 bits of raw data to the given buffer, incrementing the buffer position afterwards.
		 *
		 *  \param[in, out] BufferPos  Current position in the buffer where the data is to be written to
		 *  \param[in]      Data       Data to write to the buffer
		 */
		static inline void SDP_WriteData32(void** BufferPos,
		                                   const uint32_t Data)
		{
			*((uint32_t*)*BufferPos) = SwapEndian_32(Data);
			*BufferPos += sizeof(uint32_t);
		}

		/** Reads 8 bits of raw data from the given buffer, incrementing the buffer position afterwards.
		 *
		 *  \param[in, out] BufferPos  Current position in the buffer where the data is to be read from
		 *
		 *  \return Data read from the buffer
		 */
		static inline uint8_t SDP_ReadData8(const void** BufferPos)
		{
			uint8_t Data = *((const uint8_t*)*BufferPos);
			*BufferPos += sizeof(uint8_t);

			return Data;
		}

		/** Reads 16 bits of raw data from the given buffer, incrementing the buffer position afterwards.
		 *
		 *  \param[in, out] BufferPos  Current position in the buffer where the data is to be read from
		 *
		 *  \return Data read from the buffer
		 */
		static inline uint16_t SDP_ReadData16(const void** BufferPos)
		{
			uint16_t Data = SwapEndian_16(*((const uint16_t*)*BufferPos));
			*BufferPos += sizeof(uint16_t);

			return Data;
		}

		/** Reads 32 bits of raw data from the given buffer, incrementing the buffer position afterwards.
		 *
		 *  \param[in, out] BufferPos  Current position in the buffer where the data is to be read from
		 *
		 *  \return Data read from the buffer
		 */
		static inline uint32_t SDP_ReadData32(const void** BufferPos)
		{
			uint32_t Data = SwapEndian_32(*((const uint32_t*)*BufferPos));
			*BufferPos += sizeof(uint32_t);

			return Data;
		}

		/** Adds a new Data Element Sequence container with a 16-bit size header to the buffer. The buffer
		 *  pointer's position is advanced past the added header once the element has been added. The returned
		 *  size header value is pre-zeroed out so that it can be incremented as data is placed into the Data
		 *  Element Sequence container.
		 *
		 *  The total added size of the container header is three bytes, regardless of the size of its contents
		 *  as long as the contents' size in bytes fits into a 16-bit integer.
		 *
		 *  \param[in, out] BufferPos  Pointer to a buffer where the container header is to be placed
		 *
		 *  \return Pointer to the 16-bit size value of the container header, which has been pre-zeroed
		 */
		static inline uint16_t* SDP_AddSequence16(void** BufferPos)
		{
			SDP_WriteData8(BufferPos, (SDP_DATASIZE_Variable16Bit | SDP_DATATYPE_Sequence));

			uint16_t* SizePos = *BufferPos;
			SDP_WriteData16(BufferPos, 0);

			return SizePos;
		}

	/* Function Prototypes: */
		void SDP_ProcessPacket(void* Data,
		                       Bluetooth_Channel_t* const Channel);

		#if defined(INCLUDE_FROM_SERVICEDISCOVERYPROTOCOL_C)
			static void     SDP_ProcessServiceSearch(const SDP_PDUHeader_t* const SDPHeader,
			                                         Bluetooth_Channel_t* const Channel);
			static void     SDP_ProcessServiceAttribute(const SDP_PDUHeader_t* const SDPHeader,
			                                            Bluetooth_Channel_t* const Channel);
			static void     SDP_ProcessServiceSearchAttribute(const SDP_PDUHeader_t* const SDPHeader,
			                                                  Bluetooth_Channel_t* const Channel);

			static uint16_t SDP_AddListedAttributesToResponse(const ServiceAttributeTable_t* AttributeTable,
			                                                  uint16_t AttributeList[][2],
			                                                  const uint8_t TotalAttributes,
			                                                  void** const BufferPos);
			static uint16_t SDP_AddAttributeToResponse(const uint16_t AttributeID,
			                                           const void* AttributeValue,
			                                           void** ResponseBuffer);
			static void*    SDP_GetAttributeValue(const ServiceAttributeTable_t* AttributeTable,
			                                      const uint16_t AttributeID);

			static bool     SDP_SearchServiceTable(uint8_t UUIDList[][UUID_SIZE_BYTES],
			                                       const uint8_t TotalUUIDs,
			                                       const ServiceAttributeTable_t* CurrAttributeTable);
			static void     SDP_CheckUUIDMatch(uint8_t UUIDList[][UUID_SIZE_BYTES],
			                                   const uint8_t TotalUUIDs,
			                                   uint16_t* const UUIDMatchFlags,
			                                   const void* CurrAttribute);

			static uint8_t  SDP_GetAttributeList(uint16_t AttributeList[][2],
			                                     const void** const CurrentParameter);
			static uint8_t  SDP_GetUUIDList(uint8_t UUIDList[][UUID_SIZE_BYTES],
			                                const void** const CurrentParameter);

			static uint32_t SDP_GetLocalAttributeContainerSize(const void* const AttributeData,
			                                                   uint8_t* const HeaderSize);
			static uint32_t SDP_GetDataElementSize(const void** const AttributeHeader,
			                                       uint8_t* const ElementHeaderSize);
		#endif

#endif

