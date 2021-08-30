/* https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term */
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

/* https://docs.qmk.fm/#/tap_hold?id=ignore-mod-tap-interrupt */
#define IGNORE_MOD_TAP_INTERRUPT
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

/* https://docs.qmk.fm/#/tap_hold?id=retro-tapping */
/* #define RETRO_TAPPING */

/*
  allow the microdox board to work with either controller plugged in
  docs: https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom

  flashing the controllers:
  make boardsource/microdox:via:dfu-split-left
  make boardsource/microdox:via:dfu-split-right

  loading keymap with via: load your via keymap with each side plugged in
*/
#define EE_HANDS

/* https://beta.docs.qmk.fm/developing-qmk/qmk-reference/config_options#features-that-can-be-enabled */
#define FORCE_NKRO

/* combos: https://beta.docs.qmk.fm/using-qmk/software-features/feature_combo */
#define COMBO_ALLOW_ACTION_KEYS
#define COMBO_VARIABLE_LEN
#define COMBO_PERMISSIVE_HOLD
