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
#include "USBMode.h"

#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_HOSTSTDREQ_C
#include "HostStandardReq.h"

uint8_t USB_Host_SendControlRequest(void* const BufferPtr)
{
	uint8_t* HeaderStream   = (uint8_t*)&USB_ControlRequest;
	uint8_t* DataStream     = (uint8_t*)BufferPtr;
	bool     BusSuspended   = USB_Host_IsBusSuspended();
	uint8_t  ReturnStatus   = HOST_SENDCONTROL_Successful;
	uint16_t DataLen        = USB_ControlRequest.wLength;

	USB_Host_ResumeBus();
	
	if ((ReturnStatus = USB_Host_WaitMS(1)) != HOST_WAITERROR_Successful)
	  goto End_Of_Control_Send;

	Pipe_SetPipeToken(PIPE_TOKEN_SETUP);
	Pipe_ClearErrorFlags();

	Pipe_Unfreeze();

	for (uint8_t HeaderByte = 0; HeaderByte < sizeof(USB_Request_Header_t); HeaderByte++)
	  Pipe_Write_Byte(*(HeaderStream++));

	Pipe_ClearSETUP();
	
	if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_SetupSent)) != HOST_SENDCONTROL_Successful)
	  goto End_Of_Control_Send;

	Pipe_Freeze();

	if ((ReturnStatus = USB_Host_WaitMS(1)) != HOST_WAITERROR_Successful)
	  goto End_Of_Control_Send;

	if ((USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_DIRECTION) == REQDIR_DEVICETOHOST)
	{
		Pipe_SetPipeToken(PIPE_TOKEN_IN);
		
		if (DataStream != NULL)
		{
			while (DataLen)
			{
				Pipe_Unfreeze();

				if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_InReceived)) != HOST_SENDCONTROL_Successful)
				  goto End_Of_Control_Send;
							
				if (!(Pipe_BytesInPipe()))
				  DataLen = 0;
				
				while (Pipe_BytesInPipe() && DataLen)
				{
					*(DataStream++) = Pipe_Read_Byte();
					DataLen--;
				}

				Pipe_Freeze();
				Pipe_ClearIN();
			}
		}

		Pipe_SetPipeToken(PIPE_TOKEN_OUT);
		Pipe_Unfreeze();
		
		if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_OutReady)) != HOST_SENDCONTROL_Successful)
		  goto End_Of_Control_Send;

		Pipe_ClearOUT();

		if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_OutReady)) != HOST_SENDCONTROL_Successful)
		  goto End_Of_Control_Send;
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
				  goto End_Of_Control_Send;

				while (DataLen && (Pipe_BytesInPipe() < USB_ControlPipeSize))
				{					
					Pipe_Write_Byte(*(DataStream++));
					DataLen--;
				}
				
				Pipe_ClearOUT();
			}

			if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_OutReady)) != HOST_SENDCONTROL_Successful)
			  goto End_Of_Control_Send;

			Pipe_Freeze();
		}
		
		Pipe_SetPipeToken(PIPE_TOKEN_IN);
		Pipe_Unfreeze();

		if ((ReturnStatus = USB_Host_WaitForIOS(USB_HOST_WAITFOR_InReceived)) != HOST_SENDCONTROL_Successful)
		  goto End_Of_Control_Send;

		Pipe_ClearIN();
	}

End_Of_Control_Send:
	Pipe_Freeze();
	
	if (BusSuspended)
	  USB_Host_SuspendBus();

	Pipe_ResetPipe(PIPE_CONTROLPIPE);

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

#endif
