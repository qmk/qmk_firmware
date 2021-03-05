#include QMK_KEYBOARD_H
#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familiar enough to know which is better or why...
static const char * const secrets[] = {
  "test1",
  "test2"
};
#endif

/* Name Layers */
enum layers {
  _BASE,
  _NAV_ETC,
  _MOUSE_F,
  _SYMBOLS,
  _RGB_MEDIA,
  _WORDS,
};

/* Macros */
enum custom_keycodes {
  PLEAD = SAFE_RANGE,
  THANK,
  KC_SECRET_1,
  KC_SECRET_2
};

/* Layer Tap */
  #define NAV_ESC LT(_NAV_ETC, KC_ESC)
  #define PGU_MS_F LT(_MOUSE_F, KC_PGUP)
  #define ENT_SYM LT(_SYMBOLS, KC_ENT)
  #define RGB_RIGHT LT(_RGB_MEDIA, KC_RIGHT)
/* Mod Tap */
  #define ALT_TAB LALT_T(KC_TAB)
  #define CTL_MIN RCTL_T(KC_MINUS)
  #define GUI_LEFT RGUI_T(KC_LEFT)
  #define ALT_DOWN RALT_T(KC_DOWN)
  #define CTL_UP RCTL_T(KC_UP)
  #define PGD_GUI LGUI_T(KC_PGDOWN)
/* Shortcuts */
  #define SCREEN_CAP LSFT(LGUI(KC_4))
  #define SCRN_BRIT KC_F15
  #define SCRN_DARK KC_F14
  #define COPY LGUI(KC_C)
  #define PASTE LGUI(KC_V)
/* Amethyst */
  #define AM_1 LCTL_T(KC_F4)
  #define AM_2 LALT_T(KC_F2)
  #define AM_3 LGUI_T(KC_F3)
  #define AM_LEFT LALT(LCTL(LSFT(KC_2)))
  #define AM_RITE LALT(LCTL(LSFT(KC_1)))
  #define AM_CYCLE LSFT(LALT(LCTL(KC_SPC)))
  #define AM_CW LSFT(LALT(KC_J))
  #define AM_CCW LSFT(LALT(KC_K))
/* Mission Control */
  #define DESK_L RCTL(KC_LEFT)
  #define DESK_R RCTL(KC_RIGHT)
  #define DESKTOP KC_F11
  #define MISSION RCTL(KC_UP)
/* Audio */
  #define VOL_D KC_AUDIO_VOL_DOWN
  #define VOL_U KC_AUDIO_VOL_UP
  #define MUTE KC_AUDIO_MUTE
/* Abbreviations */
  #define CAPS KC_CAPSLOCK
  #define DEL KC_DELETE
  #define R_PAREN KC_RIGHT_PAREN
  #define L_PAREN KC_LEFT_PAREN
  #define MS_WH_U KC_MS_WH_UP
  #define MS_WH_D KC_MS_WH_DOWN
  #define L_CLICK KC_MS_BTN1
  #define R_CLICK KC_MS_BTN2
  #define MS_L KC_MS_LEFT
  #define MS_D KC_MS_DOWN
  #define MS_U KC_MS_UP
  #define MS_R KC_MS_RIGHT
  #define LEFT KC_LEFT
  #define RIGHT KC_RIGHT
/* TEXT NAV */
  #define ALT_L RALT(KC_LEFT)
  #define ALT_R RALT(KC_RIGHT)
  #define GUI_L RGUI(KC_LEFT)
  #define GUI_R RGUI(KC_RIGHT)
  #define GUI_BSPC RGUI(KC_BSPC)
/* APP nav */
  #define ALT_D RALT(KC_DOWN)
  #define ALT_U RALT(KC_UP)
  #define WEB_B RGUI(KC_LBRC)
  #define WEB_F RGUI(KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT_ortho_4x12(
		ALT_TAB , KC_Q, KC_W , KC_E , KC_R    , KC_T    , KC_Y   , KC_U     , KC_I     , KC_O     , KC_P    , KC_BSPC   ,
		NAV_ESC , KC_A, KC_S , KC_D , KC_F    , KC_G    , KC_H   , KC_J     , KC_K     , KC_L     , KC_SCLN , KC_QUOT  ,
		KC_LSFT , KC_Z, KC_X , KC_C , KC_V    , KC_B    , KC_N   , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH , CTL_MIN   ,
		AM_LEFT , AM_1, AM_2 , AM_3 , PGD_GUI , ENT_SYM , KC_SPC , PGU_MS_F , GUI_LEFT , ALT_DOWN , CTL_UP  , RGB_RIGHT
  ),

	[_NAV_ETC] = LAYOUT_ortho_4x12(
		CAPS    , _______ , ALT_U  , _______  , KC_BSPC    , _______   , GUI_L    , KC_END  , KC_HOME , GUI_R   , _______ , GUI_BSPC ,
		_______ , WEB_B   , ALT_D  , WEB_F    , DEL        , _______    , LEFT     , KC_DOWN , KC_UP   , RIGHT   , _______ , _______  ,
		_______ , _______ , _______ , _______  , _______    , _______    , ALT_L    , _______ , _______ , ALT_R   , _______ , _______  ,
		AM_RITE , AM_CW   , AM_CCW  , AM_CYCLE , MO(_WORDS) , SCREEN_CAP , _______  , _______ , DESK_L  , DESKTOP , MISSION , DESK_R
	),

	[_SYMBOLS] = LAYOUT_ortho_4x12(
		_______ , KC_RCBR , KC_RBRC , R_PAREN , KC_GRAVE , _______ , _______ , KC_7 , KC_8    , KC_9    , KC_EQL   , _______ ,
		_______ , KC_LCBR , KC_LBRC , L_PAREN , KC_TILDE , _______ , _______ , KC_4 , KC_5    , KC_6    , KC_COLON , KC_BSLS ,
		_______ , _______ , _______ , COPY    , PASTE    , _______ , _______ , KC_1 , KC_2    , KC_3    , _______  , _______ ,
		_______ , _______ , _______ , _______ , _______  , _______ , KC_DOT  , KC_0 , _______ , _______ , _______  , _______
	),

	[_MOUSE_F] = LAYOUT_ortho_4x12(
		KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  ,
		_______ , _______ , MS_WH_U , MS_WH_D , L_CLICK , R_CLICK , MS_L    , MS_D    , MS_U    , MS_R    , _______ , _______ ,
		_______ , _______ , KC_ACL0 , KC_ACL1 , KC_ACL2 , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
	),

	[_RGB_MEDIA] = LAYOUT_ortho_4x12(
		_______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______   , _______   , _______ , DEL     ,
		_______ , RGB_TOG , RGB_MOD , RGB_HUI , RGB_HUD , _______ , _______ , _______ , _______   , _______   , _______ , _______ ,
		_______ , BL_TOGG , BL_STEP , _______ , _______ , RESET   , _______ , _______ , VOL_D     , VOL_U     , MUTE    , _______ ,
		_______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , SCRN_DARK , SCRN_BRIT , _______ , _______
  ),

	[_WORDS] = LAYOUT_ortho_4x12(
		_______ , _______ , _______  , _______ , PLEAD       , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______  , _______ , KC_SECRET_1 , _______ , _______ , THANK   , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______  , _______ , KC_SECRET_2 , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
		_______ , _______ , _______  , _______ , _______     , _______ , _______ , _______ , _______ , _______ , _______ , _______
	),

/* 	[BLANK] = LAYOUT_ortho_4x12( */
/* 		_______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , */
/* 		_______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , */
/* 		_______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , */
/* 		_______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ */
/* 	), */

};

void matrix_init_user(void) {
  /* RGBLIGHT_ANIMATIONS = 10; */
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SECRET_1 ... KC_SECRET_2: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secrets[keycode - KC_SECRET_1], MACRO_TIMER);
      }
      break;
    case THANK:
      if (record->event.pressed) {
        SEND_STRING("Thanks!");
      } else {
      }
      break;
    case PLEAD:
      if (record->event.pressed) {
        SEND_STRING("Please take a look at my PR:");
      } else {
      }
      break;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

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

enum combo_events {
  ALFRED,
  TERMINAL
};

const uint16_t PROGMEM call_alfred[] = {KC_F, KC_J, COMBO_END};
const uint16_t PROGMEM terminal_hotkey[] = {KC_F, KC_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [ALFRED] = COMBO_ACTION(call_alfred),
  [TERMINAL] = COMBO_ACTION(terminal_hotkey)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
 switch(combo_index) {
   case ALFRED:
     if (pressed) {
       tap_code16(LGUI(KC_SPC));
     }
     break;
   case TERMINAL:
     if (pressed) {
       tap_code16(KC_NUMLOCK);
     }
     break;
 }
}
