#include QMK_KEYBOARD_H

#define LAYER_IS_ON(n) (layer_state & (2 << ((n) - 1)))

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

enum custom_keycodes {
    KC_D_MOUS = SAFE_RANGE
};

/* KEYCODE DEFINITIONS */

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

#define KC_ES_ALT LALT_T(KC_ESC)
#define KC_RA_ENT LT(RAISE, KC_ENT)
/* #define KC_D_MOUS LT(MOUSE, KC_D) */
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
    LSFT, LSFT, Z,    X,    C,      V,     B,    N,    B,    B,    N,   M,      COMM, DOT,  SLSH, ____,
    /* */ ____, ____, ____, ES_ALT, SPC,   SPC,              TAB,  TAB, RA_ENT, ____, ____, ____
),

[RAISE] = LAYOUT_kc( \
    ____, BSPC, 1,    2,    3,     4,     5,     6,    5,    6,     7,   8,    9,    0,    EQL,  ____,
    ____, ____, ____, ____, LCBR,  LPRN,  LBRC,  ____, ____, RBRC, RPRN, RCBR, PIPE, ____, PLUS, ____,
    ____, ____, EXLM, AT,   HASH,  DLR,   PERC,  CIRC, PERC, CIRC, AMPR, ASTR, ____, ____, BSLS, ____,
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

uint16_t d_mous_timer;

void matrix_scan_user (void) {
    if (d_mous_timer) {
        uint16_t elapsed_time =  timer_elapsed(d_mous_timer);
        if (elapsed_time >= TAPPING_TERM_2) {
            /* 1000 ms elapsed with timer active -> register D key instead and settle state */
            layer_off(MOUSE);
            register_code(KC_D);
            d_mous_timer = 0;
        } else if (elapsed_time >= TAPPING_TERM) {
            /* TAPPING_TERM elapsed with timer active -> activate MOUSE layer */
            layer_on(MOUSE);
        }
    }
}

bool process_record_keymap (uint16_t keycode, keyrecord_t *record) {
    if (d_mous_timer && record->event.pressed) {
        /* interrupted -> settle state */
        if (!LAYER_IS_ON(MOUSE)) {
            register_code(KC_D);
        }
        d_mous_timer = 0;
    }
    switch (keycode) {
      case KC_D_MOUS:
        if (record->event.pressed) {
            /* first tap -> activate timer */
            d_mous_timer = timer_read();
        } else if (d_mous_timer) {
            /* timer is active and the key is released -> just send "D" */
            d_mous_timer = 0;
            layer_off(MOUSE);
            tap_code(KC_D);
        } else {
            /* state is settled and the key is released -> restore registered keys */
            unregister_code(KC_D);
            layer_off(MOUSE);
        }
        return false;
    }
    return true;
}
