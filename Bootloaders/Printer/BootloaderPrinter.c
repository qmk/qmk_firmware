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
} HEXParser =
	{
		.ParserState = HEX_PARSE_STATE_WAIT_LINE
	};

/** Indicates if there is data waiting to be written to a physical page of
 *  memory in FLASH.
 */
static bool PageDirty = false;

/**
 * Determines if a given input byte of data is an ASCII encoded HEX value.
 *
 * \note Input HEX bytes are expected to be in uppercase only.
 *
 * \param[in] Byte  ASCII byte of data to check
 *
 * \return Boolean \c true if the input data is ASCII encoded HEX, false otherwise.
 */
static bool IsHex(const char Byte)
{
	return ((Byte >= 'A') && (Byte <= 'F')) ||
	       ((Byte >= '0') && (Byte <= '9'));
}

/**
 * Converts a given input byte of data from an ASCII encoded HEX value to an integer value.
 *
 * \note Input HEX bytes are expected to be in uppercase only.
 *
 * \param[in] Byte  ASCII byte of data to convert
 *
 * \return Integer converted value of the input ASCII encoded HEX byte of data.
 */
static uint8_t HexToDecimal(const char Byte)
{
	if ((Byte >= 'A') && (Byte <= 'F'))
	  return (10 + (Byte - 'A'));
	else if ((Byte >= '0') && (Byte <= '9'))
	  return (Byte - '0');

	return 0;
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
		HEXParser.ParserState  = HEX_PARSE_STATE_WAIT_LINE;
		HEXParser.ReadMSB      = false;

		/* ASCII ':' indicates the start of a new HEX record */
		if (ReadCharacter == ':')
		  HEXParser.ParserState = HEX_PARSE_STATE_BYTE_COUNT;

		return;
	}

	/* Only allow ASCII HEX encoded digits, ignore all other characters */
	if (!IsHex(ReadCharacter))
	  return;

	/* Read and convert the next nibble of data from the current character */
	HEXParser.Data    = (HEXParser.Data << 4) | HexToDecimal(ReadCharacter);
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
					/* If we are writing to a new page, we need to erase it
					 * first
					 */
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
					uint32_t NewPageStartAddress = (HEXParser.CurrAddress & ~(SPM_PAGESIZE - 1));
					if (PageDirty && (HEXParser.PageStartAddress != NewPageStartAddress))
					{
						boot_page_write(HEXParser.PageStartAddress);
						boot_spm_busy_wait();

						HEXParser.PageStartAddress = NewPageStartAddress;

						PageDirty = false;
					}
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
			uint32_t NewPageStartAddress = (HEXParser.CurrAddress & ~(SPM_PAGESIZE - 1));
			if (PageDirty && (HEXParser.PageStartAddress != NewPageStartAddress))
			{
				boot_page_write(HEXParser.PageStartAddress);
				boot_spm_busy_wait();

				HEXParser.PageStartAddress = NewPageStartAddress;

				PageDirty = false;
			}

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

	for (;;)
	{
		USB_USBTask();

		Endpoint_SelectEndpoint(PRINTER_OUT_EPADDR);

		/* Check if we have received new printer data from the host */
		if (Endpoint_IsOUTReceived()) {
			LEDs_ToggleLEDs(LEDMASK_USB_BUSY);

			/* Read all bytes of data from the host and parse them */
			while (Endpoint_IsReadWriteAllowed())
			{
				/* Feed the next byte of data to the HEX parser */
				ParseIntelHEXByte(Endpoint_Read_8());
			}

			/* Send an ACK to the host, ready for the next data packet */
			Endpoint_ClearOUT();

			LEDs_SetAllLEDs(LEDMASK_USB_READY);
		}
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
	ConfigSuccess &= Endpoint_ConfigureEndpoint(PRINTER_IN_EPADDR,  EP_TYPE_BULK, PRINTER_IO_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(PRINTER_OUT_EPADDR, EP_TYPE_BULK, PRINTER_IO_EPSIZE, 1);

	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to
 *  the device from the USB host before passing along unhandled control requests to the library for processing
 *  internally.
 */
void EVENT_USB_Device_ControlRequest(void)
{
	/* Process Printer specific control requests */
	switch (USB_ControlRequest.bRequest)
	{
		case PRNT_REQ_GetDeviceID:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Generic printer IEEE 1284 identification string, will bind to an in-built driver on
				 * Windows systems, and will fall-back to a text-only printer driver on *nix.
				 */
				const char PrinterIDString[] =
					"MFG:Generic;"
					"MDL:Generic_/_Text_Only;"
					"CMD:1284.4;"
					"CLS:PRINTER";

				Endpoint_ClearSETUP();
				Endpoint_Write_16_BE(sizeof(PrinterIDString));
				Endpoint_Write_Control_Stream_LE(PrinterIDString, strlen(PrinterIDString));
				Endpoint_ClearStatusStage();
			}

			break;
		case PRNT_REQ_GetPortStatus:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_Write_8(PRNT_PORTSTATUS_NOTERROR | PRNT_PORTSTATUS_SELECT);
				Endpoint_ClearStatusStage();
			}

			break;
		case PRNT_REQ_SoftReset:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_ClearStatusStage();
			}

			break;
	}
}
