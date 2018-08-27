#ifdef RGBLIGHT_ENABLE

#include "rgblight.h"
#include "color.h"
#include "fancylighting.h"


__attribute__ ((weak))
void matrix_scan_keymap(void) {
  // override me, if you want.
  return;
}

#define ABSDIFF(a,b) ((a)>(b)?(a)-(b):(b)-(a))
#ifdef MAX
#undef MAX
#endif
#ifdef MIN
#undef MIN
#endif
#define MIN(a,b) ((a)>(b)?(b):(a))
#define MAX(a,b) ((a)<(b)?(b):(a))

#define FADE_BACK_TIME 500
#define BREATH_FIRE_TIME 1000
#define ANIMATION_STEP_INTERVAL 20
#define POWER_KEY_OFFSET (RGBLED_NUM / 2)
#define SPACE_OFFSET_MAX (RGBLED_NUM / 2)


uint16_t effect_start_timer = 0;
uint8_t user_rgb_mode = 0;
LED_TYPE shadowed_led[RGBLED_NUM] = {0};

void start_firey_return(void) {
  user_rgb_mode = BREATH_FIRE;
  effect_start_timer = timer_read();
  for(uint8_t i = 0; i < RGBLED_NUM; i++) {
    shadowed_led[i] = led[i];
  }
}

/** 0---max
 *  [___]
 *  [__/]
 *  [_/\]
 *  [/\_]
 *  [\__]
 *  [___]
 **/

// #define FIRE_GRADIENT
#ifdef FIRE_GRADIENT
static LED_TYPE firey_gradient[] = {
  { .r = 0x00, .g = 0x00, .b = 0x00 },
  { .r = 0x66, .g = 0x00, .b = 0x02 },
  { .r = 0xc5, .g = 0x2f, .b = 0x0a },
  { .r = 0xff, .g = 0x5d, .b = 0x13 },
  { .r = 0xff, .g = 0x7d, .b = 0x13 },
  { .r = 0xff, .g = 0x9e, .b = 0x13 },
  { .r = 0xff, .g = 0xd0, .b = 0x8c },
  { .r = 0xff, .g = 0xe9, .b = 0x67 },
  { .r = 0xff, .g = 0xe9, .b = 0x67 },
  { .r = 0xff, .g = 0xe9, .b = 0x67 }
};
#endif

void set_color_for_offsets(uint16_t time_offset, uint16_t space_offset, uint8_t idx) {
  float time_progress = (float)time_offset / BREATH_FIRE_TIME;
  float space_progress = (float)space_offset / SPACE_OFFSET_MAX;
  float progress = time_progress * 5.0 - space_progress;
  if(progress > 1.0) {
    progress -= 1.0;
    progress /= 4.0;
    progress = 1.0 - progress;
  }
  progress = MAX(0.0,progress);
  progress *= progress; // squared!

  float alpha = (time_progress + 0.1) * 7.0 - space_progress;
  alpha = MIN(1.0, alpha*alpha);

#ifdef FIRE_GRADIENT

  float flidx = progress * (sizeof(firey_gradient)/sizeof(*firey_gradient) - 1);
  LED_TYPE lower = firey_gradient[(uint8_t)floor(flidx)];
  float mix = 1.0 - (flidx - floor(flidx));
  LED_TYPE higher = firey_gradient[(uint8_t)ceil(flidx)];

  led[idx].r = alpha * (mix * lower.r + (1.0 - mix) * higher.r) + ( 1.0 - alpha) * shadowed_led[idx].r;
  led[idx].g = alpha * (mix * lower.g + (1.0 - mix) * higher.g) + ( 1.0 - alpha) * shadowed_led[idx].g;
  led[idx].b = alpha * (mix * lower.b + (1.0 - mix) * higher.b) + ( 1.0 - alpha) * shadowed_led[idx].b;
#else
  LED_TYPE px[1] = {0};
  sethsv((uint16_t)(fmod(time_progress * 1.5 + space_progress,1.0)*360), 255, (uint8_t)(progress*255),&px[0]);
  led[idx].r = alpha * px[0].r + ( 1.0 - alpha) * shadowed_led[idx].r;
  led[idx].g = alpha * px[0].g + ( 1.0 - alpha) * shadowed_led[idx].g;
  led[idx].b = alpha * px[0].b + ( 1.0 - alpha) * shadowed_led[idx].b;
#endif
}

void rgb_mode_breath_fire(void) {
  static uint16_t last_timer = 0;
  if(!last_timer) last_timer = timer_read();
  uint16_t this_timer = timer_read();

  // too soon. don't spam updates
  if(this_timer - last_timer < ANIMATION_STEP_INTERVAL) return;

  uint16_t elapsed = this_timer - effect_start_timer;

  last_timer = this_timer;
  if(elapsed >= BREATH_FIRE_TIME) {
    // complete
    user_rgb_mode = FADE_BACK;
    effect_start_timer = this_timer;
  } else {
    // linear fade
    for(uint16_t i = 0; i < RGBLED_NUM; i++) {
      uint16_t space_offset = ABSDIFF(i,POWER_KEY_OFFSET);
      if(space_offset > SPACE_OFFSET_MAX) space_offset = RGBLED_NUM - space_offset;

      set_color_for_offsets(elapsed, space_offset, i);
    }
    rgblight_set();
  }
}

void rgb_mode_fade_back(void) {
  static uint16_t last_timer = 0;
  if(!last_timer) last_timer = timer_read();
  uint16_t this_timer = timer_read();

  // too soon. don't spam updates
  if(this_timer - last_timer < ANIMATION_STEP_INTERVAL) return;

  uint16_t elapsed = this_timer - effect_start_timer;

  last_timer = this_timer;
  float progress = (float)elapsed / FADE_BACK_TIME;
  progress = MIN(1.0,progress);

  for(uint8_t i = 0; i < RGBLED_NUM; i++) {
    led[i].r = shadowed_led[i].r * progress;
    led[i].g = shadowed_led[i].g * progress;
    led[i].b = shadowed_led[i].b * progress;
  }
  rgblight_set();

  if(elapsed >= FADE_BACK_TIME) user_rgb_mode = 0;
}

/** called when layer state or vstate has changed */
__attribute__ ((weak))
void set_state_leds(void) {
  return;
}

void matrix_scan_user(void) {
  static uint32_t last_layer = 0;
  static uint32_t last_vstate = 0;
  if(last_layer != layer_state || last_vstate != vstate) set_state_leds();
  last_layer = layer_state;
  last_vstate = vstate;

  switch (user_rgb_mode) {
    case BREATH_FIRE:
      rgb_mode_breath_fire();
      break;
    case FADE_BACK:
      rgb_mode_fade_back();
      break;
  }
  matrix_scan_keymap();
  keyboard_has_heat();
}

float keyboard_heat = 0;
float decay_fraction = 0.9;
float decay_step = 0.01; // to make sure we hit zero eventually


void keyboard_has_heat(void) {
  static uint16_t last_timer = 0;
  uint16_t this_timer = timer_read();
  // too soon. don't spam updates
  if(this_timer - last_timer < ANIMATION_STEP_INTERVAL) return;
  last_timer = this_timer;

  keyboard_heat *= decay_fraction;
  keyboard_heat -= decay_step;

  if(keyboard_heat > 0.0) xprintf("heat: %u\n", (uint16_t)(1000*keyboard_heat));
}
#else

//noop
float keyboard_heat = 0;
void start_firey_return(void) {}

#endif
