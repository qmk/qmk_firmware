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

#define  INCLUDE_FROM_BLUETOOTH_ACLPACKETS_C
#include "BluetoothACLPackets.h"

void Bluetooth_ProcessACLPackets(void)
{
	Bluetooth_ACL_Header_t ACLPacketHeader;

	Pipe_SelectPipe(BLUETOOTH_DATA_IN_PIPE);
	Pipe_SetToken(PIPE_TOKEN_IN);
	Pipe_Unfreeze();
	
	if (!(Pipe_ReadWriteAllowed()))
	{
		Pipe_Freeze();
		return;
	}
	  
	Pipe_Read_Stream_LE(&ACLPacketHeader, sizeof(ACLPacketHeader));
		
	Bluetooth_DataPacket_Header_t DataHeader;
	Pipe_Read_Stream_LE(&DataHeader, sizeof(DataHeader));

	BT_DEBUG("(ACL) Packet Received", NULL);
	BT_DEBUG("(ACL) -- Connection Handle: 0x%04X", ACLPacketHeader.ConnectionHandle);
	BT_DEBUG("(ACL) -- Data Length: 0x%04X", ACLPacketHeader.DataLength);
	BT_DEBUG("(ACL) -- Destination Channel: 0x%04X", DataHeader.DestinationChannel);
	BT_DEBUG("(ACL) -- Payload Length: 0x%04X", DataHeader.PayloadLength);

	if (DataHeader.DestinationChannel == BLUETOOTH_CHANNEL_SIGNALING)
	{
		Bluetooth_SignalCommand_Header_t SignalCommandHeader;
		Pipe_Read_Stream_LE(&SignalCommandHeader, sizeof(SignalCommandHeader));

		switch (SignalCommandHeader.Code)
		{
			case BLUETOOTH_SIGNAL_CONNECTION_REQUEST:
				Bluetooth_ProcessSignalPacket_ConnectionRequest(&ACLPacketHeader, &DataHeader, &SignalCommandHeader);
				break;
			case BLUETOOTH_SIGNAL_CONFIGURATION_REQUEST:
				Bluetooth_ProcessSignalPacket_ConfigurationRequest(&ACLPacketHeader, &DataHeader, &SignalCommandHeader);
				break;			
			default:
				BT_DEBUG("(ACL) >> Unknown Signalling Command 0x%02X", SignalCommandHeader.Code);
					
				Pipe_Discard_Stream(ACLPacketHeader.DataLength);
				Pipe_ClearCurrentBank();		
				Pipe_Freeze();
				break;
		}
	}
	else
	{
		uint8_t DataPayload[DataHeader.PayloadLength];
		Pipe_Read_Stream_LE(&DataPayload, sizeof(DataPayload));
		DataHeader.PayloadLength = 0;
	
		BT_DEBUG("(ACL) -- Data Payload: ", NULL);
		for (uint16_t B = 0; B < sizeof(DataPayload); B++)
		  printf("0x%02X ", DataPayload[B]);
		BT_DEBUG("", NULL);

		Pipe_Discard_Stream(ACLPacketHeader.DataLength);
		Pipe_ClearCurrentBank();		
		Pipe_Freeze();
	}
}

static inline void Bluetooth_ProcessSignalPacket_ConnectionRequest(Bluetooth_ACL_Header_t* ACLPacketHeader,
                                                                   Bluetooth_DataPacket_Header_t* DataHeader,
                                                                   Bluetooth_SignalCommand_Header_t* SignalCommandHeader)
{
	Bluetooth_SignalCommand_ConnectionRequest_t ConnectionRequest;
	
	Pipe_Read_Stream_LE(&ConnectionRequest, sizeof(ConnectionRequest));

	BT_DEBUG("(ACL) >> L2CAP Connection Request", NULL);
	BT_DEBUG("(ACL) -- PSM: 0x%04X", ConnectionRequest.PSM);
	BT_DEBUG("(ACL) -- Source Channel: 0x%04X", ConnectionRequest.SourceChannel);
	
	Pipe_ClearCurrentBank();
	Pipe_Freeze();
	Pipe_SelectPipe(BLUETOOTH_DATA_OUT_PIPE);
	Pipe_SetToken(PIPE_TOKEN_OUT);
	Pipe_Unfreeze();
	
	Bluetooth_SignalCommand_ConnectionResponse_t ConnectionResponse;

	ACLPacketHeader->DataLength           = sizeof(*DataHeader) + sizeof(*SignalCommandHeader) + sizeof(ConnectionResponse);
	DataHeader->PayloadLength             = sizeof(*SignalCommandHeader) + sizeof(ConnectionResponse);
	DataHeader->DestinationChannel        = BLUETOOTH_CHANNEL_SIGNALING;
	SignalCommandHeader->Code             = BLUETOOTH_SIGNAL_CONNECTION_RESPONSE;
	SignalCommandHeader->Length           = sizeof(ConnectionResponse);
	
	Bluetooth_Channel_t* ChannelData      = Bluetooth_InitChannelData(ConnectionRequest.SourceChannel, ConnectionRequest.PSM);
	
	ConnectionResponse.Result             = (ChannelData == NULL) ? BLUETOOTH_CONNECTION_REFUSED_RESOURCES :
																    BLUETOOTH_CONNECTION_SUCCESSFUL;
	ConnectionResponse.DestinationChannel = ChannelData->LocalNumber;
	ConnectionResponse.SourceChannel      = ChannelData->RemoteNumber;
	ConnectionResponse.Status             = 0x00;

	Pipe_Write_Stream_LE(ACLPacketHeader, sizeof(*ACLPacketHeader));
	Pipe_Write_Stream_LE(DataHeader, sizeof(*DataHeader));
	Pipe_Write_Stream_LE(SignalCommandHeader, sizeof(*SignalCommandHeader));
	Pipe_Write_Stream_LE(&ConnectionResponse, sizeof(ConnectionResponse));
	
	Pipe_ClearCurrentBank();		
	Pipe_Freeze();
	
	BT_DEBUG("(ACL) Packet Sent", NULL);
	BT_DEBUG("(ACL) -- Connection Handle: 0x%04X", ACLPacketHeader->ConnectionHandle);
	BT_DEBUG("(ACL) -- Data Length: 0x%04X", ACLPacketHeader->DataLength);
	BT_DEBUG("(ACL) -- Destination Channel: 0x%04X", DataHeader->DestinationChannel);
	BT_DEBUG("(ACL) -- Payload Length: 0x%04X", DataHeader->PayloadLength);			
	BT_DEBUG("(ACL) >> L2CAP Connection Response", NULL);
	BT_DEBUG("(ACL) -- Source Channel: 0x%04X", ConnectionResponse.SourceChannel);
	BT_DEBUG("(ACL) -- Destination Channel: 0x%04X", ConnectionResponse.DestinationChannel);
}

static inline void Bluetooth_ProcessSignalPacket_ConfigurationRequest(Bluetooth_ACL_Header_t* ACLPacketHeader,
                                                                      Bluetooth_DataPacket_Header_t* DataHeader,
                                                                      Bluetooth_SignalCommand_Header_t* SignalCommandHeader)
{
	Bluetooth_SignalCommand_ConfigurationRequest_t ConfigurationRequest;
	
	Pipe_Read_Stream_LE(&ConfigurationRequest, sizeof(ConfigurationRequest));

	BT_DEBUG("(ACL) >> L2CAP Configuration Request", NULL);
	BT_DEBUG("(ACL) -- Destination Channel: 0x%04X", ConfigurationRequest.DestinationChannel);
	
	Pipe_ClearCurrentBank();
	Pipe_Freeze();
	Pipe_SelectPipe(BLUETOOTH_DATA_OUT_PIPE);
	Pipe_SetToken(PIPE_TOKEN_OUT);
	Pipe_Unfreeze();
	
	Bluetooth_SignalCommand_ConfigurationResponse_t ConfigurationResponse;

	ACLPacketHeader->DataLength           = sizeof(*DataHeader) + sizeof(*SignalCommandHeader) + sizeof(ConfigurationResponse);
	DataHeader->PayloadLength             = sizeof(*SignalCommandHeader) + sizeof(ConfigurationResponse);
	DataHeader->DestinationChannel        = BLUETOOTH_CHANNEL_SIGNALING;
	SignalCommandHeader->Code             = BLUETOOTH_SIGNAL_CONFIGURATION_RESPONSE;
	SignalCommandHeader->Length           = sizeof(ConfigurationResponse);
	
	Bluetooth_Channel_t* ChannelData      = Bluetooth_GetChannelData(ConfigurationRequest.DestinationChannel, CHANNEL_LOOKUP_BY_DESTINATION);

	if (ChannelData != NULL)
	  ChannelData->State = Channel_Open;
	  
	 // TODO: Add channel config data to the tail of ConfigurationResponse

	ConfigurationResponse.SourceChannel   = ChannelData->RemoteNumber;
	ConfigurationResponse.Flags           = 0x00;
	ConfigurationResponse.Result          = (ChannelData != NULL) ? BLUETOOTH_CONFIGURATION_SUCCESSFUL : BLUETOOTH_CONFIGURATION_REJECTED;

	Pipe_Write_Stream_LE(ACLPacketHeader, sizeof(*ACLPacketHeader));
	Pipe_Write_Stream_LE(DataHeader, sizeof(*DataHeader));
	Pipe_Write_Stream_LE(SignalCommandHeader, sizeof(*SignalCommandHeader));
	Pipe_Write_Stream_LE(&ConfigurationResponse, sizeof(ConfigurationResponse));
	
	Pipe_ClearCurrentBank();		
	Pipe_Freeze();
	
	BT_DEBUG("(ACL) Packet Sent", NULL);
	BT_DEBUG("(ACL) -- Connection Handle: 0x%04X", ACLPacketHeader->ConnectionHandle);
	BT_DEBUG("(ACL) -- Data Length: 0x%04X", ACLPacketHeader->DataLength);
	BT_DEBUG("(ACL) -- Destination Channel: 0x%04X", DataHeader->DestinationChannel);
	BT_DEBUG("(ACL) -- Payload Length: 0x%04X", DataHeader->PayloadLength);			
	BT_DEBUG("(ACL) >> L2CAP Configuration Response", NULL);
}
