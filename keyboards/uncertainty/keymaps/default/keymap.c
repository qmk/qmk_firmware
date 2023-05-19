#include QMK_KEYBOARD_H


#include "print.h"
#include <stdio.h>
char wpm_str[10];
typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

user_config_t user_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 0
    *        ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
    *        │ Esc  │  F1  │  F2  │  F3  │  F4  │  F5  │  F6  │  F7  │  F8  │  F9  │  F10 │  F11 │  F12 │PrtScn│  Del │ Home │  End │ PgUp │ PgDn │
    *        ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┴──────┼──────┼──────┼──────┼──────┤
    *        │   `  │   1  │   2  │   3  │   4  │   5  │   6  │   7  │   8  │   9  │   0  │  -   │  =   │    Bksp     │ # Lk │   /  │   *  │  -   │
    * ┌──────┼──────┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬──┴───┬─────────┼──────┼──────┼──────┼──────┤
    * │ Mute │   Tab    │   Q  │   W  │   E  │   R  │   T  │   Y  │   U  │   I  │   O  │   P  │  [   │  ]   │    \    │  7   │  8   │  9   │      │
    * ├──────┼──────────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─────────┼──────┼──────┼──────┤  +   |
    * │ Null │   Caps     │   A  │   S  │   D  │   F  │   G  │   H  │   J  │   K  │   L  │   ;  │   '  │    Enter     │  4   │  5   │  6   │      |
    * ├──────┼────────────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴─┬────┴───────┬──────┼──────┤──────┼──────┼──────┤
    * │ Null │     Shft     │   Z  │   X  │   C  │   V  │   B  │   N  │   M  │   ,  │   .  │   /  │    Shft    │  Up  │  1   │  2   │  3   │      │
    * ├──────┼───────┬──────┴┬─────┴─┬────┴──────┴──────┴──────┴──────┴──────┴─────┬┴─────┬┴─────┬┴─────┬──────┼──────┼──────┼──────┼──────┤ Entr |
    * │ Null │ Ctrl  │ Gui   │ Alt   │                  Space                      │ Alt  │   Fn │ Ctrl │ Left │ Down │ Right│  0   │   .  │      │
    * └──────┴───────┴───────┴───────┴─────────────────────────────────────────────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘
    */
    [0] = LAYOUT(
                 KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_DEL,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN, 
                 KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC         , KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, 
        KC_MUTE, KC_TAB   ,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS      , KC_P7,   KC_P8,   KC_P9,   KC_PPLS, 
        XXXXXXX, KC_CAPS     , KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT             ,  KC_P4,   KC_P5,   KC_P6,   
        XXXXXXX, KC_LSFT      , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT            , KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT, 
        XXXXXXX, KC_LCTL  , KC_LGUI  , KC_LALT  ,                    KC_SPC                           ,  KC_RALT, MO(1)   , KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT  
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  }
};
#endif

#ifdef RGBLIGHT_ENABLE
// Light LEDs 0 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN}       // Light 1 LEDs, starting with LED 0
);

// Light LEDs 1 red when num lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_GREEN}       // Light 1 LEDs, starting with LED 1
);

const rgblight_segment_t PROGMEM indicators_off_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_OFF}       // Light 1 LEDs, starting with LED 1
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    indicators_off_layer,
    my_capslock_layer,
    my_numlock_layer
);


bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    rgblight_set_layer_state(2, led_state.num_lock);
    return true;
}

void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=true;

    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, 1);
    // rgblight_mode_noeeprom(RGBLIGHT_EFFECT_KNIGHT);
    rgblight_set_effect_range(2, 6);
    
    rgblight_enable();
    //rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);

}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case :
      if (record->event.pressed) {
        // Do something when pressed
      } else {
        // Do something else when release
        print("begin rgb_mod\n");
        user_config.raw= eeconfig_read_user();
        uprintf("pre raw value: %lx\n", user_config.raw);

        user_config.rgb_layer_change = !user_config.rgb_layer_change;
        eeconfig_update_user(user_config.raw);

        user_config.raw= eeconfig_read_user();
        uprintf("post raw value: %lx\n", user_config.raw);
        print("done release rgb_mod\n");

        #ifdef RGBLIGHT_ENABLE
        print("begin change rgb mode\n");
        rgblight_step();
        print("done change rgb mode\n");
        #endif

      }
      return false; // Skip all further processing of this key
      default:
      return true; // Process all other keycodes normally
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 2;
  user_config.rgb_layer_change = true; // We want this enabled by default
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM now

  // use the non noeeprom versions, to write these values to EEPROM too
//   rgblight_enable(); // Enable RGB by default
//   rgblight_sethsv_cyan();  // Set it to CYAN by default
//   rgblight_mode(1); // set to solid by default
}

// void keyboard_post_init_user(void) {

//     debug_enable=true;
//     debug_matrix=true;

// }
#ifdef OLED_ENABLE
// typedef enum {
//     OLED_ROTATION_0   = 0,
//     OLED_ROTATION_90  = 1,
//     OLED_ROTATION_180 = 2,
//     OLED_ROTATION_270 = 3, // OLED_ROTATION_90 | OLED_ROTATION_180
// } oled_rotation_t;
// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     return OLED_ROTATION_90;
// }
// bool oled_task_user(void) {
//     oled_write_P(PSTR("WPM: "), false);
//     oled_write(get_u8_str(get_current_wpm(), '0'), false);
//     return false;
// }
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    //render_logo();
    //oled_set_cursor(1, 1);  
    oled_write_P(PSTR("WPM: "), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
    return false;
}
#endif
