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
	USB Printer host demo application.
	
	** NOT CURRENTLY FUNCTIONAL - DO NOT USE **
*/

#include "PrinterHost.h"


int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	puts_P(PSTR(ESC_RESET ESC_BG_WHITE ESC_INVERSE_ON ESC_ERASE_DISPLAY
	       "Printer Host Demo running.\r\n" ESC_INVERSE_OFF));
	
	for (;;)
	{
		USB_Printer_Host();
		USB_USBTask();
	}
}

void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	SerialStream_Init(9600, false);
	LEDs_Init();
	USB_Init();
}

void EVENT_USB_DeviceAttached(void)
{
	puts_P(PSTR("Device Attached.\r\n"));
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

void EVENT_USB_DeviceUnattached(void)
{
	puts_P(PSTR("\r\nDevice Unattached.\r\n"));
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

void EVENT_USB_HostError(uint8_t ErrorCode)
{
	USB_ShutDown();

	puts_P(PSTR(ESC_BG_RED "Host Mode Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

void EVENT_USB_DeviceEnumerationFailed(uint8_t ErrorCode, uint8_t SubErrorCode)
{
	puts_P(PSTR(ESC_BG_RED "Dev Enum Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);
	printf_P(PSTR(" -- In State %d\r\n"), USB_HostState);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

void EVENT_USB_DeviceEnumerationComplete(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

void USB_Printer_Host(void)
{
	uint8_t ErrorCode;

	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			puts_P(PSTR("Getting Config Data.\r\n"));
			
			/* Select the control pipe for the request transfer */
			Pipe_SelectPipe(PIPE_CONTROLPIPE);			
		
			/* Get and process the configuration descriptor data */
			if ((ErrorCode = ProcessConfigurationDescriptor()) != SuccessfulConfigRead)
			{
				if (ErrorCode == ControlError)
				  puts_P(PSTR("Control Error (Get Configuration).\r\n"));
				else
				  puts_P(PSTR("Invalid Device.\r\n"));

				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);
				
				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
				
			/* Set the device configuration to the first configuration (rarely do devices use multiple configurations) */
			if ((ErrorCode = USB_Host_SetDeviceConfiguration(1)) != HOST_SENDCONTROL_Successful)
			{
				puts_P(PSTR("Control Error (Set Configuration).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			/* Some printers use alternate settings to determine the communication protocol used - if so, send a SetInterface
			 * request to switch to the interface alternate setting with the Bidirection protocol */
			if (PrinterAltSetting)
			{
				USB_ControlRequest = (USB_Request_Header_t)
					{
						bmRequestType: (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_INTERFACE),
						bRequest:      REQ_SetInterface,
						wValue:        PrinterAltSetting,
						wIndex:        PrinterInterfaceNumber,
						wLength:       0,
					};
					
				if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
				{
					puts_P(PSTR("Control Error (Set Interface).\r\n"));
					printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);

					/* Indicate error via status LEDs */
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

					/* Wait until USB device disconnected */
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;					
				}
			}
			
			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
			puts_P(PSTR("Retrieving Device ID...\r\n"));
		
			Device_ID_String_t DeviceIDString;
			if ((ErrorCode = Printer_GetDeviceID(&DeviceIDString)) != HOST_SENDCONTROL_Successful)
			{
				puts_P(PSTR("Control Error (Get DeviceID).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			printf_P(PSTR("Printer Device ID: %s\r\n"), DeviceIDString.String);

			puts_P(PSTR("Printer Enumerated.\r\n"));
					
			USB_HostState = HOST_STATE_Ready;
			break;
		case HOST_STATE_Ready:
			/* Indicate device busy via the status LEDs */
			LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
		
            //--------------------------------------------------------------
			#define TEST_TEXT_PAGE "\033%-12345X\033E LUFA PCL Test Page \033E\033%-12345X"
//			#define TEST_TEXT_PAGE "\033@\033i\001\033X\001\060\000\r\nLUFA ESCP/2 Test Page\r\n"
			#define PAGE_SIZE      (sizeof(TEST_TEXT_PAGE) - 1)

			Pipe_SelectPipe(PRINTER_DATA_OUT_PIPE);
            Pipe_Unfreeze();
			
			puts_P(PSTR("Waiting for Printer to Become Ready...\r\n"));
			
			while (!(Pipe_IsReadWriteAllowed()));

			printf_P(PSTR("Printer Write Allowed, Sending Page (%d bytes)...\r\n"), PAGE_SIZE);
				
			Pipe_Write_Stream_LE(TEST_TEXT_PAGE, PAGE_SIZE);
            Pipe_ClearOUT();

			puts_P(PSTR("Page Sent, Waiting for Pipe...\r\n"));

			while (!(Pipe_IsReadWriteAllowed()));
            Pipe_Freeze();				

			puts_P(PSTR("Pipe Frozen.\r\n"));
            //--------------------------------------------------------------
		
			/* Indicate device no longer busy */
			LEDs_SetAllLEDs(LEDMASK_USB_READY);

			USB_HostState = HOST_STATE_WaitForDeviceRemoval;
			break;
	}
}
