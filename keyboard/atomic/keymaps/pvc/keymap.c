#include "atomic.h"
#include "action_layer.h"
#include "led.h"

#ifdef AUDIO_ENABLE
#include "audio.h"
#include "song_list.h"
#endif

#define _QW 0
#define _LW 1
#define _RS 2
#define _AD 3
#define _FN 4
#define _MUSIC 4

#define M_QW 0
#define M_LW 1
#define M_RS 2
#define M_FN 3
#define M_T1 4
#define M_T2 5
#define M_T3 6
#define M_T4 7
#define M_TU 8
#define M_TD 9
#define M_DF 10
#define M_MUSIC_ON  11
#define M_MUSIC_OFF 12
#define M_AUDIO_ON  13
#define M_AUDIO_OFF 14

#define TIMBR_1 M(M_T1)
#define TIMBR_2 M(M_T2)
#define TIMBR_3 M(M_T3)
#define TIMBR_4 M(M_T4)
#define TMPO_UP M(M_TU)
#define TMPO_DN M(M_TD)
#define TMPO_DF M(M_DF)


#define MUS_ON  M(M_MUSIC_ON)
#define MUS_OFF M(M_MUSIC_OFF)
#define AUD_OFF M(M_AUDIO_OFF)
#define AUD_ON  M(M_AUDIO_ON)


#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

/*
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | XXXXXX . BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * | CAPS   | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | XXXXXX . ENTER  | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | XXXXXX . RSHIFT | UP     | PG DN  |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | RAISED | XXXXXX . SPACE  | LOWER  | RALT   | HOME   | END    | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_QW] = { /* QWERTY */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, XXXXXXX  },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL   },
  { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  XXXXXXX, KC_PGUP  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, XXXXXXX, KC_UP,   KC_PGDN  },
  { KC_LCTL, KC_LGUI, M(M_FN), KC_LALT, M(M_RS), KC_SPC,  XXXXXXX, M(M_LW), KC_RALT, KC_HOME, KC_END,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  },
 },
 [_LW] = { /* LOWERED */
  { KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___T___, ___T___  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS   },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },
 [_RS] = { /* RAISED */
  { KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___T___, ___T___  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS   },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },
 [_FN] = { /* FUNCTION */
  { KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___T___, ___T___  },
  { KC_SLCK, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_PAUS, KC_PSCR  },
  { KC_CAPS, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, KC_ACL0, KC_ACL2, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, ___T___, ___T___, KC_WH_U  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, KC_MS_U, KC_WH_D  },
  { _______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R  },
 },
 [_AD] = { /* ADJUST */
  { _______, TIMBR_1, TIMBR_2, TIMBR_3, TIMBR_4, TMPO_UP, TMPO_DN, TMPO_DF, _______, MUS_ON,  MUS_OFF, AUD_ON,  AUD_OFF, ___T___, ___T___  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______  },
  { _______, _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, ___T___, ___T___, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },
[_MUSIC] = {
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
}

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

#endif /* AUDIO_ENABLE */


void update_quad_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3, uint8_t layer4, bool order)
{
	if (order)
	{
		if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2))
		{
			layer_on(layer3);
		}
		else
		{
		    layer_off(layer3);
		    layer_off(layer4);
		}
	}
	else
	{
		if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2))
		{
			layer_on(layer4);
		}
		else
		{
			layer_off(layer3);
		    layer_off(layer4);
		}
	}
}


const uint16_t PROGMEM fn_actions[] = {
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{

	// MACRODOWN only works in this function
	switch(id)
	{
		case M_LW:
			if (record->event.pressed) {
				layer_on(_LW);
				update_tri_layer(_LW, _RS, _AD);
			} else {
				layer_off(_LW);
				update_tri_layer(_LW, _RS, _AD);
			}
			break;
		case M_RS:
			if (record->event.pressed) {
				layer_on(_RS);
				update_tri_layer(_LW, _RS, _AD);
			} else {
				layer_off(_RS);
				update_tri_layer(_LW, _RS, _AD);
			}
			break;

		case M_FN:
			if (record->event.pressed) {
				layer_on(_FN);
			} else {
				layer_off(_FN);
			}
			break;

		case M_T1:
			if (record->event.pressed) set_timbre(TIMBRE_12);
			break;

		case M_T2:
			if (record->event.pressed) set_timbre(TIMBRE_25);
			break;

		case M_T3:
			if (record->event.pressed) set_timbre(TIMBRE_50);
			break;

		case M_T4:
			if (record->event.pressed) set_timbre(TIMBRE_75);
			break;


		case M_TU:
			if (record->event.pressed) increase_tempo(10);
			break;

		case M_TD:
			if (record->event.pressed) decrease_tempo(10);
			break;

		case M_DF:
			if (record->event.pressed)
			{
				set_timbre(TIMBRE_DEFAULT);
				set_tempo(TEMPO_DEFAULT);
			}
			break;

		case M_AUDIO_OFF:
			if (record->event.pressed) {
				#ifdef AUDIO_ENABLE
				audio_off();
				#endif
			}
			break;

		case M_AUDIO_ON:
			if (record->event.pressed)
			{
				#ifdef AUDIO_ENABLE
				audio_on();
				PLAY_NOTE_ARRAY(tone_audio_on, false, STACCATO);
				#endif
			}
			break;

		case M_MUSIC_ON:
			if (record->event.pressed)
			{
				#ifdef AUDIO_ENABLE
				PLAY_NOTE_ARRAY(tone_music_on, false, STACCATO);
				layer_on(_MUSIC);
				#endif
			}
			break;

		case M_MUSIC_OFF:
			if (record->event.pressed)
			{
				#ifdef AUDIO_ENABLE
				layer_off(_MUSIC);
				stop_all_notes();
				#endif
			}
			break;

		default:
			break;

	}
	return MACRO_NONE;
};


#ifdef AUDIO_ENABLE

uint8_t starting_note = 0x0C;
int offset = 7;


void process_action_user(keyrecord_t *record)
{
	if (IS_LAYER_ON(_MUSIC))
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
	init_notes();
	play_startup_tone();
	println("Matrix Init");
}

void led_set_user(uint8_t usb_led)
{
	static uint8_t old_usb_led = 0;

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
	PLAY_NOTE_ARRAY(tone_my_startup, false, STACCATO);
}

void play_goodbye_tone()
{
	PLAY_NOTE_ARRAY(tone_my_goodbye, false, STACCATO);
	_delay_ms(2000);
}

#endif /* AUDIO_ENABLE */
