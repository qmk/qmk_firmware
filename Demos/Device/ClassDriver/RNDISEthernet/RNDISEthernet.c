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
 *  Main source file for the RNDISEthernet demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "RNDISEthernet.h"

/** LUFA RNDIS Class driver interface configuration and state information. This structure is
 *  passed to all RNDIS Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_RNDIS_Device_t Ethernet_RNDIS_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber     = 0,

				.DataINEndpointNumber       = CDC_TX_EPNUM,
				.DataINEndpointSize         = CDC_TXRX_EPSIZE,

				.DataOUTEndpointNumber      = CDC_RX_EPNUM,
				.DataOUTEndpointSize        = CDC_TXRX_EPSIZE,

				.NotificationEndpointNumber = CDC_NOTIFICATION_EPNUM,
				.NotificationEndpointSize   = CDC_NOTIFICATION_EPSIZE,
				
				.AdapterVendorDescription   = "LUFA RNDIS Demo Adapter",
				.AdapterMACAddress          = {ADAPTER_MAC_ADDRESS},
			},
	};

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	
	TCP_Init();
	Webserver_Init();

	printf_P(PSTR("\r\n\r\n****** RNDIS Demo running. ******\r\n"));

	for (;;)
	{
		if (Ethernet_RNDIS_Interface.State.FrameIN.FrameInBuffer)
		{
			LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
			Ethernet_ProcessPacket(&Ethernet_RNDIS_Interface.State.FrameIN, &Ethernet_RNDIS_Interface.State.FrameOUT);
			LEDs_SetAllLEDs(LEDMASK_USB_READY);
		}

		TCP_TCPTask(&Ethernet_RNDIS_Interface);

		RNDIS_Device_USBTask(&Ethernet_RNDIS_Interface);
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
	LEDs_Init();
	SerialStream_Init(9600, false);
	USB_Init();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	if (!(RNDIS_Device_ConfigureEndpoints(&Ethernet_RNDIS_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Unhandled Control Request event. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	RNDIS_Device_ProcessControlRequest(&Ethernet_RNDIS_Interface);
}
