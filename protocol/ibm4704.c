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

/*
Host to Keyboard
----------------
Data bits are LSB first and Parity is odd. Clock has around 60us high and 30us low part.

        ____        __   __   __   __   __   __   __   __   __   ________
Clock       \______/  \_/  \_/  \_/  \_/  \_/  \_/  \_/  \_/  \_/
            ^   ____ ____ ____ ____ ____ ____ ____ ____ ____ ____ ___
Data    ____|__/    X____X____X____X____X____X____X____X____X____X   \___
            |  Start   0    1    2    3    4    5    6    7    P   Stop
            Request by host

Start bit:  can be long as 300-350us.
Request:    Host pulls Clock line down to request to send a command.
Timing:     After Request keyboard pull up Data and down Clock line to low for start bit.
            After request host release Clock line once Data line becomes hi.
            Host writes a bit while Clock is hi and Keyboard reads while low.
Stop bit:   Host releases or pulls up Data line to hi after 9th clock and waits for keyboard pull down the line to lo.
*/
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
Keyboard to Host
----------------
Data bits are LSB first and Parity is odd. Clock has around 60us high and 30us low part.

        ____      __   __   __   __   __   __   __   __   __   ________
Clock       \____/  \_/  \_/  \_/  \_/  \_/  \_/  \_/  \_/  \_/
             ____ ____ ____ ____ ____ ____ ____ ____ ____ ____    
Data    ____/    X____X____X____X____X____X____X____X____X____X________
            Start   0    1    2    3    4    5    6    7    P  Stop

Start bit:  can be long as 300-350us.
Inhibit:    Pull Data line down to inhibit keyboard to send.
Timing:     Host reads bit while Clock is hi.
Stop bit:   Keyboard pulls down Data line to lo after 9th clock.
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
