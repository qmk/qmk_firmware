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

/*
	TODO: Make SendPacket respect receiver's MTU
	TODO: Make ReceivePacket stitch together MTU fragments (?)
	TODO: Add channel opened/closed callbacks
 */

#define  INCLUDE_FROM_BLUETOOTH_ACLPACKETS_C
#include "BluetoothACLPackets.h"

/** Bluetooth ACL processing task. This task should be called repeatedly the main Bluetooth
 *  stack task to manage the ACL processing state.
 */
void Bluetooth_ACLTask(void)
{
	/* Process incomming ACL packets, if any */
	Bluetooth_ProcessIncommingACLPackets();
	
	/* Check for any half-open channels, send configuration details to the remote device if found */
	for (uint8_t i = 0; i < BLUETOOTH_MAX_OPEN_CHANNELS; i++)
	{
		Bluetooth_Channel_t* ChannelData = &Bluetooth_Connection.Channels[i];
	
		bool MustSendConfigReq = true;
	
		/* Check if we are in a channel state which requires a configuration request to be sent */
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
		
		/* Only send a configuration request if it the channel was in a state which required it */
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
			
			/* Fill out the Signal Command header in the response packet */
			PacketData.SignalCommandHeader.Code            = BT_SIGNAL_CONFIGURATION_REQUEST;
			PacketData.SignalCommandHeader.Identifier      = ++Bluetooth_Connection.SignallingIdentifier;
			PacketData.SignalCommandHeader.Length          = sizeof(PacketData.ConfigurationRequest) +
			                                                 sizeof(PacketData.Option_LocalMTU);

			/* Fill out the Configuration Request in the response packet, including local MTU information */
			PacketData.ConfigurationRequest.DestinationChannel = ChannelData->RemoteNumber;
			PacketData.ConfigurationRequest.Flags          = 0;
			PacketData.Option_LocalMTU.Header.Type         = BT_CONFIG_OPTION_MTU;
			PacketData.Option_LocalMTU.Header.Length       = sizeof(PacketData.Option_LocalMTU.Value);
			PacketData.Option_LocalMTU.Value               = ChannelData->LocalMTU;

			Bluetooth_SendPacket(&PacketData, sizeof(PacketData), NULL);
			
			BT_ACL_DEBUG(1, ">> L2CAP Configuration Request");
			BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", PacketData.ConfigurationRequest.DestinationChannel);
		}
	}
}

/** Incomming ACL packet processing task. This task is called by the main ACL processing task to read in and process
 *  any incomming ACL packets to the device, handling signal requests as they are received or passing along channel
 *  data to the user application.
 */
static void Bluetooth_ProcessIncommingACLPackets(void)
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
	  
	/* Read in the received ACL packet headers when it has been discovered that a packet has been received */
	Pipe_Read_Stream_LE(&ACLPacketHeader, sizeof(ACLPacketHeader));
	Pipe_Read_Stream_LE(&DataHeader, sizeof(DataHeader));

	BT_ACL_DEBUG(2, "");
	BT_ACL_DEBUG(2, "Packet Received");
	BT_ACL_DEBUG(2, "-- Connection Handle: 0x%04X", (ACLPacketHeader.ConnectionHandle & 0x0FFF));
	BT_ACL_DEBUG(2, "-- Data Length: 0x%04X", ACLPacketHeader.DataLength);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", DataHeader.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Payload Length: 0x%04X", DataHeader.PayloadLength);

	/* Check the packet's destination channel - signalling channel should be processed by the stack internally */
	if (DataHeader.DestinationChannel == BT_CHANNEL_SIGNALING)
	{
		/* Read in the Signal Command header of the incomming packet */
		BT_Signal_Header_t SignalCommandHeader;
		Pipe_Read_Stream_LE(&SignalCommandHeader, sizeof(SignalCommandHeader));
		
		/* Dispatch to the appropriate handler function based on the Signal message code */
		switch (SignalCommandHeader.Code)
		{
			case BT_SIGNAL_CONNECTION_REQUEST:
				Bluetooth_Signal_ConnectionReq(&SignalCommandHeader);
				break;
			case BT_SIGNAL_CONNECTION_RESPONSE:
				Bluetooth_Signal_ConnectionResp(&SignalCommandHeader);
				break;
			case BT_SIGNAL_CONFIGURATION_REQUEST:
				Bluetooth_Signal_ConfigurationReq(&SignalCommandHeader);
				break;
			case BT_SIGNAL_CONFIGURATION_RESPONSE:
				Bluetooth_Signal_ConfigurationResp(&SignalCommandHeader);
				break;
			case BT_SIGNAL_DISCONNECTION_REQUEST:
				Bluetooth_Signal_DisconnectionReq(&SignalCommandHeader);
				break;
			case BT_SIGNAL_DISCONNECTION_RESPONSE:
				Bluetooth_Signal_DisconnectionResp(&SignalCommandHeader);
				break;
			case BT_SIGNAL_ECHO_REQUEST:
				Bluetooth_Signal_EchoReq(&SignalCommandHeader);
				break;
			case BT_SIGNAL_INFORMATION_REQUEST:
				Bluetooth_Signal_InformationReq(&SignalCommandHeader);
				break;
			case BT_SIGNAL_COMMAND_REJECT:
				BT_ACL_DEBUG(1, "<< Command Reject");
				
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
		/* Non-signalling packet received, read in the packet contents and pass to the user application */
		uint8_t PacketData[DataHeader.PayloadLength];
		Pipe_Read_Stream_LE(PacketData, DataHeader.PayloadLength);
		Pipe_ClearIN();
		Pipe_Freeze();

		Bluetooth_PacketReceived(PacketData, DataHeader.PayloadLength,
		                         Bluetooth_GetChannelData(DataHeader.DestinationChannel, CHANNEL_SEARCH_LOCALNUMBER));
	}
}

/** Sends a packet to the remote device on the specified channel.
 *
 * \param[in] Data     Pointer to a buffer where the data is to be sourced from
 * \param[in] DataLen  Length of the data to send
 * \param[in] Channel  Channel information structure containing the destination channel's information, NULL to send
 *                     to the remote device's signalling channel
 *
 * \return A value from the \ref BT_SendPacket_ErrorCodes_t enum
 */
uint8_t Bluetooth_SendPacket(void* Data, const uint16_t DataLen, Bluetooth_Channel_t* const Channel)
{
	BT_ACL_Header_t        ACLPacketHeader;
	BT_DataPacket_Header_t DataHeader;

	/* A remote device must be connected before a packet transmission is attempted */
	if (!(Bluetooth_Connection.IsConnected))
	  return BT_SENDPACKET_NotConnected;

	/* If the destination channel is not the signalling channel and it is not currently fully open, abort */
	if ((Channel != NULL) && (Channel->State != Channel_Open))
	  return BT_SENDPACKET_ChannelNotOpen;

	/* Fill out the packet's header from the remote device connection information structure */
	ACLPacketHeader.ConnectionHandle      = (Bluetooth_Connection.ConnectionHandle | BT_ACL_FIRST_AUTOFLUSH);
	ACLPacketHeader.DataLength            = sizeof(DataHeader) + DataLen;
	DataHeader.PayloadLength              = DataLen;
	DataHeader.DestinationChannel         = (Channel == NULL) ? BT_CHANNEL_SIGNALING : Channel->RemoteNumber;

	Pipe_SelectPipe(BLUETOOTH_DATA_OUT_PIPE);
	Pipe_Unfreeze();
	
	/* Write the packet contents to the pipe so that it can be sent to the remote device */
	Pipe_Write_Stream_LE(&ACLPacketHeader, sizeof(ACLPacketHeader));
	Pipe_Write_Stream_LE(&DataHeader, sizeof(DataHeader));
	Pipe_Write_Stream_LE(Data, DataLen);
	Pipe_ClearOUT();
	
	Pipe_Freeze();
	
	BT_ACL_DEBUG(2, "");
	BT_ACL_DEBUG(2, "Packet Sent");
	BT_ACL_DEBUG(2, "-- Connection Handle: 0x%04X", (ACLPacketHeader.ConnectionHandle & 0x0FFF));
	BT_ACL_DEBUG(2, "-- Data Length: 0x%04X", ACLPacketHeader.DataLength);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", DataHeader.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Payload Length: 0x%04X", DataHeader.PayloadLength);

	return BT_SENDPACKET_NoError;
}

/** Opens a bluetooth channel to the currently connected remote device, so that data can be exchanged.
 *
 *  \note The channel is not immediately opened when this function returns - it must undergo a two way
 *        connection and configuration process first as the main Bluetooth stack processing task is
 *        repeatedly called. The returned channel is unusable by the user application until its State
 *        element has progressed to the Open state.
 *
 *  \param[in] PSM  PSM of the service that the channel is to be opened for
 *
 *  \return Pointer to the channel information structure of the opened channel, or NULL if no free channels
 */
Bluetooth_Channel_t* Bluetooth_OpenChannel(const uint16_t PSM)
{
	Bluetooth_Channel_t* ChannelData = NULL;

	/* Search through the channel information list for a free channel item */
	for (uint8_t i = 0; i < BLUETOOTH_MAX_OPEN_CHANNELS; i++)
	{
		if (Bluetooth_Connection.Channels[i].State == Channel_Closed)
		{
			ChannelData = &Bluetooth_Connection.Channels[i];
			
			/* Set the new channel structure's local channel number to a unique value within the connection orientated
			   channel address space */
			ChannelData->LocalNumber = (BT_CHANNELNUMBER_BASEOFFSET + i);
			break;
		}
	}

	/* If no free channel item was found in the list, all channels are occupied - abort */
	if (ChannelData == NULL)
	  return NULL;

	/* Reset and fill out the allocated channel's information structure with defaults */
	ChannelData->RemoteNumber = 0;
	ChannelData->PSM          = PSM;
	ChannelData->LocalMTU     = MAXIMUM_CHANNEL_MTU;
	ChannelData->State        = Channel_WaitConnectRsp;
	  
	struct
	{
		BT_Signal_Header_t        SignalCommandHeader;
		BT_Signal_ConnectionReq_t ConnectionRequest;
	} PacketData;

	/* Fill out the Signal Command header in the response packet */
	PacketData.SignalCommandHeader.Code              = BT_SIGNAL_CONNECTION_REQUEST;
	PacketData.SignalCommandHeader.Identifier        = ++Bluetooth_Connection.SignallingIdentifier;
	PacketData.SignalCommandHeader.Length            = sizeof(PacketData.ConnectionRequest);
	
	/* Fill out the Connection Request in the response packet */
	PacketData.ConnectionRequest.PSM                 = PSM;
	PacketData.ConnectionRequest.SourceChannel       = ChannelData->LocalNumber;
	
	Bluetooth_SendPacket(&PacketData, sizeof(PacketData), NULL);

	BT_ACL_DEBUG(1, ">> L2CAP Connection Request");
	BT_ACL_DEBUG(2, "-- PSM 0x%04X", PacketData.ConnectionRequest.PSM);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", PacketData.ConnectionRequest.SourceChannel);

	return ChannelData;
}

/** Closes a bluetooth channel that is open to the currently connected remote device, so that no further data
 *  can be exchanged.
 *
 *  \note The channel is not immediately closed when this function returns - it must undergo an asynchronous
 *        disconnection process first as the main Bluetooth stack processing task is repeatedly called. The
 *        returned channel is unusable by the user application upon return however the channel is not completely
 *        closed until its State element has progressed to the Closed state.
 *
 * \param[in,out] Channel  Channel information structure of the channel to close
 */
void Bluetooth_CloseChannel(Bluetooth_Channel_t* const Channel)
{
	/* Don't try to close a non-existing or already closed channel */
	if ((Channel == NULL) || (Channel->State == Channel_Closed))
	  return;

	/* Set the channel's state to the start of the teardown process */
	Channel->State = Channel_WaitDisconnect;

	struct
	{
		BT_Signal_Header_t           SignalCommandHeader;
		BT_Signal_DisconnectionReq_t DisconnectionRequest;
	} PacketData;
	
	/* Fill out the Signal Command header in the response packet */
	PacketData.SignalCommandHeader.Code            = BT_SIGNAL_DISCONNECTION_REQUEST;
	PacketData.SignalCommandHeader.Identifier      = ++Bluetooth_Connection.SignallingIdentifier;
	PacketData.SignalCommandHeader.Length          = sizeof(PacketData.DisconnectionRequest);

	/* Fill out the Disconnection Request in the response packet */
	PacketData.DisconnectionRequest.DestinationChannel = Channel->RemoteNumber;
	PacketData.DisconnectionRequest.SourceChannel = Channel->LocalNumber;

	Bluetooth_SendPacket(&PacketData, sizeof(PacketData), NULL);
	
	BT_ACL_DEBUG(1, ">> L2CAP Disconnection Request");
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", PacketData.DisconnectionRequest.DestinationChannel);	
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", PacketData.DisconnectionRequest.SourceChannel);	
}

/** Internal Bluetooth stack Signal Command processing routine for a Connection Request command.
 *
 *  \param[in]  SignalCommandHeader  Pointer to the start of the received packet's Signal Command header
 */
static inline void Bluetooth_Signal_ConnectionReq(const BT_Signal_Header_t* const SignalCommandHeader)
{
	BT_Signal_ConnectionReq_t ConnectionRequest;
	
	Pipe_Read_Stream_LE(&ConnectionRequest, sizeof(ConnectionRequest));

	Pipe_ClearIN();
	Pipe_Freeze();

	BT_ACL_DEBUG(1, "<< L2CAP Connection Request");
	BT_ACL_DEBUG(2, "-- PSM: 0x%04X", ConnectionRequest.PSM);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ConnectionRequest.SourceChannel);
	
	/* Try to retrieve the existing channel's information structure if it exists */
	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(ConnectionRequest.SourceChannel, CHANNEL_SEARCH_REMOTENUMBER);

	/* If an existing channel item with the correct remote channel number was not found, find a free channel entry */
	if (ChannelData == NULL)
	{
		/* Look through the channel information list for a free entry */
		for (uint8_t i = 0; i < BLUETOOTH_MAX_OPEN_CHANNELS; i++)
		{
			if (Bluetooth_Connection.Channels[i].State == Channel_Closed)
			{
				ChannelData = &Bluetooth_Connection.Channels[i];

				/* Set the new channel structure's local channel number to a unique value within the connection orientated
				   channel address space */
				ChannelData->LocalNumber = (BT_CHANNELNUMBER_BASEOFFSET + i);
				break;
			}
		}
	}
	
	uint8_t ChannelStatus = BT_CONNECTION_REFUSED_RESOURCES;

	/* Reset the channel item contents only if a channel entry was found for it */
	if (ChannelData != NULL)
	{
		/* Check if the user application will allow the connection based on its PSM */
		if (Bluetooth_ChannelConnectionRequest(ConnectionRequest.PSM))
		{
			ChannelData->RemoteNumber = ConnectionRequest.SourceChannel;
			ChannelData->PSM          = ConnectionRequest.PSM;
			ChannelData->LocalMTU     = MAXIMUM_CHANNEL_MTU;
			ChannelData->State        = Channel_Config_WaitConfig;
			
			ChannelStatus = BT_CONNECTION_SUCCESSFUL;
		}
		else
		{
			ChannelStatus = BT_CONNECTION_REFUSED_PSM;		
		}
	}
	
	struct
	{
		BT_Signal_Header_t         SignalCommandHeader;
		BT_Signal_ConnectionResp_t ConnectionResponse;
	} ResponsePacket;

	/* Fill out the Signal Command header in the response packet */
	ResponsePacket.SignalCommandHeader.Code              = BT_SIGNAL_CONNECTION_RESPONSE;
	ResponsePacket.SignalCommandHeader.Identifier        = SignalCommandHeader->Identifier;
	ResponsePacket.SignalCommandHeader.Length            = sizeof(ResponsePacket.ConnectionResponse);

	/* Fill out the Connection Response in the response packet */
	ResponsePacket.ConnectionResponse.DestinationChannel = ChannelData->LocalNumber;
	ResponsePacket.ConnectionResponse.SourceChannel      = ChannelData->RemoteNumber;
	ResponsePacket.ConnectionResponse.Result             = ChannelStatus;
	ResponsePacket.ConnectionResponse.Status             = 0x00;
	
	Bluetooth_SendPacket(&ResponsePacket, sizeof(ResponsePacket), NULL);

	BT_ACL_DEBUG(1, ">> L2CAP Connection Response");
	BT_ACL_DEBUG(2, "-- Result: 0x%02X", ResponsePacket.ConnectionResponse.Result);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", ResponsePacket.ConnectionResponse.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ResponsePacket.ConnectionResponse.SourceChannel);
}

/** Internal Bluetooth stack Signal Command processing routine for a Connection Response command.
 *
 *  \param[in]  SignalCommandHeader  Pointer to the start of the received packet's Signal Command header
 */
static inline void Bluetooth_Signal_ConnectionResp(const BT_Signal_Header_t* const SignalCommandHeader)
{
	BT_Signal_ConnectionResp_t ConnectionResponse;
	
	Pipe_Read_Stream_LE(&ConnectionResponse, sizeof(ConnectionResponse));

	Pipe_ClearIN();
	Pipe_Freeze();

	BT_ACL_DEBUG(1, "<< L2CAP Connection Response");
	BT_ACL_DEBUG(2, "-- Result: 0x%02X", ConnectionResponse.Result);	
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ConnectionResponse.SourceChannel);	
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", ConnectionResponse.DestinationChannel);	

	/* Search for the referenced channel in the channel information list */
	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(ConnectionResponse.SourceChannel, CHANNEL_SEARCH_LOCALNUMBER);

	/* Only progress if the referenced channel data was found */
	if (ChannelData != NULL)
	{
		/* Set the channel structure's remote channel number to the channel allocated on the remote device */
		ChannelData->RemoteNumber = ConnectionResponse.SourceChannel;
		ChannelData->State        = (ConnectionResponse.Result == BT_CONNECTION_SUCCESSFUL) ?
		                             Channel_Config_WaitConfig : Channel_Closed;
	}
}

/** Internal Bluetooth stack Signal Command processing routine for a Configuration Request command.
 *
 *  \param[in]  SignalCommandHeader  Pointer to the start of the received packet's Signal Command header
 */
static inline void Bluetooth_Signal_ConfigurationReq(const BT_Signal_Header_t* const SignalCommandHeader)
{
	BT_Signal_ConfigurationReq_t ConfigurationRequest;
	
	/* Allocate a buffer large enough to hold the variable number of configuration options in the request */
	uint8_t OptionsLen = (SignalCommandHeader->Length - sizeof(ConfigurationRequest));
	uint8_t Options[OptionsLen];

	Pipe_Read_Stream_LE(&ConfigurationRequest, sizeof(ConfigurationRequest));	
	Pipe_Read_Stream_LE(&Options, sizeof(Options));

	Pipe_ClearIN();
	Pipe_Freeze();

	/* Search for the referenced channel in the channel information list */
	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(ConfigurationRequest.DestinationChannel, CHANNEL_SEARCH_LOCALNUMBER);

	BT_ACL_DEBUG(1, "<< L2CAP Configuration Request");
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", ConfigurationRequest.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Remote MTU: 0x%04X", ChannelData->RemoteMTU);
	BT_ACL_DEBUG(2, "-- Options Len: 0x%04X", OptionsLen);

	/* Only look at the channel configuration options if a valid channel entry for the local channel number was found */
	if (ChannelData != NULL)
	{
		/* Iterate through each option in the configuration request to look for ones which can be processed */
		uint8_t OptionPos = 0;
		while (OptionPos < OptionsLen)
		{
			BT_Config_Option_Header_t* OptionHeader = (BT_Config_Option_Header_t*)&Options[OptionPos];
			void*                      OptionData   = &Options[OptionPos + sizeof(BT_Config_Option_Header_t)];

			BT_ACL_DEBUG(2, "-- Option Type: 0x%04X", OptionHeader->Type);
			BT_ACL_DEBUG(2, "-- Option Length: 0x%04X", (sizeof(BT_Config_Option_Header_t) + OptionHeader->Length));
			
			/* Store the remote MTU option's value if present */
			if (OptionHeader->Type == BT_CONFIG_OPTION_MTU)
			  ChannelData->RemoteMTU = *((uint16_t*)OptionData);

			/* Progress to the next option in the packet */
			OptionPos += (sizeof(BT_Config_Option_Header_t) + OptionHeader->Length);
		}
	}
	
	struct
	{
		BT_Signal_Header_t            SignalCommandHeader;
		BT_Signal_ConfigurationResp_t ConfigurationResponse;
	} ResponsePacket;

	/* Fill out the Signal Command header in the response packet */
	ResponsePacket.SignalCommandHeader.Code              = BT_SIGNAL_CONFIGURATION_RESPONSE;
	ResponsePacket.SignalCommandHeader.Identifier        = SignalCommandHeader->Identifier;
	ResponsePacket.SignalCommandHeader.Length            = sizeof(ResponsePacket.ConfigurationResponse);

	/* Fill out the Configuration Response in the response packet */
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

	BT_ACL_DEBUG(1, ">> L2CAP Configuration Response");
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ResponsePacket.ConfigurationResponse.SourceChannel);
	BT_ACL_DEBUG(2, "-- Result: 0x%02X", ResponsePacket.ConfigurationResponse.Result);
}

/** Internal Bluetooth stack Signal Command processing routine for a Configuration Response command.
 *
 *  \param[in]  SignalCommandHeader  Pointer to the start of the received packet's Signal Command header
 */
static inline void Bluetooth_Signal_ConfigurationResp(const BT_Signal_Header_t* const SignalCommandHeader)
{
	BT_Signal_ConfigurationResp_t ConfigurationResponse;

	Pipe_Read_Stream_LE(&ConfigurationResponse, sizeof(ConfigurationResponse));

	Pipe_ClearIN();
	Pipe_Freeze();
	
	BT_ACL_DEBUG(1, "<< L2CAP Configuration Response");
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ConfigurationResponse.SourceChannel);
	BT_ACL_DEBUG(2, "-- Result: 0x%02X", ConfigurationResponse.Result);

	/* Search for the referenced channel in the channel information list */
	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(ConfigurationResponse.SourceChannel, CHANNEL_SEARCH_REMOTENUMBER);
	
	/* Only update the channel's state if it was found in the channel list */
	if (ChannelData != NULL)
	{
		/* Check if the channel configuration completed successfuly */
		if (ConfigurationResponse.Result == BT_CONFIGURATION_SUCCESSFUL)
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
		else
		{
			/* Configuration failed - close the channel */
			ChannelData->State = Channel_Closed;
		}
	}
}

/** Internal Bluetooth stack Signal Command processing routine for a Disconnection Request command.
 *
 *  \param[in]  SignalCommandHeader  Pointer to the start of the received packet's Signal Command header
 */
static inline void Bluetooth_Signal_DisconnectionReq(const BT_Signal_Header_t* const SignalCommandHeader)
{
	BT_Signal_DisconnectionReq_t DisconnectionRequest;
	
	Pipe_Read_Stream_LE(&DisconnectionRequest, sizeof(DisconnectionRequest));

	BT_ACL_DEBUG(1, "<< L2CAP Disconnection Request");
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", DisconnectionRequest.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", DisconnectionRequest.SourceChannel);
	
	Pipe_ClearIN();
	Pipe_Freeze();
	
	/* Search for the referenced channel in the channel information list */
	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(DisconnectionRequest.SourceChannel, CHANNEL_SEARCH_REMOTENUMBER);

	struct
	{
		BT_Signal_Header_t            SignalCommandHeader;
		BT_Signal_DisconnectionResp_t DisconnectionResponse;
	} ResponsePacket;

	/* Fill out the Signal Command header in the response packet */
	ResponsePacket.SignalCommandHeader.Code                 = BT_SIGNAL_DISCONNECTION_RESPONSE;
	ResponsePacket.SignalCommandHeader.Identifier           = SignalCommandHeader->Identifier;
	ResponsePacket.SignalCommandHeader.Length               = sizeof(ResponsePacket.DisconnectionResponse);

	/* Fill out the Disconnection Response in the response packet */
	ResponsePacket.DisconnectionResponse.DestinationChannel = ChannelData->RemoteNumber;
	ResponsePacket.DisconnectionResponse.SourceChannel      = ChannelData->LocalNumber;

	Bluetooth_SendPacket(&ResponsePacket, sizeof(ResponsePacket), NULL);

	/* If the channel was found in the channel list, close it */
	if (ChannelData != NULL)
	  ChannelData->State = Channel_Closed;

	BT_ACL_DEBUG(1, ">> L2CAP Disconnection Response");
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", ResponsePacket.DisconnectionResponse.SourceChannel);
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", ResponsePacket.DisconnectionResponse.DestinationChannel);
}

/** Internal Bluetooth stack Signal Command processing routine for a Disconnection Response command.
 *
 *  \param[in]  SignalCommandHeader  Pointer to the start of the received packet's Signal Command header
 */
static inline void Bluetooth_Signal_DisconnectionResp(const BT_Signal_Header_t* const SignalCommandHeader)
{
	BT_Signal_DisconnectionResp_t DisconnectionResponse;
	
	Pipe_Read_Stream_LE(&DisconnectionResponse, sizeof(DisconnectionResponse));

	BT_ACL_DEBUG(1, "<< L2CAP Disconnection Response");
	BT_ACL_DEBUG(2, "-- Destination Channel: 0x%04X", DisconnectionResponse.DestinationChannel);
	BT_ACL_DEBUG(2, "-- Source Channel: 0x%04X", DisconnectionResponse.SourceChannel);
	
	Pipe_ClearIN();
	Pipe_Freeze();
	
	/* Search for the referenced channel in the channel information list */
	Bluetooth_Channel_t* ChannelData = Bluetooth_GetChannelData(DisconnectionResponse.SourceChannel, CHANNEL_SEARCH_REMOTENUMBER);
	
	/* If the channel was found in the channel list, close it */	
	if (ChannelData != NULL)
	  ChannelData->State = Channel_Closed;
}

/** Internal Bluetooth stack Signal Command processing routine for an Echo Request command.
 *
 *  \param[in]  SignalCommandHeader  Pointer to the start of the received packet's Signal Command header
 */
static inline void Bluetooth_Signal_EchoReq(const BT_Signal_Header_t* const SignalCommandHeader)
{
	BT_ACL_DEBUG(1, "<< L2CAP Echo Request");
	
	Pipe_ClearIN();
	Pipe_Freeze();
	
	struct
	{
		BT_Signal_Header_t SignalCommandHeader;
	} ResponsePacket;

	/* Fill out the Signal Command header in the response packet */
	ResponsePacket.SignalCommandHeader.Code                 = BT_SIGNAL_ECHO_RESPONSE;
	ResponsePacket.SignalCommandHeader.Identifier           = SignalCommandHeader->Identifier;
	ResponsePacket.SignalCommandHeader.Length               = 0;
	
	Bluetooth_SendPacket(&ResponsePacket, sizeof(ResponsePacket), NULL);

	BT_ACL_DEBUG(1, ">> L2CAP Echo Response");
}

/** Internal Bluetooth stack Signal Command processing routine for an Information Request command.
 *
 *  \param[in]  SignalCommandHeader  Pointer to the start of the received packet's Signal Command header
 */
static inline void Bluetooth_Signal_InformationReq(const BT_Signal_Header_t* const SignalCommandHeader)
{
	BT_Signal_InformationReq_t InformationRequest;

	Pipe_Read_Stream_LE(&InformationRequest, sizeof(InformationRequest));

	BT_ACL_DEBUG(1, "<< L2CAP Information Request");
	BT_ACL_DEBUG(2, "-- Info Type: 0x%04X", InformationRequest.InfoType);
	
	Pipe_ClearIN();
	Pipe_Freeze();

	struct
	{
		BT_Signal_Header_t          SignalCommandHeader;
		BT_Signal_InformationResp_t InformationResponse;
		
		uint8_t Data[4];
	} ResponsePacket;
	
	uint8_t DataLen = 0;
	
	/* Retrieve the requested information and store it in the outgoing packet, if found */
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
	
	/* Fill out the Signal Command header in the response packet */
	ResponsePacket.SignalCommandHeader.Code                 = BT_SIGNAL_INFORMATION_RESPONSE;
	ResponsePacket.SignalCommandHeader.Identifier           = SignalCommandHeader->Identifier;
	ResponsePacket.SignalCommandHeader.Length               = sizeof(ResponsePacket.InformationResponse) + DataLen;

	/* Fill out the Information Response in the response packet */
	ResponsePacket.InformationResponse.InfoType = InformationRequest.InfoType;
	
	Bluetooth_SendPacket(&ResponsePacket, (sizeof(ResponsePacket) - sizeof(ResponsePacket.Data) + DataLen), NULL);

	BT_ACL_DEBUG(1, ">> L2CAP Information Response");	
	BT_ACL_DEBUG(2, "-- Result: 0x%02X", ResponsePacket.InformationResponse.Result);
}
