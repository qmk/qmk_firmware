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
  #ifdef DRV2605L
    DRV_init();
    dprintf("DRV2605 driver initialized\n");
    //temp testing to start keys
    haptic_enable();
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
  haptic_config.enable ^= 1;
  xprintf("haptic_config.enable = %u\n", haptic_config.enable);
  eeconfig_update_haptic(haptic_config.raw);
}

void haptic_play(void) {
  #ifdef DRV2605L
  DRV_EFFECT play_eff = strong_click; 
  DRV_pulse(play_eff);
  #endif
}

bool process_haptic(uint16_t keycode, keyrecord_t *record) {
  if (haptic_config.enable) {
    if ( record->event.pressed ) {
	// keypress
      if (haptic_config.keypress < 2) {
      void haptic_play();
      }
    } else {
    //keyrelease
      if (haptic_config.keypress > 1) {
      void haptic_play();
      }
    }
  }
  return true;
}
