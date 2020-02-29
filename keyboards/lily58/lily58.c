#include "lily58.h"
#include "ssd1306.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    /* FIXME(skullydazed):
     *     Originally this code always ran no matter what process_record_user() did.
     *     With this PR it will only run if process_record_user() returns true. We
     *     should think through the implications here.
     */
#ifdef SSD1306OLED
  return process_record_gfx(keycode,record);
#else
  return true;
#endif
}
