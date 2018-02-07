#ifndef CORE_H
#define CORE_H

#include "quantum.h"

// readability
#define XXX KC_NO

#define KEYMAP( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a,      k1c, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a,      k2c, \
	k30, k31, k32, k33, k34,      k36,      k38, k39, k3a,      k3c \
) \
{ \
  {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c}, \
	{k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, XXX, k1c}, \
	{k20, XXX, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2c}, \
	{k30, k31, XXX, k32, k33, k34, XXX, k36, XXX, k38, k39, k3a, k3c}  \
}

#define KC_KEYMAP( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a,      k1c, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a,      k2c, \
	k30, k31, k32, k33, k34,      k36,      k38, k39, k3a,      k3c \
) \
{ \
  {KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, KC_##k0a, KC_##k0b, KC_##k0c}, \
	{KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, KC_##k1a, XXX, KC_##k1c}, \
	{KC_##k20, XXX, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, KC_##k2a, KC_##k2c}, \
	{KC_##k30, KC_##k31, XXX, KC_##k32, KC_##k33, KC_##k34, XXX, KC_##k36, XXX, KC_##k38, KC_##k39, KC_##k3a, KC_##k3c}  \
}

void matrix_init_user(void);
void matrix_scan_user(void);

#endif
