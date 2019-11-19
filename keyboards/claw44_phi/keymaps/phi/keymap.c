#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  BASE = 0,
  RAISE,
  FUNCTION,
  MOUSE,
  WHEEL
};

enum custom_keycodes {
  KC_ACEL = SAFE_RANGE,
  KC_WEEL
};

#define KC_____   KC_TRNS
#define KC_XXXX   KC_NO

#define KC_RAISE  MO(RAISE)
#define KC_ESC_FN LT(FUNCTION, KC_ESC)
#define KC_D_MOUS LT(MOUSE, KC_D)

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

  [BASE] = LAYOUT_kc( \
//,-----------------------------------------. ,-----------------------------------------.
    JYEN , Q    , W    , E    , R    , T    ,   Y    , U    , I    , O    , P    , MINS , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    LCTL , A    , S    ,D_MOUS, F    , G    ,   H    , J    , K    , L    , SCLN , QUOT , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    LSFT , Z    , X    , C    , V    , B    ,   B    , N    , M    , COMM , DOT  , SLSH , \
//`------+------+------+------+------+------| |------+------+------+------+------+------'
                  LALT ,LANG2 , SPC  ,ESC_FN,   TAB  , ENT  ,LANG1 ,RAISE \
//              `---------------------------' `---------------------------'
  ),

  [RAISE] = LAYOUT_kc( \
//,-----------------------------------------. ,-----------------------------------------.
    BSPC , 1    , 2    , 3    , 4    , 5    ,   6    , 7    , 8    , 9    , 0    , EQL  , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , BSLS , LCBR , LPRN , LBRC ,   RBRC , RPRN , RCBR , PIPE , UP   , PLUS , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , EXLM , AT   , HASH , DLR  , PERC ,   CIRC , AMPR , ASTR , LEFT , DOWN , RGHT , \
//`------+------+------+------+------+------| |------+------+------+------+------+------'
                  ____ , ____ , ____ , ____ ,   RST  , ____ , XXXX , ____ \
//              `---------------------------' `---------------------------'
  ),

  [FUNCTION] = LAYOUT_kc( \
//,-----------------------------------------. ,-----------------------------------------.
    ____ , F1   , F2   , F3   , F4   , F5   ,   F6   , F7   , F8   , F9   , PSCR , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , LGUI ,   ____ , ____ , ____ , ____ , PGUP , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , HOME , PGDN , END , \
//`------+------+------+------+------+------| |------+------+------+------+------+------'
                  ____ , ____ , ____ , XXXX ,   ____ , ____ , ____ , ____ \
//              `---------------------------' `--------------------'
  ),

  [MOUSE] = LAYOUT_kc( \
//,-----------------------------------------. ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , WEEL , ____ , ACEL , ____ ,   MLFT , MDN  , MUP  , MRGT , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , BTN1 , BTN2 ,   ____ , ____ , ____ , ____ , ____ , ____ , \
//`------+------+------+------+------+------| |------+------+------+------+------+------'
                  ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____  \
//              `---------------------------' `---------------------------'
  ),

  [WHEEL] = LAYOUT_kc( \
//,-----------------------------------------. ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,   WRGT , WUP  , WDN  , WLFT , ____ , ____ , \
//|------+------+------+------+------+------| |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____ , ____ , ____ , \
//`------+------+------+------+------+------| |------+------+------+------+------+------'
                  ____ , ____ , ____ , ____ ,   ____ , ____ , ____ , ____  \
//              `---------------------------' `---------------------------'
  ),

};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_master) {
    return OLED_ROTATION_180;
  } else {
    return OLED_ROTATION_0;
  }
}

#include "../../lib/host_led_state_reader.c"
#include "../../lib/logo_reader.c"

void oled_task_user(void) {
  if (is_master) {
    oled_write_ln(read_host_led_state(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif

extern uint8_t mk_time_to_max, mk_wheel_time_to_max, mk_max_speed, mk_wheel_max_speed, mk_delay, mk_interval;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
   case KC_ACEL:
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
