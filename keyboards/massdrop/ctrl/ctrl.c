#include QMK_KEYBOARD_H

uint8_t led_animation_breathing;

uint8_t breathe_step;

float breathe_mult;

__attribute__((weak))
void led_matrix_init_user(void) {
  led_enabled = 1;
  led_animation_id = 0;
  led_lighting_mode = LED_MODE_NORMAL;
  led_animation_speed = 4.0f;
  led_animation_direction = 0;
  led_animation_breathe_cur = BREATHE_MIN_STEP;
  breathe_step = 1;
  breathe_dir = 1;
}

__attribute__((weak))
void led_matrix_run_user(void) {
  breathe_mult = 1;

  if (led_animation_breathing) {
      led_animation_breathe_cur += breathe_step * breathe_dir;

      if (led_animation_breathe_cur >= BREATHE_MAX_STEP)
          breathe_dir = -1;
      else if (led_animation_breathe_cur <= BREATHE_MIN_STEP)
          breathe_dir = 1;

      //Brightness curve created for 256 steps, 0 - ~98%
      breathe_mult = 0.000015 * led_animation_breathe_cur * led_animation_breathe_cur;
      if (breathe_mult > 1) breathe_mult = 1;
      else if (breathe_mult < 0) breathe_mult = 0;
  }
}

__attribute__((weak))
void led_run_user(led_disp_t disp, uint8_t led_index, issi3733_led_t *led, uint8_t kbled) {
  float ro = 0;
  float go = 0;
  float bo = 0;
  float px;

  uint8_t fcur = 0;
  uint8_t fmax = 0;

  uint8_t asdf = 0;
  if (led->scan == 255) {
    asdf = 9;
  }

  led_setup_t *f = (led_setup_t*) led_setups[asdf];
  // led_setup_t *f = (led_setup_t*) led_setups[led_animation_id];

  //Frames setup
  while (f[fcur].end != 1)
  {
    fcur++; //Count frames
  }

  fmax = fcur; //Store total frames count

  if (led_lighting_mode == LED_MODE_KEYS_ONLY && led->scan == 255)
  {
    //Do not act on this LED
  }
  else if (led_lighting_mode == LED_MODE_NON_KEYS_ONLY && led->scan != 255)
  {
    //Do not act on this LED
  }
  else if (led_lighting_mode == LED_MODE_INDICATORS_ONLY)
  {
    //Do not act on this LED (Only show indicators)
  }
  else
  {
    //Act on LED
    for (fcur = 0; fcur < fmax; fcur++)
    {
      px = led->px;
      float pxmod;
      pxmod = (float)(disp.frame % (uint32_t)(1000.0f / led_animation_speed)) / 10.0f * led_animation_speed;

      //Add in any moving effects
      if ((!led_animation_direction && f[fcur].ef & EF_SCR_R) || (led_animation_direction && (f[fcur].ef & EF_SCR_L)))
      {
        pxmod *= 100.0f;
        pxmod = (uint32_t)pxmod % 10000;
        pxmod /= 100.0f;

        px -= pxmod;

        if (px > 100) {
          px -= 100;
        } else if (px < 0) {
          px += 100;
        }
      }
      else if ((!led_animation_direction && f[fcur].ef & EF_SCR_L) || (led_animation_direction && (f[fcur].ef & EF_SCR_R)))
      {
        pxmod *= 100.0f;
        pxmod = (uint32_t)pxmod % 10000;
        pxmod /= 100.0f;
        px += pxmod;

        if (px > 100) px -= 100;
        else if (px < 0) px += 100;
      }

      //Check if LED's px is in current frame
      if (px < f[fcur].hs) continue;
      if (px > f[fcur].he) continue;
      //note: < 0 or > 100 continue

      //Calculate the px within the start-stop percentage for color blending
      px = (px - f[fcur].hs) / (f[fcur].he - f[fcur].hs);

      //Add in any color effects
      if (f[fcur].ef & EF_OVER)
      {
        ro = (px * (f[fcur].re - f[fcur].rs)) + f[fcur].rs;// + 0.5;
        go = (px * (f[fcur].ge - f[fcur].gs)) + f[fcur].gs;// + 0.5;
        bo = (px * (f[fcur].be - f[fcur].bs)) + f[fcur].bs;// + 0.5;
      }
      else if (f[fcur].ef & EF_SUBTRACT)
      {
        ro -= (px * (f[fcur].re - f[fcur].rs)) + f[fcur].rs;// + 0.5;
        go -= (px * (f[fcur].ge - f[fcur].gs)) + f[fcur].gs;// + 0.5;
        bo -= (px * (f[fcur].be - f[fcur].bs)) + f[fcur].bs;// + 0.5;
      }
      else
      {
        ro += (px * (f[fcur].re - f[fcur].rs)) + f[fcur].rs;// + 0.5;
        go += (px * (f[fcur].ge - f[fcur].gs)) + f[fcur].gs;// + 0.5;
        bo += (px * (f[fcur].be - f[fcur].bs)) + f[fcur].bs;// + 0.5;
      }
    }
  }

  //Clamp values 0-255
  if (ro > 255) ro = 255; else if (ro < 0) ro = 0;
  if (go > 255) go = 255; else if (go < 0) go = 0;
  if (bo > 255) bo = 255; else if (bo < 0) bo = 0;

  if (led_animation_breathing) {
    ro *= breathe_mult;
    go *= breathe_mult;
    bo *= breathe_mult;
  }

  *led->rgb.r = (uint8_t) ro;
  *led->rgb.g = (uint8_t) go;
  *led->rgb.b = (uint8_t) bo;

#ifdef USB_LED_INDICATOR_ENABLE
  if (kbled) {
    if (
      #if USB_LED_NUM_LOCK_SCANCODE != 255
      (led_cur->scan == USB_LED_NUM_LOCK_SCANCODE && kbled & (1<<USB_LED_NUM_LOCK)) ||
      #endif //NUM LOCK
      #if USB_LED_CAPS_LOCK_SCANCODE != 255
      (led_cur->scan == USB_LED_CAPS_LOCK_SCANCODE && kbled & (1<<USB_LED_CAPS_LOCK)) ||
      #endif //CAPS LOCK
      #if USB_LED_SCROLL_LOCK_SCANCODE != 255
      (led_cur->scan == USB_LED_SCROLL_LOCK_SCANCODE && kbled & (1<<USB_LED_SCROLL_LOCK)) ||
      #endif //SCROLL LOCK
      #if USB_LED_COMPOSE_SCANCODE != 255
      (led_cur->scan == USB_LED_COMPOSE_SCANCODE && kbled & (1<<USB_LED_COMPOSE)) ||
      #endif //COMPOSE
      #if USB_LED_KANA_SCANCODE != 255
      (led_cur->scan == USB_LED_KANA_SCANCODE && kbled & (1<<USB_LED_KANA)) ||
      #endif //KANA
      (0))
    {
      if (*led_cur->rgb.r > 127) *led_cur->rgb.r = 0;
      else *led_cur->rgb.r = 255;
      if (*led_cur->rgb.g > 127) *led_cur->rgb.g = 0;
      else *led_cur->rgb.g = 255;
      if (*led_cur->rgb.b > 127) *led_cur->rgb.b = 0;
      else *led_cur->rgb.b = 255;
    }
  }
#endif //USB_LED_INDICATOR_ENABLE
}
