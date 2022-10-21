# PHSC138's Layout for the atom47
## Layers
<!-- TODO: pictures -->
```c
// Tap pn for toggle to _PROG, or hold for numpad
[_BASE] = LAYOUT_split_space(
    KC_GESC,  KC_Q,     KC_W,     KC_E,        KC_R,        KC_T,       KC_Y,    KC_U,      KC_I,    KC_O,       KC_P,     KC_DEL,   KC_BSPC,
    KC_TAB,   KC_A,     KC_S,     KC_D,        KC_F,        KC_G,       KC_H,    KC_J,      KC_K,    KC_L,       KC_SCLN,            KC_ENT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,        KC_V,        KC_B,       KC_N,    KC_M,      KC_COMM, KC_DOT,     KC_RSFT,            MO(_FN1),
    KC_LCTL,  KC_LGUI,  KC_LALT,  TD(PN_SWAP),              KC_SPC,              KC_SPC,             MO(_FN),    KC_RALT,  KC_APP,   KC_RCTRL),
```


```c
// LEFT AND RIGHT SHIFT: '(' and ')' when tapped, shift when held
// LEFT AND RIGHT CTRL: '{' and '}' when tapped, ctrl when held
// LEFT AND RIGHT ALT: '[' and ']' when tapped, ctrl when held
[_PROG] = LAYOUT_split_space(
    _______,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    _______,   _______, _______,
    _______,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    _______,            _______,
    KC_LSPO,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    KC_RSPC,            _______,
    TD(LCPO), _______,  TD(LAPO), TO(_GAME),                _______,             _______,            _______,    TD(RAPC),  _______, TD(RCPC)),
```


```c
// Macro for right space is bhop
// Maco for 'fn' is move forward
// Macro for 'fn1' is spin constantly
// Macro for right shift is D20
[_GAME] = LAYOUT_split_space(
    _______,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    _______,   _______, _______,
    _______,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    _______,            _______,
    _______,  _______,  _______,  _______,     _______,     _______,    _______, _______,   _______, _______,    TD(D20),            XXXXXXX,
    _______,  _______,  _______,  TO(_BASE),                _______,             XXXXXXX,            XXXXXXX,    _______,   XXXXXXX, _______),
```


```c
[_FN] = LAYOUT_split_space(
    _______,  KC_VOLD,  KC_VOLU,  KC_MUTE,     RESET,       _______,    KC_CALC, KC_PGUP,   _______, KC_PGDN,    KC_PSCR,   KC_SLCK,  KC_PAUS,
    KC_CAPS,  KC_MPRV,  KC_MPLY,  KC_MNXT,     _______,     _______,    KC_LEFT, KC_DOWN,   KC_UP,   KC_RIGHT,   KC_INS,              _______,
    _______,  _______,  _______,  _______,     _______,     KC_HOME,    KC_END,  BL_TOGG,   BL_DEC,  BL_INC,     _______,             _______,
    _______,  _______,  _______,  _______,                  _______,             _______,            _______,    _______,   _______,  _______),
```


```c
[_FN1] = LAYOUT_split_space(
    KC_GRV,   KC_F1,    KC_F2,    KC_F3,       KC_F4,       KC_F5,      KC_F6,   KC_F7,     KC_F8,   KC_F9,      KC_F10,    KC_F11,   KC_F12,
    KC_1,     KC_2,     KC_3,     KC_4,        KC_5,        KC_6,       KC_7,    KC_8,      KC_9,    KC_0,       KC_MINS,             KC_EQL,
    _______,  _______,  _______,  _______,     _______,     KC_QUOT,    KC_SLSH, KC_LBRC,   KC_RBRC, KC_BSLS,    KC_RSFT,             _______,
    _______,  _______,  _______,  _______,     _______,     _______,             _______,            _______,    _______,             _______),
```


```c
[_NUM] = LAYOUT_split_space(
    _______,  _______,  _______,  _______,     _______,     _______,    KC_7,    KC_8,      KC_9,    _______,    PROF_MAC,  _______,  _______,
    _______,  _______,  _______,  _______,     _______,     _______,    KC_4,    KC_5,      KC_6,    _______,    _______,             _______,
    _______,  _______,  _______,  _______,     _______,     KC_1,       KC_2,    KC_3,      KC_DOT,  _______,    _______,             _______,
    _______,  _______,  _______,  _______,     _______,     KC_0,                 _______,           _______,    DEBUG,               RESET),
```
