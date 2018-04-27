#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define PRIYADI_PROMETHIUM

/* bootmagic salt key */
#define BOOTMAGIC_KEY_SALT              KC_ESC

/* skip bootmagic and eeconfig */
#define BOOTMAGIC_KEY_SKIP              KC_SPACE

#define PREVENT_STUCK_MODIFIERS

#define RGBSPS_ENABLE
#define RGBSPS_DEMO_ENABLE

#define UNICODE_TYPE_DELAY 0

#define LAYOUT_DVORAK
#define LAYOUT_COLEMAK
#define LAYOUT_NORMAN
#define LAYOUT_WORKMAN

#define DOUBLESPACE_LAYER_ENABLE
// #define TOLELOT_ENABLE

#endif
