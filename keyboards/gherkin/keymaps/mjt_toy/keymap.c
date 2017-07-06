#include "gherkin.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

//Friendly Layer Names
enum gherkin_layers {
  _QWERTY,
  _SONGS,
  _DVORAK,
  _PLOVER,
  _ADJUST
};

// custom keycodes
enum gherkin_keycodes {
  QWERTY = SAFE_RANGE,
  SONGS,
  DVORAK,
  PLOVER,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV
};
// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// basic assuming all letters play notes... may not be valid.
  [_QWERTY] = KEYMAP(
		KC_Q,  KC_W, KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,     KC_O,    KC_P,
		KC_A,  KC_S, KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,     KC_L,    LT(_ADJUST,KC_SPC),
		KC_Z,  KC_X, KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_LGUI,  KC_LCTL, KC_LALT)
  ,
  [_SONGS] = KEYMAP(
  		KC_Q,  KC_W, KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,     KC_O,    KC_P,
  		KC_A,  KC_S, KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,     KC_L,    LT(_ADJUST,KC_SPC),
  		KC_Z,  KC_X, KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_LGUI,  KC_LCTL, KC_LALT)
  ,
  [_PLOVER] = KEYMAP(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_1,       KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, KC_C,    KC_V,    XXXXXXX,    KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX)
  ,
  [_ADJUST] = KEYMAP(
  		RESET,    _______,  _______,  _______,    _______,  _______,  _______,  _______,     KC_DEL,    KC_BACKSPACE,
  		MUV_DE,    MUV_IN,    MU_ON,   MU_OFF,      SONGS,  _______,  _______,  _______,     _______,    _______,
  		BACKLIT,  _______,  _______,  _______,    _______,  _______,  _______,  _______,     _______,    _______)

};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    }
    return true;
}


/*
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	keyevent_t event = record->event;

	switch (id) {
        case 0: {
            if (record->event.pressed) {
                key_timer = timer_read(); // if the key is being pressed, we start the timer.
            }
            else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
                if (timer_elapsed(key_timer) > 150) { // 150 being 150ms, the threshhold we pick for counting something as a tap.
                    return MACRO( D(LSFT), END  );
                }
                else {
                    return MACRO( T(N), END  );
                }
            }
            break;
        }
      }
	return MACRO_NONE;
}*/

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
        music_on(); // because it's a toy!
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif

void matrix_scan_user(void) {
}

// don't know what this is doing...
/*
void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		DDRD |= (1 << 5); PORTD &= ~(1 << 5);
	} else {
		DDRD &= ~(1 << 5); PORTD &= ~(1 << 5);
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRB |= (1 << 0); PORTB &= ~(1 << 0);
	} else {
		DDRB &= ~(1 << 0); PORTB &= ~(1 << 0);
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
*/
