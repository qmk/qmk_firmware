/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Main source file for the BluetoothHost demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "BluetoothHost.h"

/** Bluetooth configuration structure. This structure configures the bluetooth stack's user alterable settings. */
Bluetooth_Device_t Bluetooth_DeviceConfiguration =
	{
		Class:   (DEVICE_CLASS_SERVICE_CAPTURING | DEVICE_CLASS_MAJOR_COMPUTER | DEVICE_CLASS_MINOR_COMPUTER_PALM),
		PINCode: "0000",
		Name:    "LUFA Bluetooth Demo"
	};

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Bluetooth Host Demo running.\r\n" ESC_FG_WHITE));
	
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	sei();

	for (;;)
	{
		Bluetooth_Stack_USBTask();
		Bluetooth_Host_Task();
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

/** Task to set the configuration of the attached device after it has been enumerated. */
void Bluetooth_Host_Task(void)
{
	uint8_t ErrorCode;

	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			puts_P(PSTR("Getting Device Data.\r\n"));
		
			/* Get and process the configuration descriptor data */
			if ((ErrorCode = ProcessDeviceDescriptor()) != SuccessfulDeviceRead)
			{
				if (ErrorCode == DevControlError)
				  puts_P(PSTR(ESC_FG_RED "Control Error (Get Device).\r\n"));
				else
				  puts_P(PSTR(ESC_FG_RED "Invalid Device.\r\n"));

				printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);
				
				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDS_LED1);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			puts_P(PSTR("Bluetooth Dongle Detected.\r\n"));

			/* Set the device configuration to the first configuration (rarely do devices use multiple configurations) */
			if ((ErrorCode = USB_Host_SetDeviceConfiguration(1)) != HOST_SENDCONTROL_Successful)
			{
				printf_P(PSTR(ESC_FG_RED "Control Error (Set Configuration).\r\n"
				                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDS_LED1);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
				
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
				LEDs_SetAllLEDs(LEDS_LED1);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			puts_P(PSTR("Bluetooth Dongle Enumerated.\r\n"));
			
			/* Initialize the Bluetooth stack */
			Bluetooth_Stack_Init();

			USB_HostState = HOST_STATE_Configured;
			break;
	}
}

/** Bluetooth stack callback event for when the Bluetooth stack has fully initialized using the attached
 *  Bluetooth dongle.
 */
void Bluetooth_StackInitialized(void)
{
	printf_P(PSTR("Stack initialized with local address %02X:%02X:%02X:%02X:%02X:%02X.\r\n"),
	         Bluetooth_State.LocalBDADDR[5], Bluetooth_State.LocalBDADDR[4], Bluetooth_State.LocalBDADDR[3],
	         Bluetooth_State.LocalBDADDR[2], Bluetooth_State.LocalBDADDR[1], Bluetooth_State.LocalBDADDR[0]);
}

/** Bluetooth stack callback event for a Bluetooth connection request. When this callback fires, the
 *  user application must indicate if the connection is to be allowed or rejected.
 *
 *  \param[in] RemoteAddress  Bluetooth address of the remote device attempting the connection
 *
 *  \return Boolean true to accept the connection, false to reject it
 */
bool Bluetooth_ConnectionRequest(const uint8_t* RemoteAddress)
{
	printf_P(PSTR("Connection Request from Device %02X:%02X:%02X:%02X:%02X:%02X.\r\n"),
	         RemoteAddress[5], RemoteAddress[4], RemoteAddress[3], RemoteAddress[2],
	         RemoteAddress[1], RemoteAddress[0]);

	/* Always accept connections from remote devices */
	return true;
}

/** Bluetooth stack callback event for a completed Bluetooth connection. When this callback is made,
 *  the connection information can be accessed through the global \ref Bluetooth_Connection structure.
 */
void Bluetooth_ConnectionComplete(void)
{
	printf_P(PSTR("Connection Complete to Device %02X:%02X:%02X:%02X:%02X:%02X.\r\n"), 
	         Bluetooth_Connection.RemoteAddress[5], Bluetooth_Connection.RemoteAddress[4],
	         Bluetooth_Connection.RemoteAddress[3], Bluetooth_Connection.RemoteAddress[2],
	         Bluetooth_Connection.RemoteAddress[1], Bluetooth_Connection.RemoteAddress[0]);
}

/** Bluetooth stack callback event for a completed Bluetooth disconnection. When this callback is made,
 *  the connection information in the global \ref Bluetooth_Connection structure is invalidated with the
 *  exception of the RemoteAddress element, which can be used to determine the address of the device that
 *  was disconnected.
 */
void Bluetooth_DisconnectionComplete(void)
{
	printf_P(PSTR("Disconnection Complete to Device %02X:%02X:%02X:%02X:%02X:%02X.\r\n"), 
	         Bluetooth_Connection.RemoteAddress[5], Bluetooth_Connection.RemoteAddress[4],
	         Bluetooth_Connection.RemoteAddress[3], Bluetooth_Connection.RemoteAddress[2],
	         Bluetooth_Connection.RemoteAddress[1], Bluetooth_Connection.RemoteAddress[0]);
}

/** Bluetooth stack callback event for a Bluetooth ACL Channel connection request. When is callback fires,
 *  the user application must indicate if the channel connection should be rejected or not, based on the 
 *  protocol (PSM) value of the requested channel.
 *
 *  \param PSM  Protocol PSM value for the requested channel
 *
 *  \return Boolean true to accept the channel connection request, false to reject it
 */
bool Bluetooth_ChannelConnectionRequest(const uint16_t PSM)
{
	/* Always accept channel connection requests regardless of PSM */
	return true;
}

/** Bluetooth stack callback event for a non-signal ACL packet reception. This callback fires once a connection
 *  to a remote Bluetooth device has been made, and the remote device has sent a non-signalling ACL packet.
 *
 *  \param[in] Data    Pointer to a buffer where the received data is stored
 *  \param[in] DataLen Length of the packet data, in bytes
 *  \param[in] Channel Bluetooth ACL data channel information structure for the packet's destination channel
 */
void Bluetooth_PacketReceived(void* Data, uint16_t DataLen, Bluetooth_Channel_t* const Channel)
{
	switch (Channel->PSM)
	{
		case CHANNEL_PSM_SDP:
			/* Service Discovery Protocol packet */
			ServiceDiscovery_ProcessPacket(Data, Channel);
			break;
		default:
			/* Unknown Protocol packet */
			printf_P(PSTR("Packet Received (Channel 0x%04X, PSM: 0x%02x):\r\n"), Channel->LocalNumber, Channel->PSM);
			for (uint16_t Byte = 0; Byte < DataLen; Byte++)
			  printf_P(PSTR("0x%02X "), ((uint8_t*)Data)[Byte]);
			puts_P(PSTR("\r\n"));
			
			break;
	}
}
