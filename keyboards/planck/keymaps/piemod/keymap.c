#include QMK_KEYBOARD_H

#define DVORAK 0
#define ARROW 1
#define SYMBOL 2
#define NUMBER 3
#define FUNCTION 4
#define EMACS 5
#define CUSTOM_MACROS 6
#define MOUSE 7

#define LT_1A LT(1, KC_A)
#define LT_2O LT(2, KC_O)
#define LT_3E LT(3, KC_E)
#define LT_4U LT(4, KC_U)
#define LT_5Q LT(5, KC_Q)
#define LT_6CTL LT(6, KC_LCTL)
#define LT_7COM LT(7, KC_COMM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DVORAK] = LAYOUT_planck_grid(
    KC_ESC,  KC_QUOTE,  LT_7COM,  KC_DOT,  KC_P,  KC_Y,  KC_F,  KC_G,  KC_C,  KC_R,  KC_L,  KC_DELETE,
    KC_TAB,  LT_1A,  LT_2O,  LT_3E,  LT_4U,  KC_I,  KC_D,  KC_H,  KC_T,  KC_N,  KC_S,  KC_ENTER,
    KC_LSFT,  KC_SCLN,  LT_5Q,   KC_J,   KC_K,  KC_X,   KC_B,   KC_M,   KC_W,  KC_V,  KC_Z,  KC_MINUS,
    C(KC_LALT), LT_6CTL,  KC_MENU, KC_LALT,  KC_LGUI,  KC_BSPC,  KC_SPACE,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_UP, KC_RIGHT
  ),

  [ARROW] = LAYOUT_planck_grid(
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,  KC_UP,  KC_END,  KC_PGUP,
    KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_PGDN,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
  ),

  [SYMBOL] = LAYOUT_planck_grid(
    KC_TILD,  KC_GRAVE,  KC_NO,  KC_EQUAL,  KC_PLUS,  KC_NO,  KC_LBRC,  KC_RBRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,
    KC_NO,  KC_NO,  KC_TRNS,  KC_SCLN,  KC_COLN,  KC_NO,  KC_LCBR,  KC_RCBR,  KC_DLR,  KC_PERC,  KC_CIRC,  S(KC_SLSH),
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_BSLS,  KC_SLASH,  KC_EXLM,  KC_AT,  KC_HASH,  KC_PIPE,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_ASTR,   KC_SLASH,  KC_MINUS,  KC_PLUS,  KC_EQUAL
  ),

  [NUMBER] = LAYOUT_planck_grid(
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_7,  KC_8,  KC_9,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_4,  KC_5,  KC_6,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_0,  KC_1,  KC_2,  KC_3,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_ASTR,  KC_SLASH,  KC_MINUS,  KC_PLUS,  KC_EQUAL
  ),

  [FUNCTION] = LAYOUT_planck_grid(
    KC_PSCR,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
     KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS,  KC_NO,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,
     KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,  KC_MEDIA_PLAY_PAUSE,
     QK_BOOT,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_DELETE,  KC_INSERT,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END
    ),

    [EMACS] = LAYOUT_planck_grid(
      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
      KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
    ),

    [CUSTOM_MACROS] = LAYOUT_planck_grid(
      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
      KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
    ),

    [MOUSE] = LAYOUT_planck_grid(
      KC_NO,  KC_NO,  KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_U,  KC_NO,  KC_NO,
      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_NO,
      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_BTN1,  KC_MS_BTN2,  KC_MS_BTN3,  KC_NO,  KC_NO,  KC_NO
    ),

  };
