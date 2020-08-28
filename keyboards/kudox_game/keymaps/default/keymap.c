#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _LIGHT 2

// Shortcut to make keymap more readable
#define SYM_L   MO(_SYMB)
#define KC_ALEN LALT_T(KC_ENT)
#define ES_LIGH LT(_LIGHT, KC_ESC)

#define CT_COPY   LCTL(KC_C)
#define CT_PASTE  LCTL(KC_V)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐
     ES_LIGH ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,
  //└────────┼────────┼────────┼────────┼────────┼────────┤
              KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,
  //┌────────┼────────┼────────┼────────┼────────┼────────┼────────┐
     CT_COPY ,CT_PASTE,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐
     KC_LSFT ,KC_Z                      ,KC_X    ,KC_C    ,KC_V    ,
  //├────────┼────────┘                 └────────┴────────┼────────┼────────┐
     KC_LCTL                                              ,SYM_L   ,KC_SPC
  //└────────┘                                            └────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,
  //└────────┼────────┼────────┼────────┼────────┼────────┤
              KC_GRV   ,KC_UP   ,KC_PIPE ,KC_LCBR ,KC_RCBR ,
  //┌────────┼────────┼────────┼────────┼────────┼────────┼────────┐
     _______ ,_______ ,KC_LEFT ,KC_DOWN ,KC_RIGHT,KC_LBRC ,KC_RBRC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐
     _______ ,KC_BSPC                   ,KC_DEL  ,KC_LPRN ,KC_RPRN ,
  //├────────┼────────┘                 └────────┴────────┼────────┼────────┐
     _______                                              ,_______ ,_______
  //└────────┘                                            └────────┴────────┘
  ),

  [_LIGHT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,RGB_HUI ,RGB_HUD ,RGB_SAI ,RGB_SAD ,RGB_VAI ,
  //└────────┼────────┼────────┼────────┼────────┼────────┤
              RGB_M_P ,RGB_M_SW,RGB_M_X ,RGB_M_B ,RGB_VAD ,
  //┌────────┼────────┼────────┼────────┼────────┼────────┼────────┐
     _______ ,_______ ,RGB_M_SN,RGB_M_G ,RGB_M_R ,RGB_M_K ,RGB_M_T ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐
     _______ ,RGB_M_T                   ,XXXXXXX ,RGB_VAI ,RGB_VAD ,
  //├────────┼────────┘                 └────────┴────────┼────────┼────────┐
     _______                                              ,RGB_MOD ,RGB_TOG
  //└────────┘                                            └────────┴────────┘
  )

};

// Runs just one time when the keyboard initializes.
#ifdef RGBLIGHT_ENABLE
void eeconfig_init_user(void) {
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
};
#endif
