#include QMK_KEYBOARD_H

enum custom_keycodes {
  UP_URL = SAFE_RANGE,
  MAC,
  LINUX,
  COLLAPSE_METHODS_LINUX,
  COLLAPSE_METHODS_MAC,
  SHRUG,
  DISFACE,
  FU,
  TFLIP,
  TFLIP2,
  SAD_EYES,
  TPUT,
  HAPPYFACE,
  HEARTFACE,
  CLOUD,
  CHANFACE,
  CMDCLEAR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [0] = LAYOUT_ortho_4x4(
        KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,   KC_AUDIO_MUTE,   KC_MEDIA_PLAY_PAUSE,
        LCTL(LALT(KC_L)), LSFT(KC_F10),   LCTL(LALT(KC_5)),   LSFT(KC_F6),
        LCTL(KC_E), LCTL(KC_O),  LCTL(KC_SPACE),   LCTL(KC_0),
        COLLAPSE_METHODS_LINUX, LCTL(LSFT(KC_EQUAL)), LINUX, TO(1)
    ),
  [1] = LAYOUT_ortho_4x4(
	 KC_7, KC_8,   KC_9,   KC_ASTR,
        KC_4, KC_5,   KC_6,   KC_SLSH,
        KC_1, KC_2,   KC_3,   KC_MINS,
        KC_0, KC_ENT, KC_DOT, TO(2)
    ),

 /* EMOJI Pad
    * ,-------------------------------.
    * |TFLIP | TFlIP2|DISFACE|   FU   |
    * |------+-------+-------+--------|
    * | CLOUD|       |       | CLEAR  |
    * |------+-------+-------+--------|
    * |SHRUG |DISFACE| HRTFAC| HAPPYF |
    * |------+-------+-------+--------|
    * | ENTER|       |LEDCNTR| tapland| 
    * `-------------------------------'
    */
      //purple
    [2] = LAYOUT_ortho_4x4(
       TFLIP,   TFLIP2,   KC_NO,      FU , 
       CLOUD,   KC_NO,  KC_NO,      CMDCLEAR, 
       SHRUG,   DISFACE,  HEARTFACE,    HAPPYFACE, 
       KC_ENT,  RGB_TOG,  KC_1, TO(0)
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UP_URL:
            if (record->event.pressed) {
                SEND_STRING("http://1upkeyboards.com");
            }
            return false;
            break;
	case MAC:
	    if (record->event.pressed) {
                SEND_STRING("MAC");
            }
            return false;
            break;
	case LINUX:
	    if (record->event.pressed) {
                SEND_STRING("LINUX");
            }
            return false;
            break;
	case COLLAPSE_METHODS_LINUX:
	    if (record->event.pressed) {
		SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_KP_ASTERISK)))"1");
	    }
	    return false;
    	    break;
case COLLAPSE_METHODS_MAC:
	    if (record->event.pressed) {
		SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_KP_ASTERISK)))"1");
	    }
	    return false;
    	    break;
	case CLOUD:       // (っ◕‿◕)っ
            if(record->event.pressed){
                SEND_STRING(SS_LALT("0028+ 3063+ 25D5+ 203F+ 25D5+ 0029+ 3063"));
            }
            return false;
            break;
     case FU:       // t(-_-t)
                if(record->event.pressed){
                    SEND_STRING("t(-_-t)");
                }
                return false;
                break;  
         case HAPPYFACE:       // ʘ‿ʘ 
                if(record->event.pressed){
                     SEND_STRING(SS_LALT("0298+ 203F+ 0298"));
                }
                return false;
                break; 
            case CMDCLEAR:
                if (record->event.pressed) {
                    register_code(KC_LGUI);
                    tap_code(KC_A);                 
                    unregister_code(KC_LGUI);
                    tap_code(KC_DEL);                 
                }
                return false;
                break;  
            case SHRUG: // ¯\_(ツ)_/¯
                if (record->event.pressed) {
                    SEND_STRING(SS_LALT("00AF+ 005C+ 005F+ 0028+ 30C4+ 0029+ 005F+ 002F+ 00AF"));
                }
                return false; 
                break;
            case HEARTFACE:       // ♥‿♥
                if(record->event.pressed){
                    SEND_STRING(SS_LALT("2665+ 203F+ 2665"));
                }
                return false;
                break;  
            case DISFACE:       // ಠ_ಠ 
                if(record->event.pressed){
                    SEND_STRING(SS_LALT("0CA0+ 005F+ 0CA0"));
                }
                return false;
                break;
            case TFLIP:         // (╯°□°)╯ ︵ ┻━┻ 
                if(record->event.pressed){
                    SEND_STRING(SS_LALT("0028+ 256F+ 00B0+ 25A1+ 00B0+ 0029+ 256F+ 0020+ FE35+ 0020+ 253B+ 2501+ 253B"));
                }
                return false;
                break;
            case TFLIP2:         // ┻━┻︵ \(°□°)/ ︵ ┻━┻  
                if(record->event.pressed){
                    SEND_STRING(SS_LALT("253B+ 2501+ 253B+ FE35+ 0020+ 005C+ 0028+ 00B0+ 25A1+ 00B0+ 0029+ 002F+ 0020+ FE35+ 0020+ 253B+ 2501+ 253B"));
                }
                return false;
                break;
                }
    
    return true;
}

void led_set_user(uint8_t usb_led) {

  #ifndef CONVERT_TO_PROTON_C
  /* Map RXLED to USB_LED_NUM_LOCK */
	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		DDRB |= (1 << 0); PORTB &= ~(1 << 0);
	} else {
		DDRB &= ~(1 << 0); PORTB &= ~(1 << 0);
	}

  /* Map TXLED to USB_LED_CAPS_LOCK */
	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRD |= (1 << 5); PORTD &= ~(1 << 5);
	} else {
		DDRD &= ~(1 << 5); PORTD &= ~(1 << 5);
	}
  #endif
}
