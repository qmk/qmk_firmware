#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    /* Colemak
     * ,-----------------------------------------------------------------------------------.
     * | Q    |   W  |   F  |   P  |   G  |  ESC |   DEL|   J  |   L  |   U  |   Y  | :    |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | A    |   R  |   S  |   T  |   D  |  TAB |RETURN|   H  |   N  |   E  | I    |  O   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Z    |   X  |   C  |   V  |   B  |   [  |   ]  |   K  |   M  |   ,  |   .  |   /  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |NO    | CAD  | GUI  | BSPC | LALT | MO1  | NO   | SHIFT| SPACE| NO   |  NO  | NO   |
     * `-----------------------------------------------------------------------------------'
     */
    
    [0] = LAYOUT_ortho_4x12(
        KC_Q, KC_W, KC_F, KC_P, KC_G, KC_GESC, KC_DEL,  KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, \
        KC_A, KC_R, KC_S, KC_T, KC_D, KC_TAB,  KC_ENT,  KC_H, KC_N, KC_E,    KC_I,   KC_O, \
        LSFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, \
        KC_LCTL, LCA(KC_DEL), KC_LGUI, LT(1,KC_BSPC), KC_LALT, TG(3), MO(2), KC_LSFT, KC_SPC, KC_NO, KC_NO, KC_NO),
    
    /* Numrow
     * ,-----------------------------------------------------------------------------------.
     * | 1    |   2  |   3  |   4  |   5  |  ESC |   DEL|   6  |   7  |   8  |   9  | 0    |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | F1   |  F2  |   F3 |   F4 |   F5 |  TAB |RETURN|      |      |      |  BSLS|   '  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |   -  |   =  |      |      |PGUP  |  UP  | PGDN |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      | Alt  | BSPC | GUI  | MO1  |      | SHIFT| SPACE| LEFT |  DWN |RIGHT |
     * `-----------------------------------------------------------------------------------'
     */
	[1] = LAYOUT_ortho_4x12(
        KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_TRNS, KC_TRNS, KC_6, KC_7, KC_8, KC_9, KC_0, \
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_CAPS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_BSLS, KC_QUOT, \
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_EQL, KC_NO, KC_NO, KC_PGDN, KC_UP, KC_PGUP, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),
    
    
    /* Media
    * ,-----------------------------------------------------------------------------------.
    * | NEXT |  Play|      |      |      |  ESC |   DEL|      |      |      |      |      |
    * |------+------+------+------+------+-------------+------+------+------+------+------|
    * |      |      |      |      |      |  TAB |RETURN|      |      |      |      |      |
    * |------+------+------+------+------+------|------+------+------+------+------+------|
    * |      |      |      |      |      |   -  |   =  |      |      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      | Alt  | BSPC | GUI  | TG3  |      | SHIFT| SPACE| LEFT |  DWN |RIGHT |
    * `-----------------------------------------------------------------------------------'
    */
    [2] = LAYOUT_ortho_4x12(
        KC_MNXT,  KC_MPLY,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_BSLS, KC_QUOT, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_EQL, KC_NO, KC_NO, KC_PGDN, KC_UP, KC_PGUP, \
        KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),
    
    /* Numpad
     * ,-----------------------------------------------------------------------------------.
     * | NEXT |  Play|   3  |   4  |   5  |  ESC |   DEL|   /  |   *  |   P7 |   P8 | P9   |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |  TAB |RETURN|      |   -  |  P4  |  P5  |  P6  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |   -  |   =  |      |    + |P1    |  P2  |  P3  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |  ALT | BSPC | GUI  | TG3  |      | SHIFT| SPACE| P0  |  PDOT |PENT  |
     * `-----------------------------------------------------------------------------------'
     */
    [3] = LAYOUT_ortho_4x12(
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS, KC_TRNS, KC_PSLS, KC_PAST, KC_P7, KC_P8, KC_P9, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_PMNS, KC_P4, KC_P5, KC_P6, \
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_EQL, KC_NO, KC_PPLS, KC_P1, KC_P2, KC_P3, \
        KC_NO, KC_NO, KC_TRNS, KC_BSPC, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_DOT, KC_PENT)
};
//Enable LED1 to indicate Caps Lock state
    void led_set_user(uint8_t usb_led){
        if(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)){
            writePinHigh(C5);
        } else {
            writePinLow(C5);
        }
};

//Enable LED2 to indicate layer state
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)){
        case 1:
            writePinHigh(C4);
            break;
        case 2:
            writePinHigh(C4);
            break;
        case 0:
            writePinLow(C4);
            break;
        case 3:
            writePinHigh(C4);
            break;
    }
    return state;
};
