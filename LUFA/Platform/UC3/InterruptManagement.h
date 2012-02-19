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
 *  \brief Interrupt Controller Driver for the AVR32 UC3 microcontrollers.
 *
 *  Interrupt controller driver for the AVR32 UC3 microcontrollers, for the configuration of interrupt
 *  handlers within the device.
 */

/** \ingroup Group_PlatformDrivers_UC3
 *  \defgroup Group_PlatformDrivers_UC3Interrupts Interrupt Controller Driver - LUFA/Platform/UC3/InterruptManagement.h
 *  \brief Interrupt Controller Driver for the AVR32 UC3 microcontrollers.
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Platform/UC3/InterruptManagement.c
 *    - LUFA/Platform/UC3/Exception.S
 *
 *  \section Sec_ModDescription Module Description
 *  Interrupt controller driver for the AVR32 UC3 microcontrollers, for the configuration of interrupt
 *  handlers within the device.
 *
 *  Usage Example:
 *  \code
 *		#include <LUFA/Platform/UC3/InterruptManagement.h>
 *
 *		ISR(USB_Group_IRQ_Handler)
 *		{
 *			// USB group handler code here
 *		}
 *
 *		void main(void)
 *		{
 *			INTC_Init();
 *			INTC_RegisterGroupHandler(INTC_IRQ_GROUP(AVR32_USBB_IRQ), AVR32_INTC_INT0, USB_Group_IRQ_Handler);
 *		}
 *  \endcode
 *
 *  @{
 */

#ifndef _UC3_INTERRUPT_MANAGEMENT_H_
#define _UC3_INTERRUPT_MANAGEMENT_H_

	/* Includes: */
		#include <LUFA/Common/Common.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Type Defines: */
			typedef void (*InterruptHandlerPtr_t)(void);

		/* External Variables: */
			#if defined(__INCLUDE_FROM_INTMANAGEMENT_C)
				extern const void        EVBA_Table;
			#endif
			extern InterruptHandlerPtr_t InterruptHandlers[AVR32_INTC_NUM_INT_GRPS];
			extern const uint32_t        Autovector_Table[];
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Converts a given interrupt index into its assocated interrupt group.
			 *
			 *  \param[in] IRQIndex  Index of the interrupt request to convert.
			 *
			 *  \return Interrupt group number associated with the interrupt index.
			 */
			#define INTC_IRQ_GROUP(IRQIndex)  (IRQIndex / 32)

			/** Converts a given interrupt index into its assocated interrupt line.
			 *
			 *  \param[in] IRQIndex  Index of the interrupt request to convert.
			 *
			 *  \return Interrupt line number associated with the interrupt index.
			 */
			#define INTC_IRQ_LINE(IRQIndex)   (IRQIndex % 32)

		/* Function Prototypes: */
			/** Initializes the interrupt controller, nulling out all interrupt handlers ready for new registration. This
			 *  function should be called once on startup to ensure the interrupt controller is ready for use.
			 */
			void INTC_Init(void);

		/* Inline Functions: */
			/** Registers a handler for a given interrupt group. On the AVR32 UC3 devices, interrupts are grouped by
			 *  peripheral. To save on SRAM used, a single ISR handles all interrupt lines within a single group - to
			 *  determine the exact line that has interrupted within the group ISR handler, use \ref INTC_GetGroupInterrupts().
			 *
			 *  If multiple interrupts with the same group are registered, the last registered handler will become the
			 *  handler called for interrupts raised within that group.
			 *
			 *  To obtain the group number of a specific interrupt index, use the \ref INTC_IRQ_GROUP() macro.
			 *
			 *  \param[in] GroupNumber       Group number of the interrupt group to register a handler for.
			 *  \param[in] InterruptLevel    Priority level for the specified interrupt, a \c AVR32_INTC_INT* mask.
			 *  \param[in] Handler           Address of the ISR handler for the interrupt group.
			 */
			static inline void INTC_RegisterGroupHandler(const uint16_t GroupNumber,
			                                             const uint8_t InterruptLevel,
			                                             const InterruptHandlerPtr_t Handler) ATTR_ALWAYS_INLINE;
			static inline void INTC_RegisterGroupHandler(const uint16_t GroupNumber,
			                                             const uint8_t InterruptLevel,
			                                             const InterruptHandlerPtr_t Handler)
			{
				InterruptHandlers[GroupNumber] = Handler;
				AVR32_INTC.ipr[GroupNumber]    = Autovector_Table[InterruptLevel];
			}

			/** Retrieves the pending interrupts for a given interrupt group. The result of this function should be masked
			 *  against interrupt request indexes converted to a request line number via the \ref INTC_IRQ_LINE() macro. To
			 *  obtain the group number of a given interrupt request, use the \ref INTC_IRQ_GROUP() macro.
			 *
			 *  \param[in] GroupNumber Group number of the interrupt group to check.
			 *
			 *  \return Mask of pending interrupt lines for the given interrupt group.
			 */
			static inline uint_reg_t INTC_GetGroupInterrupts(const uint16_t GroupNumber) ATTR_ALWAYS_INLINE;
			static inline uint_reg_t INTC_GetGroupInterrupts(const uint16_t GroupNumber)
			{
				return AVR32_INTC.irr[GroupNumber];
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

