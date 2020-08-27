#pragma once

#define XXX KC_NO

#define LAYOUT_callum(                                          \
    L00, L01, L02, L03, L04,                                    \
    L10, L11, L12, L13, L14,                                    \
    L20, L21, L22, L23, L24,                                    \
                   LT0, LT1,                                    \
                                                                \
    R00, R01, R02, R03, R04,                                    \
    R10, R11, R12, R13, R14,                                    \
    R20, R21, R22, R23, R24,                                    \
    RT0, RT1                                                    \
)                                                               \
LAYOUT_ortho_4x12(                                              \
    L00, L01, L02, L03, L04, XXX, XXX, R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, XXX, XXX, R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, XXX, XXX, R20, R21, R22, R23, R24, \
    XXX, XXX, XXX, LT0, LT1, XXX, XXX, RT0, RT1, XXX, XXX, XXX  \
)
