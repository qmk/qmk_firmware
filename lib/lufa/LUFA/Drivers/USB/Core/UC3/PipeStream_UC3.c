/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#include "../../../../Common/Common.h"
#if (ARCH == ARCH_UC3)

#define  __INCLUDE_FROM_USB_DRIVER
#include "../USBMode.h"

#if defined(USB_CAN_BE_HOST)

#include "PipeStream_UC3.h"

uint8_t Pipe_Discard_Stream(uint16_t Length,
                            uint16_t* const BytesProcessed)
{
	uint8_t  ErrorCode;
	uint16_t BytesInTransfer = 0;

	Pipe_SetPipeToken(PIPE_TOKEN_IN);

	if ((ErrorCode = Pipe_WaitUntilReady()))
	  return ErrorCode;

	if (BytesProcessed != NULL)
	  Length -= *BytesProcessed;

	while (Length)
	{
		if (!(Pipe_IsReadWriteAllowed()))
		{
			Pipe_ClearIN();

			if (BytesProcessed != NULL)
			{
				*BytesProcessed += BytesInTransfer;
				return PIPE_RWSTREAM_IncompleteTransfer;
			}

			if ((ErrorCode = Pipe_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			Pipe_Discard_8();

			Length--;
			BytesInTransfer++;
		}
	}

	return PIPE_RWSTREAM_NoError;
}

uint8_t Pipe_Null_Stream(uint16_t Length,
                         uint16_t* const BytesProcessed)
{
	uint8_t  ErrorCode;
	uint16_t BytesInTransfer = 0;

	Pipe_SetPipeToken(PIPE_TOKEN_OUT);

	if ((ErrorCode = Pipe_WaitUntilReady()))
	  return ErrorCode;

	if (BytesProcessed != NULL)
	  Length -= *BytesProcessed;

	while (Length)
	{
		if (!(Pipe_IsReadWriteAllowed()))
		{
			Pipe_ClearOUT();

			if (BytesProcessed != NULL)
			{
				*BytesProcessed += BytesInTransfer;
				return PIPE_RWSTREAM_IncompleteTransfer;
			}

			USB_USBTask();

			if ((ErrorCode = Pipe_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			Pipe_Write_8(0);

			Length--;
			BytesInTransfer++;
		}
	}

	return PIPE_RWSTREAM_NoError;
}

/* The following abuses the C preprocessor in order to copy-paste common code with slight alterations,
 * so that the code needs to be written once. It is a crude form of templating to reduce code maintenance. */

#define  TEMPLATE_FUNC_NAME                        Pipe_Write_Stream_LE
#define  TEMPLATE_BUFFER_TYPE                      const void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_OUT
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearOUT()
#define  TEMPLATE_BUFFER_OFFSET(Length)            0
#define  TEMPLATE_BUFFER_MOVE(BufferPtr, Amount)   DataStream += Amount
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         Pipe_Write_8(*BufferPtr)
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Write_Stream_BE
#define  TEMPLATE_BUFFER_TYPE                      const void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_OUT
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearOUT()
#define  TEMPLATE_BUFFER_OFFSET(Length)            (Length - 1)
#define  TEMPLATE_BUFFER_MOVE(BufferPtr, Amount)   DataStream -= Amount
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         Pipe_Write_8(*BufferPtr)
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Read_Stream_LE
#define  TEMPLATE_BUFFER_TYPE                      void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_IN
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearIN()
#define  TEMPLATE_BUFFER_OFFSET(Length)            0
#define  TEMPLATE_BUFFER_MOVE(BufferPtr, Amount)   DataStream += Amount
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         *BufferPtr = Pipe_Read_8()
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Read_Stream_BE
#define  TEMPLATE_BUFFER_TYPE                      void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_IN
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearIN()
#define  TEMPLATE_BUFFER_OFFSET(Length)            (Length - 1)
#define  TEMPLATE_BUFFER_MOVE(BufferPtr, Amount)   DataStream -= Amount
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         *BufferPtr = Pipe_Read_8()
#include "Template/Template_Pipe_RW.c"

#endif

#endif
