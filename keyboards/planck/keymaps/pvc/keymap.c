#include QMK_KEYBOARD_H
#include "mousekey.h"

#ifdef AUDIO_ENABLE
    #include "audio.h"
    #include "song_list.h"
#endif

enum keyboard_layers {
  LAYER_QWERTY = 0,
  LAYER_UPPER,
  LAYER_LOWER,
  LAYER_FUNCTION,
  LAYER_MOUSE,
  LAYER_ADJUST,
};
enum keyboard_macros {
  MACRO_QWERTY = 0,
  MACRO_UPPER,
  MACRO_LOWER,
  MACRO_FUNCTION,
  MACRO_MOUSE,
  MACRO_TIMBRE_1,
  MACRO_TIMBRE_2,
  MACRO_TIMBRE_3,
  MACRO_TIMBRE_4,
  MACRO_TEMPO_U,
  MACRO_TEMPO_D,
  MACRO_TONE_DEFAULT,
  MACRO_MUSIC_TOGGLE,
  MACRO_AUDIO_TOGGLE,
  MACRO_INC_VOICE,
  MACRO_DEC_VOICE,
  MACRO_BACKLIGHT,
  MACRO_BREATH_TOGGLE,
  MACRO_BREATH_SPEED_INC,
  MACRO_BREATH_SPEED_DEC,
  MACRO_BREATH_DEFAULT,
  MACRO_MOUSE_MOVE_UL,
  MACRO_MOUSE_MOVE_UR,
  MACRO_MOUSE_MOVE_DL,
  MACRO_MOUSE_MOVE_DR,
  MACRO_HELP_1,
  MACRO_HELP_2,
  MACRO_HELP_3,
  MACRO_HELP_4,
  MACRO_HELP_5,
  MACRO_HELP_6,
  MACRO_HELP_7,
  MACRO_HELP_8,
  MACRO_HELP_9,
};

#define M_QWRTY             M(MACRO_QWERTY)
#define M_UPPER             M(MACRO_UPPER)
#define M_LOWER             M(MACRO_LOWER)
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
#define M_BRTOG             M(MACRO_BREATH_TOGGLE)
#define M_BSPDU             M(MACRO_BREATH_SPEED_INC)
#define M_BSPDD             M(MACRO_BREATH_SPEED_DEC)
#define M_BDFLT             M(MACRO_BREATH_DEFAULT)
#define M_MS_UL             M(MACRO_MOUSE_MOVE_UL)
#define M_MS_UR             M(MACRO_MOUSE_MOVE_UR)
#define M_MS_DL             M(MACRO_MOUSE_MOVE_DL)
#define M_MS_DR             M(MACRO_MOUSE_MOVE_DR)
#define M_HELP1             M(MACRO_HELP_1)
#define M_HELP2             M(MACRO_HELP_2)
#define M_HELP3             M(MACRO_HELP_3)
#define M_HELP4             M(MACRO_HELP_4)
#define M_HELP5             M(MACRO_HELP_5)
#define M_HELP6             M(MACRO_HELP_6)
#define M_HELP7             M(MACRO_HELP_7)
#define M_HELP8             M(MACRO_HELP_8)
#define M_HELP9             M(MACRO_HELP_9)


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

#define TG_NKRO             MAGIC_TOGGLE_NKRO
#define OS_SHFT             OSM(MOD_RSFT)

#define ________________    _______, _______
#define XXXXXXXXXXXXXXXX    XXXXXXX, XXXXXXX

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER = LAYER_QWERTY
  .-----------------------------------------------------------------------------------------------------------.
  | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | BACKSP |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ESC    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | UP     | ENTER  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | LCTRL  | LWIN   | FN     | LALT   | UPPER  | SPACE  | SPACE  | LOWER  | OSHIFT | LEFT   | DOWN   | RIGHT  |
  '-----------------------------------------------------------------------------------------------------------'
*/
[LAYER_QWERTY] = LAYOUT_planck_grid(
   KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC ,
   KC_ESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT ,
   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_ENT  ,
   KC_LCTL, KC_LGUI, M_FUNCT, KC_LALT, M_UPPER, KC_SPC , KC_SPC , M_LOWER, OS_SHFT, KC_LEFT, KC_DOWN, KC_RGHT
),
/* LAYER = LAYER_UPPER
  .-----------------------------------------------------------------------------------------------------------.
  | PRINT  | F1     | F2     | F3     | F4     | NUM LK | KP /   | KP 7   | KP 8   | KP 9   | KP -   | DEL    |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | PAUSE  | F5     | F6     | F7     | F8     | SCR LK | KP *   | KP 4   | KP 5   | KP 6   | KP +   | INS    |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ______ | F9     | F10    | F11    | F12    | PAUSE  | KP 0   | KP 1   | KP 2   | KP 3   | KP ENT | HOME   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ______ | ______ | ______ | ______ | UPPER  | KP 0   | KP 0   | ______ | RALT   | KP .   | KP ENT | END    |
  '-----------------------------------------------------------------------------------------------------------'
*/
[LAYER_UPPER] = LAYOUT_planck_grid(
   KC_PSCR, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_NLCK, KC_PSLS, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, KC_DEL  ,
   KC_PAUS, KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_SLCK, KC_PAST, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_INS  ,
   _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_PAUS, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, KC_HOME ,
   _______, _______, _______, _______, M_UPPER, KC_KP_0, KC_KP_0, _______, KC_RALT, KC_PDOT, KC_PENT, KC_END
),
/* LAYER = LAYER_LOWER
  .-----------------------------------------------------------------------------------------------------------.
  | ______ | $      | {      | [      | (      | %      | #      | )      | ]      | }      | @      | PG UP  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ______ | ^      | *      | +      | -      | /      | \      | _      | '      | "      | `      | PG DN  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ______ | |      | &      | !      | ~      | ;      | :      | =      | <      | >      | ?      | HOME   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ______ | ______ | ______ | ______ | ______ | ______ | ______ | LOWER  | ______ | ______ | ______ | END    |
  '-----------------------------------------------------------------------------------------------------------'
*/
[LAYER_LOWER] = LAYOUT_planck_grid(
   _______, KC_DLR , KC_LCBR, KC_LBRC, KC_LPRN, KC_PERC, KC_HASH, KC_RPRN, KC_RBRC, KC_RCBR, KC_AT  , KC_PGUP ,
   _______, KC_CIRC, KC_ASTR, KC_PLUS, KC_MINS, KC_SLSH, KC_BSLS, KC_UNDS, KC_QUOT, KC_DQT , KC_GRV , KC_PGDN ,
   _______, KC_PIPE, KC_AMPR, KC_EXLM, KC_TILD, KC_SCLN, KC_COLN, KC_EQL , KC_LT  , KC_GT  , KC_QUES, KC_HOME ,
   _______, _______, _______, _______, _______, _______, _______, M_LOWER, _______, _______, _______, KC_END
),
/* LAYER = LAYER_FUNCTION
  .-----------------------------------------------------------------------------------------------------------.
  | XXXXXX | F13    | F14    | F15    | F16    | NUM LK | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | XXXXXX | F17    | F18    | F19    | F20    | SCR LK | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ______ | F21    | F22    | F23    | F24    | CAP LK | XXXXXX | XXXXXX | XXXXXX | XXXXXX | VOL UP | MUTE   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ______ | ______ | FN     | ______ | ______ | PLAY   | PLAY   | ______ | ______ | PREV   | VOL DN | NEXT   |
  '-----------------------------------------------------------------------------------------------------------'
*/
[LAYER_FUNCTION] = LAYOUT_planck_grid(
   XXXXXXX, KC_F13 , KC_F14 , KC_F15 , KC_F16 , KC_NLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
   XXXXXXX, KC_F17 , KC_F18 , KC_F19 , KC_F20 , KC_SLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
   _______, KC_F21 , KC_F22 , KC_F23 , KC_F24 , KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, KC_MUTE ,
   _______, _______, M_FUNCT, _______, _______, KC_MPLY, KC_MPLY, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
),
/* LAYER = LAYER_MOUSE
  .-----------------------------------------------------------------------------------------------------------.
  | ESC    | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | MS UL  | MS U   | MS UR  | MS WHL | MS WHR |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | XXXXXX | MS BT5 | MS BT4 | MS BT3 | MS BT2 | XXXXXX | XXXXXX | MS L   | XXXXXX | MS R   | XXXXXX | MS WHU |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ______ | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | MS DL  | MS D   | MS DR  | MS U   | MS WHD |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | ______ | ______ | ______ | ______ | ______ | MS BT1 | MS BT1 | ______ | ______ | MS L   | MS D   | MS R   |
  '-----------------------------------------------------------------------------------------------------------'
*/
[LAYER_MOUSE] = LAYOUT_planck_grid(
   KC_ESC , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_MS_UL, KC_MS_U, M_MS_UR, KC_WH_L, KC_WH_R ,
   XXXXXXX, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, KC_MS_L, XXXXXXX, KC_MS_R, XXXXXXX, KC_WH_U ,
   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_MS_DL, KC_MS_D, M_MS_DR, KC_MS_U, KC_WH_D ,
   _______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
),
/* LAYER = LAYER_ADJUST
  .-----------------------------------------------------------------------------------------------------------.
  | XXXXXX | HELP 1 | HELP 2 | HELP 3 | HELP 4 | HELP 5 | HELP 6 | HELP 7 | HELP 8 | HELP 9 | MUSIC  | AUDIO  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | XXXXXX | BRTOG  | BRSPD+ | BRSPD- | BRDFLT | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | XXXXXX | QWERTY | XXXXXX | XXXXXX | BACKLT | QK_BOOT  | XXXXXX | MOUSE  | XXXXXX | XXXXXX | VOICE+ | XXXXXX |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | XXXXXX | XXXXXX | XXXXXX | XXXXXX | UPPER  | XXXXXX | XXXXXX | LOWER  | XXXXXX | TEMPO- | VOICE- | TEMPO+ |
  '-----------------------------------------------------------------------------------------------------------'
*/
[LAYER_ADJUST] = LAYOUT_planck_grid(
   XXXXXXX, M_HELP1, M_HELP2, M_HELP3, M_HELP4, M_HELP5, M_HELP6, M_HELP7, M_HELP8, M_HELP9, MU_TOG , AU_TOG  ,
   XXXXXXX, M_BRTOG, M_BSPDU, M_BSPDD, M_BDFLT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
   XXXXXXX, M_QWRTY, XXXXXXX, XXXXXXX, M_BACKL, QK_BOOT, XXXXXXX, M_MOUSE, XXXXXXX, XXXXXXX, MUV_IN , XXXXXXX ,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_UPPER, XXXXXXX, XXXXXXX, M_LOWER, XXXXXXX, TMPO_DN, MUV_DE , TMPO_UP
),

};

#ifdef AUDIO_ENABLE

float tone_my_startup[][2] = SONG(ODE_TO_JOY);
float tone_my_goodbye[][2] = SONG(ROCK_A_BYE_BABY);

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

void persistent_default_layer_set(uint16_t default_layer)
{
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{

    // MACRODOWN only works in this function
    switch(id)
    {

        case MACRO_HELP_1:
            if (record->event.pressed)
            {
				uprintf("1");
            }
            break;

        case MACRO_HELP_2:
            if (record->event.pressed)
            {
				uprintf("2");
            }
            break;

        case MACRO_HELP_3:
            if (record->event.pressed)
            {
				uprintf("3");
            }
            break;

        case MACRO_HELP_4:
            if (record->event.pressed)
            {
				uprintf("4");
            }
            break;

        case MACRO_HELP_5:
            if (record->event.pressed)
            {
				uprintf("5");
            }
            break;

        case MACRO_HELP_6:
            if (record->event.pressed)
            {
				uprintf("6");
            }
            break;

        case MACRO_HELP_7:
            if (record->event.pressed)
            {
				uprintf("7");
            }
            break;

        case MACRO_HELP_8:
            if (record->event.pressed)
            {
				uprintf("8");
            }
            break;

        case MACRO_HELP_9:
            if (record->event.pressed)
            {
				uprintf("9");
            }
            break;

        case MACRO_BREATH_TOGGLE:
            if (record->event.pressed)
            {
              #ifdef BACKLIGHT_BREATHING
                breathing_toggle();
              #endif
            }
            break;

        case MACRO_BREATH_SPEED_INC:
            if (record->event.pressed)
            {
              #ifdef BACKLIGHT_BREATHING
                breathing_period_inc();
              #endif
            }
            break;

        case MACRO_BREATH_SPEED_DEC:
            if (record->event.pressed)
            {
              #ifdef BACKLIGHT_BREATHING
                breathing_period_dec();
              #endif
            }
            break;

        case MACRO_BREATH_DEFAULT:
            if (record->event.pressed)
            {
              #ifdef BACKLIGHT_BREATHING
                breathing_period_default();
              #endif
            }
            break;

        case MACRO_QWERTY:
            if (record->event.pressed)
            {
                persistent_default_layer_set(1UL<<LAYER_QWERTY);
            }
            break;

        case MACRO_UPPER:
            if (record->event.pressed)
            {
                layer_on(LAYER_UPPER);
                #ifdef BACKLIGHT_BREATHING
                  breathing_period_set(2);
                  breathing_pulse();
                #endif
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            else
            {
                layer_off(LAYER_UPPER);
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            break;

        case MACRO_LOWER:
            if (record->event.pressed)
            {
                layer_on(LAYER_LOWER);
                #ifdef BACKLIGHT_BREATHING
                  breathing_period_set(2);
                  breathing_pulse();
                #endif
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            else
            {
                layer_off(LAYER_LOWER);
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            break;

        case MACRO_FUNCTION:
            if (record->event.pressed)
            {
                #ifdef BACKLIGHT_BREATHING
                  breathing_period_set(3);
                  breathing_enable();
                #endif
                layer_on(LAYER_FUNCTION);
            }
            else
            {
                #ifdef BACKLIGHT_BREATHING
                  breathing_period_set(1);
                  breathing_self_disable();
                #endif
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

        case MACRO_MOUSE_MOVE_UL:
            if (record->event.pressed)
            {
              mousekey_on(KC_MS_UP);
              mousekey_on(KC_MS_LEFT);
            }
            else
            {
              mousekey_off(KC_MS_UP);
              mousekey_off(KC_MS_LEFT);
            }
            break;

        case MACRO_MOUSE_MOVE_UR:
            if (record->event.pressed)
            {
              mousekey_on(KC_MS_UP);
              mousekey_on(KC_MS_RIGHT);
            }
            else
            {
              mousekey_off(KC_MS_UP);
              mousekey_off(KC_MS_RIGHT);
            }
            break;

        case MACRO_MOUSE_MOVE_DL:
            if (record->event.pressed)
            {
              mousekey_on(KC_MS_DOWN);
              mousekey_on(KC_MS_LEFT);
            }
            else
            {
              mousekey_off(KC_MS_DOWN);
              mousekey_off(KC_MS_LEFT);
            }
            break;

        case MACRO_MOUSE_MOVE_DR:
            if (record->event.pressed)
            {
              mousekey_on(KC_MS_DOWN);
              mousekey_on(KC_MS_RIGHT);
            }
            else
            {
              mousekey_off(KC_MS_DOWN);
              mousekey_off(KC_MS_RIGHT);
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

#endif /* AUDIO_ENABLE */

        default:
            break;

    }
    return MACRO_NONE;
};


#ifdef AUDIO_ENABLE

void matrix_init_user(void)
{
    set_voice(default_voice);
    startup_user();
    println("Matrix Init");
}

void led_set_user(uint8_t usb_led)
{
    static uint8_t old_usb_led = 0;

    _delay_ms(10); // gets rid of tick

    if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
            // If CAPS LK LED is turning on...
            PLAY_SONG(tone_caps_on);
    }
    else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
            // If CAPS LK LED is turning off...
            PLAY_SONG(tone_caps_off);
    }
    else if ((usb_led & (1<<USB_LED_NUM_LOCK)) && !(old_usb_led & (1<<USB_LED_NUM_LOCK)))
    {
            // If NUM LK LED is turning on...
            PLAY_SONG(tone_numlk_on);
    }
    else if (!(usb_led & (1<<USB_LED_NUM_LOCK)) && (old_usb_led & (1<<USB_LED_NUM_LOCK)))
    {
            // If NUM LED is turning off...
            PLAY_SONG(tone_numlk_off);
    }
    else if ((usb_led & (1<<USB_LED_SCROLL_LOCK)) && !(old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
            // If SCROLL LK LED is turning on...
            PLAY_SONG(tone_scroll_on);
    }
    else if (!(usb_led & (1<<USB_LED_SCROLL_LOCK)) && (old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
            // If SCROLL LED is turning off...
            PLAY_SONG(tone_scroll_off);
    }
    old_usb_led = usb_led;
}


void startup_user()
{
    _delay_ms(10); // gets rid of tick
    PLAY_SONG(tone_my_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_my_goodbye);
    _delay_ms(2000);
    stop_all_notes();
}

void audio_on_user(void)
{
	PLAY_SONG(tone_audio_on);
}

void music_on_user(void)
{
	PLAY_SONG(tone_music_on);
}

void music_scale_user(void)
{
	PLAY_SONG(music_scale);
}

#endif /* AUDIO_ENABLE */
