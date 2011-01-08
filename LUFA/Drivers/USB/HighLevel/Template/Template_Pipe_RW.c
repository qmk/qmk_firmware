uint8_t TEMPLATE_FUNC_NAME (TEMPLATE_BUFFER_TYPE Buffer,
                            uint16_t Length
                            __CALLBACK_PARAM)
{
	uint8_t* DataStream = ((uint8_t*)Buffer + TEMPLATE_BUFFER_OFFSET(Length));
	uint8_t  ErrorCode;

	Pipe_SetPipeToken(TEMPLATE_TOKEN);

	if ((ErrorCode = Pipe_WaitUntilReady()))
	  return ErrorCode;

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

