#include "jj40.h"
#include "action_layer.h"

//layers
#define _QWERTY 0
#define _SYMBL  1
#define _NUMBS  2
#define _NAVIG  3

//mod tap keys
#define SHFZ MT(MOD_LSFT, KC_Z)
#define SHFS MT(MOD_RSFT, KC_SLSH)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBL,
  NUMBS,
  NAVIG,
  M_AND,
  M_OR,
  M_PE,
  M_ME,
  M_TE,
  M_DE,
  M_NE,
  M_PP,
  M_MM,
  M_EE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case M_AND:
                SEND_STRING("&&");
                return false;
            case M_OR:
                SEND_STRING("||");
                return false;
            case M_PE:
                SEND_STRING("+=");
                return false;
            case M_ME:
                SEND_STRING("-=");
                return false;
            case M_TE:
                SEND_STRING("*=");
                return false;
            case M_DE:
                SEND_STRING("/=");
                return false;
            case M_NE:
                SEND_STRING("!=");
                return false;
            case M_PP:
                SEND_STRING("++");
                return false;
            case M_MM:
                SEND_STRING("--");
                return false;
            case M_EE:
                SEND_STRING("==");
                return false;
        }
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |  [   |   ]  |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |  (   |   )  |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |  {   |   }  |   N  |   M  |   ,  |   .  |   /  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  OS  |navig |numbs |Back  |Enter | Tab  |Space |symbl |vol_dn|vol_up| Esc  |
 * `----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_Q      , KC_W   , KC_E      , KC_R      , KC_T   , KC_LBRC      , KC_RBRC, KC_Y  , KC_U      , KC_I   , KC_O   , KC_P   , \
  KC_A      , KC_S   , KC_D      , KC_F      , KC_G   , KC_LPRN      , KC_RPRN, KC_H  , KC_J      , KC_K   , KC_L   , KC_SCLN, \
  SHFZ      , KC_X   , KC_C      , KC_V      , KC_B   , KC_LCBR      , KC_RCBR, KC_N  , KC_M      , KC_COMM, KC_DOT , SHFS   , \
  KC_LCTL   , KC_LGUI, MO(_NAVIG), MO(_NUMBS), KC_BSPC, ALT_T(KC_ENT), KC_TAB , KC_SPC, MO(_SYMBL), KC_VOLD, KC_VOLU, KC_ESC   \
),

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |  ^   |  *=  |  -=  |  +=  |  !=  |      |      |   @  |  <   |   >  |  #   |   $  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  !   |   *  |   -  |   +  |   =  |      |      |   |  |  ||  |   ~  |  '   |   "  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  \   |  /=  |   %  |   _  |  ==  |      |      |   &  |  &&  |   `  |  :   |   ?  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |delete|      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBL] = KEYMAP( \
  KC_CIRC, M_TE   , M_ME   , M_PE   , M_NE   , KC_TRNS, KC_TRNS, KC_AT  , KC_LT  , KC_GT  , KC_HASH, KC_DLR , \
  KC_EXLM, KC_ASTR, KC_MINS, KC_PLUS, KC_EQL , KC_TRNS, KC_TRNS, KC_PIPE, M_OR   , KC_TILD, KC_QUOT, KC_DQUO, \
  KC_BSLS, M_DE   , KC_PERC, KC_UNDS, M_EE   , KC_TRNS, KC_TRNS, KC_AMPR, M_AND  , KC_GRV , KC_COLN, KC_QUES, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
),

/* Numbers
 * ,-----------------------------------------------------------------------------------.
 * |      | i3-1 | i3-2 | i3-3 |      |      |      |  7   |  8   |  9   |  -   |Back  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | i3-4 | i3-5 | i3-6 |      |      |      |  4   |  5   |  6   |  +   |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | i3-7 | i3-8 | i3-9 |      |      |      |  1   |  2   |  3   |  0   |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |RESET |      |      |      |      |      | lock |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBS] = KEYMAP( \
  LALT(KC_0), LALT(KC_1), LALT(KC_2), LALT(KC_3), KC_TRNS, KC_TRNS, KC_TRNS, KC_P7  , KC_P8  , KC_P9  , KC_PMNS, KC_BSPC, \
  KC_TRNS   , LALT(KC_4), LALT(KC_5), LALT(KC_6), KC_TRNS, KC_TRNS, KC_TRNS, KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_PAST, \
  KC_LSFT   , LALT(KC_7), LALT(KC_8), LALT(KC_9), KC_TRNS, KC_TRNS, KC_TRNS, KC_P1  , KC_P2  , KC_P3  , KC_P0  , KC_RSFT, \
  RESET     , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NLCK  \
),

/* Navigation
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | <-   |  v   |  ^   |  ->  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |TG(n) |
 * `-----------------------------------------------------------------------------------'
 */
[_NAVIG] = KEYMAP( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
),

};

// Loop
void matrix_scan_user(void) {
  // Empty
};
