#include "maccel.h"
#include "quantum.h"
#include "math.h"
#include "print.h"

static uint32_t maccel_timer;

static float maccel_a = MACCEL_CURVE_A;
static float maccel_b = MACCEL_CURVE_B;
static float maccel_c = MACCEL_CURVE_C;

// wip: tell a user to insert the shim themselves instead of using _user here
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    return pointing_device_task_maccel(mouse_report);
}

report_mouse_t pointing_device_task_maccel(report_mouse_t mouse_report) {
    if(mouse_report.x != 0 || mouse_report.y != 0) {
        const float speed = (sqrtf(mouse_report.x*mouse_report.x + mouse_report.y*mouse_report.y))/timer_elapsed32(maccel_timer);
        float scale_factor = maccel_c-(maccel_c-1)*expf(-1*(speed-maccel_b) * maccel_a);
        if (scale_factor <= 1) {
            scale_factor = 1;
        }
        mouse_report.x = (mouse_xy_report_t)(mouse_report.x * scale_factor);
        mouse_report.y = (mouse_xy_report_t)(mouse_report.y * scale_factor);
        maccel_timer = timer_read32();

#ifdef MACCEL_DEBUG
        printf("maccel: x = %3i, y = %3i, speed = %4f -> scale_factor = %f\r\n", mouse_report.x, mouse_report.y, speed, scale_factor);
#endif

    } //if mouse_report !=0

    return mouse_report;

} //pointing_device_task_maccel
