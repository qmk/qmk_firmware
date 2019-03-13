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
#ifdef SOLENOID_ENABLE
#include "solenoid.h"
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
  if (!haptic_config.mode){
  dprintf("No haptic config found in eeprom, setting default configs\n");
  haptic_reset();
  }
  #ifdef SOLENOID_ENABLE
    solenoid_setup();
    dprintf("Solenoid driver initialized\n");
  #endif
  #ifdef DRV2605L
    DRV_init();
    dprintf("DRV2605 driver initialized\n");
  #endif
  eeconfig_debug_haptic();
}

void haptic_task(void) {
  #ifdef SOLENOID_ENABLE
  solenoid_check();
  #endif
}

void eeconfig_debug_haptic(void) {
  dprintf("haptic_config eprom\n");
  dprintf("haptic_config.enable = %d\n", haptic_config.enable);
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

void haptic_buzz_toggle(void) {
  bool buzz_stat = !haptic_config.buzz;
  haptic_config.buzz = buzz_stat;
  haptic_set_buzz(buzz_stat);
}

void haptic_mode_increase(void) {
  uint8_t mode = haptic_config.mode + 1;
  #ifdef DRV2605L
  if (haptic_config.mode >= drv_effect_max) {
    mode = 1;
  }
  #endif
    haptic_set_mode(mode);
}

void haptic_mode_decrease(void) {
  uint8_t mode = haptic_config.mode -1;
  #ifdef DRV2605L
  if (haptic_config.mode < 1) {
    mode = (drv_effect_max - 1);
  }
  #endif
  haptic_set_mode(mode);
}

void haptic_dwell_increase(void) {
  uint8_t dwell = haptic_config.dwell + 1;
  #ifdef SOLENOID_ENABLE
  if (haptic_config.dwell >= SOLENOID_MAX_DWELL) {
    dwell = 1;
  }
  solenoid_set_dwell(dwell);
  #endif
  haptic_set_dwell(dwell);
}

void haptic_dwell_decrease(void) {
  uint8_t dwell = haptic_config.dwell -1;
  #ifdef SOLENOID_ENABLE
  if (haptic_config.dwell < SOLENOID_MIN_DWELL) {
    dwell = SOLENOID_MAX_DWELL;
  }
  solenoid_set_dwell(dwell);
  #endif
  haptic_set_dwell(dwell);
}

void haptic_reset(void){
  haptic_config.enable = true;
  uint8_t feedback = HAPTIC_FEEDBACK_DEFAULT;
  haptic_config.feedback = feedback;
  #ifdef DRV2605L
    uint8_t mode = HAPTIC_MODE_DEFAULT;
    haptic_config.mode = mode;
  #endif
  #ifdef SOLENOID_ENABLE
    uint8_t dwell = SOLENOID_DEFAULT_DWELL;
    haptic_config.dwell = dwell;
  #endif
  eeconfig_update_haptic(haptic_config.raw);
  xprintf("haptic_config.feedback = %u\n", haptic_config.feedback);
  xprintf("haptic_config.mode = %u\n", haptic_config.mode);
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

void haptic_set_buzz(uint8_t buzz) {
  haptic_config.buzz = buzz;
  eeconfig_update_haptic(haptic_config.raw);
  xprintf("haptic_config.buzz = %u\n", haptic_config.buzz);
}

void haptic_set_dwell(uint8_t dwell) {
  haptic_config.dwell = dwell;
  eeconfig_update_haptic(haptic_config.raw);
  xprintf("haptic_config.dwell = %u\n", haptic_config.dwell);
}

uint8_t haptic_get_mode(void) {
  if (!haptic_config.enable){
    return false;
  }
  return haptic_config.mode;
}

uint8_t haptic_get_feedback(void) {
  if (!haptic_config.enable){
    return false;
  }
  return haptic_config.feedback;
}

uint8_t haptic_get_dwell(void) {
  if (!haptic_config.enable){
    return false;
  }
  return haptic_config.dwell;
}

void haptic_play(void) {
  #ifdef DRV2605L
  uint8_t play_eff = 0;
  play_eff = haptic_config.mode;
  DRV_pulse(play_eff);
  #endif
  #ifdef SOLENOID_ENABLE
  solenoid_fire();
  #endif
}

bool process_haptic(uint16_t keycode, keyrecord_t *record) {
    if (keycode == HPT_ON && record->event.pressed) { haptic_enable(); }
    if (keycode == HPT_OFF && record->event.pressed) { haptic_disable(); }
    if (keycode == HPT_TOG && record->event.pressed) { haptic_toggle(); }
    if (keycode == HPT_RST && record->event.pressed) { haptic_reset(); }
    if (keycode == HPT_FBK && record->event.pressed) { haptic_feedback_toggle(); }
    if (keycode == HPT_BUZ && record->event.pressed) { haptic_buzz_toggle(); }
    if (keycode == HPT_MODI && record->event.pressed) { haptic_mode_increase(); }
    if (keycode == HPT_MODD && record->event.pressed) { haptic_mode_decrease(); }
    if (keycode == HPT_DWLI && record->event.pressed) { haptic_dwell_increase(); }
    if (keycode == HPT_DWLD && record->event.pressed) { haptic_dwell_decrease(); }
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

void haptic_shutdown(void) {
  #ifdef SOLENOID_ENABLE
  solenoid_shutdown();
  #endif

}
