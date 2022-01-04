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

#define ____ _______
#define _BASE     0
#define _LED      1
#define _ALT      2
#define _NAV      3

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
             KC_F1, KC_F2, KC_F3, 
    KC_PSLS, KC_7,  KC_8,  KC_9, 
    KC_PAST, KC_4,  KC_5,  KC_6, 
    KC_PMNS, KC_1,  KC_2,  KC_3, 
    KC_PPLS, KC_0,  KC_DOT, NAV_ENT  
  ),
  // Navigation layer (nav + media)
  [_NAV] = LAYOUT(
               _______, _______, _______, 
    PROG,      KC_MPRV, KC_MPLY, KC_MNXT, 
    TO(_LED),  KC_VOLD, KC_MUTE, KC_VOLU, 
    TO(_ALT),  RM_1,       RM_2,    RM_3, 
    TO(_BASE), _______,   DEBUG, _______  
  ),
  // LED settings layer
  [_LED] = LAYOUT(
             _______, _______, _______, 
    RGB_TOG, RGB_VAI, RGB_SAI, RGB_HUI, 
    _______, RGB_VAD, RGB_SAD, RGB_HUD, 
    _______, _______, RGB_MOD, _______, 
    _______, _______, RGB_RMOD, MO(_NAV)  
  ),
  // Altium settings layer
  [_ALT] = LAYOUT(
          ____, ____, ____, 
    ____, ____, ____, ____, 
    ____, ____, ____, ____, 
    ____, ____, ____, ____, 
    ____, ____, ____, MO(_NAV)  
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