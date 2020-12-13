#include "twschum.h"

#ifdef TWSCHUM_TAPPING_CTRL_PREFIX
// state for the great state machine of custom actions!
#define TIMEOUT_DELAY 200 // ms
static uint16_t idle_timer;
static bool timeout_is_active = false;

static bool ctrl_shortcuts_enabled_g = false;
//static bool B_down = 0; // TODO just use top bit from count
//static int8_t B_count = 0;

#define N_TAPPING_CTRL_KEYS 2
static struct Tapping_ctrl_key_t special_keys_g[N_TAPPING_CTRL_KEYS] = {
    {false, 0, KC_B}, {false, 0, KC_A}
};

static inline void start_idle_timer(void) {
    idle_timer = timer_read();
    timeout_is_active = true;
}
static inline void clear_state_after_idle_timeout(void) {
    idle_timer = 0;
    timeout_is_active = false;

    // send timed out plain keys from tapping ctrl mod
    for (int i = 0; i < N_TAPPING_CTRL_KEYS; ++i) {
        struct Tapping_ctrl_key_t* key = special_keys_g + i;
        repeat_send_keys(key->count, key->keycode);
        key->count = 0;
    }
}

inline void matrix_scan_user(void) {
    if (timeout_is_active && timer_elapsed(idle_timer) > TIMEOUT_DELAY) {
        clear_state_after_idle_timeout();
    }
}

static inline bool tap_ctrl_event(struct Tapping_ctrl_key_t* key, keyrecord_t* record) {
    if (!ctrl_shortcuts_enabled_g) {
        // normal operation, just send the plain keycode
        if (record->event.pressed) {
            register_code(key->keycode);
        }
        else {
            unregister_code(key->keycode);
        }
        return false;
    }
    key->down = record->event.pressed;
    // increment count and reset timer when key pressed
    // start the timeout when released
    if (key->down) {
        ++(key->count);
        timeout_is_active = false;
        idle_timer = 0;
    }
    else {
        if (key->count) {
            start_idle_timer();
        }
    }
    return false;
}

static inline bool tap_ctrl_other_pressed(void) {
    for (int i = 0; i < N_TAPPING_CTRL_KEYS; ++i) {
        struct Tapping_ctrl_key_t* key = special_keys_g + i;
        if (key->count) {
            if (key->down) {
                // another key has been pressed while the leader key is down,
                // so send number of ctrl-KEY combos before the other key
                repeat_send_keys(key->count, KC_LCTL, key->keycode);
                key->count = 0;
            }
            else {
                // another key pressed after leader key released,
                // need to send the plain keycode plus potential mods
                if (get_mods() & MOD_MASK_CTRL) {
                    // make sure to send a shift if prssed
                    repeat_send_keys(key->count, KC_RSHIFT, key->keycode);
                }
                else {
                    repeat_send_keys(key->count, key->keycode);
                }
                key->count = 0;
            }
            return true; // will send the other keycode
        }
    }
    return true; // safe default
}
#endif /* TWSCHUM_TAPPING_CTRL_PREFIX */


/* Use RGB underglow to indicate layer
 * https://docs.qmk.fm/reference/customizing-functionality
 */
// add to quantum/rgblight_list.h
#ifdef RGBLIGHT_ENABLE
static bool rgb_layers_enabled = true;
static bool rgb_L0_enabled = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    if (!rgb_layers_enabled) {
        return state;
    }
    switch (get_highest_layer(state)) {
    case _Base:
        if (rgb_L0_enabled) {
            rgblight_sethsv_noeeprom(_Base_HSV_ON);
        }
        else {
            rgblight_sethsv_noeeprom(_Base_HSV_OFF);
        }
        break;
    case _Vim:
        rgblight_sethsv_noeeprom(_Vim_HSV);
        break;
    case _Fn:
        rgblight_sethsv_noeeprom(_Fn_HSV);
        break;
    case _Nav:
        rgblight_sethsv_noeeprom(_Nav_HSV);
        break;
    case _Num:
        rgblight_sethsv_noeeprom(_Num_HSV);
        break;
    case _Cfg:
        rgblight_sethsv_noeeprom(_Cfg_HSV);
        break;
    case _None:
        rgblight_sethsv_noeeprom(_None_HSV);
        break;
    }
    return state;
}
#endif /* RGBLIGHT_ENABLE */

/* process_record_vimlayer: handles the VIM_ keycodes from xtonhasvim's vim
 * emulation layer
 * add process_record_keymap to allow specific keymap to still add keys
 * Makes the callstack look like:
 * process_record_
 *  _quantum
 *    _kb
 *      _user
 *        _keymap
 *        _vimlayer
 */
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

/* Return True to continue processing keycode, false to stop further processing
 * process_record_keymap to be call by process_record_user in the vim addon */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  /* keymap gets first whack, then vimlayer */
  if(!process_record_keymap(keycode, record)) return false;
  if(!process_record_vimlayer(keycode, record)) return false;

    switch (keycode) {
        /* KC_MAKE is a keycode to be used with any keymap
         * Outputs `make <keyboard>:<keymap>`
         * Holding shift will add the appropriate flashing command (:dfu,
         *   :teensy, :avrdude, :dfu-util) for a majority of keyboards.
         * Holding control will add some commands that will speed up compiling
         *   time by processing multiple files at once
         * For the boards that lack a shift key, or that you want to always
         *   attempt the flashing part, you can add FLASH_BOOTLOADER = yes to the
         *   rules.mk of that keymap.
         */
        case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            uint8_t temp_osm = get_oneshot_mods();
            clear_mods(); clear_oneshot_mods();
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
        #ifndef FLASH_BOOTLOADER
            if ( (temp_mod | temp_osm) & MOD_MASK_SHIFT ) {
                SEND_STRING(":flash");
            }
        #endif
            if ( (temp_mod | temp_osm) & MOD_MASK_CTRL) {
                SEND_STRING(" -j8 --output-sync");
            }
            SEND_STRING(SS_TAP(X_ENTER));
            set_mods(temp_mod);
        }
        break;

        #ifdef RGBLIGHT_ENABLE
        case TG_LAYER_RGB:
            if (record->event.pressed) {
                rgb_layers_enabled = !rgb_layers_enabled;
            }
            return false;
        case TG_L0_RGB:
            if (record->event.pressed) {
                rgb_L0_enabled = !rgb_L0_enabled;
            }
            return false;
        #endif

        case SALT_CMD:
            if (!record->event.pressed) {
                SEND_STRING(SALT_CMD_MACRO);
            }
            return false;
        case LESS_PD:
            if (!record->event.pressed) {
                SEND_STRING(LESS_PD_MACRO);
            }
            return false;
        case CODE_PASTE:
            if (!record->event.pressed) {
                SEND_STRING(CODE_PASTE_MACRO);
            }
            return false;

        #ifdef TWSCHUM_TAPPING_CTRL_PREFIX
        case EN_CTRL_SHORTCUTS:
            if (record->event.pressed) {
                ctrl_shortcuts_enabled_g = !ctrl_shortcuts_enabled_g;
                start_idle_timer(); // need to clear out state in some cases
            }
            return false;
        case CTRL_A:
            return tap_ctrl_event(&special_keys_g[1], record);
        case CTRL_B:
            return tap_ctrl_event(&special_keys_g[0], record);
        default:
            if (record->event.pressed) {
                return tap_ctrl_other_pressed();
            }
        #endif
    }
    return true;
}

#ifdef RGBLIGHT_ENABLE
void matrix_init_user(void) {
    // called once on board init
    rgblight_enable();
}
#endif

void suspend_power_down_user(void) {
    // TODO shut off backlighting
}

void suspend_wakeup_init_user(void) {
    // TODO turn on backlighting
}
