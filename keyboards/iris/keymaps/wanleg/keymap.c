
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
     K31,	K32,	K33,	K34,	K35,	K36,	GHERKIN,ONEHAND,	K37,	K38,	K39,	K3A,	K3B,	K3C, \
                               ONEHAND,	NUMBER,	ETCETERA,			KC_SPC,	DIRECTION,	KC_RGUI                  \
  )
#define LAYOUT_iris_base_wrapper(...)       LAYOUT_iris_base(__VA_ARGS__)
#define _________________BLANK_48__________________ KC_ESC, _______, _______, _______, _______, GHERKIN, GHERKIN, _______, _______, _______, _______, KC_BSPC

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_GK] = LAYOUT_iris_base_wrapper(
    _______________GherkinLike_0_______________,
    _______________GherkinLike_1_______________,
    _______________GherkinLike_2_______________,
	_______________GherkinLike_3_______________
  ),
  [ONE] = LAYOUT_wrapper(
    _______________Qwerty_Row__0_______________,
    _______________Qwerty_Row__1_______________,
	_______________Qwerty_Row__2_______________,
    KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, SUBTER,  KC_LSFT,		NUMBER, KC_LSFT,		KC_SPC,  SUPRA,   KC_RGUI, KC_RALT, KC_DEL,  KC_RCTL,
												_______,SUBTER, SH_T(KC_SPC),		SH_T(KC_SPC),SUPRA, _______
  ),
  [_QW] = LAYOUT_iris_base_wrapper(
    _______________Qwerty_Row__0_______________,
    _______________Qwerty_Row__1_______________,
    _______________Qwerty_Row__2_______________,
	_______________Qwerty_Row__3_______________
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
  [NUM] = LAYOUT_wrapper(
    _______________NUMBERS_Row_0_______________,
    _______________NUMBERS_Row_1_______________,
	_______________NUMBERS_Row_2_______________,
    _______, _______, _______, _______, _______, _______,		_______, _______,		KC_ENT, KC_RSFT, KC_RGUI, _______, _______, _______,
										_______,_______, _______,		KC_ENT,	KC_RSFT, _______
  ),
  [DIR] = LAYOUT_iris_base_wrapper(
    _____________DIRECTIONS_Row__0_____________,
    _____________DIRECTIONS_Row__1_____________,
    _____________DIRECTIONS_Row__2_____________,
	_____________DIRECTIONS_Row__3_____________
  ),
  [ETC] = LAYOUT_wrapper(
    ______________ETCETERA_Row__0______________,
    ______________ETCETERA_Row__1______________,
	______________ETCETERA_Row__2______________,
    _______, _______, _______, _______, _______, _______,		_______, _______,		LALT(LCTL(KC_DEL)), _______, _______, _______, _______, _______,
												_______,_______, _______,		LALT(LCTL(KC_DEL)),	_______, _______
  )
  
};


void matrix_init_keymap(void) {
  DDRD &= ~(1<<5);
  PORTD &= ~(1<<5);

  DDRB &= ~(1<<0);
  PORTB &= ~(1<<0);
}
