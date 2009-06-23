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

#include "BluetoothHCICommands.h"

static   Bluetooth_HCICommand_Header_t HCICommandHeader;
static   Bluetooth_HCIEvent_Header_t   HCIEventHeader;

         uint8_t                       Bluetooth_HCIProcessingState;
static   uint8_t                       Bluetooth_TempDeviceAddress[6];

static uint8_t Bluetooth_SendHCICommand(void* Parameters, uint8_t ParamLength)
{
	uint8_t CommandBuffer[sizeof(HCICommandHeader) + HCICommandHeader.ParameterLength];

	USB_ControlRequest = (USB_Request_Header_t)
		{
			bmRequestType: (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_DEVICE),
			bRequest:      0,
			wValue:        0,
			wIndex:        0,
			wLength:       sizeof(CommandBuffer)
		};
		
	memset(CommandBuffer, 0x00, sizeof(CommandBuffer));
	memcpy(CommandBuffer, &HCICommandHeader, sizeof(HCICommandHeader));
	
	if (ParamLength)
	  memcpy(&CommandBuffer[sizeof(HCICommandHeader)], Parameters, ParamLength);

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(CommandBuffer);
}

static bool Bluetooth_GetNextHCIEventHeader(void)
{
	Pipe_SelectPipe(BLUETOOTH_EVENTS_PIPE);
	Pipe_Unfreeze();
	
	if (!(Pipe_IsReadWriteAllowed()))
	{
		Pipe_Freeze();
		return false;
	}
	  
	Pipe_Read_Stream_LE(&HCIEventHeader, sizeof(HCIEventHeader));
	  
	Pipe_Freeze();

	return true;
}

static void Bluetooth_DiscardRemainingHCIEventParameters(void)
{
	Pipe_SelectPipe(BLUETOOTH_EVENTS_PIPE);
	
	Pipe_Unfreeze();
	Pipe_Discard_Stream(HCIEventHeader.ParameterLength);
	Pipe_ClearIN();
	Pipe_Freeze();
}

void Bluetooth_ProcessHCICommands(void)
{
	uint8_t ErrorCode;

	switch (Bluetooth_HCIProcessingState)
	{
		case Bluetooth_Init:
			Pipe_SelectPipe(BLUETOOTH_EVENTS_PIPE);
			
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

			do
			{
				while (!(Bluetooth_GetNextHCIEventHeader()));
				Bluetooth_DiscardRemainingHCIEventParameters();
			} while (HCIEventHeader.EventCode != EVENT_COMMAND_COMPLETE);

			Bluetooth_HCIProcessingState = Bluetooth_Init_ReadBufferSize;
			break;
		case Bluetooth_Init_ReadBufferSize:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
			{
				OpCode: {OGF: OGF_CTRLR_INFORMATIONAL, OCF: OGF_CTRLR_INFORMATIONAL_READBUFFERSIZE},
				ParameterLength: 0,
			};
		
			BT_DEBUG("(HCI) Enter State: Bluetooth_Init_ReadBufferSize", NULL);

			ErrorCode = Bluetooth_SendHCICommand(NULL, 0);

			do
			{
				while (!(Bluetooth_GetNextHCIEventHeader()));
				Bluetooth_DiscardRemainingHCIEventParameters();
			} while (HCIEventHeader.EventCode != EVENT_COMMAND_COMPLETE);

			Bluetooth_HCIProcessingState = Bluetooth_Init_SetEventMask;		
			break;
		case Bluetooth_Init_SetEventMask:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
			{
				OpCode: {OGF: OGF_CTRLR_BASEBAND, OCF: OCF_CTRLR_BASEBAND_SET_EVENT_MASK},
				ParameterLength: 8,
			};
		
			BT_DEBUG("(HCI) Enter State: Bluetooth_Init_SetEventMask", NULL);
			
			uint8_t EventMask[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
			ErrorCode = Bluetooth_SendHCICommand(&EventMask, 8);

			BT_DEBUG("(HCI) -- Event mask: 0x%02X%02X%02X%02X%02X%02X%02X%02X", EventMask[7], EventMask[6], EventMask[5], EventMask[4],
			                                                                    EventMask[3], EventMask[2], EventMask[1], EventMask[0]);
			do
			{
				while (!(Bluetooth_GetNextHCIEventHeader()));
				Bluetooth_DiscardRemainingHCIEventParameters();
			} while (HCIEventHeader.EventCode != EVENT_COMMAND_COMPLETE);
		

			Bluetooth_HCIProcessingState = Bluetooth_Init_SetLocalName;		
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
			
			do
			{
				while (!(Bluetooth_GetNextHCIEventHeader()));
				Bluetooth_DiscardRemainingHCIEventParameters();
			} while (HCIEventHeader.EventCode != EVENT_COMMAND_COMPLETE);
			
			Bluetooth_HCIProcessingState = Bluetooth_Init_SetDeviceClass;
			break;
		case Bluetooth_Init_SetDeviceClass:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_CTRLR_BASEBAND, OCF: OCF_CTRLR_BASEBAND_WRITE_CLASS_OF_DEVICE},
					ParameterLength: 3,
				};

			BT_DEBUG("(HCI) Enter State: Bluetooth_Init_SetDeviceClass", NULL);

			ErrorCode = Bluetooth_SendHCICommand(&Bluetooth_DeviceConfiguration.Class, 3);

			do
			{
				while (!(Bluetooth_GetNextHCIEventHeader()));
				Bluetooth_DiscardRemainingHCIEventParameters();
			} while (HCIEventHeader.EventCode != EVENT_COMMAND_COMPLETE);

			Bluetooth_HCIProcessingState = Bluetooth_Init_WriteScanEnable;	
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

			do
			{
				while (!(Bluetooth_GetNextHCIEventHeader()));
				Bluetooth_DiscardRemainingHCIEventParameters();
			} while (HCIEventHeader.EventCode != EVENT_COMMAND_COMPLETE);

			Bluetooth_HCIProcessingState = Bluetooth_PrepareToProcessEvents;
			break;
		case Bluetooth_PrepareToProcessEvents:
			BT_DEBUG("(HCI) Enter State: Bluetooth_ProcessEvents", NULL);

			Bluetooth_HCIProcessingState     = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_ProcessEvents:
			if (Bluetooth_GetNextHCIEventHeader())
			{
				BT_DEBUG("(HCI) Event Code: 0x%02X", HCIEventHeader.EventCode);
			
				if (HCIEventHeader.EventCode == EVENT_COMMAND_STATUS)
				{
					Bluetooth_HCIEvent_CommandStatus_Header_t CommandStatusHeader;

					Pipe_Read_Stream_LE(&CommandStatusHeader, sizeof(CommandStatusHeader));
					HCIEventHeader.ParameterLength -= sizeof(CommandStatusHeader);
										
					BT_DEBUG("(HCI) >> Command status: 0x%02X", CommandStatusHeader.CommandStatus);
					
					if (CommandStatusHeader.CommandStatus)
					  Bluetooth_HCIProcessingState = Bluetooth_Init;
				}
				else if (HCIEventHeader.EventCode == EVENT_CONNECTION_REQUEST)
				{
					Bluetooth_HCIEvent_ConnectionRequest_Header_t ConnectionRequestParams;
					
					Pipe_Read_Stream_LE(&ConnectionRequestParams, sizeof(ConnectionRequestParams));
					HCIEventHeader.ParameterLength -= sizeof(ConnectionRequestParams);

					BT_DEBUG("(HCI) >> Connection Request from device %02X:%02X:%02X:%02X:%02X:%02X",
					         ConnectionRequestParams.RemoteAddress[5], ConnectionRequestParams.RemoteAddress[4], 
					         ConnectionRequestParams.RemoteAddress[3], ConnectionRequestParams.RemoteAddress[2], 
					         ConnectionRequestParams.RemoteAddress[1], ConnectionRequestParams.RemoteAddress[0]);
 					BT_DEBUG("(HCI) -- Device Class: 0x%02X%04X", ConnectionRequestParams.ClassOfDevice_Service,
					                                              ConnectionRequestParams.ClassOfDevice_MajorMinor);
					BT_DEBUG("(HCI) -- Link Type: 0x%02x", ConnectionRequestParams.LinkType);
					
					memcpy(Bluetooth_TempDeviceAddress, ConnectionRequestParams.RemoteAddress,
					       sizeof(Bluetooth_TempDeviceAddress));

					Bluetooth_HCIProcessingState = (Bluetooth_Connection.IsConnected) ? Bluetooth_Conn_RejectConnection :
						                                                                Bluetooth_Conn_AcceptConnection;
				}
				else if (HCIEventHeader.EventCode == EVENT_DISCONNECTION_COMPLETE)
				{
					BT_DEBUG("(HCI) >> Disconnection from device complete.", NULL);
					Bluetooth_HCIProcessingState = Bluetooth_Init;
				}
				else if (HCIEventHeader.EventCode == EVENT_CONNECTION_COMPLETE)
				{
					Bluetooth_HCIEvent_ConnectionComplete_Header_t ConnectionCompleteParams;
					
					Pipe_Read_Stream_LE(&ConnectionCompleteParams, sizeof(ConnectionCompleteParams));
					HCIEventHeader.ParameterLength -= sizeof(ConnectionCompleteParams);

					BT_DEBUG("(HCI) >> Connection to device complete.", NULL);
					BT_DEBUG("(HCI) -- Status: %d", ConnectionCompleteParams.Status);
					BT_DEBUG("(HCI) -- Handle: %d", ConnectionCompleteParams.ConnectionHandle);
					
					if (ConnectionCompleteParams.Status == 0x00)
					{
						memcpy(Bluetooth_Connection.DeviceAddress, ConnectionCompleteParams.RemoteAddress,
							   sizeof(Bluetooth_Connection.DeviceAddress));
						Bluetooth_Connection.ConnectionHandle = ConnectionCompleteParams.ConnectionHandle;
						Bluetooth_Connection.IsConnected = true;
					}
				}
				else if (HCIEventHeader.EventCode == EVENT_PIN_CODE_REQUEST)
				{
					Pipe_Read_Stream_LE(&Bluetooth_TempDeviceAddress, sizeof(Bluetooth_TempDeviceAddress));
					HCIEventHeader.ParameterLength -= sizeof(Bluetooth_TempDeviceAddress);

					BT_DEBUG("(HCI) >> PIN code Request from device %02X:%02X:%02X:%02X:%02X:%02X", 
							 Bluetooth_TempDeviceAddress[5], Bluetooth_TempDeviceAddress[4], Bluetooth_TempDeviceAddress[3],
							 Bluetooth_TempDeviceAddress[2], Bluetooth_TempDeviceAddress[1], Bluetooth_TempDeviceAddress[0]);
							 
					Bluetooth_HCIProcessingState = Bluetooth_Conn_SendPINCode;
				}
				
				BT_DEBUG("(HCI) -- Unread Event Param Length: %d", HCIEventHeader.ParameterLength);

				Bluetooth_DiscardRemainingHCIEventParameters();
			}

			break;
		case Bluetooth_Conn_AcceptConnection:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_LINK_CONTROL, OCF: OCF_LINK_CONTROL_ACCEPT_CONNECTION_REQUEST},
					ParameterLength: sizeof(Bluetooth_HCICommand_AcceptConnectionRequest_Params_t),
				};
			
			BT_DEBUG("(HCI) Enter State: Bluetooth_Conn_AcceptConnection", NULL);

			Bluetooth_HCICommand_AcceptConnectionRequest_Params_t AcceptConnectionParams;
							 
			memcpy(AcceptConnectionParams.RemoteAddress, Bluetooth_TempDeviceAddress,
			       sizeof(Bluetooth_TempDeviceAddress));
			AcceptConnectionParams.SlaveRole = true;

			Bluetooth_SendHCICommand(&AcceptConnectionParams, sizeof(AcceptConnectionParams));
			
			Bluetooth_HCIProcessingState     = Bluetooth_PrepareToProcessEvents;
			break;
		case Bluetooth_Conn_RejectConnection:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_LINK_CONTROL, OCF: OCF_LINK_CONTROL_ACCEPT_CONNECTION_REQUEST},
					ParameterLength: sizeof(Bluetooth_HCICommand_RejectConnectionRequest_Params_t),
				};
			
			BT_DEBUG("(HCI) Enter State: Bluetooth_Conn_RejectConnection", NULL);

			Bluetooth_HCICommand_RejectConnectionRequest_Params_t RejectConnectionParams;

			memcpy(RejectConnectionParams.RemoteAddress, Bluetooth_TempDeviceAddress,
			       sizeof(Bluetooth_TempDeviceAddress));
			RejectConnectionParams.Reason = ERROR_LIMITED_RESOURCES;

			Bluetooth_SendHCICommand(&AcceptConnectionParams, sizeof(AcceptConnectionParams));
		
			Bluetooth_HCIProcessingState     = Bluetooth_PrepareToProcessEvents;
			break;
		case Bluetooth_Conn_SendPINCode:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_LINK_CONTROL, OCF: OCF_LINK_CONTROL_PIN_CODE_REQUEST_REPLY},
					ParameterLength: sizeof(Bluetooth_HCICommand_PinCodeResponse_Params_t),
				};
			
			BT_DEBUG("(HCI) Enter State: Bluetooth_Conn_SendPINCode", NULL);
			BT_DEBUG("(HCI) -- PIN: %s", Bluetooth_DeviceConfiguration.PINCode);

			Bluetooth_HCICommand_PinCodeResponse_Params_t PINCodeRequestParams;
		
			memcpy(PINCodeRequestParams.RemoteAddress, Bluetooth_TempDeviceAddress,
			       sizeof(Bluetooth_TempDeviceAddress));
			PINCodeRequestParams.PINCodeLength = strlen(Bluetooth_DeviceConfiguration.PINCode);
			memcpy(PINCodeRequestParams.PINCode, Bluetooth_DeviceConfiguration.PINCode,
			       sizeof(Bluetooth_DeviceConfiguration.PINCode));
			
			Bluetooth_SendHCICommand(&PINCodeRequestParams, sizeof(PINCodeRequestParams));
		
			do
			{
				while (!(Bluetooth_GetNextHCIEventHeader()));
				Bluetooth_DiscardRemainingHCIEventParameters();
			} while (HCIEventHeader.EventCode != EVENT_COMMAND_COMPLETE);

			Bluetooth_HCIProcessingState     = Bluetooth_PrepareToProcessEvents;
			break;
	}
}
