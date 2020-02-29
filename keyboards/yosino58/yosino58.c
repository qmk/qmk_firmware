#include "yosino58.h"
#include "ssd1306.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
#ifdef SSD1306OLED
  return process_record_gfx(keycode,record);
#else
  return true;
#endif
}
