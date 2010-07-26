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
		.Status     = TMC_REQUEST_STATUS_SUCCESS,
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
uint8_t RequestInProgess = 0;

/** Stream callback abort flag for bulk IN data */
bool IsTMCBulkINReset    = false;

/** Stream callback abort flag for bulk OUT data */
bool IsTMCBulkOUTReset   = false;


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

void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

void EVENT_USB_Device_ConfigurationChanged(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	/* Setup TMC In and Out Endpoints */
	if (!(Endpoint_ConfigureEndpoint(TMC_IN_EPNUM, EP_TYPE_BULK,
		                             ENDPOINT_DIR_IN, TMC_IO_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}

	if (!(Endpoint_ConfigureEndpoint(TMC_OUT_EPNUM, EP_TYPE_BULK,
		                             ENDPOINT_DIR_OUT, TMC_IO_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
}

void EVENT_USB_Device_UnhandledControlRequest(void)
{
	switch (USB_ControlRequest.bRequest)
	{
		case Req_InitiateAbortBulkOut:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				Endpoint_ClearSETUP();
				
				/* Check to see if a split request is already being processed before starting a new one */
				if (RequestInProgess != 0)
				{
					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SPLIT_IN_PROGRESS);				
				}
				else
				{
					/* Indicate that all in-progress/pending data OUT requests should be aborted */
					IsTMCBulkOUTReset = true;
					
					/* Save the split request for later checking when a new request is received */
					RequestInProgess = Req_InitiateAbortBulkOut;

					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SUCCESS);
				}
				
				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}
			
			break;
		case Req_CheckAbortBulkOutStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				Endpoint_ClearSETUP();
				
				/* Check to see the correct split request is in progress before the status can be retrieved */
				if (RequestInProgess != Req_InitiateAbortBulkOut)
				{
					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SPLIT_NOT_IN_PROGRESS);				
				}
				else
				{
					// TODO: CLEAR BULK OUT
				
					/* Clear the pending split request value so that a new request can be made */
					RequestInProgess = 0;

					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SUCCESS);
				}
				
				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();				
			}
			
			break;
		case Req_InitiateAbortBulkIn:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				Endpoint_ClearSETUP();
				
				/* Check to see if a split request is already being processed before starting a new one */
				if (RequestInProgess != 0)
				{
					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SPLIT_IN_PROGRESS);				
				}
				else
				{
					/* Indicate that all in-progress/pending data IN requests should be aborted */
					IsTMCBulkINReset  = true;
					
					/* Save the split request for later checking when a new request is received */
					RequestInProgess = Req_InitiateAbortBulkIn;

					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SUCCESS);
				}
				
				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}
			
			break;
		case Req_CheckAbortBulkInStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				Endpoint_ClearSETUP();
				
				/* Check to see the correct split request is in progress before the status can be retrieved */
				if (RequestInProgess != Req_InitiateAbortBulkIn)
				{
					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SPLIT_NOT_IN_PROGRESS);				
				}
				else
				{
					// TODO: CLEAR BULK IN
				
					/* Clear the pending split request value so that a new request can be made */
					RequestInProgess = 0;

					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SUCCESS);
				}
				
				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();				
			}
			
			break;
		case Req_InitiateClear:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				/* Check to see if a split request is already being processed before starting a new one */
				if (RequestInProgess != 0)
				{
					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SPLIT_IN_PROGRESS);				
				}
				else
				{
					/* Indicate that all in-progress/pending data IN and OUT requests should be aborted */
					IsTMCBulkINReset  = true;
					IsTMCBulkOUTReset = true;
					
					/* Save the split request for later checking when a new request is received */
					RequestInProgess = Req_InitiateClear;

					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SUCCESS);
				}
				
				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}
			
			break;
		case Req_CheckClearStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				/* Check to see the correct split request is in progress before the status can be retrieved */
				if (RequestInProgess != Req_InitiateClear)
				{
					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SPLIT_NOT_IN_PROGRESS);				
				}
				else
				{
					// TODO: CLEAR STATUS
				
					/* Clear the pending split request value so that a new request can be made */
					RequestInProgess = 0;

					Endpoint_Write_Byte(TMC_REQUEST_STATUS_SUCCESS);
				}
				
				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();				
			}
			
			break;
		case Req_GetCapabilities:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Acknowledge the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();
					
				/* Write the device capabilities to the control endpoint */
				Endpoint_Write_Control_Stream_LE(&Capabilities, sizeof(TMC_Capabilities_t));
				
				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearOUT();
			}
			
			break;
	}
}
	
void TMC_Task(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;
	  
	Endpoint_SelectEndpoint(TMC_OUT_EPNUM);
	
	if (Endpoint_IsOUTReceived())
	{
		// TEMP - Indicate data received
		LEDs_SetAllLEDs(LEDS_ALL_LEDS);
		Endpoint_ClearOUT();
	}
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
