/*
 * WARNING: be careful changing this code, it is very timing dependent
 *
 * 2018-10-28 checked
 *  avr-gcc 4.9.2
 *  avr-gcc 5.4.0
 *  avr-gcc 7.3.0
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

#ifdef SOFT_SERIAL_PIN

#ifdef __AVR_ATmega32U4__
  // if using ATmega32U4 I2C, can not use PD0 and PD1 in soft serial.
  #ifdef USE_I2C
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

//////////////// for backward compatibility ////////////////////////////////
#ifndef SERIAL_USE_MULTI_TRANSACTION
/* --- USE Simple API (OLD API, compatible with let's split serial.c) */
  #if SERIAL_SLAVE_BUFFER_LENGTH > 0
  uint8_t volatile serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH] = {0};
  #endif
  #if SERIAL_MASTER_BUFFER_LENGTH > 0
  uint8_t volatile serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH] = {0};
  #endif
  uint8_t volatile status0 = 0;

SSTD_t transactions[] = {
    { (uint8_t *)&status0,
  #if SERIAL_MASTER_BUFFER_LENGTH > 0
      sizeof(serial_master_buffer), (uint8_t *)serial_master_buffer,
  #else
      0, (uint8_t *)NULL,
  #endif
  #if SERIAL_SLAVE_BUFFER_LENGTH > 0
      sizeof(serial_slave_buffer), (uint8_t *)serial_slave_buffer
  #else
      0, (uint8_t *)NULL,
  #endif
  }
};

void serial_master_init(void)
{ soft_serial_initiator_init(transactions, TID_LIMIT(transactions)); }

void serial_slave_init(void)
{ soft_serial_target_init(transactions, TID_LIMIT(transactions)); }

// 0 => no error
// 1 => slave did not respond
// 2 => checksum error
int serial_update_buffers()
{
    int result;
    result = soft_serial_transaction();
    return result;
}

#endif // end of Simple API (OLD API, compatible with let's split serial.c)
////////////////////////////////////////////////////////////////////////////

#define ALWAYS_INLINE __attribute__((always_inline))
#define NO_INLINE __attribute__((noinline))
#define _delay_sub_us(x)    __builtin_avr_delay_cycles(x)

// parity check
#define ODD_PARITY 1
#define EVEN_PARITY 0
#define PARITY EVEN_PARITY

#ifdef SERIAL_DELAY
  // custom setup in config.h
  // #define TID_SEND_ADJUST 2
  // #define SERIAL_DELAY 6             // micro sec
  // #define READ_WRITE_START_ADJUST 30 // cycles
  // #define READ_WRITE_WIDTH_ADJUST 8 // cycles
#else
// ============ Standard setups ============

#ifndef SELECT_SOFT_SERIAL_SPEED
#define SELECT_SOFT_SERIAL_SPEED 1
//  0: about 189kbps
//  1: about 137kbps (default)
//  2: about 75kbps
//  3: about 39kbps
//  4: about 26kbps
//  5: about 20kbps
#endif

#if __GNUC__ < 6
  #define TID_SEND_ADJUST 14
#else
  #define TID_SEND_ADJUST 2
#endif

#if SELECT_SOFT_SERIAL_SPEED == 0
  // Very High speed
  #define SERIAL_DELAY 4             // micro sec
  #if __GNUC__ < 6
    #define READ_WRITE_START_ADJUST 33 // cycles
    #define READ_WRITE_WIDTH_ADJUST 3 // cycles
  #else
    #define READ_WRITE_START_ADJUST 34 // cycles
    #define READ_WRITE_WIDTH_ADJUST 7 // cycles
  #endif
#elif SELECT_SOFT_SERIAL_SPEED == 1
  // High speed
  #define SERIAL_DELAY 6             // micro sec
  #if __GNUC__ < 6
    #define READ_WRITE_START_ADJUST 30 // cycles
    #define READ_WRITE_WIDTH_ADJUST 3 // cycles
  #else
    #define READ_WRITE_START_ADJUST 33 // cycles
    #define READ_WRITE_WIDTH_ADJUST 7 // cycles
  #endif
#elif SELECT_SOFT_SERIAL_SPEED == 2
  // Middle speed
  #define SERIAL_DELAY 12            // micro sec
  #define READ_WRITE_START_ADJUST 30 // cycles
  #if __GNUC__ < 6
    #define READ_WRITE_WIDTH_ADJUST 3 // cycles
  #else
    #define READ_WRITE_WIDTH_ADJUST 7 // cycles
  #endif
#elif SELECT_SOFT_SERIAL_SPEED == 3
  // Low speed
  #define SERIAL_DELAY 24            // micro sec
  #define READ_WRITE_START_ADJUST 30 // cycles
  #if __GNUC__ < 6
    #define READ_WRITE_WIDTH_ADJUST 3 // cycles
  #else
    #define READ_WRITE_WIDTH_ADJUST 7 // cycles
  #endif
#elif SELECT_SOFT_SERIAL_SPEED == 4
  // Very Low speed
  #define SERIAL_DELAY 36            // micro sec
  #define READ_WRITE_START_ADJUST 30 // cycles
  #if __GNUC__ < 6
    #define READ_WRITE_WIDTH_ADJUST 3 // cycles
  #else
    #define READ_WRITE_WIDTH_ADJUST 7 // cycles
  #endif
#elif SELECT_SOFT_SERIAL_SPEED == 5
  // Ultra Low speed
  #define SERIAL_DELAY 48            // micro sec
  #define READ_WRITE_START_ADJUST 30 // cycles
  #if __GNUC__ < 6
    #define READ_WRITE_WIDTH_ADJUST 3 // cycles
  #else
    #define READ_WRITE_WIDTH_ADJUST 7 // cycles
  #endif
#else
#error invalid SELECT_SOFT_SERIAL_SPEED value
#endif /* SELECT_SOFT_SERIAL_SPEED */
#endif /* SERIAL_DELAY */

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
static uint8_t Transaction_table_size = 0;

inline static void serial_delay(void) ALWAYS_INLINE;
inline static
void serial_delay(void) {
  _delay_us(SERIAL_DELAY);
}

inline static void serial_delay_half1(void) ALWAYS_INLINE;
inline static
void serial_delay_half1(void) {
  _delay_us(SERIAL_DELAY_HALF1);
}

inline static void serial_delay_half2(void) ALWAYS_INLINE;
inline static
void serial_delay_half2(void) {
  _delay_us(SERIAL_DELAY_HALF2);
}

inline static void serial_output(void) ALWAYS_INLINE;
inline static
void serial_output(void) {
  SERIAL_PIN_DDR |= SERIAL_PIN_MASK;
}

// make the serial pin an input with pull-up resistor
inline static void serial_input_with_pullup(void) ALWAYS_INLINE;
inline static
void serial_input_with_pullup(void) {
  SERIAL_PIN_DDR  &= ~SERIAL_PIN_MASK;
  SERIAL_PIN_PORT |= SERIAL_PIN_MASK;
}

inline static uint8_t serial_read_pin(void) ALWAYS_INLINE;
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

void soft_serial_initiator_init(SSTD_t *sstd_table, int sstd_table_size)
{
    Transaction_table = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;
    serial_output();
    serial_high();
}

void soft_serial_target_init(SSTD_t *sstd_table, int sstd_table_size)
{
    Transaction_table = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;
    serial_input_with_pullup();

    // Enable INT0-INT3,INT6
    EIMSK |= EIMSK_BIT;
#if SERIAL_PIN_MASK == _BV(PE6)
    // Trigger on falling edge of INT6
    EICRB &= EICRx_BIT;
#else
    // Trigger on falling edge of INT0-INT3
    EICRA &= EICRx_BIT;
#endif
}

// Used by the sender to synchronize timing with the reciver.
static void sync_recv(void) NO_INLINE;
static
void sync_recv(void) {
  for (uint8_t i = 0; i < SERIAL_DELAY*5 && serial_read_pin(); i++ ) {
  }
  // This shouldn't hang if the target disconnects because the
  // serial line will float to high if the target does disconnect.
  while (!serial_read_pin());
}

// Used by the reciver to send a synchronization signal to the sender.
static void sync_send(void) NO_INLINE;
static
void sync_send(void) {
  serial_low();
  serial_delay();
  serial_high();
}

// Reads a byte from the serial line
static uint8_t serial_read_chunk(uint8_t *pterrcount, uint8_t bit) NO_INLINE;
static uint8_t serial_read_chunk(uint8_t *pterrcount, uint8_t bit) {
    uint8_t byte, i, p, pb;

  _delay_sub_us(READ_WRITE_START_ADJUST);
  for( i = 0, byte = 0, p = PARITY; i < bit; i++ ) {
      serial_delay_half1();   // read the middle of pulses
      if( serial_read_pin() ) {
          byte = (byte << 1) | 1; p ^= 1;
      } else {
          byte = (byte << 1) | 0; p ^= 0;
      }
      _delay_sub_us(READ_WRITE_WIDTH_ADJUST);
      serial_delay_half2();
  }
  /* recive parity bit */
  serial_delay_half1();   // read the middle of pulses
  pb = serial_read_pin();
  _delay_sub_us(READ_WRITE_WIDTH_ADJUST);
  serial_delay_half2();

  *pterrcount += (p != pb)? 1 : 0;

  return byte;
}

// Sends a byte with MSB ordering
void serial_write_chunk(uint8_t data, uint8_t bit) NO_INLINE;
void serial_write_chunk(uint8_t data, uint8_t bit) {
    uint8_t b, p;
    for( p = PARITY, b = 1<<(bit-1); b ; b >>= 1) {
        if(data & b) {
            serial_high(); p ^= 1;
        } else {
            serial_low();  p ^= 0;
        }
        serial_delay();
    }
    /* send parity bit */
    if(p & 1) { serial_high(); }
    else      { serial_low(); }
    serial_delay();

    serial_low(); // sync_send() / senc_recv() need raise edge
}

static void serial_send_packet(uint8_t *buffer, uint8_t size) NO_INLINE;
static
void serial_send_packet(uint8_t *buffer, uint8_t size) {
  for (uint8_t i = 0; i < size; ++i) {
    uint8_t data;
    data = buffer[i];
    sync_send();
    serial_write_chunk(data,8);
  }
}

static uint8_t serial_recive_packet(uint8_t *buffer, uint8_t size) NO_INLINE;
static
uint8_t serial_recive_packet(uint8_t *buffer, uint8_t size) {
  uint8_t pecount = 0;
  for (uint8_t i = 0; i < size; ++i) {
    uint8_t data;
    sync_recv();
    data = serial_read_chunk(&pecount, 8);
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

static inline uint8_t nibble_bits_count(uint8_t bits)
{
    bits = (bits & 0x5) + (bits >> 1 & 0x5);
    bits = (bits & 0x3) + (bits >> 2 & 0x3);
    return bits;
}

// interrupt handle to be used by the target device
ISR(SERIAL_PIN_INTERRUPT) {

#ifndef SERIAL_USE_MULTI_TRANSACTION
  serial_low();
  serial_output();
  SSTD_t *trans = Transaction_table;
#else
  // recive transaction table index
  uint8_t tid, bits;
  uint8_t pecount = 0;
  sync_recv();
  bits = serial_read_chunk(&pecount,7);
  tid = bits>>3;
  bits = (bits&7) != nibble_bits_count(tid);
  if( bits || pecount> 0 || tid > Transaction_table_size ) {
      return;
  }
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
          *trans->status = TRANSACTION_DATA_ERROR;
      }
  } else {
      *trans->status = TRANSACTION_ACCEPTED;
  }

  sync_recv(); //weit initiator output to high
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
  if( sstd_index > Transaction_table_size )
      return TRANSACTION_TYPE_ERROR;
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
  int tid = (sstd_index<<3) | (7 & nibble_bits_count(sstd_index));
  sync_send();
  _delay_sub_us(TID_SEND_ADJUST);
  serial_write_chunk(tid, 7);
  serial_delay_half1();

  // wait for the target response (step1 low->high)
  serial_input_with_pullup();
  while( !serial_read_pin() ) {
      _delay_sub_us(2);
  }

  // check if the target is present (step2 high->low)
  for( int i = 0; serial_read_pin(); i++ ) {
      if (i > SLAVE_INT_ACK_WIDTH + 1) {
          // slave failed to pull the line low, assume not present
          serial_output();
          serial_high();
          *trans->status = TRANSACTION_NO_RESPONSE;
          sei();
          return TRANSACTION_NO_RESPONSE;
      }
      _delay_sub_us(SLAVE_INT_ACK_WIDTH_UNIT);
  }
#endif

  // initiator recive phase
  // if the target is present syncronize with it
  if( trans->target2initiator_buffer_size > 0 ) {
      if (!serial_recive_packet((uint8_t *)trans->target2initiator_buffer,
                                trans->target2initiator_buffer_size) ) {
          serial_output();
          serial_high();
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

// Helix serial.c history
//   2018-1-29 fork from let's split and add PD2, modify sync_recv() (#2308, bceffdefc)
//   2018-6-28 bug fix master to slave comm and speed up (#3255, 1038bbef4)
//             (adjusted with avr-gcc 4.9.2)
//   2018-7-13 remove USE_SERIAL_PD2 macro (#3374, f30d6dd78)
//             (adjusted with avr-gcc 4.9.2)
//   2018-8-11 add support multi-type transaction (#3608, feb5e4aae)
//             (adjusted with avr-gcc 4.9.2)
//   2018-10-21 fix serial and RGB animation conflict (#4191, 4665e4fff)
//             (adjusted with avr-gcc 7.3.0)
//   2018-10-28 re-adjust compiler depend value of delay (#4269, 8517f8a66)
//             (adjusted with avr-gcc 5.4.0, 7.3.0)
