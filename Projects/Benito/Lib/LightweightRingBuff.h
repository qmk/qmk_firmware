/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** \file
 *
 *  Ultra lightweight ring buffer, for fast insertion/deletion.
 */
 
#ifndef _ULW_RING_BUFF_H_
#define _ULW_RING_BUFF_H_

	/* Includes: */
		#include <stdint.h>
		#include <stdbool.h>

	/* Defines: */
		/** Size of each ring buffer, in bytes */
		#define BUFFER_SIZE      128
		
		/** Type of data to store into the buffer */
		#define RingBuff_Data_t  uint8_t

	/* Type Defines: */
		typedef struct
		{
			RingBuff_Data_t  Buffer[BUFFER_SIZE];
			RingBuff_Data_t* In;
			RingBuff_Data_t* Out;
			uint8_t          Count;
		} RingBuff_t;
	
	/* Inline Functions: */
		static inline void RingBuffer_InitBuffer(RingBuff_t* const Buffer)
		{
			Buffer->In  = Buffer->Buffer;
			Buffer->Out = Buffer->Buffer;
			Buffer->Count = 0;
		}
		
		static inline void RingBuffer_Insert(RingBuff_t* const Buffer, RingBuff_Data_t Data)
		{
			*Buffer->In = Data;
		
			if (++Buffer->In == &Buffer->Buffer[BUFFER_SIZE])
			  Buffer->In = Buffer->Buffer;
			  
			Buffer->Count++;
		}

		static inline RingBuff_Data_t RingBuffer_Remove(RingBuff_t* const Buffer)
		{
			RingBuff_Data_t Data = *Buffer->Out;
		
			if (++Buffer->Out == &Buffer->Buffer[BUFFER_SIZE])
			  Buffer->Out = Buffer->Buffer;
			  
			Buffer->Count--;

			return Data;
		}

#endif
 