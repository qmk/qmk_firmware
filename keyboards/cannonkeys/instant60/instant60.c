#include "instant60.h"
#include "ch.h"
#include "hal.h"
#include "led_custom.h"
#include "util.h"
#include "quantum.h"

#include "ws2812.h"

backlight_config_t kb_backlight_config = {
  .enable = true,
  .breathing = true,
  .level = BACKLIGHT_LEVELS
};

void matrix_init_kb(void){
      /* MOSI pin*/
    palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(0));
    wait_ms(500);

#ifdef RGBLIGHT_ENABLE
    leds_init();
#endif
    backlight_init_ports();
}

void matrix_scan_kb(void)
{
  #ifdef RGBLIGHT_ENABLE
    rgblight_task();
  #endif
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BL_INC:
      if (record->event.pressed) {
        kb_backlight_config.level = kb_backlight_config.level + 1;
        if(kb_backlight_config.level > BACKLIGHT_LEVELS){
          kb_backlight_config.level = BACKLIGHT_LEVELS;
        }
        backlight_set(kb_backlight_config.level);
      }
      return false;
    case BL_TOGG:
    case BL_DEC:
      if (record->event.pressed) {
        if(kb_backlight_config.level == 1){
          kb_backlight_config.level = 0;
        } else {
          kb_backlight_config.level = kb_backlight_config.level - 1;
        }
        backlight_set(kb_backlight_config.level);
      }
      return false;
    case BL_BRTG:
      kb_backlight_config.breathing = !kb_backlight_config.breathing;
      if(!kb_backlight_config.breathing){
        breathing_disable();
      } else{
        breathing_enable();
      }
      return false;
  }
  return true;
}
