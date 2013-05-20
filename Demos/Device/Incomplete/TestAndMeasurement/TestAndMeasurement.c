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

#include "TestAndMeasurement.h"

/** Contains the (usually static) capabilities of the TMC device. This table is requested by the
 *  host upon enumeration to give it information on what features of the Test and Measurement USB
 *  Class the device supports.
 */
TMC_Capabilities_t Capabilities =
	{
		.Status     = TMC_STATUS_SUCCESS,
		.TMCVersion = VERSION_BCD(1.00),

		.Interface  =
			{
				.ListenOnly             = false,
				.TalkOnly               = false,
				.PulseIndicateSupported = false,
			},

		.Device     =
			{
				.SupportsAbortINOnMatch = false,
			},
	};

/** Current TMC control request that is being processed */
static uint8_t RequestInProgress = 0;

/** Stream callback abort flag for bulk IN data */
static bool IsTMCBulkINReset = false;

/** Stream callback abort flag for bulk OUT data */
static bool IsTMCBulkOUTReset = false;

/** Last used tag value for data transfers */
static uint8_t CurrentTransferTag = 0;

/** Length of last data transfer, for reporting to the host in case an in-progress transfer is aborted */
static uint16_t LastTransferLength = 0;

/** Buffer to hold the next message to sent to the TMC host */
static uint8_t NextResponseBuffer[64];

/** Indicates the length of the next response to send */
static uint8_t NextResponseLen;

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		TMC_Task();
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
	USB_Init();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management and CDC management tasks.
 */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the CDC management task started.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	/* Setup TMC In, Out and Notification Endpoints */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(TMC_NOTIFICATION_EPADDR, EP_TYPE_INTERRUPT, TMC_IO_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(TMC_IN_EPADDR,  EP_TYPE_BULK, TMC_IO_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(TMC_OUT_EPADDR, EP_TYPE_BULK, TMC_IO_EPSIZE, 1);

	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to
 *  the device from the USB host before passing along unhandled control requests to the library for processing
 *  internally.
 */
void EVENT_USB_Device_ControlRequest(void)
{
	uint8_t TMCRequestStatus = TMC_STATUS_SUCCESS;

	/* Process TMC specific control requests */
	switch (USB_ControlRequest.bRequest)
	{
		case Req_InitiateAbortBulkOut:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				/* Check that no split transaction is already in progress and the data transfer tag is valid */
				if (RequestInProgress != 0)
				{
					TMCRequestStatus = TMC_STATUS_SPLIT_IN_PROGRESS;
				}
				else if (USB_ControlRequest.wValue != CurrentTransferTag)
				{
					TMCRequestStatus = TMC_STATUS_TRANSFER_NOT_IN_PROGRESS;
				}
				else
				{
					/* Indicate that all in-progress/pending data OUT requests should be aborted */
					IsTMCBulkOUTReset = true;

					/* Save the split request for later checking when a new request is received */
					RequestInProgress = Req_InitiateAbortBulkOut;
				}

				Endpoint_ClearSETUP();

				/* Write the request response byte */
				Endpoint_Write_8(TMCRequestStatus);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}

			break;
		case Req_CheckAbortBulkOutStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				/* Check that an ABORT BULK OUT transaction has been requested and that the request has completed */
				if (RequestInProgress != Req_InitiateAbortBulkOut)
				  TMCRequestStatus = TMC_STATUS_SPLIT_NOT_IN_PROGRESS;
				else if (IsTMCBulkOUTReset)
				  TMCRequestStatus = TMC_STATUS_PENDING;
				else
				  RequestInProgress = 0;

				Endpoint_ClearSETUP();

				/* Write the request response bytes */
				Endpoint_Write_8(TMCRequestStatus);
				Endpoint_Write_16_LE(0);
				Endpoint_Write_32_LE(LastTransferLength);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}

			break;
		case Req_InitiateAbortBulkIn:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				/* Check that no split transaction is already in progress and the data transfer tag is valid */
				if (RequestInProgress != 0)
				{
					TMCRequestStatus = TMC_STATUS_SPLIT_IN_PROGRESS;
				}
				else if (USB_ControlRequest.wValue != CurrentTransferTag)
				{
					TMCRequestStatus = TMC_STATUS_TRANSFER_NOT_IN_PROGRESS;
				}
				else
				{
					/* Indicate that all in-progress/pending data IN requests should be aborted */
					IsTMCBulkINReset = true;

					/* Save the split request for later checking when a new request is received */
					RequestInProgress = Req_InitiateAbortBulkIn;
				}

				Endpoint_ClearSETUP();

				/* Write the request response bytes */
				Endpoint_Write_8(TMCRequestStatus);
				Endpoint_Write_8(CurrentTransferTag);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}

			break;
		case Req_CheckAbortBulkInStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				/* Check that an ABORT BULK IN transaction has been requested and that the request has completed */
				if (RequestInProgress != Req_InitiateAbortBulkIn)
				  TMCRequestStatus = TMC_STATUS_SPLIT_NOT_IN_PROGRESS;
				else if (IsTMCBulkINReset)
				  TMCRequestStatus = TMC_STATUS_PENDING;
				else
				  RequestInProgress = 0;

				Endpoint_ClearSETUP();

				/* Write the request response bytes */
				Endpoint_Write_8(TMCRequestStatus);
				Endpoint_Write_16_LE(0);
				Endpoint_Write_32_LE(LastTransferLength);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}

			break;
		case Req_InitiateClear:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Check that no split transaction is already in progress */
				if (RequestInProgress != 0)
				{
					Endpoint_Write_8(TMC_STATUS_SPLIT_IN_PROGRESS);
				}
				else
				{
					/* Indicate that all in-progress/pending data IN and OUT requests should be aborted */
					IsTMCBulkINReset  = true;
					IsTMCBulkOUTReset = true;

					/* Save the split request for later checking when a new request is received */
					RequestInProgress = Req_InitiateClear;
				}

				Endpoint_ClearSETUP();

				/* Write the request response byte */
				Endpoint_Write_8(TMCRequestStatus);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}

			break;
		case Req_CheckClearStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Check that a CLEAR transaction has been requested and that the request has completed */
				if (RequestInProgress != Req_InitiateClear)
				  TMCRequestStatus = TMC_STATUS_SPLIT_NOT_IN_PROGRESS;
				else if (IsTMCBulkINReset || IsTMCBulkOUTReset)
				  TMCRequestStatus = TMC_STATUS_PENDING;
				else
				  RequestInProgress = 0;

				Endpoint_ClearSETUP();

				/* Write the request response bytes */
				Endpoint_Write_8(TMCRequestStatus);
				Endpoint_Write_8(0);

				Endpoint_ClearIN();
				Endpoint_ClearStatusStage();
			}

			break;
		case Req_GetCapabilities:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				/* Write the device capabilities to the control endpoint */
				Endpoint_Write_Control_Stream_LE(&Capabilities, sizeof(TMC_Capabilities_t));
				Endpoint_ClearOUT();
			}

			break;
	}
}

void ProcessSentMessage(uint8_t* const Data, const uint8_t Length)
{
	if (strncmp((char*)Data, "*IDN?", 5) == 0)
	  strcpy((char*)NextResponseBuffer, "LUFA TMC DEMO");

	NextResponseLen = strlen((char*)NextResponseBuffer);
}

uint8_t GetNextMessage(uint8_t* const Data)
{
	  strcpy((char*)NextResponseBuffer, "LUFA TMC DEMO");

	NextResponseLen = strlen((char*)NextResponseBuffer);
// ---
	uint8_t DataLen = MIN(NextResponseLen, 64);

	strlcpy((char*)Data, (char*)NextResponseBuffer, DataLen);

	return DataLen;
}

/** Function to manage TMC data transmission and reception to and from the host. */
void TMC_Task(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	TMC_MessageHeader_t MessageHeader;
	uint8_t             MessagePayload[128];

	/* Try to read in a TMC message from the interface, process if one is available */
	if (ReadTMCHeader(&MessageHeader))
	{
		/* Indicate busy */
		LEDs_SetAllLEDs(LEDMASK_USB_BUSY);

		switch (MessageHeader.MessageID)
		{
			case TMC_MESSAGEID_DEV_DEP_MSG_OUT:
				LastTransferLength = 0;
				while (Endpoint_Read_Stream_LE(MessagePayload, MIN(MessageHeader.TransferSize, sizeof(MessagePayload)), &LastTransferLength) ==
				       ENDPOINT_RWSTREAM_IncompleteTransfer)
				{
					if (IsTMCBulkOUTReset)
					  break;
				}

				Endpoint_ClearOUT();

				ProcessSentMessage(MessagePayload, LastTransferLength);
				break;
			case TMC_MESSAGEID_DEV_DEP_MSG_IN:
				Endpoint_ClearOUT();

				MessageHeader.TransferSize = GetNextMessage(MessagePayload);
				MessageHeader.MessageIDSpecific.DeviceOUT.LastMessageTransaction = true;
				WriteTMCHeader(&MessageHeader);

				LastTransferLength = 0;
				while (Endpoint_Write_Stream_LE(MessagePayload, MessageHeader.TransferSize, &LastTransferLength) ==
				       ENDPOINT_RWSTREAM_IncompleteTransfer)
				{
					if (IsTMCBulkINReset)
					  break;
				}

				Endpoint_ClearIN();
				break;
			default:
				Endpoint_StallTransaction();
				break;
		}

		LEDs_SetAllLEDs(LEDMASK_USB_READY);
	}

	/* All pending data has been processed - reset the data abort flags */
	IsTMCBulkINReset  = false;
	IsTMCBulkOUTReset = false;
}

/** Attempts to read in the TMC message header from the TMC interface.
 *
 *  \param[out] MessageHeader  Pointer to a location where the read header (if any) should be stored
 *
 *  \return Boolean \c true if a header was read, \c false otherwise
 */
bool ReadTMCHeader(TMC_MessageHeader_t* const MessageHeader)
{
	uint16_t BytesTransferred;
	uint8_t  ErrorCode;

	/* Select the Data Out endpoint */
	Endpoint_SelectEndpoint(TMC_OUT_EPADDR);

	/* Abort if no command has been sent from the host */
	if (!(Endpoint_IsOUTReceived()))
	  return false;

	/* Read in the header of the command from the host */
	BytesTransferred = 0;
	while ((ErrorCode = Endpoint_Read_Stream_LE(MessageHeader, sizeof(TMC_MessageHeader_t), &BytesTransferred)) ==
	       ENDPOINT_RWSTREAM_IncompleteTransfer)
	{
		if (IsTMCBulkOUTReset)
		  break;
	}

	/* Store the new command tag value for later use */
	CurrentTransferTag = MessageHeader->Tag;

	/* Indicate if the command has been aborted or not */
	return (!(IsTMCBulkOUTReset) && (ErrorCode == ENDPOINT_RWSTREAM_NoError));
}

bool WriteTMCHeader(TMC_MessageHeader_t* const MessageHeader)
{
	uint16_t BytesTransferred;
	uint8_t  ErrorCode;

	/* Set the message tag of the command header */
	MessageHeader->Tag        =  CurrentTransferTag;
	MessageHeader->InverseTag = ~CurrentTransferTag;

	/* Select the Data In endpoint */
	Endpoint_SelectEndpoint(TMC_IN_EPADDR);

	/* Send the command header to the host */
	BytesTransferred = 0;
	while ((ErrorCode = Endpoint_Write_Stream_LE(MessageHeader, sizeof(TMC_MessageHeader_t), &BytesTransferred)) ==
	       ENDPOINT_RWSTREAM_IncompleteTransfer)
	{
		if (IsTMCBulkINReset)
		  break;
	}

	/* Indicate if the command has been aborted or not */
	return (!(IsTMCBulkINReset) && (ErrorCode == ENDPOINT_RWSTREAM_NoError));
}

