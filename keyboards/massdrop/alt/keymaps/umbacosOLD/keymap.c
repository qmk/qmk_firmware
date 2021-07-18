#include QMK_KEYBOARD_H

void usage(void) {
    SEND_STRING("Usage:\n" \
          "Double tap q to get €\n" \
          "Double or triple tap vowels to get accents (eg. à, á, è, é, ...) \n" \
          "Double tap PageUp/PageDn to get Home/End\n" \
          "Press FN+Tab to work on Windows (requires Wincompose installed)\n" \
          "Press FN+CapsLock to work on Mac (requires Unicode Hex Input as keyboard)\n" \
          "To disable all above feature (eg. during gaming) press FN+LeftShift\n" \
          "To re-enable all above features, just press FN once\n" \
          "RGB Light press FN and:\n" \
          "   Q/A rotate effect\n" \
          "   W/S intensity\n" \
          "   E/D speed\n" \
          "   R/F hue\n" \
          "   T/G saturation\n" \
          "   Z   toggle on/off\n" \
          "Multimedia press FN and:\n" \
          "   End   Mute\n" \
          "   PgUp/PgDn  volume +/-\n" \
          "*** Press FN+H for this help\n");
}

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    UC_USAGE,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

const uint32_t PROGMEM GRAVE_UNICODE[] = {
  [KC_A]  = 0xE0,  // à
  [KC_E]  = 0xE8,  // è
  [KC_I]  = 0xEC,  // ì
  [KC_O]  = 0xF2,  // ò
  [KC_U]  = 0xF9,  // ù
  [KC_Q] = 0x20AC, // €
};

#define KC_UPPER_CASE (MODS_SHIFT << 5) // offset of unicode for upper case

void grave_accent (qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
  [KC_A]  = ACTION_TAP_DANCE_FN (grave_accent),
  [KC_E]  = ACTION_TAP_DANCE_FN (grave_accent),
  [KC_I]  = ACTION_TAP_DANCE_FN (grave_accent),
  [KC_O]  = ACTION_TAP_DANCE_FN (grave_accent),
  [KC_U]  = ACTION_TAP_DANCE_FN (grave_accent),
  [KC_Q]  = ACTION_TAP_DANCE_FN (grave_accent),
  [KC_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_HOME),
  [KC_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_END),
};

void tap_unicode(uint16_t keycode) {
  unicode_input_start();
  register_hex(keycode);
  unicode_input_finish();
}

void grave_accent (qk_tap_dance_state_t *state, void *user_data) {

  uint8_t keycode = state->keycode - QK_TAP_DANCE; // remove 0x5700 QK_TAP_DANCE enum base

  if (state->count == 1)   // normal character
        tap_code(keycode);
  else                     // tap dance
        if (state->count == 3)
          tap_unicode(GRAVE_UNICODE[keycode] - KC_UPPER_CASE);
}

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

keymap_config_t keymap_config;
#define TAPPING_TOGGLE 1
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(  // editing layer
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,  \
        KC_TAB,  TD(KC_Q),    KC_W,TD(KC_E),KC_R,    KC_T,    KC_Y,TD(KC_U),TD(KC_I),TD(KC_O),    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, \
        KC_ESC, TD(KC_A),KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  TD(KC_PGUP), \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   TD(KC_PGDN), \
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RALT, MO(2),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT_65_ansi_blocker(  // gaming layer
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_MUTE, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_VOLU, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_VOLD, \
        KC_LCTL, KC_LALT, KC_LALT,                            KC_SPC,                             KC_RALT, TO(0),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [2] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, KC_END, \
        UNICODE_MODE_WINC	,  RGB_MOD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_MUTE, \
        UNICODE_MODE_OSX	,  RGB_RMOD,RGB_VAD, RGB_SPD, RGB_HUD, RGB_SAD, UC_USAGE, _______, _______, _______, _______, _______,          _______, KC_VOLU, \
        TO(1),  RGB_TOG, _______, _______, _______, MD_BOOT, TG_NKRO, DBG_TOG, _______, _______, _______, _______,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  rgblight_decrease_sat();
  rgblight_decrease_sat();
  rgblight_decrease_sat();
  rgblight_decrease_speed();
  rgblight_decrease_speed();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;

            case UC_USAGE:
                if (record->event.pressed)
                  usage();
                return false;

        default:
            return true; //Process all other keycodes normally
    }
}
