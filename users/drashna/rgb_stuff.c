
#include "rgb_stuff.h"
#include "drashna.h"

#ifdef RGBLIGHT_TWINKLE
static rgblight_fadeout lights[RGBLED_NUM];

__attribute__ ((weak))
bool indicator_is_this_led_used(uint8_t index) { return false; }

void scan_rgblight_fadeout(void) {
  bool litup = false;
  for (uint8_t light_index = 0 ; light_index < RGBLED_NUM ; ++light_index ) {
    if (lights[light_index].enabled && timer_elapsed(lights[light_index].timer) > 10) {
      rgblight_fadeout *light = &lights[light_index];
      litup = true;

      if (light->life) {
        if (biton32(layer_state) == _QWERTY) {
          light->life -= 1;
          sethsv(light->hue + rand() % 0xF, 255, light->life, (LED_TYPE *)&led[light_index]);
        }
        light->timer = timer_read();
      }
      else {
        if (light->enabled) { rgblight_sethsv_default_helper(light_index); }
        litup = light->enabled = false;
      }
    }
  }
  if (litup) {
    rgblight_set();
  }
}

void start_rgb_light(void) {

    uint8_t indices[RGBLED_NUM];
    uint8_t indices_count = 0;
    uint8_t min_life = 0xFF;
    uint8_t min_life_index = -1;
    for (uint8_t index = 0 ; index < RGBLED_NUM ; ++index ) {
      if (indicator_is_this_led_used(index)) { continue; }
      if (lights[index].enabled) {
        if (min_life_index == -1 ||
          lights[index].life < min_life)
        {
          min_life = lights[index].life;
          min_life_index = index;
        }
        continue;
      }

      indices[indices_count] = index;
      ++indices_count;
    }

    uint8_t light_index;
    if (!indices_count) {
        light_index = min_life_index;
    }
    else {
      light_index = indices[rand() % indices_count];
    }

    rgblight_fadeout *light = &lights[light_index];
    light->enabled = true;
    light->timer = timer_read();
    light->life = 0xC0 + rand() % 0x40;

    light->hue = rand() % 0x168;

    rgblight_sethsv_at(light->hue, 255, light->life, light_index);
}


bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) { return true; }

    switch (keycode) {
    case KC_A ... KC_SLASH:
    case KC_F1 ... KC_F12:
    case KC_INSERT ... KC_UP:
    case KC_KP_SLASH ... KC_KP_DOT:
    case KC_F13 ... KC_F24:
    case KC_AUDIO_MUTE ... KC_MEDIA_REWIND:
        start_rgb_light();
    }

    return true;
}

#else
bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) { return true; }
#endif
