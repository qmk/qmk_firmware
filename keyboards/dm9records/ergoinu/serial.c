/*
 * WARNING: be careful changing this code, it is very timing dependent
 */

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "serial.h"

#ifdef USE_SERIAL

#define _delay_sub_us(x)    __builtin_avr_delay_cycles(x)

// Serial pulse period in microseconds.
#define SELECT_SERIAL_SPEED 1
#if SELECT_SERIAL_SPEED == 0
  // Very High speed
  #define SERIAL_DELAY 4             // micro sec
  #define READ_WRITE_START_ADJUST 30 // cycles
  #define READ_WRITE_WIDTH_ADJUST 10 // cycles
#elif SELECT_SERIAL_SPEED == 1
  // High speed
  #define SERIAL_DELAY 6             // micro sec
  #define READ_WRITE_START_ADJUST 23 // cycles
  #define READ_WRITE_WIDTH_ADJUST 10 // cycles
#elif SELECT_SERIAL_SPEED == 2
  // Middle speed
  #define SERIAL_DELAY 12            // micro sec
  #define READ_WRITE_START_ADJUST 25 // cycles
  #define READ_WRITE_WIDTH_ADJUST 10 // cycles
#elif SELECT_SERIAL_SPEED == 3
  // Low speed
  #define SERIAL_DELAY 24            // micro sec
  #define READ_WRITE_START_ADJUST 25 // cycles
  #define READ_WRITE_WIDTH_ADJUST 10 // cycles
#elif SELECT_SERIAL_SPEED == 4
  // Very Low speed
  #define SERIAL_DELAY 50            // micro sec
  #define READ_WRITE_START_ADJUST 25 // cycles
  #define READ_WRITE_WIDTH_ADJUST 10 // cycles
#else
#error Illegal Serial Speed
#endif


#define SERIAL_DELAY_HALF1 (SERIAL_DELAY/2)
#define SERIAL_DELAY_HALF2 (SERIAL_DELAY - SERIAL_DELAY/2)

#define SLAVE_INT_WIDTH 1
#define SLAVE_INT_RESPONSE_TIME SERIAL_DELAY

uint8_t volatile serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH] = {0};
uint8_t volatile serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH] = {0};

#define SLAVE_DATA_CORRUPT (1<<0)
volatile uint8_t status = 0;

inline static
void serial_delay(void) {
  _delay_us(SERIAL_DELAY);
}

inline static
void serial_delay_half1(void) {
  _delay_us(SERIAL_DELAY_HALF1);
}

inline static
void serial_delay_half2(void) {
  _delay_us(SERIAL_DELAY_HALF2);
}

inline static
void serial_output(void) {
  SERIAL_PIN_DDR |= SERIAL_PIN_MASK;
}

// make the serial pin an input with pull-up resistor
inline static
void serial_input_with_pullup(void) {
  SERIAL_PIN_DDR  &= ~SERIAL_PIN_MASK;
  SERIAL_PIN_PORT |= SERIAL_PIN_MASK;
}

inline static
uint8_t serial_read_pin(void) {
  return !!(SERIAL_PIN_INPUT & SERIAL_PIN_MASK);
}

inline static
void serial_low(void) {
  SERIAL_PIN_PORT &= ~SERIAL_PIN_MASK;
}

inline static
void serial_high(void) {
  SERIAL_PIN_PORT |= SERIAL_PIN_MASK;
}

void serial_master_init(void) {
  serial_output();
  serial_high();
}

void serial_slave_init(void) {
  serial_input_with_pullup();

#if SERIAL_PIN_MASK == _BV(PD0)
  // Enable INT0
  EIMSK |= _BV(INT0);
  // Trigger on falling edge of INT0
  EICRA &= ~(_BV(ISC00) | _BV(ISC01));
#elif SERIAL_PIN_MASK == _BV(PD2)
  // Enable INT2
  EIMSK |= _BV(INT2);
  // Trigger on falling edge of INT2
  EICRA &= ~(_BV(ISC20) | _BV(ISC21));
#else
 #error unknown SERIAL_PIN_MASK value
#endif
}

// Used by the sender to synchronize timing with the reciver.
static
void sync_recv(void) {
  for (int i = 0; i < SERIAL_DELAY*5 && serial_read_pin(); i++ ) {
  }
  // This shouldn't hang if the slave disconnects because the
  // serial line will float to high if the slave does disconnect.
  while (!serial_read_pin());
}

// Used by the reciver to send a synchronization signal to the sender.
static
void sync_send(void) {
  serial_low();
  serial_delay();
  serial_high();
}

// Reads a byte from the serial line
static
uint8_t serial_read_byte(void) {
  uint8_t byte = 0;
  _delay_sub_us(READ_WRITE_START_ADJUST);
  for ( uint8_t i = 0; i < 8; ++i) {
    serial_delay_half1();   // read the middle of pulses
    byte = (byte << 1) | serial_read_pin();
    _delay_sub_us(READ_WRITE_WIDTH_ADJUST);
    serial_delay_half2();
  }
  return byte;
}

// Sends a byte with MSB ordering
static
void serial_write_byte(uint8_t data) {
  uint8_t b = 1<<7;
  while( b ) {
    if(data & b) {
      serial_high();
    } else {
      serial_low();
    }
    b >>= 1;
    serial_delay();
  }
  serial_low(); // sync_send() / senc_recv() need raise edge
}

// interrupt handle to be used by the slave device
ISR(SERIAL_PIN_INTERRUPT) {
  serial_output();

  // slave send phase
  uint8_t checksum = 0;
  for (int i = 0; i < SERIAL_SLAVE_BUFFER_LENGTH; ++i) {
    sync_send();
    serial_write_byte(serial_slave_buffer[i]);
    checksum += serial_slave_buffer[i];
  }
  sync_send();
  serial_write_byte(checksum);

  // slave switch to input
  sync_send(); //0
  serial_delay_half1(); //1
  serial_low();         //2
  serial_input_with_pullup(); //2
  serial_delay_half1(); //3

  // slave recive phase
  uint8_t checksum_computed = 0;
  for (int i = 0; i < SERIAL_MASTER_BUFFER_LENGTH; ++i) {
    sync_recv();
    serial_master_buffer[i] = serial_read_byte();
    checksum_computed += serial_master_buffer[i];
  }
  sync_recv();
  uint8_t checksum_received = serial_read_byte();

  if ( checksum_computed != checksum_received ) {
    status |= SLAVE_DATA_CORRUPT;
  } else {
    status &= ~SLAVE_DATA_CORRUPT;
  }

  sync_recv(); //weit master output to high
}

inline
bool serial_slave_DATA_CORRUPT(void) {
  return status & SLAVE_DATA_CORRUPT;
}

// Copies the serial_slave_buffer to the master and sends the
// serial_master_buffer to the slave.
//
// Returns:
// 0 => no error
// 1 => slave did not respond
// 2 => checksum error
int serial_update_buffers(void) {
  // this code is very time dependent, so we need to disable interrupts
  cli();

  // signal to the slave that we want to start a transaction
  serial_output();
  serial_low();
  _delay_us(SLAVE_INT_WIDTH);

  // wait for the slaves response
  serial_input_with_pullup();
  _delay_us(SLAVE_INT_RESPONSE_TIME);

  // check if the slave is present
  if (serial_read_pin()) {
    // slave failed to pull the line low, assume not present
    serial_output();
    serial_high();
    sei();
    return 1;
  }

  // master recive phase
  // if the slave is present syncronize with it

  uint8_t checksum_computed = 0;
  // receive data from the slave
  for (int i = 0; i < SERIAL_SLAVE_BUFFER_LENGTH; ++i) {
    sync_recv();
    serial_slave_buffer[i] = serial_read_byte();
    checksum_computed += serial_slave_buffer[i];
  }
  sync_recv();
  uint8_t checksum_received = serial_read_byte();

  if (checksum_computed != checksum_received) {
    serial_output();
    serial_high();
    sei();
    return 2;
  }

  // master switch to output
  sync_recv(); //0
  serial_delay();  //1
  serial_low();    //3
  serial_output(); // 3
  serial_delay_half1(); //4

  // master send phase
  uint8_t checksum = 0;

  for (int i = 0; i < SERIAL_MASTER_BUFFER_LENGTH; ++i) {
    sync_send();
    serial_write_byte(serial_master_buffer[i]);
    checksum += serial_master_buffer[i];
  }
  sync_send();
  serial_write_byte(checksum);

  // always, release the line when not in use
  sync_send();

  sei();
  return 0;
}

#endif
