#include QMK_KEYBOARD_H
#include "secrets.c"

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
  }
  return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();


/*
    SEQ_TWO_KEYS(KC_L, KC_L) { // WinLogin
        SEND_STRING((SS_LCTRL(SS_LALT(X_DELETE))) SS_DELAY(1000));
        send_string(login);
    }
    SEQ_ONE_KEY(KC_L) { // Windows HEllo
        send_string(login);
        SEND_STRING(SS_TAP(X_ENTER));
    }*/
    SEQ_ONE_KEY(KC_Z) { // Invoke Password Manager
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(DE_Z);
        unregister_code(DE_Z);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
    }
    SEQ_ONE_KEY(KC_C) { // Windows screenshot
        SEND_STRING(SS_LCTRL(SS_LALT("C")));
    }
  }
}

/*
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    // for basic strings
    case HUNT_ANTIDODE: {
        if (record->event.pressed) {
            SEND_STRING("YOUR_STRING_HERE"); // REPLACE with what you want your macro to be
            //SEND_STRING(SS_TAP(X_PSCREEN) SS_LGUI("r"));
            //_delay_ms(500);
            //SEND_STRING("mspaint" SS_TAP(X_ENTER));
            //_delay_ms(500);
            //SEND_STRING(SS_LCTRL("v"));
            return false;
        }
    }


    // for more complex macros (want to add modifiers, etc.)
    case HUNT_HEAL_FAST: {
      if (record->event.pressed) {
        return MACRO(
          // INSERT CODE HERE for your macro. See https://docs.qmk.fm/macros.html
        );
      }
    }
    case HUNT_HEAL_SLOW: {
      if (record->event.pressed) {
        return MACRO(
          // INSERT CODE HERE for your macro. See https://docs.qmk.fm/macros.html
        );
      }
    }
  }
  return MACRO_NONE;
};


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
            tap_code(KC_VOLU);
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
            tap_code(KC_VOLD);
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
#endif
*/
