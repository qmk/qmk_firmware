#ifndef ROADKIT_H
#define ROADKIT_H

#include "quantum.h"

// This is a shortcut to help you visually see your layout.
#define KEYMAP( \
    K00, K01, K02, K03, \
    K10, K11, K12,      \
    K20, K21, K22, K23, \
    K30,      K32       \
) \
{ \
    { K00, K01,   K02, K03   }, \
    { K10, K11,   K12, KC_NO }, \
    { K20, K21,   K22, K23   }, \
    { K30, KC_NO, K32, KC_NO }  \
}

#define SINGLES_KEYMAP( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33  \
) \
{ \
    { K00,   K01,   K02,   K03 }, \
    { K10,   K11,   K12,   K13 }, \
    { K20,   K21,   K22,   K23 }, \
    { K30,   K31,   K32,   K33 }  \
}

#define LAYOUT_ortho_4x4 SINGLES_KEYMAP

#endif
