#ifndef ATOM47_H
#define ATOM47_H

#include "quantum.h"

// readability
#define XXX KC_NO

#define KEYMAP_ANSI( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a,      k1c, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, \
	k30, k31, k32, k33,      k35,      k37,      k39, k3a, k3b, k3c \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c}, \
	{k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, XXX, k1c}, \
	{k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c}, \
	{k30, k31, k32, k33, XXX, k35, XXX, k37, XXX, k39, k3a, k3b, k3c}  \
}

void matrix_init_user(void);
void matrix_scan_user(void);

#endif
