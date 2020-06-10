// https://github.com/manna-harbour/qmk_firmware/blob/crkbd/keyboards/crkbd/keymaps/manna-harbour/readme.org

#include QMK_KEYBOARD_H

#if defined MH_OLED_IMAGE_FILE && defined OLED_DRIVER_ENABLE
#include "mh_image.h"
#endif

#if defined CONSOLE_ENABLE
#include <print.h>
#endif

#if defined PS2_MOUSE_ENABLE
#include "ps2_mouse.h"
#endif

#if defined MOUSEKEY_ENABLE
#include "mousekey.h"
#endif

#if defined SSD1306OLED
#include "ssd1306.h"
#endif

#if defined MH_AUTO_BUTTONS
#include MH_USER_NAME_H // for MH_AUTO_BUTTONS_LAYER
#endif


#if defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && defined MOUSEKEY_ENABLE

static uint16_t mh_auto_buttons_timer;
extern int tp_buttons; // mousekey button state set in action.c and used in ps2_mouse.c

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
  if (mh_auto_buttons_timer) {
    mh_auto_buttons_timer = timer_read();
  } else {
    if (!tp_buttons) {
      layer_on(MH_AUTO_BUTTONS_LAYER);
      mh_auto_buttons_timer = timer_read();
  #if defined CONSOLE_ENABLE
      print("mh_auto_buttons: on\n");
  #endif
    }
  }
}

void matrix_scan_user(void) {
  if (mh_auto_buttons_timer && (timer_elapsed(mh_auto_buttons_timer) > MH_AUTO_BUTTONS_TIMEOUT)) {
    if (!tp_buttons) {
      layer_off(MH_AUTO_BUTTONS_LAYER);
      mh_auto_buttons_timer = 0;
  #if defined CONSOLE_ENABLE
      print("mh_auto_buttons: off\n");
  #endif
    }
  }
}

#endif // defined MH_AUTO_BUTTONS && defined PS2_MOUSE_ENABLE && #defined MOUSEKEY_ENABLE


#if defined MH_OLED_IMAGE_LOGO && defined OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return isLeftHand ? rotation : OLED_ROTATION_180;
}

void mh_draw_image(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
  oled_write_P(qmk_logo, false);
}

#elif defined MH_OLED_IMAGE_FILE && defined OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return isLeftHand || mh_image_portrait ? rotation : OLED_ROTATION_180;
}

void mh_draw_image(void) {
  oled_write_raw_P(mh_image, mh_image_size);
}

#endif // defined MH_OLED_IMAGE_FILE && defined OLED_DRIVER_ENABLE


#if defined OLED_DRIVER_ENABLE

#if defined MH_OLED_TIMEOUT
static uint32_t mh_oled_timer;
#endif

void oled_task_user(void) {
  #if defined MH_OLED_TIMEOUT
    #if defined CONSOLE_ENABLE
  uprintf("mh_oled_timer elapsed: %d\n", (int)timer_elapsed32(mh_oled_timer));
    #endif
  if (timer_elapsed32(mh_oled_timer) > OLED_TIMEOUT) {
    oled_off();
    return;
  }
  #endif // defined MH_OLED_TIMEOUT
  #if defined MH_OLED_MODE_STATIC
  mh_draw_image();
  #elif defined MH_OLED_MODE_CAPS
  if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
    mh_draw_image();
  } else {
    oled_off();
  }
  #endif // defined MH_OLED_MODE_CAPS
}

#endif // defined OLED_DRIVER_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#if defined MH_OLED_TIMEOUT && defined OLED_DRIVER_ENABLE
  if (record->event.pressed) {
    mh_oled_timer = timer_read32();
  }
#endif // defined MH_OLED_TIMEOUT && defined OLED_DRIVER_ENABLE
#if defined MH_RGB_TOGGLE_OFF && RGB_MATRIX_ENABLE
  if (record->event.pressed && (keycode == RGB_TOG) && (get_mods() & MOD_MASK_SHIFT)) {
    rgblight_disable();
    return false;
  }
#endif // defined MH_RGB_TOGGLE_OFF && RGB_MATRIX_ENABLE
  return true;
}


#if defined SSD1306OLED

const char *read_logo(void);

void matrix_init_user(void) {
  iota_gfx_init(!isLeftHand);
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  #if defined MH_OLED_MODE_STATIC
  matrix_write(matrix, read_logo());
  #elif defined MH_OLED_MODE_CAPS
  if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
    matrix_write(matrix, read_logo());
  }
  #endif // defined MH_OLED_MODE_CAPS
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

void matrix_scan_user(void) {
   iota_gfx_task();
}

#endif // defined SSD1306OLED


#if defined MH_DEBUG
void keyboard_post_init_user(void) {
  debug_enable = true;
  debug_mouse = true;
}
#endif
