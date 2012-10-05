/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#define  __INCLUDE_FROM_USB_DRIVER
#include "../../Core/USBMode.h"

#if defined(USB_CAN_BE_DEVICE)

#define  __INCLUDE_FROM_MIDI_DRIVER
#define  __INCLUDE_FROM_MIDI_DEVICE_C
#include "MIDIClassDevice.h"

bool MIDI_Device_ConfigureEndpoints(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo)
{
	memset(&MIDIInterfaceInfo->State, 0x00, sizeof(MIDIInterfaceInfo->State));

	MIDIInterfaceInfo->Config.DataINEndpoint.Type  = EP_TYPE_BULK;
	MIDIInterfaceInfo->Config.DataOUTEndpoint.Type = EP_TYPE_BULK;

	if (!(Endpoint_ConfigureEndpointTable(&MIDIInterfaceInfo->Config.DataINEndpoint, 1)))
	  return false;

	if (!(Endpoint_ConfigureEndpointTable(&MIDIInterfaceInfo->Config.DataOUTEndpoint, 1)))
	  return false;

	return true;
}

void MIDI_Device_USBTask(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	#if !defined(NO_CLASS_DRIVER_AUTOFLUSH)
	Endpoint_SelectEndpoint(MIDIInterfaceInfo->Config.DataINEndpoint.Address);
	
	if (Endpoint_IsINReady())
	  MIDI_Device_Flush(MIDIInterfaceInfo);
	#endif
}

uint8_t MIDI_Device_SendEventPacket(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo,
                                    const MIDI_EventPacket_t* const Event)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;

	uint8_t ErrorCode;

	Endpoint_SelectEndpoint(MIDIInterfaceInfo->Config.DataINEndpoint.Address);

	if ((ErrorCode = Endpoint_Write_Stream_LE(Event, sizeof(MIDI_EventPacket_t), NULL)) != ENDPOINT_RWSTREAM_NoError)
	  return ErrorCode;

	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearIN();

	return ENDPOINT_RWSTREAM_NoError;
}

uint8_t MIDI_Device_Flush(USB_ClassInfo_MIDI_Device_t* const MIDIInterfaceInfo)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;

	uint8_t ErrorCode;

	Endpoint_SelectEndpoint(MIDIInterfaceInfo->Config.DataINEndpoint.Address);

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

	Endpoint_SelectEndpoint(MIDIInterfaceInfo->Config.DataOUTEndpoint.Address);

	if (!(Endpoint_IsReadWriteAllowed()))
	  return false;

	Endpoint_Read_Stream_LE(Event, sizeof(MIDI_EventPacket_t), NULL);

	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearOUT();

	return true;
}

#endif

