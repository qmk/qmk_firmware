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

#include "BluetoothHCICommands.h"

static   Bluetooth_HCICommand_Header_t HCICommandHeader;
static   Bluetooth_HCIEvent_Header_t   HCIEventHeader;

         uint8_t                       Bluetooth_HCIProcessingState;
		 uint8_t                       Bluetooth_HCINextState;
static   uint8_t                       Bluetooth_TempDeviceAddress[6];

static uint8_t Bluetooth_SendHCICommand(void* Parameters, uint8_t ParamLength)
{
	uint8_t CommandBuffer[sizeof(HCICommandHeader) + HCICommandHeader.ParameterLength];

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_DEVICE),
			.bRequest      = 0,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = sizeof(CommandBuffer)
		};
		
	memset(CommandBuffer, 0x00, sizeof(CommandBuffer));
	memcpy(CommandBuffer, &HCICommandHeader, sizeof(HCICommandHeader));
	
	if (ParamLength)
	  memcpy(&CommandBuffer[sizeof(HCICommandHeader)], Parameters, ParamLength);

	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(CommandBuffer);
}

void Bluetooth_ProcessHCICommands(void)
{
	uint8_t ErrorCode;

	switch (Bluetooth_HCIProcessingState)
	{
		case Bluetooth_ProcessEvents:
			Pipe_SelectPipe(BLUETOOTH_EVENTS_PIPE);
			Pipe_Unfreeze();
			
			if (Pipe_IsReadWriteAllowed())
			{
				Pipe_Read_Stream_LE(&HCIEventHeader, sizeof(HCIEventHeader));
				
				uint8_t EventParams[HCIEventHeader.ParameterLength];

				Pipe_Read_Stream_LE(&EventParams, HCIEventHeader.ParameterLength);
				Pipe_ClearIN();

				BT_DEBUG("(HCI) Event Code: 0x%02X", HCIEventHeader.EventCode);
				
				switch (HCIEventHeader.EventCode)
				{
					case EVENT_COMMAND_COMPLETE:
						Bluetooth_HCIProcessingState = Bluetooth_HCINextState;

						BT_DEBUG("(HCI) >> Command Complete (Opcode 0x%04x)", 
						         ((Bluetooth_HCIEvent_CommandComplete_t*)&EventParams)->Opcode);
						break;
					case EVENT_COMMAND_STATUS:
						if (((Bluetooth_HCIEvent_CommandStatus_t*)&EventParams)->Status)
						  Bluetooth_HCIProcessingState = Bluetooth_Init;

						BT_DEBUG("(HCI) >> Command Status: 0x%02X",
						         ((Bluetooth_HCIEvent_CommandStatus_t*)&EventParams)->Status);					
						break;
					case EVENT_CONNECTION_REQUEST:
						memcpy(Bluetooth_TempDeviceAddress,
						       &((Bluetooth_HCIEvent_ConnectionRequest_t*)&EventParams)->RemoteAddress,
						       sizeof(Bluetooth_TempDeviceAddress));
					
						Bluetooth_HCIProcessingState = (Bluetooth_Connection.IsConnected ||
						                               (((Bluetooth_HCIEvent_ConnectionRequest_t*)&EventParams)->LinkType != 0x01)) ?
													   Bluetooth_Conn_RejectConnection : Bluetooth_Conn_AcceptConnection;

						BT_DEBUG("(HCI) >> Connection Request from Device %02X:%02X:%02X:%02X:%02X:%02X",
								 Bluetooth_TempDeviceAddress[5], Bluetooth_TempDeviceAddress[4], Bluetooth_TempDeviceAddress[3],
								 Bluetooth_TempDeviceAddress[2], Bluetooth_TempDeviceAddress[1], Bluetooth_TempDeviceAddress[0]);
						break;
					case EVENT_PIN_CODE_REQUEST:
						memcpy(Bluetooth_TempDeviceAddress,
						       &((Bluetooth_HCIEvent_PinCodeRequest_t*)&EventParams)->RemoteAddress,
						       sizeof(Bluetooth_TempDeviceAddress));

						Bluetooth_HCIProcessingState = Bluetooth_Conn_SendPINCode;

						BT_DEBUG("(HCI) >> PIN Request from Device %02X:%02X:%02X:%02X:%02X:%02X", 
								 Bluetooth_TempDeviceAddress[5], Bluetooth_TempDeviceAddress[4], Bluetooth_TempDeviceAddress[3],
								 Bluetooth_TempDeviceAddress[2], Bluetooth_TempDeviceAddress[1], Bluetooth_TempDeviceAddress[0]);
						break;
					case EVENT_CONNECTION_COMPLETE:
						memcpy(Bluetooth_Connection.RemoteAddress,
						       &((Bluetooth_HCIEvent_ConnectionComplete_t*)&EventParams)->RemoteAddress,
						       sizeof(Bluetooth_TempDeviceAddress));

						Bluetooth_Connection.ConnectionHandle = ((Bluetooth_HCIEvent_ConnectionComplete_t*)&EventParams)->ConnectionHandle;
						Bluetooth_Connection.IsConnected      = true;

						BT_DEBUG("(HCI) >> Connection Complete to Device %02X:%02X:%02X:%02X:%02X:%02X, Handle 0x%04x", 
								 Bluetooth_Connection.RemoteAddress[5], Bluetooth_Connection.RemoteAddress[4],
								 Bluetooth_Connection.RemoteAddress[3], Bluetooth_Connection.RemoteAddress[2],
								 Bluetooth_Connection.RemoteAddress[1], Bluetooth_Connection.RemoteAddress[0],
								 Bluetooth_Connection.ConnectionHandle);
						break;
				}
			}
			
			Pipe_Freeze();
			
			break;
		case Bluetooth_Init:
			memset(&Bluetooth_Connection, 0x00, sizeof(Bluetooth_Connection));

			Bluetooth_HCIProcessingState = Bluetooth_Init_Reset; 
			break;
		case Bluetooth_Init_Reset:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
			{
				OpCode: {OGF: OGF_CTRLR_BASEBAND, OCF: OCF_CTRLR_BASEBAND_RESET},
				ParameterLength: 0,
			};
			
			BT_DEBUG("(HCI) Enter State: Bluetooth_Init_Reset", NULL);

			ErrorCode = Bluetooth_SendHCICommand(NULL, 0);
			
			Bluetooth_HCINextState       = Bluetooth_Init_ReadBufferSize;
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_ReadBufferSize:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
			{
				OpCode: {OGF: OGF_CTRLR_INFORMATIONAL, OCF: OGF_CTRLR_INFORMATIONAL_READBUFFERSIZE},
				ParameterLength: 0,
			};
		
			BT_DEBUG("(HCI) Enter State: Bluetooth_Init_ReadBufferSize", NULL);

			ErrorCode = Bluetooth_SendHCICommand(NULL, 0);

			Bluetooth_HCINextState       = Bluetooth_Init_SetLocalName;
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_SetLocalName:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_CTRLR_BASEBAND, OCF: OCF_CTRLR_BASEBAND_WRITE_LOCAL_NAME},
					ParameterLength: 248,
				};

			BT_DEBUG("(HCI) Enter State: Bluetooth_Init_SetLocalName", NULL);
			BT_DEBUG("(HCI)  -- Name: %s", Bluetooth_DeviceConfiguration.Name);

			ErrorCode = Bluetooth_SendHCICommand(Bluetooth_DeviceConfiguration.Name, strlen(Bluetooth_DeviceConfiguration.Name));

			Bluetooth_HCINextState       = Bluetooth_Init_SetDeviceClass;
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_SetDeviceClass:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_CTRLR_BASEBAND, OCF: OCF_CTRLR_BASEBAND_WRITE_CLASS_OF_DEVICE},
					ParameterLength: 3,
				};

			BT_DEBUG("(HCI) Enter State: Bluetooth_Init_SetDeviceClass", NULL);

			ErrorCode = Bluetooth_SendHCICommand(&Bluetooth_DeviceConfiguration.Class, 3);

			Bluetooth_HCINextState       = Bluetooth_Init_WriteScanEnable;
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_WriteScanEnable:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
			{
				OpCode: {OGF: OGF_CTRLR_BASEBAND, OCF: OCF_CTRLR_BASEBAND_WRITE_SCAN_ENABLE},
				ParameterLength: 1,
			};
			
			BT_DEBUG("(HCI) Enter State: Bluetooth_Init_WriteScanEnable", NULL);

			uint8_t Interval = InquiryAndPageScans;
			ErrorCode = Bluetooth_SendHCICommand(&Interval, 1);
			
			Bluetooth_HCINextState       = Bluetooth_ProcessEvents;
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Conn_AcceptConnection:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_LINK_CONTROL, OCF: OCF_LINK_CONTROL_ACCEPT_CONNECTION_REQUEST},
					ParameterLength: sizeof(Bluetooth_HCICommand_AcceptConnectionRequest_t),
				};
			
			BT_DEBUG("(HCI) Enter State: Bluetooth_Conn_AcceptConnection", NULL);

			Bluetooth_HCICommand_AcceptConnectionRequest_t AcceptConnectionParams;

			memcpy(AcceptConnectionParams.RemoteAddress, Bluetooth_TempDeviceAddress, sizeof(Bluetooth_TempDeviceAddress));
			AcceptConnectionParams.SlaveRole = true;

			ErrorCode = Bluetooth_SendHCICommand(&AcceptConnectionParams, sizeof(AcceptConnectionParams));
			
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Conn_RejectConnection:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_LINK_CONTROL, OCF: OCF_LINK_CONTROL_REJECT_CONNECTION_REQUEST},
					ParameterLength: sizeof(Bluetooth_HCICommand_RejectConnectionRequest_t),
				};
			
			BT_DEBUG("(HCI) Enter State: Bluetooth_Conn_RejectConnection", NULL);

			Bluetooth_HCICommand_RejectConnectionRequest_t RejectConnectionParams;

			memcpy(RejectConnectionParams.RemoteAddress, Bluetooth_TempDeviceAddress, sizeof(RejectConnectionParams.RemoteAddress));
			RejectConnectionParams.Reason = ERROR_LIMITED_RESOURCES;

			ErrorCode = Bluetooth_SendHCICommand(&RejectConnectionParams, sizeof(RejectConnectionParams));
		
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Conn_SendPINCode:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_LINK_CONTROL, OCF: OCF_LINK_CONTROL_PIN_CODE_REQUEST_REPLY},
					ParameterLength: sizeof(Bluetooth_HCICommand_PinCodeResponse_t),
				};
			
			BT_DEBUG("(HCI) Enter State: Bluetooth_Conn_SendPINCode", NULL);
			BT_DEBUG("(HCI) -- PIN: %s", Bluetooth_DeviceConfiguration.PINCode);

			Bluetooth_HCICommand_PinCodeResponse_t PINCodeRequestParams;
		
			memcpy(PINCodeRequestParams.RemoteAddress, Bluetooth_TempDeviceAddress, sizeof(Bluetooth_TempDeviceAddress));
			PINCodeRequestParams.PINCodeLength = strlen(Bluetooth_DeviceConfiguration.PINCode);
			memcpy(PINCodeRequestParams.PINCode, Bluetooth_DeviceConfiguration.PINCode, sizeof(PINCodeRequestParams.PINCode));
			
			ErrorCode = Bluetooth_SendHCICommand(&PINCodeRequestParams, sizeof(PINCodeRequestParams));

			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
	}
}
