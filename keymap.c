/* 
 * keymap for modified macway keyboard
 */
#include <avr/pgmspace.h>
#include "keymap.h"

#define MATRIX_ROWS 9
#define MATRIX_COLS 8

static const uint8_t PROGMEM Keymap[MATRIX_COLS][MATRIX_ROWS] = {
    { KB_LALT,   KB_1,      KB_2,     KB_3,      KB_4,   KB_7,   KB_8,        KB_9,     KB_0 },
    { KB_NO,     KB_ESCAPE, KB_RALT,  KB_NO,     KB_5,   KB_6,   KB_EQUAL,    KB_NO,    KB_MINUS },
    { KB_BSPACE, KB_TAB,    KB_LGUI,  KB_RSHIFT, KB_T,   KB_Y,   KB_RBRACKET, KB_NO,    KB_LBRACKET },
    { KB_NO,     KB_Q,      KB_W,     KB_E,      KB_R,   KB_U,   KB_I,        KB_O,     KB_P },
    { KB_BSLASH, KB_A,      KB_S,     KB_D,      KB_F,   KB_J,   KB_K,        KB_L,     KB_SCOLON },
    { KB_NO,     KB_LCTRL,  KB_NO,    KB_UP,     KB_G,   KB_H,   KB_NO,       KB_GRAVE, KB_QUOTE },
    { KB_ENTER,  KB_Z,      KB_X,     KB_C,      KB_V,   KB_M,   KB_COMMA,    KB_DOWN,  KB_NO },
    { KB_SPACE,  KB_DOWN,   KB_RIGHT, KB_LEFT,   KB_B,   KB_N,   KB_LSHIFT,   KB_NO,    KB_SLASH }
};

uint8_t get_keycode(uint8_t row, uint8_t col)
{
    if (row >= MATRIX_ROWS)
        return KB_NO;
    if (col >= MATRIX_COLS)
        return KB_NO;
    return pgm_read_byte(&Keymap[col][row]);
}
