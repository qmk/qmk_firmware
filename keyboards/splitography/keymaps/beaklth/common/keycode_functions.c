
// ................................................................... Mod Masks

// tap dance persistant mods, see process_record_user()
// keyboard_report->mods (?) appears to be cleared by tap dance
static uint8_t mods = 0;

void tap_mods(keyrecord_t *record, uint16_t keycode)
{
  if (record->event.pressed) { mods |= MOD_BIT(keycode); }
  else                       { mods &= ~(MOD_BIT(keycode)); }
}

// (un)register modifiers
void modifier(void (*f)(uint8_t))
{
  if (mods & MOD_BIT(KC_LCTL)) { f(KC_LCTL); }
  if (mods & MOD_BIT(KC_LGUI)) { f(KC_LGUI); }
  if (mods & MOD_BIT(KC_LALT)) { f(KC_LALT); }
  if (mods & MOD_BIT(KC_LSFT)) { f(KC_LSFT); }
  if (mods & MOD_BIT(KC_RSFT)) { f(KC_RSFT); }  // note: qmk macros all use left modifiers
}

// .................................................................. Key event

int8_t key_event(keyrecord_t *record, int8_t state)
{
  if (record->event.pressed) { return state; }
  return 0;
}

// .......................................................... Keycode Primitives

// register shift keycode
void register_shift(uint16_t keycode)
{
  register_code(KC_LSFT);
  register_code(keycode);
}

// unregister shift keycode
void unregister_shift(uint16_t keycode)
{
  unregister_code(keycode);
  unregister_code(KC_LSFT);
}

// register simple key press
void tap_key(uint16_t keycode)
{
  register_code  (keycode);
  unregister_code(keycode);
}

void tap_shift(uint16_t keycode)
{
  register_code  (KC_LSFT);
  tap_key        (keycode);
  unregister_code(KC_LSFT);
}

#define SHIFT   1
#define NOSHIFT 0

void tap_mod(uint16_t mod, uint16_t keycode)
{
  switch (mod) {
  case NOSHIFT:
    tap_key(keycode);
    break;
  case SHIFT:
    tap_shift(keycode);
    break;
  default:
    register_code  (mod);
    tap_key        (keycode);
    unregister_code(mod);
  }
}

static uint16_t key_timer = 0;

// key press for thumb_roll() and lt_shift() macros
bool key_press(uint8_t shift, uint16_t keycode)
{
  if (keycode) {
    if (timer_elapsed(key_timer) < TAPPING_TERM) { tap_mod(shift, keycode); return true; }
  }
  return false;
}

// ALT_T, CTL_T, GUI_T, SFT_T for shifted keycodes
void mt_shift(keyrecord_t *record, uint16_t modifier, uint16_t modifier2, uint16_t keycode)
{
  if (record->event.pressed) {
    key_timer = timer_read();
    register_code(modifier);
    if (modifier2) { register_code(modifier2); }
  }
  else {
    unregister_code(modifier);
    if (modifier2) { unregister_code(modifier2); }
    if (timer_elapsed(key_timer) < TAPPING_TERM) { tap_shift(keycode); }
    key_timer = 0;
  }
}

// remap keycodes to other keycode values via shift for base and caps layers, see process_record_user()
bool map_shift(keyrecord_t *record, uint16_t shift_key, uint8_t shift, uint16_t keycode)
{
  // if modifier and only shift modifier and base layer..
  if (mods && ((mods & MOD_BIT(shift_key)) == mods) && (biton32(layer_state) == _BASE || biton32(layer_state) == _TTCAPS)) {
    if (record->event.pressed) {
      if (!shift) { unregister_code(KC_LSFT); }  // in event of unshifted keycode
      register_code(keycode);
    }
    else {
      unregister_code(keycode);
      if (!shift) { register_code(KC_LSFT); }    // restore SFT_T
    }
    return true;                                 // remap complete, see process_record_user()
  }
  return false;
}

// .................................................... Triple Dance Shift/Layer

static uint8_t dt_shift = 0;

void double_shift(uint16_t keycode, uint8_t layer)
{
  tap_key (keycode);
  if (DT_SHIFT) {
    // set_oneshot_mods(MOD_LSFT);
    // layer_on(layer);
    layer_on         (_SHIFT);
    set_oneshot_layer(_SHIFT, ONESHOT_START);
    dt_shift = 1;
  }
  else { layer_on(layer); }
}

static uint8_t tap_rule = 0;                        // down_rule persistance, see process_record_user()

// tap dance LT (LAYER, KEY) emulation with <KEY><DOWN> -> <KEY><SHIFT> and auto-repeat extensions!
void tap_lt(qk_tap_dance_state_t *state, uint16_t keycode, uint8_t triple, uint8_t layer, uint8_t rule, uint16_t altcode)
{
  uint8_t i;
  if (state->count > 2) {
    if (state->pressed) { register_code(keycode); } // double tap down -> keycode...
    else if (state->count == triple) {              // triple tap -> double keycode + shift
      tap_key     (keycode);
      double_shift(keycode, layer);
    }
    else for (i = 0; i < state->count; i++) { tap_key(keycode); }
  }
  else if (state->count > 1) {
    if (state->count == triple - 1) {
      if (rule == 2) { tap_key(keycode); }          // (.) double tap -> keycode keycode + shift
      double_shift(keycode, layer);
    }
    // just works out that existing function call can apply rule . space space -> . enter + shift
    else if (rule == 2) { double_shift(altcode ? altcode : keycode, layer); } // (.) double tap -> altcode + shift
    else                { double_shift(keycode, layer); }                     // tap down or double tap -> keycode + shift
  }
  else if (state->pressed) { layer_on(layer); }     // down -> shift
  else switch (rule) {                              // see process_record_user()
  case 0:
    modifier(register_code);
    tap_key (keycode);
    modifier(unregister_code);
    return;
  case 1:
    if (altcode) { tap_key (altcode); }
    return;
  case 2:
    double_shift(keycode, layer);
  }
}

void tap_reset(uint16_t keycode, uint8_t layer)
{
  unregister_code(keycode);
  dt_shift ? clear_oneshot_layer_state(ONESHOT_PRESSED) : layer_off(layer);
  dt_shift = 0;
  tap_rule = 0;                                     // clear retained down_rule, see process_record_user()
}

#define REPEATING    0
#define TRIPLE       3

// augment pseudo LT (_RSHIFT, KC_ENT) handling below for rapid <ENTER><SHIFT> sequences
void enter(qk_tap_dance_state_t *state, void *user_data)
{
  tap_lt(state, KC_ENT, TRIPLE, _RSHIFT, tap_rule, 0);  // triple tap -> double enter + shift, down -> enter...
}

void enter_reset(qk_tap_dance_state_t *state, void *user_data)
{
  tap_reset(KC_ENT, _RSHIFT);
}

// augment pseudo LT (_LSHIFT, KC_SPC) handling below for rapid <SPACE><SHIFT> sequences
void space(qk_tap_dance_state_t *state, void *user_data)
{
  tap_lt(state, KC_SPC, REPEATING, _RSHIFT, tap_rule, KC_ENT); // triple tap down -> space...
}

void space_reset(qk_tap_dance_state_t *state, void *user_data)
{
  tap_reset(KC_SPC, _RSHIFT);
}

// ......................................................... Triple Dance Insert

#ifdef HASKELL
void double_max(uint8_t count, uint8_t shift, uint16_t keycode)
{
  if (shift) {
    tap_shift(keycode);
    if (count > 1) { tap_shift(keycode); }
  }
  else {
    tap_key(keycode);
    if (count > 1) { tap_key(keycode); }
  }
}

void colon(qk_tap_dance_state_t *state, void *user_data)
{
  uint8_t i;
  if (state->count > 2) {
    if (state->pressed) { register_shift(KC_SCLN); }
    else if (state->count == 3) { send_string(" :: "); }
    else for (i = 0; i < state->count; i++) { tap_shift(KC_SCLN); }
  }
  else { state->pressed ? register_shift(KC_SCLN) : double_max(state->count, SHIFT, KC_SCLN); }
  reset_tap_dance(state);
}

void colon_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_shift(KC_SCLN);
}

#ifndef EQL_LT
#define EQL_LT _EDIT
#endif

void equal(qk_tap_dance_state_t *state, void *user_data)
{
  uint8_t i;
  if (state->count > 2) {
    if (state->pressed) { register_code(KC_EQL); }
    else if (state->count == 3) { send_string(" /= "); }
    else for (i = 0; i < state->count; i++) { tap_key(KC_EQL); }
  }
  else { state->pressed ? layer_on(EQL_LT) : double_max(state->count, NOSHIFT, KC_EQL); }
  reset_tap_dance(state);
}

void equal_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_EQL);
  layer_off(EQL_LT);
}

void lesser(qk_tap_dance_state_t *state, void *user_data)
{
  uint8_t i;
  if (state->count > 2) {
    if (state->pressed) { register_shift(KC_COMM); }
    else if (state->count == 3) { send_string(" <- "); }
    else for (i = 0; i < state->count; i++) { tap_shift(KC_COMM); }
  }
  else { state->pressed ? register_code(KC_LCTL) : double_max(state->count, SHIFT, KC_COMM); }
  reset_tap_dance(state);
}

void lesser_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_shift(KC_COMM);
  unregister_code(KC_LCTL);
}

void greater(qk_tap_dance_state_t *state, void *user_data)
{
  uint8_t i;
  if (state->count > 2) {
    if (state->pressed) { register_shift(KC_DOT); }
    else if (state->count == 3) { send_string(" -> "); }
    else for (i = 0; i < state->count; i++) { tap_shift(KC_DOT); }
  }
  else { state->pressed ? register_code(KC_LSFT) : double_max(state->count, SHIFT, KC_DOT); }
  reset_tap_dance(state);
}

void greater_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_shift(KC_DOT);
}
#endif

void tilde(qk_tap_dance_state_t *state, void *user_data)
{
  uint8_t i;
  if (state->count > 1) {
    if (state->pressed) { register_shift(KC_GRV); }
    else if (state->count == 2) { send_string("~/"); }
    else for (i = 0; i < state->count; i++) { tap_shift(KC_GRV); }
  }
  else { state->pressed ? register_shift(KC_GRV) : tap_shift(KC_GRV); }
  reset_tap_dance(state);
}

void tilde_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_shift(KC_GRV);
}

// ............................................................ Tap Dance Insert

void asterisk(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) { tap_key(KC_DOT); }
  tap_shift(KC_8);
  reset_tap_dance(state);
}

void comma(qk_tap_dance_state_t *state, void *user_data)
{
  tap_key(KC_COMM);
  if (state->count > 1) { tap_key(KC_SPC); }
  reset_tap_dance(state);
}

void dot(qk_tap_dance_state_t *state, void *user_data)
{
  state->count > 1 ? tap_shift(KC_COLN) : tap_key(KC_DOT);
  reset_tap_dance(state);
}

void emoji(qk_tap_dance_state_t *state, void *user_data)
{
  uint8_t i;
  if (state->count > 1) {
    if (state->pressed) { register_code(KC_SCLN); }
    else if (state->count == 2) { tap_shift(KC_SCLN); tap_key(KC_MINUS); }
    else for (i = 0; i < state->count; i++) { tap_key(KC_SCLN); }
  }
  else { state->pressed ? register_code(KC_SCLN) : double_max(state->count, NOSHIFT, KC_SCLN); }
  reset_tap_dance(state);
}

void emoji_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_SCLN);
}

// compile time macro string, see functions/hardware planck script
void private(qk_tap_dance_state_t *state, void *user_data)
{
#ifdef PRIVATE_STRING
  if (state->count > 1) {
#include "private_string.h"
  }
#endif
  reset_tap_dance(state);
}

// config.h defined string
void send(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) { SEND_STRING(PUBLIC_STRING); }
  reset_tap_dance(state);
}

// ................................................................... Tap Dance

qk_tap_dance_action_t tap_dance_actions[] = {
  [_ASTR] = ACTION_TAP_DANCE_FN         (asterisk)
 ,[_COMM] = ACTION_TAP_DANCE_FN         (comma)
 ,[_DOT]  = ACTION_TAP_DANCE_FN         (dot)
 ,[_ENT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, enter, enter_reset)
 ,[_PRIV] = ACTION_TAP_DANCE_FN         (private)
 ,[_SEND] = ACTION_TAP_DANCE_FN         (send)
 ,[_SPC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, space, space_reset)
 ,[_SCLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, emoji, emoji_reset)
 ,[_TILD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tilde, tilde_reset)
#ifdef HASKELL
 ,[_COLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, colon, colon_reset)
 ,[_LT]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lesser, lesser_reset)
 ,[_GT]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, greater, greater_reset)
 ,[_EQL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, equal, equal_reset)
#endif
};

// .............................................................. Dynamic Layers

#define        LEFT    1
#define        RIGHT   2
static uint8_t thumb = 0;

// rolling thumb combinations, see process_record_user()
// up,   up   -> _BASE
// up,   down -> _RSYMBOL
// down, up   -> _LSYMBOL
// down, down -> _MOUSE                     // see layer keycodes that raise mouse layer

static uint8_t overlayer = 0;

// seamlessly switch left / right thumb layer combinations
void thumb_roll(keyrecord_t *record, uint8_t side, uint8_t shift, uint16_t keycode, uint8_t repeating, uint8_t thumb_dn_layer, uint8_t thumb_up_layer)
{
  if (record->event.pressed) {
    // repeating key does not trigger on first keypress, see process_record_user()
    if (repeating) { tap_mod(shift, keycode); return; }
    layer_on(thumb_dn_layer);
    key_timer  = timer_read();
    thumb     |= side;
  }
  else {
    if (biton32(layer_state) == _MOUSE) { layer_off(_MOUSE); }  // both thumbs needed
    else if (thumb_dn_layer != _MOUSE) { layer_off(thumb_dn_layer); }
    if (!key_press(shift, keycode)) {
      // release any opposing thumb_roll() layer
      if (overlayer) {
        layer_off(overlayer);
        overlayer = 0;
      }
      // opposite thumb down? see left right combination layer table above
      if (thumb & (side == LEFT ? RIGHT : LEFT)) {
        layer_on(thumb_up_layer);
        overlayer = thumb_up_layer;
      }
    }
    clear_mods();
    thumb     &= ~side;
    key_timer  = 0;
  }
}

// extended LT macro for [shift]keycode [modifier]layer
void lt(keyrecord_t *record, uint8_t shift, uint16_t keycode, uint16_t modifier, uint8_t layer)
{
  if (record->event.pressed) {
    key_timer = timer_read();
    if (modifier) { register_code(modifier); }
    layer_on(layer);
  }
  else {
    if (modifier) { unregister_code(modifier); }
    layer_off(layer);
    // for shifted keycodes, hence, LT_SHIFT
    key_press(shift, keycode);
    clear_mods();
    key_timer = 0;
  }
}

// LT for S(keycode)
void lt_shift(keyrecord_t *record, uint16_t keycode, uint8_t layer)
{
  lt(record, SHIFT, keycode, 0, layer);
}

// set layer asap to overcome macro latency errors, notably tap dance, LT usage and..
// inexplicably sets layer_on() faster than can be done in thumb_roll() !!
void tap_layer(keyrecord_t *record, uint8_t layer)
{
  record->event.pressed ? layer_on(layer) : layer_off(layer);
}

// ..................................................................... Keymaps

// void persistant_default_layer_set(uint16_t default_layer)
// {
//   eeconfig_update_default_layer(default_layer);
//   default_layer_set            (default_layer);
// }

static uint16_t tt_keycode = 0;             // current TT keycode

void clear_layers(void)
{
  uint8_t layer;
  for (layer = 0; layer < _END_LAYERS; layer++) { layer_off(layer); }
  mods       = 0;
  key_timer  = 0;
  dt_shift   = 0;
  thumb      = 0;
  overlayer  = 0;
  tt_keycode = 0;
}

static uint8_t double_key = 0;

// dual thumb key to raise number layer
bool raise_number(keyrecord_t *record, uint8_t side)
{
  if (record->event.pressed) {
    double_key |= side;
    if (double_key == (LEFT | RIGHT)) { layer_on(_NUMBER); return true; }
  }
  else {
    double_key &= ~side;
    if (!double_key) { layer_off(_NUMBER); }  // allow single key to continue on layer :-)
  }
  return false;
}

void tt_clear(void)
{
  clear_layers();
  set_single_persistent_default_layer(_BASE);
}

// alternate escape for TT layers, see process_record_user()
void tt_escape(keyrecord_t *record, uint16_t keycode)
{
  if (record->event.pressed) { key_timer = timer_read(); }
  else {
    if (timer_elapsed(key_timer) < TAPPING_TERM) { tt_keycode = keycode; }
    key_timer = 0;
  }
}

// txbolt plover run state
static uint8_t plover = 0;

void toggle_plover(uint8_t state)
{
  if (plover != state) {
#ifdef PLOVER_KEYBIND
#include "plover_keybind.h"
#endif
    plover = state;
  }
}

void base_layer(void)
{
#ifdef AUDIO_ENABLE
  plover ? PLAY_SONG(song_plover_gb) : PLAY_SONG(song_qwerty);
#endif
  clear_layers();
  set_single_persistent_default_layer(_BASE);
  toggle_plover(0);
}

void steno(keyrecord_t *record)
{
  if (record->event.pressed) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(song_plover);
#endif
    clear_layers();
    layer_on(_PLOVER);
    if (!eeconfig_is_enabled()) { eeconfig_init(); }
    keymap_config.raw  = eeconfig_read_keymap();
    keymap_config.nkro = 1;
    eeconfig_update_keymap(keymap_config.raw);
    if (!plover) { toggle_plover(1); }
  }
}

void steno_exit(keyrecord_t *record)
{
  if (record->event.pressed) {
    base_layer();
    toggle_plover(0);
  }
}
