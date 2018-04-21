#ifndef NANO_H
#define NANO_H

#include "quantum.h"

#define LAYOUT(k01, k02, k03, k04, k05, k06, k07, k08) \
{ \
    {KC_##k01, KC_##k02, KC_##k03, KC_##k04}, \
    {KC_##k05, KC_##k06, KC_##k07, KC_##k08} \
}

#endif
