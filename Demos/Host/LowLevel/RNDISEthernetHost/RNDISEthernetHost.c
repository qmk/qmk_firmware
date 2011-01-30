/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** \file
 *
 *  Main source file for the RNDISEthernetHost demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "RNDISEthernetHost.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "RNDIS Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	sei();

	for (;;)
	{
		RNDIS_Host_Task();
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
	Serial_Init(9600, false);
	LEDs_Init();
	USB_Init();

	/* Create a stdio stream for the serial port for stdin and stdout */
	Serial_CreateStream(NULL);
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
	USB_Disable();

	printf_P(PSTR(ESC_FG_RED "Host Mode Error\r\n"
	                         " -- Error Code %d\r\n" ESC_FG_WHITE), ErrorCode);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode,
                                            const uint8_t SubErrorCode)
{
	printf_P(PSTR(ESC_FG_RED "Dev Enum Error\r\n"
	                         " -- Error Code %d\r\n"
	                         " -- Sub Error Code %d\r\n"
	                         " -- In State %d\r\n" ESC_FG_WHITE), ErrorCode, SubErrorCode, USB_HostState);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

void PrintIncomingPackets(void)
{
	uint8_t ErrorCode;

	LEDs_SetAllLEDs(LEDMASK_USB_BUSY);

	uint16_t PacketLength;
	if ((ErrorCode = RNDIS_GetPacketLength(&PacketLength)) != HOST_SENDCONTROL_Successful)
	{
		printf_P(PSTR(ESC_FG_RED "Packet Reception Error.\r\n"
								 " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);
		return;
	}

	if (!(PacketLength))
	  return;

	Pipe_Unfreeze();

	printf_P(PSTR("***PACKET (Size %d)***\r\n"), PacketLength);

	if (PacketLength > 1024)
	{
		puts_P(PSTR(ESC_FG_RED "Packet too large.\r\n" ESC_FG_WHITE));
		Pipe_Discard_Stream(PacketLength, NULL);
	}
	else
	{
		uint8_t PacketBuffer[PacketLength];

		Pipe_Read_Stream_LE(&PacketBuffer, PacketLength, NULL);

		for (uint16_t i = 0; i < PacketLength; i++)
		  printf("0x%02x ", PacketBuffer[i]);
	}

	Pipe_ClearIN();
	Pipe_Freeze();

	printf("\r\n\r\n");

	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Task to set the configuration of the attached device after it has been enumerated, and to read in
 *  data received from the attached RNDIS device and print it to the serial port.
 */
void RNDIS_Host_Task(void)
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

			uint16_t DeviceMaxPacketSize;
			if ((ErrorCode = RNDIS_InitializeDevice(1024, &DeviceMaxPacketSize)) != HOST_SENDCONTROL_Successful)
			{
				printf_P(PSTR(ESC_FG_RED "Error Initializing Device.\r\n"
				                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			printf_P(PSTR("Device Max Transfer Size: %lu bytes.\r\n"), DeviceMaxPacketSize);

			/* We set the default filter to only receive packets we would be interested in */
			uint32_t PacketFilter = (REMOTE_NDIS_PACKET_DIRECTED | REMOTE_NDIS_PACKET_BROADCAST | REMOTE_NDIS_PACKET_ALL_MULTICAST);
			if ((ErrorCode = RNDIS_SetRNDISProperty(OID_GEN_CURRENT_PACKET_FILTER,
			                                        &PacketFilter, sizeof(PacketFilter))) != HOST_SENDCONTROL_Successful)
			{
				printf_P(PSTR(ESC_FG_RED "Error Setting Device Packet Filter.\r\n"
				                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			uint32_t VendorID;
			if ((ErrorCode = RNDIS_QueryRNDISProperty(OID_GEN_VENDOR_ID,
			                                          &VendorID, sizeof(VendorID))) != HOST_SENDCONTROL_Successful)
			{
				printf_P(PSTR(ESC_FG_RED "Error Getting Vendor ID.\r\n"
				                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			printf_P(PSTR("Device Vendor ID: 0x%08lX\r\n"), VendorID);

			puts_P(PSTR("RNDIS Device Enumerated.\r\n"));

			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
			PrintIncomingPackets();

			break;
	}
}

