#ifndef CONFIG_H
#define CONFIG_H
 
#include "config_common.h"
#include "config.h"
 
/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
@@ -51,4 +51,8 @@
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
 
/* sets 'Auto Shift' timeouts */
#define AUTO_SHIFT_TIMEOUT 150
#define NO_AUTO_SHIFT_SPECIAL

#endif