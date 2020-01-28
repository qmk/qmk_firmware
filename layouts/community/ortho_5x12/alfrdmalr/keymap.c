#include "alfrdmalr.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// QWERTY 
[_QWERTY] = LAYOUT_ortho_5x12_wrapper(
  K00,     ____NUMROW_L0____, ____NUMROW_R0____, K0B,
  K10,     ____QWERTY_L1____, ____QWERTY_R1____, K1B_ALT,
  K20,     ____QWERTY_L2____, ____QWERTY_R2____, K2B,
  K30,     ____QWERTY_L3____, ____QWERTY_R3____, K3B,
  K40,     _____BASE_L4_____, _____BASE_R4_____, K4B
),

// SYMBOLS 
[_SYMBOLS] = LAYOUT_ortho_5x12_wrapper(
  K00_SYM, ____NUMROW_L0____, ____NUMROW_R0____, K0B_SYM,
  K10_SYM, ____SYMBOL_L1____, ____SYMBOL_R1____, K1B_SYM,
  K20_SYM, ____SYMBOL_L2____, ____SYMBOL_R2____, K2B_SYM,
  K30_SYM, ____SYMBOL_L3____, ____SYMBOL_R3____, K3B_SYM,
  K40_SYM, ____SYMBOL_L4____, ____SYMBOL_R4____, K4B_SYM
),

// NAVIGATION 
[_NAVIGATION] = LAYOUT_ortho_5x12_wrapper(
  K00_NAV, ____NUMROW_L0____, ____NUMROW_R0____, K0B_NAV,
  K10_NAV, __NAVIGATION_L1__, __NAVIGATION_R1__, K1B_NAV,
  K20_NAV, __NAVIGATION_L2__, __NAVIGATION_R2__, K2B_NAV,
  K30_NAV, __NAVIGATION_L3__, __NAVIGATION_R3__, K3B_NAV,
  K40_NAV, __NAVIGATION_L4__, __NAVIGATION_R4__, K4B_NAV
),

// NUMPAD 
[_NUMPAD] = LAYOUT_ortho_5x12_wrapper( 
  K00_NUM, ____NUMROW_L0____, ____NUMROW_R0____, K0B_NUM,
  K10_NUM, ____NUMPAD_L1____, ____NUMPAD_R1____, K1B_NUM,
  K20_NUM, ____NUMPAD_L2____, ____NUMPAD_R2____, K2B_NUM,
  K30_NUM, ____NUMPAD_L3____, ____NUMPAD_R3____, K3B_NUM,
  K40_NUM, ____NUMPAD_L4____, ____NUMPAD_R4____, K4B_NUM 
),

// SETTINGS 
[_SETTINGS] = LAYOUT_ortho_5x12_wrapper( 
  K00_SET, ______TRANS______,  ______TRANS______, K0B_SET,
  K10_SET, ___SETTINGS_L1___,  ___SETTINGS_R1___, K1B_SET,
  K20_SET, ___SETTINGS_L2___,  ___SETTINGS_R2___, K2B_SET,
  K30_SET, ___SETTINGS_L3___,  ___SETTINGS_R3___, K3B_SET,
  K40_SET, ___SETTINGS_L4___,  ___SETTINGS_R4___, K4B_SET
)
};