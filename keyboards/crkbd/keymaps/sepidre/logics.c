#include QMK_KEYBOARD_H

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
switch (keycode) {
    case ALT_TAB:
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                unregister_code(KC_LSHIFT);
                register_code(KC_LALT);
            }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
        break;
   case HIBER:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTRL(" "));
            SEND_STRING("hibernate");
            register_code(KC_ENT);
            return false;
        }
        break;
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
            #ifdef OLED_DRIVER_ENABLE
                oled_timer = timer_read32();
            #endif
            // Restore LEDs if they are enabled by user
            if (user_led_enabled) {
                rgb_matrix_enable_noeeprom();
            }
        }
  }
  return true;


}

//LEADER_EXTERNS();
