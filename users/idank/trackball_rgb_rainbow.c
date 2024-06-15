#include "trackball_rgb_rainbow.h"

#include "color.h"

void housekeeping_task_user(void) {
  bool run_animation = is_keyboard_master();
  // With two trackballs, always run the animation. Note that if TRACKBALL_RGB_RAINBOW isn't 'yes' we're not including
  // this file in the build.
#if defined(SPLIT_POINTING_ENABLE)
  run_animation = true;
#endif
  if (run_animation) {
    static uint32_t timer = 0;
    static HSV color = { .h = 0, .s = 255, .v = 255 };

    if (timer_elapsed32(timer) < 400)
        return;

    timer = timer_read32();

    // increase hue -> change color
    color.h++;

    RGB rgb = hsv_to_rgb(color);
    pimoroni_trackball_set_rgbw(rgb.r, rgb.g, rgb.b, 0);
  }
}
