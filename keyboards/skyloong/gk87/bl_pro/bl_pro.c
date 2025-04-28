//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "led_hc595.h"

uint8_t IND = 0;  //buffer of LED Display

int FN_ON = 0;
bool WIN_LOCK = 0;
bool DIS_BRETH = 0;
bool SLEEP = 0;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
       case MO(1):
          if (record->event.pressed) {
            FN_ON = 1;
          } else {
            FN_ON = 0;
          }
          return true;

       case MO(2):
           if (record->event.pressed) {
             FN_ON = 1;
           } else {
             FN_ON = 0;
           }
          return true;

       case MO(3):
           if (record->event.pressed) {
             FN_ON = 1;
           } else {
             FN_ON = 0;
           }
          return true;

       case KC_LGUI:
           if (FN_ON){
              if ( record->event.pressed){
                 WIN_LOCK = !WIN_LOCK ; //change win lock state
                }
              if (!WIN_LOCK) {
                 IND = IND & (~WINLK_ON);   //Close win lock display
                 s_serial_to_parallel(IND);
                 gpio_write_pin_high(WIN_LOCK_PIN);
                 return false; //windows key locked do nothing
                }
              s_serial_to_parallel(IND);
            }
           if (WIN_LOCK) {
               IND = IND | WINLK_ON;   //Open win lock display
               s_serial_to_parallel(IND);
               gpio_write_pin_low(WIN_LOCK_PIN);
               return false; //windows key locked do nothing
            }
           return true;  // continue all further processing of this key

       case BL_TOGG:
           if (record->event.pressed){
               if(is_backlight_breathing()) {
                    backlight_disable_breathing();
                    DIS_BRETH = 1;

                }else if(DIS_BRETH && !(is_backlight_enabled())){
                    backlight_enable_breathing();
                    DIS_BRETH = 0;
                }
           }
         return true;

       case BL_BRTG:
           if (record->event.pressed){
               if(DIS_BRETH || !(is_backlight_enabled())) {
                 return false;
                }
           }
         return true;

       case BL_UP:
           DIS_BRETH = 0;
         return true;

       case BL_DOWN:
           if (record->event.pressed){
               if(DIS_BRETH || !(is_backlight_enabled())) {
                 return false;
                }
           }
         return true;

    default:
      return true;
    }
   s_serial_to_parallel(IND);
}

void suspend_power_down_kb() {
    SLEEP = 1;
    suspend_power_down_user();
}

void suspend_wakeup_init_kb() {
    SLEEP = 0;
    gpio_write_pin(LED_CAPS_LOCK_PIN, !host_keyboard_led_state().caps_lock);
    gpio_write_pin(LED_SCROLL_LOCK_PIN, !host_keyboard_led_state().scroll_lock);
    gpio_write_pin(WIN_LOCK_PIN, !keycode_config.no_gui);
    s_serial_to_parallel(IND);
    suspend_wakeup_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    SLEEP = 1;
    return true;
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 0:
        //switch to win layer display
        IND = IND & (~MAC_ON);
        IND = IND | WIN_ON;
        break;
    case 1:
        //switch to mac layer display
        IND = IND & (~WIN_ON);
        IND = IND | MAC_ON;
        break;
    }
    s_serial_to_parallel(IND);
  return default_layer_state_set_user(state);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(SLEEP){
        gpio_write_pin_high(LED_CAPS_LOCK_PIN);
        gpio_write_pin_high(LED_SCROLL_LOCK_PIN);
        gpio_write_pin_high(WIN_LOCK_PIN);
        s_serial_to_parallel(0);
        return false;
        }
    if(res) {
       //caps lock display
      if (led_state.caps_lock) {
        IND = IND | CAPS_ON;
        gpio_write_pin_low(LED_CAPS_LOCK_PIN);
      } else {
        IND = IND & (~CAPS_ON);
        gpio_write_pin_high(LED_CAPS_LOCK_PIN);
      }
       //number lock display
      if (led_state.num_lock) {
        IND = IND | NUM_ON;
      } else {
        IND = IND & (~NUM_ON);
      }
       //scroll lock display
      if (led_state.scroll_lock) {
        IND = IND | SCR_ON;
        gpio_write_pin_low(LED_SCROLL_LOCK_PIN);
      } else {
        IND = IND & (~SCR_ON);
        gpio_write_pin_high(LED_SCROLL_LOCK_PIN);
      }
    }
    s_serial_to_parallel(IND);
    return res;
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    gpio_set_pin_output(WIN_LOCK_PIN);
    gpio_write_pin_high(WIN_LOCK_PIN);
    s_serial_to_parallel(0xFF);
    IND = SKYLOONG;
    SLEEP = 0;
}

