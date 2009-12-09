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
 *  Header file for PDITarget.c.
 */

#ifndef _PDI_TARGET_
#define _PDI_TARGET_

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>
		
		#include <LUFA/Common/Common.h>
	
	/* Preprocessor Checks: */
		#if (BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1)
			#undef  ENABLE_ISP_PROTOCOL
			
			#if !defined(ENABLE_PDI_PROTOCOL)
				#define ENABLE_PDI_PROTOCOL
			#endif
		#endif

	/* Defines: */
		#if BOARD == BOARD_XPLAIN
			#define PDIDATA_LINE_PORT     PORTD
			#define PDIDATA_LINE_DDR      DDRD
			#define PDIDATA_LINE_PIN      PIND
			#define PDIDATA_LINE_MASK     (1 << 2)
			
			#define PDICLOCK_LINE_PORT    PORTD
			#define PDICLOCK_LINE_DDR     DDRD
			#define PDICLOCK_LINE_MASK    (1 << 5)
		#else
			#define PDIDATA_LINE_PORT     PORTB
			#define PDIDATA_LINE_DDR      DDRB
			#define PDIDATA_LINE_PIN      PINB
			#define PDIDATA_LINE_MASK     (1 << 3)
			
			#define PDICLOCK_LINE_PORT    RESET_LINE_PORT
			#define PDICLOCK_LINE_DDR     RESET_LINE_DDR
			#define PDICLOCK_LINE_MASK    RESET_LINE_MASK
		#endif
		
		#define PDI_CMD_LDS           0x00
		#define PDI_CMD_LD            0x20
		#define PDI_CMD_STS           0x40
		#define PDI_CMD_ST            0x60
		#define PDI_CMD_LDCS          0x80
		#define PDI_CMD_REPEAT        0xA0
		#define PDI_CMD_STCS          0xC0
		#define PDI_CMD_KEY           0xE0
		
		#define PD_STATUS_REG         0
		#define PD_RESET_REG          1
		#define PD_CTRL_REG           2

		#define PDI_STATUS_NVM        (1 << 1)

		#define PDI_RESET_KEY         0x59
		#define PDI_NVMENABLE_KEY     (uint8_t[]){0x12, 0x89, 0xAB, 0x45, 0xCD, 0xD8, 0x88, 0xFF}

		#define TOGGLE_PDI_CLOCK      MACROS{ PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK; \
		                                      asm volatile ("NOP" ::);                  \
		                                      PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK; \
		                                      asm volatile ("NOP" ::);                  }MACROE
		
	/* Function Prototypes: */
		void    PDITarget_SendByte(uint8_t Byte);
		uint8_t PDITarget_ReceiveByte(void);

#endif
