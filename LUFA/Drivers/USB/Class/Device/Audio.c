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

#define  __INCLUDE_FROM_AUDIO_DRIVER
#include "Audio.h"

void Audio_Device_ProcessControlRequest(USB_ClassInfo_Audio_Device_t* const AudioInterfaceInfo)
{
	if (!(Endpoint_IsSETUPReceived()))
	  return;
	  
	if (USB_ControlRequest.wIndex != AudioInterfaceInfo->Config.StreamingInterfaceNumber)
	  return;

	switch (USB_ControlRequest.bRequest)
	{
		case REQ_SetInterface:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				AudioInterfaceInfo->State.InterfaceEnabled = ((USB_ControlRequest.wValue & 0xFF) != 0);
				  
				Endpoint_ClearStatusStage();
			}

			break;
	}
}

bool Audio_Device_ConfigureEndpoints(USB_ClassInfo_Audio_Device_t* const AudioInterfaceInfo)
{
	memset(&AudioInterfaceInfo->State, 0x00, sizeof(AudioInterfaceInfo->State));

	if (AudioInterfaceInfo->Config.DataINEndpointNumber)
	{
		if (!(Endpoint_ConfigureEndpoint(AudioInterfaceInfo->Config.DataINEndpointNumber, EP_TYPE_ISOCHRONOUS,
										 ENDPOINT_DIR_IN, AudioInterfaceInfo->Config.DataINEndpointSize,
										 ENDPOINT_BANK_DOUBLE)))
		{
			return false;
		}
	}

	if (AudioInterfaceInfo->Config.DataOUTEndpointNumber)
	{
		if (!(Endpoint_ConfigureEndpoint(AudioInterfaceInfo->Config.DataOUTEndpointNumber, EP_TYPE_ISOCHRONOUS,
										 ENDPOINT_DIR_OUT, AudioInterfaceInfo->Config.DataOUTEndpointSize,
										 ENDPOINT_BANK_DOUBLE)))
		{
			return false;
		}
	}
	
	return true;
}

#endif