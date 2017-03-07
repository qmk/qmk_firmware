#ifndef COMPACT_KEYMAP_H
#define COMPACT_KEYMAP_H

#define COMPACT_KEYMAP( \
  k00, k01, k02, k03, k04, k05, k45, k44, k43, k42, k41, k40, \
  k10, k11, k12, k13, k14, k15, k55, k54, k53, k52, k51, k50, \
  k20, k21, k22, k23, k24, k25, k65, k64, k63, k62, k61, k60, \
  k30, k31, k32, k33, k34, k35, k75, k74, k73, k72, k71, k70 \
  ) \
  { \
    { KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05 }, \
    { KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15 }, \
    { KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25 }, \
    { KC_##k30, KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35 }, \
    { KC_##k40, KC_##k41, KC_##k42, KC_##k43, KC_##k44, KC_##k45 }, \
    { KC_##k50, KC_##k51, KC_##k52, KC_##k53, KC_##k54, KC_##k55 }, \
    { KC_##k60, KC_##k61, KC_##k62, KC_##k63, KC_##k64, KC_##k65 }, \
    { KC_##k70, KC_##k71, KC_##k72, KC_##k73, KC_##k74, KC_##k75 } \
  }

#define KC_ KC_TRNS

#endif