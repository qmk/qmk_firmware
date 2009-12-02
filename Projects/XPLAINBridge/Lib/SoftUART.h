/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  David Prentice (david.prentice [at] farming [dot] uk)
  Copyright 2009  Peter Danneger
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

#ifndef _SOFT_UART_
#define _SOFT_UART_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/interrupt.h>
		#include "SoftUART.h"

	/* Macros: */
		#define BAUD       9600
		#define BIT_TIME   (uint16_t)((F_CPU + (BAUD / 2)) / BAUD)

		#define SRX        PD0
		#define SRXPIN     PIND
		#define SRXPORT    PORTD

		#define STX        PD1
		#define STXPORT    PORTD
		#define STXDDR     DDRD

	/* Function Prototypes: */
		unsigned char SoftUART_IsReady(void);
		unsigned char SoftUART_TxByte(unsigned char c);
		unsigned char SoftUART_IsReceived(void);
		unsigned char SoftUART_RxByte(void);
		void SoftUART_Init(void);

#endif