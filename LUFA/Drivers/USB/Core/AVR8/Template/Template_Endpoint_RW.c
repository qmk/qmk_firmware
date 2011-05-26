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

			if (BytesProcessed != NULL)
			{
				*BytesProcessed += BytesInTransfer;
				return ENDPOINT_RWSTREAM_IncompleteTransfer;
			}

			#if !defined(INTERRUPT_CONTROL_ENDPOINT)
			USB_USBTask();
			#endif

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
