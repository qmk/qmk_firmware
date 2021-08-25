/* https://docs.qmk.fm/#/tap_hold?id=ignore-mod-tap-interrupt */
#define IGNORE_MOD_TAP_INTERRUPT

/* https://docs.qmk.fm/#/tap_hold?id=retro-tapping */
#define RETRO_TAPPING

/*
  allow the microdox board to work with either controller plugged in
  docs: https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom

  flashing the controllers:
  make boardsource/microdox:via:dfu-split-left
  make boardsource/microdox:via:dfu-split-right

  loading keymap with via: load your via keymap with each side plugged in
*/
#define EE_HANDS
