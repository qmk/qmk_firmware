#include QMK_KEYBOARD_H

/* Holds state of modifiers when Backspace was pressed.
 * Used to ensure that the correct keycode is unregistered when Backspace is released.
 */
static uint8_t bspc_mods = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
    * ,-----------------------------------------------------------------------------------------.
    * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
    * |-----------------------------------------------------------------------------------------+
    * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
    * |-----------------------------------------------------------------------------------------+
    * |   Fn    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
    * |-----------------------------------------------------------------------------------------+
    * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RSh |  U  | Ins |
    * |-----------------------------------------------------------------------------------------+
    * | Ctrl |  Win  |  Alt  |              Space                | Alt | Menu |  L  |  D  |  R  |
    * `-----------------------------------------------------------------------------------------'
    */
    LAYOUT_directional(
        KC_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , _______, KC_BSPC,
        KC_TAB ,          KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,
        MO(1)  ,          KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,
        KC_LSFT,          KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, KC_UP  , KC_INS ,
        KC_LCTL, KC_LGUI,          KC_LALT, KC_SPC ,          KC_SPC ,          KC_SPC ,          KC_RALT, KC_RGUI, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    /* FN Layer
    * ,-----------------------------------------------------------------------------------------.
    * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |    DEL    |
    * |-----------------------------------------------------------------------------------------+
    * |        |RBB T|RGB M| Hue+| Hue-| Sat+| Sat-| Val+| Val-|     |     |      |     |       |
    * |-----------------------------------------------------------------------------------------+
    * |         | BL T| BL M| BL+ | BL- |     |     |     |     |     |     |     |             |
    * |-----------------------------------------------------------------------------------------+
    * |           |     |     |     |     |RESET|     |     |     |     |     |     | PgUp|     |
    * |-----------------------------------------------------------------------------------------+
    * |      |       |       |                                   |     |      | Home| PgDn| End |
    * `-----------------------------------------------------------------------------------------'
    */
    LAYOUT_directional(
        KC_GRV , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, KC_DEL ,
        _______,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______,
        _______,          BL_TOGG, BL_STEP, BL_INC , BL_DEC , _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, RESET  , _______, _______, _______, _______, _______, _______, KC_PGUP, _______,
        _______, _______,          _______, _______,          _______,          _______,          _______, _______, KC_HOME, KC_PGDN, KC_END
        ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_BSPC: {
            if (record->event.pressed) {
                const uint8_t current_mods = get_mods();
                const uint8_t shift = current_mods & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
                const uint8_t ctrl = current_mods & (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL));
                bspc_mods = current_mods;
                if(shift || ctrl) {
                    add_key(KC_DEL);
                    add_mods(current_mods);
                    send_keyboard_report();
                } else {
                    return true;
                }
            }
            else {
                if(bspc_mods & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)|MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))) {
                    // if Shift or Ctrl was pressed with Backspace, than that was intepreted as Del, so we need
                    // to unregister the Del key 
                    del_key(KC_DEL);
                } else {
                    // Either Backspace was pressed without mods, or with a modifier other than Shift or Ctrl
                    // so it is simply taken as Backspace
                    del_key(KC_BSPC);
                }
                send_keyboard_report();
            }
            return false;
        }
        default:
            return true;
    }
}
