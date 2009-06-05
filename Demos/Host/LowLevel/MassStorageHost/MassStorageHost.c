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

/* Scheduler Task List */
TASK_LIST
{
	{ .Task = USB_USBTask          , .TaskStatus = TASK_STOP },
	{ .Task = USB_MassStore_Host   , .TaskStatus = TASK_STOP },
};

/* Globals */
/** Index of the highest available LUN (Logical Unit) in the attached Mass Storage Device */
uint8_t MassStore_MaxLUNIndex;


/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
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
	
	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);

	/* Start-up message */
	puts_P(PSTR(ESC_RESET ESC_BG_WHITE ESC_INVERSE_ON ESC_ERASE_DISPLAY
	       "MassStore Host Demo running.\r\n" ESC_INVERSE_OFF));
		   
	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();
	
	/* Scheduling routine never returns, so put this last in the main function */
	Scheduler_Start();
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_DeviceAttached(void)
{
	puts_P(PSTR("Device Attached.\r\n"));
	UpdateStatus(Status_USBEnumerating);
	
	/* Start USB management task to enumerate the device */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_DeviceUnattached(void)
{
	/* Stop USB management and Mass Storage tasks */
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);
	Scheduler_SetTaskMode(USB_MassStore_Host, TASK_STOP);

	puts_P(PSTR("\r\nDevice Unattached.\r\n"));
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
void EVENT_USB_DeviceEnumerationComplete(void)
{
	/* Once device is fully enumerated, start the Mass Storage Host task */
	Scheduler_SetTaskMode(USB_MassStore_Host, TASK_RUN);
	
	/* Indicate device enumeration complete */
	UpdateStatus(Status_USBReady);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_HostError(const uint8_t ErrorCode)
{
	USB_ShutDown();

	puts_P(PSTR(ESC_BG_RED "Host Mode Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);

	UpdateStatus(Status_HardwareError);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
{
	puts_P(PSTR(ESC_BG_RED "Dev Enum Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);
	printf_P(PSTR(" -- Sub Error Code %d\r\n"), SubErrorCode);
	printf_P(PSTR(" -- In State %d\r\n"), USB_HostState);
	
	UpdateStatus(Status_EnumerationError);
}

/** Task to set the configuration of the attached device after it has been enumerated, and to read in blocks from
 *  the device and print them to the serial port.
 */
TASK(USB_MassStore_Host)
{
	uint8_t ErrorCode;

	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			/* Standard request to set the device configuration to configuration 1 */
			USB_ControlRequest = (USB_Request_Header_t)
				{
					.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE),
					.bRequest      = REQ_SetConfiguration,
					.wValue        = 1,
					.wIndex        = 0,
					.wLength       = 0,
				};
				
			/* Select the control pipe for the request transfer */
			Pipe_SelectPipe(PIPE_CONTROLPIPE);

			/* Send the request, display error and wait for device detach if request fails */
			if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
			{
				puts_P(PSTR("Control Error (Set Configuration).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);

				/* Indicate error via status LEDs */
				UpdateStatus(Status_EnumerationError);

				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}
				
			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
			puts_P(PSTR("Getting Config Data.\r\n"));
		
			/* Get and process the configuration descriptor data */
			if ((ErrorCode = ProcessConfigurationDescriptor()) != SuccessfulConfigRead)
			{
				if (ErrorCode == ControlError)
				  puts_P(PSTR("Control Error (Get Configuration).\r\n"));
				else
				  puts_P(PSTR("Invalid Device.\r\n"));

				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);
				
				/* Indicate error via status LEDs */
				UpdateStatus(Status_EnumerationError);

				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}

			puts_P(PSTR("Mass Storage Disk Enumerated.\r\n"));
				
			USB_HostState = HOST_STATE_Ready;
			break;
		case HOST_STATE_Ready:
			/* Indicate device busy via the status LEDs */
			UpdateStatus(Status_Busy);
			
			/* Send the request, display error and wait for device detach if request fails */
			if ((ErrorCode = MassStore_GetMaxLUN(&MassStore_MaxLUNIndex)) != HOST_SENDCONTROL_Successful)
			{	
				ShowDiskReadError(PSTR("Get Max LUN"), false, ErrorCode);
				break;
			}
			
			/* Print number of LUNs detected in the attached device */
			printf_P(PSTR("Total LUNs: %d.\r\n"), (MassStore_MaxLUNIndex + 1));
			
			/* Reset the Mass Storage device interface, ready for use */
			if ((ErrorCode = MassStore_MassStorageReset()) != HOST_SENDCONTROL_Successful)
			{
				ShowDiskReadError(PSTR("Mass Storage Reset"), false, ErrorCode);
				break;
			}
			
			/* Get sense data from the device - many devices will not accept any other commands until the sense data
			 * is read - both on start-up and after a failed command */
			SCSI_Request_Sense_Response_t SenseData;
			if (((ErrorCode = MassStore_RequestSense(0, &SenseData)) != 0) || (SCSICommandStatus.Status != Command_Pass))
			{
				ShowDiskReadError(PSTR("Request Sense"), (SCSICommandStatus.Status != Command_Pass), ErrorCode);
				break;
			}
			
			/* Set the prevent removal flag for the device, allowing it to be accessed */
			if (((ErrorCode = MassStore_PreventAllowMediumRemoval(0, true)) != 0) || (SCSICommandStatus.Status != Command_Pass))
			{
				ShowDiskReadError(PSTR("Prevent/Allow Medium Removal"), (SCSICommandStatus.Status != Command_Pass), ErrorCode);
				break;
			}

			puts_P(PSTR("Waiting until ready.."));
			
			/* Wait until disk ready */
			do
			{
				Serial_TxByte('.');
				
				if ((ErrorCode = MassStore_TestUnitReady(0)) != 0)
				{
					ShowDiskReadError(PSTR("Test Unit Ready"), false, ErrorCode);
					break;				
				}
			}
			while ((SCSICommandStatus.Status != Command_Pass) && USB_IsConnected);
			
			/* Abort if device removed */
			if (!(USB_IsConnected))
			  break;

			puts_P(PSTR("\r\nRetrieving Capacity... "));

			/* Create new structure for the disk's capacity in blocks and block size */
			SCSI_Capacity_t DiskCapacity;

			/* Retrieve disk capacity */
			if (((ErrorCode = MassStore_ReadCapacity(0, &DiskCapacity)) != 0) || (SCSICommandStatus.Status != Command_Pass))
			{
				ShowDiskReadError(PSTR("Read Capacity"), (SCSICommandStatus.Status != Command_Pass), ErrorCode);
				break;
			}
			
			/* Display the disk capacity in blocks * block size bytes */
			printf_P(PSTR("%lu blocks of %lu bytes.\r\n"), DiskCapacity.Blocks, DiskCapacity.BlockSize);

			/* Create a new buffer capabable of holding a single block from the device */
			uint8_t BlockBuffer[DiskCapacity.BlockSize];

			/* Read in the first 512 byte block from the device */
			if (((ErrorCode = MassStore_ReadDeviceBlock(0, 0x00000000, 1, DiskCapacity.BlockSize, BlockBuffer)) != 0) ||
			    (SCSICommandStatus.Status != Command_Pass))
			{
				ShowDiskReadError(PSTR("Read Device Block"), (SCSICommandStatus.Status != Command_Pass), ErrorCode);
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
				if (!(USB_IsConnected))
				  break;
			}
			
			/* Print out the entire disk contents in ASCII format */
			for (uint32_t CurrBlock = 0; CurrBlock < DiskCapacity.Blocks; CurrBlock++)
			{
				/* Read in the next block of data from the device */
				if (((ErrorCode = MassStore_ReadDeviceBlock(0, CurrBlock, 1, DiskCapacity.BlockSize, BlockBuffer)) != 0) ||
				    (SCSICommandStatus.Status != Command_Pass))
				{
					ShowDiskReadError(PSTR("Read Device Block"), (SCSICommandStatus.Status != Command_Pass), ErrorCode);
					break;
				}

				/* Send the ASCII data in the read in block to the serial port */
				for (uint16_t Byte = 0; Byte < DiskCapacity.BlockSize; Byte++)
				{
					char CurrByte = BlockBuffer[Byte];
					
					putchar(isprint(CurrByte) ? CurrByte : '.');
				}

				/* Abort if device removed */
				if (!(USB_IsConnected))
				  break;
			}
			
			/* Indicate device no longer busy */
			UpdateStatus(Status_USBReady);
			
			/* Wait until USB device disconnected */
			while (USB_IsConnected);
			
			break;
	}
}

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the MassStorageHost_StatusCodes_t enum
 */
void UpdateStatus(uint8_t CurrentStatus)
{
	uint8_t LEDMask = LEDS_NO_LEDS;
	
	/* Set the LED mask to the appropriate LED mask based on the given status code */
	switch (CurrentStatus)
	{
		case Status_USBNotReady:
			LEDMask = (LEDS_LED1);
			break;
		case Status_USBEnumerating:
			LEDMask = (LEDS_LED1 | LEDS_LED2);
			break;
		case Status_USBReady:
			LEDMask = (LEDS_LED2);
			break;
		case Status_EnumerationError:
		case Status_HardwareError:
		case Status_SCSICommandError:
			LEDMask = (LEDS_LED1 | LEDS_LED3);
			break;
		case Status_Busy:
			LEDMask = (LEDS_LED1 | LEDS_LED4);
			break;
	}
	
	/* Set the board LEDs to the new LED mask */
	LEDs_SetAllLEDs(LEDMask);
}

/** Indicates that a communication error has occurred with the attached Mass Storage Device,
 *  printing error codes to the serial port and waiting until the device is removed before
 *  continuing.
 *
 *  \param CommandString  ASCII string located in PROGMEM space indicating what operation failed
 *  \param FailedAtSCSILayer  Indicates if the command failed at the (logical) SCSI layer or at the physical USB layer
 *  \param ErrorCode      Error code of the function which failed to complete successfully
 */
void ShowDiskReadError(char* CommandString, bool FailedAtSCSILayer, uint8_t ErrorCode)
{
	if (FailedAtSCSILayer)
	{
		/* Display the error code */
		printf_P(PSTR(ESC_BG_RED "SCSI command error (%S).\r\n"), CommandString);
		printf_P(PSTR("  -- Status Code: %d"), ErrorCode);
	}
	else
	{
		/* Display the error code */
		printf_P(PSTR(ESC_BG_RED "Command error (%S).\r\n"), CommandString);
		printf_P(PSTR("  -- Error Code: %d"), ErrorCode);	
	}

	Pipe_Freeze();

	/* Indicate device error via the status LEDs */
	UpdateStatus(Status_SCSICommandError);

	/* Wait until USB device disconnected */
	while (USB_IsConnected);
}
