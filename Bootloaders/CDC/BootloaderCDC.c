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
 *  Main source file for the CDC class bootloader. This file contains the complete bootloader logic.
 */
 
#define  INCLUDE_FROM_BOOTLOADERCDC_C
#include "BootloaderCDC.h"

/** Line coding options for the virtual serial port. Although the virtual serial port data is never
 *  sent through a physical serial port, the line encoding data must still be read and preserved from
 *  the host, or the host will detect a problem and fail to open the port. This structure contains the
 *  current encoding options, including baud rate, character format, parity mode and total number of 
 *  bits in each data chunk.
 */
CDC_Line_Coding_t LineCoding = { .BaudRateBPS = 9600,
                                 .CharFormat  = OneStopBit,
                                 .ParityType  = Parity_None,
                                 .DataBits    = 8            };

/** Current address counter. This stores the current address of the FLASH or EEPROM as set by the host,
 *  and is used when reading or writing to the AVRs memory (either FLASH or EEPROM depending on the issued
 *  command.)
 */
uint32_t CurrAddress;

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
	/* Setup hardware required for the bootloader */
	SetupHardware();

	while (RunBootloader)
	{
		CDC_Task();
		USB_USBTask();
	}
	
	/* Reset all configured hardware to their default states for the user app */
	ResetHardware();

	/* Start the user application */
	AppPtr_t AppStartPtr = (AppPtr_t)0x0000;
	AppStartPtr();	
}

/** Configures all hardware required for the bootloader. */
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
	
	/* Initialize USB Subsystem */
	USB_Init();
}

/** Resets all configured hardware required for the bootloader back to their original states. */
void ResetHardware(void)
{
	/* Shut down the USB subsystem */
	USB_ShutDown();
	
	/* Relocate the interrupt vector table back to the application section */
	MCUCR = (1 << IVCE);
	MCUCR = 0;

	/* Re-enable RWW section */
	boot_rww_enable();
}

/** Event handler for the USB_ConfigurationChanged event. This configures the device's endpoints ready
 *  to relay data to and from the attached USB host.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
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

/** Event handler for the USB_UnhandledControlRequest event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library, so that they can be handled appropriately
 *  for the application.
 */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	uint8_t* LineCodingData = (uint8_t*)&LineCoding;

	/* Process CDC specific control requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				for (uint8_t i = 0; i < sizeof(LineCoding); i++)
				  Endpoint_Write_Byte(*(LineCodingData++));	
				
				Endpoint_ClearIN();
				
				Endpoint_ClearStatusStage();
			}
			
			break;
		case REQ_SetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				while (!(Endpoint_IsOUTReceived()))
				{				
					if (USB_DeviceState == DEVICE_STATE_Unattached)
					  return;
				}
			
				for (uint8_t i = 0; i < sizeof(LineCoding); i++)
				  *(LineCodingData++) = Endpoint_Read_Byte();

				Endpoint_ClearOUT();

				Endpoint_ClearStatusStage();
			}
	
			break;
		case REQ_SetControlLineState:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				Endpoint_ClearStatusStage();
			}
	
			break;
	}
}

/** Reads or writes a block of EEPROM or FLASH memory to or from the appropriate CDC data endpoint, depending
 *  on the AVR910 protocol command issued.
 *
 *  \param[in] Command  Single character AVR910 protocol command indicating what memory operation to perform
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

	if ((MemoryType != 'E') && (MemoryType != 'F'))
	{
		/* Send error byte back to the host */
		WriteNextResponseByte('?');
		
		return;
	}

	/* Check if command is to read memory */
	if (Command == 'g')
	{
		/* Re-enable RWW section */
		boot_rww_enable();

		while (BlockSize--)
		{
			if (MemoryType == 'F')
			{
				/* Read the next FLASH byte from the current FLASH page */
				#if (FLASHEND > 0xFFFF)
				WriteNextResponseByte(pgm_read_byte_far(CurrAddress | HighByte));
				#else
				WriteNextResponseByte(pgm_read_byte(CurrAddress | HighByte));					
				#endif
				
				/* If both bytes in current word have been read, increment the address counter */
				if (HighByte)
				  CurrAddress += 2;
				
				HighByte = !HighByte;
			}
			else
			{
				/* Read the next EEPROM byte into the endpoint */
				WriteNextResponseByte(eeprom_read_byte((uint8_t*)(uint16_t)(CurrAddress >> 1)));

				/* Increment the address counter after use */
				CurrAddress += 2;
			}			
		}
	}
	else
	{
		uint32_t PageStartAddress = CurrAddress;

		if (MemoryType == 'F')
		{
			boot_page_erase(PageStartAddress);
			boot_spm_busy_wait();
		}
		
		while (BlockSize--)
		{
			if (MemoryType == 'F')
			{	
				/* If both bytes in current word have been written, increment the address counter */
				if (HighByte)
				{
					/* Write the next FLASH word to the current FLASH page */
					boot_page_fill(CurrAddress, ((FetchNextCommandByte() << 8) | LowByte));

					/* Increment the address counter after use */
					CurrAddress += 2;

					HighByte = false;
				}
				else
				{
					LowByte = FetchNextCommandByte();
				
					HighByte = true;
				}
			}
			else
			{
				/* Write the next EEPROM byte from the endpoint */
				eeprom_write_byte((uint8_t*)(uint16_t)(CurrAddress >> 1), FetchNextCommandByte());					

				/* Increment the address counter after use */
				CurrAddress += 2;
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
	while (!(Endpoint_IsReadWriteAllowed()))
	{
		Endpoint_ClearOUT();

		while (!(Endpoint_IsOUTReceived()))
		{
			if (USB_DeviceState == DEVICE_STATE_Unattached)
			  return 0;
		}
	}
	
	/* Fetch the next byte from the OUT endpoint */
	return Endpoint_Read_Byte();
}

/** Writes the next response byte to the CDC data IN endpoint, and sends the endpoint back if needed to free up the
 *  bank when full ready for the next byte in the packet to the host.
 *
 *  \param[in] Response  Next response byte to send to the host
 */
static void WriteNextResponseByte(const uint8_t Response)
{
	/* Select the IN endpoint so that the next data byte can be written */
	Endpoint_SelectEndpoint(CDC_TX_EPNUM);
	
	/* If IN endpoint full, clear it and wait until ready for the next packet to the host */
	if (!(Endpoint_IsReadWriteAllowed()))
	{
		Endpoint_ClearIN();
		
		while (!(Endpoint_IsINReady()))
		{				
			if (USB_DeviceState == DEVICE_STATE_Unattached)
			  return;
		}
	}
	
	/* Write the next byte to the OUT endpoint */
	Endpoint_Write_Byte(Response);
}

/** Task to read in AVR910 commands from the CDC data OUT endpoint, process them, perform the required actions
 *  and send the appropriate response back to the host.
 */
void CDC_Task(void)
{
	/* Select the OUT endpoint */
	Endpoint_SelectEndpoint(CDC_RX_EPNUM);
	
	/* Check if endpoint has a command in it sent from the host */
	if (Endpoint_IsOUTReceived())
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
			CurrAddress   = (FetchNextCommandByte() << 9);
			CurrAddress  |= (FetchNextCommandByte() << 1);

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
			WriteNextResponseByte(AVR_SIGNATURE_3);		
			WriteNextResponseByte(AVR_SIGNATURE_2);
			WriteNextResponseByte(AVR_SIGNATURE_1);
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
		else if (Command == 'C')
		{			
			/* Write the high byte to the current flash page */
			boot_page_fill(CurrAddress, FetchNextCommandByte());

			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');		
		}
		else if (Command == 'c')
		{			
			/* Write the low byte to the current flash page */
			boot_page_fill(CurrAddress | 1, FetchNextCommandByte());
			
			/* Increment the address */
			CurrAddress += 2;

			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');		
		}
		else if (Command == 'm')
		{
			/* Commit the flash page to memory */
			boot_page_write(CurrAddress);
			
			/* Wait until write operation has completed */
			boot_spm_busy_wait();

			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');		
		}
		else if ((Command == 'B') || (Command == 'g'))
		{
			/* Delegate the block write/read to a separate function for clarity */
			ReadWriteMemoryBlock(Command);
		}
		else if (Command == 'R')
		{
			#if (FLASHEND > 0xFFFF)
			uint16_t ProgramWord = pgm_read_word_far(CurrAddress);
			#else
			uint16_t ProgramWord = pgm_read_word(CurrAddress);			
			#endif
			
			WriteNextResponseByte(ProgramWord >> 8);
			WriteNextResponseByte(ProgramWord & 0xFF);
		}
		else if (Command == 'D')
		{
			/* Read the byte from the endpoint and write it to the EEPROM */
			eeprom_write_byte((uint8_t*)((uint16_t)(CurrAddress >> 1)), FetchNextCommandByte());
			
			/* Increment the address after use */			
			CurrAddress += 2;
	
			/* Send confirmation byte back to the host */
			WriteNextResponseByte('\r');		
		}
		else if (Command == 'd')
		{
			/* Read the EEPROM byte and write it to the endpoint */
			WriteNextResponseByte(eeprom_read_byte((uint8_t*)((uint16_t)(CurrAddress >> 1))));

			/* Increment the address after use */
			CurrAddress += 2;
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
		bool IsEndpointFull = !(Endpoint_IsReadWriteAllowed());

		/* Send the endpoint data to the host */
		Endpoint_ClearIN();
		
		/* If a full endpoint's worth of data was sent, we need to send an empty packet afterwards to signal end of transfer */
		if (IsEndpointFull)
		{
			while (!(Endpoint_IsINReady()))
			{				
				if (USB_DeviceState == DEVICE_STATE_Unattached)
				  return;
			}

			Endpoint_ClearIN();
		}

		/* Wait until the data has been sent to the host */
		while (!(Endpoint_IsINReady()))
		{				
			if (USB_DeviceState == DEVICE_STATE_Unattached)
			  return;
		}
		
		/* Select the OUT endpoint */
		Endpoint_SelectEndpoint(CDC_RX_EPNUM);

		/* Acknowledge the command from the host */
		Endpoint_ClearOUT();
	}
}
