#include QMK_KEYBOARD_H
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE,
  _FN1,
  _FN2,
  _FN3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
  //┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
     KC_ESC    ,KC_1      ,KC_2      ,KC_3      ,KC_4      ,KC_5      ,
  //└──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
                KC_Q      ,KC_W      ,KC_E      ,KC_R      ,KC_T      ,
  //┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐
     LCTL(KC_C),LCTL(KC_V),KC_A      ,KC_S      ,KC_D      ,KC_F      ,KC_G      ,
  //├──────────┼──────────┼──────────┴──────────┼──────────┼──────────┼──────────┤
     KC_LSFT   ,KC_Z                            ,KC_X      ,KC_C      ,KC_V      ,
  //├──────────┼──────────┘                     └──────────┴──────────┼──────────┼──────────┐
     KC_LCTL                                                          ,TO(_FN1)  ,KC_SPC
  //└──────────┘                                                      └──────────┴──────────┘
  ),

  [_FN1] = LAYOUT(
  //┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
     KC_TRNS   ,KC_6      ,KC_7      ,KC_8      ,KC_9      ,KC_0      ,
  //└──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
                KC_GRV    ,KC_UP     ,KC_PIPE   ,KC_LCBR   ,KC_RCBR   ,
  //┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐
     KC_TRNS   ,KC_TRNS   ,KC_LEFT   ,KC_DOWN   ,KC_RIGHT  ,KC_LBRC   ,KC_RBRC   ,
  //├──────────┼──────────┼──────────┴──────────┼──────────┼──────────┼──────────┤
     KC_TRNS   ,KC_BSPC                         ,KC_DEL    ,KC_LPRN   ,KC_RPRN   ,
  //├──────────┼──────────┘                     └──────────┴──────────┼──────────┼──────────┐
     TO(_FN2)                                                         ,TO(_BASE) ,KC_TRNS
  //└──────────┘                                                      └──────────┴──────────┘
  ),

  [_FN2] = LAYOUT(
  //┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
     KC_TRNS   ,RGB_HUI   ,RGB_HUD   ,RGB_SAI   ,RGB_SAD   ,RGB_VAI   ,
  //└──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
                RGB_M_P   ,RGB_M_SW  ,RGB_M_X   ,RGB_M_B   ,RGB_VAD   ,
  //┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐
     KC_TRNS   ,KC_TRNS   ,RGB_M_SN  ,RGB_M_G   ,RGB_M_R   ,RGB_M_K   ,RGB_M_T   ,
  //├──────────┼──────────┼──────────┴──────────┼──────────┼──────────┼──────────┤
     KC_TRNS   ,RGB_M_T                         ,KC_DEL    ,RGB_VAI   ,RGB_VAD   ,
  //├──────────┼──────────┘                     └──────────┴──────────┼──────────┼──────────┐
     TO(_FN1)                                                         ,RGB_MOD   ,RGB_TOG
  //└──────────┘                                                      └──────────┴──────────┘
  ),


  [_FN3] = LAYOUT(
  //┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
     KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,
  //└──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
                KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,
  //┌──────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┐
     KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,
  //├──────────┼──────────┼──────────┴──────────┼──────────┼──────────┼──────────┤
     KC_TRNS   ,KC_TRNS                         ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,
  //├──────────┼──────────┘                     └──────────┴──────────┼──────────┼──────────┐
     KC_TRNS                                                          ,KC_TRNS   ,KC_TRNS
  //└──────────┘                                                      └──────────┴──────────┘
  )
};


#ifdef RGBLIGHT_ENABLE
void eeconfig_init_user(void) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
};
#endif
