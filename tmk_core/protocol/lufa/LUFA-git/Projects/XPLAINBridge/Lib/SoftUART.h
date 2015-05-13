/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2010  David Prentice (david.prentice [at] farming [dot] uk)
  Copyright 2010  Peter Danneger
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
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
 *  Header file for SoftUART.c.
 */

#ifndef _SOFT_UART_
#define _SOFT_UART_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>

		#include "../XPLAINBridge.h"
		#include "Config/AppConfig.h"

	/* Macros: */
		#define SRX        PD0
		#define SRXPIN     PIND
		#define SRXPORT    PORTD

		#define STX        PD1
		#define STXPORT    PORTD
		#define STXDDR     DDRD

	/* Inline Functions: */
		static inline void SoftUART_SetBaud(const uint32_t Baud)
		{
			uint16_t BitTime = ((F_CPU / Baud) - 1);

			OCR1A = BitTime;
			OCR3A = BitTime;
		}

	/* Function Prototypes: */
		void SoftUART_Init(void);

#endif

