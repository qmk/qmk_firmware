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

#ifndef _BLUETOOTH_STACK_
#define _BLUETOOTH_STACK_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>
		
		#include "BluetoothHost.h"
		
	/* Macros: */
		#define BLUETOOTH_DATA_IN_PIPE                   1
		#define BLUETOOTH_DATA_OUT_PIPE                  2
		#define BLUETOOTH_EVENTS_PIPE                    3

		#define BLUETOOTH_MAX_OPEN_CHANNELS              2
		#define BLUETOOTH_CHANNELNUMBER_BASEOFFSET       0x0040
		
		#define CHANNEL_PSM_SERVICEDISCOVERY             0x0001
		#define CHANNEL_PSM_RFCOMM                       0x0003
		
		#define MAXIMUM_CHANNEL_MTU                      255
		
	/* Enums: */
		enum BT_ChannelStates_t
		{
			Channel_Closed                = 0,
			Channel_WaitConnect           = 1,
			Channel_WaitConnectRsp        = 2,
			Channel_Config_WaitConfig     = 3,
			Channel_Config_WaitSendConfig = 4,
			Channel_Config_WaitReqResp    = 5,
			Channel_Config_WaitResp       = 6,
			Channel_Config_WaitReq        = 7,
			Channel_Open                  = 8,
			Channel_WaitDisconnect        = 9,
		};

		enum Endpoint_ControlStream_RW_ErrorCodes_t
		{
			BT_SENDPACKET_NoError            = 0,
			BT_SENDPACKET_NotConnected       = 1,
			BT_SENDPACKET_ChannelNotOpen     = 2,
		};

	/* Type Defines: */
		typedef struct
		{
			uint8_t  State;
			uint16_t LocalNumber;
			uint16_t RemoteNumber;
			uint16_t PSM;
			uint16_t LocalMTU;
			uint16_t RemoteMTU;
		} Bluetooth_Channel_t;

		typedef struct
		{
			bool                IsConnected;
			uint16_t            ConnectionHandle;
			uint8_t             RemoteAddress[6];
			Bluetooth_Channel_t Channels[BLUETOOTH_MAX_OPEN_CHANNELS];
			uint8_t             SignallingIdentifier;
		} Bluetooth_Connection_t;
		
		typedef struct
		{
			uint32_t Class;
			char     PINCode[16];
			char     Name[];
		} Bluetooth_Device_t;
	
	/* Includes: */
		#include "BluetoothHCICommands.h"
		#include "BluetoothACLPackets.h"		
		
	/* Function Prototypes: */
		Bluetooth_Channel_t* Bluetooth_GetChannelData(uint16_t ChannelNumber, bool SearchByRemoteChannel);
		Bluetooth_Channel_t* Bluetooth_InitChannelData(uint16_t RemoteChannelNumber, uint16_t PSM);
		
		void Bluetooth_Stack_Init(void);
		void Bluetooth_Stack_USBTask(void);

		bool    Bluetooth_ConnectionRequest(uint8_t* RemoteAddress);
		void    Bluetooth_ConnectionComplete(void);
		void    Bluetooth_DisconnectionComplete(void);
		void    Bluetooth_PacketReceived(uint16_t* PacketLength, Bluetooth_Channel_t* Channel);
		uint8_t Bluetooth_SendPacket(void* Data, uint16_t DataLen, Bluetooth_Channel_t* Channel);

	/* External Variables: */
		extern Bluetooth_Device_t     Bluetooth_DeviceConfiguration;
		extern Bluetooth_Connection_t Bluetooth_Connection;

#endif
