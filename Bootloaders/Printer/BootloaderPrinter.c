/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Main source file for the Printer class bootloader. This file contains the complete bootloader logic.
 */

#include "BootloaderPrinter.h"

/** LUFA Printer Class driver interface configuration and state information. This structure is
 *  passed to all Printer Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_PRNT_Device_t TextOnly_Printer_Interface =
	{
		.Config =
			{
				.InterfaceNumber          = 0,
				.DataINEndpoint           =
					{
						.Address          = PRINTER_IN_EPADDR,
						.Size             = PRINTER_IO_EPSIZE,
						.Banks            = 1,
					},
				.DataOUTEndpoint =
					{
						.Address          = PRINTER_OUT_EPADDR,
						.Size             = PRINTER_IO_EPSIZE,
						.Banks            = 1,
					},
				.IEEE1284String =
					"MFG:Generic;"
					"MDL:Generic_/_Text_Only;"
					"CMD:1284.4;"
					"CLS:PRINTER",
			},
	};

/** Intel HEX parser state machine state information, to track the contents of
 *  a HEX file streamed in as a sequence of arbitrary bytes.
 */
struct
{
	/** Current HEX parser state machine state. */
	uint8_t  ParserState;
	/** Previously decoded numerical byte of data. */
	uint8_t  PrevData;
	/** Currently decoded numerical byte of data. */
	uint8_t  Data;
	/** Indicates if both bytes that correspond to a single decoded numerical
	 *  byte of data (HEX encodes values in ASCII HEX, two characters per byte)
	 *  have been read.
	 */
	bool     ReadMSB;
	/** Intel HEX record type of the current Intel HEX record. */
	uint8_t  RecordType;
	/** Numerical bytes of data remaining to be read in the current record. */
	uint8_t  DataRem;
	/** Checksum of the current record received so far. */
	uint8_t  Checksum;
	/** Starting address of the last addressed FLASH page. */
	uint32_t PageStartAddress;
	/** Current 32-bit byte extended base address in FLASH being targeted. */
	uint32_t CurrBaseAddress;
	/** Current 32-bit byte address in FLASH being targeted. */
	uint32_t CurrAddress;
} HEXParser;

/** Indicates if there is data waiting to be written to a physical page of
 *  memory in FLASH.
 */
static bool PageDirty = false;

/** Flag to indicate if the bootloader should be running, or should exit and allow the application code to run
 *  via a soft reset. When cleared, the bootloader will abort, the USB interface will shut down and the application
 *  started via a forced watchdog reset.
 */
static bool RunBootloader = true;

/** Magic lock for forced application start. If the HWBE fuse is programmed and BOOTRST is unprogrammed, the bootloader
 *  will start if the /HWB line of the AVR is held low and the system is reset. However, if the /HWB line is still held
 *  low when the application attempts to start via a watchdog reset, the bootloader will re-start. If set to the value
 *  \ref MAGIC_BOOT_KEY the special init function \ref Application_Jump_Check() will force the application to start.
 */
uint16_t MagicBootKey ATTR_NO_INIT;


/** Special startup routine to check if the bootloader was started via a watchdog reset, and if the magic application
 *  start key has been loaded into \ref MagicBootKey. If the bootloader started via the watchdog and the key is valid,
 *  this will force the user application to start via a software jump.
 */
void Application_Jump_Check(void)
{
	/* If the reset source was the bootloader and the key is correct, clear it and jump to the application */
	if ((MCUSR & (1 << WDRF)) && (MagicBootKey == MAGIC_BOOT_KEY))
	{
		MagicBootKey = 0;

		// cppcheck-suppress constStatement
		((void (*)(void))0x0000)();
	}
}

/**
 * Converts a given input byte of data from an ASCII encoded HEX value to an integer value.
 *
 * \note Input HEX bytes are expected to be in uppercase only.
 *
 * \param[in] Byte  ASCII byte of data to convert
 *
 * \return Integer converted value of the input ASCII encoded HEX byte of data, or -1 if the
 *         input is not valid ASCII encoded HEX.
 */
static int8_t HexToDecimal(const char Byte)
{
	if ((Byte >= 'A') && (Byte <= 'F'))
	  return (10 + (Byte - 'A'));
	else if ((Byte >= '0') && (Byte <= '9'))
	  return (Byte - '0');

	return -1;
}

/**
 * Flushes a partially written page of data to physical FLASH, if a page
 * boundary has been crossed.
 *
 * \note If a page flush occurs the global HEX parser state is updated.
 */
static void FlushPageIfRequired(void)
{
	/* Abort if no data has been buffered for writing to the current page */
	if (!PageDirty)
	  return;

	/* Flush the FLASH page to physical memory if we are crossing a page boundary */
	uint32_t NewPageStartAddress = (HEXParser.CurrAddress & ~(SPM_PAGESIZE - 1));
	if (HEXParser.PageStartAddress != NewPageStartAddress)
	{
		boot_page_write(HEXParser.PageStartAddress);
		boot_spm_busy_wait();

		HEXParser.PageStartAddress = NewPageStartAddress;

		PageDirty = false;
	}
}

/**
 * Parses an input Intel HEX formatted stream one character at a time, loading
 * the data contents into the device's internal FLASH memory.
 *
 * \param[in] ReadCharacter  Next input ASCII byte of data to parse
 */
static void ParseIntelHEXByte(const char ReadCharacter)
{
	/* Reset the line parser while waiting for a new line to start */
	if ((HEXParser.ParserState == HEX_PARSE_STATE_WAIT_LINE) || (ReadCharacter == ':'))
	{
		HEXParser.Checksum     = 0;
		HEXParser.CurrAddress  = HEXParser.CurrBaseAddress;
		HEXParser.ReadMSB      = false;

		/* ASCII ':' indicates the start of a new HEX record */
		if (ReadCharacter == ':')
		  HEXParser.ParserState = HEX_PARSE_STATE_BYTE_COUNT;

		return;
	}

	/* Only allow ASCII HEX encoded digits, ignore all other characters */
	int8_t ReadCharacterDec = HexToDecimal(ReadCharacter);
	if (ReadCharacterDec < 0)
	  return;

	/* Read and convert the next nibble of data from the current character */
	HEXParser.Data    = (HEXParser.Data << 4) | ReadCharacterDec;
	HEXParser.ReadMSB = !HEXParser.ReadMSB;

	/* Only process further when a full byte (two nibbles) have been read */
	if (HEXParser.ReadMSB)
	  return;

	/* Intel HEX checksum is for all fields except starting character and the
	 * checksum itself
	 */
	if (HEXParser.ParserState != HEX_PARSE_STATE_CHECKSUM)
	  HEXParser.Checksum += HEXParser.Data;

	switch (HEXParser.ParserState)
	{
		case HEX_PARSE_STATE_BYTE_COUNT:
			HEXParser.DataRem      = HEXParser.Data;
			HEXParser.ParserState  = HEX_PARSE_STATE_ADDRESS_HIGH;
			break;

		case HEX_PARSE_STATE_ADDRESS_HIGH:
			HEXParser.CurrAddress += ((uint16_t)HEXParser.Data << 8);
			HEXParser.ParserState  = HEX_PARSE_STATE_ADDRESS_LOW;
			break;

		case HEX_PARSE_STATE_ADDRESS_LOW:
			HEXParser.CurrAddress += HEXParser.Data;
			HEXParser.ParserState  = HEX_PARSE_STATE_RECORD_TYPE;
			break;

		case HEX_PARSE_STATE_RECORD_TYPE:
			HEXParser.RecordType   = HEXParser.Data;
			HEXParser.ParserState  = (HEXParser.DataRem ? HEX_PARSE_STATE_READ_DATA : HEX_PARSE_STATE_CHECKSUM);
			break;

		case HEX_PARSE_STATE_READ_DATA:
			/* Track the number of read data bytes in the record */
			HEXParser.DataRem--;

			/* Protect the bootloader against being written to */
			if (HEXParser.CurrAddress >= BOOT_START_ADDR)
			{
				HEXParser.ParserState = HEX_PARSE_STATE_WAIT_LINE;
				PageDirty = false;
				return;
			}

			/* Wait for a machine word (two bytes) of data to be read */
			if (HEXParser.DataRem & 0x01)
			{
				HEXParser.PrevData = HEXParser.Data;
				break;
			}

			/* Convert the last two received data bytes into a 16-bit word */
			uint16_t NewDataWord = ((uint16_t)HEXParser.Data << 8) | HEXParser.PrevData;

			switch (HEXParser.RecordType)
			{
				case HEX_RECORD_TYPE_Data:
					/* If we are writing to a new page, we need to erase it first */
					if (!(PageDirty))
					{
						boot_page_erase(HEXParser.PageStartAddress);
						boot_spm_busy_wait();

						PageDirty = true;
					}

					/* Fill the FLASH memory buffer with the new word of data */
					boot_page_fill(HEXParser.CurrAddress, NewDataWord);
					HEXParser.CurrAddress += 2;

					/* Flush the FLASH page to physical memory if we are crossing a page boundary */
					FlushPageIfRequired();
					break;

				case HEX_RECORD_TYPE_ExtendedSegmentAddress:
					/* Extended address data - store the upper 12-bits of the new address */
					HEXParser.CurrBaseAddress = ((uint32_t)NewDataWord << 4);
					break;

				case HEX_RECORD_TYPE_ExtendedLinearAddress:
					/* Extended address data - store the upper 16-bits of the new address */
					HEXParser.CurrBaseAddress = ((uint32_t)NewDataWord << 16);
					break;
			}

			if (!HEXParser.DataRem)
			  HEXParser.ParserState = HEX_PARSE_STATE_CHECKSUM;
			break;

		case HEX_PARSE_STATE_CHECKSUM:
			/* Verify checksum of the completed record */
			if (HEXParser.Data != ((~HEXParser.Checksum + 1) & 0xFF))
			  break;

			/* Flush the FLASH page to physical memory if we are crossing a page boundary */
			FlushPageIfRequired();

			/* If end of the HEX file reached, the bootloader should exit at next opportunity */
			if (HEXParser.RecordType == HEX_RECORD_TYPE_EndOfFile)
			  RunBootloader = false;

			break;

		default:
			HEXParser.ParserState = HEX_PARSE_STATE_WAIT_LINE;
			break;
	}
}

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	while (RunBootloader)
	{
		uint8_t BytesReceived = PRNT_Device_BytesReceived(&TextOnly_Printer_Interface);

		if (BytesReceived)
		{
			LEDs_SetAllLEDs(LEDMASK_USB_BUSY);

			while (BytesReceived--)
			{
				int16_t ReceivedByte = PRNT_Device_ReceiveByte(&TextOnly_Printer_Interface);

				/* Feed the next byte of data to the HEX parser */
				ParseIntelHEXByte(ReceivedByte);
			}

			LEDs_SetAllLEDs(LEDMASK_USB_READY);
		}

		PRNT_Device_USBTask(&TextOnly_Printer_Interface);
		USB_USBTask();
	}

	/* Disconnect from the host - USB interface will be reset later along with the AVR */
	USB_Detach();

	/* Unlock the forced application start mode of the bootloader if it is restarted */
	MagicBootKey = MAGIC_BOOT_KEY;

	/* Enable the watchdog and force a timeout to reset the AVR */
	wdt_enable(WDTO_250MS);

	for (;;);
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
static void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Relocate the interrupt vector table to the bootloader section */
	MCUCR = (1 << IVCE);
	MCUCR = (1 << IVSEL);

	/* Hardware Initialization */
	LEDs_Init();
	USB_Init();

	/* Bootloader active LED toggle timer initialization */
	TIMSK1 = (1 << TOIE1);
	TCCR1B = ((1 << CS11) | (1 << CS10));
}

/** ISR to periodically toggle the LEDs on the board to indicate that the bootloader is active. */
ISR(TIMER1_OVF_vect, ISR_BLOCK)
{
	LEDs_ToggleLEDs(LEDS_LED1 | LEDS_LED2);
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs. */
void EVENT_USB_Device_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the Printer management task.
 */
void EVENT_USB_Device_Disconnect(void)
{
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the Mass Storage management task started.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	/* Setup Printer Data Endpoints */
	ConfigSuccess &= PRNT_Device_ConfigureEndpoints(&TextOnly_Printer_Interface);

	/* Reset the HEX parser upon successful connection to a host */
	HEXParser.ParserState = HEX_PARSE_STATE_WAIT_LINE;

	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to
 *  the device from the USB host before passing along unhandled control requests to the library for processing
 *  internally.
 */
void EVENT_USB_Device_ControlRequest(void)
{
	PRNT_Device_ProcessControlRequest(&TextOnly_Printer_Interface);
}
