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
#include "../../Core/USBMode.h"

#if defined(USB_CAN_BE_DEVICE)

#define  __INCLUDE_FROM_PRINTER_DRIVER
#define  __INCLUDE_FROM_PRINTER_DEVICE_C
#include "PrinterClassDevice.h"

void PRNT_Device_ProcessControlRequest(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo)
{
	if (!(Endpoint_IsSETUPReceived()))
	  return;

	if (USB_ControlRequest.wIndex != PRNTInterfaceInfo->Config.InterfaceNumber)
	  return;

	switch (USB_ControlRequest.bRequest)
	{
		case PRNT_REQ_GetDeviceID:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				while (!(Endpoint_IsINReady()))
				{
					if (USB_DeviceState == DEVICE_STATE_Unattached)
					  return;
				}

				uint16_t IEEEStringLen = strlen(PRNTInterfaceInfo->Config.IEEE1284String);
				Endpoint_Write_16_BE(IEEEStringLen);
				Endpoint_Write_Control_Stream_LE(PRNTInterfaceInfo->Config.IEEE1284String, IEEEStringLen);
				Endpoint_ClearStatusStage();
			}

			break;
		case PRNT_REQ_GetPortStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				while (!(Endpoint_IsINReady()))
				{
					if (USB_DeviceState == DEVICE_STATE_Unattached)
					  return;
				}

				Endpoint_Write_8(PRNTInterfaceInfo->State.PortStatus);
				Endpoint_ClearStatusStage();
			}

			break;
		case PRNT_REQ_SoftReset:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_ClearStatusStage();

				PRNTInterfaceInfo->State.IsPrinterReset = true;

				EVENT_PRNT_Device_SoftReset(PRNTInterfaceInfo);
			}

			break;
	}
}

bool PRNT_Device_ConfigureEndpoints(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo)
{
	memset(&PRNTInterfaceInfo->State, 0x00, sizeof(PRNTInterfaceInfo->State));
	PRNTInterfaceInfo->State.PortStatus = PRNT_PORTSTATUS_NOTERROR | PRNT_PORTSTATUS_SELECT;

	PRNTInterfaceInfo->Config.DataINEndpoint.Type  = EP_TYPE_BULK;
	PRNTInterfaceInfo->Config.DataOUTEndpoint.Type = EP_TYPE_BULK;

	if (!(Endpoint_ConfigureEndpointTable(&PRNTInterfaceInfo->Config.DataINEndpoint, 1)))
	  return false;

	if (!(Endpoint_ConfigureEndpointTable(&PRNTInterfaceInfo->Config.DataOUTEndpoint, 1)))
	  return false;

	return true;
}

void PRNT_Device_USBTask(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	#if !defined(NO_CLASS_DRIVER_AUTOFLUSH)
	Endpoint_SelectEndpoint(PRNTInterfaceInfo->Config.DataINEndpoint.Address);

	if (Endpoint_IsINReady())
	  PRNT_Device_Flush(PRNTInterfaceInfo);
	#endif

	if (PRNTInterfaceInfo->State.IsPrinterReset)
	{
		Endpoint_ResetEndpoint(PRNTInterfaceInfo->Config.DataOUTEndpoint.Address);
		Endpoint_ResetEndpoint(PRNTInterfaceInfo->Config.DataINEndpoint.Address);

		Endpoint_SelectEndpoint(PRNTInterfaceInfo->Config.DataOUTEndpoint.Address);
		Endpoint_ClearStall();
		Endpoint_ResetDataToggle();
		Endpoint_SelectEndpoint(PRNTInterfaceInfo->Config.DataINEndpoint.Address);
		Endpoint_ClearStall();
		Endpoint_ResetDataToggle();

		PRNTInterfaceInfo->State.IsPrinterReset = false;
	}
}

uint8_t PRNT_Device_SendString(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo,
                               const char* const String)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;

	Endpoint_SelectEndpoint(PRNTInterfaceInfo->Config.DataINEndpoint.Address);
	return Endpoint_Write_Stream_LE(String, strlen(String), NULL);
}

uint8_t PRNT_Device_SendData(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo,
                             const void* const Buffer,
                             const uint16_t Length)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;

	Endpoint_SelectEndpoint(PRNTInterfaceInfo->Config.DataINEndpoint.Address);
	return Endpoint_Write_Stream_LE(Buffer, Length, NULL);
}

uint8_t PRNT_Device_SendByte(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo,
                             const uint8_t Data)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;

	Endpoint_SelectEndpoint(PRNTInterfaceInfo->Config.DataINEndpoint.Address);

	if (!(Endpoint_IsReadWriteAllowed()))
	{
		Endpoint_ClearIN();

		uint8_t ErrorCode;

		if ((ErrorCode = Endpoint_WaitUntilReady()) != ENDPOINT_READYWAIT_NoError)
		  return ErrorCode;
	}

	Endpoint_Write_8(Data);
	return ENDPOINT_READYWAIT_NoError;
}

uint8_t PRNT_Device_Flush(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;

	uint8_t ErrorCode;

	Endpoint_SelectEndpoint(PRNTInterfaceInfo->Config.DataINEndpoint.Address);

	if (!(Endpoint_BytesInEndpoint()))
	  return ENDPOINT_READYWAIT_NoError;

	bool BankFull = !(Endpoint_IsReadWriteAllowed());

	Endpoint_ClearIN();

	if (BankFull)
	{
		if ((ErrorCode = Endpoint_WaitUntilReady()) != ENDPOINT_READYWAIT_NoError)
		  return ErrorCode;

		Endpoint_ClearIN();
	}

	return ENDPOINT_READYWAIT_NoError;
}

uint16_t PRNT_Device_BytesReceived(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return 0;

	Endpoint_SelectEndpoint(PRNTInterfaceInfo->Config.DataOUTEndpoint.Address);

	if (Endpoint_IsOUTReceived())
	{
		if (!(Endpoint_BytesInEndpoint()))
		{
			Endpoint_ClearOUT();
			return 0;
		}
		else
		{
			return Endpoint_BytesInEndpoint();
		}
	}
	else
	{
		return 0;
	}
}

int16_t PRNT_Device_ReceiveByte(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return -1;

	int16_t ReceivedByte = -1;

	Endpoint_SelectEndpoint(PRNTInterfaceInfo->Config.DataOUTEndpoint.Address);

	if (Endpoint_IsOUTReceived())
	{
		if (Endpoint_BytesInEndpoint())
		  ReceivedByte = Endpoint_Read_8();

		if (!(Endpoint_BytesInEndpoint()))
		  Endpoint_ClearOUT();
	}

	return ReceivedByte;
}

#if defined(FDEV_SETUP_STREAM)
void PRNT_Device_CreateStream(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo,
                              FILE* const Stream)
{
	*Stream = (FILE)FDEV_SETUP_STREAM(PRNT_Device_putchar, PRNT_Device_getchar, _FDEV_SETUP_RW);
	fdev_set_udata(Stream, PRNTInterfaceInfo);
}

void PRNT_Device_CreateBlockingStream(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo,
                                      FILE* const Stream)
{
	*Stream = (FILE)FDEV_SETUP_STREAM(PRNT_Device_putchar, PRNT_Device_getchar_Blocking, _FDEV_SETUP_RW);
	fdev_set_udata(Stream, PRNTInterfaceInfo);
}

static int PRNT_Device_putchar(char c,
                               FILE* Stream)
{
	return PRNT_Device_SendByte((USB_ClassInfo_PRNT_Device_t*)fdev_get_udata(Stream), c) ? _FDEV_ERR : 0;
}

static int PRNT_Device_getchar(FILE* Stream)
{
	int16_t ReceivedByte = PRNT_Device_ReceiveByte((USB_ClassInfo_PRNT_Device_t*)fdev_get_udata(Stream));

	if (ReceivedByte < 0)
	  return _FDEV_EOF;

	return ReceivedByte;
}

static int PRNT_Device_getchar_Blocking(FILE* Stream)
{
	int16_t ReceivedByte;

	while ((ReceivedByte = PRNT_Device_ReceiveByte((USB_ClassInfo_PRNT_Device_t*)fdev_get_udata(Stream))) < 0)
	{
		if (USB_DeviceState == DEVICE_STATE_Unattached)
		  return _FDEV_EOF;

		PRNT_Device_USBTask((USB_ClassInfo_PRNT_Device_t*)fdev_get_udata(Stream));
		USB_USBTask();
	}

	return ReceivedByte;
}
#endif

void PRNT_Device_Event_Stub(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo)
{

}

#endif

