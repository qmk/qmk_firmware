#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "keymap_extras/keymap_german.h"

#define UM 0

#define L0   0      // layer_0
#define L1   1      // layer_1  
#define L2   2      // layer_2
#define L3   3      // layer_3
#define L4   4      // layer_4
#define L5   5      // layer_5
#define L6   6      // layer_6

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
    .------------------------------------.------------------------------------.
    |ESC  | 1  | 2  | 3  | 4  | 5  | ´   | `   | 6  | 7  | 8  | 9  | 0  | ^   |
    !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
    |TAB  | X  | V  | L  | C  | W  |Print|     | K  | H  | G  | F  | Q  |  ß  |
    !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
    |MO(1)| U  | I  | A  | E  | O  |-----!-----! S  | N  | R  | T  | D  | Y   |
    !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
    |LSFT | ü  | ö  |  ä | P  | Z  |SPACE|     | B  | M  | ,  | .  | J  |RSFT |
    '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
     |LCTL|LGUI|LALT|MO(3)|MO(2)|                   !MO(2)|MO(3)|APP |RALT|RCTL|
     '------------------------'                     '------------------------'
                            .-----------. .-----------.
                            |VOL- |VOL+ | !MUTE |PLAY |
                      .-----+-----+-----! !-----+-----+-----.
                      !     !     |     | !     |     !     !
                      !     !     |-----| !-----|     !     !
                      ! CTL !     ! ALT ! ! CTL !     ! ALT !
                      |ENTER|MO(1)| TAB | !ESC  |MO(1)|SPACE|
                      '-----------------' '-----------------'
 */
[L0] = LAYOUT_ergodox(
 KC_ESC,  DE_1,    DE_2,     DE_3,    DE_4,     DE_5,    DE_ACUT,
 KC_TAB,  DE_X,    DE_V,     DE_L,    DE_C,     DE_W,    KC_PSCR,
 MO(1),   DE_U,    DE_I,     DE_A,    DE_E,     DE_O,
 KC_LSFT, DE_UE,   DE_OE,    DE_AE,   DE_P,     DE_Z,    KC_SPACE,
 KC_LCTL, KC_LGUI, KC_LALT,  MO(3),   MO(2),
 /*-*/    /*-*/    /*-*/     /*-*/    /*-*/     KC_VOLD, KC_VOLU,
 /*-*/    /*-*/    /*-*/     /*-*/    /*-*/     /*-*/    KC_TRNS,
 /*-*/    /*-*/    /*-*/     /*-*/    CTL_T(KC_ENTER), MO(1),   ALT_T(KC_TAB),
 DE_GRV,  DE_6,    DE_7,     DE_8,    DE_9,     DE_0,    DE_CIRC,
 KC_TRNS, DE_K,    DE_H,     DE_G,    DE_F,     DE_Q,    DE_SS,
 /*-*/    DE_S,    DE_N,     DE_R,    DE_T,     DE_D,    DE_Y,
 KC_TRNS, DE_B,    DE_M,     DE_COMM, DE_DOT,   DE_J,    KC_RSFT,
 /*-*/    /*-*/    MO(2),    MO(3),   KC_APP,   KC_RALT, KC_RCTL,
 KC_MUTE, KC_MPLY,
 KC_TRNS,
 CTL_T(KC_ESC), MO(1),   ALT_T(KC_SPACE)
),
/*
    .------------------------------------.------------------------------------.
    |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
    !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
    |     | €  | _  | [  | ]  |    |     |     | !  | <  | >  | =  | &  |     |
    !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
    |     | \  | /  |  { | }  | *  |-----!-----! ?  | (  | )  | -  | :  | @   |
    !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
    |     | #  | $  | |  | ~  |    |     |     | +  | %  | "  | '  | ;  |     |
    '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
     |    |    |    |    |    |                     !    |    |    |    |    |
     '------------------------'                     '------------------------'
                            .-----------. .-----------.
                            |     |     | !     |     |
                      .-----+-----+-----! !-----+-----+-----.
                      !     !     |     | !     |     !     !
                      !     !     !-----! !-----!     !     !
                      |     |     |     | !     |     |     |
                      '-----------------' '-----------------'
 */
[L1] = LAYOUT_ergodox(
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, DE_EURO, DE_UNDS, DE_LBRC, DE_RBRC, KC_TRNS, KC_TRNS,
 KC_TRNS, DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR,
 KC_TRNS, DE_HASH, DE_DLR,  DE_PIPE, DE_TILD, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, DE_EXLM, DE_LESS, DE_MORE, DE_EQL,  DE_AMPR, KC_TRNS,
 /*-*/    DE_QST,  DE_LPRN, DE_RPRN, DE_MINS, DE_COLN, DE_AT,
 KC_TRNS, DE_PLUS, DE_PERC, DE_DQOT, DE_QUOT, DE_SCLN, KC_TRNS,
 /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS
),
/*
 * .------------------------------------.------------------------------------.
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     |PGUP|BSPC| UP |DEL |PGDN|     |     |    |  7 |  8 |  9 |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |HOME|LEFT|DOWN|RGHT|END |-----!-----!    |  4 |  5 |  6 |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |PREV|NEXT|    |     |     |    |  1 |  2 |  3 |    |     |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     !    |    |    |    |    |
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |  0  |
 *                   '-----------------' '-----------------'
 */
[L2] = LAYOUT_ergodox(
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, KC_TRNS,
 KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, DE_7,    DE_8,    DE_9,    KC_TRNS, KC_TRNS,
 /*-*/    KC_TRNS, DE_4,    DE_5,    DE_6,    KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, DE_1,    DE_2,    DE_3,    KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS, DE_0
),
/*
 * .------------------------------------.------------------------------------.
 * |     | F1 | F2 | F3 | F4 | F5 | F6  |     |    |    |    |    |    |     |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     | F7 | F8 | F9 | F10| F11| F12 |     |    |M_WU|M_CU|M_WD|    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |M_B5 |M_B4|M_B3|M_B2|M_B1|    |-----!-----!    |M_CL|M_CD|M_CR|    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |M_A2|M_A1|M_A0|    |     |     |    |    |    |    |    |     |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     !    |    |    |    |    |
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |     |
 *                   '-----------------' '-----------------'
 */
[L3] = LAYOUT_ergodox(
 KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
 KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
 KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_ACL2, KC_ACL1, KC_ACL0, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_WH_U, KC_MS_U, KC_WH_D, KC_TRNS, KC_TRNS,
 /*-*/    KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS
),
/*
 * .------------------------------------.------------------------------------.
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |    |    |    |-----!-----!    |    |    |    |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     !    |    |    |    |    |
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |     |
 *                   '-----------------' '-----------------'
 */
[L4] = LAYOUT_ergodox(
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS
),
/*
 * .------------------------------------.------------------------------------.
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |    |    |    |-----!-----!    |    |    |    |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     !    |    |    |    |    |
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |     |
 *                   '-----------------' '-----------------'
 */
[L5] = LAYOUT_ergodox(
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS
),
/*
 * .------------------------------------.------------------------------------.
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |    |    |    |-----!-----!    |    |    |    |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     !    |    |    |    |    |
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |     |
 *                   '-----------------' '-----------------'
 */
[L6] = LAYOUT_ergodox(
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS
),
};

#define UC_MODE_WIN 0
#define UC_MODE_LINUX 1
#define UC_MODE_OSX 2

// TODO: allow default mode to be configured
static uint16_t unicode_mode = UC_MODE_WIN;

uint16_t hextokeycode(uint8_t hex) {
    if (hex == 0x0) {
        return KC_P0;
    }
    if (hex < 0xA) {
        return KC_P1 + (hex - 0x1);
    }
    return KC_A + (hex - 0xA);
}

void unicode_action_function(uint16_t hi, uint16_t lo) {
    switch (unicode_mode) {
    case UC_MODE_WIN:
        register_code(KC_LALT);

        register_code(KC_PPLS);
        unregister_code(KC_PPLS);

        register_code(hextokeycode((hi & 0xF0) >> 4));
        unregister_code(hextokeycode((hi & 0xF0) >> 4));
        register_code(hextokeycode((hi & 0x0F)));
        unregister_code(hextokeycode((hi & 0x0F)));
        register_code(hextokeycode((lo & 0xF0) >> 4));
        unregister_code(hextokeycode((lo & 0xF0) >> 4));
        register_code(hextokeycode((lo & 0x0F)));
        unregister_code(hextokeycode((lo & 0x0F)));

        unregister_code(KC_LALT);
        break;
    case UC_MODE_LINUX:
        register_code(KC_LCTL);
        register_code(KC_LSFT);

        register_code(KC_U);
        unregister_code(KC_U);

        register_code(hextokeycode((hi & 0xF0) >> 4));
        unregister_code(hextokeycode((hi & 0xF0) >> 4));
        register_code(hextokeycode((hi & 0x0F)));
        unregister_code(hextokeycode((hi & 0x0F)));
        register_code(hextokeycode((lo & 0xF0) >> 4));
        unregister_code(hextokeycode((lo & 0xF0) >> 4));
        register_code(hextokeycode((lo & 0x0F)));
        unregister_code(hextokeycode((lo & 0x0F)));

        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        break;
    case UC_MODE_OSX:
        break;
    }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (!record->event.pressed) {
        return MACRO_NONE;
    }
    // MACRODOWN only works in this function
    switch(id) {
        case UM:
            unicode_mode = (unicode_mode + 1) % 2;
            break;


        default:
            break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case L1:
            ergodox_right_led_1_on();
            break;
        case L2:
            ergodox_right_led_2_on();
            break;
        case L3:
            ergodox_right_led_3_on();
            break;
        case L4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case L5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        // case L6:
        //     ergodox_right_led_2_on();
        //     ergodox_right_led_3_on();
        //     break;
        // case L7:
        //     ergodox_right_led_1_on();
        //     ergodox_right_led_2_on();
        //     ergodox_right_led_3_on();
        //     break;
        default:
            ergodox_board_led_off();
            break;
    }
};
