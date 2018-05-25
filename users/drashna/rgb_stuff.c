
#include "rgb_stuff.h"


#ifdef RGBLIGHT_TWINKLE
static rgblight_fadeout lights[RGBLED_NUM];


void scan_rgblight_fadeout(void) {
    bool litup = false;
    for (uint8_t light_index = 0 ; light_index < RGBLED_NUM ; ++light_index ) {
        if (lights[light_index].enabled && timer_elapsed(lights[light_index].timer) > 10) {
            rgblight_fadeout *light = &lights[light_index];
            rgblight_setrgb_at(light->r, light->g, light->b, light_index);
            litup = true;

            if (light->r || light->g || light->b) {
                light->life -= 1;
                light->r = light->r ? light->r - 1 : light->r;
                light->g = light->g ? light->g - 1 : light->g;
                light->b = light->b ? light->b - 1 : light->b;
                light->timer = timer_read();
            }
            else {
                light->enabled = false;
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
    light->life = 0xFF;

    light->r = rand() % 0xFF;
    light->g = rand() % 0xFF;
    light->b = rand() % 0xFF;

    rgblight_setrgb_at(light->r, light->g, light->b, light_index);
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
