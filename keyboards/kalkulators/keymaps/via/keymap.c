// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "halconf.h"
#include "tm1638.h"
#include "wait.h"
#include "usb_util.h"
#include "calc.h"

int brightness_level = 7;

bool show_usb_connection = true;
bool show_calc_connection = true;
bool pc_connection;
int layer;

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  
  setPinOutput(TM1638_CLK_PIN);
  setPinOutput(TM1638_STB_PIN);
  setPinOutput(TM1638_DIO_PIN);
  
  displayBegin();
  wait_ms(0.1);
  brightness(brightness_level);

  if (usb_connected_state() == 1) {

    set_single_persistent_default_layer(0);
    
    if (show_usb_connection == true){
        layer = 0;
        pc_connection = true;
        show_usb_connection = false;
        reset();
        display7Seg(3, 0b01110011);
        display7Seg(4, 0b00111001);
        wait_ms(500);
        reset();
    }
    show_calc_connection = true;


  } else if (usb_connected_state() == 0){
    set_single_persistent_default_layer(1);


    if (show_calc_connection == true){
        layer = 1;
        pc_connection = false;
        show_calc_connection = false;
        reset();
        display7Seg(2, 0b00111001);
        display7Seg(3, 0b01110111);
        display7Seg(4, 0b00111000);
        display7Seg(5, 0b00111001);
        wait_ms(500);
        reset();
        display7Seg(7, 0b00111111);

    }
    show_usb_connection = true;
  }

};

enum custom_keycodes {
  KC_cl = QK_USER,   
  KC_div, 
  KC_times, 
  KC_minus,
  KC_seven,   
  KC_eight,   
  KC_nine,
  KC_four,   
  KC_five,   
  KC_six,   
  KC_plus,
  KC_one,   
  KC_two,   
  KC_three,
  KC_zero,   
  KC_dot,          
  KC_equals
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │TG1│ / │ * │ - │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┤ + │
     * │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │   │
     * ├───┴───┼───┤Ent│
     * │   0   │ . │   │
     * └───────┴───┴───┘
     */
    [0] = LAYOUT_numpad(
        KC_DELETE,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,   KC_PDOT,          KC_PENT
    ),

    [1] = LAYOUT_calc(
        QK_USER,   KC_div, KC_times, KC_minus,
        KC_seven,   KC_eight,   KC_nine,
        KC_four,   KC_five,   KC_six,   KC_plus,
        KC_one,   KC_two,   KC_three,
        KC_zero,   KC_dot,          KC_equals
    )
};



void housekeeping_task_user(void) {
  if (usb_connected_state() == 1) {
    
    if (show_usb_connection == true){
        set_single_persistent_default_layer(0);
        layer = 0;
        pc_connection = true;
        show_usb_connection = false;
        reset();
        display7Seg(3, 0b01110011);
        display7Seg(4, 0b00111001);
        wait_ms(500);
        reset();
    }
    show_calc_connection = true;


  } else if (usb_connected_state() == 0){
    set_single_persistent_default_layer(1);


    if (show_calc_connection == true){
        pc_connection = false;
        show_calc_connection = false;
        reset();
        reset_states();
        display7Seg(2, 0b00111001);
        display7Seg(3, 0b01110111);
        display7Seg(4, 0b00111000);
        display7Seg(5, 0b00111001);
        wait_ms(500);
        reset();
        display7Seg(7, 0b00111111);

    }
    show_usb_connection = true;
  }
}


enum combo_events {
  CHANGE_BRIGHTNESS_UP,
  CHANGE_BRIGHTNESS_DOWN,
  CHANGE_LAYER,
  CHANGE_LAYER_ON_PC
};
const uint16_t PROGMEM brightness_combo_up[] = {KC_cl, KC_times, COMBO_END};
const uint16_t PROGMEM brightness_combo_down[] = {KC_cl, KC_div, COMBO_END};
const uint16_t PROGMEM change_layer[] = {KC_minus, KC_plus, COMBO_END};
const uint16_t PROGMEM change_layer_on_pc[] = {KC_PMNS, KC_PPLS, COMBO_END};

combo_t key_combos[] = {
  [CHANGE_BRIGHTNESS_UP] = COMBO_ACTION(brightness_combo_up),
  [CHANGE_BRIGHTNESS_DOWN] = COMBO_ACTION(brightness_combo_down),
  [CHANGE_LAYER] = COMBO_ACTION(change_layer),
  [CHANGE_LAYER_ON_PC] = COMBO_ACTION(change_layer_on_pc)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CHANGE_BRIGHTNESS_UP:
      if (pressed) {
        if (brightness_level < 7){
          brightness_level += 1;
          brightness(brightness_level);
        }
      }
      break;
    case CHANGE_BRIGHTNESS_DOWN:
      if (pressed) {
        if (brightness_level > 0){
        brightness_level -= 1;
        brightness(brightness_level);
        }
      }
      break;
  
    case CHANGE_LAYER:
      if (pressed) {
        print("changing_layer");
        if (pc_connection == true){
          if (layer == 1){
            set_single_persistent_default_layer(0);
            layer = 0;
            reset();
            display7Seg(3, 0b01110011);
            display7Seg(4, 0b00111001);
            wait_ms(500);
            reset();
          }
          else if (layer == 0){
            set_single_persistent_default_layer(1);
            layer = 1;
            reset();
            reset_states();
            display7Seg(2, 0b00111001);
            display7Seg(3, 0b01110111);
            display7Seg(4, 0b00111000);
            display7Seg(5, 0b00111001);
            wait_ms(500);
            reset();
            display7Seg(7, 0b00111111);
          }
        }
      }
      break;
    case CHANGE_LAYER_ON_PC:
      if (pressed) {
        print("changing_layer");
        if (pc_connection == true){
          if (layer == 1){
            set_single_persistent_default_layer(0);
            layer = 0;
            reset();
            display7Seg(3, 0b01110011);
            display7Seg(4, 0b00111001);
            wait_ms(500);
            reset();
          }
          else if (layer == 0){
            set_single_persistent_default_layer(1);
            layer = 1;
            reset();
            reset_states();
            display7Seg(2, 0b00111001);
            display7Seg(3, 0b01110111);
            display7Seg(4, 0b00111000);
            display7Seg(5, 0b00111001);
            wait_ms(500);
            reset();
            display7Seg(7, 0b00111111);
          }
        }
      }
      break;
  }
}















