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

/*
	SideShow Class demonstration application. This give a reference
	for implementing Microsoft SideShow compatible devices in an
	embedded environment. SideShow allows for gadget data displayed
	on a Vista machine to also be displayed on an externally connected
	interactive display. Upon enumeration on a Vista system, this will
	appear as a new SideShow device which can have gadgets loaded onto
	it.
	
	Note that while the incomming content is buffered in packet struct
	form, the data is not actually displayed. It is left to the user to
	write sufficient code to read out the packed data for display to a
	screen.
	
	Installed gadgets can be accessed through the InstalledApplications
	array, with entries that have their InUse flag set being active. As
	only the active content is displayed on the device due to memory
	constraints, new content can be requested as needed.
*/

/*
	USB Mode:           Device
	USB Class:          Sideshow Device (Microsoft Only)
	USB Subclass:       Bulk Only
	Relevant Standards: Microsoft Sideshow Specification
	                    Microsoft OS Descriptors Specification
	                    XML Specification
	Usable Speeds:      Full Speed Mode
*/

#include "Sideshow.h"

/* Project Tags, for reading out using the ButtLoad project */
BUTTLOADTAG(ProjName,     "LUFA Sideshow App");
BUTTLOADTAG(BuildTime,    __TIME__);
BUTTLOADTAG(BuildDate,    __DATE__);
BUTTLOADTAG(LUFAVersion, "LUFA V" LUFA_VERSION_STRING);

/* Scheduler Task List */
TASK_LIST
{
	{ Task: USB_USBTask          , TaskStatus: TASK_STOP },
	{ Task: USB_Sideshow         , TaskStatus: TASK_STOP },
};

int main(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable Clock Division */
	SetSystemClockPrescaler(0);

	/* Hardware Initialization */
	SerialStream_Init(9600, false);
	LEDs_Init();
	HWB_Init();
	
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDS_LED1 | LEDS_LED3);
	
	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();

	/* Scheduling - routine never returns, so put this last in the main function */
	Scheduler_Start();
}

EVENT_HANDLER(USB_Connect)
{
	/* Start USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);

	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDS_LED1 | LEDS_LED4);
}

EVENT_HANDLER(USB_Disconnect)
{
	/* Stop running mass storage and USB management tasks */
	Scheduler_SetTaskMode(USB_Sideshow, TASK_STOP);
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);

	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDS_LED1 | LEDS_LED3);
}

EVENT_HANDLER(USB_ConfigurationChanged)
{
	/* Setup Sideshow In and Out Endpoints */
	Endpoint_ConfigureEndpoint(SIDESHOW_IN_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_IN, SIDESHOW_IO_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(SIDESHOW_OUT_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_OUT, SIDESHOW_IO_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	/* Indicate USB connected and ready */
	LEDs_SetAllLEDs(LEDS_LED2 | LEDS_LED4);
	
	/* Start Sideshow task */
	Scheduler_SetTaskMode(USB_Sideshow, TASK_RUN);
}

EVENT_HANDLER(USB_UnhandledControlPacket)
{
	/* Process UFI specific control requests */
	switch (bRequest)
	{
		case REQ_GetOSFeatureDescriptor:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_VENDOR | REQREC_DEVICE))
			{
				uint16_t wValue  = Endpoint_Read_Word_LE();
				uint16_t wIndex  = Endpoint_Read_Word_LE();
				uint16_t wLength = Endpoint_Read_Word_LE();

				void*    DescriptorPointer;
				uint16_t DescriptorSize;

				bool     SendZLP = true;
				
				if (!(USB_GetOSFeatureDescriptor(wValue, wIndex, &DescriptorPointer, &DescriptorSize)))
				  return;

				Endpoint_ClearSetupReceived();
				
				if (wLength > DescriptorSize)
				  wLength = DescriptorSize;
				
				while (wLength && (!(Endpoint_IsSetupOUTReceived())))
				{
					while (!(Endpoint_IsSetupINReady()));
					
					while (wLength && (Endpoint_BytesInEndpoint() < USB_ControlEndpointSize))
					{
						#if defined(USE_RAM_DESCRIPTORS)
						Endpoint_Write_Byte(*((uint8_t*)DescriptorPointer++));
						#elif defined (USE_EEPROM_DESCRIPTORS)
						Endpoint_Write_Byte(eeprom_read_byte(DescriptorPointer++));			
						#else
						Endpoint_Write_Byte(pgm_read_byte(DescriptorPointer++));
						#endif
						
						wLength--;
					}
					
					SendZLP = (Endpoint_BytesInEndpoint() == USB_ControlEndpointSize);
					Endpoint_ClearSetupIN();
				}
				
				if (Endpoint_IsSetupOUTReceived())
				{
					Endpoint_ClearSetupOUT();
					return;
				}
				
				if (SendZLP)
				{
					while (!(Endpoint_IsSetupINReady()));
					Endpoint_ClearSetupIN();
				}

				while (!(Endpoint_IsSetupOUTReceived()));
				Endpoint_ClearSetupOUT();				
			}

			break;
	}
}
	
TASK(USB_Sideshow)
{
	/* Check if the USB System is connected to a Host */
	if (USB_IsConnected)
	{
		/* Select the SideShow data out endpoint */
		Endpoint_SelectEndpoint(SIDESHOW_OUT_EPNUM);
		
		/* Check to see if a new SideShow message has been received */
		if (Endpoint_ReadWriteAllowed())
		{
			/* Process the received SideShow message */
			Sideshow_ProcessCommandPacket();
		}
	}
}
