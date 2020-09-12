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

#ifndef USE_I2C

// Serial pulse period in microseconds. Its probably a bad idea to lower this
// value.
#define SERIAL_DELAY 24

uint8_t volatile serial_follower_buffer[SERIAL_follower_BUFFER_LENGTH] = {0};
uint8_t volatile serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH] = {0};

#define follower_DATA_CORRUPT (1<<0)
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

void serial_follower_init(void) {
  serial_input();

  // Enable INT0
  EIMSK |= _BV(INT0);
  // Trigger on falling edge of INT0
  EICRA &= ~(_BV(ISC00) | _BV(ISC01));
}

// Used by the master to synchronize timing with the follower.
static
void sync_recv(void) {
  serial_input();
  // This shouldn't hang if the follower disconnects because the
  // serial line will float to high if the follower does disconnect.
  while (!serial_read_pin());
  serial_delay();
}

// Used by the follower to send a synchronization signal to the master.
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

// interrupt handle to be used by the follower device
ISR(SERIAL_PIN_INTERRUPT) {
  sync_send();

  uint8_t checksum = 0;
  for (int i = 0; i < SERIAL_follower_BUFFER_LENGTH; ++i) {
    serial_write_byte(serial_follower_buffer[i]);
    sync_send();
    checksum += serial_follower_buffer[i];
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
    status |= follower_DATA_CORRUPT;
  } else {
    status &= ~follower_DATA_CORRUPT;
  }
}

inline
bool serial_follower_DATA_CORRUPT(void) {
  return status & follower_DATA_CORRUPT;
}

// Copies the serial_follower_buffer to the master and sends the
// serial_master_buffer to the follower.
//
// Returns:
// 0 => no error
// 1 => follower did not respond
int serial_update_buffers(void) {
  // this code is very time dependent, so we need to disable interrupts
  cli();

  // signal to the follower that we want to start a transaction
  serial_output();
  serial_low();
  _delay_us(1);

  // wait for the followers response
  serial_input();
  serial_high();
  _delay_us(SERIAL_DELAY);

  // check if the follower is present
  if (serial_read_pin()) {
    // follower failed to pull the line low, assume not present
    sei();
    return 1;
  }

  // if the follower is present syncronize with it
  sync_recv();

  uint8_t checksum_computed = 0;
  // receive data from the follower
  for (int i = 0; i < SERIAL_follower_BUFFER_LENGTH; ++i) {
    serial_follower_buffer[i] = serial_read_byte();
    sync_recv();
    checksum_computed += serial_follower_buffer[i];
  }
  uint8_t checksum_received = serial_read_byte();
  sync_recv();

  if (checksum_computed != checksum_received) {
    sei();
    return 1;
  }

  uint8_t checksum = 0;
  // send data to the follower
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

#endif
