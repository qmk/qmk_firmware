/*
 * TWIlib.h
 *
 * Created: 6/01/2014 10:38:42 PM
 *  Author: Chris Herring
 */


#ifndef TWILIB_H_
#define TWILIB_H_
// TWI bit rate
#define TWI_FREQ 400000
// Get TWI status
#define TWI_STATUS	(TWSR & 0xF8)
// Transmit buffer length
#define TXMAXBUFLEN 20
// Receive buffer length
#define RXMAXBUFLEN 20
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

typedef enum {
	Ready,
	Initializing,
	RepeatedStartSent,
	MasterTransmitter,
	MasterReceiver,
	SlaceTransmitter,
	SlaveReciever
	} TWIMode;

 typedef struct TWIInfoStruct{
	TWIMode mode;
	uint8_t errorCode;
	uint8_t repStart;
	}TWIInfoStruct;
TWIInfoStruct TWIInfo;


// TWI Status Codes
#define TWI_START_SENT			0x08 // Start sent
#define TWI_REP_START_SENT		0x10 // Repeated Start sent
// Master Transmitter Mode
#define TWI_MT_SLAW_ACK			0x18 // SLA+W sent and ACK received
#define TWI_MT_SLAW_NACK		0x20 // SLA+W sent and NACK received
#define TWI_MT_DATA_ACK			0x28 // DATA sent and ACK received
#define TWI_MT_DATA_NACK		0x30 // DATA sent and NACK received
// Master Receiver Mode
#define TWI_MR_SLAR_ACK			0x40 // SLA+R sent, ACK received
#define TWI_MR_SLAR_NACK		0x48 // SLA+R sent, NACK received
#define TWI_MR_DATA_ACK			0x50 // Data received, ACK returned
#define TWI_MR_DATA_NACK		0x58 // Data received, NACK returned

// Miscellaneous States
#define TWI_LOST_ARBIT			0x38 // Arbitration has been lost
#define TWI_NO_RELEVANT_INFO	0xF8 // No relevant information available
#define TWI_ILLEGAL_START_STOP	0x00 // Illegal START or STOP condition has been detected
#define TWI_SUCCESS				0xFF // Successful transfer, this state is impossible from TWSR as bit2 is 0 and read only


#define TWISendStart()		(TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWIE)) // Send the START signal, enable interrupts and TWI, clear TWINT flag to resume transfer.
#define TWISendStop()		(TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE)) // Send the STOP signal, enable interrupts and TWI, clear TWINT flag.
#define TWISendTransmit()	(TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)) // Used to resume a transfer, clear TWINT and ensure that TWI and interrupts are enabled.
#define TWISendACK()		(TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA)) // FOR MR mode. Resume a transfer, ensure that TWI and interrupts are enabled and respond with an ACK if the device is addressed as a slave or after it receives a byte.
#define TWISendNACK()		(TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)) // FOR MR mode. Resume a transfer, ensure that TWI and interrupts are enabled but DO NOT respond with an ACK if the device is addressed as a slave or after it receives a byte.

// Function declarations
void TWITransmitData(void *const TXdata, uint8_t dataLen, uint8_t repStart, uint8_t blocking);
void TWIInit(void);
uint8_t TWIReadData(uint8_t TWIaddr, uint8_t bytesToRead, uint8_t repStart);
uint8_t isTWIReady(void);

#endif // TWICOMMS_H_