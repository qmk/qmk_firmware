/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
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

#include "RingBuff.h"

void Buffer_Initialize(RingBuff_t* const Buffer)
{
	BUFF_ATOMIC_BLOCK
	{
		Buffer->InPtr    = (RingBuff_Data_t*)&Buffer->Buffer;
		Buffer->OutPtr   = (RingBuff_Data_t*)&Buffer->Buffer;
		Buffer->Elements = 0;
	}
}

void Buffer_StoreElement(RingBuff_t* const Buffer, RingBuff_Data_t Data)
{
	BUFF_ATOMIC_BLOCK
	{
	#if defined(BUFF_DROPOLD)
		if (Buffer->Elements == BUFF_LENGTH)
		{
			Buffer->OutPtr++;
	
			if (Buffer->OutPtr == &Buffer->Buffer[BUFF_LENGTH])
			  Buffer->OutPtr = (RingBuff_Data_t*)&Buffer->Buffer;
		}
		else
		{
			Buffer->Elements++;
		}
	#elif defined(BUFF_DROPNEW)
		if (Buffer->Elements == BUFF_LENGTH)
		  return;
	
		  Buffer->Elements++;
	#elif defined(BUFF_NODROPCHECK)
		  Buffer->Elements++;
	#endif
	
		*(Buffer->InPtr) = Data;
		Buffer->InPtr++;
	
		if (Buffer->InPtr == &Buffer->Buffer[BUFF_LENGTH])
		  Buffer->InPtr = (RingBuff_Data_t*)&Buffer->Buffer;
	}
}

RingBuff_Data_t Buffer_GetElement(RingBuff_t* const Buffer)
{
	RingBuff_Data_t BuffData;
	
	BUFF_ATOMIC_BLOCK
	{
#if defined(BUFF_EMPTYRETURNSZERO)
		if (!(Buffer->Elements))
		  return 0;
#elif !defined(BUFF_NOEMPTYCHECK)
	#error No empty buffer check behavior specified.
#endif

		BuffData = *(Buffer->OutPtr);
	
		Buffer->OutPtr++;
		Buffer->Elements--;
	
		if (Buffer->OutPtr == &Buffer->Buffer[BUFF_LENGTH])
		  Buffer->OutPtr = (RingBuff_Data_t*)&Buffer->Buffer;
	}
	
	return BuffData;
}

#if defined(BUFF_USEPEEK)
RingBuff_Data_t Buffer_PeekElement(const RingBuff_t* const Buffer)
{
	RingBuff_Data_t BuffData;

	BUFF_ATOMIC_BLOCK
	{
#if defined(BUFF_EMPTYRETURNSZERO)
		if (!(Buffer->Elements))
		  return 0;
#elif !defined(BUFF_NOEMPTYCHECK)
	#error No empty buffer check behavior specified.
#endif

		BuffData = *(Buffer->OutPtr);
	}

	return BuffData;
}
#endif
