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
 *  Header file for TPITarget.c.
 */

#ifndef _TPI_TARGET_
#define _TPI_TARGET_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>
		
		#include <LUFA/Common/Common.h>
	
	/* Preprocessor Checks: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#undef ENABLE_ISP_PROTOCOL
			#undef ENABLE_TPI_PROTOCOL
			
			#if !defined(ENABLE_PDI_PROTOCOL)
				#define ENABLE_PDI_PROTOCOL
			#endif
		#endif

	/* Defines: */
		#define BITBANG_TPIDATA_PORT     PORTB
		#define BITBANG_TPIDATA_DDR      DDRB
		#define BITBANG_TPIDATA_PIN      PINB
		#define BITBANG_TPIDATA_MASK     (1 << 3)
			
		#define BITBANG_TPICLOCK_PORT    PORTB
		#define BITBANG_TPICLOCK_DDR     DDRB
		#define BITBANG_TPICLOCK_PIN     PINB
		#define BITBANG_TPICLOCK_MASK    (1 << 1)
		
		#define BITS_IN_TPI_FRAME        12
		
		#define TPI_NVM_TIMEOUT_MS       200

		#define TPI_NVMENABLE_KEY        (uint8_t[]){0x12, 0x89, 0xAB, 0x45, 0xCD, 0xD8, 0x88, 0xFF}
				
	/* Function Prototypes: */
		void    TPITarget_EnableTargetTPI(void);
		void    TPITarget_DisableTargetTPI(void);
		void    TPITarget_SendByte(const uint8_t Byte);
		uint8_t TPITarget_ReceiveByte(void);
		void    TPITarget_SendBreak(void);
		bool    TPITarget_WaitWhileNVMBusBusy(void);

#endif
