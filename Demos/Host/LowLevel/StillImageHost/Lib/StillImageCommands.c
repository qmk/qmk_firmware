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
 *  Still Image Device commands, to issue PIMA commands to the device for
 *  reading device status, capacity, and other characteristics as well as
 *  reading and writing of stored image data.
 */

#include "StillImageCommands.h"

/* Globals: */
/** PIMA block container for the block to send to the device */
PIMA_Container_t PIMA_SendBlock;

/** PIMA block container for the last received block from the device */
PIMA_Container_t PIMA_ReceivedBlock;

/** PIMA block container for the last event block received from the device */
PIMA_Container_t PIMA_EventBlock;


/** Function to send the PIMA command container to the attached still image device. */
void SImage_SendBlockHeader(void)
{
	/* Unfreeze the data OUT pipe ready for data transmission */
	Pipe_SelectPipe(SIMAGE_DATA_OUT_PIPE);
	Pipe_Unfreeze();

	/* Write the PIMA block to the data OUT pipe */
	Pipe_Write_Stream_LE(&PIMA_SendBlock, PIMA_COMMAND_SIZE(0));
	
	/* If the block type is a command, send its parameters (if any) */
	if (PIMA_SendBlock.Type == CType_CommandBlock)
	{
		/* Determine the size of the parameters in the block via the data length attribute */
		uint8_t ParamBytes = (PIMA_SendBlock.DataLength - PIMA_COMMAND_SIZE(0));

		/* Check if any parameters in the command block */
		if (ParamBytes)
		{
			/* Write the PIMA parameters to the data OUT pipe */
			Pipe_Write_Stream_LE(&PIMA_SendBlock.Params, ParamBytes);
		}
		
		/* Send the PIMA command block to the attached device */
		Pipe_ClearOUT();
	}
					
	/* Freeze pipe after use */
	Pipe_Freeze();
}

/** Function to receive a PIMA event container from the attached still image device. */
void SImage_RecieveEventHeader(void)
{
	/* Unfreeze the events pipe */
	Pipe_SelectPipe(SIMAGE_EVENTS_PIPE);
	Pipe_Unfreeze();
	
	/* Read in the event data into the global structure */
	Pipe_Read_Stream_LE(&PIMA_EventBlock, sizeof(PIMA_EventBlock));
	
	/* Clear the pipe after read complete to prepare for next event */
	Pipe_ClearIN();
	
	/* Freeze the event pipe again after use */
	Pipe_Freeze();
}

/** Function to receive a PIMA response container from the attached still image device. */
uint8_t SImage_RecieveBlockHeader(void)
{
	uint16_t TimeoutMSRem = COMMAND_DATA_TIMEOUT_MS;

	/* Unfreeze the data IN pipe */
	Pipe_SelectPipe(SIMAGE_DATA_IN_PIPE);
	Pipe_Unfreeze();
	
	/* Wait until data received on the IN pipe */
	while (!(Pipe_IsReadWriteAllowed()))
	{
		/* Check to see if a new frame has been issued (1ms elapsed) */
		if (USB_INT_HasOccurred(USB_INT_HSOFI))
		{
			/* Clear the flag and decrement the timeout period counter */
			USB_INT_Clear(USB_INT_HSOFI);
			TimeoutMSRem--;

			/* Check to see if the timeout period for the command has elapsed */
			if (!(TimeoutMSRem))
			{
				/* Return error code */
				return PIPE_RWSTREAM_Timeout;
			}
		}
		
		Pipe_SelectPipe(SIMAGE_DATA_OUT_PIPE);

		/* Check if pipe stalled (command failed by device) */
		if (Pipe_IsStalled())
		{
			/* Clear the stall condition on the OUT pipe */
			SImage_ClearPipeStall(SIMAGE_DATA_OUT_PIPE);

			/* Return error code and break out of the loop */
			return PIPE_RWSTREAM_PipeStalled;
		}

		Pipe_SelectPipe(SIMAGE_DATA_IN_PIPE);

		/* Check if pipe stalled (command failed by device) */
		if (Pipe_IsStalled())
		{
			/* Clear the stall condition on the IN pipe */
			SImage_ClearPipeStall(SIMAGE_DATA_IN_PIPE);

			/* Return error code */
			return PIPE_RWSTREAM_PipeStalled;
		}
		  
		/* Check to see if the device was disconnected, if so exit function */
		if (!(USB_IsConnected))
		{
			/* Return error code */
			return PIPE_RWSTREAM_DeviceDisconnected;
		}
	};
	
	/* Freeze OUT pipe after use */
	Pipe_SelectPipe(SIMAGE_DATA_OUT_PIPE);
	Pipe_Freeze();

	/* Select the IN data pipe for data reception */
	Pipe_SelectPipe(SIMAGE_DATA_IN_PIPE);
	
	/* Load in the response from the attached device */
	Pipe_Read_Stream_LE(&PIMA_ReceivedBlock, PIMA_COMMAND_SIZE(0));
	
	/* Check if the returned block type is a response block */
	if (PIMA_ReceivedBlock.Type == CType_ResponseBlock)
	{
		/* Determine the size of the parameters in the block via the data length attribute */
		uint8_t ParamBytes = (PIMA_ReceivedBlock.DataLength - PIMA_COMMAND_SIZE(0));

		/* Check if the device has returned any parameters */
		if (ParamBytes)
		{
			/* Read the PIMA parameters from the data IN pipe */
			Pipe_Read_Stream_LE(&PIMA_ReceivedBlock.Params, ParamBytes);
		}
		
		/* Clear pipe bank after use */
		Pipe_ClearIN();
	}
	
	/* Freeze the IN pipe after use */
	Pipe_Freeze();
	
	return PIPE_RWSTREAM_NoError;
}

/** Function to send the given data to the device, after a command block has been issued.
 *
 *  \param[in] Buffer  Source data buffer to send to the device
 *  \param[in] Bytes   Number of bytes to send
 */
void SImage_SendData(void* Buffer, uint16_t Bytes)
{
	/* Unfreeze the data OUT pipe */
	Pipe_SelectPipe(SIMAGE_DATA_OUT_PIPE);
	Pipe_Unfreeze();
	
	/* Write the data contents to the pipe */
	Pipe_Write_Stream_LE(Buffer, Bytes);

	/* Send the last packet to the attached device */
	Pipe_ClearOUT();

	/* Freeze the pipe again after use */
	Pipe_Freeze();
}

/** Function to receive the given data to the device, after a response block has been received.
 *
 *  \param[out] Buffer  Destination data buffer to put read bytes from the device
 *  \param[in] Bytes    Number of bytes to receive
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
uint8_t SImage_ReadData(void* Buffer, uint16_t Bytes)
{
	uint8_t ErrorCode;

	/* Unfreeze the data IN pipe */
	Pipe_SelectPipe(SIMAGE_DATA_IN_PIPE);
	Pipe_Unfreeze();

	/* Read in the data into the buffer */
	ErrorCode = Pipe_Read_Stream_LE(Buffer, Bytes);

	/* Freeze the pipe again after use */
	Pipe_Freeze();
	
	return ErrorCode;
}

/** Function to test if a PIMA event block is waiting to be read in from the attached device.
 *
 *  \return True if an event is waiting to be read in from the device, false otherwise
 */
bool SImage_IsEventReceived(void)
{
	bool IsEventReceived = false;

	/* Unfreeze the Event pipe */
	Pipe_SelectPipe(SIMAGE_EVENTS_PIPE);
	Pipe_Unfreeze();
	
	/* If the pipe contains data, an event has been received */
	if (Pipe_BytesInPipe())
	  IsEventReceived = true;
	
	/* Freeze the pipe after use */
	Pipe_Freeze();
	
	return IsEventReceived;
}

/** Clears the stall condition in the attached device on the nominated endpoint number.
 *
 *  \param[in] EndpointNum  Endpoint number in the attached device whose stall condition is to be cleared
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t SImage_ClearPipeStall(const uint8_t EndpointNum)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_ENDPOINT),
			.bRequest      = REQ_ClearFeature,
			.wValue        = FEATURE_ENDPOINT_HALT,
			.wIndex        = EndpointNum,
			.wLength       = 0,
		};
	
	/* Select the control pipe for the request transfer */
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}
