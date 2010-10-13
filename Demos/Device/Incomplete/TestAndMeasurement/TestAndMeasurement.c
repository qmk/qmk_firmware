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

#include "TestAndMeasurement.h"

/** Contains the (usually static) capabilities of the TMC device. This table is requested by the
 *  host upon enumeration to give it information on what features of the Test and Measurement USB
 *  Class the device supports.
 */
TMC_Capabilities_t Capabilities =
	{
		.Status     = TMC_STATUS_SUCCESS,
		.TMCVersion = VERSION_BCD(1.00),
		
		.Interface  =
			{
				.ListenOnly             = false,
				.TalkOnly               = false,
				.PulseIndicateSupported = false,
			},

		.Device     =
			{
				.SupportsAbortINOnMatch = false,
			},
	};

/** Current TMC control request that is being processed */
uint8_t RequestInProgress = 0;

/** Stream callback abort flag for bulk IN data */
bool IsTMCBulkINReset = false;

/** Stream callback abort flag for bulk OUT data */
bool IsTMCBulkOUTReset = false;

/** Last used tag value for data transfers */
uint8_t CurrentTransferTag = 0;


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	sei();
	
	for (;;)
	{
		TMC_Task();
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
	
	/* Hardware Initialization */
	LEDs_Init();
	USB_Init();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management and CDC management tasks.
 */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the CDC management task started.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	/* Setup TMC In, Out and Notification Endpoints */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(TMC_NOTIFICATION_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN,
	                                            TMC_IO_EPSIZE, ENDPOINT_BANK_SINGLE);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(TMC_IN_EPNUM,  EP_TYPE_BULK, ENDPOINT_DIR_IN,
	                                            TMC_IO_EPSIZE, ENDPOINT_BANK_SINGLE);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(TMC_OUT_EPNUM, EP_TYPE_BULK, ENDPOINT_DIR_OUT,
	                                            TMC_IO_EPSIZE, ENDPOINT_BANK_SINGLE);

	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the USB_UnhandledControlRequest event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the CDC control commands,
 *  which are all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	uint8_t TMCRequestStatus = TMC_STATUS_SUCCESS;

	/* Process TMC specific control requests */
	switch (USB_ControlRequest.bRequest)
	{
		case Req_InitiateAbortBulkOut:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				/* Check that no split transaction is already in progress and the data transfer tag is valid */
				if (RequestInProgress != 0)
				{
					TMCRequestStatus = TMC_STATUS_SPLIT_IN_PROGRESS;
				}
				else if (USB_ControlRequest.wValue != CurrentTransferTag)
				{
					TMCRequestStatus = TMC_STATUS_TRANSFER_NOT_IN_PROGRESS;
				}
				else
				{
					/* Indicate that all in-progress/pending data OUT requests should be aborted */
					IsTMCBulkOUTReset = true;
					
					/* Save the split request for later checking when a new request is received */
					RequestInProgress = Req_InitiateAbortBulkOut;
				}

				Endpoint_ClearSETUP();
				
				/* Write the request response byte */
				Endpoint_Write_Byte(TMCRequestStatus);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}
			
			break;
		case Req_CheckAbortBulkOutStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				/* Check that an ABORT BULK OUT transaction has been requested and that the request has completed */
				if (RequestInProgress != Req_InitiateAbortBulkOut)
				  TMCRequestStatus = TMC_STATUS_SPLIT_NOT_IN_PROGRESS;				
				else if (IsTMCBulkOUTReset)
				  TMCRequestStatus = TMC_STATUS_PENDING;
				else
				  RequestInProgress = 0;	

				Endpoint_ClearSETUP();
								
				/* Write the request response bytes */
				Endpoint_Write_Byte(TMCRequestStatus);
				Endpoint_Write_Word_LE(0);
				Endpoint_Write_DWord_LE(0); // TODO - Last transfer length

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();				
			}
			
			break;
		case Req_InitiateAbortBulkIn:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				/* Check that no split transaction is already in progress and the data transfer tag is valid */
				if (RequestInProgress != 0)
				{
					TMCRequestStatus = TMC_STATUS_SPLIT_IN_PROGRESS;				
				}
				else if (USB_ControlRequest.wValue != CurrentTransferTag)
				{
					TMCRequestStatus = TMC_STATUS_TRANSFER_NOT_IN_PROGRESS;
				}
				else
				{
					/* Indicate that all in-progress/pending data IN requests should be aborted */
					IsTMCBulkINReset = true;
					
					/* Save the split request for later checking when a new request is received */
					RequestInProgress = Req_InitiateAbortBulkIn;
				}

				Endpoint_ClearSETUP();
				
				/* Write the request response bytes */
				Endpoint_Write_Byte(TMCRequestStatus);
				Endpoint_Write_Byte(CurrentTransferTag);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}
			
			break;
		case Req_CheckAbortBulkInStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				/* Check that an ABORT BULK IN transaction has been requested and that the request has completed */
				if (RequestInProgress != Req_InitiateAbortBulkIn)
				  TMCRequestStatus = TMC_STATUS_SPLIT_NOT_IN_PROGRESS;
				else if (IsTMCBulkINReset)
				  TMCRequestStatus = TMC_STATUS_PENDING;
				else
				  RequestInProgress = 0;

				Endpoint_ClearSETUP();
								
				/* Write the request response bytes */
				Endpoint_Write_Byte(TMCRequestStatus);
				Endpoint_Write_Word_LE(0);
				Endpoint_Write_DWord_LE(0); // TODO - Last transfer length

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}
			
			break;
		case Req_InitiateClear:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Check that no split transaction is already in progress */
				if (RequestInProgress != 0)
				{
					Endpoint_Write_Byte(TMC_STATUS_SPLIT_IN_PROGRESS);				
				}
				else
				{
					/* Indicate that all in-progress/pending data IN and OUT requests should be aborted */
					IsTMCBulkINReset  = true;
					IsTMCBulkOUTReset = true;
					
					/* Save the split request for later checking when a new request is received */
					RequestInProgress = Req_InitiateClear;
				}

				Endpoint_ClearSETUP();
				
				/* Write the request response byte */
				Endpoint_Write_Byte(TMCRequestStatus);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}
			
			break;
		case Req_CheckClearStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Check that a CLEAR transaction has been requested and that the request has completed */
				if (RequestInProgress != Req_InitiateClear)
				  TMCRequestStatus = TMC_STATUS_SPLIT_NOT_IN_PROGRESS;				
				else if (IsTMCBulkINReset || IsTMCBulkOUTReset)
				  TMCRequestStatus = TMC_STATUS_PENDING;
				else
				  RequestInProgress = 0;

				Endpoint_ClearSETUP();

				/* Write the request response bytes */
				Endpoint_Write_Byte(TMCRequestStatus);
				Endpoint_Write_Byte(0);
				
				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();				
			}
			
			break;
		case Req_GetCapabilities:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
					
				/* Write the device capabilities to the control endpoint */
				Endpoint_Write_Control_Stream_LE(&Capabilities, sizeof(TMC_Capabilities_t));				
				Endpoint_ClearOUT();
			}
			
			break;
	}
}

/** Function to manage TMC data transmission and reception to and from the host. */
void TMC_Task(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;
	
	TMC_MessageHeader_t MessageHeader;
	
	/* Try to read in a TMC message from the interface, process if one is available */
	if (ReadTMCHeader(&MessageHeader))
	{
		/* Indicate busy */
		LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
		
		switch (MessageHeader.MessageID)
		{
			case TMC_MESSAGEID_DEV_DEP_MSG_OUT:
				Endpoint_Discard_Stream(MessageHeader.TransferSize, StreamCallback_AbortOUTOnRequest);
				Endpoint_ClearOUT();
				break;
			case TMC_MESSAGEID_DEV_DEP_MSG_IN:
				Endpoint_ClearOUT();

				MessageHeader.TransferSize = 3;
				WriteTMCHeader(&MessageHeader);

				Endpoint_Write_Stream_LE("TMC", 3, StreamCallback_AbortINOnRequest);
				Endpoint_ClearIN();
				break;
			default:
				Endpoint_StallTransaction();
				break;
		}

		LEDs_SetAllLEDs(LEDMASK_USB_READY);
	}
	
	/* All pending data has been processed - reset the data abort flags */
	IsTMCBulkINReset  = false;
	IsTMCBulkOUTReset = false;
}

/** Attempts to read in the TMC message header from the TMC interface.
 *
 *  \param[out] MessageHeader  Pointer to a location where the read header (if any) should be stored
 *
 *  \return Boolean true if a header was read, false otherwise
 */
bool ReadTMCHeader(TMC_MessageHeader_t* const MessageHeader)
{
	/* Select the Data Out endpoint */
	Endpoint_SelectEndpoint(TMC_OUT_EPNUM);
	
	/* Abort if no command has been sent from the host */
	if (!(Endpoint_IsOUTReceived()))
	  return false;
	
	/* Read in the header of the command from the host */
	Endpoint_Read_Stream_LE(MessageHeader, sizeof(TMC_MessageHeader_t), StreamCallback_AbortOUTOnRequest);

	/* Store the new command tag value for later use */
	CurrentTransferTag = MessageHeader->Tag;
	
	/* Indicate if the command has been aborted or not */
	return !(IsTMCBulkOUTReset);
}

bool WriteTMCHeader(TMC_MessageHeader_t* const MessageHeader)
{
	/* Compute the next transfer tag value, must be between 1 and 254 */
	if (++CurrentTransferTag == 0xFF)
	  CurrentTransferTag = 1;

	/* Set the message tag of the command header */
	MessageHeader->Tag        =  CurrentTransferTag;
	MessageHeader->InverseTag = ~CurrentTransferTag;

	/* Select the Data In endpoint */
	Endpoint_SelectEndpoint(TMC_IN_EPNUM);

	/* Send the command header to the host */
	Endpoint_Write_Stream_LE(MessageHeader, sizeof(TMC_MessageHeader_t), StreamCallback_AbortINOnRequest);

	/* Indicate if the command has been aborted or not */
	return !(IsTMCBulkINReset);
}

/** Stream callback function for the Endpoint stream write functions. This callback will abort the current stream transfer
 *  if a TMC Abort Bulk IN request has been issued to the control endpoint.
 */
uint8_t StreamCallback_AbortINOnRequest(void)
{	
	/* Abort if a TMC Bulk Data IN abort was received */
	if (IsTMCBulkINReset)
	  return STREAMCALLBACK_Abort;
	
	/* Continue with the current stream operation */
	return STREAMCALLBACK_Continue;
}

/** Stream callback function for the Endpoint stream read functions. This callback will abort the current stream transfer
 *  if a TMC Abort Bulk OUT request has been issued to the control endpoint.
 */
uint8_t StreamCallback_AbortOUTOnRequest(void)
{	
	/* Abort if a TMC Bulk Data IN abort was received */
	if (IsTMCBulkOUTReset)
	  return STREAMCALLBACK_Abort;
	
	/* Continue with the current stream operation */
	return STREAMCALLBACK_Continue;
}

