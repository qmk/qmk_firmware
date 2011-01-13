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


#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))

// Convert physical keyboard layout to matrix array.
// This is a macro to define keymap easily in keyboard layout form.
/* Apple Extended Keyboard */
#define KEYMAP( \
    K35,  K7A,K78,K63,K76, K60,K61,K62,K64, K65,K6D,K67,K6F, K69,K6B,K71,              K7F, \
    K32,K12,K13,K14,K15,K17,K16,K1A,K1C,K19,K1D,K1B,K18,K33, K72,K73,K74,  K47,K51,K4B,K43, \
    K30,K0C,K0D,K0E,K0F,K11,K10,K20,K22,K1F,K23,K21,K1E,K2A, K75,K77,K79,  K59,K5B,K5C,K4E, \
    K39,K00,K01,K02,K03,K05,K04,K26,K28,K25,K29,K27,    K24,               K56,K57,K58,K45, \
    K38,K06,K07,K08,K09,K0B,K2D,K2E,K2B,K2F,K2C,        K7B,     K3E,      K53,K54,K55,     \
    K36,K3A,K37,        K31,                                 K3B,K3D,K3C,  K52,    K41,K4C  \
) { \
    { KB_##K00, KB_##K01, KB_##K02, KB_##K03, KB_##K04, KB_##K05, KB_##K06, KB_##K07 }, \
    { KB_##K08, KB_##K09, KB_NO,    KB_##K0B, KB_##K0C, KB_##K0D, KB_##K0E, KB_##K0F }, \
    { KB_##K10, KB_##K11, KB_##K12, KB_##K13, KB_##K14, KB_##K15, KB_##K16, KB_##K17 }, \
    { KB_##K18, KB_##K19, KB_##K1A, KB_##K1B, KB_##K1C, KB_##K1D, KB_##K1E, KB_##K1F }, \
    { KB_##K20, KB_##K21, KB_##K22, KB_##K23, KB_##K24, KB_##K25, KB_##K26, KB_##K27 }, \
    { KB_##K28, KB_##K29, KB_##K2A, KB_##K2B, KB_##K2C, KB_##K2D, KB_##K2E, KB_##K2F }, \
    { KB_##K30, KB_##K31, KB_##K32, KB_##K33, KB_NO,    KB_##K35, KB_##K36, KB_##K37 }, \
    { KB_##K38, KB_##K39, KB_##K3A, KB_##K3B, KB_##K3C, KB_##K3D, KB_##K3E, KB_NO    }, \
    { KB_NO,    KB_##K41, KB_NO,    KB_##K43, KB_NO,    KB_##K45, KB_NO,    KB_##K47 }, \
    { KB_NO,    KB_NO,    KB_NO,    KB_##K4B, KB_##K4C, KB_NO,    KB_##K4E, KB_NO    }, \
    { KB_NO,    KB_##K51, KB_##K52, KB_##K53, KB_##K54, KB_##K55, KB_##K56, KB_##K57 }, \
    { KB_##K58, KB_##K59, KB_NO,    KB_##K5B, KB_##K5C, KB_NO,    KB_NO,    KB_NO    }, \
    { KB_##K60, KB_##K61, KB_##K62, KB_##K63, KB_##K64, KB_##K65, KB_NO,    KB_##K67 }, \
    { KB_NO,    KB_##K69, KB_NO,    KB_##K6B, KB_NO,    KB_##K6D, KB_NO,    KB_##K6F }, \
    { KB_NO,    KB_##K71, KB_##K72, KB_##K73, KB_##K74, KB_##K75, KB_##K76, KB_##K77 }, \
    { KB_##K78, KB_##K79, KB_##K7A, KB_##K7B, KB_NO,    KB_NO,    KB_NO,    KB_##K7F }  \
}
/* plain keymap
    {
        { KB_A,   KB_S,   KB_D,   KB_F,   KB_H,   KB_G,   KB_Z,   KB_X   }, // 00-07
        { KB_C,   KB_V,   KB_NO,  KB_B,   KB_Q,   KB_W,   KB_E,   KB_R   }, // 08-0F
        { KB_Y,   KB_T,   KB_1,   KB_2,   KB_3,   KB_4,   KB_6,   KB_5   }, // 10-17
        { KB_EQL, KB_9,   KB_7,   KB_MINS,KB_8,   KB_0,   KB_RBRC,KB_O   }, // 18-1F
        { KB_U,   KB_LBRC,KB_I,   KB_P,   KB_ENT, KB_L,   KB_J,   KB_QUOT}, // 20-27
        { KB_K,   KB_SCLN,KB_BSLS,KB_COMM,KB_SLSH,KB_N,   KB_M,   KB_DOT }, // 28-2F
        { KB_TAB, KB_SPC, KB_GRV, KB_BSPC,KB_NO,  KB_ESC, KB_LCTL,KB_LGUI}, // 30-37
        { KB_LSFT,KB_CAPS,KB_LALT,KB_LEFT,KB_RGHT,KB_DOWN,KB_UP,  KB_NO  }, // 38-3F
        { KB_NO,  KB_PDOT,KB_NO,  KB_PAST,KB_NO,  KB_PPLS,KB_NO,  KB_NLCK}, // 40-47
        { KB_NO,  KB_NO,  KB_NO,  KB_PSLS,KB_PENT,KB_NO,  KB_PMNS,KB_NO  }, // 48-4F
        { KB_NO,  KB_PEQL,KB_P0,  KB_P1,  KB_P2,  KB_P3,  KB_P4,  KB_P5  }, // 50-57
        { KB_P6,  KB_P7,  KB_NO,  KB_P8,  KB_P9,  KB_NO,  KB_NO,  KB_NO  }, // 58-5F
        { KB_F5,  KB_F6,  KB_F7,  KB_F3,  KB_F8,  KB_F9,  KB_NO,  KB_F11 }, // 60-67
        { KB_NO,  KB_PSCR,KB_NO,  KB_SLCK,KB_NO,  KB_F10, KB_NO,  KB_F12 }, // 68-6F
        { KB_NO,  KB_BRK, KB_INS, KB_HOME,KB_PGUP,KB_DEL, KB_F4,  KB_END }, // 70-77
        { KB_F2,  KB_PGDN,KB_F1,  KB_RSFT,KB_NO,  KB_NO,  KB_NO,  KB_PWR }, // 78-7F
    },
*/


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // Fn0
    0,              // Fn1
    0,              // Fn2
    0,              // Fn3
    0,              // Fn4
    0,              // Fn5
    0,              // Fn6
    0               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KB_NO,          // Fn0
    KB_NO,          // Fn1
    KB_NO,          // Fn2
    KB_NO,          // Fn3
    KB_NO,          // Fn4
    KB_NO,          // Fn5
    KB_NO,          // Fn6
    KB_NO           // Fn7
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default Layer: plain keymap
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.             ,---.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|             |Pwr|
     * `---'   `---------------' `---------------' `---------------' `-----------'             `---'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU| |NmL|  =|  /|  *|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|  -|
     * |-----------------------------------------------------------| `-----------' |---------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |               |  4|  5|  6|  +|
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Ctrl |Gui |Alt |         Space           |     |    |      | |Lef|Dow|Rig| |      0|  .|   |
     * `-----------------------------------------------------------' `-----------' `---------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,                    PWR,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,EQL, PSLS,PAST,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,  PMNS,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                                              LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),
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
