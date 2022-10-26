/*
Copyright 2022 <dennis@kruyt.org>

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
#include QMK_KEYBOARD_H

enum Layer {
    _NUMPAD = 0,        // Standard QWERTY layer
    _MOUSE,          // Function key layer
    _NAV,
};
#define _NP _NUMPAD
#define _MS _MOUSE
#define _NV _NAV

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * ,-------------------.
   * | Fx | Fx | Fx | Fx |
   * |----|----|----|----|
   * | NL | /  | *  | -  |
   * |----|----|----|----|
   * | 7  | 8  | 9  |    |
   * |----|----|----| +  |
   * | 4  | 5  | 6  |    |
   * |----|----|----|----|
   * | 1  | 2  | 3  |    |
   * |----|----|----| En |
   * |    0    | .  |    |
   * `-------------------'
   */

  [_NUMPAD] = LAYOUT_numpad_6x5(
    MO(_MS), KC_MUTE, KC_VOLD, KC_VOLU,
    KC_PSCR, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, 
    TO(_NP), KC_P7,   KC_P8,   KC_P9,   
    TO(_MS), KC_P4,   KC_P5,   KC_P6,   KC_PPLS, 
    TO(_NV), KC_P1,   KC_P2,   KC_P3,   
    KC_A, KC_P0, KC_PDOT,  KC_PENT  
  ),

  [_MOUSE] = LAYOUT_numpad_6x5(
    _______, KC_MUTE, KC_VOLD, KC_VOLU,
    KC_PSCR, KC_NUM, KC_BTN1, KC_BTN2, KC_BTN3, 
    TO(_NP), KC_P7,   KC_MS_U,   KC_P9,   
    TO(_MS), KC_MS_L,   KC_P5,   KC_MS_R,   KC_PPLS, 
    TO(_NV), KC_P1,   KC_MS_D,   KC_P3,   
    KC_A, KC_P0, KC_PDOT,  KC_PENT
  ),

  [_NAV] = LAYOUT_numpad_6x5(
    MO(_MS), KC_MUTE, KC_VOLD, KC_VOLU,
    KC_PSCR, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, 
    TO(_NP), KC_HOME,   KC_UP,   KC_PGUP,   
    TO(_MS), KC_LEFT,   _______,   KC_RIGHT,   KC_PPLS, 
    TO(_NV), KC_END,   KC_DOWN,   KC_PGDOWN,   
    KC_A, KC_INS, KC_DEL,  KC_PENT  
  ),
};

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(GP4);
  writePinLow(GP4);
  // set NumLock LED to output and low
  setPinOutput(GP5);
  writePinLow(GP5);
  // set ScrollLock LED to output and low
  setPinOutput(GP6);
  writePinLow(GP6);
}

void led_update_ports(led_t led_state) {
    writePin(GP4, led_state.num_lock);
    writePin(GP5, led_state.caps_lock);
    writePin(GP6, led_state.scroll_lock);
}

static uint16_t type_count = 0;
 void  count_type ( void ) {
    type_count++;
}

// Function to be called when the key is pressed/released 
// If the function itself is not added, add each function, if it is, add only in `#ifdef OLED_ENABLE` 
bool  process_record_user ( uint16_t keycode, keyrecord_t *record) {
 #ifdef OLED_ENABLE 
    if (record->event.pressed) {
         count_type ();
    }
#endif 
    return  true ;
}

void  oled_write_type_count ( void ) {
     oled_write_P ( PSTR ( "Type count: " ), false );
     oled_write_ln (get_u16_str(type_count, ' '), false );
}

// Layer state
void  oled_write_layer_state ( void ) {
   // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:
            oled_write_P(PSTR("Numpad\n"), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("Mouse\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined\n"), false);
    }
}

// State of NumLock/CapsLock/ScrollLock
void  oled_write_host_led_state ( void ) {
     const led_t led_state = host_keyboard_led_state ();
     oled_write_P ( PSTR ( "NL:" ), false );
     oled_write_P (led_state.num_lock ? PSTR ( "on" ) : PSTR ( "- " ), false );
     oled_write_P ( PSTR ( " CL:" ), false );
     oled_write_P (led_state.caps_lock ? PSTR ( "on" ) :PSTR ( "- " ), false );
     oled_write_P ( PSTR ( " SL:" ), false );
     oled_write_ln_P (led_state.scroll_lock ? PSTR ( "on\n" ) : PSTR ( "-\n" ), false );
}

// Uptime
// write given digit, with leading zero if digit < 10
void oled_write_2digit(unsigned int digit) {
    static char buf[6];
    itoa(digit, buf, 10);
    if (digit < 10) {
        oled_write_char('0', false);
    }
    oled_write(buf, false);
}

void oled_write_uptime(void) {
    static uint32_t uptime_s;
    uptime_s = timer_read32() / 1000;
    oled_write_P(PSTR("Uptime "), false);
    // hour
    oled_write_2digit((uptime_s / 3600) % 60);
    oled_write_char(':', false);
    // minutes
    oled_write_2digit((uptime_s / 60) % 60);
    oled_write_char(':', false);
    // seconds
    oled_write_2digit(uptime_s % 60);
    oled_write_char('\n', false);
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
 
    oled_render_logo();
    oled_write_host_led_state ();
    oled_write_layer_state ();
    oled_write_type_count ();
    oled_write_uptime ();
    return false;
}
#endif