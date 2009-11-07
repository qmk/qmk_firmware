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
 *  Main source file for the KeyboardHostWithParser demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */
 
#include "KeyboardHostWithParser.h"

/** Processed HID report descriptor items structure, containing information on each HID report element */
HID_ReportInfo_t HIDReportInfo;

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Host_t Keyboard_HID_Interface =
	{
		.Config =
			{
				.DataINPipeNumber       = 1,
				.DataINPipeDoubleBank   = false,

				.DataOUTPipeNumber      = 2,
				.DataOUTPipeDoubleBank  = false,
				
				.HIDInterfaceProtocol   = HID_NON_BOOT_PROTOCOL,
				
				.HIDParserData          = &HIDReportInfo
			},
	};

	
/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Keyboard Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		switch (USB_HostState)
		{
			case HOST_STATE_Addressed:
				LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
			
				uint16_t ConfigDescriptorSize;
				uint8_t  ConfigDescriptorData[512];

				if (USB_GetDeviceConfigDescriptor(1, &ConfigDescriptorSize, ConfigDescriptorData,
				                                  sizeof(ConfigDescriptorData)) != HOST_GETCONFIG_Successful)
				{
					printf("Error Retrieving Configuration Descriptor.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}

				if (HID_Host_ConfigurePipes(&Keyboard_HID_Interface,
				                            ConfigDescriptorSize, ConfigDescriptorData) != HID_ENUMERROR_NoError)
				{
					printf("Attached Device Not a Valid Keyboard.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}
				
				if (USB_Host_SetDeviceConfiguration(1) != HOST_SENDCONTROL_Successful)
				{
					printf("Error Setting Device Configuration.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}

				if (HID_Host_SetReportProtocol(&Keyboard_HID_Interface) != 0)
				{
					printf("Error Setting Report Protocol Mode or Not a Valid Keyboard.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}
				
				LEDs_SetAllLEDs(LEDS_NO_LEDS);

				printf("Keyboard Enumerated.\r\n");
				USB_HostState = HOST_STATE_Configured;
				break;
			case HOST_STATE_Configured:
				if (HID_Host_IsReportReceived(&Keyboard_HID_Interface))
				{
					uint8_t KeyboardReport[Keyboard_HID_Interface.State.LargestReportSize];
					HID_Host_ReceiveReport(&Keyboard_HID_Interface, &KeyboardReport);
					
					for (uint8_t ReportNumber = 0; ReportNumber < HIDReportInfo.TotalReportItems; ReportNumber++)
					{
						HID_ReportItem_t* ReportItem = &HIDReportInfo.ReportItems[ReportNumber];

						/* Check if the current report item is a keyboard scancode */
						if ((ReportItem->Attributes.Usage.Page      == USAGE_PAGE_KEYBOARD) &&
							(ReportItem->Attributes.BitSize         == 8)                   &&
							(ReportItem->Attributes.Logical.Maximum > 1)                    &&
							(ReportItem->ItemType                   == REPORT_ITEM_TYPE_In))
						{
							/* Retrieve the keyboard scancode from the report data retrieved from the device if it is
							 * contained within the current report, if not, skip to the next item in the parser list
							 */
							if (!(USB_GetHIDReportItemInfo(KeyboardReport, ReportItem)))
							  continue;

							/* Key code is an unsigned char in length, cast to the appropriate type */
							uint8_t KeyCode = (uint8_t)ReportItem->Value;

							/* If scancode is non-zero, a key is being pressed */
							if (KeyCode)
							{
								/* Toggle status LED to indicate keypress */
								LEDs_ToggleLEDs(LEDS_LED2);

								char PressedKey = 0;

								/* Convert scancode to printable character if alphanumeric */
								if ((KeyCode >= 0x04) && (KeyCode <= 0x1D))
								  PressedKey = (KeyCode - 0x04) + 'A';
								else if ((KeyCode >= 0x1E) && (KeyCode <= 0x27))
								  PressedKey = (KeyCode - 0x1E) + '0';
								else if (KeyCode == 0x2C)
								  PressedKey = ' ';						
								else if (KeyCode == 0x28)
								  PressedKey = '\n';
									 
								/* Print the pressed key character out through the serial port if valid */
								if (PressedKey)
								  putchar(PressedKey);
							}
							
							/* Once a scancode is found, stop scanning through the report items */
							break;
						}
					}
				}
				
				break;
		}
	
		HID_Host_USBTask(&Keyboard_HID_Interface);
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
	SerialStream_Init(9600, false);
	LEDs_Init();
	USB_Init();
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Host_DeviceAttached(void)
{
	puts_P(PSTR("Device Attached.\r\n"));
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_Host_DeviceUnattached(void)
{
	puts_P(PSTR("\r\nDevice Unattached.\r\n"));
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
void EVENT_USB_Host_DeviceEnumerationComplete(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_Host_HostError(const uint8_t ErrorCode)
{
	USB_ShutDown();

	printf_P(PSTR(ESC_FG_RED "Host Mode Error\r\n"
	                         " -- Error Code %d\r\n" ESC_FG_WHITE), ErrorCode);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
{
	printf_P(PSTR(ESC_FG_RED "Dev Enum Error\r\n"
	                         " -- Error Code %d\r\n"
	                         " -- Sub Error Code %d\r\n"
	                         " -- In State %d\r\n" ESC_FG_WHITE), ErrorCode, SubErrorCode, USB_HostState);
	
	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Callback for the HID Report Parser. This function is called each time the HID report parser is about to store
 *  an IN, OUT or FEATURE item into the HIDReportInfo structure. To save on RAM, we are able to filter out items
 *  we aren't interested in (preventing us from being able to extract them later on, but saving on the RAM they would
 *  have occupied).
 *
 *  \param[in] CurrentItem  Pointer to the item the HID report parser is currently working with
 *
 *  \return Boolean true if the item should be stored into the HID report structure, false if it should be discarded
 */
bool CALLBACK_HIDParser_FilterHIDReportItem(HID_ReportItem_t* CurrentItem)
{
	/* Check the attributes of the current item - see if we are interested in it or not;
	 * only store KEYBOARD usage page items into the Processed HID Report structure to
	 * save RAM and ignore the rest
	 */
	return (CurrentItem->Attributes.Usage.Page == USAGE_PAGE_KEYBOARD);
}
