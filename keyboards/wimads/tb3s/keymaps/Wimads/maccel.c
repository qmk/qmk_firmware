#include "maccel.h"
#include "quantum.h"
#include "math.h"
#include "print.h"

static uint32_t maccel_timer;

static float maccel_a = MACCEL_STEEPNESS; //steepness of acceleration curve
static float maccel_b = MACCEL_OFFSET;    //start offset of acceleration curve
static float maccel_c = MACCEL_LIMIT;     //upper limit of acceleration factor

report_mouse_t pointing_device_task_maccel(report_mouse_t mouse_report) {
    if(mouse_report.x != 0 || mouse_report.y != 0) {
        uint16_t device_dpi = pointing_device_get_cpi();
        const float velocity = (900/device_dpi)*(sqrtf(mouse_report.x*mouse_report.x + mouse_report.y*mouse_report.y))/timer_elapsed32(maccel_timer);
        float maccel_factor = maccel_c-(maccel_c-1)*expf(-1*(velocity-maccel_b) * maccel_a);
        if (maccel_factor <= 1) {
            maccel_factor = 1;
        }
        mouse_report.x = (mouse_xy_report_t)(mouse_report.x * maccel_factor);
        mouse_report.y = (mouse_xy_report_t)(mouse_report.y * maccel_factor);
        maccel_timer = timer_read32();

#ifdef MACCEL_DEBUG
        printf("DPI = %4i, factor = %4f, velocity = %4f\n", device_dpi, maccel_factor, velocity);
#endif

    } //if mouse_report !=0

    return mouse_report;

} //pointing_device_task_maccel
