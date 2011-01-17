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
 *  :|   XX    | 00-7F for normal codes
 *  f|_________|
 * 10|         |
 *  :|  E0 XX  | 80-FF for E0-prefix codes(use (XX|0x80) as code)
 * 1f|         |
 *    ---------
 * exceptions:
 * 0x83: F8(normal code placed beyond 0x7F)
 * 0xFE: PrintScreen
 * 0xFF: Puause/Break
 */
#define _PRINT_SCREEN   (0xFE)
#define _PAUSE_BREAK    (0xFF)
#define _ROW(code)      (code>>3)
#define _COL(code)      (code&0x07)

static bool _matrix_is_modified = false;

// matrix state buffer(1:on, 0:off)
#if (MATRIX_COLS <= 8)
static uint8_t *matrix;
static uint8_t _matrix0[MATRIX_ROWS];
#else
static uint16_t *matrix;
static uint16_t _matrix0[MATRIX_ROWS];
#endif

#ifdef MATRIX_HAS_GHOST
static bool matrix_has_ghost_in_row(uint8_t row);
#endif
static void _matrix_make(uint8_t code);
static void _matrix_break(uint8_t code);
static void _ps2_reset(void);
static void _ps2_set_leds(uint8_t leds);


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
    print_enable = true;
    ps2_host_init();

    _ps2_reset();

    // flush LEDs
    _ps2_set_leds(1<<PS2_LED_NUM_LOCK);
    _delay_ms(100);
    _ps2_set_leds(1<<PS2_LED_NUM_LOCK|1<<PS2_LED_CAPS_LOCK);
    _delay_ms(100);
    _ps2_set_leds(1<<PS2_LED_NUM_LOCK|1<<PS2_LED_CAPS_LOCK|1<<PS2_LED_SCROLL_LOCK);
    _delay_ms(300);
    _ps2_set_leds(0x00);
    
    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    matrix = _matrix0;

    return;
}

uint8_t matrix_scan(void)
{

    static enum {
        INIT,
        BREAK,
        E0,
        E0_F0,
        // states for PrintScreen
        E0_12,
        E0_12_E0,
        E0_F0_7C,
        E0_F0_7C_E0,
        E0_F0_7C_E0_F0,
        // states for Pause/Break
        E1,
        E1_14,
        E1_14_77,
        E1_14_77_E1,
        E1_14_77_E1_F0,
        E1_14_77_E1_F0_14,
        E1_14_77_E1_F0_14_F0,
    } state = INIT;


    _matrix_is_modified = false;

    // Pause/Break off(PS/2 has no break for this key)
    if (matrix_is_on(_ROW(_PAUSE_BREAK), _COL(_PAUSE_BREAK))) {
        _matrix_break(_PAUSE_BREAK);
    }

    uint8_t code;
    while ((code = ps2_host_recv())) {
        switch (state) {
            case INIT:
                switch (code) {
                    case 0xE0:  // 2byte make
                        state = E0;
                        break;
                    case 0xF0:  // break code
                        state = BREAK;
                        break;
                    case 0xE1:  // Pause/Break
                        state = E1;
                        break;
                    default:    // normal key make
                        if (code < 0x80) {
                            _matrix_make(code);
                        } else {
                            debug("ps/2 unknow code: "); debug_hex(code); debug("\n");
                        }
                        state = INIT;
                }
                break;
            case E0:
                switch (code) {
                    case 0x12:  // PrintScreen(make)
                        state = E0_12;
                        break;
                    case 0x7C:  // PrintScreen(typematic)
                        // ignore
                        state = INIT;
                        break;
                    case 0xF0:  // E0 break
                        state = E0_F0;
                        break;
                    default:    // E0 make
                        if (code < 0x80) {
                            _matrix_make(code|0x80);
                        } else {
                            debug("ps/2 unknow code: "); debug_hex(code); debug("\n");
                        }
                        state = INIT;
                }
                break;
            case BREAK:
                if (code < 0x80) {
                    _matrix_break(code);
                } else {
                    debug("ps/2 unknow code: "); debug_hex(code); debug("\n");
                }
                state = INIT;
                break;
            case E0_F0: // E0 break
                switch (code) {
                    case 0x7C:
                        state = E0_F0_7C;
                        break;
                    default:
                        if (code < 0x80) {
                            _matrix_break(code|0x80);
                        } else {
                            debug("ps/2 unknow code: "); debug_hex(code); debug("\n");
                        }
                        state = INIT;
                }
                break;
            /* PrintScreen(make) */
            case E0_12:
                switch (code) {
                    case 0xE0:
                        state = E0_12_E0;
                        break;
                    default:
                        state = INIT;
                }
                break;
            case E0_12_E0:
                switch (code) {
                    case 0x7C:
                        _matrix_make(_PRINT_SCREEN);
                        state = INIT;
                        break;
                    default:
                        state = INIT;
                }
                break;
            /* PrintScreen(break) */
            case E0_F0_7C:
                switch (code) {
                    case 0xE0:
                        state = E0_F0_7C_E0;
                        break;
                    default:
                        state = INIT;
                }
                break;
            case E0_F0_7C_E0:
                switch (code) {
                    case 0xF0:
                        state = E0_F0_7C_E0_F0;
                        break;
                    default:
                        state = INIT;
                }
                break;
            case E0_F0_7C_E0_F0:
                switch (code) {
                    case 0x12:
                        _matrix_break(_PRINT_SCREEN);
                        state = INIT;
                        break;
                    default:
                        state = INIT;
                }
                break;
            /* Pause/Break */
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
                        _matrix_make(_PAUSE_BREAK);
                        state = INIT;
                        break;
                    default:
                        state = INIT;
                }
                break;
            default:
                state = INIT;
        }
    }

    static uint8_t prev_leds = 0;
    if (prev_leds != usb_keyboard_leds) {
        uint8_t leds = 0;
        if (usb_keyboard_leds&(1<<USB_LED_SCROLL_LOCK))
            leds |= (1<<PS2_LED_SCROLL_LOCK);
        if (usb_keyboard_leds&(1<<USB_LED_NUM_LOCK))
            leds |= (1<<PS2_LED_NUM_LOCK);
        if (usb_keyboard_leds&(1<<USB_LED_CAPS_LOCK))
            leds |= (1<<PS2_LED_CAPS_LOCK);

        _ps2_set_leds(leds);
        prev_leds = usb_keyboard_leds;
    }

    return 1;
}

bool matrix_is_modified(void)
{
    return _matrix_is_modified;
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
static void _matrix_make(uint8_t code)
{
    if (!matrix_is_on(_ROW(code), _COL(code))) {
        matrix[_ROW(code)] |= 1<<_COL(code);
        _matrix_is_modified = true;
    }
}

inline
static void _matrix_break(uint8_t code)
{
    if (matrix_is_on(_ROW(code), _COL(code))) {
        matrix[_ROW(code)] &= ~(1<<_COL(code));
        _matrix_is_modified = true;
    }
}

static void _ps2_reset(void)
{
    ps2_host_send(0xFF);
    ps2_host_recv(); // 0xFA
    ps2_host_recv(); // 0xAA
    _delay_ms(1000);
}

static void _ps2_set_leds(uint8_t leds)
{
        ps2_host_send(0xED);
        ps2_host_recv();        // 0xFA
        ps2_host_send(leds);
        ps2_host_recv();        // 0xFA
}
