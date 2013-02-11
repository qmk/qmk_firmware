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

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "../../../../Common/Common.h"
#if (ARCH == ARCH_UC3)

#define  __INCLUDE_FROM_USB_DRIVER
#include "../USBMode.h"

#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_HOST_C
#include "../Host.h"

void USB_Host_ProcessNextHostState(void)
{
	uint8_t ErrorCode    = HOST_ENUMERROR_NoError;
	uint8_t SubErrorCode = HOST_ENUMERROR_NoError;

	static uint16_t WaitMSRemaining;
	static uint8_t  PostWaitState;

	switch (USB_HostState)
	{
		case HOST_STATE_WaitForDevice:
			if (WaitMSRemaining)
			{
				if ((SubErrorCode = USB_Host_WaitMS(1)) != HOST_WAITERROR_Successful)
				{
					USB_HostState = PostWaitState;
					ErrorCode     = HOST_ENUMERROR_WaitStage;
					break;
				}

				if (!(--WaitMSRemaining))
				  USB_HostState = PostWaitState;
			}

			break;
		case HOST_STATE_Powered:
			WaitMSRemaining = HOST_DEVICE_SETTLE_DELAY_MS;

			USB_HostState = HOST_STATE_Powered_WaitForDeviceSettle;
			break;
		case HOST_STATE_Powered_WaitForDeviceSettle:
			if (WaitMSRemaining--)
			{
				Delay_MS(1);
				break;
			}
			else
			{
				USB_Host_VBUS_Manual_Off();

				USB_OTGPAD_On();
				USB_Host_VBUS_Auto_Enable();
				USB_Host_VBUS_Auto_On();

				#if defined(NO_AUTO_VBUS_MANAGEMENT)
				USB_Host_VBUS_Manual_Enable();
				USB_Host_VBUS_Manual_On();
				#endif

				USB_HostState = HOST_STATE_Powered_WaitForConnect;
			}

			break;
		case HOST_STATE_Powered_WaitForConnect:
			if (USB_INT_HasOccurred(USB_INT_DCONNI))
			{
				USB_INT_Clear(USB_INT_DCONNI);
				USB_INT_Clear(USB_INT_DDISCI);

				USB_INT_Clear(USB_INT_VBERRI);
				USB_INT_Enable(USB_INT_VBERRI);

				USB_Host_ResumeBus();
				Pipe_ClearPipes();

				HOST_TASK_NONBLOCK_WAIT(100, HOST_STATE_Powered_DoReset);
			}

			break;
		case HOST_STATE_Powered_DoReset:
			USB_Host_ResetDevice();

			HOST_TASK_NONBLOCK_WAIT(200, HOST_STATE_Powered_ConfigPipe);
			break;
		case HOST_STATE_Powered_ConfigPipe:
			if (!(Pipe_ConfigurePipe(PIPE_CONTROLPIPE, EP_TYPE_CONTROL, ENDPOINT_CONTROLEP, PIPE_CONTROLPIPE_DEFAULT_SIZE, 1)))
			{
				ErrorCode    = HOST_ENUMERROR_PipeConfigError;
				SubErrorCode = 0;
				break;
			}

			USB_HostState = HOST_STATE_Default;
			break;
		case HOST_STATE_Default:
			USB_ControlRequest = (USB_Request_Header_t)
				{
					.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE),
					.bRequest      = REQ_GetDescriptor,
					.wValue        = (DTYPE_Device << 8),
					.wIndex        = 0,
					.wLength       = 8,
				};

			uint8_t DataBuffer[8];

			Pipe_SelectPipe(PIPE_CONTROLPIPE);
			if ((SubErrorCode = USB_Host_SendControlRequest(DataBuffer)) != HOST_SENDCONTROL_Successful)
			{
				ErrorCode = HOST_ENUMERROR_ControlError;
				break;
			}

			USB_Host_ControlPipeSize = DataBuffer[offsetof(USB_Descriptor_Device_t, Endpoint0Size)];

			USB_Host_ResetDevice();

			HOST_TASK_NONBLOCK_WAIT(200, HOST_STATE_Default_PostReset);
			break;
		case HOST_STATE_Default_PostReset:
			if (!(Pipe_ConfigurePipe(PIPE_CONTROLPIPE, EP_TYPE_CONTROL, ENDPOINT_CONTROLEP, USB_Host_ControlPipeSize, 1)))
			{
				ErrorCode    = HOST_ENUMERROR_PipeConfigError;
				SubErrorCode = 0;
				break;
			}

			USB_ControlRequest = (USB_Request_Header_t)
				{
					.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE),
					.bRequest      = REQ_SetAddress,
					.wValue        = USB_HOST_DEVICEADDRESS,
					.wIndex        = 0,
					.wLength       = 0,
				};

			if ((SubErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
			{
				ErrorCode = HOST_ENUMERROR_ControlError;
				break;
			}

			HOST_TASK_NONBLOCK_WAIT(100, HOST_STATE_Default_PostAddressSet);
			break;
		case HOST_STATE_Default_PostAddressSet:
			USB_Host_SetDeviceAddress(USB_HOST_DEVICEADDRESS);

			USB_HostState = HOST_STATE_Addressed;

			EVENT_USB_Host_DeviceEnumerationComplete();
			break;
	}

	if ((ErrorCode != HOST_ENUMERROR_NoError) && (USB_HostState != HOST_STATE_Unattached))
	{
		EVENT_USB_Host_DeviceEnumerationFailed(ErrorCode, SubErrorCode);

		USB_Host_VBUS_Auto_Off();

		EVENT_USB_Host_DeviceUnattached();

		USB_ResetInterface();
	}
}

uint8_t USB_Host_WaitMS(uint8_t MS)
{
	bool    BusSuspended = USB_Host_IsBusSuspended();
	uint8_t ErrorCode    = HOST_WAITERROR_Successful;
	bool    HSOFIEnabled = USB_INT_IsEnabled(USB_INT_HSOFI);

	USB_INT_Disable(USB_INT_HSOFI);
	USB_INT_Clear(USB_INT_HSOFI);

	USB_Host_ResumeBus();

	while (MS)
	{
		if (USB_INT_HasOccurred(USB_INT_HSOFI))
		{
			USB_INT_Clear(USB_INT_HSOFI);
			MS--;
		}

		if ((USB_HostState == HOST_STATE_Unattached) || (USB_CurrentMode != USB_MODE_Host))
		{
			ErrorCode = HOST_WAITERROR_DeviceDisconnect;

			break;
		}

		if (Pipe_IsError())
		{
			Pipe_ClearError();
			ErrorCode = HOST_WAITERROR_PipeError;

			break;
		}

		if (Pipe_IsStalled())
		{
			Pipe_ClearStall();
			ErrorCode = HOST_WAITERROR_SetupStalled;

			break;
		}
	}

	if (BusSuspended)
	  USB_Host_SuspendBus();

	if (HSOFIEnabled)
	  USB_INT_Enable(USB_INT_HSOFI);

	return ErrorCode;
}

static void USB_Host_ResetDevice(void)
{
	bool BusSuspended = USB_Host_IsBusSuspended();

	USB_INT_Disable(USB_INT_DDISCI);

	USB_Host_ResetBus();
	while (!(USB_Host_IsBusResetComplete()));
	USB_Host_ResumeBus();

	USB_Host_ConfigurationNumber = 0;

	bool HSOFIEnabled = USB_INT_IsEnabled(USB_INT_HSOFI);

	USB_INT_Disable(USB_INT_HSOFI);
	USB_INT_Clear(USB_INT_HSOFI);

	for (uint8_t MSRem = 10; MSRem != 0; MSRem--)
	{
		/* Workaround for powerless-pull-up devices. After a USB bus reset,
		   all disconnection interrupts are suppressed while a USB frame is
		   looked for - if it is found within 10ms, the device is still
		   present.                                                        */

		if (USB_INT_HasOccurred(USB_INT_HSOFI))
		{
			USB_INT_Clear(USB_INT_HSOFI);
			USB_INT_Clear(USB_INT_DDISCI);
			break;
		}

		Delay_MS(1);
	}

	if (HSOFIEnabled)
	  USB_INT_Enable(USB_INT_HSOFI);

	if (BusSuspended)
	  USB_Host_SuspendBus();

	USB_INT_Enable(USB_INT_DDISCI);
}

#endif

#endif
