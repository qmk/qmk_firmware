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
 *  Header file for ISPProtocol.c.
 */

#ifndef _ISP_PROTOCOL_
#define _ISP_PROTOCOL_

	/* Includes: */
		#include <avr/io.h>
		
		#include <LUFA/Drivers/USB/USB.h>

		#include "../V2Protocol.h"
		
	/* Preprocessor Checks: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#undef ENABLE_ISP_PROTOCOL
			
			#if !defined(ENABLE_XPROG_PROTOCOL)
				#define ENABLE_XPROG_PROTOCOL
			#endif
		#endif

	/* Macros: */
		/** Mask for the reading or writing of the high byte in a FLASH word when issuing a low-level programming command */
		#define READ_WRITE_HIGH_BYTE_MASK       (1 << 3)

		#define PROG_MODE_PAGED_WRITES_MASK     (1 << 0)
		#define PROG_MODE_WORD_TIMEDELAY_MASK   (1 << 1)
		#define PROG_MODE_WORD_VALUE_MASK       (1 << 2)
		#define PROG_MODE_WORD_READYBUSY_MASK   (1 << 3)
		#define PROG_MODE_PAGED_TIMEDELAY_MASK  (1 << 4)
		#define PROG_MODE_PAGED_VALUE_MASK      (1 << 5)
		#define PROG_MODE_PAGED_READYBUSY_MASK  (1 << 6)
		#define PROG_MODE_COMMIT_PAGE_MASK      (1 << 7)

	/* Inline Functions: */
		/** Blocking delay for a given number of milliseconds, via a hardware timer.
		 *
		 *  \param[in] DelayMS  Number of milliseconds to delay for
		 */
		static inline void ISPProtocol_DelayMS(uint8_t DelayMS)
		{
			OCR2A  = ((F_CPU / 64) / 1000);
			TCCR2A = (1 << WGM01);
			TCCR2B = ((1 << CS01) | (1 << CS00));			

			while (DelayMS)
			{
				if (TIFR2 & (1 << OCF2A))
				{
					TIFR2 = (1 << OCF2A);
					DelayMS--;
				}
			}
			
			TCCR2B = 0;			
		}

	/* Function Prototypes: */
		void ISPProtocol_EnterISPMode(void);
		void ISPProtocol_LeaveISPMode(void);
		void ISPProtocol_ProgramMemory(const uint8_t V2Command);
		void ISPProtocol_ReadMemory(const uint8_t V2Command);
		void ISPProtocol_ChipErase(void);
		void ISPProtocol_ReadFuseLockSigOSCCAL(const uint8_t V2Command);
		void ISPProtocol_WriteFuseLock(const uint8_t V2Command);
		void ISPProtocol_SPIMulti(void);

#endif
