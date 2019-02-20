/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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
#ifndef SINGA_H
#define SINGA_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, \
  k16, k17, k18, k19, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k30, k31, \
   k32,  k33, k34, k35, k36, k37, k38, k39, k40, k41, k42, k43, k44,   k45,  k46, \
    k47,   k48, k49, k50, k51, k52, k53, k54, k55, k56, k57, k58, k59,  k60, k61, \
  k62, k63,   k64, k65, k66, k67, k68, k69, k70, k71, k72, k73,  k74,   k75, k76, \
   k77,  k78,  k79,  k80,  k81,  k82,  k83,  k84,  k85, k86, k87, k88, k89, k90 \
){ \
  { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k10,   k11,   k12,   k13, k14 }, \
  { k16,   k17,   k18,   k19,   k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29, k30 }, \
  { k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k40,   k41,   k42,   k43,   k44,   k45, k46 }, \
  { k47,   k48,   k49,   k50,   k51,   k52,   k53,   k54,   k55,   k56,   k57,   k58,   k59,   k60, k61 }, \
  { k62,   k63,   k64,   k65,   k66,   k67,   k68,   k69,   k70,   k71,   k72,   k73,   k74,   k75, k76 }, \
  { k77,   k78,   k79,   k80,   k81,   k82,   KC_NO, k83,   k84,   k85,   k86,   k87,   k88,   k89, k90 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k15, k31 } \
}

#define LAYOUT_wkl( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, \
  k16, k17, k18, k19, k20, k21, k22, k23, k24, k25, k26, k27, k28,    k29,   k30, \
   k31,  k32, k33, k34, k35, k36, k37, k38, k39, k40, k41, k42, k43,   k44,  k45, \
    k46,   k47, k48, k49, k50, k51, k52, k53, k54, k55, k56, k57,     k58,   k59, \
      k60,    k61, k62, k63, k64, k65, k66, k67, k68, k69, k70,  k71,   k72, k73, \
   k74,        k75,                   k76,                   k77,  k78, k79, k80  \
){ \
  { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k10,   k11,   k12,   k13, k14   }, \
  { k16,   k17,   k18,   k19,   k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29, KC_NO }, \
  { k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k40,   k41,   k42,   k43,   k44, k45   }, \
  { k46,   k47,   k48,   k49,   k50,   k51,   k52,   k53,   k54,   k55,   k56,   k57,   KC_NO, k58, k59   }, \
  { k60,   KC_NO, k61,   k62,   k63,   k64,   k65,   k66,   k67,   k68,   k69,   k70,   k71,   k72, k73   }, \
  { k74,   KC_NO, k75,   KC_NO, KC_NO, k76,   KC_NO, KC_NO, k77,   KC_NO, KC_NO, KC_NO, k78,   k79, k80   }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k15, k30   } \
}

#define LAYOUT_wkl_split_bs( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, \
  k16, k17, k18, k19, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k81, k30, \
   k31,  k32, k33, k34, k35, k36, k37, k38, k39, k40, k41, k42, k43,   k44,  k45, \
    k46,   k47, k48, k49, k50, k51, k52, k53, k54, k55, k56, k57,     k58,   k59, \
      k60,    k61, k62, k63, k64, k65, k66, k67, k68, k69, k70,  k71,   k72, k73, \
   k74,        k75,                   k76,                   k77,  k78, k79, k80  \
){ \
  { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k10,   k11,   k12,   k13, k14 }, \
  { k16,   k17,   k18,   k19,   k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29, k81 }, \
  { k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k40,   k41,   k42,   k43,   k44, k45 }, \
  { k46,   k47,   k48,   k49,   k50,   k51,   k52,   k53,   k54,   k55,   k56,   k57,   KC_NO, k58, k59 }, \
  { k60,   KC_NO, k61,   k62,   k63,   k64,   k65,   k66,   k67,   k68,   k69,   k70,   k71,   k72, k73 }, \
  { k74,   KC_NO, k75,   KC_NO, KC_NO, k76,   KC_NO, KC_NO, k77,   KC_NO, KC_NO, KC_NO, k78,   k79, k80 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k15, k30 } \
}

#define LAYOUT_tsangan( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, \
  k16, k17, k18, k19, k20, k21, k22, k23, k24, k25, k26, k27, k28,    k29,   k30, \
   k31,  k32, k33, k34, k35, k36, k37, k38, k39, k40, k41, k42, k43,   k44,  k45, \
    k46,   k47, k48, k49, k50, k51, k52, k53, k54, k55, k56, k57,     k58,   k59, \
      k60,    k61, k62, k63, k64, k65, k66, k67, k68, k69, k70,  k71,   k72, k73, \
   k74,  k81,  k75,                   k76,                   k77,  k78, k79, k80  \
){ \
  { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k10,   k11,   k12,   k13, k14   }, \
  { k16,   k17,   k18,   k19,   k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29, KC_NO }, \
  { k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k40,   k41,   k42,   k43,   k44, k45   }, \
  { k46,   k47,   k48,   k49,   k50,   k51,   k52,   k53,   k54,   k55,   k56,   k57,   KC_NO, k58, k59   }, \
  { k60,   KC_NO, k61,   k62,   k63,   k64,   k65,   k66,   k67,   k68,   k69,   k70,   k71,   k72, k73   }, \
  { k74,   k81,   k75,   KC_NO, KC_NO, k76,   KC_NO, KC_NO, k77,   KC_NO, KC_NO, KC_NO, k78,   k79, k80   }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k15, k30   } \
}

#define LAYOUT_tsangan_split_bs( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, \
  k16, k17, k18, k19, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k82, k30, \
   k31,  k32, k33, k34, k35, k36, k37, k38, k39, k40, k41, k42, k43,   k44,  k45, \
    k46,   k47, k48, k49, k50, k51, k52, k53, k54, k55, k56, k57,     k58,   k59, \
      k60,    k61, k62, k63, k64, k65, k66, k67, k68, k69, k70,  k71,   k72, k73, \
   k74,  k81,  k75,                   k76,                   k77,  k78, k79, k80  \
){ \
  { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k10,   k11,   k12,   k13, k14 }, \
  { k16,   k17,   k18,   k19,   k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29, k82 }, \
  { k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k40,   k41,   k42,   k43,   k44, k45 }, \
  { k46,   k47,   k48,   k49,   k50,   k51,   k52,   k53,   k54,   k55,   k56,   k57,   KC_NO, k58, k59 }, \
  { k60,   KC_NO, k61,   k62,   k63,   k64,   k65,   k66,   k67,   k68,   k69,   k70,   k71,   k72, k73 }, \
  { k74,   k81,   k75,   KC_NO, KC_NO, k76,   KC_NO, KC_NO, k77,   KC_NO, KC_NO, KC_NO, k78,   k79, k80 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k15, k30 } \
}

#define LAYOUT_wk( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, \
  k16, k17, k18, k19, k20, k21, k22, k23, k24, k25, k26, k27, k28,    k29,   k30, \
   k31,  k32, k33, k34, k35, k36, k37, k38, k39, k40, k41, k42, k43,   k44,  k45, \
    k46,   k47, k48, k49, k50, k51, k52, k53, k54, k55, k56, k57,     k58,   k59, \
      k60,    k61, k62, k63, k64, k65, k66, k67, k68, k69, k70,  k71,   k72, k73, \
   k74,  k81,  k75,                 k76,               k77,  k82,  k78, k79, k80  \
){ \
  { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k10,   k11,   k12,   k13, k14   }, \
  { k16,   k17,   k18,   k19,   k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29, KC_NO }, \
  { k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k40,   k41,   k42,   k43,   k44, k45   }, \
  { k46,   k47,   k48,   k49,   k50,   k51,   k52,   k53,   k54,   k55,   k56,   k57,   KC_NO, k58, k59   }, \
  { k60,   KC_NO, k61,   k62,   k63,   k64,   k65,   k66,   k67,   k68,   k69,   k70,   k71,   k72, k73   }, \
  { k74,   k81  , k75,   KC_NO, KC_NO, k76,   KC_NO, KC_NO, k77,   KC_NO, k82,   KC_NO, k78,   k79, k80   }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k15, k30   } \
}

#define LAYOUT_wk_split_bs( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, \
  k16, k17, k18, k19, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k83, k30, \
   k31,  k32, k33, k34, k35, k36, k37, k38, k39, k40, k41, k42, k43,   k44,  k45, \
    k46,   k47, k48, k49, k50, k51, k52, k53, k54, k55, k56, k57,     k58,   k59, \
      k60,    k61, k62, k63, k64, k65, k66, k67, k68, k69, k70,  k71,   k72, k73, \
   k74,  k81,  k75,                 k76,               k77,  k82,  k78, k79, k80  \
){ \
  { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k10,   k11,   k12,   k13, k14 }, \
  { k16,   k17,   k18,   k19,   k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29, k83 }, \
  { k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k40,   k41,   k42,   k43,   k44, k45 }, \
  { k46,   k47,   k48,   k49,   k50,   k51,   k52,   k53,   k54,   k55,   k56,   k57,   KC_NO, k58, k59 }, \
  { k60,   KC_NO, k61,   k62,   k63,   k64,   k65,   k66,   k67,   k68,   k69,   k70,   k71,   k72, k73 }, \
  { k74,   k81,   k75,   KC_NO, KC_NO, k76,   KC_NO, KC_NO, k77,   KC_NO, k82,   KC_NO, k78,   k79, k80 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k15, k30 } \
}

#endif
