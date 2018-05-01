#ifndef SF68_V2_H 
#define SF68_V2_H

#include "quantum.h"

#define xxx KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1e, k1f, \
	k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,      k2e, k2f, \
	k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, k3f, \
	k40, k41, k42, k43,           k46,      k48,           k4b, k4c, k4d, k4e, k4f \
) \
{ \
	{k00, k01, k02, k03, k04, k05, k06, k07, k08}, \
    {k09, k0a, k0b, k0c, k0d, k0e, k0f, k10, k11}, \
    {k12, k13, k14, k15, k16, k17, k18, k19, k1a}, \
    {k1b, k1c, k1e, k1f, k20, k22, k23, k24, k25}, \
    {k26, k27, k28, k29, k2a, k2b, k2c, k2e, k2f}, \
    {k30, k32, k33, k34, k35, k36, k37, k38, k39}, \
    {k3a, k3b, k3d, k3e, k3f, k40, k41, k42, k43}, \
    {k46, k48, xxx, xxx, k4b, k4c, k4d, k4e, k4f} \
}

void matrix_init_user(void);
void matrix_scan_user(void);

#endif
