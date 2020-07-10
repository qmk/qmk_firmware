#include QMK_KEYBOARD_H
#ifdef COMBO_ENABLE

const uint16_t PROGMEM _combo_0[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM _combo_1[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM _combo_2[] = {KC_A, KC_T, COMBO_END};
const uint16_t PROGMEM _combo_3[] = {KC_A, KC_N, COMBO_END};
const uint16_t PROGMEM _combo_4[] = {KC_A, KC_I, COMBO_END};
const uint16_t PROGMEM _combo_5[] = {KC_A, KC_O, COMBO_END};
const uint16_t PROGMEM _combo_6[] = {KC_A, KC_P, COMBO_END};
const uint16_t PROGMEM _combo_7[] = {KC_S, KC_E, COMBO_END};
const uint16_t PROGMEM _combo_8[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM _combo_9[] = {KC_S, KC_N, COMBO_END};
const uint16_t PROGMEM _combo_10[] = {KC_S, KC_I, COMBO_END};
const uint16_t PROGMEM _combo_11[] = {KC_S, KC_O, COMBO_END};
const uint16_t PROGMEM _combo_12[] = {KC_S, KC_P, COMBO_END};
const uint16_t PROGMEM _combo_13[] = {KC_E, KC_T, COMBO_END};
const uint16_t PROGMEM _combo_14[] = {KC_E, KC_N, COMBO_END};
const uint16_t PROGMEM _combo_15[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM _combo_16[] = {KC_E, KC_O, COMBO_END};
const uint16_t PROGMEM _combo_17[] = {KC_E, KC_P, COMBO_END};
const uint16_t PROGMEM _combo_18[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM _combo_19[] = {KC_T, KC_I, COMBO_END};
const uint16_t PROGMEM _combo_20[] = {KC_T, KC_O, COMBO_END};
const uint16_t PROGMEM _combo_21[] = {KC_T, KC_P, COMBO_END};
const uint16_t PROGMEM _combo_22[] = {KC_N, KC_I, COMBO_END};
const uint16_t PROGMEM _combo_23[] = {KC_N, KC_O, COMBO_END};
const uint16_t PROGMEM _combo_24[] = {KC_N, KC_P, COMBO_END};
const uint16_t PROGMEM _combo_25[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM _combo_26[] = {KC_I, KC_P, COMBO_END};
const uint16_t PROGMEM _combo_27[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM _combo_28[] = {KC_P, KC_S, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(_combo_0, KC_W),
    COMBO(_combo_1, KC_X),
    COMBO(_combo_2, KC_F),
    COMBO(_combo_3, KC_Q),
    COMBO(_combo_4, KC_Z),
    COMBO(_combo_5, KC_LPRN),
    COMBO(_combo_6, KC_SLASH),
    COMBO(_combo_7, KC_D),
    COMBO(_combo_8, KC_C),
    COMBO(_combo_9, KC_J),
    COMBO(_combo_10, KC_K),
    COMBO(_combo_11, KC_DOT),
    COMBO(_combo_12, KC_RPRN),
    COMBO(_combo_13, KC_R),
    COMBO(_combo_14, KC_Y),
    COMBO(_combo_15, KC_COMMA),
    COMBO(_combo_16, KC_MINUS),
    COMBO(_combo_17, KC_QUOTE),
    COMBO(_combo_18, KC_B),
    COMBO(_combo_19, KC_V),
    COMBO(_combo_20, KC_G),
    COMBO(_combo_21, KC_BSPACE),
    COMBO(_combo_22, KC_H),
    COMBO(_combo_23, KC_U),
    COMBO(_combo_24, KC_M),
    COMBO(_combo_25, KC_L),
    COMBO(_combo_26, KC_EXLM),
    COMBO(_combo_27, KC_SCOLON),
    COMBO(_combo_28, KC_LPRN),
};
#endif
#include "rhruiz.h"
#include "layouts/kc_keys.h"

#define KC_ZALT LALT_T(KC_Z)

#ifndef HOME_ROW_MODS
#    undef ________L_BL_R4________
#    define ________L_BL_R4________ ZALT, X, C, V, B
#endif

#define KC_ALDE LALT_T(KC_DEL)
#define KC_ALT0 LALT_T(KC_0)

#define KC_TFN2 LT(_FN2, KC_TAB)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_kc_wrapper(
  //,-----------------------------------.                    ,-----------------------------------.
      TAB ,   ________L_BL_R2________   ,                        ________R_BL_R2________   , BSPC,
  //|-----+-----------------------------|                    |-----------------------------+-----|
      CESC,   ________L_BL_R3________   ,                        ________R_BL_R3________   , QUOT,
  //|-----+-----------------------------|                    |-----------------------------+-----|
      LSFT,   ________L_BL_R4________   ,                        ________R_BL_R4________   ,TDSNU,
  //|-----+-----------------+-----+-----+-----|  |-----+-----+-----+-----------------------+-----|
                              LGUI, _FN1, _CSP,    ENTS, TFN2, ALBS
                          //`-----------------'  `-----------------'
  ),

  [_GAME] = LAYOUT_kc(
  //,-----------------------------------.                    ,-----------------------------------.
          ,  A  ,  S  ,  E  ,  T  ,     ,                          ,  N  ,   I ,  O  ,  P  ,     ,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,                          ,     ,     ,     ,     , _TGM,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,                          ,     ,     ,     ,     ,     ,
  //|-----+-----+-----+-----+-----+-----+-----|  |-----+-----+-----+-----+-----+-----+-----+-----|
                                  ,     ,     ,        ,     ,
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

  [_FN1] = LAYOUT_kc_wrapper(
  //,-----------------------------------.                    ,-----------------------------------.
      TILD,   ________L_LWR_2________   ,                        ________R_LWR_2________   ,     ,
  //|-----+-----------------------------|                    |-----------------------------+-----|
          ,   ________L_LWR_3________   ,                        ________R_LWR_3________   ,     ,
  //|-----+-----------------------------|                    |-----------------------------+-----|
          ,   ________L_LWR_4________   ,                        ________R_LWR_4________   ,     ,
  //|-----+-----------------+-----+-----+-----|  |-----+-----+-----+-----------------------+-----|
                                  ,     ,     ,        ,     , ALDE
                          //`-----------------'  `-----------------'
    ),

  [_FN2] = LAYOUT_kc_wrapper(
  //,-----------------------------------.                    ,-----------------------------------.
      GRV ,   ________L_RSE_2________   ,                        ________R_RSE_2________   ,     ,
  //|-----+-----------------------------|                    |-----------------------------+-----|
          ,   ________L_RSE_3________   ,                        ________R_RSE_3________   ,     ,
  //|-----+-----------------------------|                    |-----------------------------+-----|
          ,   ________L_RSE_4________   ,                        ________R_RSE_4________   ,     ,
  //|-----+-----------------+-----+-----+-----|  |-----+-----+-----+-----------------------+-----|
                                  ,     ,     ,        ,     ,
                          //`-----------------'  `-----------------'
  ),

  [_CFG] = LAYOUT_kc_wrapper(
  //,-----------------------------------.                    ,-----------------------------------.
      _RST,   ________L_CFG_2________   ,                        ________R_CFG_2________   , MAKE,
  //|-----+-----------------------------|                    |-----------------------------+-----|
      _TGM,   ________L_CFG_3________   ,                        ________R_CFG_3________   , _TGN,
  //|-----+-----------------------------|                    |-----------------------------+-----|
          ,   ________L_CFG_4________   ,                        ________R_CFG_4________   ,     ,
  //|-----+-----------------+-----+-----+-----|  |-----+-----+-----+-----------------------+-----|
                                  ,     ,     ,        ,     ,
                          //`-----------------'  `-----------------'
  ),

  [_NUM] = LAYOUT_kc(
  //,-----------------------------------.                    ,-----------------------------------.
          ,     , BTN1, MS_U, BTN2, WH_D,                      ASTR,  7  ,  8  ,  9  , MINS,     ,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     , MS_L, MS_D, MS_R, WH_U,                      SLSH,  4  ,  5  ,  6  , PLUS, _TGN,
  //|-----+-----+-----+-----+-----+-----|                    |-----+-----+-----+-----+-----+-----|
          ,     ,     ,     ,     ,     ,                      COMM,  1  ,  2  ,  3  , DOT ,     ,
  //|-----+-----+-----+-----+-----+-----+-----|  |-----+-----+-----+-----+-----+-----+-----+-----|
                                  ,     ,     ,        ,     , ALT0
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

void rhruiz_update_layer_colors(layer_state_t state) {
#ifdef COMBO_ENABLE
    if (layer_state_cmp(state, _GAME)) {
        combo_enable();
    } else {
        combo_disable();
    }
#endif
#ifndef OLED_DRIVER_ENABLE
    writePinHigh(D5);
    writePinHigh(B0);

    if (layer_state_cmp(state, _NUM)) {
        writePinLow(D5);
        writePinLow(B0);
    }
#endif
}
