/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

bool Endpoint_IsINReady(void)
{
	Endpoint_SelectEndpoint(USB_Endpoint_SelectedEndpoint | ENDPOINT_DIR_IN);

	return ((USB_Endpoint_SelectedHandle->STATUS & USB_EP_BUSNACK0_bm) ? true : false);
}

bool Endpoint_IsOUTReceived(void)
{
	Endpoint_SelectEndpoint(USB_Endpoint_SelectedEndpoint & ~ENDPOINT_DIR_IN);

	if (USB_Endpoint_SelectedHandle->STATUS & USB_EP_TRNCOMPL0_bm)
	{
		USB_Endpoint_SelectedFIFO->Length = USB_Endpoint_SelectedHandle->CNT;
		return true;
	}

	return false;
}

bool Endpoint_IsSETUPReceived(void)
{
	Endpoint_SelectEndpoint(USB_Endpoint_SelectedEndpoint & ~ENDPOINT_DIR_IN);

	if (USB_Endpoint_SelectedHandle->STATUS & USB_EP_SETUP_bm)
	{
		USB_Endpoint_SelectedFIFO->Length = USB_Endpoint_SelectedHandle->CNT;
		return true;
	}

	return false;
}

void Endpoint_ClearSETUP(void)
{
	Endpoint_SelectEndpoint(USB_Endpoint_SelectedEndpoint & ~ENDPOINT_DIR_IN);
	USB_Endpoint_SelectedHandle->STATUS &= ~(USB_EP_SETUP_bm | USB_EP_TRNCOMPL0_bm | USB_EP_BUSNACK0_bm | USB_EP_OVF_bm);
	USB_Endpoint_SelectedHandle->STATUS |= USB_EP_TOGGLE_bm;
	USB_Endpoint_SelectedFIFO->Position  = 0;

	Endpoint_SelectEndpoint(USB_Endpoint_SelectedEndpoint | ENDPOINT_DIR_IN);
	USB_Endpoint_SelectedHandle->STATUS |= USB_EP_TOGGLE_bm;
	USB_Endpoint_SelectedFIFO->Position  = 0;
}

void Endpoint_ClearIN(void)
{
	USB_Endpoint_SelectedHandle->CNT     = USB_Endpoint_SelectedFIFO->Position;
	USB_Endpoint_SelectedHandle->STATUS &= ~(USB_EP_TRNCOMPL0_bm | USB_EP_BUSNACK0_bm | USB_EP_OVF_bm);
	USB_Endpoint_SelectedFIFO->Position  = 0;
}

void Endpoint_ClearOUT(void)
{
	USB_Endpoint_SelectedHandle->STATUS &= ~(USB_EP_TRNCOMPL0_bm | USB_EP_BUSNACK0_bm | USB_EP_OVF_bm);
	USB_Endpoint_SelectedFIFO->Position  = 0;
}

void Endpoint_StallTransaction(void)
{
	USB_Endpoint_SelectedHandle->CTRL |= USB_EP_STALL_bm;

	if ((USB_Endpoint_SelectedHandle->CTRL & USB_EP_TYPE_gm) == USB_EP_TYPE_CONTROL_gc)
	{
		Endpoint_SelectEndpoint(USB_Endpoint_SelectedEndpoint ^ ENDPOINT_DIR_IN);
		USB_Endpoint_SelectedHandle->CTRL |= USB_EP_STALL_bm;
	}
}

uint8_t Endpoint_Read_8(void)
{
	return USB_Endpoint_SelectedFIFO->Data[USB_Endpoint_SelectedFIFO->Position++];
}

void Endpoint_Write_8(const uint8_t Data)
{
	USB_Endpoint_SelectedFIFO->Data[USB_Endpoint_SelectedFIFO->Position++] = Data;
}

void Endpoint_SelectEndpoint(const uint8_t Address)
{
	uint8_t EndpointNumber = (Address & ENDPOINT_EPNUM_MASK);

	USB_Endpoint_SelectedEndpoint = Address;

	Endpoint_FIFOPair_t* EndpointFIFOPair = &USB_Endpoint_FIFOs[EndpointNumber];
	USB_EndpointTable_t* EndpointTable    = (USB_EndpointTable_t*)USB.EPPTR;

	if (Address & ENDPOINT_DIR_IN)
	{
		USB_Endpoint_SelectedFIFO   = &EndpointFIFOPair->IN;
		USB_Endpoint_SelectedHandle = &EndpointTable->Endpoints[EndpointNumber].IN;
	}
	else
	{
		USB_Endpoint_SelectedFIFO   = &EndpointFIFOPair->OUT;
		USB_Endpoint_SelectedHandle = &EndpointTable->Endpoints[EndpointNumber].OUT;
	}
}

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

