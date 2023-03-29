# The center sprit (as known as treadstone/stonehenge style staggered like keymap)

See [stonehenge30](https://github.com/marksard/qmk_firmware/tree/my_customize/keyboards/stonehenge30)  

A Nomu30 can use full color LED strip used by B5 pin. This keymap can use LED animation option.  

## Keymap Description

- KC_SLSF ...... / key is one tap, Shift key is long push.
- KC_Z_CT ...... Z key is one tap, Ctrl key is long tap.
- KC_X_AL ...... X key is one tap, Alt key is long tap.
- KC_C_GU ...... C key is one tap, GUI key is long tap.
- KC_M_CT ...... M key is one tap, Ctrl key is long tap.
- KC_ENSF ...... Enter key is one tap, Ctrl key is long tap.
- KC_CODO ...... , key is one tap, . key is double tap.
- KC_BSLO ...... Backspace key is one tap, Move to Lower layer with long push.
- KC_SPRA ...... Space key is one tap, Move to Raise layer with.
- AG_NORM ...... If you use Mac set to mode.
- AG_SWAP ...... If you use Win set to mode.
- KANJI ...... Japanese IME toggle key.

## How to move to Ajdust Layer

At first, Move to Lower layer with long push. After that Adjust key with long push. Now you have into Adjust layer state.

```c

  [_BASE] = LAYOUT(
  //,-------------------------------------------------------------------------------------------------------------.
          KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,  KC_BSLO,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_SLSF,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,  KC_ENSF,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_Z_CT,  KC_X_AL,  KC_C_GU,     KC_V,     KC_B,  KC_SPRA,     KC_N,  KC_M_CT,  KC_CODO
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------'
  ),

  [_LOWER] = LAYOUT(
  //,-------------------------------------------------------------------------------------------------------------.
         KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,  _______,  KC_MINS,   KC_EQL,  KC_INT3,  KC_LBRC,  KC_RBRC,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       _______,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,  XXXXXXX,  XXXXXXX,  KC_SCLN,  KC_QUOT,  KC_BSSF,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_11CT,  KC_12AL,   KC_ESC,   KC_TAB,    KANJI,  KC_MLAD,  XXXXXXX,  KC_COMM,   KC_DOT
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------'
  ),

  [_RAISE] = LAYOUT(
  //,-------------------------------------------------------------------------------------------------------------.
          KC_1,     KC_2,     KC_3,     KC_4,     KC_5,  _______,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,  KC_LSFT,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_LCTL,  KC_LALT,  KC_LGUI,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  KC_SLSH,  KC_INT1
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------'
  ),

  [_ADJUST] = LAYOUT(
  //,-------------------------------------------------------------------------------------------------------------.
         QK_BOOT, RGBRST,  AG_NORM,  AG_SWAP,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       _______,  RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  XXXXXXX,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  _______,  KC_BTN1,  KC_BTN2,  XXXXXXX
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------'
  )

```
