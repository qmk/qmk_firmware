#include QMK_KEYBOARD_H
#include "drashna.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;
extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum crkbd_keycodes {
  RGBRST = NEW_SAFE_RANGE
};

#define LAYOUT_crkbd_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,                        K06,     K07,     K08,     K09,     K0A,     KC_MINS, \
    KC_TAB, ALT_T(K11),  K12, K13,      K14,     K15,                        K16,     K17,     K18,     K19,     K1A, RGUI_T(KC_QUOT), \
    OS_LSFT, CTL_T(K21), K22, K23,      K24,     K25,                        K26,     K27,     K28,     K29,  CTL_T(K2A), OS_RSFT, \
                           LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,     KC_DEL,  KC_ENT,  RAISE                                        \
  )
#define LAYOUT_crkbd_base_wrapper(...)       LAYOUT_crkbd_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_crkbd_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),

  [_COLEMAK] = LAYOUT_crkbd_base_wrapper(
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
  ),

  [_DVORAK] = LAYOUT_crkbd_base_wrapper(
    _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
    _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
    _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
  ),

  [_WORKMAN] = LAYOUT_crkbd_base_wrapper(
    _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
  ),

  [_NORMAN] = LAYOUT_crkbd_base_wrapper(
    _________________NORMAN_L1_________________, _________________NORMAN_L1_________________,
    _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
    _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
  ),

  [_MALTRON] = LAYOUT_crkbd_base_wrapper(
    _________________MALTRON_L1________________, _________________MALTRON_R1________________,
    _________________MALTRON_L2________________, _________________MALTRON_R2________________,
    _________________MALTRON_L3________________, _________________MALTRON_R3________________
  ),

  [_EUCALYN] = LAYOUT_crkbd_base_wrapper(
    _________________EUCALYN_L1________________, _________________EUCALYN_R1________________,
    _________________EUCALYN_L2________________, _________________EUCALYN_R2________________,
    _________________EUCALYN_L3________________, _________________EUCALYN_R3________________
  ),

  [_CARPLAX] = LAYOUT_crkbd_base_wrapper(
    _____________CARPLAX_QFMLWY_L1_____________, _____________CARPLAX_QFMLWY_R1_____________,
    _____________CARPLAX_QFMLWY_L2_____________, _____________CARPLAX_QFMLWY_R2_____________,
    _____________CARPLAX_QFMLWY_L3_____________, _____________CARPLAX_QFMLWY_R3_____________
  ),

  [_MODS] = LAYOUT_wrapper(
      _______, ___________________BLANK___________________,                  ___________________BLANK___________________, _______,
      _______, ___________________BLANK___________________,                  ___________________BLANK___________________, _______,
      KC_LSFT, ___________________BLANK___________________,                  ___________________BLANK___________________, KC_RSFT,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_LOWER] = LAYOUT_wrapper(
    KC_F11,  _________________LOWER_L1__________________,                    _________________LOWER_R1__________________, KC_F11,
    KC_F12,  _________________LOWER_L2__________________,                    _________________LOWER_R2__________________, KC_PIPE,
    _______, _________________LOWER_L3__________________,                    _________________LOWER_R3__________________, _______,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_RAISE] = LAYOUT_wrapper( \
    _______, _________________RAISE_L1__________________,                    _________________RAISE_R1__________________, _______,
    _______, _________________RAISE_L2__________________,                    _________________RAISE_R2__________________, KC_BSLS,
    _______, _________________RAISE_L3__________________,                    _________________RAISE_R3__________________, _______,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_wrapper( \
    KC_MAKE, _________________ADJUST_L1_________________,                    _________________ADJUST_R1_________________, KC_RESET,
    VRSN,    _________________ADJUST_L2_________________,                    _________________ADJUST_R2_________________, EEP_RST,
    _______, _________________ADJUST_L3_________________,                    _________________ADJUST_R3_________________, KC_MPLY,
                                     _______, _______, _______,        KC_NUKE, TG_MODS, _______
  )
};

void matrix_init_keymap(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
  #endif

  #ifndef CONVERT_TO_PROTON_C
    setPinOutput(D5);
    writePinHigh(D5);

    setPinOutput(B0);
    writePinHigh(B0);
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);
char layer_state_str[24];
char modifier_state_str[24];
char host_led_state_str[24];
char keylog_str[24] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;

// const char *read_mode_icon(bool swap);
// void set_timelog(void);
// const char *read_timelog(void);

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }
  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}


const char* read_modifier_state(void) {
  uint8_t modifiers = get_mods();
  uint8_t one_shot = get_oneshot_mods();

  snprintf(modifier_state_str, sizeof(modifier_state_str), "Mods:%s %s %s %s",
    (modifiers & MOD_MASK_CTRL || one_shot & MOD_MASK_CTRL) ? "CTL" : "   ",
    (modifiers & MOD_MASK_GUI || one_shot & MOD_MASK_GUI) ? "GUI" : "   ",
    (modifiers & MOD_MASK_ALT || one_shot & MOD_MASK_ALT) ? "ALT" : "   ",
    (modifiers & MOD_MASK_SHIFT || one_shot & MOD_MASK_SHIFT) ? "SFT" : "   "
  );

  return modifier_state_str;
}

const char *read_host_led_state(void) {
  uint8_t leds = host_keyboard_leds();

  snprintf(host_led_state_str, sizeof(host_led_state_str), "NL:%s CL:%s SL:%s",
    (leds & (1 << USB_LED_NUM_LOCK)) ? "on" : "- ",
    (leds & (1 << USB_LED_CAPS_LOCK)) ? "on" : "- ",
    (leds & (1 << USB_LED_SCROLL_LOCK)) ? "on" : "- "
  );

  return host_led_state_str;
}

const char* read_layer_state(void) {
  switch (biton32(layer_state)) {
    case _RAISE:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise  ");
      break;
    case _LOWER:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower  ");
      break;
    case _ADJUST:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust ");
      break;
    default:
      switch (biton32(default_layer_state)) {
        case _QWERTY:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Qwerty ");
          break;
        case _COLEMAK:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Colemak");
          break;
        case _DVORAK:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Dvorak ");
          break;
        case _WORKMAN:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Workman");
          break;
      }
      break;
  }

    return layer_state_str;
}

void matrix_scan_keymap(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    //If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_modifier_state());
    // matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    // matrix_write(matrix, read_host_led_state());
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

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_A ... KC_SLASH:
    case KC_F1 ... KC_F12:
    case KC_INSERT ... KC_UP:
    case KC_KP_SLASH ... KC_KP_DOT:
    case KC_F13 ... KC_F24:
    if (record->event.pressed) { set_keylog(keycode, record); }
      break;
    // set_timelog();
  }
  return true;
}

#endif
