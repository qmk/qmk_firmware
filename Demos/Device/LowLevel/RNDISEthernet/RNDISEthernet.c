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
 *  Main source file for the RNDISEthernet demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "RNDISEthernet.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	/* Webserver Initialization */
	TCP_Init();
	Webserver_Init();

	printf_P(PSTR("\r\n\r\n****** RNDIS Demo running. ******\r\n"));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	
	for (;;)
	{
		Ethernet_Task();
		TCP_Task();
		RNDIS_Task();
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

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Device_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops all the relevant tasks.
 */
void EVENT_USB_Device_Disconnect(void)
{
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host sets the current configuration
 *  of the USB device after enumeration, and configures the RNDIS device endpoints and starts the relevant tasks.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	/* Indicate USB connected and ready */
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	/* Setup CDC Notification, Rx and Tx Endpoints */
	if (!(Endpoint_ConfigureEndpoint(CDC_TX_EPNUM, EP_TYPE_BULK,
		                             ENDPOINT_DIR_IN, CDC_TXRX_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}							   

	if (!(Endpoint_ConfigureEndpoint(CDC_RX_EPNUM, EP_TYPE_BULK,
		                             ENDPOINT_DIR_OUT, CDC_TXRX_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}

	if (!(Endpoint_ConfigureEndpoint(CDC_NOTIFICATION_EPNUM, EP_TYPE_INTERRUPT,
		                             ENDPOINT_DIR_IN, CDC_NOTIFICATION_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
}

/** Event handler for the USB_UnhandledControlRequest event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the RNDIS control commands,
 *  which set up the USB RNDIS network adapter), so that they can be handled appropriately for the application.
 */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	/* Process RNDIS class commands */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_SendEncapsulatedCommand:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Clear the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();
				
				/* Read in the RNDIS message into the message buffer */
				Endpoint_Read_Control_Stream_LE(RNDISMessageBuffer, USB_ControlRequest.wLength);

				/* Finalize the stream transfer to clear the last packet from the host */
				Endpoint_ClearIN();

				/* Process the RNDIS message */
				ProcessRNDISControlMessage();
			}
			
			break;
		case REQ_GetEncapsulatedResponse:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Clear the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();
				
				/* Check if a response to the last message is ready */
				if (!(MessageHeader->MessageLength))
				{
					/* Set the response to a single 0x00 byte to indicate that no response is ready */
					RNDISMessageBuffer[0] = 0;
					MessageHeader->MessageLength = 1;
				}

				/* Write the message response data to the endpoint */
				Endpoint_Write_Control_Stream_LE(RNDISMessageBuffer, MessageHeader->MessageLength);
				
				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearOUT();

				/* Reset the message header once again after transmission */
				MessageHeader->MessageLength = 0;
			}
	
			break;
	}
}

/** Task to manage the sending and receiving of encapsulated RNDIS data and notifications. This removes the RNDIS
 *  wrapper from received Ethernet frames and places them in the FrameIN global buffer, or adds the RNDIS wrapper
 *  to a frame in the FrameOUT global before sending the buffer contents to the host.
 */
void RNDIS_Task(void)
{
	/* Select the notification endpoint */
	Endpoint_SelectEndpoint(CDC_NOTIFICATION_EPNUM);

	/* Check if a message response is ready for the host */
	if (Endpoint_IsINReady() && ResponseReady)
	{
		USB_Notification_t Notification = (USB_Notification_t)
			{
				.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
				.bNotification = NOTIF_RESPONSE_AVAILABLE,
				.wValue        = 0,
				.wIndex        = 0,
				.wLength       = 0,
			};
		
		/* Indicate that a message response is ready for the host */
		Endpoint_Write_Stream_LE(&Notification, sizeof(Notification));

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();

		/* Indicate a response is no longer ready */
		ResponseReady = false;
	}
	
	/* Don't process the data endpoints until the system is in the data initialized state, and the buffer is free */
	if ((CurrRNDISState == RNDIS_Data_Initialized) && !(MessageHeader->MessageLength))
	{
		/* Create a new packet header for reading/writing */
		RNDIS_Packet_Message_t RNDISPacketHeader;

		/* Select the data OUT endpoint */
		Endpoint_SelectEndpoint(CDC_RX_EPNUM);
		
		/* Check if the data OUT endpoint contains data, and that the IN buffer is empty */
		if (Endpoint_IsOUTReceived() && !(FrameIN.FrameInBuffer))
		{
			/* Read in the packet message header */
			Endpoint_Read_Stream_LE(&RNDISPacketHeader, sizeof(RNDIS_Packet_Message_t));

			/* Stall the request if the data is too large */
			if (RNDISPacketHeader.DataLength > ETHERNET_FRAME_SIZE_MAX)
			{
				Endpoint_StallTransaction();
				return;
			}
			
			/* Read in the Ethernet frame into the buffer */
			Endpoint_Read_Stream_LE(FrameIN.FrameData, RNDISPacketHeader.DataLength);

			/* Finalize the stream transfer to send the last packet */
			Endpoint_ClearOUT();
			
			/* Store the size of the Ethernet frame */
			FrameIN.FrameLength = RNDISPacketHeader.DataLength;

			/* Indicate Ethernet IN buffer full */
			FrameIN.FrameInBuffer = true;
		}
		
		/* Select the data IN endpoint */
		Endpoint_SelectEndpoint(CDC_TX_EPNUM);
		
		/* Check if the data IN endpoint is ready for more data, and that the IN buffer is full */
		if (Endpoint_IsINReady() && FrameOUT.FrameInBuffer)
		{
			/* Clear the packet header with all 0s so that the relevant fields can be filled */
			memset(&RNDISPacketHeader, 0, sizeof(RNDIS_Packet_Message_t));

			/* Construct the required packet header fields in the buffer */
			RNDISPacketHeader.MessageType   = REMOTE_NDIS_PACKET_MSG;
			RNDISPacketHeader.MessageLength = (sizeof(RNDIS_Packet_Message_t) + FrameOUT.FrameLength);
			RNDISPacketHeader.DataOffset    = (sizeof(RNDIS_Packet_Message_t) - sizeof(RNDIS_Message_Header_t));
			RNDISPacketHeader.DataLength    = FrameOUT.FrameLength;

			/* Send the packet header to the host */
			Endpoint_Write_Stream_LE(&RNDISPacketHeader, sizeof(RNDIS_Packet_Message_t));

			/* Send the Ethernet frame data to the host */
			Endpoint_Write_Stream_LE(FrameOUT.FrameData, RNDISPacketHeader.DataLength);
			
			/* Finalize the stream transfer to send the last packet */
			Endpoint_ClearIN();
			
			/* Indicate Ethernet OUT buffer no longer full */
			FrameOUT.FrameInBuffer = false;
		}
	}
}

/** Ethernet frame processing task. This task checks to see if a frame has been received, and if so hands off the processing
 *  of the frame to the Ethernet processing routines.
 */
void Ethernet_Task(void)
{
	/* Task for Ethernet processing. Incoming ethernet frames are loaded into the FrameIN structure, and
	   outgoing frames should be loaded into the FrameOUT structure. Both structures can only hold a single
	   Ethernet frame at a time, so the FrameInBuffer bool is used to indicate when the buffers contain data. */

	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	/* Check if a frame has been written to the IN frame buffer */
	if (FrameIN.FrameInBuffer)
	{
		/* Indicate packet processing started */
		LEDs_SetAllLEDs(LEDMASK_USB_BUSY);

		/* Process the ethernet frame - replace this with your own Ethernet handler code as desired */
		Ethernet_ProcessPacket();

		/* Indicate packet processing complete */
		LEDs_SetAllLEDs(LEDMASK_USB_READY);
	}
}
