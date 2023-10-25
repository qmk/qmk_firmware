#include "quantum.h"

#if defined(__AVR__)
#    include <avr/io.h>
#    include <avr/interrupt.h>
#endif

#define ROWS_PER_HAND (MATRIX_ROWS / 2)
#define SLAVE_MATRIX_SYNC_ADDR (0x01)

typedef struct {
    char*  buffer;
    size_t count;
    bool*  flag;
} transmit_status;

transmit_status irx = {}, itx = {};

// Buffer for master/slave matrix scan transmit.
// Master: receive buffer.
// Slave: transmit buffer.
matrix_row_t sync_matrix[ROWS_PER_HAND];
bool         matrix_synced = false;

void USART_init(uint16_t baud) {
    cli();

    // UBRR1H = (unsigned char)(baud >>8);
    // UBRR1L = (unsigned char)(baud);
    UBRR1 = baud;
    // Enable U2X1 for double speed.
    UCSR1A = (1 << U2X1);
    // Enable RX/TX, 9N1 mode
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1) | (1 << TXCIE1) | (1 << UCSZ12);
    UCSR1C = (1 << UCSZ10) | (1 << UCSZ11);
    sei();
}

ISR(USART1_RX_vect) {
    // read data from reg.
    uint8_t status   = UCSR1A;
    uint8_t high_bit = UCSR1B;
    uint8_t low_data = UDR1;
    if (status & ((1 << FE1) | (1 << DOR1) | (1 << UPE1))) {
        // Something error happen, ignore this package.
        irx.count = 0;
        return;
    }

    // Is it a addr? (9th bit is one/zero?)
    if (high_bit & (1 << RXB81)) {
        // data is addr. prepend for receive.
        switch (low_data) {
            case SLAVE_MATRIX_SYNC_ADDR:
                irx.buffer = (char *)sync_matrix;
                irx.count = sizeof(sync_matrix) * sizeof(matrix_row_t);
                irx.flag = &matrix_synced;
                break;

            default:
                // ignore this package.
                irx.count = 0;
                break;
        }

    } else if (irx.count > 0) {
        *irx.buffer = low_data;
        ++irx.buffer;
        if (--irx.count == 0 && irx.flag != NULL) {
            *irx.flag = true;
        }
    }
}

// TX complete
ISR(USART1_TX_vect) {
    // Is in transmit?
    if (itx.count > 0) {
        // Send data.
        UCSR1B &= ~(1 << TXB81);
        UDR1 = *itx.buffer;

        // Move to next char.
        ++itx.buffer;
        if (--itx.count == 0) {
            *itx.flag = true;
        }
    }
    // TODO: read queue/register for next message.
}

// return: queue depth.
int send_packet(uint8_t addr, char* buffer, size_t length, bool* flag) {
    // See if we can start transmit right now.
    if ((itx.count == 0) && (UCSR1A & (1 << UDRE1))) {
        // Ready to write.
        // Prepend registers.
        itx.buffer = buffer;
        itx.count  = length;
        itx.flag   = flag;

        // Write addr to kick start transmit.
        UCSR1B |= (1 << TXB81);
        UDR1 = addr;
        // TODO: put request in queue;
        // }else{
    }

    return 0;
}

void transport_master_init(void) { USART_init(0); }

void transport_slave_init(void) { USART_init(0); }

// returns false if valid data not received from slave
bool transport_master(matrix_row_t matrix[]) {
    if (matrix_synced) {
        for (uint8_t i = 0; i < ROWS_PER_HAND; ++i) {
            matrix[i] = sync_matrix[i];
        }
        matrix_synced = false;
        return true;
    }
    return false;
}

void transport_slave(matrix_row_t matrix[]) {
    for (uint8_t i = 0; i < ROWS_PER_HAND; ++i) {
        sync_matrix[i] = matrix[i];
    }
    matrix_synced = false;
    send_packet(SLAVE_MATRIX_SYNC_ADDR, (char*)sync_matrix, sizeof(sync_matrix) * sizeof(matrix_row_t), &matrix_synced);
}
