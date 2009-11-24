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

#if defined(USB_CAN_BE_HOST)

#define  INCLUDE_FROM_PIPE_C
#include "Pipe.h"

uint8_t USB_ControlPipeSize = PIPE_CONTROLPIPE_DEFAULT_SIZE;

bool Pipe_ConfigurePipe(const uint8_t Number, const uint8_t Type, const uint8_t Token, const uint8_t EndpointNumber,
						const uint16_t Size, const uint8_t Banks)
{
	Pipe_SelectPipe(Number);
	Pipe_EnablePipe();

	UPCFG1X = 0;
	
	UPCFG0X = ((Type << EPTYPE0) | Token | ((EndpointNumber & PIPE_EPNUM_MASK) << PEPNUM0));
	UPCFG1X = ((1 << ALLOC) | Banks | Pipe_BytesToEPSizeMask(Size));

	Pipe_SetInfiniteINRequests();

	return Pipe_IsConfigured();
}

void Pipe_ClearPipes(void)
{
	UPINT = 0;

	for (uint8_t PNum = 0; PNum < PIPE_TOTAL_PIPES; PNum++)
	{
		Pipe_ResetPipe(PNum);
		Pipe_SelectPipe(PNum);
		UPIENX = 0;
		UPINTX = 0;
		Pipe_ClearError();
		Pipe_ClearErrorFlags();
		Pipe_DeallocateMemory();
		Pipe_DisablePipe();
	}
}

bool Pipe_IsEndpointBound(const uint8_t EndpointAddress)
{
	uint8_t PrevPipeNumber = Pipe_GetCurrentPipe();

	for (uint8_t PNum = 0; PNum < PIPE_TOTAL_PIPES; PNum++)
	{
		Pipe_SelectPipe(PNum);
		
		if (Pipe_IsConfigured() && (Pipe_BoundEndpointNumber() == (EndpointAddress & PIPE_EPNUM_MASK)))
		  return true;
	}
	
	Pipe_SelectPipe(PrevPipeNumber);
	return false;
}

uint8_t Pipe_WaitUntilReady(void)
{
	#if (USB_STREAM_TIMEOUT_MS < 0xFF)
	uint8_t  TimeoutMSRem = USB_STREAM_TIMEOUT_MS;	
	#else
	uint16_t TimeoutMSRem = USB_STREAM_TIMEOUT_MS;
	#endif
	
	for (;;)
	{
		if (Pipe_GetPipeToken() == PIPE_TOKEN_IN)
		{
			if (Pipe_IsINReceived())
			  return PIPE_READYWAIT_NoError;
		}
		else
		{
			if (Pipe_IsOUTReady())
			  return PIPE_READYWAIT_NoError;		
		}

		if (Pipe_IsStalled())
		  return PIPE_READYWAIT_PipeStalled;
		else if (USB_HostState == HOST_STATE_Unattached)
		  return PIPE_READYWAIT_DeviceDisconnected;
			  
		if (USB_INT_HasOccurred(USB_INT_HSOFI))
		{
			USB_INT_Clear(USB_INT_HSOFI);

			if (!(TimeoutMSRem--))
			  return PIPE_READYWAIT_Timeout;
		}
	}
}

uint8_t Pipe_Discard_Stream(uint16_t Length
#if !defined(NO_STREAM_CALLBACKS)
                                 , StreamCallbackPtr_t Callback
#endif
								 )
{
	uint8_t  ErrorCode;
	
	Pipe_SetToken(PIPE_TOKEN_IN);

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
						Pipe_ClearIN();
							
						#if !defined(NO_STREAM_CALLBACKS)
						if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
						  return PIPE_RWSTREAM_CallbackAborted;
						#endif

						if ((ErrorCode = Pipe_WaitUntilReady()))
						  return ErrorCode;
					}

					Length -= 8;
					
					Pipe_Discard_Byte();
			case 7: Pipe_Discard_Byte();
			case 6: Pipe_Discard_Byte();
			case 5: Pipe_Discard_Byte();
			case 4: Pipe_Discard_Byte();
			case 3: Pipe_Discard_Byte();
			case 2: Pipe_Discard_Byte();
			case 1:	Pipe_Discard_Byte();
				} while (Length >= 8);	
		}
	}
	#endif

	while (Length)
	{
		if (!(Pipe_IsReadWriteAllowed()))
		{
			Pipe_ClearIN();
				
			#if !defined(NO_STREAM_CALLBACKS)
			if ((Callback != NULL) && (Callback() == STREAMCALLBACK_Abort))
			  return PIPE_RWSTREAM_CallbackAborted;
			#endif

			if ((ErrorCode = Pipe_WaitUntilReady()))
			  return ErrorCode;
		}
		else
		{
			Pipe_Discard_Byte();
			Length--;
		}
	}

	return PIPE_RWSTREAM_NoError;
}

#define  TEMPLATE_FUNC_NAME                        Pipe_Write_Stream_LE
#define  TEMPLATE_BUFFER_TYPE                      const void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_OUT
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearOUT()
#define  TEMPLATE_BUFFER_OFFSET(Length)            0
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         Pipe_Write_Byte(*((uint8_t*)BufferPtr++))
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Write_PStream_LE
#define  TEMPLATE_BUFFER_TYPE                      const void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_OUT
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearOUT()
#define  TEMPLATE_BUFFER_OFFSET(Length)            0
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         Pipe_Write_Byte(pgm_read_byte((uint8_t*)BufferPtr++))
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Write_EStream_LE
#define  TEMPLATE_BUFFER_TYPE                      const void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_OUT
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearOUT()
#define  TEMPLATE_BUFFER_OFFSET(Length)            0
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         Pipe_Write_Byte(eeprom_read_byte((uint8_t*)BufferPtr++))
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Write_Stream_BE
#define  TEMPLATE_BUFFER_TYPE                      const void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_OUT
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearOUT()
#define  TEMPLATE_BUFFER_OFFSET(Length)            Length - 1
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         Pipe_Write_Byte(*((uint8_t*)BufferPtr--))
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Write_PStream_BE
#define  TEMPLATE_BUFFER_TYPE                      const void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_OUT
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearOUT()
#define  TEMPLATE_BUFFER_OFFSET(Length)            Length - 1
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         Pipe_Write_Byte(pgm_read_byte((uint8_t*)BufferPtr--))
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Write_EStream_BE
#define  TEMPLATE_BUFFER_TYPE                      const void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_OUT
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearOUT()
#define  TEMPLATE_BUFFER_OFFSET(Length)            Length - 1
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         Pipe_Write_Byte(eeprom_read_byte((uint8_t*)BufferPtr--))
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Read_Stream_LE
#define  TEMPLATE_BUFFER_TYPE                      void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_IN
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearIN()
#define  TEMPLATE_BUFFER_OFFSET(Length)            0
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         *((uint8_t*)BufferPtr++) = Pipe_Read_Byte()
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Read_EStream_LE
#define  TEMPLATE_BUFFER_TYPE                      void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_IN
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearIN()
#define  TEMPLATE_BUFFER_OFFSET(Length)            0
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         eeprom_write_byte((uint8_t*)BufferPtr++, Pipe_Read_Byte())
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Read_Stream_BE
#define  TEMPLATE_BUFFER_TYPE                      void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_IN
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearIN()
#define  TEMPLATE_BUFFER_OFFSET(Length)            Length - 1
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         *((uint8_t*)BufferPtr--) = Pipe_Read_Byte()
#include "Template/Template_Pipe_RW.c"

#define  TEMPLATE_FUNC_NAME                        Pipe_Read_EStream_BE
#define  TEMPLATE_BUFFER_TYPE                      void*
#define  TEMPLATE_TOKEN                            PIPE_TOKEN_IN
#define  TEMPLATE_CLEAR_PIPE()                     Pipe_ClearIN()
#define  TEMPLATE_BUFFER_OFFSET(Length)            Length - 1
#define  TEMPLATE_TRANSFER_BYTE(BufferPtr)         eeprom_write_byte((uint8_t*)BufferPtr--, Pipe_Read_Byte())
#include "Template/Template_Pipe_RW.c"

#endif
