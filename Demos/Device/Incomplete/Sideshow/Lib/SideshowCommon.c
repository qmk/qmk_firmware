/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
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

#include "SideshowCommon.h"

uint16_t SideShow_Read_Unicode_String(void* const UnicodeString,
                                      const uint16_t MaxBytes)
{
	Unicode_String_t* const UnicodeStruct = (Unicode_String_t*)UnicodeString;
	uint32_t                UnicodeCharsToRead;

	Endpoint_Read_Stream_LE(&UnicodeCharsToRead, sizeof(uint32_t), NULL);

	int UnicodeData[UnicodeCharsToRead];

	UnicodeStruct->LengthInBytes = (UnicodeCharsToRead << 1);

	Endpoint_Read_Stream_LE(&UnicodeData, UnicodeStruct->LengthInBytes, NULL);

	if (UnicodeStruct->LengthInBytes > MaxBytes)
	  UnicodeStruct->LengthInBytes = MaxBytes;

	memcpy(&UnicodeStruct->UnicodeString, &UnicodeData, UnicodeStruct->LengthInBytes);

	return ((UnicodeCharsToRead << 1) + sizeof(uint32_t));
}

void SideShow_Write_Unicode_String(void* const UnicodeString)
{
	Unicode_String_t* const UnicodeStruct = (Unicode_String_t*)UnicodeString;

	uint32_t StringSizeInCharacters = (UnicodeStruct->LengthInBytes >> 1);

	Endpoint_Write_Stream_LE(&StringSizeInCharacters, sizeof(uint32_t), NULL);
	Endpoint_Write_Stream_LE(&UnicodeStruct->UnicodeString, UnicodeStruct->LengthInBytes, NULL);
}

void SideShow_Discard_Byte_Stream(void)
{
	uint32_t StreamSize;

	Endpoint_Read_Stream_LE(&StreamSize, sizeof(uint32_t), NULL);
	Endpoint_Discard_Stream(StreamSize, NULL);
}

