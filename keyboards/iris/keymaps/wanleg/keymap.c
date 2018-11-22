
#include QMK_KEYBOARD_H
#include "wanleg.h"


#define LAYOUT_iris_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, \
	K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C  \
  ) \
  LAYOUT_wrapper( \
     K01,	K02,	K03,	K04,	K05,	K06,						K07,	K08,	K09,	K0A,	K0B,	K0C, \
     K11,	K12,	K13,	K14,	K15,	K16,						K17,	K18,	K19,	K1A,	K1B,	K1C, \
     K21,	K22,	K23,	K24,	K25,	K26,						K27,	K28,	K29,	K2A,	K2B,	K2C, \
     K31,	K32,	K33,	K34,	K35,	K36,	_______, _______,	K37,	K38,	K39,	K3A,	K3B,	K3C, \
                               _______, _______, _______,			_______, _______, _______                  \
  )
#define LAYOUT_iris_base_wrapper(...)       LAYOUT_iris_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_GK] = LAYOUT_iris_base_wrapper(
    _______________GherkinLike_0_______________,
    _______________GherkinLike_1_______________,
    _______________GherkinLike_2_______________,
	_______________GherkinLike_3_OneHand_______
  ),
  [ONE] = LAYOUT_wrapper(
    _______________Qwerty_Row__0_______________,
    _______________Qwerty_Row__1_______________,
	_______________Qwerty_Row__2_______________,
	KC_LCTL, KC_LGUI, KC_LALT, GHERKIN, SUBTER, SH_T(KC_SPC),		_______, _______,		SH_T(KC_SPC), SUPRA, KC_RGUI, KC_RALT, GHERKIN, KC_RCTL,
												_______, _______, _______,		_______, _______, _______
  ),
  [SUP] = LAYOUT_iris_base_wrapper(
    ________________SUPRA_Row_0________________,
    ________________SUPRA_Row_1________________,
    ________________SUPRA_Row_2________________,
	________________SUPRA_Row_3________________
  ),
  [SUB] = LAYOUT_iris_base_wrapper(
    _______________SUBTER_Row__0_______________,
    _______________SUBTER_Row__1_______________,
    _______________SUBTER_Row__2_______________,
	_______________SUBTER_Row__3_______________
  ),
  [NUM] = LAYOUT_iris_base_wrapper(
    _______________NUMBERS_Row_0_______________,
    _______________NUMBERS_Row_1_______________,
	_______________NUMBERS_Row_2_______________,
	_______________NUMBERS_Row_3_______________
  ),
  [DIR] = LAYOUT_iris_base_wrapper(
    _____________DIRECTIONS_Row__0_____________,
    _____________DIRECTIONS_Row__1_____________,
    _____________DIRECTIONS_Row__2_____________,
	_______, _______, ONEHAND, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [ETC] = LAYOUT_iris_base_wrapper(
    ______________ETCETERA_Row__0______________,
    ______________ETCETERA_Row__1______________,
	______________ETCETERA_Row__2______________,
	______________ETCETERA_Row__3______________
  )
  
};


void matrix_init_keymap(void) {
  DDRD &= ~(1<<5);
  PORTD &= ~(1<<5);

  DDRB &= ~(1<<0);
  PORTB &= ~(1<<0);
}
