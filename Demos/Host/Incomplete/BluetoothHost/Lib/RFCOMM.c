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
 *  RFCOMM layer module. This module manages the RFCOMM layer of the
 *  stack, providing virtual serial port channels on top of the lower
 *  L2CAP layer.
 */

#define  INCLUDE_FROM_RFCOMM_C
#include "RFCOMM.h"

/** 8-Bit CRC table used by the FCS field of each RFCOMM encoded frame, sourced from the ETSI TS 101 369 V7.2.0
 *  specification document, upon which the RFCOMM specification is based.
 */
const uint8_t CRC8_Table[256] PROGMEM =
	{
		0x00, 0x91, 0xE3, 0x72, 0x07, 0x96, 0xE4, 0x75, 0x0E, 0x9F, 0xED, 0x7C, 0x09, 0x98, 0xEA, 0x7B,
		0x1C, 0x8D, 0xFF, 0x6E, 0x1B, 0x8A, 0xF8, 0x69, 0x12, 0x83, 0xF1, 0x60, 0x15, 0x84, 0xF6, 0x67,
		0x38, 0xA9, 0xDB, 0x4A, 0x3F, 0xAE, 0xDC, 0x4D, 0x36, 0xA7, 0xD5, 0x44, 0x31, 0xA0, 0xD2, 0x43,
		0x24, 0xB5, 0xC7, 0x56, 0x23, 0xB2, 0xC0, 0x51, 0x2A, 0xBB, 0xC9, 0x58, 0x2D, 0xBC, 0xCE, 0x5F,
		0x70, 0xE1, 0x93, 0x02, 0x77, 0xE6, 0x94, 0x05, 0x7E, 0xEF, 0x9D, 0x0C, 0x79, 0xE8, 0x9A, 0x0B,
		0x6C, 0xFD, 0x8F, 0x1E, 0x6B, 0xFA, 0x88, 0x19, 0x62, 0xF3, 0x81, 0x10, 0x65, 0xF4, 0x86, 0x17,
		0x48, 0xD9, 0xAB, 0x3A, 0x4F, 0xDE, 0xAC, 0x3D, 0x46, 0xD7, 0xA5, 0x34, 0x41, 0xD0, 0xA2, 0x33,
		0x54, 0xC5, 0xB7, 0x26, 0x53, 0xC2, 0xB0, 0x21, 0x5A, 0xCB, 0xB9, 0x28, 0x5D, 0xCC, 0xBE, 0x2F,
		0xE0, 0x71, 0x03, 0x92, 0xE7, 0x76, 0x04, 0x95, 0xEE, 0x7F, 0x0D, 0x9C, 0xE9, 0x78, 0x0A, 0x9B,
		0xFC, 0x6D, 0x1F, 0x8E, 0xFB, 0x6A, 0x18, 0x89, 0xF2, 0x63, 0x11, 0x80, 0xF5, 0x64, 0x16, 0x87,
		0xD8, 0x49, 0x3B, 0xAA, 0xDF, 0x4E, 0x3C, 0xAD, 0xD6, 0x47, 0x35, 0xA4, 0xD1, 0x40, 0x32, 0xA3,
		0xC4, 0x55, 0x27, 0xB6, 0xC3, 0x52, 0x20, 0xB1, 0xCA, 0x5B, 0x29, 0xB8, 0xCD, 0x5C, 0x2E, 0xBF,
		0x90, 0x01, 0x73, 0xE2, 0x97, 0x06, 0x74, 0xE5, 0x9E, 0x0F, 0x7D, 0xEC, 0x99, 0x08, 0x7A, 0xEB,
		0x8C, 0x1D, 0x6F, 0xFE, 0x8B, 0x1A, 0x68, 0xF9, 0x82, 0x13, 0x61, 0xF0, 0x85, 0x14, 0x66, 0xF7,
		0xA8, 0x39, 0x4B, 0xDA, 0xAF, 0x3E, 0x4C, 0xDD, 0xA6, 0x37, 0x45, 0xD4, 0xA1, 0x30, 0x42, 0xD3,
		0xB4, 0x25, 0x57, 0xC6, 0xB3, 0x22, 0x50, 0xC1, 0xBA, 0x2B, 0x59, 0xC8, 0xBD, 0x2C, 0x5E, 0xCF
	};

/** RFCOMM channel state structure, to retain information about each open channel in the RFCOMM multiplexer. */
RFCOMM_Channel_t RFCOMM_Channels[RFCOMM_MAX_OPEN_CHANNELS];


/** Initialises the RFCOMM service, ready for new connections from a SDP client. */
void RFCOMM_Initialize(void)
{
	/* Reset the RFCOMM channel structures, to invalidate any configured RFCOMM channels */
	for (uint8_t i = 0; i < RFCOMM_MAX_OPEN_CHANNELS; i++)
	  RFCOMM_Channels[i].State = RFCOMM_Channel_Closed;
}

/** Services all the logical RFCOMM channels on the given ACL channel, sending any RFCOMM control requests to
 *  the remote device as needed to establish new logical RFCOMM channels. This function should be called repeatedly
 *  in the main program loop when an ACL channel with an RFCOMM PSM has been established between the local and remote
 *  device.
 *
 *  \param[in] ACLChannel  ACL channel which has been previously opened to handle RFCOMM traffic between devices
 */
void RFCOMM_ServiceChannels(Bluetooth_Channel_t* const ACLChannel)
{
	/* Abort if the RFCOMM ACL channel is not currently open */
	if ((ACLChannel == NULL) || (ACLChannel->State != BT_Channel_Open))
	  return;

	/* Loop through each of the RFCOMM channels, send any required RFCOMM control commands */
	for (uint8_t i = 0; i < RFCOMM_MAX_OPEN_CHANNELS; i++)
	{
		RFCOMM_Channel_t* RFCOMMChannel = &RFCOMM_Channels[i];

		if (RFCOMMChannel->State == RFCOMM_Channel_Configure)
		{
			/* Check if the local signals have not yet been sent on the current channel */
			if (!(RFCOMMChannel->ConfigFlags & RFCOMM_CONFIG_LOCALSIGNALSSENT))
			{
				/* Indicate that the local signals have been sent, transmit them to the remote device */
				RFCOMMChannel->ConfigFlags |= RFCOMM_CONFIG_LOCALSIGNALSSENT;
				RFCOMM_SendChannelSignals(RFCOMMChannel, ACLChannel);
			}

			/* If signals have been configured in both directions, progress to the open state */
			if ((RFCOMMChannel->ConfigFlags & (RFCOMM_CONFIG_REMOTESIGNALS | RFCOMM_CONFIG_LOCALSIGNALS)) ==
			                                  (RFCOMM_CONFIG_REMOTESIGNALS | RFCOMM_CONFIG_LOCALSIGNALS))
			{
				RFCOMMChannel->State = RFCOMM_Channel_Open;
				RFCOMM_ChannelOpened(RFCOMMChannel);
			}
		}
	}
}

/** Processes an incoming RFCOMM packet on an ACL channel which has been previously opened between the local and
 *  a remote device to handle RFCOMM traffic.
 *
 *  \param[in] Data        Incoming packet data containing the RFCOMM packet
 *  \param[in] ACLChannel  ACL channel the request was issued to by the remote device
 */
void RFCOMM_ProcessPacket(void* Data,
                          Bluetooth_Channel_t* const ACLChannel)
{
	const RFCOMM_Header_t* FrameHeader  = (const RFCOMM_Header_t*)Data;
	const uint8_t*         FrameData    = (const uint8_t*)Data + sizeof(RFCOMM_Header_t);
	uint16_t               FrameDataLen = RFCOMM_GetVariableFieldValue(&FrameData);

	/* Decode the RFCOMM frame type from the header */
	switch (FrameHeader->Control & ~FRAME_POLL_FINAL)
	{
		case RFCOMM_Frame_DM:
			RFCOMM_ProcessDM(&FrameHeader->Address, ACLChannel);
			break;
		case RFCOMM_Frame_DISC:
			RFCOMM_ProcessDISC(&FrameHeader->Address, ACLChannel);
			break;
		case RFCOMM_Frame_SABM:
			RFCOMM_ProcessSABM(&FrameHeader->Address, ACLChannel);
			break;
		case RFCOMM_Frame_UA:
			RFCOMM_ProcessUA(&FrameHeader->Address, ACLChannel);
			break;
		case RFCOMM_Frame_UIH:
			RFCOMM_ProcessUIH(&FrameHeader->Address, FrameDataLen, FrameData, ACLChannel);
			break;
		default:
			BT_RFCOMM_DEBUG(1, "<< Unknown Frame Received");
			break;
	}
}

/** Sends an RFCOMM notification to the remote device that the local terminal control signals (located in the
 *  "Local" structure of the RFCOMM channel) have changed, pushing the new signals to the remote device.
 *
 *  \param[in] RFCOMMChannel  RFCOMM logical channel whose local terminal signals have changed
 *  \param[in] ACLChannel     ACL channel which has been opened to carry RFCOMM traffic between devices
 */
void RFCOMM_SendChannelSignals(const RFCOMM_Channel_t* const RFCOMMChannel,
                               Bluetooth_Channel_t* const ACLChannel)
{
	BT_RFCOMM_DEBUG(1, ">> MSC Command");
	BT_RFCOMM_DEBUG(2, "-- DLCI 0x%02X", RFCOMMChannel->DLCI);

	struct
	{
		RFCOMM_Command_t        CommandHeader;
		uint8_t                 Length;
		RFCOMM_MSC_Parameters_t Params;
	} MSCommand;

	MSCommand.CommandHeader      = (RFCOMM_Command_t){.Command = RFCOMM_Control_ModemStatus, .EA = true, .CR = true};
	MSCommand.Length             = (sizeof(MSCommand.Params) << 1) | 0x01;
	MSCommand.Params.Channel     = (RFCOMM_Address_t){.DLCI = RFCOMMChannel->DLCI, .EA = true, .CR = true};
	MSCommand.Params.Signals     = RFCOMMChannel->Local.Signals;
	MSCommand.Params.BreakSignal = RFCOMMChannel->Local.BreakSignal;

	/* Send the MSC command to the remote device */
	RFCOMM_SendFrame(RFCOMM_CONTROL_DLCI, true, RFCOMM_Frame_UIH, sizeof(MSCommand), &MSCommand, ACLChannel);
}

/** Sends new data through an open logical RFCOMM channel. This should be used to transmit data through a
 *  RFCOMM channel once it has been opened.
 *
 *  \param[in] DataLen        Length of the RFCOMM data to send, in bytes
 *  \param[in] Data           Pointer to a buffer where the data to send is located
 *  \param[in] RFCOMMChannel  RFCOMM logical channel which is to be transmitted to
 *  \param[in] ACLChannel     ACL channel which has been opened to carry RFCOMM traffic between devices
 */
void RFCOMM_SendData(const uint16_t DataLen,
                     const uint8_t* Data,
                     const RFCOMM_Channel_t* const RFCOMMChannel,
                     Bluetooth_Channel_t* const ACLChannel)
{
	if (RFCOMMChannel->State != RFCOMM_Channel_Open)
	  return;

	BT_RFCOMM_DEBUG(1, ">> UIH Frame");
	BT_RFCOMM_DEBUG(2, "-- DLCI 0x%02X", RFCOMMChannel->DLCI);

	/* Send the MSC command to the remote device */
	RFCOMM_SendFrame(RFCOMMChannel->DLCI, false, RFCOMM_Frame_UIH, DataLen, Data, ACLChannel);
}

RFCOMM_Channel_t* RFCOMM_GetFreeChannelEntry(const uint8_t DLCI)
{
	/* Find a free entry in the RFCOMM channel multiplexer state array */
	for (uint8_t i = 0; i < RFCOMM_MAX_OPEN_CHANNELS; i++)
	{
		RFCOMM_Channel_t* RFCOMMChannel = &RFCOMM_Channels[i];

		/* If the channel's state is closed, the channel state entry is free */
		if (RFCOMMChannel->State == RFCOMM_Channel_Closed)
		{
			RFCOMMChannel->DLCI               = DLCI;
			RFCOMMChannel->State              = RFCOMM_Channel_Configure;
			RFCOMMChannel->Priority           = 7 + (RFCOMMChannel->DLCI & 0xF8);
			RFCOMMChannel->MTU                = 0xFFFF;
			RFCOMMChannel->Remote.Signals     = 0 | (1 << 0);
			RFCOMMChannel->Remote.BreakSignal = 0 | (1 << 0);
			RFCOMMChannel->Local.Signals      = RFCOMM_SIGNAL_RTC | RFCOMM_SIGNAL_RTR | RFCOMM_SIGNAL_DV | (1 << 0);
			RFCOMMChannel->Local.BreakSignal  = 0 | (1 << 0);
			RFCOMMChannel->ConfigFlags        = 0;

			return RFCOMMChannel;
		}
	}

	return NULL;
}

RFCOMM_Channel_t* RFCOMM_GetChannelData(const uint8_t DLCI)
{
	/* Search through the RFCOMM channel list, looking for the specified channel */
	for (uint8_t i = 0; i < RFCOMM_MAX_OPEN_CHANNELS; i++)
	{
		RFCOMM_Channel_t* CurrRFCOMMChannel = &RFCOMM_Channels[i];

		/* If the current non-closed channel's DLCI matches the search DLCI, return it to the caller */
		if ((CurrRFCOMMChannel->State != RFCOMM_Channel_Closed) && (CurrRFCOMMChannel->DLCI == DLCI))
		  return CurrRFCOMMChannel;
	}

	/* Channel not found in the channel state table, return failure */
	return NULL;
}

uint16_t RFCOMM_GetVariableFieldValue(const uint8_t** BufferPos)
{
	uint8_t FirstOctet;
	uint8_t SecondOctet = 0;

	FirstOctet = **BufferPos;
	(*BufferPos)++;

	/* If the field size is more than a single byte, fetch the next byte in the variable length field */
	if (!(FirstOctet & 0x01))
	{
		SecondOctet = **BufferPos;
		(*BufferPos)++;

		/* Discard any remaining bytes in the variable length field that won't fit in the return value */
		while (!(**BufferPos & 0x01))
		  (*BufferPos)++;
	}

	/* Bit-shift the bytes that comprise the variable length field so that they form a single integer */
	return (((uint16_t)SecondOctet << 7) | FirstOctet >> 1);
}

void RFCOMM_SendFrame(const uint8_t DLCI,
                      const bool CommandResponse,
                      const uint8_t Control,
                      const uint16_t DataLen,
                      const void* Data,
                      Bluetooth_Channel_t* const ACLChannel)
{
	struct
	{
		RFCOMM_Header_t FrameHeader;
		uint8_t         Size[(DataLen < 128) ? 1 : 2];
		uint8_t         Data[DataLen];
		uint8_t         FCS;
	} ResponsePacket;

	/* Set the frame header values to the specified address and frame type */
	ResponsePacket.FrameHeader.Control = Control;
	ResponsePacket.FrameHeader.Address = (RFCOMM_Address_t){.DLCI = DLCI, .EA   = true, .CR = CommandResponse};

	/* Set the lower 7 bits of the packet length */
	ResponsePacket.Size[0] = (DataLen << 1);

	/* Terminate the size field if size is 7 bits or lower, otherwise set the upper 8 bits of the length */
	if (DataLen < 128)
	  ResponsePacket.Size[0] |= 0x01;
	else
	  ResponsePacket.Size[1]  = (DataLen >> 7);

	/* Copy over the packet data from the source buffer to the response packet buffer */
	memcpy(ResponsePacket.Data, Data, DataLen);

	/* Determine the length of the frame which is to be used to calculate the CRC value */
	uint8_t CRCLength = sizeof(ResponsePacket.FrameHeader);

	/* UIH frames do not have the CRC calculated on the Size field in the response, all other frames do */
	if ((Control & ~FRAME_POLL_FINAL) != RFCOMM_Frame_UIH)
	  CRCLength += sizeof(ResponsePacket.Size);

	/* Calculate the frame checksum from the appropriate fields */
	ResponsePacket.FCS = RFCOMM_GetFCSValue(&ResponsePacket, CRCLength);

	/* Send the completed response packet to the sender */
	Bluetooth_SendPacket(&ResponsePacket, sizeof(ResponsePacket), ACLChannel);
}

static uint8_t RFCOMM_GetFCSValue(const void* FrameStart,
                                  uint8_t Length)
{
	uint8_t FCS = 0xFF;

	/* Calculate new Frame CRC value via the given data bytes and the CRC table */
	for (uint8_t i = 0; i < Length; i++)
	  FCS = pgm_read_byte(&CRC8_Table[FCS ^ ((const uint8_t*)FrameStart)[i]]);

	return ~FCS;
}

static void RFCOMM_ProcessDM(const RFCOMM_Address_t* const FrameAddress,
                             Bluetooth_Channel_t* const ACLChannel)
{
	BT_RFCOMM_DEBUG(1, "<< DM Received");
	BT_RFCOMM_DEBUG(2, "-- DLCI 0x%02X", FrameAddress->DLCI);
}

static void RFCOMM_ProcessDISC(const RFCOMM_Address_t* const FrameAddress,
                               Bluetooth_Channel_t* const ACLChannel)
{
	BT_RFCOMM_DEBUG(1, "<< DISC Received");
	BT_RFCOMM_DEBUG(2, "-- DLCI 0x%02X", FrameAddress->DLCI);

	RFCOMM_Channel_t* RFCOMMChannel = RFCOMM_GetChannelData(FrameAddress->DLCI);

	/* If the requested channel is currently open, destroy it */
	if (RFCOMMChannel != NULL)
	  RFCOMMChannel->State = RFCOMM_Channel_Closed;

	BT_RFCOMM_DEBUG(1, ">> UA Sent");
	RFCOMM_SendFrame(FrameAddress->DLCI, true, (RFCOMM_Frame_UA | FRAME_POLL_FINAL), 0, NULL, ACLChannel);
}

static void RFCOMM_ProcessSABM(const RFCOMM_Address_t* const FrameAddress,
                               Bluetooth_Channel_t* const ACLChannel)
{
	BT_RFCOMM_DEBUG(1, "<< SABM Received");
	BT_RFCOMM_DEBUG(2, "-- DLCI 0x%02X", FrameAddress->DLCI);

	if (FrameAddress->DLCI == RFCOMM_CONTROL_DLCI)
	{
		BT_RFCOMM_DEBUG(1, ">> UA Sent");

		/* Free channel found, or request was to the control channel - accept SABM by sending a UA frame */
		RFCOMM_SendFrame(FrameAddress->DLCI, true, (RFCOMM_Frame_UA | FRAME_POLL_FINAL), 0, NULL, ACLChannel);

		return;
	}

	/* Find the existing channel's entry in the channel table */
	RFCOMM_Channel_t* RFCOMMChannel = RFCOMM_GetChannelData(FrameAddress->DLCI);

	/* Existing entry not found, create a new entry for the channel */
	if (RFCOMMChannel == NULL)
	  RFCOMMChannel = RFCOMM_GetFreeChannelEntry(FrameAddress->DLCI);

	/* If space was found in the channel table for the new channel, ACK the request */
	if (RFCOMMChannel != NULL)
	{
		BT_RFCOMM_DEBUG(1, ">> UA Sent");

		/* Free channel found, or request was to the control channel - accept SABM by sending a UA frame */
		RFCOMM_SendFrame(FrameAddress->DLCI, true, (RFCOMM_Frame_UA | FRAME_POLL_FINAL), 0, NULL, ACLChannel);
	}
	else
	{
		BT_RFCOMM_DEBUG(1, ">> DM Sent");

		/* No free channel in the multiplexer - decline the SABM by sending a DM frame */
		RFCOMM_SendFrame(FrameAddress->DLCI, true, (RFCOMM_Frame_DM | FRAME_POLL_FINAL), 0, NULL, ACLChannel);
	}
}

static void RFCOMM_ProcessUA(const RFCOMM_Address_t* const FrameAddress,
                             Bluetooth_Channel_t* const ACLChannel)
{
	BT_RFCOMM_DEBUG(1, "<< UA Received");
	BT_RFCOMM_DEBUG(2, "-- DLCI 0x%02X", FrameAddress->DLCI);
}

static void RFCOMM_ProcessUIH(const RFCOMM_Address_t* const FrameAddress,
                              const uint16_t FrameLength,
                              const uint8_t* FrameData,
                              Bluetooth_Channel_t* const ACLChannel)
{
	if (FrameAddress->DLCI == RFCOMM_CONTROL_DLCI)
	{
		RFCOMM_ProcessControlCommand(FrameData, ACLChannel);
		return;
	}

	BT_RFCOMM_DEBUG(1, "<< UIH Received");
	BT_RFCOMM_DEBUG(2, "-- DLCI 0x%02X", FrameAddress->DLCI);
	BT_RFCOMM_DEBUG(2, "-- Length 0x%02X", FrameLength);

	RFCOMM_Channel_t* RFCOMMChannel = RFCOMM_GetChannelData(FrameAddress->DLCI);

	if (RFCOMMChannel != NULL)
	  RFCOMM_DataReceived(RFCOMMChannel, FrameLength, FrameData);
}

