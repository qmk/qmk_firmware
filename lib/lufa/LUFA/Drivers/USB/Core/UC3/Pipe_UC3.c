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

#include "../../../../Common/Common.h"
#if (ARCH == ARCH_UC3)

#define  __INCLUDE_FROM_USB_DRIVER
#include "../USBMode.h"

#if defined(USB_CAN_BE_HOST)

#include "../Pipe.h"

uint8_t USB_Host_ControlPipeSize = PIPE_CONTROLPIPE_DEFAULT_SIZE;

volatile uint32_t USB_Pipe_SelectedPipe = PIPE_CONTROLPIPE;
volatile uint8_t* USB_Pipe_FIFOPos[PIPE_TOTAL_PIPES];

bool Pipe_ConfigurePipeTable(const USB_Pipe_Table_t* const Table,
                             const uint8_t Entries)
{
	for (uint8_t i = 0; i < Entries; i++)
	{
		if (!(Table[i].Address))
		  continue;

		if (!(Pipe_ConfigurePipe(Table[i].Address, Table[i].Type, Table[i].EndpointAddress, Table[i].Size, Table[i].Banks)))
		{
			return false;
		}
	}

	return true;
}

bool Pipe_ConfigurePipe(const uint8_t Address,
                        const uint8_t Type,
                        const uint8_t EndpointAddress,
                        const uint16_t Size,
                        const uint8_t Banks)
{
	uint8_t Number = (Address & PIPE_EPNUM_MASK);
	uint8_t Token  = (Address & PIPE_DIR_IN) ? PIPE_TOKEN_IN : PIPE_TOKEN_OUT;

	if (Number >= PIPE_TOTAL_PIPES)
	  return false;

	if (Type == EP_TYPE_CONTROL)
	  Token = PIPE_TOKEN_SETUP;

	USB_Pipe_FIFOPos[Number]     = &AVR32_USBB_SLAVE[Number * PIPE_HSB_ADDRESS_SPACE_SIZE];

#if defined(ORDERED_EP_CONFIG)
	Pipe_SelectPipe(Number);
	Pipe_EnablePipe();

	(&AVR32_USBB.upcfg0)[Number] = 0;
	(&AVR32_USBB.upcfg0)[Number] = (AVR32_USBB_ALLOC_MASK |
	                                ((uint32_t)Type  << AVR32_USBB_PTYPE_OFFSET)  |
	                                ((uint32_t)Token << AVR32_USBB_PTOKEN_OFFSET) |
	                                ((Banks > 1) ? AVR32_USBB_PBK_MASK : 0)       |
	                                Pipe_BytesToEPSizeMask(Size) |
	                                ((uint32_t)Number << AVR32_USBB_PEPNUM_OFFSET));

	Pipe_SetInfiniteINRequests();

	return Pipe_IsConfigured();
#else
	for (uint8_t PNum = Number; PNum < PIPE_TOTAL_PIPES; PNum++)
	{
		uint32_t UPCFG0Temp;

		Pipe_SelectPipe(PNum);

		if (PNum == Number)
		{
			UPCFG0Temp = (AVR32_USBB_ALLOC_MASK |
			              ((uint32_t)Type  << AVR32_USBB_PTYPE_OFFSET)  |
			              ((uint32_t)Token << AVR32_USBB_PTOKEN_OFFSET) |
			              ((Banks > 1) ? AVR32_USBB_PBK_MASK : 0)       |
			              Pipe_BytesToEPSizeMask(Size) |
			              ((EndpointAddress & PIPE_EPNUM_MASK) << AVR32_USBB_PEPNUM_OFFSET));
		}
		else
		{
			UPCFG0Temp = (&AVR32_USBB.upcfg0)[PNum];
		}

		if (!(UPCFG0Temp & AVR32_USBB_ALLOC_MASK))
		  continue;

		Pipe_DisablePipe();
		(&AVR32_USBB.upcfg0)[PNum] &= ~AVR32_USBB_ALLOC_MASK;

		Pipe_EnablePipe();
		(&AVR32_USBB.upcfg0)[PNum] = UPCFG0Temp;

		Pipe_SetInfiniteINRequests();

		if (!(Pipe_IsConfigured()))
		  return false;
	}

	Pipe_SelectPipe(Number);
	return true;
#endif
}

void Pipe_ClearPipes(void)
{
	for (uint8_t PNum = 0; PNum < PIPE_TOTAL_PIPES; PNum++)
	{
		Pipe_SelectPipe(PNum);
		(&AVR32_USBB.upcfg0)[PNum]    = 0;
		(&AVR32_USBB.upcon0clr)[PNum] = -1;
		USB_Pipe_FIFOPos[PNum]        = &AVR32_USBB_SLAVE[PNum * 0x10000];
		Pipe_DisablePipe();
	}
}

bool Pipe_IsEndpointBound(const uint8_t EndpointAddress)
{
	uint8_t PrevPipeNumber = Pipe_GetCurrentPipe();

	for (uint8_t PNum = 0; PNum < PIPE_TOTAL_PIPES; PNum++)
	{
		Pipe_SelectPipe(PNum);

		if (!(Pipe_IsConfigured()))
		  continue;

		if (Pipe_GetBoundEndpointAddress() == EndpointAddress)
		  return true;
	}

	Pipe_SelectPipe(PrevPipeNumber);
	return false;
}

uint8_t Pipe_WaitUntilReady(void)
{
	#if (USB_STREAM_TIMEOUT_MS < 0xFF)
	uint8_t  TimeoutMSRem = USB_STREAM_TIMEOUT_MS;
	#else
	uint16_t TimeoutMSRem = USB_STREAM_TIMEOUT_MS;
	#endif

	uint16_t PreviousFrameNumber = USB_Host_GetFrameNumber();

	for (;;)
	{
		if (Pipe_GetPipeToken() == PIPE_TOKEN_IN)
		{
			if (Pipe_IsINReceived())
			  return PIPE_READYWAIT_NoError;
		}
		else
		{
			if (Pipe_IsOUTReady())
			  return PIPE_READYWAIT_NoError;
		}

		if (Pipe_IsStalled())
		  return PIPE_READYWAIT_PipeStalled;
		else if (USB_HostState == HOST_STATE_Unattached)
		  return PIPE_READYWAIT_DeviceDisconnected;

		uint16_t CurrentFrameNumber = USB_Host_GetFrameNumber();

		if (CurrentFrameNumber != PreviousFrameNumber)
		{
			PreviousFrameNumber = CurrentFrameNumber;

			if (!(TimeoutMSRem--))
			  return PIPE_READYWAIT_Timeout;
		}
	}
}

#endif

#endif
