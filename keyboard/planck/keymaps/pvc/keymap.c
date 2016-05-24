#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "led.h"

#ifdef AUDIO_ENABLE
    #include "audio.h"
    #include "song_list.h"
#endif

#define LAYER_QWERTY         0
#define LAYER_COLEMAK        1
#define LAYER_DVORAK         2
#define LAYER_LOWER          3
#define LAYER_RAISE          4
#define LAYER_FUNCTION       5
#define LAYER_MOUSE          6
#define LAYER_MUSIC          7
#define LAYER_ADJUST         8

#define MACRO_QWERTY         0
#define MACRO_COLEMAK        1
#define MACRO_DVORAK         2
#define MACRO_LOWER          3
#define MACRO_RAISE          4
#define MACRO_FUNCTION       5
#define MACRO_MOUSE          6
#define MACRO_TIMBRE_1       7
#define MACRO_TIMBRE_2       8
#define MACRO_TIMBRE_3       9
#define MACRO_TIMBRE_4      10
#define MACRO_TEMPO_U       11
#define MACRO_TEMPO_D       12
#define MACRO_TONE_DEFAULT  13
#define MACRO_MUSIC_ON      14
#define MACRO_MUSIC_OFF     15
#define MACRO_AUDIO_ON      16
#define MACRO_AUDIO_OFF     17
#define MACRO_INC_VOICE     18
#define MACRO_DEC_VOICE     19
#define MACRO_BACKLIGHT     20

#define M_QWRTY             M(MACRO_QWERTY)
#define M_COLMK             M(MACRO_COLEMAK)
#define M_DVORK             M(MACRO_DVORAK)
#define M_LOWER             M(MACRO_LOWER)
#define M_RAISE             M(MACRO_RAISE)
#define M_FUNCT             M(MACRO_FUNCTION)
#define M_MOUSE             M(MACRO_MOUSE)
#define TIMBR_1             M(MACRO_TIMBRE_1)
#define TIMBR_2             M(MACRO_TIMBRE_2)
#define TIMBR_3             M(MACRO_TIMBRE_3)
#define TIMBR_4             M(MACRO_TIMBRE_4)
#define TMPO_UP             M(MACRO_TEMPO_U)
#define TMPO_DN             M(MACRO_TEMPO_D)
#define TMPO_DF             M(MACRO_TONE_DEFAULT)
#define M_BACKL             M(MACRO_BACKLIGHT)


#define MUS_ON              M(MACRO_MUSIC_ON)
#define MUS_OFF             M(MACRO_MUSIC_OFF)
#define AUD_OFF             M(MACRO_AUDIO_OFF)
#define AUD_ON              M(MACRO_AUDIO_ON)
#define VC_UP               M(MACRO_INC_VOICE)
#define VC_DOWN             M(MACRO_DEC_VOICE)


#define SC_UNDO             LCTL(KC_Z)
#define SC_REDO             LCTL(KC_Y)
#define SC_CUT              LCTL(KC_X)
#define SC_COPY             LCTL(KC_C)
#define SC_PSTE             LCTL(KC_V)
#define SC_SELA             LCTL(KC_A)
#define SC_SAVE             LCTL(KC_S)
#define SC_OPEN             LCTL(KC_O)
#define SC_ACLS             LALT(KC_F4)
#define SC_CCLS             LCTL(KC_F4)


#define _______             KC_TRNS
#define XXXXXXX             KC_NO
#define ________________    _______, _______
#define XXXXXXXXXXXXXXXX    XXXXXXX, XXXXXXX

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .-----------------------------------------------------------------------------------------------------------.
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ESC    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | RAISE  | SPACE  | SPACE  | LOWER  | UP     | DOWN   | LEFT   | RIGHT  |
 * '-----------------------------------------------------------------------------------------------------------'
 */

 [LAYER_QWERTY]       = { /* QWERTY */
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC   },
  { KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT   },
  { KC_LCTL, KC_LGUI, M_FUNCT, KC_LALT, M_RAISE, KC_SPC,  KC_SPC,  M_LOWER, KC_UP,   KC_DOWN, KC_LEFT, KC_RGHT  },
 },

/* COLEMAK
 * .-----------------------------------------------------------------------------------------------------------.
 * | TAB    | Q      | W      | F      | P      | G      | J      | L      | U      | Y      | ;      | ESC    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | BACKSP | A      | R      | S      | T      | D      | H      | N      | E      | I      | O      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | K      | M      | ,      | .      | /      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | RAISE  | SPACE  | SPACE  | LOWER  | UP     | DOWN   | LEFT   | RIGHT  |
 * '-----------------------------------------------------------------------------------------------------------'
 */

 [LAYER_COLEMAK]      = { /* COLEMAK */
  { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_ESC   },
  { KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT   },
  { KC_LCTL, KC_LGUI, M_FUNCT, KC_LALT, M_RAISE, KC_SPC,  KC_SPC,  M_LOWER, KC_UP,   KC_DOWN, KC_LEFT, KC_RGHT  },
 },

/* DVORAK
 * .-----------------------------------------------------------------------------------------------------------.
 * | TAB    | '      | ,      | .      | P      | Y      | F      | G      | C      | R      | L      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ESC    | A      | O      | E      | U      | I      | D      | H      | T      | N      | S      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LSHIFT | ;      | Q      | J      | K      | X      | B      | M      | W      | V      | Z      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | RAISE  | SPACE  | SPACE  | LOWER  | UP     | DOWN   | LEFT   | RIGHT  |
 * '-----------------------------------------------------------------------------------------------------------'
 */

 [LAYER_DVORAK]       = { /* DVORAK */
  { KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC  },
  { KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH  },
  { KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT   },
  { KC_LCTL, KC_LGUI, M_FUNCT, KC_LALT, M_RAISE, KC_SPC,  KC_SPC,  M_LOWER, KC_UP,   KC_DOWN, KC_LEFT, KC_RGHT  },
 },

/* Raise
 * .-----------------------------------------------------------------------------------------------------------.
 * | ~      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | F1     | F2     | F3     | F4     | F5     | F6     | _      | +      | [      | ]      | \      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LSHIFT | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX | XXXXXX | XXXXXX | XXXXXX | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | RAISE  | BACKSP | BACKSP | LOWER  | PG UP  | PG DN  | HOME   | END    |
 * '-----------------------------------------------------------------------------------------------------------'
 */

 [LAYER_RAISE]        = { /* RAISED */
  { KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL   },
  { XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS  },
  { _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  },
  { _______, _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, KC_PGUP, KC_PGDN, KC_HOME, KC_END   },
 },


/* LOWERED
 * .-----------------------------------------------------------------------------------------------------------.
 * | ~      | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      | INS    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | F1     | F2     | F3     | F4     | F5     | F6     | _      | +      | {      | }      | |      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LSHIFT | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX | XXXXXX | XXXXXX | XXXXXX | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | RAISE  | BACKSP | BACKSP | LOWER  | PG UP  | PG DN  | HOME   | END    |
 * '-----------------------------------------------------------------------------------------------------------'
 */

 [LAYER_LOWER]        = { /* LOWERED */
  { KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_INS   },
  { XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS  },
  { _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  },
  { _______, _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, KC_PGUP, KC_PGDN, KC_HOME, KC_END   },
 },

/* FUNCTION
 * .-----------------------------------------------------------------------------------------------------------.
 * | NUM LK | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | PAUSE  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | CAP LK | F11    | F12    | F13    | F14    | F15    | F16    | F17    | F18    | F19    | F20    | PRINT  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | SCR LK | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | MUTE   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | RAISE  | PLAY   | PLAY   | LOWER  | VOL UP | VOL DN | NEXT   | PREV   |
 * '-----------------------------------------------------------------------------------------------------------'
 */
 [LAYER_FUNCTION]     = { /* FUNCTION */
  { KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PAUS  },
  { KC_CAPS, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_PSCR  },
  { KC_SLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE  },
  { _______, _______, _______, _______, _______, KC_MPLY, KC_MPLY, _______, KC_VOLU, KC_VOLD, KC_MPRV, KC_MNXT  },
 },

#ifdef MOUSEKEY_ENABLE

 [LAYER_MOUSE]        = { /* MOUSE */
  { KC_ESC,  KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC   },
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  },
  { _______, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_U, KC_WH_D  },
  { _______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, KC_MS_U, KC_MS_D, KC_MS_L, KC_MS_R  },
 },

#endif

 [LAYER_MUSIC]        = { /* MUSIC */
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  },
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  },
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  },
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_RAISE, XXXXXXX, XXXXXXX, M_LOWER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  },
 },

 [LAYER_ADJUST]       = { /* ADJUST */
  { _______, TIMBR_1, TIMBR_2, TIMBR_3, TIMBR_4, TMPO_UP, TMPO_DN, TMPO_DF, MUS_ON,  MUS_OFF, AUD_ON,  AUD_OFF  },
  { _______, M_QWRTY, M_COLMK, M_DVORK, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______, _______, _______, M_BACKL, RESET,   _______, M_MOUSE, _______, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, VC_UP,   VC_DOWN, _______, _______  },
 },


/*
 [LAYER_EMPTY]        = {
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  },
  { _______, _______, _______, _______, _______, ________________, _______, _______, _______, _______, _______,  },
 },
*/

};

#ifdef AUDIO_ENABLE

float tone_my_startup[][2] = SONG(ODE_TO_JOY);
float tone_my_goodbye[][2] = SONG(ROCK_A_BYE_BABY);

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);

float tone_audio_on[][2]   = SONG(CLOSE_ENCOUNTERS_5_NOTE);
float tone_music_on[][2]   = SONG(DOE_A_DEER);
float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

#endif /* AUDIO_ENABLE */

void persistant_default_layer_set(uint16_t default_layer)
{
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{

    // MACRODOWN only works in this function
    switch(id)
    {

        case MACRO_QWERTY:
            if (record->event.pressed)
            {
                persistant_default_layer_set(1UL<<LAYER_QWERTY);
				#ifdef AUDIO_ENABLE
                	PLAY_NOTE_ARRAY(tone_qwerty, false, STACCATO);
				#endif /* AUDIO_ENABLE */
            }
            break;

        case MACRO_COLEMAK:
            if (record->event.pressed)
            {
                persistant_default_layer_set(1UL<<LAYER_COLEMAK);
				#ifdef AUDIO_ENABLE
                	PLAY_NOTE_ARRAY(tone_colemak, false, STACCATO);
				#endif /* AUDIO_ENABLE */
            }
            break;

        case MACRO_DVORAK:
            if (record->event.pressed)
            {
                persistant_default_layer_set(1UL<<LAYER_DVORAK);
				#ifdef AUDIO_ENABLE
    	            PLAY_NOTE_ARRAY(tone_dvorak, false, STACCATO);
				#endif /* AUDIO_ENABLE */
            }
            break;

        case MACRO_LOWER:
            if (record->event.pressed)
            {
                layer_on(LAYER_LOWER);
                update_tri_layer(LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
            }
            else
            {
                layer_off(LAYER_LOWER);
                update_tri_layer(LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
            }
            break;

        case MACRO_RAISE:
            if (record->event.pressed)
            {
                layer_on(LAYER_RAISE);
                update_tri_layer(LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
            }
            else
            {
                layer_off(LAYER_RAISE);
                update_tri_layer(LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
            }
            break;

        case MACRO_FUNCTION:
            if (record->event.pressed)
            {
                layer_on(LAYER_FUNCTION);
            }
            else
            {
                layer_off(LAYER_FUNCTION);
            }
            break;


#ifdef BACKLIGHT_ENABLE
		case MACRO_BACKLIGHT:
			if (record->event.pressed)
			{
				backlight_step();
			}
#endif

#ifdef MOUSEKEY_ENABLE

        case MACRO_MOUSE:
            if (record->event.pressed)
            {
                layer_invert(LAYER_MOUSE);
            }
            break;

#endif /* MOUSEKEY_ENABLE */

#ifdef AUDIO_ENABLE

        case MACRO_TIMBRE_1:
            if (record->event.pressed) set_timbre(TIMBRE_12);
            break;

        case MACRO_TIMBRE_2:
            if (record->event.pressed) set_timbre(TIMBRE_25);
            break;

        case MACRO_TIMBRE_3:
            if (record->event.pressed) set_timbre(TIMBRE_50);
            break;

        case MACRO_TIMBRE_4:
            if (record->event.pressed) set_timbre(TIMBRE_75);
            break;

        case MACRO_TEMPO_U:
            if (record->event.pressed) increase_tempo(10);
            break;

        case MACRO_TEMPO_D:
            if (record->event.pressed) decrease_tempo(10);
            break;

        case MACRO_TONE_DEFAULT:
            if (record->event.pressed)
            {
                set_timbre(TIMBRE_DEFAULT);
                set_tempo(TEMPO_DEFAULT);
            }
            break;

        case MACRO_AUDIO_OFF:
            if (record->event.pressed)
            {
                #ifdef AUDIO_ENABLE
                    audio_off();
                #endif
            }
            break;

        case MACRO_AUDIO_ON:
            if (record->event.pressed)
            {
                #ifdef AUDIO_ENABLE
                    audio_on();
                PLAY_NOTE_ARRAY(tone_audio_on, false, STACCATO);
                #endif
            }
            break;

        case MACRO_MUSIC_ON:
            if (record->event.pressed)
            {
                #ifdef AUDIO_ENABLE
                    PLAY_NOTE_ARRAY(tone_music_on, false, STACCATO);
                    layer_on(LAYER_MUSIC);
                #endif
            }
            break;

        case MACRO_MUSIC_OFF:
            if (record->event.pressed)
            {
                #ifdef AUDIO_ENABLE
                    layer_off(LAYER_MUSIC);
                    stop_all_notes();
                #endif
            }
            break;

        case MACRO_INC_VOICE:
            if (record->event.pressed)
            {
                #ifdef AUDIO_ENABLE
                    voice_iterate();
                    PLAY_NOTE_ARRAY(music_scale, false, STACCATO);
                #endif
            }
            break;

        case MACRO_DEC_VOICE:
            if (record->event.pressed)
            {
                #ifdef AUDIO_ENABLE
                    voice_deiterate();
                    PLAY_NOTE_ARRAY(music_scale, false, STACCATO);
                #endif
            }
            break;

#endif /* AUDIO_ENABLE */

        default:
            break;

    }
    return MACRO_NONE;
};


#ifdef AUDIO_ENABLE


void process_action_user(keyrecord_t *record)
{

    uint8_t starting_note = 0x0C;
    int offset = 7;

    if (IS_LAYER_ON(LAYER_MUSIC))
    {
        if (record->event.pressed)
        {
            play_note(((double)220.0)*pow(2.0, -4.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row)), 0xF);
        }
        else
        {
            stop_note(((double)220.0)*pow(2.0, -4.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row)));
        }
    }
}


void matrix_init_user(void)
{
    set_voice(default_voice);
    play_startup_tone();
    println("Matrix Init");
}

void led_set_user(uint8_t usb_led)
{
    static uint8_t old_usb_led = 0;

    _delay_ms(10); // gets rid of tick

    if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
            // If CAPS LK LED is turning on...
            PLAY_NOTE_ARRAY(tone_caps_on,  false, LEGATO);
    }
    else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
            // If CAPS LK LED is turning off...
            PLAY_NOTE_ARRAY(tone_caps_off, false, LEGATO);
    }
    else if ((usb_led & (1<<USB_LED_NUM_LOCK)) && !(old_usb_led & (1<<USB_LED_NUM_LOCK)))
    {
            // If NUM LK LED is turning on...
            PLAY_NOTE_ARRAY(tone_numlk_on,  false, LEGATO);
    }
    else if (!(usb_led & (1<<USB_LED_NUM_LOCK)) && (old_usb_led & (1<<USB_LED_NUM_LOCK)))
    {
            // If NUM LED is turning off...
            PLAY_NOTE_ARRAY(tone_numlk_off, false, LEGATO);
    }
    else if ((usb_led & (1<<USB_LED_SCROLL_LOCK)) && !(old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
            // If SCROLL LK LED is turning on...
            PLAY_NOTE_ARRAY(tone_scroll_on,  false, LEGATO);
    }
    else if (!(usb_led & (1<<USB_LED_SCROLL_LOCK)) && (old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
            // If SCROLL LED is turning off...
            PLAY_NOTE_ARRAY(tone_scroll_off, false, LEGATO);
    }
    old_usb_led = usb_led;
}


void play_startup_tone()
{
    _delay_ms(10); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_my_startup, false, STACCATO);
}

void play_goodbye_tone()
{
    PLAY_NOTE_ARRAY(tone_my_goodbye, false, STACCATO);
    _delay_ms(1000);
}

#endif /* AUDIO_ENABLE */