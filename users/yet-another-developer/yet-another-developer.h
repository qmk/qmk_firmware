#pragma once
#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "wrappers.h"
#include "process_records.h"

#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
  #define KC_TMX TD(TD_TMX)   // tap1: 't'  tap2: <CTL>+b
  #define KC_EOL TD(TD_EOL)   // tap1: 'e'  tap2: <CTL>+e
  #define KC_BOL TD(TD_BOL)   // tap1: 'a'  tap2: <CTL>+a
  #define KC_NW TD(TD_NW)     // tap1: 'f'  tap2: <ALT>+f
  #define KC_PW TD(TD_PW)     // tap1: 'b'  tap2: <ALT>+b
  #define KC_DW TD(TD_DW)     // tap1: 'w'  tap2: <CTL>+w
#endif //!TAP_DANCE_ENABLE
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
  #include "rgb_stuff.h"
#endif
#if defined(UNICODEMAP_ENABLE) || defined(UNICODE_ENABLE)
  #include "unicode.h"
#endif //!UNICODE_ENABLE

#define MC_BOL LCTL(KC_A)   // jump to beginning of line
#define MC_EOL LCTL(KC_E)   // jump to end       of line
#define MC_NW LALT(KC_F)    //     next word
#define MC_PW LALT(KC_B)    // previous word
#define MC_DW LCTL(KC_W)    //   delete word

/* Define layer names */
enum userspace_layers {
    _QWERTY  = 0,
    _NUMLOCK = 0,
    _COLEMAK,
    _DVORAK,
    _WORKMAN,
    _UNICODE,
    _MODS, /* layer 8 */
    _MACROS,
    _MEDIA,
    _LOWER,
    _RAISE,
    _ADJUST,
};

bool          mod_key_press_timer(uint16_t code, uint16_t mod_code, bool pressed);
bool          mod_key_press(uint16_t code, uint16_t mod_code, bool pressed, uint16_t this_timer);
void          matrix_init_keymap(void);
void          suspend_power_down_keymap(void);
void          suspend_wakeup_init_keymap(void);
void          matrix_scan_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
void led_set_keymap(uint8_t usb_led);
void eeconfig_init_keymap(void);

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


