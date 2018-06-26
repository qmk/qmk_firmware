// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "telophase.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum telophase_layers
{
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _EMOJI,
};

enum telophase_keycodes
{
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  EMOJI,
  ABOVE,
  BUG,
  CONFUSED,
  CRY,
  FLIP,
  FNGLEFT,
  FNGRIGHT,
  FROWN,
  GRIN,
  HEART,
  JOY,
  LLAP,
  SHIT,
  SHRUG,
  THMBDN,
  THMBUP,
  TOUNGE,
  WINK
};

#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 300

#define KC_X0 MT(MOD_LCTL, KC_ESC)  // Hold for Left Ctrl, Tap for GraveESC
#define KC_X1 MT(MOD_RSFT, KC_ENT)  // Hold for Right Shift, Tap for Enter
#define KC_X2 MT(MOD_RSFT, LGUI(KC_ENT))  // Send Command Enter
#define KC_BACK LGUI(KC_LBRC) // Back
#define KC_FORWARD LGUI(KC_RBRC) // Forward
#define KC_EMOJ TT(_EMOJI)  // Hold for Emoji Layer, or tap 5 times.
#define KC_QS LGUI(KC_SPC)  // Send Command + Space (for QuickSilver).
#define KC_TABR LGUI(KC_RCBR)  // Send Command + } (for tab changing).
#define KC_TABL LGUI(KC_LCBR)  // Send Command + { (for tab changing).
#define HYPR_0 HYPR(KC_TILD)  // Send Hyper + ~.
#define HYPR_1 HYPR(KC_EXLM)  // Send Hyper + !.
#define HYPR_2 HYPR(KC_AT)  // Send Hyper + @.

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* Qwerty
  * ,-----------------------------------------------------------------------------------.
  * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |Emoji | Ctrl | Alt  |Lower | Cmd  |Space |Space |Raise | Left | Down |  Up  |Right |
  * `-----------------------------------------------------------------------------------'
  */
[_QWERTY] = {
  {KC_TAB,  KC_Q,      KC_W,    KC_E,    KC_R,  KC_T,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC },
  {KC_X0,   KC_A,      KC_S,    KC_D,    KC_F,  KC_G,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
  {KC_LSFT, KC_Z,      KC_X,    KC_C,    KC_V,  KC_B,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_X1   },
  {KC_EMOJ, KC_LCTL,   KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC,  RAISE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT }
},
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  | TAB_L| TAB_R|  <-  |  ->  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Tab- | Vol- | Vol+ | Tab+ |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC    },
  {KC_DEL,  KC_TABL, KC_TABR, KC_BACK, KC_FORWARD, KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE   },
  {KC_LSFT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______ },
  {_______, _______, _______, _______, _______, KC_QS,   KC_QS,   _______, KC_TABL, _______,  _______, KC_TABR   }
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgUp | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC   },
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS  },
  {KC_LSFT, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, KC_X2    },
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   }

},

/* Emoji Layer
 *
 * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
 * │HYPR0│     │ ;-) │     │     │ :-P │     │     │:'-( │FLIP │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │HYPR1│  👆 │SHRUG│     │ :-( │     │ <3  │ :-) │     │LLAP │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │HYPR2│     │     │ :-\ |     │ 🐛  │     │ :-D │ SHIT│     │     │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │     │Brig-│   Sleep   │Brig+│ 👈  │ 👎  |  👍 │ 👉 │
 * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
 */
[_EMOJI] = {
  {HYPR_0,  _______, WINK,    _______, _______,  TOUNGE,  _______, _______, CRY,     FLIP,    _______, _______ },
  {HYPR_1,  ABOVE,   SHRUG,   _______, FROWN,    _______, HEART,   JOY,     _______, LLAP,    _______, _______ },
  {HYPR_2,  _______, _______, CONFUSED, _______, BUG, _______, GRIN,    SHIT,    _______, _______, _______ },
  {_______, _______, _______, _______, KC_SLCK,  KC_SLEP, KC_SLEP, KC_PAUS, FNGLEFT, THMBDN,  THMBUP,  FNGRIGHT}
},

[_ADJUST] = {
    {_______, RESET,   _______, _______, KC_PSCR, _______, _______, _______, _______, _______, _______, KC_DEL  },
    {_______, _______, _______, _______, _______, AG_NORM, AG_SWAP, _______, _______, _______, _______, _______ },
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
},

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
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
    case SHIT:
      if (record->event.pressed) {
        SEND_STRING("&shit; ");
      }
      return false;
      break;
    case SHRUG:
      if (record->event.pressed) {
        SEND_STRING("&shrug; ");
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

void matrix_scan_user(void) {
    return;
};

