#include QMK_KEYBOARD_H

#define SPC_FN(LY) LT(LY, KC_SPC)

#define MS_BTN1 KC_MS_BTN1
#define MS_BTN2 KC_MS_BTN2
#define MS_BTN3 KC_MS_BTN3
#define MS_W_UP KC_MS_WH_UP
#define MS_W_DN KC_MS_WH_DOWN
#define MS_UP KC_MS_UP
#define MS_DOWN KC_MS_DOWN
#define MS_LEFT KC_MS_LEFT
#define MS_RGHT KC_MS_RIGHT
#define DF_CODE DF(CODING)
#define DF_GAME DF(GAMING)

enum LAYERS {
  CODING, // All the bells and whistles for coding.
  GAMING, // Simpler control scheme for games (e.g. space is just space).
  FN,     // Function keys (e.g. screen brightness, media keys).
  CTRL,   // Controls for the keyboard (e.g. brightness, colours) and mouse (buttons and movement).
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CODING] = LAYOUT_all(
      KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSPC, XXXXXXX,
      KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      MO(FN),     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, DF_GAME,
      KC_LCTL, KC_LGUI, KC_LALT,                         SPC_FN(FN),                            KC_RALT, MO(CTRL), KC_RCTL
  ),
  [GAMING] = LAYOUT_all(
       KC_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DF_CODE,
      _______, _______, _______,                             KC_SPC,                            _______, _______, _______
  ),
  [FN] = LAYOUT_all(
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL, XXXXXXX,
      _______, KC_BRID, KC_BRIU, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______,
      _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_HOME, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_END, _______, _______,
      _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______,                            _______,                            _______, _______, _______
  ),
  [CTRL] = LAYOUT_all(
      _______,  EF_DEC,  EF_INC,  H1_DEC,  H1_INC,  H2_DEC,  H2_INC,  S1_DEC,  S1_INC,  S2_DEC,  S2_INC,  ES_DEC,  ES_INC, _______, XXXXXXX,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  BR_DEC,  BR_INC, _______,
      _______, _______, _______, _______, _______, _______, MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT, _______, _______, _______,
      _______, MS_W_DN, MS_W_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      MS_BTN1, MS_BTN3, MS_BTN2,                            _______,                            _______, _______, _______
  ),
};


