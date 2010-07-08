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
 *  Bluetooth stack event callback handlers. This module handles the callback events that are
 *  thrown from the Bluetooth stack in response to changes in the connection and channel
 *  states.
 */

#include "BluetoothEvents.h"

/** Bluetooth RFCOMM channel structure - used to send and receive RFCOMM data between the local and remote
 *  device once a RFCOMM channel has been opened.
 */
Bluetooth_Channel_t* RFCOMMChannel = NULL;


/** Bluetooth stack callback event for when the Bluetooth stack has fully initialized using the attached
 *  Bluetooth dongle.
 */
void Bluetooth_StackInitialized(void)
{
	printf_P(PSTR("Stack initialized with local address %02X:%02X:%02X:%02X:%02X:%02X.\r\n"),
	         Bluetooth_State.LocalBDADDR[5], Bluetooth_State.LocalBDADDR[4], Bluetooth_State.LocalBDADDR[3],
	         Bluetooth_State.LocalBDADDR[2], Bluetooth_State.LocalBDADDR[1], Bluetooth_State.LocalBDADDR[0]);
			 
	/* Reinitialize the services placed on top of the Bluetooth stack ready for new connections */
	RFCOMM_Initialize();
}

/** Bluetooth stack callback event for a Bluetooth connection request. When this callback fires, the
 *  user application must indicate if the connection is to be allowed or rejected.
 *
 *  \param[in] RemoteAddress  Bluetooth address of the remote device attempting the connection
 *
 *  \return Boolean true to accept the connection, false to reject it
 */
bool Bluetooth_ConnectionRequest(const uint8_t* RemoteAddress)
{
	printf_P(PSTR("Connection Request from Device %02X:%02X:%02X:%02X:%02X:%02X.\r\n"),
	         RemoteAddress[5], RemoteAddress[4], RemoteAddress[3], RemoteAddress[2],
	         RemoteAddress[1], RemoteAddress[0]);

	/* Always accept connections from remote devices */
	return true;
}

/** Bluetooth stack callback event for a completed Bluetooth connection. When this callback is made,
 *  the connection information can be accessed through the global \ref Bluetooth_Connection structure.
 */
void Bluetooth_ConnectionComplete(void)
{
	printf_P(PSTR("Connection Complete to Device %02X:%02X:%02X:%02X:%02X:%02X.\r\n"), 
	         Bluetooth_Connection.RemoteAddress[5], Bluetooth_Connection.RemoteAddress[4],
	         Bluetooth_Connection.RemoteAddress[3], Bluetooth_Connection.RemoteAddress[2],
	         Bluetooth_Connection.RemoteAddress[1], Bluetooth_Connection.RemoteAddress[0]);

	LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
}

/** Bluetooth stack callback event for a completed Bluetooth disconnection. When this callback is made,
 *  the connection information in the global \ref Bluetooth_Connection structure is invalidated with the
 *  exception of the RemoteAddress element, which can be used to determine the address of the device that
 *  was disconnected.
 */
void Bluetooth_DisconnectionComplete(void)
{
	printf_P(PSTR("Disconnection Complete to Device %02X:%02X:%02X:%02X:%02X:%02X.\r\n"), 
	         Bluetooth_Connection.RemoteAddress[5], Bluetooth_Connection.RemoteAddress[4],
	         Bluetooth_Connection.RemoteAddress[3], Bluetooth_Connection.RemoteAddress[2],
	         Bluetooth_Connection.RemoteAddress[1], Bluetooth_Connection.RemoteAddress[0]);

	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Bluetooth stack callback event for a Bluetooth ACL Channel connection request. When is callback fires,
 *  the user application must indicate if the channel connection should be rejected or not, based on the 
 *  protocol (PSM) value of the requested channel.
 *
 *  \param[in] PSM  Protocol PSM value for the requested channel
 *
 *  \return Boolean true to accept the channel connection request, false to reject it
 */
bool Bluetooth_ChannelConnectionRequest(const uint16_t PSM)
{
	/* Always accept channel connection requests regardless of PSM */
	return true;
}

/** Bluetooth stack callback event for when a Bluetooth ACL channel has been fully created and configured,
 *  either at the request of the local device, or the remote device.
 *
 *  \param[in] Channel  Bluetooth ACL data channel information structure for the channel that can now be used
 */
void Bluetooth_ChannelOpened(Bluetooth_Channel_t* const Channel)
{
	/* Save the RFCOMM channel for later use when we want to send RFCOMM data */
	if (Channel->PSM == CHANNEL_PSM_RFCOMM)
	  RFCOMMChannel = Channel;
}

/** Bluetooth stack callback event for a non-signal ACL packet reception. This callback fires once a connection
 *  to a remote Bluetooth device has been made, and the remote device has sent a non-signalling ACL packet.
 *
 *  \param[in] Data     Pointer to a buffer where the received data is stored
 *  \param[in] DataLen  Length of the packet data, in bytes
 *  \param[in] Channel  Bluetooth ACL data channel information structure for the packet's destination channel
 */
void Bluetooth_PacketReceived(void* Data, uint16_t DataLen, Bluetooth_Channel_t* const Channel)
{
	/* Run the correct packet handler based on the received packet's PSM, which indicates the service being carried */
	switch (Channel->PSM)
	{
		case CHANNEL_PSM_SDP:
			/* Service Discovery Protocol packet */
			SDP_ProcessPacket(Data, Channel);
			break;
		case CHANNEL_PSM_RFCOMM:
			/* RFCOMM (Serial Port) Protocol packet */
			RFCOMM_ProcessPacket(Data, Channel);
			break;
		default:
			/* Unknown Protocol packet */
			printf_P(PSTR("Unknown Packet Received (Channel 0x%04X, PSM: 0x%02X, Len: 0x%04X):\r\n"),
			              Channel->LocalNumber, Channel->PSM, DataLen);			
			break;
	}
}
