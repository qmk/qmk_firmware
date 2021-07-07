/*
Copyright 2014 Jun WAKO <wakojun@gmail.com>
*/

#pragma once

#define IBM4704_ERR_NONE 0
#define IBM4704_ERR_PARITY 0x70

void    ibm4704_init(void);
uint8_t ibm4704_send(uint8_t data);
uint8_t ibm4704_recv_response(void);
uint8_t ibm4704_recv(void);

/* Check pin configuration */
#if !(defined(IBM4704_CLOCK_PORT) && defined(IBM4704_CLOCK_PIN) && defined(IBM4704_CLOCK_DDR) && defined(IBM4704_CLOCK_BIT))
#    error "ibm4704 clock pin configuration is required in config.h"
#endif

#if !(defined(IBM4704_DATA_PORT) && defined(IBM4704_DATA_PIN) && defined(IBM4704_DATA_DDR) && defined(IBM4704_DATA_BIT))
#    error "ibm4704 data pin configuration is required in config.h"
#endif

/*--------------------------------------------------------------------
 * static functions
 *------------------------------------------------------------------*/
static inline void clock_lo(void) {
    IBM4704_CLOCK_PORT &= ~(1 << IBM4704_CLOCK_BIT);
    IBM4704_CLOCK_DDR |= (1 << IBM4704_CLOCK_BIT);
}
static inline void clock_hi(void) {
    /* input with pull up */
    IBM4704_CLOCK_DDR &= ~(1 << IBM4704_CLOCK_BIT);
    IBM4704_CLOCK_PORT |= (1 << IBM4704_CLOCK_BIT);
}
static inline bool clock_in(void) {
    IBM4704_CLOCK_DDR &= ~(1 << IBM4704_CLOCK_BIT);
    IBM4704_CLOCK_PORT |= (1 << IBM4704_CLOCK_BIT);
    _delay_us(1);
    return IBM4704_CLOCK_PIN & (1 << IBM4704_CLOCK_BIT);
}
static inline void data_lo(void) {
    IBM4704_DATA_PORT &= ~(1 << IBM4704_DATA_BIT);
    IBM4704_DATA_DDR |= (1 << IBM4704_DATA_BIT);
}
static inline void data_hi(void) {
    /* input with pull up */
    IBM4704_DATA_DDR &= ~(1 << IBM4704_DATA_BIT);
    IBM4704_DATA_PORT |= (1 << IBM4704_DATA_BIT);
}
static inline bool data_in(void) {
    IBM4704_DATA_DDR &= ~(1 << IBM4704_DATA_BIT);
    IBM4704_DATA_PORT |= (1 << IBM4704_DATA_BIT);
    _delay_us(1);
    return IBM4704_DATA_PIN & (1 << IBM4704_DATA_BIT);
}

static inline uint16_t wait_clock_lo(uint16_t us) {
    while (clock_in() && us) {
        asm("");
        _delay_us(1);
        us--;
    }
    return us;
}
static inline uint16_t wait_clock_hi(uint16_t us) {
    while (!clock_in() && us) {
        asm("");
        _delay_us(1);
        us--;
    }
    return us;
}
static inline uint16_t wait_data_lo(uint16_t us) {
    while (data_in() && us) {
        asm("");
        _delay_us(1);
        us--;
    }
    return us;
}
static inline uint16_t wait_data_hi(uint16_t us) {
    while (!data_in() && us) {
        asm("");
        _delay_us(1);
        us--;
    }
    return us;
}

/* idle state that device can send */
static inline void idle(void) {
    clock_hi();
    data_hi();
}

/* inhibit device to send
 * keyboard checks Data line on start bit(Data:hi) and it stops sending if Data line is low.
 */
static inline void inhibit(void) {
    clock_hi();
    data_lo();
}
