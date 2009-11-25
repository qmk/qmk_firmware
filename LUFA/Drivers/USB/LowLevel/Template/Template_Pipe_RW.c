uint8_t TEMPLATE_FUNC_NAME (TEMPLATE_BUFFER_TYPE Buffer, uint16_t Length __CALLBACK_PARAM)
{
	uint8_t* DataStream = ((uint8_t*)Buffer + TEMPLATE_BUFFER_OFFSET(Length));
	uint8_t  ErrorCode;
	
	Pipe_SetPipeToken(TEMPLATE_TOKEN);

	if ((ErrorCode = Pipe_WaitUntilReady()))
	  return ErrorCode;

	#if defined(FAST_STREAM_TRANSFERS)
	uint8_t BytesRemToAlignment = (Pipe_BytesInPipe() & 0x07);

	if (Length >= 8)
	{
		Length -= BytesRemToAlignment;

		switch (BytesRemToAlignment)
		{
			default:
				do
				{
					if (!(Pipe_IsReadWriteAllowed()))
					{
						TEMPLATE_CLEAR_PIPE();

						#if !defined(NO_STREAM_CALLBACKS)
						if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
						  return PIPE_RWSTREAM_CallbackAborted;
						#endif

						if ((ErrorCode = Pipe_WaitUntilReady()))
						  return ErrorCode;
					}

					Length -= 8;
					
					TEMPLATE_TRANSFER_BYTE(DataStream);
			case 7: TEMPLATE_TRANSFER_BYTE(DataStream);
			case 6: TEMPLATE_TRANSFER_BYTE(DataStream);
			case 5: TEMPLATE_TRANSFER_BYTE(DataStream);
			case 4: TEMPLATE_TRANSFER_BYTE(DataStream);
			case 3: TEMPLATE_TRANSFER_BYTE(DataStream);
			case 2: TEMPLATE_TRANSFER_BYTE(DataStream);
			case 1:	TEMPLATE_TRANSFER_BYTE(DataStream);
				} while (Length >= 8);	
		}
	}
	#endif

	while (Length)
	{
		if (!(Pipe_IsReadWriteAllowed()))
		{
			TEMPLATE_CLEAR_PIPE();

			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return PIPE_RWSTREAM_CallbackAborted;
			#endif

			if ((ErrorCode = Pipe_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			TEMPLATE_TRANSFER_BYTE(DataStream);
			Length--;
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
