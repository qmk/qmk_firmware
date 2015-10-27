/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_MIDI_DRIVER
#define  __INCLUDE_FROM_MIDI_HOST_C
#include "MIDIClassHost.h"

uint8_t MIDI_Host_ConfigurePipes(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo,
                                 uint16_t ConfigDescriptorSize,
                                 void* ConfigDescriptorData)
{
	USB_Descriptor_Endpoint_t*  DataINEndpoint  = NULL;
	USB_Descriptor_Endpoint_t*  DataOUTEndpoint = NULL;
	USB_Descriptor_Interface_t* MIDIInterface   = NULL;

	memset(&MIDIInterfaceInfo->State, 0x00, sizeof(MIDIInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return MIDI_ENUMERROR_InvalidConfigDescriptor;

	while (!(DataINEndpoint) || !(DataOUTEndpoint))
	{
		if (!(MIDIInterface) ||
		    USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DCOMP_MIDI_Host_NextMIDIStreamingDataEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
			                              DCOMP_MIDI_Host_NextMIDIStreamingInterface) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				return MIDI_ENUMERROR_NoCompatibleInterfaceFound;
			}

			MIDIInterface = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Interface_t);

			DataINEndpoint  = NULL;
			DataOUTEndpoint = NULL;

			continue;
		}

		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if ((EndpointData->EndpointAddress & ENDPOINT_DIR_MASK) == ENDPOINT_DIR_IN)
		  DataINEndpoint  = EndpointData;
		else
		  DataOUTEndpoint = EndpointData;
	}

	MIDIInterfaceInfo->Config.DataINPipe.Size  = le16_to_cpu(DataINEndpoint->EndpointSize);
	MIDIInterfaceInfo->Config.DataINPipe.EndpointAddress = DataINEndpoint->EndpointAddress;
	MIDIInterfaceInfo->Config.DataINPipe.Type  = EP_TYPE_BULK;

	MIDIInterfaceInfo->Config.DataOUTPipe.Size = le16_to_cpu(DataOUTEndpoint->EndpointSize);
	MIDIInterfaceInfo->Config.DataOUTPipe.EndpointAddress = DataOUTEndpoint->EndpointAddress;
	MIDIInterfaceInfo->Config.DataOUTPipe.Type = EP_TYPE_BULK;

	if (!(Pipe_ConfigurePipeTable(&MIDIInterfaceInfo->Config.DataINPipe, 1)))
	  return MIDI_ENUMERROR_PipeConfigurationFailed;

	if (!(Pipe_ConfigurePipeTable(&MIDIInterfaceInfo->Config.DataOUTPipe, 1)))
	  return MIDI_ENUMERROR_PipeConfigurationFailed;

	MIDIInterfaceInfo->State.InterfaceNumber = MIDIInterface->InterfaceNumber;
	MIDIInterfaceInfo->State.IsActive = true;

	return MIDI_ENUMERROR_NoError;
}

static uint8_t DCOMP_MIDI_Host_NextMIDIStreamingInterface(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		if ((Interface->Class    == AUDIO_CSCP_AudioClass)            &&
		    (Interface->SubClass == AUDIO_CSCP_MIDIStreamingSubclass) &&
		    (Interface->Protocol == AUDIO_CSCP_StreamingProtocol))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DCOMP_MIDI_Host_NextMIDIStreamingDataEndpoint(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* Endpoint = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Endpoint_t);

		uint8_t EndpointType = (Endpoint->Attributes & EP_TYPE_MASK);

		if ((EndpointType == EP_TYPE_BULK) && !(Pipe_IsEndpointBound(Endpoint->EndpointAddress)))
		  return DESCRIPTOR_SEARCH_Found;
	}
	else if (Header->Type == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

void MIDI_Host_USBTask(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MIDIInterfaceInfo->State.IsActive))
	  return;

	#if !defined(NO_CLASS_DRIVER_AUTOFLUSH)
	MIDI_Host_Flush(MIDIInterfaceInfo);
	#endif
}

uint8_t MIDI_Host_Flush(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MIDIInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	uint8_t ErrorCode;

	Pipe_SelectPipe(MIDIInterfaceInfo->Config.DataOUTPipe.Address);
	Pipe_Unfreeze();

	if (Pipe_BytesInPipe())
	{
		Pipe_ClearOUT();

		if ((ErrorCode = Pipe_WaitUntilReady()) != PIPE_READYWAIT_NoError)
		{
			Pipe_Freeze();
			return ErrorCode;
		}
	}

	Pipe_Freeze();

	return PIPE_READYWAIT_NoError;
}

uint8_t MIDI_Host_SendEventPacket(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo,
                                  MIDI_EventPacket_t* const Event)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MIDIInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	uint8_t ErrorCode;

	Pipe_SelectPipe(MIDIInterfaceInfo->Config.DataOUTPipe.Address);
	Pipe_Unfreeze();

	if ((ErrorCode = Pipe_Write_Stream_LE(Event, sizeof(MIDI_EventPacket_t), NULL)) != PIPE_RWSTREAM_NoError)
	{
		Pipe_Freeze();
		return ErrorCode;
	}

	if (!(Pipe_IsReadWriteAllowed()))
	  Pipe_ClearOUT();

	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

bool MIDI_Host_ReceiveEventPacket(USB_ClassInfo_MIDI_Host_t* const MIDIInterfaceInfo,
                                  MIDI_EventPacket_t* const Event)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(MIDIInterfaceInfo->State.IsActive))
	  return HOST_SENDCONTROL_DeviceDisconnected;

	bool DataReady = false;

	Pipe_SelectPipe(MIDIInterfaceInfo->Config.DataINPipe.Address);
	Pipe_Unfreeze();

	if (Pipe_IsINReceived())
	{
		if (Pipe_BytesInPipe())
		{
			Pipe_Read_Stream_LE(Event, sizeof(MIDI_EventPacket_t), NULL);
			DataReady = true;
		}

		if (!(Pipe_BytesInPipe()))
		  Pipe_ClearIN();
	}

	Pipe_Freeze();

	return DataReady;
}

#endif

