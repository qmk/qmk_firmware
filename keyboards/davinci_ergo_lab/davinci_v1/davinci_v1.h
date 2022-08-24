#pragma once


#if defined(KEYBOARD_redox_rev1_proton_c)
#    include "proton_c.h"
#endif

#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
#endif

#define LAYOUT( \
  k00, k01, k02, k03, k04, k05, k06,           k07, k08, k09, k10, k11, k12, k13, \
  k14, k15, k16, k17, k18, k19, k20,           k21, k22, k23, k24, k25, k26, k27, \
  k28, k29, k30, k31, k32, k33, k34,           k35, k36, k37, k38, k39, k40, k41, \
  k42, k43, k44, k45, k46, k47, k48,           k49, k50, k51, k52, k53, k54, k55, \
  k56, k57, k58, k59, k60, k61, k62,           k63, k64, k65, k66, k67, k68, k69, \
  k70, k71, k72, k73, k74, k75, k76,           k77, k78, k79, k80, k81, k82, k83, \
  k84, k85, k86, k87, k88, k89, k90,           k91, k92, k93, k94, k95, k96, k97, \
  k98, k99,k100,k101,k102,k103,k104,          k105,k106,k107 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08 }, \
    { k18, k19, k20, k21, k22, k23, k24, k25, k26 }, \
    { k36, k37, k38, k39, k40, k41, k42, k43, k44 }, \
    { k54, k55, k56, k57, k58, k59, k60, k61, k62 }, \
    { k72, k73, k74, k75, k76, k77, k78, k79, k80 }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98 }, \
    { k09, k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k27, k28, k29, k30, k31, k32, k33, k34, k35 }, \
    { k45, k46, k47, k48, k49, k50, k51, k52, k53 }, \
    { k63, k64, k65, k66, k67, k68, k69, k70, k71 }, \
    { k81, k82, k83, k84, k85, k86, k87, k88, k89 }, \
    { k99,k100,k101,k102,k103,k104,k105,k106,k107 }, \
}

