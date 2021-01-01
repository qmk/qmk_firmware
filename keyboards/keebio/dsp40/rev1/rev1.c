#include "rev1.h"

void eeconfig_init_kb(void) {
#ifdef BACKLIGHT_ENABLE
    backlight_enable();
    backlight_level(5);
#endif
    eeconfig_update_kb(0);
    eeconfig_init_user();
}
