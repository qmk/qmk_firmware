RGB_MATRIX_EFFECT(CUSTOM_GRADIENT)
RGB_MATRIX_EFFECT(COOL_DIAGONAL)
RGB_MATRIX_EFFECT(FLOWER_BLOOMING)
RGB_MATRIX_EFFECT(KITT)
RGB_MATRIX_EFFECT(RANDOM_BREATH_RAINBOW)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "led/custom_gradient.c"
#include "led/cool_diagonal.c"
#include "led/flower_blooming/flower_blooming.c"
#include "led/kitt.c"
#include "led/random_breath_rainbow.c"

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS