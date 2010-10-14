/* 
 * keymap for modified Macway
 */
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "matrix.h"
#include "keymap.h"
#include "usb_keyboard.h"

int current_layer = 0;
bool key_sent = false;

/*
 * Layer0(Default Layer)
 * ,----------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp|
 * |----------------------------------------------------------|
 * |Tab |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |
 * |----------------------------------------------------'     |
 * |Contr|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
 * |----------------------------------------------------------|
 * |Shift  |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn2|
 * |----------------------------------------------------------|
 * |Fn3|Gui |Alt  |Space                |Fn1  |Lef|Dow|Up |Rig|
 * `----------------------------------------------------------'
 * 
 * Layer1(with Fn1)
 * ,----------------------------------------------------------.
 * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete|
 * |----------------------------------------------------------|
 * |  \ |   |   |   |   |   |   |   |   |   |   |   |   |     |
 * |----------------------------------------------------'     |
 * |Contr|   |   |   |   |   |Lef|Dow|Up |Rig|   |   |  \     |
 * |----------------------------------------------------------|
 * |Shift  |   |   |   |   |   |Hom|PgD|PgU|End|   |Shift |   |
 * |----------------------------------------------------------|
 * |   |Gui |Alt  |                     |Fn1  |Lef|Dow|Up |Rig|
 * `----------------------------------------------------------'
 * 
 * Layer2(with Fn2)
 * ,----------------------------------------------------------.
 * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete|
 * |----------------------------------------------------------|
 * |  \ |   |   |   |   |   |   |   |   |   |   |Up |   |     |
 * |----------------------------------------------------'     |
 * |Contr|VoD|VoU|Mut|F20|   |  *|  /|Hom|PgU|Lef|Rig|  \     |
 * |----------------------------------------------------------|
 * |Shift  |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |Fn2|
 * |----------------------------------------------------------|
 * |   |Gui |Alt  |                     |     |Lef|Dow|Up |Rig|
 * `----------------------------------------------------------'
 * 
 * Layer3(with Fn3)
 * ,----------------------------------------------------------.
 * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete|
 * |----------------------------------------------------------|
 * |  \ |   |   |   |   |   |   |   |   |   |   |   |   |     |
 * |----------------------------------------------------'     |
 * |Contr|Mb1|Mb2|Mb3|   |   |McL|McD|McU|McR|   |   |  \     |
 * |----------------------------------------------------------|
 * |Shift  |   |   |   |   |   |MwL|MwD|MwU|MwR|   |Shift |   |
 * |----------------------------------------------------------|
 * |   |Gui |Alt  |Mb1                  |Mb2  |MsL|MsD|MsU|MsR|
 * `----------------------------------------------------------'
 * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
 */
static const uint8_t PROGMEM Keymap[][MATRIX_ROWS][MATRIX_COLS] = {
    // 0: default
    {
        { KB_LALT, KB_NO,     KB_BSPACE,  KB_NO, KB_LEFT,   KB_NO,      KB_ENTER, KB_SPACE },
        { KB_1,    KB_ESCAPE, KB_TAB,     KB_Q,  KB_A,      KB_LCTRL,   KB_Z,     KB_RIGHT },
        { KB_2,    FN_1,      KB_LGUI,    KB_W,  KB_S,      KB_NO,      KB_X,     KB_UP },
        { KB_3,    KB_NO,     KB_RSHIFT,  KB_E,  KB_D,      FN_2,       KB_C,     KB_DOWN },
        { KB_4,    KB_5,      KB_T,       KB_R,  KB_F,      KB_G,       KB_V,     KB_B },
        { KB_7,    KB_6,      KB_Y,       KB_U,  KB_J,      KB_H,       KB_M,     KB_N },
        { KB_8,    KB_EQUAL,  KB_RBRACKET,KB_I,  KB_K,      KB_NO,      KB_COMMA, KB_LSHIFT },
        { KB_9,    KB_NO,     KB_NO,      KB_O,  KB_L,      FN_3,       KB_DOT,   KB_NO },
        { KB_0,    KB_MINUS,  KB_LBRACKET,KB_P,  KB_SCOLON, KB_QUOTE,   KB_NO,    KB_SLASH }
    },
    // 1: FN_1(RIGHT ALT)
    {
        { KB_LALT, KB_NO,     KB_DELETE,  KB_NO, KB_NO,     KB_NO,      KB_BSLASH,KB_NO },
        { KB_F1,   KB_GRAVE,  KB_BSLASH,  KB_NO, KB_NO,     KB_LCTRL,   KB_NO,    KB_NO },
        { KB_F2,   KB_NO,     KB_LGUI,    KB_NO, KB_NO,     KB_NO,      KB_NO,    KB_NO },
        { KB_F3,   KB_NO,     KB_RSHIFT,  KB_NO, KB_NO,     KB_NO,      KB_NO,    KB_NO },
        { KB_F4,   KB_F5,     KB_NO,      KB_NO, KB_NO,     KB_NO,      KB_NO,    KB_NO },
        { KB_F7,   KB_F6,     KB_NO,      KB_NO, KB_DOWN,   KB_LEFT,    KB_PGDOWN,KB_HOME },
        { KB_F8,   KB_F12,    KB_NO,      KB_NO, KB_UP,     KB_NO,      KB_PGUP,  KB_LSHIFT },
        { KB_F9,   KB_NO,     KB_NO,      KB_NO, KB_RIGHT,  KB_NO,      KB_END,   KB_NO },
        { KB_F10,  KB_F11,    KB_NO,      KB_NO, KB_NO,     KB_NO,      KB_NO,    KB_NO }
    },
    // 2: FN_2(HHKB Fn)
    {
        { KB_LALT, KB_NO,     KB_DELETE,  KB_NO, KB_NO,     KB_NO,      KB_BSLASH,KB_NO },
        { KB_F1,   KB_GRAVE,  KB_BSLASH,  KB_NO, KB_VOLDOWN,KB_LCTRL,   KB_NO,    KB_NO },
        { KB_F2,   KB_NO,     KB_LGUI,    KB_NO, KB_VOLUP,  KB_NO,      KB_NO,    KB_NO },
        { KB_F3,   KB_NO,     KB_RSHIFT,  KB_NO, KB_MUTE,   KB_NO,      KB_NO,    KB_NO },
        { KB_F4,   KB_F5,     KB_NO,      KB_NO, KB_F20,    KB_NO,      KB_NO,    KB_NO },
        { KB_F7,   KB_F6,     KB_NO,      KB_NO, KP_SLASH,  KP_ASTERISK,KP_MINUS, KP_PLUS },
        { KB_F8,   KB_F12,    KB_NO,      KB_NO, KB_HOME,   KB_NO,      KB_END,   KB_LSHIFT },
        { KB_F9,   KB_NO,     KB_NO,      KB_NO, KB_PGUP,   KB_NO,      KB_PGDOWN,KB_NO },
        { KB_F10,  KB_F11,    KB_UP,      KB_NO, KB_LEFT,   KB_RIGHT,   KB_NO,    KB_DOWN }
    },
    // 3: FN_3(LEFT Bottom)
    {
        { KB_LALT, KB_NO,     KB_DELETE,  KB_NO, MS_LEFT,   KB_NO,      KB_BSLASH,  MS_BTN1 },
        { KB_F1,   KB_GRAVE,  KB_BSLASH,  KB_NO, MS_BTN1,   KB_LCTRL,   KB_NO,      MS_RIGHT },
        { KB_F2,   MS_BTN2,   KB_LGUI,    KB_NO, MS_BTN2,   KB_NO,      KB_NO,      MS_UP },
        { KB_F3,   KB_NO,     KB_RSHIFT,  KB_NO, MS_BTN3,   KB_NO,      KB_NO,      MS_DOWN },
        { KB_F4,   KB_F5,     KB_NO,      KB_NO, KB_NO,     KB_NO,      KB_NO,      KB_NO },
        { KB_F7,   KB_F6,     KB_NO,      KB_NO, MS_DOWN,   MS_LEFT,    MS_WH_UP,   MS_WH_LEFT },
        { KB_F8,   KB_F12,    MS_BTN5,    KB_NO, MS_UP,     KB_NO,      MS_WH_DOWN, KB_LSHIFT },
        { KB_F9,   KB_NO,     KB_NO,      KB_NO, MS_RIGHT,  KB_NO,      MS_WH_RIGHT,KB_NO },
        { KB_F10,  KB_F11,    MS_BTN4,    KB_NO, KB_NO,     KB_NO,      KB_NO,      KB_NO }
    },
};


uint8_t get_keycode(int layer, int row, int col)
{
    if (row >= MATRIX_ROWS)
        return KB_NO;
    if (col >= MATRIX_COLS)
        return KB_NO;
    return pgm_read_byte(&Keymap[layer][row][col]);
}

int get_layer(void) {
    int layer = 0;
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_ROWS; col++) {
            if (matrix[row] & 1<<col) continue;
            if (get_keycode(0, row, col) == FN_1) layer = 1;
            if (get_keycode(0, row, col) == FN_2) layer = 2;
            if (get_keycode(0, row, col) == FN_3) layer = 3;
        }
    }
    current_layer = layer;
    return current_layer;
}
