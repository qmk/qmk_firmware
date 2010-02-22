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
 *  Atomic block header for the 32-bit AVRs, modelled on the 8-bit AVR's util/atomic.h
 *  header.
 *
 *  \note Do not include this file directly, rather include the Common.h header file instead to gain this file's
 *        functionality on the 32-bit AVRs.
 */

#ifndef __ATOMIC_H__
#define __ATOMIC_H__

	/* Includes: */
		#include <avr32/io.h>
		#include <stdint.h>
		#include <stdbool.h>

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#define ATOMIC_BLOCK(type) for ( type, __ToDo = __iCliRetVal(); \
									   __ToDo ; __ToDo = 0 )
			#define NONATOMIC_BLOCK(type) for ( type, __ToDo = __iSeiRetVal(); \
										  __ToDo ;  __ToDo = 0 )
			#define ATOMIC_RESTORESTATE uint8_t sreg_save \
				__attribute__((__cleanup__(__iRestore))) = 0 /* TODO */
			#define ATOMIC_FORCEON uint8_t sreg_save \
				__attribute__((__cleanup__(__iSeiParam))) = 0
			#define NONATOMIC_RESTORESTATE uint8_t sreg_save \
				__attribute__((__cleanup__(__iRestore))) = 0 /* TODO */
			#define NONATOMIC_FORCEOFF uint8_t sreg_save \
				__attribute__((__cleanup__(__iCliParam))) = 0

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Inline Functions: */
			static __inline__ uint8_t __iSeiRetVal(void)
			{
				((avr32_sr_t*)AVR32_SR_T)->gm = true;
				return 1;
			}

			static __inline__ uint8_t __iCliRetVal(void)
			{
				((avr32_sr_t*)AVR32_SR_T)->gm = false;
				return 1;
			}

			static __inline__ void __iSeiParam(const uint8_t *__s)
			{
				((avr32_sr_t*)AVR32_SR_T)->gm = true;
				__asm__ volatile ("" ::: "memory");
				(void)__s;
			}

			static __inline__ void __iCliParam(const uint8_t *__s)
			{
				((avr32_sr_t*)AVR32_SR_T)->gm = false;
				__asm__ volatile ("" ::: "memory");
				(void)__s;
			}

			static __inline__ void __iRestore(const uint8_t *__s)
			{
				((avr32_sr_t*)AVR32_SR_T)->gm = *__s;
				__asm__ volatile ("" ::: "memory");
			}
	#endif

#endif
