#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _ARROWS 1
#define _SYMBOLS 2
#define _NUMFUN 3
#define _NUMPAD 4
#define _MODIFIED 5

enum my_keycodes {
  ALT_TAB = SAFE_RANGE,
};

// Tap Dance declarations
enum {
    TD_Q_ESC,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
};

// Add tap dance item in place of a key code
// TD(TD_Q_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.                        ,--------+--------+--------+--------+--------+--------+--------.
     BL_TOGG,  TD(TD_Q_ESC),    KC_W,    KC_E,    KC_R,    KC_T,    _______,                          _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
  //|--------+--------+--------+--------+--------+--------+--------|                        |--------+--------+--------+--------+--------+--------+--------|
     BL_INC,  LCTL_T(KC_A), LSFT_T(KC_S), LALT_T(KC_D), LT(_NUMPAD, KC_F),    KC_G,    _______,      _______, KC_H,    RGUI_T(KC_J), RALT_T(KC_K), RSFT_T(KC_L), RCTL_T(KC_SCLN), _______,
  //|--------+--------+--------+--------+--------+--------+--------|                        |--------+--------+--------+--------+--------+--------+--------|
     BL_DEC, KC_Z, KC_X, KC_C, KC_V, KC_B, _______,                                         _______, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                        |--------+--------+--------+--------+--------+--------+--------|
     RGB_TOG, RGB_HUI, RGB_MOD, LT(_NUMFUN, KC_DELETE),   LT(_MODIFIED, KC_TAB),   LT(_ARROWS, KC_ENT),           LT(_SYMBOLS, KC_SPC),  LT(_NUMPAD, KC_BSPC), LT(_NUMFUN, KC_QUOT), _______,   _______, _______
  //`--------+--------+--------+--------+--------+--------+--------/                        \--------+--------+--------+--------+--------+--------+--------'
  ),

  [_ARROWS] = LAYOUT(
  _______, _______,  _______,   _______, _______,  _______, _______,                         _______,     KC_LABK, KC_HOME, KC_UP, KC_END, KC_LCBR, KC_BRIU,  \
  _______, KC_LCTL,    KC_LSFT,   KC_LALT,   KC_LGUI,   _______,   _______,                  _______,     KC_RABK,   KC_LEFT, KC_DOWN, KC_RIGHT, KC_RCBR, KC_BRID, \
  _______, _______,    _______,   _______,   _______,  _______,  _______,                    _______,     KC_BSLS,  KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_LBRACKET, KC_RBRACKET, _______, \
  _______, _______,  _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______  \

  ),

  [_SYMBOLS] = LAYOUT(
 
  _______,  KC_GRAVE,    KC_PERCENT,  KC_PIPE,   KC_AMPR,    KC_EQUAL,     _______,          _______,     _______,    _______,    _______,    _______,    _______,    _______,  \
  KC_CAPSLOCK, KC_EXCLAIM,    KC_AT,  KC_HASH,   KC_DOLLAR, KC_RABK,  _______,          _______,   _______,   _______, _______,  _______, _______, _______, \
  _______,  KC_CIRC,    KC_ASTR,  KC_UNDERSCORE,   KC_PLUS, KC_MINUS,  _______,          _______,   _______,   _______, _______, _______, _______, _______, \
  _______, _______, _______,  _______, _______, _______,                                 _______, _______, _______, _______, _______, _______  \
  
  ),

  [_NUMPAD] = LAYOUT(
     _______,  RESET,  _______, _______, _______, _______, _______,         _______,  _______, KC_7, KC_8, KC_9, SGUI(KC_S), _______,
     _______, _______,  DM_REC1, DM_RSTP, DM_PLY1, _______, _______,         _______,  _______, KC_4, KC_5, KC_6, _______, _______,
     _______, _______,  DM_REC2, DM_RSTP, DM_PLY2, _______, _______,         _______,  _______, KC_1, KC_2, KC_3, _______, _______,
     _______, _______, _______, _______,           _______, _______,         KC_MINUS,  KC_KP_0,          _______, _______, _______, _______
  ),

  [_NUMFUN] = LAYOUT(
     _______,  KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, _______,                   _______,  KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______,
     _______, KC_1,  KC_2, KC_3, KC_4, KC_5, _______,                         _______,  KC_6, KC_7, KC_8, KC_9, KC_0, _______,
     _______, _______,  LGUI(KC_V), KC_VOLD, KC_VOLU, _______, _______,         _______,  _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
     _______, _______, _______, _______,           _______, _______,         _______,  _______,          _______, _______, _______, _______
  ),

  [_MODIFIED] = LAYOUT(
  _______, _______,  _______,   _______, LCTL(KC_R),  _______, _______,                               _______,     BL_INC, BL_STEP, _______, _______, _______, _______,  \
  _______, LCTL(KC_A),  LCTL(KC_S),   LCTL(KC_D), LCTL(KC_F),  _______,   _______,                    _______,     BL_DEC,   BL_TOGG, BL_BRTG, _______, _______, _______, \
  _______, LCTL(KC_Z),    LCTL(KC_X),   LCTL(KC_C),   LCTL(KC_V),  LCTL(KC_B),  _______,              _______,     _______,  BL_ON, BL_OFF, _______, _______, _______, \
  _______, _______,  _______, _______, _______, _______,                                              _______, _______, _______, _______, _______, _______  \

  ),

};

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
      switch (keycode) {
         case LT(_ARROWS, KC_ENT):
         case LCTL_T(KC_A):
         case LSFT_T(KC_S):
         case LALT_T(KC_D):
         case LT(_NUMPAD, KC_F):
         case RGUI_T(KC_J):
         case RALT_T(KC_K):
         case RSFT_T(KC_L):
         case RCTL_T(KC_SCLN):
            return true;
         default:
            return false;
      }
}

// Common key processing
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{    
   // persistant variable
   static bool in_tab = false; // does an ALT-TAB, for windows cycling, without an alt key

   if (keycode != ALT_TAB && in_tab)
   {
      // Exit alt tab before treating normally the keycode
      SEND_STRING(SS_UP(X_LALT));
      in_tab = false;
   }

   switch (keycode) {
      case ALT_TAB:
         // Macro to handle lower-tab as alt-tab
         if (record->event.pressed) {
            if (!in_tab)
            {
               SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_TAB));
               in_tab = true;
            } else {
               SEND_STRING(SS_TAP(X_TAB));
               // Do not release Alt here, or it will be impossible to switch more than one window:
               // alt-tab-tab will be interpreted as alt-tab, then tab
            }
         }

         return false;
   }
      
   return true;
}
