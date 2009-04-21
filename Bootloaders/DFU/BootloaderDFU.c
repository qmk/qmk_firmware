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
 *  Main source file for the DFU class bootloader. This file contains the complete bootloader logic.
 */

#define  INCLUDE_FROM_BOOTLOADER_C
#include "BootloaderDFU.h"

/** Flag to indicate if the bootloader is currently running in secure mode, disallowing memory operations
 *  other than erase. This is initially set to the value set by SECURE_MODE, and cleared by the bootloader
 *  once a memory erase has completed.
 */
bool IsSecure      = SECURE_MODE;

/** Flag to indicate if the bootloader should be running, or should exit and allow the application code to run
 *  via a soft reset. When cleared, the bootloader will abort, the USB interface will shut down and the application
 *  jumped to via an indirect jump to location 0x0000 (or other location specified by the host).
 */
bool RunBootloader = true;

/** Flag to indicate if the bootloader is waiting to exit. When the host requests the bootloader to exit and
 *  jump to the application address it specifies, it sends two sequential commands which must be properly
 *  acknowledged. Upon reception of the first the RunBootloader flag is cleared and the WaitForExit flag is set,
 *  causing the bootloader to wait for the final exit command before shutting down.
 */
bool WaitForExit = false;

/** Current DFU state machine state, one of the values in the DFU_State_t enum. */
uint8_t DFU_State = dfuIDLE;

/** Status code of the last executed DFU command. This is set to one of the values in the DFU_Status_t enum after
 *  each operation, and returned to the host when a Get Status DFU request is issued.
 */
uint8_t DFU_Status = OK;

/** Data containing the DFU command sent from the host. */
DFU_Command_t SentCommand;

/** Response to the last issued Read Data DFU command. Unlike other DFU commands, the read command
 *  requires a single byte response from the bootloader containing the read data when the next DFU_UPLOAD command
 *  is issued by the host.
 */
uint8_t ResponseByte;

/** Pointer to the start of the user application. By default this is 0x0000 (the reset vector), however the host
 *  may specify an alternate address when issuing the application soft-start command.
 */
AppPtr_t AppStartPtr = (AppPtr_t)0x0000;

/** 64-bit flash page number. This is concatenated with the current 16-bit address on USB AVRs containing more than
 *  64KB of flash memory.
 */
uint8_t Flash64KBPage = 0;

/** Memory start address, indicating the current address in the memory being addressed (either FLASH or EEPROM
 *  depending on the issued command from the host).
 */
uint16_t StartAddr = 0x0000;

/** Memory end address, indicating the end address to read to/write from in the memory being addressed (either FLASH
 *  of EEPROM depending on the issued command from the host).
 */
uint16_t EndAddr = 0x0000;

/** Main program entry point. This routine configures the hardware required by the bootloader, then continuously 
 *  runs the bootloader processing routine until instructed to soft-exit, or hard-reset via the watchdog to start
 *  the loaded application code.
 */
int main (void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
	
	/* Relocate the interrupt vector table to the bootloader section */
	MCUCR = (1 << IVCE);
	MCUCR = (1 << IVSEL);

	/* Initialize the USB subsystem */
	USB_Init();

	/* Run the USB management task while the bootloader is supposed to be running */
	while (RunBootloader || WaitForExit)
	  USB_USBTask();
	
	/* Shut down the USB subsystem */
	USB_ShutDown();
	
	/* Relocate the interrupt vector table back to the application section */
	MCUCR = (1 << IVCE);
	MCUCR = 0;

	/* Reset any used hardware ports back to their defaults */
	PORTD = 0;
	DDRD  = 0;
	
	#if defined(PORTE)
	PORTE = 0;
	DDRE  = 0;
	#endif
	
	/* Start the user application */
	AppStartPtr();
}

/** Event handler for the USB_Disconnect event. This indicates that the bootloader should exit and the user
 *  application started.
 */
EVENT_HANDLER(USB_Disconnect)
{
	/* Upon disconnection, run user application */
	RunBootloader = false;
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the DFU commands, which are
 *  all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
EVENT_HANDLER(USB_UnhandledControlPacket)
{
	/* Discard unused wIndex value */
	Endpoint_Discard_Word();
	
	/* Discard unused wValue value */
	Endpoint_Discard_Word();

	/* Get the size of the command and data from the wLength value */
	SentCommand.DataSize = Endpoint_Read_Word_LE();

	switch (bRequest)
	{
		case DFU_DNLOAD:
			Endpoint_ClearSETUP();
			
			/* Check if bootloader is waiting to terminate */
			if (WaitForExit)
			{
				/* Bootloader is terminating - process last received command */
				ProcessBootloaderCommand();
				
				/* Indicate that the last command has now been processed - free to exit bootloader */
				WaitForExit = false;
			}
			  
			/* If the request has a data stage, load it into the command struct */
			if (SentCommand.DataSize)
			{
				while (!(Endpoint_IsOUTReceived()));

				/* First byte of the data stage is the DNLOAD request's command */
				SentCommand.Command = Endpoint_Read_Byte();
					
				/* One byte of the data stage is the command, so subtract it from the total data bytes */
				SentCommand.DataSize--;
				
				/* Load in the rest of the data stage as command parameters */
				for (uint8_t DataByte = 0; (DataByte < sizeof(SentCommand.Data)) &&
				     Endpoint_BytesInEndpoint(); DataByte++)
				{
					SentCommand.Data[DataByte] = Endpoint_Read_Byte();
					SentCommand.DataSize--;
				}
				
				/* Process the command */
				ProcessBootloaderCommand();
			}
			
			/* Check if currently downloading firmware */
			if (DFU_State == dfuDNLOAD_IDLE)
			{									
				if (!(SentCommand.DataSize))
				{
					DFU_State = dfuIDLE;
				}
				else
				{
					/* Throw away the filler bytes before the start of the firmware */
					DiscardFillerBytes(DFU_FILLER_BYTES_SIZE);

					/* Throw away the page alignment filler bytes before the start of the firmware */
					DiscardFillerBytes(StartAddr % SPM_PAGESIZE);
					
					/* Calculate the number of bytes remaining to be written */
					uint16_t BytesRemaining = ((EndAddr - StartAddr) + 1);
					
					if (IS_ONEBYTE_COMMAND(SentCommand.Data, 0x00))        // Write flash
					{
						/* Calculate the number of words to be written from the number of bytes to be written */
						uint16_t WordsRemaining = (BytesRemaining >> 1);
					
						union
						{
							uint16_t Words[2];
							uint32_t Long;
						} CurrFlashAddress                 = {.Words = {StartAddr, Flash64KBPage}};
						
						uint32_t CurrFlashPageStartAddress = CurrFlashAddress.Long;
						uint8_t  WordsInFlashPage          = 0;

						while (WordsRemaining--)
						{
							/* Check if endpoint is empty - if so clear it and wait until ready for next packet */
							if (!(Endpoint_BytesInEndpoint()))
							{
								Endpoint_ClearOUT();
								while (!(Endpoint_IsOUTReceived()));
							}

							/* Write the next word into the current flash page */
							boot_page_fill(CurrFlashAddress.Long, Endpoint_Read_Word_LE());

							/* Adjust counters */
							WordsInFlashPage      += 1;
							CurrFlashAddress.Long += 2;

							/* See if an entire page has been written to the flash page buffer */
							if ((WordsInFlashPage == (SPM_PAGESIZE >> 1)) || !(WordsRemaining))
							{
								/* Commit the flash page to memory */
								boot_page_write(CurrFlashPageStartAddress);
								boot_spm_busy_wait();
								
								/* Check if programming incomplete */
								if (WordsRemaining)
								{
									CurrFlashPageStartAddress = CurrFlashAddress.Long;
									WordsInFlashPage          = 0;

									/* Erase next page's temp buffer */
									boot_page_erase(CurrFlashAddress.Long);
									boot_spm_busy_wait();
								}
							}
						}
					
						/* Once programming complete, start address equals the end address */
						StartAddr = EndAddr;
					
						/* Re-enable the RWW section of flash */
						boot_rww_enable();
					}
					else                                                   // Write EEPROM
					{
						while (BytesRemaining--)
						{
							/* Check if endpoint is empty - if so clear it and wait until ready for next packet */
							if (!(Endpoint_BytesInEndpoint()))
							{
								Endpoint_ClearOUT();
								while (!(Endpoint_IsOUTReceived()));
							}

							/* Read the byte from the USB interface and write to to the EEPROM */
							eeprom_write_byte((uint8_t*)StartAddr, Endpoint_Read_Byte());
							
							/* Adjust counters */
							StartAddr++;
						}
					}
					
					/* Throw away the currently unused DFU file suffix */
					DiscardFillerBytes(DFU_FILE_SUFFIX_SIZE);
				}
			}

			Endpoint_ClearOUT();

			/* Acknowledge status stage */
			while (!(Endpoint_IsINReady()));
			Endpoint_ClearIN();
				
			break;
		case DFU_UPLOAD:
			Endpoint_ClearSETUP();

			while (!(Endpoint_IsINReady()));

			if (DFU_State != dfuUPLOAD_IDLE)
			{
				if ((DFU_State == dfuERROR) && IS_ONEBYTE_COMMAND(SentCommand.Data, 0x01))       // Blank Check
				{
					/* Blank checking is performed in the DFU_DNLOAD request - if we get here we've told the host
					   that the memory isn't blank, and the host is requesting the first non-blank address */
					Endpoint_Write_Word_LE(StartAddr);
				}
				else
				{
					/* Idle state upload - send response to last issued command */
					Endpoint_Write_Byte(ResponseByte);
				}
			}
			else
			{
				/* Determine the number of bytes remaining in the current block */
				uint16_t BytesRemaining = ((EndAddr - StartAddr) + 1);

				if (IS_ONEBYTE_COMMAND(SentCommand.Data, 0x00))            // Read FLASH
				{
					/* Calculate the number of words to be written from the number of bytes to be written */
					uint16_t WordsRemaining = (BytesRemaining >> 1);

					union
					{
						uint16_t Words[2];
						uint32_t Long;
					} CurrFlashAddress = {.Words = {StartAddr, Flash64KBPage}};

					while (WordsRemaining--)
					{
						/* Check if endpoint is full - if so clear it and wait until ready for next packet */
						if (Endpoint_BytesInEndpoint() == FIXED_CONTROL_ENDPOINT_SIZE)
						{
							Endpoint_ClearIN();
							while (!(Endpoint_IsINReady()));
						}

						/* Read the flash word and send it via USB to the host */
						#if defined(RAMPZ)
							Endpoint_Write_Word_LE(pgm_read_word_far(CurrFlashAddress.Long));
						#else
							Endpoint_Write_Word_LE(pgm_read_word(CurrFlashAddress.Long));							
						#endif

						/* Adjust counters */
						CurrFlashAddress.Long += 2;
					}
					
					/* Once reading is complete, start address equals the end address */
					StartAddr = EndAddr;
				}
				else if (IS_ONEBYTE_COMMAND(SentCommand.Data, 0x02))       // Read EEPROM
				{
					while (BytesRemaining--)
					{
						/* Check if endpoint is full - if so clear it and wait until ready for next packet */
						if (Endpoint_BytesInEndpoint() == FIXED_CONTROL_ENDPOINT_SIZE)
						{
							Endpoint_ClearIN();
							while (!(Endpoint_IsINReady()));
						}

						/* Read the EEPROM byte and send it via USB to the host */
						Endpoint_Write_Byte(eeprom_read_byte((uint8_t*)StartAddr));

						/* Adjust counters */
						StartAddr++;
					}
				}

				/* Return to idle state */
				DFU_State = dfuIDLE;
			}

			Endpoint_ClearIN();

			/* Acknowledge status stage */
			while (!(Endpoint_IsOUTReceived()));
			Endpoint_ClearOUT();

			break;
		case DFU_GETSTATUS:
			Endpoint_ClearSETUP();
			
			/* Write 8-bit status value */
			Endpoint_Write_Byte(DFU_Status);
			
			/* Write 24-bit poll timeout value */
			Endpoint_Write_Byte(0);
			Endpoint_Write_Word_LE(0);
			
			/* Write 8-bit state value */
			Endpoint_Write_Byte(DFU_State);

			/* Write 8-bit state string ID number */
			Endpoint_Write_Byte(0);

			Endpoint_ClearIN();
			
			/* Acknowledge status stage */
			while (!(Endpoint_IsOUTReceived()));
			Endpoint_ClearOUT();
	
			break;		
		case DFU_CLRSTATUS:
			Endpoint_ClearSETUP();
			
			/* Reset the status value variable to the default OK status */
			DFU_Status = OK;

			/* Acknowledge status stage */
			while (!(Endpoint_IsINReady()));
			Endpoint_ClearIN();
			
			break;
		case DFU_GETSTATE:
			Endpoint_ClearSETUP();
			
			/* Write the current device state to the endpoint */
			Endpoint_Write_Byte(DFU_State);
		
			Endpoint_ClearIN();
			
			/* Acknowledge status stage */
			while (!(Endpoint_IsOUTReceived()));
			Endpoint_ClearOUT();

			break;
		case DFU_ABORT:
			Endpoint_ClearSETUP();
			
			/* Reset the current state variable to the default idle state */
			DFU_State = dfuIDLE;
			
			/* Acknowledge status stage */
			while (!(Endpoint_IsINReady()));
			Endpoint_ClearIN();

			break;
	}
}

/** Routine to discard the specified number of bytes from the control endpoint stream. This is used to
 *  discard unused bytes in the stream from the host, including the memory program block suffix.
 *
 *  \param NumberOfBytes  Number of bytes to discard from the host from the control endpoint
 */
static void DiscardFillerBytes(uint8_t NumberOfBytes)
{
	while (NumberOfBytes--)
	{
		if (!(Endpoint_BytesInEndpoint()))
		{
			Endpoint_ClearOUT();

			/* Wait until next data packet received */
			while (!(Endpoint_IsOUTReceived()));
		}

		Endpoint_Discard_Byte();						
	}
}

/** Routine to process an issued command from the host, via a DFU_DNLOAD request wrapper. This routine ensures
 *  that the command is allowed based on the current secure mode flag value, and passes the command off to the
 *  appropriate handler function.
 */
static void ProcessBootloaderCommand(void)
{
	/* Check if device is in secure mode */
	if (IsSecure)
	{
		/* Don't process command unless it is a READ or chip erase command */
		if (!(((SentCommand.Command == COMMAND_WRITE)             &&
		        IS_TWOBYTE_COMMAND(SentCommand.Data, 0x00, 0xFF)) ||
			   (SentCommand.Command == COMMAND_READ)))
		{
			/* Set the state and status variables to indicate the error */
			DFU_State  = dfuERROR;
			DFU_Status = errWRITE;
			
			/* Stall command */
			Endpoint_StallTransaction();
			
			/* Don't process the command */
			return;
		}
	}

	/* Dispatch the required command processing routine based on the command type */
	switch (SentCommand.Command)
	{
		case COMMAND_PROG_START:
			ProcessMemProgCommand();
			break;
		case COMMAND_DISP_DATA:
			ProcessMemReadCommand();
			break;
		case COMMAND_WRITE:
			ProcessWriteCommand();
			break;
		case COMMAND_READ:
			ProcessReadCommand();
			break;
		case COMMAND_CHANGE_BASE_ADDR:
			if (IS_TWOBYTE_COMMAND(SentCommand.Data, 0x03, 0x00))              // Set 64KB flash page command
			  Flash64KBPage = SentCommand.Data[2];

			break;
	}
}

/** Routine to concatenate the given pair of 16-bit memory start and end addresses from the host, and store them
 *  in the StartAddr and EndAddr global variables.
 */
static void LoadStartEndAddresses(void)
{
	union
	{
		uint8_t  Bytes[2];
		uint16_t Word;
	} Address[2] = {{.Bytes = {SentCommand.Data[2], SentCommand.Data[1]}},
	                {.Bytes = {SentCommand.Data[4], SentCommand.Data[3]}}};
		
	/* Load in the start and ending read addresses from the sent data packet */
	StartAddr = Address[0].Word;
	EndAddr   = Address[1].Word;
}

/** Handler for a Memory Program command issued by the host. This routine handles the preparations needed
 *  to write subsequent data from the host into the specified memory.
 */
static void ProcessMemProgCommand(void)
{
	if (IS_ONEBYTE_COMMAND(SentCommand.Data, 0x00) ||                          // Write FLASH command
	    IS_ONEBYTE_COMMAND(SentCommand.Data, 0x01))                            // Write EEPROM command
	{
		/* Load in the start and ending read addresses */
		LoadStartEndAddresses();
		
		/* If FLASH is being written to, we need to pre-erase the first page to write to */
		if (IS_ONEBYTE_COMMAND(SentCommand.Data, 0x00))
		{
			union
			{
				uint16_t Words[2];
				uint32_t Long;
			} CurrFlashAddress = {.Words = {StartAddr, Flash64KBPage}};
			
			/* Erase the current page's temp buffer */
			boot_page_erase(CurrFlashAddress.Long);
			boot_spm_busy_wait();
		}
		
		/* Set the state so that the next DNLOAD requests reads in the firmware */
		DFU_State = dfuDNLOAD_IDLE;
	}
}

/** Handler for a Memory Read command issued by the host. This routine handles the preparations needed
 *  to read subsequent data from the specified memory out to the host, as well as implementing the memory
 *  blank check command.
 */
static void ProcessMemReadCommand(void)
{
	if (IS_ONEBYTE_COMMAND(SentCommand.Data, 0x00) ||                          // Read FLASH command
        IS_ONEBYTE_COMMAND(SentCommand.Data, 0x02))                            // Read EEPROM command
	{
		/* Load in the start and ending read addresses */
		LoadStartEndAddresses();

		/* Set the state so that the next UPLOAD requests read out the firmware */
		DFU_State = dfuUPLOAD_IDLE;
	}
	else if (IS_ONEBYTE_COMMAND(SentCommand.Data, 0x01))                       // Blank check FLASH command
	{
		uint32_t CurrFlashAddress = 0;

		while (CurrFlashAddress < BOOT_START_ADDR)
		{
			/* Check if the current byte is not blank */
			#if defined(RAMPZ)
			if (pgm_read_byte_far(CurrFlashAddress) != 0xFF)
			#else
			if (pgm_read_byte(CurrFlashAddress) != 0xFF)
			#endif
			{
				/* Save the location of the first non-blank byte for response back to the host */
				Flash64KBPage = (CurrFlashAddress >> 16);
				StartAddr     = CurrFlashAddress;
			
				/* Set state and status variables to the appropriate error values */
				DFU_State  = dfuERROR;
				DFU_Status = errCHECK_ERASED;

				break;
			}

			CurrFlashAddress++;
		}
	}
}

/** Handler for a Data Write command issued by the host. This routine handles non-programming commands such as
 *  bootloader exit (both via software jumps and hardware watchdog resets) and flash memory erasure.
 */
static void ProcessWriteCommand(void)
{
	if (IS_ONEBYTE_COMMAND(SentCommand.Data, 0x03))                            // Start application
	{
		/* Indicate that the bootloader is terminating */
		WaitForExit = true;

		/* Check if empty request data array - an empty request after a filled request retains the
		   previous valid request data, but initializes the reset */
		if (!(SentCommand.DataSize))
		{
			if (SentCommand.Data[1] == 0x00)                                   // Start via watchdog
			{
				/* Start the watchdog to reset the AVR once the communications are finalized */
				wdt_enable(WDTO_250MS);
			}
			else                                                               // Start via jump
			{
				/* Load in the jump address into the application start address pointer */
				union
				{
					uint8_t  Bytes[2];
					AppPtr_t FuncPtr;
				} Address = {.Bytes = {SentCommand.Data[4], SentCommand.Data[3]}};

				AppStartPtr = Address.FuncPtr;
				
				/* Set the flag to terminate the bootloader at next opportunity */
				RunBootloader = false;
			}
		}
	}
	else if (IS_TWOBYTE_COMMAND(SentCommand.Data, 0x00, 0xFF))                 // Erase flash
	{
		uint32_t CurrFlashAddress = 0;

		/* Clear the application section of flash */
		while (CurrFlashAddress < BOOT_START_ADDR)
		{
			boot_page_erase(CurrFlashAddress);
			boot_spm_busy_wait();
			boot_page_write(CurrFlashAddress);
			boot_spm_busy_wait();

			CurrFlashAddress += SPM_PAGESIZE;
		}

		/* Re-enable the RWW section of flash as writing to the flash locks it out */
		boot_rww_enable();
					
		/* Memory has been erased, reset the security bit so that programming/reading is allowed */
		IsSecure = false;
	}
}

/** Handler for a Data Read command issued by the host. This routine handles bootloader information retrieval
 *  commands such as device signature and bootloader version retrieval.
 */
static void ProcessReadCommand(void)
{
	const uint8_t BootloaderInfo[3] = {BOOTLOADER_VERSION, BOOTLOADER_ID_BYTE1, BOOTLOADER_ID_BYTE2};
	const uint8_t SignatureInfo[3]  = {SIGNATURE_0, SIGNATURE_1, SIGNATURE_2};

	uint8_t DataIndexToRead = SentCommand.Data[1];

	if (IS_ONEBYTE_COMMAND(SentCommand.Data, 0x00))                         // Read bootloader info
	{
		ResponseByte = BootloaderInfo[DataIndexToRead];
	}
	else if (IS_ONEBYTE_COMMAND(SentCommand.Data, 0x01))                    // Read signature byte
	{
		ResponseByte = SignatureInfo[DataIndexToRead - 0x30];
	}
}
