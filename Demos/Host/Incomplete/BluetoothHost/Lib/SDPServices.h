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

/** \file
 *
 *  Header file for SDPServices.c.
 */

#ifndef _SDPSERVICES_H_
#define _SDPSERVICES_H_
	
	/* Includes: */
		#include "ServiceDiscoveryProtocol.h"

	/* Macros: */
		/** Size of a full 128 bit UUID, in bytes. */
		#define UUID_SIZE_BYTES                         16
		
		/** First 80 bits common to all standardized Bluetooth services. */
		#define BASE_80BIT_UUID                         SWAPENDIAN_32(0xFB349B5F), SWAPENDIAN_16(0x8000), SWAPENDIAN_16(0x0080), SWAPENDIAN_16(0x0010)
		
		#define SDP_ATTRIBUTE_ID_SERVICERECORDHANDLE    0x0000
		#define SDP_ATTRIBUTE_ID_SERVICECLASSIDS        0x0001
		#define SDP_ATTRIBUTE_ID_LANGIDOFFSET           0x0006
		#define SDP_ATTRIBUTE_ID_VERSION                0x0200
		#define SDP_ATTRIBUTE_ID_SERVICENAME            0x0100
		#define SDP_ATTRIBUTE_ID_SERVICEDESCRIPTION     0x0101
		
		#define SWAPENDIAN_16(x)                        ((((x) & 0xFF00) >> 8) | (((x) & 0x00FF) << 8))
		#define SWAPENDIAN_32(x)                        ((((x) & 0xFF000000) >> 24) | (((x) & 0x00FF0000) >> 8) | \
		                                                 (((x) & 0x0000FF00) << 8) | (((x) & 0x000000FF) << 24))
		
		/** Terminator for a service attribute table of type \ref ServiceAttributeTable_t. */
		#define SERVICE_ATTRIBUTE_TABLE_TERMINATOR      {.Data = NULL}
		
	/* Type Defines: */
		typedef struct
		{
			uint32_t A;
			uint16_t B;
			uint16_t C;
			uint16_t D;
			uint8_t  E[6];
		} UUID_t;
	
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
			UUID_t      UUID; /**< UUID of a service supported by the device */
			const void* AttributeTable; /**< Pointer to the UUID's attribute table, located in PROGMEM memory space */
		} ServiceTable_t;

		/** Structure for a list of Data Elements containing UUIDs, for service attributes requiring UUID lists. */
		typedef struct
		{
			uint8_t Header; /**< Data Element header, should be (SDP_DATATYPE_UUID | SDP_DATASIZE_128Bit) */
			UUID_t  UUID; /**< UUID to store in the list Data Element */
		} ItemUUID_t;

		/** Structure for a list of Data Elements containing 8-bit integers, for service attributes requiring such lists. */
		typedef struct
		{
			uint8_t Header; /**< Data Element header, should be (SDP_DATATYPE_UnsignedInt | SDP_DATASIZE_8Bit) */
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

	/* External Variables: */
		extern const ServiceAttributeTable_t SDP_Attribute_Table[];
		extern const ServiceAttributeTable_t RFCOMM_Attribute_Table[];
		
#endif
