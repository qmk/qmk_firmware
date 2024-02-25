#include QMK_KEYBOARD_H

#ifdef VIA_ENABLE
  #include "via.h"
#endif

enum keycodes {
  KC_CYCLE_LAYERS = QK_USER,
};

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
      KC_MEDIA_PLAY_PAUSE,
      KC_CYCLE_LAYERS, KC_KP_2, KC_KP_3, KC_KP_4, KC_KP_5,
      KC_KP_6, KC_KP_7, KC_KP_8, LCTL(KC_LEFT), LCTL(KC_RIGHT)
  ),
  [1] = LAYOUT(
      _______,
      KC_CYCLE_LAYERS, _______, _______, _______, _______,
      _______, _______, _______, _______, _______
  ),
  [2] = LAYOUT(
      _______,
      KC_CYCLE_LAYERS, _______, _______, _______, _______,
      _______, _______, _______, _______, _______
  ),
  [3] = LAYOUT(
      _______,
      KC_CYCLE_LAYERS, _______, _______, _______, _______,
      _______, _______, _______, _______, _______
  ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
  [1] = { ENCODER_CCW_CW(_______, _______) },
  [2] = { ENCODER_CCW_CW(_______, _______) },
  [3] = { ENCODER_CCW_CW(_______, _______) }
};
#endif


#ifdef OLED_ENABLE

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
  };

  oled_write_raw_P(qmk_logo, sizeof(qmk_logo));
}

enum DisplayMode {
    LOGO_MODE,
    TEXT_MODE
};

static enum DisplayMode display_mode = LOGO_MODE;

bool oled_task_user(void) {
  if (display_mode == LOGO_MODE) {
      render_qmk_logo();
      display_mode = TEXT_MODE;
  } else if (display_mode == TEXT_MODE) {
      // Set cursor position
    oled_set_cursor(0, 0);
    // Switch on current active layer
    switch (get_highest_layer(layer_state)) {
        case 0 :
            oled_write("Layer 1", false);
            break;
        case 1 :
            oled_write("Layer 2", false);
            break;
        case 2 : 
            oled_write("Layer 3", false);
            break;
        case 3 :
            oled_write("Layer 4", false);
            break;
    }
  }
  return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (display_mode == LOGO_MODE) {
    display_mode = TEXT_MODE; // Переключаемся на отображение текста
  }
  switch (keycode) {
    case KC_CYCLE_LAYERS:
      // Our logic will happen on presses, nothing is done on releases
      if (!record->event.pressed) { 
        // We've already handled the keycode (doing nothing), let QMK know so no further code is run unnecessarily
        return false;
      }

      uint8_t current_layer = get_highest_layer(layer_state);

      // Check if we are within the range, if not quit
      if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
        return false;
      }

      uint8_t next_layer = current_layer + 1;
      if (next_layer > LAYER_CYCLE_END) {
          next_layer = LAYER_CYCLE_START;
      }
      layer_move(next_layer);
      return false;

    // Process other keycodes normally
    default:
      // Код клавиши будет отображаться на OLED дисплее
      oled_clear(); // Очищаем дисплей
      oled_set_cursor(0, 2);
      oled_write_ln_P("Keycode:", false); // Отображаем текст "Keycode:"
      char keycode_str[6]; // Создаем массив для хранения строки с кодом клавиши (5 символов для числа + 1 символ для завершающего нуля)
      itoa(keycode, keycode_str, 10); // Преобразуем код клавиши в строку
      oled_write_ln_P(keycode_str, false); // Отображаем код клавиши на OLED дисплее
      return true;
  }
}

#endif
