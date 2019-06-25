#include "ergo42.h"

/* LAYER DEFINITIONS */

#define BASE     0
#define RAISE    1
#define MOUSE    3
#define WHEEL    4
#define FUNCTION 5

/* KEYCODE DEFINITIONS */

enum custom_keycodes {
    KC_ACEL = SAFE_RANGE,
    KC_WEEL
};

/* invalid / blank keys */
#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

/* layers */
#define KC_D_MOUS LT(MOUSE, KC_D)
#define KC_L1_RAI LT(RAISE, KC_LANG1)
#define KC_L2_ALT LALT_T(KC_LANG2)
#define KC_ESC_FN LT(FUNCTION, KC_ESC)

/* aliases */
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

[BASE] = LAYOUT_kc_ortho_4x14( \
//,------+----------------------------------.             ,-----------------------------------------.
    JYEN , Q    , W    , E    , R    , T    , XXXX , XXXX , Y    , U    , I    , O    , P    , MINS , \
//|------+------+------+------+------+------|             |------+------+------+------+------+------|
    LCTL , A    , S    ,D_MOUS, F    , G    , XXXX , XXXX , H    , J    , K    , L    , SCLN , QUOT , \
//|------+------+------+------+------+------|             |------+------+------+------+------+------|
    LSFT , Z    , X    , C    , V    , B    , XXXX , XXXX , B    , N    , M    , COMM , DOT  , SLSH , \
//`---------------------------+------+------+------.-------------+------+------+--------------------'
    XXXX , XXXX , XXXX , XXXX ,L2_ALT, SPC  ,ESC_FN, TAB  , ENT  ,L1_RAI, XXXX , XXXX , XXXX , XXXX   \
//                            `--------------------'--------------------'
),

[RAISE] = LAYOUT_kc_ortho_4x14( \
//,------+----------------------------------.             ,-----------------------------------------.
    BSPC , 1    , 2    , 3    , 4    , 5    , XXXX , XXXX , 6    , 7    , 8    , 9    , 0    , EQL  , \
//|------+------+------+------+------+------|             |------+------+------+------+------+------|
    ____ , ____ , BSLS , LCBR , LPRN , LBRC , XXXX , XXXX , RBRC , RPRN , RCBR , PIPE , UP   , PLUS , \
//|------+------+------+------+------+------|             |------+------+------+------+------+------|
    ____ , EXLM , AT   , HASH , DLR  , PERC , XXXX , XXXX , CIRC , AMPR , ASTR , LEFT , DOWN , RGHT , \
//`---------------------------+------+------+------.--------------+-----+-----+---------------------'
    XXXX , XXXX , XXXX , XXXX , ____ , ____ , ____ , RST  , ____ , XXXX , XXXX , XXXX , XXXX , XXXX   \
//                            `--------------------'--------------------'
),

[FUNCTION] = LAYOUT_kc_ortho_4x14( \
//,------+----------------------------------.             ,-----------------------------------------.
    ____ , ____ , ____ , PGUP , ____ , ____ , XXXX , XXXX , ____ , ____ , UP   , ____ , PSCR , BSPC , \
//|------+------+------+------+------+------|             |------+------+------+------+------+------|
    ____ , ____ , HOME , PGDN , END  , LGUI , XXXX , XXXX , ____ , LEFT , DOWN , RGHT , ____ , ____ , \
//|------+------+------+------+------+------|             |------+------+------+------+------+------|
    ____ , F1   , F2   , F3   , F4   , F5   , XXXX , XXXX , F6   , F7   , F8   , F9   , F10  , ____ , \
//`---------------------------+------+------+------.--------------+-----+-----+---------------------'
    XXXX , XXXX , XXXX , XXXX , ____ , ____ , ____ , ____ , ____ , ____ , XXXX , XXXX , XXXX , XXXX   \
//                            `--------------------'--------------------'
),

[MOUSE] = LAYOUT_kc_ortho_4x14( \
//,------+----------------------------------.             ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ , XXXX , XXXX , ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------|             |------+------+------+------+------+------|
    ____ , ____ , WEEL , ____ , ACEL , ____ , XXXX , XXXX , MLFT , MDN  , MUP  , MRGT , ____ , ____ , \
//|------+------+------+------+------+------|             |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , BTN1 , BTN2 , XXXX , XXXX , ____ , ____ , ____ , ____ , ____ , ____ , \
//`---------------------------+------+------+------.--------------+-----+-----+---------------------'
    XXXX , XXXX , XXXX , XXXX , ____ , ____ , ____ , ____ , ____ , ____ , XXXX , XXXX , XXXX , XXXX   \
//                            `--------------------'--------------------'
),

[WHEEL] = LAYOUT_kc_ortho_4x14( \
//,------+----------------------------------.             ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ , XXXX , XXXX , ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------|             |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ , XXXX , XXXX , WRGT , WUP  , WDN  , WLFT , ____ , ____ , \
//|------+------+------+------+------+------|             |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ , XXXX , XXXX , ____ , ____ , ____ , ____ , ____ , ____ , \
//`---------------------------+------+------+------.--------------+-----+-----+---------------------'
    XXXX , XXXX , XXXX , XXXX , ____ , ____ , ____ , ____ , ____ , ____ , XXXX , XXXX , XXXX , XXXX   \
//                            `--------------------'--------------------'
),

};

extern uint8_t mk_time_to_max, mk_wheel_time_to_max, mk_max_speed, mk_wheel_max_speed, mk_delay, mk_interval;

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
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
        return false;
    }
    return true;
}
