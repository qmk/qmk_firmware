#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

#define DVORAK 0
#define ARROW 1 //F(1)
#define SYMBOL 2 // F(2)
#define NUMBER 3 // F(3)
#define FUNCTION 4 // F(4)
#define EMACS 5 // F(5)
#define CUSTOM_MACROS 6 // F(6)
#define MOUSE 7 // F(7)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DVORAK] = {
    {KC_ESC,  KC_QUOTE,  F(7),  KC_DOT,  KC_P,  KC_Y,  KC_F,  KC_G,  KC_C,  KC_R,  KC_L,  KC_DELETE},
    {KC_TAB,  F(1),  F(2),  F(3),  F(4),  KC_I,  KC_D,  KC_H,  KC_T,  KC_N,  KC_S,  KC_ENTER},
    {KC_LSHIFT,  KC_SCOLON,  F(5),   KC_J,   KC_K,  KC_X,   KC_B,   KC_M,   KC_W,  KC_V,  KC_Z,  KC_MINUS},
    {F(10), F(6),  KC_MENU, KC_LALT,  KC_LGUI,  KC_BSPACE,  KC_SPACE,  KC_RCTRL,  KC_LEFT,  KC_DOWN,  KC_UP, KC_RIGHT},
  },

  [ARROW] = {
    {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,  KC_UP,  KC_END,  KC_PGUP},
    {KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_PGDN},
    {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,  KC_NO},
    {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO}
  },

  [SYMBOL] = {
    {KC_TILD,  KC_GRAVE,  KC_NO,  KC_EQUAL,  KC_PLUS,  KC_NO,  KC_LBRACKET,  KC_RBRACKET,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN},
    {KC_NO,  KC_NO,  KC_TRNS,  KC_SCOLON,  KC_COLN,  KC_NO,  KC_LCBR,  KC_RCBR,  KC_DLR,  KC_PERC,  KC_CIRC,  F(21)},
    {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_BSLASH,  KC_SLASH,  KC_EXLM,  KC_AT,  KC_HASH,  KC_PIPE},
    {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_ASTR,   KC_SLASH,  KC_MINUS,  KC_PLUS,  KC_EQUAL}
  },

  [NUMBER] = {
    {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_7,  KC_8,  KC_9,  KC_NO},
    {KC_NO,  KC_NO,  KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_4,  KC_5,  KC_6,  KC_NO},
    {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_0,  KC_1,  KC_2,  KC_3,  KC_NO},
    {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_ASTR,  KC_SLASH,  KC_MINUS,  KC_PLUS,  KC_EQUAL}
  },

  [FUNCTION] = {
    {KC_PSCREEN,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6},
     {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS,  KC_NO,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12},
     {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,  KC_MEDIA_PLAY_PAUSE},
     {RESET,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_DELETE,  KC_INSERT,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END}
    },

    [EMACS] = {
      {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO},
      {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO},
      {KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO},
      {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO}
    },

    [CUSTOM_MACROS] = {
      {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO},
      {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO},
      {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO},
      {KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO}
    },

    [MOUSE] = {
      {KC_NO,  KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_U,  KC_NO,  KC_NO},
      {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_NO},
      {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO},
      {KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_BTN1,  KC_MS_BTN2,  KC_MS_BTN3,  KC_NO,  KC_NO,  KC_NO}
    },

  };

  enum function_id {
    TEENSY_KEY,
    CUSTOM_KEY,
    L_CTRL_ALT_ENT,
    R_CTRL_ALT_ENT,
  };

  int CAPSLOCKED = 0;

  const uint16_t PROGMEM fn_actions[] = {

    // DVORAK 0
    // ARROW 1, F(1)
    // SYMBOL 2, F(2)
    // NUMBER 3, F(3)
    // FUNCTION 4, F(4)
    // EMACS 5, F(5)
    // MACROS 6, F(6)
    // MOUSE 7, F(7)

    // Layers
    [1] =  ACTION_LAYER_TAP_KEY(1, KC_A),     // FN1 = Momentary Arrow layer on A.
    [2] =  ACTION_LAYER_TAP_KEY(2, KC_O),     // FN2 = Momentary symbOl layer on O.
    [3] =  ACTION_LAYER_TAP_KEY(3, KC_E),     // FN3 = Momentary numbEr layer on E.
    [4] =  ACTION_LAYER_TAP_KEY(4, KC_U),     // FN4 = Momentary fUnction layer on U.
    [5] =  ACTION_LAYER_TAP_KEY(5, KC_Q),     // FN5 = Momentary emaQs layer on Q.
    [6] =  ACTION_LAYER_TAP_KEY(6, KC_LCTRL), // FN6 = Momentary MACROS on ??? key.
    [7] =  ACTION_LAYER_TAP_KEY(7, KC_COMMA), // FN7 = Momentary MOUSE on , key.

    // Special Keys
    [10] =  ACTION_MODS_KEY(KC_LCTRL, KC_LALT), // FN10 = Ctrl + Alt.

    // Symbols
    [21] =  ACTION_MODS_KEY(MOD_LSFT, KC_SLASH), // FN21 = Question mark.

  };
