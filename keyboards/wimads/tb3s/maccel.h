// TODO header

// todo: how to include

#pragma once

#include "quantum.h"

#define MACCEL_CURVE_A 0.4   //steepness of accel curve
#define MACCEL_CURVE_B 0.8    //X-offset of accel curve
#define MACCEL_CURVE_C 4   //max scale_factor

#define MACCEL_DEBUG

report_mouse_t pointing_device_task_maccel(report_mouse_t mouse_report);

