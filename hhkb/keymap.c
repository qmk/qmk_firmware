/* 
 * keymap for HHKB pro
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
 * Layer1(Fn) HHKB mode
 * ,-----------------------------------------------------------.
 * |Pow| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
 * |-----------------------------------------------------------|
 * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
 * |-----------------------------------------------------------|
 * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
 * |-----------------------------------------------------------|
 * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |xxx|
 * `-----------------------------------------------------------'
 *      |Gui |Alt  |Space                  |Alt  |Gui|
 *      `--------------------------------------------'
 * 
 * Layer3(RALT) vi mode
 * ,-----------------------------------------------------------.
 * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
 * |-----------------------------------------------------------|
 * |Tab  |   |   |   |   |   |Hom|PgD|PgUlEnd|   |   |   |Backs|
 * |-----------------------------------------------------------|
 * |Contro|   |   |   |   |   |Lef|Dow|Up |Rig|   |   |Return  |
 * |-----------------------------------------------------------|
 * |Shift   |   |   |   |   |   |McL|McD|McU|McR|Mb1|Mb2   |   |
 * `-----------------------------------------------------------'
 *       |Gui|Alt  |Sapce                  |xxxxx|Mb3|
 *       `-------------------------------------------'
 *
 * Layer4(semicolon) mouse mode
 * ,-----------------------------------------------------------.
 * |Esc|   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * |-----------------------------------------------------------|
 * |Tab  |   |   |   |   |   |MwL|MwD|MwU|MwR|   |   |   |Backs|
 * |-----------------------------------------------------------|
 * |Contro|   |   |   |   |   |McL|McD|McU|McR|xxx|   |Return  |
 * |-----------------------------------------------------------|
 * |Shift   |   |   |   |   |   |   |Mb1|Mb2|Mb3|   |Shift |   |
 * `-----------------------------------------------------------'
 *      |Gui |Alt  |Mb1                    |Alt  |Gui|
 *      `--------------------------------------------'
 * 
 * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
 */

/* keycode sent when Fn key released without using layer keys. */
static const uint8_t PROGMEM FnKey[] = {
    KB_NO,          // this must be KB_NO. (not used)
    KB_NO,          // FN_1
    KB_RALT,        // FN_2
    KB_SCOLON,      // FN_3
};

static const uint8_t PROGMEM Keymap[][MATRIX_ROWS][MATRIX_COLS] = {
/*  plain keymap
    {
        { KB_2,       KB_Q,       KB_W,       KB_S,       KB_A,       KB_Z,       KB_X,       KB_C        },
        { KB_3,       KB_4,       KB_R,       KB_E,       KB_D,       KB_F,       KB_V,       KB_B        },
        { KB_5,       KB_6,       KB_Y,       KB_T,       KB_G,       KB_H,       KB_N,       KB_NO       },
        { KB_1,       KB_ESCAPE,  KB_TAB,     KB_LCTRL,   KB_LSHIFT,  KB_LGUI,    KB_LALT,    KB_SPACE    },
        { KB_7,       KB_8,       KB_U,       KB_I,       KB_K,       KB_J,       KB_M,       KB_NO       },
        { KB_BSLASH,  KB_GRAVE,   KB_BSPACE,  KB_ENTER,   FN_1,       KB_RSHIFT,  KB_RGUI,    KB_RALT     },
        { KB_9,       KB_0,       KB_O,       KB_P,       KB_SCOLON,  KB_L,       KB_COMMA,   KB_NO       },
        { KB_MINUS,   KB_EQUAL,   KB_RBRACKET,KB_LBRACKET,KB_QUOTE,   KB_SLASH,   KB_DOT,     KB_NO       },
    },
*/
    // 0: default
    {
        { KB_2,       KB_Q,       KB_W,       KB_S,       KB_A,       KB_Z,       KB_X,       KB_C        },
        { KB_3,       KB_4,       KB_R,       KB_E,       KB_D,       KB_F,       KB_V,       KB_B        },
        { KB_5,       KB_6,       KB_Y,       KB_T,       KB_G,       KB_H,       KB_N,       KB_NO       },
        { KB_1,       KB_ESCAPE,  KB_TAB,     KB_LCTRL,   KB_LSHIFT,  KB_LGUI,    KB_LALT,    KB_SPACE    },
        { KB_7,       KB_8,       KB_U,       KB_I,       KB_K,       KB_J,       KB_M,       KB_NO       },
        { KB_BSLASH,  KB_GRAVE,   KB_BSPACE,  KB_ENTER,   FN_1,       KB_RSHIFT,  KB_RGUI,    FN_2        },
        { KB_9,       KB_0,       KB_O,       KB_P,       FN_3,       KB_L,       KB_COMMA,   KB_NO       },
        { KB_MINUS,   KB_EQUAL,   KB_RBRACKET,KB_LBRACKET,KB_QUOTE,   KB_SLASH,   KB_DOT,     KB_NO       },
    },
    // 1: FN_1 HHKB mode(Fn)
    {
        { KB_F2,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO       },
        { KB_F3,      KB_F4,      KB_NO,      KB_NO,      KB_MUTE,    KB_F20,     KB_NO,      KB_NO       },
        { KB_F5,      KB_F6,      KB_NO,      KB_NO,      KB_NO,      KP_ASTERISK,KP_PLUS,    KB_NO       },
        { KB_F1,      KB_POWER,   KB_CAPSLOCK,KB_LCTRL,   KB_LSHIFT,  KB_LGUI,    KB_LALT,    KB_SPACE    },
        { KB_F7,      KB_F8,      KB_NO,      KB_PSCREEN, KB_HOME,    KP_SLASH,   KB_MINUS,   KB_NO       },
        { KB_INSERT,  KB_DELETE,  KB_BSPACE,  KP_ENTER,   KB_NO,      KB_RSHIFT,  KB_RGUI,    KB_RALT     },
        { KB_F9,      KB_F10,     KB_SCKLOCK, KB_BREAK,   KB_LEFT,    KB_PGUP,    KB_END,     KB_NO       },
        { KB_F11,     KB_F12,     KB_NO,      KB_UP,      KB_RIGHT,   KB_DOWN,    KB_PGDOWN,  KB_NO       },
    },
    // 2: FN_2 vi mode(RALT)
    {
        { KB_F2,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO       },
        { KB_F3,      KB_F4,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO       },
        { KB_F5,      KB_F6,      KB_HOME,    KB_NO,      KB_NO,      KB_LEFT,    MS_LEFT,    KB_NO       },
        { KB_F1,      KB_ESCAPE,  KB_TAB,     KB_LCTRL,   KB_LSHIFT,  KB_LGUI,    KB_LALT,    KB_SPACE    },
        { KB_F7,      KB_F8,      KB_PGDOWN,  KB_PGUP,    KB_UP,      KB_DOWN,    MS_DOWN,    KB_NO       },
        { KB_INSERT,  KB_DELETE,  KB_BSPACE,  KB_ENTER,   KB_NO,      MS_BTN2,    MS_BTN3,    KB_NO       },
        { KB_F9,      KB_F10,     KB_END,     KB_NO,      KB_NO,      KB_RIGHT,   MS_UP,      KB_NO       },
        { KB_F11,     KB_F12,     MS_WH_UP,   MS_WH_DOWN, KB_NO,      MS_BTN1,    MS_RIGHT,   KB_NO       },
    },
    // 3: FN_3 vi mouse mode(SCOLON)
    {
        { KB_F2,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO       },
        { KB_F3,      KB_F4,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO,      KB_NO       },
        { KB_F5,      KB_F6,      MS_WH_LEFT, KB_NO,      KB_NO,      MS_LEFT,    KB_NO,      KB_NO       },
        { KB_F1,      KB_ESCAPE,  KB_TAB,     KB_LCTRL,   KB_LSHIFT,  KB_LGUI,    KB_LALT,    MS_BTN1     },
        { KB_F7,      KB_F8,      MS_WH_DOWN, MS_WH_UP,   MS_UP,      MS_DOWN,    MS_BTN1,    KB_NO       },
        { KB_NO,      KB_NO,      KB_BSPACE,  KB_ENTER,   KB_NO,      KB_RSHIFT,  KB_RGUI,    KB_RALT     },
        { KB_F9,      KB_F10,     MS_WH_RIGHT,KB_NO,      KB_NO,      MS_RIGHT,   MS_BTN2,    KB_NO       },
        { KB_F11,     KB_F12,     KB_NO,      KB_NO,      KB_NO,      KB_NO,      MS_BTN3,    KB_NO       },
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
    // keep modifier state when Fn key pressed
    static uint8_t preserved_modifiers = 0;
    int layer = 0;
    uint8_t modifiers = 0;
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_ROWS; col++) {
            if (matrix[row] & 1<<col) continue; // NOT pressed
            uint8_t code = get_keycode(0, row, col);

            // NOT change current_layer when one more Fn keys pressed
            //                          when other than Fn key pressed
            if      (code == FN_1) layer = layer ? current_layer : 1;
            else if (code == FN_2) layer = layer ? current_layer : 2;
            else if (code == FN_3) layer = layer ? current_layer : 3;
            else if (code == FN_4) layer = layer ? current_layer : 4;
            else if (KB_LCTRL <= code && code <= KB_RGUI)
                modifiers |= 1<<(code & 0x07);
            else // other_key_pressed
                layer = current_layer;
        }
    }

    // TODO: this logic should go anywhere
    // TODO: need timeout for key_sent
    // send key when Fn key reloeased without used
    if (layer != current_layer) {
        if (layer == 0 && !key_sent) {
            uint8_t code = pgm_read_byte(&FnKey[current_layer]);
            if (code) {
                // send modifiers when Fn key pressed.
                keyboard_modifier_keys = preserved_modifiers;
                for (int i = 0; i < 6; i++) keyboard_keys[i] = KB_NO;

                if (KB_LCTRL <= code && code <= KB_RGUI) {
                    keyboard_modifier_keys |= 1<<(code & 0x07);
                } else  {
                    keyboard_keys[0] = code;
                }
                usb_keyboard_send();
            }
        }
        current_layer = layer;
        key_sent = false;
        preserved_modifiers = modifiers;
    }

    return current_layer;
}
