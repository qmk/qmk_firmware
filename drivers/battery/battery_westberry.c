#include "quantum.h"
#include "westberry/module.h"

void battery_driver_init(void) {
}

uint8_t battery_driver_sample_percent(void) {
    if (*md_getp_state() != MD_STATE_NONE) {
        md_inquire_bat();
    }
    return *md_getp_bat();
}
