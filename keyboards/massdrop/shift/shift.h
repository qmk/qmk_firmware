#pragma once

#include "quantum.h"
#include "config_led.h"
#include "matrix.h"

#include "i2c_master.h"
#include "led_matrix.h" //For led keycodes
#include "usb/udi_cdc.h"
#include "usb/usb2422.h"

#define LAYOUT( \
    K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, \
    K014, K015, K016, K017, K018, K019, K020, K021, K022, K023, K024, K025, K026, \
    K027, K028, K029, K030, K031, K032, K033, K034, K035, K036, K037, K038, K039, \
    K040, K041, K042, K043, K044, K045, K046, K047, K048, K049, K050, K051, K052, \
    K053, K054, K055, K056, K057, K058, K059, K060, K061, K062, K063, K064, K065, \
    K066, K067, K068, K069, K070, K071, K072, K073, K074, K075, K076, K077, K078, \
    K079, K080, K081, K082, K083, K084, K085, K086, K087, K088, K089, K090, K091, \
    K092, K093, K094, K095, K096, K097, K098, K099, K100, K101, K102 \
) { \
    {   K001,  K002,  K003,  K005,  K006,  K007,  K008,  K010,  K012,  K014,  K015,  K016,  K017    }, \
    {   K022,  K023,  K004,  K027,  K029,  K030,  K009,  K011,  K013,  K018,  K019,  K020,  K021    }, \
    {   K040,  K024,  K025,  K028,  K046,  K031,  K032,  K034,  K035,  K036,  K037,  K038,  K039    }, \
    {   K058,  K041,  K026,  K044,  K047,  K048,  K033,  K051,  K052,  K054,  K055,  K056,  K057    }, \
    {   K075,  K042,  K043,  K045,  K064,  K049,  K050,  K068,  K053,  K071,  K072,  K073,  K074    }, \
    {   K092,  K059,  K061,  K062,  K065,  K066,  K067,  K084,  K069,  K087,  K088,  K089,  K091    }, \
    {   K093,  K060,  K077,  K063,  K080,  K082,  K083,  K085,  K070,  K090,  K102,  K098,  K099    }, \
    {   K094,  K076,  K078,  K079,  K095,  K081,  K096,  K097,  K086,  K100,  K101,  KC_NO, KC_NO   }  \
}

#define TOGGLE_FLAG_AND_PRINT(var, name) { \
        if (var) { \
            dprintf(name " disabled\r\n"); \
            var = !var; \
        } else { \
            var = !var; \
            dprintf(name " enabled\r\n"); \
        } \
    }
