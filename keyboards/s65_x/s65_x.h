#ifndef S60X_H
#define S60X_H

#include "quantum.h"

// There's an extra 2 x 5 column on the left. Not sure what that's all about
// ANSI has more standard width shift, delete, and enter keys, doesn't use all of the 1U keys
#define LAYOUT_ansi( \
  K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014, K015, \
  K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, \
  K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, \
  K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, K315, \
  K400, K401, K402,                   K408,                   K410, K411, K412, K413, K414, K415  \
) { \
  { KC_NO, KC_NO, K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  KC_NO, K014, K015 }, \
  { KC_NO, KC_NO, K100,  KC_NO, K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114, K115 }, \
  { KC_NO, KC_NO, K200,  KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214, K215 }, \
  { KC_NO, KC_NO, KC_NO, K300,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  KC_NO, K313,  K314, K315 }, \
  { KC_NO, KC_NO, K400,  K401,  K402,  KC_NO, KC_NO, KC_NO, K408,  KC_NO, KC_NO, KC_NO, K410,  K411,  K412,  K413,  K414, K415 }  \
}


#define LAYOUT_iso( \
  K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014, K015, \
  K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,       K115, \
  K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, \
  K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, K315, \
  K400, K401, K402,                   K408,                   K410, K411, K412, K413, K414, K415  \
) { \
  { KC_NO, KC_NO, K000, K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  KC_NO, K014,  K015 }, \
  { KC_NO, KC_NO, K100, KC_NO, K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K214,  K115 }, \
  { KC_NO, KC_NO, K200, KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO, K215 }, \
  { KC_NO, KC_NO, K300, K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  KC_NO, K313,  K314,  K315 }, \
  { KC_NO, KC_NO, K400, K401,  K402,  KC_NO, KC_NO, KC_NO, K408,  KC_NO, KC_NO, KC_NO, K410,  K411,  K412,  K413,  K414,  K415 }  \
}
void matrix_init_user(void);
void matrix_scan_user(void);

#endif
