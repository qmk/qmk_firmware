/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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

#ifndef _BLUETOOTH_HCICOMMANDS_H_
#define _BLUETOOTH_HCICOMMANDS_H_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>
		#include <stdbool.h>

		#include <LUFA/Drivers/USB/USB.h>

		#include "BluetoothStack.h"
		#include "BluetoothClassCodes.h"

	/* Macros: */
		#define OGF_LINK_CONTROL                               0x01
		#define OGF_CTRLR_BASEBAND                             0x03
		#define OGF_CTRLR_INFORMATIONAL                        0x04

		#define OCF_LINK_CONTROL_INQUIRY                       0x0001
		#define OCF_LINK_CONTROL_INQUIRY_CANCEL                0x0002
		#define OCF_LINK_CONTROL_PERIODIC_INQUIRY              0x0003
		#define OCF_LINK_CONTROL_EXIT_PERIODIC_INQUIRY         0x0004
		#define OCF_LINK_CONTROL_CREATE_CONNECTION             0x0005
		#define OCF_LINK_CONTROL_DISCONNECT                    0x0006
		#define OCF_LINK_CONTROL_CREATE_CONNECTION_CANCEL      0x0008
		#define OCF_LINK_CONTROL_ACCEPT_CONNECTION_REQUEST     0x0009
		#define OCF_LINK_CONTROL_REJECT_CONNECTION_REQUEST     0x000A
		#define OCF_LINK_CONTROL_LINK_KEY_REQUEST_REPLY        0x000B
		#define OCF_LINK_CONTROL_LINK_KEY_REQUEST_NEG_REPLY    0x000C
		#define OCF_LINK_CONTROL_PIN_CODE_REQUEST_REPLY        0x000D
		#define OCF_LINK_CONTROL_PIN_CODE_REQUEST_NEG_REPLY    0x000E
		#define OCF_LINK_CONTROL_CHANGE_CONNECTION_PACKET_TYPE 0x000F
		#define OCF_LINK_CONTROL_REMOTE_NAME_REQUEST           0x0019
		#define OCF_CTRLR_BASEBAND_SET_EVENT_MASK              0x0001
		#define OCF_CTRLR_BASEBAND_RESET                       0x0003
		#define OCF_CTRLR_BASEBAND_WRITE_PIN_TYPE              0x000A
		#define OCF_CTRLR_BASEBAND_WRITE_LOCAL_NAME            0x0013
		#define OCF_CTRLR_BASEBAND_READ_LOCAL_NAME             0x0014
		#define OCF_CTRLR_BASEBAND_WRITE_SCAN_ENABLE           0x001A
		#define OCF_CTRLR_BASEBAND_WRITE_CLASS_OF_DEVICE       0x0024
		#define OCF_CTRLR_BASEBAND_WRITE_SIMPLE_PAIRING_MODE   0x0056
		#define OCF_CTRLR_BASEBAND_WRITE_AUTHENTICATION_ENABLE 0x0020
		#define OGF_CTRLR_INFORMATIONAL_READBUFFERSIZE         0x0005
		
		#define EVENT_COMMAND_STATUS                           0x0F
		#define EVENT_COMMAND_COMPLETE                         0x0E
		#define EVENT_CONNECTION_COMPLETE                      0x03
		#define EVENT_CONNECTION_REQUEST                       0x04
		#define EVENT_DISCONNECTION_COMPLETE                   0x05
		#define EVENT_REMOTE_NAME_REQUEST_COMPLETE             0x07
		#define EVENT_PIN_CODE_REQUEST                         0x16
		
		#define ERROR_LIMITED_RESOURCES                        0x0D
		
	/* Type Defines: */
		typedef struct
		{
			struct
			{
				int OCF : 10;
				int OGF : 6;
			} OpCode;

			uint8_t  ParameterLength;
			uint8_t  Parameters[];
		} Bluetooth_HCICommand_Header_t;

		typedef struct
		{
			uint8_t  EventCode;
			uint8_t  ParameterLength;
		} Bluetooth_HCIEvent_Header_t;

		typedef struct
		{
			uint8_t CommandStatus;
			uint8_t CommandPackets;

			struct
			{
				int OCF : 10;
				int OGF : 6;
			} OpCode;
		} Bluetooth_HCIEvent_CommandStatus_Header_t;
		
		typedef struct
		{
			uint8_t  RemoteAddress[6];
			uint8_t  ClassOfDevice_Service;
			uint16_t ClassOfDevice_MajorMinor;
			uint8_t  LinkType;
		} Bluetooth_HCIEvent_ConnectionRequest_Header_t;

		typedef struct
		{
			uint8_t  Status;
			uint16_t ConnectionHandle;
			uint8_t  RemoteAddress[6];
			uint8_t  LinkType;
			uint8_t  EncryptionEnabled;
		} Bluetooth_HCIEvent_ConnectionComplete_Header_t;
		
		typedef struct
		{
			uint8_t  RemoteAddress[6];
			uint8_t  SlaveRole;
		} Bluetooth_HCICommand_AcceptConnectionRequest_Params_t;
		
		typedef struct
		{
			uint8_t  RemoteAddress[6];
			uint8_t  Reason;
		} Bluetooth_HCICommand_RejectConnectionRequest_Params_t;

		typedef struct
		{
			uint8_t  RemoteAddress[6];
			uint8_t  PINCodeLength;
			char     PINCode[16];
		} Bluetooth_HCICommand_PinCodeResponse_Params_t;
		
	/* Enums: */
		enum Bluetooth_ScanEnable_Modes_t
		{
			NoScansEnabled            = 0,
			InquiryScanOnly           = 1,
			PageScanOnly              = 2,
			InquiryAndPageScans       = 3,
		};

		enum BluetoothStack_States_t
		{
			Bluetooth_Init                            = 0,
			Bluetooth_Init_Reset                      = 1,
			Bluetooth_Init_ReadBufferSize             = 2,
			Bluetooth_Init_SetEventMask               = 3,
			Bluetooth_Init_SetLocalName               = 4,
			Bluetooth_Init_SetDeviceClass             = 5,
			Bluetooth_Init_WriteScanEnable            = 6,
			Bluetooth_PrepareToProcessEvents          = 7,
			Bluetooth_ProcessEvents                   = 8,
			Bluetooth_Conn_AcceptConnection           = 9,
			Bluetooth_Conn_RejectConnection           = 10,
			Bluetooth_Conn_SendPINCode                = 11,
		};
		
	/* External Variables: */
		extern uint8_t Bluetooth_HCIProcessingState;

	/* Function Prototypes: */
		void Bluetooth_ProcessHCICommands(void);

		#if defined(INCLUDE_FROM_BLUETOOTHHCICOMMANDS_C)
			static uint8_t Bluetooth_SendHCICommand(void* Parameters, uint8_t ParamLength);
			static bool    Bluetooth_GetNextHCIEventHeader(void);
			static void    Bluetooth_DiscardRemainingHCIEventParameters(void);
			static void    Bluetooth_ProcessHCICommands(void);
		#endif
		
#endif
