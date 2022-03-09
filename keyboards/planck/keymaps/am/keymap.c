// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _TOUCHCURSOR,
  _MOUSE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// Taps
#define CTL_ESC CTL_T(KC_ESC)            // Tap for Esc, hold for Ctr
#define SFT_ENT SFT_T(KC_ENT)            // Tap for Enter, hold for Shift
#define LT_TC   LT(_TOUCHCURSOR, KC_SPC) // L-ayer T-ap T-ouch C-ursor
#define LT_ML   LT(_MOUSE, KC_A)         // L-ayer T-ap M-ouse C-ursor (on A)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,--------------------------------------------------------------------------------------.
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp  |
 * |--------+------+------+------+------+-------------+------+------+------+------+-------|
 * |Ctrl/Esc| ML/A |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   "   |
 * |--------+------+------+------+------+------|------+------+------+------+------+-------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Sft/Ent|
 * |--------+------+------+------+------+------+------+------+------+------+------+-------|
 * | Power  |   ~  | Alt  | GUI  |Lower |   TC/Space  |Raise | Next | Vol- | Vol+ |  Play |
 * `--------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  CTL_ESC, LT_ML,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_ENT,
  KC_CAPS, KC_TILD, KC_LALT, KC_LGUI, LOWER,   LT_TC,   LT_TC,   RAISE,   KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Colemak
 * ,-------------------------------------------------------------------------------------.
 * | Tab    |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |--------+------+------+------+------+-------------+------+------+------+------+------|
 * |Ctrl/Esc| ML/A |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |--------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |--------+------+------+------+------+------+------+------+------+------+------+------|
 * | Power  |   ~  | Alt  | GUI  |Lower |   TC/Space  |Raise | Next | Vol- | Vol+ | Play |
 * `-------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  CTL_ESC, LT_ML,   KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_CAPS, KC_TILD, KC_LALT, KC_LGUI, LOWER,   LT_TC,   LT_TC,   RAISE,   KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
 ),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   |  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   +  |   {  |   }  |  `   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   \  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   _  |   =  |   [  |   ]  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Sleep |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_PIPE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_GRV,
  KC_BSLS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_SLSH,
  KC_SLEP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ^  |   4  |   5  |   6  |   .  |   +  |   *  |   4  |   5  |   6  |   -  |  $   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   =  |   7  |   8  |   9  |   0  |   -  |   /  |   1  |   2  |   3  |   .  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Sleep |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
  KC_0,    KC_1,    KC_2,    KC_3,    KC_4,   KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_CIRC, KC_4,    KC_5,    KC_6,    KC_DOT, KC_PLUS,  KC_ASTR, KC_4,    KC_5,    KC_6,    KC_MINS, KC_DLR,
  KC_EQL,  KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS,  KC_SLSH, KC_1,    KC_2,    KC_3,    KC_DOT,  KC_ENT,
  KC_SLEP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* TouchCursor layer (http://martin-stone.github.io/touchcursor/) plus personal customizations
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |Shift | GUI  |  ~   |Insert| Home |  Up  | End  | Bksp |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Alt  |Space |      | Find |Again | PgUp | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy |Paste |  `   | PgDn | Del  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
 * The KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, KC_FIND, and KC_AGAIN keycodes don't
 * seem to work on Mac. Presumably they'll work under Windows.
 */

[_TOUCHCURSOR] = LAYOUT_planck_grid(
  _______, _______, _______, KC_LSFT, KC_LGUI, KC_TILD, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_BSPC, _______,
  _______, KC_LALT, KC_SPC,  _______, KC_FIND,KC_AGAIN, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,KC_GRV,  KC_PGDN, KC_DEL,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Mouse Layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |ACCL0 |ACCL1 |ACCL2 |ACCL2 |      |WHL_L |  Up  |WHL_R | BTN2 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      | BTN3 | BTN1 | BTN4 |WHL_Up| Left | Down |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      | BTN2 | BTN5 |WHL_Dn| BTN1 |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_MOUSE] = LAYOUT_planck_grid(
  _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_ACL2, _______, KC_WH_L, KC_MS_U, KC_WH_R, KC_BTN2, _______,
  _______, _______, _______, KC_BTN3, KC_BTN1, KC_BTN4, KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
  _______, _______, _______, _______, KC_BTN2, KC_BTN5, KC_WH_D, KC_BTN1, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, _______, _______, _______,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)


};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
  }
  return true;
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
  case RAISE:
  case LOWER:
    return false;
  default:
    return true;
  }
}
