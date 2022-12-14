// Copyright 2022 Era James(@Era1112)
// SPDX - License - Identifier: GPL - 2.0 - or -later

#include QMK_KEYBOARD_H                     // Default statement

#define HSV_RETRO_CONSOLE   36, 150, 255    //HSV_YELLOW = 43, 255, 255


//----------- RGB Default Settings -----------//
//--------------------------------------------//
#ifdef RGBLIGHT_ENABLE

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_RETRO_CONSOLE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

#endif  // RGBLIGHT_ENABLE

//----------- Layer names -----------//
//-----------------------------------//
enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};


//----------- Sounds -----------//
//------------------------------//
#ifdef AUDIO_ENABLE

    float capslockToggleSound[][2] = SONG(STARTUP_SOUND);
    float dynamicBufferRecordSound[][2] = SONG(STARTUP_SOUND);
    float dynamicBufferFullSound[][2] = SONG(GOODBYE_SOUND);

#endif  // AUDIO_ENABLE


//----------- Called when dynamic buffer full -----------//
//-------------------------------------------------------//
void backlight_toggle(void) {
#ifdef AUDIO_ENABLE

    PLAY_SONG(dynamicBufferFullSound);

#endif  // AUDIO_ENABLE
}


//----------- Tapdance prelims -----------//
//----------------------------------------//
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_1_TAP,
    TD_1_HOLD,
    TD_2_TAP,
    TD_2_HOLD,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t* state);

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t* state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return TD_1_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        } else {
        return TD_1_HOLD;
        }
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->pressed) return TD_2_HOLD;
        else return TD_2_TAP;
    } else {
        return TD_UNKNOWN;
    }
}


//----------- 2tap capslock --------------//
//----------------------------------------//
void twoCapsLock_finished(tap_dance_state_t* state, void* user_data);
void twoCapsLock_reset(tap_dance_state_t* state, void* user_data);

static td_tap_t twoCapsLock_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void twoCapsLock_finished(tap_dance_state_t* state, void* user_data) {
    twoCapsLock_tap_state.state = cur_dance(state);
    switch (twoCapsLock_tap_state.state) {
    case TD_NONE: register_code(KC_LSFT); break;
    case TD_UNKNOWN: register_code(KC_LSFT); break;
    case TD_1_TAP: register_code(KC_LSFT); break;
    case TD_1_HOLD: register_code(KC_LSFT); break;
    case TD_2_TAP:
        register_code(KC_CAPS);
#ifdef AUDIO_ENABLE
        PLAY_SONG(capslockToggleSound);
#endif  // AUDIO_ENABLE
        break;
    case TD_2_HOLD: register_code(KC_LSFT); break;      
    }
}

void twoCapsLock_reset(tap_dance_state_t* state, void* user_data) {
    switch (twoCapsLock_tap_state.state) {
    case TD_UNKNOWN: unregister_code(KC_LSFT); break;
    case TD_NONE: unregister_code(KC_LSFT); break;
    case TD_1_TAP: unregister_code(KC_LSFT); break;
    case TD_1_HOLD: unregister_code(KC_LSFT); break;
    case TD_2_TAP:
        unregister_code(KC_CAPS);
#ifdef AUDIO_ENABLE
        PLAY_SONG(capslockToggleSound);
#endif  // AUDIO_ENABLE
        break;
    case TD_2_HOLD: unregister_code(KC_LSFT); break;
    }
    twoCapsLock_tap_state.state = TD_NONE;
}


//----------- Rotary Encoder --------------//
//----------------------------------------//
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (layer_state_is(_QWERTY)) {
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    }
    else if (layer_state_is(_LOWER)) {
        if (clockwise) {
            tap_code16(S(KC_F3));
        } else {
            tap_code(KC_F3);
        }
    } else if (layer_state_is(_RAISE)) {
        if (clockwise) {
            tap_code16(C(KC_Z));
        } else {
            tap_code16(C(KC_Y));
        }
    }
    return false;
}

//----------- Custom keycodes ------------//
//----------------------------------------//
enum {
    TD_2_CAPSLOCK
};

enum custom_keycodes {
    CU_BLNKON = SAFE_RANGE,
    CU_BLNKOFF,
    CU_RGBON,
    CU_RGBOFF,
    ENC_MODE
};

static bool blinky = false;         // Track blinky behavior on/off for keycode

tap_dance_action_t tap_dance_actions[] = {
    [TD_2_CAPSLOCK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, twoCapsLock_finished, twoCapsLock_reset)
};


//----------- Intercepts and overrides ------------//
//-------------------------------------=-----------//
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    // Turn RGB LEDs off
    case CU_RGBOFF:

        // If pressed
        if (record->event.pressed) {
            rgblight_sethsv_noeeprom(HSV_OFF);   
            return true;

        // If released
        } else {
            return true;
        }

    // Turn RGB LEDs on
    case CU_RGBON:

        // If pressed
        if (record->event.pressed) {
            rgblight_sethsv_noeeprom(HSV_RETRO_CONSOLE);  
            return true;

        // If released
        } else {
            return true;
        }

    // Turn blinky LEDs off
    case CU_BLNKOFF:

        // If pressed
        if (record->event.pressed) {
            blinky = false;
            return true;

        // If released
        } else {
            return true;
        }

    // Turn blinky LEDs on
    case CU_BLNKON:

        // If pressed
        if (record->event.pressed) {
            blinky = true;
            return true;

        // If released
        } else {
            return true;
        }

    // Sound when Dynamic recording started
    case QK_DYNAMIC_MACRO_RECORD_START_1:

        // If pressed
        if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(dynamicBufferRecordSound);
        #endif  // AUDIO_ENABLE
            return true; // Let QMK send the press/release events

        // If released
        } else {
            return true; // Let QMK send the press/release events
        }

    // Sound when Dynamic recording stopped
    case QK_DYNAMIC_MACRO_RECORD_STOP:

        // If pressed
        if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(dynamicBufferFullSound); 
        #endif  // AUDIO_ENABLE
            return true; // Let QMK send the enter press/release events

        // If released
        } else {
            return true; // Let QMK send the press/release events
        }

    // Encoder Click
    case ENC_MODE:
        if (record->event.pressed) {
            if (layer_state_is(_QWERTY)) {
                tap_code(KC_BTN1);
                return false;
            } else if (layer_state_is(_LOWER)) {
                return false;
            } else if (layer_state_is(_RAISE)) {
                return false;
            }
        }


    // Adds blinks if blinky is on
    default:
        if (blinky == true) {
            rgblight_toggle();
        }

    return true; // Process all other keycodes normally

    }
}


//----------- Keymap ------------//
//-------------------------------//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // main layer
    [_QWERTY] = LAYOUT_ortho_5x12 (
        // (Non-disabled top row), uncomment and replace if you want preonic-style instead of planck-style
        // KC_MINS,            KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,           KC_7,           KC_8,       KC_9,       KC_0,       KC_EQL,
		KC_NO,              KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_TAB,             KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,       KC_O,       KC_P,       KC_BSPC,
        KC_ESC,             KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,           KC_J,           KC_K,       KC_L,       KC_SCLN,    KC_ENT,
        KC_LSFT,            KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMM,    KC_DOT,     KC_SLSH,    TD(TD_2_CAPSLOCK),
        ENC_MODE,           KC_LCTL,        KC_LGUI,        KC_LALT,        MO(_LOWER),     KC_SPC,         KC_SPC,         MO(_RAISE),     KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT
    ),

    // lower key
    [_LOWER] = LAYOUT_ortho_5x12 (
        DM_PLY1,            DM_REC1,        DM_RSTP,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,            KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,           KC_7,               KC_8,           KC_9,       KC_0,       KC_DEL,
        KC_BSPC,            KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_QUOT,            KC_GRV,         KC_LCBR,    KC_RCBR,    KC_TRNS,
        KC_TRNS,            KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_MINS,            KC_EQL,         KC_TRNS,    KC_BSLS,    KC_TRNS,
        KC_TRNS,            KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        MO(_ADJUST),        KC_HOME,        KC_PGDN,    KC_PGUP,    KC_END
    ),

    // raise key
    [_RAISE] = LAYOUT_ortho_5x12 (
        DM_PLY1,            DM_REC1,        DM_RSTP,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,            KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_CIRC,        KC_AMPR,            KC_ASTR,        KC_LPRN,    KC_RPRN,    KC_DEL,
        KC_DEL,             KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_DQUO,            KC_TILD,        KC_LBRC,    KC_RBRC,    KC_TRNS,
        KC_TRNS,            KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_UNDS,            KC_PLUS	,       KC_TRNS,    KC_PIPE,    KC_TRNS,
        KC_TRNS,            KC_TRNS,        KC_TRNS,        KC_TRNS,        MO(_ADJUST),    KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_MUTE,        KC_VOLD,    KC_VOLU,    KC_F24
    ),

    // hardware adjust layer, raise+lower
    [_ADJUST] = LAYOUT_ortho_5x12 (
        AU_ON,              AU_OFF,          CK_ON,           CK_OFF,          KC_NO,           KC_NO,           KC_NO,       KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_NO,
																																															
        CU_RGBON,           CU_RGBOFF,       CU_BLNKON,       CU_BLNKOFF,      KC_NO,           KC_NO,           KC_NO,       KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_NO,
		KC_NO,              KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,       KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,              KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,       KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,              KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,       KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_NO
    )
    
};
