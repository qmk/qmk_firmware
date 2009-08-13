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
 *  Main source file for the MassStorageHost demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */
 
#include "MassStorageHost.h"

/** LUFA Mass Storage Class driver interface configuration and state information. This structure is
 *  passed to all Mass Storage Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_MS_Host_t FlashDisk_MS_Interface =
	{
		.Config =
			{
				.DataINPipeNumber       = 1,
				.DataOUTPipeNumber      = 2,
			},
	};

	
/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Mass Storage Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		switch (USB_HostState)
		{
			case HOST_STATE_Addressed:
				LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
			
				uint16_t ConfigDescriptorSize;
				uint8_t  ConfigDescriptorData[512];

				if ((USB_GetDeviceConfigDescriptor(1, &ConfigDescriptorSize, NULL) != HOST_SENDCONTROL_Successful) ||
				    (ConfigDescriptorSize > sizeof(ConfigDescriptorData)) ||
					(USB_GetDeviceConfigDescriptor(1, &ConfigDescriptorSize, ConfigDescriptorData)))
				{
					printf("Error Retrieving Configuration Descriptor.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}

				if (MS_Host_ConfigurePipes(&FlashDisk_MS_Interface,
				                            ConfigDescriptorSize, ConfigDescriptorData) != MS_ENUMERROR_NoError)
				{
					printf("Attached Device Not a Valid Mouse.\r\n");
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
				
				printf("Mouse Enumerated.\r\n");
				USB_HostState = HOST_STATE_Configured;
				break;
			case HOST_STATE_Configured:
				LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
				
				uint8_t MaxLUNIndex;
				if (MS_Host_GetMaxLUN(&FlashDisk_MS_Interface, &MaxLUNIndex))
				{
					printf("Error retrieving max LUN index.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}
				
				if (MS_Host_ResetMSInterface(&FlashDisk_MS_Interface))
				{
					printf("Error resetting Mass Storage interface.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}
				
				SCSI_Inquiry_Response_t InquiryData;
				if (MS_Host_GetInquiryData(&FlashDisk_MS_Interface, &InquiryData))
				{
					printf("Error retreiving device Inquiry data.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;				
				}

				printf("Vendor \"%.8s\", Product \"%.16s\"\r\n", InquiryData.VendorID, InquiryData.ProductID);
				
				bool DeviceReady;
				printf("Waiting until ready...\r\n"));

				do
				{
					if (MS_Host_TestUnitReady(&FlashDisk_MS_Interface, 0, &DeviceReady))
					{
						printf("Error waiting for device to be ready.\r\n");
						LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
						USB_HostState = HOST_STATE_WaitForDeviceRemoval;
						break;
					}
				}
				while (!(DeviceReady));

				puts_P(PSTR("Retrieving Capacity... "));

				SCSI_Capacity_t DiskCapacity;
				if (MS_Host_ReadDeviceCapacity(0, &DiskCapacity))
				{
					printf("Error retrieving device capacity.\r\n");
					LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}
				
				printf("%lu blocks of %lu bytes.\r\n", DiskCapacity.Blocks, DiskCapacity.BlockSize);

				LEDs_SetAllLEDs(LEDMASK_USB_READY);
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
		}
	
		MS_Host_USBTask(&FlashDisk_MS_Interface);
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
