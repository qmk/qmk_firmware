#include QMK_KEYBOARD_H

enum hardy_layers {
  _MAIN = 0,
  _EXTENDED,
  _GAMING,
  _SETTINGS,
  _MOUSE
};

#define EXT    MO(_EXTENDED)
#define GAME   TT(_GAMING)
#define SET    MO(_SETTINGS)
#define MOUSE  MO(_MOUSE)

//Mods
#define CTL_ESC  LCTL_T(KC_ESC)
#define SFT_SPC  LSFT_T(KC_SPC)
#define SFT_ENT  LSFT_T(KC_ENT)
#define CTR_SFT  MT(MOD_LCTL | MOD_LSFT, KC_PAST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* MAIN */
/* ,-----------------------------------------------------------------------------------------. */
/* | ` ~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  | Del | */
/* |-----------------------------------------------------------------------------------------+ */
/* | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  | Bkspc  | */
/* |-----------------------------------------------------------------------------------------+ */
/* | Ctrl    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    | */
/* |-----------------------------------------------------------------------------------------+ */
/* | LSh | LSh |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  U  |  RShift   | */
/* |-----------------------------------------------------------------------------------------+ */
/* | GAME |  GUI  |  LAlt |    Space     |  EXT  |    Space    | AGr |  L  |  D  |  R  | SET | */
/* `-----------------------------------------------------------------------------------------' */

	[_MAIN] = LAYOUT_all(
/* |---------|--------|--------|-------|--------|-------|--------|--------|--------|--------|--------|--------|--------|--------|--------| */
		 KC_GRV  , KC_1   , KC_2   , KC_3  , KC_4   , KC_5  , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSLS, KC_DEL ,
/* |---------|--------|--------|-------|--------|-------|--------|--------|--------|--------|--------|--------|--------|--------|--------| */
/* |-----------|--------|--------|-------|--------|-------|--------|--------|--------|--------|--------|--------|--------|---------------| */
		  KC_TAB   , KC_Q   , KC_W   , KC_E  , KC_R   , KC_T  , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC,    KC_BSPC    ,
/* |-----------|--------|--------|-------|--------|-------|--------|--------|--------|--------|--------|--------|--------|---------------| */
/* |-------------|--------|--------|-------|--------|-------|--------|--------|--------|--------|---------|--------|---------------------| */
		   CTL_ESC   , KC_A   , KC_S   , KC_D  , KC_F   , KC_G  , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN , KC_QUOT,       KC_ENT        ,
/* |-------------|--------|--------|-------|--------|-------|--------|--------|--------|--------|---------|--------|---------------------| */
/* |-------|--------|--------|-------|-------|-------|--------|--------|--------|---------|--------|--------|--------|---------|---------| */
		CTR_SFT,  MOUSE , KC_Z   , KC_X  , KC_C  , KC_V  , KC_B   , KC_N   , KC_M   , KC_COMM , KC_DOT , KC_SLSH, KC_UP  , KC_LEAD , XXXXXXX ,
/* |-------|--------|--------|-------|-------|-------|--------|--------|--------|---------|--------|--------|--------|---------|---------| */
/* |--------|-----------|--------|---------------------|-----------|----------------------|--------|--------|--------|---------|---------| */
	    GAME  ,  KC_LGUI  , KC_LALT,       SFT_SPC       ,    EXT    ,        SFT_ENT       , KC_RALT, KC_LEFT, KC_DOWN, KC_RIGHT,   SET
/* |--------|-----------|--------|---------------------|-----------|----------------------|--------|--------|--------|---------|---------| */
		),

	[_EXTENDED] = LAYOUT_all(
		KC_ESC                , KC_F1         , KC_F2      , KC_F3          , KC_F4         , KC_F5      , KC_F6   , KC_F7      , KC_F8      , KC_F9       , KC_F10        , KC_F11       , KC_F12       , KC_BSLS      , KC_DEL  ,
 		RESET                 , _______       , KC_UP      , KC_EXEC        , _______       , _______    , _______ , _______    , _______    , KC_PAUS     , KC_SLCK       , KC_INS       , _______      , MO(_SETTINGS),
		_______               , KC_LEFT       , KC_DOWN    , KC_RIGHT       , _______       , _______    , _______ , _______    , KC_MPLY    , _______     , _______       , _______      , KC_PGUP      ,
		_______               , _______       , _______    , KC_MUTE        , KC_VOLD       , KC_VOLU    , KC_MSTP , KC_MPLY    , KC_MPRV    , KC_MNXT     , _______       , _______      , KC_PGUP      , KC_APP        , XXXXXXX ,
		_______               , _______       , _______    , KC_BSPC        , _______       , KC_DEL     , KC_MENU , KC_HOME    , KC_PGDOWN  , KC_END      , MOUSE
		),

	[_GAMING] = LAYOUT_all(
		KC_GESC               , KC_1          , KC_2       , KC_3           , KC_4          , KC_5       , KC_6    , KC_7       , KC_8       , KC_9        , KC_0          , KC_MINS      , KC_EQL       , XXXXXXX       , KC_BSPC ,
		KC_TAB                , KC_Q          , KC_W       , KC_E           , KC_R          , KC_T       , KC_Y    , KC_U       , KC_I       , KC_O        , KC_PSCR       , KC_VOLD      , KC_VOLU      , KC_BSLS       ,
		KC_LSPO               , KC_A          , KC_S       , KC_D           , KC_F          , KC_G       , KC_H    , KC_J       , KC_K       , KC_L        , KC_SCLN       , KC_QUOT      , KC_ENT       ,
		KC_LCTRL              , KC_CAPS       , KC_Z       , KC_X           , KC_C          , KC_V       , KC_B    , KC_N       , KC_M       , KC_COMM     , KC_DOT        , KC_SLSH      , KC_UP        , KC_RSPC       , XXXXXXX ,
		_______               , KC_M          , _______    , _______        , _______       , KC_DEL     , RESET   , KC_HOME    , KC_PGDOWN  , KC_END      , _______
		),

	[_SETTINGS] = LAYOUT_all(
  		RESET                 , M(1)          , M(2)       , M(3)           , M(4)          , M(5)       , M(6)    , M(7)       , M(8)       , M(9)        , M(10)         , KC_BRID      , KC_BRIU      , XXXXXXX       , KC_DEL  ,
		VLK_TOG               , RGB_TOG       , RGB_MOD    , RGB_HUI        , RGB_HUD       , RGB_SAI    , RGB_SAD , RGB_VAI    , RGB_VAD    , _______     , KC_PSCR       , _______      , _______      , _______       ,
  		_______               , _______       , _______    , _______        , _______       , _______    , _______ , _______    , _______    , _______     , _______       , _______      , _______      ,
  		_______               , _______       , _______    , _______        , _______       , _______    , _______ , _______    , _______    , _______     , _______       , _______      , KC_PGUP      , _______       , XXXXXXX ,
  		EEP_RST               , _______       , _______    , KC_TAB         , _______       , KC_DEL     , _______ , KC_HOME    , KC_PGDOWN  , KC_END      , _______
		),

	[_MOUSE] = LAYOUT_all(
		KC_ESC                , KC_F1         , KC_F2      , KC_F3          , KC_F4         , KC_F5      , KC_F6   , KC_F7      , KC_F8      , KC_F9       , KC_MS_ACCEL0  , KC_MS_ACCEL1 , KC_MS_ACCEL2 , XXXXXXX       , KC_DEL  ,
  		KC_MS_WH_UP           , KC_MS_WH_LEFT , KC_MS_UP   , KC_MS_WH_RIGHT , _______       , _______    , _______ , _______    , _______    , KC_PAUS     , _______       , _______      , _______      , RESET         ,
		KC_MS_WH_DOWN         , KC_MS_LEFT    , KC_MS_DOWN , KC_MS_RIGHT    , _______       , _______    , _______ , _______    , KC_MPLY    , _______     , _______       , _______      , KC_MS_BTN1   ,
		_______               , _______       , _______    , KC_MUTE        , KC_VOLD       , KC_VOLU    , KC_MSTP , KC_MPLY    , KC_MPRV    , KC_MNXT     , _______       , KC_MS_BTN3   , KC_MS_UP     , KC_MS_BTN2    , XXXXXXX ,
		_______               , _______       , _______    , KC_MS_BTN1     , KC_MS_BTN3    , KC_MS_BTN2 , KC_MENU , KC_MS_LEFT , KC_MS_DOWN , KC_MS_RIGHT , _______
		),
};

void hardy_layer_state_colors(void) {
	switch (biton32(layer_state)) {
		case _EXTENDED:
			rgblight_sethsv_noeeprom_orange();
			break;
		case _GAMING:
			rgblight_sethsv_noeeprom_green();
			break;
		case _SETTINGS:
			rgblight_sethsv_noeeprom_purple();
			break;
		case _MOUSE:
			rgblight_sethsv_noeeprom_gold();
			break;
		default:
			if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
				rgblight_sethsv_noeeprom_red();
			} else {
				rgblight_sethsv_noeeprom_cyan();
			}
			break;
	}
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
	hardy_layer_state_colors();

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_P) {
      SEND_STRING(":poop:");
    }
    SEQ_TWO_KEYS(KC_Y, KC_Y) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_TWO_KEYS(KC_G, KC_T) {
      register_code(KC_LCTL);
      register_code(KC_LGUI);
      register_code(KC_RGHT);
      unregister_code(KC_RGHT);
      unregister_code(KC_LGUI);
      unregister_code(KC_LCTL);
    }
    SEQ_THREE_KEYS(KC_G, KC_T, KC_T) {
      register_code(KC_LCTL);
      register_code(KC_LGUI);
      register_code(KC_LEFT);
      unregister_code(KC_LEFT);
      unregister_code(KC_LGUI);
      unregister_code(KC_LCTL);
    }
  }
}

