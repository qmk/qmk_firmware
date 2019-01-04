#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_layers {
  _QWERTY,
  _WORKMAN,
  _LOWER,
  _RAISE,
  _ADJUST,
  _EMOJI,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  WORKMAN,
  LOWER,
  RAISE,
  ADJUST,
  EMOJI,
  ABOVE,
  BUG,
  CONFUSED,
  CRY,
  CLAP,
  ELIP,
  FLIP,
  FNGLEFT,
  FNGRIGHT,
  FROWN,
  GRIN,
  HEART,
  JOY,
  LLAP,
  ROFL,
  SHIT,
  SING,
  SHRUG,
  THINK,
  THMBDN,
  THMBUP,
  TOUNGE,
  THANKS,
  WINK
};

#define KC_X0 MT(MOD_LCTL, KC_ESC)  // Hold for Left Ctrl, Tap for GraveESC
#define KC_X1 MT(MOD_RSFT, KC_ENT)  // Hold for Right Shift, Tap for Enter
#define KC_X2 MT(MOD_RSFT, LGUI(KC_ENT))  // Send Command Enter
#define KC_BACK LGUI(KC_LBRC) // Back
#define KC_FORWARD LGUI(KC_RBRC) // Forward
#define KC_EMOJ TT(_EMOJI)  // Hold for Emoji Layer, or tap 5 times.
#define KC_QS LGUI(KC_SPC)  // Send Command + Space (for QuickSilver).
#define KC_WTAB LGUI(KC_TILD)  // Send Command + ~ (for window changing).
#define KC_TABR LGUI(KC_RCBR)  // Send Command + } (for tab changing).
#define KC_TABL LGUI(KC_LCBR)  // Send Command + { (for tab changing).
#define HYPR_0 HYPR(KC_TILD)  // Send Hyper + ~.
#define HYPR_1 HYPR(KC_EXLM)  // Send Hyper + !.
#define HYPR_2 HYPR(KC_AT)  // Send Hyper + @.

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


#define KC_QWERTY QWERTY
#define KC_WORKMAN WORKMAN
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  /* ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐*/
       KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤*/
       KC_X0, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤*/
       KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_X1,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤*/
      KC_EMOJ,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LPRN,          KC_RALT,  KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RGHT,
  /* └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘*/
                                      KC_LGUI, LOWER,   KC_SPC,                   KC_SPC,  RAISE,   KC_LEFT
                                 /* └────────┴────────┴────────┘                 └────────┴────────┴────────┘*/
  ),

  [_LOWER] = LAYOUT(
  /* ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐*/
      KC_TILD, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤*/
      KC_TILD, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤*/
      _______, _______, KC_LEFT, KC_RGHT, KC_UP,   KC_LBRC,                            KC_RBRC, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_PIPE,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤*/
      _______, _______, _______, _______, KC_DOWN, KC_LCBR, KC_LPRN,          KC_RPRN, KC_RCBR, KC_P1,   KC_P2,   KC_P3,   KC_MINS, _______,
  /* └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘*/
                                      _______, _______, KC_DEL,                    KC_DEL,  _______, KC_P0
                                /*  └────────┴────────┴────────┘                 └────────┴────────┴────────┘*/
  ),

  [_RAISE] = LAYOUT(

  /* ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐*/
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, /**/
  /* ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤*/
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤*/
      _______, _______, LGUI(KC_LEFT), LGUI(KC_RGHT), LGUI(KC_UP), KC_UNDS,                            KC_EQL,  KC_HOME, _______, _______, _______, KC_BSLS,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤*/
      _______, _______, _______, _______, LGUI(KC_DOWN), KC_MINS, KC_LPRN,          _______, KC_PLUS, KC_END,  _______, _______, _______, _______,
  /* └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘*/
                                      _______, _______, _______,                   _______, _______, _______
                                /*  └────────┴────────┴────────┘                 └────────┴────────┴────────┘*/
  ),

  [_ADJUST] = LAYOUT(
  /* ┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐*/
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤*/
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤*/
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  /* ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤*/
      _______, _______, _______, _______, _______, _______, KC_QWERTY,          KC_WORKMAN, _______, _______, _______, _______, _______, _______,
  /* └────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘*/
                                     _______, ADJUST, _______,                   _______, ADJUST, _______
                                /*  └────────┴────────┴────────┘                 └────────┴────────┴────────┘*/
  ),
  /* Emoji Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │HYPR0│  Q  │ ;-) │  E  │  🤣 │ :-P │ 🙏🏼  │  U  │:'-( │FLIP │  P  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │HYPR1│  👆 │SHRUG│ GRIN│ :-( │  G  │ <3  │ :-) │  k  │LLAP │  ;  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │HYPR2│🎶^🎶│💭^💭│ 👏 | :-\ │ 🐛  │  n  │ :-D │ SHIT│  ...  │  /  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │Brig-│   Sleep   │Brig+│ 👈  │ 👎  |  👍 │ 👉 │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [_EMOJI] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
    HYPR_0,  _______, WINK,    _______, ROFL,     TOUNGE,                         THANKS,  _______, CRY,     FLIP,    _______, _______ ,
    HYPR_1,  ABOVE,   SHRUG,   GRIN,    FROWN,    _______,                        HEART,   JOY,     _______, LLAP,    _______, _______ ,
    HYPR_2,  SING,    THINK,   CLAP,    CONFUSED, BUG,    _______,       _______, _______, SHIT,     ELIP,  _______, _______ ,_______ ,
                                   _______, _______, _______,                   _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case KC_WORKMAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
      break;
    case ABOVE:
      if (record->event.pressed) {
        SEND_STRING("&above; ");
      }
      return false;
      break;
    case BUG:
      if (record->event.pressed) {
        SEND_STRING("&bug;");
      }
      return false;
      break;
    case CONFUSED:
      if (record->event.pressed) {
        SEND_STRING(":-\\");
      }
      return false;
      break;
    case CRY:
      if (record->event.pressed) {
        SEND_STRING(":'-( ");
      }
      return false;
      break;
    case CLAP:
      if (record->event.pressed) {
        SEND_STRING("&clap; ");
      }
      return false;
      break;
    case ELIP:
      if (record->event.pressed) {
        SEND_STRING("...");
      }
      return false;
      break;
    case FLIP:
      if (record->event.pressed) {
        SEND_STRING("&fliptable;");
      }
      return false;
      break;
    case FNGLEFT:
      if (record->event.pressed) {
        SEND_STRING("&fingerleft; ");
      }
      return false;
      break;
    case FNGRIGHT:
      if (record->event.pressed) {
        SEND_STRING("&fingerright; ");
      }
      return false;
      break;
    case FROWN:
      if (record->event.pressed) {
        SEND_STRING(":-( ");
      }
      return false;
      break;
    case GRIN:
      if (record->event.pressed) {
        SEND_STRING(":-D ");
      }
      return false;
      break;
    case HEART:
      if (record->event.pressed) {
        SEND_STRING("<3 ");
      }
      return false;
      break;
    case JOY:
      if (record->event.pressed) {
        SEND_STRING(":-) ");
      }
      return false;
      break;
    case LLAP:
      if (record->event.pressed) {
        SEND_STRING("&llap; ");
      }
      return false;
      break;
    case ROFL:
      if (record->event.pressed) {
        SEND_STRING("&rofl; ");
      }
      return false;
      break;
    case SHIT:
      if (record->event.pressed) {
        SEND_STRING("&shit; ");
      }
      return false;
      break;
    case SING:
      if (record->event.pressed) {
        SEND_STRING("_sing_");
      }
      return false;
      break;
    case SHRUG:
      if (record->event.pressed) {
        SEND_STRING("&shrug; ");
      }
      return false;
      break;
    case THANKS:
      if (record->event.pressed) {
        SEND_STRING("&thanks;");
      }
      return false;
      break;
    case THINK:
      if (record->event.pressed) {
        SEND_STRING("_think_");
      }
      return false;
      break;
    case THMBDN:
      if (record->event.pressed) {
        SEND_STRING("&thumbdown; ");
      }
      return false;
      break;
    case THMBUP:
      if (record->event.pressed) {
        SEND_STRING("&thumbup; ");
      }
      return false;
      break;
    case TOUNGE:
      if (record->event.pressed) {
        SEND_STRING(":-P ");
      }
      return false;
      break;
    case WINK:
      if (record->event.pressed) {
        SEND_STRING(";-) ");
      }
      return false;
      break;

  }
  return true;
}
