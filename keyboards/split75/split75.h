#pragma once

#include "quantum.h"

// Number of keys in rows
// 0 + 7 / 9
// 2 + 7 / 8
// 2 + 6 / 9
// 2 + 6 / 8
// 2 + 6 / 8
// 2 + 5 / 7

#define LAYOUT( \
            K05, K15, K25, K35, K45, K55, K65, K75, K85, K95, K105, K115, K125, K135, K86, K87, \
  K47, K46, K04, K14, K24, K34, K44, K54, K64, K74, K84, K94, K104, K114, K124,       K96, K97, \
  K37, K36, K03, K13, K23, K33, K43, K53,      K73, K83, K93, K103, K113, K123, K133, K106, K107, \
  K27, K26, K02, K12, K22, K32, K42, K52,      K72, K82, K92, K102, K112, K122,       K116, K117, \
  K17, K16, K01,      K21, K31, K41, K51, K61, K71, K81, K91, K101, K111,       K131, K126, K127, \
  K07, K06, K00, K10, K20, K30, K40,           K70,           K100, K110, K120, K130, K136, K137  \
){ \
  { K00,    K10,    K20,    K30,    K40,    KC_NO,  KC_NO,  K70,    KC_NO,  KC_NO,  K100,   K110,   K120,   K130 }, \
  { K01,    KC_NO,  K21,    K31,    K41,    K51,    K61,    K71,    K81,    K91,    K101,   K111,   KC_NO,  K131 }, \
  { K02,    K12,    K22,    K32,    K42,    K52,    KC_NO,  K72,    K82,    K92,    K102,   K112,   K122,        }, \
  { K03,    K13,    K23,    K33,    K43,    K53,    KC_NO,  K73,    K83,    K93,    K103,   K113,   K123,   K133 }, \
  { K04,    K14,    K24,    K34,    K44,    K54,    K64,    K74,    K84,    K94,    K104,   K114,   K124,        }, \
  { K05,    K15,    K25,    K35,    K45,    K55,    K65,    K75,    K85,    K95,    K105,   K115,   K125,   K135 }, \
  { K06,    K16,    K26,    K36,    K46,    KC_NO,  KC_NO,  KC_NO,  K86,    K96,    K106,   K116,   K126,   K136 }, \
  { K07,    K17,    K27,    K37,    K47,    KC_NO,  KC_NO,  KC_NO,  K87,    K97,    K107,   K117,   K127,   K137 }  \
}

#define NUMLOCK_LED_PIN D0
#define CAPSLOCK_LED_PIN D1
#define SCROLLLOCK_LED_PIN D6
