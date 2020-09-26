#ifndef SOFT_SERIAL_H
#define SOFT_SERIAL_H

#include <stdbool.h>

// /////////////////////////////////////////////////////////////////
// Need Soft Serial defines in config.h
// /////////////////////////////////////////////////////////////////
// ex.
//  #define SOFT_SERIAL_PIN ??   // ?? = D0,D1,D2,D3,E6
//  OPTIONAL: #define SELECT_SOFT_SERIAL_SPEED ? // ? = 1,2,3,4,5
//                                               //  1: about 137kbps (default)
//                                               //  2: about 75kbps
//                                               //  3: about 39kbps
//                                               //  4: about 26kbps
//                                               //  5: about 20kbps
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
#define TID_LIMIT( table ) (sizeof(table) / sizeof(SSTD_t))

// initiator is transaction start side
void soft_serial_initiator_init(SSTD_t *sstd_table, int sstd_table_size);
// target is interrupt accept side
void soft_serial_target_init(SSTD_t *sstd_table, int sstd_table_size);

// initiator resullt
#define TRANSACTION_END 0
#define TRANSACTION_NO_RESPONSE 0x1
#define TRANSACTION_DATA_ERROR  0x2
#define TRANSACTION_TYPE_ERROR  0x4
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
#define TRANSACTION_ACCEPTED 0x8
#ifdef SERIAL_USE_MULTI_TRANSACTION
int  soft_serial_get_and_clean_status(int sstd_index);
#endif

#endif /* SOFT_SERIAL_H */
