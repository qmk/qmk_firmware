/* 
 * Keymap for ADB keyboard
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

// TODO: ADB to USB default keymap
// TODO: keymap macro template for m0116/m0115
/* Apple Keyboard m0116
    K7F, \
    K35, K12, K13, K14, K15, K17, K16, K1A, K1C, K19, K1D, K1B, K18, K33,       K47, K51, K4B, K43, \
    K30, K0C, K0D, K0E, K0F, K10, K11, K20, K22, K1F, K23, K21, K1E,            K59, K5B, K5C, K4E, \
    K36, K00, K01, K02, K03, K05, K04, K26, K28, K25, K29, K27,      K24,       K56, K57, K58, K45, \
    K38, K06, K07, K08, K09, K0B, K2D, K2E, K2B, K2F, K2C,           K7B,       K53, K54, K55,      \
    K39, K3A, K37, K32,           K31,           K2A, K3B, K3C, K3D, K3E,       K52,      K41, K4C  \
*/

/* no tenkey
    K7F, \
    K35, K12, K13, K14, K15, K17, K16, K1A, K1C, K19, K1D, K1B, K18, K33, \
    K30, K0C, K0D, K0E, K0F, K10, K11, K20, K22, K1F, K23, K21, K1E,      \
    K36, K00, K01, K02, K03, K05, K04, K26, K28, K25, K29, K27,      K24, \
    K38, K06, K07, K08, K09, K0B, K2D, K2E, K2B, K2F, K2C,           K7B, \
    K39, K3A, K37, K32,           K31,           K2A, K3B, K3C, K3D, K3E \
*/
#define KEYMAP( \
    K7F, \
    K35, K12, K13, K14, K15, K17, K16, K1A, K1C, K19, K1D, K1B, K18, K33, \
    K30, K0C, K0D, K0E, K0F, K10, K11, K20, K22, K1F, K23, K21, K1E,      \
    K36, K00, K01, K02, K03, K05, K04, K26, K28, K25, K29, K27,      K24, \
    K38, K06, K07, K08, K09, K0B, K2D, K2E, K2B, K2F, K2C,           K7B, \
    K39, K3A, K37, K32,           K31,           K2A, K3B, K3C, K3D, K3E  \
) { \
    { K00, K01, K02, K03, K04, K05, K06,  K07 }, \
    { K08, K09, 000, K0B, K0C, K0D, K0E,  K0F }, \
    { K10, K11, K12, K13, K14, K15, K16,  K17 }, \
    { K18, K19, K1A, K1B, K1C, K1D, K1E,  K1F }, \
    { K20, K21, K22, K23, K24, K25, K26,  K27 }, \
    { K28, K29, K2A, K2B, K2C, K2D, K2E,  K2F }, \
    { K30, K31, K32, K33, 000, K35, K36,  K37 }, \
    { K38, K39, K3A, K3B, K3C, K3D, K3E,  000 }, \
    { 000, 000, 000, 000, 000, 000, 000,  000 }, \
    { 000, 000, 000, 000, 000, 000, 000,  000 }, \
    { 000, 000, 000, 000, 000, 000, 000,  000 }, \
    { 000, 000, 000, 000, 000, 000, 000,  000 }, \
    { 000, 000, 000, 000, 000, 000, 000,  000 }, \
    { 000, 000, 000, 000, 000, 000, 000,  000 }, \
    { 000, 000, 000, 000, 000, 000, 000,  000 }, \
    { 000, 000, 000, K7B, 000, 000, 000,  K7F }, \
}

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // FN_0
    0,              // FN_1
    0,              // FN_2
    0,              // FN_3
    0,              // FN_4
    0,              // FN_5
    0,              // FN_6
    0               // FN_7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KB_NO,          // FN_0
    KB_NO,          // FN_1
    KB_NO,          // FN_2
    KB_NO,          // FN_3
    KB_NO,          // FN_4
    KB_NO,          // FN_5
    KB_NO,          // FN_6
    KB_NO           // FN_7
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,---------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs|
     * |---------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   |
     * |-----------------------------------------------------'   |
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return|
     * |---------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift   |
     * |---------------------------------------------------------|
     * |Shi|Alt|Gui   l  `|                  |  \|Lef|Rig|Dow|Up |
     * `---------------------------------------------------------'
     */
    KEYMAP(KB_PWR, \
           KB_ESC, KB_1,   KB_2,   KB_3,   KB_4,   KB_5,   KB_6,   KB_7,   KB_8,   KB_9,   KB_0,   KB_MINS,KB_EQL, KB_BSPC, \
           KB_TAB, KB_Q,   KB_W,   KB_E,   KB_R,   KB_T,   KB_Y,   KB_U,   KB_I,   KB_O,   KB_P,   KB_LBRC,KB_RBRC, \
           KB_LCTL,KB_A,   KB_S,   KB_D,   KB_F,   KB_G,   KB_H,   KB_J,   KB_K,   KB_L,   KB_SCLN,KB_QUOT,KB_ENT, \
           KB_LSFT,KB_Z,   KB_X,   KB_C,   KB_V,   KB_B,   KB_N,   KB_M,   KB_COMM,KB_DOT, KB_SLSH,KB_RSFT, \
           KB_LSFT,KB_LALT,KB_LGUI,KB_GRV, KB_SPC, KB_BSLS,KB_LEFT,KB_RGHT,KB_DOWN,KB_UP),

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
    //return (usb_keyboard_mods == (BIT_LCTRL | BIT_LSHIFT | BIT_LALT | BIT_LGUI));
    return (usb_keyboard_mods == (BIT_RSHIFT));
}
