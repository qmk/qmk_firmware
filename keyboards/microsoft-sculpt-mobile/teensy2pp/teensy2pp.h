#ifndef MICROSOFT_SCULPT_MOBILE_TEENSY_H
#define MICROSOFT_SCULPT_MOBILE_TEENSY_H


#include "../config.h"



#define KEYMAP( \
		k7Q, k6O, k6P,  k6Q, k5O, k5P, k5Q, k7A, k7B, k7C, k7D, k7E, k7F, k1O, k1K, k1L, \
		k5A,  k5K,  k5L, k5M, k5N, k5H, k5I, k2A, k2B, k2C, k2D, k5B, k5C, k5J, k2E, \
		k6R,  k6D,  k6E, k6F, k7I, k7J, k4A, k4B, k4C, k4D, k3A, k3B, k3C, k3D, \
		k0J, k6A, k6B, k6C, k7H, k1A, k1B, k5D, k5E, k5F, k5G, k1C, k7P,   k2G, \
		k2P, k7K, k7L, k7M, k7O, k0A, k0B, k0C, k0D, k0E, k0F, k2L, k6G, k1P,\
		k1Q, k4N, k3O,k6N, k3K, k0R, k1M, k6H, k6I, k6J \
) \
{ \
        {k0A, k0B, k0C, k0D, k0E, k0F, KC_NO, KC_NO, KC_NO, k0J, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,KC_NO, KC_NO, k0R},\
        {k1A, k1B, k1C, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k1K, k1L, k1M, KC_NO, k1O, k1P, k1Q, KC_NO},\
        {k2A, k2B, k2C, k2D, k2E, KC_NO, k2G, KC_NO, KC_NO, KC_NO, KC_NO, k2L, KC_NO, KC_NO, KC_NO, k2P, KC_NO, KC_NO},\
        {k3A, k3B, k3C, k3D, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k3K, KC_NO, KC_NO, KC_NO, k3O, KC_NO, KC_NO, KC_NO},\
        {k4A, k4B, k4C, k4D, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, k4N, KC_NO,KC_NO, KC_NO, KC_NO},\
        {k5A, k5B, k5C, k5D, k5E, k5F, k5G, k5H, k5I, k5J, k5K, k5L, k5M, k5N, k5O, k5P, k5Q, KC_NO },\
        {k6A, k6B, k6C, k6D, k6E, k6F, k6G, k6H, k6I, k6J, KC_NO, KC_NO, KC_NO, k6N, k6O, k6P, k6Q, k6R},\
        {k7A, k7B, k7C, k7D, k7E, k7F, KC_NO, k7H, k7I, k7J, k7K, k7L, k7M, KC_NO, k7O, k7P, k7Q, KC_NO},\
}


#endif
