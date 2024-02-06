// TODO header

// todo: how to include

#pragma once

#include "quantum.h"

#define MACCEL_STEEPNESS 0.4   //steepness of accel curve
#define MACCEL_OFFSET 0.8    //X-offset of accel curve
#define MACCEL_LIMIT 4.5   //max scale_factor

#define MACCEL_DEBUG

report_mouse_t pointing_device_task_maccel(report_mouse_t mouse_report);

