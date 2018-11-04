#include "helix.h"
#include "ssd1306.h" 

#ifdef OLED_ENABLED
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    process_record_gfx(keycode,record);
	return process_record_user(keycode, record);
}
#endif