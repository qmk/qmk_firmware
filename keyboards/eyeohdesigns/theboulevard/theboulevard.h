/* Copyright 2021 eye oh designs
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#define LAYOUT_ortho1( \
    k00, k01,                                                           k0a, k0b, k0c, \
    k10, k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c, \
    k20, k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, k2b, k2c, \
    k30, k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c, \
    k40, k41,   k42,   k43,   k44,   k45,      k47,       k48,   k49,   k4a, k4b, k4c  \
) \
{ \
    { k00, k01, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k0a, k0b, k0c },\
    { k10, k11, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c },\
    { k20, k21, k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, k2b, k2c },\
    { k30, k31, k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c }, \
    { k40, k41, k42,   k43,   k44,   k45,   KC_NO, k47,   k48,   k49,   k4a, k4b, k4c }\
}

#define LAYOUT_ortho2( \
    k00, k01,                                                           k0a, k0b, k0c, \
    k10, k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c, \
    k20, k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, k2b, k2c, \
    k30, k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c, \
    k40, k41,   k42,   k43,   k44,       k45,          k48,      k49,   k4a, k4b, k4c  \
) \
{ \
    { k00, k01, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k0a, k0b, k0c },\
    { k10, k11, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c },\
    { k20, k21, k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, k2b, k2c },\
    { k30, k31, k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c }, \
    { k40, k41, k42,   k43,   k44,   k45,   KC_NO, KC_NO, k48,   k49,   k4a, k4b, k4c }\
}

#define LAYOUT_ortho3( \
    k00, k01,                                                           k0a, k0b, k0c, \
    k10, k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c, \
    k20, k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, k2b, k2c, \
    k30, k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c, \
    k40, k41,   k42,   k43,          k45,          k48,                 k4a, k4b, k4c  \
) \
{ \
    { k00, k01, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k0a, k0b, k0c },\
    { k10, k11, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c },\
    { k20, k21, k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, k2b, k2c },\
    { k30, k31, k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c }, \
    { k40, k41, k42,   k43,   KC_NO, k45,   KC_NO, KC_NO, k48,   KC_NO, k4a, k4b, k4c }\
}

#define LAYOUT_ortho4( \
    k00, k01,                                                           k0a, k0b, k0c, \
    k10, k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c, \
    k20, k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, k2b, k2c, \
    k30, k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c, \
    k40, k41,   k42,                    k46,                            k4a, k4b, k4c  \
) \
{ \
    { k00, k01, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k0a, k0b, k0c },\
    { k10, k11, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c },\
    { k20, k21, k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, k2b, k2c },\
    { k30, k31, k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c }, \
    { k40, k41, k42,   KC_NO, KC_NO, KC_NO, k46,   KC_NO, KC_NO, KC_NO, k4a, k4b, k4c }\
}

#define LAYOUT_ortho5( \
    k00, k01,                                                           k0a, k0b, k0c, \
    k10, k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c, \
    k20, k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, k2b, k2c, \
    k30, k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c, \
    k40, k41,   k42,                    k47,                                 k4b, k4c  \
) \
{ \
    { k00, k01, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k0a,   k0b, k0c },\
    { k10, k11, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a,   k1b, k1c },\
    { k20, k21, k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a,   k2b, k2c },\
    { k30, k31, k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a,   k3b, k3c }, \
    { k40, k41, k42,   KC_NO, KC_NO, KC_NO, KC_NO, k47,   KC_NO, KC_NO, KC_NO, k4b, k4c }\
}

#define LAYOUT_stagger1( \
    k00, k01,                                                           k0a, k0b, k0c, \
    k10, k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c, \
    k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a,   k2c, \
    k30,      k31,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b,  k3c, \
    k40, k41,   k42,   k43,   k44,   k45,      k47,       k48,   k49,   k4a, k4b, k4c  \
) \
{ \
    { k00, k01, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k0a, k0b, k0c },\
    { k10, k11, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c },\
    { k20, k21, k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, KC_NO, k2c },\
    { k30, k31, KC_NO,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c }, \
    { k40, k41, k42,   k43,   k44,   k45,   KC_NO, k47,   k48,   k49,   k4a, k4b, k4c }\
}

#define LAYOUT_stagger2( \
    k00, k01,                                                           k0a, k0b, k0c, \
    k10, k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c, \
    k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a,   k2c, \
    k30,      k31,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b,  k3c, \
    k40, k41,   k42,   k43,   k44,       k45,          k48,      k49,   k4a, k4b, k4c  \
) \
{ \
    { k00, k01, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k0a, k0b, k0c },\
    { k10, k11, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c },\
    { k20, k21, k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, KC_NO, k2c },\
    { k30, k31, KC_NO,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c }, \
    { k40, k41, k42,   k43,   k44,   k45,   KC_NO, KC_NO, k48,   k49,   k4a, k4b, k4c }\
}

#define LAYOUT_stagger3( \
    k00, k01,                                                           k0a, k0b, k0c, \
    k10, k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c, \
    k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a,   k2c, \
    k30,      k31,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b,  k3c, \
    k40, k41,   k42,   k43,          k45,          k48,                 k4a, k4b, k4c  \
) \
{ \
    { k00, k01, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k0a, k0b, k0c },\
    { k10, k11, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c },\
    { k20, k21, k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, KC_NO, k2c },\
    { k30, k31, KC_NO,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c }, \
    { k40, k41, k42,   k43,   KC_NO, k45,   KC_NO, KC_NO, k48,   KC_NO, k4a, k4b, k4c }\
}

#define LAYOUT_stagger4( \
    k00, k01,                                                           k0a, k0b, k0c, \
    k10, k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c, \
    k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a,   k2c, \
    k30,      k31,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b,  k3c, \
    k40, k41,   k42,                    k46,                            k4a, k4b, k4c  \
) \
{ \
    { k00, k01, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k0a, k0b, k0c },\
    { k10, k11, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c },\
    { k20, k21, k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, KC_NO, k2c },\
    { k30, k31, KC_NO,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c }, \
    { k40, k41, k42,   KC_NO, KC_NO, KC_NO, k46,   KC_NO, KC_NO, KC_NO, k4a, k4b, k4c }\
}

#define LAYOUT_stagger5( \
    k00, k01,                                                           k0a, k0b, k0c, \
    k10, k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c, \
    k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a,   k2c, \
    k30,      k31,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b,  k3c, \
    k40, k41,   k42,                    k47,                                 k4b, k4c  \
) \
{ \
    { k00, k01, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k0a, k0b, k0c },\
    { k10, k11, k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1a, k1b, k1c },\
    { k20, k21, k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2a, KC_NO, k2c },\
    { k30, k31, KC_NO,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3a, k3b, k3c }, \
    { k40, k41, k42,   KC_NO, KC_NO, KC_NO, KC_NO, k47,   KC_NO, KC_NO, KC_NO, k4b, k4c }\
}
