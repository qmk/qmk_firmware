// Configure the global tapping term (default: 200ms)
// https://docs.qmk.fm/#/tap_hold?id=tapping-term
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// Prevent normal rollover on alphas from accidentally triggering mods.
// https://docs.qmk.fm/#/tap_hold?id=ignore-mod-tap-interrupt
#define IGNORE_MOD_TAP_INTERRUPT
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// https://docs.qmk.fm/#/tap_hold?id=tapping-force-hold
#define TAPPING_FORCE_HOLD
#define TAPPING_FORCE_HOLD_PER_KEY

// Allow modifiers to be activated within the typing term
#define PERMISSIVE_HOLD
#define PERMISSIVE_HOLD_PER_KEY

/*
  allow the microdox board to work with either controller plugged in
  docs: https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom

  flashing the controllers:
  make boardsource/microdox:chadhs:dfu-split-left
  make boardsource/microdox:chadhs:dfu-split-right
*/
#define EE_HANDS

// https://docs.qmk.fm/#/config_options?id=features-that-can-be-enabled
#define FORCE_NKRO

// https://beta.docs.qmk.fm/using-qmk/software-features/feature_combo
#define COMBO_VARIABLE_LEN // http://combos.gboards.ca/docs/install/#combos
#define COMBO_TERM 50 // http://combos.gboards.ca/docs/install/#combos
#define COMBO_ALLOW_ACTION_KEYS
#define COMBO_PERMISSIVE_HOLD

// https://docs.qmk.fm/#/feature_rgblight?id=lighting-layers
#define RGBLIGHT_LAYERS
// https://docs.qmk.fm/#/feature_rgblight?id=configuration
// see info.json in the v1 folder
//#define RGBLIGHT_LIMIT_VAL 192

// https://docs.qmk.fm/#/feature_mouse_keys?id=accelerated-mode
/* #define MOUSEKEY_INTERVAL 16 */
/* #define MOUSEKEY_DELAY 0 */
/* #define MOUSEKEY_TIME_TO_MAX 60 */
/* #define MOUSEKEY_MAX_SPEED 4 // 7 */
/* #define MOUSEKEY_WHEEL_DELAY 0 */
