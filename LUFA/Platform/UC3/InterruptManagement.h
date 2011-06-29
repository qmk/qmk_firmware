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

#ifndef _INTERRUPT_MANAGEMENT_H_
#define _INTERRUPT_MANAGEMENT_H_

	/* Includes: */
		#include <avr32/io.h>
		#include <stdbool.h>
		#include <stdint.h>

		#include <LUFA/Common/Common.h>

	/* Macros: */
		#if !defined(ISR)
			#define ISR(Name)                 void Name (void) __attribute__((__interrupt__)); void Name (void)
		#endif
		
		#define INTC_EnableInterrupts()   do { GCC_MEMORY_BARRIER(); __builtin_csrf(AVR32_SR_GM_OFFSET); } while (0)
		#define INTC_DisableInterrupts()  do { __builtin_ssrf(AVR32_SR_GM_OFFSET); GCC_MEMORY_BARRIER(); } while (0)

	/* Type Defines: */
		typedef void (*InterruptHandlerPtr_t)(void);

	/* External Variables: */
		extern const void            EVBA_Table;
		extern const uint32_t        Autovector_Table[];
		extern InterruptHandlerPtr_t InterruptHandlers[AVR32_INTC_NUM_INT_GRPS];

	/* Function Prototypes: */
		void INTC_Init(void);

	/* Inline Functions: */
		/** Registers a handler for a given interrupt group. On the AVR32 UC3 devices, interrupts are grouped by
		 *  peripheral. To save on SRAM used, a single ISR handles all interrupt lines within a single group - to
		 *  determine the exact line that has interrupted within the group ISR handler, examine the module's interrupt
		 *  flag register bits.
		 *
		 *  If multiple interrupts with the same group are registered, the last registered handler will become the
		 *  handler called for interrupts raised within that group.
		 *
		 *  \param[in] InterruptRequest  Interrupt request index for the given interrupt, a AVR32_*_IRQ mask.
		 *  \param[in] InterruptLevel    Priority level for the specified interrupt, a AVR32_INTC_INT* mask.
		 *  \param[in] Handler           Address of the ISR handler for the interrupt group.
		 */
		static inline void INTC_RegisterGroupHandler(const uint16_t InterruptRequest,
												     const uint8_t  InterruptLevel,
												     const InterruptHandlerPtr_t Handler)
		{
			uint8_t InterruptGroup = (InterruptRequest >> 5);

			InterruptHandlers[InterruptGroup] = Handler;
			AVR32_INTC.ipr[InterruptGroup]    = Autovector_Table[InterruptLevel];
		}

#endif
