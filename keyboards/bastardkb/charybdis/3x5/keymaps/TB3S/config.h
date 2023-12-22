#pragma once

////KEYMAP CONFIG////
//Tap Hold:
#define PERMISSIVE_HOLD
#define TAPPING_TERM 185
#define TAPPING_TERM_PER_KEY

//Combos:
#define COMBO_VARIABLE_LEN
#define COMBO_TERM 60
#define COMBO_SHOULD_TRIGGER

//Capsword:
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

////HARDWARE CONFIG////
//Trackball:
  //undefine charybdis default configuration
#undef ROTATIONAL_TRANSFORM_ANGLE
#undef POINTING_DEVICE_INVERT_X
  //define Wimads trackball configuration
#define POINTING_DEVICE_INVERT_Y
#define CHARYBDIS_MINIMUM_SNIPING_DPI 300
#define CHARYBDIS_MINIMUM_DEFAULT_DPI 700
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#define CHARYBDIS_DRAGSCROLL_BUFFER_SIZE 2

//Elite-c pinout:
  //undefine charybdis default configuration
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef MATRIX_ROW_PINS_RIGHT
#undef MATRIX_COL_PINS_RIGHT
#undef SOFT_SERIAL_PIN
#undef PMW33XX_CS_PIN
  //define Wimads pinout configuration
#define MATRIX_ROW_PINS       { B5, F7, F6, B6 }
#define MATRIX_COL_PINS       { E6, C6, B1, B3, B2 }
#define MATRIX_ROW_PINS_RIGHT { B5, F7, F6, B6 }
#define MATRIX_COL_PINS_RIGHT { E6, C6, F1, C7, D5 }
#define SOFT_SERIAL_PIN D0
#define PMW33XX_CS_PIN F0
