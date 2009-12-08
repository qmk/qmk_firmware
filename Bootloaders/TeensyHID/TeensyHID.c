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
 *  Main source file for the TeensyHID bootloader. This file contains the complete bootloader logic.
 */
 
#include "TeensyHID.h"

/** Flag to indicate if the bootloader should be running, or should exit and allow the application code to run
 *  via a soft reset. When cleared, the bootloader will abort, the USB interface will shut down and the application
 *  started via a forced watchdog reset.
 */
bool RunBootloader = true;

/** Main program entry point. This routine configures the hardware required by the bootloader, then continuously 
 *  runs the bootloader processing routine until instructed to soft-exit.
 */
int main(void)
{
	/* Setup hardware required for the bootloader */
	SetupHardware();
	
	while (RunBootloader)
	  USB_USBTask();
	
	/* Turn off the USB interface, disconnect from the host */
	USB_ShutDown();

	/* Enable the watchdog and force a timeout to reset the AVR */
	wdt_enable(WDTO_250MS);
					
	for (;;);
}

/** Configures all hardware required for the bootloader. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Relocate the interrupt vector table to the bootloader section */
	MCUCR = (1 << IVCE);
	MCUCR = (1 << IVSEL);

	/* Initialize USB subsystem */
	USB_Init();
}

/** Event handler for the USB_ConfigurationChanged event. This configures the device's endpoints ready
 *  to relay data to and from the attached USB host.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	/* Setup HID Report Endpoint */
	Endpoint_ConfigureEndpoint(HID_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_IN, HID_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);
}

/** Event handler for the USB_UnhandledControlRequest event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the HID commands, which are
 *  all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	/* Handle HID Class specific requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_SetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				/* Wait until the command has been sent by the host */
				while (!(Endpoint_IsOUTReceived()));
			
				/* Read in the write destination address */
				uint16_t PageAddress = Endpoint_Read_Word_LE();
				
				/* Check if the command is a program page command, or a start application command */
				if (PageAddress == TEENSY_STARTAPPLICATION)
				{
					RunBootloader = false;
				}
				else
				{
					/* Erase the given FLASH page, ready to be programmed */
					boot_page_erase(PageAddress);
					boot_spm_busy_wait();
					
					/* Write each of the FLASH page's bytes in sequence */
					for (uint8_t PageByte = 0; PageByte < SPM_PAGESIZE; PageByte += 2)
					{
						/* Check if endpoint is empty - if so clear it and wait until ready for next packet */
						if (!(Endpoint_BytesInEndpoint()))
						{
							Endpoint_ClearOUT();
							while (!(Endpoint_IsOUTReceived()));
						}

						/* Write the next data word to the FLASH page */
						boot_page_fill(PageAddress + PageByte, Endpoint_Read_Word_LE());
					}

					/* Write the filled FLASH page to memory */
					boot_page_write(PageAddress);
					boot_spm_busy_wait();

					/* Re-enable RWW section */
					boot_rww_enable();
				}

				Endpoint_ClearOUT();

				Endpoint_ClearStatusStage();
			}
			
			break;
	}
}
