#ifndef DZ60_H
#define DZ60_H

#include "quantum.h"

// Corresponding changes to the layout names and/or definitions must also be made to info.json


// 标准配列
/* Standard arrangement / LAYOUT
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │
 * ├────┼───┴┬──┴─┬─┴───┴──┬┴───┼───┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
 * │40  │41  │43  │44      │46  │48        │4a │4b │4c │4d │4e │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, \
    k40, k41,      k43, k44,      k46,      k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,  k05,   k06,  k07,   k08,  k09,   k0a,  k0b,  k0c,   k0d,  k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,  k15,   k16,  k17,   k18,  k19,   k1a,  k1b,  k1c,   k1d,  k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,  k25,   k26,  k27,   k28,  k29,   k2a,  k2b,  k2c,   k2d,  KC_NO }, \
    { k30,  k31,   k32,   k33,  k34,  k35,   k36,  k37,   k38,  k39,   k3a,  k3b,  KC_NO, k3d,  k3e   }, \
    { k40,  k41,   KC_NO, k43,  k44,  KC_NO, k46,  KC_NO, k48,  KC_NO, k4a,  k4b,  k4c,   k4d,  k4e   }  \
}

/* LAYOUT_true_hhkb
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │
 * ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴──┬┴───┴┬──┴┬─────┴───┤
 * │▓▓▓▓▓│41 │43   │46 (6u)                │4a   │4b │▓▓▓▓▓▓▓▓▓│
 * └─────┴───┴─────┴───────────────────────┴─────┴───┴─────────┘
*/
#define LAYOUT_true_hhkb( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,       \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, \
         k41,      k43,            k46,               k4a, k4b  \
) { \
    { k00,   k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,  k0b,  k0c,   k0d,   k0e   }, \
    { k10,   KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,   k1d,   k1e   }, \
    { k20,   KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,   k2d,   KC_NO }, \
    { k30,   k31,   k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  KC_NO, k3d,   k3e   }, \
    { KC_NO, k41,   KC_NO, k43,  KC_NO, KC_NO, k46,  KC_NO, KC_NO, KC_NO, k4a,  k4b,  KC_NO, KC_NO, KC_NO }  \
}

/* LAYOUT_60_hhkb
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │
 * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤
 * │▓▓▓▓▓│41 │43   │46 (7u)                    │4b   │4d │▓▓▓▓▓│
 * └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
*/
#define LAYOUT_60_hhkb( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, \
         k41,      k43,           k46,                     k4b,      k4d       \
) { \
    { k00,   k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,   k0b,  k0c,   k0d,  k0e   }, \
    { k10,   KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,   k1b,  k1c,   k1d,  k1e   }, \
    { k20,   KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,   k2b,  k2c,   k2d,  KC_NO }, \
    { k30,   KC_NO, k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,   k3b,  KC_NO, k3d,  k3e   }, \
    { KC_NO, k41,   KC_NO, k43,  KC_NO, KC_NO, k46,  KC_NO, KC_NO, KC_NO, KC_NO, k4b,  KC_NO, k4d,  KC_NO }  \
}

// 带方向配列
/* Directional arrangement | LAYOUT_directional
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┬───┤
 * │30     │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3c │3d │3e │
 * ├────┬──┴─┬─┴──┬┴───┴───┼───┴┬──┴───┴───┼───┼───┼───┼───┼───┤
 * │40  │41  │43  │44      │46  │48        │4a │4b │4c │4d │4e │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/
#define LAYOUT_directional( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41,      k43, k44,      k46,      k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,  k05,   k06,  k07,   k08,  k09,   k0a,  k0b,  k0c,  k0d,  k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,  k15,   k16,  k17,   k18,  k19,   k1a,  k1b,  k1c,  k1d,  k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,  k25,   k26,  k27,   k28,  k29,   k2a,  k2b,  k2c,  k2d,  KC_NO }, \
    { k30,  KC_NO, k32,   k33,  k34,  k35,   k36,  k37,   k38,  k39,   k3a,  k3b,  k3c,  k3d,  k3e   }, \
    { k40,  k41,   KC_NO, k43,  k44,  KC_NO, k46,  KC_NO, k48,  KC_NO, k4a,  k4b,  k4c,  k4d,  k4e   }  \
}

/* LAYOUT_all
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├───┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┬───┤
 * │30 │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3c │3d │3e │
 * ├───┴┬──┴─┬─┴──┬┴───┴───┼───┴┬──┴───┴───┼───┼───┼───┼───┼───┤
 * │40  │41  │43  │44      │46  │48        │4a │4b │4c │4d │4e │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/
#define LAYOUT_all( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
    k40, k41,      k43, k44,      k46,      k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,  k05,   k06,  k07,   k08,  k09,   k0a,  k0b,  k0c,  k0d,  k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,  k15,   k16,  k17,   k18,  k19,   k1a,  k1b,  k1c,  k1d,  k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,  k25,   k26,  k27,   k28,  k29,   k2a,  k2b,  k2c,  k2d,  KC_NO }, \
    { k30,  k31,   k32,   k33,  k34,  k35,   k36,  k37,   k38,  k39,   k3a,  k3b,  k3c,  k3d,  k3e   }, \
    { k40,  k41,   KC_NO, k43,  k44,  KC_NO, k46,  KC_NO, k48,  KC_NO, k4a,  k4b,  k4c,  k4d,  k4e   }  \
}

/* LAYOUT_60_ansi
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d        │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │40  │41  │43  │46                      │4a  │4b  │4d  │4e  │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
*/
#define LAYOUT_60_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d,      \
    k40, k41,      k43,           k46,                k4a, k4b,      k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,  k0b,  k0c,   KC_NO, k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,   k1d,   k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,   k2d,   KC_NO }, \
    { k30,  KC_NO, k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  KC_NO, k3d,   KC_NO }, \
    { k40,  k41,   KC_NO, k43,  KC_NO, KC_NO, k46,  KC_NO, KC_NO, KC_NO, k4a,  k4b,  KC_NO, k4d,   k4e   }  \
}

/* LAYOUT_60_ansi_split
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d        │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │40  │41  │43  │44      │46  │48        │4a  │4b  │4d  │4e  │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
*/
#define LAYOUT_60_ansi_split( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d,      \
    k40, k41,      k43, k44,      k46,      k48,      k4a, k4b,      k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,  k0b,  k0c,   KC_NO, k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,   k1d,   k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,   k2d,   KC_NO }, \
    { k30,  KC_NO, k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  KC_NO, k3d,   KC_NO }, \
    { k40,  k41,   KC_NO, k43,  k44,   KC_NO, k46,  KC_NO, k48,   KC_NO, k4a,  k4b,  KC_NO, k4d,   k4e   }  \
}

/* LAYOUT_60_iso
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐2d  │
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │1e │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d        │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │40  │41  │43  │46                      │4a  │4b  │4d  │4e  │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
*/
#define LAYOUT_60_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k1e, k2d, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d,      \
    k40, k41,      k43,           k46,                k4a, k4b,      k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,  k0b,  k0c,   KC_NO, k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,   k1d,   k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,   k2d,   KC_NO }, \
    { k30,  k31,   k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  KC_NO, k3d,   KC_NO }, \
    { k40,  k41,   KC_NO, k43,  KC_NO, KC_NO, k46,  KC_NO, KC_NO, KC_NO, k4a,  k4b,  KC_NO, k4d,   k4e   }  \
}

/* LAYOUT_60_iso_5x1u
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐2d  │
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │1e │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d        │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┬───┤
 * │40  │41  │43  │46                      │4a │4b │4c │4d │4e │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
*/
#define LAYOUT_60_iso_5x1u( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k1e, k2d, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d,      \
    k40, k41,      k43,           k46,                k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,  k0b,  k0c,   KC_NO, k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,   k1d,   k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,   k2d,   KC_NO }, \
    { k30,  k31,   k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  KC_NO, k3d,   KC_NO }, \
    { k40,  k41,   KC_NO, k43,  KC_NO, KC_NO, k46,  KC_NO, KC_NO, KC_NO, k4a,  k4b,  k4c,   k4d,   k4e   }  \
}

/* LAYOUT_60_iso_split
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐2d  │
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │1e │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d        │
 * ├────┼───┴┬──┴─┬─┴───┴──┬┴───┼───┴───┴──┬┴───┼───┴┬────┬────┤
 * │40  │41  │43  │44      │46  │48        │4a  │4b  │4d  │4e  │
 * └────┴────┴────┴────────┴────┴──────────┴────┴────┴────┴────┘
*/
#define LAYOUT_60_iso_split( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k1e, k2d, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d,      \
    k40, k41,      k43, k44,      k46,      k48,      k4a, k4b,      k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,  k0b,  k0c,   KC_NO, k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,  k1b,  k1c,   k1d,   k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,  k2b,  k2c,   k2d,   KC_NO }, \
    { k30,  k31,   k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,  k3b,  KC_NO, k3d,   KC_NO }, \
    { k40,  k41,   KC_NO, k43,  k44,   KC_NO, k46,  KC_NO, k48,   KC_NO, k4a,  k4b,  KC_NO, k4d,   k4e   }  \
}

/* LAYOUT_60_b_ansi (maximized DZ60 Plate B layout for ANSI)
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3c    │3d │3e │
 * ├────┬───┴┬──┴─┬─┴───┴──┬┴───┼───┴───┴──┬┴──┬┴──┬───┼───┼───┤
 * │40  │41  │43  │44      │46  │48        │4a │4b │4c │4d │4e │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/
#define LAYOUT_60_b_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a,      k3c, k3d, k3e, \
    k40, k41,      k43, k44,      k46,      k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,  k05,   k06,  k07,   k08,  k09,   k0a,  k0b,   k0c,  k0d,  k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,  k15,   k16,  k17,   k18,  k19,   k1a,  k1b,   k1c,  k1d,  k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,  k25,   k26,  k27,   k28,  k29,   k2a,  k2b,   k2c,  k2d,  KC_NO }, \
    { k30,  KC_NO, k32,   k33,  k34,  k35,   k36,  k37,   k38,  k39,   k3a,  KC_NO, k3c,  k3d,  k3e   }, \
    { k40,  k41,   KC_NO, k43,  k44,  KC_NO, k46,  KC_NO, k48,  KC_NO, k4a,  k4b,   k4c,  k4d,  k4e   }  \
}

/* LAYOUT_60_b_iso (maximized DZ60 Plate B layout for ISO)
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐2d  │
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │1e │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬──┴────┤
 * │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3c    │3d │3e │
 * ├────┼───┴┬──┴─┬─┴───┴──┬┴───┼───┴───┴──┬┴──┬┴──┬───┼───┼───┤
 * │40  │41  │43  │44      │46  │48        │4a │4b │4c │4d │4e │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/
#define LAYOUT_60_b_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k1e, k2d, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a,      k3c, k3d, k3e, \
    k40, k41,      k43, k44,      k46,      k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,  k05,   k06,  k07,   k08,  k09,   k0a,  k0b,   k0c,  k0d,  k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,  k15,   k16,  k17,   k18,  k19,   k1a,  k1b,   k1c,  k1d,  k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,  k25,   k26,  k27,   k28,  k29,   k2a,  k2b,   k2c,  k2d,  KC_NO }, \
    { k30,  k31,   k32,   k33,  k34,  k35,   k36,  k37,   k38,  k39,   k3a,  KC_NO, k3c,  k3d,  k3e   }, \
    { k40,  k41,   KC_NO, k43,  k44,  KC_NO, k46,  KC_NO, k48,  KC_NO, k4a,  k4b,   k4c,  k4d,  k4e   }  \
}

/* LAYOUT_60_tsangan
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │    0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │
 * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤
 * │40   │41 │43   │46 (7u)                    │4b   │4d │4e   │
 * └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
*/
#define LAYOUT_60_tsangan( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, \
    k40, k41,      k43,           k46,                     k4b,      k4d, k4e  \
) { \
    { k00,   k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,   k0b,  k0c,   KC_NO,  k0e   }, \
    { k10,   KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,   k1b,  k1c,   k1d,    k1e   }, \
    { k20,   KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,   k2b,  k2c,   k2d,    KC_NO }, \
    { k30,   KC_NO, k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,   k3b,  KC_NO, k3d,    k3e   }, \
    { k40,   k41,   KC_NO, k43,  KC_NO, KC_NO, k46,  KC_NO, KC_NO, KC_NO, KC_NO, k4b,  KC_NO, k4d,    k4e   }  \
}

/* LAYOUT_60_tsangan_hhkb
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │
 * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤
 * │40   │41 │43   │46 (7u)                    │4b   │4d │4e   │
 * └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
*/
#define LAYOUT_60_tsangan_hhkb( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, \
    k40, k41,      k43,           k46,                     k4b,      k4d, k4e  \
) { \
    { k00,   k01,   k02,   k03,  k04,   k05,   k06,  k07,   k08,   k09,   k0a,   k0b,  k0c,   k0d,  k0e   }, \
    { k10,   KC_NO, k12,   k13,  k14,   k15,   k16,  k17,   k18,   k19,   k1a,   k1b,  k1c,   k1d,  k1e   }, \
    { k20,   KC_NO, k22,   k23,  k24,   k25,   k26,  k27,   k28,   k29,   k2a,   k2b,  k2c,   k2d,  KC_NO }, \
    { k30,   KC_NO, k32,   k33,  k34,   k35,   k36,  k37,   k38,   k39,   k3a,   k3b,  KC_NO, k3d,  k3e   }, \
    { k40,   k41,   KC_NO, k43,  KC_NO, KC_NO, k46,  KC_NO, KC_NO, KC_NO, KC_NO, k4b,  KC_NO, k4d,  k4e   }  \
}^

/* LAYOUT_60_olligranlund_ISO
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐2d  │
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │1e │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30  |31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │40  │41  │43  │46                      │4a  │4b  │4d  │4e  │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
*/
#define LAYOUT_60_olligranlund_ISO( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d,      \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k1e, k2d, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, \
    k40, k41,      k43, k44,      k46,      k48,      k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00,  k01,   k02,   k03,  k04,  k05,   k06,  k07,   k08,  k09,   k0a,  k0b,   k0c,  k0d,  k0e   }, \
    { k10,  KC_NO, k12,   k13,  k14,  k15,   k16,  k17,   k18,  k19,   k1a,  k1b,   k1c,  k1d,  k1e   }, \
    { k20,  KC_NO, k22,   k23,  k24,  k25,   k26,  k27,   k28,  k29,   k2a,  k2b,   k2c,  k2d,  KC_NO }, \
    { k30,  k31,   k32,   k33,  k34,  k35,   k36,  k37,   k38,  k39,   k3a,  k3b,   KC_NO,k3d,  k3e   }, \
    { k40,  k41,   KC_NO, k43,  k44,  KC_NO, k46,  KC_NO, k48,  KC_NO, k4a,  k4b,   k4c,  k4d,  k4e   }  \
}

#endif
