#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  BASE = 0,
  RAISE,
  CURSOR,
  CURSOR_ACL,
  FUNCTION,
  MOUSE,
  WHEEL
};

enum custom_keycodes {
  KC_ACCL = SAFE_RANGE,
  KC_WEEL
};

#define KC_____   KC_TRNS
#define KC_XXXX   KC_NO

#define KC_D_MOUS LT(MOUSE, KC_D)
#define KC_C_ALT  LALT_T(KC_C)
#define KC_M_ALT  LALT_T(KC_M)
#define KC_N_RAI  LT(RAISE, KC_N)
#define KC_V_RAI  LT(RAISE, KC_V)
#define KC_S_UNDS LSFT_T(KC_UNDS)
#define KC_S_CUR  LT(CURSOR, KC_S)
#define KC_FN_ENT LT(FUNCTION, KC_ENT)
#define KC_CTL_TB LCTL_T(KC_TAB)
#define KC_CACL   MO(CURSOR_ACL)

#define KC_RST  RESET
#define KC_MUP  KC_MS_U
#define KC_MDN  KC_MS_D
#define KC_MLFT KC_MS_L
#define KC_MRGT KC_MS_R
#define KC_WUP  KC_WH_U
#define KC_WDN  KC_WH_D
#define KC_WLFT KC_WH_L
#define KC_WRGT KC_WH_R

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* removed: LBRC, RBRC(, LCBR, RCBR) */

  [BASE] = LAYOUT_kc( \
//,-----------------------------------------. ,-----------------------------------------.
    JYEN , Q    , W    , E    , R    , T    ,   Y    , U    , I    , O    , P    , MINS , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
   CTL_TB, A    , S_CUR,D_MOUS, F    , G    ,   H    , J    , K    , L    , SCLN ,FN_ENT, \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    LSFT , Z    , X    , C_ALT, V_RAI, SPC  ,   B    , N_RAI, M_ALT, COMM , DOT  , SLSH   \
//`-----------------------------------------' `-----------------------------------------'
  ),

  /* removed: LPRN, RPRN */

  [RAISE] = LAYOUT_kc( \
//,-----------------------------------------. ,------------------------------------------.
    BSPC , 1    , 2    , 3    , 4    , 5    ,   6    , 7    , 8    , 9    , 0    , EQL  , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , EXLM , AT   , HASH , DLR  , PERC ,   CIRC , AMPR , ASTR , QUOT , ____ , PLUS , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , LANG2, LANG1, ESC  ,   TAB  , ____ , ____ , ____ , PIPE , BSLS   \
//`------+------+------+------+------+------' `------+------+------+------+------+------'
  ),

  [CURSOR] = LAYOUT_kc(                                                 \
//,-----------------------------------------. ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____ , \
//,------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , CACL , ____ , ____ ,   LEFT , DOWN , UP   , RGHT , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____   \
//`------+------+------+------+------+------' `------+------+------+------+------+------'
  ),

  [CURSOR_ACL] = LAYOUT_kc(                                                 \
//,-----------------------------------------. ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,   HOME , PGDN , PGUP , END  , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____   \
//`------+------+------+------+------+------' `------+------+------+------+------+------'
  ),

  [FUNCTION] = LAYOUT_kc( \
//,-----------------------------------------. ,-----------------------------------------.
    ____ , F1   , F2   , F3   , F4   , F5   ,   F6   , F7   , F8   , F9   , PSCR , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    RST  , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , LGUI , ____ ,   ____ , ____ , ____ , ____ , ____ , ____   \
//`------+------+------+------+------+------' `------+------+------+------+------+------'
  ),

  [MOUSE] = LAYOUT_kc( \
//,-----------------------------------------. ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , WEEL , ____ , ACCL , ____ ,   MLFT , MDN  , MUP  , MRGT , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , BTN1 , BTN2 ,   ____ , ____ , ____ , ____ , ____ , ____   \
//`------+------+------+------+------+------' `------+------+------+------+------+------'
  ),

  [WHEEL] = LAYOUT_kc( \
//,-----------------------------------------. ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,   WRGT , WUP  , WDN  , WLFT , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____   \
//`------+------+------+------+------+------' `------+------+------+------+------+------'
  ),

};

bool get_ignore_mod_tap_interrupt(uint16_t keycode) {
  switch (keycode) {
   case KC_C_ALT: case KC_M_ALT:
    return true;
   default:
    return false;
  }
}

extern uint8_t mk_time_to_max, mk_wheel_time_to_max, mk_max_speed, mk_wheel_max_speed, mk_delay, mk_interval;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
   case KC_ACCL:
    if (record->event.pressed) {
      mk_max_speed = MOUSEKEY_ACL_MAX_SPEED;
      mk_wheel_max_speed = MOUSEKEY_ACL_WHEEL_MAX_SPEED;
      mk_time_to_max = 0;
      mk_wheel_time_to_max = 0;
    } else {
      mk_max_speed = MOUSEKEY_MAX_SPEED;
      mk_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
      mk_time_to_max = MOUSEKEY_TIME_TO_MAX;
      mk_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;
    }
    return false;
   case KC_WEEL:
    if (record->event.pressed) {
      mk_delay = MOUSEKEY_WHEEL_DELAY / 10;
      mk_interval = MOUSEKEY_WHEEL_INTERVAL;
      layer_on(WHEEL);
    } else {
      mk_delay = MOUSEKEY_DELAY / 10;
      mk_interval = MOUSEKEY_INTERVAL;
      layer_off(WHEEL);
    }
    break;
  }
  return true;
}
