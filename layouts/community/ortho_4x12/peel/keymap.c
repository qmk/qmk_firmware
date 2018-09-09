#include QMK_KEYBOARD_H
#include "action_layer.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _COLEMAK 0
#define _LCOLEMAK _COLEMAK+1
#define _RCOLEMAK _COLEMAK+2
#define _NUMBER 3
#define _NUMSYM 4
#define _SYMBOL 5
#define _MOUSE 6
#define _ADJUST 7

static uint8_t _LSHIFT = _LCOLEMAK;
static uint8_t _RSHIFT = _RCOLEMAK;

enum custom_keycodes {
  COLEMAK = SAFE_RANGE
  ,PS_PERC   // pseudo ALT_T(S(KC_5))            for modified key-codes, see process_record_user()
  ,PS_CIRC   // pseudo GUI_T(S(KC_6))            for modified key-codes, see process_record_user()
  ,PS_DLR    // pseudo SFT_T(S(KC_4))            for modified key-codes, see process_record_user()
  ,PS_LEFT   // pseudo LT   (_MOUSE, S(KC_LEFT)) for modified key-codes, see process_record_user()
  ,PS_PIPE   // pseudo LT   (_MOUSE, S(KC_BSLS)) for modified key-codes, see process_record_user()
  ,BACKLIT
  ,LT_0    = LT (_ADJUST, KC_0)
  ,LT_BSLS = LT (_ADJUST, KC_BSLS)
  ,LT_ESC  = LT (_NUMBER, KC_ESC)
  ,LT_LEFT = LT (_SYMBOL, KC_LEFT)           // see process_record_user() for extended handling
  ,OS_ALT  = OSM(MOD_LALT)
  ,OS_CALT = OSM(MOD_LALT | MOD_LCTL)
  ,OS_CGUI = OSM(MOD_LGUI | MOD_LCTL)
  ,OS_CSFT = OSM(MOD_LSFT | MOD_LCTL)
  ,OS_CTL  = OSM(MOD_LCTL)
  ,OS_GUI  = OSM(MOD_LGUI)
  ,OS_SALT = OSM(MOD_LALT | MOD_LSFT)
  ,OS_SFT  = OSM(MOD_LSFT)
  ,OS_SGUI = OSM(MOD_LGUI | MOD_LSFT)
};

// modifier keys
#define AT_DOWN ALT_T(KC_DOWN)
#define CT_RGHT CTL_T(KC_RGHT)
#define GT_UP   GUI_T(KC_UP)

#define HOME_A  CTL_T(KC_A)
#define HOME_R  GUI_T(KC_R)
#define HOME_S  ALT_T(KC_S)
#define HOME_T  SFT_T(KC_T)
#define HOME_O  CTL_T(KC_O)
#define HOME_I  GUI_T(KC_I)
#define HOME_E  ALT_T(KC_E)
#define HOME_N  SFT_T(KC_N)
#define CTL_TAB CTL_T(KC_TAB)
#define CTL_BSPC CTL_T(KC_BSPC)

#define S_DOWN  S    (KC_DOWN)
#define S_RGHT  S    (KC_RGHT)
#define S_UP    S    (KC_UP)

// tap dance keys
enum tap_dance {
                _CAPS = 0
                ,_COLN
                ,_DQOT
                ,_ENT
                ,_GRV
                ,_GT
                ,_LBRC
                ,_LCBR
                ,_LPRN
                ,_LT
                ,_SHEX
                ,_QUOT
                ,_SPC
                ,_TILD
};

#define TD_CAPS TD(_CAPS)
#define TD_COLN TD(_COLN)
#define TD_PERC TD(_PERC)
#define TD_DQOT TD(_DQOT)
#define TD_ENT  TD(_ENT)
#define TD_GRV  TD(_GRV)
#define TD_GT   TD(_GT)
#define TD_LBRC TD(_LBRC)
#define TD_LCBR TD(_LCBR)
#define TD_LPRN TD(_LPRN)
#define TD_LT   TD(_LT)
#define TD_SHEX TD(_SHEX)
#define TD_QUOT TD(_QUOT)
#define TD_SPC  TD(_SPC)                    // see process_record_user() for extended handling of Spc
#define TD_TILD TD(_TILD)

// keycodes
#define ___x___ KC_TRNS
#ifdef _______
#undef _______
#endif
#define _______ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// ..................................................................... Colemak
// http://www.keyboard-layout-editor.com/#/gists/c5b045c538d84c5df37c1fc0fe485e2a

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   ;  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ↑Alt | ↑GUI |   M  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   D  |   V  | Caps |^Shift|   K  |   H  |   ,  |   .  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc | Space|  Tab | Bksp |  Ent | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_COLEMAK] = LAYOUT_ortho_4x12( \
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    OS_CALT, OS_CGUI,  KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, \
    HOME_A,  HOME_R,  HOME_S,  HOME_T,  KC_G,    OS_SALT, OS_SGUI,  KC_M,    HOME_N,  HOME_E,  HOME_I, HOME_O, \
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    TD_CAPS, OS_CSFT,  KC_K,    KC_H,    KC_COMM, KC_DOT, TD_QUOT, \
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  TD_SPC,  CTL_TAB, CTL_BSPC, TD_ENT,  LT_LEFT, AT_DOWN, GT_UP,  CT_RGHT \
  ),

// ............................................................... Shift Colemak
// http://www.keyboard-layout-editor.com/#/gists/79cdc09e5317d5ea0d84809c49fe9465

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   :  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ↑Alt | ↑GUI |   M  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   Z  |   X  |   C  |   D  |   V  | Caps |^Shift|   K  |   H  |   /  |   ?  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |  f() |  Tab |  Del |   -  | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_LCOLEMAK] = LAYOUT_ortho_4x12( \
    S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_B), OS_CALT, OS_CGUI,  S(KC_J), S(KC_L), S(KC_U), S(KC_Y), TD_COLN, \
    S(KC_A), S(KC_R), S(KC_S), S(KC_T), S(KC_G), OS_SALT, OS_SGUI,  S(KC_M), S(KC_N), S(KC_E), S(KC_I), S(KC_O), \
    S(KC_Z), S(KC_X), S(KC_C), S(KC_D), S(KC_V), TD_CAPS, OS_CSFT,  S(KC_K), S(KC_H), KC_SLSH, KC_QUES, TD_DQOT, \
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  ___x___, CTL_TAB, CTL_BSPC, KC_MINS, PS_LEFT, S_DOWN,  S_UP,    S_RGHT  \
  ),

  // ,-----------------------------------------------------------------------------------.
  // |   Q  |   W  |   F  |   P  |   B  | ^Alt | ^GUI |   J  |   L  |   U  |   Y  |   :  |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |   A  |   R  |   S  |   T  |   G  | ↑Alt | ↑GUI |   M  |   N  |   E  |   I  |   O  |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // |   X  |   V  |   F  |   D  |   B  | Caps |^Shift|   K  |   H  |   ~  |   `  |   "  |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // | Ctrl |  GUI |  Alt |  Esc |   _  | ↑Tab | Bksp |  f() | Left | Down |  Up  | Right|
  // `-----------------------------------------------------------------------------------'

  [_RCOLEMAK] = LAYOUT_ortho_4x12( \
    S(KC_Q), S(KC_W), S(KC_F), S(KC_P), S(KC_B), OS_CALT, OS_CGUI, S(KC_J), S(KC_L), S(KC_U), S(KC_Y), TD_COLN, \
    S(HOME_A), S(HOME_R), S(HOME_S), S(HOME_T), S(KC_G), OS_SALT, OS_SGUI, S(KC_M), S(HOME_N), S(HOME_E), S(HOME_I), S(HOME_O), \
    S(KC_Z), S(KC_X), S(KC_C), S(KC_D), S(KC_V), TD_CAPS, OS_CSFT, S(KC_K), S(KC_H), TD_TILD, TD_GRV,  TD_DQOT, \
    OS_CTL,  OS_GUI,  OS_ALT,  LT_ESC,  KC_UNDS, CTL_TAB, CTL_BSPC, ___x___, PS_LEFT, S_DOWN,  S_UP,    S_RGHT  \
  ),

// ......................................................... Number Keypad Layer
//
// http://www.keyboard-layout-editor.com/#/gists/5e11e5e90ee2b40cb5caf0f9231f23f7

  // .-----------------------------------------------------------------------------------.
  // |      |      | ^Alt |      |      |      |      |      |   7  |   8  |   9  |   /  |
  // |-----------------------------------------------------------------------------------|
  // | Ctrl |  GUI |  Alt | Shift|      |      |      |      |   4  |   5  |   6  |   *  |
  // |-----------------------------------------------------------------------------------|
  // |      |      | ↑Alt |      |      |      |      |      |   1  |   2  |   3  |   -  |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |       |      |  =  |   0  |   .  |   ,  |   +  |
  // '-----------------------------------------------------------------------------------'

  [_NUMBER] = LAYOUT_ortho_4x12( \
    _______, _______, OS_CALT, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_SLSH, \
    OS_CTL,  OS_GUI,  OS_ALT,  TD_SHEX, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_ASTR, \
    _______, _______, OS_SALT, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_MINS, \
    ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, KC_EQL,  LT_0,    KC_DOT,  KC_COMM, KC_PLUS \
  ),

  // .-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |      |   &  |   ~  |   ?  |   :  |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |      |      |      |   $  |   %  |   ^  |   |  |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |      |      |      |   !  |   @  |   #  |   X  |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |  f() |      |      |      | Space|   \  |   <  |   >  |      |
  // '-----------------------------------------------------------------------------------'

  [_NUMSYM] = LAYOUT_ortho_4x12( \
    _______, _______, _______, ___x___, _______, _______, _______, _______, KC_AMPR, KC_TILD, KC_QUES, KC_COLN, \
    ___x___, ___x___, ___x___, ___x___, _______, _______, _______, _______, KC_DLR,  KC_PERC, KC_CIRC, KC_PIPE, \
    _______, _______, _______, ___x___, _______, _______, _______, _______, KC_EXLM, KC_AT,   KC_HASH, KC_X   , \
    ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, KC_SPC,  KC_BSLS, KC_LT,   KC_GT,   _______ \
  ),

// ..................................................... Symbol Navigation Layer
//
// http://www.keyboard-layout-editor.com/#/gists/475b46cf0546fd102b5d7cb729c490a6

  // .-----------------------------------------------------------------------------------.
  // |   {  |   .  |   *  |   &  |   }  |      |      |      | Home |  Up  |  End | PgUp |
  // |-----------------------------------------------------------------------------------|
  // |   (  |   ^  |   %  |   $  |   )  |      |      |      | Left | Down | Right| PgDn |
  // |-----------------------------------------------------------------------------------|
  // |   [  |   #  |   @  |   !  |   ]  |      |      |      |      |   <  |   >  |      |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |   \  |   |  |      |      |      |  f() |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_SYMBOL] = LAYOUT_ortho_4x12( \
    TD_LCBR, KC_DOT,  KC_ASTR, KC_AMPR, KC_RCBR, _______, _______, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, \
    TD_LPRN, PS_CIRC, PS_PERC, PS_DLR,  KC_RPRN, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, \
    TD_LBRC, KC_HASH, KC_AT,   KC_EXLM, KC_RBRC, _______, _______, _______, _______, TD_LT,   TD_GT,   _______, \
    ___x___, ___x___, ___x___, LT_BSLS, PS_PIPE, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___ \
  ),

// ............................................................... Mouse Actions
//
// http://www.keyboard-layout-editor.com/#/gists/863abbf3ae716a267b60337a953588d5

  // .-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |      | Left |  Up  | Right|  Up  |
  // |-----------------------------------------------------------------------------------|
  // |Brite | Btn3 | Btn2 | Btn1 |      |      |      |      | Left | Down | Right| Down |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |      |      |      |      |      |      |      |      |
  // |-----------------------------------------------------------------------------------|
  // |      |      |      |      |  f() |      |      |      |  f() |      |      |      |
  // '-----------------------------------------------------------------------------------'

  [_MOUSE] = LAYOUT_ortho_4x12( \
    _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, \
    BACKLIT, KC_BTN3, KC_BTN2, KC_BTN1, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, ___x___, _______, _______, _______, ___x___, _______, _______, _______ \
  ),


// ................................................................ Adjust Layer
//
// http://www.keyboard-layout-editor.com/#/gists/08f08c811c7dc502617f0758bce59bf6

  // ,-----------------------------------------------------------------------------------.
  // |      |      |      |      |      |      |      |      |      |      |      |      |
  // |------+------+------+------+------+-------------+------+------+------+------+------|
  // |Aud on| Brite|      |      |      |      |      |      |      |      |      |      |
  // |------+------+------+------+------+------|------+------+------+------+------+------|
  // | Reset|      |      |      |      |      |      |      |      |      |      |      |
  // |------+------+------+------+------+------+------+------+------+------+------+------|
  // |      |      |      |  f() |      |      |      |      |  f() |      |      |      |
  // `-----------------------------------------------------------------------------------'

  [_ADJUST] = LAYOUT_ortho_4x12( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    AU_ON,   BACKLIT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, ___x___, _______, _______, _______, _______, ___x___, _______, _______, _______ \
                                 )
};

#ifdef AUDIO_ENABLE
float song_startup  [][2] = SONG(STARTUP_SOUND);
float song_caps_on  [][2] = SONG(CAPS_LOCK_ON_SOUND);
float song_caps_off [][2] = SONG(CAPS_LOCK_OFF_SOUND);
float music_scale   [][2] = SONG(MUSIC_SCALE_SOUND);
float song_goodbye  [][2] = SONG(GOODBYE_SOUND);
#endif

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

#define         SHIFT   1
#define         NOSHIFT 0

static uint16_t key_timer = 0;

// key press for com_layer() and lt_shift() macros
bool key_press(uint16_t keycode, uint8_t shift)
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
void mt_shift(keyrecord_t *record, uint16_t modifier, uint16_t keycode)
{
  if (record->event.pressed) {
    register_code (modifier);
    key_timer = timer_read();
  }
  else {
    unregister_code (modifier);
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

// ............................................................ Tap Dance Layers

void symhex(qk_tap_dance_state_t *state, void *user_data)
{
    layer_on(_NUMSYM);
    set_oneshot_layer(_NUMSYM, ONESHOT_START);
}
void symhex_reset(qk_tap_dance_state_t *state, void *user_data)
{
  clear_oneshot_layer_state(ONESHOT_PRESSED);
}

// ......................................................... Triple Dance Insert

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

// .................................................... Triple Dance Shift/Layer

static uint8_t dt_shift = 0;

// tap dance LT (LAYER, KEY) emulation with <KEY><DOWN> -> <KEY><SHIFT> and auto-repeat extensions!
void tap_shift(qk_tap_dance_state_t *state, uint16_t keycode, uint8_t layer)
{
  // double tap plus down: repeating keycode
  if (state->count > 2) {
    register_code(keycode);
  }
  // tap plus down (or double tap): keycode (one shot) shift
  else if (state->count > 1) {
    tap_key (keycode);
    if (DT_SHIFT) {
      // set_oneshot_mods(MOD_LSFT);
      layer_on(layer);
      set_oneshot_layer(layer, ONESHOT_START);
      dt_shift = 1;
    }
    else {
      layer_on(layer);
    }
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

// tap dance symbol pairs
void tap_pair(qk_tap_dance_state_t *state, uint8_t shift, uint16_t left, uint16_t right, uint8_t modifier)
{
  // triple tap: left right with cursor between symbol pair a la vim :-)
  if (state->count > 2) {
    symbol_pair(shift, left, right);
    tap_key(KC_LEFT);
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
  // tap: left
  else {
    if (shift & S_SINGLE) {
      shift_key(left);
    }
    else {
      tap_key(left);
    }
  }
  if (!modifier) {
    reset_tap_dance(state);
  }
}

void brace(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, KC_LBRC, KC_RBRC, 0);
}

void curly(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_LBRC, KC_RBRC, 0);
}

void doublequote(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_QUOT, KC_QUOT, 0);
}

void grave(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, KC_GRV, KC_GRV, 0);
}

void paren(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_ALWAYS, KC_9, KC_0, KC_LCTL);
}

void paren_reset(qk_tap_dance_state_t *state, void *user_data)
{
  unregister_code(KC_LCTL);
}

void quote(qk_tap_dance_state_t *state, void *user_data)
{
  tap_pair(state, S_NEVER, KC_QUOT, KC_QUOT, 0);
}

// ............................................................ Tap Dance Insert

void colon(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_key(KC_SPC);
    shift_key(KC_SCLN);
    shift_key(KC_SCLN);
    tap_key(KC_SPC);
  }
  else {
    shift_key(KC_SCLN);
  }
  reset_tap_dance(state);
}

void greater(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_key(KC_SPC);
    tap_key(KC_MINS);
    shift_key(KC_DOT);
    tap_key(KC_SPC);
  }
  else {
    shift_key(KC_DOT);
  }
  reset_tap_dance(state);
}

void lesser(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_key(KC_SPC);
    shift_key(KC_COMM);
    tap_key(KC_MINS);
    tap_key(KC_SPC);
  }
  else {
    shift_key(KC_COMM);
  }
  reset_tap_dance(state);
}

// ............................................................ Tap Dance Toggle

void caps(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1) {
    tap_key(KC_CAPS);
  }
  else {
    set_oneshot_mods(MOD_LSFT);
  }
  reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [_CAPS] = ACTION_TAP_DANCE_FN         (caps)
 ,[_COLN] = ACTION_TAP_DANCE_FN         (colon)
 ,[_DQOT] = ACTION_TAP_DANCE_FN         (doublequote)
 ,[_ENT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, enter, enter_reset)
 ,[_GT]   = ACTION_TAP_DANCE_FN         (greater)
 ,[_GRV]  = ACTION_TAP_DANCE_FN         (grave)
 ,[_LBRC] = ACTION_TAP_DANCE_FN         (brace)
 ,[_LCBR] = ACTION_TAP_DANCE_FN         (curly)
 ,[_LPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, paren, paren_reset)
 ,[_LT]   = ACTION_TAP_DANCE_FN         (lesser)
 ,[_SHEX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, symhex, symhex_reset)
 ,[_QUOT] = ACTION_TAP_DANCE_FN         (quote)
 ,[_SPC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, space, space_reset)
 ,[_TILD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tilde, tilde_reset)
};

// .............................................................. Dynamic Layers

#define        LEFT    1
#define        RIGHT   2
static uint8_t thumb = 0;

// LEFT (KC_SPC, S(KC_BSLS)), RIGHT (KC_LEFT, S(KC_LEFT)) opposite thumb combinations, see process_record_user()
// up,   up   -> _COLEMAK
// up,   down -> _SYMBOL
// down, up   -> _NUMBER
// down, down -> _MOUSE
#define THUMBS_DOWN _MOUSE

static uint8_t overlayer = THUMBS_DOWN;

// left right layer combinations
void com_layer(keyrecord_t *record, uint8_t side, uint16_t keycode, uint8_t shift, uint8_t layer, uint8_t default_layer)
{
  if (record->event.pressed) {
    // layer_on via tap_layer(), see process_record_user()
    key_timer = timer_read();
    thumb     = thumb | side;
  }
  else {
    layer_off(layer);
    // opposite com_layer() thumb may have switched effective layer!
    if (overlayer) {
      layer_off(overlayer);
      overlayer = THUMBS_DOWN;
    }
    if (!key_press(keycode, shift)) {
      // opposite thumb down? see left right combination layer table above
      if (thumb & (side == LEFT ? RIGHT : LEFT)) {
        layer_on(default_layer);
        overlayer = default_layer;
      }
    }
    clear_mods();
    thumb     = thumb & ~side;
    key_timer = 0;
  }
}

// LT for S(keycode)
void lt_shift(keyrecord_t *record, uint16_t keycode, uint8_t layer)
{
  if (record->event.pressed) {
    layer_on(layer);
    key_timer = timer_read();
  }
  else {
    layer_off(layer);
    // for shifted keycodes, hence, LT_SHIFT
    key_press(keycode, SHIFT);
    clear_mods();
    key_timer = 0;
  }
}

// set layer asap to overcome macro latency errors, notably tap dance and LT usage
// this routine inexplicably (?) sets layer_on() faster than can be done in com_layer()
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

void persistant_default_layer_set(uint16_t default_layer)
{
  eeconfig_update_default_layer(default_layer);
  default_layer_set            (default_layer);
}

void clear_layers(void)
{
  uint8_t layer;
  for (layer = 0; layer <= _ADJUST; layer++) {
    layer_off(layer);
  }
}


// ........................................................... User Keycode Trap

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
    case AT_DOWN:
      tap_mods(record, KC_LALT);
      break;
    case CT_RGHT:
      tap_mods(record, KC_LCTL);
      break;
    case GT_UP:
      tap_mods(record, KC_LGUI);
      break;
    case LT_ESC:
      tap_layer(record, _NUMBER);
      break;
    case LT_0:
      tap_layer(record, _ADJUST);
      break;
    case LT_LEFT:
      tap_layer(record, _SYMBOL);
      // LT (_SYMBOL, KC_LEFT) left right combination layer
      com_layer(record, RIGHT, 0, 0, _SYMBOL, _LSHIFT);
      break;
    case OS_ALT:
      tap_mods(record, KC_LALT);
      break;
    case OS_CTL:
      tap_mods(record, KC_LCTL);
      break;
    case OS_GUI:
      tap_mods(record, KC_LGUI);
      break;
    case PS_PERC:
      // ALT_T(S(KC_5))
      mt_shift(record, KC_LALT, KC_5);
      break;
    case PS_CIRC:
      // GUI_T(S(KC_6))
      mt_shift(record, KC_LGUI, KC_6);
      break;
    case PS_DLR:
      // SFT_T(S(KC_4))
      mt_shift(record, KC_LSFT, KC_4);
      break;
    case PS_LEFT:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, S(KC_LEFT)) left right combination layer
      com_layer(record, RIGHT, KC_LEFT, SHIFT, _MOUSE, _LSHIFT);
      break;
    case PS_PIPE:
      tap_layer(record, _MOUSE);
      // LT (_MOUSE, S(KC_BSLS)) left right combination layer
      com_layer(record, LEFT, KC_BSLS, SHIFT, _MOUSE, _SYMBOL);
      break;
    case TD_ENT:
      tap_layer(record, _RSHIFT);
      // LT (_RSHIFT, KC_ENT) emulation, see tap dance enter
      break;
    case TD_SPC:
      tap_layer(record, _LSHIFT);
      // LT (_LSHIFT, KC_SPC) left right combination layer, see tap dance space
      com_layer(record, LEFT, 0, 0, _LSHIFT, _SYMBOL);
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
            backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
  }
  return true;
}

// ....................................................................... Audio

void matrix_init_user(void)
{
#ifdef AUDIO_ENABLE
  startup_user();
#endif
}

#ifdef AUDIO_ENABLE
#ifdef BACKLIGHT_ENABLE
void led_set_user(uint8_t usb_led)
{
  static uint8_t old_usb_led = 0;
  _delay_ms(10);                            // gets rid of tick
  if (!is_playing_notes()) {
    if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK))) {
      // if capslock LED is turning on
      PLAY_SONG(song_caps_on);
    }
    else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK))) {
      // if capslock LED is turning off
      PLAY_SONG(song_caps_off);
    }
  }
  old_usb_led = usb_led;
}
#endif

void startup_user(void)
{
  _delay_ms(20);                            // gets rid of tick
  PLAY_SONG(song_startup);
}

void shutdown_user(void)
{
  PLAY_SONG(song_goodbye);
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_SONG(music_scale);
}
#endif
