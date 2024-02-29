/*
Copyright 2023 Qwertykeys

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
    {0, SW1_CS2, SW1_CS3, SW1_CS1},    /* RGB0-ESC ROW0*/
    {0, SW1_CS5, SW1_CS6, SW1_CS4},    /* RGB1-F1 */
    {0, SW1_CS8, SW1_CS9, SW1_CS7},    /* RGB2-F2 */
    {0, SW1_CS11, SW1_CS12, SW1_CS10}, /* RGB3-F3 */
    {0, SW1_CS14, SW1_CS15, SW1_CS13}, /* RGB4-F4 */
    {0, SW1_CS17, SW1_CS18, SW1_CS16}, /* RGB5-F5 */
    {0, SW1_CS20, SW1_CS21, SW1_CS19}, /* RGB6-F6 */
    {0, SW1_CS23, SW1_CS24, SW1_CS22}, /* RGB7-F7 */
    {0, SW1_CS26, SW1_CS27, SW1_CS25}, /* RGB8-F8 */
    {0, SW1_CS29, SW1_CS30, SW1_CS28}, /* RGB9-F9 */
    {0, SW1_CS32, SW1_CS33, SW1_CS31}, /* RGB10-F10 */
    {0, SW1_CS35, SW1_CS36, SW1_CS34}, /* RGB11-F11 */
    {0, SW1_CS38, SW1_CS39, SW1_CS37}, /* RGB12-F12 */
    {0, SW7_CS29, SW7_CS30, SW7_CS28}, /* RGB13-Delete */
    {0, SW7_CS32, SW7_CS33, SW7_CS31}, /* RGB14-End */
    {0, SW7_CS35, SW7_CS36, SW7_CS34}, /* RGB15-Insert */
    {0, SW7_CS38, SW7_CS39, SW7_CS37}, /* RGB16-Home */
    {0, SW2_CS2, SW2_CS3, SW2_CS1},    /* RGB17-~ ----ROW1*/
    {0, SW2_CS5, SW2_CS6, SW2_CS4},    /* RGB18-1 */
    {0, SW2_CS8, SW2_CS9, SW2_CS7},    /* RGB19-2 */
    {0, SW2_CS11, SW2_CS12, SW2_CS10}, /* RGB20-3 */
    {0, SW2_CS14, SW2_CS15, SW2_CS13}, /* RGB21-4 */
    {0, SW2_CS17, SW2_CS18, SW2_CS16}, /* RGB22-5 */
    {0, SW2_CS20, SW2_CS21, SW2_CS19}, /* RGB23-6 */
    {0, SW2_CS23, SW2_CS24, SW2_CS22}, /* RGB24-7 */
    {0, SW2_CS26, SW2_CS27, SW2_CS25}, /* RGB25-8 */
    {0, SW2_CS29, SW2_CS30, SW2_CS28}, /* RGB26-9 */
    {0, SW2_CS32, SW2_CS33, SW2_CS31}, /* RGB27-0 */
    {0, SW2_CS35, SW2_CS36, SW2_CS34}, /* RGB28--- */
    {0, SW2_CS38, SW2_CS39, SW2_CS37}, /* RGB29-+= */
    {0, SW7_CS26, SW7_CS27, SW7_CS25}, /* RGB30-BS */
    {0, SW8_CS29, SW8_CS30, SW8_CS28}, /* RGB31-Num Lock */
    {0, SW8_CS32, SW8_CS33, SW8_CS31}, /* RGB32- / */
    {0, SW8_CS35, SW8_CS36, SW8_CS34}, /* RGB33- * */
    {0, SW8_CS38, SW8_CS39, SW8_CS37}, /* RGB34- - */
    {0, SW3_CS2, SW3_CS3, SW3_CS1},    /* RGB35-TAB ----ROW2*/
    {0, SW3_CS5, SW3_CS6, SW3_CS4},    /* RGB36-Q */
    {0, SW3_CS8, SW3_CS9, SW3_CS7},    /* RGB37-W */
    {0, SW3_CS11, SW3_CS12, SW3_CS10}, /* RGB38-E */
    {0, SW3_CS14, SW3_CS15, SW3_CS13}, /* RGB39-R */
    {0, SW3_CS17, SW3_CS18, SW3_CS16}, /* RGB40-T */
    {0, SW3_CS20, SW3_CS21, SW3_CS19}, /* RGB41-Y */
    {0, SW3_CS23, SW3_CS24, SW3_CS22}, /* RGB42-U */
    {0, SW3_CS26, SW3_CS27, SW3_CS25}, /* RGB43-I */
    {0, SW3_CS29, SW3_CS30, SW3_CS28}, /* RGB44-O */
    {0, SW3_CS32, SW3_CS33, SW3_CS31}, /* RGB45-P */
    {0, SW3_CS35, SW3_CS36, SW3_CS34}, /* RGB46-[ */
    {0, SW3_CS38, SW3_CS39, SW3_CS37}, /* RGB47-] */
    {0, SW9_CS26, SW9_CS27, SW9_CS25}, /* RGB48-\ */
    {0, SW9_CS29, SW9_CS30, SW9_CS28}, /* RGB49-page up */
    {0, SW9_CS32, SW9_CS33, SW9_CS31}, /* RGB50-7 */
    {0, SW9_CS35, SW9_CS36, SW9_CS34}, /* RGB51-8 */
    {0, SW9_CS38, SW9_CS39, SW9_CS37}, /* RGB52-9 */
    {0, SW4_CS2, SW4_CS3, SW4_CS1},    /* RGB53-CAPS---ROW3*/
    {0, SW4_CS5, SW4_CS6, SW4_CS4},    /* RGB54-A-- */
    {0, SW4_CS8, SW4_CS9, SW4_CS7},    /* RGB55-S-- */
    {0, SW4_CS11, SW4_CS12, SW4_CS10}, /* RGB56-D */
    {0, SW4_CS14, SW4_CS15, SW4_CS13}, /* RGB57-F */
    {0, SW4_CS17, SW4_CS18, SW4_CS16}, /* RGB58-G */
    {0, SW4_CS20, SW4_CS21, SW4_CS19}, /* RGB59-H */
    {0, SW4_CS23, SW4_CS24, SW4_CS22}, /* RGB60-J */
    {0, SW4_CS26, SW4_CS27, SW4_CS25}, /* RGB61-K */
    {0, SW4_CS29, SW4_CS30, SW4_CS28}, /* RGB62-L */
    {0, SW4_CS32, SW4_CS33, SW4_CS31}, /* RGB63-;: */
    {0, SW4_CS35, SW4_CS36, SW4_CS34}, /* RGB64-'" */
    {0, SW4_CS38, SW4_CS39, SW4_CS37}, /* RGB65-ENTER */
    {0, SW7_CS11, SW7_CS12, SW7_CS10}, /* RGB66-Page Down */
    {0, SW7_CS14, SW7_CS15, SW7_CS13}, /* RGB67-4 */
    {0, SW7_CS17, SW7_CS18, SW7_CS16}, /* RGB68-5 */
    {0, SW7_CS20, SW7_CS21, SW7_CS19}, /* RGB69-6 */
    {0, SW7_CS23, SW7_CS24, SW7_CS22}, /* RGB70-+ */
    {0, SW5_CS2, SW5_CS3, SW5_CS1},    /* RGB71-LSF --ROW4*/
    {0, SW5_CS5, SW5_CS6, SW5_CS4},    /* RGB72-Z */
    {0, SW5_CS8, SW5_CS9, SW5_CS7},    /* RGB73-X */
    {0, SW5_CS11, SW5_CS12, SW5_CS10}, /* RGB74-C */
    {0, SW5_CS14, SW5_CS15, SW5_CS13}, /* RGB75-V */
    {0, SW5_CS17, SW5_CS18, SW5_CS16}, /* RGB76-B */
    {0, SW5_CS20, SW5_CS21, SW5_CS19}, /* RGB77-N */
    {0, SW5_CS23, SW5_CS24, SW5_CS22}, /* RGB78-M */
    {0, SW5_CS26, SW5_CS27, SW5_CS25}, /* RGB79-,< */
    {0, SW5_CS29, SW5_CS30, SW5_CS28}, /* RGB80->. */
    {0, SW5_CS32, SW5_CS33, SW5_CS31}, /* RGB81-?/ */
    {0, SW5_CS35, SW5_CS36, SW5_CS34}, /* RGB82-RSF */
    {0, SW5_CS38, SW5_CS39, SW5_CS37}, /* RGB83-UP */
    {0, SW8_CS14, SW8_CS15, SW8_CS13}, /* RGB84-1*/
    {0, SW8_CS17, SW8_CS18, SW8_CS16}, /* RGB85-2 */
    {0, SW8_CS20, SW8_CS21, SW8_CS19}, /* RGB86-3 */
    {0, SW8_CS23, SW8_CS24, SW8_CS22}, /* RGB87-Enter */
    {0, SW6_CS2, SW6_CS3, SW6_CS1},    /* RGB88-lct-- ROW5*/
    {0, SW6_CS5, SW6_CS6, SW6_CS4},    /* RGB89-lwin */
    {0, SW6_CS8, SW6_CS9, SW6_CS7},    /* RGB90-lalt */
    {0, SW6_CS11, SW6_CS12, SW6_CS10}, /* RGB91-sp0 */
    {0, SW6_CS17, SW6_CS18, SW6_CS16}, /* RGB92-sp */
    {0, SW6_CS26, SW6_CS27, SW6_CS25}, /* RGB93-sp2 */
    {0, SW6_CS29, SW6_CS30, SW6_CS28}, /* RGB94-ralt */
    {0, SW6_CS32, SW6_CS33, SW6_CS31}, /* RGB95- fn */
    {0, SW6_CS35, SW6_CS36, SW6_CS34}, /* RGB96-left */
    {0, SW6_CS38, SW6_CS39, SW6_CS37}, /* RGB97-down */
    {0, SW9_CS11, SW9_CS12, SW9_CS10}, /* RGB98-right */
    {0, SW9_CS14, SW9_CS15, SW9_CS13}, /* RGB99- 0 */
    {0, SW9_CS20, SW9_CS21, SW9_CS19}  /* RGB100- . */
};

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_KB_0:
                rgb_matrix_toggle();
                break;

            case QK_KB_1:
                rgb_matrix_step();
                break;

            case QK_KB_2:
                rgb_matrix_step_reverse();
                break;

            case QK_KB_3:
                rgb_matrix_increase_hue(); // Increase the hue for effect range LEDs
                break;

            case QK_KB_4:
                rgb_matrix_decrease_hue(); // Decrease the hue for effect range LEDs
                break;

            case QK_KB_5:
                rgb_matrix_increase_sat(); // Increase the saturation for effect range LEDs
                break;

            case QK_KB_6:
                rgb_matrix_decrease_sat(); // Decrease the saturation for effect range LEDs
                break;

            case QK_KB_7:
                rgb_matrix_increase_val(); // Increase the value for effect range LEDs
                break;

            case QK_KB_8:
                rgb_matrix_decrease_val(); // Decrease the value for effect range LEDs
                break;

            case QK_KB_9:
                rgb_matrix_increase_speed(); // Increase the speed of the animations
                break;

            case QK_KB_10:
                rgb_matrix_decrease_speed(); // Decrease the speed of the animations
                break;

            default:
                break;
        }
    }
    return process_record_user(keycode, record);
}
#endif

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_WHITE});

const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS({3, 3, HSV_WHITE});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_capslock_layer, my_numlock_layer);

void keyboard_post_init_kb(void) {
    rgblight_layers = my_rgb_layers;
    keyboard_post_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        rgblight_set_layer_state(0, led_state.caps_lock);
        rgblight_set_layer_state(1, !led_state.num_lock);
    }
    return res;
}