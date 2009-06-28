/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "../HighLevel/USBMode.h"

#if defined(USB_CAN_BE_DEVICE)

#define  INCLUDE_FROM_ENDPOINT_C
#include "Endpoint.h"

#if !defined(FIXED_CONTROL_ENDPOINT_SIZE)
uint8_t USB_ControlEndpointSize = ENDPOINT_CONTROLEP_DEFAULT_SIZE;
#endif

uint8_t Endpoint_BytesToEPSizeMaskDynamic(const uint16_t Size)
{
	return Endpoint_BytesToEPSizeMask(Size);
}

bool Endpoint_ConfigureEndpoint_Prv(const uint8_t Number, const uint8_t UECFG0XData, const uint8_t UECFG1XData)
{
	Endpoint_SelectEndpoint(Number);
	Endpoint_EnableEndpoint();

	UECFG1X = 0;

	UECFG0X = UECFG0XData;
	UECFG1X = UECFG1XData;

	return Endpoint_IsConfigured();
}

void Endpoint_ClearEndpoints(void)
{
	UEINT = 0;

	for (uint8_t EPNum = 0; EPNum < ENDPOINT_TOTAL_ENDPOINTS; EPNum++)
	{
		Endpoint_SelectEndpoint(EPNum);	
		UEIENX = 0;
		UEINTX = 0;
		Endpoint_DeallocateMemory();
		Endpoint_DisableEndpoint();
	}
}

#if !defined(CONTROL_ONLY_DEVICE)
uint8_t Endpoint_WaitUntilReady(void)
{
	#if (USB_STREAM_TIMEOUT_MS < 0xFF)
	uint8_t  TimeoutMSRem = USB_STREAM_TIMEOUT_MS;	
	#else
	uint16_t TimeoutMSRem = USB_STREAM_TIMEOUT_MS;
	#endif

	for (;;)
	{
		if (Endpoint_GetEndpointDirection() == ENDPOINT_DIR_IN)
		{
			if (Endpoint_IsINReady())
			  return ENDPOINT_READYWAIT_NoError;
		}
		else
		{
			if (Endpoint_IsOUTReceived())
			  return ENDPOINT_READYWAIT_NoError;		
		}
		
		if (!(USB_IsConnected))
		  return ENDPOINT_READYWAIT_DeviceDisconnected;
		else if (Endpoint_IsStalled())
		  return ENDPOINT_READYWAIT_EndpointStalled;
			  
		if (USB_INT_HasOccurred(USB_INT_SOFI))
		{
			USB_INT_Clear(USB_INT_SOFI);

			if (!(TimeoutMSRem--))
			  return ENDPOINT_READYWAIT_Timeout;
		}
	}
}

uint8_t Endpoint_Discard_Stream(uint16_t Length
#if !defined(NO_STREAM_CALLBACKS)
                                , StreamCallbackPtr_t Callback
#endif
								)
{
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
						Endpoint_ClearOUT();

						#if !defined(NO_STREAM_CALLBACKS)
						if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
						  return ENDPOINT_RWSTREAM_CallbackAborted;
						#endif

						if ((ErrorCode = Endpoint_WaitUntilReady()))
						  return ErrorCode;
					}

					Length -= 8;
					
					Endpoint_Discard_Byte();
			case 7: Endpoint_Discard_Byte();
			case 6: Endpoint_Discard_Byte();
			case 5: Endpoint_Discard_Byte();
			case 4: Endpoint_Discard_Byte();
			case 3: Endpoint_Discard_Byte();
			case 2: Endpoint_Discard_Byte();
			case 1:	Endpoint_Discard_Byte();
				} while (Length >= 8);	
		}
	}
	#endif

	while (Length)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearOUT();

			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			Endpoint_Discard_Byte();
			Length--;
		}
	}
	
	return ENDPOINT_RWSTREAM_NoError;
}

uint8_t Endpoint_Write_Stream_LE(const void* Buffer, uint16_t Length
#if !defined(NO_STREAM_CALLBACKS)
                                 , StreamCallbackPtr_t Callback
#endif
								 )
{
	uint8_t* DataStream   = (uint8_t*)Buffer;
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
						Endpoint_ClearIN();

						#if !defined(NO_STREAM_CALLBACKS)
						if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
						  return ENDPOINT_RWSTREAM_CallbackAborted;
						#endif

						if ((ErrorCode = Endpoint_WaitUntilReady()))
						  return ErrorCode;
					}

					Length -= 8;
					
					Endpoint_Write_Byte(*(DataStream++));
			case 7: Endpoint_Write_Byte(*(DataStream++));
			case 6: Endpoint_Write_Byte(*(DataStream++));
			case 5: Endpoint_Write_Byte(*(DataStream++));
			case 4: Endpoint_Write_Byte(*(DataStream++));
			case 3: Endpoint_Write_Byte(*(DataStream++));
			case 2: Endpoint_Write_Byte(*(DataStream++));
			case 1:	Endpoint_Write_Byte(*(DataStream++));
				} while (Length >= 8);	
		}
	}
	#endif

	while (Length)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearIN();
			
			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			Endpoint_Write_Byte(*(DataStream++));
			Length--;
		}
	}

	return ENDPOINT_RWSTREAM_NoError;
}

uint8_t Endpoint_Write_Stream_BE(const void* Buffer, uint16_t Length
#if !defined(NO_STREAM_CALLBACKS)
                                 , StreamCallbackPtr_t Callback
#endif
								 )
{
	uint8_t* DataStream = (uint8_t*)(Buffer + Length - 1);
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
						Endpoint_ClearIN();

						#if !defined(NO_STREAM_CALLBACKS)
						if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
						  return ENDPOINT_RWSTREAM_CallbackAborted;
						#endif

						if ((ErrorCode = Endpoint_WaitUntilReady()))
						  return ErrorCode;
					}

					Length -= 8;
					
					Endpoint_Write_Byte(*(DataStream--));
			case 7: Endpoint_Write_Byte(*(DataStream--));
			case 6: Endpoint_Write_Byte(*(DataStream--));
			case 5: Endpoint_Write_Byte(*(DataStream--));
			case 4: Endpoint_Write_Byte(*(DataStream--));
			case 3: Endpoint_Write_Byte(*(DataStream--));
			case 2: Endpoint_Write_Byte(*(DataStream--));
			case 1:	Endpoint_Write_Byte(*(DataStream--));
				} while (Length >= 8);	
		}
	}
	#endif

	while (Length)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearIN();

			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			Endpoint_Write_Byte(*(DataStream--));
			Length--;
		}
	}

	return ENDPOINT_RWSTREAM_NoError;
}

uint8_t Endpoint_Read_Stream_LE(void* Buffer, uint16_t Length
#if !defined(NO_STREAM_CALLBACKS)
                                 , StreamCallbackPtr_t Callback
#endif
								 )
{
	uint8_t* DataStream = (uint8_t*)Buffer;
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
						Endpoint_ClearOUT();

						#if !defined(NO_STREAM_CALLBACKS)
						if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
						  return ENDPOINT_RWSTREAM_CallbackAborted;
						#endif

						if ((ErrorCode = Endpoint_WaitUntilReady()))
						  return ErrorCode;
					}

					Length -= 8;
					
					*(DataStream++) = Endpoint_Read_Byte();
			case 7: *(DataStream++) = Endpoint_Read_Byte();
			case 6: *(DataStream++) = Endpoint_Read_Byte();
			case 5: *(DataStream++) = Endpoint_Read_Byte();
			case 4: *(DataStream++) = Endpoint_Read_Byte();
			case 3: *(DataStream++) = Endpoint_Read_Byte();
			case 2: *(DataStream++) = Endpoint_Read_Byte();
			case 1:	*(DataStream++) = Endpoint_Read_Byte();
				} while (Length >= 8);	
		}
	}
	#endif

	while (Length)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearOUT();

			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			*(DataStream++) = Endpoint_Read_Byte();
			Length--;
		}
	}

	return ENDPOINT_RWSTREAM_NoError;
}

uint8_t Endpoint_Read_Stream_BE(void* Buffer, uint16_t Length
#if !defined(NO_STREAM_CALLBACKS)
                                 , StreamCallbackPtr_t Callback
#endif
								 )
{
	uint8_t* DataStream = (uint8_t*)(Buffer + Length - 1);
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
						Endpoint_ClearOUT();

						#if !defined(NO_STREAM_CALLBACKS)
						if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
						  return ENDPOINT_RWSTREAM_CallbackAborted;
						#endif

						if ((ErrorCode = Endpoint_WaitUntilReady()))
						  return ErrorCode;
					}

					Length -= 8;
					
					*(DataStream--) = Endpoint_Read_Byte();
			case 7: *(DataStream--) = Endpoint_Read_Byte();
			case 6: *(DataStream--) = Endpoint_Read_Byte();
			case 5: *(DataStream--) = Endpoint_Read_Byte();
			case 4: *(DataStream--) = Endpoint_Read_Byte();
			case 3: *(DataStream--) = Endpoint_Read_Byte();
			case 2: *(DataStream--) = Endpoint_Read_Byte();
			case 1:	*(DataStream--) = Endpoint_Read_Byte();
				} while (Length >= 8);	
		}
	}
	#endif

	while (Length)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearOUT();

			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			*(DataStream--) = Endpoint_Read_Byte();
			Length--;
		}
	}

	return ENDPOINT_RWSTREAM_NoError;
}
#endif

uint8_t Endpoint_Write_Control_Stream_LE(const void* Buffer, uint16_t Length)
{
	uint8_t* DataStream     = (uint8_t*)Buffer;
	bool     LastPacketFull = false;
	
	if (Length > USB_ControlRequest.wLength)
	  Length = USB_ControlRequest.wLength;
	
	while (Length && !(Endpoint_IsOUTReceived()))
	{
		while (!(Endpoint_IsINReady()));
		
		while (Length && (Endpoint_BytesInEndpoint() < USB_ControlEndpointSize))
		{
			Endpoint_Write_Byte(*(DataStream++));
			Length--;
		}
		
		LastPacketFull = (Endpoint_BytesInEndpoint() == USB_ControlEndpointSize);
		Endpoint_ClearIN();
	}
	
	if (Endpoint_IsOUTReceived())
	  return ENDPOINT_RWCSTREAM_HostAborted;
	
	if (LastPacketFull)
	{
		while (!(Endpoint_IsINReady()));
		Endpoint_ClearIN();
	}
	
	while (!(Endpoint_IsOUTReceived()));

	return ENDPOINT_RWCSTREAM_NoError;
}

uint8_t Endpoint_Write_Control_Stream_BE(const void* Buffer, uint16_t Length)
{
	uint8_t* DataStream     = (uint8_t*)(Buffer + Length - 1);
	bool     LastPacketFull = false;
	
	if (Length > USB_ControlRequest.wLength)
	  Length = USB_ControlRequest.wLength;

	while (Length && !(Endpoint_IsOUTReceived()))
	{
		if (Endpoint_IsINReady())
		{
			while (Length && (Endpoint_BytesInEndpoint() < USB_ControlEndpointSize))
			{
				Endpoint_Write_Byte(*(DataStream--));
				Length--;
			}
			
			LastPacketFull = (Endpoint_BytesInEndpoint() == USB_ControlEndpointSize);
			Endpoint_ClearIN();
		}
	}
	
	if (Endpoint_IsOUTReceived())
	  return ENDPOINT_RWCSTREAM_HostAborted;
	
	if (LastPacketFull)
	{
		while (!(Endpoint_IsINReady()));
		Endpoint_ClearIN();
	}
	
	while (!(Endpoint_IsOUTReceived()));

	return ENDPOINT_RWCSTREAM_NoError;
}

uint8_t Endpoint_Read_Control_Stream_LE(void* Buffer, uint16_t Length)
{
	uint8_t* DataStream = (uint8_t*)Buffer;
	
	while (Length)
	{
		if (Endpoint_IsOUTReceived())
		{
			while (Length && Endpoint_BytesInEndpoint())
			{
				*(DataStream++) = Endpoint_Read_Byte();
				Length--;
			}
			
			Endpoint_ClearOUT();
		}
	}
	
	while (!(Endpoint_IsINReady()));
	
	return ENDPOINT_RWCSTREAM_NoError;
}

uint8_t Endpoint_Read_Control_Stream_BE(void* Buffer, uint16_t Length)
{
	uint8_t* DataStream = (uint8_t*)(Buffer + Length - 1);
	
	while (Length)
	{
		if (Endpoint_IsOUTReceived())
		{
			while (Length && Endpoint_BytesInEndpoint())
			{
				*(DataStream--) = Endpoint_Read_Byte();
				Length--;
			}
			
			Endpoint_ClearOUT();
		}
	}
	
	while (!(Endpoint_IsINReady()));

	return ENDPOINT_RWCSTREAM_NoError;
}

#endif
