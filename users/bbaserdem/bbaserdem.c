#include "bbaserdem.h"
#include "action_layer.h"

// Enable lock functionality
bool lock_flag = false;

/*---------------*\
|*-----MOUSE-----*|
\*---------------*/
#ifdef MOUSEKEY_ENABLE
#include "mousekey.h"
#endif

/*-------------*\
|*-----RGB-----*|
\*-------------*/
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

// Let's split eh slave refresh
#ifdef SPLIT_KEYBOARD
#include "split_flags.h"
#endif

/*-----------------*\
|*-----SECRETS-----*|
\*-----------------*/
// Enabled by adding a non-tracked secrets.h to this dir.
#if (__has_include("secret.h")) && !defined(NO_SECRETS))
#include "secret.h"
else
static const char * const secret[] = {
  "R52uPWNmih2EmaLko8OKIFGhX",
  "szZ7gUcdPJlGpvCcqP9NXNO4z",
  "Mgo0Lws6YqxWvWWcNRB30FCt0",
  "hHgvEEwSi3FVn1ecz7eySMW8J"
};
#endif

/*---------------*\
|*-----MUSIC-----*|
\*---------------*/
#ifdef AUDIO_ENABLE
float tone_game[][2]    = SONG(ZELDA_PUZZLE);
float tone_return[][2]  = SONG(ZELDA_TREASURE);
float tone_linux[][2]   = SONG(UNICODE_LINUX);
float tone_windows[][2] = SONG(UNICODE_WINDOWS);
#endif

/*-------------------*\
|*-----TAP-DANCE-----*|
\*-------------------*/
void d_num_gam_dn (qk_tap_dance_state_t *state, void *user_data) {
  lock_flag = false;
  if (state->count == 1) {
    layer_on  (_NU);
  } else if (state->count == 2) {
    layer_off (_NU);
    layer_on  (_GA);
    lock_flag = true;
  } else {
    layer_off (_GA);
    lock_flag = false;
  }
}
void d_num_gam_up (qk_tap_dance_state_t *state, void *user_data) {
  if ( lock_flag ) {
    lock_flag = false;
  } else {
      layer_off (_NU);
      layer_off (_GA);
    }
  }
}
void d_set_mou_dn (qk_tap_dance_state_t *state, void *user_data) {
  lock_flag = false;
  if (state->count == 1) {
    layer_on  (_SE);
  } else if (state->count == 2) {
    layer_off (_SE);
    layer_on  (_MO);
  } else {
    layer_off (_MO);
  }
}
void d_set_mou_up (qk_tap_dance_state_t *state, void *user_data) {
  if ( lock_flag ) {
    lock_flag = false;
  } else {
    if (state->count == 1) {
      layer_off (_SE);
    } else if (state->count == 2) {
      layer_off (_MO);
    }
  }
}
qk_tap_dance_action_t tap_dance_actions[] = {
  [NUG] = ACTION_TAP_DANCE_FN_ADVANCED (d_num_gam_dn,NULL,d_num_gam_up)
  [SEM] = ACTION_TAP_DANCE_FN_ADVANCED (d_set_mou_dn,NULL,d_set_mou_up)
};
#endif

/* In keymaps, instead of writing _user functions, write _keymap functions
 * The __attribute__((weak)) allows for empty definitions here, and during
 * compilation, if these functions are defined elsewhere, they are written
 * over. This allows to include custom code from keymaps in the generic code
 * in this file.
 */
__attribute__ ((weak)) void matrix_init_keymap(void) { }
__attribute__ ((weak)) void matrix_scan_keymap(void) { }
__attribute__ ((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {return true;}
__attribute__ ((weak)) uint32_t layer_state_set_keymap (uint32_t state) {return state;}
__attribute__ ((weak)) void led_set_keymap(uint8_t usb_led) { }

// Ideally layer switching stuff would go here, but doesn't work consistently
// across keyboards for me; thus I do explicit layer checking in matrix-scan
uint32_t layer_state_set_user(uint32_t state) {
    state = layer_state_set_keymap (state);
    return state;
}

/* ----------------------- *\
 * -----RGB Functions----- *
\* ----------------------- */
#ifdef RGBLIGHT_ENABLE
// Storage variables
extern  rgblight_config_t rgblight_config;
bool    base_sta;   // Keeps track if in saveable state
bool    base_tog;   // Whether base state is active or not
int     base_hue;   // Hue value of base state
int     base_sat;   // Saturation value of base state
int     base_val;   // Brightness value of base state
uint8_t base_mod;   // Animation mode of the base state
// Save the current state of the rgb mode
void rgblight_saveBase(void) {
    base_hue = rgblight_config.hue;
    base_sat = rgblight_config.sat;
    base_val = rgblight_config.val;
    base_mod = rgblight_config.mode;
    base_tog = rgblight_config.enable;
    base_sta = false;   // If saving, that means base layer is being left
}
// Load the base state back
void rgblight_loadBase(void) {
    // Don't do anything if not enabled
    if ( !base_sta ) {
        if ( base_tog ) {
            rgblight_enable();
            rgblight_mode( base_mod );
            rgblight_sethsv( base_hue, base_sat, base_val );
            rgblight_enable();
        } else {
            rgblight_disable();
        }
    }
    // Mark that base is loaded, and to be saved before leaving
    base_sta = true;
}
// Set to plain HSV color
void rgblight_colorStatic( int hu, int sa, int va ) {
    // First, it must be enabled or color change is not written
    rgblight_enable();
    rgblight_mode(1);
    rgblight_sethsv(hu,sa,va);
    rgblight_enable();
}
// Set RGBLIGHT state depending on layer
void rgblight_change( uint8_t this_layer ) {
    // Save state, if saving is requested
    if ( base_sta ) {
        rgblight_saveBase();
    }
    // Change RGB light
    switch ( this_layer ) {
        case _BA:   // Load base layer
            rgblight_loadBase();
            break;
        case _GA:   // Do purple for game
            rgblight_colorStatic(285,255,255);
            break;
        case _NU:   // Do azure for number
            rgblight_colorStatic(186,200,255);
            break;
        case _SE:   // Do red for settings
            rgblight_colorStatic( 16,255,255);
            break;
        case _MO:   // Do green for mouse
            rgblight_colorStatic(120,255,255);
            break;
        case _MU:   // Do yellow for music
            rgblight_colorStatic( 60,255,255);
            break;
        default:    // Something went wrong: RED
            rgblight_colorStatic(  0,255,255);
            break;
    }
    // For lets split it up
#ifdef SPLIT_KEYBOARD
    RGB_DIRTY = true;
#endif
}
#endif

/*---------------------*\
|*-----MATRIX INIT-----*|
\*---------------------*/
void matrix_init_user (void) {
    // Keymap specific things, do it first thing to allow for delays etc
    matrix_init_keymap();
#ifdef UNICODE_ENABLE   // Correct unicode
    set_unicode_input_mode(UC_LNX);
#endif
    // Fix beginning base layer
    set_single_persistent_default_layer(_BA);
#ifdef RGBLIGHT_ENABLE  // RGB light initialize base layer
    base_hue = 100;
    base_sat = 0;
    base_val = 255;
    base_mod = 2;
    base_tog = false;
    rgblight_enable();
    rgblight_mode(base_mod);
    rgblight_sethsv(base_hue,base_sat,base_val);
    rgblight_disable();
    rgblight_loadBase();
#endif
}

/*---------------------*\
|*-----MATRIX SCAN-----*|
\*---------------------*/
void matrix_scan_user (void) {
    // Keymap specific, do it first
    matrix_scan_keymap();
    // Hook on to layer change events
    uint8_t static prev_layer;
    uint8_t current_layer = biton32( layer_state );
    if ( prev_layer != current_layer ) {
#ifdef RGBLIGHT_ENABLE  // Indicator lights
        rgblight_change( current_layer );
#endif
#ifdef AUDIO_ENABLE     // Layer sound effects
        stop_all_notes();
        if ( prev_layer == _GA ) {
            PLAY_SONG(tone_return);
        } else if ( current_layer == _GA ) {
            PLAY_SONG(tone_game);
        }
#endif
        prev_layer = current_layer;
    }
}

/*------------------*\
|*-----KEYCODES-----*|
\*------------------*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t layer = biton32(layer_state);
    switch (keycode) {
        case SECRET1 ... SECRET4:
            if( !record->event.pressed ) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                send_string_with_delay(secret[keycode - SECRET1], MACRO_TIMER);
            }
            return false;
            break;
#ifdef RGBLIGHT_ENABLE              // RGB keys load base layer config
        case RGB_TOG:
        case RGB_MOD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_HUI:
        case RGB_HUD:
            if ( !base_sta ) {
                rgblight_loadBase();
            }
            return true;
            break;
#endif
        // Lock functionality: These layers are locked if the LOCKED buttons are
        // pressed. Otherwise, they are momentary toggles
        case K_LOCK:
            if (record->event.pressed) {
                lock_flag = !lock_flag;
            }
            return false;
            break;
        // Layer switches
        case MU_TOG:
            if (record->event.pressed) {
                // On press, turn off layer if active
                if ( layer == _SE ) {
                    layer_off(_SE);
                    layer_on(_MU);
                } else {
                    layer_off(_MU);
                }
            }
            return true;
            break;
#ifdef UNICODE_ENABLE       // UNICODE
        case UNI_LI:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(tone_linux);
#endif
                set_unicode_input_mode(UC_LNX);
            }
            return false;
            break;
        case UNI_WN:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(tone_windows);
#endif
                set_unicode_input_mode(UC_WIN);
            }
            return false;
            break;
#endif
#ifdef MOUSEKEY_ENABLE      // Diagonal mouse movements
        case MO_NE:
            if( record->event.pressed ) {
                mousekey_on(MO_N);
                mousekey_on(MO_E);
                mousekey_send();
            } else {
                mousekey_off(MO_N);
                mousekey_off(MO_E);
                mousekey_send();
            }
            return false;
            break;
        case MO_NW:
            if( record->event.pressed ) {
                mousekey_on(MO_N);
                mousekey_on(MO_W);
                mousekey_send();
            } else {
                mousekey_off(MO_N);
                mousekey_off(MO_W);
                mousekey_send();
            }
            return false;
            break;
        case MO_SE:
            if( record->event.pressed ) {
                mousekey_on(MO_S);
                mousekey_on(MO_E);
                mousekey_send();
            } else {
                mousekey_off(MO_S);
                mousekey_off(MO_E);
                mousekey_send();
            }
            return false;
            break;
        case MO_SW:
            if( record->event.pressed ) {
                mousekey_on(MO_S);
                mousekey_on(MO_W);
                mousekey_send();
            } else {
                mousekey_off(MO_S);
                mousekey_off(MO_W);
                mousekey_send();
            }
            return false;
            break;
        case MO_S_NE:
            if( record->event.pressed ) {
                mousekey_on(MO_S_N);
                mousekey_on(MO_S_E);
                mousekey_send();
            } else {
                mousekey_off(MO_S_N);
                mousekey_off(MO_S_E);
                mousekey_send();
            }
            return false;
            break;
        case MO_S_NW:
            if( record->event.pressed ) {
                mousekey_on(MO_S_N);
                mousekey_on(MO_S_W);
                mousekey_send();
            } else {
                mousekey_off(MO_S_N);
                mousekey_off(MO_S_W);
                mousekey_send();
            }
            return false;
            break;
        case MO_S_SE:
            if( record->event.pressed ) {
                mousekey_on(MO_S_S);
                mousekey_on(MO_S_E);
                mousekey_send();
            } else {
                mousekey_off(MO_S_S);
                mousekey_off(MO_S_E);
                mousekey_send();
            }
            return false;
            break;
        case MO_S_SW:
            if( record->event.pressed ) {
                mousekey_on(MO_S_S);
                mousekey_on(MO_S_W);
                mousekey_send();
            } else {
                mousekey_off(MO_S_S);
                mousekey_off(MO_S_W);
                mousekey_send();
            }
            return false;
            break;
#endif
//------DOUBLE PRESS keys (Unused)
        case DBL_SPC:
            if( record->event.pressed ) {
                SEND_STRING("  "SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_ANG:
            if( record->event.pressed ) {
                SEND_STRING("<>"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_PAR:
            if( record->event.pressed ) {
                SEND_STRING("()"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_SQR:
            if( record->event.pressed ) {
                SEND_STRING("[]"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_BRC:
            if( record->event.pressed ) {
                SEND_STRING("{}"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_QUO:
            if( record->event.pressed ) {
                SEND_STRING("\'\'"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_DQT:
            if( record->event.pressed ) {
                SEND_STRING("\"\""SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_GRV:
            if( record->event.pressed ) {
                SEND_STRING("``"SS_TAP(X_LEFT));
            }
            return false;
            break;
// END OF KEYCODES
    }
    return process_record_keymap(keycode, record);
}
