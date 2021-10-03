RGB_MATRIX_EFFECT(CUSTOM_GRADIENT)
RGB_MATRIX_EFFECT(DIAGONAL)
RGB_MATRIX_EFFECT(KITT)
RGB_MATRIX_EFFECT(RANDOM_BREATH_RAINBOW)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "led/custom_gradient.c"
#include "led/diagonal.c"
#include "led/kitt.c"
#include "led/random_breath_rainbow.c"

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS