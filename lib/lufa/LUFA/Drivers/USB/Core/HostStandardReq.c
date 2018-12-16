/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
#include "USBMode.h"

#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_HOSTSTDREQ_C
#include "HostStandardReq.h"

uint8_t USB_Host_ConfigurationNumber;

static uint8_t USB_Host_SendControlRequest_PRV(void* const BufferPtr)
{
	uint8_t* DataStream   = (uint8_t*)BufferPtr;
	uint8_t  ReturnStatus = HOST_SENDCONTROL_Successful;
	uint16_t DataLen      = USB_ControlRequest.wLength;

	USB_Host_ResumeBus();

	if ((ReturnStatus = USB_Host_WaitMS(1)) != HOST_WAITERROR_Successful)
	  return ReturnStatus;

	Pipe_SetPipeToken(PIPE_TOKEN_SETUP);
	Pipe_ClearError();

	Pipe_Unfreeze();

	#if defined(ARCH_BIG_ENDIAN)
	Pipe_Write_8(USB_ControlRequest.bmRequestType);
	Pipe_Write_8(USB_ControlRequest.bRequest);
	Pipe_Write_16_LE(USB_ControlRequest.wValue);
	Pipe_Write_16_LE(USB_ControlRequest.wIndex);
	Pipe_Write_16_LE(USB_ControlRequest.wLength);
	#else
	uint8_t* HeaderStream = (uint8_t*)&USB_ControlRequest;

	for (uint8_t HeaderByte = 0; HeaderByte < sizeof(USB_Request_Header_t); HeaderByte++)
	  Pipe_Write_8(*(HeaderStream++));
	#endif

	Pipe_ClearSETUP();

	if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_SetupSent)) != HOST_SENDCONTROL_Successful)
	  return ReturnStatus;

	Pipe_Freeze();

	if ((ReturnStatus = USB_Host_WaitMS(1)) != HOST_WAITERROR_Successful)
	  return ReturnStatus;

	if ((USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_DIRECTION) == REQDIR_DEVICETOHOST)
	{
		Pipe_SetPipeToken(PIPE_TOKEN_IN);

		if (DataStream != NULL)
		{
			while (DataLen)
			{
				Pipe_Unfreeze();

				if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_InReceived)) != HOST_SENDCONTROL_Successful)
				  return ReturnStatus;

				if (!(Pipe_BytesInPipe()))
				  DataLen = 0;

				while (Pipe_BytesInPipe() && DataLen)
				{
					*(DataStream++) = Pipe_Read_8();
					DataLen--;
				}

				Pipe_Freeze();
				Pipe_ClearIN();
			}
		}

		Pipe_SetPipeToken(PIPE_TOKEN_OUT);
		Pipe_Unfreeze();

		if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_OutReady)) != HOST_SENDCONTROL_Successful)
		  return ReturnStatus;

		Pipe_ClearOUT();

		if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_OutReady)) != HOST_SENDCONTROL_Successful)
		  return ReturnStatus;
	}
	else
	{
		if (DataStream != NULL)
		{
			Pipe_SetPipeToken(PIPE_TOKEN_OUT);
			Pipe_Unfreeze();

			while (DataLen)
			{
				if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_OutReady)) != HOST_SENDCONTROL_Successful)
				  return ReturnStatus;

				while (DataLen && (Pipe_BytesInPipe() < USB_Host_ControlPipeSize))
				{
					Pipe_Write_8(*(DataStream++));
					DataLen--;
				}

				Pipe_ClearOUT();
			}

			if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_OutReady)) != HOST_SENDCONTROL_Successful)
			  return ReturnStatus;

			Pipe_Freeze();
		}

		Pipe_SetPipeToken(PIPE_TOKEN_IN);
		Pipe_Unfreeze();

		if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_InReceived)) != HOST_SENDCONTROL_Successful)
		  return ReturnStatus;

		Pipe_ClearIN();
	}

	return ReturnStatus;
}

static uint8_t USB_Host_WaitForIOS(const uint8_t WaitType)
{
	#if (USB_HOST_TIMEOUT_MS < 0xFF)
	uint8_t  TimeoutCounter = USB_HOST_TIMEOUT_MS;
	#else
	uint16_t TimeoutCounter = USB_HOST_TIMEOUT_MS;
	#endif

	while (!(((WaitType == USB_HOST_WAITFOR_SetupSent)  && Pipe_IsSETUPSent())  ||
	         ((WaitType == USB_HOST_WAITFOR_InReceived) && Pipe_IsINReceived()) ||
	         ((WaitType == USB_HOST_WAITFOR_OutReady)   && Pipe_IsOUTReady())))
	{
		uint8_t ErrorCode;

		if ((ErrorCode = USB_Host_WaitMS(1)) != HOST_WAITERROR_Successful)
		  return ErrorCode;

		if (!(TimeoutCounter--))
		  return HOST_SENDCONTROL_SoftwareTimeOut;
	}

	return HOST_SENDCONTROL_Successful;
}

uint8_t USB_Host_SendControlRequest(void* const BufferPtr)
{
	bool BusSuspended    = USB_Host_IsBusSuspended();
	uint8_t ReturnStatus = USB_Host_SendControlRequest_PRV(BufferPtr);

	Pipe_Freeze();

	if (BusSuspended)
	  USB_Host_SuspendBus();

	Pipe_ResetPipe(PIPE_CONTROLPIPE);

	return ReturnStatus;
}

uint8_t USB_Host_SetDeviceConfiguration(const uint8_t ConfigNumber)
{
	uint8_t ErrorCode;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE),
			.bRequest      = REQ_SetConfiguration,
			.wValue        = ConfigNumber,
			.wIndex        = 0,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(NULL)) == HOST_SENDCONTROL_Successful)
	{
		USB_Host_ConfigurationNumber = ConfigNumber;
		USB_HostState                = (ConfigNumber) ? HOST_STATE_Configured : HOST_STATE_Addressed;
	}

	return ErrorCode;
}

uint8_t USB_Host_GetDeviceConfiguration(uint8_t* const ConfigNumber)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE),
			.bRequest      = REQ_GetConfiguration,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = sizeof(uint8_t),
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(ConfigNumber);
}

uint8_t USB_Host_GetDescriptor(const uint8_t Type,
                               const uint8_t Index,
                               void* const Buffer,
                               const uint8_t BufferLength)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE),
			.bRequest      = REQ_GetDescriptor,
			.wValue        = (((uint16_t)Type << 8) | Index),
			.wIndex        = 0,
			.wLength       = BufferLength,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(Buffer);
}

uint8_t USB_Host_GetDeviceStatus(uint8_t* const FeatureStatus)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE),
			.bRequest      = REQ_GetStatus,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(FeatureStatus);
}

uint8_t USB_Host_ClearEndpointStall(const uint8_t EndpointAddress)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_ENDPOINT),
			.bRequest      = REQ_ClearFeature,
			.wValue        = FEATURE_SEL_EndpointHalt,
			.wIndex        = EndpointAddress,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}

uint8_t USB_Host_SetInterfaceAltSetting(const uint8_t InterfaceIndex,
                                        const uint8_t AltSetting)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_INTERFACE),
			.bRequest      = REQ_SetInterface,
			.wValue        = AltSetting,
			.wIndex        = InterfaceIndex,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}

uint8_t USB_Host_GetInterfaceAltSetting(const uint8_t InterfaceIndex,
                                        uint8_t* const AltSetting)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_INTERFACE),
			.bRequest      = REQ_GetInterface,
			.wValue        = 0,
			.wIndex        = InterfaceIndex,
			.wLength       = sizeof(uint8_t),
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(AltSetting);
}

#endif

