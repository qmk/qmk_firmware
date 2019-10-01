#include <string.h>
#include "oled.h"

// NOTE: Redefined to avoid to use snprintf(); It makes size of firmware big.
const char *read_mode_icon(bool windows_mode) {
  static const char logo[][2][3] = {{{0x95, 0x96, 0}, {0xb5, 0xb6, 0}}, {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}}};
  static char mode_icon[10];

  int mode_number = windows_mode ? 1 : 0;
  strcpy(mode_icon, logo[mode_number][0]);

  strcat(mode_icon, "\n");
  strcat(mode_icon, logo[mode_number][1]);

  return mode_icon;
}

const char *read_layer_state(void) {
  static char layer_state_str[24];
  char layer_name[17];

  switch (biton32(layer_state)) {
    case L_BASE:
      strcpy(layer_name, default_layer_state == 1UL<<_EDVORAK ? "EDVORAK" : "QWERTY");
      break;
    case _EDVORAKJ1:
    case _EDVORAKJ2:
      strcpy(layer_name, "JP_EXT");
      break;
    case _RAISE:
      strcpy(layer_name, "Raise");
      break;
    case _LOWER:
      strcpy(layer_name, "Lower");
      break;
    case _ADJUST:
      strcpy(layer_name, "Adjust");
      break;
    default:
      snprintf(layer_name, sizeof(layer_name), "Undef-%ld", layer_state);
  }

  strcpy(layer_state_str, "Layer: ");

  strcat(layer_state_str, layer_name);
  strcat(layer_state_str, "\n");
  return layer_state_str;
}

const char *read_host_led_state(void) {
  static char led_str[24];
  bool ext_status = get_enable_jp_extra_layer() && get_japanese_mode();
  strcpy(led_str, ext_status ? "EXT" : "   ");

  strcat(led_str, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? " NMLK" : "     ");
  strcat(led_str, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? " CAPS" : "    ");
  strcat(led_str, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? " SCLK" : "     ");
  return led_str;
}

void matrix_update(struct CharacterMatrix *dest,
                   const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

  matrix_clear(&matrix);
  if (is_master) {
    matrix_write(&matrix, read_mode_icon(!get_enable_kc_lang()));
    matrix_write(&matrix, " ");
    matrix_write(&matrix, read_layer_state());
    matrix_write(&matrix, read_host_led_state());
  } else {
    matrix_write(&matrix, read_logo());
  }
  matrix_update(&display, &matrix);
}
