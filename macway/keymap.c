/* 
 * Keymap for Macway mod
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "usb_keyboard.h"
#include "usb_keycodes.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "controller.h"
#include "keymap_skel.h"


#define KEYMAP( \
    R1C1, R1C0, R2C0, R3C0, R4C0, R4C1, R5C1, R5C0, R6C0, R7C0, R8C0, R8C1, R6C1, R0C2, \
    R1C2, R1C3, R2C3, R3C3, R4C3, R4C2, R5C2, R5C3, R6C3, R7C3, R8C3, R8C2, R6C2, \
    R1C5, R1C4, R2C4, R3C4, R4C4, R4C5, R5C5, R5C4, R6C4, R7C4, R8C4, R8C5, R0C6, \
    R6C7, R1C6, R2C6, R3C6, R4C6, R4C7, R5C7, R5C6, R6C6, R7C6, R8C7, R3C2, R3C5, \
    R7C5, R2C2, R0C0, R0C7, R2C1, R0C4, R3C7, R2C7, R1C7 \
) { \
    { R0C0, KB_NO, R0C2,  KB_NO, R0C4, KB_NO, R0C6,  R0C7 }, \
    { R1C0, R1C1,  R1C2,  R1C3,  R1C4, R1C5,  R1C6,  R1C7 }, \
    { R2C0, R2C1,  R2C2,  R2C3,  R2C4, KB_NO, R2C6,  R2C7 }, \
    { R3C0, KB_NO, R3C2,  R3C3,  R3C4, R3C5,  R3C6,  R3C7 }, \
    { R4C0, R4C1,  R4C2,  R4C3,  R4C4, R4C5,  R4C6,  R4C7 }, \
    { R5C0, R5C1,  R5C2,  R5C3,  R5C4, R5C5,  R5C6,  R5C7 }, \
    { R6C0, R6C1,  R6C2,  R6C3,  R6C4, KB_NO, R6C6,  R6C7 }, \
    { R7C0, KB_NO, KB_NO, R7C3,  R7C4, R7C5,  R7C6,  KB_NO }, \
    { R8C0, R8C1,  R8C2,  R8C3,  R8C4, R8C5,  KB_NO, R8C7 } \
}

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


static const uint8_t PROGMEM fn_layer[] = { 0, 1, 2, 3, 4, 0, 2, 3 };

static const uint8_t PROGMEM fn_keycode[] = {
    KB_NO,          // FN_0 [NOT USED]
    KB_NO,          // FN_1 layer 1
    KB_QUOTE,       // FN_2 layer 2
    KB_SCOLON,      // FN_3 layer 3
    KB_SPACE,       // FN_4 layer 4
    KB_NO,          // FN_5 [NOT USED]
    KB_NO,          // FN_6 layer 2
    KB_NO           // FN_7 layer 3
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |
     * |-----------------------------------------------------'     |
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|Fn2|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn1|
     * |-----------------------------------------------------------|
     * |Fn7|Gui |Alt  |Fn4                   |Fn6  |\  |`  |   |   |
     * `-----------------------------------------------------------'
     */
    KEYMAP(KB_ESC, KB_1,   KB_2,   KB_3,   KB_4,   KB_5,   KB_6,   KB_7,   KB_8,   KB_9,   KB_0,   KB_MINS,KB_EQL, KB_BSPC, \
           KB_TAB, KB_Q,   KB_W,   KB_E,   KB_R,   KB_T,   KB_Y,   KB_U,   KB_I,   KB_O,   KB_P,   KB_LBRC,KB_RBRC, \
           KB_LCTL,KB_A,   KB_S,   KB_D,   KB_F,   KB_G,   KB_H,   KB_J,   KB_K,   KB_L,   FN_3,   FN_2,   KB_ENT, \
           KB_LSFT,KB_Z,   KB_X,   KB_C,   KB_V,   KB_B,   KB_N,   KB_M,   KB_COMM,KB_DOT, KB_SLSH,KB_RSFT,FN_1, \
           FN_7,   KB_LGUI,KB_LALT,FN_4,   FN_6,   KB_BSLS,KB_GRV, KB_NO,  KB_NO),


    /* Layer 1: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Pow| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |     |
     * |-----------------------------------------------------'     |
     * |Contro|   |   |   |   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |xxx|
     * |-----------------------------------------------------------|
     * |   |Gui |Alt  |                      |Alt  |   |   |   |   |
     * `-----------------------------------------------------------'
     */ 
    KEYMAP(KB_PWR, KB_F1,  KB_F2,  KB_F3,  KB_F4,  KB_F5,  KB_F6,  KB_F7,  KB_F8,  KB_F9,  KB_F10, KB_F11, KB_F12, KB_DEL, \
           KB_CAPS,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_PSCR,KB_SLCK,KB_BRK, KB_UP,  KB_NO, \
           KB_LCTL,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KP_ASTR,KP_SLSH,KB_HOME,KB_PGUP,KB_LEFT,KB_RGHT,KB_ENT, \
           KB_LSFT,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KP_PLUS,KP_MINS,KB_END, KB_PGDN,KB_DOWN,KB_RSFT,FN_1, \
           KB_NO,  KB_LGUI,KB_LALT,KB_SPC, KB_RALT,KB_NO,  KB_NO,  KB_NO,  KB_NO),


    /* Layer 2: Vi mode (Quote/Rmeta)
     * ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   `   |
     * |-----------------------------------------------------------|
     * |  \  |Hom|PgD|Up |PgU|End|Hom|PgD|PgU|End|   |   |   |     |
     * |-----------------------------------------------------'     |
     * |Contro|   |Lef|Dow|Rig|   |Lef|Dow|Up |Rig|   |xxx|   \    |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Hom|PgD|PgU|End|   |Shift |   |
     * |-----------------------------------------------------------|
     * |   |Gui |Alt  |Space                 |xxxxx|   |   |   |   |
     * `-----------------------------------------------------------'
     */
    KEYMAP(KB_GRV, KB_F1,  KB_F2,  KB_F3,  KB_F4,  KB_F5,  KB_F6,  KB_F7,  KB_F8,  KB_F9,  KB_F10, KB_F11, KB_F12, KB_GRV, \
           KB_BSLS,KB_HOME,KB_PGDN,KB_UP,  KB_PGUP,KB_END, KB_HOME,KB_PGDN,KB_PGUP,KB_END, KB_NO,  KB_NO,  KB_NO, \
           KB_LCTL,KB_NO,  KB_LEFT,KB_DOWN,KB_RGHT,KB_NO,  KB_LEFT,KB_DOWN,KB_UP,  KB_RGHT,KB_NO,  FN_2,   KB_BSLS, \
           KB_LSFT,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_RSFT,KB_NO, \
           KB_NO,  KB_LGUI,KB_LALT,KB_SPC, FN_6,   KB_NO,  KB_NO,  KB_NO,  KB_NO),


    /* Layer 3: Mouse mode (Semicolon)
     * ,-------------------------------------------------------- --.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
     * |-----------------------------------------------------------|
     * |Tab  |MwL|MwD|McU|MwU|MwR|MwL|MwD|MwU|MwR|   |   |   |     |
     * |-----------------------------------------------------'     |
     * |Contro|   |McL|McD|McR|   |McL|McD|McU|McR|xxx|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |Mb1|Mb2|Mb3|Mb2|Mb1|   |   |   |Shift |   |
     * |-----------------------------------------------------------|
     * |xxx|Gui |Alt  |Mb1                   |Alt  |   |   |   |   |
     * `-----------------------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
     */
    KEYMAP(KB_ESC, KB_F1,  KB_F2,  KB_F3,  KB_F4,  KB_F5,  KB_F6,  KB_F7,  KB_F8,  KB_F9,  KB_F10, KB_F11, KB_F12, KB_DEL, \
           KB_TAB, MS_WH_L,MS_WH_D,MS_UP,  MS_WH_U,MS_WH_R,MS_WH_L,MS_WH_D,MS_WH_U,MS_WH_R,KB_NO,  KB_NO,  KB_NO, \
           KB_LCTL,KB_NO,  MS_LEFT,MS_DOWN,MS_RGHT,KB_NO,  MS_LEFT,MS_DOWN,MS_UP,  MS_RGHT,FN_3,   KB_NO,  KB_ENT, \
           KB_LSFT,KB_NO,  KB_NO,  MS_BTN1,MS_BTN2,MS_BTN3,MS_BTN2,MS_BTN1,KB_NO,  KB_NO,  KB_NO,  KB_RSFT,KB_NO, \
           FN_7,   KB_LGUI,KB_LALT,MS_BTN1,KB_RALT,KB_NO,  KB_NO,  KB_NO,  KB_NO),


    /* Layer 4: Matias half keyboard style (Space)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
     * |-----------------------------------------------------------|
     * |Backs|  P|  O|  I|  U|  Y|  T|  R|  E|  W|  Q|Tab|Tab|     |
     * |-----------------------------------------------------'     |
     * |Contro|  ;|  L|  K|  J|  H|  G|  F|  D|  S|  A|Con|Control |
     * |-----------------------------------------------------------|
     * |Shift   |  /|  .|  ,|  M|  N|  B|  V|  C|  X|  Z|Shift |   |
     * |-----------------------------------------------------------|
     * |   |Gui |Alt  |xxxxxxxxxxxxxxxxxxxxxx|Alt  |   |   |   |   |
     * `-----------------------------------------------------------'
     */
    KEYMAP(KB_MINS,KB_0,   KB_9,   KB_8,   KB_7,   KB_6,   KB_5,   KB_4,   KB_3,   KB_2,   KB_1,   KB_NO,  KB_NO,  KB_ESC, \
           KB_BSPC,KB_P,   KB_O,   KB_I,   KB_U,   KB_Y,   KB_T,   KB_R,   KB_E,   KB_W,   KB_Q,   KB_TAB, KB_TAB, \
           KB_LCTL,KB_SCLN,KB_L,   KB_K,   KB_J,   KB_H,   KB_G,   KB_F,   KB_D,   KB_S,   KB_A,   KB_RCTL,KB_RCTL, \
           KB_LSFT,KB_SLSH,KB_DOT, KB_COMM,KB_M,   KB_N,   KB_B,   KB_V,   KB_C,   KB_X,   KB_Z,   KB_RSFT,KB_NO, \
           KB_NO,  KB_LGUI,KB_LALT,FN_4,   KB_RALT,KB_NO,  KB_NO,  KB_NO,  KB_NO),
};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

int keymap_fn_layer(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_layer[biton(fn_bits)]);
}

uint8_t keymap_fn_keycode(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_keycode[(biton(fn_bits))]);
}

bool keymap_is_special_mode(uint8_t fn_bits)
{
    return (usb_keyboard_mods == (BIT_LCTRL | BIT_LSHIFT | BIT_LALT | BIT_LGUI));
}
