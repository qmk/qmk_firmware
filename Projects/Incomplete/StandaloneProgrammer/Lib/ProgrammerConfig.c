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

#include "ProgrammerConfig.h"

struct
{
	uint16_t SigBytes[4];
	bool EnforceSigBytes;
	
	uint32_t ProgrammingSpeed;
} ProgrammerConfig;

bool ProgrammerConfig_ProcessConfiguration(void)
{
	memset(&ProgrammerConfig, sizeof(ProgrammerConfig), 0x00);

	if (!(pf_open("CONF.txt") == FR_OK))
	{
		puts(" >> ERROR: CONF.txt File Not Found.\r\n");
		return false;
	}
	
	char  LineBuff[100];
	char* CurrentLine;
			
	do
	{
		CurrentLine = fgets(LineBuff, sizeof(LineBuff), &DiskStream);
		
		if (CurrentLine)
		{
			sscanf(CurrentLine, "SIGNATURE = %02x %02x %02x %02x", &ProgrammerConfig.SigBytes[0],
			                                                       &ProgrammerConfig.SigBytes[1],
			                                                       &ProgrammerConfig.SigBytes[2],
			                                                       &ProgrammerConfig.SigBytes[3]);

			sscanf(CurrentLine, "SPEED = %lu", &ProgrammerConfig.ProgrammingSpeed);
		}
	} while (CurrentLine);
	
	printf(" >> *** Configuration: ***\r\n");
	printf(" >> Device Signature: 0x%02x 0x%02x 0x%02x 0x%02x\r\n", ProgrammerConfig.SigBytes[0],
			                                                        ProgrammerConfig.SigBytes[1],
			                                                        ProgrammerConfig.SigBytes[2],
			                                                        ProgrammerConfig.SigBytes[3]);
	printf(" >> Programming Speed: %lu Hz\r\n", ProgrammerConfig.ProgrammingSpeed);
	
	return true;
}
