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
 *  \brief Common library convenience macros and functions.
 *
 *  This file contains macros which are common to all library elements, and which may be useful in user code. It
 *  also includes other common headers, such as Atomic.h, Attributes.h and BoardTypes.h.
 */
 
/** @defgroup Group_Common Common Utility Headers - LUFA/Drivers/Common/Common.h
 *
 *  Common utility headers containing macros, functions, enums and types which are common to all
 *  aspects of the library.
 *
 *  @{
 */

/** @defgroup Group_Debugging Debugging Macros
 *
 *  Macros for debugging use.
 */
 
/** @defgroup Group_BitManip Endian and Bit Macros
 *
 *  Functions for swapping endianness and reversing bit orders.
 */

#ifndef __COMMON_H__
#define __COMMON_H__

	/* Includes: */
		#include <stdint.h>
		#include <stdbool.h>
	
		#include "Attributes.h"
		#include "BoardTypes.h"

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Macro for encasing other multi-statement macros. This should be used along with an opening brace
			 *  before the start of any multi-statement macro, so that the macros contents as a whole are treated
			 *  as a discrete block and not as a list of separate statements which may cause problems when used as
			 *  a block (such as inline IF statements).
			 */
			#define MACROS                  do

			/** Macro for encasing other multi-statement macros. This should be used along with a preceding closing
			 *  brace at the end of any multi-statement macro, so that the macros contents as a whole are treated
			 *  as a discrete block and not as a list of separate statements which may cause problems when used as
			 *  a block (such as inline IF statements).
			 */
			#define MACROE                  while (0)
			
			/** Defines a volatile NOP statement which cannot be optimized out by the compiler, and thus can always
			 *  be set as a breakpoint in the resulting code. Useful for debugging purposes, where the optimiser
			 *  removes/reorders code to the point where break points cannot reliably be set.
			 *
			 *  \ingroup Group_Debugging
			 */
			#define JTAG_DEBUG_POINT()      asm volatile ("NOP" ::)

			/** Defines an explicit JTAG break point in the resulting binary via the ASM BREAK statement. When
			 *  a JTAG is used, this causes the program execution to halt when reached until manually resumed.
			 *
			 *  \ingroup Group_Debugging
			 */
			#define JTAG_DEBUG_BREAK()      asm volatile ("BREAK" ::)
			
			/** Macro for testing condition "x" and breaking via JTAG_DEBUG_BREAK() if the condition is false.
			 *
			 *  \ingroup Group_Debugging
			*/
			#define JTAG_DEBUG_ASSERT(x)    MACROS{ if (!(x)) { JTAG_DEBUG_BREAK(); } }MACROE

			/** Macro for testing condition "x" and writing debug data to the stdout stream if false. The stdout stream
			 *  must be pre-initialized before this macro is run and linked to an output device, such as the AVR's USART
			 *  peripheral.
			 *
			 *  The output takes the form "{FILENAME}: Function {FUNCTION NAME}, Line {LINE NUMBER}: Assertion {x} failed."
			 *
			 *  \ingroup Group_Debugging
			 */
			#define STDOUT_ASSERT(x)        MACROS{ if (!(x)) { printf_P(PSTR("%s: Function \"%s\", Line %d: "   \
			                                             "Assertion \"%s\" failed.\r\n"),     \
			                                             __FILE__, __func__, __LINE__, #x); } }MACROE

			#if !defined(pgm_read_ptr) || defined(__DOXYGEN__)
				/** Reads a pointer out of PROGMEM space. This is currently a wrapper for the avr-libc pgm_read_ptr()
				 *  macro with a void* cast, so that its value can be assigned directly to a pointer variable or used
				 *  in pointer arithmetic without further casting in C. In a future avr-libc distribution this will be
				 *  part of the standard API and will be implemented in a more formal manner.
				 *
				 *  \param[in] Addr  Address of the pointer to read.
				 *
				 *  \return Pointer retrieved from PROGMEM space.
				 */
				#define pgm_read_ptr(Addr)    (void*)pgm_read_word(Addr)
			#endif

			/** Swaps the byte ordering of a 16-bit value at compile time. Do not use this macro for swapping byte orderings
			 *  of dynamic values computed at runtime, use \ref SwapEndian_16() instead. The result of this macro can be used
			 *  inside struct or other variable initializers outside of a function, something that is not possible with the
			 *  inline function variant.
			 *
			 *  \param[in]  x  16-bit value whose byte ordering is to be swapped.
			 *
			 *  \return Input value with the byte ordering reversed.
			 */
			#define SWAPENDIAN_16(x)          ((((x) & 0xFF00) >> 8) | (((x) & 0x00FF) << 8))

			/** Swaps the byte ordering of a 32-bit value at compile time. Do not use this macro for swapping byte orderings
			 *  of dynamic values computed at runtime- use \ref SwapEndian_32() instead. The result of this macro can be used
			 *  inside struct or other variable initializers outside of a function, something that is not possible with the
			 *  inline function variant.
			 *
			 *  \param[in]  x  32-bit value whose byte ordering is to be swapped.
			 *
			 *  \return Input value with the byte ordering reversed.
			 */
			#define SWAPENDIAN_32(x)          ((((x) & 0xFF000000UL) >> 24UL) | (((x) & 0x00FF0000UL) >> 8UL) | \
			                                   (((x) & 0x0000FF00UL) << 8UL)  | (((x) & 0x000000FFUL) << 24UL))

		/* Inline Functions: */
			/** Function to reverse the individual bits in a byte - i.e. bit 7 is moved to bit 0, bit 6 to bit 1,
			 *  etc.
			 *
			 *  \ingroup Group_BitManip
			 *
			 *  \param[in] Byte  Byte of data whose bits are to be reversed.
			 */
			static inline uint8_t BitReverse(uint8_t Byte) ATTR_WARN_UNUSED_RESULT ATTR_CONST;
			static inline uint8_t BitReverse(uint8_t Byte)
			{
				Byte = (((Byte & 0xF0) >> 4) | ((Byte & 0x0F) << 4));
				Byte = (((Byte & 0xCC) >> 2) | ((Byte & 0x33) << 2));
				Byte = (((Byte & 0xAA) >> 1) | ((Byte & 0x55) << 1));

				return Byte;
			}
			
			/** Function to reverse the byte ordering of the individual bytes in a 16 bit number.
			 *
			 *  \ingroup Group_BitManip
			 *
			 *  \param[in] Word  Word of data whose bytes are to be swapped.
			 */
			static inline uint16_t SwapEndian_16(const uint16_t Word) ATTR_WARN_UNUSED_RESULT ATTR_CONST;
			static inline uint16_t SwapEndian_16(const uint16_t Word)
			{
				uint8_t Temp;

				union
				{
					uint16_t Word;
					uint8_t  Bytes[2];
				} Data;
				
				Data.Word = Word;
				
				Temp = Data.Bytes[0];
				Data.Bytes[0] = Data.Bytes[1];
				Data.Bytes[1] = Temp;
				
				return Data.Word;
			}

			/** Function to reverse the byte ordering of the individual bytes in a 32 bit number.
			 *
			 *  \ingroup Group_BitManip
			 *
			 *  \param[in] DWord  Double word of data whose bytes are to be swapped.
			 */
			static inline uint32_t SwapEndian_32(const uint32_t DWord) ATTR_WARN_UNUSED_RESULT ATTR_CONST;
			static inline uint32_t SwapEndian_32(const uint32_t DWord)
			{
				uint8_t Temp;

				union
				{
					uint32_t DWord;
					uint8_t  Bytes[4];
				} Data;
				
				Data.DWord = DWord;
				
				Temp = Data.Bytes[0];
				Data.Bytes[0] = Data.Bytes[3];
				Data.Bytes[3] = Temp;
				
				Temp = Data.Bytes[1];
				Data.Bytes[1] = Data.Bytes[2];
				Data.Bytes[2] = Temp;
				
				return Data.DWord;
			}

			/** Function to reverse the byte ordering of the individual bytes in a n byte number.
			 *
			 *  \ingroup Group_BitManip
			 *
			 *  \param[in,out] Data   Pointer to a number containing an even number of bytes to be reversed.
			 *  \param[in]     Bytes  Length of the data in bytes.
			 */
			static inline void SwapEndian_n(void* Data,
			                                uint8_t Bytes) ATTR_NON_NULL_PTR_ARG(1);
			static inline void SwapEndian_n(void* Data,
			                                uint8_t Bytes)
			{
				uint8_t* CurrDataPos = (uint8_t*)Data;
			
				while (Bytes > 1)
				{
					uint8_t Temp = *CurrDataPos;
					*CurrDataPos = *(CurrDataPos + Bytes - 1);
					*(CurrDataPos + Bytes - 1) = Temp;

					CurrDataPos++;
					Bytes -= 2;
				}
			}

#endif

/** @} */
