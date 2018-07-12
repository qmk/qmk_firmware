/* Library made by: g4lvanix
 * Github repository: https://github.com/g4lvanix/I2C-slave-lib
 */

#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>

#include "i2c_slave.h"

void i2c_init(uint8_t address){
	// load address into TWI address register
	TWAR = (address << 1);
	// set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
}

void i2c_stop(void){
	// clear acknowledge and enable bits
	TWCR &= ~( (1<<TWEA) | (1<<TWEN) );
}

ISR(TWI_vect){
	
	// temporary stores the received data
	uint8_t data;
	
	// own address has been acknowledged
	if( (TWSR & 0xF8) == TW_SR_SLA_ACK ){  
		buffer_address = 0xFF;
		// clear TWI interrupt flag, prepare to receive next byte and acknowledge
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
	}
	else if( (TWSR & 0xF8) == TW_SR_DATA_ACK ){ // data has been received in slave receiver mode
		
		// save the received byte inside data 
		data = TWDR;
		
		// check wether an address has already been transmitted or not
		if(buffer_address == 0xFF){
			
			buffer_address = data; 
			
			// clear TWI interrupt flag, prepare to receive next byte and acknowledge
			TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
		}
		else{ // if a databyte has already been received
			
			// store the data at the current address
			rxbuffer[buffer_address] = data;
			
			// increment the buffer address
			buffer_address++;
			
			// if there is still enough space inside the buffer
			if(buffer_address < 0xFF){
				// clear TWI interrupt flag, prepare to receive next byte and acknowledge
				TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
			}
			else{
				// Don't acknowledge
				TWCR &= ~(1<<TWEA); 
				// clear TWI interrupt flag, prepare to receive last byte.
				TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEN); 
			}
		}
	}
	else if( (TWSR & 0xF8) == TW_ST_DATA_ACK ){ // device has been addressed to be a transmitter
		
		// copy data from TWDR to the temporary memory
		data = TWDR;
		
		// if no buffer read address has been sent yet
		if( buffer_address == 0xFF ){
			buffer_address = data;
		}
		
		// copy the specified buffer address into the TWDR register for transmission
		TWDR = txbuffer[buffer_address];
		// increment buffer read address
		buffer_address++;
		
		// if there is another buffer address that can be sent
		if(buffer_address < 0xFF){
			// clear TWI interrupt flag, prepare to send next byte and receive acknowledge
			TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
		}
		else{
			// Don't acknowledge
			TWCR &= ~(1<<TWEA); 
			// clear TWI interrupt flag, prepare to receive last byte.
			TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEN); 
		}
		
	}
	else{
		// if none of the above apply prepare TWI to be addressed again
		TWCR |= (1<<TWIE) | (1<<TWEA) | (1<<TWEN);
	} 
}
