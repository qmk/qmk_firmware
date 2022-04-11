#include "../base.h"

// Fix for hardware swapped LGUI and LALT
#if SWAP_GUI_ALT == true
const uint16_t TMP_LGUI = KC_LGUI;
const uint16_t TMP_LALT = KC_LALT;
#    define KC_LGUI TMP_LALT
#    define KC_LALT TMP_LGUI
#endif
