#include "crkbd.h"
#ifdef OLED_ENABLE
  #include "ssd1306.h"
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}
