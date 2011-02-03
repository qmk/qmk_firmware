/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "util.h"
#include "debug.h"
#include "ps2.h"
#include "usb_keyboard.h"
#include "matrix_skel.h"


#if (MATRIX_COLS > 16)
#   error "MATRIX_COLS must not exceed 16"
#endif
#if (MATRIX_ROWS > 255)
#   error "MATRIX_ROWS must not exceed 255"
#endif


/*
 * Matrix usage:
 * "PS/2 Scan Codes Set 2" is assigned to 256(32x8)cells matrix.
 * Hmm, It is very sparse and not efficient :(
 *
 *      8bit
 *    ---------
 *  0|         |
 *  :|   XX    | 00-7F for normal codes(without E0-prefix)
 *  f|_________|
 * 10|         |
 *  :|  E0 XX  | 80-FF for E0-prefix codes(use (XX|0x80) as code)
 * 1f|         |
 *    ---------
 * exceptions:
 * 83:    F8[0x83](normal codes but > 0x7F)
 * FC:    PrintScreen[E0 7C or 84]
 * FE:    Puause
 */
#define F8             (0x83)
#define PRINT_SCREEN   (0xFC)
#define PAUSE          (0xFE)
#define ROW(code)      (code>>3)
#define COL(code)      (code&0x07)

static bool is_modified = false;

// matrix state buffer(1:on, 0:off)
#if (MATRIX_COLS <= 8)
static uint8_t matrix[MATRIX_ROWS];
#else
static uint16_t matrix[MATRIX_ROWS];
#endif

#ifdef MATRIX_HAS_GHOST
static bool matrix_has_ghost_in_row(uint8_t row);
#endif
static void matrix_make(uint8_t code);
static void matrix_break(uint8_t code);
static void ps2_reset(void);
static void ps2_set_leds(uint8_t leds);


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

void matrix_init(void)
{
    ps2_host_init();
    _delay_ms(1000);

    // flush LEDs
/*
    ps2_set_leds(1<<PS2_LED_NUM_LOCK);
    _delay_ms(100);
    ps2_set_leds(1<<PS2_LED_NUM_LOCK|1<<PS2_LED_CAPS_LOCK);
    _delay_ms(100);
    ps2_set_leds(1<<PS2_LED_NUM_LOCK|1<<PS2_LED_CAPS_LOCK|1<<PS2_LED_SCROLL_LOCK);
    _delay_ms(300);
    ps2_set_leds(0x00);
*/
    
    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    return;
}

/*
 * PS/2 Scan Code Set 2: Exceptional Handling
 *
 * There are several keys to be handled exceptionally.
 * The scan code for these keys are varied or prefix/postfix'd
 * depending on modifier key state.
 *
 * References:
 *     http://www.microsoft.com/whdc/archive/scancode.mspx
 *     http://download.microsoft.com/download/1/6/1/161ba512-40e2-4cc9-843a-923143f3456c/scancode.doc
 *
 *
 * Insert, Delete, Home, End, PageUp, PageDown, Up, Down, Right, Left:
 *     Num Lock: off
 *     modifiers | make                      | break
 *     ----------+---------------------------+----------------------
 *     Ohter     |                    <make> | <break>
 *     LShift    | E0 F0 12           <make> | <break>  E0 12
 *     RShift    | E0 F0 59           <make> | <break>  E0 59
 *     L+RShift  | E0 F0 12  E0 F0 59 <make> | <break>  E0 59 E0 12
 *
 *     Num Lock: on
 *     modifiers | make                      | break
 *     ----------+---------------------------+----------------------
 *     Other     | E0 12              <make> | <break>  E0 F0 12
 *     Shift'd   |                    <make> | <break>
 *
 *     Handling: ignore these prefix/postfix codes
 *
 *
 * Keypad-/:
 *     modifiers | make                      | break
 *     ----------+---------------------------+----------------------
 *     Ohter     |                    <make> | <break>
 *     LShift    | E0 F0 12           <make> | <break>  E0 12
 *     RShift    | E0 F0 59           <make> | <break>  E0 59
 *     L+RShift  | E0 F0 12  E0 F0 59 <make> | <break>  E0 59 E0 12
 *
 *     Handling: ignore these prefix/postfix codes
 *
 *
 * PrintScreen:
 *     With hoding down modifiers, the scan code is sent as following:
 *
 *     modifiers | make         | break
 *     ----------+--------------+-----------------------------------
 *     Other     | E0 12  E0 7C | E0 F0 7C  E0 F0 12
 *     Shift'd   |        E0 7C | E0 F0 7C
 *     Control'd |        E0 7C | E0 F0 7C
 *     Alt'd     |           84 | F0 84
 *
 *     Handling: ignore prefix/postfix codes and treat both scan code
 *               E0 7C and 84 as PrintScreen.
 *
 * Pause:
 *     With hoding down modifiers, the scan code is sent as following:
 *
 *     modifiers | make(no break code)
 *     ----------+--------------------------------------------------
 *     no mods   | E1 14 77 E1 F0 14 F0 77
 *     Control'd | E0 7E E0 F0 7E
 *
 *     Handling: treat these two code sequence as Pause
 *
 */
uint8_t matrix_scan(void)
{

    static enum {
        INIT,
        F0,
        E0,
        E0_F0,
        // states for Pause/Break
        E1,
        E1_14,
        E1_14_77,
        E1_14_77_E1,
        E1_14_77_E1_F0,
        E1_14_77_E1_F0_14,
        E1_14_77_E1_F0_14_F0,
    } state = INIT;


    is_modified = false;

    // Pause/Break off(PS/2 has no break for this key)
    if (matrix_is_on(ROW(PAUSE), COL(PAUSE))) {
        matrix_break(PAUSE);
    }

    uint8_t code;
    code = ps2_host_recv();
    if (code == 0x00) return 0;
    //while ((code = ps2_host_recv())) {
//phex(code); print(" ");
        switch (state) {
            case INIT:
                switch (code) {
                    case 0xE0:  // 2byte make
                        state = E0;
                        break;
                    case 0xF0:  // break code
                        state = F0;
                        break;
                    case 0xE1:  // Pause/Break
                        state = E1;
                        break;
                    case 0x83:  // F8
                        matrix_make(F8);
                        state = INIT;
                        break;
                    case 0x84:  // PrintScreen
                        matrix_make(PRINT_SCREEN);
                        state = INIT;
                        break;
                    default:    // normal key make
                        if (code < 0x80) {
                            matrix_make(code);
                        } else {
                            debug("unexpected scan code at INIT: "); debug_hex(code); debug("\n");
                        }
                        state = INIT;
                }
                break;
            case E0:
                switch (code) {
                    case 0x12:  // postfix/postfix code for exceptional keys
                    case 0x59:  // postfix/postfix code for exceptional keys
                        // ignore
                        state = INIT;
                        break;
                    case 0x7E:  // former part of Control-Pause[E0 7E  E0 F0 7E]
                        matrix_make(PAUSE);
                        state = INIT;
                        break;
                    case 0xF0:  // E0 break
                        state = E0_F0;
                        break;
                    default:    // E0 make
                        if (code < 0x80) {
                            matrix_make(code|0x80);
                        } else {
                            debug("unexpected scan code at E0: "); debug_hex(code); debug("\n");
                        }
                        state = INIT;
                }
                break;
            case F0:
                switch (code) {
                    case 0x83:
                        matrix_break(F8);
                        state = INIT;
                        break;
                    case 0x84:
                        matrix_break(PRINT_SCREEN);
                        state = INIT;
                        break;
                    default:
                    if (code < 0x80) {
                        matrix_break(code);
                    } else {
                        debug("unexpected scan code at F0: "); debug_hex(code); debug("\n");
                    }
                    state = INIT;
                }
                break;
            case E0_F0: // E0 break
                switch (code) {
                    case 0x12:  // postfix/postfix code for exceptional keys
                    case 0x59:  // postfix/postfix code for exceptional keys
                    case 0x7E:  // latter part of Control-Pause[E0 7E  E0 F0 7E]
                        // ignore
                        state = INIT;
                        break;
                    default:
                        if (code < 0x80) {
                            matrix_break(code|0x80);
                        } else {
                            debug("unexpected scan code at E0_F0: "); debug_hex(code); debug("\n");
                        }
                        state = INIT;
                }
                break;
            /* Pause */
            case E1:
                switch (code) {
                    case 0x14:
                        state = E1_14;
                        break;
                    default:
                        state = INIT;
                }
                break;
            case E1_14:
                switch (code) {
                    case 0x77:
                        state = E1_14_77;
                        break;
                    default:
                        state = INIT;
                }
                break;
            case E1_14_77:
                switch (code) {
                    case 0xE1:
                        state = E1_14_77_E1;
                        break;
                    default:
                        state = INIT;
                }
                break;
            case E1_14_77_E1:
                switch (code) {
                    case 0xF0:
                        state = E1_14_77_E1_F0;
                        break;
                    default:
                        state = INIT;
                }
                break;
            case E1_14_77_E1_F0:
                switch (code) {
                    case 0x14:
                        state = E1_14_77_E1_F0_14;
                        break;
                    default:
                        state = INIT;
                }
                break;
            case E1_14_77_E1_F0_14:
                switch (code) {
                    case 0xF0:
                        state = E1_14_77_E1_F0_14_F0;
                        break;
                    default:
                        state = INIT;
                }
                break;
            case E1_14_77_E1_F0_14_F0:
                switch (code) {
                    case 0x77:
                        matrix_make(PAUSE);
                        state = INIT;
                        break;
                    default:
                        state = INIT;
                }
                break;
            default:
                state = INIT;
        }
    //}
//print("|");

    // handle LED indicators
/*
    static uint8_t prev_leds = 0;
    if (prev_leds != usb_keyboard_leds) {
        uint8_t leds = 0;
        if (usb_keyboard_leds&(1<<USB_LED_SCROLL_LOCK))
            leds |= (1<<PS2_LED_SCROLL_LOCK);
        if (usb_keyboard_leds&(1<<USB_LED_NUM_LOCK))
            leds |= (1<<PS2_LED_NUM_LOCK);
        if (usb_keyboard_leds&(1<<USB_LED_CAPS_LOCK))
            leds |= (1<<PS2_LED_CAPS_LOCK);

        ps2_set_leds(leds);
        prev_leds = usb_keyboard_leds;
    }
*/

    return 1;
}

bool matrix_is_modified(void)
{
    return is_modified;
}

inline
bool matrix_has_ghost(void)
{
#ifdef MATRIX_HAS_GHOST
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix_has_ghost_in_row(i))
            return true;
    }
#endif
    return false;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline
#if (MATRIX_COLS <= 8)
uint8_t matrix_get_row(uint8_t row)
#else
uint16_t matrix_get_row(uint8_t row)
#endif
{
    return matrix[row];
}

void matrix_print(void)
{
#if (MATRIX_COLS <= 8)
    print("\nr/c 01234567\n");
#else
    print("\nr/c 0123456789ABCDEF\n");
#endif
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
#if (MATRIX_COLS <= 8)
        pbin_reverse(matrix_get_row(row));
#else
        pbin_reverse16(matrix_get_row(row));
#endif
#ifdef MATRIX_HAS_GHOST
        if (matrix_has_ghost_in_row(row)) {
            print(" <ghost");
        }
#endif
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
#if (MATRIX_COLS <= 8)
        count += bitpop(matrix[i]);
#else
        count += bitpop16(matrix[i]);
#endif
    }
    return count;
}

#ifdef MATRIX_HAS_GHOST
inline
static bool matrix_has_ghost_in_row(uint8_t row)
{
    // no ghost exists in case less than 2 keys on
    if (((matrix[row] - 1) & matrix[row]) == 0)
        return false;

    // ghost exists in case same state as other row
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && (matrix[i] & matrix[row]) == matrix[row])
            return true;
    }
    return false;
}
#endif


inline
static void matrix_make(uint8_t code)
{
    if (!matrix_is_on(ROW(code), COL(code))) {
        matrix[ROW(code)] |= 1<<COL(code);
        is_modified = true;
        //print("matrix_make: "); phex(code); print("\n");
    }
}

inline
static void matrix_break(uint8_t code)
{
    if (matrix_is_on(ROW(code), COL(code))) {
        matrix[ROW(code)] &= ~(1<<COL(code));
        is_modified = true;
        //print("matrix_break: "); phex(code); print("\n");
    }
}

static void ps2_reset(void)
{
    ps2_host_send(0xFF);
    if (ps2_host_recv() != 0xFA) return;
    _delay_ms(1000);
    if (ps2_host_recv() != 0xAA) return;
}

static void ps2_set_leds(uint8_t leds)
{
        ps2_host_send(0xED);
        if (ps2_host_recv() != 0xFA) return;        // 0xFA
        ps2_host_send(leds);
        if (ps2_host_recv() != 0xFA) return;        // 0xFA
}
