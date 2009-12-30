/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Main source file for the TemperatureDataLogger project. This file contains the main tasks of
 *  the project and is responsible for the initial application hardware configuration.
 */

#include "TempDataLogger.h"

/** LUFA Mass Storage Class driver interface configuration and state information. This structure is
 *  passed to all Mass Storage Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_MS_Device_t Disk_MS_Interface =
	{
		.Config =
			{
				.InterfaceNumber           = 0,

				.DataINEndpointNumber      = MASS_STORAGE_IN_EPNUM,
				.DataINEndpointSize        = MASS_STORAGE_IO_EPSIZE,
				.DataINEndpointDoubleBank  = false,

				.DataOUTEndpointNumber     = MASS_STORAGE_OUT_EPNUM,
				.DataOUTEndpointSize       = MASS_STORAGE_IO_EPSIZE,
				.DataOUTEndpointDoubleBank = false,

				.TotalLUNs                 = 1,
			},
	};

/** FAT Fs structure to hold the internal state of the FAT driver for the dataflash contents. */
FATFS DiskFATState;

/** FAT Fs structure to hold a FAT file handle for the log data write destination. */
FIL TempLogFile;

/** Counter to count the number of 10 millisecond ticks that has elapsed since the last sample */
uint16_t CurrentLogTick;


ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
	if (CurrentLogTick++ != LOG_INTERVAL_10MS)
	  return;
	  
	uint8_t LEDMask = LEDs_GetLEDs();

	LEDs_SetAllLEDs(LEDMASK_USB_BUSY);

	CurrentLogTick = 0;

	if (USB_DeviceState == DEVICE_STATE_Unattached)
	{
		f_printf(&TempLogFile, "%d Degrees\r\n", Temperature_GetTemperature());
		f_sync(&TempLogFile);
	}
	
	LEDs_SetAllLEDs(LEDMask);
}


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	/* Mount and open the log file on the dataflash FAT partition */
	f_mount(0, &DiskFATState);
	f_open(&TempLogFile, LOG_FILENAME, FA_OPEN_ALWAYS | FA_WRITE);
	f_lseek(&TempLogFile, TempLogFile.fsize);
	f_printf(&TempLogFile, "===========================\r\n");
	
	/* Discard the first sample from the temperature sensor, as it is generally incorrect */
	uint8_t Dummy = Temperature_GetTemperature();
	(void)Dummy;
	
	for (;;)
	{
		MS_Device_USBTask(&Disk_MS_Interface);
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
	LEDs_Init();
	SPI_Init(SPI_SPEED_FCPU_DIV_2 | SPI_SCK_LEAD_FALLING | SPI_SAMPLE_TRAILING | SPI_MODE_MASTER);
	ADC_Init(ADC_REFERENCE_AVCC | ADC_FREE_RUNNING | ADC_PRESCALE_128);
	Temperature_Init();
	Dataflash_Init();
	USB_Init();
	
	/* 10ms interval timer configuration */
	OCR1A   = (((F_CPU / 1024) / 100) - 1);
	TCCR1B  = (1 << WGM12) | (1 << CS12) | (1 << CS10);   // CTC mode, Fcpu/1024 speed
	TIMSK1  = (1 << OCIE1A);

	/* Clear Dataflash sector protections, if enabled */
	DataflashManager_ResetDataflashProtections();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);

	/* Close the log file so that the host has exclusive filesystem access */
	f_close(&TempLogFile);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	
	/* When disconnected from the host, re-open log file so we can resume logging */
	f_mount(0, &DiskFATState);
	f_open(&TempLogFile, LOG_FILENAME, FA_OPEN_ALWAYS | FA_WRITE);
	f_lseek(&TempLogFile, TempLogFile.fsize);
	f_printf(&TempLogFile, "===========================\r\n");
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	if (!(MS_Device_ConfigureEndpoints(&Disk_MS_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Unhandled Control Request event. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	MS_Device_ProcessControlRequest(&Disk_MS_Interface);
}

/** Mass Storage class driver callback function the reception of SCSI commands from the host, which must be processed.
 *
 *  \param[in] MSInterfaceInfo  Pointer to the Mass Storage class interface configuration structure being referenced
 */
bool CALLBACK_MS_Device_SCSICommandReceived(USB_ClassInfo_MS_Device_t* MSInterfaceInfo)
{
	bool CommandSuccess;
	
	LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
	CommandSuccess = SCSI_DecodeSCSICommand(MSInterfaceInfo);
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
	
	return CommandSuccess;
}
