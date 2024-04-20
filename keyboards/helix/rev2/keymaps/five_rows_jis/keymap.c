#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include <stdio.h>
#include <string.h>

// * If you want to recognize that you pressed the Adjust key with the Lower / Raise key you can enable this comment out. However, the binary size may be over. *
// #define ADJUST_MACRO_ENABLE

// * If you want to use the Kana key you can enable this comment out. However, the binary size may be over. *
// #define KANA_ENABLE

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
  RGBRST = SAFE_RANGE,
  #ifdef KANA_ENABLE
  EISU,
  KANA,
  #endif
};

// Layer Mode aliases
#define DL_BAS  DF(_BASE)
#define DL_BASE DF(_BAS_E)
#define ML_LOW  MO(_LOWER)
#define ML_LOWE MO(_LOW_E)
#define ML_RAI  MO(_RAISE)
#define ML_RAIE MO(_RAI_E)
#define ML_ADJ  MO(_ADJUST)

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
  [_BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    JP_ZKHK, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, JP_COLN,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT,
    KC_LCTL, KC_LALT, KC_LGUI, ML_ADJ,  ML_LOW,  KC_SPC,  KC_BSPC, KC_SPC,  KC_SPC,  ML_RAI,  KC_APP,  KC_LEFT, KC_DOWN, KC_RGHT
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
  [_BAS_E] = LAYOUT(
    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,                   KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT,                     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, JP_COLN,                   XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_ENT,  JP_ZKHK, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
    KC_SPC,  ML_RAIE, JP_RBRC, KC_APP,  KC_LEFT, KC_DOWN, KC_RGHT, ML_ADJ,  KC_LCTL, KC_LALT, KC_LGUI, JP_LBRC, ML_LOWE, KC_BSPC
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
  [_LOWER] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, JP_CIRC, JP_YEN,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, JP_AT,   JP_LBRC,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, KC_SCLN, JP_COLN, JP_RBRC,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, JP_BSLS,
    _______, _______, _______, _______, XXXXXXX, XXXXXXX, KC_DEL,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
  [_LOW_E] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, KC_MINS, JP_CIRC, JP_YEN,                    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, JP_AT,   JP_LBRC,                   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, KC_SCLN, JP_COLN, JP_RBRC,                   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_COMM, KC_DOT,  KC_SLSH, JP_BSLS, KC_PGUP, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, XXXXXXX, _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, _______, XXXXXXX, _______, KC_DEL
    ),

  /* Raise JIS Normal
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |MsWhL |MsWhU | Home |PageUp| F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |MsWhR |MsWhD | End  |PageDn|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |MsBtn1|MsBtn2| MsUp |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |MsLeft|MsDown|MsRght|
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT(
    _______, KC_F1  , KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_WH_L, KC_WH_U, KC_HOME, KC_PGUP, KC_F12,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_WH_R, KC_WH_D, KC_END,  KC_PGDN, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, KC_MS_U, XXXXXXX,
    _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R
    ),

  /* Raise JIS Exchange L and R
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F6  |  F7  |  F8  |  F9  | F10  | F11  |             |      |  F1  |  F2  |  F3  |  F4  |  F5  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |MsWhL |MsWhU | F12  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |MsWhR |MsWhD |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |MsBtn1|MsBtn2| MsUp |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |MsLeft|MsDown|MsRght|      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAI_E] = LAYOUT(
    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    _______, KC_F1  , KC_F2,   KC_F3,   KC_F4,   KC_F5,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_U, KC_F12,                    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_R, KC_WH_D, XXXXXXX,                   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, KC_MS_U, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, XXXXXXX, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX
    ),

  /* Adjust (Lower + Raise) Common map for Normal and Exchange
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|RGBRST|      |      |      |             |      | Reset|RGBRST|      |      |      |
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
  [_ADJUST] =  LAYOUT(
    XXXXXXX, QK_BOOT, RGBRST,  XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, QK_BOOT, RGBRST,  XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, DL_BAS,  DL_BASE, AG_NORM, AG_SWAP, XXXXXXX,                   XXXXXXX, DL_BAS,  DL_BASE, AG_NORM, AG_SWAP, XXXXXXX,
    XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                   XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,
    XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

#if defined(OLED_ENABLE)
char keylog[24] = {};
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', '-', ' ', '@', ' ', ' ',
    ' ', ';', ':', ' ', ',', '.', '/', ' ', ' ', ' '};

static inline void set_keylog(uint16_t keycode, keyrecord_t *record)
{
  char name = ' ';
  led_t led_state = host_keyboard_led_state();

  if (keycode < 60)
  {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog, sizeof(keylog), "\n%dx%d %2x %c %c %c %c",
           record->event.key.row,
           record->event.key.col,
           keycode,
           name,
          led_state.num_lock ? 'N' : ' ',
          led_state.caps_lock ? 'C' : ' ',
          led_state.scroll_lock ? 'S' : ' '
           );
}
#endif

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT(mode) rgblight_mode(mode)
#else
#define RGBLIGHT(mode)
#endif

// define variables for reactive RGB
int RGB_current_mode;
#ifdef ADJUST_MACRO_ENABLE
// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    RGBLIGHT(RGB_current_mode);
    layer_on(layer3);
   } else {
    layer_off(layer3);
  }
}
#define ADJUST_MACRO(layer1, layer2, layer3) update_tri_layer_RGB(layer1, layer2, layer3)
#else
#define ADJUST_MACRO(layer1, layer2, layer3)
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #if defined(OLED_ENABLE)
    if (record->event.pressed) {
      set_keylog(keycode, record);
    }
  #endif

  switch (keycode) {
    #ifdef RGBLIGHT_ENABLE
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_get_mode();
          }
        break;
    #endif
    #ifdef KANA_ENABLE
      case EISU:
        if (record->event.pressed) {
          if (keymap_config.swap_lalt_lgui==false) {
            register_code(KC_LNG2);
          } else {
            SEND_STRING(SS_LALT("`"));
          }
        } else {
          unregister_code(KC_LNG2);
        }
        break;
      case KANA:
        if (record->event.pressed) {
          if(keymap_config.swap_lalt_lgui==false){
            register_code(KC_LNG1);
          }else{
            SEND_STRING(SS_LALT("`"));
          }
        } else {
          unregister_code(KC_LNG1);
        }
        break;
    #endif
    #ifdef RGBLIGHT_ENABLE
      case RGBRST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_get_mode();
          }
        break;
    #endif
    default:
      return true;
  }

  return false;
}

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_get_mode();
  #endif
}

//OLED update loop
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_180;
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

const char helix_logo[]={
  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
  0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
  0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
  0};

static inline void render_logo(void) {
  oled_write(helix_logo, false);
}

const char mac_win_logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};

static inline void render_status(void) {
  char buf[20];
  // Render to mode icon
  if(keymap_config.swap_lalt_lgui==false){
    oled_write(mac_win_logo[0][0], false);
    oled_write_P(PSTR("\n"), false);
    oled_write(mac_win_logo[0][1], false);
  } else {
    oled_write(mac_win_logo[1][0], false);
    oled_write_P(PSTR("\n"), false);
    oled_write(mac_win_logo[1][1], false);
  }

  #ifdef RGBLIGHT_ENABLE
    snprintf(buf, sizeof(buf), "  LED mode:%d", (short)RGB_current_mode);
    oled_write(buf, false);
  #endif

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  oled_write_P(PSTR("\nLayer: "), false);
  switch (layer_state) {
    case L_BASE:
      oled_write_P(default_layer_state == (1UL<<_BAS_E) ? PSTR("BaseEx") : PSTR("Base"), false);
      break;
    case L_RAISE:
      oled_write_P(PSTR("Raise"), false);
      break;
    case L_RAI_E:
      oled_write_P(PSTR("RaiseEx"), false);
      break;
    case L_LOWER:
      oled_write_P(PSTR("Lower"), false);
      break;
    case L_LOW_E:
      oled_write_P(PSTR("LowerEx"), false);
      break;
    case L_ADJUST:
    case L_ADJUST_TRI:
    case L_ADJUST_TRIE:
      oled_write_P(PSTR("Adjust"), false);
      break;
    default:
      snprintf(buf, sizeof(buf), "%d", (short)layer_state);
      oled_write(buf, false);
  }

  oled_write(keylog, false);
}

bool oled_task_user(void) {

#    if DEBUG_TO_SCREEN
    if (debug_enable) {
        return;
    }
#    endif

  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
  }

  return false;
}

#endif // end of OLED_ENABLE
