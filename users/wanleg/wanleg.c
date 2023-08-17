#include "wanleg.h"

// Defines actions for my global custom keycodes. Defined in wanleg.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QW);
		#if defined(RGBLIGHT_ENABLE)
		rgblight_sethsv_noeeprom(0,0,128);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
		#endif
      }
      return false;
      break;
    case GHERKIN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GK);
		#if defined(RGBLIGHT_ENABLE)
        rgblight_sethsv_noeeprom(128,255,64);
		#endif
      }
      return false;
      break;
    case gGHERKIN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(gGK);
		#if defined(RGBLIGHT_ENABLE)
        rgblight_sethsv_noeeprom(128,255,128);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT);
		#endif
      }
      return false;
      break;
    case ONEHAND:
    if (record->event.pressed) {
      set_single_persistent_default_layer(ONE);
      }
      return false;
      break;
    case NUMPAD:
    if (record->event.pressed) {
      set_single_persistent_default_layer(PAD);
      }
      return false;
      break;
    case GHERKIN50:
    if (record->event.pressed) {
      set_single_persistent_default_layer(GK50);
      }
      return false;
      break;
    case SUBTER:
      if (record->event.pressed) {
        layer_on(SUB);
      } else {
        layer_off(SUB);
      }
      return false;
      break;
    case SUPRA:
      if (record->event.pressed) {
        layer_on(SUP);
      } else {
        layer_off(SUP);
      }
      return false;
      break;
	case NUMBER:
      if (record->event.pressed) {
        layer_on(NUM);
      } else {
        layer_off(NUM);
      }
      return false;
      break;
	case DIRECTION:
      if (record->event.pressed) {
        layer_on(DIR);
      } else {
        layer_off(DIR);
      }
      return false;
      break;
	case ETCETERA:
      if (record->event.pressed) {
        layer_on(ETC);
      } else {
        layer_off(ETC);
      }
      return false;
      break;
  case gNUMBER:
      if (record->event.pressed) {
        layer_on(gNUM);
      } else {
        layer_off(gNUM);
      }
      return false;
      break;
  case gDIRECTION:
      if (record->event.pressed) {
        layer_on(gDIR);
      } else {
        layer_off(gDIR);
      }
      return false;
      break;
	case gETCETERA:
      if (record->event.pressed) {
        layer_on(gETC);
      } else {
        layer_off(gETC);
      }
      return false;
      break;
	case FUNCTION:
      if (record->event.pressed) {
        layer_on(_FN);
      } else {
        layer_off(_FN);
      }
      return false;
      break;
  //on RESET, underglow red if present
  case QK_BOOT:
      if (record->event.pressed) {
		  #if defined(RGBLIGHT_ENABLE)
		  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
		  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
		  rgblight_sethsv_noeeprom(HSV_RED);
		  #endif
      }
      return true; // Let QMK send the press/release events as normal
      break;
  }
  return true;
}

/// Turn off LEDs on ProMicros of Let's Split ///
// LEDs only on by default on Let's Split
// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

// Call user matrix init, then call the keymap's init function
void matrix_init_user(void) {
//turn off pro micro LEDs
#if defined(KEYBOARD_lets_split_rev2)
  DDRD &= ~(1<<5);
  PORTD &= ~(1<<5);

  DDRB &= ~(1<<0);
  PORTB &= ~(1<<0);
#endif

//disable backlight breathing for keyboard using random flashing RGB LEDs for backlight
//(breathing provides insufficient power to integrated LED IC)
#if defined(KEYBOARD_kbdfans_kbd6x) && defined(BACKLIGHT_BREATHING)
  breathing_disable();
#endif
  matrix_init_keymap();
}

//at end of firmware startup process, change powerup default layer and underglow colour for kbd6x
void keyboard_post_init_user(void) {
  #if defined(KEYBOARD_kbdfans_kbd6x)
    set_single_persistent_default_layer(_QW);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 5);
    rgblight_sethsv_noeeprom(0,0,128);
  #endif
}
