// Copyright 2023 <dennis@kruyt.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┌───┬───┬───┬───┐
     * │OLD│Esc│Vo-│Vo+│Bsp│
     * ├───┼───┼───┼───┼───┤
     * │MO1│Num│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │M1 │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┼───┤ + │
     * │M2 │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┼───┤
     * │M3 │ 1 │ 2 │ 3 │   │
     * ├───┼───┴───┼───┤Ent│
     * │M4 │ 0     │ . │   │
     * └───┴───────┴───┴───┘
     */

    // Numpad
    [0] = LAYOUT(
                 KC_ESC, KC_VOLD, KC_VOLU, KC_BSPC,
        MO(4),   KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        _______, KC_P7,  KC_P8,   KC_P9,   KC_PPLS,
        _______, KC_P4,  KC_P5,   KC_P6,   
        _______, KC_P1,  KC_P2,   KC_P3,   KC_PENT,
        _______, KC_P0,           KC_PDOT 
    ),
    // Nav
    [1] = LAYOUT(
                 _______,    _______,    _______,    _______,
        _______, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN4,
        _______, KC_HOME,    KC_UP,      KC_PGUP,    _______,
        _______, KC_LEFT,    XXXXXXX,    KC_RGHT, 
        _______, KC_END,     KC_DOWN,    KC_PGDN,    _______,
        _______, KC_INS,     KC_DEL  
    ),
    // Mouse
    [2] = LAYOUT(
                 _______,    _______,    _______,     _______,
        _______, _______,    _______,    _______,     _______,
        _______, _______,    KC_MS_UP,   _______,     _______,
        _______, KC_MS_LEFT, _______,    KC_MS_RIGHT, 
        _______, _______,    KC_MS_DOWN, _______,     _______,
        _______, _______,    _______  
    ),
    // Media
    [3] = LAYOUT(
                 _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, KC_MPRV, KC_MPLY, KC_MNXT, 
        _______, _______, _______, _______, _______,
        _______, _______, _______  
    ),
    // Layer Switching
    [4] = LAYOUT(
                 QK_BOOT, KC_MUTE, _______, _______,
        _______, _______, _______, _______, _______,
        TO(0),   _______, _______, _______, _______,
        TO(1),   _______, _______, _______, 
        TO(2),   _______, _______, _______, _______,
        TO(3),   _______,          _______  
    )
};

#define LED_0_PIN GP4
#define LED_1_PIN GP5
#define LED_2_PIN GP6
#define LED_3_PIN GP7
#define LED_4_PIN GP8

void matrix_init_user(void) {
  // Set the LED pins as output pins
  setPinOutput(LED_0_PIN);
  setPinOutput(LED_1_PIN);
  setPinOutput(LED_2_PIN);
  setPinOutput(LED_3_PIN);
  setPinOutput(LED_4_PIN);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(LED_0_PIN, layer_state_cmp(state, 0));
    writePin(LED_1_PIN, layer_state_cmp(state, 1));
    writePin(LED_2_PIN, layer_state_cmp(state, 2));
    writePin(LED_3_PIN, layer_state_cmp(state, 3));
    writePin(LED_4_PIN, layer_state_cmp(state, 4));
    return state;
}


#ifdef OLED_ENABLE 

// Count number of key presses
static uint16_t type_count = 0;
 void  count_type ( void ) {
    type_count++;
}

// Function to be called when the key is pressed/released 
// If the function itself is not added, add each function, if it is, add only in `#ifdef OLED_ENABLE` 
bool  process_record_user ( uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
         count_type ();
    }
    return  true ;
}

// Write keypress counter
void oled_write_type_count ( void ) {
     oled_write_P ( PSTR ( "Type count: " ), false );
     oled_write_ln (get_u16_str(type_count, ' '), false );
}

// Layer state
void  oled_write_layer_state ( void ) {
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Numpad\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Mouse\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case 4:
            oled_write_P(PSTR("Layer Switch\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
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
     oled_write_ln_P (led_state.scroll_lock ? PSTR ( "on\n" ) : PSTR ( "-" ), false );
}

// Uptime
// Write a two-digit number to the OLED display
static void oled_write_2digit(uint8_t digit) {
    oled_write_char(digit < 10 ? '0' : digit / 10 + '0', false);
    oled_write_char(digit % 10 + '0', false);
}

// Write the current uptime to the OLED display
void oled_write_uptime(void) {
    static uint32_t last_update = 0;
    uint32_t uptime_s = timer_read32() / 1000;
    if (uptime_s - last_update >= 1) { // Update display every second
        last_update = uptime_s;
        oled_write_P(("Uptime "), false);
        oled_write_2digit(uptime_s / 3600 % 24);
        oled_write_char(':', false);
        oled_write_2digit(uptime_s / 60 % 60);
        oled_write_char(':', false);
        oled_write_2digit(uptime_s % 60);
        oled_write_char('\n', false);
    }
}

// logo
void oled_render_qmk(void) {
    static const char PROGMEM qmk_logo[] = {
	    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(PSTR("\n\n"), false);
    oled_write_P(qmk_logo, false);
}

void oled_render_logo(void) {
    static const unsigned char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224,248,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,192,192,240,252,254,248,240,224,192,192,240,252,254,255,255,255,255,254,128,128,  0,  0,128,128,192,192, 32,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,240,248,252,254,254,255,254,254,254,254,255,255,255,255,255,255,255,251,241,241,241,241,249,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,193,128,192,192,192,192, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,248,248,  0,  0,  0,  0, 48, 48,240,240, 48, 48, 48, 48, 48, 48, 48,176,240,112,  0,  0,  0,  0,  0,  0, 16, 56,112,  0,  0, 24, 56, 32,128,192,224,248, 24,  0,  0,  0,  0,  0,  0,248,248,  0, 16,112,224,128,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  3,  7,  3,  3,  3,  3,  7,  7,  3,  7, 15,  7,  7, 31, 15, 15, 15, 31, 31, 31,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,243,192,128,192,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,254, 63,  0,  0,255,255,  0,  3, 31,152,128,128,192,195,231,110, 60, 56, 60,126,231,195,193,128,128,128,  0,  0,  0,  0,255,255,219,153,153,153,255,255,153,153,153,255,255,  0,  0, 24, 24, 24, 24,255,255,220, 24, 24, 24, 25,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24,  8,  8, 12,  4,  6,  6,  3,131,195,227,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,240,224,224, 96,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,255,255,  0,  0,  1,  3, 49, 49, 48, 48, 48, 48,254,254,254, 48, 48, 48, 48, 49, 49,  1,  0,  0,  0, 12, 12,236,236,108,108,108,108,108,108,108,108,236,236, 12,  4,  0,128,224,254, 15,  3, 31,248,192,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,248,248,240,240,248,254,254,252,255,254,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,252,252,128,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63, 63,  0,  0, 24, 24, 24, 24, 24, 24, 24, 24, 31, 31, 31, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0,  0,  0, 63, 63, 12, 12, 12, 12, 12, 12, 12, 12, 63, 63,  0, 24, 60, 15,  3,  0,  0,  0,  0,  1,  3, 14, 60, 16,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  3,  7, 31,127,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,127,127,127, 63, 63, 63, 63, 31, 31, 31, 31, 30,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,  7,  7,  7,  7,  7,  3,  3,  3,  3,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     };
    oled_write_raw((char*)raw_logo, sizeof(raw_logo));

}

// This is a variable to keep track of the time elapsed since power up
static uint32_t logo_timer = 0;

// Write all to oled
bool oled_task_user(void) {
  if (logo_timer == 0) {
    logo_timer = timer_read32();
  }

  // display the logo
uint32_t elapsed_time = timer_elapsed32(logo_timer);
if (elapsed_time < 5000) {
  oled_render_logo();
  return false;
}
else if (elapsed_time < 5200) {
  oled_clear();
  return false;
}
else if (elapsed_time < 8000) {
  oled_render_qmk();
  return false;
}
    // Write other OLED content here
    oled_write_host_led_state ();
    oled_write_P(PSTR("\n"), false);
    oled_write_layer_state ();
    oled_write_type_count ();
    oled_write_P(PSTR("\n"), false);
    oled_write_uptime ();
    return false;
}
#endif