#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY   0
#define _LOWER    1
#define _RAISE    2  
#define _ADJUST     3

// #define RAISE MO(_RAISE)
// #define LOWER MO(_LOWER)

//==========================================
// CUSTOM KEYCODES DEFINITION
//==========================================

// Macro declarations
enum custom_keycodes {
    // Macro code
    M_MAC1 = SAFE_RANGE,
    M_MAC2,
};

//==========================================
// BUNCH OF DEFINITIONS
//==========================================

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
//void set_keylog(uint16_t keycode, keyrecord_t *record);
//const char *read_keylog(void);
//const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

//==========================================
// MACRO DEFINITION
//==========================================

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
   set_timelog();
  }
/*     switch (keycode) {
    case M_MAC1:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case M_MAC2:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
        } else {
            // when keycode QMKBEST is released
        }
        break;	
    } */
    return true;
};



//==========================================
// LAYER DEFINITIOM
//==========================================

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
     KC_GESC  , KC_1  , KC_2    ,   KC_3  , KC_4  ,   KC_5  ,                KC_6   ,   KC_7  ,   KC_8  ,   KC_9    , KC_0    , KC_BSPC ,
     KC_TAB   , KC_Q  , KC_W    ,   KC_E  , KC_R  ,   KC_T  ,                KC_Y   ,   KC_U  ,   KC_I  ,   KC_O    , KC_P    , KC_BSLS ,
     KC_LCTL  , KC_A  , KC_S    ,   KC_D  , KC_F  ,   KC_G  ,                KC_H   ,   KC_J  ,   KC_K  ,   KC_L    , KC_SCLN , KC_QUOT ,
     KC_LSFT  , KC_Z  , KC_X    ,   KC_C  , KC_V  ,   KC_B  ,                KC_N   ,   KC_M  ,   KC_COMM,  KC_DOT  , KC_SLSH , OSL(1) ,
                        KC_LBRC  ,  KC_RBRC,                                                      KC_MINS,  KC_EQL,
                                    KC_LGUI,  MO(1),                                    KC_ENT,   KC_SPC,
                                            KC_LALT , KC_DEL,                KC_PGUP, KC_LGUI,
                                            KC_INS  , KC_INS,                KC_N , KC_PGDN
  ),

  [_LOWER] = LAYOUT(

     KC_TILD    , KC_F1   , KC_F2   , KC_F3   , KC_F4     , KC_F5  ,      KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_DEL ,
     _______    , _______ , _______  , _______ , RESET     , _______,      _______ , _______ , _______ , _______ , _______ , _______,
     _______    , _______ , _______ , _______ , _______ , _______,        KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT, _______ , _______,
     _______    , _______ , _______   , _______ , _______ , _______,      _______ , _______ , _______ , _______ , _______ , _______,
                            _______ , _______ ,                                               _______ , _______ ,
                                      _______ , _______ ,                           _______ , _______ ,
                                                KC_TRNS   , _______,      _______ , _______,
                                                KC_TRNS   , _______,      _______ , _______

  ),

  [_RAISE] = LAYOUT(

     _______  , _______ , _______ , _______ , _______ , _______,      _______ , _______ , _______ , _______ , _______ , _______,
     _______  , _______ , _______ , _______ , _______ , _______,      _______ , _______ , _______ , _______ , _______ , _______,
     _______  , _______ , _______ , _______ , _______ , _______,      _______ , _______ , _______ , _______ , _______ , _______,
     _______  , _______ , _______ , _______ , _______ , _______,      _______ , _______ , _______ , _______ , _______ , _______,
                              _______ , _______ ,                                         _______ , _______ ,
                                    _______ , _______ ,                         _______ , _______ ,
                                              _______ , _______,      _______ , _______,
                                              _______ , _______,      _______ , _______
  ), 

  [_ADJUST] = LAYOUT(

     _______  , _______ , _______ , _______ , _______ , _______,      _______ , _______ , _______ , _______ , _______ , _______,
     _______  , _______ , _______ , _______ , _______ , _______,      _______ , _______ , _______ , _______ , _______ , _______,
     _______  , _______ , _______ , _______ , _______ , _______,      _______ , _______ , _______ , _______ , _______ , _______,
     _______  , _______ , _______ , _______ , _______ , _______,      _______ , _______ , _______ , _______ , _______ , _______,
                              _______ , _______ ,                                         _______ , _______ ,
                                    _______ , _______ ,                         _______ , _______ ,
                                              _______ , _______,      _______ , _______,
                                              _______ , _______,      _______ , _______
  ),

};

//==========================================

//==========================================
// ENCODERS DEFINITIOM
//==========================================

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

//==========================================
// OLED DEFINITIOM
//==========================================

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE