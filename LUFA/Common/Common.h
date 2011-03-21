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

#ifndef __LUFA_COMMON_H__
#define __LUFA_COMMON_H__

	/* Macros: */
		#define __INCLUDE_FROM_COMMON_H
		
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
			
			#define ARCH_HAS_EEPROM_ADDRESS_SPACE
			#define ARCH_HAS_FLASH_ADDRESS_SPACE
			#define ARCH_HAS_MULTI_ADDRESS_SPACE
			#define ARCH_LITTLE_ENDIAN

			#include "Endianness.h"
		#elif (ARCH == ARCH_UC3)
			#include <avr32/io.h>

			// === TODO: Find abstracted way to handle these ===
			#define ISR(Name)                void Name (void) __attribute__((__interrupt__)); void Name (void)
			#define PROGMEM                  const
			#define ATOMIC_BLOCK(x)          if (1)
			#define ATOMIC_RESTORESTATE
			#define pgm_read_byte(x)         *x
			#define _delay_ms(x)
			#define memcmp_P(...)            memcmp(__VA_ARGS__)
			#define memcpy_P(...)            memcpy(__VA_ARGS__)
			// ==================================================

			typedef uint32_t uint_reg_t;
			
			#define  ARCH_BIG_ENDIAN

			#include "Endianness.h"
		#else
			#error Unknown device architecture specified.
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

			/** Forces GCC to create a memory barrier, ensuring that memory accesses are not reordered past the barrier point.
			 *  This can be used before ordering-critical operations, to ensure that the compiler does not re-order the resulting
			 *  assembly output in an unexpected manner on sections of code that are ordering-specific.
			 */
			#define GCC_MEMORY_BARRIER()                __asm__ __volatile__("" ::: "memory");

		/* Inline Functions: */
			/** Function to reverse the individual bits in a byte - i.e. bit 7 is moved to bit 0, bit 6 to bit 1,
			 *  etc.
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

#endif

/** @} */

