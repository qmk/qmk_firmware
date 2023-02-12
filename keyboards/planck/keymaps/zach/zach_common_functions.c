#ifndef ZACH_COMMON_FUNCTIONS
#define ZACH_COMMON_FUNCTIONS
#include "eeconfig.h"
#include "action_layer.h"
#include "keymap_colemak.h"
extern keymap_config_t keymap_config;

#undef C
#define C(n)    RCTL(n)
#define CADKEY  RCTL(RALT(KC_DEL))

void tap(uint16_t keycode){
    register_code(keycode);
    unregister_code(keycode);
};

void persistent_default_layer_set(uint16_t default_layer){
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
};

// Automatic number generation of important keywords
enum my_keycodes{
    // Layer numbers
    _COLEMAK = 0,
    _SWCOLE,
    _RAISE,
    _LOWER,
    _ADJUST,
    _UNICODES,
    // These use process_record_user()
    COLEMAK = SAFE_RANGE,
    SWCOLE,
    LOWER,
    RAISE,
    SHFT_CAP,
    CTRLB,
    CPYPST,
    FACE,
    UNIWIN,
    UNILIN,
    DISFACE,
    TFLIP,
    TPUT,
    SHRUG,
    RANDIG,
    // Tap_Dance nums
    RAI = 0,
    LOW,
    SUP
};

#ifdef AUDIO_ENABLE
#include "audio.h"
float tone_startup[][2]         = SONG(STARTUP_SOUND);
float tone_goodbye[][2]         = SONG(GOODBYE_SOUND);
float tone_colemak[][2]         = SONG(COLEMAK_SOUND);
float tone_swcole[][2]          = SONG(QWERTY_SOUND);
float tone_capslock_on[][2]     = SONG(CAPS_LOCK_ON_SOUND);
float tone_capslock_off[][2]    = SONG(CAPS_LOCK_OFF_SOUND);
float tone_ctrl_mod[][2]        = SONG(COIN_SOUND);
float tone_copy[][2]            = SONG(SCROLL_LOCK_ON_SOUND);
float tone_paste[][2]           = SONG(SCROLL_LOCK_OFF_SOUND);
float uniwin[][2]               = SONG(UNICODE_WINDOWS);
float unilin[][2]               = SONG(UNICODE_LINUX);
#endif

#ifdef TAP_DANCE_ENABLE
#define TAPPING_TERM 200

void dance_raise_press(tap_dance_state_t *state, void *user_data){// Called on each tap
  switch(state->count){      // Only turn the layer on once
    case 1:
        layer_off(_UNICODES);
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        break;
  }
};
void dance_raise_lift(tap_dance_state_t *state, void *user_data){ // Called on release
  switch(state->count){
    case 1:         // Normal action. Turn off layers
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        layer_off(_UNICODES);
        break;
  }
};
/////////////////////////////////////////////////////////////////////
void dance_lower_press(tap_dance_state_t *state, void *user_data){// Called on tap
  switch(state->count){
    case 1:         // Turn on lower
        layer_off(_UNICODES);
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        break;
  }
};
void dance_lower_lift(tap_dance_state_t *state, void *user_data){ // Called on release
  switch(state->count){
    case 1:         // Normal action. Turn off layers
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        layer_off(_UNICODES);
        break;
    case 2:         // Turn on _UNICODES layer
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        layer_on(_UNICODES);
        #ifdef AUDIO_ENABLE
            PLAY_SONG(tone_ctrl_mod);
        #endif
        break;
  }
};
/////////////////////////////////////////////////////////////////////
void dance_super_press(tap_dance_state_t *state, void *user_data){   // Called on down
    if(state->count == 1){
        register_code(KC_LGUI);
    }
}
void dance_super_done(tap_dance_state_t *state, void *user_data){    // Called on timeout
  switch(state->count){
    case 2:
        register_code(KC_LGUI);
        tap(KC_L);
        unregister_code(KC_LGUI);
        break;
  }
}
void dance_super_lift(tap_dance_state_t *state, void *user_data){        // Called on up
    unregister_code(KC_LGUI);
}

tap_dance_action_t tap_dance_actions[] = {
    [RAI] = ACTION_TAP_DANCE_FN_ADVANCED(dance_raise_press, NULL, dance_raise_lift),
    [LOW] = ACTION_TAP_DANCE_FN_ADVANCED(dance_lower_press, NULL, dance_lower_lift),
    [SUP] = ACTION_TAP_DANCE_FN_ADVANCED(dance_super_press, dance_super_done, dance_super_lift)
};
#endif

//#ifdef UNICODE_ENABLE
// Unicode shortcuts
#define IBANG   X(0x203D)
#define RAROW   X(0x2192)
#define LAROW   X(0x2190)
#define DEGREE  X(0x00B0)
#define OMEGA   X(0x03A9)
#define WOMEGA  X(0x03C9)
#define MICRO   X(0x00B5)
#define PLUMIN  X(0x00B1)
#define SUPA2   X(0x00B2)
#define ROMAN1  X(0x2160)
#define ROMAN2  X(0x2161)
#define ROMAN3  X(0x2162)
#define ROMAN4  X(0x2163)
#define ROMAN5  X(0x2164)
#define ROMAN6  X(0x2165)
#define ROMAN7  X(0x2166)
#define roman1  X(0x2170)
#define roman2  X(0x2171)
#define roman3  X(0x2172)
#define roman4  X(0x2173)
#define roman5  X(0x2174)
#define roman6  X(0x2175)
#define roman7  X(0x2176)

#ifdef UNICODEMAP_ENABLE        // For Unicode characters larger than 0x8000. Send with X(<unicode>)
enum Ext_Unicode{
    PENGUIN = 0,
    BOAR,
    MONKEY,
    DRAGON,
    CHICK,
    TUMBLER
};
const uint32_t unicode_map[] PROGMEM = {
    [PENGUIN]   = 0x1F427,
    [BOAR]      = 0x1F417,
    [MONKEY]    = 0x1F412,
    [DRAGON]    = 0x1F409,
    [CHICK]     = 0x1F425,
    [TUMBLER]   = 0x1F943
};
#define PENGY   X(PENGUIN)
#define BOARY   X(BOAR)
#define MNKY    X(MONKEY)
#define DRGN    X(DRAGON)
#define DUCK    X(CHICK)
#define TMBL    X(TUMBLER)
#endif

//#endif

static uint16_t key_timer;
static uint8_t  caps_status = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
        if(record->event.pressed){
            persistent_default_layer_set(1UL<<_COLEMAK);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_colemak);
            #endif
        }
        return false;
        break;
    case SWCOLE:
        if(record->event.pressed){
            persistent_default_layer_set(1UL<<_SWCOLE);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_swcole);
            #endif
        }
        return false;
        break;
    case RAISE:
        if(record->event.pressed){
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case LOWER:
        if(record->event.pressed){
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case SHFT_CAP:
        if(record->event.pressed){
            key_timer = timer_read();               // if the key is being pressed, we start the timer.
            register_code(KC_LSFT);
        } else {                                    // this means the key was just released (tap or "held down")
            if(timer_elapsed(key_timer) < 152){     // Time in ms, the threshold we pick for counting something as a tap.
                tap(KC_CAPS);
                if(caps_status == 0){
                    caps_status = 1;
                    #ifdef AUDIO_ENABLE
                        PLAY_SONG(tone_capslock_on);
                    #endif
                } else {
                    caps_status = 0;
                    #ifdef AUDIO_ENABLE
                        PLAY_SONG(tone_capslock_off);
                    #endif
                }
            }
            unregister_code(KC_LSFT);
        }
        return false;
        break;
    case CTRLB:                                     // Control-B on tap (bold)
        if(record->event.pressed){
            key_timer = timer_read();               // if the key is being pressed, we start the timer.
            register_code(KC_LCTL);
        } else {                                    // this means the key was just released (tap or "held down")
            if (timer_elapsed(key_timer) < 152) {   // Time in ms, the threshold we pick for counting something as a tap.
                tap(KC_B);
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(tone_ctrl_mod);
                #endif
                #ifdef BACKLIGHT_BREATHING
                    breathing_period_set(2);
                    breathing_pulse();
                #endif
            }
            unregister_code(KC_LCTL);
        }
        return false;
        break;
    case CPYPST:                                    // One key copy/paste
        if(record->event.pressed){
            key_timer = timer_read();
        } else {
            if (timer_elapsed(key_timer) > 152) {   // Hold, copy
                register_code(KC_LCTL);
                tap(KC_C);
                unregister_code(KC_LCTL);
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(tone_copy);
                #endif
            } else {                                // Tap, paste
                register_code(KC_LCTL);
                tap(KC_V);
                unregister_code(KC_LCTL);
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(tone_paste);
                #endif
            }
        }
        return false;
        break;
    #ifdef UNICODE_ENABLE
    case UNIWIN:
        if(record->event.pressed){
            set_unicode_input_mode(UNICODE_MODE_WINDOWS);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(uniwin);
            #endif
        }
        return false;
        break;
    case UNILIN:
        if(record->event.pressed){
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            #ifdef AUDIO_ENABLE
              PLAY_SONG(unilin);
            #endif
        }
        return false;
        break;
    case DISFACE:       // ಠ_ಠ
        if(record->event.pressed){
            process_unicode((0x0CA0|QK_UNICODE), record);   // Eye
            register_code(KC_RSFT);
            tap(KC_MINS);
            unregister_code(KC_RSFT);
            process_unicode((0x0CA0|QK_UNICODE), record);   // Eye
        }
        return false;
        break;
    case TFLIP:         // (╯°□°)╯ ︵ ┻━┻
        if(record->event.pressed){
            register_code(KC_RSFT);
            tap(KC_9);
            unregister_code(KC_RSFT);
            process_unicode((0x256F|QK_UNICODE), record);   // Arm
            process_unicode((0x00B0|QK_UNICODE), record);   // Eye
            process_unicode((0x25A1|QK_UNICODE), record);   // Mouth
            process_unicode((0x00B0|QK_UNICODE), record);   // Eye
            register_code(KC_RSFT);
            tap(KC_0);
            unregister_code(KC_RSFT);
            process_unicode((0x256F|QK_UNICODE), record);   // Arm
            tap(KC_SPC);
            process_unicode((0x0361|QK_UNICODE), record);   // Flippy
            tap(KC_SPC);
            process_unicode((0x253B|QK_UNICODE), record);   // Table
            process_unicode((0x2501|QK_UNICODE), record);   // Table
            process_unicode((0x253B|QK_UNICODE), record);   // Table
        }
        return false;
        break;
    case TPUT:          // ┬──┬ ノ( ゜-゜ノ)
        if(record->event.pressed){
            process_unicode((0x252C|QK_UNICODE), record);   // Table
            process_unicode((0x2500|QK_UNICODE), record);   // Table
            process_unicode((0x2500|QK_UNICODE), record);   // Table
            process_unicode((0x252C|QK_UNICODE), record);   // Table
            tap(KC_SPC);
            process_unicode((0x30CE|QK_UNICODE), record);   // Arm
            register_code(KC_RSFT);
            tap(KC_9);
            unregister_code(KC_RSFT);
            tap(KC_SPC);
            process_unicode((0x309C|QK_UNICODE), record);   // Eye
            tap(KC_MINS);
            process_unicode((0x309C|QK_UNICODE), record);   // Eye
            process_unicode((0x30CE|QK_UNICODE), record);   // Arm
            register_code(KC_RSFT);
            tap(KC_0);
            unregister_code(KC_RSFT);
        }
        return false;
        break;
    case SHRUG:         // ¯\_(ツ)_/¯
        if(record->event.pressed){
            process_unicode((0x00AF|QK_UNICODE), record);   // Hand
            tap(KC_BSLS);                                   // Arm
            register_code(KC_RSFT);
            tap(KC_UNDS);                                   // Arm
            tap(KC_LPRN);                                   // Head
            unregister_code(KC_RSFT);
            process_unicode((0x30C4|QK_UNICODE), record);   // Face
            register_code(KC_RSFT);
            tap(KC_RPRN);                                   // Head
            tap(KC_UNDS);                                   // Arm
            unregister_code(KC_RSFT);
            tap(KC_SLSH);                                   // Arm
            process_unicode((0x00AF|QK_UNICODE), record);   // Hand
        }
        return false;
        break;
    #endif
    case FACE:          // (o_O)
        if(record->event.pressed){
            register_code(KC_RSFT);
            tap(KC_LPRN);
            unregister_code(KC_RSFT);
            tap(KC_O);
            register_code(KC_RSFT);
            tap(KC_UNDS);
            tap(KC_O);
            tap(KC_RPRN);
            unregister_code(KC_RSFT);
        }
        return false;
        break;
    case RANDIG:
        if (record->event.pressed) {
            tap_random_base64();
        }
        return false;
        break;
  }
  return true;
};

void matrix_init_user(void){        // Run once at startup
    #ifdef AUDIO_ENABLE
        _delay_ms(50); // gets rid of tick
        PLAY_SONG(tone_startup);
    #endif
}

#ifdef AUDIO_ENABLE
void play_goodbye_tone(void){
  PLAY_SONG(tone_goodbye);
  _delay_ms(150);
}

void shutdown_user(void){
    PLAY_SONG(tone_goodbye);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void){           // Run when the music layer is turned on
    PLAY_SONG(tone_startup);
}

void music_off_user(void){          // Run when music is turned off
	PLAY_SONG(tone_goodbye);
}
#endif

#endif
