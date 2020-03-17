#include QMK_KEYBOARD_H

#define TAPPING_TERM_2 1000

enum layer_number {
    BASE = 0,
    RAISE,
    MOUSE,
    WHEEL,
    /* FUNCTION, */
    CURSOR,
    /* CURSOR_ACCL  */
};

/* KEYCODE DEFINITIONS */

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

#define KC_ES_ALT LALT_T(KC_ESC)
#define KC_RA_ENT LT(RAISE, KC_ENT)
#define KC_D_MOUS LT(MOUSE, KC_D)
#define KC_F_CUR  LT(CURSOR, KC_F)
#define KC_WEEL   MO(WHEEL)

#define KC_RST  RESET
#define KC_MUP  KC_MS_U
#define KC_MDN  KC_MS_D
#define KC_MLFT KC_MS_L
#define KC_MRGT KC_MS_R
#define KC_WUP  KC_WH_U
#define KC_WDN  KC_WH_D
#define KC_WLFT KC_WH_L
#define KC_WRGT KC_WH_R
#define KC_ACCL KC_MS_ACCEL0

/* KEYMAPS */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_kc( \
    BSPC, JYEN, Q,    W,    E,      R,     T,    Y,    T,    Y,    U,   I,      O,    P,    MINS, ____,
    LCTL, LCTL, A,    S,    D_MOUS, F_CUR, G,    LBRC, RBRC, H,    J,   K,      L,    SCLN, QUOT, ____,
    LSFT, LSFT, Z,    X,    C,      V,     B,    N,    B,    N,   M,      COMM, DOT,  SLSH, BSLS, ____,
    /* */ ____, ____, ____, ES_ALT, SPC,   SPC,              TAB,  TAB, RA_ENT, ____, ____, ____
),

[RAISE] = LAYOUT_kc( \
    ____, BSPC, 1,    2,    3,     4,     5,     6,    5,    6,     7,   8,    9,    0,    EQL,  ____,
    ____, ____, ____, ____, LCBR,  LPRN,  LBRC,  ____, ____, RBRC, RPRN, RCBR, PIPE, ____, PLUS, ____,
    ____, ____, EXLM, AT,   HASH,  DLR,   PERC,  CIRC, PERC, CIRC, AMPR, ASTR, ____, ____, ____, ____,
    /* */ ____, ____, ____, LANG2, LANG1, LANG1,             RST,  RST,  ____, ____, ____, ____
),

[MOUSE] = LAYOUT_kc( \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, WEEL, ____, ACCL, ____, ____, ____, MLFT, MDN,  MUP,  MRGT, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
    /* */ ____, ____, ____, BTN2, BTN1, BTN1,             ____, ____, ____, ____, ____, ____
),

[WHEEL] = LAYOUT_kc( \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____, ____, ____, WRGT, WUP,  WDN,  WLFT, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
    /* */ ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____
),

[CURSOR] = LAYOUT_kc( \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____, ____, ____, LEFT, DOWN, UP,   RGHT, ____, ____, ____,
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,
    /* */ ____, ____, ____, ____, ____, ____,             ____, ____, ____, ____, ____, ____
),

};
