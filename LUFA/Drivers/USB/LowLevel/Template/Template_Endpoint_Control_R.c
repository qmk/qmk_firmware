uint8_t TEMPLATE_FUNC_NAME (void* Buffer, uint16_t Length)
{
	uint8_t* DataStream = (uint8_t*)(Buffer + TEMPLATE_BUFFER_OFFSET(Length));
	
	while (Length)
	{
		if (Endpoint_IsOUTReceived())
		{
			while (Length && Endpoint_BytesInEndpoint())
			{
				TEMPLATE_TRANSFER_BYTE(DataStream);
				Length--;
			}
			
			Endpoint_ClearOUT();
		}
	}
	
	while (!(Endpoint_IsINReady()));
	
	return ENDPOINT_RWCSTREAM_NoError;
}


#undef TEMPLATE_BUFFER_OFFSET
#undef TEMPLATE_FUNC_NAME
#undef TEMPLATE_TRANSFER_BYTE