/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2019  Filipe Rodrigues (filipepazrodrigues [at] gmail [dot] com)

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

#include "Iso7816.h"


void Iso7816_CreateSimpleAtr(uint8_t* const attr,
                             uint8_t* const attrLength)
{
	attr[0] = 0x3B; //TS: direct convention

	uint8_t interfaceBytesPresence = 0;

	uint8_t historicalBytes[14]   = "LUFA CCID Demo"; // Must be equal or less than 15
	uint8_t historicalBytesLength = sizeof(historicalBytes);

	attr[1] = (interfaceBytesPresence << 4) + historicalBytesLength;
	memcpy(attr + 2, historicalBytes, historicalBytesLength);

	*attrLength = historicalBytesLength + 2;
}
