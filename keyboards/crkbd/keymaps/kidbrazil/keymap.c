#include QMK_KEYBOARD_H
#include "enums.h"
#include "layer.h"
#include "lufa.h"

// [Init Variables] ----------------------------------------------------------//
// Oled timer similar to Drashna's
static uint32_t oled_timer = 0;
// Boolean to store LED state
bool user_led_enabled = true;
// Boolean to store the master LED clear so it only runs once.
bool master_oled_cleared = false;

// [Keymaps] -----------------------------------------------------------------//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	  [_QWERTY] = LAYOUT_split_3x6_3(
      KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,                                  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
      LSFT_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G,                          KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
      KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                                 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                          LGUI_T(KC_PGUP), MO(_NUM), KC_SPC,         KC_ENT, MO(_SYM), LALT_T(KC_PGDN)
    ),

	  [_NUM] = LAYOUT_split_3x6_3(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                                      KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
      LSFT_T(KC_TAB), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                         KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_F12, KC_NO,
      KC_LCTL, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,                               KC_PGUP, KC_PGDN, KC_HOME, KC_END, KC_F11, KC_NO,
                               LGUI_T(KC_PGUP), KC_TRNS, KC_SPC,         KC_ENT, KC_TRNS, LALT_T(KC_PGDN)
    ),

	  [_SYM] = LAYOUT_split_3x6_3(
      KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
      LSFT_T(KC_TAB), RGB_TOG, KC_MPLY, KC_MUTE, KC_VOLU, KC_VOLD,                        KC_MINS, KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV,
      KC_LCTL, KC_CALC, KC_MYCM, KC_MPRV, KC_MNXT, TG(_GAME),                             KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,
                                          LGUI_T(KC_PGUP), KC_TRNS, KC_SPC,       KC_ENT, KC_TRNS, LALT_T(KC_PGDN)
    ),

	  [_GAME] = LAYOUT_split_3x6_3(
      KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,                                   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
      KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,                                  KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO,
      KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_TRNS,                               KC_PGUP, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_NO,
                            KC_TAB, MO(_WEAPON), KC_SPC,              KC_ENT, KC_TRNS, KC_NO
      ),

	  [_WEAPON] = LAYOUT_split_3x6_3(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_LSFT, KC_A, KC_S, KC_D, KC_F,                               KC_6, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_LCTL, KC_Z, KC_X, KC_C, KC_V,                               KC_7, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EE_CLR,
                                KC_TRNS, KC_TAB, KC_TRNS,             KC_SPC, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

// [Post Init] --------------------------------------------------------------//
void keyboard_post_init_user(void) {
    // Set RGB to known state
    rgb_matrix_enable_noeeprom();
    rgb_matrix_set_color_all(RGB_GREEN);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    user_led_enabled = true;
}
// [Process User Input] ------------------------------------------------------//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      // Handle RGB Changes sans eeprom - necessary due to the layer dependent RGB color
      // changes in marrix_scan_user
      case RGB_TOG:
          if (record->event.pressed) {
              // Toggle matrix on key press
              user_led_enabled ? rgb_matrix_disable_noeeprom() : rgb_matrix_enable_noeeprom();
              // Toggle boolean flag
              user_led_enabled = !user_led_enabled;
          }
          return false;
      default:
          // Use process_record_keymap to reset timer on all other keypresses to awaken from idle.
          if (record->event.pressed) {
              #ifdef OLED_ENABLE
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

// [Matrix Scan] ------------------------------------------------------------//
void matrix_scan_user(void) {
     // Iddle timer to return to default layer if left on game layer
     if (timer_elapsed32(oled_timer) > 380000 && timer_elapsed32(oled_timer) < 479999) {
         // Reset layer in case it got left on _GAME
         // This prevents the issue where the master side sometimes wont switch off as expected
         // in the next step.
         if (get_highest_layer(layer_state) == _GAME) {
             layer_off(_GAME);
             layer_on(_QWERTY);
         }
         return;
     }
     // Timeout to turn off LEDs
     else if (timer_elapsed32(oled_timer) > 480000) {
         rgb_matrix_disable_noeeprom();
         return;
     }
     // Set RGB Matrix color based on layers
     if (user_led_enabled) {
         switch (get_highest_layer(layer_state)){
            case _GAME:
                rgb_matrix_set_color_all(RGB_PURPLE);
                break;
            case _NUM:
            case _SYM:
            case _QWERTY:
                rgb_matrix_set_color_all(RGB_GREEN);
                break;
            default:
                rgb_matrix_set_color_all(RGB_GREEN);
                break;

          }
     } else {
         rgb_matrix_disable_noeeprom();
         return;
     }
}
// [OLED Configuration] ------------------------------------------------------//
#ifdef OLED_ENABLE
// Init Oled and Rotate....
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master())
      return OLED_ROTATION_180;  // flips the display 180 to see it from my side
    return rotation;
}

// Read logo from font file
const char *read_logo(void);

// {OLED helpers} -----------------------------------------------//
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
bool oled_task_user(void) {
    // First time out switches to logo as first indication of iddle.
    if (timer_elapsed32(oled_timer) > 100000 && timer_elapsed32(oled_timer) < 479999) {
        // Render logo on both halves before full timeout
        if (is_keyboard_master() && !master_oled_cleared) {
            // Clear master OLED once so the logo renders properly
            oled_clear();
            master_oled_cleared = true;
        }
        render_logo();
        return false;
    }
    // Drashna style timeout for LED and OLED Roughly 8mins
    else if (timer_elapsed32(oled_timer) > 480000) {
        oled_off();
        rgb_matrix_disable_noeeprom();
        return false;
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
                if (is_keyboard_master()) {
                    render_master_oled();
                } else {
                    render_slave_oled();
                }
        }
    }
    return false;
}
#endif
