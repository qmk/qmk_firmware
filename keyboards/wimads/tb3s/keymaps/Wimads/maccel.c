/* Copyright 2024 burkfers (@burkfers)
 * Copyright 2024 Wimads (@wimads)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "math.h"
#include "print.h"

static uint32_t maccel_timer; //timer for calculation of velocity

/* DEVICE_CPI_PARAM
A device specific parameter required to ensure consistent acceleration
behaviour across different devices and user dpi settings.
Set to match the value for your device sensor:
 * PMW3360: 0.087
 * PMW3389: tbd
 * Cirque: tbd
 * Azoteq: tbd
*///disclaimer: values guestimated by scientifically questionable emperical testing
#ifndef DEVICE_CPI_PARAM
#define DEVICE_CPI_PARAM .087  //device specific cpi scaling parameter
#endif
#ifndef MACCEL_STEEPNESS
#define MACCEL_STEEPNESS 0.3  // steepness of accel curve
#endif
#ifndef MACCEL_OFFSET
#define MACCEL_OFFSET 1     // start offset of accel curve
#endif
#ifndef MACCEL_LIMIT
#define MACCEL_LIMIT 6      // upper limit of accel cuve
#endif

const float maccel_a = MACCEL_STEEPNESS; //steepness of acceleration curve
const float maccel_b = MACCEL_OFFSET;    //start offset of acceleration curve
const float maccel_c = MACCEL_LIMIT;     //upper limit of acceleration curve

// Clamp a value to the maximum report size to prevent over- and underflows
static inline mouse_xy_report_t clamp_to_report(float val) {
    if (val < XY_REPORT_MIN) {
        return XY_REPORT_MIN;
    } else if (val > XY_REPORT_MAX) {
        return XY_REPORT_MAX;
    } else {
        return val;
    }
}

report_mouse_t pointing_device_task_maccel(report_mouse_t mouse_report) {
    if(mouse_report.x != 0 || mouse_report.y != 0) {
        //calculate dpi correction factor (for normalizing velocity range across different user dpi settings)
        const float dpi_correction = (float) 100/(DEVICE_CPI_PARAM*pointing_device_get_cpi());
        //calculate delta velocity: dv = dpi_correction * sqrt(dx^2 + dy^2)/dt
        const float velocity = dpi_correction*(sqrtf(mouse_report.x*mouse_report.x + mouse_report.y*mouse_report.y))/timer_elapsed32(maccel_timer);
        //calculate mouse acceleration factor: f(dv) = c - (c - 1) * e^(-(dv - b) * a)
        float maccel_factor = maccel_c-(maccel_c-1)*expf(-1*(velocity-maccel_b) * maccel_a);
        if (maccel_factor <= 1) { //cut-off acceleration curve below maccel_factor = 1
            maccel_factor = 1;
        }
        //calculate accelerated delta X and Y values:
        const float x = (mouse_xy_report_t)(mouse_report.x * maccel_factor);
        const float y = (mouse_xy_report_t)(mouse_report.y * maccel_factor);
        //set (clamped) mouse reports for X and Y
        mouse_report.x = clamp_to_report(x);
        mouse_report.y = clamp_to_report(y);
        //record time of last mouse report:
        maccel_timer = timer_read32();

#ifdef MACCEL_DEBUG //console output for debugging (enable/disable in maccel.h)
        float accelerated = velocity * maccel_factor; //resulting velocity after acceleration; unneccesary for calculation, but nice for debug console
        printf("DPI = %4i, correction = %4f, factor = %4f, velocity = %4f, accelerated = %4f\n", pointing_device_get_cpi(), dpi_correction, maccel_factor, velocity, accelerated);
#endif //MACCEL_DEBUG

    } //if mouse_report !=0

    return mouse_report;

} //pointing_device_task_maccel
