#include "rgblight_user.h"
extern rgblight_config_t rgblight_config;
bool                     has_initialized;
uint8_t                  base_hue;  // Hue value of base state
uint8_t                  base_sat;  // Saturation value of base state
uint8_t                  base_val;  // Brightness value of base state
uint8_t                  base_mod;  // Animation mode of the base state

void rgblight_savebase(void) {  // Save the current settings to ram
  base_hue = rgblight_config.hue;
  base_sat = rgblight_config.sat;
  base_val = rgblight_config.val;
  base_mod = rgblight_config.mode;
}
void rgblight_loadbase(void) {  // Load settings from ram to eeprom
  rgblight_mode( base_mod );
  rgblight_sethsv_eeprom_helper(base_hue, base_sat, base_val, true);
}



bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }
  switch (keycode) {
    case KC_RGB_T:  // Switch between underglow layer indication and normal qmk behaviour
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
      if (record->event.pressed) {
        userspace_config.rgb_layer_change ^= 1;
        xprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
        eeconfig_update_user(userspace_config.raw);
        if (userspace_config.rgb_layer_change) {
          layer_state_set(layer_state);  // Immediately set the layer color (looks better)
        }
      }
#endif  // RGBLIGHT_ENABLE
      return false;
      break;
#ifdef RGBLIGHT_ENABLE
    case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT:  // quantum_keycodes.h L400 for definitions
      if (record->event.pressed) {  // This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
        if (userspace_config.rgb_layer_change) {
          userspace_config.rgb_layer_change = false;
          xprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
          eeconfig_update_user(userspace_config.raw);
        }
      }
      return true;
      break;
#endif  // RGBLIGHT_ENABLE
  }
  return true;
}

void keyboard_post_init_rgb(void) {
# if defined(RGBLIGHT_ENABLE) || defined(RGBLIGHT_STARTUP_ANIMATION)
  bool is_enabled = rgblight_config.enable;
  if (userspace_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
  }
  if (rgblight_config.enable) {
    layer_state_set_user(layer_state);
    uint16_t old_hue = rgblight_config.hue;
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    for (uint16_t i = 255; i > 0; i--) {
      rgblight_sethsv_noeeprom((i + old_hue) % 255, 255, 255);
      wait_ms(5);
    }
  }
  if (!is_enabled) {
    rgblight_disable_noeeprom();
  }
# endif // !RGBLIGHT_ENABLE || RGBLIGHT_STARTUP_ANIMATION
  layer_state_set_user(layer_state);
}

void matrix_scan_rgb(void) {
# ifdef INDICATOR_LIGHTS
  matrix_scan_indicator();
# endif
}

layer_state_t layer_state_set_rgb(layer_state_t state) {
# ifdef RGBLIGHT_ENABLE
  if (userspace_config.rgb_layer_change) {
    switch (get_highest_layer(state)) {  // _RAISE, _LOWER and _ADJUST use a custom color and the breathing effect
      case _RAISE:
        rgblight_sethsv_noeeprom_green();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        break;
      case _LOWER:
        rgblight_sethsv_noeeprom_red();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        break;
      case _ADJUST:
        rgblight_sethsv_noeeprom_white();
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
        break;
      default:  // Use a solid color for normal layers
        switch (get_highest_layer(default_layer_state)) {
          case _QWERTY:
            rgblight_sethsv_noeeprom_magenta();
            break;
          case _COLEMAK:
            rgblight_sethsv_noeeprom_green();
            break;
          case _DVORAK:
            rgblight_sethsv_noeeprom_blue();
            break;
          case _WORKMAN:
            rgblight_sethsv_noeeprom_goldenrod();
            break;
          case _PLOVER:
            rgblight_sethsv_noeeprom_pink();
            break;
          default:
            rgblight_sethsv_noeeprom_white();
            break;
        }
        get_highest_layer(state) == _MODS ? rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING) : rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);  // if _MODS layer is on, then breath to denote it
        break;
    }
  }
# endif  // !RGBLIGHT_ENABLE
  return state;
}

#ifdef INDICATOR_LIGHTS
void matrix_scan_indicator(void) {
  if (has_initialized) {
    set_rgb_indicators(get_mods(), host_keyboard_leds(), get_oneshot_mods());
  }
}
#endif // !INDICATOR_LIGHTS

void rgblight_fade_helper(bool direction){
  // true: increase val = fade in
  // false: decrease val = fade out
  for (uint8_t index = 0; index <  RGBLIGHT_VAL_STEP ; index++) {
    direction ? rgblight_increase_val()  : rgblight_decrease_val();
    wait_ms(5);
  }
}
void fadeflash_leds(uint8_t hue, uint8_t sat, uint8_t val){
  // indicate success / fail of a leader sequence
  // fade out, set new hue and saturation, fade in, fade out, set old color, fade in
  // this is used in leader.c
  // TODO: come up with a better name maybe
  rgblight_fade_helper(false);
  rgblight_sethsv_noeeprom(hue, sat, 0);
  rgblight_fade_helper(true);
  rgblight_fade_helper(false);
  rgblight_sethsv_noeeprom(base_hue, base_sat, 0);
  rgblight_fade_helper(true);
}
