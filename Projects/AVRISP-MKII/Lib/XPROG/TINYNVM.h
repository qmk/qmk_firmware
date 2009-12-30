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
 *  Header file for TINYNVM.c.
 */

#ifndef _TINY_NVM_
#define _TINY_NVM_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>
		
		#include <LUFA/Common/Common.h>
		
		#include "XPROGProtocol.h"
		#include "XPROGTarget.h"
	
	/* Preprocessor Checks: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#undef ENABLE_ISP_PROTOCOL
			
			#if !defined(ENABLE_XPROG_PROTOCOL)
				#define ENABLE_XPROG_PROTOCOL
			#endif
		#endif

	/* Defines: */
		#define TINY_NVM_CMD_NOOP              0x00
		#define TINY_NVM_CMD_CHIPERASE         0x10
		#define TINY_NVM_CMD_SECTIONERASE      0x14
		#define TINY_NVM_CMD_WORDWRITE         0x1D

	/* Function Prototypes: */
		void TINYNVM_SendPointerAddress(const uint16_t AbsoluteAddress);
		bool TINYNVM_WaitWhileNVMBusBusy(void);
		bool TINYNVM_ReadMemory(const uint32_t ReadAddress, uint8_t* ReadBuffer, uint16_t ReadLength);
		bool TINYNVM_WriteMemory(const uint32_t WriteAddress, const uint8_t* WriteBuffer, uint16_t WriteLength);
		bool TINYNVM_EraseMemory(void);

#endif
