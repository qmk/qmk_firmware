/*
Copyright 2019 Andre Poley <andre.poley@mailbox.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "quantum.h"
#include "kuchosauronad0.h"

userspace_config_t userspace_config;
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
#  define KUCHOSAURONAD0_UNICODE_MODE UC_WINC
#else
#  define KUCHOSAURONAD0_UNICODE_MODE 2 // set to 2 for UC_WIN, set to 4 for UC_WINC
#endif


// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void) {
  userspace_config.raw = eeconfig_read_user();

  #ifdef BOOTLOADER_CATERINA
    DDRD &= ~(1<<5);
    PORTD &= ~(1<<5);

    DDRB &= ~(1<<0);
    PORTB &= ~(1<<0);
  #endif

  #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(KUCHOSAURONAD0_UNICODE_MODE);
    get_unicode_input_mode();
  #endif //UNICODE_ENABLE
  matrix_init_keymap();
}

__attribute__((weak))
void keyboard_post_init_keymap(void){ }

void keyboard_post_init_user(void){
#ifdef RGBLIGHT_ENABLE
  keyboard_post_init_rgb();
#endif
  keyboard_post_init_keymap();
}

__attribute__ ((weak))
void shutdown_keymap(void) {}

void shutdown_user (void) {
  #ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb_teal();
  #endif // RGBLIGHT_ENABLE
  #ifdef RGB_MATRIX_ENABLE
    // uint16_t timer_start = timer_read();
    // rgb_matrix_set_color_all( 0xFF, 0x00, 0x00 );
    // while(timer_elapsed(timer_start) < 250) { wait_ms(1); }
  #endif //RGB_MATRIX_ENABLE
  shutdown_keymap();
}

__attribute__ ((weak))
void suspend_power_down_keymap(void) {}

void suspend_power_down_user(void) {
    suspend_power_down_keymap();
}

__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
  suspend_wakeup_init_keymap();
}


__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_user(void){
  static bool has_ran_yet;
  if (!has_ran_yet) {
    has_ran_yet = true;
    startup_user();
  }

#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
//  run_diablo_macro_check();
#endif // !TAP_DANCE_ENABLE

#ifdef RGBLIGHT_ENABLE
  matrix_scan_rgb();
#endif // !RGBLIGHT_ENABLE

  matrix_scan_keymap();
}

__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#ifdef RGBLIGHT_ENABLE
  state = layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
  return layer_state_set_keymap (state);
}


__attribute__ ((weak))
layer_state_t default_layer_state_set_keymap (layer_state_t state) {
  return state;
}

// Runs state check and changes underglow color and animation
layer_state_t default_layer_state_set_user(layer_state_t state) {
  state = default_layer_state_set_keymap(state);
#if 0
#ifdef RGBLIGHT_ENABLE
  state = default_layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
#endif
  return state;
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

// Any custom LED code goes here.
// So far, I only have keyboard specific code,
// So nothing goes here.
void led_set_user(uint8_t usb_led) {
  led_set_keymap(usb_led);
}
__attribute__ ((weak))
void eeconfig_init_keymap(void) {}

void eeconfig_init_user(void) {
  userspace_config.raw = 0;
  userspace_config.rgb_layer_change = true;
  eeconfig_update_user(userspace_config.raw);
  #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(KUCHOSAURONAD0_UNICODE_MODE);
    get_unicode_input_mode();
  #else
    eeprom_update_byte(EECONFIG_UNICODEMODE, KUCHOSAURONAD0_UNICODE_MODE);
  #endif
  eeconfig_init_keymap();
  keyboard_init();
}

// TMUX stuff
void tmux_prefix(void) {
  register_code(KC_LCTL);
  tap_code(KC_B);
  unregister_code(KC_LCTL);
}


void tmux_pane_last(void) {
  tmux_prefix();
  tap_code(KC_SCLN);
}

void tmux_pane_switch_repeat(void) {
  tmux_pane_last();
  tap_code(KC_UP);
  tap_code(KC_ENT);
  tmux_pane_last();
}

/* vi: ft=c:tw=80:sw=2:ts=2:sts=2:et */
