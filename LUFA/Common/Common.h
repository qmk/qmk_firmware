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
 *  \brief Common library convenience headers, macros and functions.
 *
 *  \copydetails Group_Common
 */

/** \defgroup Group_Common Common Utility Headers - LUFA/Drivers/Common/Common.h
 *  \brief Common library convenience headers, macros and functions.
 *
 *  Common utility headers containing macros, functions, enums and types which are common to all
 *  aspects of the library.
 *
 *  @{
 */

/** \defgroup Group_Debugging Debugging Macros
 *  \brief Convenience macros to aid in debugging applications.
 *
 *  Macros to aid debugging of a user application.
 */

/** \defgroup Group_BitManip Endian and Bit Macros
 *  \brief Convenience macros to aid in bit manipulations and endianness transforms.
 *
 *  Functions for swapping endianness and reversing bit orders of data.
 */

#ifndef __LUFA_COMMON_H__
#define __LUFA_COMMON_H__

	/* Macros: */
		#if !defined(__DOXYGEN__)
			#define __INCLUDE_FROM_COMMON_H
		#endif
		
	/* Includes: */
		#include <stdint.h>
		#include <stdbool.h>
		#include <string.h>
		#include <stddef.h>
		
		#include "Architectures.h"
		#include "Attributes.h"
		#include "BoardTypes.h"
		
	/* Architecture specific utility includes: */
		#if defined(__DOXYGEN__)
			/** Type define for an unsigned integer the same width as the selected architecture's machine register. */
			typedef MACHINE_REG_t uint_reg_t;
		#elif (ARCH == ARCH_AVR8)
			#include <avr/io.h>
			#include <avr/interrupt.h>
			#include <avr/pgmspace.h>
			#include <avr/eeprom.h>
			#include <avr/boot.h>
			#include <util/atomic.h>
			#include <util/delay.h>
			
			typedef uint8_t uint_reg_t;
		#elif (ARCH == ARCH_UC3B)
			#include <avr32/io.h>

			typedef uint32_t uint_reg_t;
			
			// TODO
			#define EEMEM
			#define PROGMEM                  const
			#define ISR(Name)                void Name (void)
			#define ATOMIC_BLOCK(x)          if (1)
			#define ATOMIC_RESTORESTATE
			#define pgm_read_byte(x)         *x
			#define eeprom_read_byte(x)      *x
			#define eeprom_update_byte(x, y) *x = y
			#define eeprom_write_byte(x, y)  *x = y
			#define _delay_ms(x)
			#define memcmp_P(...)            memcmp(__VA_ARGS__)
			#define memcpy_P(...)            memcpy(__VA_ARGS__)
			
			#warning The UC3B architecture support is currently experimental and incomplete!
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Macro for encasing other multi-statement macros. This should be used along with an opening brace
			 *  before the start of any multi-statement macro, so that the macros contents as a whole are treated
			 *  as a discrete block and not as a list of separate statements which may cause problems when used as
			 *  a block (such as inline \c if statements).
			 */
			#define MACROS                  do

			/** Macro for encasing other multi-statement macros. This should be used along with a preceding closing
			 *  brace at the end of any multi-statement macro, so that the macros contents as a whole are treated
			 *  as a discrete block and not as a list of separate statements which may cause problems when used as
			 *  a block (such as inline \c if statements).
			 */
			#define MACROE                  while (0)

			/** Convenience macro to determine the larger of two values.
			 *
			 *  \note This macro should only be used with operands that do not have side effects from being evaluated
			 *        multiple times.
			 *
			 *  \param[in] x  First value to compare
			 *  \param[in] y  First value to compare
			 *
			 *  \return The larger of the two input parameters
			 */
			#if !defined(MAX) || defined(__DOXYGEN__)
				#define MAX(x, y)               ((x > y) ? x : y)
			#endif

			/** Convenience macro to determine the smaller of two values.
			 *
			 *  \note This macro should only be used with operands that do not have side effects from being evaluated
			 *        multiple times.
			 *
			 *  \param[in] x  First value to compare
			 *  \param[in] y  First value to compare
			 *
			 *  \return The smaller of the two input parameters
			 */
			#if !defined(MIN) || defined(__DOXYGEN__)
				#define MIN(x, y)               ((x < y) ? x : y)
			#endif

			#if (ARCH == ARCH_AVR8) || defined(__DOXYGEN__)
				/** Defines a volatile \c NOP statement which cannot be optimized out by the compiler, and thus can always
				 *  be set as a breakpoint in the resulting code. Useful for debugging purposes, where the optimiser
				 *  removes/reorders code to the point where break points cannot reliably be set.
				 *
				 *  \ingroup Group_Debugging
				 */
				#define JTAG_DEBUG_POINT()      __asm__ __volatile__ ("NOP" ::)

				/** Defines an explicit JTAG break point in the resulting binary via the assembly \c BREAK statement. When
				 *  a JTAG is used, this causes the program execution to halt when reached until manually resumed.
				 *
				 *  \ingroup Group_Debugging
				 */
				#define JTAG_DEBUG_BREAK()      __asm__ __volatile__ ("BREAK" ::)

				#if !defined(pgm_read_ptr) || defined(__DOXYGEN__)
					/** Reads a pointer out of PROGMEM space on the AVR8 architecture. This is currently a wrapper for the
					 *  avr-libc \c pgm_read_ptr() macro with a \c void* cast, so that its value can be assigned directly
					 *  to a pointer variable or used in pointer arithmetic without further casting in C. In a future
					 *  avr-libc distribution this will be part of the standard API and will be implemented in a more formal
					 *  manner.
					 *
					 *  \param[in] Addr  Address of the pointer to read.
					 *
					 *  \return Pointer retrieved from PROGMEM space.
					 */
					#define pgm_read_ptr(Addr)    (void*)pgm_read_word(Addr)
				#endif

				/** Macro for testing condition "x" and breaking via \ref JTAG_DEBUG_BREAK() if the condition is false.
				 *
				 *  \param[in] Condition  Condition that will be evaluated,
				 *
				 *  \ingroup Group_Debugging
				*/
				#define JTAG_DEBUG_ASSERT(Condition)    MACROS{ if (!(Condition)) { JTAG_DEBUG_BREAK(); } }MACROE

				/** Macro for testing condition "x" and writing debug data to the stdout stream if \c false. The stdout stream
				 *  must be pre-initialized before this macro is run and linked to an output device, such as the microcontroller's
				 *  USART peripheral.
				 *
				 *  The output takes the form "{FILENAME}: Function {FUNCTION NAME}, Line {LINE NUMBER}: Assertion {Condition} failed."
				 *
				 *  \param[in] Condition  Condition that will be evaluated,
				 *
				 *  \ingroup Group_Debugging
				 */
				#define STDOUT_ASSERT(Condition)        MACROS{ if (!(x)) { printf_P(PSTR("%s: Function \"%s\", Line %d: "   \
				                                                "Assertion \"%s\" failed.\r\n"),     \
				                                                __FILE__, __func__, __LINE__, #Condition); } }MACROE
			#endif
			
			/** Forces GCC to use pointer indirection (via the device's pointer register pairs) when accessing the given
			 *  struct pointer. In some cases GCC will emit non-optimal assembly code when accessing a structure through
			 *  a pointer, resulting in a larger binary. When this macro is used on a (non \c const) structure pointer before
			 *  use, it will force GCC to use pointer indirection on the elements rather than direct store and load
			 *  instructions.
			 *
			 *  \param[in, out] StructPtr  Pointer to a structure which is to be forced into indirect access mode.
			 */
			#define GCC_FORCE_POINTER_ACCESS(StructPtr) __asm__ __volatile__("" : "=b" (StructPtr) : "0" (StructPtr))

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

