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

#include "ConfigDescriptor.h"

#if defined(USB_CAN_BE_HOST)
uint8_t USB_GetDeviceConfigDescriptor(uint16_t* const ConfigSizePtr, void* BufferPtr)
{
	uint8_t ErrorCode;

	USB_HostRequest = (USB_Host_Request_Header_t)
		{
			bmRequestType: (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE),
			bRequest:      REQ_GetDescriptor,
			wValue:        (DTYPE_Configuration << 8),
			wIndex:        0,
			wLength:       sizeof(USB_Descriptor_Configuration_Header_t),
		};
	
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if (BufferPtr == NULL)
	{
		uint8_t ConfigHeader[sizeof(USB_Descriptor_Configuration_Header_t)];

		ErrorCode      = USB_Host_SendControlRequest(ConfigHeader);

		#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES)
		*ConfigSizePtr = DESCRIPTOR_CAST(ConfigHeader, USB_Descriptor_Configuration_Header_t).TotalConfigurationSize;
		#else
		*ConfigSizePtr = DESCRIPTOR_CAST(ConfigHeader, USB_Descriptor_Configuration_Header_t).wTotalLength;		
		#endif
	}
	else
	{
		USB_HostRequest.wLength = *ConfigSizePtr;
		
		ErrorCode      = USB_Host_SendControlRequest(BufferPtr);				
	}

	return ErrorCode;
}
#endif

void USB_GetNextDescriptorOfType(uint16_t* const BytesRem,
                                 uint8_t** const CurrConfigLoc,
                                 const uint8_t Type)
{
	while (*BytesRem)
	{
		USB_GetNextDescriptor(BytesRem, CurrConfigLoc);	  

		if (DESCRIPTOR_TYPE(*CurrConfigLoc) == Type)
		  return;
	}
}

void USB_GetNextDescriptorOfTypeBefore(uint16_t* const BytesRem,
                                       uint8_t** const CurrConfigLoc,
                                       const uint8_t Type,
                                       const uint8_t BeforeType)
{
	while (*BytesRem)
	{
		USB_GetNextDescriptor(BytesRem, CurrConfigLoc);

		if (DESCRIPTOR_TYPE(*CurrConfigLoc) == Type)
		{
			return;
		}
		else if (DESCRIPTOR_TYPE(*CurrConfigLoc) == BeforeType)
		{
			*BytesRem = 0;
			return;
		}
	}
}

void USB_GetNextDescriptorOfTypeAfter(uint16_t* const BytesRem,
                                      uint8_t** const CurrConfigLoc,
                                      const uint8_t Type,
                                      const uint8_t AfterType)
{
	USB_GetNextDescriptorOfType(BytesRem, CurrConfigLoc, AfterType);
	
	if (*BytesRem)
	  USB_GetNextDescriptorOfType(BytesRem, CurrConfigLoc, Type);
}
			
uint8_t USB_GetNextDescriptorComp_P(uint16_t* BytesRem, uint8_t** CurrConfigLoc, ComparatorPtr_t ComparatorRoutine)
{
	uint8_t ErrorCode;
		
	while (*BytesRem)
	{
		uint8_t*  PrevDescLoc = *CurrConfigLoc;
		uint16_t  PrevBytesRem = *BytesRem;

		USB_GetNextDescriptor(BytesRem, CurrConfigLoc);

		if ((ErrorCode = ComparatorRoutine(*CurrConfigLoc)) != Descriptor_Search_NotFound)
		{
			if (ErrorCode == Descriptor_Search_Fail)
			{
				*CurrConfigLoc = PrevDescLoc;
				*BytesRem      = PrevBytesRem;
			}
		
			return ErrorCode;
		}
	}
	
	return Descriptor_Search_Comp_EndOfDescriptor;
}
