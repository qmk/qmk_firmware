/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Main source file for the USB device application. This file contains the
 *  main tasks of the application and is responsible for the initial
 *  application hardware configuration.
 */

#include "DeviceApplication.h"

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	GlobalInterruptEnable();

	for (;;)
	{
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

		/* Hardware Initialization */
		USB_Init(USB_MODE_Device, USB_DEVICE_OPT_FULLSPEED | USB_OPT_AUTO_PLL);
	#elif (ARCH == ARCH_XMEGA)
		/* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
		XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
		XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);

		/* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
		XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
		XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);

		PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;

		/* Hardware Initialization */
		USB_Init(USB_OPT_RC32MCLKSRC | USB_OPT_BUSEVENT_PRIHIGH);
	#endif
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{

}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{

}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{

}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{

}
