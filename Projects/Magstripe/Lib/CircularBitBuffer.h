/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)
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

/** \file
 *
 *  Header file for CircularBitBuffer.c.
 */

#ifndef _CIRCULARBITBUFFER_H_
#define _CIRCULARBITBUFFER_H_

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>

		#include <LUFA/Common/Common.h>

	/* Macros: */
		#if (defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB647__) || \
		     defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__)) || defined(__DOXYGEN__)
			/** Maximum number of bits which can be stored into a bit buffer. The memory usage is one eighth of this value per buffer. */
			#define MAX_BITS 8192
		#else
			#define MAX_BITS 1024
		#endif

	/* Type Defines: */
		/** Type define for a pointer to a bit in a bit buffer. */
		typedef struct
		{
			uint8_t* CurrentByte; /**< Pointer to the current byte in the buffer */
			uint8_t  ByteMask; /**< Mask of the current bit in the buffer */
		} BitBufferPointer_t;

		/** Type define for a circular packet bit buffer. */
		typedef struct
		{
			uint8_t            Data[MAX_BITS / 8]; /**< Buffer to hold the stored bits in packed form */
			uint16_t           Elements; /**< Number of stored bits in the bit buffer */

			BitBufferPointer_t In; /**< Bit pointer to the next storage location in the buffer */
			BitBufferPointer_t Out; /**< Bit pointer to the next retrieval location in the buffer */
		} BitBuffer_t;

	/* Function Prototypes: */
		/** Initialises or resets a given bit buffer, ready to store new bits.
		 *
		 *  \param[in,out] Buffer  Bit buffer to initialize
		 */
		void BitBuffer_Init(BitBuffer_t* const Buffer) ATTR_NON_NULL_PTR_ARG(1);

		/** Stores a bit into the next location inside a given bit buffer.
		 *
		 *  \param[in,out] Buffer  Bit buffer to store a bit into
		 *  \param[in] Bit  Bit to store into the buffer
		 */
		void BitBuffer_StoreNextBit(BitBuffer_t* const Buffer,
		                            const bool Bit) ATTR_NON_NULL_PTR_ARG(1);

		/** Retrieves a bit from the next location inside a given bit buffer.
		 *
		 *  \param[in,out] Buffer  Bit buffer to store a bit into
		 *
		 *  \return Next bit from the buffer
		 */
		bool BitBuffer_GetNextBit(BitBuffer_t* const Buffer) ATTR_NON_NULL_PTR_ARG(1);

#endif

