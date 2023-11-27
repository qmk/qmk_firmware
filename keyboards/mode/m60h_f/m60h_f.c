#include "eeconfig.h"
#include "quantum.h"

void keyboard_post_init_kb(void) {
    wait_ms(200);
    rgblight_reload_from_eeprom();
}