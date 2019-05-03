#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "quantum.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "matrix.h"
#include <avr/interrupt.h>


/*
 * Infinity Pinusage:
 * Column pins are input with internal pull-down. Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *  INFINITY PRODUCTION (NO LED)
 *     col: { PTD1, PTD2, PTD3, PTD4, PTD5, PTD6, PTD7 }
 *     row: { PTB0, PTB1, PTB2, PTB3, PTB16, PTB17, PTC4, PTC5, PTD0 }
 *  INFINITY PRODUCTION (WITH LED)
 *     col: { PTD1, PTD2, PTD3, PTD4, PTD5, PTD6, PTD7 }
 *     row: { PTC0, PTC1, PTC2, PTC3, PTC4, PTC5, PTC6, PTC7, PTD0 }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
// static bool debouncing = false;
// static uint16_t debouncing_time = 0;
volatile uint8_t portb_buffer = 0;
volatile uint8_t portc_buffer = 0;
volatile uint8_t portd_buffer = 0;
volatile uint8_t porte_buffer = 0;
volatile uint8_t portb_buffer1 = 0;
volatile uint8_t portc_buffer1 = 0;
volatile uint8_t portd_buffer1 = 0;
volatile uint8_t porte_buffer1 = 0;
volatile uint8_t portb_buffer2 = 0;
volatile uint8_t portc_buffer2 = 0;
volatile uint8_t portd_buffer2 = 0;
volatile uint8_t porte_buffer2 = 0;
volatile uint8_t portb_buffer3 = 0;
volatile uint8_t portc_buffer3 = 0;
volatile uint8_t portd_buffer3 = 0;
volatile uint8_t porte_buffer3 = 0;
volatile uint8_t triggered = 0;
// static uint8_t portf_buffer = 0;
static uint32_t switch_buffer = 0;


void matrix_init(void) {
    //Set I/O as pull-up inputs to read states
    setPinInputHigh(B7);
DDRC = 0x00;        //make port a as input
PORTC = 0xFF;       //enable all pull-ups 
    setPinInputHigh(D0);
    setPinInputHigh(D1);
    setPinInputHigh(D2);
    setPinInputHigh(D3);
    setPinInputHigh(D4);
    setPinInputHigh(D5);
    setPinInputHigh(D7);
    setPinInputHigh(E0);
    setPinInputHigh(E1);
    setPinInputHigh(F0);
    setPinInputHigh(F1);
    setPinInputHigh(F3);
    setPinInputHigh(F5);
    setPinInputHigh(F7);

    cli();
    EIMSK = 1 << INT3 | 1 << INT2 | 1 << INT1;
    EICRA = 1 << ISC11 | 0 << ISC10| 1 << ISC21 | 0 << ISC20| 1 << ISC31 | 0 << ISC30;
    sei();

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    matrix_init_quantum();
}

ISR(INT3_vect){
    portb_buffer3 = PINB;
    portc_buffer3 = PINC;
    portd_buffer3 = PIND;
    porte_buffer3 = PINE;
    if (!triggered){
        portb_buffer = portb_buffer3;
        portc_buffer = portc_buffer3;
        portd_buffer = portd_buffer3;
        porte_buffer = porte_buffer3;
        triggered = 1;
    }
}

ISR(INT2_vect){
    portb_buffer2 = PINB;
    portc_buffer2 = PINC;
    portd_buffer2 = PIND;
    porte_buffer2 = PINE;
    if (!triggered){
        portb_buffer = portb_buffer2;
        portc_buffer = portc_buffer2;
        portd_buffer = portd_buffer2;
        porte_buffer = porte_buffer2;
        triggered = 1;
    }
}

ISR(INT1_vect){
    portb_buffer1 = PINB;
    portc_buffer1 = PINC;
    portd_buffer1 = PIND;
    porte_buffer1 = PINE;
    if (!triggered){
        portb_buffer = portb_buffer1;
        portc_buffer = portc_buffer1;
        portd_buffer = portd_buffer1;
        porte_buffer = porte_buffer1;
        triggered = 1;
    }
}

uint8_t matrix_scan(void) {
    // matrix_row_t data = 0;

    switch_buffer = (((uint32_t)portc_buffer) | ((uint32_t)(portd_buffer & 0x01) << 8) | ((uint32_t)(portd_buffer & 0x02) << 8) | ((uint32_t)(portd_buffer & 0x04) << 8) | (((uint32_t)portd_buffer & 0x08) << 8) | (((uint32_t)portd_buffer & 0x10) << 8) | (((uint32_t)portd_buffer & 0x20) << 8) | (((uint32_t)portd_buffer & 0x80) << 7) | (((uint32_t)porte_buffer & 0x01) << 15) | (((uint32_t)porte_buffer & 0x02) << 15) | (((uint32_t)portb_buffer & 0x80) << 10));

    switch (switch_buffer) {
        case 0x1134E: matrix[0] = 0x01; triggered = 0; break;
        case 0x3774D: matrix[0] = 0x02; triggered = 0; break;
        case 0x10BCC: matrix[0] = 0x04; triggered = 0; break;
        case 0x16B4B: matrix[0] = 0x08; triggered = 0; break;
        case 0x167CA: matrix[0] = 0x10; triggered = 0; break;
        case 0x35FC9: matrix[0] = 0x20; triggered = 0; break;
        case 0x15B48: matrix[0] = 0x40; triggered = 0; break;
        case 0x28347: matrix[0] = 0x80; triggered = 0; break;
        case 0x173C6: matrix[0] = 0x100; triggered = 0; break;
        case 0x143CF: matrix[0] = 0x200; triggered = 0; break;
        case 0x3FDC5: matrix[0] = 0x400; triggered = 0; break;
        case 0x3FD21: matrix[0] = 0x800; triggered = 0; break;
        case 0x3FD77: matrix[0] = 0x1000; triggered = 0; break;
        case 0x3E7FA: matrix[0] = 0x8000; triggered = 0; break;
        case 0x183EE: matrix[0] = 0x10000; triggered = 0; break;
        case 0x197F3: matrix[0] = 0x20000; triggered = 0; break;
        case 0x1AB7E: matrix[0] = 0x40000; triggered = 0; break;
        default: matrix[0] = 0x00;
                 matrix[1] = 0x00;
                 triggered = 0;
    //              matrix_debouncing[1] = 0x00;
    //              matrix_debouncing[2] = 0x00;
    //              matrix_debouncing[3] = 0x00;
     }
        //      if (portb_buffer != 255){
        // uprintf("B%d", portb_buffer);
        // }
        // if (portc_buffer != 255){
        // uprintf("C%d", portc_buffer);
        // }

        // if (portd_buffer != 255){
        // uprintf("D%d", portd_buffer);
        // }
        // if (porte_buffer != 255){
        // uprintf("E%d", porte_buffer);
        // uprintf("S%lu\n", (switch_buffer));
        // }
portb_buffer = 255;
portc_buffer = 255;
portd_buffer = 255;
porte_buffer = 255;
    
    // for (int row = 0; row < MATRIX_ROWS; row++) {
    //     if (matrix_debouncing[row] != data) {
    //         matrix_debouncing[row] = data;
    //         debouncing = true;
    //         debouncing_time = timer_read();
    //     }
    // }

    // if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        // for (int row = 0; row < MATRIX_ROWS; row++) {
        //     matrix[row] = matrix_debouncing[row];
        // }
    //     debouncing = false;
    // }
        // if (portc_buffer != 255){
        // uprintf("X%d", portc_buffer);
        // }
    matrix_scan_quantum();
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    //xprintf(switch_buffer);
//     xprintf("\nr/c 01234567\n");
//     for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
//         xprintf("%02X: ");
//         matrix_row_t data = matrix_get_row(row);
//         for (int col = 0; col < MATRIX_COLS; col++) {
//             if (data & (1<<col))
//                 xprintf("1");
//             else
//                 xprintf("0");
//         }
//         xprintf("\n");
//     }
}

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

