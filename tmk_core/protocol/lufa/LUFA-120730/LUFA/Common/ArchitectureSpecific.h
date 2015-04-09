/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Architecture specific definitions relating to specific processor architectures.
 *
 *  \copydetails Group_ArchitectureSpecific
 *
 *  \note Do not include this file directly, rather include the Common.h header file instead to gain this file's
 *        functionality.
 */

/** \ingroup Group_Common
 *  \defgroup Group_ArchitectureSpecific Architecture Specific Definitions
 *  \brief Architecture specific definitions relating to specific processor architectures.
 *
 *  Architecture specific macros, functions and other definitions, which relate to specific architectures. This
 *  definitions may or may not be available in some form on other architectures, and thus should be protected by
 *  preprocessor checks in portable code to prevent compile errors.
 *
 *  @{
 */

#ifndef __LUFA_ARCHSPEC_H__
#define __LUFA_ARCHSPEC_H__

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_COMMON_H)
			#error Do not include this file directly. Include LUFA/Common/Common.h instead to gain this functionality.
		#endif

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#if (ARCH == ARCH_AVR8) || (ARCH == ARCH_XMEGA) || defined(__DOXYGEN__)
				#if (ARCH == ARCH_AVR8) || defined(__DOXYGEN__)
					/** Re-enables the AVR's JTAG bus in software, until a system reset. This will re-enable JTAG debugging
					 *  interface after is has been disabled in software via \ref JTAG_DISABLE().
					 *
					 *  \note This macro is not available for all architectures.
					 */
					#define JTAG_ENABLE()                  MACROS{                                      \
																	__asm__ __volatile__ (               \
																	"in __tmp_reg__,__SREG__" "\n\t"     \
																	"cli" "\n\t"                         \
																	"out %1, %0" "\n\t"                  \
																	"out __SREG__, __tmp_reg__" "\n\t"   \
																	"out %1, %0" "\n\t"                  \
																	:                                    \
																	: "r" (MCUCR & ~(1 << JTD)),         \
																	  "M" (_SFR_IO_ADDR(MCUCR))          \
																	: "r0");                             \
															}MACROE

					/** Disables the AVR's JTAG bus in software, until a system reset. This will override the current JTAG
					 *  status as set by the JTAGEN fuse, disabling JTAG debugging and reverting the JTAG pins back to GPIO
					 *  mode.
					 *
					 *  \note This macro is not available for all architectures.
					 */
					#define JTAG_DISABLE()                  MACROS{                                      \
																	__asm__ __volatile__ (               \
																	"in __tmp_reg__,__SREG__" "\n\t"     \
																	"cli" "\n\t"                         \
																	"out %1, %0" "\n\t"                  \
																	"out __SREG__, __tmp_reg__" "\n\t"   \
																	"out %1, %0" "\n\t"                  \
																	:                                    \
																	: "r" (MCUCR | (1 << JTD)),          \
																	  "M" (_SFR_IO_ADDR(MCUCR))          \
																	: "r0");                             \
															}MACROE
				#endif

				/** Defines a volatile \c NOP statement which cannot be optimized out by the compiler, and thus can always
				 *  be set as a breakpoint in the resulting code. Useful for debugging purposes, where the optimizer
				 *  removes/reorders code to the point where break points cannot reliably be set.
				 *
				 *  \note This macro is not available for all architectures.
				 */
				#define JTAG_DEBUG_POINT()              __asm__ __volatile__ ("nop" ::)

				/** Defines an explicit JTAG break point in the resulting binary via the assembly \c BREAK statement. When
				 *  a JTAG is used, this causes the program execution to halt when reached until manually resumed.
				 *
				 *  \note This macro is not available for all architectures.
				 */
				#define JTAG_DEBUG_BREAK()              __asm__ __volatile__ ("break" ::)

				/** Macro for testing condition "x" and breaking via \ref JTAG_DEBUG_BREAK() if the condition is false.
				 *
				 *  \note This macro is not available for all architectures.
				 *
				 *  \param[in] Condition  Condition that will be evaluated.
				*/
				#define JTAG_ASSERT(Condition)          MACROS{ if (!(Condition)) { JTAG_DEBUG_BREAK(); } }MACROE

				/** Macro for testing condition \c "x" and writing debug data to the stdout stream if \c false. The stdout stream
				 *  must be pre-initialized before this macro is run and linked to an output device, such as the microcontroller's
				 *  USART peripheral.
				 *
				 *  The output takes the form "{FILENAME}: Function {FUNCTION NAME}, Line {LINE NUMBER}: Assertion {Condition} failed."
				 *
				 *  \note This macro is not available for all architectures.
				 *
				 *  \param[in] Condition  Condition that will be evaluated,
				 */
				#define STDOUT_ASSERT(Condition)        MACROS{ if (!(x)) {                                             \
				                                                     printf_P(PSTR("%s: Function \"%s\", Line %d: "     \
				                                                                   "Assertion \"%s\" failed.\r\n"),     \
				                                                                   __FILE__, __func__, __LINE__, #Condition); } }MACROE

				#if !defined(pgm_read_ptr) || defined(__DOXYGEN__)
					/** Reads a pointer out of PROGMEM space on the AVR8 architecture. This is currently a wrapper for the
					 *  avr-libc \c pgm_read_ptr() macro with a \c void* cast, so that its value can be assigned directly
					 *  to a pointer variable or used in pointer arithmetic without further casting in C. In a future
					 *  avr-libc distribution this will be part of the standard API and will be implemented in a more formal
					 *  manner.
					 *
					 *  \note This macro is not available for all architectures.
					 *
					 *  \param[in] Address  Address of the pointer to read.
					 *
					 *  \return Pointer retrieved from PROGMEM space.
					 */
					#define pgm_read_ptr(Address)        (void*)pgm_read_word(Address)
				#endif
			#elif (ARCH == ARCH_UC3)
				#define JTAG_DEBUG_POINT()              __asm__ __volatile__ ("nop" ::)
				#define JTAG_DEBUG_BREAK()              __asm__ __volatile__ ("breakpoint" ::)
				#define JTAG_ASSERT(Condition)          MACROS{ if (!(Condition)) { JTAG_DEBUG_BREAK(); } }MACROE
				#define STDOUT_ASSERT(Condition)        MACROS{ if (!(x)) {                                      \
				                                                     printf("%s: Function \"%s\", Line %d: "     \
				                                                            "Assertion \"%s\" failed.\r\n"),     \
				                                                            __FILE__, __func__, __LINE__, #Condition); } }MACROE
			#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

