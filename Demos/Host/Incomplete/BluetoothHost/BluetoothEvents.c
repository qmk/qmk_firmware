/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.
              
  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** Pointer to the opened Bluetooth ACL channel structure for RFCOMM, used to send and receive data between the
 *  local and remote device once a RFCOMM channel has been opened.
 */
Bluetooth_Channel_t* SerialChannel_ACL    = NULL;

/** Pointer to the opened RFCOMM logical channel between local and remote device, once a RFCOMM ACL channel has been
 *  negotiated and a logical RFCOMM channel requested.
 */
RFCOMM_Channel_t*    SerialChannel_RFCOMM = NULL;

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
	/* Only accept connections for channels that will be used for RFCOMM or SDP data */
	return ((PSM == CHANNEL_PSM_RFCOMM) || (PSM == CHANNEL_PSM_SDP));
}

/** Bluetooth stack callback event for when a Bluetooth ACL channel has been fully created and configured,
 *  either at the request of the local device, or the remote device.
 *
 *  \param[in] ACLChannel  Bluetooth ACL data channel information structure for the channel that can now be used
 */
void Bluetooth_ChannelOpened(Bluetooth_Channel_t* const ACLChannel)
{
	/* Save the RFCOMM channel for later use when we want to send RFCOMM data */
	if (ACLChannel->PSM == CHANNEL_PSM_RFCOMM)
	  SerialChannel_ACL = ACLChannel;
}

/** Bluetooth stack callback event for a non-signal ACL packet reception. This callback fires once a connection
 *  to a remote Bluetooth device has been made, and the remote device has sent a non-signaling ACL packet.
 *
 *  \param[in] Data        Pointer to a buffer where the received data is stored
 *  \param[in] DataLen     Length of the packet data, in bytes
 *  \param[in] ACLChannel  Bluetooth ACL data channel information structure for the packet's destination channel
 */
void Bluetooth_PacketReceived(void* Data, uint16_t DataLen, Bluetooth_Channel_t* const ACLChannel)
{
	/* Run the correct packet handler based on the received packet's PSM, which indicates the service being carried */
	switch (ACLChannel->PSM)
	{
		case CHANNEL_PSM_SDP:
			/* Service Discovery Protocol packet */
			SDP_ProcessPacket(Data, ACLChannel);
			break;
		case CHANNEL_PSM_RFCOMM:
			/* RFCOMM (Serial Port) Protocol packet */
			RFCOMM_ProcessPacket(Data, ACLChannel);
			break;
	}
}

/** RFCOMM layer callback for event for when a RFCOMM logical channel has been fully opened and configured between
 *  the local and remote device. Once open, this RFCOMM channel can be read from and written to freely until is it
 *  closed by either end.
 *
 *  \param[in] RFCOMMChannel  RFCOMM channel that was opened
 */ 
void RFCOMM_ChannelOpened(RFCOMM_Channel_t* const RFCOMMChannel)
{
	/* Save the serial port RFCOMM logical channel for later use */
	SerialChannel_RFCOMM = RFCOMMChannel;
}

/** RFCOMM layer callback event for when a packet is received on an open RFCOMM channel.
 *
 *  \param[in] ACLChannel  RFCOMM ACL channel that the data was directed to
 *  \param[in] DataLen     Length of the received data, in bytes
 *  \param[in] Data        Pointer to a buffer where the received data is stored
 */
void RFCOMM_DataReceived(RFCOMM_Channel_t* const ACLChannel, uint16_t DataLen, const uint8_t* Data)
{
	/* Write the received bytes to the serial port */
	for (uint8_t i = 0; i < DataLen; i++)
	  putchar(Data[i]);
	
	/* Echo the data back to the sending device */
	RFCOMM_SendData(DataLen, Data, SerialChannel_RFCOMM, SerialChannel_ACL);
}

/** RFCOMM layer callback event for when the remote device has updated the channel terminal control signals
 *  for a particular RFCOMM channel.
 *
 *  \param[in] RFCOMMChannel  RFCOMM logical channel whose signals were altered
 */ 
void RFCOMM_ChannelSignalsReceived(RFCOMM_Channel_t* const RFCOMMChannel)
{
	// Currently do nothing in response to the remote device sending new terminal control signals
}

