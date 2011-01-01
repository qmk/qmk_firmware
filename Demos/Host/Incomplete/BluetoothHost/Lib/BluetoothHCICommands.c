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
 *  Bluetooth HCI layer management code. This module manages the overall
 *  Bluetooth stack connection state to and from other devices, processes
 *  received events from the Bluetooth controller, and issues commands to
 *  modify the controller's configuration, such as the broadcast name of the
 *  device.
 */

/*
	TODO: Add local to remote device connections
 */

#define  INCLUDE_FROM_BLUETOOTHHCICOMMANDS_C
#include "BluetoothHCICommands.h"

/** Temporary Bluetooth Device Address, for HCI responses which much include the destination address */
static uint8_t Bluetooth_TempDeviceAddress[6];

/** Bluetooth HCI processing task. This task should be called repeatedly the main Bluetooth
 *  stack task to manage the HCI processing state.
 */
void Bluetooth_HCITask(void)
{
	BT_HCICommand_Header_t HCICommandHeader;

	switch (Bluetooth_State.CurrentHCIState)
	{
		case Bluetooth_ProcessEvents:
			Pipe_SelectPipe(BLUETOOTH_EVENTS_PIPE);
			Pipe_Unfreeze();

			if (Pipe_IsReadWriteAllowed())
			{
				BT_HCIEvent_Header_t HCIEventHeader;

				/* Read in the event header to fetch the event code and payload length */
				Pipe_Read_Stream_LE(&HCIEventHeader, sizeof(HCIEventHeader));

				/* Create a temporary buffer for the event parameters */
				uint8_t EventParams[HCIEventHeader.ParameterLength];

				/* Read in the event parameters into the temporary buffer */
				Pipe_Read_Stream_LE(&EventParams, HCIEventHeader.ParameterLength);
				Pipe_ClearIN();

				BT_HCI_DEBUG(1, "Event Received (0x%02X)", HCIEventHeader.EventCode);

				switch (HCIEventHeader.EventCode)
				{
					case EVENT_COMMAND_COMPLETE:
						BT_HCI_DEBUG(1, "<< Command Complete");

						/* Check which operation was completed in case we need to process the even parameters */
						switch (((BT_HCIEvent_CommandComplete_t*)&EventParams)->Opcode)
						{
							case (OGF_CTRLR_INFORMATIONAL | OCF_CTRLR_INFORMATIONAL_READBDADDR):
								/* A READ BDADDR command completed, copy over the local device's BDADDR from the response */
								memcpy(Bluetooth_State.LocalBDADDR,
								       &((BT_HCIEvent_CommandComplete_t*)&EventParams)->ReturnParams[1],
								       sizeof(Bluetooth_State.LocalBDADDR));
								break;
						}

						Bluetooth_State.CurrentHCIState = Bluetooth_State.NextHCIState;
						break;
					case EVENT_COMMAND_STATUS:
						BT_HCI_DEBUG(1, "<< Command Status");
						BT_HCI_DEBUG(2, "-- Status Code: 0x%02X", (((BT_HCIEvent_CommandStatus_t*)&EventParams)->Status));

						/* If the execution of a command failed, reset the stack */
						if (((BT_HCIEvent_CommandStatus_t*)&EventParams)->Status)
						  Bluetooth_State.CurrentHCIState = Bluetooth_Init;
						break;
					case EVENT_CONNECTION_REQUEST:
						BT_HCI_DEBUG(1, "<< Connection Request");
						BT_HCI_DEBUG(2, "-- Link Type: 0x%02X", (((BT_HCIEvent_ConnectionRequest_t*)&EventParams)->LinkType));

						/* Need to store the remote device's BT address in a temporary buffer for later use */
						memcpy(Bluetooth_TempDeviceAddress,
						       &((BT_HCIEvent_ConnectionRequest_t*)&EventParams)->RemoteAddress,
						       sizeof(Bluetooth_TempDeviceAddress));

						bool IsACLConnection = (((BT_HCIEvent_ConnectionRequest_t*)&EventParams)->LinkType == 0x01);

						/* Only accept the connection if it is a ACL (data) connection, a device is not already connected
						   and the user application has indicated that the connection should be allowed */
						Bluetooth_State.CurrentHCIState = (Bluetooth_Connection.IsConnected || !(IsACLConnection) ||
													      !(Bluetooth_ConnectionRequest(Bluetooth_TempDeviceAddress))) ?
													      Bluetooth_Conn_RejectConnection : Bluetooth_Conn_AcceptConnection;

						BT_HCI_DEBUG(2, "-- Connection %S", (Bluetooth_State.CurrentHCIState == Bluetooth_Conn_RejectConnection) ?
						                                     PSTR("REJECTED") : PSTR("ACCEPTED"));

						break;
					case EVENT_PIN_CODE_REQUEST:
						BT_HCI_DEBUG(1, "<< Pin Code Request");

						/* Need to store the remote device's BT address in a temporary buffer for later use */
						memcpy(Bluetooth_TempDeviceAddress,
						       &((BT_HCIEvent_PinCodeReq_t*)&EventParams)->RemoteAddress,
						       sizeof(Bluetooth_TempDeviceAddress));

						Bluetooth_State.CurrentHCIState = Bluetooth_Conn_SendPINCode;
						break;
					case EVENT_LINK_KEY_REQUEST:
						BT_HCI_DEBUG(1, "<< Link Key Request");

						/* Need to store the remote device's BT address in a temporary buffer for later use */
						memcpy(Bluetooth_TempDeviceAddress,
						       &((BT_HCIEvent_LinkKeyReq_t*)&EventParams)->RemoteAddress,
						       sizeof(Bluetooth_TempDeviceAddress));

						Bluetooth_State.CurrentHCIState = Bluetooth_Conn_SendLinkKeyNAK;
						break;
					case EVENT_CONNECTION_COMPLETE:
						BT_HCI_DEBUG(1, "<< Connection Complete");
						BT_HCI_DEBUG(2, "-- Handle: 0x%04X", ((BT_HCIEvent_ConnectionComplete_t*)&EventParams)->ConnectionHandle);

						/* Need to store the remote device's BT address in a temporary buffer for later use */
						memcpy(Bluetooth_Connection.RemoteAddress,
						       &((BT_HCIEvent_ConnectionComplete_t*)&EventParams)->RemoteAddress,
						       sizeof(Bluetooth_TempDeviceAddress));

						/* Store the created connection handle and indicate that the connection has been established */
						Bluetooth_Connection.ConnectionHandle = ((BT_HCIEvent_ConnectionComplete_t*)&EventParams)->ConnectionHandle;
						Bluetooth_Connection.IsConnected      = true;

						Bluetooth_ConnectionComplete();
						break;
					case EVENT_DISCONNECTION_COMPLETE:
						BT_HCI_DEBUG(1, "<< Disconnection Complete");

						/* Device disconnected, indicate connection information no longer valid */
						Bluetooth_Connection.IsConnected = false;

						Bluetooth_DisconnectionComplete();
						break;
				}
			}

			Pipe_Freeze();

			break;
		case Bluetooth_Init:
			BT_HCI_DEBUG(1, "# Init");

			Bluetooth_State.IsInitialized = false;

			/* Reset the connection information structure to destroy any previous connection state */
			memset(&Bluetooth_Connection, 0x00, sizeof(Bluetooth_Connection));

			Bluetooth_State.CurrentHCIState = Bluetooth_Init_Reset;
			break;
		case Bluetooth_Init_Reset:
			BT_HCI_DEBUG(1, "# Reset");

			HCICommandHeader = (BT_HCICommand_Header_t)
			{
				OpCode: (OGF_CTRLR_BASEBAND | OCF_CTRLR_BASEBAND_RESET),
				ParameterLength: 0,
			};

			/* Send the command to reset the Bluetooth dongle controller */
			Bluetooth_SendHCICommand(&HCICommandHeader, NULL, 0);

			Bluetooth_State.NextHCIState    = Bluetooth_Init_ReadBufferSize;
			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_ReadBufferSize:
			BT_HCI_DEBUG(1, "# Read Buffer Size");

			HCICommandHeader = (BT_HCICommand_Header_t)
			{
				OpCode: (OGF_CTRLR_INFORMATIONAL | OCF_CTRLR_INFORMATIONAL_READBUFFERSIZE),
				ParameterLength: 0,
			};

			/* Send the command to read the Bluetooth buffer size (mandatory before device sends any data) */
			Bluetooth_SendHCICommand(&HCICommandHeader, NULL, 0);

			Bluetooth_State.NextHCIState    = Bluetooth_Init_GetBDADDR;
			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_GetBDADDR:
			BT_HCI_DEBUG(1, "# Get BDADDR");

			HCICommandHeader = (BT_HCICommand_Header_t)
			{
				OpCode: (OGF_CTRLR_INFORMATIONAL | OCF_CTRLR_INFORMATIONAL_READBDADDR),
				ParameterLength: 0,
			};

			/* Send the command to retrieve the BDADDR of the inserted Bluetooth dongle */
			Bluetooth_SendHCICommand(&HCICommandHeader, NULL, 0);

			Bluetooth_State.NextHCIState    = Bluetooth_Init_SetLocalName;
			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_SetLocalName:
			BT_HCI_DEBUG(1, "# Set Local Name");

			HCICommandHeader = (BT_HCICommand_Header_t)
				{
					OpCode: (OGF_CTRLR_BASEBAND | OCF_CTRLR_BASEBAND_WRITE_LOCAL_NAME),
					ParameterLength: 248,
				};

			/* Send the command to set the Bluetooth dongle's name for other devices to see */
			Bluetooth_SendHCICommand(&HCICommandHeader, Bluetooth_DeviceConfiguration.Name, strlen(Bluetooth_DeviceConfiguration.Name));

			Bluetooth_State.NextHCIState    = Bluetooth_Init_SetDeviceClass;
			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_SetDeviceClass:
			BT_HCI_DEBUG(1, "# Set Device Class");

			HCICommandHeader = (BT_HCICommand_Header_t)
				{
					OpCode: (OGF_CTRLR_BASEBAND | OCF_CTRLR_BASEBAND_WRITE_CLASS_OF_DEVICE),
					ParameterLength: 3,
				};

			/* Send the command to set the class of the device for other devices to see */
			Bluetooth_SendHCICommand(&HCICommandHeader, &Bluetooth_DeviceConfiguration.Class, 3);

			Bluetooth_State.NextHCIState    = Bluetooth_Init_WriteScanEnable;
			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_WriteScanEnable:
			BT_HCI_DEBUG(1, "# Write Scan Enable");

			HCICommandHeader = (BT_HCICommand_Header_t)
			{
				OpCode: (OGF_CTRLR_BASEBAND | OCF_CTRLR_BASEBAND_WRITE_SCAN_ENABLE),
				ParameterLength: 1,
			};

			uint8_t Interval = BT_SCANMODE_InquiryAndPageScans;

			/* Send the command to set the remote device scanning mode */
			Bluetooth_SendHCICommand(&HCICommandHeader, &Interval, 1);

			Bluetooth_State.NextHCIState    = Bluetooth_Init_FinalizeInit;
			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Init_FinalizeInit:
			Bluetooth_State.IsInitialized = true;

			/* Fire the user application callback to indicate that the stack is now fully initialized */
			Bluetooth_StackInitialized();

			Bluetooth_State.NextHCIState    = Bluetooth_ProcessEvents;
			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Conn_AcceptConnection:
			BT_HCI_DEBUG(1, "# Accept Connection");

			HCICommandHeader = (BT_HCICommand_Header_t)
				{
					OpCode: (OGF_LINK_CONTROL | OCF_LINK_CONTROL_ACCEPT_CONNECTION_REQUEST),
					ParameterLength: sizeof(BT_HCICommand_AcceptConnectionReq_t),
				};

			/* Copy over the temporary BT device address saved from the Connection Request event, indicate slave
			   connection role */
			BT_HCICommand_AcceptConnectionReq_t AcceptConnectionParams;
			memcpy(AcceptConnectionParams.RemoteAddress, Bluetooth_TempDeviceAddress,
			       sizeof(AcceptConnectionParams.RemoteAddress));
			AcceptConnectionParams.SlaveRole = true;

			/* Send the command to accept the remote connection request */
			Bluetooth_SendHCICommand(&HCICommandHeader, &AcceptConnectionParams, sizeof(BT_HCICommand_AcceptConnectionReq_t));

			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Conn_RejectConnection:
			BT_HCI_DEBUG(1, "# Reject Connection");

			HCICommandHeader = (BT_HCICommand_Header_t)
				{
					OpCode: (OGF_LINK_CONTROL | OCF_LINK_CONTROL_REJECT_CONNECTION_REQUEST),
					ParameterLength: sizeof(BT_HCICommand_RejectConnectionReq_t),
				};

			/* Copy over the temporary BT device address saved from the Connection Request event, indicate failure
			   to accept the connection due to limited device resources or incorrect device address */
			BT_HCICommand_RejectConnectionReq_t RejectConnectionParams;
			memcpy(RejectConnectionParams.RemoteAddress, Bluetooth_TempDeviceAddress, sizeof(RejectConnectionParams.RemoteAddress));
			RejectConnectionParams.Reason = Bluetooth_Connection.IsConnected ? ERROR_LIMITED_RESOURCES : ERROR_UNACCEPTABLE_BDADDR;

			/* Send the command to reject the remote connection request */
			Bluetooth_SendHCICommand(&HCICommandHeader, &RejectConnectionParams, sizeof(BT_HCICommand_RejectConnectionReq_t));

			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Conn_SendPINCode:
			BT_HCI_DEBUG(1, "# Send Pin Code");

			HCICommandHeader = (BT_HCICommand_Header_t)
				{
					OpCode: (OGF_LINK_CONTROL | OCF_LINK_CONTROL_PIN_CODE_REQUEST_REPLY),
					ParameterLength: sizeof(BT_HCICommand_PinCodeResp_t),
				};

			/* Copy over the temporary BT device address saved from the PIN Code Request event, copy over the
			   local PIN authentication code to the response */
			BT_HCICommand_PinCodeResp_t PINCodeRequestParams;
			memcpy(PINCodeRequestParams.RemoteAddress, Bluetooth_TempDeviceAddress, sizeof(PINCodeRequestParams.RemoteAddress));
			PINCodeRequestParams.PINCodeLength = strlen(Bluetooth_DeviceConfiguration.PINCode);
			memcpy(PINCodeRequestParams.PINCode, Bluetooth_DeviceConfiguration.PINCode, sizeof(PINCodeRequestParams.PINCode));

			/* Send the command to transmit the device's local PIN number for authentication */
			Bluetooth_SendHCICommand(&HCICommandHeader, &PINCodeRequestParams, sizeof(BT_HCICommand_PinCodeResp_t));

			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
		case Bluetooth_Conn_SendLinkKeyNAK:
			BT_HCI_DEBUG(1, "# Send Link Key NAK");

			HCICommandHeader = (BT_HCICommand_Header_t)
				{
					OpCode: (OGF_LINK_CONTROL | OCF_LINK_CONTROL_LINK_KEY_REQUEST_NEG_REPLY),
					ParameterLength: sizeof(BT_HCICommand_LinkKeyNAKResp_t),
				};

			/* Copy over the temporary BT device address saved from the Link Key Request event */
			BT_HCICommand_LinkKeyNAKResp_t LinkKeyNAKParams;
			memcpy(LinkKeyNAKParams.RemoteAddress, Bluetooth_TempDeviceAddress, sizeof(LinkKeyNAKParams.RemoteAddress));

			/* Send the command to transmit the link key NAK to the receiver */
			Bluetooth_SendHCICommand(&HCICommandHeader, &LinkKeyNAKParams, sizeof(BT_HCICommand_LinkKeyNAKResp_t));

			Bluetooth_State.CurrentHCIState = Bluetooth_ProcessEvents;
			break;
	}
}

/** Sends a Bluetooth HCI control command to the attached Bluetooth device.
 *
 *  \param[in] HCICommandHeader  HCI command header to send to the attached device
 *  \param[in] Parameters        Pointer to the source of the control parameters (if any)
 *  \param[in] ParameterLength   Length of the parameters to send in bytes
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum.
 */
static uint8_t Bluetooth_SendHCICommand(const BT_HCICommand_Header_t* const HCICommandHeader,
                                        const void* Parameters,
                                        const uint16_t ParameterLength)
{
	/* Need to reserve the amount of bytes given in the header for the complete payload */
	uint8_t CommandBuffer[sizeof(BT_HCICommand_Header_t) + HCICommandHeader->ParameterLength];

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_DEVICE),
			.bRequest      = 0,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = sizeof(CommandBuffer)
		};

	/* Copy over the HCI command header to the allocated buffer */
	memcpy(CommandBuffer, HCICommandHeader, sizeof(BT_HCICommand_Header_t));

	/* Zero out the parameter section of the response so that all padding bytes are known to be zero */
	memset(&CommandBuffer[sizeof(BT_HCICommand_Header_t)], 0x00, HCICommandHeader->ParameterLength);

	/* Copy over the command parameters (if any) to the command buffer - note, the number of actual source parameter bytes
	   may differ to those in the header; any difference in length is filled with 0x00 padding bytes */
	memcpy(&CommandBuffer[sizeof(BT_HCICommand_Header_t)], Parameters, ParameterLength);

	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(CommandBuffer);
}

