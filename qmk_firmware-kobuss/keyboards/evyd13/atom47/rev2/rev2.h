#ifndef ATOM47_H
#define ATOM47_H

#include "quantum.h"

// readability
#define XXX KC_NO

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a,      k1c, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a,      k2c, \
	k30, k31, k32, k33, k34,      k36,      k38, k39, k3a,      k3c \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c}, \
	{k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, XXX, k1c}, \
	{k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, XXX, k2c}, \
	{k30, k31, k32, k33, k34, XXX, k36, XXX, k38, k39, k3a, XXX, k3c}  \
}

void matrix_init_user(void);
void matrix_scan_user(void);

#endif
