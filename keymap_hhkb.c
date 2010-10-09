/* 
 * keymap for modified macway keyboarq
 */
#include <avr/pgmspace.h>
#include "matrix.h"
#include "keymap_hhkb.h"

int current_layer = 0;

/*
 * Layer0(Default Layer)
 * ,-----------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
 * |-----------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
 * |-----------------------------------------------------------|
 * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
 * |-----------------------------------------------------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Fn2   |Fn1|
 * `-----------------------------------------------------------'
 *       |Gui|Alt  |Space                  |Fn3  |Gui|
 *       `-------------------------------------------'
 * 
 * Layer1(Fn1) HHKB mode
 * ,-----------------------------------------------------------.
 * |Pow| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
 * |-----------------------------------------------------------|
 * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
 * |-----------------------------------------------------------|
 * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
 * |-----------------------------------------------------------|
 * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |   |
 * `-----------------------------------------------------------'
 *      |Gui |Alt  |Space                  |Alt  |Gui|
 *      `--------------------------------------------'
 * 
 * Layer2(Fn2) HHKB mouse mode
 * ,-----------------------------------------------------------.
 * |Esc|   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * |-----------------------------------------------------------|
 * |Tab  |   |   |   |   |   |   |   |   |   |   |McU|   |Backs|
 * |-----------------------------------------------------------|
 * |Contro|   |   |   |   |   |   |   |MwL|MwU|McL|McR|Return  |
 * |-----------------------------------------------------------|
 * |Shift   |   |   |   |   |   |   |   |MwR|MwD|McD|      |   |
 * `-----------------------------------------------------------'
 *      |Gui |Alt  |Space                  |Mb1  |Mb2|
 *      `--------------------------------------------'
 * 
 * Layer3(Fn3) vi mode
 * ,-----------------------------------------------------------.
 * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |   |
 * |-----------------------------------------------------------|
 * |Tab  |   |   |   |   |   |Hom|PgD|PgUlEnd|   |MwD|MwU|     |
 * |-----------------------------------------------------------|
 * |Contro|   |   |   |   |   |Lef|Dow|Up |Rig|   |   |Return  |
 * |-----------------------------------------------------------|
 * |Shift   |   |   |   |   |Mb2|McL|McD|McU|McR|Mb1|Mb1   |   |
 * `-----------------------------------------------------------'
 *       |Gui|Alt  |Space                  |     |Mb2|
 *       `-------------------------------------------'
 * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
 */
static const uint8_t PROGMEM Keymap[][MATRIX_ROWS][MATRIX_COLS] = {
    // 0: default
    {
        { KB_2,       KB_Q,       KB_W,       KB_S,       KB_A,       KB_Z,       KB_X,       KB_C        },
        { KB_3,       KB_4,       KB_R,       KB_E,       KB_D,       KB_F,       KB_V,       KB_B        },
        { KB_5,       KB_6,       KB_Y,       KB_T,       KB_G,       KB_H,       KB_N,       KB_NO       },
        { KB_1,       KB_ESCAPE,  KB_TAB,     KB_LCTRL,   KB_LSHIFT,  KB_LGUI,    KB_LALT,    KB_SPACE    },
        { KB_7,       KB_8,       KB_U,       KB_I,       KB_K,       KB_J,       KB_M,       KB_NO       },
        { KB_BSLASH,  KB_GRAVE,   KB_BSPACE,  KB_ENTER,   FN_1,       FN_2,       KB_RGUI,    FN_3        },
        { KB_9,       KB_0,       KB_O,       KB_P,       KB_SCOLON,  KB_L,       KB_COMMA,   KB_NO       },
        { KB_MINUS,   KB_EQUAL,   KB_RBRACKET,KB_LBRACKET,KB_QUOTE,   KB_SLASH,   KB_DOT,     KB_NO       },
    },
    // 1: FN_1(HHKB Fn) HHKB mode
    {
        { KB_F2,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      },
        { KB_F3,      KB_F4,      KB_NO,      KB_NO,      KB_MUTE,    KB_F20,     KB_NO,      KB_NO,      },
        { KB_F5,      KB_F6,      KB_NO,      KB_NO,      KB_NO,      KP_ASTERISK,KP_PLUS,    KB_NO       },
        { KB_F1,      KB_POWER,   KB_CAPSLOCK,KB_LCTRL,   KB_LSHIFT,  KB_LGUI,    KB_LALT,    KB_SPACE    },
        { KB_F7,      KB_F8,      KB_NO,      KB_PSCREEN, KB_HOME,    KP_SLASH,   KB_MINUS,   KB_NO       },
        { KB_INSERT,  KB_DELETE,  KB_BSPACE,  KP_ENTER,   KB_NO,      KB_RSHIFT,  KB_RGUI,    KB_RALT     },
        { KB_F9,      KB_F10,     KB_SCKLOCK, KB_BREAK,   KB_LEFT,    KB_PGUP,    KB_END,     KB_NO       },
        { KB_F11,     KB_F12,     KB_NO,      KB_UP,      KB_RIGHT,   KB_DOWN,    KB_PGDOWN,  KB_NO       },
    },
    // 2: FN_2(Right Shift) HHKB mouse mode
    {
        { KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      },
        { KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_MUTE,    KB_NO,      KB_NO,      KB_NO,      },
        { KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO       },
        { KB_NO,      KB_ESCAPE,  KB_TAB,     KB_LCTRL,   KB_LSHIFT,  KB_LGUI,    KB_LALT,    KB_SPACE    },
        { KB_NO,      KB_NO,      KB_NO,      KB_NO,      MS_WH_LEFT, KP_SLASH,   KB_MINUS,   KB_NO       },
        { KB_NO,      KB_NO,      KB_BSPACE,  KB_ENTER,   KB_NO,      KB_NO,      MS_BTN2,    MS_BTN1     },
        { KB_NO,      KB_NO,      KB_NO,      KB_NO,      MS_LEFT,    MS_WH_DOWN, MS_WH_RIGHT,KB_NO       },
        { KB_NO,      KB_NO,      KB_NO,      MS_UP,      MS_RIGHT,   MS_DOWN,    MS_WH_UP,   KB_NO       },
    },
    // 3: FN_3(Right Alt) vi mode
    {
        { KB_F2,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      },
        { KB_F3,      KB_F4,      KB_NO,      KB_NO,      KB_NO,      KB_F20,     KB_NO,      KB_NO,      },
        { KB_F5,      KB_F6,      KB_HOME,    KB_NO,      KB_NO,      KB_LEFT,    MS_LEFT,    KB_NO       },
        { KB_F1,      KB_ESCAPE,  KB_TAB,     KB_LCTRL,   KB_LSHIFT,  KB_LGUI,    KB_LALT,    KB_SPACE    },
        { KB_F7,      KB_F8,      KB_PGDOWN,  KB_PGUP,    KB_UP,      KB_DOWN,    MS_DOWN,    KB_NO       },
        { KB_INSERT,  KB_NO,      KB_BSPACE,  KB_ENTER,   KB_NO,      MS_BTN1,    MS_BTN2,    KB_NO       },
        { KB_F9,      KB_F10,     KB_END,     KB_NO,      KB_NO,      KB_RIGHT,   MS_UP,      KB_NO       },
        { KB_F11,     KB_F12,     MS_WH_DOWN, MS_WH_UP,   KB_NO,      MS_BTN1,    MS_RIGHT,   KB_NO       },
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
            if (get_keycode(0, row, col) == FN_1) layer = ((layer == 0 || layer > 1) ? 1 : layer);
            if (get_keycode(0, row, col) == FN_2) layer = ((layer == 0 || layer > 2) ? 2 : layer);
            if (get_keycode(0, row, col) == FN_3) layer = ((layer == 0 || layer > 3) ? 3 : layer);
        }
    }
    current_layer = layer;
    return current_layer;
}
