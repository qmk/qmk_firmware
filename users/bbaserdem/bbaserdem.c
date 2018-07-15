#include "bbaserdem.h"

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

/*-----------------*\
|*-----SECRETS-----*|
\*-----------------*/
// Enabled by adding a non-tracked secrets.h to this dir.
#if (__has_include("secrets.h"))
#include "secrets.h"
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
#ifdef TAP_DANCE_ENABLE
qk_tap_dance_action_t tap_dance_actions[] = {
    // Shift on double tap of semicolon
    [SCL] = ACTION_TAP_DANCE_DOUBLE( KC_SCLN, KC_COLN )
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
__attribute__ ((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}
__attribute__ ((weak)) uint32_t layer_state_set_keymap (uint32_t state) {
    return state;
}
__attribute__ ((weak)) void led_set_keymap(uint8_t usb_led) { }

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
}
/* HSV values, thank you @drashna!
 * white        (  0,   0, 255)
 * red          (  0, 255, 255)
 * coral        ( 16, 176, 255)
 * orange       ( 39, 255, 255)
 * goldenrod    ( 43, 218, 218)
 * gold         ( 51, 255, 255)
 * yellow       ( 60, 255, 255)
 * chartreuse   ( 90, 255, 255)
 * green        (120, 255, 255)
 * springgreen  (150, 255, 255)
 * turquoise    (174,  90, 112)
 * teal         (180, 255, 128)
 * cyan         (180, 255, 255)
 * azure        (186, 102, 255)
 * blue         (240, 255, 255)
 * purple       (270, 255, 255)
 * magenta      (300, 255, 255)
 * pink         (330, 128, 255)
 */
// Set RGBLIGHT state depending on layer
void rgblight_change( uint8_t last_layer ) {
    // Save state, if saving is requested
    /*
    if ( base_sta ) {
        rgblight_saveBase();
    }
    */
    // Change RGB light
    switch ( last_layer ) {
        case _DV:
            // Load base layer
            rgblight_loadBase();
            break;
        case _AL:
            // Do yellow for alternate
            rgblight_colorStatic( 60,255,255);
            break;
        case _GA:
            // Do purple for game
            rgblight_colorStatic(285,255,255);
            break;
        case _NU:
            // Do azure for number
            rgblight_colorStatic(186,200,255);
            break;
        case _SE:
            // Do red for settings
            rgblight_colorStatic( 16,255,255);
            break;
        case _MO:
            // Do green for mouse
            rgblight_colorStatic(120,255,255);
            break;
#ifdef AUDIO_ENABLE
        case _MU:
            // Do orange for music
            rgblight_colorStatic( 39,255,255);
            break;
#endif
        default:
            // Something went wrong
            rgblight_colorStatic(  0,255,255);
            break;
    }
}

#endif

/*---------------------*\
|*-----MATRIX INIT-----*|
\*---------------------*/
void matrix_init_user (void) {

    // Keymap specific things, do it first thing to allow for delays etc
    matrix_init_keymap();

    // Correct unicode
    set_unicode_input_mode(UC_LNX);

    // Make beginning layer DVORAK
    set_single_persistent_default_layer(_DV);

//--RGB light initialize base layer
#ifdef RGBLIGHT_ENABLE
    // Base hue is white, and RGB disabled
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
    // Moved RGB check to layer_state_set_user
}

/*------------------*\
|*-----KEYCODES-----*|
\*------------------*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Shift check
    bool is_capital = ( keyboard_report->mods & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)) );
    static bool lock_flag = false;
    uint8_t layer = biton32 (layer_state);

    switch (keycode) {
        // Secrets implementation
        case SECRET1 ... SECRET3:
#if (__has_include("secrets.h"))
            if( !record->event.pressed ) {
                send_string_P( secret[ keycode - SECRET1 ] );
            }
#endif
            return false;
            break;
        // If these keys are pressed, load base layer config, and mark saving
        case RGB_TOG:
        case RGB_MOD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_HUI:
        case RGB_HUD:
#ifdef RGBLIGHT_ENABLE
            if ( !base_sta ) {
                rgblight_loadBase(); 
            }
#endif
            return true;
            break;

        // Lock functionality: These layers are locked if the LOCKED buttons are
        // pressed. Otherwise, they are momentary toggles
        case K_LOCK:
            if (record->event.pressed) {
                lock_flag = !lock_flag;
            }
            return false;
            break;
        case K_MOUSE:
#ifdef MOUSEKEY_ENABLE
            if (record->event.pressed) {
                layer_on(_MO);
                lock_flag = false;
            } else {
                if ( lock_flag ) {
                    lock_flag = false;
                } else {
                    layer_off(_MO);
                }
            }
#endif
            return false;
            break;
        case K_NUMBR:
            if (record->event.pressed) {
                layer_on(_NU);
                lock_flag = false;
            } else {
                if ( lock_flag ) {
                    lock_flag = false;
                } else {
                    layer_off(_NU);
                }
            }
            return false;
            break;
            
        // Layer switches with sound
        case K_GAMES:
            if (record->event.pressed) {
                // On press, turn off layer if active
                if ( layer == _GA ) {
#ifdef AUDIO_ENABLE
                    stop_all_notes();
                    PLAY_SONG(tone_return);
#endif
                    layer_off(_GA);
                }
            } else {
                // After click, turn on layer if accessed from setting
                if ( layer == _SE ) {
#ifdef AUDIO_ENABLE
                    stop_all_notes();
                    PLAY_SONG(tone_game);
#endif
                    layer_on(_GA);
                    layer_off(_SE);
                }
            }
            return false;
            break;
        case MU_TOG:
#ifdef AUDIO_ENABLE
            if (record->event.pressed) {
                // On press, turn off layer if active
                if ( layer == _SE ) {
                    layer_off(_SE);
                    layer_on(_MU);
                } else {
                    layer_off(_MU);
                }
            }
#endif
            return true;
            break;

//------UNICODE
        // Unicode switches with sound
        case UNI_LI:
#ifdef UNICODE_ENABLE
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(tone_linux);
#endif
                set_unicode_input_mode(UC_LNX);
            }
#endif
            return false;
            break;
        case UNI_WN:
#ifdef UNICODE_ENABLE
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(tone_windows);
#endif
                set_unicode_input_mode(UC_WIN);
            }
#endif
            return false;
            break;

        // Turkish letters, with capital functionality
        case TUR_A:
#ifdef UNICODE_ENABLE
            if (record->event.pressed) {
                if ( is_capital ) {
                    unicode_input_start();
                    register_hex(0x00c2);
                    unicode_input_finish();
                } else {
                    unicode_input_start();
                    register_hex(0x00e2);
                    unicode_input_finish();
                }
            }
#endif
            return false;
            break;
        case TUR_O:
#ifdef UNICODE_ENABLE
            if (record->event.pressed) {
                if ( is_capital ) {
                    unicode_input_start();
                    register_hex(0x00d6);
                    unicode_input_finish();
                } else {
                    unicode_input_start();
                    register_hex(0x00f6);
                    unicode_input_finish();
                }
            }
#endif
            return false;
            break;
        case TUR_U:
#ifdef UNICODE_ENABLE
            if (record->event.pressed) {
                if ( is_capital ) {
                    unicode_input_start();
                    register_hex(0x00dc);
                    unicode_input_finish();
                } else {
                    unicode_input_start();
                    register_hex(0x00fc);
                    unicode_input_finish();
                }
            }
#endif
            return false;
            break;
        case TUR_I:
#ifdef UNICODE_ENABLE
            if (record->event.pressed) {
                if ( is_capital ) {
                    unicode_input_start();
                    register_hex(0x0130);
                    unicode_input_finish();
                } else {
                    unicode_input_start();
                    register_hex(0x0131);
                    unicode_input_finish();
                }
            }
#endif
            return false;
            break;
        case TUR_G:
#ifdef UNICODE_ENABLE
            if (record->event.pressed) {
                if ( is_capital ) {
                    unicode_input_start();
                    register_hex(0x011e);
                    unicode_input_finish();
                } else {
                    unicode_input_start();
                    register_hex(0x011f);
                    unicode_input_finish();
                }
            }
#endif
            return false;
            break;
        case TUR_C:
#ifdef UNICODE_ENABLE
            if (record->event.pressed) {
                if ( is_capital ) {
                    unicode_input_start();
                    register_hex(0x00c7);
                    unicode_input_finish();
                } else {
                    unicode_input_start();
                    register_hex(0x00e7);
                    unicode_input_finish();
                }
            }
#endif
            return false;
            break;
        case TUR_S:
#ifdef UNICODE_ENABLE
            if (record->event.pressed) {
                if ( is_capital ) {
                    unicode_input_start();
                    register_hex(0x015e);
                    unicode_input_finish();
                } else {
                    unicode_input_start();
                    register_hex(0x015f);
                    unicode_input_finish();
                }
            }
#endif
            return false;
            break;

//-------Diagonal mouse movements
        case MO_NE:
#ifdef MOUSEKEY_ENABLE
            if( record->event.pressed ) {
                mousekey_on(MO_N);
                mousekey_on(MO_E);
                mousekey_send();
            } else {
                mousekey_off(MO_N);
                mousekey_off(MO_E);
                mousekey_send();
            }
#endif
            return false;
            break;
        case MO_NW:
#ifdef MOUSEKEY_ENABLE
            if( record->event.pressed ) {
                mousekey_on(MO_N);
                mousekey_on(MO_W);
                mousekey_send();
            } else {
                mousekey_off(MO_N);
                mousekey_off(MO_W);
                mousekey_send();
            }
#endif
            return false;
            break;
        case MO_SE:
#ifdef MOUSEKEY_ENABLE
            if( record->event.pressed ) {
                mousekey_on(MO_S);
                mousekey_on(MO_E);
                mousekey_send();
            } else {
                mousekey_off(MO_S);
                mousekey_off(MO_E);
                mousekey_send();
            }
#endif
            return false;
            break;
        case MO_SW:
#ifdef MOUSEKEY_ENABLE
            if( record->event.pressed ) {
                mousekey_on(MO_S);
                mousekey_on(MO_W);
                mousekey_send();
            } else {
                mousekey_off(MO_S);
                mousekey_off(MO_W);
                mousekey_send();
            }
#endif
            return false;
            break;
        case MO_S_NE:
#ifdef MOUSEKEY_ENABLE
            if( record->event.pressed ) {
                mousekey_on(MO_S_N);
                mousekey_on(MO_S_E);
                mousekey_send();
            } else {
                mousekey_off(MO_S_N);
                mousekey_off(MO_S_E);
                mousekey_send();
            }
#endif
            return false;
            break;
        case MO_S_NW:
#ifdef MOUSEKEY_ENABLE
            if( record->event.pressed ) {
                mousekey_on(MO_S_N);
                mousekey_on(MO_S_W);
                mousekey_send();
            } else {
                mousekey_off(MO_S_N);
                mousekey_off(MO_S_W);
                mousekey_send();
            }
#endif
            return false;
            break;
        case MO_S_SE:
#ifdef MOUSEKEY_ENABLE
            if( record->event.pressed ) {
                mousekey_on(MO_S_S);
                mousekey_on(MO_S_E);
                mousekey_send();
            } else {
                mousekey_off(MO_S_S);
                mousekey_off(MO_S_E);
                mousekey_send();
            }
#endif
            return false;
            break;
        case MO_S_SW:
#ifdef MOUSEKEY_ENABLE
            if( record->event.pressed ) {
                mousekey_on(MO_S_S);
                mousekey_on(MO_S_W);
                mousekey_send();
            } else {
                mousekey_off(MO_S_S);
                mousekey_off(MO_S_W);
                mousekey_send();
            }
#endif
            return false;
            break;
//------DOUBLE PRESS, with added left navigation
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

/*----------------------*\
|*-----LAYER CHANGE-----*|
\*----------------------*/

uint32_t layer_state_set_user(uint32_t state) {

    state = layer_state_set_keymap (state);
#ifdef RGBLIGHT_ENABLE
    // Change RGB lighting depending on the last layer activated
    rgblight_change( biton32(state) );
#endif
    return state;
}
