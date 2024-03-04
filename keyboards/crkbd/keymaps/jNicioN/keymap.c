#include "keycodes.h"
#include QMK_KEYBOARD_H

// qmk flash -kb crkbd/rev1 -km jNicioN

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
	[TD_CTRALT]     = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LALT),    // Funciona como ctrl si presionas una vez o como alt si la presionas dos veces
	[TD_MAYUS]      = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),     // Funciona como shift, si se presiona dos veces activa Bloqueo Mayusculas
	[TD_QUESAPE]    = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_EQUAL),   // Funciona como tecla de acento, si se presiona dos veces activa simbolo de inicio de pregunta
	[TD_MENMAY]     = ACTION_TAP_DANCE_DOUBLE(KC_LT, KC_GT)       // Funciona como tecla de menor que, si se presiona dos veces activa simbolo de mayor que
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
    │    ↹    │    Q    │    W    │    E    │    R    │    T    │                        │    Y    │    U    │    I    │    O    │    P    │    ⌫    │
    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    │   ⇧/⇪   │    A    │    S    │    D    │    F    │    G    │                        │    H    │    J    │    K    │    L    │    Ñ    │   ´/¿   │
    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    │    ⌘    │    Z    │    X    │    C    │    V    │    B    │                        │    N    │    N    │    ,    │    .    │    -    │    '    │
    └─────────┴─────────┴─────────┴─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
                                            │   ⌃/⌥   │  LT(1)  │  /LT(3) │    │         │ ↵/LT(2) │         │
                                            └─────────┴─────────┴─────────┘    └─────────┴─────────┴─────────┘
*/

    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_TAB,         KC_Q,       KC_W,       KC_E,               KC_R,               KC_T,                       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
        TD(TD_MAYUS),   KC_A,       KC_S,       KC_D,               KC_F,               KC_G,                       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    TD(TD_QUESAPE),
        KC_LGUI,        KC_Z,       KC_X,       KC_C,               KC_V,               KC_B,                       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLASH,   KC_MINUS,
                                                TD(TD_CTRALT),      MO(1),              LT(3,KC_SPACE),             KC_SPACE,   LT(2,KC_ENTER), KC_F17
    ),
/* NAV(1)
    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
    │   Esc   │    @    │ XXXXXXX │  M(R)   │  M(↑)   │  M(L)   │                        │   HOME  │    ↑    │   END   │ XXXXXXX │  ImpPnt │    ⌦    │
    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    │    ⇧    │ XXXXXXX │ XXXXXXX │  M(←)   │  M(↓)   │  M(→)   │                        │    ←    │    ↓    │    →    │    ⇧    │   F14   │  Insert │
    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    │    ⌃    │    ⌥    │    ⌘    │   copy  │  paste  │ XXXXXXX │                        │    ⌃    │    ⌥    │    ⌘    │ XXXXXXX │   F15   │ XXXXXXX │
    └─────────┴─────────┴─────────┴─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
                                            │    ⌘    │ _______ │         │    │  MO(4)  │ _______ │ _______ │
                                            └─────────┴─────────┴─────────┘    └─────────┴─────────┴─────────┘
*/
    [_NAV] = LAYOUT_split_3x6_3(
        KC_ESCAPE,      RALT(KC_Q), XXXXXXX,    KC_BTN1,            KC_MS_U,            KC_BTN2,                    KC_HOME,    KC_UP,      KC_END,     XXXXXXX,    KC_F13,    KC_DELETE,
        KC_LSFT,        XXXXXXX,    XXXXXXX,    KC_MS_L,            KC_MS_D,            KC_MS_R,                    KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_RSFT,    KC_F14,    KC_INSERT,
        KC_LCTL,        KC_LALT,    KC_LGUI,    LCTL(KC_INSERT),    LSFT(KC_INSERT),    XXXXXXX,                    KC_LCTL,    KC_LALT,    KC_LGUI,    XXXXXXX,    KC_F15,    XXXXXXX,
                                                KC_LGUI,            _______,            KC_SPC,                     MO(4),  _______,    _______
    ),
/* SYMBOL(2)
    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
    │    |    │    !    │    "    │    #    │    $    │    %    │                        │    &    │    /    │    (    │    )    │    =    │    ¿    │
    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    │   F1    │   F2    │   F3    │   F4    │   F5    │   F6    │                        │    @    │    \    │    {    │    }    │    ´    │    ←    │
    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    │   F7    │   F8    │   F9    │   F10   │   F11   │   F12   │                        │    ⇧    │    +    │    [    │    ]    │    `    │    <    │
    └─────────┴─────────┴─────────┴─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
                                            │    ⌃    │    ⌥    │    ⌘    │    │ _______ │ _______ │ _______ │
                                            └─────────┴─────────┴─────────┘    └─────────┴─────────┴─────────┘
*/
    [_SYMBOL] = LAYOUT_split_3x6_3(
        KC_GRAVE,   KC_EXLM,    KC_AT,  KC_HASH,    KC_DLR,     KC_PERC,                             KC_CIRC,       KC_AMPR,        KC_ASTR,        KC_LPRN,                KC_RPRN,                KC_EQUAL,
        KC_F1,      KC_F2,      KC_F3,  KC_F4,      KC_F5,      KC_F6,                               RALT(KC_Q),    RALT(KC_MINUS), KC_QUOTE,       KC_NONUS_HASH,          KC_LBRC,                KC_BSPC,
        KC_F7,      KC_F8,      KC_F9,  KC_F10,     KC_F11,     KC_F12,                              KC_LSFT,       KC_RBRC,         LSFT(KC_QUOTE), LSFT(KC_NONUS_HASH),    RALT(KC_NONUS_HASH),    KC_NUBS,
                                                    KC_LCTL,    KC_LALT,    KC_LGUI,      _______,   _______,       _______
    ),
/* _NUMPAD(3)
    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
    │    |    │ XXXXXXX │  Vol*   │  Vol-   │  Vol+   │   F17   │                        │    7    │    8    │    9    │    -    │    /    │    ←    │
    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    │ XXXXXXX │ XXXXXXX │  Prev   │  Play   │  Next   │   F18   │                        │    4    │    5    │    6    │    +    │    *    │    =    │
    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    │ XXXXXXX │ XXXXXXX │ XXXXXXX │ XXXXXXX │   App   │   F19   │                        │    1    │    2    │    3    │    .    │    <    │    >    │
    └─────────┴─────────┴─────────┴─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
                                            │         │ _______ │         │    │    ↵    │    0    │ NumLock │
                                            └─────────┴─────────┴─────────┘    └─────────┴─────────┴─────────┘
*/
    [_NUMPAD] = LAYOUT_split_3x6_3(
        XXXXXXX,          XXXXXXX,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_F18,                                 KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_KP_PLUS,     KC_KP_ASTERISK, LSFT(KC_0),
        LCA(KC_DELETE),   XXXXXXX,    KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_F17,                                 KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_KP_MINUS,    KC_KP_SLASH,    KC_BSPC,
        XXXXXXX,          XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_APP,     KC_F19,                                 KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_KP_DOT,      KC_NUBS,        LSFT(KC_NUBS),
                                                            _______,    _______,    _______,          KC_ENT,   KC_KP_0,    KC_NUM_LOCK
  ),
/* CONFIG(4)
    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                        ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
    │        │ XXXXXXX │  Vol*   │  Vol-   │  Vol+   │   F17   │                        │    7    │    8    │    9    │    -    │    /    │    ←    │
    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    │ XXXXXXX │ XXXXXXX │  Prev   │  Play   │  Next   │   F18   │                        │    4    │    5    │    6    │    +    │    *    │    =    │
    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                        ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    │ XXXXXXX │ XXXXXXX │ XXXXXXX │ XXXXXXX │   App   │   F19   │                        │    1    │    2    │    3    │    .    │    <    │    >    │
    └─────────┴─────────┴─────────┴─────────┼─────────┼─────────┼─────────┐    ┌─────────┼─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
                                            │         │ _______ │         │    │    ↵    │    0    │ NumLock │
                                            └─────────┴─────────┴─────────┘    └─────────┴─────────┴─────────┘
*/
    [_CONFIG] = LAYOUT_split_3x6_3(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_M_SN, RGB_M_B,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_M_K, RGB_M_R,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, _______
  )
};

#ifdef RGB_MATRIX_ENABLE
    void suspend_power_down_user(void){
        rgb_matrix_set_suspend_state(true);
    }

    void suspend_wake_init_user(void){
        rgb_matrix_set_suspend_state(false);
    }
#endif
