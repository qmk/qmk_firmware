/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#ifndef _TESTANDMEASUREMENT_H_
#define _TESTANDMEASUREMENT_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>

		#include "Descriptors.h"

		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Platform/Platform.h>

	/* Macros: */
		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY                  LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING              (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY                    (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR                    (LEDS_LED1 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is busy. */
		#define LEDMASK_USB_BUSY                      LEDS_LED2

		#define Req_InitiateAbortBulkOut              0x01
		#define Req_CheckAbortBulkOutStatus           0x02
		#define Req_InitiateAbortBulkIn               0x03
		#define Req_CheckAbortBulkInStatus            0x04
		#define Req_InitiateClear                     0x05
		#define Req_CheckClearStatus                  0x06
		#define Req_GetCapabilities                   0x07
		#define Req_IndicatorPulse                    0x40

		#define TMC_STATUS_SUCCESS                    0x01
		#define TMC_STATUS_PENDING                    0x02
		#define TMC_STATUS_FAILED                     0x80
		#define TMC_STATUS_TRANSFER_NOT_IN_PROGRESS   0x81
		#define TMC_STATUS_SPLIT_NOT_IN_PROGRESS      0x82
		#define TMC_STATUS_SPLIT_IN_PROGRESS          0x83

		#define TMC_MESSAGEID_DEV_DEP_MSG_OUT         0x01
		#define TMC_MESSAGEID_DEV_DEP_MSG_IN          0x02
		#define TMC_MESSAGEID_DEV_VENDOR_OUT          0x7E
		#define TMC_MESSAGEID_DEV_VENDOR_IN           0x7F

	/* Type Defines */
		typedef struct
		{
			uint8_t  Status;
			uint8_t  Reserved;

			uint16_t TMCVersion;

			struct
			{
				unsigned ListenOnly             : 1;
				unsigned TalkOnly               : 1;
				unsigned PulseIndicateSupported : 1;
				unsigned Reserved               : 5;
			} Interface;

			struct
			{
				unsigned SupportsAbortINOnMatch : 1;
				unsigned Reserved               : 7;
			} Device;

			uint8_t Reserved2[6];
			uint8_t Reserved3[12];
		} TMC_Capabilities_t;

		typedef struct
		{
			uint8_t LastMessageTransaction;
			uint8_t TermChar;
			uint8_t Reserved[2];
		} TMC_DevOUTMessageHeader_t;

		typedef struct
		{
			uint8_t LastMessageTransaction;
			uint8_t Reserved[3];
		} TMC_DevINMessageHeader_t;

		typedef struct
		{
			uint8_t  MessageID;
			uint8_t  Tag;
			uint8_t  InverseTag;
			uint8_t  Reserved;
			uint32_t TransferSize;

			union
			{
				TMC_DevOUTMessageHeader_t DeviceOUT;
				TMC_DevINMessageHeader_t  DeviceIN;
				uint32_t                  VendorSpecific;
			} MessageIDSpecific;
		} TMC_MessageHeader_t;

	/* Function Prototypes: */
		void SetupHardware(void);
		void TMC_Task(void);
		bool ReadTMCHeader(TMC_MessageHeader_t* const MessageHeader);
		bool WriteTMCHeader(TMC_MessageHeader_t* const MessageHeader);

		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_ControlRequest(void);

#endif

