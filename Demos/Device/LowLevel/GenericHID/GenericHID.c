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

/** \file
 *
 *  Main source file for the GenericHID demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "GenericHID.h"

/** Static buffer to hold the last received report from the host, so that it can be echoed back in the next sent report */
static uint8_t LastReceived[GENERIC_REPORT_SIZE];


/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the USB management task.
 */
int main(void)
{
	SetupHardware();
	
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		HID_Task();
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
void EVENT_USB_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management task.
 */
void EVENT_USB_Disconnect(void)
{
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host sets the current configuration
 *  of the USB device after enumeration, and configures the generic HID device endpoints.
 */
void EVENT_USB_ConfigurationChanged(void)
{
	/* Indicate USB connected and ready */
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	/* Setup Generic IN Report Endpoint */
	if (!(Endpoint_ConfigureEndpoint(GENERIC_IN_EPNUM, EP_TYPE_INTERRUPT,
		                             ENDPOINT_DIR_IN, GENERIC_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
	
	/* Setup Generic OUT Report Endpoint */
	if (!(Endpoint_ConfigureEndpoint(GENERIC_OUT_EPNUM, EP_TYPE_INTERRUPT,
		                             ENDPOINT_DIR_OUT, GENERIC_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the HID commands, which are
 *  all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
void EVENT_USB_UnhandledControlPacket(void)
{
	/* Handle HID Class specific requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				uint8_t GenericData[GENERIC_REPORT_SIZE];

				Endpoint_ClearSETUP();
	
				CreateGenericHIDReport(GenericData);

				/* Write the report data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(&GenericData, sizeof(GenericData));

				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearOUT();
			}
		
			break;
		case REQ_SetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				uint8_t GenericData[GENERIC_REPORT_SIZE];

				Endpoint_ClearSETUP();
				
				/* Wait until the generic report has been sent by the host */
				while (!(Endpoint_IsOUTReceived()));

				Endpoint_Read_Control_Stream_LE(&GenericData, sizeof(GenericData));

				ProcessGenericHIDReport(GenericData);
			
				/* Clear the endpoint data */
				Endpoint_ClearOUT();

				/* Wait until the host is ready to receive the request confirmation */
				while (!(Endpoint_IsINReady()));
				
				/* Handshake the request by sending an empty IN packet */
				Endpoint_ClearIN();
			}
			
			break;
	}
}

/** Function to process the lest received report from the host.
 *
 *  \param[in] DataArray  Pointer to a buffer where the last report data is stored
 */
void ProcessGenericHIDReport(uint8_t* DataArray)
{
	/*
		This is where you need to process the reports being sent from the host to the device.
		DataArray is an array holding the last report from the host. This function is called
		each time the host has sent a report to the device.
	*/
	
	for (uint8_t i = 0; i < GENERIC_REPORT_SIZE; i++)
	  LastReceived[i] = DataArray[i];
}

/** Function to create the next report to send back to the host at the next reporting interval.
 *
 *  \param[out] DataArray  Pointer to a buffer where the next report data should be stored
 */
void CreateGenericHIDReport(uint8_t* DataArray)
{
	/*
		This is where you need to create reports to be sent to the host from the device. This
		function is called each time the host is ready to accept a new report. DataArray is 
		an array to hold the report to the host.
	*/

	for (uint8_t i = 0; i < GENERIC_REPORT_SIZE; i++)
	  DataArray[i] = LastReceived[i];
}

void HID_Task(void)
{
	/* Check if the USB system is connected to a host */
	if (USB_IsConnected)
	{
		Endpoint_SelectEndpoint(GENERIC_OUT_EPNUM);
		
		/* Check to see if a packet has been sent from the host */
		if (Endpoint_IsOUTReceived())
		{
			/* Check to see if the packet contains data */
			if (Endpoint_IsReadWriteAllowed())
			{
				/* Create a temporary buffer to hold the read in report from the host */
				uint8_t GenericData[GENERIC_REPORT_SIZE];
				
				/* Read Generic Report Data */
				Endpoint_Read_Stream_LE(&GenericData, sizeof(GenericData));
				
				/* Process Generic Report Data */
				ProcessGenericHIDReport(GenericData);
			}

			/* Finalize the stream transfer to send the last packet */
			Endpoint_ClearOUT();
		}	

		Endpoint_SelectEndpoint(GENERIC_IN_EPNUM);
		
		/* Check to see if the host is ready to accept another packet */
		if (Endpoint_IsINReady())
		{
			/* Create a temporary buffer to hold the report to send to the host */
			uint8_t GenericData[GENERIC_REPORT_SIZE];
			
			/* Create Generic Report Data */
			CreateGenericHIDReport(GenericData);

			/* Write Generic Report Data */
			Endpoint_Write_Stream_LE(&GenericData, sizeof(GenericData));

			/* Finalize the stream transfer to send the last packet */
			Endpoint_ClearIN();
		}
	}
}
