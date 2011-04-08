/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Lightweight ring buffer, for fast insertion/deletion of bytes.
 *
 *  Lightweight ring buffer, for fast insertion/deletion. Multiple buffers can be created of
 *  different sizes to suit different needs.
 *
 *  Note that for each buffer, insertion and removal operations may occur at the same time (via
 *  a multi-threaded ISR based system) however the same kind of operation (two or more insertions
 *  or deletions) must not overlap. If there is possibility of two or more of the same kind of
 *  operating occurring at the same point in time, atomic (mutex) locking should be used.
 */
 
/** \ingroup Group_MiscDrivers
 *  \defgroup Group_RingBuff Generic Byte Ring Buffer - LUFA/Drivers/Misc/RingBuffer.h
 *  \brief Lightweight ring buffer, for fast insertion/deletion of bytes.
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_ModDescription Module Description
 *  Lightweight ring buffer, for fast insertion/deletion. Multiple buffers can be created of
 *  different sizes to suit different needs.
 *
 *  Note that for each buffer, insertion and removal operations may occur at the same time (via
 *  a multi-threaded ISR based system) however the same kind of operation (two or more insertions
 *  or deletions) must not overlap. If there is possibility of two or more of the same kind of
 *  operating occurring at the same point in time, atomic (mutex) locking should be used.
 *
 *  \section Sec_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      // Create the buffer structure and its underlying storage array
 *      RingBuffer_t Buffer;
 *      uint8_t      BufferData[128];
 *
 *      // Initialise the buffer with the created storage array
 *      RingBuffer_InitBuffer(&Buffer, BufferData, sizeof(BufferData));
 *
 *      // Insert some data into the buffer
 *      RingBuffer_Insert(Buffer, 'H');
 *      RingBuffer_Insert(Buffer, 'E');
 *      RingBuffer_Insert(Buffer, 'L');
 *      RingBuffer_Insert(Buffer, 'L');
 *      RingBuffer_Insert(Buffer, 'O');
 *
 *      // Cache the number of stored bytes in the buffer
 *      uint16_t BufferCount = RingBuffer_GetCount(&Buffer);
 *
 *      // Printer stored data length
 *      printf("Buffer Length: %d, Buffer Data: \r\n", BufferCount);
 *
 *      // Print contents of the buffer one character at a time
 *      while (BufferCount--)
 *        putc(RingBuffer_Remove(&Buffer));
 *  \endcode
 *
 *  @{
 */

#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

	/* Includes: */
		#include "../../Common/Common.h"

	/* Type Defines: */
		/** \brief Ring Buffer Management Structure.
		 *
		 *  Type define for a new ring buffer object. Buffers should be initialized via a call to
		 *  \ref RingBuffer_InitBuffer() before use.
		 */
		typedef struct
		{
			uint8_t* In; /**< Current storage location in the circular buffer. */
			uint8_t* Out; /**< Current retrieval location in the circular buffer. */
			uint8_t* Start; /**< Pointer to the start of the buffer's underlying storage array. */
			uint8_t* End; /**< Pointer to the end of the buffer's underlying storage array. */
			uint8_t  Size; /**< Size of the buffer's underlying storage array. */
			uint16_t Count; /**< Number of bytes currently stored in the buffer. */
		} RingBuffer_t;

	/* Inline Functions: */
		/** Initializes a ring buffer ready for use. Buffers must be initialized via this function
		 *  before any operations are called upon them. Already initialized buffers may be reset
		 *  by re-initializing them using this function.
		 *
		 *  \param[out] Buffer   Pointer to a ring buffer structure to initialize.
		 *  \param[out] DataPtr  Pointer to a global array that will hold the data stored into the ring buffer.
		 *  \param[out] Size     Maximum number of bytes that can be stored in the underlying data array.
		 */
		static inline void RingBuffer_InitBuffer(RingBuffer_t* Buffer, uint8_t* const DataPtr, const uint16_t Size)
		{
			GCC_FORCE_POINTER_ACCESS(Buffer);

			uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
			GlobalInterruptDisable();
	
			Buffer->In     = DataPtr;
			Buffer->Out    = DataPtr;
			Buffer->Start  = &DataPtr[0];
			Buffer->End    = &DataPtr[Size];
			Buffer->Size   = Size;
			Buffer->Count  = 0;

			SetGlobalInterruptMask(CurrentGlobalInt);
		}

		/** Retrieves the minimum number of bytes stored in a particular buffer. This value is computed
		 *  by entering an atomic lock on the buffer while the IN and OUT locations are fetched, so that
		 *  the buffer cannot be modified while the computation takes place. This value should be cached
		 *  when reading out the contents of the buffer, so that as small a time as possible is spent
		 *  in an atomic lock.
		 *
		 *  \note The value returned by this function is guaranteed to only be the minimum number of bytes
		 *        stored in the given buffer; this value may change as other threads write new data and so
		 *        the returned number should be used only to determine how many successive reads may safely
		 *        be performed on the buffer.
		 *
		 *  \param[in] Buffer  Pointer to a ring buffer structure whose count is to be computed.
		 */
		static inline uint16_t RingBuffer_GetCount(RingBuffer_t* const Buffer)
		{
			uint16_t Count;

			uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
			GlobalInterruptDisable();
			
			Count = Buffer->Count;

			SetGlobalInterruptMask(CurrentGlobalInt);
			return Count;
		}

		/** Atomically determines if the specified ring buffer contains any free space. This should
		 *  be tested before storing data to the buffer, to ensure that no data is lost due to a
		 *  buffer overrun.
		 *
		 *  \param[in,out] Buffer  Pointer to a ring buffer structure to insert into.
		 *
		 *  \return Boolean \c true if the buffer contains no free space, false otherwise.
		 */
		static inline bool RingBuffer_IsFull(RingBuffer_t* const Buffer)
		{
			return (RingBuffer_GetCount(Buffer) == Buffer->Size);
		}

		/** Atomically determines if the specified ring buffer contains any data. This should
		 *  be tested before removing data from the buffer, to ensure that the buffer does not
		 *  underflow.
		 *
		 *  If the data is to be removed in a loop, store the total number of bytes stored in the
		 *  buffer (via a call to the \ref RingBuffer_GetCount() function) in a temporary variable
		 *  to reduce the time spent in atomicity locks.
		 *
		 *  \param[in,out] Buffer  Pointer to a ring buffer structure to insert into.
		 *
		 *  \return Boolean \c true if the buffer contains no free space, false otherwise.
		 */
		static inline bool RingBuffer_IsEmpty(RingBuffer_t* const Buffer)
		{
			return (RingBuffer_GetCount(Buffer) == 0);
		}

		/** Inserts an element into the ring buffer.
		 *
		 *  \note Only one execution thread (main program thread or an ISR) may insert into a single buffer
		 *        otherwise data corruption may occur. Insertion and removal may occur from different execution
		 *        threads.
		 *
		 *  \param[in,out] Buffer  Pointer to a ring buffer structure to insert into.
		 *  \param[in]     Data    Data element to insert into the buffer.
		 */
		static inline void RingBuffer_Insert(RingBuffer_t* Buffer,
		                                     const uint8_t Data)
		{
			GCC_FORCE_POINTER_ACCESS(Buffer);

			*Buffer->In = Data;

			if (++Buffer->In == Buffer->End)
			  Buffer->In = Buffer->Start;

			uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
			GlobalInterruptDisable();
			
			Buffer->Count++;

			SetGlobalInterruptMask(CurrentGlobalInt);
		}

		/** Removes an element from the ring buffer.
		 *
		 *  \note Only one execution thread (main program thread or an ISR) may remove from a single buffer
		 *        otherwise data corruption may occur. Insertion and removal may occur from different execution
		 *        threads.
		 *
		 *  \param[in,out] Buffer  Pointer to a ring buffer structure to retrieve from.
		 *
		 *  \return Next data element stored in the buffer.
		 */
		static inline uint8_t RingBuffer_Remove(RingBuffer_t* Buffer)
		{
			GCC_FORCE_POINTER_ACCESS(Buffer);
		
			uint8_t Data = *Buffer->Out;

			if (++Buffer->Out == Buffer->End)
			  Buffer->Out = Buffer->Start;

			uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
			GlobalInterruptDisable();
			
			Buffer->Count--;

			SetGlobalInterruptMask(CurrentGlobalInt);

			return Data;
		}

		/** Returns the next element stored in the ring buffer, without removing it.
		 *
		 *  \param[in,out] Buffer  Pointer to a ring buffer structure to retrieve from.
		 *
		 *  \return Next data element stored in the buffer.
		 */
		static inline uint8_t RingBuffer_Peek(RingBuffer_t* const Buffer)
		{
			return *Buffer->Out;
		}

#endif

/** @} */

