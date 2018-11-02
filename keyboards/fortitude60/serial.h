#ifndef SOFT_SERIAL_H
#define SOFT_SERIAL_H

#include <stdbool.h>

// /////////////////////////////////////////////////////////////////
// Need Soft Serial defines in serial_config.h
// /////////////////////////////////////////////////////////////////
// ex.
//  #define SERIAL_PIN_DDR DDRD
//  #define SERIAL_PIN_PORT PORTD
//  #define SERIAL_PIN_INPUT PIND
//  #define SERIAL_PIN_MASK _BV(PD?)   ?=0,2
//  #define SERIAL_PIN_INTERRUPT INT?_vect  ?=0,2
//
// //// USE Simple API (OLD API, compatible with let's split serial.c)
// ex.
//  #define SERIAL_SLAVE_BUFFER_LENGTH MATRIX_ROWS/2
//  #define SERIAL_MASTER_BUFFER_LENGTH 1
//
// //// USE flexible API (using multi-type transaction function)
//  #define SERIAL_USE_MULTI_TRANSACTION
//
// /////////////////////////////////////////////////////////////////


#ifndef SERIAL_USE_MULTI_TRANSACTION
/* --- USE Simple API (OLD API, compatible with let's split serial.c) */
#if SERIAL_SLAVE_BUFFER_LENGTH > 0
extern volatile uint8_t serial_slave_buffer[SERIAL_SLAVE_BUFFER_LENGTH];
#endif
#if SERIAL_MASTER_BUFFER_LENGTH > 0
extern volatile uint8_t serial_master_buffer[SERIAL_MASTER_BUFFER_LENGTH];
#endif

void serial_master_init(void);
void serial_slave_init(void);
int serial_update_buffers(void);

#endif // USE Simple API

// Soft Serial Transaction Descriptor
typedef struct _SSTD_t  {
    uint8_t *status;
    uint8_t initiator2target_buffer_size;
    uint8_t *initiator2target_buffer;
    uint8_t target2initiator_buffer_size;
    uint8_t *target2initiator_buffer;
} SSTD_t;

// initiator is transaction start side
void soft_serial_initiator_init(SSTD_t *sstd_table);
// target is interrupt accept side
void soft_serial_target_init(SSTD_t *sstd_table);

// initiator resullt
#define TRANSACTION_END 0
#define TRANSACTION_NO_RESPONSE 0x1
#define TRANSACTION_DATA_ERROR  0x2
#ifndef SERIAL_USE_MULTI_TRANSACTION
int  soft_serial_transaction(void);
#else
int  soft_serial_transaction(int sstd_index);
#endif

// target status
// *SSTD_t.status has
//   initiator:
//       TRANSACTION_END
//    or TRANSACTION_NO_RESPONSE
//    or TRANSACTION_DATA_ERROR
//   target:
//       TRANSACTION_DATA_ERROR
//    or TRANSACTION_ACCEPTED
#define TRANSACTION_ACCEPTED 0x4
#ifdef SERIAL_USE_MULTI_TRANSACTION
int  soft_serial_get_and_clean_status(int sstd_index);
#endif

#endif /* SOFT_SERIAL_H */