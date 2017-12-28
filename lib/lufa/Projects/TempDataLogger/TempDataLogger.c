/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
				.InterfaceNumber           = INTERFACE_ID_MassStorage,
				.DataINEndpoint            =
					{
						.Address           = MASS_STORAGE_IN_EPADDR,
						.Size              = MASS_STORAGE_IO_EPSIZE,
						.Banks             = 1,
					},
				.DataOUTEndpoint           =
					{
						.Address           = MASS_STORAGE_OUT_EPADDR,
						.Size              = MASS_STORAGE_IO_EPSIZE,
						.Banks             = 1,
					},
				.TotalLUNs                 = 1,
			},
	};

/** Buffer to hold the previously generated HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevHIDReportBuffer[GENERIC_REPORT_SIZE];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Generic_HID_Interface =
	{
		.Config =
			{
				.InterfaceNumber              = INTERFACE_ID_HID,
				.ReportINEndpoint             =
					{
						.Address              = GENERIC_IN_EPADDR,
						.Size                 = GENERIC_EPSIZE,
						.Banks                = 1,
					},
				.PrevReportINBuffer           = PrevHIDReportBuffer,
				.PrevReportINBufferSize       = sizeof(PrevHIDReportBuffer),
			},
	};

/** Non-volatile Logging Interval value in EEPROM, stored as a number of 500ms ticks */
static uint8_t EEMEM LoggingInterval500MS_EEPROM = DEFAULT_LOG_INTERVAL;

/** SRAM Logging Interval value fetched from EEPROM, stored as a number of 500ms ticks */
static uint8_t LoggingInterval500MS_SRAM;

/** Total number of 500ms logging ticks elapsed since the last log value was recorded */
static uint16_t CurrentLoggingTicks;

/** FAT Fs structure to hold the internal state of the FAT driver for the Dataflash contents. */
static FATFS DiskFATState;

/** FAT Fs structure to hold a FAT file handle for the log data write destination. */
static FIL TempLogFile;


/** ISR to handle the 500ms ticks for sampling and data logging */
ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
	/* Signal a 500ms tick has elapsed to the RTC */
	RTC_Tick500ms();

	/* Check to see if the logging interval has expired */
	if (++CurrentLoggingTicks < LoggingInterval500MS_SRAM)
	  return;

	/* Reset log tick counter to prepare for next logging interval */
	CurrentLoggingTicks = 0;

	uint8_t LEDMask = LEDs_GetLEDs();
	LEDs_SetAllLEDs(LEDMASK_USB_BUSY);

	/* Only log when not connected to a USB host */
	if (USB_DeviceState == DEVICE_STATE_Unattached)
	{
		TimeDate_t CurrentTimeDate;
		RTC_GetTimeDate(&CurrentTimeDate);

		char     LineBuffer[100];
		uint16_t BytesWritten;

		BytesWritten = sprintf(LineBuffer, "%02d/%02d/20%02d, %02d:%02d:%02d, %d Degrees\r\n",
		                       CurrentTimeDate.Day, CurrentTimeDate.Month, CurrentTimeDate.Year,
		                       CurrentTimeDate.Hour, CurrentTimeDate.Minute, CurrentTimeDate.Second,
		                       Temperature_GetTemperature());

		f_write(&TempLogFile, LineBuffer, BytesWritten, &BytesWritten);
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

	/* Fetch logging interval from EEPROM */
	LoggingInterval500MS_SRAM = eeprom_read_byte(&LoggingInterval500MS_EEPROM);

	/* Check if the logging interval is invalid (0xFF) indicating that the EEPROM is blank */
	if (LoggingInterval500MS_SRAM == 0xFF)
	  LoggingInterval500MS_SRAM = DEFAULT_LOG_INTERVAL;

	/* Mount and open the log file on the Dataflash FAT partition */
	OpenLogFile();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		MS_Device_USBTask(&Disk_MS_Interface);
		HID_Device_USBTask(&Generic_HID_Interface);
		USB_USBTask();
	}
}

/** Opens the log file on the Dataflash's FAT formatted partition according to the current date */
void OpenLogFile(void)
{
	char LogFileName[12];

	/* Get the current date for the filename as "DDMMYY.csv" */
	TimeDate_t CurrentTimeDate;
	RTC_GetTimeDate(&CurrentTimeDate);
	sprintf(LogFileName, "%02d%02d%02d.csv", CurrentTimeDate.Day, CurrentTimeDate.Month, CurrentTimeDate.Year);

	/* Mount the storage device, open the file */
	f_mount(0, &DiskFATState);
	f_open(&TempLogFile, LogFileName, FA_OPEN_ALWAYS | FA_WRITE);
	f_lseek(&TempLogFile, TempLogFile.fsize);
}

/** Closes the open data log file on the Dataflash's FAT formatted partition */
void CloseLogFile(void)
{
	/* Sync any data waiting to be written, unmount the storage device */
	f_sync(&TempLogFile);
	f_close(&TempLogFile);
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#endif

	/* Hardware Initialization */
	LEDs_Init();
	ADC_Init(ADC_FREE_RUNNING | ADC_PRESCALE_128);
	Temperature_Init();
	Dataflash_Init();
	USB_Init();
	TWI_Init(TWI_BIT_PRESCALE_4, TWI_BITLENGTH_FROM_FREQ(4, 50000));
	RTC_Init();

	/* 500ms logging interval timer configuration */
	OCR1A   = (((F_CPU / 256) / 2) - 1);
	TCCR1B  = (1 << WGM12) | (1 << CS12);
	TIMSK1  = (1 << OCIE1A);

	/* Check if the Dataflash is working, abort if not */
	if (!(DataflashManager_CheckDataflashOperation()))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		for(;;);
	}

	/* Clear Dataflash sector protections, if enabled */
	DataflashManager_ResetDataflashProtections();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);

	/* Close the log file so that the host has exclusive file system access */
	CloseLogFile();
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	/* Mount and open the log file on the Dataflash FAT partition */
	OpenLogFile();
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Generic_HID_Interface);
	ConfigSuccess &= MS_Device_ConfigureEndpoints(&Disk_MS_Interface);

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	MS_Device_ProcessControlRequest(&Disk_MS_Interface);
	HID_Device_ProcessControlRequest(&Generic_HID_Interface);
}

/** Mass Storage class driver callback function the reception of SCSI commands from the host, which must be processed.
 *
 *  \param[in] MSInterfaceInfo  Pointer to the Mass Storage class interface configuration structure being referenced
 */
bool CALLBACK_MS_Device_SCSICommandReceived(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo)
{
	bool CommandSuccess;

	LEDs_SetAllLEDs(LEDMASK_USB_BUSY);
	CommandSuccess = SCSI_DecodeSCSICommand(MSInterfaceInfo);
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	return CommandSuccess;
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean \c true to force the sending of the report, \c false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	Device_Report_t* ReportParams = (Device_Report_t*)ReportData;

	RTC_GetTimeDate(&ReportParams->TimeDate);

	ReportParams->LogInterval500MS = LoggingInterval500MS_SRAM;

	*ReportSize = sizeof(Device_Report_t);
	return true;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	Device_Report_t* ReportParams = (Device_Report_t*)ReportData;

	RTC_SetTimeDate(&ReportParams->TimeDate);

	/* If the logging interval has changed from its current value, write it to EEPROM */
	if (LoggingInterval500MS_SRAM != ReportParams->LogInterval500MS)
	{
		LoggingInterval500MS_SRAM = ReportParams->LogInterval500MS;
		eeprom_update_byte(&LoggingInterval500MS_EEPROM, LoggingInterval500MS_SRAM);
	}
}

