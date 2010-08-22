uint8_t TEMPLATE_FUNC_NAME (TEMPLATE_BUFFER_TYPE Buffer,
                            uint16_t Length
                            __CALLBACK_PARAM)
{
	uint8_t* DataStream = ((uint8_t*)Buffer + TEMPLATE_BUFFER_OFFSET(Length));
	uint8_t  ErrorCode;
	
	if ((ErrorCode = Endpoint_WaitUntilReady()))
	  return ErrorCode;

	#if defined(FAST_STREAM_TRANSFERS)
	uint8_t BytesRemToAlignment = (Endpoint_BytesInEndpoint() & 0x07);

	if (Length >= 8)
	{
		Length -= BytesRemToAlignment;

		switch (BytesRemToAlignment)
		{
			default:
				do
				{
					if (!(Endpoint_IsReadWriteAllowed()))
					{
						TEMPLATE_CLEAR_ENDPOINT();

						#if !defined(NO_STREAM_CALLBACKS)
						if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
						  return ENDPOINT_RWSTREAM_CallbackAborted;
						#endif

						if ((ErrorCode = Endpoint_WaitUntilReady()))
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
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			TEMPLATE_CLEAR_ENDPOINT();

			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			TEMPLATE_TRANSFER_BYTE(DataStream);
			Length--;
		}
	}

	return ENDPOINT_RWSTREAM_NoError;
}

#undef TEMPLATE_FUNC_NAME
#undef TEMPLATE_BUFFER_TYPE
#undef TEMPLATE_TRANSFER_BYTE
#undef TEMPLATE_CLEAR_ENDPOINT
#undef TEMPLATE_BUFFER_OFFSET