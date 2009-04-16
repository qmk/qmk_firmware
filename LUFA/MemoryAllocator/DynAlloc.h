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

/** \file
 *
 *  Dynamic, auto-defragmenting block memory allocator library. This library provides a convenient replacement for
 *  the standard avr-libc dynamic memory allocation routines. Memory is handed out in block chunks, to reduce the
 *  management memory overhead.
 *
 *  Unlike the normal memory allocation routines, this library gives out handles to memory which must be dereferenced
 *  at the exact time of use, rather than handing back direct memory pointers. By using library managed handles
 *  instead of pointers, allocated memory blocks can be shifted around as needed transparently to defragment the
 *  memory as more blocks are requested.
 *
 *  The memory heap is static, thus the total memory usage of the compiled application (as reported by the avr-size
 *  tool of the AVR-GCC toolchain) includes the dynamic memory heap.
 *
 *  The constants NUM_BLOCKS, BLOCK_SIZE and NUM_HANDLES must be defined in the project makefile (and passed to the
 *  preprocessor via the -D GCC switch) for this library to compile.
 *
 *  NUM_BLOCKS indicates the number of memory blocks in the memory psudoheap which can be chained together and handed
 *  to the application via a memory handle. NUM_HANDLES is the maximum number of memory handles (pointing to one or
 *  more chained memory blocks) which can be handed out simultaneously before requiring a handle (and its associated
 *  memory) to be freed. BLOCK_SIZE gives the number of bytes in each memory block.
 */

/** @defgroup Group_MemoryAllocator Dynamic Block Memory Allocator - LUFA/MemoryAllocator/DynAlloc.h
 *
 *  Dynamic auto-degragmenting memory block allocator functions. See DynAlloc.h description for more details.
 *
 *  @{
 */

#ifndef __DYN_ALLOC__
#define __DYN_ALLOC__

	/* Includes : */
		#include <avr/io.h>
		#include <stdbool.h>
		#include <string.h>
	
	/* Preprocessor Checks: */
		#if (!defined(NUM_BLOCKS) || !defined(BLOCK_SIZE) || !defined(NUM_HANDLES))
			#error NUM_BLOCKS, BLOCK_SIZE and NUM_HANDLES must be defined before use via makefile.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Macro to dereference a given memory handle into the given type. The given type should be a pointer
			 *  if the memory is to contain an array of items, or should be a standard type (such as a primitive or
			 *  structure) if the memory is to hold a single item of a single type. */
			#define DEREF(handle, type)       (*(type*)handle)
			
			/** Constant, giving the total heap size in bytes. */
			#define ALLOCABLE_BYTES           (1UL * NUM_BLOCKS * BLOCK_SIZE)
		
		/* Type Defines: */
			/** Memory handle type, used to store handles given by the library functions. */
			typedef const void** Mem_Handle_t;
			
			#if (ALLOCABLE_BYTES > 0xFFFF) || defined(__DOXYGEN__)
				/** Type define for the size (in bytes) for an allocation for passing to the library functions.
				 *  The exact type width varies depending on the value of ALLOCABLE_BYTES to ensure that a single
				 *  allocation can request the entire heap if needed.
				 */
				typedef uint32_t Alloc_Size_t;
			#elif (ALLOCABLE_BYTES > 0xFF)
				typedef uint16_t Alloc_Size_t;
			#else			
				typedef uint8_t  Alloc_Size_t;
			#endif

			#if (NUM_BLOCKS > 0xFFFF) || defined(__DOXYGEN__)
				/** Type define for a block number in the heap. The exact type width varies depending on the
				 *   value of NUM_BLOCKS to ensure that the type can store an index to any block in the block pool.
				 */
				typedef uint32_t Block_Number_t;
			#elif (NUM_BLOCKS > 0xFF)
				typedef uint16_t Block_Number_t;
			#else
				typedef uint8_t  Block_Number_t;
			#endif

			#if (NUM_HANDLES > 0xFFFF) || defined(__DOXYGEN__)
				/** Type define for a handle number. The exact type width varies depending on the value of NUM_HANDLES
				 *  to ensure that the type can store the index of any handle in the handle pool.
				 */
				typedef uint32_t Handle_Number_t;
			#elif (NUM_HANDLES > 0xFF)
				typedef uint16_t Handle_Number_t;
			#else			
				typedef uint8_t  Handle_Number_t;
			#endif
			
		/* Function Prototypes: */
			/** Allocates a given number of blocks from the heap (calculated from the requested number of bytes) and
			 *  returns a handle to the newly allocated memory.
			 *
			 *  \param Bytes  The number of bytes requested to be allocated from the heap
			 *
			 *  \return NULL handle if the allocation fails, or handle to the allocated memory if the allocation succeeds
			 */
			Mem_Handle_t    Mem_Alloc(const Alloc_Size_t Bytes);
			
			/** Allocates a given number of blocks from the heap (calculated from the requested number of bytes) and
			 *  returns a handle to the newly allocated memory. Calloced memory is automatically cleared to all 0x00
			 *  values at the time of allocation.
			 *
			 *  \param Bytes  The number of pre-cleared bytes requested to be allocated from the heap
			 *
			 *  \return NULL handle if the allocation fails, or handle to the allocated memory if the allocation succeeds
			 */
			Mem_Handle_t    Mem_Calloc(const Alloc_Size_t Bytes);

			/** Deallocates a given memory handle, and attempts to allocates the given number of blocks from the heap
			 *  (calculated from the requested number of bytes) immediately following the deallocation. The new memory
			 *  may be located in the same area as the previous memory, but this is not guaranteed.
			 *
			 *  \param CurrAllocHdl  Handle to an already allocated section of memory in the heap to deallocate
			 *  \param Bytes         The number of bytes requested to be allocated from the heap following the
			 *                       deallocation
			 *
			 *  \return NULL handle if the allocation fails, or handle to the allocated memory if the allocation succeeds
			 *
			 *  \warning Even if the allocation fails, the deallocation will still occur. Care should be taken to ensure
			 *           that the previously allocated memory is not used following an unsuccessful realloc().
			 */
			Mem_Handle_t    Mem_Realloc(Mem_Handle_t CurrAllocHdl, const Alloc_Size_t Bytes);
			
			/** Deallocates a given previously allocated section of memory from the heap.
			 *
			 *  \param CurrAllocHdl  Handle to a previously allocated section of memory in the heap
			 */
			void            Mem_Free(Mem_Handle_t CurrAllocHdl);
			
			/** Returns the total number of unallocated blocks in the heap.
			 *
			 *  \return Number of free blocks in the heap, as a Block_Number_t integer
			 */
			Block_Number_t  Mem_TotalFreeBlocks(void);

			/** Returns the total number of unallocated handles in the handle pool.
			 *
			 *  \return Number of free handles in the handle pool, as a Handle_Number_t integer
			 */
			Handle_Number_t Mem_TotalFreeHandles(void);
		
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define BLOCK_USED_MASK           (1 << 0)
			#define BLOCK_LINKED_MASK         (1 << 1)
			
		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_DYNALLOC_C)
				static uint8_t Mem_GetBlockFlags(const Block_Number_t BlockNum);
				static void    Mem_SetBlockFlags(const Block_Number_t BlockNum, const uint8_t Flags);
				static void    Mem_Defrag(void);
			#endif
	#endif
	
#endif

/** @} */
