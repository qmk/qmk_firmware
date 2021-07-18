#include QMK_KEYBOARD_H

/*
  Define a keycode KF_LAYO to rotate between available default layers.
  Shift+KF_LAYO makes the current one persistent.

  To use:

  in your keymap.c, define KF_LAYO so it does not conflict with anything else.
  then include this header and set highest_base_layer.

    #define KF_LAYO SAFE_RANGE
    #include "feature_default_layers_selector.h"

    const uint8_t highest_base_layer = 4; // the index

  and in your rules.mk,

    SRC += feature_default_layers_selector.c
*/

/*
  See https://docs.qmk.fm/#/keymap for docs about layers including the concept
  of "base" or "default" layers.

  This is broken into two functions so that:

  - If you don't want to store the default layer state in eeprom, don't call
  process_record_save_default_layer.

  - If you have your own mechanism for setting the default layer state (to one
  or multiple layers), do that instead of process_record_select_default_layer.

  If you call both functions, call process_record_save_default_layer first.

  The QMK docs seem to assume that you will have only one layer as your
  default layer at any time, but the source code actually supports an arbitrary
  default_layer_state (composition of layers)

  quantum has "set_single_persistent_default_layer" but that writes to eeprom
  every time you change your default layer preference. i wanted a behavior
  instead which lets you switch default layers all you want, then store the
  current configuration once you're happy with it. that way if you get into an
  unusable state you can just unplug and replug your keyboard to escape from it.

  this code assumes:

  1. each default layer state that you would select among consists of a single
  layer, which we will call a "base" layer.

  2. all your "base" layers are stored contiguously at the bottom of your
  keymaps[] stack, and there are no non-"base" layers mixed in.

  3. you have a maximum of 8 "base" layers. that is, the highest base layer is
  index 7.

  while 16 and 32 bit platforms might allow default_layer_state to include more
  and higher-numbered layers, eeconfig_update_default_layer saves only the first
  8 bits of default_layer_state to eeprom.

*/

#ifndef KF_LAYO
#define KF_LAYO SAFE_RANGE
#endif

const uint8_t highest_base_layer;
bool process_record_save_default_layer(uint16_t keycode, keyrecord_t *record);
bool process_record_select_default_layer(uint16_t keycode, keyrecord_t *record);
