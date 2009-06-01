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

#define  INCLUDE_FROM_MS_CLASS_C
#include "MassStorage.h"

static USB_ClassInfo_MS_t* CallbackMSInterfaceInfo;

void USB_MS_ProcessControlPacket(USB_ClassInfo_MS_t* MSInterfaceInfo)
{
	if (!(Endpoint_IsSETUPReceived()))
	  return;
	  
	if (USB_ControlRequest.wIndex != MSInterfaceInfo->InterfaceNumber)
	  return;

	switch (USB_ControlRequest.bRequest)
	{
		case REQ_MassStorageReset:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				MSInterfaceInfo->IsMassStoreReset = true;			

				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}

			break;
		case REQ_GetMaxLUN:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				Endpoint_Write_Byte(MSInterfaceInfo->TotalLUNs - 1);
				
				Endpoint_ClearIN();
				
				while (!(Endpoint_IsOUTReceived()));
				Endpoint_ClearOUT();
			}
			
			break;
	}
}

bool USB_MS_ConfigureEndpoints(USB_ClassInfo_MS_t* MSInterfaceInfo)
{
	if (!(Endpoint_ConfigureEndpoint(MSInterfaceInfo->DataINEndpointNumber, EP_TYPE_BULK,
							         ENDPOINT_DIR_IN, MSInterfaceInfo->DataINEndpointSize,
							         ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}

	if (!(Endpoint_ConfigureEndpoint(MSInterfaceInfo->DataOUTEndpointNumber, EP_TYPE_BULK,
	                                 ENDPOINT_DIR_OUT, MSInterfaceInfo->DataOUTEndpointSize,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}

	return true;
}

void USB_MS_USBTask(USB_ClassInfo_MS_t* MSInterfaceInfo)
{
	if (!(USB_IsConnected))
	  return;

	Endpoint_SelectEndpoint(MSInterfaceInfo->DataOUTEndpointNumber);
		
	if (Endpoint_IsReadWriteAllowed())
	{
		if (USB_MS_ReadInCommandBlock(MSInterfaceInfo))
		{
			if (MSInterfaceInfo->CommandBlock.Flags & COMMAND_DIRECTION_DATA_IN)
			  Endpoint_SelectEndpoint(MSInterfaceInfo->DataINEndpointNumber);
			  
			MSInterfaceInfo->CommandStatus.Status              = CALLBACK_USB_MS_SCSICommandReceived(MSInterfaceInfo) ?
			                                                      Command_Pass : Command_Fail;
			MSInterfaceInfo->CommandStatus.Signature           = CSW_SIGNATURE;
			MSInterfaceInfo->CommandStatus.Tag                 = MSInterfaceInfo->CommandBlock.Tag;
			MSInterfaceInfo->CommandStatus.DataTransferResidue = MSInterfaceInfo->CommandBlock.DataTransferLength;

			if ((MSInterfaceInfo->CommandStatus.Status == Command_Fail) && (MSInterfaceInfo->CommandStatus.DataTransferResidue))
			  Endpoint_StallTransaction();
			
			USB_MS_ReturnCommandStatus(MSInterfaceInfo);
			
			if (MSInterfaceInfo->IsMassStoreReset)
			{
				Endpoint_ResetFIFO(MSInterfaceInfo->DataOUTEndpointNumber);
				Endpoint_ResetFIFO(MSInterfaceInfo->DataINEndpointNumber);
				
				Endpoint_SelectEndpoint(MSInterfaceInfo->DataOUTEndpointNumber);
				Endpoint_ClearStall();
				Endpoint_SelectEndpoint(MSInterfaceInfo->DataINEndpointNumber);
				Endpoint_ClearStall();

				MSInterfaceInfo->IsMassStoreReset = false;
			}
		}
	}
}

static bool USB_MS_ReadInCommandBlock(USB_ClassInfo_MS_t* MSInterfaceInfo)
{
	Endpoint_SelectEndpoint(MSInterfaceInfo->DataOUTEndpointNumber);

	CallbackMSInterfaceInfo = MSInterfaceInfo;
	Endpoint_Read_Stream_LE(&MSInterfaceInfo->CommandBlock,
	                        (sizeof(CommandBlockWrapper_t) - MAX_SCSI_COMMAND_LENGTH),
	                        StreamCallback_AbortOnMassStoreReset);

	if ((MSInterfaceInfo->CommandBlock.Signature         != CBW_SIGNATURE)              ||
	    (MSInterfaceInfo->CommandBlock.LUN               >= MSInterfaceInfo->TotalLUNs) ||
		(MSInterfaceInfo->CommandBlock.SCSICommandLength >  MAX_SCSI_COMMAND_LENGTH))
	{
		Endpoint_StallTransaction();
		Endpoint_SelectEndpoint(MSInterfaceInfo->DataINEndpointNumber);
		Endpoint_StallTransaction();
		
		return false;
	}

	CallbackMSInterfaceInfo = MSInterfaceInfo;
	Endpoint_Read_Stream_LE(&MSInterfaceInfo->CommandBlock.SCSICommandData,
	                        MSInterfaceInfo->CommandBlock.SCSICommandLength,
	                        StreamCallback_AbortOnMassStoreReset);
							
	Endpoint_ClearOUT();
	  
	if (MSInterfaceInfo->IsMassStoreReset)
	  return false;

	return true;
}

static void USB_MS_ReturnCommandStatus(USB_ClassInfo_MS_t* MSInterfaceInfo)
{
	Endpoint_SelectEndpoint(MSInterfaceInfo->DataOUTEndpointNumber);

	while (Endpoint_IsStalled())
	{
		USB_USBTask();

		if (MSInterfaceInfo->IsMassStoreReset)
		  return;
	}

	Endpoint_SelectEndpoint(MSInterfaceInfo->DataINEndpointNumber);

	while (Endpoint_IsStalled())
	{
		USB_USBTask();

		if (MSInterfaceInfo->IsMassStoreReset)
		  return;
	}
	
	CallbackMSInterfaceInfo = MSInterfaceInfo;
	Endpoint_Write_Stream_LE(&MSInterfaceInfo->CommandStatus, sizeof(CommandStatusWrapper_t),
	                         StreamCallback_AbortOnMassStoreReset);
	
	Endpoint_ClearIN();

	if (MSInterfaceInfo->IsMassStoreReset)
	  return;
}

static uint8_t StreamCallback_AbortOnMassStoreReset(void)
{
	USB_MS_USBTask(CallbackMSInterfaceInfo);

	if (CallbackMSInterfaceInfo->IsMassStoreReset)
	  return STREAMCALLBACK_Abort;
	else
	  return STREAMCALLBACK_Continue;
}
