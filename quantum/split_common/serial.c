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

#ifdef SOFT_SERIAL_PIN

#ifdef __AVR_ATmega32U4__
  // if using ATmega32U4 I2C, can not use PD0 and PD1 in soft serial.
  #ifdef USE_AVR_I2C
     #if SOFT_SERIAL_PIN == D0 || SOFT_SERIAL_PIN == D1
       #error Using ATmega32U4 I2C, so can not use PD0, PD1
     #endif
  #endif

  #if SOFT_SERIAL_PIN >= D0 && SOFT_SERIAL_PIN <= D3
    #define SERIAL_PIN_DDR   DDRD
    #define SERIAL_PIN_PORT  PORTD
    #define SERIAL_PIN_INPUT PIND
    #if SOFT_SERIAL_PIN == D0
      #define SERIAL_PIN_MASK _BV(PD0)
      #define EIMSK_BIT       _BV(INT0)
      #define EICRx_BIT       (~(_BV(ISC00) | _BV(ISC01)))
      #define SERIAL_PIN_INTERRUPT INT0_vect
    #elif  SOFT_SERIAL_PIN == D1
      #define SERIAL_PIN_MASK _BV(PD1)
      #define EIMSK_BIT       _BV(INT1)
      #define EICRx_BIT       (~(_BV(ISC10) | _BV(ISC11)))
      #define SERIAL_PIN_INTERRUPT INT1_vect
    #elif  SOFT_SERIAL_PIN == D2
      #define SERIAL_PIN_MASK _BV(PD2)
      #define EIMSK_BIT       _BV(INT2)
      #define EICRx_BIT       (~(_BV(ISC20) | _BV(ISC21)))
      #define SERIAL_PIN_INTERRUPT INT2_vect
    #elif  SOFT_SERIAL_PIN == D3
      #define SERIAL_PIN_MASK _BV(PD3)
      #define EIMSK_BIT       _BV(INT3)
      #define EICRx_BIT       (~(_BV(ISC30) | _BV(ISC31)))
      #define SERIAL_PIN_INTERRUPT INT3_vect
    #endif
  #elif  SOFT_SERIAL_PIN == E6
    #define SERIAL_PIN_DDR   DDRE
    #define SERIAL_PIN_PORT  PORTE
    #define SERIAL_PIN_INPUT PINE
    #define SERIAL_PIN_MASK  _BV(PE6)
    #define EIMSK_BIT        _BV(INT6)
    #define EICRx_BIT        (~(_BV(ISC60) | _BV(ISC61)))
    #define SERIAL_PIN_INTERRUPT INT6_vect
  #else
  #error invalid SOFT_SERIAL_PIN value
  #endif

#else
 #error serial.c now support ATmega32U4 only
#endif

// Serial pulse period in microseconds. Its probably a bad idea to lower this
// value.
#define SERIAL_DELAY 24

uint8_t volatile serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH] = {0};
uint8_t volatile serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH] = {0};

#define SLAVE_DATA_CORRUPT (1<<0)
volatile uint8_t status = 0;

inline static
void serial_delay(void) {
  _delay_us(SERIAL_DELAY);
}

inline static
void serial_output(void) {
  SERIAL_PIN_DDR |= SERIAL_PIN_MASK;
}

// make the serial pin an input with pull-up resistor
inline static
void serial_input(void) {
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
  serial_input();

  // Enable INT0
  EIMSK |= _BV(INT0);
  // Trigger on falling edge of INT0
  EICRA &= ~(_BV(ISC00) | _BV(ISC01));
}

// Used by the master to synchronize timing with the slave.
static
void sync_recv(void) {
  serial_input();
  // This shouldn't hang if the slave disconnects because the
  // serial line will float to high if the slave does disconnect.
  while (!serial_read_pin());
  serial_delay();
}

// Used by the slave to send a synchronization signal to the master.
static
void sync_send(void) {
  serial_output();

  serial_low();
  serial_delay();

  serial_high();
}

// Reads a byte from the serial line
static
uint8_t serial_read_byte(void) {
  uint8_t byte = 0;
  serial_input();
  for ( uint8_t i = 0; i < 8; ++i) {
    byte = (byte << 1) | serial_read_pin();
    serial_delay();
    _delay_us(1);
  }

  return byte;
}

// Sends a byte with MSB ordering
static
void serial_write_byte(uint8_t data) {
  uint8_t b = 8;
  serial_output();
  while( b-- ) {
    if(data & (1 << b)) {
      serial_high();
    } else {
      serial_low();
    }
    serial_delay();
  }
}

// interrupt handle to be used by the slave device
ISR(SERIAL_PIN_INTERRUPT) {
  sync_send();

  uint8_t checksum = 0;
  for (int i = 0; i < SERIAL_SLAVE_BUFFER_LENGTH; ++i) {
    serial_write_byte(serial_slave_buffer[i]);
    sync_send();
    checksum += serial_slave_buffer[i];
  }
  serial_write_byte(checksum);
  sync_send();

  // wait for the sync to finish sending
  serial_delay();

  // read the middle of pulses
  _delay_us(SERIAL_DELAY/2);

  uint8_t checksum_computed = 0;
  for (int i = 0; i < SERIAL_MASTER_BUFFER_LENGTH; ++i) {
    serial_master_buffer[i] = serial_read_byte();
    sync_send();
    checksum_computed += serial_master_buffer[i];
  }
  uint8_t checksum_received = serial_read_byte();
  sync_send();

  serial_input(); // end transaction

  if ( checksum_computed != checksum_received ) {
    status |= SLAVE_DATA_CORRUPT;
  } else {
    status &= ~SLAVE_DATA_CORRUPT;
  }
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
int serial_update_buffers(void) {
  // this code is very time dependent, so we need to disable interrupts
  cli();

  // signal to the slave that we want to start a transaction
  serial_output();
  serial_low();
  _delay_us(1);

  // wait for the slaves response
  serial_input();
  serial_high();
  _delay_us(SERIAL_DELAY);

  // check if the slave is present
  if (serial_read_pin()) {
    // slave failed to pull the line low, assume not present
    sei();
    return 1;
  }

  // if the slave is present syncronize with it
  sync_recv();

  uint8_t checksum_computed = 0;
  // receive data from the slave
  for (int i = 0; i < SERIAL_SLAVE_BUFFER_LENGTH; ++i) {
    serial_slave_buffer[i] = serial_read_byte();
    sync_recv();
    checksum_computed += serial_slave_buffer[i];
  }
  uint8_t checksum_received = serial_read_byte();
  sync_recv();

  if (checksum_computed != checksum_received) {
    sei();
    return 1;
  }

  uint8_t checksum = 0;
  // send data to the slave
  for (int i = 0; i < SERIAL_MASTER_BUFFER_LENGTH; ++i) {
    serial_write_byte(serial_master_buffer[i]);
    sync_recv();
    checksum += serial_master_buffer[i];
  }
  serial_write_byte(checksum);
  sync_recv();

  // always, release the line when not in use
  serial_output();
  serial_high();

  sei();
  return 0;
}

#endif /* SOFT_SERIAL_PIN */
