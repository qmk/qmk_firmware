#include "contra.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Custom Key Combos
#define LCKSCR LCTL(LGUI(KC_Q))
//#define KC_CAD LCTL(LALT(KC_DEL)) // CTL+ALT+DEL (windows)
//#define KC_CAE LGUI(LALT(KC_ESC)) // CMD+ALT+ESC (Force Close)
//#define KC_SCREENSHOT LGUI(S(KC_4)) // CMD+SHIFT+4 (Mac Screenshot)

#define _QWERTY 0
#define _QWERTYMAC 1
#define _L1  2
#define _L2  3
#define _L3  4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  QWERTYMAC,
  L1,
  L2,
  L3
};

//Tap Dance Declarations
#define COLON TD(CLN)
#define QUOTE TD(QUOT)
#define PARAN TD(PAR)
#define CURLY TD(CUR)
#define SQUAR TD(SQU)
#define ANGUL TD(ANG)
#define TMUX TD(TD_TMUX)
#define CADCAE TD(CAD_CAE)
#define SHIFTSLASHPIPE TD(TD_SHIFTSLASHPIPE)

enum {
  CLN = 0,
  QUOT,
  CAD_CAE,
  PAR,
  CUR,
  SQU,
  ANG,
  TD_TMUX,
  TD_SHIFTSLASHPIPE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  |  '@  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |  \|  |  L1  |      |      |  L2  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,    KC_Q, KC_W,               KC_E,       KC_R,  KC_T,    KC_Y,       KC_U,    KC_I,    KC_O,        KC_P,  KC_BSPC},
  {KC_ESC,    KC_A, KC_S,               KC_D,       KC_F,  KC_G,    KC_H,       KC_J,    KC_K,    KC_L,       COLON,  QUOTE},
  {KC_LSFT,    KC_Z, KC_X,               KC_C,       KC_V,  KC_B,    KC_N,       KC_M, KC_COMM,  KC_DOT,     KC_SLSH,   KC_ENT},
  {KC_LCTL, KC_LGUI, KC_LALT, KC_NONUS_BSLASH,    MO(_L1), XXXXXXX, KC_SPC,    MO(_L2), KC_LEFT, KC_DOWN,       KC_UP,  KC_RGHT}
},

/* QwertyMAC
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  |  '@  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |  \|  |  L1  |      |      |  L2  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTYMAC] = {
  {KC_TAB,    KC_Q, KC_W,               KC_E,       KC_R,  KC_T,    KC_Y,       KC_U,    KC_I,    KC_O,        KC_P,  KC_BSPC},
  {KC_ESC,    KC_A, KC_S,               KC_D,       KC_F,  KC_G,    KC_H,       KC_J,    KC_K,    KC_L,       COLON,  QUOTE},
  {KC_LSFT,    KC_Z, KC_X,               KC_C,       KC_V,  KC_B,    KC_N,       KC_M, KC_COMM,  KC_DOT,     KC_SLSH,   KC_ENT},
  {KC_LCTL, KC_LALT, KC_LGUI, KC_NONUS_BSLASH,    MO(_L1), XXXXXXX,KC_SPC,    MO(_L2), KC_LEFT, KC_DOWN,       KC_UP,  KC_RGHT}
},

/* L1
 * ,-----------------------------------------------------------------------------------.
 * |  `¬  |INSERT| PGUP | HOME |  <>  |      |  ()  |  7&  |  8*  |  9(  |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |DELETE| PGDN | END  |  []  |  {}  |  =+  |  4$  |  5%  |  6^  |  *   | LMAC |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LSHIFT|PSCRN |      |CADCAE|  L3  |LCKSCR|  -_  |  1!  |  2"  |  3£  |  /?  |ENTER |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |  #~  |      |      |      |      |   0) |  .>  |      | MENU |
 * `-----------------------------------------------------------------------------------'
 */
[_L1] = {
  {KC_GRV,  KC_INSERT,   KC_PGUP,  KC_HOME,   ANGUL, XXXXXXX,   PARAN,    KC_7,  KC_8,           KC_9, XXXXXXX, KC_BSPC},
  {XXXXXXX,  KC_DELETE, KC_PGDOWN,   KC_END,   SQUAR,   CURLY,  KC_EQL,    KC_4,  KC_5,           KC_6, S(KC_8), TG(_QWERTYMAC)},
  {_______, KC_PSCREEN,   XXXXXXX,   CADCAE, MO(_L3),  LCKSCR, KC_MINS,    KC_1,  KC_2,           KC_3, KC_SLSH,  KC_ENT},
  {_______,    _______,   _______,  KC_NUHS, XXXXXXX, XXXXXXX,  KC_SPC, XXXXXXX,  KC_0, ALGR_T(KC_DOT), XXXXXXX, KC_MENU}
},

/* L2
 * ,-----------------------------------------------------------------------------------.
 * |Sysreq|  F9  |  F10 |  F11 |  F12 |      |NUMLK |   7  |   8  |   9  |   *  |Bksp  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      |   4  |   5  |   6  |  /   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |   1  |   2  |   3  |  +   |KP_ENT|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |      |      |      |      |      |   0  |   .  |  -   |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_L2] = {
    {KC_SYSREQ,   KC_F9,  KC_F10,  KC_F11,      KC_F12, XXXXXXX, KC_NUMLOCK, KC_KP_7, KC_KP_8,   KC_KP_9, KC_KP_ASTERISK,     KC_BSPC},
    {XXXXXXX,   KC_F5,   KC_F6,   KC_F7,       KC_F8, XXXXXXX,    XXXXXXX, KC_KP_4, KC_KP_5,   KC_KP_6,    KC_KP_SLASH,     _______},
    {XXXXXXX,   KC_F1,   KC_F2,   KC_F3,       KC_F4, XXXXXXX,    XXXXXXX, KC_KP_1, KC_KP_2,   KC_KP_3,     KC_KP_PLUS, KC_KP_ENTER},
    {_______, _______, _______, XXXXXXX,     XXXXXXX, XXXXXXX,     KC_SPC, XXXXXXX, KC_KP_0, KC_KP_DOT,    KC_KP_MINUS,      _______}
 },

/* L3
 * ,-----------------------------------------------------------------------------------.
 * |RGBTOG|RGBHUI|RGBHUD|RGBSAI|RGBSAD|      |      | PGDN | PGUP |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |BLTOG |BLSTEP|RGBVAI|RGBVAD|RGBMOD|RGBRMD| Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | TMUX |      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 [_L3] = {
    {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,   KC_PGDOWN, KC_PGUP,  XXXXXXX, XXXXXXX, XXXXXXX},
    {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT,     KC_DOWN,   KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX},
    {TMUX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  KC_ENT},
    {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_SPC,     XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX}
 }

};

// Parantheses
void paranthesis_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("()"); register_code(KC_LEFT); unregister_code(KC_LEFT);
  } else if (state->count == 2) {
    SEND_STRING("(");
  } else if (state->count == 3) {
    SEND_STRING(")");
  }
}

void curly_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("{}"); register_code(KC_LEFT); unregister_code(KC_LEFT);
  } else if (state->count == 2) {
    SEND_STRING("{");
  } else if (state->count == 3) {
    SEND_STRING("}");
  }
}

void square_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("[]"); register_code(KC_LEFT); unregister_code(KC_LEFT);
  } else if (state->count == 2) {
    SEND_STRING("[");
  } else if (state->count == 3) {
    SEND_STRING("]");
  }
}

void angular_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("<>"); register_code(KC_LEFT); unregister_code(KC_LEFT);
  } else if (state->count == 2) {
    SEND_STRING("<");
  } else if (state->count == 3) {
    SEND_STRING(">");
  }
}

void tmux_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("tmux"); register_code(KC_ENT); unregister_code(KC_ENT);
  } else if (state->count == 2) {
    register_mods(MOD_BIT(KC_LCTRL));
    register_code(KC_B); unregister_code(KC_B);
    unregister_mods(MOD_BIT(KC_LCTRL));
    register_mods(MOD_BIT(KC_LSHIFT));
    register_code(KC_5); unregister_code(KC_5);
    unregister_mods(MOD_BIT(KC_LSHIFT));
  }
}

void cmd_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_mods(MOD_BIT(KC_LCTRL));
    register_mods(MOD_BIT(KC_LALT));
    register_code(KC_DELETE);
    unregister_mods(MOD_BIT(KC_LCTRL));
    unregister_mods(MOD_BIT(KC_LALT));
    unregister_code(KC_DELETE);
  } else if (state->count == 2) {
    register_mods(MOD_BIT(KC_LGUI));
    register_mods(MOD_BIT(KC_LALT));
    register_code(KC_ESC);
    unregister_mods(MOD_BIT(KC_LGUI));
    unregister_mods(MOD_BIT(KC_LALT));
    unregister_code(KC_ESC);
  } else if (state->count == 3) {
    register_mods(MOD_BIT(KC_LGUI));
    register_mods(MOD_BIT(KC_LSHIFT));
    register_code(KC_4);
    unregister_mods(MOD_BIT(KC_LGUI));
    unregister_mods(MOD_BIT(KC_LSHIFT));
    unregister_code(KC_4);
  }
}

void cmd_sft_slash_pipe_down (qk_tap_dance_state_t *state, void *user_data) { 
  if (state->count == 1) {
    if (state->interrupted || state->pressed==0) {
      register_code (KC_NONUS_BSLASH);
    } else {
      register_code (KC_LSFT); 
    }
  } else if (state->count == 2) {
    register_mods(MOD_BIT(KC_LSFT));
    register_code(KC_NONUS_BSLASH);
  }
}

void cmd_sft_slash_pipe_up (qk_tap_dance_state_t *state, void *user_data) { 
  if (state->count == 1) { 
    if (keyboard_report->mods & MOD_BIT(KC_LSFT)) { 
      unregister_code (KC_LSFT); 
    } else {
      unregister_code (KC_NONUS_BSLASH);
    }
  } else if (state->count == 2) {
    unregister_mods(MOD_BIT(KC_LSFT));
    unregister_code(KC_NONUS_BSLASH);
  }
}

 //All tap dance functions would go here. Only showing this one.
 qk_tap_dance_action_t tap_dance_actions[] = {
   [CLN] = ACTION_TAP_DANCE_DOUBLE (KC_SCLN, S(KC_SCLN ))
   ,[QUOT] = ACTION_TAP_DANCE_DOUBLE (KC_QUOT, S(KC_2))
   ,[CAD_CAE] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, cmd_dance )
   ,[PAR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, paranthesis_dance )
   ,[CUR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, curly_dance )
   ,[SQU] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, square_dance )
   ,[ANG] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, angular_dance )
   ,[TD_TMUX] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, tmux_dance )
   ,[TD_SHIFTSLASHPIPE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, cmd_sft_slash_pipe_down, cmd_sft_slash_pipe_up) 
 };
