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
 *  Main source file for the Benito project. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "Benito.h"

/** Counter for the number of milliseconds remaining for the target /RESET pulse being generated. */
volatile uint8_t ResetPulseMSRemaining = 0;

/** Counter for the number of milliseconds remaining for the TX activity LED pulse being generated. */
volatile uint8_t TxPulseMSRemaining    = 0;

/** Counter for the number of milliseconds remaining for the RX activity LED pulse being generated. */
volatile uint8_t RxPulseMSRemaining    = 0;

/** Counter for the number of milliseconds remaining for the enumeration LED ping-pong being generated. */
volatile uint8_t PingPongMSRemaining   = 0;

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
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
			},
	};

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	for (;;)
	{
		/* Echo bytes from the host to the target via the hardware USART */
		if (CDC_Device_BytesReceived(&VirtualSerial_CDC_Interface) > 0)
		{
			Serial_TxByte(CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface));

			LEDs_TurnOnLEDs(LEDMASK_TX);
			TxPulseMSRemaining = TX_RX_LED_PULSE_MS;			
		}
		
		/* Echo bytes from the target to the host via the virtual serial port */
		if (Serial_IsCharReceived())
		{
			CDC_Device_SendByte(&VirtualSerial_CDC_Interface, Serial_RxByte());

			LEDs_TurnOnLEDs(LEDMASK_RX);
			RxPulseMSRemaining = TX_RX_LED_PULSE_MS;
		}
		
		/* Check if the millisecond timer has elapsed */
		if (TIFR0 & (1 << OCF0A))
		{
			/* Check if the LEDs should be ping-ponging (during enumeration) */
			if (PingPongMSRemaining && !(--PingPongMSRemaining))
			{
				LEDs_ToggleLEDs(LEDMASK_BUSY);
				PingPongMSRemaining = PING_PONG_LED_PULSE_MS;
			}
		
			/* Check if the reset pulse period has elapsed, if so tristate the target reset line */
			if (ResetPulseMSRemaining && !(--ResetPulseMSRemaining))
			{
				LEDs_TurnOffLEDs(LEDMASK_BUSY);
				AVR_RESET_LINE_DDR &= ~AVR_RESET_LINE_MASK;
			}
			
			/* Turn off TX LED(s) once the TX pulse period has elapsed */
			if (TxPulseMSRemaining && !(--TxPulseMSRemaining))
			  LEDs_TurnOffLEDs(LEDMASK_TX);

			/* Turn off RX LED(s) once the RX pulse period has elapsed */
			if (RxPulseMSRemaining && !(--RxPulseMSRemaining))
			  LEDs_TurnOffLEDs(LEDMASK_RX);

			/* Clear the millisecond timer CTC flag (cleared by writing logic one to the register) */
			TIFR0 |= (1 << OCF0A);		
		}
		
		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
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
	USB_Init();

	/* Millisecond Timer Interrupt */
	OCR0A  = (F_CPU / 64 / 1000);
	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS01) | (1 << CS00));
	
	/* Tristate target /RESET Line */
	AVR_RESET_LINE_PORT &= ~AVR_RESET_LINE_MASK;
	AVR_RESET_LINE_DDR  &= ~AVR_RESET_LINE_MASK;
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	PingPongMSRemaining = PING_PONG_LED_PULSE_MS;
	LEDs_SetAllLEDs(LEDMASK_TX);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	PingPongMSRemaining = 0;
	LEDs_TurnOffLEDs(LEDMASK_BUSY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	PingPongMSRemaining = 0;
	LEDs_TurnOffLEDs(LEDMASK_BUSY);

	if (!(CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface)))
	  LEDs_TurnOnLEDs(LEDMASK_ERROR);
}

/** Event handler for the library USB Unhandled Control Request event. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

/** Event handler for the CDC Class driver Line Encoding Changed event.
 *
 *  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
 */
void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	uint8_t ConfigMask = 0;

	switch (CDCInterfaceInfo->State.LineEncoding.ParityType)
	{
		case CDC_PARITY_Odd:
			ConfigMask = ((1 << UPM11) | (1 << UPM10));		
			break;
		case CDC_PARITY_Even:
			ConfigMask = (1 << UPM11);		
			break;
	}

	if (CDCInterfaceInfo->State.LineEncoding.CharFormat == CDC_LINEENCODING_TwoStopBits)
	  ConfigMask |= (1 << USBS1);

	switch (CDCInterfaceInfo->State.LineEncoding.DataBits)
	{
		case 6:
			ConfigMask |= (1 << UCSZ10);
			break;
		case 7:
			ConfigMask |= (1 << UCSZ11);
			break;
		case 8:
			ConfigMask |= ((1 << UCSZ11) | (1 << UCSZ10));
			break;
	}
	
	UCSR1A = (1 << U2X1);
	UCSR1B = ((1 << TXEN1) | (1 << RXEN1));
	UCSR1C = ConfigMask;	
	UBRR1  = SERIAL_2X_UBBRVAL((uint16_t)CDCInterfaceInfo->State.LineEncoding.BaudRateBPS);
}

/** Event handler for the CDC Class driver Host-to-Device Line Encoding Changed event.
 *
 *  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
 */
void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	/* Check if the DTR line has been asserted - if so, start the target AVR's reset pulse */
	if (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR)
	{
		LEDs_TurnOnLEDs(LEDMASK_BUSY);
	
		AVR_RESET_LINE_DDR |= AVR_RESET_LINE_MASK;
		ResetPulseMSRemaining = AVR_RESET_PULSE_MS;
	}
}
