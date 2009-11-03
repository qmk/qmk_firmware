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

#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_HOST)

#define  INCLUDE_FROM_MIDI_CLASS_HOST_C
#include "MIDI.h"

uint8_t MIDI_Host_ConfigurePipes(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo, uint16_t ConfigDescriptorSize,
                                 uint8_t* ConfigDescriptorData)
{
	uint8_t FoundEndpoints = 0;

	memset(&MIDIInterfaceInfo->State, 0x00, sizeof(MIDIInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return MIDI_ENUMERROR_InvalidConfigDescriptor;
	
	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
	                              DComp_MIDI_Host_NextMIDIStreamingInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return MIDI_ENUMERROR_NoStreamingInterfaceFound;
	}
	
	while (FoundEndpoints != (MIDI_FOUND_DATAPIPE_IN | MIDI_FOUND_DATAPIPE_OUT))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DComp_MIDI_Host_NextMIDIStreamingDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			return MIDI_ENUMERROR_EndpointsNotFound;
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
		{
			Pipe_ConfigurePipe(MIDIInterfaceInfo->Config.DataINPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_IN,
							   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
			MIDIInterfaceInfo->State.DataINPipeSize = EndpointData->EndpointSize;
			
			FoundEndpoints |= MIDI_FOUND_DATAPIPE_IN;
		}
		else
		{
			Pipe_ConfigurePipe(MIDIInterfaceInfo->Config.DataOUTPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_OUT,
							   EndpointData->EndpointAddress, EndpointData->EndpointSize, PIPE_BANK_SINGLE);
			MIDIInterfaceInfo->State.DataOUTPipeSize = EndpointData->EndpointSize;

			FoundEndpoints |= MIDI_FOUND_DATAPIPE_OUT;
		}
	}
	
	MIDIInterfaceInfo->State.IsActive = true;
	return MIDI_ENUMERROR_NoError;
}

static uint8_t DComp_MIDI_Host_NextMIDIStreamingInterface(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* CurrentInterface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                                USB_Descriptor_Interface_t);

		if ((CurrentInterface->Class    == MIDI_STREAMING_CLASS)    &&
		    (CurrentInterface->SubClass == MIDI_STREAMING_SUBCLASS) &&
		    (CurrentInterface->Protocol == MIDI_STREAMING_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DComp_MIDI_Host_NextMIDIStreamingDataEndpoint(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* CurrentEndpoint = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                              USB_Descriptor_Endpoint_t);
	
		uint8_t EndpointType = (CurrentEndpoint->Attributes & EP_TYPE_MASK);
	
		if ((EndpointType == EP_TYPE_BULK) && !(Pipe_IsEndpointBound(CurrentEndpoint->EndpointAddress)))
		  return DESCRIPTOR_SEARCH_Found;
	}
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

void MIDI_Host_USBTask(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo)
{

}

uint8_t MIDI_Host_SendEventPacket(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo, MIDI_EventPacket_t* const Event)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MIDIInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnect;
	
	Pipe_SelectPipe(MIDIInterfaceInfo->Config.DataOUTPipeNumber);

	if (Pipe_IsReadWriteAllowed());
	{
		uint8_t ErrorCode;

		if ((ErrorCode = Pipe_Write_Stream_LE(Event, sizeof(MIDI_EventPacket_t), NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
		  return ErrorCode;

		Pipe_ClearOUT();
	}
	
	return PIPE_RWSTREAM_NoError;
}

bool MIDI_Host_ReceiveEventPacket(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo, MIDI_EventPacket_t* const Event)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MIDIInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnect;
	
	Pipe_SelectPipe(MIDIInterfaceInfo->Config.DataINPipeNumber);

	if (!(Pipe_IsReadWriteAllowed()))
	  return false;

	Pipe_Read_Stream_LE(Event, sizeof(MIDI_EventPacket_t), NO_STREAM_CALLBACK);
	Pipe_ClearIN();
	
	return true;
}

#endif
