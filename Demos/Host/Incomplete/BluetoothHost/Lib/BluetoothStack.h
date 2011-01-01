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
 *  Header file for BluetoothStack.c.
 */

#ifndef _BLUETOOTH_STACK_
#define _BLUETOOTH_STACK_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include "../ConfigDescriptor.h"

	/* Macros: */
		#define BLUETOOTH_MAX_OPEN_CHANNELS    6

		#define CHANNEL_PSM_SDP                0x0001
		#define CHANNEL_PSM_UDP                0x0002
		#define CHANNEL_PSM_RFCOMM             0x0003
		#define CHANNEL_PSM_TCP                0x0004
		#define CHANNEL_PSM_IP                 0x0009
		#define CHANNEL_PSM_FTP                0x000A
		#define CHANNEL_PSM_HTTP               0x000C
		#define CHANNEL_PSM_UPNP               0x0010
		#define CHANNEL_PSM_HIDP               0x0011

		#define CHANNEL_SEARCH_LOCALNUMBER     0
		#define CHANNEL_SEARCH_REMOTENUMBER    1
		#define CHANNEL_SEARCH_PSM             2

		#define MAXIMUM_CHANNEL_MTU            255

	/* Enums: */
		/** Enum for the possible states for a Bluetooth ACL channel. */
		enum BT_ChannelStates_t
		{
			BT_Channel_Closed                = 0, /**< Channel is closed and inactive. No data may be sent or received. */
			BT_Channel_WaitConnect           = 1, /**< A connection request has been received, but a response has not been sent. */
			BT_Channel_WaitConnectRsp        = 2, /**< A connection request has been sent, but a response has not been received. */
			BT_Channel_Config_WaitConfig     = 3, /**< Channel has been connected, but not yet configured on either end. */
			BT_Channel_Config_WaitSendConfig = 4, /**< Channel configuration has been received and accepted, but not yet sent. */
			BT_Channel_Config_WaitReqResp    = 5, /**< Channel configuration has been sent but not responded to, and a configuration
			                                       *   request from the remote end has not yet been received.
			                                       */
			BT_Channel_Config_WaitResp       = 6, /**< Channel configuration has been sent but not accepted, but a configuration request
			                                       *   from the remote end has been accepted.
			                                       */
			BT_Channel_Config_WaitReq        = 7, /**< Channel configuration has been sent and accepted, but a configuration request
			                                       *   from the remote end has not yet been accepted.
			                                       */
			BT_Channel_Open                  = 8, /**< Channel is open and ready to send or receive data */
			BT_Channel_WaitDisconnect        = 9, /**< A disconnection request has been sent, but not yet acknowledged. */
		};

		/** Enum for the possible error codes returned by the \ref Bluetooth_SendPacket() function. */
		enum BT_SendPacket_ErrorCodes_t
		{
			BT_SENDPACKET_NoError            = 0, /**< The packet was sent successfully. */
			BT_SENDPACKET_NotConnected       = 1, /**< The Bluetooth stack is not currently connected to a remote device. */
			BT_SENDPACKET_ChannelNotOpen     = 2, /**< The given channel is not currently in the Open state. */
		};

	/* Type Defines: */
		/** Type define for a Bluetooth ACL channel information structure. This structure contains all the relevant
		 *  information on an ACL channel for data transmission and reception by the stack.
		 */
		typedef struct
		{
			uint8_t  State; /**< Current channel state, a value from the \ref BT_ChannelStates_t enum. */
			uint16_t LocalNumber; /**< Local channel number on the device. */
			uint16_t RemoteNumber; /**< Remote channel number on the connected device. */
			uint16_t PSM; /**< Protocol used on the channel. */
			uint16_t LocalMTU; /**< MTU of data sent from the connected device to the local device. */
			uint16_t RemoteMTU; /**< MTU of data sent from the local device to the connected device. */
		} Bluetooth_Channel_t;

		/** Type define for a Bluetooth device connection information structure. This structure contains all the
		 *  information needed to maintain a connection to a remote Bluetooth device via the Bluetooth stack.
		 */
		typedef struct
		{
			bool                IsConnected; /**< Indicates if the stack is currently connected to a remote device - if this value is
			                                  *   false, the remaining elements are invalid.
											  */
			uint16_t            ConnectionHandle; /**< Connection handle to the remote device, used internally in the stack. */
			uint8_t             RemoteAddress[6]; /**< Bluetooth device address of the attached remote device. */
			Bluetooth_Channel_t Channels[BLUETOOTH_MAX_OPEN_CHANNELS]; /**< Channel information structures for the connection. */
			uint8_t             SignalingIdentifier; /**< Next Signaling Channel unique command sequence identifier. */
		} Bluetooth_Connection_t;

		/** Local Bluetooth device information structure, for the defining of local device characteristics for the Bluetooth stack. */
		typedef struct
		{
			uint32_t Class; /**< Class of the local device, a mask of DEVICE_CLASS_* masks. */
			char     PINCode[16]; /**< Pin code required to send or receive in order to authenticate with a remote device. */
			char     Name[]; /**< Name of the local Bluetooth device, up to 248 characters. */
		} Bluetooth_Device_t;

		/** Bluetooth stack state information structure, for the containment of the Bluetooth stack state. The values in
		 *  this structure are set by the Bluetooth stack internally, and should all be treated as read only by the user
		 *  application.
		 */
		typedef struct
		{
			uint8_t CurrentHCIState; /**< Current HCI state machine state. */
			uint8_t NextHCIState; /**< Next HCI state machine state to progress to once the currently issued command completes. */
			bool    IsInitialized; /**< Indicates if the Bluetooth stack is currently initialized and ready for connections
			                        *   to or from a remote Bluetooth device.
			                        */
			uint8_t LocalBDADDR[6]; /**< Local Bluetooth adapter's BDADDR, valid when the stack is fully initialized. */
		} Bluetooth_Stack_State_t;

	/* Includes: */
		#include "BluetoothHCICommands.h"
		#include "BluetoothACLPackets.h"

	/* Function Prototypes: */
		void Bluetooth_Stack_Init(void);
		void Bluetooth_Stack_USBTask(void);

		void                 Bluetooth_StackInitialized(void);
		bool                 Bluetooth_ConnectionRequest(const uint8_t* RemoteAddress);
		void                 Bluetooth_ConnectionComplete(void);
		void                 Bluetooth_DisconnectionComplete(void);
		bool                 Bluetooth_ChannelConnectionRequest(const uint16_t PSM);
		void                 Bluetooth_PacketReceived(void* Data, uint16_t DataLen,
		                                              Bluetooth_Channel_t* const ACLChannel);
		void                 Bluetooth_ChannelOpened(Bluetooth_Channel_t* const ACLChannel);

		Bluetooth_Channel_t* Bluetooth_GetChannelData(const uint16_t SearchValue,
		                                              const uint8_t SearchKey);
		Bluetooth_Channel_t* Bluetooth_OpenChannel(const uint16_t PSM);
		void                 Bluetooth_CloseChannel(Bluetooth_Channel_t* const ACLChannel);
		uint8_t              Bluetooth_SendPacket(void* Data,
		                                          uint16_t DataLen,
		                                          Bluetooth_Channel_t* const ACLChannel);

	/* External Variables: */
		extern Bluetooth_Device_t      Bluetooth_DeviceConfiguration;
		extern Bluetooth_Connection_t  Bluetooth_Connection;
		extern Bluetooth_Stack_State_t Bluetooth_State;

#endif

