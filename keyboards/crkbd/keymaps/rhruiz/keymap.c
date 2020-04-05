#include QMK_KEYBOARD_H
#include "rhruiz.h"
#include "rhruiz_kc_keys.h"

extern uint8_t is_master;
#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

#define KC_AFN2 LALT_T(KC_BSPC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_kc(
  //,-----------------------------------.                    ,-----------------------------------.
      TAB ,  Q  ,  W  ,  E  ,  R  ,  T  ,                       Y  ,  U  ,  I  ,  O  ,  P  , BSPC,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
      CESC,  A  ,  S  ,  D  ,  F  ,  G  ,                       H  ,  J  ,  K  ,  L  , SCLN, QUOT,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
      LSFT,  Z  ,  X  ,  C  ,  V  ,  B  ,                       N  ,  M  , COMM, DOT , SLSH, RSFT,
  //|-----+-----+-----+-----+-----+-----+-----|  |-----+-----+-----+-----+-----+-----+-----+-----|
                              LGUI, _FN1, SPC ,    ENT , _FN2, AFN2
                          //`-----------------'  `-----------------'
  ),

  [_KEY_OVERRIDE] = LAYOUT_kc(
  //,-----------------------------------.                    ,-----------------------------------.
          ,     ,     ,     ,     ,     ,                          ,     ,     ,     ,     , DEL ,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,                          ,     ,     ,     ,     , DQUO,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,                          ,     ,     ,     ,     ,     ,
  //|-----+-----+-----+-----+-----+-----+-----|  |-----+-----+-----+-----+-----+-----+-----+-----|
                                  ,     ,     ,        ,     ,
                          //`-----------------'  `-----------------'
    ),

  [_FN1] = LAYOUT_kc(
  //,-----------------------------------.                    ,-----------------------------------.
       GRV,  1  ,  2  ,  3  ,  4  ,  5  ,                       6  ,  7  ,  8  ,  9  ,  0  ,     ,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          , BSLS, LBRC, RBRC,MINUS, PLUS,                          ,     , LPRN, RPRN, COLN,     ,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,                          ,     ,     ,     ,     ,     ,
  //|-----+-----+-----+-----+-----+-----+-----|  |-----+-----+-----+-----+-----+-----+-----+-----|
                                  ,     ,     ,        ,     ,
                          //`-----------------'  `-----------------'
    ),

  [_FN2] = LAYOUT_kc(
  //,-----------------------------------.                    ,-----------------------------------.
      TILD, EXLM,  AT , HASH, DLR , PERC,                      CIRC, AMPR, ASTR, LPRN, RPRN,     ,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          , PIPE, LCBR, RCBR, UNDS, EQL ,                          , LEFT, DOWN,  UP ,RIGHT,     ,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,                      EPIP,     ,  LT ,  GT , QUES,     ,
  //|-----+-----+-----+-----+-----+-----+-----|  |-----+-----+-----+-----+-----+-----+-----+-----|
                                  ,     ,     ,        ,     ,
                          //`-----------------'  `-----------------'
  ),

  [_CFG] = LAYOUT_kc(
  //,-----------------------------------.                    ,-----------------------------------.
      _RST, RTOG, RMOD,     , RSAI, RVAD,                          , _WL , _STP, _SBT, _WR , MAKE,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          , _VUP, _VDN, MUTE, RHUI, RHUD,                          , HOME, PGDN, PGUP, END , _TGN,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     , RSAI, RSAD,                          ,     ,     ,     ,     ,     ,
  //|-----+-----+-----+-----+-----+-----+-----|  |-----+-----+-----+-----+-----+-----+-----+-----|
                                  ,     ,     ,        ,     ,
                          //`-----------------'  `-----------------'
  ),

  [_NUM] = LAYOUT_kc(
  //,-----------------------------------.                    ,-----------------------------------.
          , BTN1, MS_U, BTN2, WH_D,     ,                       7  ,  8  ,  9  , ASTR,     ,     ,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          , MS_L, MS_D, MS_R, WH_U,     ,                       4  ,  5  ,  6  , PLUS,     , _TGN,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,                       1  ,  2  ,  3  , MINS,     ,     ,
  //|-----+-----+-----+-----+-----+-----+-----|  |-----+-----+-----+-----+-----+-----+-----+-----|
                                  ,     ,     ,        ,  0  , DOT
                          //`-----------------'  `-----------------'
    ),

  /* template
  [_LAYER] = LAYOUT_kc(
  //,-----------------------------------.                    ,-----------------------------------.
          ,     ,     ,     ,     ,     ,                          ,     ,     ,     ,     ,     ,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,                          ,     ,     ,     ,     ,     ,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,                          ,     ,     ,     ,     ,     ,
  //|-----+-----+-----+-----+-----+-----+-----|  |-----+-----+-----+-----+-----+-----+-----+-----|
                                  ,     ,     ,        ,     ,
                          //`-----------------'  `-----------------'
    ),
  */
};
// clang-format on

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return rotation; }

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }

    if (is_master) {
        render_crkbd_logo();
    } else {
        render_crkbd_logo();
        oled_scroll_left();  // Turns on scrolling
    }
}

void suspend_power_down_user(void) { oled_off(); }

void suspend_wakeup_init_user(void) { oled_on(); }

bool rhruiz_process_record(uint16_t keycode, keyrecord_t *record) {
    oled_timer = timer_read32();
    return true;
}

#endif

void matrix_init_keymap(void) {
    setPinOutput(B0);
    setPinOutput(D5);
    writePinHigh(D5);
    writePinHigh(B0);
}

void rhruiz_update_layer_colors(layer_state_t state) {
    if (isLeftHand && layer_state_cmp(state, _FN1)) {
        writePinLow(D5); writePinLow(B0); } else if (!isLeftHand && layer_state_cmp(state, _FN2)) { writePinLow(D5);
        writePinLow(B0);
    } else {
        writePinHigh(D5);
        writePinHigh(B0);
    }
}
