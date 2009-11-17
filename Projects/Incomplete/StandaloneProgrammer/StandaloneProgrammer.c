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
	
/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber         = 0,

				.DataINEndpointNumber           = CDC_TX_EPNUM,
				.DataINEndpointSize             = CDC_TXRX_EPSIZE,
				.DataINEndpointDoubleBank       = false,

				.DataOUTEndpointNumber          = CDC_RX_EPNUM,
				.DataOUTEndpointSize            = CDC_TXRX_EPSIZE,
				.DataOUTEndpointDoubleBank      = false,

				.NotificationEndpointNumber     = CDC_NOTIFICATION_EPNUM,
				.NotificationEndpointSize       = CDC_NOTIFICATION_EPSIZE,
				.NotificationEndpointDoubleBank = false,
			},
	};

/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs
 */
FILE USBSerialStream;

/** Standard file stream for the currently open file on the dataflash disk. */
FILE DataflashStream = FDEV_SETUP_STREAM(NULL, Dataflash_getchar, _FDEV_SETUP_READ);

/** Petite FAT Fs structure to hold the internal state of the FAT driver for the dataflash contents. */
FATFS DataflashData;


/** Stream character fetching routine for the FAT driver so that characters from the currently open file can be
 *  readin sequence when applied to a stdio stream.
 */
static int Dataflash_getchar(FILE* Stream)
{
	char ReadByte;
	WORD ByteWasRead;

	if (pf_read(&ReadByte, 1, &ByteWasRead) != FR_OK)
	  return _FDEV_ERR;

	return (ByteWasRead ? ReadByte : _FDEV_EOF);
}

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
		
		fputs("==== PROGRAMMING CYCLE STARTED ====\r\n", &USBSerialStream);

		fputs("Reading Configuration File...\r\n", &USBSerialStream);
		
		if (!(ProgrammerConfig_ProcessConfiguration()))
		  goto EndOfProgCycle;

		EndOfProgCycle:
		fputs("==== PROGRAMMING CYCLE FINISHED ====\r\n", &USBSerialStream);
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

	/* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		Programmer_Task();
		  
		/* Must throw away unused bytes from the host, or it will lock up while waiting for the device */
		while (CDC_Device_BytesReceived(&VirtualSerial_CDC_Interface))
		  CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
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
	Dataflash_Init();
	USB_Init();
	Buttons_Init();
	pf_mount(&DataflashData);

	/* Clear Dataflash sector protections, if enabled */
	DataflashManager_ResetDataflashProtections();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	if (!(MS_Device_ConfigureEndpoints(&Disk_MS_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

	if (!(CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Unhandled Control Request event. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	MS_Device_ProcessControlRequest(&Disk_MS_Interface);
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
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
