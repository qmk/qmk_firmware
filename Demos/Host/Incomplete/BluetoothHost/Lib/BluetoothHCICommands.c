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

static Bluetooth_HCICommand_Header_t HCICommandHeader;

       uint8_t                       Bluetooth_HCIProcessingState;
static uint8_t                       Bluetooth_HCINextState;
static uint8_t                       Bluetooth_TempDeviceAddress[6];

static uint8_t Bluetooth_SendHCICommand(void* Parameters, uint16_t ParameterLength)
{
	/* Need to reserve the amount of bytes given in the header for the complete payload */
	uint8_t CommandBuffer[sizeof(HCICommandHeader) + HCICommandHeader.ParameterLength];

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_DEVICE),
			.bRequest      = 0,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = sizeof(CommandBuffer)
		};

	/* Copy over the HCI command header to the allocated buffer */
	memcpy(CommandBuffer, &HCICommandHeader, sizeof(HCICommandHeader));
	
	/* Zero out the parameter section of the response to ensure that any padding bytes do not expose private RAM contents */
	memset(&CommandBuffer[sizeof(HCICommandHeader)], 0x00, HCICommandHeader.ParameterLength);

	/* Copy over the command parameters (if any) to the command buffer - note, the number of actual source parameter bytes
	   may differ to those in the header; any difference in length is filled with 0x00 padding bytes */
	memcpy(&CommandBuffer[sizeof(HCICommandHeader)], Parameters, ParameterLength);
	
	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(CommandBuffer);
}

void Bluetooth_ProcessHCICommands(void)
{
	switch (Bluetooth_HCIProcessingState)
	{
		case Bluetooth_ProcessEvents:
			Pipe_SelectPipe(BLUETOOTH_EVENTS_PIPE);
			Pipe_Unfreeze();
			
			if (Pipe_IsReadWriteAllowed())
			{
				Bluetooth_HCIEvent_Header_t HCIEventHeader;

				/* Read in the event header to fetch the event code and payload length */
				Pipe_Read_Stream_LE(&HCIEventHeader, sizeof(HCIEventHeader));
				
				/* Create a temporary buffer for the event parameters */
				uint8_t EventParams[HCIEventHeader.ParameterLength];

				/* Read in the event parameters into the temporary buffer */
				Pipe_Read_Stream_LE(&EventParams, HCIEventHeader.ParameterLength);
				Pipe_ClearIN();

				BT_HCI_DEBUG("Event Code: 0x%02X", HCIEventHeader.EventCode);
				
				switch (HCIEventHeader.EventCode)
				{
					case EVENT_COMMAND_COMPLETE:
						Bluetooth_HCIProcessingState = Bluetooth_HCINextState;

						BT_HCI_DEBUG(">> Command Complete (Opcode 0x%04x)", 
						         ((Bluetooth_HCIEvent_CommandComplete_t*)&EventParams)->Opcode);
						break;
					case EVENT_COMMAND_STATUS:
						/* If the execution of a command failed, reset the stack */
						if (((Bluetooth_HCIEvent_CommandStatus_t*)&EventParams)->Status)
						  Bluetooth_HCIProcessingState = Bluetooth_Init;

						BT_HCI_DEBUG(">> Command Status: 0x%02X",
						         ((Bluetooth_HCIEvent_CommandStatus_t*)&EventParams)->Status);					
						break;
					case EVENT_CONNECTION_REQUEST:
						/* Need to store the remote device's BT address in a temporary buffer for later use */
						memcpy(Bluetooth_TempDeviceAddress,
						       &((Bluetooth_HCIEvent_ConnectionRequest_t*)&EventParams)->RemoteAddress,
						       sizeof(Bluetooth_TempDeviceAddress));
							   
						bool IsACLConnection = (((Bluetooth_HCIEvent_ConnectionRequest_t*)&EventParams)->LinkType == 0x01);

						/* Only accept the connection if it is a ACL (data) connection, a device is not already connected
						   and the user application has indicated that the connection should be allowed */
						Bluetooth_HCIProcessingState = (Bluetooth_Connection.IsConnected || !(IsACLConnection) ||
													    !(CALLBACK_Bluetooth_ConnectionRequest(Bluetooth_TempDeviceAddress))) ?
													   Bluetooth_Conn_RejectConnection : Bluetooth_Conn_AcceptConnection;

						BT_HCI_DEBUG(">> Connection Request from Device %02X:%02X:%02X:%02X:%02X:%02X",
								 Bluetooth_TempDeviceAddress[5], Bluetooth_TempDeviceAddress[4], Bluetooth_TempDeviceAddress[3],
								 Bluetooth_TempDeviceAddress[2], Bluetooth_TempDeviceAddress[1], Bluetooth_TempDeviceAddress[0]);
						break;
					case EVENT_PIN_CODE_REQUEST:
						/* Need to store the remote device's BT address in a temporary buffer for later use */
						memcpy(Bluetooth_TempDeviceAddress,
						       &((Bluetooth_HCIEvent_PinCodeRequest_t*)&EventParams)->RemoteAddress,
						       sizeof(Bluetooth_TempDeviceAddress));

						Bluetooth_HCIProcessingState = Bluetooth_Conn_SendPINCode;

						BT_HCI_DEBUG(">> PIN Request from Device %02X:%02X:%02X:%02X:%02X:%02X", 
								 Bluetooth_TempDeviceAddress[5], Bluetooth_TempDeviceAddress[4], Bluetooth_TempDeviceAddress[3],
								 Bluetooth_TempDeviceAddress[2], Bluetooth_TempDeviceAddress[1], Bluetooth_TempDeviceAddress[0]);
						break;
					case EVENT_CONNECTION_COMPLETE:
						/* Need to store the remote device's BT address in a temporary buffer for later use */
						memcpy(Bluetooth_Connection.RemoteAddress,
						       &((Bluetooth_HCIEvent_ConnectionComplete_t*)&EventParams)->RemoteAddress,
						       sizeof(Bluetooth_TempDeviceAddress));

						/* Store the created connection handle and indicate that the connection has been established */
						Bluetooth_Connection.ConnectionHandle = ((Bluetooth_HCIEvent_ConnectionComplete_t*)&EventParams)->ConnectionHandle;
						Bluetooth_Connection.IsConnected      = true;

						BT_HCI_DEBUG(">> Connection Complete to Device %02X:%02X:%02X:%02X:%02X:%02X, Handle 0x%04x", 
								 Bluetooth_Connection.RemoteAddress[5], Bluetooth_Connection.RemoteAddress[4],
								 Bluetooth_Connection.RemoteAddress[3], Bluetooth_Connection.RemoteAddress[2],
								 Bluetooth_Connection.RemoteAddress[1], Bluetooth_Connection.RemoteAddress[0],
								 Bluetooth_Connection.ConnectionHandle);
						break;
					case EVENT_DISCONNECTION_COMPLETE:
						BT_HCI_DEBUG(">> Disconnection Complete", NULL);

						/* Device disconnected, indicate connection information no longer valid */
						Bluetooth_Connection.IsConnected = false;
						
						Bluetooth_HCIProcessingState = Bluetooth_Init;
						break;					
				}
			}
			
			Pipe_Freeze();
			
			break;
		case Bluetooth_Init:
			/* Reset the connection information structure to destroy any previous connection state */
			memset(&Bluetooth_Connection, 0x00, sizeof(Bluetooth_Connection));

			Bluetooth_HCIProcessingState = Bluetooth_Init_Reset; 
			break;
		case Bluetooth_Init_Reset:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
			{
				OpCode: {OGF: OGF_CTRLR_BASEBAND, OCF: OCF_CTRLR_BASEBAND_RESET},
				ParameterLength: 0,
			};
			
			BT_HCI_DEBUG("Enter State: Bluetooth_Init_Reset", NULL);

			/* Send the command to reset the bluetooth dongle controller */
			Bluetooth_SendHCICommand(NULL, 0);
			
			Bluetooth_HCINextState       = Bluetooth_Init_SetLocalName;
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_SetLocalName:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_CTRLR_BASEBAND, OCF: OCF_CTRLR_BASEBAND_WRITE_LOCAL_NAME},
					ParameterLength: 248,
				};

			BT_HCI_DEBUG("Enter State: Bluetooth_Init_SetLocalName", NULL);
			BT_HCI_DEBUG("-- Name: %s", Bluetooth_DeviceConfiguration.Name);

			/* Send the command to set the bluetooth dongle's name for other devices to see */
			Bluetooth_SendHCICommand(Bluetooth_DeviceConfiguration.Name, strlen(Bluetooth_DeviceConfiguration.Name));

			Bluetooth_HCINextState       = Bluetooth_Init_SetDeviceClass;
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_SetDeviceClass:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_CTRLR_BASEBAND, OCF: OCF_CTRLR_BASEBAND_WRITE_CLASS_OF_DEVICE},
					ParameterLength: 3,
				};

			BT_HCI_DEBUG("Enter State: Bluetooth_Init_SetDeviceClass", NULL);

			/* Send the command to set the class of the device for other devices to see */
			Bluetooth_SendHCICommand(&Bluetooth_DeviceConfiguration.Class, 3);

			Bluetooth_HCINextState       = Bluetooth_Init_WriteScanEnable;
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_WriteScanEnable:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
			{
				OpCode: {OGF: OGF_CTRLR_BASEBAND, OCF: OCF_CTRLR_BASEBAND_WRITE_SCAN_ENABLE},
				ParameterLength: 1,
			};
			
			BT_HCI_DEBUG("Enter State: Bluetooth_Init_WriteScanEnable", NULL);

			uint8_t Interval = BT_SCANMODE_InquiryAndPageScans;
			
			/* Send the command to set the remote device scanning mode */
			Bluetooth_SendHCICommand(&Interval, 1);
			
			Bluetooth_HCINextState       = Bluetooth_ProcessEvents;
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Conn_AcceptConnection:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_LINK_CONTROL, OCF: OCF_LINK_CONTROL_ACCEPT_CONNECTION_REQUEST},
					ParameterLength: sizeof(Bluetooth_HCICommand_AcceptConnectionRequest_t),
				};
			
			BT_HCI_DEBUG("Enter State: Bluetooth_Conn_AcceptConnection", NULL);

			/* Copy over the temporary BT device address saved from the Connection Request event, indicate slave
			   connection role */
			Bluetooth_HCICommand_AcceptConnectionRequest_t AcceptConnectionParams;
			memcpy(AcceptConnectionParams.RemoteAddress, Bluetooth_TempDeviceAddress,
			       sizeof(AcceptConnectionParams.RemoteAddress));
			AcceptConnectionParams.SlaveRole = true;

			/* Send the command to accept the remote connection request */
			Bluetooth_SendHCICommand(&AcceptConnectionParams, sizeof(Bluetooth_HCICommand_AcceptConnectionRequest_t));
			
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Conn_RejectConnection:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_LINK_CONTROL, OCF: OCF_LINK_CONTROL_REJECT_CONNECTION_REQUEST},
					ParameterLength: sizeof(Bluetooth_HCICommand_RejectConnectionRequest_t),
				};
			
			BT_HCI_DEBUG("Enter State: Bluetooth_Conn_RejectConnection", NULL);

			/* Copy over the temporary BT device address saved from the Connection Request event, indicate failure
			   to accept the connection due to limited device resources or incorrect device address */
			Bluetooth_HCICommand_RejectConnectionRequest_t RejectConnectionParams;
			memcpy(RejectConnectionParams.RemoteAddress, Bluetooth_TempDeviceAddress, sizeof(RejectConnectionParams.RemoteAddress));
			RejectConnectionParams.Reason = Bluetooth_Connection.IsConnected ? ERROR_LIMITED_RESOURCES : ERROR_UNACCEPTABLE_BDADDR;

			/* Send the command to reject the remote connection request */
			Bluetooth_SendHCICommand(&RejectConnectionParams, sizeof(Bluetooth_HCICommand_RejectConnectionRequest_t));
		
			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Conn_SendPINCode:
			HCICommandHeader = (Bluetooth_HCICommand_Header_t)
				{
					OpCode: {OGF: OGF_LINK_CONTROL, OCF: OCF_LINK_CONTROL_PIN_CODE_REQUEST_REPLY},
					ParameterLength: sizeof(Bluetooth_HCICommand_PinCodeResponse_t),
				};
			
			BT_HCI_DEBUG("Enter State: Bluetooth_Conn_SendPINCode", NULL);
			BT_HCI_DEBUG("-- PIN: %s", Bluetooth_DeviceConfiguration.PINCode);

			/* Copy over the temporary BT device address saved from the PIN Code Request event, copy over the
			   local PIN authentication code to the response */
			Bluetooth_HCICommand_PinCodeResponse_t PINCodeRequestParams;
			memcpy(PINCodeRequestParams.RemoteAddress, Bluetooth_TempDeviceAddress, sizeof(PINCodeRequestParams.RemoteAddress));
			PINCodeRequestParams.PINCodeLength = strlen(Bluetooth_DeviceConfiguration.PINCode);
			memcpy(PINCodeRequestParams.PINCode, Bluetooth_DeviceConfiguration.PINCode, sizeof(PINCodeRequestParams.PINCode));
			
			/* Send the command to transmit the device's local PIN number for authentication */
			Bluetooth_SendHCICommand(&PINCodeRequestParams, sizeof(Bluetooth_HCICommand_PinCodeResponse_t));

			Bluetooth_HCIProcessingState = Bluetooth_ProcessEvents;
			break;
	}
}
