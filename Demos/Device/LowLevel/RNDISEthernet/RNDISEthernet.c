/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

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
	bool ConfigSuccess = true;

	/* Setup RNDIS Data Endpoints */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_TX_EPADDR, EP_TYPE_BULK, CDC_TXRX_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_RX_EPADDR, EP_TYPE_BULK, CDC_TXRX_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_NOTIFICATION_EPADDR, EP_TYPE_INTERRUPT, CDC_NOTIFICATION_EPSIZE, 1);

	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to
 *  the device from the USB host before passing along unhandled control requests to the library for processing
 *  internally.
 */
void EVENT_USB_Device_ControlRequest(void)
{
	/* Process RNDIS class commands */
	switch (USB_ControlRequest.bRequest)
	{
		case RNDIS_REQ_SendEncapsulatedCommand:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				/* Read in the RNDIS message into the message buffer */
				Endpoint_Read_Control_Stream_LE(RNDISMessageBuffer, USB_ControlRequest.wLength);
				Endpoint_ClearIN();

				/* Process the RNDIS message */
				ProcessRNDISControlMessage();
			}

			break;
		case RNDIS_REQ_GetEncapsulatedResponse:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Check if a response to the last message is ready */
				if (!(MessageHeader->MessageLength))
				{
					/* Set the response to a single 0x00 byte to indicate that no response is ready */
					RNDISMessageBuffer[0] = 0;
					MessageHeader->MessageLength = 1;
				}

				Endpoint_ClearSETUP();

				/* Write the message response data to the endpoint */
				Endpoint_Write_Control_Stream_LE(RNDISMessageBuffer, MessageHeader->MessageLength);
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
	Endpoint_SelectEndpoint(CDC_NOTIFICATION_EPADDR);

	/* Check if a message response is ready for the host */
	if (Endpoint_IsINReady() && ResponseReady)
	{
		USB_Request_Header_t Notification = (USB_Request_Header_t)
			{
				.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
				.bRequest      = RNDIS_NOTIF_ResponseAvailable,
				.wValue        = 0,
				.wIndex        = 0,
				.wLength       = 0,
			};

		/* Indicate that a message response is ready for the host */
		Endpoint_Write_Stream_LE(&Notification, sizeof(Notification), NULL);

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
		Endpoint_SelectEndpoint(CDC_RX_EPADDR);

		/* Check if the data OUT endpoint contains data, and that the IN buffer is empty */
		if (Endpoint_IsOUTReceived() && !(FrameIN.FrameLength))
		{
			/* Read in the packet message header */
			Endpoint_Read_Stream_LE(&RNDISPacketHeader, sizeof(RNDIS_Packet_Message_t), NULL);

			/* Stall the request if the data is too large */
			if (RNDISPacketHeader.DataLength > ETHERNET_FRAME_SIZE_MAX)
			{
				Endpoint_StallTransaction();
				return;
			}

			/* Read in the Ethernet frame into the buffer */
			Endpoint_Read_Stream_LE(FrameIN.FrameData, RNDISPacketHeader.DataLength, NULL);

			/* Finalize the stream transfer to send the last packet */
			Endpoint_ClearOUT();

			/* Store the size of the Ethernet frame */
			FrameIN.FrameLength = RNDISPacketHeader.DataLength;
		}

		/* Select the data IN endpoint */
		Endpoint_SelectEndpoint(CDC_TX_EPADDR);

		/* Check if the data IN endpoint is ready for more data, and that the IN buffer is full */
		if (Endpoint_IsINReady() && FrameOUT.FrameLength)
		{
			/* Clear the packet header with all 0s so that the relevant fields can be filled */
			memset(&RNDISPacketHeader, 0, sizeof(RNDIS_Packet_Message_t));

			/* Construct the required packet header fields in the buffer */
			RNDISPacketHeader.MessageType   = REMOTE_NDIS_PACKET_MSG;
			RNDISPacketHeader.MessageLength = (sizeof(RNDIS_Packet_Message_t) + FrameOUT.FrameLength);
			RNDISPacketHeader.DataOffset    = (sizeof(RNDIS_Packet_Message_t) - sizeof(RNDIS_Message_Header_t));
			RNDISPacketHeader.DataLength    = FrameOUT.FrameLength;

			/* Send the packet header to the host */
			Endpoint_Write_Stream_LE(&RNDISPacketHeader, sizeof(RNDIS_Packet_Message_t), NULL);

			/* Send the Ethernet frame data to the host */
			Endpoint_Write_Stream_LE(FrameOUT.FrameData, RNDISPacketHeader.DataLength, NULL);

			/* Finalize the stream transfer to send the last packet */
			Endpoint_ClearIN();

			/* Indicate Ethernet OUT buffer no longer full */
			FrameOUT.FrameLength = 0;
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
	if (FrameIN.FrameLength)
	{
		/* Indicate packet processing started */
		LEDs_SetAllLEDs(LEDMASK_USB_BUSY);

		/* Process the ethernet frame - replace this with your own Ethernet handler code as desired */
		Ethernet_ProcessPacket();

		/* Indicate packet processing complete */
		LEDs_SetAllLEDs(LEDMASK_USB_READY);
	}
}

