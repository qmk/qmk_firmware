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

haptic_config_t haptic_config;

void haptic_init(void) {
  /*check signature */
  if (!eeconfig_is_enabled()) {
  	eeconfig_init();
  }
  haptic_config.raw = eeconfig_read_haptic();
  #ifdef DRV2605L
    DRV_init();
    dprintf("DRV2605 driver initialized\n");
    //temp testing to start keys
  #endif
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
  xprintf("haptic_config.enable = %u\n", !haptic_config.enable);
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
  haptic_config.feedback = 0;
  eeconfig_update_haptic(haptic_config.raw);
}

void haptic_mode_toggle(void){
  haptic_config.mode++;
    if (haptic_config.mode >= drv_effect_max) {haptic_config.mode = 0;}
      haptic_config.mode = 0;
  eeconfig_update_haptic(haptic_config.raw);
}

void haptic_play(void) {
  #ifdef DRV2605L
  DRV_EFFECT play_eff = strong_click; 
  DRV_pulse(play_eff);
  #endif
}

bool process_haptic(uint16_t keycode, keyrecord_t *record) {
    if (keycode == HAPT_TOGGLE && record->event.pressed) { haptic_toggle(); }
    if (keycode == HAPT_ON && record->event.pressed) { haptic_enable(); }
    if (keycode == HAPT_OFF && record->event.pressed) { haptic_disable(); }
    if (keycode == HAPT_FEEDBACK && record->event.pressed) { haptic_feedback_toggle(); }
    if (keycode == HAPT_MODE && record->event.pressed) { haptic_mode_toggle(); }
  if (haptic_config.enable) {
    if ( record->event.pressed ) {
	// keypress
      if (haptic_config.feedback < 3) {
      haptic_play();
      }
    } else {
    //keyrelease
      if (haptic_config.feedback > 1) {
      haptic_play();
      }
    }
  }
  return true;
}
