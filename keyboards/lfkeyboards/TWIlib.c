/*
 * TWIlib.c
 *
 *  Created: 6/01/2014 10:41:33 PM
 *  Author: Chris Herring
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TWIlib.h"
#include <util/delay.h>
#include "print.h"

// Global transmit buffer
volatile uint8_t *TWITransmitBuffer;
// Global receive buffer
volatile uint8_t TWIReceiveBuffer[RXMAXBUFLEN];
// Buffer indexes
volatile int TXBuffIndex; // Index of the transmit buffer. Is volatile, can change at any time.
int RXBuffIndex; // Current index in the receive buffer
// Buffer lengths
int TXBuffLen; // The total length of the transmit buffer
int RXBuffLen; // The total number of bytes to read (should be less than RXMAXBUFFLEN)

TWIInfoStruct TWIInfo;

void TWIInit(void)
{
	TWIInfo.mode = Ready;
	TWIInfo.errorCode = 0xFF;
	TWIInfo.repStart = 0;
	// Set pre-scalers (no pre-scaling)
	TWSR = 0;
	// Set bit rate
	TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
	// Enable TWI and interrupt
	TWCR = (1 << TWIE) | (1 << TWEN);
}

uint8_t isTWIReady(void)
{
	if ( (TWIInfo.mode == Ready) | (TWIInfo.mode == RepeatedStartSent) )
	{
		return 1;
	}
	else
	{
		if(TWIInfo.mode == Initializing){
			switch(TWIInfo.errorCode){
		        case TWI_SUCCESS:
		        case TWI_NO_RELEVANT_INFO:
		        	break;
				case TWI_LOST_ARBIT:
				case TWI_MT_DATA_NACK:
					// Some kind of I2C error, reset and re-init
		        	xprintf("I2C init error: %d\n", TWIInfo.errorCode);
			        TWCR = (1 << TWINT)|(1 << TWSTO);
		        	TWIInit();
		        	break;
		        default:
		        	xprintf("Other i2c init error: %d\n", TWIInfo.errorCode);
			}
		}
		return 0;
	}
}


void TWITransmitData(void *const TXdata, uint8_t dataLen, uint8_t repStart, uint8_t blocking)
{
	// Wait until ready
	while (!isTWIReady()) {_delay_us(1);}
	// Reset the I2C stuff
	TWCR = (1 << TWINT)|(1 << TWSTO);
	TWIInit();
	// Set repeated start mode
	TWIInfo.repStart = repStart;
	// Copy transmit info to global variables
	TWITransmitBuffer = (uint8_t *)TXdata;
	TXBuffLen = dataLen;
	TXBuffIndex = 0;

	// If a repeated start has been sent, then devices are already listening for an address
	// and another start does not need to be sent.
	if (TWIInfo.mode == RepeatedStartSent)
	{
		TWIInfo.mode = Initializing;
		TWDR = TWITransmitBuffer[TXBuffIndex++]; // Load data to transmit buffer
		TWISendTransmit(); // Send the data
	}
	else // Otherwise, just send the normal start signal to begin transmission.
	{
		TWIInfo.mode = Initializing;
		TWISendStart();
	}
	if(blocking){
		// Wait until ready
		while (!isTWIReady()){_delay_us(1);}
	}
}


// uint8_t TWITransmitData(void *const TXdata, uint8_t dataLen, uint8_t repStart)
// {
// 	if (dataLen <= TXMAXBUFLEN)
// 	{
// 		// Wait until ready
// 		while (!isTWIReady()) {_delay_us(1);}
// 		// Set repeated start mode
// 		TWIInfo.repStart = repStart;
// 		// Copy data into the transmit buffer
// 		uint8_t *data = (uint8_t *)TXdata;
// 		for (int i = 0; i < dataLen; i++)
// 		{
// 			TWITransmitBuffer[i] = data[i];
// 		}
// 		// Copy transmit info to global variables
// 		TXBuffLen = dataLen;
// 		TXBuffIndex = 0;

// 		// If a repeated start has been sent, then devices are already listening for an address
// 		// and another start does not need to be sent.
// 		if (TWIInfo.mode == RepeatedStartSent)
// 		{
// 			TWIInfo.mode = Initializing;
// 			TWDR = TWITransmitBuffer[TXBuffIndex++]; // Load data to transmit buffer
// 			TWISendTransmit(); // Send the data
// 		}
// 		else // Otherwise, just send the normal start signal to begin transmission.
// 		{
// 			TWIInfo.mode = Initializing;
// 			TWISendStart();
// 		}

// 	}
// 	else
// 	{
// 		return 1; // return an error if data length is longer than buffer
// 	}
// 	return 0;
// }

uint8_t TWIReadData(uint8_t TWIaddr, uint8_t bytesToRead, uint8_t repStart)
{
	// Check if number of bytes to read can fit in the RXbuffer
	if (bytesToRead < RXMAXBUFLEN)
	{
		// Reset buffer index and set RXBuffLen to the number of bytes to read
		RXBuffIndex = 0;
		RXBuffLen = bytesToRead;
		// Create the one value array for the address to be transmitted
		uint8_t TXdata[1];
		// Shift the address and AND a 1 into the read write bit (set to write mode)
		TXdata[0] = (TWIaddr << 1) | 0x01;
		// Use the TWITransmitData function to initialize the transfer and address the slave
		TWITransmitData(TXdata, 1, repStart, 0);
	}
	else
	{
		return 0;
	}
	return 1;
}

ISR (TWI_vect)
{
	switch (TWI_STATUS)
	{
		// ----\/ ---- MASTER TRANSMITTER OR WRITING ADDRESS ----\/ ----  //
		case TWI_MT_SLAW_ACK: // SLA+W transmitted and ACK received
		// Set mode to Master Transmitter
		TWIInfo.mode = MasterTransmitter;
		case TWI_START_SENT: // Start condition has been transmitted
		case TWI_MT_DATA_ACK: // Data byte has been transmitted, ACK received
			if (TXBuffIndex < TXBuffLen) // If there is more data to send
			{
				TWDR = TWITransmitBuffer[TXBuffIndex++]; // Load data to transmit buffer
				TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
				TWISendTransmit(); // Send the data
			}
			// This transmission is complete however do not release bus yet
			else if (TWIInfo.repStart)
			{
				TWIInfo.errorCode = 0xFF;
				TWISendStart();
			}
			// All transmissions are complete, exit
			else
			{
				TWIInfo.mode = Ready;
				TWIInfo.errorCode = 0xFF;
				TWISendStop();
			}
			break;

		// ----\/ ---- MASTER RECEIVER ----\/ ----  //

		case TWI_MR_SLAR_ACK: // SLA+R has been transmitted, ACK has been received
			// Switch to Master Receiver mode
			TWIInfo.mode = MasterReceiver;
			// If there is more than one byte to be read, receive data byte and return an ACK
			if (RXBuffIndex < RXBuffLen-1)
			{
				TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
				TWISendACK();
			}
			// Otherwise when a data byte (the only data byte) is received, return NACK
			else
			{
				TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
				TWISendNACK();
			}
			break;

		case TWI_MR_DATA_ACK: // Data has been received, ACK has been transmitted.

			/// -- HANDLE DATA BYTE --- ///
			TWIReceiveBuffer[RXBuffIndex++] = TWDR;
			// If there is more than one byte to be read, receive data byte and return an ACK
			if (RXBuffIndex < RXBuffLen-1)
			{
				TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
				TWISendACK();
			}
			// Otherwise when a data byte (the only data byte) is received, return NACK
			else
			{
				TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
				TWISendNACK();
			}
			break;

		case TWI_MR_DATA_NACK: // Data byte has been received, NACK has been transmitted. End of transmission.

			/// -- HANDLE DATA BYTE --- ///
			TWIReceiveBuffer[RXBuffIndex++] = TWDR;
			// This transmission is complete however do not release bus yet
			if (TWIInfo.repStart)
			{
				TWIInfo.errorCode = 0xFF;
				TWISendStart();
			}
			// All transmissions are complete, exit
			else
			{
				TWIInfo.mode = Ready;
				TWIInfo.errorCode = 0xFF;
				TWISendStop();
			}
			break;

		// ----\/ ---- MT and MR common ----\/ ---- //

		case TWI_MR_SLAR_NACK: // SLA+R transmitted, NACK received
		case TWI_MT_SLAW_NACK: // SLA+W transmitted, NACK received
		case TWI_MT_DATA_NACK: // Data byte has been transmitted, NACK received
		case TWI_LOST_ARBIT: // Arbitration has been lost
			// Return error and send stop and set mode to ready
			if (TWIInfo.repStart)
			{
				TWIInfo.errorCode = TWI_STATUS;
				TWISendStart();
			}
			// All transmissions are complete, exit
			else
			{
				TWIInfo.mode = Ready;
				TWIInfo.errorCode = TWI_STATUS;
				TWISendStop();
			}
			break;
		case TWI_REP_START_SENT: // Repeated start has been transmitted
			// Set the mode but DO NOT clear TWINT as the next data is not yet ready
			TWIInfo.mode = RepeatedStartSent;
			break;

		// ----\/ ---- SLAVE RECEIVER ----\/ ----  //

		// TODO  IMPLEMENT SLAVE RECEIVER FUNCTIONALITY

		// ----\/ ---- SLAVE TRANSMITTER ----\/ ----  //

		// TODO  IMPLEMENT SLAVE TRANSMITTER FUNCTIONALITY

		// ----\/ ---- MISCELLANEOUS STATES ----\/ ----  //
		case TWI_NO_RELEVANT_INFO: // It is not really possible to get into this ISR on this condition
								   // Rather, it is there to be manually set between operations
			break;
		case TWI_ILLEGAL_START_STOP: // Illegal START/STOP, abort and return error
			TWIInfo.errorCode = TWI_ILLEGAL_START_STOP;
			TWIInfo.mode = Ready;
			TWISendStop();
			break;
	}

}
