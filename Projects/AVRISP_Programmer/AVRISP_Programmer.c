/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  AVR ISP Programmer code Copyright 2009  Opendous Inc. (www.opendous.org)
  For more info and usage instructions for this firmware, visit:
  http://code.google.com/p/avropendous/wiki/AVR_ISP_Programmer

  Note that this firmware is designed to work with AVRdude:
  http://savannah.nongnu.org/projects/avrdude
  But should work with other software that supports the AVR910 ISP
  programmer or STK200 hardware.

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

/*
    Usage:
     avrdude -vv -F -P COM7 -c avr910 -p t261
       Note -F flag which overrides signature check and enables programming
       of any "In-System Programmable via SPI Port" AVR MCU.  Part number,
       t261, should be set to your target device.
     avrdude -vv -F -P COM7 -c avr910 -p t261 -U flash:w:PROG.hex
       PROG.hex is the hex file to program your t261 AVR with
     avrdude -vv -F -P COM7 -b 115200 -c avr910 -p t261 -U flash:w:test.hex
       The -b 115200 sets the SPI clock to 62.5kHz from the default 125kHz and may
       work when the default programming speed fails.
     AVROSP.exe -dATtiny261 -cCOM7 -rf
       AVRosp is the Open Source AVR ISP Programming Software available from Atmel.com

    Note: on Linux systems, COM7 should be replaced with someting like /dev/ttyACM0
          You can determine this value by running dmesg after plugging in the device
    Note: you must RESET the programmer after each use (AVRdude session).

    Note: If you experience errors with older devices, try changing the DELAY defines

    MISO, MOSI, and SCK are connected directly from the AVRopendous board
    to the pin of the same functionality on the target.  RESET pin on the target
    can be connected either to SS (PB0), or PC2.  Do not have any other pins
    connected - especially HWB pin, to avoid unintentional behaviour.

    AVR910 functionality was overlayed on USBtoSerial  functionality.
    Keep this in mind when looking over the code.
    Default target speed is 125kHz and corresponds to 19200 baud, which
    is the default setting for AVRdude.

    Changing "Baud-Rate" will change the SPI speed.  Defualt SPI clock speed
    is 8Mhz / 4 = 2MHz.  8Mhz is the device clock speed.  This is the setting at
    9600 baud.  The following is a table of baud-rate vs. SPI Speed that will result
         9600 = 2Mhz
         14400 = 1MHz
         19200 = 125kHz (AVRdude Default)
         38400 = 250kHz
         57600 = 500kHz
         115200 = 62.5kHz

	Before running, you will need to install the INF file that
	is located in the project directory. This will enable
	Windows to use its inbuilt CDC drivers, negating the need
	for special Windows drivers for the device. To install,
	right-click the .INF file and choose the Install option.
*/

/*	TODO: - fix the requirement that a RESET must be performed after each session, which
            is only an issue under Windows.  Everything works fine under Linux
*/

#include "AVRISP_Programmer.h"

/* Project Tags, for reading out using the ButtLoad project */
BUTTLOADTAG(ProjName,    "LUFA AVR910 ISP Programmer");
BUTTLOADTAG(BuildTime,   __TIME__);
BUTTLOADTAG(BuildDate,   __DATE__);
BUTTLOADTAG(LUFAVersion, "LUFA V" LUFA_VERSION_STRING);


#define RESETPORT       PORTB
#define RESETPIN        PB0
#define RESETPORT2      PORTC
#define RESETPIN2       PC2
#define CR_HEX          '\r'

#define DELAY_VERYSHORT    0x01
#define DELAY_SHORT        0x02
#define DELAY_MEDIUM       0x03
#define DELAY_LONG         0x05
#define DELAY_MULTIPLE     0x02


/*  AVR Device Codes - Can have a maximum of 14 but can be any you want.
    Note that these are completely irrelevent.  If AVRdude supports a device,
    then that device is programmable.  Use -F switch to ignore device codes. */
#define AVRDEVCODE01	0x55 /* ATtiny12 */
#define AVRDEVCODE02	0x56 /* ATtiny15 */
#define AVRDEVCODE03	0x5E /* ATtiny261 */
#define AVRDEVCODE04	0x76 /* ATmega8 */
#define AVRDEVCODE05	0x74 /* ATmega16 */
#define AVRDEVCODE06	0x72 /* ATmega32 */
#define AVRDEVCODE07	0x45 /* ATmega64 */
#define AVRDEVCODE08	0x74 /* ATmega644 */
#define AVRDEVCODE09	0x43 /* ATmega128 */
#define AVRDEVCODE10	0x63 /* ATmega162 */
#define AVRDEVCODE11	0x78 /* ATmega169 */
#define AVRDEVCODE12	0x6C /* AT90S4434 */
#define AVRDEVCODE13	0x38 /* AT90S8515A */
#define AVRDEVCODE14	0x65 /* AT90S8555 */


/* Scheduler Task List */
TASK_LIST
{
	{ Task: USB_USBTask          , TaskStatus: TASK_STOP },
	{ Task: CDC_Task             , TaskStatus: TASK_STOP },
};

/* Globals: */
/** Contains the current baud rate and other settings of the virtual serial port.
 *
    These values are set by the host via a class-specific request, and the physical USART should be reconfigured to match the
    new settings each time they are changed by the host.
 */
CDC_Line_Coding_t LineCoding = { BaudRateBPS: 9600,
                                 CharFormat:  OneStopBit,
                                 ParityType:  Parity_None,
                                 DataBits:    8            };

/** Ring (circular) buffer to hold the RX data - data from the host to the attached device on the serial port. */
RingBuff_t Rx_Buffer;

/** Ring (circular) buffer to hold the TX data - data from the attached device on the serial port to the host. */
RingBuff_t Tx_Buffer;

/** Flag to indicate if the USART is currently transmitting data from the Rx_Buffer circular buffer. */
volatile bool Transmitting = false;

/* some global variables used throughout */
uint16_t currAddress = 0;

/** Main program entry point. This routine configures the hardware required by the application, then
    starts the scheduler to run the application tasks.
 */
int main(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	LEDs_Init();
	ReconfigureSPI();

	DDRC |= ((1 << PC2) | (1 << PC4) | (1 << PC5) | (1 << PC6) | (1 << PC7)); //AT90USBxx2
	// PC2 is also used for RESET, so set it HIGH initially - note 'P' command sets it to LOW (Active)
	PORTC |= ((1 << PC2) | (1 << PC4) | (1 << PC5) | (1 << PC6) | (1 << PC7)); //AT90USBxx2
	DDRD = 0;
	PORTD = (1 << PB7); // only PB7(HWB) should be High as this is the bootloader pin
	// Prepare PortB for SPI - set PB0(^SS), PB1(SCK), PB2(MOSI) as output as well as all other pins except PB3(MISO)
	DDRB = (1 << PB0) | (1 << PB1) | (1 << PB2) | (0 << PB3) | (1 << PB4) | (1 << PB5) | (1 << PB6) | (1 << PB7);
	PORTB |= (1 << PB0);
    // make sure DataFlash devices to not interfere - deselect them by setting PE0 and PE1 HIGH:
    PORTE = 0xFF;
    DDRE  = 0xFF;

	/* Ringbuffer Initialization */
	Buffer_Initialize(&Rx_Buffer);
	Buffer_Initialize(&Tx_Buffer);
	
	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
	
	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();

	/* Scheduling - routine never returns, so put this last in the main function */
	Scheduler_Start();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and
    starts the library USB task to begin the enumeration and USB management process.
 */
EVENT_HANDLER(USB_Connect)
{
	/* Start USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);

	/* Indicate USB enumerating */
	UpdateStatus(Status_USBEnumerating);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
    the status LEDs and stops the USB management and CDC management tasks.
 */
EVENT_HANDLER(USB_Disconnect)
{
	/* Stop running CDC and USB management tasks */
	Scheduler_SetTaskMode(CDC_Task, TASK_STOP);
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);

	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
    of the USB device after enumeration - the device endpoints are configured and the CDC management task started.
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

	/* Indicate USB connected and ready */
	UpdateStatus(Status_USBReady);

	/* Start CDC task */
	Scheduler_SetTaskMode(CDC_Task, TASK_RUN);
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
    control requests that are not handled internally by the USB library (including the CDC control commands,
    which are all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
EVENT_HANDLER(USB_UnhandledControlPacket)
{
	uint8_t* LineCodingData = (uint8_t*)&LineCoding;

	/* Process CDC specific control requests */
	switch (bRequest)
	{
		case REQ_GetLineEncoding:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{	
				/* Acknowedge the SETUP packet, ready for data transfer */
				Endpoint_ClearSetupReceived();

				/* Write the line coding data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(LineCodingData, sizeof(LineCoding));
				
				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearSetupOUT();
			}
			
			break;
		case REQ_SetLineEncoding:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Acknowedge the SETUP packet, ready for data transfer */
				Endpoint_ClearSetupReceived();

				/* Read the line coding data in from the host into the global struct */
				Endpoint_Read_Control_Stream_LE(LineCodingData, sizeof(LineCoding));

				/* Finalize the stream transfer to clear the last packet from the host */
				Endpoint_ClearSetupIN();
				
				/* Reconfigure the USART with the new settings */
				ReconfigureSPI();
			}
	
			break;
		case REQ_SetControlLineState:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Acknowedge the SETUP packet, ready for data transfer */
				Endpoint_ClearSetupReceived();
				
				/* Send an empty packet to acknowedge the command */
				Endpoint_ClearSetupIN();
			}
	
			break;
	}
}

/** Task to manage CDC data transmission and reception to and from the host, from and to the physical USART. */
TASK(CDC_Task)
{
	if (USB_IsConnected)
	{
		/* Select the Serial Rx Endpoint */
		Endpoint_SelectEndpoint(CDC_RX_EPNUM);
		
		if (Endpoint_ReadWriteAllowed())
		{
			/* Read the received data endpoint into the transmission buffer */
			while (Endpoint_BytesInEndpoint())
			{
				/* Wait until the buffer has space for a new character */
				while (!((BUFF_STATICSIZE - Rx_Buffer.Elements)));
			
				/* Store each character from the endpoint */
				Buffer_StoreElement(&Rx_Buffer, Endpoint_Read_Byte());

                /* Run the given command once enough data is available. */
                if (Rx_Buffer.Elements)
				{
					const uint8_t ZeroDataByteCommands[]  = {'P', 'a', 'm', 'R', 'd', 'e', 'L', 's', 't', 'S', 'V', 'v', 'p', 'F'};
					const uint8_t OneDataByteCommands[]   = {'T', 'c', 'C', 'D', 'l', 'f', 'x', 'y'};
					const uint8_t TwoDataByteCommands[]   = {'A', 'Z'};
					const uint8_t ThreeDataByteCommands[] = {':'};
					const uint8_t FourDataByteCommands[]  = {'.'};
					
					const struct
					{
						const uint8_t  TotalCommands;
						const uint8_t* CommandBytes;
					} AVR910Commands[] = {{sizeof(ZeroDataByteCommands),  ZeroDataByteCommands},
					                      {sizeof(OneDataByteCommands),   OneDataByteCommands},
					                      {sizeof(TwoDataByteCommands),   TwoDataByteCommands},
					                      {sizeof(ThreeDataByteCommands), ThreeDataByteCommands},
					                      {sizeof(FourDataByteCommands),  FourDataByteCommands}};
					
					/* Determine the data length of the issued command */
					uint8_t CommandDataLength = (Rx_Buffer.Elements - 1);
					
					/* Loop through each of the possible command bytes allowable from the given command data length */
					for (uint8_t CurrentCommand = 0; CurrentCommand < AVR910Commands[CommandDataLength].TotalCommands; CurrentCommand++)
					{
						/* If issues command matches an allowable command, process it */
						if (Buffer_PeekElement(&Rx_Buffer) == AVR910Commands[CommandDataLength].CommandBytes[CurrentCommand])
						  processHostSPIRequest();
					}
                }
			}
			
			/* Clear the endpoint buffer */
			Endpoint_ClearCurrentBank();
		}

		/* Select the Serial Tx Endpoint */
		Endpoint_SelectEndpoint(CDC_TX_EPNUM);

		/* Check if the Tx buffer contains anything to be sent to the host */
		if (Tx_Buffer.Elements)
		{
			/* Wait until Serial Tx Endpoint Ready for Read/Write */
			while (!(Endpoint_ReadWriteAllowed()));
			
			/* Check before sending the data if the endpoint is completely full */
			bool IsFull = (Endpoint_BytesInEndpoint() == CDC_TXRX_EPSIZE);
			
			/* Write the transmission buffer contents to the received data endpoint */
			while (Tx_Buffer.Elements && (Endpoint_BytesInEndpoint() < CDC_TXRX_EPSIZE))
			  Endpoint_Write_Byte(Buffer_GetElement(&Tx_Buffer));
			
			/* Send the data */
			Endpoint_ClearCurrentBank();

			/* If a full endpoint was sent, we need to send an empty packet afterwards to terminate the transfer */
			if (IsFull)
			{
				/* Wait until Serial Tx Endpoint Ready for Read/Write */
				while (!(Endpoint_ReadWriteAllowed()));

				/* Send an empty packet to terminate the transfer */
				Endpoint_ClearCurrentBank();
			}
		}
	}
}

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the USBtoSerial_StatusCodes_t enum
 */
void UpdateStatus(uint8_t CurrentStatus)
{
	uint8_t LEDMask = LEDS_NO_LEDS;
	
	/* Set the LED mask to the appropriate LED mask based on the given status code */
	switch (CurrentStatus)
	{
		case Status_USBNotReady:
			LEDMask = (LEDS_LED1);
			break;
		case Status_USBEnumerating:
			LEDMask = (LEDS_LED1 | LEDS_LED2);
			break;
		case Status_USBReady:
			LEDMask = (LEDS_LED2 | LEDS_LED4);
			break;
	}
	
	/* Set the board LEDs to the new LED mask */
	LEDs_SetAllLEDs(LEDMask);
}

/** Reconfigures SPI to match the current serial port settings issued by the host. */
void ReconfigureSPI(void)
{
	uint8_t SPCRmask = (1 << SPE) | (1 << MSTR); // always enable SPI as Master
	uint8_t SPSRmask = 0;

	/* Determine stop bits - 1.5 stop bits is set as 1 stop bit due to hardware limitations */
	/* For SPI, determine whether format is LSB or MSB */
	if (LineCoding.CharFormat == TwoStopBits) {	
		SPCRmask |= (1 << DORD);
	} else if (LineCoding.CharFormat == OneStopBit) {
		SPCRmask |= (0 << DORD);
	}

	/* Determine data size - 5, 6, 7, or 8 bits are supported */
	/* Changing line coding changes SPI Mode
		CPOL=0, CPHA=0 Sample (Rising) Setup (Falling) SPI-Mode0 == 8 bits line coding
		CPOL=0, CPHA=1 Setup (Rising) Sample (Falling) SPI-Mode1 == 7 bits line coding
		CPOL=1, CPHA=0 Sample (Falling) Setup (Rising) SPI-Mode2 == 6 bits line coding
		CPOL=1, CPHA=1 Setup (Falling) Sample (Rising) SPI-Mode3 == 5 bits line coding
	*/
	if (LineCoding.DataBits == 5) {
		SPCRmask |= ((1 << CPOL) | (1 << CPHA));
	} else if (LineCoding.DataBits == 6) {
		SPCRmask |= ((1 << CPOL) | (0 << CPHA));
	} else if (LineCoding.DataBits == 7) {
		SPCRmask |= ((0 << CPOL) | (1 << CPHA));
	} else if (LineCoding.DataBits == 8) {
		SPCRmask |= ((0 << CPOL) | (0 << CPHA));
	}


	/* Set the USART baud rate register to the desired baud rate value */
	/* also alter the SPI speed via value of baud rate */
	if        (LineCoding.BaudRateBPS == 9600) {	// 2Mhz SPI (Fosc / 4)
		SPCRmask |= ((0 << SPR1) | (0 << SPR0));
		SPSRmask |= (0 << SPI2X);
	} else if (LineCoding.BaudRateBPS == 14400) {	// 1Mhz SPI (Fosc / 8)
		SPCRmask |= ((0 << SPR1) | (1 << SPR0));
		SPSRmask |= (1 << SPI2X);
	} else if (LineCoding.BaudRateBPS == 57600) {	// 500kHz SPI (Fosc / 16)
		SPCRmask |= ((0 << SPR1) | (1 << SPR0));
		SPSRmask |= (0 << SPI2X);
	} else if (LineCoding.BaudRateBPS == 38400) {	// 250kHz SPI (Fosc / 32)
		SPCRmask |= ((1 << SPR1) | (0 << SPR0));
		SPSRmask |= (1 << SPI2X);
	} else if (LineCoding.BaudRateBPS == 19200) {	// 125kHz SPI (Fosc / 64)
		SPCRmask |= ((1 << SPR1) | (0 << SPR0));
		SPSRmask |= (0 << SPI2X);
	} else if (LineCoding.BaudRateBPS == 115200) {	// 62.5kHz SPI (Fosc / 128)
		SPCRmask |= ((1 << SPR1) | (1 << SPR0));
		SPSRmask |= (0 << SPI2X);
	}

	SPCR = SPCRmask;
	SPSR = SPSRmask;
}


/* process data according to AVR910 protocol */
void processHostSPIRequest(void) {

	uint8_t readByte1 = 0;
	uint8_t readByte2 = 0;
	uint8_t readByte3 = 0;
	uint8_t readByte4 = 0;
	uint8_t firstByte = 0;

	/*	Taken from a90isp_ver23.asm:
		+-------------+------------+------+
		;*  Commands                           | Host writes | Host reads |      |
		;*  --------                           +-----+-------+------+-----+      |
		;*                                     | ID  | data  | data |     | Note |
		;* +-----------------------------------+-----+-------+------+-----+------+
		;* | Enter programming mode            | 'P' |       |      | 13d |   1  |
		;* | Report autoincrement address      | 'a' |       | 	    | 'Y' |      |
		;* | Set address                       | 'A' | ah al |      | 13d |   2  |
		;* | Write program memory, low byte    | 'c' |    dd |      | 13d |   3  |
		;* | Write program memory, high byte   | 'C' |    dd |      | 13d |   3  |
		;* | Issue Page Write                  | 'm' |       |      | 13d |      |
		;* | Read program memory               | 'R' |       |dd(dd)|     |   4  |
		;* | Write data memory                 | 'D' |    dd |      | 13d |      |
		;* | Read data memory                  | 'd' |       |   dd |     |      |
		;* | Chip erase                        | 'e' |       |      | 13d |      |
		;* | Write lock bits                   | 'l' |    dd |      | 13d |      |
		;* | Write fuse bits                   | 'f' |    dd |      | 13d |  11  |
		;* | Read fuse and lock bits           | 'F' |       |   dd |     |  11  |
		;* | Leave programming mode            | 'L' |       |      | 13d |   5  |
		;* | Select device type                | 'T' |    dd |      | 13d |   6  |
		;* | Read signature bytes              | 's' |       | 3*dd |     |      |
		;* | Return supported device codes     | 't' |       | n*dd | 00d |   7  |
		;* | Return software identifier        | 'S' |       | s[7] |     |   8  |
		;* | Return sofware version            | 'V' |       |dd dd |     |   9  |
		;* | Return hardware version           | 'v' |       |dd dd |     |   9  |
		;* | Return programmer type            | 'p' |       |   dd |     |  10  |
		;* | Set LED                           | 'x' |    dd |      | 13d |  12  |
		;* | Clear LED                         | 'y' |    dd |      | 13d |  12  |
		;* | Universial command                | ':' |  3*dd |   dd | 13d |      |
		;* | New universal command	           | '.' |  4*dd |   dd | 13d |      |
		;* | Special test command	           | 'Z' |  2*dd |   dd |     |      |
	*/

	firstByte = Buffer_GetElement(&Rx_Buffer);
	Buffer_Initialize(&Tx_Buffer); // make sure the buffer is clear before proceeding

	if        (firstByte == 'P') { // enter Programming mode
		// enable SPI -- already done
		// enter programming mode on target:
		//PORTB = 0; // set clock to zero
		RESETPORT = (1 << RESETPIN); // set RESET pin on target to 1
		RESETPORT2 = (1 << RESETPIN2);
		_delay_ms(DELAY_SHORT);
		//RESETPORT = (RESETPORT & ~(1 << RESETPIN)); // set RESET pin on target to 0 - Active
		RESETPORT = 0x00;
		RESETPORT2 = 0;
		_delay_ms(DELAY_SHORT);
		SPI_SendByte(0xAC);
		SPI_SendByte(0x53);
		SPI_SendByte(0x00);
		SPI_SendByte(0x00);
		_delay_ms(DELAY_VERYSHORT);
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'T') { // Select device type
		Buffer_GetElement(&Rx_Buffer); // set device type
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'a') { // Report autoincrement address
		Buffer_StoreElement(&Tx_Buffer, 'Y'); // return 'Y' - Auto-increment enabled

	} else if (firstByte == 'A') { //Load Address
		// get two bytes over serial and set currAddress to them
		readByte1 = Buffer_GetElement(&Rx_Buffer); // high byte
		readByte2 = Buffer_GetElement(&Rx_Buffer); // low byte
		currAddress = (readByte1 << 8) | (readByte2);
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'c') { // Write program memory, low byte
		// send 4 bytes over SPI; 0x40, then Address High Byte, then Low, then data
		readByte1 = Buffer_GetElement(&Rx_Buffer);
		SPI_SendByte(0x40);
		SPI_SendByte((currAddress >> 8)); // high byte
		SPI_SendByte((currAddress)); // low byte
		SPI_SendByte(readByte1); // data
		_delay_ms(DELAY_MEDIUM); // certain MCUs require a delay of about 24585 cycles
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'C') { // Write program memory, high byte
		// send 4 bytes over SPI; 0x48, then Address High Byte, then Low, then data
		readByte1 = Buffer_GetElement(&Rx_Buffer);
		SPI_SendByte(0x48);
		SPI_SendByte((currAddress >> 8)); // high byte
		SPI_SendByte((currAddress)); // low byte
		SPI_SendByte(readByte1); // data
		currAddress++; // increment currAddress
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'm') { // Write Program Memory Page
		// send 4 bytes over SPI; 0x4c, then Address High Byte, then Low, then 0x00
		SPI_SendByte(0x4C);
		SPI_SendByte((currAddress >> 8)); // high byte
		SPI_SendByte((currAddress)); // low byte
		SPI_SendByte(0x00);
		_delay_ms(DELAY_LONG);
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'R') { // Read Program Memory
		// send 4 bytes over SPI; 0x28, then Address High Byte, then Low, then send back read data from 4th byte over serial
		SPI_SendByte(0x28);
		SPI_SendByte((currAddress >> 8)); // high byte
		SPI_SendByte((currAddress)); // low byte
		readByte1 = SPI_TransferByte(0x00); // read in data
		Buffer_StoreElement(&Tx_Buffer, readByte1);
		// send 4 bytes over SPI; 0x20, then Address High Byte, then Low, then send back read data from 4th byte over serial
		SPI_SendByte(0x20);
		SPI_SendByte((currAddress >> 8)); // high byte
		SPI_SendByte((currAddress)); // low byte
		readByte2 = SPI_TransferByte(0x00); // read in data
		Buffer_StoreElement(&Tx_Buffer, readByte2);
		currAddress++; // increment currAddress

	} else if (firstByte == 'D') { // Write Data Memory
		// send 4 bytes over SPI; 0xc0, then Address High Byte, then Low, then data
		readByte1 = Buffer_GetElement(&Rx_Buffer);
		SPI_SendByte(0xC0);
		SPI_SendByte((currAddress >> 8)); // high byte
		SPI_SendByte((currAddress)); // low byte
		SPI_SendByte(readByte1); // data
		_delay_ms(DELAY_MEDIUM);
		currAddress++; // increment currAddress
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'd') { // Read Data Memory
		// send 4 bytes over SPI; 0xa0, then Address High Byte, then Low, then send back read data from 4th byte over serial
		SPI_SendByte(0xA0);
		SPI_SendByte((currAddress >> 8)); // high byte
		SPI_SendByte((currAddress)); // low byte
		readByte1 = SPI_TransferByte(0x00); // read in data
		Buffer_StoreElement(&Tx_Buffer, readByte1);
		currAddress++; // increment currAddress

	} else if (firstByte == 'e') { // erase the target device
		// send 4 bytes over SPI; 0xac, 0x80, 0x04, 0x00
		SPI_SendByte(0xAC);
		SPI_SendByte(0x80);
		SPI_SendByte(0x04);
		SPI_SendByte(0x00);
		_delay_ms(DELAY_LONG);
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'l') { // write lock bits
		// send 4 bytes over SPI; 0xac, [andi s_data 0x06], 0xe0, 0x00
		readByte1 = Buffer_GetElement(&Rx_Buffer); // read in lock bits data
		SPI_SendByte(0xAC);
		SPI_SendByte(((0x06 & readByte1) | 0xE0)); // TODO - is this correct???
		SPI_SendByte(0x00);
		SPI_SendByte(0x00);
		_delay_ms(DELAY_MEDIUM);
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'f') { // write fuse bits
		// ignore this command, but need to remove data from the receive buffer
		readByte1 = Buffer_GetElement(&Rx_Buffer);
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'L') { // leave programming mode
		RESETPORT |= (1 << RESETPIN); // set RESET pin on target to 1
		RESETPORT2 |= (1 << RESETPIN2); // set RESET pin on target to 1
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 's') { // Read signature bytes
		// send 4 bytes over SPI; 0x30, 0x00, 0x02, read and send last byte over serial
		SPI_SendByte(0x30);
		SPI_SendByte(0x00);
		SPI_SendByte(0x02);
		readByte1 = SPI_TransferByte(0x00); // read in data
		Buffer_StoreElement(&Tx_Buffer, readByte1);
		SPI_SendByte(0x30);
		SPI_SendByte(0x00);
		SPI_SendByte(0x01);
		readByte1 = SPI_TransferByte(0x00); // read in data
		Buffer_StoreElement(&Tx_Buffer, readByte1);
		SPI_SendByte(0x30);
		SPI_SendByte(0x00);
		SPI_SendByte(0x00);
		readByte1 = SPI_TransferByte(0x00); // read in data
		Buffer_StoreElement(&Tx_Buffer, readByte1);

	} else if (firstByte == 't') { // Return supported device codes
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE01);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE02);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE03);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE04);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE05);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE06);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE07);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE08);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE09);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE10);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE11);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE12);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE13);
		Buffer_StoreElement(&Tx_Buffer, AVRDEVCODE14);
		Buffer_StoreElement(&Tx_Buffer, 0x00);

	} else if (firstByte == 'S') { // Return software identifier
		// return string[7] with "AVR ISP"
		Buffer_StoreElement(&Tx_Buffer, 'A');
		Buffer_StoreElement(&Tx_Buffer, 'V');
		Buffer_StoreElement(&Tx_Buffer, 'R');
		Buffer_StoreElement(&Tx_Buffer, 0x20);
		Buffer_StoreElement(&Tx_Buffer, 'I');
		Buffer_StoreElement(&Tx_Buffer, 'S');
		Buffer_StoreElement(&Tx_Buffer, 'P');

	} else if (firstByte == 'V') { // Return sofware version
		//return two bytes, software Major then Minor
		Buffer_StoreElement(&Tx_Buffer, '2');
		Buffer_StoreElement(&Tx_Buffer, '3');

	} else if (firstByte == 'v') { // Return hardware version
		//return two bytes, hardware Major then Minor	
		Buffer_StoreElement(&Tx_Buffer, ('1'));
		Buffer_StoreElement(&Tx_Buffer, ('0'));

	} else if (firstByte == 'p') { // Return programmer type
		// return 'S' for Serial Programmer
		Buffer_StoreElement(&Tx_Buffer, 'S');

	} else if (firstByte == 'x') { // set LED
		// ignore this command, but need to remove data from the receive buffer
		readByte1 = Buffer_GetElement(&Rx_Buffer);
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'y') { // clear LED
		// ignore this command, but need to remove data from the receive buffer
		readByte1 = Buffer_GetElement(&Rx_Buffer);
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == ':') { // Universal Command
		// get 3 bytes over serial
		readByte1 = Buffer_GetElement(&Rx_Buffer);
		readByte2 = Buffer_GetElement(&Rx_Buffer);
		readByte3 = Buffer_GetElement(&Rx_Buffer);
		SPI_SendByte(readByte1);
		SPI_SendByte(readByte2);
		SPI_SendByte(readByte3);
		readByte1 = SPI_TransferByte(0x00);
		Buffer_StoreElement(&Tx_Buffer, readByte1);
		_delay_ms(DELAY_MEDIUM);
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == '.') { // New Universal Command
		// get 4 bytes over serial
		readByte1 = Buffer_GetElement(&Rx_Buffer);
		readByte2 = Buffer_GetElement(&Rx_Buffer);
		readByte3 = Buffer_GetElement(&Rx_Buffer);
		readByte4 = Buffer_GetElement(&Rx_Buffer);
		SPI_SendByte(readByte1);
		SPI_SendByte(readByte2);
		SPI_SendByte(readByte3);
		readByte1 = SPI_TransferByte(readByte4);
		Buffer_StoreElement(&Tx_Buffer, readByte1);
		_delay_ms(DELAY_MEDIUM);
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful

	} else if (firstByte == 'Z') { // Special test command
		// do nothing, but need to remove data from the receive buffer
		readByte1 = Buffer_GetElement(&Rx_Buffer);
		readByte2 = Buffer_GetElement(&Rx_Buffer);

	} else {
		// do nothing, but need to return with a carriage return
		Buffer_StoreElement(&Tx_Buffer, CR_HEX); // return carriage return (CR_HEX) if successful
	}
}

