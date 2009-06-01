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

#include "USBtoSerial.h"

RingBuff_t Rx_Buffer;
RingBuff_t Tx_Buffer;

USB_ClassInfo_CDC_t VirtualSerial_CDC_Interface =
	{
		.ControlInterfaceNumber     = 0,

		.DataINEndpointNumber       = CDC_TX_EPNUM,
		.DataINEndpointSize         = CDC_TXRX_EPSIZE,

		.DataOUTEndpointNumber      = CDC_RX_EPNUM,
		.DataOUTEndpointSize        = CDC_TXRX_EPSIZE,

		.NotificationEndpointNumber = CDC_NOTIFICATION_EPNUM,
		.NotificationEndpointSize   = CDC_NOTIFICATION_EPSIZE,
	};

int main(void)
{
	SetupHardware();
	
	Buffer_Initialize(&Rx_Buffer);
	Buffer_Initialize(&Tx_Buffer);

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		for (uint8_t DataBytesRem = USB_CDC_BytesReceived(&VirtualSerial_CDC_Interface); DataBytesRem != 0; DataBytesRem--)
		{
			if (!(BUFF_STATICSIZE - Rx_Buffer.Elements))
			  break;
			  
			Buffer_StoreElement(&Rx_Buffer, USB_CDC_ReceiveByte(&VirtualSerial_CDC_Interface));
		}
		
		if (Tx_Buffer.Elements)
		  USB_CDC_SendByte(&VirtualSerial_CDC_Interface, Buffer_GetElement(&Rx_Buffer));
		  
		if (Rx_Buffer.Elements)
		  Serial_TxByte(Buffer_GetElement(&Rx_Buffer));
		
		USB_CDC_USBTask(&VirtualSerial_CDC_Interface);
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
	Joystick_Init();
	LEDs_Init();
	USB_Init();
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

	if (!(USB_CDC_ConfigureEndpoints(&VirtualSerial_CDC_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

void EVENT_USB_UnhandledControlPacket(void)
{
	USB_CDC_ProcessControlPacket(&VirtualSerial_CDC_Interface);
}

ISR(USART1_RX_vect, ISR_BLOCK)
{
	if (USB_IsConnected)
	  Buffer_StoreElement(&Tx_Buffer, UDR1);
}

void EVENT_USB_CDC_LineEncodingChanged(USB_ClassInfo_CDC_t* CDCInterfaceInfo)
{
	uint8_t ConfigMask = 0;

	if (CDCInterfaceInfo->LineEncoding.ParityType == Parity_Odd)
	  ConfigMask = ((1 << UPM11) | (1 << UPM10));
	else if (CDCInterfaceInfo->LineEncoding.ParityType == Parity_Even)
	  ConfigMask = (1 << UPM11);

	if (CDCInterfaceInfo->LineEncoding.CharFormat == TwoStopBits)
	  ConfigMask |= (1 << USBS1);

	if (CDCInterfaceInfo->LineEncoding.DataBits == 6)
	  ConfigMask |= (1 << UCSZ10);
	else if (CDCInterfaceInfo->LineEncoding.DataBits == 7)
	  ConfigMask |= (1 << UCSZ11);
	else if (CDCInterfaceInfo->LineEncoding.DataBits == 8)
	  ConfigMask |= ((1 << UCSZ11) | (1 << UCSZ10));
	
	UCSR1A = (1 << U2X1);	
	UCSR1B = ((1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1));
	UCSR1C = ConfigMask;	
	UBRR1  = SERIAL_2X_UBBRVAL((uint16_t)CDCInterfaceInfo->LineEncoding.BaudRateBPS);
}
