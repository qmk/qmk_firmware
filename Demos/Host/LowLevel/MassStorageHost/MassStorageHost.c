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

/** Index of the highest available LUN (Logical Unit) in the attached Mass Storage Device */
uint8_t MassStore_MaxLUNIndex;


/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Mass Storage Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		MassStorage_Task();
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
	Buttons_Init();
	USB_Init();
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Host_DeviceAttached(void)
{
	puts_P(PSTR(ESC_FG_GREEN "Device Attached.\r\n" ESC_FG_WHITE));
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_Host_DeviceUnattached(void)
{
	puts_P(PSTR(ESC_FG_GREEN "\r\nDevice Unattached.\r\n" ESC_FG_WHITE));
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

/** Task to set the configuration of the attached device after it has been enumerated, and to read in blocks from
 *  the device and print them to the serial port.
 */
void MassStorage_Task(void)
{
	uint8_t ErrorCode;

	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			puts_P(PSTR("Getting Config Data.\r\n"));
		
			/* Get and process the configuration descriptor data */
			if ((ErrorCode = ProcessConfigurationDescriptor()) != SuccessfulConfigRead)
			{
				if (ErrorCode == ControlError)
				  puts_P(PSTR(ESC_FG_RED "Control Error (Get Configuration).\r\n"));
				else
				  puts_P(PSTR(ESC_FG_RED "Invalid Device.\r\n"));

				printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);
				
				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			/* Set the device configuration to the first configuration (rarely do devices use multiple configurations) */
			if ((ErrorCode = USB_Host_SetDeviceConfiguration(1)) != HOST_SENDCONTROL_Successful)
			{
				printf_P(PSTR(ESC_FG_RED "Control Error (Set Configuration).\r\n"
				                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
				
			puts_P(PSTR("Mass Storage Disk Enumerated.\r\n"));

			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
			/* Indicate device busy via the status LEDs */
			LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
			
			/* Send the request, display error and wait for device detach if request fails */
			if ((ErrorCode = MassStore_GetMaxLUN(&MassStore_MaxLUNIndex)) != HOST_SENDCONTROL_Successful)
			{	
				ShowDiskReadError(PSTR("Get Max LUN"), ErrorCode);

				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			/* Print number of LUNs detected in the attached device */
			printf_P(PSTR("Total LUNs: %d - Using first LUN in device.\r\n"), (MassStore_MaxLUNIndex + 1));
			
			/* Reset the Mass Storage device interface, ready for use */
			if ((ErrorCode = MassStore_MassStorageReset()) != HOST_SENDCONTROL_Successful)
			{
				ShowDiskReadError(PSTR("Mass Storage Reset"), ErrorCode);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			/* Get sense data from the device - many devices will not accept any other commands until the sense data
			 * is read - both on start-up and after a failed command */
			SCSI_Request_Sense_Response_t SenseData;
			if ((ErrorCode = MassStore_RequestSense(0, &SenseData)) != 0)
			{
				ShowDiskReadError(PSTR("Request Sense"), ErrorCode);
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			/* Set the prevent removal flag for the device, allowing it to be accessed */
			if ((ErrorCode = MassStore_PreventAllowMediumRemoval(0, true)) != 0)
			{
				ShowDiskReadError(PSTR("Prevent/Allow Medium Removal"), ErrorCode);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			/* Get inquiry data from the device */
			SCSI_Inquiry_Response_t InquiryData;
			if ((ErrorCode = MassStore_Inquiry(0, &InquiryData)) != 0)
			{
				ShowDiskReadError(PSTR("Inquiry"), ErrorCode);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			/* Print vendor and product names of attached device */
			printf_P(PSTR("Vendor \"%.8s\", Product \"%.16s\"\r\n"), InquiryData.VendorID, InquiryData.ProductID);
						
			/* Wait until disk ready */
			puts_P(PSTR("Waiting until ready.."));

			for (;;)
			{
				Serial_TxByte('.');

				/* Abort if device removed */
				if (USB_HostState == HOST_STATE_Unattached)
				  break;

				/* Check to see if the attached device is ready for new commands */
				ErrorCode = MassStore_TestUnitReady(0);
				  
				/* If attached device is ready, abort the loop */
				if (!(ErrorCode))
				  break;

				/* If an error other than a logical command failure (indicating device busy) returned, abort */
				if (ErrorCode != MASS_STORE_SCSI_COMMAND_FAILED)
				{
					ShowDiskReadError(PSTR("Test Unit Ready"), ErrorCode);

					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}
			}

			puts_P(PSTR("\r\nRetrieving Capacity... "));

			/* Create new structure for the disk's capacity in blocks and block size */
			SCSI_Capacity_t DiskCapacity;

			/* Retrieve disk capacity */
			if ((ErrorCode = MassStore_ReadCapacity(0, &DiskCapacity)) != 0)
			{
				ShowDiskReadError(PSTR("Read Capacity"), ErrorCode);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			/* Display the disk capacity in blocks * block size bytes */
			printf_P(PSTR("%lu blocks of %lu bytes.\r\n"), DiskCapacity.Blocks, DiskCapacity.BlockSize);

			/* Create a new buffer capable of holding a single block from the device */
			uint8_t BlockBuffer[DiskCapacity.BlockSize];

			/* Read in the first 512 byte block from the device */
			if ((ErrorCode = MassStore_ReadDeviceBlock(0, 0x00000000, 1, DiskCapacity.BlockSize, BlockBuffer)) != 0)
			{
				ShowDiskReadError(PSTR("Read Device Block"), ErrorCode);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			puts_P(PSTR("\r\nContents of first block:\r\n"));

			/* Print out the first block in both HEX and ASCII, 16 bytes per line */
			for (uint16_t Chunk = 0; Chunk < (DiskCapacity.BlockSize >> 4); Chunk++)
			{
				/* Pointer to the start of the current 16-byte chunk in the read block of data */
				uint8_t* ChunkPtr = &BlockBuffer[Chunk << 4];
				
				/* Print out the 16 bytes of the chunk in HEX format */
				for (uint8_t ByteOffset = 0; ByteOffset < (1 << 4); ByteOffset++)
				{
					char CurrByte = *(ChunkPtr + ByteOffset);
				
					printf_P(PSTR("%.2X "), CurrByte);
				}
				
				puts_P(PSTR("    "));

				/* Print out the 16 bytes of the chunk in ASCII format */
				for (uint8_t ByteOffset = 0; ByteOffset < (1 << 4); ByteOffset++)
				{
					char CurrByte = *(ChunkPtr + ByteOffset);
				
					putchar(isprint(CurrByte) ? CurrByte : '.');
				}
				
				puts_P(PSTR("\r\n"));
			}
			
			puts_P(PSTR("\r\n\r\nPress board button to read entire ASCII contents of disk...\r\n\r\n"));
			
			/* Wait for the board button to be pressed */
			while (!(Buttons_GetStatus() & BUTTONS_BUTTON1))
			{
				/* Abort if device removed */
				if (USB_HostState == HOST_STATE_Unattached)
				  break;
			}

			/* Abort if device removed */
			if (USB_HostState == HOST_STATE_Unattached)
			  break;
			
			/* Print out the entire disk contents in ASCII format */
			for (uint32_t CurrBlockAddress = 0; CurrBlockAddress < DiskCapacity.Blocks; CurrBlockAddress++)
			{
				/* Read in the next block of data from the device */
				if ((ErrorCode = MassStore_ReadDeviceBlock(0, CurrBlockAddress, 1, DiskCapacity.BlockSize, BlockBuffer)) != 0)
				{
					ShowDiskReadError(PSTR("Read Device Block"), ErrorCode);
					
					USB_HostState = HOST_STATE_WaitForDeviceRemoval;
					break;
				}

				/* Send the ASCII data in the read in block to the serial port */
				for (uint16_t Byte = 0; Byte < DiskCapacity.BlockSize; Byte++)
				{
					char CurrByte = BlockBuffer[Byte];
					
					putchar(isprint(CurrByte) ? CurrByte : '.');
				}

				/* Abort if device removed */
				if (USB_HostState == HOST_STATE_Unattached)
				  break;
			}
			
			/* Indicate device no longer busy */
			LEDs_SetAllLEDs(LEDMASK_USB_READY);
			
			/* Wait until USB device disconnected */
			USB_HostState = HOST_STATE_WaitForDeviceRemoval;
			break;
	}
}

/** Indicates that a communication error has occurred with the attached Mass Storage Device,
 *  printing error codes to the serial port and waiting until the device is removed before
 *  continuing.
 *
 *  \param[in] CommandString  ASCII string located in PROGMEM space indicating what operation failed
 *  \param[in] ErrorCode      Error code of the function which failed to complete successfully
 */
void ShowDiskReadError(char* CommandString, uint8_t ErrorCode)
{
	if (ErrorCode == MASS_STORE_SCSI_COMMAND_FAILED)
	{
		/* Display the error code */
		printf_P(PSTR(ESC_FG_RED "SCSI command error (%S).\r\n"), CommandString);
	}
	else
	{
		/* Display the error code */
		printf_P(PSTR(ESC_FG_RED "Command error (%S).\r\n"), CommandString);
		printf_P(PSTR("  -- Error Code: %d" ESC_FG_WHITE), ErrorCode);	
	}

	Pipe_Freeze();

	/* Indicate device error via the status LEDs */
	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}
