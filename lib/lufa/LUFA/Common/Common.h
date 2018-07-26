/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \dir
 *  \brief Common library header files.
 *
 *  This folder contains header files which are common to all parts of the LUFA library. They may be used freely in
 *  user applications.
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

/** \defgroup Group_GlobalInt Global Interrupt Macros
 *  \brief Convenience macros for the management of interrupts globally within the device.
 *
 *  Macros and functions to create and control global interrupts within the device.
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
		#include "BoardTypes.h"
		#include "ArchitectureSpecific.h"
		#include "CompilerSpecific.h"
		#include "Attributes.h"

		#if defined(USE_LUFA_CONFIG_HEADER)
			#include "LUFAConfig.h"
		#endif

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Architecture specific utility includes: */
		#if defined(__DOXYGEN__)
			/** Type define for an unsigned integer the same width as the selected architecture's machine register.
			 *  This is distinct from the non-specific standard int data type, whose width is machine dependant but
			 *  which may not reflect the actual machine register width on some targets (e.g. AVR8).
			 */
			typedef MACHINE_REG_t uint_reg_t;
		#elif (ARCH == ARCH_AVR8)
			#include <avr/io.h>
			#include <avr/interrupt.h>
			#include <avr/pgmspace.h>
			#include <avr/eeprom.h>
			#include <avr/boot.h>
			#include <math.h>
			#include <util/delay.h>

			typedef uint8_t uint_reg_t;

			#define ARCH_HAS_EEPROM_ADDRESS_SPACE
			#define ARCH_HAS_FLASH_ADDRESS_SPACE
			#define ARCH_HAS_MULTI_ADDRESS_SPACE
			#define ARCH_LITTLE_ENDIAN

			#include "Endianness.h"
		#elif (ARCH == ARCH_UC3)
			#include <avr32/io.h>
			#include <math.h>

			// === TODO: Find abstracted way to handle these ===
			#define PROGMEM
			#define pgm_read_byte(x)         *x
			#define memcmp_P(...)            memcmp(__VA_ARGS__)
			#define memcpy_P(...)            memcpy(__VA_ARGS__)
			// =================================================

			typedef uint32_t uint_reg_t;

			#define ARCH_BIG_ENDIAN

			#include "Endianness.h"
		#elif (ARCH == ARCH_XMEGA)
			#include <avr/io.h>
			#include <avr/interrupt.h>
			#include <avr/pgmspace.h>
			#include <avr/eeprom.h>
			#include <math.h>
			#include <util/delay.h>

			typedef uint8_t uint_reg_t;

			#define ARCH_HAS_EEPROM_ADDRESS_SPACE
			#define ARCH_HAS_FLASH_ADDRESS_SPACE
			#define ARCH_HAS_MULTI_ADDRESS_SPACE
			#define ARCH_LITTLE_ENDIAN

			#include "Endianness.h"
		#else
			#error Unknown device architecture specified.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#if !defined(__DOXYGEN__)
				// Obsolete, retained for compatibility with user code
				#define MACROS                  do
				#define MACROE                  while (0)
			#endif

			/** Convenience macro to determine the larger of two values.
			 *
			 *  \attention This macro should only be used with operands that do not have side effects from being evaluated
			 *             multiple times.
			 *
			 *  \param[in] x  First value to compare
			 *  \param[in] y  First value to compare
			 *
			 *  \return The larger of the two input parameters
			 */
			#if !defined(MAX) || defined(__DOXYGEN__)
				#define MAX(x, y)               (((x) > (y)) ? (x) : (y))
			#endif

			/** Convenience macro to determine the smaller of two values.
			 *
			 *  \attention This macro should only be used with operands that do not have side effects from being evaluated
			 *             multiple times.
			 *
			 *  \param[in] x  First value to compare.
			 *  \param[in] y  First value to compare.
			 *
			 *  \return The smaller of the two input parameters
			 */
			#if !defined(MIN) || defined(__DOXYGEN__)
				#define MIN(x, y)               (((x) < (y)) ? (x) : (y))
			#endif

			#if !defined(STRINGIFY) || defined(__DOXYGEN__)
				/** Converts the given input into a string, via the C Preprocessor. This macro puts literal quotation
				 *  marks around the input, converting the source into a string literal.
				 *
				 *  \param[in] x  Input to convert into a string literal.
				 *
				 *  \return String version of the input.
				 */
				#define STRINGIFY(x)            #x

				/** Converts the given input into a string after macro expansion, via the C Preprocessor. This macro puts
				 *  literal quotation marks around the expanded input, converting the source into a string literal.
				 *
				 *  \param[in] x  Input to expand and convert into a string literal.
				 *
				 *  \return String version of the expanded input.
				 */
				#define STRINGIFY_EXPANDED(x)   STRINGIFY(x)
			#endif

			#if !defined(CONCAT) || defined(__DOXYGEN__)
				/** Concatenates the given input into a single token, via the C Preprocessor.
				 *
				 *  \param[in] x  First item to concatenate.
				 *  \param[in] y  Second item to concatenate.
				 *
				 *  \return Concatenated version of the input.
				 */
				#define CONCAT(x, y)            x ## y

				/** CConcatenates the given input into a single token after macro expansion, via the C Preprocessor.
				 *
				 *  \param[in] x  First item to concatenate.
				 *  \param[in] y  Second item to concatenate.
				 *
				 *  \return Concatenated version of the expanded input.
				 */
				#define CONCAT_EXPANDED(x, y)   CONCAT(x, y)
			#endif

			#if !defined(ISR) || defined(__DOXYGEN__)
				/** Macro for the definition of interrupt service routines, so that the compiler can insert the required
				 *  prologue and epilogue code to properly manage the interrupt routine without affecting the main thread's
				 *  state with unintentional side-effects.
				 *
				 *  Interrupt handlers written using this macro may still need to be registered with the microcontroller's
				 *  Interrupt Controller (if present) before they will properly handle incoming interrupt events.
				 *
				 *  \note This macro is only supplied on some architectures, where the standard library does not include a valid
				 *        definition. If an existing definition exists, the alternative definition here will be ignored.
				 *
				 *  \ingroup Group_GlobalInt
				 *
				 *  \param[in] Name  Unique name of the interrupt service routine.
				 */
				#define ISR(Name, ...)          void Name (void) __attribute__((__interrupt__)) __VA_ARGS__; void Name (void)
			#endif

		/* Inline Functions: */
			/** Function to reverse the individual bits in a byte - i.e. bit 7 is moved to bit 0, bit 6 to bit 1,
			 *  etc.
			 *
			 *  \param[in] Byte  Byte of data whose bits are to be reversed.
			 *
			 *  \return Input data with the individual bits reversed (mirrored).
			 */
			static inline uint8_t BitReverse(uint8_t Byte) ATTR_WARN_UNUSED_RESULT ATTR_CONST;
			static inline uint8_t BitReverse(uint8_t Byte)
			{
				Byte = (((Byte & 0xF0) >> 4) | ((Byte & 0x0F) << 4));
				Byte = (((Byte & 0xCC) >> 2) | ((Byte & 0x33) << 2));
				Byte = (((Byte & 0xAA) >> 1) | ((Byte & 0x55) << 1));

				return Byte;
			}

			/** Function to perform a blocking delay for a specified number of milliseconds. The actual delay will be
			 *  at a minimum the specified number of milliseconds, however due to loop overhead and internal calculations
			 *  may be slightly higher.
			 *
			 *  \param[in] Milliseconds  Number of milliseconds to delay
			 */
			static inline void Delay_MS(uint16_t Milliseconds) ATTR_ALWAYS_INLINE;
			static inline void Delay_MS(uint16_t Milliseconds)
			{
				#if (ARCH == ARCH_AVR8)
				if (GCC_IS_COMPILE_CONST(Milliseconds))
				{
					_delay_ms(Milliseconds);
				}
				else
				{
					while (Milliseconds--)
					  _delay_ms(1);
				}
				#elif (ARCH == ARCH_UC3)
				while (Milliseconds--)
				{
					__builtin_mtsr(AVR32_COUNT, 0);
					while ((uint32_t)__builtin_mfsr(AVR32_COUNT) < (F_CPU / 1000));
				}
				#elif (ARCH == ARCH_XMEGA)
				if (GCC_IS_COMPILE_CONST(Milliseconds))
				{
					_delay_ms(Milliseconds);
				}
				else
				{
					while (Milliseconds--)
					  _delay_ms(1);
				}
				#endif
			}

			/** Retrieves a mask which contains the current state of the global interrupts for the device. This
			 *  value can be stored before altering the global interrupt enable state, before restoring the
			 *  flag(s) back to their previous values after a critical section using \ref SetGlobalInterruptMask().
			 *
			 *  \ingroup Group_GlobalInt
			 *
			 *  \return  Mask containing the current Global Interrupt Enable Mask bit(s).
			 */
			static inline uint_reg_t GetGlobalInterruptMask(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline uint_reg_t GetGlobalInterruptMask(void)
			{
				GCC_MEMORY_BARRIER();

				#if (ARCH == ARCH_AVR8)
				return SREG;
				#elif (ARCH == ARCH_UC3)
				return __builtin_mfsr(AVR32_SR);
				#elif (ARCH == ARCH_XMEGA)
				return SREG;
				#endif
			}

			/** Sets the global interrupt enable state of the microcontroller to the mask passed into the function.
			 *  This can be combined with \ref GetGlobalInterruptMask() to save and restore the Global Interrupt Enable
			 *  Mask bit(s) of the device after a critical section has completed.
			 *
			 *  \ingroup Group_GlobalInt
			 *
			 *  \param[in] GlobalIntState  Global Interrupt Enable Mask value to use
			 */
			static inline void SetGlobalInterruptMask(const uint_reg_t GlobalIntState) ATTR_ALWAYS_INLINE;
			static inline void SetGlobalInterruptMask(const uint_reg_t GlobalIntState)
			{
				GCC_MEMORY_BARRIER();

				#if (ARCH == ARCH_AVR8)
				SREG = GlobalIntState;
				#elif (ARCH == ARCH_UC3)
				if (GlobalIntState & AVR32_SR_GM)
				  __builtin_ssrf(AVR32_SR_GM_OFFSET);
				else
				  __builtin_csrf(AVR32_SR_GM_OFFSET);
				#elif (ARCH == ARCH_XMEGA)
				SREG = GlobalIntState;
				#endif

				GCC_MEMORY_BARRIER();
			}

			/** Enables global interrupt handling for the device, allowing interrupts to be handled.
			 *
			 *  \ingroup Group_GlobalInt
			 */
			static inline void GlobalInterruptEnable(void) ATTR_ALWAYS_INLINE;
			static inline void GlobalInterruptEnable(void)
			{
				GCC_MEMORY_BARRIER();

				#if (ARCH == ARCH_AVR8)
				sei();
				#elif (ARCH == ARCH_UC3)
				__builtin_csrf(AVR32_SR_GM_OFFSET);
				#elif (ARCH == ARCH_XMEGA)
				sei();
				#endif

				GCC_MEMORY_BARRIER();
			}

			/** Disabled global interrupt handling for the device, preventing interrupts from being handled.
			 *
			 *  \ingroup Group_GlobalInt
			 */
			static inline void GlobalInterruptDisable(void) ATTR_ALWAYS_INLINE;
			static inline void GlobalInterruptDisable(void)
			{
				GCC_MEMORY_BARRIER();

				#if (ARCH == ARCH_AVR8)
				cli();
				#elif (ARCH == ARCH_UC3)
				__builtin_ssrf(AVR32_SR_GM_OFFSET);
				#elif (ARCH == ARCH_XMEGA)
				cli();
				#endif

				GCC_MEMORY_BARRIER();
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

