#include "pointing_devices.h"

void pointing_device_init(void) {
#ifdef THUMBSTICK_ENABLE
    thumbstick_init_user();
#endif
}

void pointing_device_task(void) {
#ifdef THUMBSTICK_ENABLE
    report_mouse_t report  = pointing_device_get_report();
    bool           changed = thumbstick_update(&report);
    pointing_device_set_report(report);
    pointing_device_send();
    if (changed) {
        thumbstick_update_user();
    }
#endif
}
