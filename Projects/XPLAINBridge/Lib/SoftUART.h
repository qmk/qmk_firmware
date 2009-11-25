/*

	soft_uart

	Copyright John Steggall 2009

*/


/*
  Copyright 2009  John Steggall (steggall.j@gmail.com)

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

/* 
  Specifically designed for the xplain board, other uses could be made by furkling through the code
  and replacing the port and pin assignments. Also relies on and external interupt to detect the low
  level of the start bit, in this case INT0.
  Always configured to 9600baud. Can be changed by setting the BITLENGTH define to F_CPU/(desired baud)
  code may need optimising when getting any faster to sample the bit in the correct place. No 
  compensation has been made for the response time of the int routine.
 */

#ifndef UART_SOFT_H
#define UART_SOFT_H

	/*  initialises software uart and enables transmit */
	extern void SoftUART_Init(void);

	/* checks if there is a byte in the receive buffer*/
	extern unsigned char SoftUART_IsReceived(void);

	/*  returns the received byte */
	extern unsigned char SoftUART_RxByte(void);

	/* starts a byte send and returns the byte to be sent */
	extern unsigned char SoftUART_TxByte(unsigned char data);

	/* Simulates polling UDRE to see if tx buffer is empty and ready */
	extern unsigned char SoftUART_IsReady(void);

#endif
