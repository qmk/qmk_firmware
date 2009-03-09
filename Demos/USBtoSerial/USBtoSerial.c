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

/* Project Tags, for reading out using the ButtLoad project */
BUTTLOADTAG(ProjName,    "LUFA USB RS232 App");
BUTTLOADTAG(BuildTime,   __TIME__);
BUTTLOADTAG(BuildDate,   __DATE__);
BUTTLOADTAG(LUFAVersion, "LUFA V" LUFA_VERSION_STRING);

/* Scheduler Task List */
TASK_LIST
{
	{ Task: USB_USBTask          , TaskStatus: TASK_STOP },
	{ Task: CDC_Task             , TaskStatus: TASK_STOP },
};

/* Globals: */
/** Contains the current baud rate and other settings of the virtual serial port.
 *
 *  These values are set by the host via a class-specific request, and the physical USART should be reconfigured to match the
 *  new settings each time they are changed by the host.
 */
CDC_Line_Coding_t LineCoding = { BaudRateBPS: 9600,
                                 CharFormat:  OneStopBit,
                                 ParityType:  Parity_None,
                                 DataBits:    8            };

/** Ring (circular) buffer to hold the RX data - data from the host to the attached device on the serial port. */
RingBuff_t Rx_Buffer;

/** Ring (circular) buffer to hold the TX data - data from the attached device on the serial port to the host. */
RingBuff_t Tx_Buffer;

/** Flag to indicate if the USART is currently transmitting data from the Rx_Buffer circular buffer. */
volatile bool Transmitting = false;

/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	LEDs_Init();
	ReconfigureUSART();
	
	/* Ringbuffer Initialization */
	Buffer_Initialize(&Rx_Buffer);
	Buffer_Initialize(&Tx_Buffer);
	
	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
	
	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();

	/* Scheduling - routine never returns, so put this last in the main function */
	Scheduler_Start();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
EVENT_HANDLER(USB_Connect)
{
	/* Start USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);

	/* Indicate USB enumerating */
	UpdateStatus(Status_USBEnumerating);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management and CDC management tasks.
 */
EVENT_HANDLER(USB_Disconnect)
{
	/* Stop running CDC and USB management tasks */
	Scheduler_SetTaskMode(CDC_Task, TASK_STOP);
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);
	
	/* Reset Tx and Rx buffers, device disconnected */
	Buffer_Initialize(&Rx_Buffer);
	Buffer_Initialize(&Tx_Buffer);

	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the CDC management task started.
 */
EVENT_HANDLER(USB_ConfigurationChanged)
{
	/* Setup CDC Notification, Rx and Tx Endpoints */
	Endpoint_ConfigureEndpoint(CDC_NOTIFICATION_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_IN, CDC_NOTIFICATION_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(CDC_TX_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_IN, CDC_TXRX_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(CDC_RX_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_OUT, CDC_TXRX_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	/* Indicate USB connected and ready */
	UpdateStatus(Status_USBReady);

	/* Start CDC task */
	Scheduler_SetTaskMode(CDC_Task, TASK_RUN);
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the CDC control commands,
 *  which are all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
EVENT_HANDLER(USB_UnhandledControlPacket)
{
	uint8_t* LineCodingData = (uint8_t*)&LineCoding;

	/* Process CDC specific control requests */
	switch (bRequest)
	{
		case REQ_GetLineEncoding:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{	
				/* Acknowedge the SETUP packet, ready for data transfer */
				Endpoint_ClearSetupReceived();

				/* Write the line coding data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(LineCodingData, sizeof(LineCoding));
				
				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearSetupOUT();
			}
			
			break;
		case REQ_SetLineEncoding:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Acknowedge the SETUP packet, ready for data transfer */
				Endpoint_ClearSetupReceived();

				/* Read the line coding data in from the host into the global struct */
				Endpoint_Read_Control_Stream_LE(LineCodingData, sizeof(LineCoding));

				/* Finalize the stream transfer to clear the last packet from the host */
				Endpoint_ClearSetupIN();
				
				/* Reconfigure the USART with the new settings */
				ReconfigureUSART();
			}
	
			break;
		case REQ_SetControlLineState:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
#if 0
				/* NOTE: Here you can read in the line state mask from the host, to get the current state of the output handshake
				         lines. The mask is read in from the wValue parameter, and can be masked against the CONTROL_LINE_OUT_* masks
				         to determine the RTS and DTR line states using the following code:
				*/

				uint16_t wIndex = Endpoint_Read_Word_LE();
					
				// Do something with the given line states in wIndex
#endif
				
				/* Acknowedge the SETUP packet, ready for data transfer */
				Endpoint_ClearSetupReceived();
				
				/* Send an empty packet to acknowedge the command */
				Endpoint_ClearSetupIN();
			}
	
			break;
	}
}

/** Task to manage CDC data transmission and reception to and from the host, from and to the physical USART. */
TASK(CDC_Task)
{
	if (USB_IsConnected)
	{
#if 0
		/* NOTE: Here you can use the notification endpoint to send back line state changes to the host, for the special RS-232
				 handshake signal lines (and some error states), via the CONTROL_LINE_IN_* masks and the following code:
		*/

		USB_Notification_Header_t Notification = (USB_Notification_Header_t)
			{
				NotificationType: (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
				Notification:     NOTIF_SerialState,
				wValue:           0,
				wIndex:           0,
				wLength:          sizeof(uint16_t),
			};
			
		uint16_t LineStateMask;
		
		// Set LineStateMask here to a mask of CONTROL_LINE_IN_* masks to set the input handshake line states to send to the host
		
		Endpoint_SelectEndpoint(CDC_NOTIFICATION_EPNUM);
		Endpoint_Write_Stream_LE(&Notification, sizeof(Notification));
		Endpoint_Write_Stream_LE(&LineStateMask, sizeof(LineStateMask));
		Endpoint_ClearCurrentBank();
#endif

		/* Select the Serial Rx Endpoint */
		Endpoint_SelectEndpoint(CDC_RX_EPNUM);
		
		if (Endpoint_ReadWriteAllowed())
		{
			/* Read the received data endpoint into the transmission buffer */
			while (Endpoint_BytesInEndpoint())
			{
				/* Wait until the buffer has space for a new character */
				while (!((BUFF_STATICSIZE - Rx_Buffer.Elements)));
			
				/* Store each character from the endpoint */
				Buffer_StoreElement(&Rx_Buffer, Endpoint_Read_Byte());
			}
			
			/* Clear the endpoint buffer */
			Endpoint_ClearCurrentBank();
		}
		
		/* Check if Rx buffer contains data */
		if (Rx_Buffer.Elements)
		{
			/* Initiate the transmission of the buffer contents if USART idle */
			if (!(Transmitting))
			{
				Transmitting = true;
				Serial_TxByte(Buffer_GetElement(&Rx_Buffer));
			}
		}

		/* Select the Serial Tx Endpoint */
		Endpoint_SelectEndpoint(CDC_TX_EPNUM);

		/* Check if the Tx buffer contains anything to be sent to the host */
		if (Tx_Buffer.Elements)
		{
			/* Wait until Serial Tx Endpoint Ready for Read/Write */
			while (!(Endpoint_ReadWriteAllowed()));
			
			/* Check before sending the data if the endpoint is completely full */
			bool IsFull = (Endpoint_BytesInEndpoint() == CDC_TXRX_EPSIZE);
			
			/* Write the transmission buffer contents to the received data endpoint */
			while (Tx_Buffer.Elements && (Endpoint_BytesInEndpoint() < CDC_TXRX_EPSIZE))
			  Endpoint_Write_Byte(Buffer_GetElement(&Tx_Buffer));
			
			/* Send the data */
			Endpoint_ClearCurrentBank();

			/* If a full endpoint was sent, we need to send an empty packet afterwards to terminate the transfer */
			if (IsFull)
			{
				/* Wait until Serial Tx Endpoint Ready for Read/Write */
				while (!(Endpoint_ReadWriteAllowed()));

				/* Send an empty packet to terminate the transfer */
				Endpoint_ClearCurrentBank();
			}
		}
	}
}

/** ISR to handle the USART transmit complete interrupt, fired each time the USART has sent a character. This reloads the USART
 *  data register with the next byte from the Rx_Buffer circular buffer if a character is available, or stops the transmission if
 *  the buffer is currently empty.
 */
ISR(USART1_TX_vect, ISR_BLOCK)
{
	/* Send next character if available */
	if (Rx_Buffer.Elements)
	  UDR1 = Buffer_GetElement(&Rx_Buffer);
	else
	  Transmitting = false;
}

/** ISR to handle the USART receive complete interrupt, fired each time the USART has received a character. This stores the received
 *  character into the Tx_Buffer circular buffer for later transmission to the host.
 */
ISR(USART1_RX_vect, ISR_BLOCK)
{
	/* Only store received characters if the USB interface is connected */
	if (USB_IsConnected)
	{
		/* Character received, store it into the buffer */
		Buffer_StoreElement(&Tx_Buffer, UDR1);
	}
}

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the USBtoSerial_StatusCodes_t enum
 */
void UpdateStatus(uint8_t CurrentStatus)
{
	uint8_t LEDMask = LEDS_NO_LEDS;
	
	/* Set the LED mask to the appropriate LED mask based on the given status code */
	switch (CurrentStatus)
	{
		case Status_USBNotReady:
			LEDMask = (LEDS_LED1);
			break;
		case Status_USBEnumerating:
			LEDMask = (LEDS_LED1 | LEDS_LED2);
			break;
		case Status_USBReady:
			LEDMask = (LEDS_LED2 | LEDS_LED4);
			break;
	}
	
	/* Set the board LEDs to the new LED mask */
	LEDs_SetAllLEDs(LEDMask);
}

/** Reconfigures the USART to match the current serial port settings issued by the host as closely as possible. */
void ReconfigureUSART(void)
{
	uint8_t ConfigMask = 0;

	/* Determine parity - non odd/even parity mode defaults to no parity */
	if (LineCoding.ParityType == Parity_Odd)
	  ConfigMask = ((1 << UPM11) | (1 << UPM10));
	else if (LineCoding.ParityType == Parity_Even)
	  ConfigMask = (1 << UPM11);

	/* Determine stop bits - 1.5 stop bits is set as 1 stop bit due to hardware limitations */
	if (LineCoding.CharFormat == TwoStopBits)
	  ConfigMask |= (1 << USBS1);

	/* Determine data size - 5, 6, 7, or 8 bits are supported */
	if (LineCoding.DataBits == 6)
	  ConfigMask |= (1 << UCSZ10);
	else if (LineCoding.DataBits == 7)
	  ConfigMask |= (1 << UCSZ11);
	else if (LineCoding.DataBits == 8)
	  ConfigMask |= ((1 << UCSZ11) | (1 << UCSZ10));
	
	/* Enable double speed, gives better error percentages at 8MHz */
	UCSR1A = (1 << U2X1);
	
	/* Enable transmit and receive modules and interrupts */
	UCSR1B = ((1 << TXCIE1) | (1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1));

	/* Set the USART mode to the mask generated by the Line Coding options */
	UCSR1C = ConfigMask;
	
	/* Set the USART baud rate register to the desired baud rate value */
	UBRR1  = SERIAL_2X_UBBRVAL((uint16_t)LineCoding.BaudRateBPS);
}
