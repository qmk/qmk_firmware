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

// Serial pulse period in microseconds. Its probably a bad idea to lower this
// value.
#define SERIAL_DELAY 6             // micro sec
#define READ_WRITE_START_ADJUST 20 // cycles
#define READ_WRITE_WIDTH_ADJUST 10 // cycles

#define SERIAL_DELAY_HALF1 (SERIAL_DELAY/2)
#define SERIAL_DELAY_HALF2 (SERIAL_DELAY - SERIAL_DELAY/2)

uint8_t volatile serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH] = {0};
uint8_t volatile serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH] = {0};

#define SLAVE_DATA_CORRUPT (1<<0)
volatile uint8_t status = 0;

#ifdef SERIAL_DEBUG_MODE
 #define serial_debug_init() SERIAL_DBGPIN_DDR |= SERIAL_DBGPIN_MASK
#else
 #define serial_debug_init()
#endif

#if SERIAL_DEBUG_MODE & SERIAL_DEBUG_MODE_WATCH_OUTMODE
 #define debug_output_mode() SERIAL_DBGPIN_PORT |= SERIAL_DBGPIN_MASK
 #define debug_input_mode()  SERIAL_DBGPIN_PORT &= ~SERIAL_DBGPIN_MASK
#else
 #define debug_output_mode()
 #define debug_input_mode()
#endif

#if SERIAL_DEBUG_MODE & SERIAL_DEBUG_MODE_WATCH_RCVSAMPLE
  #define debug_recvsample() SERIAL_DBGPIN_PORT ^= SERIAL_DBGPIN_MASK
#else
  #define debug_recvsample()
#endif

#if SERIAL_DEBUG_MODE & SERIAL_DEBUG_MODE_WATCH_BYTEWIDTH
  #define debug_bytewidth_start()  SERIAL_DBGPIN_PORT |= SERIAL_DBGPIN_MASK
  #define debug_bytewidth_end()  SERIAL_DBGPIN_PORT &= ~SERIAL_DBGPIN_MASK
#else
  #define debug_bytewidth_start()
  #define debug_bytewidth_end()
#endif

#if SERIAL_DEBUG_MODE & SERIAL_DEBUG_MODE_WATCH_SYNC
  #define debug_sync_start() SERIAL_DBGPIN_PORT |= SERIAL_DBGPIN_MASK
  #define debug_sync_end() SERIAL_DBGPIN_PORT &= ~SERIAL_DBGPIN_MASK
#else
  #define debug_sync_start()
  #define debug_sync_end()
#endif

#if SERIAL_DEBUG_MODE & SERIAL_DEBUG_MODE_WATCH_IOCHG
  #define debug_iochg_on() SERIAL_DBGPIN_PORT |= SERIAL_DBGPIN_MASK; _delay_us(1)
  #define debug_iochg_off() SERIAL_DBGPIN_PORT &= ~SERIAL_DBGPIN_MASK
#else
  #define debug_iochg_on()
  #define debug_iochg_off()
#endif

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
  debug_output_mode();
  SERIAL_PIN_DDR |= SERIAL_PIN_MASK;
}

// make the serial pin an input with pull-up resistor
inline static
void serial_input(void) {
  debug_input_mode();
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
  serial_debug_init();
  serial_output();
  serial_high();
}

void serial_slave_init(void) {
  serial_debug_init();
  serial_input();

#ifndef USE_SERIAL_PD2
  // Enable INT0
  EIMSK |= _BV(INT0);
  // Trigger on falling edge of INT0
  EICRA &= ~(_BV(ISC00) | _BV(ISC01));
#else
  // Enable INT2
  EIMSK |= _BV(INT2);
  // Trigger on falling edge of INT2
  EICRA &= ~(_BV(ISC20) | _BV(ISC21));
#endif
}

// Used by the master to synchronize timing with the slave.
static
void sync_recv(void) {
  debug_sync_start();
  // This shouldn't hang if the slave disconnects because the
  // serial line will float to high if the slave does disconnect.
  while (!serial_read_pin());
  debug_sync_end();
}

// Used by the slave to send a synchronization signal to the master.
static
void sync_send(void) {
  debug_sync_start();
  serial_low();
  serial_delay();
  serial_high();
  debug_sync_end();
}

// Reads a byte from the serial line
static
uint8_t serial_read_byte(void) {
  uint8_t byte = 0;
  _delay_sub_us(READ_WRITE_START_ADJUST);
  for ( uint8_t i = 0; i < 8; ++i) {
    serial_delay_half1();   // read the middle of pulses
    byte = (byte << 1) | serial_read_pin();
    debug_recvsample();
    _delay_sub_us(READ_WRITE_WIDTH_ADJUST);
    debug_recvsample();
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
    debug_recvsample();
    serial_delay();
    debug_recvsample()
  }
  serial_low(); // sync_recv() need low
}

// interrupt handle to be used by the slave device
ISR(SERIAL_PIN_INTERRUPT) {
  serial_output();
  sync_send();

  // slave send phase
  uint8_t checksum = 0;
  for (int i = 0; i < SERIAL_SLAVE_BUFFER_LENGTH; ++i) {
    debug_bytewidth_start();
    serial_write_byte(serial_slave_buffer[i]);
    debug_bytewidth_end();
    sync_send();
    checksum += serial_slave_buffer[i];
  }
  serial_write_byte(checksum);
  serial_low();

  // slave switch to input
  debug_iochg_on(); //1
  sync_send();
  debug_iochg_off();
  serial_delay_half1();
  debug_iochg_on(); //2
  serial_low();
  debug_iochg_off();
  serial_input();
  debug_iochg_on(); //3
  serial_delay();
  debug_iochg_off();

  // slave recv phase
  sync_recv();
  uint8_t checksum_computed = 0;
  for (int i = 0; i < SERIAL_MASTER_BUFFER_LENGTH; ++i) {
    debug_bytewidth_start();
    serial_master_buffer[i] = serial_read_byte();
    debug_bytewidth_end();
    sync_recv();
    checksum_computed += serial_master_buffer[i];
  }
  uint8_t checksum_received = serial_read_byte();

  if ( checksum_computed != checksum_received ) {
    status |= SLAVE_DATA_CORRUPT;
  } else {
    status &= ~SLAVE_DATA_CORRUPT;
  }
  sync_recv(); //weit master output to hight
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
    serial_output();
    serial_high();
    sei();
    return 1;
  }

  // master recv phase
  // if the slave is present syncronize with it
  sync_recv();

  uint8_t checksum_computed = 0;
  // receive data from the slave
  for (int i = 0; i < SERIAL_SLAVE_BUFFER_LENGTH; ++i) {
    debug_bytewidth_start();
    serial_slave_buffer[i] = serial_read_byte();
    debug_bytewidth_end();
    sync_recv();
    checksum_computed += serial_slave_buffer[i];
  }
  uint8_t checksum_received = serial_read_byte();

  if (checksum_computed != checksum_received) {
    serial_output();
    serial_high();
    sei();
    return 2;
  }

  // master switch to output
  debug_iochg_on(); //1
  sync_recv();
  debug_iochg_off();
  serial_delay();
  debug_iochg_on(); //2
  serial_output();
  debug_iochg_off();
  serial_low();
  debug_iochg_on(); //3
  serial_delay_half1();
  debug_iochg_off();

  // master send phase
  uint8_t checksum = 0;

  sync_send();
  for (int i = 0; i < SERIAL_MASTER_BUFFER_LENGTH; ++i) {
    debug_bytewidth_start();
    serial_write_byte(serial_master_buffer[i]);
    debug_bytewidth_end();
    sync_send();
    checksum += serial_master_buffer[i];
  }
  serial_write_byte(checksum);

  // always, release the line when not in use
  sync_send();

  sei();
  return 0;
}

#endif
