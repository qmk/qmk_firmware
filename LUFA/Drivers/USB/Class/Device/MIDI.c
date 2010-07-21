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

#define  __INCLUDE_FROM_USB_DRIVER
#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_DEVICE)

#define  __INCLUDE_FROM_MIDI_DRIVER
#include "MIDI.h"

bool MIDI_Device_ConfigureEndpoints(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo)
{
	memset(&MIDIInterfaceInfo->State, 0x00, sizeof(MIDIInterfaceInfo->State));

	if (MIDIInterfaceInfo->Config.DataINEndpointNumber)
	{
		if (!(Endpoint_ConfigureEndpoint(MIDIInterfaceInfo->Config.DataINEndpointNumber, EP_TYPE_BULK,
										 ENDPOINT_DIR_IN, MIDIInterfaceInfo->Config.DataINEndpointSize,
										 MIDIInterfaceInfo->Config.DataINEndpointDoubleBank ? ENDPOINT_BANK_DOUBLE : ENDPOINT_BANK_SINGLE)))
		{
			return false;
		}
	}

	if (MIDIInterfaceInfo->Config.DataOUTEndpointNumber)
	{
		if (!(Endpoint_ConfigureEndpoint(MIDIInterfaceInfo->Config.DataOUTEndpointNumber, EP_TYPE_BULK,
										 ENDPOINT_DIR_OUT, MIDIInterfaceInfo->Config.DataOUTEndpointSize,
										 MIDIInterfaceInfo->Config.DataOUTEndpointDoubleBank ? ENDPOINT_BANK_DOUBLE : ENDPOINT_BANK_SINGLE)))
		{
			return false;
		}
	}

	return true;
}

uint8_t MIDI_Device_SendEventPacket(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo,
                                    const MIDI_EventPacket_t* const Event)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;
	
	Endpoint_SelectEndpoint(MIDIInterfaceInfo->Config.DataINEndpointNumber);

	if (Endpoint_IsReadWriteAllowed())
	{
		uint8_t ErrorCode;

		if ((ErrorCode = Endpoint_Write_Stream_LE(Event, sizeof(MIDI_EventPacket_t), NO_STREAM_CALLBACK)) != ENDPOINT_RWSTREAM_NoError)
		  return ErrorCode;

		if (!(Endpoint_IsReadWriteAllowed()))
		  Endpoint_ClearIN();
	}
	
	return ENDPOINT_RWSTREAM_NoError;
}

uint8_t MIDI_Device_Flush(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;
	
	uint8_t ErrorCode;

	Endpoint_SelectEndpoint(MIDIInterfaceInfo->Config.DataINEndpointNumber);

	if (Endpoint_BytesInEndpoint())
	{
		Endpoint_ClearIN();

		if ((ErrorCode = Endpoint_WaitUntilReady()) != ENDPOINT_READYWAIT_NoError)
		  return ErrorCode;
	}

	return ENDPOINT_READYWAIT_NoError;
}

bool MIDI_Device_ReceiveEventPacket(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo,
                                    MIDI_EventPacket_t* const Event)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return false;
	
	Endpoint_SelectEndpoint(MIDIInterfaceInfo->Config.DataOUTEndpointNumber);

	if (!(Endpoint_IsReadWriteAllowed()))
	  return false;

	Endpoint_Read_Stream_LE(Event, sizeof(MIDI_EventPacket_t), NO_STREAM_CALLBACK);
	
	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearOUT();
	
	return true;
}

#endif
