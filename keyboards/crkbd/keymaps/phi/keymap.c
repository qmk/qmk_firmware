#include QMK_KEYBOARD_H

extern uint8_t is_master;

/* GLOBAL VARS */

#define BASE      0
#define RAISE     1
#define FUNCTION  2
#define GARAKE    3
#define GARARAISE 4
#define TENKEY    5
#define MOUSE     6
#define WHEEL     7

#define L_BASE      0
#define L_RAISE     (2 << (RAISE - 1))
#define L_FUNCTION  (2 << (FUNCTION - 1))
#define L_GARAKE    (2 << (GARAKE - 1))
#define L_GARARAISE (2 << (GARARAISE - 1))
#define L_TENKEY    (2 << (TENKEY - 1))
#define L_MOUSE     (2 << (MOUSE - 1))
#define L_WHEEL     (2 << (WHEEL - 1))

/* FEATURES */

#ifdef RGBLIGHT_ENABLE
#include "./rgb.c"
#endif
#ifdef TAP_DANCE_ENABLE
#include "dance.c"
#endif
#ifdef SSD1306OLED
#include "./oled.c"
#endif

/* TAPDANCE ACTIONS */

#ifdef TAP_DANCE_ENABLE
enum tapdance_actions {
  TD_ESC_FUNC,
  TD_GARAKE1,
  TD_GARAKE2,
  TD_GARAKE3,
  TD_GARAKE4,
  TD_GARAKE5,
  TD_GARAKE6,
  TD_GARAKE7,
  TD_GARAKE8,
  TD_GARAKE9,
  TD_GARAKE0_RAISE
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_FUNC]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_finished,  esc_reset),
  [TD_GARAKE7]       = ACTION_TAP_DANCE_FN(garake7),
  [TD_GARAKE8]       = ACTION_TAP_DANCE_FN(garake8),
  [TD_GARAKE9]       = ACTION_TAP_DANCE_FN(garake9),
  [TD_GARAKE4]       = ACTION_TAP_DANCE_FN(garake4),
  [TD_GARAKE5]       = ACTION_TAP_DANCE_FN(garake5),
  [TD_GARAKE6]       = ACTION_TAP_DANCE_FN(garake6),
  [TD_GARAKE1]       = ACTION_TAP_DANCE_FN(garake1),
  [TD_GARAKE2]       = ACTION_TAP_DANCE_FN(garake2),
  [TD_GARAKE3]       = ACTION_TAP_DANCE_FN(garake3),
  [TD_GARAKE0_RAISE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, garake0_finished, garake0_reset)
};
#endif

/* KEYCODE DEFINITIONS */

#define KC_____ KC_TRNS
#define KC_XXXX KC_NO

#define KC_D_MOUS LT(MOUSE, KC_D)
#define KC_L1_RAI LT(RAISE, KC_LANG1)
#define KC_L2_ALT LALT_T(KC_LANG2)
#define KC_BASE   TO(BASE)
#define KC_GARAKE TG(GARAKE)
#define KC_TENKEY TG(TENKEY)
#define KC_WEEL   MO(WHEEL)
#define KC_SFT_EN LSFT_T(KC_ENT)
#define KC_CTR_SP LCTL_T(KC_SPC)

#ifdef TAP_DANCE_ENABLE
#define KC_ESC_FN  TD(TD_ESC_FUNC)
#define KC_GK1     TD(TD_GARAKE1)
#define KC_GK2     TD(TD_GARAKE2)
#define KC_GK3     TD(TD_GARAKE3)
#define KC_GK4     TD(TD_GARAKE4)
#define KC_GK5     TD(TD_GARAKE5)
#define KC_GK6     TD(TD_GARAKE6)
#define KC_GK7     TD(TD_GARAKE7)
#define KC_GK8     TD(TD_GARAKE8)
#define KC_GK9     TD(TD_GARAKE9)
#define KC_GK0R    TD(TD_GARAKE0_RAISE)
#else
#define KC_ESC_FN  LT(FUNCTION, KC_ESC)
#define KC_GK1     KC_1
#define KC_GK2     KC_2
#define KC_GK3     KC_3
#define KC_GK4     KC_4
#define KC_GK5     KC_5
#define KC_GK6     KC_6
#define KC_GK7     KC_7
#define KC_GK8     KC_8
#define KC_GK9     KC_9
#define KC_GK0R    LT(RAISE, KC_0)
#endif

#define KC_RST  RESET
#define KC_MUP  KC_MS_U
#define KC_MDN  KC_MS_D
#define KC_MLFT KC_MS_L
#define KC_MRGT KC_MS_R
#define KC_WUP  KC_WH_U
#define KC_WDN  KC_WH_D
#define KC_WLFT KC_WH_L
#define KC_WRGT KC_WH_R
#define KC_ACEL KC_MS_ACCEL2

/* KEYMAPS */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    JYEN , Q    , W    , E    , R    , T    ,                  Y    , U    , I    , O    , P    , MINS , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    LCTL , A    , S    ,D_MOUS, F    , G    ,                  H    , J    , K    , L    , SCLN , QUOT , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    LSFT , Z    , X    , C    , V    , B    ,                  B    , N    , M    , COMM , DOT  , SLSH , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------|
                               L2_ALT, SPC  ,ESC_FN,    TAB  , ENT  ,L1_RAI \
//                            `--------------------'  `--------------------'
),

[RAISE] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    BSPC , 1    , 2    , 3    , 4    , 5    ,                  6    , 7    , 8    , 9    , 0    , EQL  , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , BSLS , LCBR , LPRN , LBRC ,                  RBRC , RPRN , RCBR , PIPE , UP   , PLUS , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , EXLM , AT   , HASH , DLR  , PERC ,                  CIRC , AMPR , ASTR , LEFT , DOWN , RGHT , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , RST  ,   GARAKE, ____ , XXXX  \
//                            `--------------------'  `--------------------'
),

[FUNCTION] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , F1   , F2   , F3   , F4   , F5   ,                  F6   , F7   , F8   , F9   , PSCR , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , LGUI ,                  ____ , ____ , ____ , ____ , PGUP , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , ____ , ____ , HOME , PGDN , END , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , XXXX ,    ____ , ____ , ____  \
//                            `--------------------'  `--------------------'
),

[GARAKE] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,                 TENKEY, GK7  , GK8  , GK9  , BSPC , MINS , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  LANG2, GK4  , GK5  , GK6  , SCLN , QUOT , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  LANG1, GK1  , GK2  , GK3  , DOT  , SLSH , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , BASE ,   CTR_SP,SFT_EN, GK0R  \
//                            `--------------------'  `--------------------'
),

[GARARAISE] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ESC  , BTN1 , MUP  , BTN2 , ____ , EQL  , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  TAB  , MLFT , MDN  , MRGT , UP   , PLUS , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , WUP  , WDN  , LEFT , DOWN , RGHT , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , ____ ,    ____ , ____ , XXXX  \
//                            `--------------------'  `--------------------'
),

[TENKEY] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , 7    , 8    , 9    , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , 4    , 5    , 6    , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , 1    , 2    , 3    , ____ , ____ , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , ____ ,    ____ , ____ , 0     \
//                            `--------------------'  `--------------------'
),

[MOUSE] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , WEEL , ____ , ACEL , ____ ,                  MLFT , MDN  , MUP  , MRGT , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , BTN1 , BTN2 ,                  ____ , ____ , ____ , ____ , ____ , ____ , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , ____ ,    ____ , ____ , ____  \
//                            `--------------------'  `--------------------'
),

[WHEEL] = LAYOUT_kc( \
//,-----------------------------------------.                ,-----------------------------------------.
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , ____ , ____ , ____ , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  WRGT , WUP  , WDN  , WLFT , ____ , ____ , \
//|------+------+------+------+------+------|                |------+------+------+------+------+------|
    ____ , ____ , ____ , ____ , ____ , ____ ,                  ____ , ____ , ____ , ____ , ____ , ____ , \
//`------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------'
                                ____ , ____ , ____ ,    ____ , ____ , ____  \
//                            `--------------------'  `--------------------'
),

};

/* USER TASKS */

void keybaord_post_init_user (void) {
  #ifdef RGBLIGHT_ENABLE
    update_rgblight(false);
  #endif
}

void matrix_init_user(void) {
  #ifdef SSD1306OLED
    oled_init();
  #endif
}

void matrix_scan_user(void) {
  #ifdef SSD1306OLED
    oled_update();
  #endif
  #ifdef RGBLIGHT_ENABLE
    update_rgblight(false);
  #endif
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
 #ifdef SSD1306OLED
  oled_record_event(keycode, record);
 #endif
  return true;
}
