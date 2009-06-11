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

#include "MIDI.h"

void MIDI_Device_ProcessControlPacket(USB_ClassInfo_MIDI_t* MIDIInterfaceInfo)
{

}

bool MIDI_Device_ConfigureEndpoints(USB_ClassInfo_MIDI_t* MIDIInterfaceInfo)
{
	if (MIDIInterfaceInfo->DataINEndpointNumber)
	{
		if (!(Endpoint_ConfigureEndpoint(MIDIInterfaceInfo->DataINEndpointNumber, EP_TYPE_BULK,
										 ENDPOINT_DIR_IN, MIDIInterfaceInfo->DataINEndpointSize,
										 ENDPOINT_BANK_SINGLE)))
		{
			return false;
		}
	}

	if (MIDIInterfaceInfo->DataOUTEndpointNumber)
	{
		if (!(Endpoint_ConfigureEndpoint(MIDIInterfaceInfo->DataOUTEndpointNumber, EP_TYPE_BULK,
										 ENDPOINT_DIR_OUT, MIDIInterfaceInfo->DataOUTEndpointSize,
										 ENDPOINT_BANK_SINGLE)))
		{
			return false;
		}
	}

	return true;
}

void MIDI_Device_USBTask(USB_ClassInfo_MIDI_t* MIDIInterfaceInfo)
{

}

void MIDI_Device_SendEventPacket(USB_ClassInfo_MIDI_t* MIDIInterfaceInfo, USB_MIDI_EventPacket_t* Event)
{
	if (!(USB_IsConnected))
	  return;
	
	Endpoint_SelectEndpoint(MIDIInterfaceInfo->DataINEndpointNumber);

	if (Endpoint_IsReadWriteAllowed());
	{
		Endpoint_Write_Stream_LE(Event, sizeof(USB_MIDI_EventPacket_t), NO_STREAM_CALLBACK);
		Endpoint_ClearIN();
	}
}

bool MIDI_Device_ReceiveEventPacket(USB_ClassInfo_MIDI_t* MIDIInterfaceInfo, USB_MIDI_EventPacket_t* Event)
{
	if (!(USB_IsConnected))
	  return false;
	
	Endpoint_SelectEndpoint(MIDIInterfaceInfo->DataOUTEndpointNumber);

	if (!(Endpoint_IsReadWriteAllowed()))
	  return false;

	Endpoint_Read_Stream_LE(Event, sizeof(USB_MIDI_EventPacket_t), NO_STREAM_CALLBACK);
	Endpoint_ClearOUT();
	
	return true;
}
