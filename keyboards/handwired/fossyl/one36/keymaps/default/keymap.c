#include QMK_KEYBOARD_H

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#define SFT_ESC  SFT_T(KC_ESC)
#define SFT_TAB  SFT_T(KC_TAB)
#define SFT_QUOT  SFT_T(KC_QUOT)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)
#define SFT_SPC  SFT_T(KC_SPC)

#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN1

#define SFT_MHEN SFT_T(KC_MHEN)
#define SFT_HENK SFT_T(KC_HENK)

#define RAISE LT(_RAISE,KC_SPC)
#define LOWER LT(_LOWER,KC_ENT)
#define RAISE1 LT(_RAISE,KC_X)
#define LOWER1 LT(_LOWER,KC_DOT)
#define RAISE2 LT(_RAISE,KC_Z)
#define LOWER2 LT(_LOWER,KC_SLSH)

#define ADJ_R LT(_ADJUST,KC_ENT)
#define ADJ_L LT(_ADJUST,KC_SPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)
     * +-----------------------------------------+                             +-----------------------------------------+
     * | TAB  |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |  -   |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |SHMHEN|   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ;  |SHFT_'|
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     *        |   z  |   x  |   c  |   v  |   b  |                             |   n  |   m  |   ,  |   .  |   /  |
     *        +------+------+------+-------------+                             +-------------+------+------+------+
     *                                    |RAISE |                             |LOWER |
     *                                    +------+                             +------+
     */
    [_BASE] = LAYOUT(
        KC_TAB,  KC_Q,   KC_W,        KC_E,        KC_R,    KC_T,               KC_Y,        KC_U,        KC_I,           KC_O,    KC_P,    KC_MINS,
        SFT_MHEN,KC_A,   KC_S,        KC_D,        KC_F,    KC_G,               KC_H,        KC_J,        KC_K,           KC_L,    KC_SCLN, SFT_QUOT,
                 KC_Z,  KC_X, LCTL_T(KC_C),LOPT_T(KC_V),LCMD_T(KC_B),           RCMD_T(KC_N),ROPT_T(KC_M),RCTL_T(KC_COMM),KC_DOT,  KC_SLSH,
                                                            RAISE,              LOWER
    ),

    /* LOWER
     * +-----------------------------------------+                             +-----------------------------------------+
     * | ESC  |   !  |   @  |   #  |   $  |   %  |                             | BTN1 | BTN1 | BTN1 | BTN2 |   -  | BSPC |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |   ^  |   &  |   *  |   (  |   )  |                             |MLEFT |MDOWN | MUP  |MRIGHT|   +  |SFHENK|
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     *        |   _  |   |  |   -  |   _  |   \  |                             |HLEFT |HDOWN | HUP  |HRIGHT|   =  |
     *        +------+------+------+------+------+                             +-------------+------+------+------+
     *                                    |ADJUST|                             |      |
     *                                    +------+                             +------+
     */
    [_LOWER] = LAYOUT(
        KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,             KC_BTN1, KC_BTN1, KC_BTN1, KC_BTN2, KC_MINS, KC_DEL,
        _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,             KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_PLUS, SFT_HENK,
                 KC_UNDS, KC_PIPE, KC_MINS, KC_UNDS, KC_BSLS,             KC_WH_R, KC_WH_U, KC_WH_D, KC_WH_L, KC_EQL,
                                                     ADJ_L,               _______
    ),
    /* RAISE
     * +-----------------------------------------+                             +-----------------------------------------+
     * | ECS  |   1  |   2  |   3  |   4  |   5  |                             |   6  |   7  |   8  |   9  |   0  | BSPC |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |   `  |   @  |   #  |   $  |   %  |                             | LEFT | DOWN |  UP  |RIGHT |      |SFHENK|
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     *        |   !  |   ?  |   ~  |   (  |   [  |                             |   ]  |   )  |      |      |   =  |
     *        +------+------+------+-------------+                             +-------------+------+------+------+
     *                                    |      |                             |ADJUST|
     *                                    +------+                             +------+
     */
    [_RAISE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        _______, KC_GRV,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,             KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, SFT_HENK,
                 KC_EXLM, KC_QUES, KC_TILD, KC_LPRN, KC_LBRC,             KC_RBRC, KC_RPRN, _______, _______, KC_EQL,
                                                     _______,            ADJ_R
    ),
    /* ADJUST
     * +-----------------------------------------+                             +-----------------------------------------+
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                             |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                             |      |      |      |      |      |SFHENK|
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     *        |      |      |      |      |RESET |                             |      |      |      |      |      |
     *        +------+------+------+-------------+                             +-------------+------+------+------+
     *                                    |      |                             |      |
     *                                    +------+                             +------+
     */
    [_ADJUST] = LAYOUT(
        KC_F1,  KC_F2,    KC_F3,    KC_F4,   KC_F5,    KC_F6,               KC_F7,   KC_F8,   KC_F9,    KC_F10,    KC_F11,    KC_F12,
        _______,_______,  _______,  _______, _______,  _______,             _______, _______, _______,  _______, _______,     SFT_HENK,
                 _______, _______, _______, _______, RESET,                 _______, _______, _______, _______, _______,
                                                     _______,            _______
    )
};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

/*COMBO keymaps*/

enum combo_events {
    HELLOWORLD,
    FUNCTION,
    ZH,
    ZJ,
    ZK,
    ZL,



    TABW_GRV,
    OMINS_BSPC,
    QW_ESC,
    TABMHEN_LBRC,
    MINSQUOT_RBRC,
};

const uint16_t PROGMEM helloworld_combo[] = {KC_H, KC_W, COMBO_END};
const uint16_t PROGMEM function_combo[] = {KC_F, KC_U, COMBO_END};
const uint16_t PROGMEM zh_combo[] = {KC_Z, KC_H, COMBO_END};
const uint16_t PROGMEM zj_combo[] = {KC_Z, KC_J, COMBO_END};
const uint16_t PROGMEM zk_combo[] = {KC_Z, KC_K, COMBO_END};
const uint16_t PROGMEM zl_combo[] = {KC_Z, KC_L, COMBO_END};

const uint16_t PROGMEM tabw_combo[] = {KC_TAB, KC_W, COMBO_END};
const uint16_t PROGMEM omins_combo[] = {KC_O, KC_MINS, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM tabmhen_combo[] = {KC_TAB, SFT_MHEN, COMBO_END};
const uint16_t PROGMEM minsquot_combo[] = {KC_MINS, SFT_QUOT, COMBO_END};

combo_t key_combos[] = {
    [HELLOWORLD] = COMBO_ACTION(helloworld_combo),
    [FUNCTION] = COMBO_ACTION(function_combo),
    [ZH] = COMBO_ACTION(zh_combo),
    [ZJ] = COMBO_ACTION(zj_combo),
    [ZK] = COMBO_ACTION(zk_combo),
    [ZL] = COMBO_ACTION(zl_combo),

    [TABW_GRV] = COMBO(tabw_combo, KC_GRV),
    [OMINS_BSPC] = COMBO(omins_combo, KC_BSPC),
    [QW_ESC] = COMBO(qw_combo, KC_ESC),
    [TABMHEN_LBRC] = COMBO(tabmhen_combo, KC_LBRC),
    [MINSQUOT_RBRC] = COMBO(minsquot_combo, KC_RBRC),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case HELLOWORLD:
            if (pressed) {
                SEND_STRING("hello, world");
            }
            break;
        case FUNCTION:
            if (pressed) {
                SEND_STRING("const increment = (n: number): number => { return n + 1 };");
                tap_code16(LOWER);
                SEND_STRING("const myFunc = (s: string): string => `${s} hello, world`");
            }
            break;
        case ZH:
            if (pressed) {
                SEND_STRING("<-");
            }
            break;
        case ZJ:
            if (pressed) {
                SEND_STRING("<=");
            }
            break;
        case ZK:
            if (pressed) {
                SEND_STRING("=>");
            }
            break;
        case ZL:
            if (pressed) {
                SEND_STRING("->");
            }
            break;
    }
}
