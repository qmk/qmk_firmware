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

#include "Audio.h"

void USB_Audio_ProcessControlPacket(USB_ClassInfo_Audio_t* AudioInterfaceInfo)
{
	if (!(Endpoint_IsSETUPReceived()))
	  return;
	  
	if (USB_ControlRequest.wIndex != AudioInterfaceInfo->StreamingInterfaceNumber)
	  return;

	switch (USB_ControlRequest.bRequest)
	{
		case REQ_SetInterface:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				AudioInterfaceInfo->InterfaceEnabled = (USB_ControlRequest.wValue != 0);
				  
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}

			break;
	}
}

bool USB_Audio_ConfigureEndpoints(USB_ClassInfo_Audio_t* AudioInterfaceInfo)
{
	if (AudioInterfaceInfo->DataINEndpointNumber)
	{
		if (!(Endpoint_ConfigureEndpoint(AudioInterfaceInfo->DataINEndpointNumber, EP_TYPE_ISOCHRONOUS,
										 ENDPOINT_DIR_IN, AudioInterfaceInfo->DataINEndpointSize,
										 ENDPOINT_BANK_DOUBLE)))
		{
			return false;
		}
	}

	if (AudioInterfaceInfo->DataOUTEndpointNumber)
	{
		if (!(Endpoint_ConfigureEndpoint(AudioInterfaceInfo->DataOUTEndpointNumber, EP_TYPE_ISOCHRONOUS,
										 ENDPOINT_DIR_OUT, AudioInterfaceInfo->DataOUTEndpointSize,
										 ENDPOINT_BANK_DOUBLE)))
		{
			return false;
		}
	}

	return true;
}

void USB_Audio_USBTask(USB_ClassInfo_Audio_t* AudioInterfaceInfo)
{

}

int8_t USB_Audio_ReadSample8(void)
{
	int8_t Sample;

	Sample = Endpoint_Read_Byte();

	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearOUT();
	
	return Sample;
}

int16_t USB_Audio_ReadSample16(void)
{
	int16_t Sample;

	Sample = (int16_t)Endpoint_Read_Word_LE();
		  
	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearOUT();

	return Sample;
}

int32_t USB_Audio_ReadSample24(void)
{
	int32_t Sample;

	Sample = (((uint32_t)Endpoint_Read_Byte() << 16) | Endpoint_Read_Word_LE());
		  
	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearOUT();

	return Sample;
}

void USB_Audio_WriteSample8(int8_t Sample)
{
	Endpoint_Write_Byte(Sample);

	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearIN();
}

void USB_Audio_WriteSample16(int16_t Sample)
{
	Endpoint_Write_Word_LE(Sample);

	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearIN();
}

void USB_Audio_WriteSample24(int32_t Sample)
{
	Endpoint_Write_Byte(Sample >> 16);
	Endpoint_Write_Word_LE(Sample);

	if (!(Endpoint_IsReadWriteAllowed()))
	  Endpoint_ClearIN();
}

bool USB_Audio_IsSampleReceived(USB_ClassInfo_Audio_t* AudioInterfaceInfo)
{
	Endpoint_SelectEndpoint(AudioInterfaceInfo->DataOUTEndpointNumber);
	return Endpoint_IsOUTReceived();
}

bool USB_Audio_IsReadyForNextSample(USB_ClassInfo_Audio_t* AudioInterfaceInfo)
{
	Endpoint_SelectEndpoint(AudioInterfaceInfo->DataINEndpointNumber);
	return Endpoint_IsINReady();
}
