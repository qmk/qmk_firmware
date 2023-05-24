# The LikeJIS is Japanese Keyboard like keymap

A Nomu30 can use full color LED strip used by B5 pin. This keymap can use LED animation option.

## Keymap Description

- KC_CMSF ...... , key is one tap, Shift key is long push.
- KC_DTCT ...... . key is one tap, Ctrl key is long tap.
- KC_ENSF ...... Enter key is one tap, Ctrl key is long tap.
- KC_Z_AL ...... Z key is one tap, Alt key is long tap.
- KC_X_GU ...... X key is one tap, GUI key is long tap.
- KC_BSLO ...... Backspace key is one tap, Move to Lower layer with long push.
- KC_SPRA ...... Space key is one tap, Move to Raise layer with.
- AG_NORM ...... If you use Mac set to mode.
- AG_SWAP ...... If you use Win set to mode.
- KANJI ...... Japanese IME toggle key.

## How to move to Ajdust Layer

At first, Move to Lower layer with long push. After that Adjust key with long push. Now you have into Adjust layer state.

```c

  [_BASE] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------------------.
                    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_BSLO,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_CMSF,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,  KC_ENSF,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       KC_DTCT,  KC_Z_AL,  KC_X_GU,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,  KC_SPRA
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------'
  ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------------------.
                   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,  KC_MINS,   KC_EQL,  KC_JYEN,  KC_LBRC,  KC_RBRC,  _______,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       _______,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,  XXXXXXX,  XXXXXXX,  KC_SCLN,  KC_QUOT,  KC_BSSF,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       _______,  KC_11AL,   KC_F12,   KC_ESC,   KC_TAB,    KANJI,  KC_COMM,   KC_DOT,  KC_MLAD
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------------------.
                    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,   KC_DEL,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,  KC_LSFT,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       _______,  KC_LALT,  KC_LGUI,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_SLSH,    KC_RO,  _______
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------'
  ),

  [_ADJUST] = LAYOUT(
  //,-----------------------------------------------------------------------------------------------------------------------.
                   RESET,   RGBRST,  AG_NORM,  AG_SWAP,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       _______,  RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  XXXXXXX,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
       _______,  RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  KC_BTN1,  KC_BTN2,  XXXXXXX
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------'
  )

```
