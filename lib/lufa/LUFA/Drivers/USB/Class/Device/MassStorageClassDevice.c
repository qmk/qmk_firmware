/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#define  __INCLUDE_FROM_MS_DRIVER
#define  __INCLUDE_FROM_MASSSTORAGE_DEVICE_C
#include "MassStorageClassDevice.h"

void MS_Device_ProcessControlRequest(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	if (!(Endpoint_IsSETUPReceived()))
	  return;

	if (USB_ControlRequest.wIndex != MSInterfaceInfo->Config.InterfaceNumber)
	  return;

	switch (USB_ControlRequest.bRequest)
	{
		case MS_REQ_MassStorageReset:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_ClearStatusStage();

				MSInterfaceInfo->State.IsMassStoreReset = true;
			}

			break;
		case MS_REQ_GetMaxLUN:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				while (!(Endpoint_IsINReady()));
				Endpoint_Write_8(MSInterfaceInfo->Config.TotalLUNs - 1);
				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}

			break;
	}
}

bool MS_Device_ConfigureEndpoints(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	memset(&MSInterfaceInfo->State, 0x00, sizeof(MSInterfaceInfo->State));

	MSInterfaceInfo->Config.DataINEndpoint.Type  = EP_TYPE_BULK;
	MSInterfaceInfo->Config.DataOUTEndpoint.Type = EP_TYPE_BULK;

	if (!(Endpoint_ConfigureEndpointTable(&MSInterfaceInfo->Config.DataINEndpoint, 1)))
	  return false;

	if (!(Endpoint_ConfigureEndpointTable(&MSInterfaceInfo->Config.DataOUTEndpoint, 1)))
	  return false;

	return true;
}

void MS_Device_USBTask(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataOUTEndpoint.Address);

	if (Endpoint_IsOUTReceived())
	{
		if (MS_Device_ReadInCommandBlock(MSInterfaceInfo))
		{
			if (MSInterfaceInfo->State.CommandBlock.Flags & MS_COMMAND_DIR_DATA_IN)
			  Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataINEndpoint.Address);

			bool SCSICommandResult = CALLBACK_MS_Device_SCSICommandReceived(MSInterfaceInfo);

			MSInterfaceInfo->State.CommandStatus.Status              = (SCSICommandResult) ? MS_SCSI_COMMAND_Pass : MS_SCSI_COMMAND_Fail;
			MSInterfaceInfo->State.CommandStatus.Signature           = CPU_TO_LE32(MS_CSW_SIGNATURE);
			MSInterfaceInfo->State.CommandStatus.Tag                 = MSInterfaceInfo->State.CommandBlock.Tag;
			MSInterfaceInfo->State.CommandStatus.DataTransferResidue = MSInterfaceInfo->State.CommandBlock.DataTransferLength;

			if (!(SCSICommandResult) && (le32_to_cpu(MSInterfaceInfo->State.CommandStatus.DataTransferResidue)))
			  Endpoint_StallTransaction();

			MS_Device_ReturnCommandStatus(MSInterfaceInfo);
		}
	}

	if (MSInterfaceInfo->State.IsMassStoreReset)
	{
		Endpoint_ResetEndpoint(MSInterfaceInfo->Config.DataOUTEndpoint.Address);
		Endpoint_ResetEndpoint(MSInterfaceInfo->Config.DataINEndpoint.Address);

		Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataOUTEndpoint.Address);
		Endpoint_ClearStall();
		Endpoint_ResetDataToggle();
		Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataINEndpoint.Address);
		Endpoint_ClearStall();
		Endpoint_ResetDataToggle();

		MSInterfaceInfo->State.IsMassStoreReset = false;
	}
}

static bool MS_Device_ReadInCommandBlock(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	uint16_t BytesProcessed;

	Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataOUTEndpoint.Address);

	BytesProcessed = 0;
	while (Endpoint_Read_Stream_LE(&MSInterfaceInfo->State.CommandBlock,
	                               (sizeof(MS_CommandBlockWrapper_t) - 16), &BytesProcessed) ==
	                               ENDPOINT_RWSTREAM_IncompleteTransfer)
	{
		if (MSInterfaceInfo->State.IsMassStoreReset)
		  return false;
	}

	if ((MSInterfaceInfo->State.CommandBlock.Signature         != CPU_TO_LE32(MS_CBW_SIGNATURE))     ||
	    (MSInterfaceInfo->State.CommandBlock.LUN               >= MSInterfaceInfo->Config.TotalLUNs) ||
		(MSInterfaceInfo->State.CommandBlock.Flags              & 0x1F)                              ||
		(MSInterfaceInfo->State.CommandBlock.SCSICommandLength == 0)                                 ||
		(MSInterfaceInfo->State.CommandBlock.SCSICommandLength >  16))
	{
		Endpoint_StallTransaction();
		Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataINEndpoint.Address);
		Endpoint_StallTransaction();

		return false;
	}

	BytesProcessed = 0;
	while (Endpoint_Read_Stream_LE(&MSInterfaceInfo->State.CommandBlock.SCSICommandData,
	                                MSInterfaceInfo->State.CommandBlock.SCSICommandLength, &BytesProcessed) ==
	                                ENDPOINT_RWSTREAM_IncompleteTransfer)
	{
		if (MSInterfaceInfo->State.IsMassStoreReset)
		  return false;
	}

	Endpoint_ClearOUT();

	return true;
}

static void MS_Device_ReturnCommandStatus(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataOUTEndpoint.Address);

	while (Endpoint_IsStalled())
	{
		#if !defined(INTERRUPT_CONTROL_ENDPOINT)
		USB_USBTask();
		#endif

		if (MSInterfaceInfo->State.IsMassStoreReset)
		  return;
	}

	Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataINEndpoint.Address);

	while (Endpoint_IsStalled())
	{
		#if !defined(INTERRUPT_CONTROL_ENDPOINT)
		USB_USBTask();
		#endif

		if (MSInterfaceInfo->State.IsMassStoreReset)
		  return;
	}

	uint16_t BytesProcessed = 0;
	while (Endpoint_Write_Stream_LE(&MSInterfaceInfo->State.CommandStatus,
	                                sizeof(MS_CommandStatusWrapper_t), &BytesProcessed) ==
	                                ENDPOINT_RWSTREAM_IncompleteTransfer)
	{
		if (MSInterfaceInfo->State.IsMassStoreReset)
		  return;
	}

	Endpoint_ClearIN();
}

#endif

