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
 *  Main source file for the StillImageHost demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "StillImageHost.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Still Image Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		StillImage_Task();
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable Clock Division */
	CLKPR = (1 << CLKPCE);
	CLKPR = 0;

	/* Hardware Initialization */
	SerialStream_Init(9600, false);
	LEDs_Init();
	USB_Init();
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_DeviceAttached(void)
{
	puts_P(PSTR(ESC_FG_GREEN "Device Attached.\r\n" ESC_FG_WHITE));
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_DeviceUnattached(void)
{
	puts_P(PSTR(ESC_FG_GREEN "\r\nDevice Unattached.\r\n" ESC_FG_WHITE));
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
void EVENT_USB_DeviceEnumerationComplete(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_HostError(const uint8_t ErrorCode)
{
	USB_ShutDown();

	puts_P(PSTR(ESC_FG_RED "Host Mode Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n" ESC_FG_WHITE), ErrorCode);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
{
	puts_P(PSTR(ESC_FG_RED "Dev Enum Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);
	printf_P(PSTR(" -- Sub Error Code %d\r\n"), SubErrorCode);
	printf_P(PSTR(" -- In State %d\r\n" ESC_FG_WHITE), USB_HostState);
	
	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Task to set the configuration of the attached device after it has been enumerated, and to print device information
 *  through the serial port.
 */
void StillImage_Task(void)
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
				puts_P(PSTR(ESC_FG_RED "Control Error (Set Configuration).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
				
			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
			puts_P(PSTR("Still Image Device Enumerated.\r\n"));
				
			USB_HostState = HOST_STATE_Ready;
			break;
		case HOST_STATE_Ready:
			/* Indicate device busy via the status LEDs */
			LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
			
			puts_P(PSTR("Retrieving Device Info...\r\n"));
			
			PIMA_SendBlock = (PIMA_Container_t)
				{
					.DataLength    = PIMA_COMMAND_SIZE(0),
					.Type          = CType_CommandBlock,
					.Code          = PIMA_OPERATION_GETDEVICEINFO,
					.TransactionID = 0x00000000,
					.Params        = {},
				};
			
			/* Send the GETDEVICEINFO block */
			SImage_SendBlockHeader();
			
			/* Receive the response data block */
			if ((ErrorCode = SImage_RecieveBlockHeader()) != PIPE_RWSTREAM_NoError)
			{
				ShowCommandError(ErrorCode, false);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			/* Calculate the size of the returned device info data structure */
			uint16_t DeviceInfoSize = (PIMA_ReceivedBlock.DataLength - PIMA_COMMAND_SIZE(0));
			
			/* Create a buffer large enough to hold the entire device info */
			uint8_t DeviceInfo[DeviceInfoSize];

			/* Read in the data block data (containing device info) */
			SImage_ReadData(DeviceInfo, DeviceInfoSize);
			
			/* Once all the data has been read, the pipe must be cleared before the response can be sent */
			Pipe_ClearIN();
			
			/* Create a pointer for walking through the info dataset */
			uint8_t* DeviceInfoPos = DeviceInfo;
			
			/* Skip over the data before the unicode device information strings */
			DeviceInfoPos +=  8;                                          // Skip to VendorExtensionDesc String
			DeviceInfoPos += (1 + UNICODE_STRING_LENGTH(*DeviceInfoPos)); // Skip over VendorExtensionDesc String
			DeviceInfoPos +=  2;                                          // Skip over FunctionalMode
			DeviceInfoPos += (4 + (*(uint32_t*)DeviceInfoPos << 1));      // Skip over OperationCode Array
			DeviceInfoPos += (4 + (*(uint32_t*)DeviceInfoPos << 1));      // Skip over EventCode Array
			DeviceInfoPos += (4 + (*(uint32_t*)DeviceInfoPos << 1));      // Skip over DevicePropCode Array
			DeviceInfoPos += (4 + (*(uint32_t*)DeviceInfoPos << 1));      // Skip over ObjectFormatCode Array
			DeviceInfoPos += (4 + (*(uint32_t*)DeviceInfoPos << 1));      // Skip over ObjectFormatCode Array
			
			/* Extract and convert the Manufacturer Unicode string to ASCII and print it through the USART */
			char Manufacturer[*DeviceInfoPos];
			UnicodeToASCII(DeviceInfoPos, Manufacturer);
			printf_P(PSTR("   Manufacturer: %s\r\n"), Manufacturer);

			DeviceInfoPos += 1 + UNICODE_STRING_LENGTH(*DeviceInfoPos);   // Skip over Manufacturer String

			/* Extract and convert the Model Unicode string to ASCII and print it through the USART */
			char Model[*DeviceInfoPos];
			UnicodeToASCII(DeviceInfoPos, Model);
			printf_P(PSTR("   Model: %s\r\n"), Model);

			DeviceInfoPos += 1 + UNICODE_STRING_LENGTH(*DeviceInfoPos);   // Skip over Model String

			/* Extract and convert the Device Version Unicode string to ASCII and print it through the USART */
			char DeviceVersion[*DeviceInfoPos];
			UnicodeToASCII(DeviceInfoPos, DeviceVersion);
			printf_P(PSTR("   Device Version: %s\r\n"), DeviceVersion);

			/* Receive the final response block from the device */
			if ((ErrorCode = SImage_RecieveBlockHeader()) != PIPE_RWSTREAM_NoError)
			{
				ShowCommandError(ErrorCode, false);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			/* Verify that the command completed successfully */
			if ((PIMA_ReceivedBlock.Type != CType_ResponseBlock) || (PIMA_ReceivedBlock.Code != PIMA_RESPONSE_OK))
			{
				ShowCommandError(PIMA_ReceivedBlock.Code, true);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			puts_P(PSTR("Opening Session...\r\n"));
			
			PIMA_SendBlock = (PIMA_Container_t)
				{
					.DataLength    = PIMA_COMMAND_SIZE(1),
					.Type          = CType_CommandBlock,
					.Code          = PIMA_OPERATION_OPENSESSION,
					.TransactionID = 0x00000000,
					.Params        = {0x00000001},
				};
			
			/* Send the OPENSESSION block, open a session with an ID of 0x0001 */
			SImage_SendBlockHeader();
			
			/* Receive the response block from the device */
			if ((ErrorCode = SImage_RecieveBlockHeader()) != PIPE_RWSTREAM_NoError)
			{
				ShowCommandError(ErrorCode, false);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			/* Verify that the command completed successfully */
			if ((PIMA_ReceivedBlock.Type != CType_ResponseBlock) || (PIMA_ReceivedBlock.Code != PIMA_RESPONSE_OK))
			{
				ShowCommandError(PIMA_ReceivedBlock.Code, true);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			puts_P(PSTR("Closing Session...\r\n"));

			PIMA_SendBlock = (PIMA_Container_t)
				{
					.DataLength    = PIMA_COMMAND_SIZE(1),
					.Type          = CType_CommandBlock,
					.Code          = PIMA_OPERATION_CLOSESESSION,
					.TransactionID = 0x00000001,
					.Params        = {0x00000001},
				};
			
			/* Send the CLOSESESSION block, close the session with an ID of 0x0001 */
			SImage_SendBlockHeader();
			
			/* Receive the response block from the device */
			if ((ErrorCode = SImage_RecieveBlockHeader()) != PIPE_RWSTREAM_NoError)
			{
				ShowCommandError(ErrorCode, false);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			/* Verify that the command completed successfully */
			if ((PIMA_ReceivedBlock.Type != CType_ResponseBlock) || (PIMA_ReceivedBlock.Code != PIMA_RESPONSE_OK))
			{
				ShowCommandError(PIMA_ReceivedBlock.Code, true);
				
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			puts_P(PSTR("Done.\r\n"));

			/* Indicate device no longer busy */
			LEDs_SetAllLEDs(LEDMASK_USB_READY);
			
			/* Wait until USB device disconnected */
			while (USB_IsConnected);
			
			break;
	}
}

/** Function to convert a given Unicode encoded string to ASCII. This function will only work correctly on Unicode
 *  strings which contain ASCII printable characters only.
 *
 *  \param[in] UnicodeString  Pointer to a Unicode encoded input string
 *  \param[out] Buffer        Pointer to a buffer where the converted ASCII string should be stored
 */
void UnicodeToASCII(uint8_t* UnicodeString, char* Buffer)
{
	/* Get the number of characters in the string, skip to the start of the string data */
	uint8_t CharactersRemaining = *(UnicodeString++);
	
	/* Loop through the entire unicode string */
	while (CharactersRemaining--)
	{
		/* Load in the next unicode character (only the lower byte, only Unicode coded ASCII supported) */
		*(Buffer++) = *UnicodeString;
		
		/* Jump to the next unicode character */
		UnicodeString += 2;
	}
	
	/* Null terminate the string */
	*Buffer = 0;
}

/** Displays a PIMA command error via the device's serial port.
 *
 *  \param[in] ErrorCode          Error code of the function which failed to complete successfully
 *  \param[in] ResponseCodeError  Indicates if the error is due to a command failed indication from the device, or a communication failure
 */
void ShowCommandError(uint8_t ErrorCode, bool ResponseCodeError)
{
	char* FailureType = ((ResponseCodeError) ? PSTR("Response Code != OK") : PSTR("Transaction Fail"));

	printf_P(PSTR(ESC_FG_RED "Command Error (%S).\r\n"), FailureType);
	printf_P(PSTR(" -- Error Code %d\r\n" ESC_FG_WHITE), ErrorCode);
			
	/* Indicate error via status LEDs */
	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}
