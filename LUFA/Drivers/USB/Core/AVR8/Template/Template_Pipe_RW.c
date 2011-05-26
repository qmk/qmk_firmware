uint8_t TEMPLATE_FUNC_NAME (TEMPLATE_BUFFER_TYPE const Buffer,
                            uint16_t Length,
                            uint16_t* const BytesProcessed)
{
	uint8_t* DataStream      = ((uint8_t*)Buffer + TEMPLATE_BUFFER_OFFSET(Length));
	uint16_t BytesInTransfer = 0;
	uint8_t  ErrorCode;

	Pipe_SetPipeToken(TEMPLATE_TOKEN);

	if ((ErrorCode = Pipe_WaitUntilReady()))
	  return ErrorCode;

	if (BytesProcessed != NULL)
	{
		Length -= *BytesProcessed;
		TEMPLATE_BUFFER_MOVE(DataStream, *BytesProcessed);
	}
	
	while (Length)
	{
		if (!(Pipe_IsReadWriteAllowed()))
		{
			TEMPLATE_CLEAR_PIPE();

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
			TEMPLATE_TRANSFER_BYTE(DataStream);
			TEMPLATE_BUFFER_MOVE(DataStream, 1);
			Length--;
			BytesInTransfer++;
		}
	}

	return PIPE_RWSTREAM_NoError;
}

#undef TEMPLATE_FUNC_NAME
#undef TEMPLATE_BUFFER_TYPE
#undef TEMPLATE_TOKEN
#undef TEMPLATE_TRANSFER_BYTE
#undef TEMPLATE_CLEAR_PIPE
#undef TEMPLATE_BUFFER_OFFSET
#undef TEMPLATE_BUFFER_MOVE
