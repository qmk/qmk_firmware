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

#define  INCLUDE_FROM_USBTASK_C
#include "USBTask.h"

volatile bool        USB_IsInitialized;
USB_Request_Header_t USB_ControlRequest;

#if defined(USB_CAN_BE_HOST) && !defined(HOST_STATE_AS_GPIOR)
volatile uint8_t     USB_HostState;
#endif

#if defined(USB_CAN_BE_DEVICE) && !defined(DEVICE_STATE_AS_GPIOR)
volatile uint8_t     USB_DeviceState;
#endif

void USB_USBTask(void)
{
	#if defined(USB_HOST_ONLY)
		USB_HostTask();
	#elif defined(USB_DEVICE_ONLY)
		USB_DeviceTask();
	#else
		if (USB_CurrentMode == USB_MODE_DEVICE)
		  USB_DeviceTask();
		else if (USB_CurrentMode == USB_MODE_HOST)
		  USB_HostTask();
	#endif
}

#if defined(USB_CAN_BE_DEVICE)
static void USB_DeviceTask(void)
{
	if (USB_DeviceState != DEVICE_STATE_Unattached)
	{
		uint8_t PrevEndpoint = Endpoint_GetCurrentEndpoint();
	
		Endpoint_SelectEndpoint(ENDPOINT_CONTROLEP);

		if (Endpoint_IsSETUPReceived())
		  USB_Device_ProcessControlPacket();
		
		Endpoint_SelectEndpoint(PrevEndpoint);
	}
}
#endif

#if defined(USB_CAN_BE_HOST)
static void USB_HostTask(void)
{
	uint8_t PrevPipe = Pipe_GetCurrentPipe();
	
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	USB_Host_ProcessNextHostState();
	
	Pipe_SelectPipe(PrevPipe);
}
#endif
