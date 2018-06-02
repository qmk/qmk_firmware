/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#if defined(TEMPLATE_FUNC_NAME)

uint8_t TEMPLATE_FUNC_NAME (TEMPLATE_BUFFER_TYPE const Buffer,
                            uint16_t Length,
                            uint16_t* const BytesProcessed)
{
	uint8_t* DataStream      = ((uint8_t*)Buffer + TEMPLATE_BUFFER_OFFSET(Length));
	uint16_t BytesInTransfer = 0;
	uint8_t  ErrorCode;

	if ((ErrorCode = Endpoint_WaitUntilReady()))
	  return ErrorCode;

	if (BytesProcessed != NULL)
	{
		Length -= *BytesProcessed;
		TEMPLATE_BUFFER_MOVE(DataStream, *BytesProcessed);
	}

	while (Length)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			TEMPLATE_CLEAR_ENDPOINT();

			#if !defined(INTERRUPT_CONTROL_ENDPOINT)
			USB_USBTask();
			#endif

			if (BytesProcessed != NULL)
			{
				*BytesProcessed += BytesInTransfer;
				return ENDPOINT_RWSTREAM_IncompleteTransfer;
			}

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			TEMPLATE_TRANSFER_BYTE(DataStream);
			TEMPLATE_BUFFER_MOVE(DataStream, 1);
			Length--;
			BytesInTransfer++;
		}
	}

	return ENDPOINT_RWSTREAM_NoError;
}

#undef TEMPLATE_FUNC_NAME
#undef TEMPLATE_BUFFER_TYPE
#undef TEMPLATE_TRANSFER_BYTE
#undef TEMPLATE_CLEAR_ENDPOINT
#undef TEMPLATE_BUFFER_OFFSET
#undef TEMPLATE_BUFFER_MOVE

#endif

