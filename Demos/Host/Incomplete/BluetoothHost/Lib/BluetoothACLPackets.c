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

#define  INCLUDE_FROM_BLUETOOTH_ACLPACKETS_C
#include "BluetoothACLPackets.h"

void Bluetooth_ACLTask(void)
{
	Bluetooth_ProcessACLPackets();
	
	for (uint8_t i = 0; i < BLUETOOTH_MAX_OPEN_CHANNELS; i++)
	{
		Bluetooth_Channel_t* ChannelData = &Bluetooth_Connection.Channels[i];
	
		bool MustSendConfigReq = true;
	
		switch (ChannelData->State)
		{
			case Channel_Config_WaitConfig:
				ChannelData->State = Channel_Config_WaitReqResp;
				break;
			case Channel_Config_WaitSendConfig:
				ChannelData->State = Channel_Config_WaitResp;
				break;
			default:
				MustSendConfigReq  = false;
				break;
		}
		
		if (MustSendConfigReq)
		{
			struct
			{
				BT_Signal_Header_t           SignalCommandHeader;
				BT_Signal_ConfigurationReq_t ConfigurationRequest;
				
				struct
				{
					BT_Config_Option_Header_t Header;
					uint16_t Value;
				} Option_LocalMTU;
			} PacketData;
			
			PacketData.SignalCommandHeader.Code            = BT_SIGNAL_CONFIGURATION_REQUEST;
			PacketData.SignalCommandHeader.Identifier      = ++Bluetooth_Connection.SignallingIdentifier;
			PacketData.SignalCommandHeader.Length          = sizeof(PacketData.ConfigurationRequest) +
			                                                 sizeof(PacketData.Option_LocalMTU);
			PacketData.ConfigurationRequest.DestinationChannel = ChannelData->RemoteNumber;
			PacketData.ConfigurationRequest.Flags          = 0;
			PacketData.Option_LocalMTU.Header.Type         = BT_CONFIG_OPTION_MTU;
			PacketData.Option_LocalMTU.Header.Length       = sizeof(PacketData.Option_LocalMTU.Value);
			PacketData.Option_LocalMTU.Value               = ChannelData->LocalMTU;

			Bluetooth_SendPacket(&PacketData, sizeof(PacketData), NULL);
			
			BT_ACL_DEBUG(1, ">> L2CAP Configuration Request", NULL);
			BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", PacketData.ConfigurationRequest.DestinationChannel);
		}
	}
}

static void Bluetooth_ProcessACLPackets(void)
{
	BT_ACL_Header_t        ACLPacketHeader;
	BT_DataPacket_Header_t DataHeader;

	Pipe_SelectPipe(BLUETOOTH_DATA_IN_PIPE);
	Pipe_Unfreeze();
	
	if (!(Pipe_IsReadWriteAllowed()))
	{
		Pipe_Freeze();
		return;
	}
	  
	Pipe_Read_Stream_LE(&ACLPacketHeader, sizeof(ACLPacketHeader));
	Pipe_Read_Stream_LE(&DataHeader, sizeof(DataHeader));

	BT_ACL_DEBUG(2, "", NULL);
	BT_ACL_DEBUG(2, "Packet Received", NULL);
	BT_ACL_DEBUG(2, "-- Connection Handle: 0x%04X", (ACLPacketHeader.ConnectionHandle & 0x0FFF));
	BT_ACL_DEBUG(2, "-- Data Length: 0x%04X", ACLPacketHeader.DataLength);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", DataHeader.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Payload Length: 0x%04X", DataHeader.PayloadLength);

	if (DataHeader.DestinationChannel == BT_CHANNEL_SIGNALING)
	{
		BT_Signal_Header_t SignalCommandHeader;
		Pipe_Read_Stream_LE(&SignalCommandHeader, sizeof(SignalCommandHeader));
		
		switch (SignalCommandHeader.Code)
		{
			case BT_SIGNAL_CONNECTION_REQUEST:
				Bluetooth_Signal_ConnectionReq(&ACLPacketHeader, &DataHeader, &SignalCommandHeader);
				break;
			case BT_SIGNAL_CONNECTION_RESPONSE:
				Bluetooth_Signal_ConnectionResp(&ACLPacketHeader, &DataHeader, &SignalCommandHeader);
				break;
			case BT_SIGNAL_CONFIGURATION_REQUEST:
				Bluetooth_Signal_ConfigurationReq(&ACLPacketHeader, &DataHeader, &SignalCommandHeader);
				break;
			case BT_SIGNAL_CONFIGURATION_RESPONSE:
				Bluetooth_Signal_ConfigurationResp(&ACLPacketHeader, &DataHeader, &SignalCommandHeader);
				break;
			case BT_SIGNAL_DISCONNECTION_REQUEST:
				Bluetooth_Signal_DisconnectionReq(&ACLPacketHeader, &DataHeader, &SignalCommandHeader);
				break;
			case BT_SIGNAL_DISCONNECTION_RESPONSE:
				Bluetooth_Signal_DisconnectionResp(&ACLPacketHeader, &DataHeader, &SignalCommandHeader);
				break;
			case BT_SIGNAL_ECHO_REQUEST:
				Bluetooth_Signal_EchoReq(&ACLPacketHeader, &DataHeader, &SignalCommandHeader);
				break;
			case BT_SIGNAL_INFORMATION_REQUEST:
				Bluetooth_Signal_InformationReq(&ACLPacketHeader, &DataHeader, &SignalCommandHeader);
				break;
			case BT_SIGNAL_COMMAND_REJECT:
				BT_ACL_DEBUG(1, "<< Command Reject", NULL);
				
				uint16_t RejectReason;
				Pipe_Read_Stream_LE(&RejectReason, sizeof(RejectReason));
				Pipe_Discard_Stream(ACLPacketHeader.DataLength - sizeof(RejectReason));
				Pipe_ClearIN();
				Pipe_Freeze();				
			
				BT_ACL_DEBUG(2, "-- Reason: %d", RejectReason);
				break;
			default:
				BT_ACL_DEBUG(1, "<< Unknown Signaling Command 0x%02X", SignalCommandHeader.Code);
	
				Pipe_Discard_Stream(ACLPacketHeader.DataLength);
				Pipe_ClearIN();		
				Pipe_Freeze();
				break;
		}
	}
	else
	{
		Bluetooth_PacketReceived(&DataHeader.PayloadLength, Bluetooth_GetChannelData(DataHeader.DestinationChannel, false));
	
		Pipe_SelectPipe(BLUETOOTH_DATA_IN_PIPE);
		Pipe_Discard_Stream(DataHeader.PayloadLength);
		Pipe_ClearIN();
		Pipe_Freeze();
	}
}

uint8_t Bluetooth_SendPacket(void* Data, uint16_t DataLen, Bluetooth_Channel_t* Channel)
{
	BT_ACL_Header_t        ACLPacketHeader;
	BT_DataPacket_Header_t DataHeader;

	if (!(Bluetooth_Connection.IsConnected))
	  return BT_SENDPACKET_NotConnected;

	if ((Channel != NULL) && (Channel->State != Channel_Open))
	  return BT_SENDPACKET_ChannelNotOpen;

	// TODO: Add packet fragmentation here after retrieving the device's signal channel MTU

	ACLPacketHeader.ConnectionHandle      = (Bluetooth_Connection.ConnectionHandle | BT_ACL_FIRST_AUTOFLUSH);
	ACLPacketHeader.DataLength            = sizeof(DataHeader) + DataLen;
	DataHeader.PayloadLength              = DataLen;
	DataHeader.DestinationChannel         = (Channel == NULL) ? BT_CHANNEL_SIGNALING : Channel->RemoteNumber;

	Pipe_SelectPipe(BLUETOOTH_DATA_OUT_PIPE);
	Pipe_Unfreeze();
	
	Pipe_Write_Stream_LE(&ACLPacketHeader, sizeof(ACLPacketHeader));
	Pipe_Write_Stream_LE(&DataHeader, sizeof(DataHeader));
	Pipe_Write_Stream_LE(Data, DataLen);
	Pipe_ClearOUT();
	
	Pipe_Freeze();
	
	BT_ACL_DEBUG(2, "", NULL);
	BT_ACL_DEBUG(2, "Packet Sent", NULL);
	BT_ACL_DEBUG(2, "-- Connection Handle: 0x%04X", (ACLPacketHeader.ConnectionHandle & 0x0FFF));
	BT_ACL_DEBUG(2, "-- Data Length: 0x%04X", ACLPacketHeader.DataLength);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", DataHeader.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Payload Length: 0x%04X", DataHeader.PayloadLength);

	return BT_SENDPACKET_NoError;
}

Bluetooth_Channel_t* Bluetooth_OpenChannel(uint16_t PSM)
{
	Bluetooth_Channel_t* ChannelData = NULL;

	for (uint8_t i = 0; i < BLUETOOTH_MAX_OPEN_CHANNELS; i++)
	{
		if (Bluetooth_Connection.Channels[i].State == Channel_Closed)
		{
			ChannelData = &Bluetooth_Connection.Channels[i];				
			ChannelData->LocalNumber = (BT_CHANNELNUMBER_BASEOFFSET + i);
			break;
		}
	}

	if (ChannelData == NULL)
	  return NULL;

	ChannelData->RemoteNumber = 0;
	ChannelData->PSM          = PSM;
	ChannelData->LocalMTU     = MAXIMUM_CHANNEL_MTU;
	ChannelData->State        = Channel_Config_WaitConfig;
	  
	struct
	{
		BT_Signal_Header_t        SignalCommandHeader;
		BT_Signal_ConnectionReq_t ConnectionRequest;
	} PacketData;

	PacketData.SignalCommandHeader.Code              = BT_SIGNAL_CONNECTION_REQUEST;
	PacketData.SignalCommandHeader.Identifier        = ++Bluetooth_Connection.SignallingIdentifier;
	PacketData.SignalCommandHeader.Length            = sizeof(PacketData.ConnectionRequest);
	PacketData.ConnectionRequest.PSM                 = PSM;
	PacketData.ConnectionRequest.SourceChannel       = ChannelData->LocalNumber;
	
	Bluetooth_SendPacket(&PacketData, sizeof(PacketData), NULL);

	BT_ACL_DEBUG(1, ">> L2CAP Connection Request", NULL);
	BT_ACL_DEBUG(2, "-- PSM 0x%04X", PacketData.ConnectionRequest.PSM);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", PacketData.ConnectionRequest.SourceChannel);

	return ChannelData;
}

void Bluetooth_CloseChannel(Bluetooth_Channel_t* Channel)
{
	if ((Channel == NULL) || (Channel->State == Channel_Closed))
	  return;
	  
	Channel->State = Channel_WaitDisconnect;

	struct
	{
		BT_Signal_Header_t           SignalCommandHeader;
		BT_Signal_DisconnectionReq_t DisconnectionRequest;
	} PacketData;
	
	PacketData.SignalCommandHeader.Code            = BT_SIGNAL_DISCONNECTION_REQUEST;
	PacketData.SignalCommandHeader.Identifier      = ++Bluetooth_Connection.SignallingIdentifier;
	PacketData.SignalCommandHeader.Length          = sizeof(PacketData.DisconnectionRequest);
	PacketData.DisconnectionRequest.DestinationChannel = Channel->RemoteNumber;
	PacketData.DisconnectionRequest.SourceChannel = Channel->LocalNumber;

	Bluetooth_SendPacket(&PacketData, sizeof(PacketData), NULL);
	
	BT_ACL_DEBUG(1, ">> L2CAP Disconnection Request", NULL);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", PacketData.DisconnectionRequest.DestinationChannel);	
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", PacketData.DisconnectionRequest.SourceChannel);	
}

static inline void Bluetooth_Signal_ConnectionReq(BT_ACL_Header_t*        ACLPacketHeader,
                                                  BT_DataPacket_Header_t* DataHeader,
                                                  BT_Signal_Header_t*     SignalCommandHeader)
{
	BT_Signal_ConnectionReq_t ConnectionRequest;
	
	Pipe_Read_Stream_LE(&ConnectionRequest, sizeof(ConnectionRequest));

	Pipe_ClearIN();
	Pipe_Freeze();

	BT_ACL_DEBUG(1, "<< L2CAP Connection Request", NULL);
	BT_ACL_DEBUG(2, "-- PSM: 0x%04X", ConnectionRequest.PSM);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ConnectionRequest.SourceChannel);
	
	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(ConnectionRequest.SourceChannel, true);

	if (ChannelData == NULL)
	{
		for (uint8_t i = 0; i < BLUETOOTH_MAX_OPEN_CHANNELS; i++)
		{
			if (Bluetooth_Connection.Channels[i].State == Channel_Closed)
			{
				ChannelData = &Bluetooth_Connection.Channels[i];				
				ChannelData->LocalNumber = (BT_CHANNELNUMBER_BASEOFFSET + i);
				break;
			}
		}
	}

	if (ChannelData != NULL)
	{
		ChannelData->RemoteNumber = ConnectionRequest.SourceChannel;
		ChannelData->PSM          = ConnectionRequest.PSM;
		ChannelData->LocalMTU     = MAXIMUM_CHANNEL_MTU;
		ChannelData->State        = Channel_Config_WaitConfig;
	}
	
	struct
	{
		BT_Signal_Header_t         SignalCommandHeader;
		BT_Signal_ConnectionResp_t ConnectionResponse;
	} ResponsePacket;

	ResponsePacket.SignalCommandHeader.Code              = BT_SIGNAL_CONNECTION_RESPONSE;
	ResponsePacket.SignalCommandHeader.Identifier        = SignalCommandHeader->Identifier;
	ResponsePacket.SignalCommandHeader.Length            = sizeof(ResponsePacket.ConnectionResponse);
	ResponsePacket.ConnectionResponse.DestinationChannel = ChannelData->LocalNumber;
	ResponsePacket.ConnectionResponse.SourceChannel      = ChannelData->RemoteNumber;
	ResponsePacket.ConnectionResponse.Result             = (ChannelData == NULL) ? BT_CONNECTION_REFUSED_RESOURCES :
	                                                                               BT_CONNECTION_SUCCESSFUL;
	ResponsePacket.ConnectionResponse.Status             = 0x00;
	
	Bluetooth_SendPacket(&ResponsePacket, sizeof(ResponsePacket), NULL);

	BT_ACL_DEBUG(1, ">> L2CAP Connection Response", NULL);
	BT_ACL_DEBUG(2, "-- Result: 0x%02X", ResponsePacket.ConnectionResponse.Result);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", ResponsePacket.ConnectionResponse.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ResponsePacket.ConnectionResponse.SourceChannel);
}

static inline void Bluetooth_Signal_ConnectionResp(BT_ACL_Header_t* ACLPacketHeader,
                                                   BT_DataPacket_Header_t* DataHeader,
                                                   BT_Signal_Header_t* SignalCommandHeader)
{
	BT_Signal_ConnectionResp_t ConnectionResponse;
	
	Pipe_Read_Stream_LE(&ConnectionResponse, sizeof(ConnectionResponse));

	Pipe_ClearIN();
	Pipe_Freeze();

	BT_ACL_DEBUG(1, "<< L2CAP Connection Response", NULL);
	BT_ACL_DEBUG(2, "-- Result: 0x%02X", ConnectionResponse.Result);	
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ConnectionResponse.SourceChannel);	
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", ConnectionResponse.DestinationChannel);	

	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(ConnectionResponse.DestinationChannel, false);

	if (ChannelData != NULL)
	{
		ChannelData->RemoteNumber = ConnectionResponse.SourceChannel;
		ChannelData->State        = (ConnectionResponse.Result == BT_CONNECTION_SUCCESSFUL) ?
		                             Channel_Config_WaitConfig : Channel_Closed;
	}
}


static inline void Bluetooth_Signal_ConfigurationReq(BT_ACL_Header_t*        ACLPacketHeader,
                                                     BT_DataPacket_Header_t* DataHeader,
                                                     BT_Signal_Header_t*     SignalCommandHeader)
{
	BT_Signal_ConfigurationReq_t ConfigurationRequest;
	uint8_t OptionsLen = (SignalCommandHeader->Length - sizeof(ConfigurationRequest));
	uint8_t Options[OptionsLen];

	Pipe_Read_Stream_LE(&ConfigurationRequest, sizeof(ConfigurationRequest));	
	Pipe_Read_Stream_LE(&Options, sizeof(Options));

	Pipe_ClearIN();
	Pipe_Freeze();

	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(ConfigurationRequest.DestinationChannel, false);

	BT_ACL_DEBUG(1, "<< L2CAP Configuration Request", NULL);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", ConfigurationRequest.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Remote MTU: 0x%04X", ChannelData->RemoteMTU);
	BT_ACL_DEBUG(2, "-- Options Len: 0x%04X", OptionsLen);

	uint8_t OptionPos = 0;
	while (OptionPos < OptionsLen)
	{
		BT_Config_Option_Header_t* OptionHeader = (BT_Config_Option_Header_t*)&Options[OptionPos];

		BT_ACL_DEBUG(2, "-- Option Type: 0x%04X", OptionHeader->Type);
		BT_ACL_DEBUG(2, "-- Option Length: 0x%04X", (sizeof(*OptionHeader) + OptionHeader->Length));
		
		if ((OptionHeader->Type == BT_CONFIG_OPTION_MTU) && (ChannelData != NULL))
		  ChannelData->RemoteMTU = *((uint16_t*)&Options[OptionPos + sizeof(*OptionHeader)]);

		OptionPos += (sizeof(*OptionHeader) + OptionHeader->Length);
	}
	
	struct
	{
		BT_Signal_Header_t            SignalCommandHeader;
		BT_Signal_ConfigurationResp_t ConfigurationResponse;
	} ResponsePacket;

	ResponsePacket.SignalCommandHeader.Code              = BT_SIGNAL_CONFIGURATION_RESPONSE;
	ResponsePacket.SignalCommandHeader.Identifier        = SignalCommandHeader->Identifier;
	ResponsePacket.SignalCommandHeader.Length            = sizeof(ResponsePacket.ConfigurationResponse);
	ResponsePacket.ConfigurationResponse.SourceChannel   = ChannelData->RemoteNumber;
	ResponsePacket.ConfigurationResponse.Flags           = 0x00;
	ResponsePacket.ConfigurationResponse.Result          = (ChannelData != NULL) ? BT_CONFIGURATION_SUCCESSFUL : BT_CONFIGURATION_REJECTED;

	Bluetooth_SendPacket(&ResponsePacket, sizeof(ResponsePacket), NULL);

	if (ChannelData != NULL)
	{
		switch (ChannelData->State)
		{
			case Channel_Config_WaitConfig:
				ChannelData->State = Channel_Config_WaitSendConfig;
				break;
			case Channel_Config_WaitReqResp:
				ChannelData->State = Channel_Config_WaitResp;
				break;
			case Channel_Config_WaitReq:
				ChannelData->State = Channel_Open;
				break;
		}
	}

	BT_ACL_DEBUG(1, ">> L2CAP Configuration Response", NULL);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ResponsePacket.ConfigurationResponse.SourceChannel);
	BT_ACL_DEBUG(2, "-- Result: 0x%02X", ResponsePacket.ConfigurationResponse.Result);
}

static inline void Bluetooth_Signal_ConfigurationResp(BT_ACL_Header_t*        ACLPacketHeader,
                                                      BT_DataPacket_Header_t* DataHeader,
                                                      BT_Signal_Header_t*     SignalCommandHeader)
{
	BT_Signal_ConfigurationResp_t ConfigurationResponse;

	Pipe_Read_Stream_LE(&ConfigurationResponse, sizeof(ConfigurationResponse));

	Pipe_ClearIN();
	Pipe_Freeze();
	
	BT_ACL_DEBUG(1, "<< L2CAP Configuration Response", NULL);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ConfigurationResponse.SourceChannel);
	BT_ACL_DEBUG(2, "-- Result: 0x%02X", ConfigurationResponse.Result);

	if (ConfigurationResponse.Result == BT_CONFIGURATION_SUCCESSFUL)
	{
		Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(ConfigurationResponse.SourceChannel, true);
		
		if (ChannelData != NULL)
		{
			switch (ChannelData->State)
			{
				case Channel_Config_WaitReqResp:
					ChannelData->State = Channel_Config_WaitReq;
					break;
				case Channel_Config_WaitResp:
					ChannelData->State = Channel_Open;
					break;
			}
		}		
	}
}

static inline void Bluetooth_Signal_DisconnectionReq(BT_ACL_Header_t*        ACLPacketHeader,
                                                     BT_DataPacket_Header_t* DataHeader,
                                                     BT_Signal_Header_t*     SignalCommandHeader)
{
	BT_Signal_DisconnectionReq_t DisconnectionRequest;
	
	Pipe_Read_Stream_LE(&DisconnectionRequest, sizeof(DisconnectionRequest));

	BT_ACL_DEBUG(1, "<< L2CAP Disconnection Request", NULL);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", DisconnectionRequest.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", DisconnectionRequest.SourceChannel);
	
	Pipe_ClearIN();
	Pipe_Freeze();
	
	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(DisconnectionRequest.SourceChannel, true);

	struct
	{
		BT_Signal_Header_t            SignalCommandHeader;
		BT_Signal_DisconnectionResp_t DisconnectionResponse;
	} ResponsePacket;

	ResponsePacket.SignalCommandHeader.Code                 = BT_SIGNAL_DISCONNECTION_RESPONSE;
	ResponsePacket.SignalCommandHeader.Identifier           = SignalCommandHeader->Identifier;
	ResponsePacket.SignalCommandHeader.Length               = sizeof(ResponsePacket.DisconnectionResponse);
	ResponsePacket.DisconnectionResponse.DestinationChannel = ChannelData->RemoteNumber;
	ResponsePacket.DisconnectionResponse.SourceChannel      = ChannelData->LocalNumber;

	Bluetooth_SendPacket(&ResponsePacket, sizeof(ResponsePacket), NULL);

	if (ChannelData != NULL)
	  ChannelData->State = Channel_Closed;

	BT_ACL_DEBUG(1, ">> L2CAP Disconnection Response", NULL);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ResponsePacket.DisconnectionResponse.SourceChannel);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", ResponsePacket.DisconnectionResponse.DestinationChannel);
}

static inline void Bluetooth_Signal_DisconnectionResp(BT_ACL_Header_t*        ACLPacketHeader,
                                                      BT_DataPacket_Header_t* DataHeader,
                                                      BT_Signal_Header_t*     SignalCommandHeader)
{
	BT_Signal_DisconnectionResp_t DisconnectionResponse;
	
	Pipe_Read_Stream_LE(&DisconnectionResponse, sizeof(DisconnectionResponse));

	BT_ACL_DEBUG(1, "<< L2CAP Disconnection Response", NULL);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", DisconnectionResponse.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", DisconnectionResponse.SourceChannel);
	
	Pipe_ClearIN();
	Pipe_Freeze();
	
	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(DisconnectionResponse.SourceChannel, true);
	
	if (ChannelData->State == Channel_WaitDisconnect)
	  ChannelData->State = Channel_Closed;
}

static inline void Bluetooth_Signal_EchoReq(BT_ACL_Header_t* ACLPacketHeader,
                                            BT_DataPacket_Header_t* DataHeader,
                                            BT_Signal_Header_t* SignalCommandHeader)
{
	BT_ACL_DEBUG(1, "<< L2CAP Echo Request", NULL);
	
	Pipe_ClearIN();
	Pipe_Freeze();
	
	struct
	{
		BT_Signal_Header_t SignalCommandHeader;
	} ResponsePacket;

	ResponsePacket.SignalCommandHeader.Code                 = BT_SIGNAL_ECHO_RESPONSE;
	ResponsePacket.SignalCommandHeader.Identifier           = SignalCommandHeader->Identifier;
	ResponsePacket.SignalCommandHeader.Length               = 0;
	
	Bluetooth_SendPacket(&ResponsePacket, sizeof(ResponsePacket), NULL);

	BT_ACL_DEBUG(1, ">> L2CAP Echo Response", NULL);
}

static inline void Bluetooth_Signal_InformationReq(BT_ACL_Header_t*        ACLPacketHeader,
                                                   BT_DataPacket_Header_t* DataHeader,
                                                   BT_Signal_Header_t*     SignalCommandHeader)
{
	BT_Signal_InformationReq_t InformationRequest;

	Pipe_Read_Stream_LE(&InformationRequest, sizeof(InformationRequest));

	BT_ACL_DEBUG(1, "<< L2CAP Information Request", NULL);
	BT_ACL_DEBUG(2, "-- Info Type: 0x%04X", InformationRequest.InfoType);
	
	Pipe_ClearIN();
	Pipe_Freeze();

	struct
	{
		BT_Signal_Header_t SignalCommandHeader;
		BT_Signal_InformationResp_t InformationResponse;
		
		uint8_t Data[4];
	} ResponsePacket;
	
	uint8_t DataLen = 0;
	
	switch (InformationRequest.InfoType)
	{
		case BT_INFOREQ_MTU:		
			ResponsePacket.InformationResponse.Result = BT_INFORMATION_SUCCESSFUL;
			DataLen = 2;
			
			*((uint16_t*)&ResponsePacket.Data) = MAXIMUM_CHANNEL_MTU;
			break;
		case BT_INFOREQ_EXTENDEDFEATURES:
			ResponsePacket.InformationResponse.Result = BT_INFORMATION_SUCCESSFUL;
			DataLen = 4;
			
			*((uint32_t*)&ResponsePacket.Data) = 0;
			break;
		default:
			ResponsePacket.InformationResponse.Result = BT_INFORMATION_NOTSUPPORTED;
			DataLen = 0;
			break;
	}
	
	ResponsePacket.SignalCommandHeader.Code                 = BT_SIGNAL_INFORMATION_RESPONSE;
	ResponsePacket.SignalCommandHeader.Identifier           = SignalCommandHeader->Identifier;
	ResponsePacket.SignalCommandHeader.Length               = sizeof(ResponsePacket.InformationResponse) + DataLen;

	Bluetooth_SendPacket(&ResponsePacket, (sizeof(ResponsePacket) - sizeof(ResponsePacket.Data) + DataLen), NULL);

	BT_ACL_DEBUG(1, ">> L2CAP Information Response", NULL);	
	BT_ACL_DEBUG(2, "-- Result: 0x%02X", ResponsePacket.InformationResponse.Result);
}
