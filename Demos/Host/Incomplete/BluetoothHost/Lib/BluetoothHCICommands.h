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

#ifndef _BLUETOOTH_HCICOMMANDS_H_
#define _BLUETOOTH_HCICOMMANDS_H_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>
		#include <stdbool.h>
		#include <stdio.h>

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Peripheral/SerialStream.h>

		#include "BluetoothStack.h"
		#include "BluetoothClassCodes.h"

	/* Macros: */
		#define BT_HCI_DEBUG(l, s, ...)                        do { if (HCI_DEBUG_LEVEL >= l) printf_P(PSTR("(HCI) " s "\r\n"), ##__VA_ARGS__); } while (0)
		#define HCI_DEBUG_LEVEL                                0

		#define OGF_LINK_CONTROL                              (0x01 << 10)
		#define OGF_CTRLR_BASEBAND                            (0x03 << 10)
		#define OGF_CTRLR_INFORMATIONAL                       (0x04 << 10)

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
		#define OCF_CTRLR_INFORMATIONAL_READBUFFERSIZE         0x0005
		#define OCF_CTRLR_INFORMATIONAL_READBDADDR             0x0009
		
		#define EVENT_COMMAND_STATUS                           0x0F
		#define EVENT_COMMAND_COMPLETE                         0x0E
		#define EVENT_CONNECTION_COMPLETE                      0x03
		#define EVENT_CONNECTION_REQUEST                       0x04
		#define EVENT_DISCONNECTION_COMPLETE                   0x05
		#define EVENT_REMOTE_NAME_REQUEST_COMPLETE             0x07
		#define EVENT_PIN_CODE_REQUEST                         0x16
		#define EVENT_LINK_KEY_REQUEST                         0x17
		
		#define ERROR_LIMITED_RESOURCES                        0x0D
		#define ERROR_UNACCEPTABLE_BDADDR                      0x0F
		
	/* Type Defines: */
		typedef struct
		{
			uint16_t OpCode;
			uint8_t  ParameterLength;
			uint8_t  Parameters[];
		} BT_HCICommand_Header_t;

		typedef struct
		{
			uint8_t  EventCode;
			uint8_t  ParameterLength;
		} BT_HCIEvent_Header_t;

		typedef struct
		{
			uint8_t  Status;
			uint8_t  Packets;
			uint16_t OpCode;
		} BT_HCIEvent_CommandStatus_t;
		
		typedef struct
		{
			uint8_t  HCIPacketsAllowable;
			uint16_t Opcode;
			uint8_t  ReturnParams[];
		} BT_HCIEvent_CommandComplete_t;

		typedef struct
		{
			uint8_t  RemoteAddress[6];
			uint8_t  ClassOfDevice_Service;
			uint16_t ClassOfDevice_MajorMinor;
			uint8_t  LinkType;
		} BT_HCIEvent_ConnectionRequest_t;

		typedef struct
		{
			uint8_t  Status;
			uint16_t ConnectionHandle;
			uint8_t  RemoteAddress[6];
			uint8_t  LinkType;
			uint8_t  EncryptionEnabled;
		} BT_HCIEvent_ConnectionComplete_t;
		
		typedef struct
		{
			uint8_t  RemoteAddress[6];
		} BT_HCIEvent_PinCodeReq_t;

		typedef struct
		{
			uint8_t  RemoteAddress[6];
		} BT_HCIEvent_LinkKeyReq_t;
				
		typedef struct
		{
			uint8_t  RemoteAddress[6];
		} BT_HCICommand_LinkKeyNAKResp_t;

		typedef struct
		{
			uint8_t  RemoteAddress[6];
			uint8_t  PINCodeLength;
			char     PINCode[16];
		} BT_HCICommand_PinCodeResp_t;
		
		typedef struct
		{
			uint8_t  RemoteAddress[6];
			uint8_t  SlaveRole;
		} BT_HCICommand_AcceptConnectionReq_t;
		
		typedef struct
		{
			uint8_t  RemoteAddress[6];
			uint8_t  Reason;
		} BT_HCICommand_RejectConnectionReq_t;		

	/* Enums: */
		enum BT_ScanEnable_Modes_t
		{
			BT_SCANMODE_NoScansEnabled       = 0,
			BT_SCANMODE_InquiryScanOnly      = 1,
			BT_SCANMODE_PageScanOnly         = 2,
			BT_SCANMODE_InquiryAndPageScans  = 3,
		};

		enum BT_HCIStates_t
		{
			Bluetooth_ProcessEvents          = 0,
			Bluetooth_Init                   = 1,
			Bluetooth_Init_Reset             = 2,
			Bluetooth_Init_ReadBufferSize    = 3,
			Bluetooth_Init_GetBDADDR         = 4,
			Bluetooth_Init_SetLocalName      = 5,
			Bluetooth_Init_SetDeviceClass    = 6,
			Bluetooth_Init_WriteScanEnable   = 7,
			Bluetooth_Init_FinalizeInit      = 8,
			Bluetooth_Conn_AcceptConnection  = 9,
			Bluetooth_Conn_RejectConnection  = 10,
			Bluetooth_Conn_SendPINCode       = 11,
			Bluetooth_Conn_SendLinkKeyNAK    = 12,
		};
		
	/* Function Prototypes: */
		void Bluetooth_HCITask(void);
			
		#if defined(INCLUDE_FROM_BLUETOOTHHCICOMMANDS_C)
			static uint8_t Bluetooth_SendHCICommand(const BT_HCICommand_Header_t* const HCICommandHeader, const void* Parameters,
			                                        const uint16_t ParameterLength);
		#endif
		
#endif
