#include "numpad20.h"

#define KC_ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    LEFT,RGHT, UP ,DOWN, \
     P7 , P8 , P9 ,PLUS, \
     P4 , P5 , P6 ,MINS, \
     P1 , P2 , P3 , ENT, \
     P0 ,DOT ,RGHT, TAB \
    )
};

const uint16_t PROGMEM fn_actions[] = {
};
