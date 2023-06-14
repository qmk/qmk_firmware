// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <stdio.h>


//bool encoder_update_user(uint8_t index, bool clockwise) {
//    if (index == 0) { /* First encoder */
//        if (clockwise) {
//            tap_code(KC_PGDN);
//        } else {
//            tap_code(KC_PGUP);
//        }
//    }
//    return false;
//};

enum custom_keycodes {
  CUS_HUE = SAFE_RANGE,
  CUS_SAT,
  CUS_SPD,
  CUS_VAL,
};

uint8_t encoder_mode = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(1) && record->event.pressed) {
        switch (keycode) {
        case CUS_HUE:
            encoder_mode = 1;
            break;
        case CUS_SAT:
            encoder_mode = 2;
            break;
        case CUS_SPD:
            encoder_mode = 3;
            break;
        case CUS_VAL:
            encoder_mode = 4;
            break;
        default:
            encoder_mode = 0;
        }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (!(state & (1UL << 1))) {
        encoder_mode = 0;
    }
    return state;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // First encoder 
    if (IS_LAYER_ON(1)) {
      switch (encoder_mode) { 
      case 1:
        if (clockwise) {
          rgb_matrix_increase_hue();
        } else {
          rgb_matrix_decrease_hue();
        }
        break;
      case 2: 
        if (clockwise) {
          rgb_matrix_increase_sat();
        } else {
          rgb_matrix_decrease_sat();
        }
        break;
      case 3: 
        if (clockwise) {
          rgb_matrix_increase_speed();
        } else {
          rgb_matrix_decrease_speed();
        }
        break;
      case 4: 
        if (clockwise) {
          rgb_matrix_increase_val();
        } else {
          rgb_matrix_decrease_val();
        }
        break;        
    }
  }
    else {
      if (clockwise) {
        tap_code(KC_DOWN);
      } else {
        tap_code(KC_UP);
      }
    }
  }
      return false;
};


/*
#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("Hello world"), false);
    return false;
}
#endif
*/

#ifdef OLED_ENABLE
bool oled_task_user(void) {
uint8_t    HUE_value = rgb_matrix_get_hue();
uint8_t    SAT_value = rgb_matrix_get_sat();
uint8_t    SPD_value = rgb_matrix_get_speed();
uint8_t    VAL_value = rgb_matrix_get_val();


char buf_hue[4];
char buf_sat[4];
char buf_spd[4];
char buf_val[4];


/*
char buf_hue = (char) HUE_value;
char buf_sat = (char) SAT_value;
char buf_spd = (char) SPD_value;
char buf_val = (char) VAL_value;
*/

/*  
sprintf(buf_hue, "Hue: %u ", HUE_value);
sprintf(buf_sat, "    SAT: %u \n", SAT_value);
sprintf(buf_spd, "SPD: %u", SPD_value);
sprintf(buf_val, "     VAL: %u", VAL_value);

oled_write(buf_hue, false);
oled_write(buf_sat, false);
oled_write(buf_spd, false);
oled_write(buf_val, false);
*/

/*
sprintf(buf_hue, "Hue: %u", HUE_value);
sprintf(buf_sat, "SAT: %u", SAT_value);
sprintf(buf_spd, "SPD: %u", SPD_value);
sprintf(buf_val, "VAL: %u", VAL_value);
*/





sprintf(buf_hue, "%3u", HUE_value);
sprintf(buf_sat, "%3u", SAT_value);
sprintf(buf_spd, "%3u", SPD_value);
sprintf(buf_val, "%3u", VAL_value);





//oled_clear();

/*
oled_write(buf_hue, false);
oled_set_cursor(13,0);
oled_write(buf_sat, false);
//oled_write_P(PSTR("\n"), false);
oled_set_cursor(0,1);
oled_write(buf_spd, false);
oled_set_cursor(13,1);
oled_write(buf_val, false);
*/

//void oled_clear(void);

oled_set_cursor(0,0);


oled_write_P(PSTR("HUE:"), false);

//oled_set_cursor(7-strlen(buf_hue),0);
oled_set_cursor(4,0);
oled_write(buf_hue, false);

oled_set_cursor(13,0);
oled_write_P(PSTR("SAT:"), false);

oled_set_cursor(18,0);
oled_write(buf_sat, false);

oled_set_cursor(0,1);
oled_write_P(PSTR("SPD:"), false);

oled_set_cursor(4,1);
oled_write(buf_spd, false);

oled_set_cursor(13,1);
oled_write_P(PSTR("VAL:"), false);

oled_set_cursor(18,1);
oled_write(buf_val, false);



  //  oled_write_P(PSTR("HUE: "), false);
  //  oled_write(HUE_value(), false);
  //  oled_write_P(PSTR("SAT: \n"), false);
  //  oled_write_P(PSTR("SPD: "), false);
    return false;
}
#endif


