/* Copyright 2021 Kyle McCreery
 * Copyright 2021 Jonavin Eng
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
#include <stdio.h>
#include "jonavin.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_all(
                                                                                                                KC_MUTE,
    KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    TT(_RAISE),       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFTCAPS, KC_SLSH, KC_Z,  KC_X,  KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,           KC_SFTENT,
    KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,  LT(_LOWER,KC_SPC),         KC_SPC,           KC_RALT, MO(_FN1),  KC_RCTL ),

  [_FN1] = LAYOUT_all(
                                                                                                                ENCFUNC,
    KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
    KC_CAPS,          KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PSCR, KC_SLCK, KC_PAUS, KC_NO,   KC_NO,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NLCK, KC_NO,   KC_NO,   KC_NO,            KC_SFTENT,
    KC_TRNS, KC_WINLCK, KC_TRNS,        KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS ),

  [_LOWER] = LAYOUT_all(
                                                                                                                KC_TRNS,
    KC_GRAVE,         KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    KC_TRNS,          KC_MINS, KC_EQL,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_QUES, KC_SLSH, KC_PIPE, KC_BSLS, KC_TILD,
    KC_TRNS, KC_TRNS, KC_UNDS, KC_PLUS, KC_NO,   KC_NO,   KC_NO,   KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS ),

  [_RAISE] = LAYOUT_all(
                                                                                                                KC_TRNS,
  	KC_TAB,          KC_HOME,  KC_UP,   KC_END,  KC_PGUP, KC_PMNS, KC_PPLS, KC_P7,   KC_P8,   KC_P9,    KC_P0,  KC_TRNS,
  	TT(_RAISE),      KC_LEFT,  KC_DOWN, KC_RIGHT,KC_PGDN, KC_PSLS, KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_PDOT, KC_PEQL,
  	KC_TRNS, KC_TRNS, KC_NO,   KC_DEL,  KC_INS,  KC_NO,   KC_PAST, KC_P0,   KC_P1,   KC_P2,   KC_P3,            KC_PENT,
  	KC_TRNS, KC_TRNS, KC_TRNS,          KC_BSPC, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS )
};

/*  These are needed whether encoder function is enabled or not when ENCFUNC keycode is pressed.?
    Defaults never changes if no encoder present to change it
*/
typedef struct {
     char keydesc[6];    // this will be displayed on OLED
    uint16_t keycode;   // this is the keycode that will be sent when activted
} keycodedescType;

static const keycodedescType PROGMEM keyselection[] = {
    // list of key codes that will be scrollled through by encoder and description
        {"TASK",    KC_TASK},
        {"INS",     KC_INS},
        {"DEL",     KC_DEL},
        {"PrtSc",   KC_PSCR},
        {"ScrLk",   KC_SCLN},
        {"Break",   KC_PAUS},
        {"C-A-D",   KC_CAD},  // Ctrl-Alt-Del
        {"AltF4",   KC_AF4},
        {"PLAY",    KC_MEDIA_PLAY_PAUSE},
        {"RESET",   RESET},   // firmware flash mode
};

#define MAX_KEYSELECTION sizeof(keyselection)/sizeof(keyselection[0])

static uint8_t selectedkey_idx = 0;
static keycodedescType selectedkey_rec;

static void set_selectedkey(uint8_t idx) {
    // make a copy from PROGMEM
    memcpy_P (&selectedkey_rec, &keyselection[idx], sizeof selectedkey_rec);

    //selectedkey_rec = keyselection[idx];

}

void keyboard_post_init_keymap(void) {
  // Call the keyboard post init code.
    set_selectedkey(selectedkey_idx);
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ENCFUNC:
        if (record->event.pressed) {
            selectedkey_rec.keycode == RESET ? reset_keyboard() : tap_code16(selectedkey_rec.keycode); // handle RESET code
        } else {
            // when keycode is released
        }
        break;
    }
    return true;
};



#ifdef ENCODER_ENABLE       // Encoder Functionality
    uint8_t selected_layer = 0;

    bool encoder_update_user(uint8_t index, bool clockwise) {
        #ifdef OLED_ENABLE
            oled_clear();
            oled_render();
        #endif
        switch (index) {
            case 0:         // This is the only encoder right now, keeping for consistency
                switch(get_highest_layer(layer_state)){  // special handling per layer
                case _FN1:  // on Fn layer select what the encoder does when pressed
                    if (!keyboard_report->mods) {
                        if ( clockwise ) {
                            if ( selectedkey_idx  < MAX_KEYSELECTION-1) {
                                selectedkey_idx ++;
                            } else {
                               // do nothing
                            }
                        } else if ( !clockwise ) {
                            if ( selectedkey_idx  > 0){
                                selectedkey_idx --;
                            } else {
                                // do nothing
                            }
                        }
                        set_selectedkey(selectedkey_idx);
                        break;
                    } else {
                           // continue to default
                    }
                default:   // all other layers
                    if ( clockwise ) {
                        if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, encoder changes layers
                            if(selected_layer  < 3) {
                                selected_layer ++;
                                layer_move(selected_layer);
                            }
                        } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate next word
                             tap_code16(LCTL(KC_RGHT));
                        } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next track
                            tap_code(KC_MEDIA_NEXT_TRACK);
                        } else  {
                            tap_code(KC_VOLU);                                                   // Otherwise it just changes volume
                        }
                    } else if ( !clockwise ) {
                        if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) {
                            if (selected_layer  > 0) {
                                selected_layer --;
                                layer_move(selected_layer);
                            }
                        } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate previous word
                            tap_code16(LCTL(KC_LEFT));
                        } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media previous track
                            tap_code(KC_MEDIA_PREV_TRACK);
                        } else {
                            tap_code(KC_VOLD);
                        }
                    }
                    break;
                }
                break;
        }
        return true;
    }
#endif

#ifdef OLED_ENABLE   // OLED Functionality
    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_180;       // flips the display 180 degrees if offhand
    }

    bool clear_screen = false;          // used to manage singular screen clears to prevent display glitch
    static void render_name(void) {     // Render Mercutio Script Text
        static const char PROGMEM mercutio_name[] = {
            0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0xB6, 0x95, 0xB5, 0x96, 0xD5, 0xB6, 0xB6,
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        };
        oled_write_P(mercutio_name, false);
    }

    static void render_logo(void) {     // Render MechWild "MW" Logo
        static const char PROGMEM logo_1[] = {0x97, 0x98, 0x99, 0x9A,0x00};
        static const char PROGMEM logo_2[] = {0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x00};
        static const char PROGMEM logo_3[] = {0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xB6, 0x00};
        static const char PROGMEM logo_4[] = {0xB6, 0xB6, 0xB6, 0x9B, 0x9C, 0x9D, 0x9E, 0x00};
        oled_set_cursor(0,0);
        oled_write_P(logo_1, false);
        oled_set_cursor(0,1);
        oled_write_P(logo_2, false);
        oled_set_cursor(0,2);
        oled_write_P(logo_3, false);
        oled_set_cursor(0,3);
        oled_write_P(logo_4, false);
    }

    void oled_task_user(void) {

        if ( IS_HOST_LED_OFF(USB_LED_NUM_LOCK) && IS_HOST_LED_OFF(USB_LED_CAPS_LOCK) && selected_layer == 0 && get_highest_layer(layer_state) == 0 ) {
            render_name();
            clear_screen = true;
        } else {
            if (clear_screen == true) {
                oled_clear();
                oled_render();
                clear_screen = false;
            }
            render_logo();
            oled_set_cursor(8,2);
            char fn_str[12];
            switch(selected_layer){
                case 0:
                    oled_write_P(PSTR("BASE"), false);
                    break;
                case 1:
                    sprintf(fn_str, "FN %5s", selectedkey_rec.keydesc);
                    oled_write(fn_str, false);
                    //oled_write_P(PSTR("FN "), false);
                    break;
                case 2:
                    oled_write_P(PSTR("LOWER"), false);
                    break;
                case 3:
                    oled_write_P(PSTR("RAISE"), false);
                    break;
                default:
                    oled_write_P(PSTR("Layer ?"), false);    // Should never display, here as a catchall
            }
            oled_write_P(keymap_config.no_gui ? PSTR(" WL") : PSTR("   "), false);
            oled_set_cursor(8,3);
            if (get_highest_layer(layer_state) == selected_layer) {
                oled_write_P(PSTR("             "), false);
            } else {
                switch (get_highest_layer(layer_state)) {
                    case 0:
                        oled_write_P(PSTR("Temp BASE"), false);
                        break;
                    case 1:
                        sprintf(fn_str, "Temp FN %5s", selectedkey_rec.keydesc);
                        oled_write(fn_str, false);
                        break;
                    case 2:
                        oled_write_P(PSTR("Temp LOWER"), false);
                        break;
                    case 3:
                        oled_write_P(PSTR("Temp RAISE"), false);
                        break;
                    default:
                        oled_write_P(PSTR("Temp Layer ?"), false);    // Should never display, here as a catchall
                }
            }
            led_t led_state = host_keyboard_led_state();
            oled_set_cursor(8,0);
            uint8_t wpm_count;
            char wpm_str[10];
            wpm_count=get_current_wpm();

            if (wpm_count > 020) { // how wpm when > 20
                 sprintf(wpm_str, " WPM: %03d", wpm_count);
                oled_write(wpm_str, false);
            } else {
                oled_write_P(PSTR(" JONAVIN "), false); // otherwise display keymap name
            }

            oled_set_cursor(8,1);
            oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
            oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
            oled_write_P(led_state.scroll_lock ? PSTR("SCR") : PSTR("   "), false);

        }

    }

    void suspend_power_down_user(void) {  // shutdown oled when powered down to prevent OLED from showing Mercutio all the time
      oled_off();
    }
#endif
