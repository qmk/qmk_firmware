uint8_t TEMPLATE_FUNC_NAME (void* Buffer, uint16_t Length)
{
	uint8_t* DataStream     = (uint8_t*)(Buffer + TEMPLATE_BUFFER_OFFSET(Length));
	bool     LastPacketFull = false;
	
	if (Length > USB_ControlRequest.wLength)
	  Length = USB_ControlRequest.wLength;
	
	while (Length && !(Endpoint_IsOUTReceived()))
	{
		while (!(Endpoint_IsINReady()))
		{
			if (USB_DeviceState == DEVICE_STATE_Unattached)
			  return ENDPOINT_RWCSTREAM_DeviceDisconnected;
		}
		
		while (Length && (Endpoint_BytesInEndpoint() < USB_ControlEndpointSize))
		{
			TEMPLATE_TRANSFER_BYTE(DataStream);
			Length--;
		}
		
		LastPacketFull = (Endpoint_BytesInEndpoint() == USB_ControlEndpointSize);
		Endpoint_ClearIN();
	}
	
	if (Endpoint_IsOUTReceived())
	  return ENDPOINT_RWCSTREAM_HostAborted;
	
	if (LastPacketFull)
	{
		while (!(Endpoint_IsINReady()))
		{
			if (USB_DeviceState == DEVICE_STATE_Unattached)
			  return ENDPOINT_RWCSTREAM_DeviceDisconnected;		
		}
		
		Endpoint_ClearIN();
	}
	
	while (!(Endpoint_IsOUTReceived()))
	{
		if (USB_DeviceState == DEVICE_STATE_Unattached)
		  return ENDPOINT_RWCSTREAM_DeviceDisconnected;	
	}

	return ENDPOINT_RWCSTREAM_NoError;
}

#undef TEMPLATE_BUFFER_OFFSET
#undef TEMPLATE_FUNC_NAME
#undef TEMPLATE_TRANSFER_BYTE