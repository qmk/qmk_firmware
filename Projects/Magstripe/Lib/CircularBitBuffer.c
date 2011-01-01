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

/** Circular bit buffer library. This will allow for individual bits
 *  to be stored in packed form inside circular buffers, to reduce
 *  overall RAM usage.
 */

#include "CircularBitBuffer.h"

/** Function to initialize or reset a bit buffer, ready for data to be stored into it. */
void BitBuffer_Init(BitBuffer_t* const Buffer)
{
	/* Reset the number of stored bits in the buffer */
	Buffer->Elements        = 0;

	/* Reset the data in and out pointer structures in the buffer to the first buffer bit */
	Buffer->In.CurrentByte  = Buffer->Data;
	Buffer->In.ByteMask     = (1 << 0);
	Buffer->Out.CurrentByte = Buffer->Data;
	Buffer->Out.ByteMask    = (1 << 0);
}

/** Function to store the given bit into the given bit buffer. */
void BitBuffer_StoreNextBit(BitBuffer_t* const Buffer,
                            const bool Bit)
{
	/* If the bit to store is true, set the next bit in the buffer */
	if (Bit)
	  *Buffer->In.CurrentByte |= Buffer->In.ByteMask;

	/* Increment the number of stored bits in the buffer counter */
	Buffer->Elements++;

	/* Check if the current buffer byte is full of stored bits */
	if (Buffer->In.ByteMask == (1 << 7))
	{
		/* Check if the end of the buffer has been reached, if so reset to start of buffer, otherwise advance to next bit */
		if (Buffer->In.CurrentByte != &Buffer->Data[sizeof(Buffer->Data) - 1])
		  Buffer->In.CurrentByte++;
		else
		  Buffer->In.CurrentByte = Buffer->Data;

		/* Reset the storage bit mask in the current buffer byte to the first bit */
		Buffer->In.ByteMask = (1 << 0);
	}
	else
	{
		/* Shift the current storage bit mask to the next bit in the current byte */
		Buffer->In.ByteMask <<= 1;
	}
}

/** Function to retrieve the next bit stored in the given bit buffer. */
bool BitBuffer_GetNextBit(BitBuffer_t* const Buffer)
{
	/* Retrieve the value of the next bit stored in the buffer */
	bool Bit = ((*Buffer->Out.CurrentByte & Buffer->Out.ByteMask) != 0);

	/* Clear the buffer bit */
	*Buffer->Out.CurrentByte &= ~Buffer->Out.ByteMask;

	/* Decrement the number of stored bits in the buffer counter */
	Buffer->Elements--;

	/* Check if the current buffer byte is empty of stored bits */
	if (Buffer->Out.ByteMask == (1 << 7))
	{
		/* Check if the end of the buffer has been reached, if so reset to start of buffer, otherwise advance to next bit */
		if (Buffer->Out.CurrentByte != &Buffer->Data[sizeof(Buffer->Data) - 1])
		  Buffer->Out.CurrentByte++;
		else
		  Buffer->Out.CurrentByte = Buffer->Data;

		/* Reset the retrieval bit mask in the current buffer byte to the first bit */
		Buffer->Out.ByteMask = (1 << 0);
	}
	else
	{
		/* Shift the current retrieval bit mask to the next bit in the current byte */
		Buffer->Out.ByteMask <<= 1;
	}

	/* Return the retrieved bit from the buffer */
	return Bit;
}

