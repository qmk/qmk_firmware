uint8_t TEMPLATE_FUNC_NAME (void* Buffer, uint16_t Length)
{
	uint8_t* DataStream     = (uint8_t*)(Buffer + TEMPLATE_BUFFER_OFFSET(Length));
	bool     LastPacketFull = false;
	
	if (Length > USB_ControlRequest.wLength)
	  Length = USB_ControlRequest.wLength;

	while (Length || LastPacketFull)
	{
		if (Endpoint_IsSETUPReceived())
		  return ENDPOINT_RWCSTREAM_HostAborted;

		if (USB_DeviceState == DEVICE_STATE_Unattached)
		  return ENDPOINT_RWCSTREAM_DeviceDisconnected;
		  
		if (Endpoint_IsOUTReceived())
		{
			LastPacketFull = (Endpoint_BytesInEndpoint() == USB_ControlEndpointSize);
		
			while (Length && Endpoint_BytesInEndpoint())
			{
				TEMPLATE_TRANSFER_BYTE(DataStream);
				Length--;
			}
			
			Endpoint_ClearOUT();
			
			if (!(LastPacketFull))
			  Length = 0;
		}		  
	}
	
	while (!(Endpoint_IsINReady()))
	{
		if (USB_DeviceState == DEVICE_STATE_Unattached)
		  return ENDPOINT_RWCSTREAM_DeviceDisconnected;
	}
	
	return ENDPOINT_RWCSTREAM_NoError;
}


#undef TEMPLATE_BUFFER_OFFSET
#undef TEMPLATE_FUNC_NAME
#undef TEMPLATE_TRANSFER_BYTE