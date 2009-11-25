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

/** \file
 *
 *  Main source file for the Standalone Programmer project. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#define  INCLUDE_FROM_STANDALONEPROG_C
#include "StandaloneProgrammer.h"

/** Standard file stream for the currently open file on the disk. */
FILE DiskStream = FDEV_SETUP_STREAM(NULL, Disk_getchar, _FDEV_SETUP_READ);

/** Petite FAT Fs structure to hold the internal state of the FAT driver for the dataflash contents. */
FATFS DiskFATState;

/** Stream character fetching routine for the FAT driver so that characters from the currently open file can be
 *  read in sequence when applied to a stdio stream.
 */
static int Disk_getchar(FILE* Stream)
{
	char ReadByte;
	WORD ByteWasRead;

	if (pf_read(&ReadByte, 1, &ByteWasRead) != FR_OK)
	  return _FDEV_ERR;

	return (ByteWasRead ? ReadByte : _FDEV_EOF);
}

#if defined(USB_CAN_BE_BOTH)
/** Event to handle mode changes in the library, to clear the FAT library's drive state structure when transitioning
 *  between modes. This ensures that the library always works with current disk data.
 */
void EVENT_USB_UIDChange(void)
{
	pf_mount(&DiskFATState);
}
#endif

/** Task to determine if the user is wishes to start the programming sequence, and if so executes the 
 *  required functions to program the attached target (if any) with the files loaded to the dataflash.
 */
void Programmer_Task(void)
{
	static bool HasAttempted = false;

	if (Buttons_GetStatus() & BUTTONS_BUTTON1)
	{
		if (!(HasAttempted))
			HasAttempted = true;
		else
			return;
			
		puts("==== PROGRAMMING CYCLE STARTED ====\r\n");

		#if defined(USB_CAN_BE_BOTH)
		printf("Using %s Drive...\r\n", (USB_CurrentMode == USB_MODE_HOST) ? "External" : "Internal");
		#endif

		puts("Reading Configuration File...\r\n");
		if (!(ProgrammerConfig_ProcessConfiguration()))
		  goto EndOfProgCycle;

		EndOfProgCycle:
		puts("==== PROGRAMMING CYCLE FINISHED ====\r\n");
	}
	else
	{
		HasAttempted = false;
	}
}

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		Programmer_Task();
		  
		if (USB_CurrentMode == USB_MODE_HOST)
		{
			#if defined(USB_CAN_BE_HOST)
			DiskHost_USBTask();
			#endif
		}
		else
		{
			#if defined(USB_CAN_BE_DEVICE)
			DiskDevice_USBTask();
			#endif
		}
		
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	#if defined(USB_CAN_BE_BOTH)
	USB_Init(USB_MODE_UID);
	#else
	USB_Init();
	#endif

	LEDs_Init();
	SPI_Init(SPI_SPEED_FCPU_DIV_2 | SPI_SCK_LEAD_FALLING | SPI_SAMPLE_TRAILING | SPI_MODE_MASTER);
	Dataflash_Init();
	Buttons_Init();
	SerialStream_Init(9600, true);

	#if defined(USB_CAN_BE_DEVICE)
	/* Clear Dataflash sector protections, if enabled */
	DataflashManager_ResetDataflashProtections();
	#endif
}
