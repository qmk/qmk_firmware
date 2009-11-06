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

#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_DEVICE)

#define  INCLUDE_FROM_MS_CLASS_DEVICE_C
#include "MassStorage.h"

static USB_ClassInfo_MS_Device_t* CallbackMSInterfaceInfo;

void MS_Device_ProcessControlRequest(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	if (!(Endpoint_IsSETUPReceived()))
	  return;
	  
	if (USB_ControlRequest.wIndex != MSInterfaceInfo->Config.InterfaceNumber)
	  return;

	switch (USB_ControlRequest.bRequest)
	{
		case REQ_MassStorageReset:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				MSInterfaceInfo->State.IsMassStoreReset = true;			

				Endpoint_ClearStatusStage();
			}

			break;
		case REQ_GetMaxLUN:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				Endpoint_Write_Byte(MSInterfaceInfo->Config.TotalLUNs - 1);				
				Endpoint_ClearIN();
				
				Endpoint_ClearStatusStage();
			}
			
			break;
	}
}

bool MS_Device_ConfigureEndpoints(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	memset(&MSInterfaceInfo->State, 0x00, sizeof(MSInterfaceInfo->State));

	if (!(Endpoint_ConfigureEndpoint(MSInterfaceInfo->Config.DataINEndpointNumber, EP_TYPE_BULK,
							         ENDPOINT_DIR_IN, MSInterfaceInfo->Config.DataINEndpointSize,
							         MSInterfaceInfo->Config.DataINEndpointDoubleBank ? ENDPOINT_BANK_DOUBLE : ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}

	if (!(Endpoint_ConfigureEndpoint(MSInterfaceInfo->Config.DataOUTEndpointNumber, EP_TYPE_BULK,
	                                 ENDPOINT_DIR_OUT, MSInterfaceInfo->Config.DataOUTEndpointSize,
	                                 MSInterfaceInfo->Config.DataOUTEndpointDoubleBank ? ENDPOINT_BANK_DOUBLE : ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}

	return true;
}

void MS_Device_USBTask(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataOUTEndpointNumber);
		
	if (Endpoint_IsReadWriteAllowed())
	{
		if (MS_Device_ReadInCommandBlock(MSInterfaceInfo))
		{
			if (MSInterfaceInfo->State.CommandBlock.Flags & MS_COMMAND_DIR_DATA_IN)
			  Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataINEndpointNumber);
			  
			MSInterfaceInfo->State.CommandStatus.Status = CALLBACK_MS_Device_SCSICommandReceived(MSInterfaceInfo) ?
			                                                                 SCSI_Command_Pass : SCSI_Command_Fail;
			MSInterfaceInfo->State.CommandStatus.Signature           = MS_CSW_SIGNATURE;
			MSInterfaceInfo->State.CommandStatus.Tag                 = MSInterfaceInfo->State.CommandBlock.Tag;
			MSInterfaceInfo->State.CommandStatus.DataTransferResidue = MSInterfaceInfo->State.CommandBlock.DataTransferLength;

			if ((MSInterfaceInfo->State.CommandStatus.Status == SCSI_Command_Fail) &&
			    (MSInterfaceInfo->State.CommandStatus.DataTransferResidue))
			{
				Endpoint_StallTransaction();
			}
			
			MS_Device_ReturnCommandStatus(MSInterfaceInfo);
			
			if (MSInterfaceInfo->State.IsMassStoreReset)
			{
				Endpoint_ResetFIFO(MSInterfaceInfo->Config.DataOUTEndpointNumber);
				Endpoint_ResetFIFO(MSInterfaceInfo->Config.DataINEndpointNumber);
				
				Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataOUTEndpointNumber);
				Endpoint_ClearStall();
				Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataINEndpointNumber);
				Endpoint_ClearStall();
			}
		}
	}
	
	MSInterfaceInfo->State.IsMassStoreReset = false;
}

static bool MS_Device_ReadInCommandBlock(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataOUTEndpointNumber);

	CallbackMSInterfaceInfo = MSInterfaceInfo;
	Endpoint_Read_Stream_LE(&MSInterfaceInfo->State.CommandBlock,
	                        (sizeof(MS_CommandBlockWrapper_t) - 16),
	                        StreamCallback_MS_Device_AbortOnMassStoreReset);

	if ((MSInterfaceInfo->State.CommandBlock.Signature         != MS_CBW_SIGNATURE)                  ||
	    (MSInterfaceInfo->State.CommandBlock.LUN               >= MSInterfaceInfo->Config.TotalLUNs) ||
		(MSInterfaceInfo->State.CommandBlock.Flags              & 0x1F)                              ||
		(MSInterfaceInfo->State.CommandBlock.SCSICommandLength == 0)                                 ||
		(MSInterfaceInfo->State.CommandBlock.SCSICommandLength >  16))
	{
		Endpoint_StallTransaction();
		Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataINEndpointNumber);
		Endpoint_StallTransaction();
		
		return false;
	}

	CallbackMSInterfaceInfo = MSInterfaceInfo;
	Endpoint_Read_Stream_LE(&MSInterfaceInfo->State.CommandBlock.SCSICommandData,
	                        MSInterfaceInfo->State.CommandBlock.SCSICommandLength,
	                        StreamCallback_MS_Device_AbortOnMassStoreReset);
							
	Endpoint_ClearOUT();
	  
	if (MSInterfaceInfo->State.IsMassStoreReset)
	  return false;

	return true;
}

static void MS_Device_ReturnCommandStatus(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataOUTEndpointNumber);

	while (Endpoint_IsStalled())
	{
		USB_USBTask();

		if (MSInterfaceInfo->State.IsMassStoreReset)
		  return;
	}

	Endpoint_SelectEndpoint(MSInterfaceInfo->Config.DataINEndpointNumber);

	while (Endpoint_IsStalled())
	{
		USB_USBTask();

		if (MSInterfaceInfo->State.IsMassStoreReset)
		  return;
	}
	
	CallbackMSInterfaceInfo = MSInterfaceInfo;
	Endpoint_Write_Stream_LE(&MSInterfaceInfo->State.CommandStatus, sizeof(MS_CommandStatusWrapper_t),
	                         StreamCallback_MS_Device_AbortOnMassStoreReset);
	
	Endpoint_ClearIN();

	if (MSInterfaceInfo->State.IsMassStoreReset)
	  return;
}

static uint8_t StreamCallback_MS_Device_AbortOnMassStoreReset(void)
{
	MS_Device_USBTask(CallbackMSInterfaceInfo);

	if (CallbackMSInterfaceInfo->State.IsMassStoreReset)
	  return STREAMCALLBACK_Abort;
	else
	  return STREAMCALLBACK_Continue;
}

#endif
