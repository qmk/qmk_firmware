#include "helix.h"
#include "bootloader.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#include "LUFA/Drivers/Peripheral/TWI.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

// * If you want to recognize that you pressed the Adjust key with the Lower / Raise key you can enable this comment out. However, the binary size may be over. *
// #define ADJUST_MACRO_ENABLE

// * If you want to use the Kana key you can enable this comment out. However, the binary size may be over. *
// #define KANA_ENABLE

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _BASE = 0,
  _BAS_E,
  _LOWER,
  _LOW_E,
  _RAISE,
  _RAI_E,
  _ADJUST,
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  BAS_E,
  LOWER,
  LOW_E,
  RAISE,
  RAI_E,
  ADJUST,
  EISU,
  #ifdef KANA_ENABLE
  KANA,
  #endif
  RGBRST
};

// JIS key aliases
#define JP_CFTD KC_EQL   // ^ and ~ Circumflex (Hat) and Tilde
#define JP_ATBQ KC_LBRC  // @ and ` Atmark and Back-quote
#define JP_CLAS KC_QUOT  // : and * Colon and Asterisk
#define JP_BSVL KC_JYEN  // \ and | Back slash and and Vertical-line)
#define JP_LBRC KC_RBRC  // [ and { Left-bracket
#define JP_RBRC KC_BSLS  // ] and } Right-bracket
#define JP_BSUS KC_RO    // \ and _ Back slash and Under-score

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty JIS Normal
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |  1!  |  2"  |  3#  |  4$  |  5%  |             |  6&  |  7'  |  8(  |  9)  |   0  |  -=  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | KANJI|   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  @`  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |  ;+  |  :*  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   B  |   N  |   M  |  ,<  |  .>  |  Up  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  |Adjust|Lower |Space |Bksp  |Space |Space |Raise | APP  | Left | Down |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_BASE] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    EISU,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_ATBQ, \
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, JP_CLAS, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT,  \
    KC_LCTL, KC_LALT, KC_LGUI, ADJUST,  LOWER,   KC_SPC,  KC_BSPC, KC_SPC,  KC_SPC,  RAISE,   KC_APP,  KC_LEFT, KC_DOWN, KC_RGHT  \
    ),

  /* Qwerty JIS Exchange L and R
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  6&  |  7'  |  8(  |  9)  |   0  |  -=  |             | Esc  |  1!  |  2"  |  3#  |  4$  |  5%  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   Y  |   U  |   I  |   O  |   P  |  @`  |             | Tab  |   Q  |   W  |   E  |   R  |   T  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   H  |   J  |   K  |   L  |  ;+  |  :*  |             |      |   A  |   S  |   D  |   F  |   G  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |   N  |   M  |  ,<  |  .>  |  /?  |  Up  |Enter |KANJI | Shift|   Z  |   X  |   C  |   V  |   B  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Space |Raise |  }]  | APP  | Left | Down |Right |Adjust| Ctrl | GUI  | Alt  |  [{  |Lower | Bksp |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_BAS_E] = LAYOUT( \
    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,                   KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   \
    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_ATBQ,                   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   \
    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, JP_CLAS,                   XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   \
    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_ENT,  EISU,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   \
    KC_SPC,  RAI_E,   JP_RBRC, KC_APP,  KC_LEFT, KC_DOWN, KC_RGHT, ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, JP_LBRC, LOW_E,   KC_BSPC \
    ),

  /* Lower JIS Normal
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |  -=  |  ^~  |  \|  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |  @`  |  [{  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |  ;+  |  :*  |  ]}  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |  ,<  |  .>  |  /?  |  \_  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      | Del  |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, JP_CFTD, JP_BSVL, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, JP_ATBQ, JP_LBRC, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, KC_SCLN, JP_CLAS, JP_RBRC, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, JP_BSUS, \
    _______, _______, _______, _______, XXXXXXX, XXXXXXX, KC_DEL,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
    ),

  /* Lower JIS Exchange L and R
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |  -=  |  ^~  |  \|  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |  @`  |  [{  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |  ;+  |  :*  |  ]}  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  ,<  |  .>  |  /?  |  \_  |PageUp|      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      | Home |PageDn| End  |      |      |      |      |      |      | Del  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOW_E] = LAYOUT( \
    _______, XXXXXXX, XXXXXXX, KC_MINS, JP_CFTD, JP_BSVL,                   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, JP_ATBQ, JP_LBRC,                   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, XXXXXXX, KC_SCLN, JP_CLAS, JP_RBRC,                   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, KC_COMM, KC_DOT,  KC_SLSH, JP_BSUS, KC_PGUP, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, _______, XXXXXXX, _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, _______, XXXXXXX, _______, KC_DEL   \
    ),

  /* Raise JIS Normal
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      | Home |PageUp|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      | End  |PageDn|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |MsBtn1|MsBtn2|      |      |      |      |      |      |      |      |      | MsUp |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |MsLeft|MsDown|MsRght|
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
    KC_F1  , KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGUP, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_END,  KC_PGDN, \
    _______, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, \
    _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R  \
    ),

  /* Raise JIS Exchange L and R
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |             |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      | MsUp |      |      |      |MsBtn1|MsBtn2|      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |MsLeft|MsDown|MsRght|      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAI_E] = LAYOUT( \
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                    KC_F1  , KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, _______, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, _______, XXXXXXX, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX  \
    ),

  /* Adjust (Lower + Raise) Common map for Normal and Exchange
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|RGBRST|Aud on|Audoff|      |             |      | Reset|RGBRST|Aud on|Audoff|      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |ModNrm|ModExc| Mac  | Win  |      |             |      |ModNrm|ModExc| Mac  | Win  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------|------+
   * |      |RGB ON| HUE+ | SAT+ | VAL+ |      |             |      |RGB ON| HUE+ | SAT+ | VAL+ |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------|------+
   * |      | MODE | HUE- | SAT- | VAL- |      |      |      |      | MODE | HUE- | SAT- | VAL- |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
    XXXXXXX, RESET,   RGBRST,  AU_ON,   AU_OFF,  XXXXXXX,                   XXXXXXX, RESET,   RGBRST,  AU_ON,   AU_OFF,  XXXXXXX, \
    XXXXXXX, BASE,    BAS_E,   AG_NORM, AG_SWAP, XXXXXXX,                   XXXXXXX, BASE,    BAS_E,   AG_NORM, AG_SWAP, XXXXXXX, \
    XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                   XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, \
    XXXXXXX, RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    ),
};

#elif HELIX_ROWS == 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Do it yourself :)
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

#ifdef ADJUST_MACRO_ENABLE
// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
   } else {
    layer_off(layer3);
  }
}
#endif

void toggle_lower_raise_layer(bool pressed, uint16_t dist_layer, uint16_t lower_layer, uint16_t raise_layer) {
  if (pressed) {
    //not sure how to have keyboard check mode and set it to a variable, so my work around
    //uses another variable that would be set to true after the first time a reactive key is pressed.
    if (!TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
      TOG_STATUS = !TOG_STATUS;
      #ifdef RGBLIGHT_ENABLE
        if (dist_layer == _LOWER || dist_layer == _LOW_E) {
          rgblight_mode(16);
        } else {
          rgblight_mode(15);
        }
      #endif
    }

    layer_on(dist_layer);
    #ifdef ADJUST_MACRO_ENABLE
      update_tri_layer_RGB(lower_layer, raise_layer, _ADJUST);
    #endif
  } else {
    #ifdef RGBLIGHT_ENABLE
      rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
    #endif
    TOG_STATUS = false;
    layer_off(dist_layer);
    #ifdef ADJUST_MACRO_ENABLE
      update_tri_layer_RGB(lower_layer, raise_layer, _ADJUST);
    #endif
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BASE:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_BASE);
      }
      return false;
      break;
    case BAS_E:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_BAS_E);
      }
      return false;
      break;
    case LOWER:
      toggle_lower_raise_layer(record->event.pressed, _LOWER, _LOWER, _RAISE);
      return false;
      break;
    case LOW_E:
      toggle_lower_raise_layer(record->event.pressed, _LOW_E, _LOW_E, _RAI_E);
      return false;
      break;
    case RAISE:
      toggle_lower_raise_layer(record->event.pressed, _RAISE, _LOWER, _RAISE);
      return false;
      break;
    case RAI_E:
      toggle_lower_raise_layer(record->event.pressed, _RAI_E, _LOW_E, _RAI_E);
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          #ifdef RGBLIGHT_ENABLE
            rgblight_mode(14);
          #endif
          layer_on(_ADJUST);
        } else {
          #ifdef RGBLIGHT_ENABLE
            rgblight_mode(RGB_current_mode);
          #endif
          layer_off(_ADJUST);
        }
        return false;
        break;
    //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        if (keymap_config.swap_lalt_lgui==false) {
          register_code(KC_LANG2);
        } else {
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    #ifdef KANA_ENABLE
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    #endif
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }

  return true;
  // return process_layer_control(keycode, record, false) ? process_layer_control(keycode, record, true) : true;
}

void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    startup_user();
  #endif
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
    iota_gfx_init(!has_usb());   // turns on the display
  #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
  _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
  _delay_ms(150);
  stop_all_notes();
}

void music_on_user(void)
{
  music_scale_user();
}

void music_scale_user(void)
{
  PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
  iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE _BASE
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)
#define L_LOW_E (1<<_LOW_E)
#define L_RAI_E (1<<_RAI_E)
#define L_ADJUST_TRIE (L_ADJUST|L_RAI_E|L_LOW_E)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  } else {
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[16];
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
      case L_BASE:
        if (default_layer_state == (1UL<<_BAS_E)) {
          matrix_write_P(matrix, PSTR("Base_Ex"));
        } else {
          matrix_write_P(matrix, PSTR("Base"));
        }
        break;
      case L_RAISE:
        matrix_write_P(matrix, PSTR("Raise"));
        break;
      case L_RAI_E:
        matrix_write_P(matrix, PSTR("Raise_Ex"));
        break;
      case L_LOWER:
        matrix_write_P(matrix, PSTR("Lower"));
        break;
      case L_LOW_E:
        matrix_write_P(matrix, PSTR("Lower_Ex"));
        break;
      case L_ADJUST:
      case L_ADJUST_TRI:
      case L_ADJUST_TRIE:
        matrix_write_P(matrix, PSTR("Adjust"));
        break;
      default:
        snprintf(buf, sizeof(buf), "Undef-%d", (short)layer_state);
        matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[32];
  snprintf(led, sizeof(led), "\n%s  %s  %s",
          (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
          (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
          (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if (is_master) {
    render_status(&matrix);
  } else {
    render_logo(&matrix);
  }

  matrix_update(&display, &matrix);
}

#endif
