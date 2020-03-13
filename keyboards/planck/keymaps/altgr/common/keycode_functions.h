
// .......................................................... Keycode Primitives

// register simple key press
void tap_key(uint16_t keycode)
{
  register_code  (keycode);
  unregister_code(keycode);
}

void shift_key(uint16_t keycode)
{
  register_code  (KC_LSFT);
  tap_key        (keycode);
  unregister_code(KC_LSFT);
}

#define SHIFT   1
#define NOSHIFT 0

static uint16_t key_timer = 0;

// key press for thumb_layer() and lt_shift() macros
bool key_press(uint8_t shift, uint16_t keycode)
{
  if (keycode) {
    if (timer_elapsed(key_timer) < TAPPING_TERM) {
      if (shift) {
        shift_key(keycode);
      }
      else {
        tap_key(keycode);
      }
      return true;
    }
  }
  return false;
}

// ALT_T, CTL_T, GUI_T, SFT_T for shifted keycodes
void mt_shift(keyrecord_t *record, uint16_t modifier, uint16_t modifier2, uint16_t keycode)
{
  if (record->event.pressed) {
    key_timer = timer_read();
    register_code(modifier);
    if (modifier2) {
      register_code(modifier2);
    }
  }
  else {
    unregister_code(modifier);
    if (modifier2) {
      unregister_code(modifier2);
    }
    if (timer_elapsed(key_timer) < TAPPING_TERM) {
      shift_key(keycode);
    }
    key_timer = 0;
  }
}

// ................................................................... Mod Masks

// tap dance persistant mods, see process_record_user()
// keyboard_report->mods (?) appears to be cleared by tap dance
static uint8_t mods = 0;

void tap_mods(keyrecord_t *record, uint16_t keycode)
{
  if (record->event.pressed) {
    mods |= MOD_BIT(keycode);
  }
  else {
    mods &= ~(MOD_BIT(keycode));
  }
}

// (un)register modifiers
void modifier(void (*f)(uint8_t))
{
  if (mods & MOD_BIT(KC_LCTL)) {
    (*f)(KC_LCTL);
  }
  if (mods & MOD_BIT(KC_LGUI)) {
    (*f)(KC_LGUI);
  }
  if (mods & MOD_BIT(KC_LALT)) {
    (*f)(KC_LALT);
  }
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
  else {
    layer_on(layer);
  }
}

// tap dance LT (LAYER, KEY) emulation with <KEY><DOWN> -> <KEY><SHIFT> and auto-repeat extensions!
void tap_shift(qk_tap_dance_state_t *state, uint16_t keycode, uint8_t layer)
{
  // double tap plus down
  if (state->count > 2) {
    // double enter shift
    if (keycode == KC_ENT) {
      tap_key     (keycode);
      double_shift(keycode, layer);
    }
    // repeating keycode
    else {
      register_code(keycode);
    }
  }
  // tap plus down (or double tap): keycode (one shot) shift
  else if (state->count > 1) {
    double_shift(keycode, layer);
  }
  // down: shift
  else if (state->pressed) {
    layer_on(layer);
  }
  // tap: keycode
  else {
    modifier(register_code);
    tap_key (keycode);
    modifier(unregister_code);
  }
}

void tap_reset(uint16_t keycode, uint8_t layer)
{
  unregister_code(keycode);
  if (DT_SHIFT && dt_shift) {
    clear_oneshot_layer_state(ONESHOT_PRESSED);
    dt_shift = 0;
  }
  else {
    layer_off(layer);
  }
}

// augment pseudo LT (_RSHIFT, KC_ENT) handling below for rapid <ENTER><SHIFT> sequences
void enter(qk_tap_dance_state_t *state, void *user_data)
{
  tap_shift(state, KC_ENT, _RSHIFT);
}

void enter_reset(qk_tap_dance_state_t *state, void *user_data)
{
  tap_reset(KC_ENT, _RSHIFT);
}

// augment pseudo LT (_LSHIFT, KC_SPC) handling below for rapid <SPACE><SHIFT> sequences
void space(qk_tap_dance_state_t *state, void *user_data)
{
  tap_shift(state, KC_SPC, _LSHIFT);
}

void space_reset(qk_tap_dance_state_t *state, void *user_data)
{
  tap_reset(KC_SPC, _LSHIFT);
}

// ......................................................... Triple Dance Insert

void double_max(uint8_t count, uint8_t shift, uint16_t keycode)
{
  if (shift) {
    shift_key(keycode);
    if (count > 1) {
      shift_key(keycode);
    }
  }
  else {
    tap_key(keycode);
    if (count > 1) {
      tap_key(keycode);
    }
  }
}

void colon(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 2) {
    tap_key  (KC_SPC);
    shift_key(KC_SCLN);
    shift_key(KC_SCLN);
    tap_key  (KC_SPC);
  }
  else {
    double_max(state->count, SHIFT, KC_SCLN);
  }
  reset_tap_dance(state);
}

void eql(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 2) {
    tap_key(KC_SPC);
    tap_key(KC_SLSH);
    tap_key(KC_EQL);
    tap_key(KC_SPC);
  }
  else {
    double_max(state->count, NOSHIFT, KC_EQL);
  }
  reset_tap_dance(state);
}

void greater(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 2) {
    tap_key  (KC_SPC);
    tap_key  (KC_MINS);
    shift_key(KC_DOT);
    tap_key  (KC_SPC);
  }
  else {
    double_max(state->count, SHIFT, KC_DOT);
  }
  reset_tap_dance(state);
}

void lesser(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 2) {
    tap_key  (KC_SPC);
    shift_key(KC_COMM);
    tap_key  (KC_MINS);
    tap_key  (KC_SPC);
  }
  else {
    double_max(state->count, SHIFT, KC_COMM);
  }
  reset_tap_dance(state);
}

void tilde(qk_tap_dance_state_t *state, void *user_data)
{
  // double tap plus down: repeating keycode
  if (state->count > 2) {
    register_code(KC_LSFT);
    register_code(KC_GRV);
  }
  // tap: keycode
  else {
    shift_key(KC_GRV);
    // double tap: unix home directory
    if (state->count > 1) {
      tap_key(KC_SLSH);
    }
  }
}

void tilde_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_GRV);
  unregister_code(KC_LSFT);
}

// ............................................................. Tap Dance Pairs

// tap dance shift rules
#define S_NEVER  0
#define S_SINGLE 1
#define S_DOUBLE 2
#define S_ALWAYS S_SINGLE | S_DOUBLE

void symbol_pair(uint8_t shift, uint16_t left, uint16_t right)
{
  if (shift & S_DOUBLE) {
    shift_key(left);
    shift_key(right);
  }
  else {
    tap_key(left);
    tap_key(right);
  }
}

#define CLOSE 1

// tap dance symbol pairs
void tap_pair(qk_tap_dance_state_t *state, uint8_t shift, uint16_t left, uint16_t right, uint16_t modifier, uint8_t close)
{
  // triple tap: left right with cursor between symbol pair a la vim :-)
  if (state->count > 2) {
    symbol_pair(shift, left, right);
    tap_key    (KC_LEFT);
  }
  // double tap: left right
  else if (state->count > 1) {
    symbol_pair(shift, left, right);
  }
  // down: modifier
  else if (state->pressed) {
    if (modifier) {
      register_code(modifier);
    }
  }
  // tap: left (close: right)
  else {
    if (shift & S_SINGLE) {
      shift_key(close ? right : left);
    }
    else {
      tap_key(close ? right : left);
    }
  }
  if (!modifier) {
    reset_tap_dance(state);
  }
}

void doublequote(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_QUOT, KC_QUOT, 0, 0);
}

void grave(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, KC_GRV, KC_GRV, 0, 0);
}

void lbrace(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, KC_LBRC, KC_RBRC, 0, 0);
}

void lcurly(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_LBRC, KC_RBRC, 0, 0);
}

void lparen(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_9, KC_0, KC_LCTL, 0);
}

void lparen_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_LCTL);
}

void quote(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, KC_QUOT, KC_QUOT, 0, 0);
}

void rangle(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_COMM, KC_DOT, 0, CLOSE);
}

void rbrace(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, KC_LBRC, KC_RBRC, 0, CLOSE);
}

void rcurly(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_LBRC, KC_RBRC, 0, CLOSE);
}

void rparen(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_9, KC_0, 0, CLOSE);
}

void rparen_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_LCTL);
}

// ............................................................ Tap Dance Insert

void comma(qk_tap_dance_state_t *state, void *user_data)
{
  tap_key(KC_COMM);
  if (state->count > 1) {
    tap_key(KC_SPC);
  }
  reset_tap_dance(state);
}

void dot(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    shift_key(KC_COLN);
  }
  else {
    tap_key(KC_DOT);
  }
  reset_tap_dance(state);
}

// compile time macro string, see functions/hardware planck script
void private(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
#ifdef PRIVATE_STRING
#include "private_string.h"
#endif
  }
  reset_tap_dance(state);
}

// config.h defined string
void send(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    SEND_STRING(PUBLIC_STRING);
  }
  reset_tap_dance(state);
}

// .......................................................... Tap Dance One Shot

void caps(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_key(KC_CAPS);
  }
  else {
    set_oneshot_mods(MOD_LSFT);
    register_code   (KC_LSFT);              // on hold down
  }
}

void caps_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_LSFT);
}

// ................................................................... Tap Dance

qk_tap_dance_action_t tap_dance_actions[] = {
  [_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps, caps_reset)
 ,[_COLN] = ACTION_TAP_DANCE_FN         (colon)
 ,[_COMM] = ACTION_TAP_DANCE_FN         (comma)
 ,[_DOT]  = ACTION_TAP_DANCE_FN         (dot)
 ,[_DQOT] = ACTION_TAP_DANCE_FN         (doublequote)
 ,[_ENT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, enter, enter_reset)
 ,[_EQL]  = ACTION_TAP_DANCE_FN         (eql)
 ,[_GRV]  = ACTION_TAP_DANCE_FN         (grave)
 ,[_GT]   = ACTION_TAP_DANCE_FN         (greater)
 ,[_LBRC] = ACTION_TAP_DANCE_FN         (lbrace)
 ,[_LCBR] = ACTION_TAP_DANCE_FN         (lcurly)
 ,[_LPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lparen, lparen_reset)
 ,[_LT]   = ACTION_TAP_DANCE_FN         (lesser)
 ,[_PRIV] = ACTION_TAP_DANCE_FN         (private)
 ,[_QUOT] = ACTION_TAP_DANCE_FN         (quote)
 ,[_RBRC] = ACTION_TAP_DANCE_FN         (rbrace)
 ,[_RCBR] = ACTION_TAP_DANCE_FN         (rcurly)
 ,[_RNGL] = ACTION_TAP_DANCE_FN         (rangle)
 ,[_RPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rparen, rparen_reset)
 ,[_SEND] = ACTION_TAP_DANCE_FN         (send)
 ,[_SPC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, space, space_reset)
 ,[_TILD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tilde, tilde_reset)
};

// .............................................................. Dynamic Layers

#define        LEFT    1
#define        RIGHT   2
static uint8_t thumb = 0;

// LEFT (KC_SPC, S(KC_BSLS)), RIGHT (KC_LEFT, S(KC_LEFT)) opposite thumb combinations, see process_record_user()
// up,   up   -> _BASE
// up,   down -> _SYMBOL
// down, up   -> _NUMBER
// down, down -> _MOUSE                     // see layer keycodes that raise mouse layer
#define THUMBS_DOWN _MOUSE                  // layer

static uint8_t overlayer = 0;

// left right thumb layer combinations
void thumb_layer(keyrecord_t *record, uint8_t side, uint8_t shift, uint16_t keycode, uint8_t thumb_dn_layer, uint8_t thumb_up_layer)
{
  if (record->event.pressed) {
    // layer_on via tap_layer(), see process_record_user()
    key_timer = timer_read();
    thumb     = thumb | side;
  }
  else {
    layer_off(thumb_dn_layer);
    // opposite thumb_layer() thumb may have switched effective layer!
    if (overlayer) {
      layer_off(overlayer);
      overlayer = 0;
    }
    if (!key_press(shift, keycode)) {
      layer_off(THUMBS_DOWN);               // both thumbs needed
      // opposite thumb down? see left right combination layer table above
      if (thumb & (side == LEFT ? RIGHT : LEFT)) {
        layer_on(thumb_up_layer);
        overlayer = thumb_up_layer;
      }
    }
    clear_mods();
    thumb     = thumb & ~side;
    key_timer = 0;
  }
}

// #ifdef STENO_ENABLE
// // LT for steno keycode
// void stn_layer(keyrecord_t *record, uint16_t keycode, uint8_t layer)
// {
//   if (record->event.pressed) {
//     key_timer = timer_read();
//     if (keycode) {
//       process_steno(keycode, record);
//     }
//     layer_on(layer);
//   }
//   else {
//     layer_off(layer);
//     if (keycode) {
//       if (timer_elapsed(key_timer) < TAPPING_TERM) {
//         process_steno(keycode, record);
//       }
//       else {
//         // clear pressed state (request push of updated) process_steno.c and .h
//         // steno_clear_state();
//       }
//     }
//     key_timer = 0;
//   }
// }
// #endif

// LT for S(keycode)
void lt_shift(keyrecord_t *record, uint16_t keycode, uint8_t layer)
{
  if (record->event.pressed) {
    key_timer = timer_read();
    layer_on(layer);
  }
  else {
    layer_off(layer);
    // for shifted keycodes, hence, LT_SHIFT
    key_press(SHIFT, keycode);
    clear_mods();
    key_timer = 0;
  }
}

// set layer asap to overcome macro latency errors, notably tap dance and LT usage
// this routine inexplicably (?) sets layer_on() faster than can be done in thumb_layer()
void tap_layer(keyrecord_t *record, uint8_t layer)
{
  if (record->event.pressed) {
    layer_on(layer);
  }
  else {
    layer_off(layer);
  }
}

// ..................................................................... Keymaps

// void persistant_default_layer_set(uint16_t default_layer)
// {
//   eeconfig_update_default_layer(default_layer);
//   default_layer_set            (default_layer);
// }

void clear_layers(void)
{
  uint8_t layer;
  for (layer = 0; layer < _END_LAYERS; layer++) {
    layer_off(layer);
  }
}

#ifdef CENTER_TT
static uint16_t tt_keycode = 0;             // current TT keycode

void clear_tt(void)
{
  if (tt_keycode == KC_CAPS) {
    tap_key(KC_CAPS);                       // clear capslock
  }
  tt_keycode = 0;
  clear_layers();
  set_single_persistent_default_layer(_BASE);
}
#endif

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
  if (plover) {
    PLAY_SONG(song_plover_gb);
  }
  else {
    PLAY_SONG(song_qwerty);
  }
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
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }
    keymap_config.raw  = eeconfig_read_keymap();
    keymap_config.nkro = 1;
    eeconfig_update_keymap(keymap_config.raw);
    if (!plover) {
      toggle_plover(1);
    }
  }
}

void steno_exit(keyrecord_t *record)
{
  if (record->event.pressed) {
    base_layer();
    toggle_plover(0);
  }
}
