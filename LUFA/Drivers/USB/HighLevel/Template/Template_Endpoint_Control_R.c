uint8_t TEMPLATE_FUNC_NAME (void* const Buffer,
                            uint16_t Length)
{
	uint8_t* DataStream = ((uint8_t*)Buffer + TEMPLATE_BUFFER_OFFSET(Length));

	if (!(Length))
	  Endpoint_ClearOUT();

	while (Length)
	{
		uint8_t USB_DeviceState_LCL = USB_DeviceState;

		if (USB_DeviceState_LCL == DEVICE_STATE_Unattached)
		  return ENDPOINT_RWCSTREAM_DeviceDisconnected;
		else if (USB_DeviceState_LCL == DEVICE_STATE_Suspended)
		  return ENDPOINT_RWCSTREAM_BusSuspended;
		else if (Endpoint_IsSETUPReceived())
		  return ENDPOINT_RWCSTREAM_HostAborted;

		if (Endpoint_IsOUTReceived())
		{
			while (Length && Endpoint_BytesInEndpoint())
			{
				TEMPLATE_TRANSFER_BYTE(DataStream);
				TEMPLATE_BUFFER_MOVE(DataStream, 1);
				Length--;
			}

			Endpoint_ClearOUT();
		}
	}

	while (!(Endpoint_IsINReady()))
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
