/* 
 * Keymap for PFU HHKB Pro
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "usb_keyboard.h"
#include "usb_keycodes.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap_skel.h"


// Convert physical keyboard layout to matrix array.
// This is a macro to define keymap easily in keyboard layout form.
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

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // Fn0
    1,              // Fn1
    2,              // Fn2
    3,              // Fn3
    4,              // Fn4
    0,              // Fn5
    0,              // Fn6
    1               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KB_NO,          // Fn0
    KB_NO,          // Fn1
    KB_SLSH,        // Fn2
    KB_SCLN,        // Fn3
    KB_SPC,         // Fn4
    KB_NO,          // Fn5
    KB_NO,          // Fn6
    KB_NO           // Fn7
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift |Fn1|
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |Fn4                    |Alt  |Fn7|
     *       `-------------------------------------------'
     */
    KEYMAP(KB_ESC, KB_1,   KB_2,   KB_3,   KB_4,   KB_5,   KB_6,   KB_7,   KB_8,   KB_9,   KB_0,   KB_MINS,KB_EQL, KB_BSLS,KB_GRV, \
           KB_TAB, KB_Q,   KB_W,   KB_E,   KB_R,   KB_T,   KB_Y,   KB_U,   KB_I,   KB_O,   KB_P,   KB_LBRC,KB_RBRC,KB_BSPC, \
           KB_LCTL,KB_A,   KB_S,   KB_D,   KB_F,   KB_G,   KB_H,   KB_J,   KB_K,   KB_L,   KB_FN3, KB_QUOT,KB_ENT, \
           KB_LSFT,KB_Z,   KB_X,   KB_C,   KB_V,   KB_B,   KB_N,   KB_M,   KB_COMM,KB_DOT, KB_FN2, KB_RSFT,KB_FN1, \
           KB_LGUI,KB_LALT,KB_FN4, KB_RALT,KB_RGUI),

    /* Layer 1: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |xxx|
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |Space                  |Alt  |xxx|
     *      `--------------------------------------------'
     */ 
    KEYMAP(KB_ESC, KB_F1,  KB_F2,  KB_F3,  KB_F4,  KB_F5,  KB_F6,  KB_F7,  KB_F8,  KB_F9,  KB_F10, KB_F11, KB_F12, KB_INS, KB_DEL, \
           KB_CAPS,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_PSCR,KB_SLCK,KB_BRK, KB_UP,  KB_NO,  KB_BSPC, \
           KB_LCTL,KB_VOLD,KB_VOLU,KB_MUTE,KB_NO,  KB_NO,  KB_PAST,KB_PSLS,KB_HOME,KB_PGUP,KB_LEFT,KB_RGHT,KB_ENT, \
           KB_LSFT,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_PPLS,KB_PMNS,KB_END, KB_PGDN,KB_DOWN,KB_RSFT,KB_FN1, \
           KB_LGUI,KB_LALT,KB_SPC, KB_RALT,KB_FN7),

    /* Layer 2: Vi mode (Slash)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |Hom|PgD|Up |PgU|End|Hom|PgD|PgUlEnd|   |   |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|   |Lef|Dow|Rig|   |Lef|Dow|Up |Rig|   |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Hom|PgD|PgUlEnd|xxx|Shift |   |
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |Space                  |Alt  |Gui|
     *       `-------------------------------------------'
     */
    KEYMAP(KB_ESC, KB_F1,  KB_F2,  KB_F3,  KB_F4,  KB_F5,  KB_F6,  KB_F7,  KB_F8,  KB_F9,  KB_F10, KB_F11, KB_F12, KB_INS, KB_DEL, \
           KB_TAB, KB_HOME,KB_PGDN,KB_UP,  KB_PGUP,KB_END, KB_HOME,KB_PGDN,KB_PGUP,KB_END, KB_NO,  KB_NO,  KB_NO,  KB_BSPC, \
           KB_LCTL,KB_NO,  KB_LEFT,KB_DOWN,KB_RGHT,KB_NO,  KB_LEFT,KB_DOWN,KB_UP,  KB_RGHT,KB_NO,  KB_NO,  KB_ENT, \
           KB_LSFT,KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_NO,  KB_HOME,KB_PGDN,KB_PGUP,KB_END, KB_FN2, KB_RSFT,KB_NO, \
           KB_LGUI,KB_LALT,KB_SPC, KB_RALT,KB_RGUI),

    /* Layer 3: Mouse mode (Semicolon)
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Tab  |MwL|MwU|McU|MwD|MwR|MwL|MwD|MwU|MwR|   |   |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|   |McL|McD|McR|   |McL|McD|McU|McR|xxx|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |Mb4|Mb5|Mb1|Mb2|Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
     * `-----------------------------------------------------------'
     *      |Gui |Alt  |Mb1                    |Alt  |Gui|
     *      `--------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
     */
    KEYMAP(KB_ESC, KB_F1,  KB_F2,  KB_F3,  KB_F4,  KB_F5,  KB_F6,  KB_F7,  KB_F8,  KB_F9,  KB_F10, KB_F11, KB_F12, KB_INS, KB_DEL, \
           KB_TAB, KB_WH_L,KB_WH_U,KB_MS_U,KB_WH_D,KB_WH_R,KB_WH_L,KB_WH_D,KB_WH_U,KB_WH_R,KB_NO,  KB_NO,  KB_NO,  KB_BSPC, \
           KB_LCTL,KB_NO,  KB_MS_L,KB_MS_D,KB_MS_R,KB_NO,  KB_MS_L,KB_MS_D,KB_MS_U,KB_MS_R,KB_FN3, KB_NO,  KB_ENT, \
           KB_LSFT,KB_BTN4,KB_BTN5,KB_BTN1,KB_BTN2,KB_BTN3,KB_BTN2,KB_BTN1,KB_BTN4,KB_BTN5,KB_NO,  KB_RSFT,KB_NO, \
           KB_LGUI,KB_LALT,KB_BTN1,KB_RALT,KB_RGUI),

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
           KB_LGUI,KB_LALT,KB_FN4, KB_RALT,KB_RGUI)
};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

uint8_t keymap_fn_layer(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_layer[biton(fn_bits)]);
}

uint8_t keymap_fn_keycode(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_keycode[(biton(fn_bits))]);
}

// define a condition to enter special function mode
bool keymap_is_special_mode(uint8_t fn_bits)
{
    return (usb_keyboard_mods == (BIT_LCTRL | BIT_LSHIFT | BIT_LALT | BIT_LGUI));
}
