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

#include "Temperature.h"

static const uint16_t PROGMEM Temperature_Lookup[] = {
   0x3B4, 0x3B0, 0x3AB, 0x3A6, 0x3A0, 0x39A, 0x394, 0x38E, 0x388, 0x381, 0x37A, 0x373,
   0x36B, 0x363, 0x35B, 0x353, 0x34A, 0x341, 0x338, 0x32F, 0x325, 0x31B, 0x311, 0x307,
   0x2FC, 0x2F1, 0x2E6, 0x2DB, 0x2D0, 0x2C4, 0x2B8, 0x2AC, 0x2A0, 0x294, 0x288, 0x27C,
   0x26F, 0x263, 0x256, 0x24A, 0x23D, 0x231, 0x225, 0x218, 0x20C, 0x200, 0x1F3, 0x1E7,
   0x1DB, 0x1CF, 0x1C4, 0x1B8, 0x1AC, 0x1A1, 0x196, 0x18B, 0x180, 0x176, 0x16B, 0x161,
   0x157, 0x14D, 0x144, 0x13A, 0x131, 0x128, 0x11F, 0x117, 0x10F, 0x106, 0x0FE, 0x0F7,
   0x0EF, 0x0E8, 0x0E1, 0x0DA, 0x0D3, 0x0CD, 0x0C7, 0x0C0, 0x0BA, 0x0B5, 0x0AF, 0x0AA,
   0x0A4, 0x09F, 0x09A, 0x096, 0x091, 0x08C, 0x088, 0x084, 0x080, 0x07C, 0x078, 0x074,
   0x071, 0x06D, 0x06A, 0x067, 0x064, 0x061, 0x05E, 0x05B, 0x058, 0x055, 0x053, 0x050,
   0x04E, 0x04C, 0x049, 0x047, 0x045, 0x043, 0x041, 0x03F, 0x03D, 0x03C, 0x03A, 0x038
   };

int8_t Temperature_GetTemperature(void)
{
	uint16_t Temp_ADC = ADC_GetChannelReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | TEMP_ADC_CHANNEL);

	if (Temp_ADC > pgm_read_word(&Temperature_Lookup[0]))
	  return TEMP_MIN_TEMP;

	for (uint16_t Index = 0; Index < TEMP_TABLE_SIZE; Index++)
	{
		if (Temp_ADC > pgm_read_word(&Temperature_Lookup[Index]))
		  return (Index + TEMP_TABLE_OFFSET);
	}

	return TEMP_MAX_TEMP;
}
