#pragma once

#include "quantum.h"
#include "config_led.h"
#include "matrix.h"

#include "i2c_master.h"
#include "md_rgb_matrix.h" //For led keycodes
#include "usb/udi_cdc.h"
#include "usb/usb_hub.h"

#define TOGGLE_FLAG_AND_PRINT(var, name) { \
        if (var) { \
            dprintf(name " disabled\r\n"); \
            var = !var; \
        } else { \
            var = !var; \
            dprintf(name " enabled\r\n"); \
        } \
    }
