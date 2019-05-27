#include "crkbd.h"

#ifdef SSD1306OLED
#   include "LUFA/Drivers/Peripheral/TWI.h"

void matrix_master_OLED_init (void) {
    TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
#ifdef SSD1306OLED
  return process_record_gfx(keycode,record) && process_record_user(keycode, record);
#else
  return process_record_user(keycode, record);
#endif
}
