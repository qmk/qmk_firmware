#ifdef KEYBOARD_zeal60
#include "config.h"
#include "zeal60.h"
#include "rgb_backlight.h"
#include "action_layer.h"
#include "solarized.h"
#include "talljoe.h"

// from zeal_backlight.c
// we want to be able to set indicators for the spacebar stabs
// but they are not represented by a row/index.
extern backlight_config g_config;
void map_row_column_to_led( uint8_t row, uint8_t column, uint8_t *led );

void set_backlight_defaults(void) {
  uint8_t space;
  uint8_t caps_lock;
  map_row_column_to_led(3, 12, &caps_lock);
  map_row_column_to_led(4, 7, &space);
  backlight_config default_values = {
    .use_split_backspace = USE_SPLIT_BACKSPACE,
    .use_split_left_shift = USE_SPLIT_LEFT_SHIFT,
    .use_split_right_shift = USE_SPLIT_RIGHT_SHIFT,
    .use_7u_spacebar = USE_7U_SPACEBAR,
    .use_iso_enter = USE_ISO_ENTER,
    .disable_when_usb_suspended = 1,
    .disable_after_timeout = 0,
    .brightness = 255,
    .effect = 10,
    .color_1 = solarized.base2,
    .color_2 = solarized.base02,
    .caps_lock_indicator = { .index = caps_lock, .color = solarized.red },
    .layer_1_indicator = { .index = space, .color = solarized.blue },
    .layer_2_indicator = { .index = space, .color = solarized.yellow },
    .layer_3_indicator = { .index = 254, .color = solarized.red },
    .alphas_mods = {
      RGB_BACKLIGHT_ALPHAS_MODS_ROW_0,
      RGB_BACKLIGHT_ALPHAS_MODS_ROW_1,
      RGB_BACKLIGHT_ALPHAS_MODS_ROW_2,
      RGB_BACKLIGHT_ALPHAS_MODS_ROW_3,
      RGB_BACKLIGHT_ALPHAS_MODS_ROW_4 }
  };
  memcpy(&g_config, &default_values, sizeof(backlight_config));
  backlight_config_save();

#undef CUSTOM_RGB_LAYOUTS
#ifdef CUSTOM_RGB_LAYOUTS
  solarized_t* S = &solarized;
  HSV alphas = S->base2;
  HSV custom_color_map[MATRIX_ROWS][MATRIX_COLS] = CM(
    S->red, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, S->red,
    S->orange, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, S->orange,
    S->green, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, S->green,
    S->blue, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, alphas, S->blue, S->blue,
    S->violet, S->magenta, S->yellow,              alphas,          S->yellow, S->magenta, S->violet, S->green
  );
  for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
      uint8_t index;
			map_row_column_to_led( row, col, &index );
      set_key_color(index, custom_color_map[row][col]);
    }
  }
#endif // CUSTOM_RGB_LAYOUTS
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  static uint8_t last_effect;
  switch (keycode) {
    case DFAULTS:
      if (IS_PRESSED(record->event)) set_backlight_defaults();
      return false;
    case BL_TOGG:
      if (IS_PRESSED(record->event)) {
        if (g_config.effect) {
          last_effect = g_config.effect;
          g_config.effect = 0;
        } else {
          g_config.effect = last_effect;
        }
      }
      return false;
    case EFFECT...EFFECT_END:
      if (IS_PRESSED(record->event)) {
        uint8_t effect = keycode - EFFECT;
        g_config.effect = effect;
        backlight_config_save();
      }
      return false;
  }

  return true;
}
#endif
