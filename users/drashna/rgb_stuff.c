
#include "drashna.h"
#include "rgb_stuff.h"

extern rgblight_config_t rgblight_config;
extern userspace_config_t userspace_config;

#ifdef RGBLIGHT_ENABLE
void rgblight_sethsv_default_helper(uint8_t index) {
  rgblight_sethsv_at(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, index);
}
#endif // RGBLIGHT_ENABLE

#ifdef INDICATOR_LIGHTS
uint8_t last_mod;
uint8_t last_led;
uint8_t last_osm;
#endif

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
        light->life -= 1;
        if (biton32(layer_state) == 0) {
          sethsv(light->hue + rand() % 0xF, 255, light->life, (LED_TYPE *)&led[light_index]);
        }
        light->timer = timer_read();
      }
      else {
        if (light->enabled && biton32(layer_state) == 0) { rgblight_sethsv_default_helper(light_index); }
        litup = light->enabled = false;
      }
    }
  }
  if (litup && biton32(layer_state) == 0) {
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

    light->hue = rgblight_config.hue + (rand() % 0xB4) - 0x54;

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


void layer_state_set_rgb(void) {
#ifdef INDICATOR_LIGHTS
  if (last_mod & MODS_SHIFT_MASK || last_led & (1<<USB_LED_CAPS_LOCK) || last_osm & MODS_SHIFT_MASK) {
    rgblight_sethsv_at(0, 255, 255, SHFT_LED1);
    rgblight_sethsv_at(0, 255, 255, SHFT_LED2);
  }
  if (last_mod & MODS_CTRL_MASK || last_osm & MODS_CTRL_MASK) {
    rgblight_sethsv_at(51, 255, 255, CTRL_LED1);
    rgblight_sethsv_at(51, 255, 255, CTRL_LED2);
  }
  if (last_mod & MODS_ALT_MASK || last_osm & MODS_ALT_MASK) {
    rgblight_sethsv_at(120, 255, 255, GUI_LED1);
    rgblight_sethsv_at(120, 255, 255, GUI_LED2);
  }
#endif
}

void matrix_init_rgb(void) {
#ifdef INDICATOR_LIGHTS
  last_mod = get_mods();
  last_led = host_keyboard_leds();
  last_osm = get_oneshot_mods();
#endif
}

void matrix_scan_rgb(void) {
#ifdef RGBLIGHT_TWINKLE
  scan_rgblight_fadeout();
#endif // RGBLIGHT_ENABLE

#ifdef INDICATOR_LIGHTS
  uint8_t current_mod = get_mods();
  uint8_t current_led = host_keyboard_leds();
  uint8_t current_osm = get_oneshot_mods();

  last_mod = current_mod;
  last_led = current_led;
  last_osm = current_osm;


  if (userspace_config.rgb_layer_change && biton32(layer_state) == 0) {
    if (current_mod & MODS_SHIFT_MASK || current_led & (1<<USB_LED_CAPS_LOCK) || current_osm & MODS_SHIFT_MASK) {
      rgblight_sethsv_at(0, 255, 255, SHFT_LED1);
      rgblight_sethsv_at(0, 255, 255, SHFT_LED2);
    } else {
      rgblight_sethsv_default_helper(SHFT_LED1);
      rgblight_sethsv_default_helper(SHFT_LED2);
    }
    if (current_mod & MODS_CTRL_MASK || current_osm & MODS_CTRL_MASK) {
      rgblight_sethsv_at(51, 255, 255, CTRL_LED1);
      rgblight_sethsv_at(51, 255, 255, CTRL_LED2);
    } else {
      rgblight_sethsv_default_helper(CTRL_LED1);
      rgblight_sethsv_default_helper(CTRL_LED2);
    }
    if (current_mod & MODS_GUI_MASK || current_osm & MODS_GUI_MASK) {
      rgblight_sethsv_at(120, 255, 255, GUI_LED1);
      rgblight_sethsv_at(120, 255, 255, GUI_LED2);
    } else {
      rgblight_sethsv_default_helper(GUI_LED1);
      rgblight_sethsv_default_helper(GUI_LED2);
    }
  }
#endif

}
