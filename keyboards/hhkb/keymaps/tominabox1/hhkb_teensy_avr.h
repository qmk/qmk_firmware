#ifndef HHKB_AVR_H
#define HHKB_AVR_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// Timer resolution check
#if (1000000/TIMER_RAW_FREQ > 20)
#   error "Timer resolution(>20us) is not enough for HHKB matrix scan tweak on V-USB."
#endif


/*
 * HHKB Matrix I/O
 *
 * row:     HC4051[A,B,C]  selects scan row0-7
 * row-ext: [En0,En1] row extention for JP
 * col:     LS145[A,B,C,D] selects scan col0-7 and enable(D)
 * key:     on: 0/off: 1
 * prev:    hysteresis control: assert(1) when previous key state is on
 */

/*
 * For TMK HHKB teensy based controller(ATMega32U4)
 *
 * row:     PB0-2
 * col:     PB3-5,6
 * key:     PF0(pull-uped)
 * prev:    PF1
 *
 */
static inline void KEY_ENABLE(void) { (PORTB &= ~(1<<6)); }
static inline void KEY_UNABLE(void) { (PORTB |=  (1<<6)); }
static inline bool KEY_STATE(void) { return (PINF & (1<<0)); }
static inline void KEY_PREV_ON(void) { (PORTF |=  (1<<1)); }
static inline void KEY_PREV_OFF(void) { (PORTF &= ~(1<<1)); }
static inline void KEY_POWER_ON(void) {}
static inline void KEY_POWER_OFF(void) {}
static inline bool KEY_POWER_STATE(void) { return true; }
static inline void KEY_INIT(void)
{
    /* row,col,prev: output */
    DDRB  = 0xFF;
    PORTB = 0x00;   // unable
    KEY_UNABLE();
    KEY_PREV_OFF();
    KEY_POWER_OFF();
}
static inline void KEY_SELECT(uint8_t ROW, uint8_t COL)
{
    PORTB = (PORTB & 0xC0) | (((COL) & 0x07)<<3) | ((ROW) & 0x07);
}


#endif
