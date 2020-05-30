/* Copyright 2019 bemeier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bmek.h"
#include "../bmledlib.h"

void bm_update_led_indicators(void);
kb_config_big_t bmek_config;

// Smooth LED transitions
enum bmled_smooth_vals {
  smooth_brightness = 0,
  smooth_saturation,
  smooth_layer_hue
};

static bool leds_enabled = true;

// Idle Timers
static bool idle = false;
static uint32_t idle_timer;
// TODO: make this configurable from keymap/rules.mk?
static uint32_t idle_timeout = 120000;

// Config
static bool settings_dirty = false;
static uint8_t cfg_layer_idx = 0;
static bool multiply_speed = false;

// Macros
static bool recording = false;


void bmek_update_config(void) {
    eeprom_update_dword(EECONFIG_BMEK_0, bmek_config.raw_hue0);
    eeprom_update_dword(EECONFIG_BMEK_1, bmek_config.raw_hue1);
    eeprom_update_dword(EECONFIG_BMEK_2, bmek_config.raw_hue2);
    eeprom_update_dword(EECONFIG_BMEK_3, bmek_config.raw_hue3);
    eeprom_update_dword(EECONFIG_BMEK_4, bmek_config.raw_bri_sat_fade);
}

void bmek_read_config(void) {
    bmek_config.raw_hue0 = eeprom_read_dword(EECONFIG_BMEK_0);
    bmek_config.raw_hue1 = eeprom_read_dword(EECONFIG_BMEK_1);
    bmek_config.raw_hue2 = eeprom_read_dword(EECONFIG_BMEK_2);
    bmek_config.raw_hue3 = eeprom_read_dword(EECONFIG_BMEK_3);
    bmek_config.raw_bri_sat_fade = eeprom_read_dword(EECONFIG_BMEK_4);
}

void eeconfig_init_kb(void) {
  bmek_config.raw_hue0 = 0;
  bmek_config.raw_hue1 = 0;
  bmek_config.raw_hue2 = 0;
  bmek_config.raw_hue3 = 0;
  bmek_config.raw_bri_sat_fade = 0;
  bmek_config.layer_hues[0] = 100.0;
  bmek_config.layer_hues[1] = 120.0;
  bmek_config.layer_hues[2] = 180.0;
  bmek_config.layer_hues[3] = 210.0;
  bmek_config.brightness = 255;
  bmek_config.saturation = 255;
  bmek_config.fade_span = 25;
  bmek_update_config();
}

void matrix_init_kb(void) {
  // idle timer (turns of lights after idle_timeout ms)
  bmek_read_config();

  // Setup smoothing engine
  bmled_smooth_init(smooth_brightness, 0, (float) bmek_config.brightness, 0, 255, 0.2, false);
  bmled_smooth_init(smooth_saturation, 0, (float) bmek_config.saturation, 0, 255, 0.3, false);
  bmled_smooth_init(smooth_layer_hue, 0, bmek_config.layer_hues[eeconfig_read_default_layer()], 1, 255, 0.25, true);
  rgblight_enable_noeeprom();
  return matrix_init_user();
}

void matrix_scan_kb(void) {
  bm_update_led_indicators();
  return matrix_scan_user();
}

void dynamic_macro_record_start_user(void) {
  recording = true;
}

void dynamic_macro_record_key_user(int8_t dir, keyrecord_t *record) {
  bmled_smooth_add_target(smooth_saturation, -255);
}

void dynamic_macro_record_end_user(int8_t dir) {
  recording = false;
}

void dynamic_macro_play_user(int8_t dir) {
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  // Wake up from idle on keypress, re-enable lights and reset timer
  if (idle || timer_elapsed32(idle_timer) >= idle_timeout) {
    if (idle && leds_enabled) rgblight_enable_noeeprom();
    idle = false;
    idle_timer = timer_read32();
  }

  // Config keycodes
  switch (keycode) {
    case BM_MULT: // FASTER CONFIG CHANGES
      if (record->event.pressed)
        multiply_speed = true;
      else
        multiply_speed = false;
      break;
    case BM_LED: // TOGGLE LEDS
      if (record->event.pressed) break;
      leds_enabled = !leds_enabled;
      if (leds_enabled) rgblight_enable_noeeprom();
      else rgblight_disable_noeeprom();
      break;
    case BM_RST: // RESET KEYBOARD
      if (record->event.pressed) break;
      rgblight_sethsv(250, 255, 50);
      reset_keyboard();
      break;
    case BM_WIPE: // RESET EEPROM
      if (record->event.pressed) break;
      eeconfig_init();
      break;
	case BM_HI_1 ... BM_HD_4: // SET LAYER COLORS
      settings_dirty = true;
      float delta = 0.25;
      if (multiply_speed) delta = delta * 10;
      cfg_layer_idx = keycode - BM_HI_1;
      if (keycode >= BM_HD_1) {
        delta = -delta;
        cfg_layer_idx = keycode - BM_HD_1;
      }
      float new_val = fmod((bmek_config.layer_hues[cfg_layer_idx] + delta), 255.0);
      bmek_config.layer_hues[cfg_layer_idx] = new_val;
      break;
    case BM_SI ... BM_FD: // BRIGHTNESS, SATURATION & INDICATOR FADE
	  settings_dirty = true;
	  int delta_sb = 1;
      if (multiply_speed) delta = delta * 10;
      if (keycode == BM_BI) bmled_smooth_add_target(smooth_brightness,  delta_sb);
      if (keycode == BM_BD) bmled_smooth_add_target(smooth_brightness, -delta_sb);
      if (keycode == BM_SI) bmled_smooth_add_target(smooth_saturation,  delta_sb);
      if (keycode == BM_SD) bmled_smooth_add_target(smooth_saturation, -delta_sb);
      bmek_config.brightness = bmled_get_target(smooth_brightness);
      bmek_config.saturation = bmled_get_target(smooth_saturation);
      if (keycode == BM_FI && bmek_config.fade_span < 255)
        bmek_config.fade_span += delta_sb;
      if (keycode == BM_FD && bmek_config.fade_span > 0)
        bmek_config.fade_span -= delta_sb;
	  bmek_config.fade_span = (uint8_t) fmax(fmin(bmek_config.fade_span, 255), 0);
	  break;
  }

  return process_record_user(keycode, record);
}

void bm_update_led_indicators(void) {
  // get the highest active (default) layer to set the color indicator...
  layer_state_t hl = get_highest_layer(layer_state);
  layer_state_t hdl = get_highest_layer(default_layer_state);
  if (recording) {
	// Do nothing, target is updated below...
  } else if (hl > hdl && hl <= 3) { // only first 4 layers supported since we cant store more than 4 bytes of hue data in eeprom easily(?)
    bmled_smooth_set_target_f(smooth_layer_hue, bmek_config.layer_hues[hl]);
    bmled_smooth_set_target(smooth_saturation, bmek_config.saturation);
  } else if (hdl <= 3 && hl < 3) {
    bmled_smooth_set_target_f(smooth_layer_hue, bmek_config.layer_hues[hdl]);
    bmled_smooth_set_target(smooth_saturation, bmek_config.saturation);
    if (settings_dirty) {
      settings_dirty = false;
      bmek_update_config();
    }
  } else { // If on a higher layer, we assume it's the config layer and instead we show the currently configured hue:
    bmled_smooth_set_target(smooth_layer_hue, bmek_config.layer_hues[cfg_layer_idx]);
    bmled_smooth_set_target(smooth_saturation, bmek_config.saturation);
  }

  if (leds_enabled && bmled_smooth_update()) {
    float span = (float) bmek_config.fade_span / 1.55;
	if (recording) {
	  bmled_smooth_add_target(smooth_layer_hue, 7);
	  span = 64;
    } 

	uint8_t current_hue = bmled_get_val_f(smooth_layer_hue);
    int half_leds = RGBLED_NUM/2;
	for (int i = 0; i < half_leds; i++) {
		uint8_t this_hue = (uint8_t) (current_hue - span * fmod((float) i / (RGBLED_NUM/2.0), 255.0));
    	rgblight_sethsv_at(this_hue, bmled_get_val(smooth_saturation), bmled_get_val(smooth_brightness), i);
    	rgblight_sethsv_at(this_hue, bmled_get_val(smooth_saturation), bmled_get_val(smooth_brightness), i+half_leds);
	}


    if (!idle && timer_elapsed32(idle_timer) >= idle_timeout) {
		// fade out when the timer is reached:
        bmled_smooth_set_target(smooth_brightness, 0);
		// turn of led's completely after fade is complete:
		if (bmled_get_val(smooth_brightness) <= 1) {
          rgblight_disable_noeeprom();
          idle = true;
        }
    } else if (!idle) {
      bmled_smooth_set_target(smooth_brightness, bmek_config.brightness);
    }
  }
}
