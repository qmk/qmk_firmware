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
 *  Main source file for the CDC class bootloader. This file contains the complete bootloader logic.
 */
 
#define  INCLUDE_FROM_BOOTLOADERCDC_C
#include "BootloaderCDC.h"

/* Globals: */
/** Line coding options for the virtual serial port. Although the virtual serial port data is never
 *  sent through a physical serial port, the line encoding data must still be read and preserved from
 *  the host, or the host will detect a problem and fail to open the port. This structure contains the
 *  current encoding options, including baud rate, character format, parity mode and total number of 
 *  bits in each data chunk.
 */
CDC_Line_Coding_t LineCoding = { BaudRateBPS: 9600,
                                 CharFormat:  OneStopBit,
                                 ParityType:  Parity_None,
                                 DataBits:    8            };

/** Current address counter. This stores the current address of the FLASH or EEPROM as set by the host,
 *  and is used when reading or writing to the AVRs memory (either FLASH or EEPROM depending on the issued
 *  command.)
 */
uint16_t CurrAddress;

/** Flag to indicate if the bootloader should be running, or should exit and allow the application code to run
 *  via a soft reset. When cleared, the bootloader will abort, the USB interface will shut down and the application
 *  jumped to via an indirect jump to location 0x0000.
 */
bool RunBootloader = true;


/** Main program entry point. This routine configures the hardware required by the bootloader, then continuously 
 *  runs the bootloader processing routine until instructed to soft-exit, or hard-reset via the watchdog to start
 *  the loaded application code.
 */
int main(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
	
	/* Relocate the interrupt vector table to the bootloader section */
	MCUCR = (1 << IVCE);
	MCUCR = (1 << IVSEL);
	
	/* Initialize USB Subsystem */
	USB_Init();

	while (RunBootloader)
	{
		USB_USBTask();
		CDC_Task();
	}
	
	Endpoint_SelectEndpoint(CDC_TX_EPNUM);

	/* Wait until any pending transmissions have completed before shutting down */
	while (!(Endpoint_ReadWriteAllowed()));
	
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
	
	/* Re-enable RWW section */
	boot_rww_enable();

	/* Start the user application */
	AppPtr_t AppStartPtr = (AppPtr_t)0x0000;
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

/** Event handler for the USB_ConfigurationChanged event. This configures the device's endpoints ready
 *  to relay data to and from the attached USB host.
 */
EVENT_HANDLER(USB_ConfigurationChanged)
{
	/* Setup CDC Notification, Rx and Tx Endpoints */
	Endpoint_ConfigureEndpoint(CDC_NOTIFICATION_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_IN, CDC_NOTIFICATION_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(CDC_TX_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_IN, CDC_TXRX_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(CDC_RX_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_OUT, CDC_TXRX_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library, so that they can be handled appropriately
 *  for the application.
 */
EVENT_HANDLER(USB_UnhandledControlPacket)
{
	uint8_t* LineCodingData = (uint8_t*)&LineCoding;

	Endpoint_Discard_Word();

	/* Process CDC specific control requests */
	switch (bRequest)
	{
		case REQ_GetLineEncoding:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSetupReceived();

				for (uint8_t i = 0; i < sizeof(LineCoding); i++)
				  Endpoint_Write_Byte(*(LineCodingData++));	
				
				Endpoint_ClearSetupIN();
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupOUTReceived()));
				Endpoint_ClearSetupOUT();
			}
			
			break;
		case REQ_SetLineEncoding:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSetupReceived();

				while (!(Endpoint_IsSetupOUTReceived()));

				for (uint8_t i = 0; i < sizeof(LineCoding); i++)
				  *(LineCodingData++) = Endpoint_Read_Byte();

				Endpoint_ClearSetupOUT();

				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupINReady()));
				Endpoint_ClearSetupIN();
			}
	
			break;
		case REQ_SetControlLineState:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSetupReceived();
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupINReady()));
				Endpoint_ClearSetupIN();
			}
	
			break;
	}
}

/** Reads or writes a block of EEPROM or FLASH memory to or from the appropriate CDC data endpoint, depending
 *  on the AVR910 protocol command issued.
 *
 *  \param Command  Single character AVR910 protocol command indicating what memory operation to perform
 */
static void ReadWriteMemoryBlock(const uint8_t Command)
{
	uint16_t BlockSize;
	char     MemoryType;
	
	bool     HighByte = false;
	uint8_t  LowByte  = 0;
	
	BlockSize  = (FetchNextCommandByte() << 8);
	BlockSize |=  FetchNextCommandByte();
	
	MemoryType =  FetchNextCommandByte();

	if ((MemoryType == 'E') || (MemoryType == 'F'))
	{
		/* Check if command is to read memory */
		if (Command == 'g')
		{
			/* Re-enable RWW section */
			boot_rww_enable();

			while (BlockSize--)
			{
				if (MemoryType == 'E')
				{
					/* Read the next EEPROM byte into the endpoint */
					WriteNextResponseByte(eeprom_read_byte((uint8_t*)CurrAddress));

					/* Increment the address counter after use */
					CurrAddress++;
				}
				else
				{
					/* Read the next FLASH byte from the current FLASH page */
					#if defined(RAMPZ)
					WriteNextResponseByte(pgm_read_byte_far(((uint32_t)CurrAddress << 1) + HighByte));
					#else
					WriteNextResponseByte(pgm_read_byte((CurrAddress << 1) + HighByte));					
					#endif
					
					/* If both bytes in current word have been read, increment the address counter */
					if (HighByte)
					  CurrAddress++;
					
					HighByte ^= 1;
				}
			}
		}
		else
		{
			uint32_t PageStartAddress = ((uint32_t)CurrAddress << 1);
	
			if (MemoryType == 'F')
			{
				boot_page_erase(PageStartAddress);
				boot_spm_busy_wait();
			}
			
			while (BlockSize--)
			{
				if (MemoryType == 'E')
				{
					/* Write the next EEPROM byte from the endpoint */
					eeprom_write_byte((uint8_t*)CurrAddress, FetchNextCommandByte());					

					/* Increment the address counter after use */
					CurrAddress++;
				}
				else
				{	
					/* If both bytes in current word have been written, increment the address counter */
					if (HighByte)
					{
						/* Write the next FLASH word to the current FLASH page */
						boot_page_fill(((uint32_t)CurrAddress << 1), ((FetchNextCommandByte() << 8) | LowByte));

						HighByte = false;
						
						/* Increment the address counter after use */
						CurrAddress++;
					}
					else
					{
						LowByte = FetchNextCommandByte();
					
						HighByte = true;
					}
				}
			}

			/* If in FLASH programming mode, commit the page after writing */
			if (MemoryType == 'F')
			{
				/* Commit the flash page to memory */
				boot_page_write(PageStartAddress);
				
				/* Wait until write operation has completed */
				boot_spm_busy_wait();
			}
		
			/* Send response byte back to the host */
			WriteNextResponseByte('\r');		
		}
	}
	else
	{
		/* Send error byte back to the host */
		WriteNextResponseByte('?');
	}
}

/** Retrieves the next byte from the host in the CDC data OUT endpoint, and clears the endpoint bank if needed
 *  to allow reception of the next data packet from the host.
 *
 *  \return Next received byte from the host in the CDC data OUT endpoint
 */
static uint8_t FetchNextCommandByte(void)
{
	/* Select the OUT endpoint so that the next data byte can be read */
	Endpoint_SelectEndpoint(CDC_RX_EPNUM);
	
	/* If OUT endpoint empty, clear it and wait for the next packet from the host */
	if (!(Endpoint_ReadWriteAllowed()))
	{
		Endpoint_ClearCurrentBank();
		while (!(Endpoint_ReadWriteAllowed()));
	}
	
	/* Fetch the next byte from the OUT endpoint */
	return Endpoint_Read_Byte();
}

/** Writes the next response byte to the CDC data IN endpoint, and sends the endpoint back if needed to free up the
 *  bank when full ready for the next byte in the packet to the host.
 *
 *  \param Response  Next response byte to send to the host
 */
static void WriteNextResponseByte(const uint8_t Response)
{
	/* Select the IN endpoint so that the next data byte can be written */
	Endpoint_SelectEndpoint(CDC_TX_EPNUM);
	
	/* If OUT endpoint empty, clear it and wait for the next packet from the host */
	if (!(Endpoint_ReadWriteAllowed()))
	{
		Endpoint_ClearCurrentBank();
		while (!(Endpoint_ReadWriteAllowed()));
	}
	
	/* Write the next byte to the OUT endpoint */
	Endpoint_Write_Byte(Response);
}

/** Task to read in AVR910 commands from the CDC data OUT endpoint, process them, perform the required actions
 *  and send the appropriate response back to the host.
 */
TASK(CDC_Task)
{
	/* Select the OUT endpoint */
	Endpoint_SelectEndpoint(CDC_RX_EPNUM);
	
	/* Check if endpoint has a command in it sent from the host */
	if (Endpoint_ReadWriteAllowed())
	{
		/* Read in the bootloader command (first byte sent from host) */
		uint8_t Command = FetchNextCommandByte();

		if ((Command == 'L') || (Command == 'P') || (Command == 'T') || (Command == 'E'))
		{
			if (Command == 'E')
			  RunBootloader = false;
			if (Command == 'T')
			  FetchNextCommandByte();

			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');			
		}
		else if (Command == 't')
		{
			/* Return ATMEGA128 part code - this is only to allow AVRProg to use the bootloader */
			WriteNextResponseByte(0x44);

			WriteNextResponseByte(0x00);
		}
		else if (Command == 'a')
		{
			/* Indicate auto-address increment is supported */
			WriteNextResponseByte('Y');
		}
		else if (Command == 'A')
		{
			/* Set the current address to that given by the host */
			CurrAddress  = (FetchNextCommandByte() << 8);
			CurrAddress |=  FetchNextCommandByte();

			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');
		}
		else if (Command == 'p')
		{
			/* Indicate serial programmer back to the host */
			WriteNextResponseByte('S');		 
		}
		else if (Command == 'S')
		{
			/* Write the 7-byte software identifier to the endpoint */
			for (uint8_t CurrByte = 0; CurrByte < 7; CurrByte++)
			  WriteNextResponseByte(SOFTWARE_IDENTIFIER[CurrByte]);		
		}
		else if (Command == 'V')
		{
			WriteNextResponseByte('0' + BOOTLOADER_VERSION_MAJOR);
			WriteNextResponseByte('0' + BOOTLOADER_VERSION_MINOR);
		}
		else if (Command == 's')
		{
			WriteNextResponseByte(boot_signature_byte_get(4));
			WriteNextResponseByte(boot_signature_byte_get(2));
			WriteNextResponseByte(boot_signature_byte_get(0));		
		}
		else if (Command == 'b')
		{
			WriteNextResponseByte('Y');
				
			/* Send block size to the host */
			WriteNextResponseByte(SPM_PAGESIZE >> 8);
			WriteNextResponseByte(SPM_PAGESIZE & 0xFF);		
		}
		else if (Command == 'e')
		{
			/* Clear the application section of flash */
			for (uint32_t CurrFlashAddress = 0; CurrFlashAddress < BOOT_START_ADDR; CurrFlashAddress++)
			{
				boot_page_erase(CurrFlashAddress);
				boot_spm_busy_wait();
				boot_page_write(CurrFlashAddress);
				boot_spm_busy_wait();

				CurrFlashAddress += SPM_PAGESIZE;
			}
			
			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');		
		}
		else if (Command == 'l')
		{
			/* Set the lock bits to those given by the host */
			boot_lock_bits_set(FetchNextCommandByte());

			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');
		}
		else if (Command == 'r')
		{
			WriteNextResponseByte(boot_lock_fuse_bits_get(GET_LOCK_BITS));		
		}
		else if (Command == 'F')
		{
			WriteNextResponseByte(boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS));
		}
		else if (Command == 'N')
		{
			WriteNextResponseByte(boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS));		
		}
		else if (Command == 'Q')
		{
			WriteNextResponseByte(boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS));		
		}
		else if ((Command == 'C') || (Command == 'c'))
		{
			if (Command == 'c')
			{
				/* Increment the address if the second byte is being written */
				CurrAddress++;
			}
			
			/* Write the high byte to the current flash page */
			boot_page_fill(((uint32_t)CurrAddress << 1), FetchNextCommandByte());
			
			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');		
		}
		else if (Command == 'm')
		{
			/* Commit the flash page to memory */
			boot_page_write((uint32_t)CurrAddress << 1);
			
			/* Wait until write operation has completed */
			boot_spm_busy_wait();

			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');		
		}
		else if ((Command == 'B') || (Command == 'g'))
		{
			/* Delegate the block write/read to a seperate function for clarity */
			ReadWriteMemoryBlock(Command);
		}
		else if (Command == 'R')
		{
			#if defined(RAMPZ)
			uint16_t ProgramWord = pgm_read_word_far(((uint32_t)CurrAddress << 1));
			#else
			uint16_t ProgramWord = pgm_read_word(CurrAddress << 1);			
			#endif
			
			WriteNextResponseByte(ProgramWord >> 8);
			WriteNextResponseByte(ProgramWord & 0xFF);
		}
		else if (Command == 'D')
		{
			/* Read the byte from the endpoint and write it to the EEPROM */
			eeprom_write_byte((uint8_t*)CurrAddress, FetchNextCommandByte());
			
			/* Increment the address after use */			
			CurrAddress++;
	
			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');		
		}
		else if (Command == 'd')
		{
			/* Read the EEPROM byte and write it to the endpoint */
			WriteNextResponseByte(eeprom_read_byte((uint8_t*)CurrAddress));

			/* Increment the address after use */
			CurrAddress++;
		}
		else if (Command == 27)
		{
			/* Escape is sync, ignore */
		}
		else
		{
			/* Unknown command, return fail code */
			WriteNextResponseByte('?');
		}

		/* Select the IN endpoint */
		Endpoint_SelectEndpoint(CDC_TX_EPNUM);

		/* Remember if the endpoint is completely full before clearing it */
		bool IsEndpointFull = !(Endpoint_ReadWriteAllowed());

		/* Send the endpoint data to the host */
		Endpoint_ClearCurrentBank();
		
		/* If a full endpoint's worth of data was sent, we need to send an empty packet afterwards to signal end of transfer */
		if (IsEndpointFull)
		{
			while (!(Endpoint_ReadWriteAllowed()));
			Endpoint_ClearCurrentBank();
		}
		
		/* Select the OUT endpoint */
		Endpoint_SelectEndpoint(CDC_RX_EPNUM);

		/* Acknowledge the command from the host */
		Endpoint_ClearCurrentBank();
	}
}
