#include QMK_KEYBOARD_H
#include "led.h"

enum keyboard_layers {
  LAYER_QWERTY = 0,
  LAYER_UPPER,
  LAYER_LOWER,
  LAYER_FUNCTION,
  LAYER_MOUSE,
  LAYER_ADJUST,
};

enum custom_keycodes {
  M_CP_CT = SAFE_RANGE,
  M_UPPER,
  M_LOWER,
  M_MOUSE,
  TIMBR_1,
  TIMBR_2,
  TIMBR_3,
  TIMBR_4,
  TMPO_UP,
  TMPO_DN,
  TMPO_DF
};

#define SC_UNDO             LCTL(KC_Z)
#define SC_REDO             LCTL(KC_Y)
#define SC_CUT              LCTL(KC_X)
#define SC_COPY             LCTL(KC_C)
#define SC_PSTE             LCTL(KC_V)
#define SC_SELA             LCTL(KC_A)
#define SC_SAVE             LCTL(KC_S)
#define SC_OPEN             LCTL(KC_O)
#define SC_ACLS             LALT(KC_F4)
#define SC_CCLS             LCTL(KC_F4)

#define OS_SHFT             OSM(MOD_LSFT)

#define ________________    _______, _______
#define XXXXXXXXXXXXXXXX    XXXXXXX, XXXXXXX

const matrix_row_t matrix_mask[MATRIX_ROWS] =
{
//  1098765432109876543210987654321
  0b0000000001111111101111011111111,
  0b0000000001111111111111111111111,
  0b0000000001111111111111111111111,
  0b0000000001111111111111111111111,
  0b0000000001010111111111111111111,
  0b0000000001111101111111101011111,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
/* LAYER = LAYER_QWERTY
  .-----------------------------------.       .-----------------------------------------------------------------------------------------------------------------------------.       .-----------------------------------.
  | VOL DN | MUTE   | VOL UP | BACKLT |       | F1     | F2     | F3     | F4     | XXXXXX | F5     | F6     | F7     | F8     | XXXXXX | F9     | F10    | F11    | F12    |       | PRINT  | SCR LK | PAUSE  | FN     |
  '-----------------------------------'       '-----------------------------------------------------------------------------------------------------------------------------'       '-----------------------------------'
  .-----------------------------------.       .-----------------------------------------------------------------------------------------------------------------------------.       .-----------------------------------.
  | NUM LK | KP /   | KP *   | KP -   |       | ESC    | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | =      | BACKSP |       | INS    | HOME   | PG UP  | XXXXXX |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|       |--------|--------|--------+--------|
  | KP 7   | KP 8   | KP 9   | KP +   |       | TAB    | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | -      | \      |       | DEL    | END    | PG DN  | XXXXXX |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|   o   |--------|--------|--------+--------|
  | KP 4   | KP 5   | KP 6   | KP +   |       | CAP LK | BACKSP | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | ENTER  |   o   | CP/CT  | UNDO   | PASTE  | XXXXXX |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|   o   |--------|--------|--------+--------|
  | KP 1   | KP 2   | KP 3   | KP Ent |       | LSHIFT | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | RSHIFT | RSHIFT |       | XXXXXX | UP     | XXXXXX | XXXXXX |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|       |--------|--------|--------+--------|
  | KP 0   | KP ,   | KP .   | KP Ent |       | LCTRL  | XXXXXX | LWIN   | XXXXXX | LALT   | UPPER  | SPACE  . SPACE  | LOWER  | OSHIFT | RALT   | APP    | XXXXXX | RCTRL  |       | LEFT   | DOWN   | RIGHT  | XXXXXX |
  '-----------------------------------'       '-----------------------------------------------------------------------------------------------------------------------------'       '-----------------------------------'
*/
KEYMAP(LAYER_QWERTY, \
    KC_VOLD, KC_MUTE, KC_VOLU, BL_STEP,         KC_F1  , KC_F2  , KC_F3  , KC_F4  , XXXXXXX, KC_F5  , KC_F6  , KC_F7  , KC_F8  , XXXXXXX, KC_F9  , KC_F10 , KC_F11 , KC_F12 ,         KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX , \
    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,         KC_ESC , KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_EQL , KC_BSPC,         KC_INS , KC_HOME, KC_PGUP, XXXXXXX , \
    KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS,         KC_TAB , KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MINS, KC_BSLS,         KC_DEL , KC_END , KC_PGDN, XXXXXXX , \
    KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS,         KC_CAPS, KC_BSPC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,         M_CP_CT, SC_UNDO, SC_PSTE, XXXXXXX , \
    KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT,         KC_LSFT, KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, KC_RSFT,         XXXXXXX, KC_UP  , XXXXXXX, XXXXXXX , \
    KC_KP_0, KC_PCMM, KC_PDOT, KC_PENT,         KC_LCTL, XXXXXXX, KC_LGUI, XXXXXXX, KC_LALT, M_UPPER, KC_SPC , KC_SPC , M_LOWER, OS_SHFT, KC_RALT, KC_APP , XXXXXXX, KC_RCTL,         KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX   \
),
/* LAYER = LAYER_LOWER
  .-----------------------------------.       .-----------------------------------------------------------------------------------------------------------------------------.       .-----------------------------------.
  | ______ | ______ | ______ | ______ |       | F13    | F14    | F15    | F16    | XXXXXX | F17    | F18    | F19    | F20    | XXXXXX | F21    | F22    | F23    | F24    |       | ______ | ______ | ______ | ______ |
  '-----------------------------------'       '-----------------------------------------------------------------------------------------------------------------------------'       '-----------------------------------'
  .-----------------------------------.       .-----------------------------------------------------------------------------------------------------------------------------.       .-----------------------------------.
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|       |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | $      | {      | [      | (      | %      | #      | )      | ]      | }      | @      | ______ | ______ |       | ______ | ______ | ______ | ______ |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|   o   |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ^      | *      | +      | -      | /      | \      | _      | '      | "      | `      | ______ | ______ |   o   | ______ | ______ | ______ | ______ |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|   o   |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | |      | &      | !      | ~      | ;      | :      | =      | <      | >      | ?      | ______ | ______ |       | ______ | ______ | ______ | ______ |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|       |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ | ______ | ______ | ______ . ______ | LOWER  | ______ | ______ | ______ | XXXXXX | ______ |       | ______ | ______ | ______ | ______ |
  '-----------------------------------'       '-----------------------------------------------------------------------------------------------------------------------------'       '-----------------------------------'
*/
KEYMAP(LAYER_LOWER, \
    _______, _______, _______, _______,         KC_F13 , KC_F14 , KC_F15 , KC_F16 , XXXXXXX, KC_F17 , KC_F18 , KC_F19 , KC_F20 , XXXXXXX, KC_F21 , KC_F22 , KC_F23 , KC_F24 ,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, KC_DLR , KC_LCBR, KC_LBRC, KC_LPRN, KC_PERC, KC_HASH, KC_RPRN, KC_RBRC, KC_RCBR, KC_AT  , _______, _______,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, KC_CIRC, KC_ASTR, KC_PLUS, KC_MINS, KC_SLSH, KC_BSLS, KC_UNDS, KC_QUOT, KC_DQT , KC_GRV , _______, _______,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, KC_PIPE, KC_AMPR, KC_EXLM, KC_TILD, KC_SCLN, KC_COLN, KC_EQL , KC_LT  , KC_GT  , KC_QUES, _______, _______,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, M_LOWER, _______, _______, _______, XXXXXXX, _______,         _______, _______, _______, _______  \
),
/* LAYER = LAYER_UPPER
  .-----------------------------------.       .-----------------------------------------------------------------------------------------------------------------------------.       .-----------------------------------.
  | ______ | ______ | ______ | ______ |       | F13    | F14    | F15    | F16    | XXXXXX | F17    | F18    | F19    | F20    | XXXXXX | F21    | F22    | F23    | F24    |       | ______ | ______ | ______ | ______ |
  '-----------------------------------'       '-----------------------------------------------------------------------------------------------------------------------------'       '-----------------------------------'
  .-----------------------------------.       .-----------------------------------------------------------------------------------------------------------------------------.       .-----------------------------------.
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|       |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | F1     | F2     | F3     | F4     | NUM LK | KP /   | KP 7   | KP 8   | KP 9   | KP -   | ______ | ______ |       | ______ | ______ | ______ | ______ |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|   o   |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | F5     | F6     | F7     | F8     | CAP LK | KP *   | KP 4   | KP 5   | KP 6   | KP +   | ______ | ______ |   o   | ______ | ______ | ______ | ______ |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|   o   |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | F9     | F10    | F11    | F12    | SCR LK | KP 0   | KP 1   | KP 2   | KP 3   | KP Ent | ______ | ______ |       | ______ | ______ | ______ | ______ |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|       |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ | ______ | UPPER  | KP 0   . KP 0   | ______ | RALT   | KP .   | KP Ent | XXXXXX | ______ |       | ______ | ______ | ______ | ______ |
  '-----------------------------------'       '-----------------------------------------------------------------------------------------------------------------------------'       '-----------------------------------'
*/
KEYMAP(LAYER_UPPER, \
    _______, _______, _______, _______,         KC_F13 , KC_F14 , KC_F15 , KC_F16 , XXXXXXX, KC_F17 , KC_F18 , KC_F19 , KC_F20 , XXXXXXX, KC_F21 , KC_F22 , KC_F23 , KC_F24 ,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_NLCK, KC_PSLS, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, _______, _______,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_CAPS, KC_PAST, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______, _______,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_SLCK, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______, _______,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, M_UPPER, KC_KP_0, KC_KP_0, _______, KC_RALT, KC_PDOT, KC_PENT, XXXXXXX, _______,         _______, _______, _______, _______  \
),
/* LAYER = LAYER_MOUSE
  .-----------------------------------.       .-----------------------------------------------------------------------------------------------------------------------------.       .-----------------------------------.
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ |
  '-----------------------------------'       '-----------------------------------------------------------------------------------------------------------------------------'       '-----------------------------------'
  .-----------------------------------.       .-----------------------------------------------------------------------------------------------------------------------------.       .-----------------------------------.
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ |       | MS AC0 | MS WHU | MS AC2 | MS BT1 |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|       |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ |       | MS WHL | MS WHD | MS WHU | MS BT2 |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|   o   |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ |   o   | MS BT1 | MS BT2 | MS BT3 | MS BT3 |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|   o   |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ | ______ |       | XXXXXX | MS U   | XXXXXX | MS BT4 |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|       |--------|--------|--------+--------|
  | ______ | ______ | ______ | ______ |       | ______ | ______ | ______ | ______ | ______ | ______ | ______ . ______ | ______ | ______ | ______ | ______ | ______ | ______ |       | MS L   | MS D   | MS R   | MS BT5 |
  '-----------------------------------'       '-----------------------------------------------------------------------------------------------------------------------------'       '-----------------------------------'
*/
KEYMAP(LAYER_MOUSE, \
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, \
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         KC_ACL0, KC_WH_U, KC_ACL2, KC_BTN1, \
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         KC_WH_L, KC_WH_D, KC_WH_U, KC_BTN2, \
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN3, \
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         XXXXXXX, KC_MS_U, XXXXXXX, KC_BTN4, \
    _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5  \
),
/* LAYER = LAYER_ADJUST
  .-----------------------------------.       .-----------------------------------------------------------------------------------------------------------------------------.       .-----------------------------------.
  | VOICE- | AUDIO  | VOICE+ | MUSIC  |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
  '-----------------------------------'       '-----------------------------------------------------------------------------------------------------------------------------'       '-----------------------------------'
  .-----------------------------------.       .-----------------------------------------------------------------------------------------------------------------------------.       .-----------------------------------.
  | XXXXXX | XXXXXX | XXXXXX | XXXXXX |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|       |--------|--------|--------+--------|
  | XXXXXX | XXXXXX | XXXXXX | XXXXXX |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|   o   |--------|--------|--------+--------|
  | XXXXXX | XXXXXX | XXXXXX | XXXXXX |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |   o   | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|   o   |--------|--------|--------+--------|
  | XXXXXX | XXXXXX | XXXXXX | XXXXXX |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | RESET  | XXXXXX | MOUSE  | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
  |--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|       |--------|--------|--------+--------|
  | XXXXXX | XXXXXX | XXXXXX | XXXXXX |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | UPPER  | XXXXXX . XXXXXX | LOWER  | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |       | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
  '-----------------------------------'       '-----------------------------------------------------------------------------------------------------------------------------'       '-----------------------------------'
*/
KEYMAP(LAYER_ADJUST, \
    MUV_DE , AU_TOG , MUV_IN , MU_TOG ,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET  , XXXXXXX, M_MOUSE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_UPPER, XXXXXXX, XXXXXXX, M_LOWER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
),
};

#ifdef AUDIO_ENABLE

float tone_my_startup[][2] = SONG(ODE_TO_JOY);
float tone_my_goodbye[][2] = SONG(ROCK_A_BYE_BABY);

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);

float tone_audio_on[][2]   = SONG(CLOSE_ENCOUNTERS_5_NOTE);
float tone_music_on[][2]   = SONG(DOE_A_DEER);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);

#endif /* AUDIO_ENABLE */

void persistent_default_layer_set(uint16_t default_layer)
{
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case M_CP_CT:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            if (record->tap.count == 1) {
                register_code(KC_C);
                unregister_code(KC_C);
            } else if (record->tap.count == 2) {
                register_code(KC_X);
                unregister_code(KC_X);
            }
            unregister_code(KC_LCTL);
        }
        return false;

  case M_UPPER:
    if (record->event.pressed) {
      layer_on(LAYER_UPPER);
      breathing_period_set(2);
      breathing_pulse();
      update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
    } else {
      layer_off(LAYER_UPPER);
      update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
    }
    return false;

  case M_LOWER:
    if (record->event.pressed) {
      layer_on(LAYER_LOWER);
      breathing_period_set(2);
      breathing_pulse();
      update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
    } else {
      layer_off(LAYER_LOWER);
      update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
    }
    return false;

#ifdef MOUSEKEY_ENABLE
  case M_MOUSE:
    if (record->event.pressed) {
      layer_invert(LAYER_MOUSE);
    }
    return false;
#endif /* MOUSEKEY_ENABLE */

#ifdef AUDIO_ENABLE
  case TIMBR_1:
    if (record->event.pressed) set_timbre(TIMBRE_12);
    return false;
  case TIMBR_2:
    if (record->event.pressed) set_timbre(TIMBRE_25);
    return false;
  case TIMBR_3:
    if (record->event.pressed) set_timbre(TIMBRE_50);
    return false;
  case TIMBR_4:
    if (record->event.pressed) set_timbre(TIMBRE_75);
    return false;
  case TMPO_UP:
    if (record->event.pressed) increase_tempo(10);
    return false;
  case TMPO_DN:
    if (record->event.pressed) decrease_tempo(10);
    return false;
  case TMPO_DF:
    if (record->event.pressed) {
      set_timbre(TIMBRE_DEFAULT);
      set_tempo(TEMPO_DEFAULT);
    }
    return false;
#endif /* AUDIO_ENABLE */

  default:
    return true;
  }
  return true;
};

#ifdef AUDIO_ENABLE

void matrix_init_user(void)
{
  set_voice(default_voice);
  startup_user();
  println("Matrix Init");
}

void led_set_user(uint8_t usb_led)
{
  static uint8_t old_usb_led = 0;

  _delay_ms(10); // gets rid of tick

  if (!is_playing_notes())
  {
    if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
      // If CAPS LK LED is turning on...
      PLAY_SONG(tone_caps_on);
    }
    else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
      // If CAPS LK LED is turning off...
      PLAY_SONG(tone_caps_off);
    }
    else if ((usb_led & (1<<USB_LED_NUM_LOCK)) && !(old_usb_led & (1<<USB_LED_NUM_LOCK)))
    {
      // If NUM LK LED is turning on...
      PLAY_SONG(tone_numlk_on);
    }
    else if (!(usb_led & (1<<USB_LED_NUM_LOCK)) && (old_usb_led & (1<<USB_LED_NUM_LOCK)))
    {
      // If NUM LED is turning off...
      PLAY_SONG(tone_numlk_off);
    }
    else if ((usb_led & (1<<USB_LED_SCROLL_LOCK)) && !(old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
      // If SCROLL LK LED is turning on...
      PLAY_SONG(tone_scroll_on);
    }
    else if (!(usb_led & (1<<USB_LED_SCROLL_LOCK)) && (old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
      // If SCROLL LED is turning off...
      PLAY_SONG(tone_scroll_off);
    }
  }

  old_usb_led = usb_led;
}

void startup_user()
{
  _delay_ms(10); // gets rid of tick
  // PLAY_SONG(tone_my_startup);
}

void shutdown_user()
{
  // PLAY_SONG(tone_my_goodbye);
  _delay_ms(2000);
  stop_all_notes();
}

void audio_on_user(void)
{
  PLAY_SONG(tone_audio_on);
}

void music_on_user(void)
{
  PLAY_SONG(tone_music_on);
}

void music_scale_user(void)
{
  PLAY_SONG(music_scale);
}

#endif /* AUDIO_ENABLE */
