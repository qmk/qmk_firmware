//
// Created by Tyler Thrailkill on 4/2/21.
//

#ifndef QMK_FIRMWARE_OLED_SETUP_H
#define QMK_FIRMWARE_OLED_SETUP_H

#endif  // QMK_FIRMWARE_OLED_SETUP_H

#pragma once

#include "quantum.h"
#ifdef OLED_DRIVER_ENABLE
#include "oled_driver.h"
#define OLED_RENDER_WPM_COUNTER " WPM: "
#endif
#ifdef LUNA_ENABLE
#include "luna.h"
#endif
#ifdef OCEAN_DREAM_ENABLE
#include "ocean_dream.h"
#endif