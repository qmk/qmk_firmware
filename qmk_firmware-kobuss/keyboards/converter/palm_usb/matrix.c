/*
Copyright 2018 milestogo 
with elements Copyright 2014 cy384 under a modified BSD license
building on qmk structure Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "protocol/serial.h"
#include "timer.h"


/*
 * Matrix Array usage:
 *
 * ROW: 12(4bits)
 * COL:  8(3bits)
 *
 *   +---------+
 *  0|00 ... 07|
 *  1|00 ... 07|
 *  :|   ...   |
 *  :|   ...   |
 *  A|         |
 *  B|         |
 *   +---------+
 */
static uint8_t matrix[MATRIX_ROWS];


// we're going to need a sleep timer
static uint16_t last_activity ;
// and a byte to track duplicate up events signalling all keys up. 
static uint16_t last_upKey ;
// serial device can disconnect. Check every MAXDROP characters. 
static uint16_t disconnect_counter = 0;


// bitmath masks. 
#define KEY_MASK 0b10000000
#define COL_MASK 0b00000111
#define ROW_MASK 0b01111000


#define ROW(code)    (( code & ROW_MASK ) >>3)
#define COL(code)    ((code & COL_MASK) )
#define KEYUP(code) ((code & KEY_MASK) >>7 )

static bool is_modified = false;

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

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}


void pins_init(void) {
 // set pins for pullups, Rts , power &etc. 

    //print ("pins setup\n");
    setPinOutput(VCC_PIN);
    writePinLow(VCC_PIN);

#if ( HANDSPRING == 0)

#ifdef CY835
    setPinOutput(GND_PIN);
    writePinLow(GND_PIN);

    setPinOutput(PULLDOWN_PIN);
    writePinLow(PULLDOWN_PIN);
#endif

    setPinInput(DCD_PIN);
    setPinInput(RTS_PIN);
#endif

/* check that the other side isn't powered up. 
    test=readPin(DCD_PIN);
    xprintf("b%02X:", test);
    test=readPin(RTS_PIN);
    xprintf("%02X\n", test);
*/
 
}

uint8_t rts_reset(void) {
    static uint8_t firstread ;
/* bounce RTS so device knows it is rebooted */

// On boot, we keep rts as input, then switch roles here
// on leaving sleep, we toggle the same way

    firstread=readPin(RTS_PIN);
   // printf("r%02X:", firstread);

    setPinOutput(RTS_PIN);

    if (firstread) {
        writePinLow(RTS_PIN);
    } 
     _delay_ms(10);
    writePinHigh(RTS_PIN);
    

/* the future is Arm 
    if (!palReadPad(RTS_PIN_IOPRT))
  {
    _delay_ms(10);
    palSetPadMode(RTS_PINn_IOPORT, PinDirectionOutput_PUSHPULL);
    palSetPad(RTS_PORT, RTS_PIN);
  }
  else
  {
    palSetPadMode(RTS_PIN_RTS_PORT, PinDirectionOutput_PUSHPULL);
    palSetPad(RTS_PORT, RTS_PIN);
    palClearPad(RTS_PORT, RTS_PIN);
    _delay_ms(10);
    palSetPad(RTS_PORT, RTS_PIN);
  }
*/


 _delay_ms(5);  
 //print("rts\n");
 return 1;
}

uint8_t get_serial_byte(void) {
    static uint8_t code;
    while(1) {
        code = serial_recv();
        if (code) { 
            debug_hex(code); debug(" ");
            return code;
        }
    }
}

uint8_t palm_handshake(void) {
    // assumes something has seen DCD go high, we've toggled RTS 
    // and we now need to verify handshake. 
    // listen for up to 4 packets before giving up. 
    // usually I get the sequence FF FA FD
    static uint8_t codeA=0;
 
    for (uint8_t i=0; i < 5; i++) {
        codeA=get_serial_byte();
        if ( 0xFA == codeA) {
            if( 0xFD == get_serial_byte()) {
                return 1;
            }
        }
    }
    return 0;
}

uint8_t palm_reset(void) {
    print("@");
    rts_reset();  // shouldn't need to power cycle. 

    if ( palm_handshake() ) {
        last_activity = timer_read();
        return 1;
    } else { 
        print("failed reset");
        return 0;
    }

}

uint8_t handspring_handshake(void) {
    // should be sent 15 ms after power up. 
    // listen for up to 4 packets before giving up. 
    static uint8_t codeA=0;
 
    for (uint8_t i=0; i < 5; i++) {
        codeA=get_serial_byte();
        if ( 0xF9 == codeA) {
            if( 0xFB == get_serial_byte()) {
                return 1;
            }
        }
    }
    return 0;
}

uint8_t handspring_reset(void) {
    writePinLow(VCC_PIN);
    _delay_ms(5);
    writePinHigh(VCC_PIN);

    if ( handspring_handshake() ) {
        last_activity = timer_read();
        disconnect_counter=0;
        return 1;
    } else { 
        print("-HSreset");
        return 0;   
    }
}

void matrix_init(void)
{
    debug_enable = true;
    //debug_matrix =true;
    
    serial_init(); // arguments all #defined 
 
#if (HANDSPRING == 0)
    pins_init(); // set all inputs and outputs. 
#endif

    print("power up\n");
    writePinHigh(VCC_PIN);

    // wait for DCD strobe from keyboard - it will do this 
    // up to 3 times, then the board needs the RTS toggled to try again
  
#if ( HANDSPRING == 1)
    if ( handspring_handshake() ) {
        last_activity = timer_read();
    } else { 
        print("failed handshake");
        _delay_ms(1000);
        //BUG /should/ power cycle or toggle RTS & reset, but this usually works. 
    }

#else  /// Palm / HP  device with DCD
    while( !readPin(DCD_PIN) ) {;} 
    print("dcd\n");

    rts_reset(); // at this point the keyboard should think all is well. 

    if ( palm_handshake() ) {
        last_activity = timer_read();
    } else { 
        print("failed handshake");
        _delay_ms(1000);
        //BUG /should/ power cycle or toggle RTS & reset, but this usually works. 
    }

#endif

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    matrix_init_quantum();
    return;
    
    
}


uint8_t matrix_scan(void)
{
    uint8_t code;
    code = serial_recv();
    if (!code) {
/*         
        disconnect_counter ++;
        if (disconnect_counter > MAXDROP) {
            //  set all keys off
             for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00; 
        }
*/
        // check if the keyboard is asleep. 
        if (timer_elapsed(last_activity) > SLEEP_TIMEOUT) {
#if(HANDSPRING ==0 )
            palm_reset();
#else
            handspring_reset();
#endif
            return 0;
        } 

    }

   last_activity = timer_read();
   disconnect_counter=0; // if we are getting serial data, we're connected. 

    debug_hex(code); debug(" ");


    switch (code) {
        case 0xFD:  // unexpected reset byte 2
             print("rstD ");
            return 0;
        case 0xFA:  // unexpected reset
            print("rstA ");
            return 0;
    }

    if (KEYUP(code)) {
        if (code == last_upKey) {
            // all keys are not pressed. 
            // Manual says to disable all modifiers left open now. 
            // but that could defeat sticky keys. 
            // BUG? dropping this byte. 
            last_upKey=0;
            return 0;
        }
        // release
        if (matrix_is_on(ROW(code), COL(code))) {
            matrix[ROW(code)] &= ~(1<<COL(code));
            last_upKey=code;
        }
    } else {
       // press
        if (!matrix_is_on(ROW(code), COL(code))) {
            matrix[ROW(code)] |= (1<<COL(code));

        }
    }

    matrix_scan_quantum();
    return code;
}

bool matrix_is_modified(void)
{
    return is_modified;
}

inline
bool matrix_has_ghost(void)
{
    return false;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline
uint8_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop(matrix[i]);
    }
    return count;
}
