#include "keymap_german.h"
#include "led.c"

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUM, _SYM, _ADJ);
}

// [Post Init] --------------------------------------------------------------//
void keyboard_post_init_user(void) {
    // Set RGB to known state
    rgblight_disable_noeeprom();
    rgblight_setrgb(RGB_GREEN);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    user_led_enabled = true;
}
// [Process User Input] ------------------------------------------------------//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
switch (keycode) {
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
            user_led_enabled ? rgblight_disable_noeeprom() : rgblight_enable_noeeprom();
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
                rgblight_disable_noeeprom();
            }
        }
  }
  return true;
}
LEADER_EXTERNS();
void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        // for single key sequences
        // register_code(KC_LGUI);
        // register_code(KC_S);
        // unregister_code(KC_S);
        // unregister_code(KC_LGUI);
        SEQ_ONE_KEY(KC_C) {
            SEND_STRING(SS_LCTL("c"));
        }
        SEQ_ONE_KEY(KC_V) {
            SEND_STRING(SS_LCTL("v"));
        }
        SEQ_ONE_KEY(KC_X) {
            SEND_STRING(SS_LCTL("x"));
        }
        SEQ_ONE_KEY(KC_L) {
            SEND_STRING(SS_LGUI("l"));
        }
        SEQ_ONE_KEY(KC_E) {
            SEND_STRING(SS_LGUI("e"));
        }
        SEQ_ONE_KEY(KC_DOT) {
            SEND_STRING(SS_LGUI("."));
        }
        SEQ_ONE_KEY(KC_TAB) {
            register_code(KC_LALT);
            register_code(KC_TAB);
            unregister_code(KC_LALT);
            unregister_code(KC_TAB);
        }

        // for two-key sequences
        SEQ_TWO_KEYS(KC_C, KC_A) {
            SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
        }
        SEQ_TWO_KEYS(KC_T, KC_O) {
            // Start Toggle
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(DE_AE);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(DE_AE);
        }
        SEQ_TWO_KEYS(KC_L, KC_O) {
            // Start STRG ALT DEL
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_DEL);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_DEL);
        }
        SEQ_TWO_KEYS(KC_P, KC_S) {
            // Start Taskmgmnr
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_ESC);
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_ESC);
        }
        SEQ_TWO_KEYS(KC_C, KC_S) {
            // Start Greenshot
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_C);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_C);
        }
        SEQ_TWO_KEYS(KC_E, KC_O) {
            // Start Enpass
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_Z);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_Z);
        }
        SEQ_TWO_KEYS(KC_E, KC_U) {
            // Copy User Enpass
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_U);
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_U);
        }
        SEQ_TWO_KEYS(KC_E, KC_P) {
            // Copy PWD Enpass
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_P);
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_P);
        }
        SEQ_TWO_KEYS(KC_E, KC_T) {
            // Copy Token Enpass
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_T);
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);
            unregister_code(KC_T);
        }

        // for three-key sequences
        //SEQ_THREE_KEYS(KC_XXXX, KC_YYYY, KC_ZZZZ) {
            // INSERT CODE HERE: anything you can do in a macro
        //}

        // ..., the rest of your Leader Key definitions.
    }
    led_logics();
}
