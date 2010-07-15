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
		#include <util/atomic.h>
	
		#include <stdint.h>
		#include <stdbool.h>

	/* Defines: */
		/** Size of each ring buffer, in data elements - must be between 1 and 255. */
		#define BUFFER_SIZE      255
		
		/** Type of data to store into the buffer. */
		#define RingBuff_Data_t  uint8_t

	/* Type Defines: */
		/** Type define for a new ring buffer object. Buffers should be initialized via a call to
		 *  \ref RingBuffer_InitBuffer() before use.
		 */
		typedef struct
		{
			RingBuff_Data_t  Buffer[BUFFER_SIZE]; /**< Internal ring buffer data, referenced by the buffer pointers. */
			RingBuff_Data_t* In; /**< Current storage location in the circular buffer */
			RingBuff_Data_t* Out; /**< Current retrieval location in the circular buffer */
			uint8_t          Count; /**< Total number of bytes stored in the circular buffer */
		} RingBuff_t;
	
	/* Inline Functions: */
		/** Initializes a ring buffer ready for use. Buffers must be initialized via this function
		 *  before any operations are called upon them. Already initialized buffers may be reset
		 *  by re-initializing them using this function.
		 *
		 *  \param[out] Buffer  Pointer to a ring buffer structure to initialize
		 */
		static inline void RingBuffer_InitBuffer(RingBuff_t* const Buffer)
		{
			Buffer->In    = Buffer->Buffer;
			Buffer->Out   = Buffer->Buffer;
			Buffer->Count = 0;
		}
		
		/** Atomically determines if the specified ring buffer contains any free space. This should
		 *  be tested before storing data to the buffer, to ensure that no data is lost due to a
		 *  buffer overrun.
		 *
		 *  \param[in,out] Buffer  Pointer to a ring buffer structure to insert into
		 *
		 *  \return Boolean true if the buffer contains no free space, false otherwise
		 */		 
		static inline bool RingBuffer_IsFull(RingBuff_t* const Buffer)
		{
			bool IsFull;
			
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				IsFull = (Buffer->Count == BUFFER_SIZE);
			}
			
			return IsFull;
		}
		
		/** Atomically inserts an element into the ring buffer.
		 *
		 *  \param[in,out] Buffer  Pointer to a ring buffer structure to insert into
		 *  \param[in]     Data    Data element to insert into the buffer
		 */
		static inline void RingBuffer_AtomicInsert(RingBuff_t* const Buffer, RingBuff_Data_t Data)
		{
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				*Buffer->In = Data;
			
				if (++Buffer->In == &Buffer->Buffer[BUFFER_SIZE])
				  Buffer->In = Buffer->Buffer;
				  
				Buffer->Count++;
			}
		}

		/** Atomically retrieves an element from the ring buffer.
		 *
		 *  \param[in,out] Buffer  Pointer to a ring buffer structure to retrieve from
		 *
		 *  \return Next data element stored in the buffer
		 */
		static inline RingBuff_Data_t RingBuffer_AtomicRemove(RingBuff_t* const Buffer)
		{
			RingBuff_Data_t Data;
			
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				Data = *Buffer->Out;
			
				if (++Buffer->Out == &Buffer->Buffer[BUFFER_SIZE])
				  Buffer->Out = Buffer->Buffer;
				  
				Buffer->Count--;
			}

			return Data;
		}

		/** Inserts an element into the ring buffer.
		 *
		 *  \param[in,out] Buffer  Pointer to a ring buffer structure to insert into
		 *  \param[in]     Data    Data element to insert into the buffer
		 */
		static inline void RingBuffer_Insert(RingBuff_t* const Buffer, RingBuff_Data_t Data)
		{
			*Buffer->In = Data;
			
			if (++Buffer->In == &Buffer->Buffer[BUFFER_SIZE])
			  Buffer->In = Buffer->Buffer;
				  
			Buffer->Count++;
		}

		/** Retrieves an element from the ring buffer.
		 *
		 *  \param[in,out] Buffer  Pointer to a ring buffer structure to retrieve from
		 *
		 *  \return Next data element stored in the buffer
		 */
		static inline RingBuff_Data_t RingBuffer_Remove(RingBuff_t* const Buffer)
		{
			RingBuff_Data_t Data = *Buffer->Out;
			
			if (++Buffer->Out == &Buffer->Buffer[BUFFER_SIZE])
			  Buffer->Out = Buffer->Buffer;
				  
			Buffer->Count--;

			return Data;
		}

#endif
 