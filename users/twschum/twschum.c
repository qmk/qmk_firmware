#include "twschum.h"

static bool rgb_layers_enabled = true;
static bool rgb_L0_enabled = false;

// state for the great state machine of custom actions!
#define TIMEOUT_DELAY 150 // ms
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
                if (get_mods() & MODS_CTRL_MASK) {
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

/* Return True to continue processing keycode, false to stop further processing */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
        case SALT_CMD:
            if (!record->event.pressed) {
                SEND_STRING("sudo salt \\* cmd.run ''"SS_TAP(X_LEFT));
            }
            return false;
        case LESS_PD:
            if (!record->event.pressed) {
                SEND_STRING("sudo less /pipedream/cache/");
            }
            return false;
        default:
            if (record->event.pressed) {
                return tap_ctrl_other_pressed();
            }
    }
    return true;
}

void matrix_init_user(void) {
    // called once on board init
    rgblight_enable();
}

void suspend_power_down_user(void) {
    // TODO shut off backlighting
}

void suspend_wakeup_init_user(void) {
    // TODO turn on backlighting
}

// add to quantum/rgblight_list.h
#define  HSV_OFF          0,    0,    0
/* Use RGB underglow to indicate layer
 * https://docs.qmk.fm/reference/customizing-functionality
 */
uint32_t layer_state_set_user(uint32_t state) {
    if (!rgb_layers_enabled) {
        return state;
    }
    switch (biton32(state)) {
    case L_Base:
        if (rgb_L0_enabled) {
            rgblight_sethsv_noeeprom(HSV_WHITE);
        }
        else {
            rgblight_sethsv_noeeprom(HSV_OFF);
        }
        break;
    case L_Fn:
        rgblight_sethsv_noeeprom(HSV_GREEN);
        break;
    case L_Nav:
        rgblight_sethsv_noeeprom(HSV_AZURE);
        break;
    case L_Num:
        rgblight_sethsv_noeeprom(HSV_GOLD);
        break;
    case L_Cfg:
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
    case L_None:
        rgblight_sethsv_noeeprom(HSV_WHITE);
        break;
    }
    return state;
}
