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
 *  \brief Special function/variable attribute macros.
 *
 *  \copydetails Group_FuncVarAttributes
 *
 *  \note Do not include this file directly, rather include the Common.h header file instead to gain this file's
 *        functionality.
 */

/** \ingroup Group_Common
 *  \defgroup Group_FuncVarAttributes Function/Variable Attributes
 *  \brief Special function/variable attribute macros.
 *
 *  This module contains macros for applying specific attributes to functions and variables to control various
 *  optimizer and code generation features of the compiler. Attributes may be placed in the function prototype
 *  or variable declaration in any order, and multiple attributes can be specified for a single item via a space
 *  separated list.
 *
 *  On incompatible versions of GCC or on other compilers, these macros evaluate to nothing unless they are
 *  critical to the code's function and thus must throw a compile error when used.
 *
 *  @{
 */

#ifndef __LUFA_FUNCATTR_H__
#define __LUFA_FUNCATTR_H__

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_COMMON_H)
			#error Do not include this file directly. Include LUFA/Common/Common.h instead to gain this functionality.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#if (__GNUC__ >= 3) || defined(__DOXYGEN__)
				/** Indicates to the compiler that the function can not ever return, so that any stack restoring or
				 *  return code may be omitted by the compiler in the resulting binary.
				 */
				#define ATTR_NO_RETURN              __attribute__ ((noreturn))

				/** Indicates that the function returns a value which should not be ignored by the user code. When
				 *  applied, any ignored return value from calling the function will produce a compiler warning.
				 */
				#define ATTR_WARN_UNUSED_RESULT     __attribute__ ((warn_unused_result))

				/** Indicates that the specified parameters of the function are pointers which should never be \c NULL.
				 *  When applied as a 1-based comma separated list the compiler will emit a warning if the specified
				 *  parameters are known at compiler time to be \c NULL at the point of calling the function.
				 */
				#define ATTR_NON_NULL_PTR_ARG(...)  __attribute__ ((nonnull (__VA_ARGS__)))

				/** Removes any preamble or postamble from the function. When used, the function will not have any
				 *  register or stack saving code. This should be used with caution, and when used the programmer
				 *  is responsible for maintaining stack and register integrity.
				 */
				#define ATTR_NAKED                  __attribute__ ((naked))

				/** Prevents the compiler from considering a specified function for in-lining. When applied, the given
				 *  function will not be in-lined under any circumstances.
				 */
				#define ATTR_NO_INLINE              __attribute__ ((noinline))

				/** Forces the compiler to inline the specified function. When applied, the given function will be
				 *  in-lined under all circumstances.
				 */
				#define ATTR_ALWAYS_INLINE          __attribute__ ((always_inline))

				/** Indicates that the specified function is pure, in that it has no side-effects other than global
				 *  or parameter variable access.
				 */
				#define ATTR_PURE                   __attribute__ ((pure))

				/** Indicates that the specified function is constant, in that it has no side effects other than
				 *  parameter access.
				 */
				#define ATTR_CONST                  __attribute__ ((const))

				/** Marks a given function as deprecated, which produces a warning if the function is called. */
				#define ATTR_DEPRECATED             __attribute__ ((deprecated))

				/** Marks a function as a weak reference, which can be overridden by other functions with an
				 *  identical name (in which case the weak reference is discarded at link time).
				 */
				#define ATTR_WEAK                   __attribute__ ((weak))
			#endif

			/** Forces the compiler to not automatically zero the given global variable on startup, so that the
			 *  current RAM contents is retained. Under most conditions this value will be random due to the
			 *  behaviour of volatile memory once power is removed, but may be used in some specific circumstances,
			 *  like the passing of values back after a system watchdog reset.
			 */
			#define ATTR_NO_INIT                    __attribute__ ((section (".noinit")))

			/** Places the function in one of the initialization sections, which execute before the main function
			 *  of the application. Refer to the avr-libc manual for more information on the initialization sections.
			 *
			 *  \param[in] SectionIndex  Initialization section number where the function should be placed.
			 */
			#define ATTR_INIT_SECTION(SectionIndex) __attribute__ ((used, naked, section (".init" #SectionIndex )))

			/** Marks a function as an alias for another function.
			 *
			 *  \param[in] Func  Name of the function which the given function name should alias.
			 */
			#define ATTR_ALIAS(Func)               __attribute__ ((alias( #Func )))

			/** Marks a variable or struct element for packing into the smallest space available, omitting any
			 *  alignment bytes usually added between fields to optimize field accesses.
			 */
			#define ATTR_PACKED                     __attribute__ ((packed))

			/** Indicates the minimum alignment in bytes for a variable or struct element.
			 *
			 *  \param[in] Bytes  Minimum number of bytes the item should be aligned to.
			 */
			#define ATTR_ALIGNED(Bytes)            __attribute__ ((aligned(Bytes)))
#endif

/** @} */

