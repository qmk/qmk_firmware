/*
Copyright 2010,2011,2012,2013 Jun WAKO <wakojun@gmail.com>
*/
#include <stdbool.h>
#include <util/delay.h>
#include "debug.h"
#include "ibm4704.h"


#define WAIT(stat, us, err) do { \
    if (!wait_##stat(us)) { \
        ibm4704_error = err; \
        goto ERROR; \
    } \
} while (0)


uint8_t ibm4704_error = 0;


void ibm4704_init(void)
{
    inhibit();
}

uint8_t ibm4704_send(uint8_t data)
{
    bool parity = true; // odd parity
    ibm4704_error = 0;

    /* Request to send */
    idle();
    clock_lo();

    /* wait for Start bit(Clock:lo/Data:hi) */
    WAIT(data_hi, 300, 0x30);

    /* Data bit */
    for (uint8_t i = 0; i < 8; i++) {
        WAIT(clock_hi, 100, 0x40+i);
        //_delay_us(5);
        if (data&(1<<i)) {
            parity = !parity;
            data_hi();
        } else {
            data_lo();
        }
        WAIT(clock_lo, 100, 0x48+i);
    }

    /* Parity bit */
    WAIT(clock_hi, 100, 0x34);
    if (parity) { data_hi(); } else { data_lo(); }
    WAIT(clock_lo, 100, 0x35);

    /* Stop bit */
    WAIT(clock_hi, 100, 0x34);
    data_hi();

    /* End */
    WAIT(data_lo, 100, 0x36);

    inhibit();
    _delay_us(200); // wait to recover clock to hi
    return 0;
ERROR:
    inhibit();
    if (ibm4704_error >= 0x30) {
        xprintf("x%02X ", ibm4704_error);
    }
    _delay_us(200); // wait to recover clock to hi
    return -1;
}

/* receive data when host want else inhibit communication */
uint8_t ibm4704_recv_response(void)
{
    // 250 * 100us(wait start bit in ibm4704_recv)
    uint8_t data = 0;
    uint8_t try = 250;
    do {
        data = ibm4704_recv();
    } while (try-- && ibm4704_error);
    return data;
}

/*
Keyboard to Host:
Clock   ~~~~___~~_~~_~~_~~_~~_~~_~~_~~_~~_~~~~~~~~ H:60us/L:30us

Data    ____~~X==X==X==X==X==X==X==X==X==X________
            |  0  1  2  3  4  5  6  7  P(odd)
            |  LSB                MSB
            Start bit(80us)
*/
uint8_t ibm4704_recv(void)
{
    uint8_t data = 0;
    bool parity = true;    // odd parity
    ibm4704_error = IBM4704_ERR_NONE;

    idle();
    _delay_us(5);   // wait for line settles

    /* start bit */
    WAIT(clock_lo, 100, 0x11); // wait for keyboard to send
    WAIT(data_hi, 100, 0x12);  // can be delayed that long

    WAIT(clock_hi, 100, 0x13); // first rising edge which can take longer
    /* data */
    for (uint8_t i = 0; i < 8; i++) {
        WAIT(clock_hi, 100, 0x20+i);
        //_delay_us(5);
        if (data_in()) {
            parity = !parity;
            data |= (1<<i);
        }
        WAIT(clock_lo, 150, 0x28+i);
    }

    /* parity */
    WAIT(clock_hi, 100, 0x17);
    if (data_in() != parity) {
        ibm4704_error = IBM4704_ERR_PARITY;
        goto ERROR;
    }
    WAIT(clock_lo, 150, 0x18);

    /* stop bit */
    WAIT(clock_hi, 100, 0x19);
    WAIT(data_lo, 1, 0x19);

    inhibit();
    _delay_us(200); // wait to recover clock to hi
    return data;
ERROR:
    if (ibm4704_error > 0x12) {
        xprintf("x%02X ", ibm4704_error);
    }
    inhibit();
    _delay_us(200); // wait to recover clock to hi
    return -1;
}
