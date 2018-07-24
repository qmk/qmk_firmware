/*
 * WARNING: be careful changing this code, it is very timing dependent
 */

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stddef.h>
#include <stdbool.h>
#include "serial.h"
//#include <pro_micro.h>

#ifdef USE_SERIAL

#define ALWAYS_INLINE __attribute__((always_inline))
#define NO_INLINE __attribute__((noinline))
#define _delay_sub_us(x)    __builtin_avr_delay_cycles(x)

// Serial pulse period in microseconds.
#define TID_SEND_ADJUST 14

#define SELECT_SERIAL_SPEED 1
#if SELECT_SERIAL_SPEED == 0
  // Very High speed
  #define SERIAL_DELAY 4             // micro sec
  #define READ_WRITE_START_ADJUST 33 // cycles
  #define READ_WRITE_WIDTH_ADJUST 3 // cycles
#elif SELECT_SERIAL_SPEED == 1
  // High speed
  #define SERIAL_DELAY 6             // micro sec
  #define READ_WRITE_START_ADJUST 30 // cycles
  #define READ_WRITE_WIDTH_ADJUST 3 // cycles
#elif SELECT_SERIAL_SPEED == 2
  // Middle speed
  #define SERIAL_DELAY 12            // micro sec
  #define READ_WRITE_START_ADJUST 30 // cycles
  #define READ_WRITE_WIDTH_ADJUST 3 // cycles
#elif SELECT_SERIAL_SPEED == 3
  // Low speed
  #define SERIAL_DELAY 24            // micro sec
  #define READ_WRITE_START_ADJUST 30 // cycles
  #define READ_WRITE_WIDTH_ADJUST 3 // cycles
#elif SELECT_SERIAL_SPEED == 4
  // Very Low speed
  #define SERIAL_DELAY 50            // micro sec
  #define READ_WRITE_START_ADJUST 30 // cycles
  #define READ_WRITE_WIDTH_ADJUST 3 // cycles
#else
#error Illegal Serial Speed
#endif


#define SERIAL_DELAY_HALF1 (SERIAL_DELAY/2)
#define SERIAL_DELAY_HALF2 (SERIAL_DELAY - SERIAL_DELAY/2)

#define SLAVE_INT_WIDTH_US 1
#ifndef SERIAL_USE_MULTI_TRANSACTION
  #define SLAVE_INT_RESPONSE_TIME SERIAL_DELAY
#else
  #define SLAVE_INT_ACK_WIDTH_UNIT 2
  #define SLAVE_INT_ACK_WIDTH 4
#endif

static SSTD_t *Transaction_table = NULL;

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

inline static void serial_output(void) ALWAYS_INLINE;
inline static
void serial_output(void) {
  debug_output_mode();
  SERIAL_PIN_DDR |= SERIAL_PIN_MASK;
}

// make the serial pin an input with pull-up resistor
inline static void serial_input_with_pullup(void) ALWAYS_INLINE;
inline static
void serial_input_with_pullup(void) {
  debug_input_mode();
  SERIAL_PIN_DDR  &= ~SERIAL_PIN_MASK;
  SERIAL_PIN_PORT |= SERIAL_PIN_MASK;
}

inline static
uint8_t serial_read_pin(void) {
  return !!(SERIAL_PIN_INPUT & SERIAL_PIN_MASK);
}

inline static void serial_low(void) ALWAYS_INLINE;
inline static
void serial_low(void) {
  SERIAL_PIN_PORT &= ~SERIAL_PIN_MASK;
}

inline static void serial_high(void) ALWAYS_INLINE;
inline static
void serial_high(void) {
  SERIAL_PIN_PORT |= SERIAL_PIN_MASK;
}

void soft_serial_initiator_init(SSTD_t *sstd_table)
{
    serial_debug_init();
    Transaction_table = sstd_table;
    serial_output();
    serial_high();
}

void soft_serial_target_init(SSTD_t *sstd_table)
{
    serial_debug_init();
    Transaction_table = sstd_table;
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
static void sync_recv(void) NO_INLINE;
static
void sync_recv(void) {
  debug_sync_start();
  for (uint8_t i = 0; i < SERIAL_DELAY*5 && serial_read_pin(); i++ ) {
      debug_sync_end(); debug_sync_start();
  }
  // This shouldn't hang if the target disconnects because the
  // serial line will float to high if the target does disconnect.
  while (!serial_read_pin());
  debug_sync_end();
}

// Used by the reciver to send a synchronization signal to the sender.
static void sync_send(void)NO_INLINE;
static
void sync_send(void) {
  debug_sync_start();
  serial_low();
  serial_delay();
  serial_high();
  debug_sync_end();
}

// Reads a byte from the serial line
static uint8_t serial_read_chunk(uint8_t *pterrcount, uint8_t bit) NO_INLINE;
static uint8_t serial_read_chunk(uint8_t *pterrcount, uint8_t bit) {
    uint8_t byte, i, p, pb;

  _delay_sub_us(READ_WRITE_START_ADJUST);
  for( i = 0, byte = 0, p = 0; i < bit; i++ ) {
      serial_delay_half1();   // read the middle of pulses
      debug_recvsample();
      if( serial_read_pin() ) {
	  byte = (byte << 1) | 1; p ^= 1;
      } else {
	  byte = (byte << 1) | 0; p ^= 0;
      }
      debug_recvsample();
      _delay_sub_us(READ_WRITE_WIDTH_ADJUST);
      serial_delay_half2();
      debug_dummy_delay_recv();
  }
  /* recive parity bit */
  serial_delay_half1();   // read the middle of pulses
  debug_recvsample();
  pb = serial_read_pin();
  debug_recvsample();
  _delay_sub_us(READ_WRITE_WIDTH_ADJUST);
  serial_delay_half2();
  debug_dummy_delay_recv();

  if( p == pb ) debug_parity_on();
  *pterrcount += (p != pb)? 1 : 0;
  debug_parity_off();

  return byte;
}

// Sends a byte with MSB ordering
void serial_write_chunk(uint8_t data, uint8_t bit) NO_INLINE;
void serial_write_chunk(uint8_t data, uint8_t bit) {
    uint8_t b, p;
    for( p = 0, b = 1<<(bit-1); b ; b >>= 1) {
	if(data & b) {
	    serial_high(); p ^= 1;
	} else {
	    serial_low();  p ^= 0;
	}
	debug_recvsample();
	serial_delay();
	debug_recvsample();
	debug_dummy_delay_send();
    }
    /* send parity bit */
    if(p & 1) { serial_high(); }
    else      { serial_low(); }
    debug_recvsample();
    serial_delay();
    debug_recvsample();
    debug_dummy_delay_send();

    serial_low(); // sync_send() / senc_recv() need raise edge
}

static void serial_send_packet(uint8_t *buffer, uint8_t size) NO_INLINE;
static
void serial_send_packet(uint8_t *buffer, uint8_t size) {
  for (uint8_t i = 0; i < size; ++i) {
    uint8_t data;
    data = buffer[i];
    sync_send();
    debug_bytewidth_start();
    serial_write_chunk(data,8);
    debug_bytewidth_end();
  }
}

static uint8_t serial_recive_packet(uint8_t *buffer, uint8_t size) NO_INLINE;
static
uint8_t serial_recive_packet(uint8_t *buffer, uint8_t size) {
  uint8_t pecount = 0;
  for (uint8_t i = 0; i < size; ++i) {
    uint8_t data;
    sync_recv();
    debug_bytewidth_start();
    data = serial_read_chunk(&pecount, 8);
    debug_bytewidth_end();
    buffer[i] = data;
  }
  return pecount == 0;
}

inline static
void change_sender2reciver(void) {
    sync_send();          //0
    serial_delay_half1(); //1
    serial_low();         //2
    serial_input_with_pullup(); //2
    serial_delay_half1(); //3
}

inline static
void change_reciver2sender(void) {
    sync_recv();     //0
    serial_delay();  //1
    serial_low();    //3
    serial_output(); //3
    serial_delay_half1(); //4
}

// interrupt handle to be used by the target device
ISR(SERIAL_PIN_INTERRUPT) {
  debug_output_mode(); debug_input_mode(); // indicate intterupt entry
  debug_recvsample();  debug_recvsample(); // indicate intterupt entry
  debug_sync_start();  debug_sync_end(); // indicate intterupt entry

#ifndef SERIAL_USE_MULTI_TRANSACTION
  serial_low();
  serial_output();
  SSTD_t *trans = Transaction_table;
#else
  // recive transaction table index
  uint8_t tid;
  uint8_t pecount = 0;
  sync_recv();
  debug_bytewidth_start();
  tid = serial_read_chunk(&pecount,4);
  debug_bytewidth_end();
  if(pecount> 0)
      return;
  serial_delay_half1();

  serial_high(); // response step1 low->high
  serial_output();
  _delay_sub_us(SLAVE_INT_ACK_WIDTH_UNIT*SLAVE_INT_ACK_WIDTH);
  SSTD_t *trans = &Transaction_table[tid];
  serial_low(); // response step2 ack high->low
#endif

  // target send phase
  if( trans->target2initiator_buffer_size > 0 )
      serial_send_packet((uint8_t *)trans->target2initiator_buffer,
			 trans->target2initiator_buffer_size);
  // target switch to input
  change_sender2reciver();

  // target recive phase
  if( trans->initiator2target_buffer_size > 0 ) {
      if (serial_recive_packet((uint8_t *)trans->initiator2target_buffer,
			       trans->initiator2target_buffer_size) ) {
	  *trans->status = TRANSACTION_ACCEPTED;
      } else {
	  debug_parity_on();
	  *trans->status = TRANSACTION_DATA_ERROR;
	  debug_parity_off();
      }
  } else {
      *trans->status = TRANSACTION_ACCEPTED;
  }

  sync_recv(); //weit initiator output to high
  debug_output_mode(); debug_input_mode(); // indicate intterupt exit
}

/////////
//  start transaction by initiator
//
// int  soft_serial_transaction(int sstd_index)
//
// Returns:
//    TRANSACTION_END
//    TRANSACTION_NO_RESPONSE
//    TRANSACTION_DATA_ERROR
// this code is very time dependent, so we need to disable interrupts
#ifndef SERIAL_USE_MULTI_TRANSACTION
int  soft_serial_transaction(void) {
  SSTD_t *trans = Transaction_table;
#else
int  soft_serial_transaction(int sstd_index) {
  SSTD_t *trans = &Transaction_table[sstd_index];
#endif
  cli();

  // signal to the target that we want to start a transaction
  serial_output();
  serial_low();
  _delay_us(SLAVE_INT_WIDTH_US);

#ifndef SERIAL_USE_MULTI_TRANSACTION
  // wait for the target response
  serial_input_with_pullup();
  _delay_us(SLAVE_INT_RESPONSE_TIME);

  // check if the target is present
  if (serial_read_pin()) {
    // target failed to pull the line low, assume not present
    serial_output();
    serial_high();
    *trans->status = TRANSACTION_NO_RESPONSE;
    sei();
    return TRANSACTION_NO_RESPONSE;
  }

#else
  // send transaction table index
  sync_send();
  debug_bytewidth_start();
  _delay_sub_us(TID_SEND_ADJUST);
  serial_write_chunk(sstd_index, 4);
  debug_bytewidth_end();
  serial_delay_half1();

  // wait for the target response (step1 low->high)
  serial_input_with_pullup();
  while( !serial_read_pin() ) {
      _delay_sub_us(2);
      debug_output_mode(); debug_input_mode(); // indicate check pin timeing
  }

  // check if the target is present (step2 high->low)
  debug_output_mode(); _delay_sub_us(1); debug_input_mode(); // indicate check pin timeing
  for( int i = 0; serial_read_pin(); i++ ) {
      if (i > SLAVE_INT_ACK_WIDTH + 1) {
	  // slave failed to pull the line low, assume not present
	  serial_output();
	  serial_high();
	  *trans->status = TRANSACTION_NO_RESPONSE;
	  sei();
	  return TRANSACTION_NO_RESPONSE;
      }
      debug_output_mode();
      _delay_sub_us(SLAVE_INT_ACK_WIDTH_UNIT);
      debug_input_mode(); // indicate check pin timeing
  }
#endif

  // initiator recive phase
  // if the target is present syncronize with it
  if( trans->target2initiator_buffer_size > 0 ) {
      if (!serial_recive_packet((uint8_t *)trans->target2initiator_buffer,
				trans->target2initiator_buffer_size) ) {
	  debug_parity_on();
	  serial_output();
	  serial_high();
	  debug_parity_off();
	  *trans->status = TRANSACTION_DATA_ERROR;
	  sei();
	  return TRANSACTION_DATA_ERROR;
      }
   }

  // initiator switch to output
  change_reciver2sender();

  // initiator send phase
  if( trans->initiator2target_buffer_size > 0 ) {
      serial_send_packet((uint8_t *)trans->initiator2target_buffer,
			 trans->initiator2target_buffer_size);
  }

  // always, release the line when not in use
  sync_send();
  debug_input_mode(); debug_output_mode(); // indicate intterupt exit

  *trans->status = TRANSACTION_END;
  sei();
  return TRANSACTION_END;
}

#ifdef SERIAL_USE_MULTI_TRANSACTION
int soft_serial_get_and_clean_status(int sstd_index) {
    SSTD_t *trans = &Transaction_table[sstd_index];
    cli();
    int retval = *trans->status;
    *trans->status = 0;;
    sei();
    return retval;
}
#endif

#endif
