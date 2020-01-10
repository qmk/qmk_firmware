#include QMK_KEYBOARD_H

// [Init Variables] ----------------------------------------------------------//
extern uint8_t is_master;
// Oled timer similar to Drashna's
static uint32_t oled_timer = 0;
// Boolean to store LED state
bool user_led_enabled = true;
// Boolean to store the master LED clear so it only runs once.
bool master_oled_cleared = false;

// [CRKBD layers Init] -------------------------------------------------------//
enum crkbd_layers {
    _QWERTY,
    _NUM,
    _SYM,
    _GAME,
    _WEAPON
};

// [Keymaps] -----------------------------------------------------------------//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	  [_QWERTY] = LAYOUT(
      KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,                                  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
      LSFT_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G,                          KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
      KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                                 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                          LGUI_T(KC_PGUP), MO(_NUM), KC_SPC,         KC_ENT, MO(_SYM), LALT_T(KC_PGDN)
    ),

	  [_NUM] = LAYOUT(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                                      KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
      LSFT_T(KC_TAB), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                         KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_F12, KC_NO,
      KC_LCTL, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                               KC_PGUP, KC_PGDN, KC_HOME, KC_END, KC_F11, KC_NO,
                               LGUI_T(KC_PGUP), KC_TRNS, KC_SPC,         KC_ENT, KC_TRNS, LALT_T(KC_PGDN)
    ),

	  [_SYM] = LAYOUT(
      KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
      LSFT_T(KC_TAB), RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,                        KC_MINS, KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV,
      KC_LCTL, RGB_VAD, RGB_RMOD, RGB_HUD, RGB_SAD, TG(_GAME),                            KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,
                                          LGUI_T(KC_PGUP), KC_TRNS, KC_SPC,       KC_ENT, KC_TRNS, LALT_T(KC_PGDN)
    ),

	  [_GAME] = LAYOUT(
      KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,                                   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
      KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,                                  KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO,
      KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_TRNS,                               KC_PGUP, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_NO,
                            KC_TAB, MO(_WEAPON), KC_SPC,              KC_ENT, KC_TRNS, KC_NO
      ),

	  [_WEAPON] = LAYOUT(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_LSFT, KC_A, KC_S, KC_D, KC_F,                               KC_6, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_LCTL, KC_Z, KC_X, KC_C, KC_V,                               KC_7, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TAB, KC_TRNS,             KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

// [Post Init] --------------------------------------------------------------//
void keyboard_post_init_user(void) {
    // Set RGB to known state
    rgb_matrix_enable_noeeprom();
    rgb_matrix_set_color_all(RGB_GREEN);
    user_led_enabled = true;

}
// [Process User Input] ------------------------------------------------------//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case RGB_TOG:
        if (record->event.pressed) {
            // Toggle matrix on key press
            user_led_enabled ? rgb_matrix_disable_noeeprom() : rgb_matrix_enable_noeeprom();
        } else {
            // Flip User_led_enabled variable on key release
            user_led_enabled = !user_led_enabled;
        }
        return false; // Skip all further processing of this key
      default:
          // Use process_record_keymap to reset timer on all other keypresses
          if (record->event.pressed) {
              #ifdef OLED_DRIVER_ENABLE
                  oled_timer = timer_read32();
              #endif
              // Restore LEDs if they are enabled by user
              if (user_led_enabled) {
                  rgb_matrix_enable_noeeprom();
              }
          }
          return true;
    }
}

// [OLED Configuration] ------------------------------------------------------//
#ifdef OLED_DRIVER_ENABLE

// Init Oled and Rotate....
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!has_usb())
      return OLED_ROTATION_180;  // flips the display 180 to see it from my side
    return rotation;
}

// Read logo from font file
const char *read_logo(void);

// {OLED helpers} -----------------------------------------------//

// Render Blank Space
void render_space(void) {
    oled_write_ln_P(PSTR("     "), false);
}

// Render separator lines for oled display
void render_separator(void) {
    switch (get_highest_layer(layer_state)){
        case _GAME:
        case _WEAPON:
            oled_write_ln_P(PSTR("===================="), false);
            break;
        default:
            oled_write_ln_P(PSTR("++++++++++++++++++++"), false);
    }
}

// Render current layer state
void render_layer_state(void){
	// If you want to change the display of OLED, you need to change here
    switch (get_highest_layer(layer_state)){
        case _QWERTY:
            oled_write_ln_P(PSTR("| MODE | QWRTY     ]"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("| MODE | NUMBERS   ]"), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("| MODE | SYMBOLS   ]"), false);
            break;
        case _GAME:
            oled_write_ln_P(PSTR("|    G  A  M  E    ]"), false);
            break;
        case _WEAPON:
            oled_write_ln_P(PSTR("| W  E  A  P  O  N ]"), false);
            break;
        default:
            oled_write_ln_P(PSTR("| MODE | UNDEF     ]"), false);
    }
}

// Render USB State
void render_usb_state(void) {
    switch (USB_DeviceState) {
      case DEVICE_STATE_Unattached:
			    oled_write_ln_P(PSTR("| USB  | FREE      ]"), false);
          break;
      case DEVICE_STATE_Suspended:
          oled_write_ln_P(PSTR("| USB  | SLEEP     ]"), false);
          break;
      case DEVICE_STATE_Configured:
          oled_write_ln_P(PSTR("| USB  | READY     ]"), false);
          break;
      case DEVICE_STATE_Powered:
          oled_write_ln_P(PSTR("| USB  | PWRD      ]"), false);
          break;
      case DEVICE_STATE_Default:
          oled_write_ln_P(PSTR("| USB  | DFLT      ]"), false);
          break;
      case DEVICE_STATE_Addressed:
          oled_write_ln_P(PSTR("| USB  | ADDRS     ]"), false);
          break;
      default:
          oled_write_ln_P(PSTR("| USB  | INVALID   ]"), false);
    }
}

// Render Logo
void render_logo(void) {
    oled_write(read_logo(), false);
}

// Master OLED Screen (Left Hand )
void render_master_oled(void) {
    // Switch display based on Layer
    switch (get_highest_layer(layer_state)){
        case _GAME:
            render_separator();
            render_layer_state();
            render_separator();
            render_separator();
            break;
        case _WEAPON:
            render_separator();
            render_separator();
            render_layer_state();
            render_separator();
            break;
        default:
            render_separator();
            render_layer_state();
            render_separator();
            render_usb_state();
    }
}

// Slave OLED scren (Right Hand)
void render_slave_oled(void) {
    render_logo();
}

// {OLED Task} -----------------------------------------------//
void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 80000 && timer_elapsed32(oled_timer) < 479999) {
        // Render logo on both halves before full timeout
        if (is_master && !master_oled_cleared) {
            // Clear master OLED once so the logo renders properly
            oled_clear();
            master_oled_cleared = true;
        }
        render_logo();
        return;
    }
    // Drashna style timeout for LED and OLED Roughly 8mins
    else if (timer_elapsed32(oled_timer) > 480000) {
        oled_off();
        rgb_matrix_disable_noeeprom();
        return;
    }
    else {
        oled_on();
        // Reset OLED Clear flag
        master_oled_cleared = false;
        // Show logo when USB dormant
        switch (USB_DeviceState) {
            case DEVICE_STATE_Unattached:
            case DEVICE_STATE_Powered:
            case DEVICE_STATE_Suspended:
                render_logo();
                break;
            default:
                if (is_master) {
                    render_master_oled();
                } else {
                    render_slave_oled();
                }
        }
    }
}
#endif
