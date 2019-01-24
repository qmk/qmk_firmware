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

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#ifdef DRV2605L
#include "DRV2605L.h"
#endif

/* EEPROM config settings */
typedef union {
  uint16_t raw;
  struct {
    bool    enable    :1;
    uint8_t feedback  :2;
    uint8_t reserved  :8;
/* bits reserved for future features */
    uint8_t mode      :7;
  };
} haptic_config_t;

typedef enum HAPTIC_FEEDBACK{
  KEY_PRESS,
  KEY_PRESS_RELEASE,
  KEY_RELEASE,
  HAPTIC_FEEDBACK_MAX,
} HAPTIC_FEEDBACK;

bool process_haptic(uint16_t keycode, keyrecord_t *record);

void haptic_init(void);
void eeconfig_debug_haptic(void);
void haptic_enable(void);
void haptic_disable(void);
void haptic_toggle(void);
void haptic_play(void);
void haptic_feedback_toggle(void);
void haptic_intensity_toggle(void);
void haptic_mode_toggle(void);

//under developement

uint8_t haptic_get_feedback(uint8_t mode);
uint8_t haptic_get_intensity(uint8_t intensity);
void haptic_set_intensity(uint8_t intensity);
uint8_t haptic_get_mode(uint8_t mode);
void haptic_set_intensity(uint8_t intensity);
void haptic_set_feedback(uint8_t feedback);
void haptic_set_mode(uint8_t mode);
void haptic_set(void);




