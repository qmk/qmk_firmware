/* Copyright 2024 GSKY <gskyGit@gsky.com.tw>
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

#define HOLD_TIME 3000
#define BLINK_WHITE 0
#define BLINK_RED   1

static bool fn_pressed = false;
static bool lalt_pressed = false;

static bool led_on = false;
static uint16_t blink_timer = 0;
static uint8_t blink_count = 7;
static uint8_t reset_blink_count =7;
uint8_t blinking = 0;

static uint16_t reset_timer = 0;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.

#define RGB_HSV_MAX 7
static uint8_t rgb_hsvs[7][3] = {
    {0, 255, 255},
    {77,255, 255},
    {170,255,255},
    {10, 255,255},
    {209,255,255},
    {36, 255,255},
    {0,  0,  255},
};

enum layers {
    _Win,
    _Mac,
    _Winfn,
    _Macfn,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_Win] = LAYOUT_75_ansi(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,      KC_F4,        KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,      KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_PAUS, KC_DEL,
  KC_GRV,  KC_1,    KC_2,    KC_3,       KC_4,         KC_5,    KC_6,    KC_7,    KC_8,    KC_9,       KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
  KC_TAB,  KC_Q,    KC_W,    KC_E,       KC_R,         KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,       KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
  KC_CAPS, KC_A,    KC_S,    KC_D,       KC_F,         KC_G,    KC_H,    KC_J,    KC_K,    KC_L,       KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP,
  KC_LSFT, KC_Z,    KC_X,    KC_C,       KC_V,         KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,     KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
  KC_LCTL, KC_LGUI, KC_LALT,                           KC_SPC,                    KC_RALT, MO(_Winfn), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[_Winfn] = LAYOUT_75_ansi(
  KC_TRNS, KC_BRID, KC_BRIU, LGUI(KC_D), LGUI(KC_TAB), KC_MAIL, KC_CALC, KC_MPRV, KC_MPLY, KC_MNXT,    KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_INS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RM_NEXT,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RM_HUEU,
  KC_TRNS, TO(_Win),TO(_Mac),KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, RM_TOGG,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, RM_VALU, KC_TRNS,
  KC_TRNS, GU_TOGG, KC_TRNS,                           EE_CLR,                    KC_TRNS, KC_TRNS,    KC_TRNS, RM_SPDD, RM_VALD, RM_SPDU),

[_Mac] = LAYOUT_75_ansi(

  KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL,    KC_LPAD,      KC_NO,   KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT,    KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR, KC_PAUS, KC_DEL,
  KC_GRV,  KC_1,    KC_2,    KC_3,       KC_4,         KC_5,    KC_6,    KC_7,    KC_8,    KC_9,       KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
  KC_TAB,  KC_Q,    KC_W,    KC_E,       KC_R,         KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,       KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
  KC_CAPS, KC_A,    KC_S,    KC_D,       KC_F,         KC_G,    KC_H,    KC_J,    KC_K,    KC_L,       KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP,
  KC_LSFT, KC_Z,    KC_X,    KC_C,       KC_V,         KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,     KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
  KC_LCTL, KC_LALT, KC_LGUI,                           KC_SPC,                    KC_RGUI, MO(_Macfn), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

[_Macfn] = LAYOUT_75_ansi(
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,      KC_F4,        KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,      KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_INS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RM_NEXT,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RM_HUEU,
  KC_TRNS, TO(_Win),TO(_Mac),KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, RM_TOGG,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, RM_VALU, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS,                           EE_CLR,                    KC_TRNS, KC_TRNS,    KC_TRNS ,RM_SPDD, RM_VALD, RM_SPDU)
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag: 1;
        uint8_t rgb_enable: 1;
        uint8_t no_gui: 1;
        uint8_t rgb_status: 1;
        uint8_t rgb_hsv_index: 3;
        uint8_t rgb_brightness;
        uint8_t Num_To_F1: 1;
        uint8_t hui_index: 3;
    };
} confinfo_t;
confinfo_t confinfo;

typedef struct {
    uint8_t brightness_level: 5;
    uint8_t speed_level: 3;
    bool    close_rgb;
} settings_t;
settings_t settings;


void blink_all_led_matrix(uint8_t blink_color) {

    if(blink_color == BLINK_WHITE)
    {
       if (timer_elapsed(blink_timer) > 165)
       {
          blink_timer = timer_read();

          if (blink_count < 7) {
              led_on = !led_on;
              blink_count++;
          }
          else
          {
            blink_color = 0;
            blinking = 0;
          }
       }
    }
    else if(blink_color == BLINK_RED)
    {
       if (timer_elapsed(blink_timer) > 165)
       {
          blink_timer = timer_read();

          if (reset_blink_count < 7) {
              led_on = !led_on;
              reset_blink_count++;
          }
          else
          {
            blink_color = 0;
            blinking = 0;
          }

       }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode)
    {
    case EE_CLR:
       {
           if (record->event.pressed) {
                reset_timer = timer_read();
           }
           return false;
       }
       break;
       case RM_SPDD:
       {
           if (record->event.pressed)
           {
               if(settings.speed_level <=  1 )
               {
                   rgb_matrix_set_speed(15);

                   blinking = 1;
                   blink_count = 0;
                   return false;
               }
               if(settings.speed_level ==  2 )
               {
                   rgb_matrix_set_speed(15);

                   blinking = 1;
                   blink_count = 0;
                   settings.speed_level--;
                   return false;
               }
               else
               {
                    settings.speed_level--;
               }
           }
       }
       break;
       case RM_SPDU:
       {
           if (record->event.pressed)
           {
               if(settings.speed_level >=  5 )
               {
                   blinking = 1;
                   blink_count = 0;
                   return false;
               }
               else if(settings.speed_level ==  4 )
               {
                   blinking = 1;
                   blink_count = 0;
                   settings.speed_level++;
               }
               else
               {
                    settings.speed_level++;
               }
           }
       }
       break;
       case RM_VALU:
       {
           if (record->event.pressed)
           {
               if(settings.brightness_level >=  5 )
               {
                   blinking = 1;
                   blink_count = 0;
                   return false;
               }
               else if(settings.brightness_level ==  4 )
               {
                   blinking = 1;
                   blink_count = 0;
                   settings.brightness_level++;
               }
               else
               {
                   settings.brightness_level++;
               }
           }
       }
       break;
       case RM_VALD:
       {
           if (record->event.pressed)
           {
               if(settings.brightness_level == 1)
               {
                   blinking = 1;
                   blink_count = 0;
                   return false;
               }
               else if(settings.brightness_level == 2)
               {
                   blinking = 1;
                   blink_count = 0;
                   settings.brightness_level--;
               }
               else
               {
                   settings.brightness_level--;
               }
           }
       }
       break;
       case KC_LGUI: {
           if (record->event.pressed)
           {
               if(confinfo.no_gui)
               return false;
               else
               return true;
           }
       }break;
       case GU_TOGG: {
           if(record->event.pressed){
               confinfo.no_gui = !confinfo.no_gui;
           }
            return false;
       }break;
       case RM_TOGG: {
           if(record->event.pressed){
               settings.close_rgb = !settings.close_rgb;
           }
           return false;
       }break;
       case RM_HUEU:
           if (record->event.pressed) {
               confinfo.hui_index = (confinfo.hui_index + 1) % RGB_HSV_MAX;

               rgb_matrix_sethsv(rgb_hsvs[confinfo.hui_index][0],
                                   rgb_hsvs[confinfo.hui_index][1],
                                   rgb_matrix_get_val());
               eeconfig_update_user(confinfo.raw);
           }
           return false;
       break;
       case RGB_HUD:
           if (record->event.pressed) {
               uint8_t now_mode_one = rgb_matrix_get_mode();
               if((now_mode_one == 6) ||(now_mode_one == 13) ||(now_mode_one == 15) ||(now_mode_one == 16) ||(now_mode_one == 25) ||(now_mode_one == 26) ||(now_mode_one == 34)){
                   (confinfo.rgb_hsv_index == 0)? (confinfo.rgb_hsv_index = 5):(confinfo.rgb_hsv_index = confinfo.rgb_hsv_index - 1);
                   rgb_matrix_sethsv(rgb_hsvs[confinfo.rgb_hsv_index][0],
                                       rgb_hsvs[confinfo.rgb_hsv_index][1],
                                       rgb_matrix_get_val());
               }else{
                   (confinfo.rgb_hsv_index == 0)? (confinfo.rgb_hsv_index = 6):(confinfo.rgb_hsv_index = confinfo.rgb_hsv_index - 1);
                   rgb_matrix_sethsv(rgb_hsvs[confinfo.rgb_hsv_index][0],
                                       rgb_hsvs[confinfo.rgb_hsv_index][1],
                                       rgb_matrix_get_val());
               }
               eeconfig_update_user(confinfo.raw);
           }
           return false;
           break;
       case TO(_Win): {
           if(record->event.pressed) {
               blinking = 1;
               blink_count = 0;
               set_single_persistent_default_layer(_Win);
           }
           return false;
       } break;
       case TO(_Mac): {
           if (record->event.pressed) {
               blinking = 1;
               blink_count = 0;
               confinfo.no_gui = false;
               set_single_persistent_default_layer(_Mac);
           }
           return false;
       } break;
       default:
       break;
    }
    return true;
}

void matrix_scan_user(void) {

    if(matrix_is_on(5,9))
      fn_pressed = true;
    else
      fn_pressed = false;

    if(matrix_is_on(5,3))
      lalt_pressed = true;
    else
      lalt_pressed = false;

    if(matrix_is_on(2,0)) {
        if ((fn_pressed)&&(lalt_pressed)){
             reset_keyboard();
        }
    }

    if(blinking ==1 )
       blink_all_led_matrix(BLINK_WHITE);
    else if(blinking ==2 )
       blink_all_led_matrix(BLINK_RED);


    if(reset_timer != 0 )
    {
        if(timer_elapsed(reset_timer) >= 5000)
        {
           reset_timer = 0;
           reset_blink_count = 0;
           confinfo.no_gui = false;
           blinking = 2;

           layer_state_t default_layer_temp = default_layer_state;
           eeconfig_init();
           default_layer_set(default_layer_temp);

           // This resets the layout options
           // via_set_layout_options(VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT);
           // This resets the keymaps in EEPROM to what is in flash.
           // dynamic_keymap_reset();
           // This resets the macros in EEPROM to nothing.
           // dynamic_keymap_macro_reset();

           rgb_matrix_enable();
           rgb_matrix_mode(13);
           // set to cycle_left_right by default
           rgb_matrix_sethsv(HSV_RED);
           rgb_matrix_set_speed(195);

           rgb_matrix_set_flags(LED_FLAG_ALL);

           settings.brightness_level = 5;
           settings.speed_level = 3;
           confinfo.no_gui = 0;
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if(settings.close_rgb){
        rgb_matrix_set_color_all(0,0,0);
    }

    if (host_keyboard_led_state().caps_lock) {
         rgb_matrix_set_color(37, 0, 0, 0xff);
    }

    // GUI lock
    if (confinfo.no_gui) {
         rgb_matrix_set_color(2, 255, 255, 255);
    }

    if(blink_count <6)
    {
        if (led_on) {
            rgb_matrix_set_color_all(0,0,0);
        } else {
            rgb_matrix_set_color_all(100,100,100);
        }
    }
    else if(reset_blink_count <6)
    {
        if (led_on) {
            rgb_matrix_set_color_all(0,0,0);
        } else {
            rgb_matrix_set_color_all(255,0,0);
        }
    }

    return true;
}
