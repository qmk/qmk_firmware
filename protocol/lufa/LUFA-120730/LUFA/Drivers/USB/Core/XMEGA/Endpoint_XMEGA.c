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
#if (ARCH == ARCH_XMEGA)

#define  __INCLUDE_FROM_USB_DRIVER
#include "../USBMode.h"

#if defined(USB_CAN_BE_DEVICE)

#include "../Endpoint.h"

#if !defined(FIXED_CONTROL_ENDPOINT_SIZE)
uint8_t USB_Device_ControlEndpointSize = ENDPOINT_CONTROLEP_DEFAULT_SIZE;
#endif

Endpoint_FIFOPair_t       USB_Endpoint_FIFOs[ENDPOINT_TOTAL_ENDPOINTS];

volatile uint8_t          USB_Endpoint_SelectedEndpoint;
volatile USB_EP_t*        USB_Endpoint_SelectedHandle;
volatile Endpoint_FIFO_t* USB_Endpoint_SelectedFIFO;

bool Endpoint_ConfigureEndpointTable(const USB_Endpoint_Table_t* const Table,
                                     const uint8_t Entries)
{
	for (uint8_t i = 0; i < Entries; i++)
	{
		if (!(Table[i].Address))
		  continue;
	
		if (!(Endpoint_ConfigureEndpoint(Table[i].Address, Table[i].Type, Table[i].Size, Table[i].Banks)))
		{
			return false;
		}
	}
	
	return true;
}

bool Endpoint_ConfigureEndpoint_PRV(const uint8_t Address,
                                    const uint8_t Config,
                                    const uint8_t Size)
{
	Endpoint_SelectEndpoint(Address);

	USB_Endpoint_SelectedHandle->CTRL    = 0;
	USB_Endpoint_SelectedHandle->STATUS  = (Address & ENDPOINT_DIR_IN) ? USB_EP_BUSNACK0_bm : 0;
	USB_Endpoint_SelectedHandle->CTRL    = Config;
	USB_Endpoint_SelectedHandle->CNT     = 0;
	USB_Endpoint_SelectedHandle->DATAPTR = (intptr_t)USB_Endpoint_SelectedFIFO->Data;

	USB_Endpoint_SelectedFIFO->Length    = (Address & ENDPOINT_DIR_IN) ? Size : 0;
	USB_Endpoint_SelectedFIFO->Position  = 0;

	return true;
}

void Endpoint_ClearEndpoints(void)
{
	for (uint8_t EPNum = 0; EPNum < ENDPOINT_TOTAL_ENDPOINTS; EPNum++)
	{
		((USB_EndpointTable_t*)USB.EPPTR)->Endpoints[EPNum].IN.CTRL  = 0;
		((USB_EndpointTable_t*)USB.EPPTR)->Endpoints[EPNum].OUT.CTRL = 0;
	}
}

void Endpoint_ClearStatusStage(void)
{
	if (USB_ControlRequest.bmRequestType & REQDIR_DEVICETOHOST)
	{
		while (!(Endpoint_IsOUTReceived()))
		{
			if (USB_DeviceState == DEVICE_STATE_Unattached)
			  return;
		}

		Endpoint_ClearOUT();
	}
	else
	{
		while (!(Endpoint_IsINReady()))
		{
			if (USB_DeviceState == DEVICE_STATE_Unattached)
			  return;
		}

		Endpoint_ClearIN();
	}
}

#if !defined(CONTROL_ONLY_DEVICE)
uint8_t Endpoint_WaitUntilReady(void)
{
	#if (USB_STREAM_TIMEOUT_MS < 0xFF)
	uint8_t  TimeoutMSRem = USB_STREAM_TIMEOUT_MS;
	#else
	uint16_t TimeoutMSRem = USB_STREAM_TIMEOUT_MS;
	#endif

	uint16_t PreviousFrameNumber = USB_Device_GetFrameNumber();

	for (;;)
	{
		if (Endpoint_GetEndpointDirection() == ENDPOINT_DIR_IN)
		{
			if (Endpoint_IsINReady())
			  return ENDPOINT_READYWAIT_NoError;
		}
		else
		{
			if (Endpoint_IsOUTReceived())
			  return ENDPOINT_READYWAIT_NoError;
		}

		uint8_t USB_DeviceState_LCL = USB_DeviceState;

		if (USB_DeviceState_LCL == DEVICE_STATE_Unattached)
		  return ENDPOINT_READYWAIT_DeviceDisconnected;
		else if (USB_DeviceState_LCL == DEVICE_STATE_Suspended)
		  return ENDPOINT_READYWAIT_BusSuspended;
		else if (Endpoint_IsStalled())
		  return ENDPOINT_READYWAIT_EndpointStalled;

		uint16_t CurrentFrameNumber = USB_Device_GetFrameNumber();

		if (CurrentFrameNumber != PreviousFrameNumber)
		{
			PreviousFrameNumber = CurrentFrameNumber;

			if (!(TimeoutMSRem--))
			  return ENDPOINT_READYWAIT_Timeout;
		}
	}
}
#endif

#endif

#endif

