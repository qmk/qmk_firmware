/* Copyright 2021 Jay Greco
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

#include QMK_KEYBOARD_H
#include "14seg_animation.h"

bool numlock_set = false;

enum layers {
    _BASE = 0,
    _LED,
    _ALT,
    _NAV
};

#define DISP_ADDR 0x70
HT16K33 *disp;
animation_t *animation;
char message[16];

uint16_t tap_timer = 0;
bool nav_press_active = false;

enum custom_keycodes {
  PROG = SAFE_RANGE,
  NAV_ENT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Base layer (numpad)
  [_BASE] = LAYOUT(
                           KC_PSLS, KC_PAST, KC_PMNS, 
  KC_VOLD, KC_VOLU, KC_P7, KC_P8,   KC_P9,   KC_PPLS, 
  KC_TRNS, KC_TRNS, KC_P4, KC_P5,   KC_P6,   KC_PPLS, 
  KC_TRNS, KC_TRNS, KC_P1, KC_P2,   KC_P3,   NAV_ENT, 
  KC_TRNS, KC_TRNS, KC_P0, KC_P0,   KC_PDOT, NAV_ENT  
  ),

  // Navigation layer (nav + media)
  [_NAV] = LAYOUT(
                         KC_TRNS, KC_TRNS, KC_TRNS, 
    ___, ___, PROG,      KC_MPRV, KC_MPLY, KC_MNXT, 
    ___, ___, TO(_LED),  KC_VOLD, KC_MUTE, KC_VOLU, 
    ___, ___, TO(_ALT),  KC_TRNS, KC_TRNS, KC_TRNS, 
    ___, ___, TO(_BASE), KC_TRNS, DEBUG,   KC_TRNS  
  ),
  // LED settings layer
  [_LED] = LAYOUT(
                       KC_TRNS, KC_TRNS,  KC_TRNS, 
    ___, ___, RGB_TOG, RGB_VAI, RGB_SAI,  RGB_HUI, 
    ___, ___, KC_TRNS, RGB_VAD, RGB_SAD,  RGB_HUD, 
    ___, ___, KC_TRNS, KC_TRNS, RGB_MOD,  KC_TRNS, 
    ___, ___, KC_TRNS, KC_TRNS, RGB_RMOD, MO(_NAV)  
  ),
  // Alternate settings layer

  [_ALT] = LAYOUT(
                 ___, ___, ___, 
  ___, ___, ___, ___, ___, ___, 
  ___, ___, ___, ___, ___, ___, 
  ___, ___, ___, ___, ___, ___, 
  ___, ___, ___, ___, ___, MO(_NAV)   
  ),
};

void matrix_init_user(void) {
  matrix_init_remote_kb();
  set_bitc_LED(LED_OFF);

  disp = newHT16K33(4, DISP_ADDR);

  animation = newAnimation(disp);
  animation->message = message;
  animation->mode = DISP_MODE_BOUNCE;
  animation->enabled = true;

  char tmp[] = "TIDBIT";
  strcpy(message, tmp);
}

void matrix_scan_user(void) {
  matrix_scan_remote_kb();

  animation_refresh(animation);

  if (nav_press_active) {
    if (timer_elapsed(tap_timer) > 120) {
      //change layer
      layer_on(_NAV);
      nav_press_active = false;
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  process_record_remote_kb(keycode, record);

  // Get the current NLCK status & set if not set.
  // Only do this once, in case user has a NLCK key
  // and wants to disable it later on.
  if (!numlock_set && record->event.pressed) {
    led_t led_state = host_keyboard_led_state();
    if (!led_state.num_lock) {
      register_code(KC_NLCK);
    }
    numlock_set = true;
  }

  switch(keycode) {
    case PROG:
      if (record->event.pressed) {
        char tmp[] = "PROG";
        strcpy(message, tmp);
        force_animation_refresh(animation); //force refresh
        rgblight_disable_noeeprom();
        bootloader_jump(); //jump to bootloader
      }
    break;
    case NAV_ENT:
      if (record->event.pressed) {
        nav_press_active = true;
        tap_timer = timer_read();
      }
      else {
        if (nav_press_active) {
          nav_press_active = false;
          SEND_STRING(SS_TAP(X_PENT));
        }
        else {
          nav_press_active = false;
          layer_off(_NAV);
        }
      }
    break;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _BASE:
      {
      set_bitc_LED(LED_OFF);
      char tmp[] = "TIDBIT";
      strcpy(message, tmp);
      force_animation_refresh(animation); //force refresh
      break;
      }
    case _NAV:
      {
      set_bitc_LED(LED_ON);
      char tmp[] = "NAV MENU";
      strcpy(message, tmp);
      force_animation_refresh(animation); //force refresh
      break;
      }
    case _LED:
      {
      set_bitc_LED(LED_OFF);
      char tmp[] = "LED MENU";
      strcpy(message, tmp);
      force_animation_refresh(animation); //force refresh
      break;
      }
    case _ALT:
      {
      set_bitc_LED(LED_OFF);
      char tmp[] = "ALTERNATE";
      strcpy(message, tmp);
      force_animation_refresh(animation); //force refresh
      break;
      }
    default: //  for any other layers, or the default layer
      {
      set_bitc_LED(LED_OFF);
      char tmp[] = BLANK;
      strcpy(message, tmp);
      force_animation_refresh(animation); //force refresh
      break;
      }
    }
  return state;
}