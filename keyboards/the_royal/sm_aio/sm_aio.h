#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT_split_space( \
              k01, k02, k03, k04, k05,   k06, k07, k08, k09, \
	k10,      k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111, k112, k113, \
	k20,       k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211, k212,      \
	k30,         k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311, k312,    \
	k40,      k41,   k42,   k43,       k45,       k46,       k410,   k411,   k412  \
) { \
    { XXX,    k01, k02, k03, k04, k05, k06, k07, k08, k09, XXX,  XXX,  XXX,   XXX }, \
    { k10,    k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111, k112, k113 },  \
    { k20,    k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211, k212,  XXX },  \
    { k30,    k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311, k312,  XXX },  \
	{ k40,    k41, k42, k43, XXX, k45, k46, XXX, XXX, XXX, k410, k411, k412,  XXX }   \
}

#define LAYOUT_six_space( \
              k01, k02, k03, k04, k05,   k06, k07, k08, k09, \
	k10,      k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111, k112, k113, \
	k20,       k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211, k212,      \
	k30,         k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311, k312,    \
	k40,      k41,   k42,   k43,       k45,       k46,       k410,   k411,   k412  \
) { \
    { XXX,    k01, k02, k03, k04, k05, k06, k07, k08, k09, XXX,  XXX,  XXX,   XXX }, \
    { k10,    k11, k12, k13, k14, k15, k16, k17, k18, k19, k110, k111, k112, k113 },  \
    { k20,    k21, k22, k23, k24, k25, k26, k27, k28, k29, k210, k211, k212,  XXX },  \
    { k30,    k31, k32, k33, k34, k35, k36, k37, k38, k39, k310, k311, k312,  XXX },  \
	{ k40,    k41, k42, k43, XXX, XXX, k46, XXX, XXX, XXX, k410, k411, k412,  XXX }   \
}
