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

#include "USBMode.h"
#if defined(USB_CAN_BE_HOST)

#include "Host.h"

uint8_t USB_Host_WaitMS(uint8_t MS)
{
	bool    BusSuspended = USB_Host_IsBusSuspended();
	uint8_t ErrorCode    = HOST_WAITERROR_Successful;
	
	USB_INT_Clear(USB_INT_HSOFI);
	USB_Host_ResumeBus();

	while (MS)
	{
		if (USB_INT_HasOccurred(USB_INT_HSOFI))
		{
			USB_INT_Clear(USB_INT_HSOFI);
			MS--;
		}
					
		if ((USB_IsConnected == false) || (USB_CurrentMode == USB_MODE_DEVICE))
		{
			ErrorCode = HOST_WAITERROR_DeviceDisconnect;
			
			break;
		}

		if (Pipe_IsError() == true)
		{
			Pipe_ClearError();
			ErrorCode = HOST_WAITERROR_PipeError;
			
			break;
		}
		
		if (Pipe_IsStalled() == true)
		{
			Pipe_ClearStall();
			ErrorCode = HOST_WAITERROR_SetupStalled;
			
			break;			
		}
	}

	if (BusSuspended)
	  USB_Host_SuspendBus();

	return ErrorCode;
}

void USB_Host_ResetDevice(void)
{
	bool BusSuspended = USB_Host_IsBusSuspended();

	USB_INT_Disable(USB_INT_DDISCI);
	
	USB_Host_ResetBus();
	while (!(USB_Host_IsResetBusDone()));

	USB_INT_Clear(USB_INT_HSOFI);
	USB_Host_ResumeBus();	
	
	for (uint8_t MSRem = 10; MSRem != 0; MSRem--)
	{
		/* Workaround for powerless-pullup devices. After a USB bus reset,
		   all disconnection interrupts are supressed while a USB frame is
		   looked for - if it is found within 10ms, the device is still
		   present.                                                        */

		if (USB_INT_HasOccurred(USB_INT_HSOFI))
		{
			USB_INT_Clear(USB_INT_DDISCI);
			break;
		}
		
		_delay_ms(1);
	}

	if (BusSuspended)
	  USB_Host_SuspendBus();

	USB_INT_Enable(USB_INT_DDISCI);
}
#endif
