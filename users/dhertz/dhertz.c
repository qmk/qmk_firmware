#include "dhertz.h"
#include "quantum.h"
#include "action.h"
// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}
__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

__attribute__ ((weak))
void action_function_keymap(keyrecord_t *record, uint8_t id, uint8_t opt) {}

// Call user matrix init, then call the keymap's init function
void matrix_init_user(void) {
  matrix_init_keymap();
}

// No global matrix scan code, so just run keymap's matix
// scan function
void matrix_scan_user(void) {
  matrix_scan_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case HSH_TLD:
                if (get_mods()&(MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))) {
                    SEND_STRING(SS_TAP(X_NONUS_BSLASH));
                } else {
                    SEND_STRING(SS_LALT("3"));
                }
                break;
            case CTRL_A:
                SEND_STRING(SS_LCTRL("a"));
                break;
            case CMD_ALT_C:
                SEND_STRING(SS_LGUI(SS_LALT("c")));
                break;
            case CMD_SFT_L:
                SEND_STRING(SS_LGUI("L"));
                break;
            default:
                return process_record_keymap(keycode, record);
        }
        return false;
    }
    return process_record_keymap(keycode, record);
}

const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
    [0]  = ACTION_FUNCTION_TAP(CMD_TAB_CMD),           // tap cmd tab or cmd
    [1]  = ACTION_FUNCTION_TAP(CMD_GRV_CMD),                    // grave tab
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case CMD_TAB_CMD:
            cmd_or_macro(record, KC_LGUI, SS_LGUI(SS_TAP(X_TAB)));
            break;
        case CMD_GRV_CMD:
            cmd_or_macro(record, KC_RGUI, SS_LGUI(SS_TAP(X_GRAVE)));
            break;
        default:
            action_function_keymap(record, id, opt);
    }
}

void cmd_or_macro(keyrecord_t *record, uint16_t kc_mod, char* macro) {
    if (record->event.pressed) {
        if (record->tap.count > 0 && !record->tap.interrupted) {
            if (record->tap.interrupted) {
                register_mods(MOD_BIT(kc_mod));
            }
        } else {
            register_mods(MOD_BIT(kc_mod));
        }
    } else {
        if (record->tap.count > 0 && !(record->tap.interrupted)) {
            send_string(macro);
            record->tap.count = 0;  // ad hoc: cancel tap
        } else {
            unregister_mods(MOD_BIT(kc_mod));
        }
    }
}

// Runs state check and changes underglow color and animation
// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
uint32_t layer_state_set_user (uint32_t state) {
  return layer_state_set_keymap (state);
}

void led_set_user(uint8_t usb_led) {
   led_set_keymap(usb_led);
}

