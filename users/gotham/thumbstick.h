#pragma once

#include "timer.h"
#include "analog.h"
#include "lib/lib8tion/lib8tion.h"
#ifdef SPLIT_KEYBOARD
#    include "split_util.h"
#endif

#if !defined(THUMBSTICK_PIN_X) || !defined(THUMBSTICK_PIN_Y)
#    error "No pins defined by THUMBSTICK_PIN_X and THUMBSTICK_PIN_Y"
#endif

#if defined(OLED_DRIVER_ENABLE) && (OLED_CUSTOM_TIMEOUT > 0)
#    include "oled_utils.h"
#endif

// Parameters
#define THUMBSTICK_DEAD_ZONE 25  // Values below this are ignored (deadzone)
#define THUMBSTICK_FINE_ZONE 35  // Values below this enable fine movement

#define THUMBSTICK_MODE THUMBSTICK_MODE_MOUSE
#define THUMBSTICK_SPEED 72  // Range [0 - 127]
#define THUMBSTICK_FINE_SPEED 48
#define THUMBSTICK_SCROLL_SPEED 1

#define THUMBSTICK_EIGHT_AXIS true
#define THUMBSTICK_AXIS_SEPARATION 24  // range [0 - 127], angle away from diagonals

// Implicit and derived constants
#define THUMBSTICK_TIMEOUT 10          // Mouse report throttling time in ms
#define THUMBSTICK_SCROLL_TIMEOUT 200  // Mouse scroll throttling time in ms
#define THUMBSTICK_RANGE_START 0
#define THUMBSTICK_RANGE_STOP 1023
#define THUMBSTICK_RANGE_CENTER (THUMBSTICK_RANGE_STOP - THUMBSTICK_RANGE_START + 1) / 2
#define THUMBSTICK_RANGE_MOVEMENT (THUMBSTICK_RANGE_CENTER - THUMBSTICK_DEAD_ZONE)
#if THUMBSTICK_SPEED > 127
#    undef THUMBSTICK_SPEED
#    define THUMBSTICK_SPEED 127
#endif

#if defined THUMBSTICK_DEBUG
#    include "print.h"
uint16_t rawX;
uint16_t rawY;
uint16_t distX;
uint16_t distY;
uint16_t thumbstickLogTimer;
uint16_t get_raw_x(void);
uint16_t get_raw_y(void);
#endif

typedef enum { THUMBSTICK_MODE_MOUSE = 0, THUMBSTICK_MODE_ARROWS, THUMBSTICK_MODE_SCROLL, _THUMBSTICK_MODE_COUNT } thumbstick_mode_t;

// Just enough information to save in eeprom
typedef struct {
    thumbstick_mode_t mode;
} thumbstick_config_t;

typedef struct {
    int8_t x;
    int8_t y;
} thumbstick_vector_t;

typedef struct {
    bool up;
    bool right;
    bool down;
    bool left;
} thumbstick_direction_t;

typedef struct {
    thumbstick_config_t    config;
    thumbstick_vector_t    vector;
    thumbstick_direction_t direction;
    thumbstick_direction_t lastDirection;
    report_mouse_t         report;
} thumbstick_state_t;

// Just enough information for split transport
typedef struct {
    thumbstick_mode_t   mode;
    thumbstick_vector_t vector;
} thumbstick_transport_state_t;

uint16_t thumbstickTimer;
uint16_t thumbstickScrollTimer;

thumbstick_state_t thumbstick_state;

void thumbstick_init_user(void);
void thumbstick_init_keymap(void);

bool thumbstick_update(report_mouse_t* report);
void thumbstick_update_user(void);
void thumbstick_update_keymap(void);

bool process_record_user_thumbstick(uint16_t keycode, keyrecord_t* record);
bool process_record_keymap_thumbstick(uint16_t keycode, keyrecord_t* record);

thumbstick_mode_t   thumbstick_mode_get(void);
thumbstick_vector_t thumbstick_vector_get(void);
void                thumbstick_mode_set(thumbstick_mode_t mode);
void                thumbstick_vector_set(thumbstick_vector_t vector);
void                thumbstick_mode_cycle_forward(void);
void                thumbstick_mode_cycle_backward(void);
