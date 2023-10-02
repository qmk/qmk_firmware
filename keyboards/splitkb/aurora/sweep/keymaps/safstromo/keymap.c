#include QMK_KEYBOARD_H
#define GAMING DF(_GAMING)
#define COLEMAK DF(_COLEMAK_DH)
#define SYM MO(_SYM)
#define NAV MO(_NAV)
#define FKEYS MO(_FUNCTION)
#define ADJUST MO(_ADJUST)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define UNDO LCTL(KC_Z)
#define CUT LCTL(KC_X)
#define SFT_QT LSFT(RALT(KC_DQT))
#define ALT_SQT RALT(KC_QUOT)
#define ALT_SPC LALT_T(KC_SPC)

enum layers {
    _COLEMAK_DH = 0,
    _GAMING,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,

};
enum custom_keycodes {
    ARROW = SAFE_RANGE,
    ARROW_EQL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer: Colemak DH
     *
     * ,----------------------------------.                              ,----------------------------------.
     * |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |
     * |------+------+------+------+------|                              |------+------+------+------+------|
     * |   A  |alt(R)|sft(S)|ctl(T)|   G  |                              |   M  |ctl(N)|sft(E)|alt(I)|GUI(O)|
     * |------+------+------+------+------|                              |------+------+------+------+------|
     * |GUI(Z)  |   X  |   C  |   D  | V  |                              |   K  |   H  | ,  < | . >  | /  ? |
     * `--------------------+------+------|                              |------+------+------+------+------'
     *                      |  Sym |Space |                              | Enter|  Nav |
     *                      `-------------'                              `-------------'
     */
    [_COLEMAK_DH] = LAYOUT(KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_A, LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G, KC_M, RCTL_T(KC_N), RSFT_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O), LGUI_T(KC_Z), KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, SYM, ALT_SPC, KC_ENT, NAV),
    /*
     * Gaming: Gaming layer
     *
     * ,----------------------------------.                              ,----------------------------------.
     * |  TAB |   Q  |   W  |   E  |   R  |                              |   T  |   Y  |   U  |   I  |  O   |
     * |------+------+------+------+------|                              |------+------+------+------+------|
     * | SHIFT|   A  |   S  |   D  |   F  |                              |   G  |   H  |   J  |   K  |  L   |
     * |------+------+------+------+------|                              |------+------+------+------+------|
     * | CTRL |   Z  |   X  |   C  |   V  |                              |   B  |   N  |   M  | , <  | . >  |
     * `--------------------+------+------|                              |------+------+------+------+------'
     *                      |   /  |Space |                              | Enter|  Nav |
     *                      `-------------'                              `-------------'
     */
    [_GAMING] = LAYOUT(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_SPC, KC_ENT, NAV),
    /*
     * Nav/Num Layer: Numbers, navigation
     *
     * ,----------------------------------.                              ,----------------------------------.
     * |   1  |   2  |  3   |  4   |  5   |                              |   6  |   7  |   8  |   9  |  0   |
     * |------+------+------+------+------|                              |------+------+------+------+------|
     * |  GUI |  Alt | Shift| CTRL |      |                              | PgUp |  ←   |   ↓  |  ↑   |  →   |
     * |------+------+------+------+------|                              |------+------+------+------+------|
     * |      | CUT  | COPY | UNDO | PASTE|                              | PgDn | Home |  End |Insert|Delete|
     * `--------------------+------+------|                              |------+------+------+------+------'
     *                      |Fkeys |Space |                              | Enter|      |
     *                      `-------------'                              `-------------'
     */
    [_NAV] = LAYOUT(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______, KC_PGUP, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, CUT, COPY, UNDO, PASTE, KC_PGDN, KC_HOME, KC_END, KC_INS, KC_DEL, FKEYS, KC_TRNS, KC_TRNS, _______),
    /*
     * Sym Layer: Symbols
     *
     * ,----------------------------------.                                ,-----------------------------------.
     * |   !    |   @  |   #  |   $  |   %  |                              |   ^  |   [  |   ]  |   &  |   *   |
     * |--------+------+------+------+------|                              |------+------+------+------+-------|
     * |GUI(tab)|  alt |   "  |   '  |   |  |                              |   _  |   {  |   }  |   =  |Backspc|
     * |--------+------+------+------+------|                              |------+------+------+------+-------|
     * |   ESC  |   ~  |   `  |   |  |   \  |                              |   -  |   (  |   )  |   +  | Delete|
     * `----------------------+------+------|                              |------+------+------+------+-------'
     *                        |      |  GUI |                              | Enter| Fkeys|
     *                        `-------------'                              `-------------'
     */
    [_SYM] = LAYOUT(KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_AMPR, KC_ASTR, LGUI_T(KC_TAB), KC_LALT, SFT_QT, ALT_SQT, KC_PIPE, KC_UNDS, KC_LCBR, KC_RCBR, KC_EQL, LALT_T(KC_BSPC), KC_ESC, KC_TILD, KC_GRV, KC_PIPE, KC_BSLS, KC_MINS, KC_LPRN, KC_RPRN, KC_PPLS, KC_DEL, _______, KC_LGUI, KC_TRNS, FKEYS),
    /*
     * Function/media Layer: Function/media keys
     *
     * ,----------------------------------.                              ,-----------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |                              |   F6  |  F7  |  F8  |  F9  | F10  |
     * |------+------+------+------+------|                              |-------+------+------+------+------|
     * |  GUI | Alt  |Shift | Ctrl |RGBTOG|                              |Gaming | Ctrl |Shift |  Alt | F11  |
     * |------+------+------+------+------|                              |-------+------+------+------+------|
     * |Prtscr|      |      |      |Adjust|                              |Colemak|Vol Up|Vol DN| Mute | F12  |
     * `--------------------+------+------|                              |------+------+------+------+-------'
     *                      |      |      |                              |      |      |
     *                      `-------------'                              `-------------'
     */
    [_FUNCTION] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, RGB_TOG, GAMING, KC_LCTL, KC_LSFT, KC_LALT, KC_F11, KC_PSCR, _______, _______, _______, ADJUST, COLEMAK, KC_VOLU, KC_VOLD, KC_MUTE, KC_F12, _______, _______, _______, _______),
    /*
     * Adjust Layer: Default layer settings, RGB
     *
     * ,----------------------------------.                              ,----------------------------------.
     * |      |      |QWERTY|      |      |                              |      |      |      |      |      |
     * |------+------+------+------+------|                              |------+------+------+------+------|
     * |      |      |      |      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |
     * |------+------+------+------+------|                              |------+------+------+------+------|
     * |      |      |Colmak|      |      |                              |      | SAD  | HUD  | VAD  | RMOD |
     * `--------------------+------+------|                              |------+------+------+------+------'
     *                      |      |      |                              |      |      |
     *                      `-------------'                              `-------------'
     */
    [_ADJUST] = LAYOUT(_______, _______, GAMING, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD, _______, _______, COLEMAK, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______, _______, _______, _______),
};

const uint16_t PROGMEM backspace_combo[] = {RCTL_T(KC_N), RSFT_T(KC_E), COMBO_END};
const uint16_t PROGMEM esc_combo[]       = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM tab_combo[]       = {LALT_T(KC_R), LSFT_T(KC_S), COMBO_END};
const uint16_t PROGMEM del_combo[]       = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM a_combo[]         = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM ae_combo[]        = {RSFT_T(KC_E), LALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM oe_combo[]        = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM lprn_combo[]      = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM lcbr_combo[]      = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM rprn_combo[]      = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM rcbr_combo[]      = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM under_combo[]     = {KC_M, KC_K, COMBO_END};
const uint16_t PROGMEM arrow_combo[]     = {LCTL_T(KC_T), KC_G, COMBO_END};
const uint16_t PROGMEM arroweql_combo[]  = {KC_P, KC_B, COMBO_END};
const uint16_t PROGMEM back_to_colemak[] = {KC_ENT, KC_SPC, COMBO_END};
combo_t                key_combos[]      = {
    COMBO(backspace_combo, KC_BSPC), COMBO(esc_combo, KC_ESC), COMBO(tab_combo, KC_TAB), COMBO(del_combo, KC_DEL), COMBO(ae_combo, RALT(KC_Q)), COMBO(oe_combo, RALT(KC_P)), COMBO(a_combo, RALT(KC_W)), COMBO(lprn_combo, KC_LPRN), COMBO(lcbr_combo, KC_LCBR), COMBO(rprn_combo, KC_RPRN), COMBO(rcbr_combo, KC_RCBR), COMBO(under_combo, KC_UNDS), COMBO(arrow_combo, ARROW), COMBO(arroweql_combo, ARROW_EQL), COMBO(back_to_colemak, COLEMAK),
};
void keyboard_pre_init_user(void) {
    // Set our LED pin as output
    setPinOutput(24);
    // Turn the LED off
    // (Due to technical reasons, high is off and low is on)
    writePinHigh(24);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ARROW:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            break;

        case ARROW_EQL:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            break;
    }
    return true;
};
