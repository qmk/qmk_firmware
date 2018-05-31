#include QMK_KEYBOARD_H


extern keymap_config_t keymap_config;

#define _DVORAK 0
#define _ARROW 1 //F(1)
#define _SYMBOL 2 // F(2)
#define _NUMBER 3 // F(3)
#define _FUNCTION 4 // F(4)
#define _EMACS 5 // F(5)
#define _COMBOS 6 // F(6)
#define _MOUSE 7 // F(7)

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  ARROW,
  SYMBOL,
  NUMBER,
  FUNCTION,
  EMACS,
  COMBOS,
  MOUSE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] = LAYOUT( \
  KC_ESC,  KC_QUOTE,  LT(7, KC_COMMA),  KC_DOT,  KC_P,  KC_Y,  KC_F,  KC_G,  KC_C,  KC_R,  KC_L,  KC_DELETE, \
  KC_TAB,  LT(1, KC_A),  LT(2, KC_O),  LT(3, KC_E),  LT(4, KC_U),  KC_I,  KC_D,  KC_H,  KC_T,  KC_N,  KC_S,  KC_ENTER, \
  KC_LSHIFT,  KC_SCOLON,  LT(5, KC_Q),   KC_J,   KC_K,  KC_X,   KC_B,   KC_M,   KC_W,  KC_V,  KC_Z,  KC_MINUS, \
  F(1), LT(6, KC_LCTRL),  KC_MENU, KC_LALT,  KC_LGUI,  KC_BSPACE,  KC_SPACE,  KC_RCTRL,  KC_LEFT,  KC_DOWN,  KC_UP, KC_RIGHT \
),

[_ARROW] = LAYOUT( \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,  KC_UP,  KC_END,  KC_PGUP, \
  KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_PGDN, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,  KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO \
),

[_SYMBOL] = LAYOUT( \
  KC_TILD,  KC_GRAVE,  KC_NO,  KC_EQUAL,  KC_PLUS,  KC_NO,  KC_LBRACKET,  KC_RBRACKET,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN, \
  KC_NO,  KC_NO,  KC_TRNS,  KC_SCOLON,  KC_COLN,  KC_NO,  KC_LCBR,  KC_RCBR,  KC_DLR,  KC_PERC,  KC_CIRC,  F(2), \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_BSLASH,  KC_SLASH,  KC_EXLM,  KC_AT,  KC_HASH,  KC_PIPE, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_ASTR,   KC_SLASH,  KC_MINUS,  KC_PLUS,  KC_EQUAL \
),

[_NUMBER] = LAYOUT( \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_7,  KC_8,  KC_9,  KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_4,  KC_5,  KC_6,  KC_NO, \
 KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_0,  KC_1,  KC_2,  KC_3,  KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_ASTR,  KC_SLASH,  KC_MINUS,  KC_PLUS,  KC_EQUAL \
),

[_FUNCTION] = LAYOUT( \
  KC_PSCREEN,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6, \
  KC_NO,  RGB_HUI,  RGB_SAI,  RGB_VAI,  KC_TRNS,  KC_NO,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12, \
  KC_NO,  RGB_HUD,  RGB_SAD,  RGB_VAD,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,  KC_MEDIA_PLAY_PAUSE, \
  RESET,  RGB_TOG,  RGB_MOD,  KC_NO,  KC_NO,  KC_NO,  KC_DELETE,  KC_INSERT,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END \
),

[_EMACS] = LAYOUT( \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, \
  KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO \
),

[_COMBOS] = LAYOUT( \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, \
  KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO \
),

[_MOUSE] = LAYOUT( \
  KC_NO,  KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_U,  KC_NO,  KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, \
  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_BTN1,  KC_MS_BTN2,  KC_MS_BTN3,  KC_NO,  KC_NO,  KC_NO \
)
};

enum function_id {
    TEENSY_KEY,
    CUSTOM_KEY,
    L_CTRL_ALT_ENT,
    R_CTRL_ALT_ENT,
};

int CAPSLOCKED = 0;

  const uint16_t PROGMEM fn_actions[] = {
    // Special Keys
    [1] =  ACTION_MODS_KEY(KC_LCTRL, KC_LALT), // FN10 = Ctrl + Alt.
    // Symbols
    [2] =  ACTION_MODS_KEY(MOD_LSFT, KC_SLASH), // FN21 = Question mark.
  };
