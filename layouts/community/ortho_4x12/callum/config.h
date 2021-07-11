#pragma once

#define LAYOUT_callum(                                                                  \
    KEY00, KEY01, KEY02, KEY03, KEY04,               KEY05, KEY06, KEY07, KEY08, KEY09, \
    KEY10, KEY11, KEY12, KEY13, KEY14,               KEY15, KEY16, KEY17, KEY18, KEY19, \
    KEY20, KEY21, KEY22, KEY23, KEY24,               KEY25, KEY26, KEY27, KEY28, KEY29, \
                         KEY30, KEY31,               KEY32, KEY33                       \
)                                                                                       \
LAYOUT_ortho_4x12(                                                                      \
    KEY00, KEY01, KEY02, KEY03, KEY04, KC_NO, KC_NO, KEY05, KEY06, KEY07, KEY08, KEY09, \
    KEY10, KEY11, KEY12, KEY13, KEY14, KC_NO, KC_NO, KEY15, KEY16, KEY17, KEY18, KEY19, \
    KEY20, KEY21, KEY22, KEY23, KEY24, KC_NO, KC_NO, KEY25, KEY26, KEY27, KEY28, KEY29, \
    KC_NO, KC_NO, KC_NO, KEY30, KEY31, KC_NO, KC_NO, KEY32, KEY33, KC_NO, KC_NO, KC_NO  \
)
