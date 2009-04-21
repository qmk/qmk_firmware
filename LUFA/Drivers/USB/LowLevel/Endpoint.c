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

#if !defined(STATIC_ENDPOINT_CONFIGURATION)
bool Endpoint_ConfigureEndpoint(const uint8_t  Number, const uint8_t Type, const uint8_t Direction,
			                    const uint16_t Size, const uint8_t Banks)
{
	Endpoint_SelectEndpoint(Number);
	Endpoint_EnableEndpoint();

	UECFG1X = 0;	

	UECFG0X = ((Type << EPTYPE0) | Direction);
	UECFG1X = ((1 << ALLOC) | Banks | Endpoint_BytesToEPSizeMask(Size));

	return Endpoint_IsConfigured();
}
#else
bool Endpoint_ConfigureEndpointStatic(const uint8_t Number, const uint8_t UECFG0XData, const uint8_t UECFG1XData)
{
	Endpoint_SelectEndpoint(Number);
	Endpoint_EnableEndpoint();

	UECFG1X = 0;

	UECFG0X = UECFG0XData;
	UECFG1X = UECFG1XData;

	return Endpoint_IsConfigured();
}
#endif

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

uint8_t Endpoint_WaitUntilReady(void)
{
	uint16_t TimeoutMSRem = USB_STREAM_TIMEOUT_MS;

	USB_INT_Clear(USB_INT_SOFI);

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
                                , uint8_t (* const Callback)(void)
#endif
								)
{
	uint8_t  ErrorCode;
	
	if ((ErrorCode = Endpoint_WaitUntilReady()))
	  return ErrorCode;

	while (Length--)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearOUT();

			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_ERROR_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			Endpoint_Discard_Byte();
		}
	}
	
	return ENDPOINT_RWSTREAM_ERROR_NoError;
}

uint8_t Endpoint_Write_Stream_LE(const void* Buffer, uint16_t Length
#if !defined(NO_STREAM_CALLBACKS)
                                 , uint8_t (* const Callback)(void)
#endif
								 )
{
	uint8_t* DataStream   = (uint8_t*)Buffer;
	uint8_t  ErrorCode;
	
	if ((ErrorCode = Endpoint_WaitUntilReady()))
	  return ErrorCode;

	while (Length--)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearIN();
			
			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_ERROR_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			Endpoint_Write_Byte(*(DataStream++));
		}
	}
	
	return ENDPOINT_RWSTREAM_ERROR_NoError;
}

uint8_t Endpoint_Write_Stream_BE(const void* Buffer, uint16_t Length
#if !defined(NO_STREAM_CALLBACKS)
                                 , uint8_t (* const Callback)(void)
#endif
								 )
{
	uint8_t* DataStream = (uint8_t*)(Buffer + Length - 1);
	uint8_t  ErrorCode;
	
	if ((ErrorCode = Endpoint_WaitUntilReady()))
	  return ErrorCode;

	while (Length--)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearIN();

			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_ERROR_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			Endpoint_Write_Byte(*(DataStream--));
		}
	}
	
	return ENDPOINT_RWSTREAM_ERROR_NoError;
}

uint8_t Endpoint_Read_Stream_LE(void* Buffer, uint16_t Length
#if !defined(NO_STREAM_CALLBACKS)
                                 , uint8_t (* const Callback)(void)
#endif
								 )
{
	uint8_t* DataStream = (uint8_t*)Buffer;
	uint8_t  ErrorCode;
	
	if ((ErrorCode = Endpoint_WaitUntilReady()))
	  return ErrorCode;

	while (Length--)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearOUT();

			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_ERROR_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			*(DataStream++) = Endpoint_Read_Byte();
		}
	}
	
	return ENDPOINT_RWSTREAM_ERROR_NoError;
}

uint8_t Endpoint_Read_Stream_BE(void* Buffer, uint16_t Length
#if !defined(NO_STREAM_CALLBACKS)
                                 , uint8_t (* const Callback)(void)
#endif
								 )
{
	uint8_t* DataStream = (uint8_t*)(Buffer + Length - 1);
	uint8_t  ErrorCode;
	
	if ((ErrorCode = Endpoint_WaitUntilReady()))
	  return ErrorCode;

	while (Length--)
	{
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearOUT();

			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return ENDPOINT_RWSTREAM_ERROR_CallbackAborted;
			#endif

			if ((ErrorCode = Endpoint_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			*(DataStream--) = Endpoint_Read_Byte();
		}
	}
	
	return ENDPOINT_RWSTREAM_ERROR_NoError;
}

uint8_t Endpoint_Write_Control_Stream_LE(const void* Buffer, uint16_t Length)
{
	uint8_t* DataStream = (uint8_t*)Buffer;
	bool     SendZLP    = true;
	
	while (Length && !(Endpoint_IsOUTReceived()))
	{
		while (!(Endpoint_IsINReady()));
		
		while (Length && (Endpoint_BytesInEndpoint() < USB_ControlEndpointSize))
		{
			Endpoint_Write_Byte(*(DataStream++));
			
			Length--;
		}
		
		SendZLP = (Endpoint_BytesInEndpoint() == USB_ControlEndpointSize);
		Endpoint_ClearIN();
	}
	
	if (Endpoint_IsOUTReceived())
	  return ENDPOINT_RWCSTREAM_ERROR_HostAborted;
	
	if (SendZLP)
	{
		while (!(Endpoint_IsINReady()));
		Endpoint_ClearIN();
	}
	
	while (!(Endpoint_IsOUTReceived()));

	return ENDPOINT_RWCSTREAM_ERROR_NoError;
}

uint8_t Endpoint_Write_Control_Stream_BE(const void* Buffer, uint16_t Length)
{
	uint8_t* DataStream = (uint8_t*)(Buffer + Length - 1);
	bool     SendZLP    = true;
	
	while (Length && !(Endpoint_IsOUTReceived()))
	{
		while (!(Endpoint_IsINReady()));
		
		while (Length && (Endpoint_BytesInEndpoint() < USB_ControlEndpointSize))
		{
			Endpoint_Write_Byte(*(DataStream--));
			
			Length--;
		}
		
		SendZLP = (Endpoint_BytesInEndpoint() == USB_ControlEndpointSize);
		Endpoint_ClearIN();
	}
	
	if (Endpoint_IsOUTReceived())
	  return ENDPOINT_RWCSTREAM_ERROR_HostAborted;
	
	if (SendZLP)
	{
		while (!(Endpoint_IsINReady()));
		Endpoint_ClearIN();
	}
	
	while (!(Endpoint_IsOUTReceived()));

	return ENDPOINT_RWCSTREAM_ERROR_NoError;
}

uint8_t Endpoint_Read_Control_Stream_LE(void* Buffer, uint16_t Length)
{
	uint8_t* DataStream = (uint8_t*)Buffer;
	
	while (Length)
	{
		while (!(Endpoint_IsOUTReceived()));
		
		while (Length && Endpoint_BytesInEndpoint())
		{
			*(DataStream++) = Endpoint_Read_Byte();
			
			Length--;
		}
		
		Endpoint_ClearOUT();
	}
	
	while (!(Endpoint_IsINReady()));
	
	return ENDPOINT_RWCSTREAM_ERROR_NoError;
}

uint8_t Endpoint_Read_Control_Stream_BE(void* Buffer, uint16_t Length)
{
	uint8_t* DataStream = (uint8_t*)(Buffer + Length - 1);
	
	while (Length)
	{
		while (!(Endpoint_IsOUTReceived()));
		
		while (Length && Endpoint_BytesInEndpoint())
		{
			*(DataStream--) = Endpoint_Read_Byte();
			
			Length--;
		}
		
		Endpoint_ClearOUT();
	}
	
	while (!(Endpoint_IsINReady()));

	return ENDPOINT_RWCSTREAM_ERROR_NoError;
}

#endif
