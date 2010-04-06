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

#ifndef _BLUETOOTH_ACLPACKETS_
#define _BLUETOOTH_ACLPACKETS_

	/* Includes: */
		#include <avr/io.h>
		#include <string.h>
		#include <stdbool.h>

		#include <LUFA/Drivers/USB/USB.h>
		
		#include "BluetoothStack.h"
		
	/* Macros: */
		#define BT_ACL_DEBUG(s, ...)              printf_P(PSTR("(ACL) " s "\r\n"), __VA_ARGS__)
		#define ACL_DEBUG_LEVEL                   2

		#define BT_CHANNEL_SIGNALING              0x0001
		#define BT_CHANNEL_CONNECTIONLESS         0x0002
		
		#define BT_SIGNAL_CONNECTION_REQUEST      0x02
		#define BT_SIGNAL_CONNECTION_RESPONSE     0x03
		#define BT_SIGNAL_CONFIGURATION_REQUEST   0x04
		#define BT_SIGNAL_CONFIGURATION_RESPONSE  0x05
		#define BT_SIGNAL_DISCONNECTION_REQUEST   0x06
		#define BT_SIGNAL_DISCONNECTION_RESPONSE  0x07
		#define BT_SIGNAL_ECHO_REQUEST            0x08
		#define BT_SIGNAL_ECHO_RESPONSE           0x09
		#define BT_SIGNAL_INFORMATION_REQUEST     0x0A
		#define BT_SIGNAL_INFORMATION_RESPONSE    0x0B
		
		#define BT_INFOREQ_MTU                    0x0001
		#define BT_INFOREQ_EXTENDEDFEATURES       0x0002
		
		#define BT_INFORMATION_SUCCESSFUL         0x0000
		#define BT_INFORMATION_NOTSUPPORTED       0x0001
		
		#define BT_CONNECTION_SUCCESSFUL          0x0000
		#define BT_CONNECTION_REFUSED_RESOURCES   0x0004
		
		#define BT_CONFIGURATION_SUCCESSFUL       0x0000
		#define BT_CONFIGURATION_REJECTED         0x0002
		#define BT_CONFIGURATION_UNKNOWNOPTIONS   0x0003
		
	/* Type Defines: */
		typedef struct
		{
			uint16_t ConnectionHandle;
			uint16_t DataLength;
		} Bluetooth_ACL_Header_t;

		typedef struct
		{
			uint16_t PayloadLength;
			uint16_t DestinationChannel;
		} Bluetooth_DataPacket_Header_t;
		
		typedef struct
		{
			uint8_t  Code;
			uint8_t  Identifier;
			uint16_t Length;
		} Bluetooth_SignalCommand_Header_t;
		
		typedef struct
		{
			uint16_t PSM;
			uint16_t SourceChannel;
		} Bluetooth_SignalCommand_ConnectionRequest_t;

		typedef struct
		{
			uint16_t DestinationChannel;
			uint16_t SourceChannel;
			uint16_t Result;
			uint16_t Status;
		} Bluetooth_SignalCommand_ConnectionResponse_t;

		typedef struct
		{
			uint16_t DestinationChannel;
			uint16_t SourceChannel;
		} Bluetooth_SignalCommand_DisconnectionRequest_t;
		
		typedef struct
		{
			uint16_t DestinationChannel;
			uint16_t SourceChannel;
		} Bluetooth_SignalCommand_DisconnectionResponse_t;		

		typedef struct
		{
			uint16_t DestinationChannel;
			uint16_t Flags;
		} Bluetooth_SignalCommand_ConfigurationRequest_t;

		typedef struct
		{
			uint16_t SourceChannel;
			uint16_t Flags;
			uint16_t Result;
		} Bluetooth_SignalCommand_ConfigurationResponse_t;

		typedef struct
		{
			uint16_t InfoType;
		} Bluetooth_SignalCommand_InformationRequest_t;
		
		typedef struct
		{
			uint16_t InfoType;
			uint16_t Result;
		} Bluetooth_SignalCommand_InformationResponse_t;

	/* Function Prototypes: */
		void Bluetooth_ProcessACLPackets(void);

		#if defined(INCLUDE_FROM_BLUETOOTH_ACLPACKETS_C)
			static inline void Bluetooth_SignalPacket_ConnectionRequest(Bluetooth_ACL_Header_t* ACLPacketHeader,
                                                                  Bluetooth_DataPacket_Header_t* DataHeader,
                                                                  Bluetooth_SignalCommand_Header_t* SignalCommandHeader);
			static inline void Bluetooth_SignalPacket_EchoRequest(Bluetooth_ACL_Header_t* ACLPacketHeader,
                                                                  Bluetooth_DataPacket_Header_t* DataHeader,
                                                                  Bluetooth_SignalCommand_Header_t* SignalCommandHeader);
			static inline void Bluetooth_SignalPacket_ConfigurationRequest(Bluetooth_ACL_Header_t* ACLPacketHeader,
                                                                  Bluetooth_DataPacket_Header_t* DataHeader,
                                                                  Bluetooth_SignalCommand_Header_t* SignalCommandHeader);
			static inline void Bluetooth_SignalPacket_DisconnectionRequest(Bluetooth_ACL_Header_t* ACLPacketHeader,
                                                                  Bluetooth_DataPacket_Header_t* DataHeader,
                                                                  Bluetooth_SignalCommand_Header_t* SignalCommandHeader);
			static inline void Bluetooth_SignalPacket_InformationRequest(Bluetooth_ACL_Header_t* ACLPacketHeader,
                                                                  Bluetooth_DataPacket_Header_t* DataHeader,
                                                                  Bluetooth_SignalCommand_Header_t* SignalCommandHeader);
		#endif
		
#endif
