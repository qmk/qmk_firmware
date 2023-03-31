// Copyright 2023 Freather
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BACKSPACE,  KC_HOME,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_INS,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_DEL,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
      KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [1] = LAYOUT(
      KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11, KC_F12,  KC_TRNS,  KC_TRNS,
      KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
      KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
      KC_TRNS, KC_TRNS	, KC_TRNS	, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS

  ),
  [2] = LAYOUT(
      KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
      KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
      KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [3] = LAYOUT(
      KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
      KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
      KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
  )
};

//indicator variables
bool caps_is_active = false;
int mode = 5;

//to change color if the caps lock is on
void freather_set_color(bool capslock_is_on);
bool process_record_user(uint16_t keycode, keyrecord_t *record);



// Declaring a _freather_config_t struct that will store data
typedef struct _indicator_config_t {
    uint8_t h;
    uint8_t s;
    uint8_t v;
    bool enabled;
} indicator_config;

// Board memory layout
typedef struct _freather_config_t {
    indicator_config caps;
} freather_config;



// Check if the size of the reserved persistent memory is the same as the size of struct freather_config
_Static_assert(sizeof(indicator_config) == EECONFIG_USER_DATA_SIZE, "Mismatch in keyboard EECONFIG stored data");

// Declaring a new variable freather of type freather_config
freather_config freather;

// Declaring enums for VIA config menu
enum via_freather_enums {

    id_freather_indicator_enabled = 1,
    id_freather_indicator_color = 2

};

// Initializing persistent memory configuration: default values are declared and stored in PMEM
void eeconfig_init_user(void) {
    // Default values
    freather.caps.h       = 100;
    freather.caps.s       = 100;
    freather.caps.v       = 200;
    freather.caps.enabled = true;
    rgblight_set_effect_range(0,1);
    // Write default value to EEPROM now
    eeconfig_update_user_datablock(&freather);
}

// On Keyboard startup
void keyboard_post_init_user(void) {
    // Read custom menu variables from memory
    eeconfig_read_user_datablock(&freather);
}

// Handle the data received by the keyboard from the VIA menus
void freather_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_freather_indicator_enabled: {
            freather.caps.enabled = value_data[0];
            rgblight_sethsv_at(0,0,0,0);
            break;
        }
        case id_freather_indicator_color: {
            freather.caps.h = value_data[0];
            freather.caps.s = value_data[1];
            freather_set_color(true);
            break;
        }
    }
}

// Handle the data sent by the keyboard to the VIA menus
void freather_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_freather_indicator_enabled: {
            value_data[0] = freather.caps.enabled;
            break;
        }
        case id_freather_indicator_color: {
            value_data[0] = freather.caps.h;
            value_data[1] = freather.caps.s;
            break;
        }
    }
}

//save data to memory
void freather_config_save(void) {
    eeconfig_update_user_datablock(&freather);
}



void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                freather_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                freather_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                freather_config_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    *command_id = id_unhandled;
}


void freather_set_color(bool capslock_is_on)
{
  if(capslock_is_on == true && freather.caps.enabled == true)
  {
    rgblight_sethsv_range(freather.caps.h, freather.caps.s, freather.caps.v,0,1); //0 is the location of caps light indicator
  }
  else{
    rgblight_sethsv_at(0,0,0,0); //if is off, then turn off the caps lock indicator
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_CAPS:
      if (record->event.pressed && caps_is_active == false &&freather.caps.enabled == true) {  //turn on caps
        caps_is_active = true;
        mode = rgblight_get_mode();
        rgblight_mode(1);
        rgblight_sethsv_range(freather.caps.h, freather.caps.s, freather.caps.v, 0, 1); //needs a way to override the effect
        return true;
      }else if(record->event.pressed && caps_is_active == true ){
        rgblight_set_effect_range(0,1);
        rgblight_mode(mode);

        caps_is_active = false;
      }
    default:
      return true; // Process all other keycodes normally
  }
}
