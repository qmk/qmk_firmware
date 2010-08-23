/* 
 * keymap for modified macway keyboarq
 */
#include <avr/pgmspace.h>
#include "keymap.h"

static const uint8_t PROGMEM Keymap[MATRIX_ROWS][MATRIX_COLS] = {
    { KB_LALT, KB_NO,     KB_BSPACE,   KB_NO, KB_LEFT,   KB_NO,     KB_ENTER, KB_SPACE },
    { KB_1,    KB_ESCAPE, KB_TAB,      KB_Q,  KB_A,      KB_LCTRL,  KB_Z,     KB_RIGHT },
    { KB_2,    KB_RALT,   KB_LGUI,     KB_W,  KB_S,      KB_NO,     KB_X,     KB_UP },
    { KB_3,    KB_NO,     KB_RSHIFT,   KB_E,  KB_D,      KB_BSLASH, KB_C,     KB_DOWN },
    { KB_4,    KB_5,      KB_T,        KB_R,  KB_F,      KB_G,      KB_V,     KB_B },
    { KB_7,    KB_6,      KB_Y,        KB_U,  KB_J,      KB_H,      KB_M,     KB_N },
    { KB_8,    KB_EQUAL,  KB_RBRACKET, KB_I,  KB_K,      KB_NO,     KB_COMMA, KB_LSHIFT },
    { KB_9,    KB_NO,     KB_NO,       KB_O,  KB_L,      KB_GRAVE,  KB_DOT,   KB_NO },
    { KB_0,    KB_MINUS,  KB_LBRACKET, KB_P,  KB_SCOLON, KB_QUOTE,  KB_NO,    KB_SLASH }
};


uint8_t get_keycode(uint8_t row, uint8_t col)
{
    if (row >= MATRIX_ROWS)
        return KB_NO;
    if (col >= MATRIX_COLS)
        return KB_NO;
    return pgm_read_byte(&Keymap[row][col]);
}
