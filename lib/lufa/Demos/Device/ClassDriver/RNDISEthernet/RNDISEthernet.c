/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
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

/** Message buffer for RNDIS messages processed by the RNDIS device class driver. */
static uint8_t RNDIS_Message_Buffer[192];

/** Global to store the incoming frame from the host before it is processed by the device. */
static Ethernet_Frame_Info_t FrameIN;

/** Global to store the outgoing frame created in the device before it is sent to the host. */
static Ethernet_Frame_Info_t FrameOUT;

/** LUFA RNDIS Class driver interface configuration and state information. This structure is
 *  passed to all RNDIS Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_RNDIS_Device_t Ethernet_RNDIS_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber         = INTERFACE_ID_CDC_CCI,
				.DataINEndpoint                 =
					{
						.Address                = CDC_TX_EPADDR,
						.Size                   = CDC_TXRX_EPSIZE,
						.Banks                  = 1,
					},
				.DataOUTEndpoint                =
					{
						.Address                = CDC_RX_EPADDR,
						.Size                   = CDC_TXRX_EPSIZE,
						.Banks                  = 1,
					},
				.NotificationEndpoint           =
					{
						.Address                = CDC_NOTIFICATION_EPADDR,
						.Size                   = CDC_NOTIFICATION_EPSIZE,
						.Banks                  = 1,
					},
				.AdapterVendorDescription       = "LUFA RNDIS Demo Adapter",
				.AdapterMACAddress              = {ADAPTER_MAC_ADDRESS},
				.MessageBuffer                  = RNDIS_Message_Buffer,
				.MessageBufferLength            = sizeof(RNDIS_Message_Buffer),
			},
	};


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	TCP_Init();
	Webserver_Init();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		if (RNDIS_Device_IsPacketReceived(&Ethernet_RNDIS_Interface))
		{
			LEDs_SetAllLEDs(LEDMASK_USB_BUSY);

			RNDIS_Device_ReadPacket(&Ethernet_RNDIS_Interface, &FrameIN.FrameData, &FrameIN.FrameLength);
			Ethernet_ProcessPacket(&FrameIN, &FrameOUT);

			if (FrameOUT.FrameLength)
			{
				RNDIS_Device_SendPacket(&Ethernet_RNDIS_Interface, &FrameOUT.FrameData, FrameOUT.FrameLength);
				FrameOUT.FrameLength = 0;
			}

			LEDs_SetAllLEDs(LEDMASK_USB_READY);
		}

		TCP_TCPTask(&Ethernet_RNDIS_Interface, &FrameOUT);

		RNDIS_Device_USBTask(&Ethernet_RNDIS_Interface);
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#elif (ARCH == ARCH_XMEGA)
	/* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
	XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
	XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);

	/* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
	XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
	XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);

	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
#endif

	/* Hardware Initialization */
	LEDs_Init();
	Serial_Init(9600, false);
	USB_Init();

	/* Create a stdio stream for the serial port for stdin and stdout */
	Serial_CreateStream(NULL);
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
	bool ConfigSuccess = true;

	ConfigSuccess &= RNDIS_Device_ConfigureEndpoints(&Ethernet_RNDIS_Interface);

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	RNDIS_Device_ProcessControlRequest(&Ethernet_RNDIS_Interface);
}

