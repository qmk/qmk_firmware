#ifndef CONFIG_USER_H
#define CONFIG_USER_H
#include "../../config.h"


#define TAPPING_TERM 200

#ifdef RGBLIGHT_ENABLE
#undef RGBLIGHT_SAT_STEP 
#define RGBLIGHT_SAT_STEP 12
<<<<<<< HEAD
<<<<<<< HEAD
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 7
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 7
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#endif // RGBLIGHT_ENABLE

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#endif
=======
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 3
=======
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 7
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 7
>>>>>>> Tweaked RGB lighting stuff
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#endif // RGBLIGHT_ENABLE
<<<<<<< HEAD
#define FORCE_NKRO
>>>>>>> Updated RGB Underglow info
=======

//#define FORCE_NKRO
>>>>>>> Cleanup macros
=======
#define FORCE_NKRO
<<<<<<< HEAD
#ifdef FORCE_NKRO
#define NKRO_EPSIZE 32
#endif
<<<<<<< HEAD
>>>>>>> Add forced NKRO
=======
=======
>>>>>>> Updated macros and added workman keymaps

=======
>>>>>>> Remove force NKRO
=======
#define FORCE_NKRO
>>>>>>> Add Viterbi one handed layout and minor tweaks to others

#endif
>>>>>>> Added default layer (qwerty/colemak/dvorak) detection to RGB Underglow
=======
#endif
>>>>>>> Update to keymaps
