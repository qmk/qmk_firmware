uint8_t TEMPLATE_FUNC_NAME (const void* const Buffer,
                            uint16_t Length)
{
	uint8_t* DataStream     = ((uint8_t*)Buffer + TEMPLATE_BUFFER_OFFSET(Length));
	bool     LastPacketFull = false;

	if (Length > USB_ControlRequest.wLength)
	  Length = USB_ControlRequest.wLength;
	else if (!(Length))
	  Endpoint_ClearIN();

	while (Length || LastPacketFull)
	{
		uint8_t USB_DeviceState_LCL = USB_DeviceState;

		if (USB_DeviceState_LCL == DEVICE_STATE_Unattached)
		  return ENDPOINT_RWCSTREAM_DeviceDisconnected;
		else if (USB_DeviceState_LCL == DEVICE_STATE_Suspended)
		  return ENDPOINT_RWCSTREAM_BusSuspended;
		else if (Endpoint_IsSETUPReceived())
		  return ENDPOINT_RWCSTREAM_HostAborted;
		else if (Endpoint_IsOUTReceived())
		  break;

		if (Endpoint_IsINReady())
		{
			uint16_t BytesInEndpoint = Endpoint_BytesInEndpoint();

			while (Length && (BytesInEndpoint < USB_ControlEndpointSize))
			{
				TEMPLATE_TRANSFER_BYTE(DataStream);
				TEMPLATE_BUFFER_MOVE(DataStream, 1);
				Length--;
				BytesInEndpoint++;
			}

			LastPacketFull = (BytesInEndpoint == USB_ControlEndpointSize);
			Endpoint_ClearIN();
		}
	}

	while (!(Endpoint_IsOUTReceived()))
	{
		uint8_t USB_DeviceState_LCL = USB_DeviceState;

		if (USB_DeviceState_LCL == DEVICE_STATE_Unattached)
		  return ENDPOINT_RWCSTREAM_DeviceDisconnected;
		else if (USB_DeviceState_LCL == DEVICE_STATE_Suspended)
		  return ENDPOINT_RWCSTREAM_BusSuspended;
	}

	return ENDPOINT_RWCSTREAM_NoError;
}

#undef TEMPLATE_BUFFER_OFFSET
#undef TEMPLATE_BUFFER_MOVE
#undef TEMPLATE_FUNC_NAME
#undef TEMPLATE_TRANSFER_BYTE
