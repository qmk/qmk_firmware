/* 
 * Keymap for PFU HHKB Pro
 */
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "usb_keyboard.h"
#include "usb_keycodes.h"
#include "matrix.h"
#include "keymap.h"
#include "print.h"
#include "debug.h"


#define FN_KEYCODE(fn) (pgm_read_byte(&fn_keycode[(fn)]))
#define FN_LAYER(fn)   (pgm_read_byte(&fn_layer[(fn)]))
#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))
#define KEYMAP( \
    R3C1, R3C0, R0C0, R1C0, R1C1, R2C0, R2C1, R4C0, R4C1, R6C0, R6C1, R7C0, R7C1, R5C0, R5C1, \
    R3C2, R0C1, R0C2, R1C3, R1C2, R2C3, R2C2, R4C2, R4C3, R6C2, R6C3, R7C3, R7C2, R5C2, \
    R3C3, R0C4, R0C3, R1C4, R1C5, R2C4, R2C5, R4C5, R4C4, R6C5, R6C4, R7C4, R5C3, \
    R3C4, R0C5, R0C6, R0C7, R1C6, R1C7, R2C6, R4C6, R6C6, R7C6, R7C5, R5C5, R5C4, \
    R3C5, R3C6, R3C7, R5C7, R5C6 \
) \
{ \
    { R0C0, R0C1, R0C2, R0C3, R0C4, R0C5, R0C6, R0C7 }, \
    { R1C0, R1C1, R1C2, R1C3, R1C4, R1C5, R1C6, R1C7 }, \
    { R2C0, R2C1, R2C2, R2C3, R2C4, R2C5, R2C6, KB_NO }, \
    { R3C0, R3C1, R3C2, R3C3, R3C4, R3C5, R3C6, R3C7 }, \
    { R4C0, R4C1, R4C2, R4C3, R4C4, R4C5, R4C6, KB_NO }, \
    { R5C0, R5C1, R5C2, R5C3, R5C4, R5C5, R5C6, R5C7 }, \
    { R6C0, R6C1, R6C2, R6C3, R6C4, R6C5, R6C6, KB_NO }, \
    { R7C0, R7C1, R7C2, R7C3, R7C4, R7C5, R7C6, KB_NO } \
}


static int onbit(uint8_t bits);


static int current_layer = 0;
static bool layer_used = false;


/* layer to change into while Fn key pressed */ 
static const int PROGMEM fn_layer[] = { 0, 1, 2, 3, 4, 0, 0, 0 };

/* keycode to sent when Fn key released without using layer keys. */
static const uint8_t PROGMEM fn_keycode[] = {
    KB_NO,          // FN_0 [NOT USED]
    KB_NO,          // FN_1 layer 1
    KB_QUOTE,       // FN_2 layer 2
    KB_SCOLON,      // FN_3 layer 3
    KB_SPACE,       // FN_4 layer 4 [NOT USED]
    KB_NO,          // FN_5 [NOT USED]
    KB_NO,          // FN_6 [NOT USED]
    KB_NO           // FN_7 [NOT USED]
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|Fn2|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn1|
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |Space                  |Alt  |Gui|
     *       `-------------------------------------------'
     */
    KEYMAP(KB_ESC, KB_1,   KB_2,   KB_3,   KB_4,   KB_5,   KB_6,   KB_7,   KB_8,   KB_9,   KB_0,   KB_MINS,KB_EQL, KB_BSLS,KB_GRV, \
           KB_TAB, KB_Q,   KB_W,   KB_E,   KB_R,   KB_T,   KB_Y,   KB_U,   KB_I,   KB_O,   KB_P,   KB_LBRC,KB_RBRC,KB_BSPC, \
           KB_LCTL,KB_A,   KB_S,   KB_D,   KB_F,   KB_G,   KB_H,   KB_J,   KB_K,   KB_L,   FN_3,   FN_2,   KB_ENT, \
           KB_LSFT,KB_Z,   KB_X,   KB_C,   KB_V,   KB_B,   KB_N,   KB_M,   KB_COMM,KB_DOT, KB_SLSH,KB_RSFT,FN_1, \
           KB_LGUI,KB_LALT,KB_SPC, KB_RALT,KB_RGUI),

    /* Layer 1: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Pow| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|   |   |   |   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |xxx|
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |Space                  |Alt  |Gui|
     *      `--------------------------------------------'
     */ 
    KEYMAP(KB_PWR, KB_F1,  KB_F2,  KB_F3,  KB_F4,  KB_F5,  KB_F6,  KB_F7,  KB_F8,  KB_F9,  KB_F10, KB_F11, KB_F12, KB_INS, KB_DEL, \
           KB_CAPS,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_PSCR,KB_SLCK,KB_BRK, KB_UP,  KB_NO,  KB_BSPC, \
           KB_LCTL,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KP_ASTR,KP_SLSH,KB_HOME,KB_PGUP,KB_LEFT,KB_RGHT,KB_ENT, \
           KB_LSFT,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KP_PLUS,KP_MINS,KB_END, KB_PGDN,KB_DOWN,KB_RSFT,FN_1, \
           KB_LGUI,KB_LALT,KB_SPC, KB_RALT,KB_RGUI),

    /* Layer 2: Vi mode (Quote/Rmeta)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |Hom|PgD|Up |PgU|End|Hom|PgD|PgUlEnd|   |   |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|   |Lef|Dow|Rig|   |Lef|Dow|Up |Rig|   |xxx|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |   |   |   |   |   |Shift |   |
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |Sapce                  |Alt  |Gui|
     *       `-------------------------------------------'
     */
    KEYMAP(KB_ESC, KB_F1,  KB_F2,  KB_F3,  KB_F4,  KB_F5,  KB_F6,  KB_F7,  KB_F8,  KB_F9,  KB_F10, KB_F11, KB_F12, KB_INS, KB_DEL, \
           KB_TAB, KB_HOME,KB_PGDN,KB_UP,  KB_PGUP,KB_END, KB_HOME,KB_PGDN,KB_PGUP,KB_END, KB_NO,  KB_NO,  KB_NO,  KB_BSPC, \
           KB_LCTL,KB_NO,  KB_LEFT,KB_DOWN,KB_RGHT,KB_NO,  KB_LEFT,KB_DOWN,KB_UP,  KB_RGHT,KB_NO,  FN_2,   KB_ENT, \
           KB_LSFT,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_RSFT,KB_NO, \
           KB_LGUI,KB_LALT,KB_SPC, KB_RALT,KB_RGUI),

    /* Layer 3: Mouse mode (Semicolon)
     * ,-----------------------------------------------------------.
     * |Esc|   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * |-----------------------------------------------------------|
     * |Tab  |MwL|MwU|McU|MwD|MwL|MwR|MwD|MwU|MwR|   |   |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|   |McL|McD|McR|   |McL|McD|McU|McR|xxx|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Mb2|Mb1|Mb2|Mb3|   |Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |Mb1                    |Alt  |Gui|
     *      `--------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
     */
    KEYMAP(KB_ESC, KB_F1,  KB_F2,  KB_F3,  KB_F4,  KB_F5,  KB_F6,  KB_F7,  KB_F8,  KB_F9,  KB_F10, KB_F11, KB_F12, KB_INS, KB_DEL, \
           KB_TAB, MS_WH_L,MS_WH_U,MS_UP,  MS_WH_D,MS_WH_R,MS_WH_L,MS_WH_D,MS_WH_U,MS_WH_R,KB_NO,  KB_NO,  KB_NO,  KB_BSPC, \
           KB_LCTL,KB_NO,  MS_LEFT,MS_DOWN,MS_RGHT,KB_NO,  MS_LEFT,MS_DOWN,MS_UP,  MS_RGHT,FN_3,   KB_NO,  KB_ENT, \
           KB_LSFT,KB_NO,  MS_DOWN,KB_NO,  KB_NO,  KB_NO,  MS_BTN2,MS_BTN1,MS_BTN2,MS_BTN3,KB_NO,  KB_RSFT,KB_NO, \
           KB_LGUI,KB_LALT,MS_BTN1,KB_RALT,KB_RGUI),

    /* Layer 4: Matias half keyboard style (Space)
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
     */
    KEYMAP(KB_MINS,KB_0,   KB_9,   KB_8,   KB_7,   KB_6,   KB_5,   KB_4,   KB_3,   KB_2,   KB_1,   KB_NO,  KB_NO,  KB_NO,  KB_ESC, \
           KB_BSPC,KB_P,   KB_O,   KB_I,   KB_U,   KB_Y,   KB_T,   KB_R,   KB_E,   KB_W,   KB_Q,   KB_NO,  KB_NO,  KB_TAB, \
           KB_LCTL,KB_SCLN,KB_L,   KB_K,   KB_J,   KB_H,   KB_G,   KB_F,   KB_D,   KB_S,   KB_A,   KB_RCTL,KB_RCTL, \
           KB_LSFT,KB_SLSH,KB_DOT, KB_COMM,KB_M,   KB_N,   KB_B,   KB_V,   KB_C,   KB_X,   KB_Z,   KB_RSFT,KB_NO, \
           KB_LGUI,KB_LALT,FN_4,   KB_RALT,KB_RGUI)
};


uint8_t keymap_get_keycode(int row, int col)
{
    return keymap_get_keycodel(current_layer, row, col);
}

uint8_t keymap_get_keycodel(int layer, int row, int col)
{
    uint8_t code = KEYCODE(layer, row, col);
    // normal key or mouse key
    if (IS_KEY(code) || IS_MOUSE(code))
        layer_used = true;
    return code;
}

inline
int keymap_get_layer(void)
{
    return current_layer;
}

inline
int keymap_set_layer(int layer)
{
    current_layer = layer;
    return current_layer;
}

inline
bool keymap_is_special_mode(int fn_bits)
{
    return (keyboard_modifier_keys == (BIT_LCTRL | BIT_LSHIFT | BIT_LALT | BIT_LGUI));
}

void keymap_fn_proc(int fn_bits)
{
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
                if (IS_MOD(code)) {
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
    } else if ((fn_bits & (fn_bits - 1)) == 0) {
        // switch layer when just one Fn Key is pressed
        last_bits = fn_bits;
        last_mod = keyboard_modifier_keys;
        layer_used = false;
        keymap_set_layer(FN_LAYER(onbit(fn_bits)));
        debug("layer: "); phex(current_layer); debug("(");
        debug_bin(last_bits); debug(")\n");
        debug("last_mod: "); debug_hex(last_mod); debug("\n");
    }
}

static int onbit(uint8_t bits)
{
    int n = 0;
    if (bits >> 4) { bits >>= 4; n += 4;}
    if (bits >> 2) { bits >>= 2; n += 2;}
    if (bits >> 1) { bits >>= 1; n += 1;}
    return n;
}
