#ifndef DAISHI_H
#define DAISHI_H

#include "quantum.h"

#define encoder_update(clockwise) encoder_update_user(uint8_t index, clockwise)

// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K00A, K00B, K00C, K00D, K00E, K00F, K010, K011, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K10A, K10B, K10C, K10D, K10E, K10F, K110, K111, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K20A, K20B, K20C, K20D, K20E, K20F, K210, K211, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K30A, K30B, K30C, K30D, K30E, K30F, K310, K311, \
    K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K40A, K40B, K40C, K40D, K40E, K40F, K410, K411, \
    K500, K501, K502, K503, K504, K505, K506, K507, K508, K509, K50A, K50B, K50C, K50D, K50E, K50F, K510, K511, \
    K600, K601, K602, K603, K604, K605, K606, K607, K608, K609, K60A, K60B, K60C, K60D, K60E, K60F, K610, K611 \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K00A, K00B, K00C, K00D, K00E, K00F, K010, K011 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K10A, K10B, K10C, K10D, K10E, K10F, K110, K111 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K20A, K20B, K20C, K20D, K20E, K20F, K210, K211 }, \
    { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K30A, K30B, K30C, K30D, K30E, K30F, K310, K311 }, \
    { K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K40A, K40B, K40C, K40D, K40E, K40F, K410, K411 }, \
    { K500, K501, K502, K503, K504, K505, K506, K507, K508, K509, K50A, K50B, K50C, K50D, K50E, K50F, K510, K511 }, \
    { K600, K601, K602, K603, K604, K605, K606, K607, K608, K609, K60A, K60B, K60C, K60D, K60E, K60F, K610, K611 }  \
}

#define KC_KEYMAP( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K00A, K00B, K00C, K00D, K00E, K00F, K010, K011, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K10A, K10B, K10C, K10D, K10E, K10F, K110, K111, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K20A, K20B, K20C, K20D, K20E, K20F, K210, K211, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K30A, K30B, K30C, K30D, K30E, K30F, K310, K311, \
    K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K40A, K40B, K40C, K40D, K40E, K40F, K410, K411, \
    K500, K501, K502, K503, K504, K505, K506, K507, K508, K509, K50A, K50B, K50C, K50D, K50E, K50F, K510, K511, \
    K600, K601, K602, K603, K604, K605, K606, K607, K608, K609, K60A, K60B, K60C, K60D, K60E, K60F, K610, K611 \
) { \
    { KC_##K000, KC_##K001, KC_##K002, KC_##K003, KC_##K004, KC_##K005, KC_##K006, KC_##K007, KC_##K008, KC_##K009, KC_##K00A, KC_##K00B, KC_##K00C, KC_##K00D, KC_##K00E, KC_##K00F, KC_##K010, KC_##K011 }, \
    { KC_##K100, KC_##K101, KC_##K102, KC_##K103, KC_##K104, KC_##K105, KC_##K106, KC_##K107, KC_##K108, KC_##K109, KC_##K10A, KC_##K10B, KC_##K10C, KC_##K10D, KC_##K10E, KC_##K10F, KC_##K110, KC_##K111 }, \
    { KC_##K200, KC_##K201, KC_##K202, KC_##K203, KC_##K204, KC_##K205, KC_##K206, KC_##K207, KC_##K208, KC_##K209, KC_##K20A, KC_##K20B, KC_##K20C, KC_##K20D, KC_##K20E, KC_##K20F, KC_##K210, KC_##K211 }, \
    { KC_##K300, KC_##K301, KC_##K302, KC_##K303, KC_##K304, KC_##K305, KC_##K306, KC_##K307, KC_##K308, KC_##K309, KC_##K30A, KC_##K30B, KC_##K30C, KC_##K30D, KC_##K30E, KC_##K30F, KC_##K310, KC_##K311 }, \
    { KC_##K400, KC_##K401, KC_##K402, KC_##K403, KC_##K404, KC_##K405, KC_##K406, KC_##K407, KC_##K408, KC_##K409, KC_##K40A, KC_##K40B, KC_##K40C, KC_##K40D, KC_##K40E, KC_##K40F, KC_##K410, KC_##K411 }, \
    { KC_##K500, KC_##K501, KC_##K502, KC_##K503, KC_##K504, KC_##K505, KC_##K506, KC_##K507, KC_##K508, KC_##K509, KC_##K50A, KC_##K50B, KC_##K50C, KC_##K50D, KC_##K50E, KC_##K50F, KC_##K510, KC_##K511 }, \
    { KC_##K600, KC_##K601, KC_##K602, KC_##K603, KC_##K604, KC_##K605, KC_##K606, KC_##K607, KC_##K608, KC_##K609, KC_##K60A, KC_##K60B, KC_##K60C, KC_##K60D, KC_##K60E, KC_##K60F, KC_##K610, KC_##K611 }  \
}

#endif
