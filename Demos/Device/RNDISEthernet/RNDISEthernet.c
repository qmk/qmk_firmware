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

#include "RNDISEthernet.h"

USB_ClassInfo_RNDIS_t Ethernet_RNDIS_Interface =
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
	};
	
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	
	printf_P(PSTR("\r\n\r\n****** RNDIS Demo running. ******\r\n"));

	for (;;)
	{
		if (Ethernet_RNDIS_Interface.FrameIN.FrameInBuffer)
		{
			LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
			Ethernet_ProcessPacket(&Ethernet_RNDIS_Interface.FrameIN, &Ethernet_RNDIS_Interface.FrameOUT);
			LEDs_SetAllLEDs(LEDMASK_USB_READY);
		}

		TCP_TCPTask(&Ethernet_RNDIS_Interface);

		USB_RNDIS_USBTask(&Ethernet_RNDIS_Interface);
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
	LEDs_Init();
	SerialStream_Init(9600, false);
	USB_Init();

	/* Initialize TCP and Webserver modules */
	TCP_Init();
	Webserver_Init();
}

void EVENT_USB_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

void EVENT_USB_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

void EVENT_USB_ConfigurationChanged(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	if (!(USB_RNDIS_ConfigureEndpoints(&Ethernet_RNDIS_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

void EVENT_USB_UnhandledControlPacket(void)
{
	USB_RNDIS_ProcessControlPacket(&Ethernet_RNDIS_Interface);
}
