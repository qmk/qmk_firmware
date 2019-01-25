/* Copyright 2019 ishtob
 * Driver for haptic feedback written for QMK
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
#include "haptic.h"
#include "eeconfig.h"
#include "progmem.h"
#include "debug.h"
#ifdef DRV2605L
#include "DRV2605L.h"
#endif

haptic_config_t haptic_config;

void haptic_init(void) {
  debug_enable = 1; //Debug is ON!
  if (!eeconfig_is_enabled()) {
  	eeconfig_init();
  }
  haptic_config.raw = eeconfig_read_haptic();
  if (haptic_config.mode < 1){
  haptic_config.mode = 1;
  }
  #ifdef DRV2605L
    DRV_init();
    dprintf("DRV2605 driver initialized\n");
  #endif
  eeconfig_debug_haptic();
}

void eeconfig_debug_haptic(void) {
  dprintf("haptic_config eprom\n");
  dprintf("haptic_config.enable = %d\n", haptic_config.enable);
  dprintf("haptic_config.intensity = %d\n", haptic_config.intensity);
  dprintf("haptic_config.mode = %d\n", haptic_config.mode);
}

void haptic_enable(void) {
  haptic_config.enable = 1;
  xprintf("haptic_config.enable = %u\n", haptic_config.enable);
  eeconfig_update_haptic(haptic_config.raw);
}

void haptic_disable(void) {
  haptic_config.enable = 0;
  xprintf("haptic_config.enable = %u\n", haptic_config.enable);
  eeconfig_update_haptic(haptic_config.raw);
}

void haptic_toggle(void) {
if (haptic_config.enable) {
  haptic_disable();
  } else {
  haptic_enable();
  }
  eeconfig_update_haptic(haptic_config.raw);
}

void haptic_feedback_toggle(void){
 haptic_config.feedback++;
  if (haptic_config.feedback >= HAPTIC_FEEDBACK_MAX)
  haptic_config.feedback = KEY_PRESS;
  xprintf("haptic_config.feedback = %u\n", !haptic_config.feedback);
  eeconfig_update_haptic(haptic_config.raw);
}

void haptic_mode_increase(void) {
  uint8_t mode = haptic_config.mode + 1;
  if (haptic_config.mode >= drv_effect_max) {
    haptic_config.mode = 1;
  }
    haptic_set_mode(mode);
}

void haptic_mode_decrease(void) {
  uint8_t mode = haptic_config.mode -1;
  if (haptic_config.mode < 1) {
    mode = (drv_effect_max - 1);
  }
  haptic_set_mode(mode);
}

void haptic_mode_reset(void){
  intensity = HAPTIC_INTENSITY_DEFAULT
  feedback = HAPTIC_FEEDBACK_DEFAULT
  mode = HAPTIC_MODE_DEFAULT
  haptic_config.intensity = intensity;
  haptic_config.feedback = feedback;
  haptic_config.mode = mode;
  eeconfig_update_haptic(haptic_config.raw);
  xprintf("haptic_config.feedback = %u\n", haptic_config.feedback);
  xprintf("haptic_config.intensity = %u\n", haptic_config.intensity);
  xprintf("haptic_config.mode = %u\n", haptic_config.mode);
}

void haptic_set_intensity(uint8_t intensity) {
  haptic_config.intensity = intensity;
  eeconfig_update_haptic(haptic_config.raw);
  xprintf("haptic_config.intensity = %u\n", haptic_config.intensity);

}

void haptic_set_feedback(uint8_t feedback) {
  haptic_config.feedback = feedback;
  eeconfig_update_haptic(haptic_config.raw);
  xprintf("haptic_config.feedback = %u\n", haptic_config.feedback);

}

void haptic_set_mode(uint8_t mode) {
  haptic_config.mode = mode;
  eeconfig_update_haptic(haptic_config.raw);
  xprintf("haptic_config.mode = %u\n", haptic_config.mode);
}


uint8_t haptic_get_mode(void) {
  if (!haptic_config.enable){
    return false;
  }
  return haptic_config.mode;
}

uint8_t haptic_get_feedback(uint8_t mode) {
  if (!haptic_config.enable){
    return false;
  }
  return haptic_config.feedback;
}

uint8_t haptic_get_intensity(uint8_t intensity) {
  if (!haptic_config.enable){
    return false;
  }
  return haptic_config.intensity;
}

void haptic_play(void) {
  uint8_t play_eff = 0;
  play_eff = haptic_config.mode;
  #ifdef DRV2605L
  DRV_pulse(play_eff);
  #endif
}

bool process_haptic(uint16_t keycode, keyrecord_t *record) {
    if (keycode == HAPT_TOGGLE && record->event.pressed) { haptic_toggle(); }
    if (keycode == HAPT_ON && record->event.pressed) { haptic_enable(); }
    if (keycode == HAPT_OFF && record->event.pressed) { haptic_disable(); }
    if (keycode == HAPT_FEEDBACK && record->event.pressed) { haptic_feedback_toggle(); }
    if (keycode == HAPT_MODE_INC && record->event.pressed) { haptic_mode_increase(); }
    if (keycode == HAPT_MODE_DEC && record->event.pressed) { haptic_mode_decrease(); }
    if (keycode == HAPT_MODE_RESET && record->event.pressed) { haptic_mode_reset(); }
  if (haptic_config.enable) {
    if ( record->event.pressed ) {
	// keypress
      if (haptic_config.feedback < 2) {
      haptic_play();
      }
    } else {
    //keyrelease
      if (haptic_config.feedback > 0) {
      haptic_play();
      } 
    }
  }
  return true;
}