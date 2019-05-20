#ifndef USERSPACE
#define USERSPACE

//#pragma once

#include "quantum.h"

#include "version.h"
#include "eeprom.h"
#include "wrappers.h"
#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
#endif // TAP_DANCE_ENABLE
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
  #include "rgb_stuff.h"
#endif
#if defined(UNICODEMAP_ENABLE) || defined(UNICODE_ENABLE)
  #include "unicode.h"
#endif // UNICODE ENABLE
// Keycode aliases
#define OSL_UNI OSL(UNICODE) // activate unicode layer for one key
#define TM_X LCTL(KC_B) // Tmux control sequence
#define KC_TMX TD(TD_TMX) // Tmux control sequence
#define KC_EOL TD(TD_EOL)
#define KC_BOL TD(TD_BOL)
#define KC_NW TD(TD_NW)
#define KC_PW TD(TD_PW)
#define KC_DW TD(TD_DW)
#define MC_EOL LCTL(KC_E)
#define MC_BOL LCTL(KC_A)
#define MC_NW LALT(KC_F)
#define MC_PW LALT(KC_B)
#define MC_DW LCTL(KC_W)

// Define layer names
enum userspace_layers {
  _QWERTY = 0,
  _NUMLOCK = 0,
  _COLEMAK,
  _DVORAK,
  _WORKMAN,
  _NORMAN,
  _MALTRON,
  _EUCALYN,
  _CARPLAX,
  _UNICODE,
  _MODS, /* layer 8 now 9*/
  _GAMEPAD,
  _DIABLO,
  _MACROS,
  _MEDIA,
  _LOWER,
  _RAISE,
  _ADJUST,
};

bool mod_key_press_timer (uint16_t code, uint16_t mod_code, bool pressed);
bool mod_key_press (uint16_t code, uint16_t mod_code, bool pressed, uint16_t this_timer);
bool send_game_macro(const char *str, keyrecord_t *record, bool override);
void matrix_init_keymap(void);
void shutdown_keymap(void);
void suspend_power_down_keymap(void);
void suspend_wakeup_init_keymap(void);
void matrix_scan_keymap(void);
uint32_t layer_state_set_keymap (uint32_t state);
uint32_t default_layer_state_set_keymap (uint32_t state);
void led_set_keymap(uint8_t usb_led);
void eeconfig_init_keymap(void);

void tmux_prefix(void);
void tmux_pane_zoom(void);
void tmux_pane_last(void);
void tmux_pane_switch_repeat(void);
void tmux_pane_switch(uint16_t keycode);

void git_commit(void);
void git_add(void);
void git_push(void);
void git_revert(void);
void git_log(void);
void git_status(void);


typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
    bool     is_overwatch     :1;
    bool     nuke_switch      :1;
    uint8_t  unicode_mod      :4;
    bool     swapped_numbers  :1;
  };
} userspace_config_t;

extern userspace_config_t userspace_config;

/*
Custom Keycodes for Diablo 3 layer
But since TD() doesn't work when tap dance is disabled
We use custom codes here, so we can substitute the right stuff
*/
#ifdef TAP_DANCE_ENABLE
#define KC_D3_1 TD(TD_D3_1)
#define KC_D3_2 TD(TD_D3_2)
#define KC_D3_3 TD(TD_D3_3)
#define KC_D3_4 TD(TD_D3_4)
#else // TAP_DANCE_ENABLE
#define KC_D3_1 KC_1
#define KC_D3_2 KC_2
#define KC_D3_3 KC_3
#define KC_D3_4 KC_4
#endif // TAP_DANCE_ENABLE

#endif // !USERSPACE
