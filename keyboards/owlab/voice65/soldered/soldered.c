/* Copyright 2021 kb-elmo<mail@elmo.space>
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

#include "soldered.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, CS3_SW1,  CS2_SW1,  CS1_SW1},  /* RGB0-ESC ROW0*/
    {0, CS6_SW1,  CS5_SW1,  CS4_SW1},  /* RGB1-1 */
    {0, CS9_SW1,  CS8_SW1,  CS7_SW1},  /* RGB2-2 */
    {0, CS12_SW1,  CS11_SW1,  CS10_SW1},  /* RGB3-3 */
    {0, CS15_SW1,  CS14_SW1,  CS13_SW1},  /* RGB4-4 */
    {0, CS18_SW1,  CS17_SW1,  CS16_SW1},  /* RGB5-5 */
    {0, CS21_SW1,  CS20_SW1,  CS19_SW1},  /* RGB6-6 */
    {0, CS24_SW1,  CS23_SW1,  CS22_SW1},  /* RGB7-7 */
    {0, CS27_SW1,  CS26_SW1,  CS25_SW1},  /* RGB8-8 */
    {0, CS30_SW1,  CS29_SW1,  CS28_SW1},  /* RGB9-9 */
    {0, CS33_SW1,  CS32_SW1,  CS31_SW1},  /* RGB10-0 */
    {0, CS36_SW1,  CS35_SW1,  CS34_SW1},  /* RGB11--- */
    {0, CS39_SW6,  CS38_SW6,  CS37_SW6},  /* RGB12-+= */
    {0, CS36_SW6,  CS35_SW6,  CS34_SW6},  /* RGB13-BS */
    {0, CS27_SW6,  CS26_SW6,  CS25_SW6},  /* RGB14-BACKSPACE SPLIT */
    {0, CS36_SW8,  CS35_SW8,  CS34_SW8},  /* RGB15-DEL */
    {0, CS3_SW2,  CS2_SW2,  CS1_SW2},  /* RGB16-TAB ----ROW1*/
    {0, CS6_SW2,  CS5_SW2,  CS4_SW2}, /* RGB17-Q */
    {0, CS9_SW2,  CS8_SW2,  CS7_SW2}, /* RGB18-W */
    {0, CS12_SW2,  CS11_SW2,  CS10_SW2}, /* RGB19-E */
    {0, CS15_SW2,  CS14_SW2,  CS13_SW2}, /* RGB20-R */
    {0, CS18_SW2,  CS17_SW2,  CS16_SW2}, /* RGB21-T */
    {0, CS21_SW2,  CS20_SW2,  CS19_SW2}, /* RGB22-Y */
    {0, CS24_SW2,  CS23_SW2,  CS22_SW2}, /* RGB23-U */
    {0, CS27_SW2,  CS26_SW2,  CS25_SW2}, /* RGB24-I */
    {0, CS30_SW2,  CS29_SW2,  CS28_SW2}, /* RGB25-O */
    {0, CS33_SW2,  CS32_SW2,  CS31_SW2}, /* RGB26-P */
    {0, CS36_SW2,  CS35_SW2,  CS34_SW2}, /* RGB27-[ */
    {0, CS39_SW7,  CS38_SW7,  CS37_SW7}, /* RGB28-] */
    {0, CS36_SW7,  CS35_SW7,  CS34_SW7}, /* RGB29-\ */
    {0, CS27_SW7,  CS26_SW7,  CS25_SW7},  /* RGB30-PGUP */
    {0, CS3_SW3,  CS2_SW3,  CS1_SW3},  /* RGB31-CAPS---ROW2*/
    {0, CS6_SW3,  CS5_SW3,  CS4_SW3},  /* RGB32-A-- */
    {0, CS9_SW3,  CS8_SW3,  CS7_SW3},  /* RGB33-S-- */
    {0, CS12_SW3,  CS11_SW3,  CS10_SW3},  /* RGB34-D-- */
    {0, CS15_SW3,  CS14_SW3,  CS13_SW3},  /* RGB35-F-- */
    {0, CS18_SW3,  CS17_SW3,  CS16_SW3},  /* RGB36-G-- */
    {0, CS21_SW3,  CS20_SW3,  CS19_SW3},  /* RGB37-H-- */
    {0, CS24_SW3,  CS23_SW3,  CS22_SW3},  /* RGB38-J-- */
    {0, CS27_SW3,  CS26_SW3,  CS25_SW3},  /* RGB39-K-- */
    {0, CS30_SW3,  CS29_SW3,  CS28_SW3},  /* RGB40-L-- */
    {0, CS33_SW3,  CS32_SW3,  CS31_SW3},  /* RGB41-;:- */
    {0, CS36_SW3,  CS35_SW3,  CS34_SW3},  /* RGB42-''- */
    {0, CS39_SW8,  CS38_SW8,  CS37_SW8},  /* RGB43-ENTER- */
    {0, CS27_SW8,  CS26_SW8,  CS25_SW8},  /* RGB44-PGDN */
    {0, CS3_SW4,  CS2_SW4,  CS1_SW4},  /* RGB45-LSF --ROW3*/
    {0, CS6_SW4,  CS5_SW4,  CS4_SW4},  /* RGB46-LSF split -*/
    {0, CS9_SW4,  CS8_SW4,  CS7_SW4},  /* RGB47-Z -*/
    {0, CS12_SW4,  CS11_SW4,  CS10_SW4},  /* RGB48-X -*/
    {0, CS15_SW4,  CS14_SW4,  CS13_SW4},  /* RGB49-C -*/
    {0, CS18_SW4,  CS17_SW4,  CS16_SW4},  /* RGB50-V -*/
    {0, CS21_SW4,  CS20_SW4,  CS19_SW4},  /* RGB51-B -*/
    {0, CS24_SW4,  CS23_SW4,  CS22_SW4},  /* RGB52-N -*/
    {0, CS27_SW4,  CS26_SW4,  CS25_SW4},  /* RGB53-M -*/
    {0, CS30_SW4,  CS29_SW4,  CS28_SW4},  /* RGB54-<, -*/
    {0, CS33_SW4,  CS32_SW4,  CS31_SW4},  /* RGB55->. -*/
    {0, CS36_SW4,  CS35_SW4,  CS34_SW4},  /* RGB56-?/ -*/
    {0, CS39_SW9,  CS38_SW9,  CS37_SW9},  /* RGB57-RSF -*/
    {0, CS36_SW9,  CS35_SW9,  CS34_SW9},  /* RGB58-UP -*/
    {0, CS27_SW9,  CS26_SW9,  CS25_SW9}, /* RGB59--MO-- */
    {0, CS3_SW5, CS2_SW5, CS1_SW5}, /* RGB60-lct-- row4*/
    {0, CS6_SW5, CS5_SW5, CS4_SW5}, /* RGB61-lwin- */
    {0, CS9_SW5, CS8_SW5, CS7_SW5}, /* RGB62-lalt- */
    {0, CS12_SW5, CS11_SW5, CS10_SW5}, /* RGB63-sp2.25- */
    {0, CS15_SW5, CS14_SW5, CS13_SW5}, /* RGB64-sp7U6.25U1.25U- */
    {0, CS21_SW5, CS20_SW5, CS19_SW5}, /* RGB65-sp2.75U- */
    {0, CS30_SW5, CS29_SW5, CS28_SW5}, /* RGB66-ralt- */
    {0, CS33_SW5, CS32_SW5, CS31_SW5}, /* RGB67-rctrl- */
    {0, CS36_SW5, CS35_SW5, CS34_SW5}, /* RGB68-left- */
    {0, CS39_SW5, CS38_SW5, CS37_SW5}, /* RGB69-dn- */
    {0, CS27_SW5, CS26_SW5, CS25_SW5}, /* RGB70-right- */
};

led_config_t g_led_config = { {
    {  0,  1,  2,  3,  4,  5,      6,  7,      8,      9,  10, 11, 12, 13,     14 },
    {  16, 17, 18, 19, 20, 21,     22, 23,     24,     25, 26, 27, 28, 29,     30 },
    {  31, 32, 33, 34, 35, 36,     37, 38,     39,     40, 41, 42, 43, 15,     44 },
    {  45, 46, 47, 48, 49, 50,     51, 52,     53,     54, 55, 56, 57, 58,     59 },
    {  60, 61, 62, 63, 64, NO_LED, 65, NO_LED, NO_LED, 66, 67, 68, 69, NO_LED, 70 }
}, {
    { 0, 0 },  { 15, 0 },  { 30, 0 },  { 45, 0 },  { 60, 0  }, { 75,  0 },  { 90,  0 },   { 105, 0 },  { 120, 0 },  { 135, 0 },  { 150, 0 },  { 165, 0},   { 180, 0},   { 195, 0 },  { 209, 0 },  { 224, 0 },
    { 2, 16 }, { 18, 16 }, { 34, 16 }, { 50, 16 }, { 66, 16 }, { 82,  16 }, { 98,  16 },  { 114, 16 }, { 130, 16 }, { 146, 16 }, { 162, 16 }, { 178, 16 }, { 194, 16 }, { 208, 16 }, { 224, 16 },
    { 2, 32 }, { 20, 32 }, { 36, 32 }, { 52, 32 }, { 68, 32 }, { 84,  32 }, { 100, 32 },  { 116, 32 }, { 132, 32 }, { 148, 32 }, { 164, 32 }, { 180, 32 }, { 202, 32 }, { 224, 32 },
    { 0, 48 }, { 16, 48 }, { 32, 48 }, { 48, 48 }, { 64, 48 }, { 80,  48 }, { 96,  48 },  { 112, 48 }, { 128, 48 }, { 144, 48 }, { 160, 48 }, { 176, 48 }, { 192, 48 }, { 208, 48 }, { 224, 48 },
    { 0, 64 }, { 20, 64 }, { 40, 64 }, { 60, 64 }, { 95, 64 }, { 132, 64 }, { 152, 64 },  { 172, 64 }, { 192, 64 }, { 208, 64 }, { 224, 64 }
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    1, 1, 1, 1, 1,    1,       1, 1, 1, 1, 1
    }
};


#endif

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(31, 255, 255, 255);
    } else {
        rgb_matrix_set_color(31, 0, 0, 0);
    }
    return true;
}

enum encoder_modes{
    ENCODER_MODE_ONE,
    ENCODER_MODE_TWO,
    ENCODER_MODE_THREE
};

keyboard_config_t keyboard_config;
rgblight_config_t rgblight_config;

uint8_t pre_hue, pre_sat, pre_val;
uint8_t previous_rgb_mode = 0;
uint8_t dir_hue, dir_sat;

bool encoder_in = false;
uint32_t encoder_timer;

bool encoder_ani_start= false;
uint32_t encoder_ani_timer = 0;

bool encoder_direction_start = false;
uint32_t encoder_direction_timer = 0;


bool lizm_restart_snake = false;
void rgblight_snake_restart(uint8_t hue, uint8_t sat, uint8_t val){
    lizm_restart_snake = true;  // restart signal to local each effect
    rgblight_config.hue = hue;
    rgblight_config.sat = sat;
    rgblight_config.val = val;
}


void keyboard_post_init_kb(void){
    keyboard_config.raw = eeconfig_read_kb();
    if( keyboard_config.encoder_mode_index > ENCODER_MODE_THREE ){
        keyboard_config.encoder_mode_index = ENCODER_MODE_ONE;
        eeconfig_update_kb(keyboard_config.raw);
    }
}

void switch_encoder_mode(uint8_t mode){
       switch(mode){
            case ENCODER_MODE_ONE:
            dir_hue = 88;
            dir_sat = 255;
            break;

            case ENCODER_MODE_TWO:
            dir_hue = 0;
            dir_sat = 240;
            break;

            case ENCODER_MODE_THREE:
            dir_hue = 176;
            dir_sat = 255;
            break;
        }
        rgblight_sethsv_noeeprom(dir_hue,dir_sat,pre_val);
}


void init_encoder_mode(uint8_t mode){
    previous_rgb_mode = rgblight_get_mode();
    pre_hue = rgblight_get_hue();
    pre_sat = rgblight_get_sat();
    pre_val = rgblight_get_val();
    encoder_in = true;

    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);

    switch_encoder_mode(mode);
}


void set_encoder_mode(uint8_t mode){
    if(encoder_in == false){
       init_encoder_mode(mode);
    }else{
        switch_encoder_mode(mode);
    }
    eeconfig_update_kb(keyboard_config.raw);
    encoder_timer = timer_read32();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
        case RGB_MOD:
        case RGB_RMOD:
        case RGB_HUI:
        case RGB_HUD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_VAI:
        case RGB_VAD:

        if(encoder_in){
                return false;
            }
        break;

        case KC_F13:
        rgb_matrix_toggle();
        break;

        case KC_F14:
        rgb_matrix_step();
        break;

        case KC_F15:
        rgb_matrix_step_reverse();
        break;

        case KC_F16:
        rgb_matrix_increase_hue();  //Increase the hue for effect range LEDs
        break;

        case KC_F17:
        rgb_matrix_decrease_hue(); //Decrease the hue for effect range LEDs
        break;

        case KC_F18:
        rgb_matrix_increase_sat(); //Increase the saturation for effect range LEDs
        break;

        case KC_F19:
        rgb_matrix_decrease_sat(); //Decrease the saturation for effect range LEDs
        break;

        case KC_F20:
        rgb_matrix_increase_val(); //Increase the value for effect range LEDs
        break;

        case KC_F21:
        rgb_matrix_decrease_val();//Decrease the value for effect range LEDs
        break;

        case KC_F22:  //change encoder mode upward
        if(!encoder_direction_start){
            if(keyboard_config.encoder_mode_index < ENCODER_MODE_THREE){
                keyboard_config.encoder_mode_index++;
            }
            else{
                keyboard_config.encoder_mode_index = ENCODER_MODE_ONE;
            }
            set_encoder_mode(keyboard_config.encoder_mode_index);
        }
        return false;

        case KC_F23:
        if(!encoder_direction_start){
            if(keyboard_config.encoder_mode_index > ENCODER_MODE_ONE){
                keyboard_config.encoder_mode_index--;
            }
            else{
                keyboard_config.encoder_mode_index = ENCODER_MODE_THREE;
            }
            set_encoder_mode(keyboard_config.encoder_mode_index);
        }
        return false;

        default:
        break;
    }
  }
  return process_record_user(keycode, record);
}


void matrix_scan_kb(void) {
    if(encoder_in){
        if(timer_elapsed32(encoder_timer) > 5000){
            rgblight_mode(previous_rgb_mode);
            rgblight_sethsv(pre_hue, pre_sat, pre_val);
            encoder_in = false;
        }
    }

    if(encoder_ani_start){
        if(timer_elapsed32(encoder_ani_timer) > VOLUME_ANIMATION_TIMER){
            encoder_ani_start = false;
            rgblight_sethsv_noeeprom(0,0,0);
        }
    }

    if(encoder_direction_start){
        if(timer_elapsed32(encoder_direction_timer) > (VOLUME_ANIMATION_TIMER+1500)){
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_noeeprom(dir_hue, dir_sat, pre_val);
            encoder_direction_start = false;
        }
    }
    matrix_scan_user();
}


void set_volume_animation(bool increase){
    if(!encoder_ani_start){
        rgblight_snake_restart(dir_hue, dir_sat, pre_val);
    }

    if(increase){
        rgblight_mode_noeeprom(17);
    } else {
        rgblight_mode_noeeprom(18);
    }

    encoder_ani_timer = timer_read32();
    encoder_direction_timer = encoder_ani_timer;
    encoder_ani_start = true;
    encoder_direction_start = true;
}


bool encoder_update_kb(uint8_t index, bool clockwise) {
    uint8_t layer_now = keyboard_config.encoder_mode_index +1;
    uint16_t encoder_cw_keycode = keymap_key_to_keycode(layer_now, (keypos_t){.row=2, .col=1 });
    uint16_t encoder_ccw_keycode = keymap_key_to_keycode(layer_now, (keypos_t){.row=2, .col=2 });
    if (index == 0) { /* First encoder */
        if(encoder_in == false){
            init_encoder_mode(keyboard_config.encoder_mode_index);
        }

        if (!clockwise) {
             switch(encoder_cw_keycode) {

                case KC_F13:
                rgb_matrix_toggle();
                break;

                case KC_F14:
                rgb_matrix_step();
                break;

                case KC_F15:
                rgb_matrix_step_reverse();
                break;

                case KC_F16:
                rgb_matrix_increase_hue();  //Increase the hue for effect range LEDs
                break;

                case KC_F17:
                rgb_matrix_decrease_hue(); //Decrease the hue for effect range LEDs
                break;

                case KC_F18:
                rgb_matrix_increase_sat(); //Increase the saturation for effect range LEDs
                break;

                case KC_F19:
                rgb_matrix_decrease_sat(); //Decrease the saturation for effect range LEDs
                break;

                case KC_F20:
                rgb_matrix_increase_val(); //Increase the value for effect range LEDs
                break;

                case KC_F21:
                rgb_matrix_decrease_val();//Decrease the value for effect range LEDs
                break;

                case KC_VOLU:
                case KC_VOLD:
                tap_code(encoder_cw_keycode);
                break;

                default:
                tap_code(encoder_cw_keycode);
                break;
            }
            set_volume_animation(true);
        } else {
             switch(encoder_ccw_keycode) {

                case KC_F13:
                rgb_matrix_toggle();
                break;

                case KC_F14:
                rgb_matrix_step();
                break;

                case KC_F15:
                rgb_matrix_step_reverse();
                break;

                case KC_F16:
                rgb_matrix_increase_hue();  //Increase the hue for effect range LEDs
                break;

                case KC_F17:
                rgb_matrix_decrease_hue(); //Decrease the hue for effect range LEDs
                break;

                case KC_F18:
                rgb_matrix_increase_sat(); //Increase the saturation for effect range LEDs
                break;

                case KC_F19:
                rgb_matrix_decrease_sat(); //Decrease the saturation for effect range LEDs
                break;

                case KC_F20:
                rgb_matrix_increase_val(); //Increase the value for effect range LEDs
                break;

                case KC_F21:
                rgb_matrix_decrease_val();//Decrease the value for effect range LEDs
                break;

                case KC_VOLU:
                case KC_VOLD:
                tap_code(encoder_ccw_keycode);
                break;

                default:
                tap_code(encoder_ccw_keycode);
                break;
            }
            set_volume_animation(false);
        }
        encoder_timer = timer_read32();
    }
    return true;
}
