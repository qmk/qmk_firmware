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

#ifndef _BLUETOOTH_STACK_
#define _BLUETOOTH_STACK_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Scheduler/Scheduler.h>
		
		#include "BluetoothHost.h"
		#include "BluetoothHCICommands.h"
		#include "BluetoothACLPackets.h"
		
	/* Macros: */
		#define BLUETOOTH_MAX_OPEN_CHANNELS              2
		#define BLUETOOTH_CHANNELNUMBER_BASEOFFSET       0x0040
		
		#define CHANNEL_LOOKUP_BY_SOURCE                 true
		#define CHANNEL_LOOKUP_BY_DESTINATION            false
		
		#define BT_DEBUG(s, ...) printf_P(PSTR(s "\r\n"), __VA_ARGS__)
	
	/* Enums: */
		enum Bluetooth_Channel_State_t
		{
			Channel_Closed          = 0,
			Channel_WaitConnect     = 1,
			Channel_WaitConnectRsp  = 2,
			Channel_Config          = 3,
			Channel_Open            = 4,
			Channel_WaitDisconnect  = 5,
		};

	/* Type Defines: */
		typedef struct
		{
			uint8_t  State;
			uint16_t LocalNumber;
			uint16_t RemoteNumber;
			uint16_t PSM;
			uint16_t MTU;
		} Bluetooth_Channel_t;

		typedef struct
		{
			bool                IsConnected;
			uint16_t            ConnectionHandle;
			uint8_t             DeviceAddress[6];
			Bluetooth_Channel_t Channels[BLUETOOTH_MAX_OPEN_CHANNELS];
		} Bluetooth_Connection_t;
		
		typedef struct
		{
			uint32_t Class;
			char     PINCode[16];
			char     Name[];
		} Bluetooth_Device_t;
		
	/* Tasks: */
		TASK(Bluetooth_Task);

	/* Function Prototypes: */
		Bluetooth_Channel_t* Bluetooth_GetChannelData(uint16_t ChannelNumber, bool SearchBySource);
		Bluetooth_Channel_t* Bluetooth_InitChannelData(uint16_t RemoteChannelNumber, uint16_t PSM);

	/* External Variables: */
		extern Bluetooth_Device_t     Bluetooth_DeviceConfiguration;
		extern Bluetooth_Connection_t Bluetooth_Connection;

#endif
