#pragma once

#ifndef ericgebhart
#define ericgebhart

#include QMK_KEYBOARD_H
#include "core_keysets.h"
#include "base_layers.h"
#include "layers.h"
#if defined(OLED_ENABLE)
#    include "oled_stuff.h"
#endif


//#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
/* Define layer names */
enum userspace_layers {
    _DVORAK = 0,
    _QWERTY,
    _COLEMAK,
    _BEAKL,
    //_WORKMAN,
    //_NORMAN,
    //_MALTRON,
    //_EUCALYN,
    //_CARPLAX,
    _DVORAK_BP, // beginning of Bepo
    _BEAKL_BP,
    _BEPO,
    _NAV,   // transient layers
    _SYMB,
    _SYMB_BP,
    _KEYPAD,
    _KEYPAD_BP,
    _TOPROWS,
    _TOPROWS_BP,
    _LAYERS,
    _RGB,
    _ADJUST,
};

// clang-format off
typedef union {
  uint32_t raw;
  struct {
    bool    rgb_layer_change     :1;
    bool    is_overwatch         :1;
    bool    nuke_switch          :1;
    bool    swapped_numbers      :1;
    bool    rgb_matrix_idle_anim :1;
  };
} userspace_config_t;
// clang-format on
extern userspace_config_t userspace_config;

#endif
