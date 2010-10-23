/* 
 * keymap for HHKB pro
 */
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "usb_keyboard.h"
#include "matrix.h"
#include "keymap.h"
#include "print.h"

#define FN_KEYCODE(fn) (pgm_read_byte(&fn_keycode[(fn)]))
#define FN_LAYER(fn)   (pgm_read_byte(&fn_layer[(fn)]))
#define KEYMAPS(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))

static int current_layer = 0;
static bool layer_used = false;
static int onbit(uint8_t bits);

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
 * Layer2(RALT) vi mode
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
 * Layer3(semicolon) mouse mode
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
 * Layer4 Matias half keyboard style
 * ,-----------------------------------------------------------.
 * |  -|  0|  9|  8|  7|  6|  5|  4|  3|  2|  1|   |   |   |Esc|
 * |-----------------------------------------------------------|
 * |Backs|  P|  O|  I|  U|  Y|  T|  R|  E|  W|  Q|   |   |Tab  |
 * |-----------------------------------------------------------|
 * |Contro|  ;|  L|  K|  J|  H|  G|  F|  D|  S|  A|Con|Control |
 * |-----------------------------------------------------------|
 * |Shift   |  /|  .|  ,|  M|  N|  B|  V|  C|  X|  Z|Shift |   |
 * `-----------------------------------------------------------'
 *      |Gui |Alt  |xxxxxxxxxxxxxxxxxxxxxxx|Alt  |Gui|
 *      `--------------------------------------------'
 * 
 * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
 */

/* keycode to sent when Fn key released without using layer keys. */
static const uint8_t PROGMEM fn_keycode[] = {
    KB_NO,          // FN_0
    KB_NO,          // FN_1
    KB_NO,          // FN_2
    KB_SCOLON,      // FN_3
    KB_SPACE,       // FN_4
    KB_NO,          // FN_5
    KB_NO,          // FN_6
    KB_NO,          // FN_7
};
/* layer to change into while Fn key pressed */ 
static const int PROGMEM fn_layer[] = { 0, 1, 2, 3, 4, 0, 0, 0 };

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
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
    // 1: HHKB mode(Fn)
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
    // 2: vi mode(RALT)
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
    // 3: vi mouse mode(SCOLON)
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
    // 4: Matias half keyboard style(SPACE) [NOT USED]
    {
        { KB_9,       KB_P,       KB_O,       KB_L,       KB_SCOLON,  KB_SLASH,   KB_DOT,     KB_COMMA    },
        { KB_8,       KB_7,       KB_U,       KB_I,       KB_K,       KB_J,       KB_M,       KB_N        },
        { KB_6,       KB_5,       KB_T,       KB_Y,       KB_H,       KB_G,       KB_B,       KB_NO       },
        { KB_0,       KB_MINUS,   KB_BSPACE,  KB_LCTRL,   KB_LSHIFT,  KB_LGUI,    KB_LALT,    KB_NO       },
        { KB_4,       KB_3,       KB_R,       KB_E,       KB_D,       KB_F,       KB_V,       KB_NO       },
        { KB_NO,      KB_ESCAPE,  KB_TAB,     KB_RCTRL,   FN_1,       KB_RSHIFT,  KB_RGUI,    KB_RALT     },
        { KB_2,       KB_1,       KB_W,       KB_Q,       KB_A,       KB_S,       KB_C,       KB_NO       },
        { KB_NO,      KB_NO,      KB_RBRACKET,KB_LBRACKET,KB_QUOTE,   KB_Z,       KB_X,       KB_NO       },
    },
};


uint8_t keymap_get_keycode(int row, int col)
{
    return keymap_get_keycodel(current_layer, row, col);
}

uint8_t keymap_get_keycodel(int layer, int row, int col)
{
    uint8_t code = KEYMAPS(layer, row, col);
    // normal key or mouse key
    if ((KB_A <= code && code <= KP_HEXADECIMAL) ||
        (MS_UP <= code && code <= MS_WH_RIGHT))
        layer_used = true;
    return code;
}

inline
int keymap_get_layer(void) {
    return current_layer;
}

inline
int keymap_set_layer(int layer) {
    current_layer = layer;
    return current_layer;
}

void keymap_fn_proc(int fn_bits) {
    // layer switching
    static int last_bits = 0;
    static uint8_t last_mod = 0;

    if (usb_keyboard_has_key() || fn_bits == last_bits) {
        // do nothing during press other than Fn key 
        return;
    } else if (fn_bits == 0) {
        // send key when Fn key is released without using the layer
        if (!layer_used) {
            uint8_t code = FN_KEYCODE(onbit(last_bits));
            if (code != KB_NO) {
                if (KB_LCTRL <= code  && code <= KB_RGUI) {
                    keyboard_modifier_keys = last_mod | 1<<(code & 0x07);
                } else {
                    keyboard_keys[0] = code;
                    keyboard_modifier_keys = last_mod;
                }
                usb_keyboard_send();
                usb_keyboard_print();
                usb_keyboard_clear();
            }
        }
        last_bits = 0;
        last_mod = 0;
        layer_used = false;
        keymap_set_layer(0); // default layer
        print("layer default: "); phex(current_layer); print("\n");
    } else if ((fn_bits & (fn_bits - 1)) == 0) {
        // switch layer when just one Fn Key is pressed
        last_bits = fn_bits;
        last_mod = keyboard_modifier_keys;
        layer_used = false;
        keymap_set_layer(FN_LAYER(onbit(fn_bits)));
        print("layer: "); phex(current_layer); print("\n");
        print("last_bits: "); phex(last_bits); print("\n");
        print("last_mod: "); phex(last_mod); print("\n");
    }
}

static int onbit(uint8_t bits) {
    int n = 0;
    if (bits >> 4) { bits >>= 4; n += 4;}
    if (bits >> 2) { bits >>= 2; n += 2;}
    if (bits >> 1) { bits >>= 1; n += 1;}
    return n;
}
