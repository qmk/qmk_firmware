#include QMK_KEYBOARD_H

// Define the keycodes for one qwerty layer and one Fn layer.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: qwerty
   * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬─────────────┐
   * │ ` Esc│   1  │   2  │   3  │   4  │   5  │   6  │   7  │   8  │   9  │   0  │  -   │  =   │ Bksp        │
   * ├─────────────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼─────┬───────┤
   * │ Tab         │   Q  │   W  │   E  │   R  │   T  │   Y  │   U  │   I  │   O  │   P  │  [   │  ]  │       │
   * ├─────────────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼─────┴┐ Enter│
   * │ Layer 2     │   A  │   S  │   D  │   F  │   G  │   H  │   J  │   K  │   L  │   ;  │   '  │   #  │      │
   * ├──────┬──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┤
   * │ Shift│  \   │   Z  │   X  │   C  │   V  │   B  │   N  │   M  │   ,  │   .  │   /  │        Shift       │
   * ├──────┼──────┼──────┼──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┼──────┬──────┬──────┤
   * │ Ctrl │ Alt  │ Gui  │                            Space                             │ Gui  │ Alt  │ Ctrl │
   * └──────┴──────┴──────┴──────────────────────────────────────────────────────────────┴──────┴──────┴──────┘
   *
   * Hidden features :
   *  - Left Shift is also Home on a single tap.
   *  - Left Ctrl is also End on a single tap.
   *  - Right Shift is also page-up on a single tap.
   *  - Right Ctrl is also page-down on a single tap.
   *  - Press JKLM for Windows + L (Session lock)
   */
  [0] = LAYOUT(
    KC_ESC , KC_1   , KC_2   , KC_3 , KC_4 , KC_5 , KC_6  , KC_7 , KC_8 , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,
    KC_TAB , KC_Q   , KC_W   , KC_E , KC_R , KC_T , KC_Y  , KC_U , KC_I , KC_O   , KC_P   , KC_LBRC, KC_RBRC,
    MO(1)  , KC_A   , KC_S   , KC_D , KC_F , KC_G , KC_H  , KC_J , KC_K , KC_L   , KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT ,
    SC_LSPO, KC_NUBS, KC_Z   , KC_X , KC_C , KC_V , KC_B  , KC_N , KC_M , KC_COMM, KC_DOT , KC_SLSH, SC_RSPC         ,
    SC_LCPO, KC_LALT, KC_LGUI,                      KC_SPC,                                 KC_RGUI, KC_RALT, SC_RCPC
  ),

  /* 1: second layer for media keys and many advanced features ç
   * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬─────────────┐
   * │Alt F4│  F1  │  F2  │  F3  │  F4  │  F5  │  F6  │  F7  │  F8  │  F9  │  F10 │  F11 │  F12 │             │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼─────┬───────┤
   * │      │      │      │      │      │      │Ctrl A│ Home │  Up  │  End │      │      │      │     │       │
   * ├─────────────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼─────┴┐      │
   * │             │ Cut  │ Copy │Paste │ Del  │ Del  │ Left │ Down │Right │      │      │      │      │      │
   * ├──────┬──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┴──────┴──────┤
   * │      │      │ Mute │ Vol- │ Vol+ │      │      │      │      │      │      │Reset │                    │
   * ├──────┼──────┼──────┼──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┼──────┬──────┬──────┤
   * │      │      │      │                                                              │      │      │      │
   * └──────┴──────┴──────┴──────────────────────────────────────────────────────────────┴──────┴──────┴──────┘
   */
  [1] = LAYOUT(
    LALT(KC_F4), KC_F1     , KC_F2       , KC_F3       , KC_F4       , KC_F5  , KC_F6     , KC_F7  , KC_F8  , KC_F9   , KC_F10     , KC_F11    , KC_F12    , _______,
    _______    , _______   , _______     , _______     , _______     , _______, LCTL(KC_A), KC_HOME, KC_UP  , KC_END  , _______    , _______   , _______   ,
    _______    , _______   , LSFT(KC_DEL), LCTL(KC_INS), LSFT(KC_INS), KC_DEL , KC_DEL    , KC_LEFT, KC_DOWN, KC_RIGHT, _______    , _______   , _______   , _______,
    _______    , _______   , KC_MUTE     , KC_VOLD     , KC_VOLU     , _______, _______   , _______, _______, _______ , _______    , QK_BOOT     , _______            ,
    _______    , _______   , _______     ,                             _______,                                                      _______   , _______   , _______
  )
};
