/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for PDITarget.c.
 */

#ifndef _PDI_TARGET_
#define _PDI_TARGET_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>
		
		#include <LUFA/Common/Common.h>
		
		#include "../V2Protocol.h"
	
	/* Preprocessor Checks: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#undef ENABLE_ISP_PROTOCOL
			
			#if !defined(ENABLE_XPROG_PROTOCOL)
				#define ENABLE_XPROG_PROTOCOL
			#endif
		#endif

	/* Defines: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#define XPROG_VIA_HARDWARE_USART
		#else
			#define BITBANG_PDIDATA_PORT     PORTB
			#define BITBANG_PDIDATA_DDR      DDRB
			#define BITBANG_PDIDATA_PIN      PINB
			#define BITBANG_PDIDATA_MASK     (1 << 3)
			
			#define BITBANG_PDICLOCK_PORT    RESET_LINE_PORT
			#define BITBANG_PDICLOCK_DDR     RESET_LINE_DDR
			#define BITBANG_PDICLOCK_PIN     RESET_LINE_PIN
			#define BITBANG_PDICLOCK_MASK    RESET_LINE_MASK

			#define BITBANG_TPIDATA_PORT     PORTB
			#define BITBANG_TPIDATA_DDR      DDRB
			#define BITBANG_TPIDATA_PIN      PINB
			#define BITBANG_TPIDATA_MASK     (1 << 3)
				
			#define BITBANG_TPICLOCK_PORT    PORTB
			#define BITBANG_TPICLOCK_DDR     DDRB
			#define BITBANG_TPICLOCK_PIN     PINB
			#define BITBANG_TPICLOCK_MASK    (1 << 1)
		#endif
		
		/** Number of cycles between each clock when software USART mode is used */
		#define BITS_BETWEEN_USART_CLOCKS  100
		
		/** Total number of bits in a single USART frame */
		#define BITS_IN_USART_FRAME        12
		
		#define PDI_CMD_LDS                0x00
		#define PDI_CMD_LD                 0x20
		#define PDI_CMD_STS                0x40
		#define PDI_CMD_ST                 0x60
		#define PDI_CMD_LDCS               0x80
		#define PDI_CMD_REPEAT             0xA0
		#define PDI_CMD_STCS               0xC0
		#define PDI_CMD_KEY                0xE0
		
		#define PDI_STATUS_REG             0
		#define PDI_RESET_REG              1
		#define PDI_CTRL_REG               2
		
		#define PDI_STATUS_NVM             (1 << 1)

		#define PDI_RESET_KEY              0x59
		#define PDI_NVMENABLE_KEY          (uint8_t[]){0x12, 0x89, 0xAB, 0x45, 0xCD, 0xD8, 0x88, 0xFF}

		#define PDI_DATSIZE_1BYTE          0
		#define PDI_DATSIZE_2BYTES         1
		#define PDI_DATSIZE_3BYTES         2
		#define PDI_DATSIZE_4BYTES         3
		
		#define PDI_POINTER_INDIRECT       0
		#define PDI_POINTER_INDIRECT_PI    1
		#define PDI_POINTER_DIRECT         2

		#define TPI_CMD_SLD                0x20
		#define TPI_CMD_SST                0x60
		#define TPI_CMD_SSTPR              0x68
		#define TPI_CMD_SIN                0x10
		#define TPI_CMD_SOUT               0x90
		#define TPI_CMD_SLDCS              0x80
		#define TPI_CMD_SSTCS              0xC0
		#define TPI_CMD_SKEY               0xE0

		#define TPI_STATUS_REG             0x00
		#define TPI_CTRL_REG               0x02
		#define TPI_ID_REG                 0x0F
		
		#define TPI_STATUS_NVM             (1 << 1)

		#define TPI_NVMENABLE_KEY          (uint8_t[]){0x12, 0x89, 0xAB, 0x45, 0xCD, 0xD8, 0x88, 0xFF}

		#define TPI_POINTER_INDIRECT       0
		#define TPI_POINTER_INDIRECT_PI    (1 << 2)
		
	/* Function Prototypes: */
		void    XPROGTarget_EnableTargetPDI(void);
		void    XPROGTarget_EnableTargetTPI(void);
		void    XPROGTarget_DisableTargetPDI(void);
		void    XPROGTarget_DisableTargetTPI(void);
		void    XPROGTarget_SendByte(const uint8_t Byte);
		uint8_t XPROGTarget_ReceiveByte(void);
		void    XPROGTarget_SendBreak(void);
		bool    XPROGTarget_WaitWhileNVMBusBusy(void);

#endif
