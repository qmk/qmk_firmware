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
 *  Main source file for the XPLAINBridge project. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "XPLAINBridge.h"

/* Current firmware mode, making the device behave as either a programmer or a USART bridge */
bool CurrentFirmwareMode = MODE_PDI_PROGRAMMER;

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config = 
			{
				.ControlInterfaceNumber         = 0,

				.DataINEndpointNumber           = CDC_TX_EPNUM,
				.DataINEndpointSize             = CDC_TXRX_EPSIZE,
				.DataINEndpointDoubleBank       = false,

				.DataOUTEndpointNumber          = CDC_RX_EPNUM,
				.DataOUTEndpointSize            = CDC_TXRX_EPSIZE,
				.DataOUTEndpointDoubleBank      = false,

				.NotificationEndpointNumber     = CDC_NOTIFICATION_EPNUM,
				.NotificationEndpointSize       = CDC_NOTIFICATION_EPSIZE,
				.NotificationEndpointDoubleBank = false,
			},
	};
	
/** Circular buffer to hold data from the host before it is sent to the device via the serial port. */
RingBuff_t USBtoUART_Buffer;

/** Circular buffer to hold data from the serial port before it is sent to the host. */
RingBuff_t UARTtoUSB_Buffer;


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();
	
	Buffer_Initialize(&USBtoUART_Buffer);
	Buffer_Initialize(&UARTtoUSB_Buffer);

	for (;;)
	{
		if (USB_DeviceState == DEVICE_STATE_Configured)
		{
			if (CurrentFirmwareMode == MODE_USART_BRIDGE)
			  USARTBridge_Task();
			else
			  AVRISP_Task();
		}
		
		USB_USBTask();
	}
}

void AVRISP_Task(void)
{
	Endpoint_SelectEndpoint(AVRISP_DATA_EPNUM);
	
	/* Check to see if a V2 Protocol command has been received */
	if (Endpoint_IsOUTReceived())
	{
		LEDs_SetAllLEDs(LEDMASK_BUSY);

		/* Pass off processing of the V2 Protocol command to the V2 Protocol handler */
		V2Protocol_ProcessCommand();

		LEDs_SetAllLEDs(LEDMASK_USB_READY);
	}
}

void USARTBridge_Task(void)
{
	/* Read bytes from the USB OUT endpoint into the UART transmit buffer */
	for (uint8_t DataBytesRem = CDC_Device_BytesReceived(&VirtualSerial_CDC_Interface); DataBytesRem != 0; DataBytesRem--)
	{
		if (!(BUFF_STATICSIZE - USBtoUART_Buffer.Elements))
		  break;
		  
		Buffer_StoreElement(&USBtoUART_Buffer, CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface));
	}
	
	/* Read bytes from the UART receive buffer into the USB IN endpoint */
	if (UARTtoUSB_Buffer.Elements)
	  CDC_Device_SendByte(&VirtualSerial_CDC_Interface, Buffer_GetElement(&UARTtoUSB_Buffer));
	
	/* Load bytes from the UART transmit buffer into the UART */
	if ((USBtoUART_Buffer.Elements) && SoftUART_IsReady())
	  SoftUART_TxByte(Buffer_GetElement(&USBtoUART_Buffer));
	
	/* Load bytes from the UART into the UART receive buffer */
	if(SoftUART_IsReceived())
		Buffer_StoreElement(&UARTtoUSB_Buffer, SoftUART_RxByte());

	CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
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
	SoftUART_Init();
	LEDs_Init();
	USB_Init();
	V2Protocol_Init();
	
	/* Disable JTAG debugging */
	MCUCR |= (1 << JTD);
	MCUCR |= (1 << JTD);

	/* Enable pullup on the JTAG TDI pin so we can use it to select the mode */
	PORTF |= (1 << 7);
	_delay_ms(10);

	/* Select the firmware mode based on the JTD pin's value */
	CurrentFirmwareMode = (PINF & (1 << 7)) ? MODE_USART_BRIDGE : MODE_PDI_PROGRAMMER;
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool EndpointConfigSuccess;

	if (CurrentFirmwareMode == MODE_USART_BRIDGE)
	{
		EndpointConfigSuccess = CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
	}
	else
	{
		EndpointConfigSuccess = Endpoint_ConfigureEndpoint(AVRISP_DATA_EPNUM, EP_TYPE_BULK,
										                   ENDPOINT_DIR_OUT, AVRISP_DATA_EPSIZE,
										                   ENDPOINT_BANK_SINGLE);
	}

	if (EndpointConfigSuccess)
	  LEDs_SetAllLEDs(LEDMASK_USB_READY);
	else
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Unhandled Control Request event. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	if (CurrentFirmwareMode == MODE_USART_BRIDGE)
	  CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, void** const DescriptorAddress)
{
	if (CurrentFirmwareMode == MODE_USART_BRIDGE)
	  return USART_GetDescriptor(wValue, wIndex, DescriptorAddress);
	else
	  return AVRISP_GetDescriptor(wValue, wIndex, DescriptorAddress);
}
