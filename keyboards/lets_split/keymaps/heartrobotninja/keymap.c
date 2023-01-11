#include QMK_KEYBOARD_H


extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLE 0
#define _LOWER 1
#define _RAISE 2
#define _AUX 16

/* Layers */
enum
{
  COLE = 0,
  LOWER, // right hand 10 key.
  RAISE, // left hand Fn, right hand symbols.
  AUX,
};

/* Tap Dancery */
enum
{
  TD_BTK,
  TD_TDE,
  TD_LPRN,
  TD_RPRN,
  TD_MIN,
  TD_USC,
};

bool time_travel = false;

// Fillers to make layering more clear
#define ____ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        /* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | ' " `|   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |  = + | ~ ; :|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ( [ {|   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  | ) ] }|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | - , <|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ?  |   |  |   ^  | _ . >|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Lower |Raise | Ctrl | Alt  | Bksp | Spc  |Enter |LShft | ESC  |  <   |   v  |   >  |
 * `-----------------------------------------------------------------------------------'
 */
        [_COLE] = LAYOUT(
            TD(TD_BTK), KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_EQL, TD(TD_TDE),
            TD(TD_LPRN), KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, TD(TD_RPRN),
            TD(TD_MIN), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_SLSH, KC_BSLS, KC_UP, TD(TD_USC),
            LOWER, RAISE, OSM(MOD_LCTL), OSM(MOD_LALT), KC_SPC, KC_BSPC, KC_ENT, OSM(MOD_LSFT), KC_ESC, KC_LEFT, KC_DOWN, KC_RGHT),

        /* Lower
 * ,-----------------------------------------------------------------------------------.
 * | ---- | ---- | ---- | ---- | ---- | ---- |   7  |   8  |   9  |   *  |   /  |   ^  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ---- | ---- | ---- | ---- | ---- | ---- |  4   |   5  |   6  |   +  |   -  | ---- |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ---- | ---- | ---- | ---- | ---- | ---- |  1   |   2  |   3  |   =  | ---- | ---- |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ---- | ---- | ---- | ---- | ---- | ---- | ---- |   0  |   .  | ---- | ---- | ---- |
 * `-----------------------------------------------------------------------------------'
 */
        [_LOWER] = LAYOUT(
            ____, ____, ____, ____, ____, ____, KC_7, KC_8, KC_9, KC_PAST, KC_PSLS, KC_CIRC,
            ____, ____, ____, ____, ____, ____, KC_4, KC_5, KC_6, KC_PPLS, KC_PMNS, ____,
            ____, ____, ____, ____, ____, ____, KC_1, KC_2, KC_3, KC_PEQL, ____, ____,
            ____, ____, ____, ____, ____, ____, ____, KC_0, KC_MNXT, ____, ____, ____),

        /* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |   F4  |  F5  |  F6 |   !  |   @  |   #  |   $  |   %  |  ` ~ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   ^  |   &  |   *  |   (  |   )  |  - _ |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ |  [ { |  ] } |  \ | |  ; : | ' "  |  = + |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |  , < | . >  |  / ? |
 * `-----------------------------------------------------------------------------------'
 */
        [_RAISE] = LAYOUT(
            KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_GRV,
            KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS,
            KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_LBRC, KC_RBRC, KC_BSLS, KC_SCLN, KC_QUOT, KC_EQL,
            ____, ____, ____, ____, ____, ____, ____, ____, ____, KC_COMM, KC_DOT, KC_SLSH),

        /* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Reset| ____ | ____ | ____ | ____ | ____ | ____ | LOCK | ____ | ____ | ____ | VUP  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ____ | ____ |  RUN | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | VDWN |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | PGUP | MUTE |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | HOME | PGDN | END  |
 * `-----------------------------------------------------------------------------------'
 */
        [_AUX] = LAYOUT(
            QK_BOOT, ____, ____, ____, ____, ____, ____, LGUI(KC_L), ____, ____, ____, KC_VOLU,
            ____, ____, LGUI(KC_R), ____, ____, ____, ____, ____, ____, ____, ____, KC_VOLD,
            ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, KC_PGUP, KC_MUTE,
            ____, ____, ____, ____, KC_TAB, KC_DEL, ____, ____, ____, KC_HOME, KC_PGDN, KC_END)

};

qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_BTK] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_GRV),
        [TD_TDE] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_TILD),
        [TD_LPRN] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LPRN),
        [TD_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RPRN),
        [TD_MIN] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_MINS),
        [TD_USC] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_UNDS)};

void persistent_default_layer_set(uint16_t default_layer)
{
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
};

void matrix_scan_user(void){};

void matrix_init_user(void){};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  case COLE:
    if (record->event.pressed)
    {
      persistent_default_layer_set(1UL << _COLE);
    }
    return false;
    break;
  case LOWER:
    if (record->event.pressed)
    {
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _AUX);
    }
    else
    {
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _AUX);
    }
    return false;
    break;
  case RAISE:
    if (record->event.pressed)
    {
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _AUX);
    }
    else
    {
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _AUX);
    }
    return false;
    break;
  case AUX:
    if (record->event.pressed)
    {
      layer_on(_AUX);
    }
    else
    {
      layer_off(_AUX);
    }
    return false;
    break;
  }
  return true;
}
