#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Hexboard Keyboard layout (landscape)
     *       ___   ___   ___
     *      ❬BnU ᚛-᚜OcU ᚛-᚜MiO❭__
     *   ❬BnD᚛-᚜OcD᚛-᚜Pnc᚛-᚜Pnc❭
     *    ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾ 
     *  ___   ___   ___   ___   ___   ___   ___
     * ❬F 5᚛-᚜Gb5᚛-᚜G 5᚛-᚜Ab5᚛-᚜A 5᚛-᚜Bb5᚛-᚜B 5❭__
     *  ᚛-᚜D 5᚛-᚜Eb5᚛-᚜E 5᚛-᚜F 5᚛-᚜Gb5᚛-᚜G 5᚛-᚜Ab5❭
     * ❬Bb4᚛-᚜B 4᚛-᚜C 5᚛-᚜Db5᚛-᚜D 5᚛-᚜Eb5᚛-᚜E 5᚛-᚜
     *  ᚛-᚜G 4᚛-᚜Ab4᚛-᚜A 4᚛-᚜Bb4᚛-᚜B 4᚛-᚜C 5᚛-᚜Db5❭
     * ❬Eb4᚛-᚜E 4᚛-᚜F 4᚛-᚜Gb4᚛-᚜G 4᚛-᚜Ab4᚛-᚜A 4᚛-᚜
     *  ᚛-᚜C 4᚛-᚜Db4᚛-᚜D 4᚛-᚜Eb4᚛-᚜E 4᚛-᚜F 4᚛-᚜Gb4❭
     * ❬Ab3᚛-᚜A 3᚛-᚜Bb3᚛-᚜B 3᚛-᚜C 4᚛-᚜Db4᚛-᚜D 4᚛-᚜
     *  ᚛-᚜F 3᚛-᚜Gb3᚛-᚜G 3᚛-᚜Ab3᚛-᚜A 3᚛-᚜Bb3᚛-᚜B 3❭
     * ❬Db3᚛-᚜D 3᚛-᚜Eb3᚛-᚜E 3᚛-᚜F 3᚛-᚜Gb3᚛-᚜G 3᚛-᚜
     *  ᚛-᚜   ᚛-᚜ E ᚛-᚜   ᚛-᚜   ᚛-᚜ I ᚛-᚜   ᚛-᚜   ❭
     * ❬TAB᚛-᚜ W ᚛-᚜ R ᚛-᚜   ᚛-᚜ U ᚛-᚜ O ᚛-᚜⌫  ᚛-᚜
     *  ᚛-᚜ Q ᚛-᚜ D ᚛-᚜ T ᚛-᚜ Y ᚛-᚜ K ᚛-᚜ P ᚛-᚜   ❭
     * ❬Esc᚛-᚜ S ᚛-᚜ F ᚛-᚜   ᚛-᚜ J ᚛-᚜ L ᚛-᚜ ' ᚛-᚜
     *  ᚛-᚜ A ᚛-᚜ C ᚛-᚜ G ᚛-᚜ H ᚛-᚜ , ᚛-᚜ ; ᚛-᚜   ❭
     * ❬sft᚛-᚜ X ᚛-᚜ V ᚛-᚜   ᚛-᚜ M ᚛-᚜ . ᚛-᚜ ⏎ ᚛-᚜
     *  ᚛-᚜ Z ᚛-᚜   ᚛-᚜ B ᚛-᚜ N ᚛-᚜ 🡐 ᚛-᚜ / ᚛-᚜   ❭
     * ❬   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ 🡓 ᚛-᚜   ᚛-᚜
     *  ᚛-᚜Ctl᚛-᚜Sup᚛-᚜   ᚛-᚜   ᚛-᚜ 🡐 ᚛-᚜ 🡑 ᚛-᚜ ⏎ ❭
     * ❬   ᚛-᚜Alt᚛-᚜lyr᚛-᚜   ᚛-᚜LYR᚛-᚜ 🡓 ᚛-᚜ 🡒 ❭‾‾
     *  ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾ 
     */
    [0] = LAYOUT_landscape(
                MI_BNDU,MI_OCTU,  RGB_HUI,
          MI_BNDD,MI_OCTD,  RGB_VAD,   RGB_MOD,


MI_F5, MI_Gb5, MI_G5,   MI_Ab5,  MI_A5,  MI_Bb5, MI_B5,
    MI_D5, MI_Eb5,  MI_E5,   MI_F5,   MI_Gb5, MI_G5, MI_Ab5,
MI_Bb4,MI_B4,  MI_C5,   MI_Db5,  MI_D5,  MI_Eb5, MI_E5,
    MI_G4, MI_Ab4,  MI_A4,   MI_Bb4,  MI_B4,  MI_C5, MI_Db5,
MI_Eb4,MI_E4,  MI_F4,   MI_Gb4,  MI_G4,  MI_Ab4, MI_A4,
    MI_C4, MI_Db4,  MI_D4,   MI_Eb4,  MI_E4,  MI_F4, MI_Gb4,
MI_Ab3,MI_A3,  MI_Bb3,  MI_B3,  MI_C4,   MI_Db4, MI_D4,
    MI_F3, MI_Gb3,  MI_G3,   MI_Ab3,  MI_A3,  MI_Bb3,MI_B3,
MI_Db3,MI_D3,  MI_Eb3,  MI_E3,  MI_F3,   MI_Gb3, MI_G3,
    _______,KC_E,     _______,  _______,  KC_I,    _______,_______,
KC_TAB, KC_W,    KC_R,  _______,    KC_U,     KC_O,   KC_BSPC,
    KC_Q,   KC_D,    KC_T,     KC_Y,     KC_K,    KC_P,   _______,
KC_ESC, KC_S,    KC_F,  _______,     KC_J,     KC_L,   KC_QUOT,
    KC_A,   KC_C,     KC_G,    KC_H,     KC_COMM, KC_SCLN,_______,
KC_LSFT,KC_X,    KC_V,   _______,   KC_M,     KC_DOT,  KC_ENT, 
    KC_Z,  _______,  KC_B,     KC_N,     KC_LEFT, KC_SLSH,_______,
_______,_______, _______, _______,  _______,  KC_DOWN, _______,
    KC_LCTL,KC_LGUI, _______, _______,   KC_LEFT,   KC_UP,KC_ENT,
_______,KC_LALT, MO(1),    KC_SPC,  MO(2),    KC_DOWN,   KC_RGHT
    ),


    // "lower"
		/**
		 *  ... top rows fall through to other layer.
		 *     ___   ___   ___   ___   ___   ___   ___
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ + ᚛-᚜   ᚛-᚜   ❭
     * ❬ ~ ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ _ ᚛-᚜ { ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜ # ᚛-᚜   ᚛-᚜   ᚛-᚜ * ᚛-᚜ } ᚛-᚜   ❭
     * ❬ ⌦ ᚛-᚜ @ ᚛-᚜ $ ᚛-᚜   ᚛-᚜ & ᚛-᚜ ( ᚛-᚜ | ᚛-᚜
     *  ᚛-᚜ ! ᚛-᚜   ᚛-᚜ % ᚛-᚜ ^ ᚛-᚜   ᚛-᚜ ) ᚛-᚜   ❭
     * ❬sft᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ ⇱ ᚛-᚜   ᚛-᚜   ❭
     * ❬   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ ⇓ ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ ⇱ ᚛-᚜ ⇑ ᚛-᚜   ❭
     * ❬   ᚛-᚜   ᚛-᚜lyr᚛-᚜   ᚛-᚜LYR᚛-᚜ ⇓ ᚛-᚜ ⇲ ❭‾‾
     *  ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾ 
     */

    [1] = LAYOUT_landscape(
                MI_BNDU,MI_OCTU,  RGB_M_SN,
          MI_BNDD,MI_OCTD,  RGB_M_B,RGB_M_SW,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,KC_PLUS,_______,_______,
KC_TILD,_______,_______,_______,KC_UNDS,KC_LCBR,_______,
    _______,KC_HASH,_______,_______,KC_ASTR,KC_RCBR,_______,
KC_DEL, KC_AT,  KC_DLR,_______, KC_AMPR,KC_LPRN,KC_PIPE,
    KC_EXLM,_______,KC_PERC,KC_CIRC,_______,KC_RPRN,_______,
KC_LSFT,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,KC_HOME,_______,_______,
_______,_______,_______,_______,_______,KC_PGDN,_______,
    _______,_______,_______,_______,KC_HOME,KC_PGUP,_______,
_______,_______,_______,_______,_______,KC_PGDN,KC_END
    ),
    // "raise"
		/**
		 *  ... top rows fall through to other layer.
		 *     ___   ___   ___   ___   ___   ___   ___
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ = ᚛-᚜   ᚛-᚜   ❭
     * ❬ ~ ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ _ ᚛-᚜ [ ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜ 3 ᚛-᚜   ᚛-᚜   ᚛-᚜ 8 ᚛-᚜ ] ᚛-᚜   ❭
     * ❬ ⌦ ᚛-᚜ 2 ᚛-᚜ 4 ᚛-᚜   ᚛-᚜ 7 ᚛-᚜ 9 ᚛-᚜ \ ᚛-᚜
     *  ᚛-᚜ 1 ᚛-᚜   ᚛-᚜ 5 ᚛-᚜ 6 ᚛-᚜   ᚛-᚜ 0 ᚛-᚜   ❭
     * ❬sft᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ ⇱ ᚛-᚜   ᚛-᚜   ❭
     * ❬   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ ⇓ ᚛-᚜   ᚛-᚜
     *  ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜   ᚛-᚜ ⇱ ᚛-᚜ ⇑ ᚛-᚜   ❭
     * ❬   ᚛-᚜   ᚛-᚜lyr᚛-᚜   ᚛-᚜LYR᚛-᚜ ⇓ ᚛-᚜ ⇲ ❭‾‾
     *  ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾   ‾‾‾ 
     */
    [2] = LAYOUT_landscape(
                MI_BNDU,MI_OCTU,  RGB_HUI,
          MI_BNDD,MI_OCTD,  RGB_VAD,RGB_MOD,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,
_______,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,KC_EQL ,_______,_______,
KC_GRV ,_______,_______,_______,KC_MINS,KC_LBRC,_______,
    _______, KC_3  ,_______,_______, KC_8  ,KC_RBRC,_______,
KC_DEL , KC_2  , KC_4  ,_______, KC_7  , KC_9  ,KC_BSLS,
     KC_1  ,_______, KC_5  , KC_6  ,_______, KC_0  ,_______,
KC_LSFT,_______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,KC_HOME,KC_SLSH,_______,
_______,_______,_______,_______,_______,KC_PGDN,_______,
    _______,_______,_______,_______,KC_HOME,KC_PGUP,_______,
_______,_______,_______,_______,_______,KC_PGDN,KC_END
    )


};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    
    return false;
}
#endif
