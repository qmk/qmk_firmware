 /* Copyright 2015-2017 Christon DeWan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef RGBLIGHT_ENABLE

#include <math.h>

#include "rgblight.h"
#include "color.h"
#include "fancylighting.h"


__attribute__ ((weak))
void matrix_scan_keymap(void) {
  // override me, if you want.
  return;
}

#define ABSDIFF(a,b) ((a)>(b)?(a)-(b):(b)-(a))

#define FADE_BACK_TIME 500
#define BREATH_FIRE_TIME 1000
#define ANIMATION_STEP_INTERVAL 20

#if RGBLED_NUM >= 2
#define POWER_KEY_OFFSET (RGBLED_NUM / 2)
#define SPACE_OFFSET_MAX (RGBLED_NUM / 2)
#else
#define POWER_KEY_OFFSET 1
#define SPACE_OFFSET_MAX 1
#endif

uint16_t effect_start_timer = 0;
uint8_t user_rgb_mode = 0;
rgb_led_t shadowed_led[RGBLED_NUM] = {{0}};

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

void set_color_for_offsets(uint16_t time_offset, uint16_t space_offset, uint8_t idx) {
  float time_progress = (float)time_offset / BREATH_FIRE_TIME;
  float space_progress = (float)space_offset / SPACE_OFFSET_MAX;
  float progress = time_progress * 5.0 - space_progress;
  if(progress > 1.0) {
    progress -= 1.0;
    progress /= 4.0;
    progress = 1.0 - progress;
  }
  progress = fmax(0.0,progress);
  progress *= progress; // squared!

  float alpha = (time_progress + 0.1) * 7.0 - space_progress;
  alpha = fmin(1.0, alpha*alpha);

  rgb_led_t px[1] = {{0}};
  sethsv((uint16_t)(fmod(time_progress * 1.5 + space_progress,1.0)*360), 255, (uint8_t)(progress*255),&px[0]);
  led[idx].r = alpha * px[0].r + ( 1.0 - alpha) * shadowed_led[idx].r;
  led[idx].g = alpha * px[0].g + ( 1.0 - alpha) * shadowed_led[idx].g;
  led[idx].b = alpha * px[0].b + ( 1.0 - alpha) * shadowed_led[idx].b;
}

/**
 * It's actually a rainbow: a fire curve didn't really look right.
 * it's still cool, though!
 */
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
  progress = fmin(1.0,progress);

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
}

#else

void start_firey_return(void) {}

#endif
