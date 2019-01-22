#include "quantum.h"
#include "rgb_backlight.h"
#include "rgb_backlight_api.h"

void set_effect(uint8_t *value_data)
{
  switch (*value_data)
  {
    case 0:
      rgblight_disable();
      break;
    case 1:
      rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_enable();
      break;
    case 2:
      rgblight_mode(RGBLIGHT_MODE_BREATHING);
      rgblight_enable();
      break;
    case 3:
      rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
      rgblight_enable();
      break;
    case 4:
      rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
      rgblight_enable();
      break;
    case 5:
      rgblight_mode(RGBLIGHT_MODE_SNAKE);
      rgblight_enable();
      break;
    case 6:
      rgblight_mode(RGBLIGHT_MODE_KNIGHT);
      rgblight_enable();
      break;
    case 7:
      rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
      rgblight_enable();
      break;
    case 8:
      rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT);
      rgblight_enable();
      break;
    case 9:
      rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
      rgblight_enable();
      break;
    case 10:
      rgblight_mode(RGBLIGHT_MODE_ALTERNATING);
      rgblight_enable();
      break;
  }
}

void set_color(uint8_t *data)
{
  uint8_t *hue = &(data[0]);
  uint8_t *sat = &(data[1]);
  rgblight_sethsv(*hue, *sat, rgblight_get_val());
}

void set_brightness(uint8_t *data)
{
  uint8_t hue = rgblight_get_hue();
  uint8_t sat = rgblight_get_sat();
  rgblight_sethsv(hue, sat, *data);
}

void get_color(uint8_t *data)
{
  uint8_t hue = rgblight_get_hue();
  uint8_t sat = rgblight_get_sat();
  data[0] = hue;
  data[1] = sat;
}

uint8_t get_effect(void)
{
  uint8_t mode = rgblight_get_mode();
  switch (mode)
  {
    case RGBLIGHT_MODE_STATIC_LIGHT:
      return 1;
    case RGBLIGHT_MODE_BREATHING:
      return 2;
    case RGBLIGHT_MODE_RAINBOW_MOOD:
      return 3;
    case RGBLIGHT_MODE_RAINBOW_SWIRL:
      return 4;
    case RGBLIGHT_MODE_SNAKE:
      return 5;
    case RGBLIGHT_MODE_KNIGHT:
      return 6;
    case RGBLIGHT_MODE_CHRISTMAS:
      return 7;
    case RGBLIGHT_MODE_STATIC_GRADIENT:
      return 8;
    case RGBLIGHT_MODE_RGB_TEST:
      return 9;
    case RGBLIGHT_MODE_ALTERNATING:
      return 10;
    default:
      return 0;
  }
}

void backlight_config_get_value( uint8_t *data )
{
	uint8_t *value_id = &(data[0]);
	uint8_t *value_data = &(data[1]);
  switch (*value_id)
  {
    case id_effect:
      *value_data = get_effect();
      break;
    case id_brightness:
      *value_data = rgblight_get_val();
      break;
    case id_color_1:
      get_color(value_data);
      break;
  }
}

void backlight_config_set_value( uint8_t *data )
{
	uint8_t *value_id = &(data[0]);
	uint8_t *value_data = &(data[1]);
  switch (*value_id)
  {
    case id_effect:
      set_effect(value_data);
      break;
    case id_brightness:
      set_brightness(value_data);
      break;
    case id_color_1:
      set_color(value_data);
      break;
  }
}

