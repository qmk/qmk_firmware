#if !defined THUMBSTICK_CHANNEL_X || !defined THUMBSTICK_CHANNEL_Y
#    error "You must define THUMBSTICK_CHANNEL_X and THUMBSTICK_CHANNEL_Y in config.h, see keyboards\kyria\keymaps\gotham\README.md for more information."
#endif

#include "timer.h"
#include "pointing_device.h"
#include "LUFA/Drivers/Peripheral/ADC.h"

#if defined THUMBSTICK_DEBUG && defined CONSOLE_ENABLE
#    include <print.h>
#endif

#define STICK_MIN_X 150
#define STICK_MAX_X 790
#define STICK_DEADZONE_X_MIN 430
#define STICK_DEADZONE_X_MAX 480

#define STICK_MIN_Y 200
#define STICK_MAX_Y 860
#define STICK_DEADZONE_Y_MIN 500
#define STICK_DEADZONE_Y_MAX 550

#if defined THUMBSTICK_DEBUG && defined CONSOLE_ENABLE
static uint16_t                       raw_x  = 0;
static uint16_t                       raw_y  = 0;
static uint16_t                       last_x = 0;
static uint16_t                       last_y = 0;
#endif

#ifdef THUMBSTICK_ANGLE_CORRECT
#    define PI 3.1415926535897932384626433832795
#    define THUMBSTICK_ANGLE_CORRECT_RADIANS (double)THUMBSTICK_ANGLE_CORRECT* PI / 180.0
#endif

// Map a value from [in_min..in_max] to another value in the range of [out_min..out_max]
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) { return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min); }

static int16_t thumbstick_read(uint32_t chanmask, uint16_t high, uint16_t low, uint16_t deadzone_min, uint16_t deadzone_max) {
    uint16_t analogValue = ADC_GetChannelReading(ADC_REFERENCE_AVCC | chanmask);
#if defined THUMBSTICK_DEBUG && defined CONSOLE_ENABLE
#    ifdef THUMBSTICK_FLIP_CHANNELS
    if (chanmask == THUMBSTICK_CHANNEL_Y)
#    else
    if (chanmask == THUMBSTICK_CHANNEL_X)
#    endif
        raw_x = analogValue;
    else
        raw_y = analogValue;
#endif

    // If the current value is too close to the deadzone, do not move the mouse.
    if ((analogValue < deadzone_min) || (analogValue > deadzone_max)) {
        // Map the analog read value from 0 to 1024 to between -127 and 127 so that it can be fed to
        // mouseReport.
        // But in reality we never reach 0 and 1024 because the thumbstick is not that precise, so just
        // map from the empiric range. (Note that these values as specific to your thumbstick, if you
        // want finer control you need to adjust the defines to fit your readings).
        int32_t vMapped = map((int)analogValue, low, high, -127, 127);
        return vMapped * 1 / 8;
    }
    return 0;
}

static int32_t thumbstick_read_x(void) {
#ifdef THUMBSTICK_FLIP_CHANNELS
    int32_t val = thumbstick_read(THUMBSTICK_CHANNEL_Y, STICK_MAX_Y, STICK_MIN_Y, STICK_DEADZONE_Y_MIN, STICK_DEADZONE_Y_MAX);
#else
    int32_t val = thumbstick_read(THUMBSTICK_CHANNEL_X, STICK_MAX_X, STICK_MIN_X, STICK_DEADZONE_X_MIN, STICK_DEADZONE_X_MAX);
#endif

#ifdef THUMBSTICK_FLIP_X
    return -val;
#else
    return val;
#endif
}

static int32_t thumbstick_read_y(void) {
#ifdef THUMBSTICK_FLIP_CHANNELS
    int32_t val = thumbstick_read(THUMBSTICK_CHANNEL_X, STICK_MAX_X, STICK_MIN_X, STICK_DEADZONE_X_MIN, STICK_DEADZONE_X_MAX);
#else
    int32_t val = thumbstick_read(THUMBSTICK_CHANNEL_Y, STICK_MAX_Y, STICK_MIN_Y, STICK_DEADZONE_Y_MIN, STICK_DEADZONE_Y_MAX);
#endif

#ifdef THUMBSTICK_FLIP_Y
    return -val;
#else
    return val;
#endif
}

void init_thumbstick(void) {
    // Turn on the ADC for reading the thumbstick
    ADC_Init(ADC_SINGLE_CONVERSION | ADC_PRESCALE_32);
    ADC_SetupChannel(0);
    ADC_SetupChannel(1);
}

void process_thumbstick(void) {
    int8_t x = thumbstick_read_x();
    int8_t y = thumbstick_read_y();
#if defined THUMBSTICK_DEBUG && defined CONSOLE_ENABLE
    uint16_t timer = timer_read();
    if ((last_x != x) || (last_y != y)) {
        last_x = x;
        last_y = y;
    }
    if (timer % 10 == 0) {
        uprintf("MAP: (%d, %d); REAL: (%u, %u);\n", x, y, last_x, last_y);
    }
#endif

#ifdef THUMBSTICK_ANGLE_CORRECT
    // Angle correction
    double angle  = atan2(y, x) + THUMBSTICK_ANGLE_CORRECT_RADIANS;
    double radius = sqrt(x * x + y * y);
    x             = (int8_t)(radius * cos(angle));
    y             = (int8_t)(radius * sin(angle));
#    if defined THUMBSTICK_DEBUG && defined CONSOLE_ENABLE
    if (timer % 10 == 0) {
        uprintf("ORIG: (%d, %d); ANGLE: (%d, %d);\n", last_x, last_y, x, y);
    }
#    endif
#endif

    report_mouse_t currentReport = pointing_device_get_report();
    currentReport.x              = x;
    currentReport.y              = y;
    pointing_device_set_report(currentReport);
}
