/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "i2c_api.h"
#include "cmsis.h"
#include "pinmap.h"

#if DEVICE_I2C

static const SWM_Map SWM_I2C_SDA[] = {
    {7, 24},
};

static const SWM_Map SWM_I2C_SCL[] = {
    {8, 0},
};

static uint8_t repeated_start = 0;

#define I2C_DAT(x)          (x->i2c->MSTDAT)
#define I2C_STAT(x)         ((x->i2c->STAT >> 1) & (0x07))

static inline int i2c_status(i2c_t *obj) {
    return I2C_STAT(obj);
}

// Wait until the Serial Interrupt (SI) is set
static int i2c_wait_SI(i2c_t *obj) {
    int timeout = 0;
    while (!(obj->i2c->STAT & (1 << 0))) {
        timeout++;
        if (timeout > 100000) return -1;
    }
    return 0;
}

static inline void i2c_interface_enable(i2c_t *obj) {
    obj->i2c->CFG |= (1 << 0);
}

static inline void i2c_power_enable(i2c_t *obj) {
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);
    LPC_SYSCON->PRESETCTRL &= ~(0x1<<6);
    LPC_SYSCON->PRESETCTRL |= (0x1<<6);
}

void i2c_init(i2c_t *obj, PinName sda, PinName scl) {
    obj->i2c = (LPC_I2C_TypeDef *)LPC_I2C;
    
    const SWM_Map *swm;
    uint32_t regVal;
    
    swm = &SWM_I2C_SDA[0];
    regVal = LPC_SWM->PINASSIGN[swm->n] & ~(0xFF << swm->offset);
    LPC_SWM->PINASSIGN[swm->n] = regVal |  (sda   << swm->offset);
    
    swm = &SWM_I2C_SCL[0];
    regVal = LPC_SWM->PINASSIGN[swm->n] & ~(0xFF << swm->offset);
    LPC_SWM->PINASSIGN[swm->n] = regVal |  (scl   << swm->offset);
    
    // enable power
    i2c_power_enable(obj);
    // set default frequency at 100k
    i2c_frequency(obj, 100000);
    i2c_interface_enable(obj);
}

//Actually Wrong. Spec says: First store Address in DAT before setting STA ! 
//Undefined state when using single byte I2C operations and too much delay
//between i2c_start and do_i2c_write(Address).
//Also note that lpc812 will immediately continue reading a byte when Address b0 == 1
inline int i2c_start(i2c_t *obj) {
    int status = 0;
    if (repeated_start) {
        obj->i2c->MSTCTL = (1 << 1) | (1 << 0);
        repeated_start = 0;
    } else {
        obj->i2c->MSTCTL = (1 << 1);
    }
    return status;
}

//Generate Stop condition and wait until bus is Idle
//Will also send NAK for previous RD
inline int i2c_stop(i2c_t *obj) {
    int timeout = 0;

    obj->i2c->MSTCTL = (1 << 2) | (1 << 0); // STP bit and Continue bit. Sends NAK to complete previous RD
    
    //Spin until Ready (b0 == 1)and Status is Idle (b3..b1 == 000)
    while ((obj->i2c->STAT & ((7 << 1) | (1 << 0))) != ((0 << 1) | (1 << 0))) { 
        timeout ++;
        if (timeout > 100000) return 1;
    }

    return 0;
}

static inline int i2c_do_write(i2c_t *obj, int value, uint8_t addr) {
    // write the data
    I2C_DAT(obj) = value;
    
    if (!addr)
        obj->i2c->MSTCTL = (1 << 0);
    
    // wait and return status
    i2c_wait_SI(obj);
    return i2c_status(obj);
}

static inline int i2c_do_read(i2c_t *obj, int last) {
    // wait for it to arrive
    i2c_wait_SI(obj);
    if (!last)
        obj->i2c->MSTCTL = (1 << 0);
    
    // return the data
    return (I2C_DAT(obj) & 0xFF);
}

void i2c_frequency(i2c_t *obj, int hz) {
    // No peripheral clock divider on the M0
    uint32_t PCLK = SystemCoreClock;
    
    uint32_t clkdiv = PCLK / (hz * 4) - 1;
    
    obj->i2c->DIV = clkdiv;
    obj->i2c->MSTTIME = 0;
}

// The I2C does a read or a write as a whole operation
// There are two types of error conditions it can encounter
//  1) it can not obtain the bus
//  2) it gets error responses at part of the transmission
//
// We tackle them as follows:
//  1) we retry until we get the bus. we could have a "timeout" if we can not get it
//      which basically turns it in to a 2)
//  2) on error, we use the standard error mechanisms to report/debug
//
// Therefore an I2C transaction should always complete. If it doesn't it is usually
// because something is setup wrong (e.g. wiring), and we don't need to programatically
// check for that

//New version WH, Tested OK for Start and Repeated Start
//Old version was Wrong: Calls i2c_start without setting address, i2c_do_read continues before checking status, status check for wrong value
int i2c_read(i2c_t *obj, int address, char *data, int length, int stop) {
    int count, status;
    
    //Store the address+RD and then generate STA
    I2C_DAT(obj) = address | 0x01;
    i2c_start(obj);    

    // Wait for completion of STA and Sending of SlaveAddress+RD and first Read byte
    i2c_wait_SI(obj);
    status = i2c_status(obj);    
    if (status == 0x03) { // NAK on SlaveAddress
        i2c_stop(obj);
        return I2C_ERROR_NO_SLAVE;
    }

    // Read in all except last byte
    for (count = 0; count < (length-1); count++) {
        
      // Wait for it to arrive, note that first byte read after address+RD is already waiting
      i2c_wait_SI(obj);
      status = i2c_status(obj);
      if (status != 0x01) { // RX RDY
        i2c_stop(obj);
        return count;
      }
      data[count] = I2C_DAT(obj) & 0xFF; // Store read byte

      obj->i2c->MSTCTL = (1 << 0); // Send ACK and Continue to read
    }
    
    // Read final byte
    // Wait for it to arrive
    i2c_wait_SI(obj);

    status = i2c_status(obj);
    if (status != 0x01) { // RX RDY
      i2c_stop(obj);
      return count;
    }
    data[count] = I2C_DAT(obj) & 0xFF; // Store final read byte

    // If not repeated start, send stop.
    if (stop) {
        i2c_stop(obj); // Also sends NAK for last read byte
    } else {
        repeated_start = 1;
    }
   
    return length;
}



//New version WH, Tested OK for Start and Repeated Start
//Old version was Wrong: Calls i2c_start without setting address first
int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop) {
    int i, status;

    //Store the address+/WR and then generate STA
    I2C_DAT(obj) = address & 0xFE;   
    i2c_start(obj);
    
    // Wait for completion of STA and Sending of SlaveAddress+/WR
    i2c_wait_SI(obj);
    status = i2c_status(obj);    
    if (status == 0x03) { // NAK SlaveAddress
        i2c_stop(obj);
        return I2C_ERROR_NO_SLAVE;
    }
    
    //Write all bytes
    for (i=0; i<length; i++) {
        status = i2c_do_write(obj, data[i], 0);
        if (status != 0x02) { // TX RDY. Handles a Slave NAK on datawrite
            i2c_stop(obj);
            return i;
        }
    }
    
    // If not repeated start, send stop.
    if (stop) {
        i2c_stop(obj);
    } else {
        repeated_start = 1;
    }
    
    return length;
}



void i2c_reset(i2c_t *obj) {
    i2c_stop(obj);
}

int i2c_byte_read(i2c_t *obj, int last) {
    return (i2c_do_read(obj, last) & 0xFF);
}

int i2c_byte_write(i2c_t *obj, int data) {
    int ack;
    int status = i2c_do_write(obj, (data & 0xFF), 0);
    
    switch(status) {
        case 2:
            ack = 1;
            break;
        default:
            ack = 0;
            break;
    }

    return ack;
}

#if DEVICE_I2CSLAVE

#define I2C_SLVDAT(x)        (x->i2c->SLVDAT)
#define I2C_SLVSTAT(x)      ((x->i2c->STAT >> 9) & (0x03))
#define I2C_SLVSI(x)        ((x->i2c->STAT >> 8) & (0x01))
//#define I2C_SLVCNT(x)        (x->i2c->SLVCTL = (1 << 0))
//#define I2C_SLVNAK(x)        (x->i2c->SLVCTL = (1 << 1))

#if(0)
// Wait until the Slave Serial Interrupt (SI) is set
// Timeout when it takes too long.
static int i2c_wait_slave_SI(i2c_t *obj) {
    int timeout = 0;
    while (!(obj->i2c->STAT & (1 << 8))) {
        timeout++;
        if (timeout > 100000) return -1;
    }
    return 0;
}
#endif

void i2c_slave_mode(i2c_t *obj, int enable_slave) {

  if (enable_slave) {
//    obj->i2c->CFG &= ~(1 << 0); //Disable Master mode    
    obj->i2c->CFG |=  (1 << 1); //Enable Slave mode
  }
  else {
//    obj->i2c->CFG |=  (1 << 0); //Enable Master mode    
    obj->i2c->CFG &= ~(1 << 1); //Disable Slave mode
  } 
}

// Wait for next I2C event and find out what is going on
//
int i2c_slave_receive(i2c_t *obj) {
  int addr;
  
  // Check if there is any data pending
  if (! I2C_SLVSI(obj)) {
    return 0; //NoData    
  };
  
  // Check State
  switch(I2C_SLVSTAT(obj)) {
    case 0x0: // Slave address plus R/W received 
              // At least one of the four slave addresses has been matched by hardware.
              // You can figure out which address by checking Slave address match Index in STAT register.
               
              // Get the received address
              addr = I2C_SLVDAT(obj) & 0xFF;
              // Send ACK on address and Continue
              obj->i2c->SLVCTL = (1 << 0); 
              
              if (addr == 0x00) {
                return 2; //WriteGeneral
              }  
              //check the RW bit
              if ((addr & 0x01) == 0x01) {
                return 1; //ReadAddressed
              }
              else {
                return 3; //WriteAddressed
              }
              //break;
    
    case 0x1: // Slave receive. Received data is available (Slave Receiver mode).
              // Oops, should never get here...     
              obj->i2c->SLVCTL = (1 << 1);  // Send NACK on received data, try to recover...
              return 0; //NoData        
              
    case 0x2: // Slave transmit. Data can be transmitted (Slave Transmitter mode).
              // Oops, should never get here...         
              I2C_SLVDAT(obj) = 0xFF;       // Send dummy data for transmission
              obj->i2c->SLVCTL = (1 << 0);  // Continue and try to recover...
              return 0; //NoData        
    
    case 0x3: // Reserved.
    default:  // Oops, should never get here... 
              obj->i2c->SLVCTL = (1 << 0);  // Continue and try to recover...              
              return 0; //NoData        
              //break; 
  } //switch status  
}

// The dedicated I2C Slave byte read and byte write functions need to be called
// from 'common' mbed I2CSlave API for devices that have separate Master and 
// Slave engines such as the lpc812 and lpc1549.

//Called when Slave is addressed for Write, Slave will receive Data in polling mode
//Parameter last=1 means received byte will be NACKed.
int i2c_slave_byte_read(i2c_t *obj, int last) {
  int data;
  
  // Wait for data
  while (!I2C_SLVSI(obj)); // Wait forever
//if (i2c_wait_slave_SI(obj) != 0) {return -2;} // Wait with timeout

  // Dont bother to check State, were not returning it anyhow..
//if (I2C_SLVSTAT(obj)) == 0x01) {
  // Slave receive. Received data is available (Slave Receiver mode).    
//};

  data = I2C_SLVDAT(obj) & 0xFF; // Get and store the received data
  if (last) {
    obj->i2c->SLVCTL = (1 << 1);  // Send NACK on received data and Continue 
  }    
  else {  
    obj->i2c->SLVCTL = (1 << 0);  // Send ACK on data and Continue to read                
  }
 
  return data; 
}


//Called when Slave is addressed for Read, Slave will send Data in polling mode
//
int i2c_slave_byte_write(i2c_t *obj, int data) {

  // Wait until Ready 
  while (!I2C_SLVSI(obj)); // Wait forever
//  if (i2c_wait_slave_SI(obj) != 0) {return -2;} // Wait with timeout

  // Check State
  switch(I2C_SLVSTAT(obj)) {
    case 0x0: // Slave address plus R/W received 
              // At least one of the four slave addresses has been matched by hardware.
              // You can figure out which address by checking Slave address match Index in STAT register.                
              // I2C Restart occurred
              return -1; 
              //break;    
    case 0x1: // Slave receive. Received data is available (Slave Receiver mode).
              // Should not get here... 
              return -2;
              //break;                
    case 0x2: // Slave transmit. Data can be transmitted (Slave Transmitter mode).
              I2C_SLVDAT(obj) = data & 0xFF; // Store the data for transmission
              obj->i2c->SLVCTL = (1 << 0);   // Continue to send
              
              return 1;    
              //break;      
    case 0x3: // Reserved.
    default:
              // Should not get here... 
              return -3;
              //break; 
  } // switch status
}


//Called when Slave is addressed for Write, Slave will receive Data in polling mode
//Parameter length (>=1) is the maximum allowable number of bytes. All bytes will be ACKed.
int i2c_slave_read(i2c_t *obj, char *data, int length) {
  int count=0;
  
  // Read and ACK all expected bytes
  while (count < length) {
    // Wait for data
    while (!I2C_SLVSI(obj)); // Wait forever
//    if (i2c_wait_slave_SI(obj) != 0) {return -2;} // Wait with timeout

    // Check State
    switch(I2C_SLVSTAT(obj)) {
      case 0x0: // Slave address plus R/W received 
                // At least one of the four slave addresses has been matched by hardware.
                // You can figure out which address by checking Slave address match Index in STAT register.                
                // I2C Restart occurred
                return -1; 
                //break;
    
      case 0x1: // Slave receive. Received data is available (Slave Receiver mode).
                data[count] = I2C_SLVDAT(obj) & 0xFF; // Get and store the received data
                obj->i2c->SLVCTL = (1 << 0);          // Send ACK on data and Continue to read                
                break;

      case 0x2: // Slave transmit. Data can be transmitted (Slave Transmitter mode).
      case 0x3: // Reserved.
      default:  // Should never get here... 
                return -2;
                //break; 
    } // switch status
    
    count++;
  } // for all bytes
    
  return count; // Received the expected number of bytes
}


//Called when Slave is addressed for Read, Slave will send Data in polling mode
//Parameter length (>=1) is the maximum number of bytes. Exit when Slave byte is NACKed.
int i2c_slave_write(i2c_t *obj, const char *data, int length) {
  int count;
  
  // Send and all bytes or Exit on NAK
  for (count=0; count < length; count++) {
    // Wait until Ready for data 
    while (!I2C_SLVSI(obj)); // Wait forever
//    if (i2c_wait_slave_SI(obj) != 0) {return -2;} // Wait with timeout

    // Check State
    switch(I2C_SLVSTAT(obj)) {
      case 0x0: // Slave address plus R/W received 
                // At least one of the four slave addresses has been matched by hardware.
                // You can figure out which address by checking Slave address match Index in STAT register.                
                // I2C Restart occurred
                return -1; 
                //break;    
      case 0x1: // Slave receive. Received data is available (Slave Receiver mode).
                // Should not get here... 
                return -2;
                //break;                
      case 0x2: // Slave transmit. Data can be transmitted (Slave Transmitter mode).
                I2C_SLVDAT(obj) = data[count] & 0xFF; // Store the data for transmission
                obj->i2c->SLVCTL = (1 << 0);          // Continue to send
                break;      
      case 0x3: // Reserved.
      default:
              // Should not get here... 
              return -3;
              //break; 
    } // switch status
  } // for all bytes
     
  return length; // Transmitted the max number of bytes
}


// Set the four slave addresses. 
void i2c_slave_address(i2c_t *obj, int idx, uint32_t address, uint32_t mask) {
  obj->i2c->SLVADR0   = (address & 0xFE); // Store address in address 0 register
  obj->i2c->SLVADR1   = (0x00    & 0xFE); // Store general call write address in address 1 register
  obj->i2c->SLVADR2   = (0x01);           // Disable address 2 register
  obj->i2c->SLVADR3   = (0x01);           // Disable address 3 register
  obj->i2c->SLVQUAL0  = (mask & 0xFE);    // Qualifier mask for address 0 register. Any maskbit that is 1 will always be a match 
}

#endif

#endif
