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
 *  Main source file for the Mass Storage demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#define  INCLUDE_FROM_MASSSTORAGE_C
#include "MassStorage.h"

/* Scheduler Task List */
TASK_LIST
{
	{ .Task = USB_MassStorage      , .TaskStatus = TASK_STOP },
};

/* Global Variables */
/** Structure to hold the latest Command Block Wrapper issued by the host, containing a SCSI command to execute. */
CommandBlockWrapper_t  CommandBlock;

/** Structure to hold the latest Command Status Wrapper to return to the host, containing the status of the last issued command. */
CommandStatusWrapper_t CommandStatus = { .Signature = CSW_SIGNATURE };

/** Flag to asynchronously abort any in-progress data transfers upon the reception of a mass storage reset command. */
volatile bool          IsMassStoreReset = false;

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
	Dataflash_Init(SPI_SPEED_FCPU_DIV_2);

	/* Clear Dataflash sector protections, if enabled */
	DataflashManager_ResetDataflashProtections();
	
	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
	
	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();

	/* Scheduling - routine never returns, so put this last in the main function */
	Scheduler_Start();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs. */
EVENT_HANDLER(USB_Connect)
{
	/* Indicate USB enumerating */
	UpdateStatus(Status_USBEnumerating);
	
	/* Reset the MSReset flag upon connection */
	IsMassStoreReset = false;
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the Mass Storage management task.
 */
EVENT_HANDLER(USB_Disconnect)
{
	/* Stop running mass storage task */
	Scheduler_SetTaskMode(USB_MassStorage, TASK_STOP);

	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the Mass Storage management task started.
 */
EVENT_HANDLER(USB_ConfigurationChanged)
{
	/* Setup Mass Storage In and Out Endpoints */
	Endpoint_ConfigureEndpoint(MASS_STORAGE_IN_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_IN, MASS_STORAGE_IO_EPSIZE,
	                           ENDPOINT_BANK_DOUBLE);

	Endpoint_ConfigureEndpoint(MASS_STORAGE_OUT_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_OUT, MASS_STORAGE_IO_EPSIZE,
	                           ENDPOINT_BANK_DOUBLE);

	/* Indicate USB connected and ready */
	UpdateStatus(Status_USBReady);
	
	/* Start mass storage task */
	Scheduler_SetTaskMode(USB_MassStorage, TASK_RUN);
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the Mass Storage class-specific
 *  requests) so that they can be handled appropriately for the application.
 */
EVENT_HANDLER(USB_UnhandledControlPacket)
{
	/* Process UFI specific control requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_MassStorageReset:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				/* Indicate that the current transfer should be aborted */
				IsMassStoreReset = true;			

				/* Acknowledge status stage */
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}

			break;
		case REQ_GetMaxLUN:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				/* Indicate to the host the number of supported LUNs (virtual disks) on the device */
				Endpoint_Write_Byte(TOTAL_LUNS - 1);
				
				Endpoint_ClearIN();
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsOUTReceived()));
				Endpoint_ClearOUT();
			}
			
			break;
	}
}

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the MassStorage_StatusCodes_t enum
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
		case Status_CommandBlockError:
			LEDMask = (LEDS_LED1);
			break;
		case Status_ProcessingCommandBlock:
			LEDMask = (LEDS_LED1 | LEDS_LED2);
			break;
	}
	
	/* Set the board LEDs to the new LED mask */
	LEDs_SetAllLEDs(LEDMask);
}

/** Task to manage the Mass Storage interface, reading in Command Block Wrappers from the host, processing the SCSI commands they
 *  contain, and returning Command Status Wrappers back to the host to indicate the success or failure of the last issued command.
 */
TASK(USB_MassStorage)
{
	/* Check if the USB System is connected to a Host */
	if (USB_IsConnected)
	{
		/* Select the Data Out Endpoint */
		Endpoint_SelectEndpoint(MASS_STORAGE_OUT_EPNUM);
		
		/* Check to see if a command from the host has been issued */
		if (Endpoint_IsReadWriteAllowed())
		{	
			/* Indicate busy */
			UpdateStatus(Status_ProcessingCommandBlock);

			/* Process sent command block from the host */
			if (ReadInCommandBlock())
			{
				/* Check direction of command, select Data IN endpoint if data is from the device */
				if (CommandBlock.Flags & COMMAND_DIRECTION_DATA_IN)
				  Endpoint_SelectEndpoint(MASS_STORAGE_IN_EPNUM);

				/* Decode the received SCSI command */
				SCSI_DecodeSCSICommand();

				/* Load in the CBW tag into the CSW to link them together */
				CommandStatus.Tag = CommandBlock.Tag;

				/* Load in the data residue counter into the CSW */
				CommandStatus.DataTransferResidue = CommandBlock.DataTransferLength;

				/* Stall the selected data pipe if command failed (if data is still to be transferred) */
				if ((CommandStatus.Status == Command_Fail) && (CommandStatus.DataTransferResidue))
				  Endpoint_StallTransaction();

				/* Return command status block to the host */
				ReturnCommandStatus();
				
				/* Check if a Mass Storage Reset occurred */
				if (IsMassStoreReset)
				{
					/* Reset the data endpoint banks */
					Endpoint_ResetFIFO(MASS_STORAGE_OUT_EPNUM);
					Endpoint_ResetFIFO(MASS_STORAGE_IN_EPNUM);

					/* Clear the abort transfer flag */
					IsMassStoreReset = false;
				}

				/* Indicate ready */
				UpdateStatus(Status_USBReady);
			}
			else
			{
				/* Indicate error reading in the command block from the host */
				UpdateStatus(Status_CommandBlockError);
			}
		}
	}
}

/** Function to read in a command block from the host, via the bulk data OUT endpoint. This function reads in the next command block
 *  if one has been issued, and performs validation to ensure that the block command is valid.
 *
 *  \return Boolean true if a valid command block has been read in from the endpoint, false otherwise
 */
static bool ReadInCommandBlock(void)
{
	/* Select the Data Out endpoint */
	Endpoint_SelectEndpoint(MASS_STORAGE_OUT_EPNUM);

	/* Read in command block header */
	Endpoint_Read_Stream_LE(&CommandBlock, (sizeof(CommandBlock) - sizeof(CommandBlock.SCSICommandData)),
	                        AbortOnMassStoreReset);

	/* Check if the current command is being aborted by the host */
	if (IsMassStoreReset)
	  return false;

	/* Verify the command block - abort if invalid */
	if ((CommandBlock.Signature != CBW_SIGNATURE) ||
	    (CommandBlock.LUN >= TOTAL_LUNS) ||
		(CommandBlock.SCSICommandLength > MAX_SCSI_COMMAND_LENGTH))
	{
		/* Stall both data pipes until reset by host */
		Endpoint_StallTransaction();
		Endpoint_SelectEndpoint(MASS_STORAGE_IN_EPNUM);
		Endpoint_StallTransaction();
		
		return false;
	}

	/* Read in command block command data */
	Endpoint_Read_Stream_LE(&CommandBlock.SCSICommandData,
	                        CommandBlock.SCSICommandLength,
	                        AbortOnMassStoreReset);
	  
	/* Check if the current command is being aborted by the host */
	if (IsMassStoreReset)
	  return false;

	/* Finalize the stream transfer to send the last packet */
	Endpoint_ClearOUT();
	
	return true;
}

/** Returns the filled Command Status Wrapper back to the host via the bulk data IN endpoint, waiting for the host to clear any
 *  stalled data endpoints as needed.
 */
static void ReturnCommandStatus(void)
{
	/* Select the Data Out endpoint */
	Endpoint_SelectEndpoint(MASS_STORAGE_OUT_EPNUM);

	/* While data pipe is stalled, wait until the host issues a control request to clear the stall */
	while (Endpoint_IsStalled())
	{
		/* Check if the current command is being aborted by the host */
		if (IsMassStoreReset)
		  return;
	}

	/* Select the Data In endpoint */
	Endpoint_SelectEndpoint(MASS_STORAGE_IN_EPNUM);

	/* While data pipe is stalled, wait until the host issues a control request to clear the stall */
	while (Endpoint_IsStalled())
	{
		/* Check if the current command is being aborted by the host */
		if (IsMassStoreReset)
		  return;
	}
	
	/* Write the CSW to the endpoint */
	Endpoint_Write_Stream_LE(&CommandStatus, sizeof(CommandStatus),
	                          AbortOnMassStoreReset);
	
	/* Check if the current command is being aborted by the host */
	if (IsMassStoreReset)
	  return;

	/* Finalize the stream transfer to send the last packet */
	Endpoint_ClearIN();
}

/** Stream callback function for the Endpoint stream read and write functions. This callback will abort the current stream transfer
 *  if a Mass Storage Reset request has been issued to the control endpoint.
 */
STREAM_CALLBACK(AbortOnMassStoreReset)
{	
	/* Abort if a Mass Storage reset command was received */
	if (IsMassStoreReset)
	  return STREAMCALLBACK_Abort;
	
	/* Continue with the current stream operation */
	return STREAMCALLBACK_Continue;
}
