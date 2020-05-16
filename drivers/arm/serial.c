#include <stddef.h>
#include <stdint.h>

#include "serial.h"

static SSTD_t *Transaction_table      = NULL;
static uint8_t Transaction_table_size = 0;

void soft_serial_initiator_init(SSTD_t *sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;
}

void soft_serial_target_init(SSTD_t *sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;
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
#    ifndef SERIAL_USE_MULTI_TRANSACTION
int soft_serial_transaction(void) {
    SSTD_t *trans = Transaction_table;
#    else
int soft_serial_transaction(int sstd_index) {
    if (sstd_index > Transaction_table_size) return TRANSACTION_TYPE_ERROR;
    SSTD_t *trans = &Transaction_table[sstd_index];
#    endif
    (void)trans;
    return -1;
}
