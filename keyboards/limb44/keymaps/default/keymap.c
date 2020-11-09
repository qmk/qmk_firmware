////
//A01:LowerとRaiseにF13とF14を割り当て
//B01:コード入力マクロ
////


#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _MOUSECURSOR 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  CODE,//B01
  MOUSECURSOR
};


/*keycord変換*/
#define KC_TGMSC TG(_MOUSECURSOR)	//MSCレイヤに切り替え
#define KC_MOMSC MO(_MOUSECURSOR)	//押している間MSCレイヤ
#define KC_CTLC LCTL(KC_C)			//Ctrl+C
#define KC_CTLV LCTL(KC_V)			//Ctrl+V
#define KC_CTLZ LCTL(KC_Z)			//Ctrl+Z
#define KC_CTLX LCTL(KC_X)			//Ctrl+X
#define SPC_MSC LT(_MOUSECURSOR,KC_SPC)
#define ALT_SPC ALT_T(KC_SPC)   //HOLDでALT、TAPでSPC
#define ALT_TAB RALT(KC_TAB)    //ALT+TAB
#define KC_HNKN LALT(KC_GRV)       //ALT+"`"

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          TAB,       Q,       W,       E,       R,       T,                            Y,       U,       I,       O,      P,     MINS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         LCTL,       A,       S,       D,       F,       G,                            H,       J,       K,       L,    SCLN,    QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         LSFT,       Z,       X,       C,       V,       B,                            N,       M,    COMM,     DOT,    SLSH,    RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    LALT,    LGUI,   LOWER,     SPC,        ENT,  RAISE,     RGUI,    RALT \
                              //`----------------------------------'  `-----------------------------------'

  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          ESC,    EXLM,      AT,    HASH,     DLR,    PERC,                         CIRC,    AMPR,    ASTR,    LPRN,    RPRN,     GRV,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         LCTL,       1,       2,       3,       4,       5,                         PMNS,     EQL,    LBRC,    RBRC,    BSLS,    TILD,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        MOMSC,       6,       7,       8,       9,       0,                         UNDS,    PPLS,    LCBR,    RCBR,    PIPE,    RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    LALT,    BSPC,   LOWER,     ENT,        ENT,  RAISE,     RGUI,    RALT \
                              //`----------------------------------'  `-----------------------------------'
    ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          ESC,      F1,      F2,      F3,      F4,      F5,                           F6,      F7,      F8,      F9,     F10,     DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         LCTL,     F11,     F12, XXXXXXX, XXXXXXX, XXXXXXX,                         LEFT,    DOWN,      UP,    RGHT,    WH_U,    BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         LSFT,    PSCR,    PAUS, XXXXXXX, XXXXXXX,    CODE,                          END,    PGDN,    PGUP,    HOME,    WH_D,    RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    LALT,    LGUI,   LOWER,     SPC,        ENT,  RAISE,     RGUI,  TGMSC \
                              //`----------------------------------'  `-----------------------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET,  RGBRST,RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX,                         PAST,      P7,      P8,      P9, XXXXXXX,    HNKN,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                         PMNS,      P4,      P5,      P6, XXXXXXX,    BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                         PPLS,      P1,      P2,      P3, XXXXXXX,    RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    LALT,    LGUI,   LOWER,     SPC,        ENT,  RAISE,     RGUI,      P0 \
                              //`----------------------------------'  `-----------------------------------'
  ),

  [_MOUSECURSOR] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    WH_L,      UP,    WH_R, XXXXXXX, XXXXXXX,                      XXXXXXX,    WH_L,    MS_U,    WH_R, XXXXXXX,     DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    LEFT,    DOWN,    RGHT, XXXXXXX, XXXXXXX,                      XXXXXXX,    MS_L,    MS_D,    MS_R,    WH_U,    BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    CTLZ,    CTLX,    CTLC,    CTLV, XXXXXXX,                      XXXXXXX, XXXXXXX,    BTN3,    BTN2,    WH_D,    RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    LALT,    LGUI,   LOWER,     SPC,        ENT,    BTN1,   TGMSC,    RALT \
                              //`----------------------------------'  `-----------------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

//A01 From
static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;
//A01 To

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
	  break;//A01
    case LOWER:
      if (record->event.pressed) {
      	lower_pressed = true;//A01
      	lower_pressed_time = record->event.time;//A01

        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
//A01 From
      	if (lower_pressed && (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)){
      		register_code(KC_LANG2); //for MacOS
      		//register_code(KC_MHEN);
      		register_code(KC_F13);
      		unregister_code(KC_LANG2);//for MacOS
      		unregister_code(KC_F13);
      		//unregister_code(KC_MHEN);
      	}
      	lower_pressed = false;
      }
      return false;
	  break;
//A01 To
    case RAISE:
      if (record->event.pressed) {
      	raise_pressed = true;//A01
      	raise_pressed_time = record->event.time;//A01

        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
//A01 From
      	if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)){
      		register_code(KC_LANG1); //for MacOS
      		//register_code(KC_HENK);
      		register_code(KC_F16);
      		unregister_code(KC_LANG1);//for MacOS
      		unregister_code(KC_F16);
      		//unregister_code(KC_HENK);
      	}
      	raise_pressed = false;
      }
      return false;
  	  break;
//A01 To
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
//B01 From
   case CODE:
  	if(record->event.pressed) {
  		SEND_STRING("yorosikuonegaiitasimasu.");
  	}
	return false;
  	break;
//B01 To
//A01 From
  default:
  	if (record->event.pressed){
  		//reset the flag
  		lower_pressed = false;
  		raise_pressed = false;
  		}
//A01 To
  	break;
  }
  return true;
}