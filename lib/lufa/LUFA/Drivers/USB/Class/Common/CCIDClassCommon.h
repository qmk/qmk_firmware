/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2019  Filipe Rodrigues (filipepazrodrigues [at] gmail [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  \brief Common definitions and declarations for the library USB CCID Class driver.
 *
 *  Common definitions and declarations for the library USB CCID Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassCCID
 *  \defgroup Group_USBClassCCIDCommon  Common Class Definitions
 *
 *  \section Sec_USBClassCCIDCommon_ModDescription Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  CCID Class.
 *
 *  @{
 */

#ifndef _CCID_CLASS_COMMON_H_
#define _CCID_CLASS_COMMON_H_

	/* Includes: */
		#include "../../Core/StdDescriptors.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_CCID_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Macros: */
		#define CCID_CURRENT_SPEC_RELEASE_NUMBER              0x0110
		#define CCID_VOLTAGESUPPORT_5V                        0
		#define CCID_VOLTAGESUPPORT_3V                        (1 << 0)
		#define CCID_VOLTAGESUPPORT_1V8                       (1 << 1)

		#define CCID_PROTOCOLS_T0                             (1 << 0)
		#define CCID_PROTOCOLS_T1                             (1 << 1)

		#define CCID_PROTOCOLNUM_T0                           0
		#define CCID_PROTOCOLNUM_T1                           (1 << 0)

		#define CCID_ICCSTATUS_PRESENTANDACTIVE               0
		#define CCID_ICCSTATUS_PRESENTANDINACTIVE             (1 << 0)
		#define CCID_ICCSTATUS_NOICCPRESENT                   (1 << 1)

		#define CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR      0
		#define CCID_COMMANDSTATUS_ERROR                      1
		#define CCID_COMMANDSTATUS_FAILED                     (1 << 6)
		#define CCID_COMMANDSTATUS_TIMEEXTENSIONREQUESTED     (2 << 6)
		#define CCID_COMMANDSTATUS_RFU                        (3 << 6)

		#define CCID_ERROR_RFU_START                          0x80
		#define CCID_ERROR_NO_ERROR                           0x80
		#define CCID_ERROR_NOT_SUPPORTED                      0
		#define CCID_ERROR_CMD_ABORTED                        0xFF
		#define CCID_ERROR_CMD_NOT_ABORTED                    0xFF

		#define CCID_ERROR_PARAMETERS_PROTOCOL_NOT_SUPPORTED  0x7

		#define CCID_ERROR_SLOT_NOT_FOUND                     5

		#define CCID_DESCRIPTOR_CLOCK_KHZ(khz)                (khz)
		#define CCID_DESCRIPTOR_CLOCK_MHZ(mhz)                ((mhz) * 1000)


	/* Enums: */
		/** Enum for possible Class, Subclass and Protocol values of device and interface descriptors relating to the CCID
		 *  device class.
		 */
		enum CCID_Descriptor_ClassSubclassProtocol_t
		{
			CCID_CSCP_CCIDClass                         = 0x0b, /**< Descriptor Class value indicating that the device or interface
			                                                     *   belongs to the CCID class.
			                                                     */
			CCID_CSCP_NoSpecificSubclass                = 0x00, /**< Descriptor Subclass value indicating that the device or interface
			                                                     *   belongs to no specific subclass of the CCID class.
			                                                     */
			CCID_CSCP_NoSpecificProtocol                = 0x00, /**< Descriptor Protocol value indicating that the device or interface
			                                                     *   belongs to no specific protocol of the CCID class.
			                                                     */
		};

		/** Enum for possible bulk messages between PC and Reader */
		enum CCID_BulkOutMessages_t
		{
			CCID_PC_to_RDR_IccPowerOn                   = 0x62,
			CCID_PC_to_RDR_IccPowerOff                  = 0x63,
			CCID_PC_to_RDR_GetSlotStatus                = 0x65,
			CCID_PC_to_RDR_XfrBlock                     = 0x6f,
			CCID_PC_to_RDR_GetParameters                = 0x6c,
			CCID_PC_to_RDR_ResetParameters              = 0x6d,
			CCID_PC_to_RDR_SetParameters                = 0x61,
			CCID_PC_to_RDR_Escape                       = 0x6b,
			CCID_PC_to_RDR_IccClock                     = 0x6e,
			CCID_PC_to_RDR_T0APDU                       = 0x6a,
			CCID_PC_to_RDR_Secure                       = 0x69,
			CCID_PC_to_RDR_Mechanical                   = 0x71,
			CCID_PC_to_RDR_Abort                        = 0x72,
			CCID_PC_to_RDR_SetDataRateAndClockFrequency = 0x73,

			CCID_RDR_to_PC_DataBlock                    = 0x80,
			CCID_RDR_to_PC_SlotStatus                   = 0x81,
			CCID_RDR_to_PC_Parameters                   = 0x82,
			CCID_RDR_to_PC_Escape                       = 0x83,
			CCID_RDR_to_PC_DataRateAndClockFrequency    = 0x84,
		};

		/** Enum for the CCID class specific control requests that can be issued by the USB bus host. */
		enum CCID_ClassRequests_t
		{
			CCID_ABORT                                  = 0x1,
			CCID_GET_CLOCK_FREQUENCIES                  = 0x2,
			CCID_GET_DATA_RATES                         = 0x3,
		};

		/** Enum for the CCID class specific descriptor types. */
		enum CCID_DescriptorTypes_t
		{
			CCID_DTYPE_Functional                       = 0x21, /**< CCID class specific Interface functional descriptor. */
		};

		enum CCID_Features_Auto_t
		{
			CCID_Features_Auto_None 					= 0x0,
			CCID_Features_Auto_ParameterConfiguration	= 0x2,
			CCID_Features_Auto_ICCActivation			= 0x4,
			CCID_Features_Auto_VoltageSelection			= 0x8,

			CCID_Features_Auto_ICCClockFrequencyChange	= 0x10,
			CCID_Features_Auto_ICCBaudRateChange		= 0x20,
			CCID_Features_Auto_ParameterNegotiation		= 0x40,
			CCID_Features_Auto_PPS						= 0x80,
		};

		enum CCID_Features_ExchangeLevel_t
		{
			CCID_Features_ExchangeLevel_TPDU  				= 0x00010000,
			CCID_Features_ExchangeLevel_ShortAPDU 			= 0x00020000,
			CCID_Features_ExchangeLevel_ShortExtendedAPDU	= 0x00040000
		};

	/* Type Defines: */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */

			uint16_t    CCID;
			uint8_t     MaxSlotIndex;
			uint8_t     VoltageSupport;
			uint32_t    Protocols;
			uint32_t    DefaultClock;
			uint32_t    MaximumClock;
			uint8_t     NumClockSupported;
			uint32_t    DataRate;
			uint32_t    MaxDataRate;
			uint8_t     NumDataRatesSupported;
			uint32_t    MaxIFSD;
			uint32_t    SynchProtocols;
			uint32_t    Mechanical;
			uint32_t    Features;
			uint32_t    MaxCCIDMessageLength;
			uint8_t     ClassGetResponse;
			uint8_t     ClassEnvelope;
			uint16_t    LcdLayout;
			uint8_t     PINSupport;
			uint8_t     MaxCCIDBusySlots;
		} ATTR_PACKED USB_CCID_Descriptor_t;

		typedef struct
		{
			uint8_t FindexDindex;
			uint8_t TCCKST0;
			uint8_t GuardTimeT0;
			uint8_t WaitingIntegerT0;
			uint8_t ClockStop;
		} ATTR_PACKED USB_CCID_ProtocolData_T0_t;

		typedef struct
		{
			uint8_t FindexDindex;
			uint8_t TCCKST1;
			uint8_t GuardTimeT1;
			uint8_t WaitingIntegerT1;
			uint8_t ClockStop;
			uint8_t FSC;
			uint8_t NadValue;
		} ATTR_PACKED USB_CCID_ProtocolData_T1_t;


		/** Enum for a common bulk message header. */
		typedef struct
		{
			uint8_t     MessageType;
			uint32_t    Length;
			uint8_t     Slot;
			uint8_t     Seq;
		} ATTR_PACKED USB_CCID_BulkMessage_Header_t;

		typedef struct
		{
			USB_CCID_BulkMessage_Header_t CCIDHeader;
			uint8_t Status;
			uint8_t Error;
			uint8_t ChainParam;
			uint8_t Data[0];
		} ATTR_PACKED USB_CCID_RDR_to_PC_DataBlock_t;

		typedef struct
		{
			USB_CCID_BulkMessage_Header_t CCIDHeader;
			uint8_t Status;
			uint8_t Error;
			uint8_t ClockStatus;
		} ATTR_PACKED USB_CCID_RDR_to_PC_SlotStatus_t;

		typedef struct
		{
			USB_CCID_BulkMessage_Header_t CCIDHeader;
			uint8_t Status;
			uint8_t Error;
			uint8_t ProtocolNum;
			union
			{
				USB_CCID_ProtocolData_T0_t T0;
				USB_CCID_ProtocolData_T1_t T1;
			} ProtocolData;
		} ATTR_PACKED USB_CCID_RDR_to_PC_Parameters_t;

		typedef struct
		{
			USB_CCID_BulkMessage_Header_t CCIDHeader;
			uint8_t Status;
			uint8_t Error;
			uint8_t RFU;
			uint8_t Data[0];
		} ATTR_PACKED USB_CCID_RDR_to_PC_Escape_t;

		typedef struct
		{
			USB_CCID_BulkMessage_Header_t CCIDHeader;
			uint8_t Status;
			uint8_t Error;
			uint8_t RFU;
			uint32_t ClockFrequency;
			uint32_t DataRate;
		} ATTR_PACKED USB_CCID_RDR_to_PC_DataRateAndClockFrequency_t;

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

