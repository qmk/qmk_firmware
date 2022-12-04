#pragma once


/* key matrix pins */

#define MATRIX_ROW_PINS { B5, B4, D7, D6 }
#define MATRIX_COL_PINS { E6, F0, F1, C7, C6, B6, D4, D5, D3, D2, D1, D0, B7, B0 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW


#define RGB_DI_PIN F7
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 10
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
#define GRAVE_ESC_CTRL_OVERRIDE






