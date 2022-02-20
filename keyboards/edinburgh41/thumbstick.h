#pragma once

typedef enum {
    THUMBSTICK_MODE_MOUSE = 0,
    THUMBSTICK_MODE_KEYPRESS,
    THUMBSTICK_MODE_SCROLL,
} thumbstick_mode_t;

#define THUMBSTICK_MODE THUMBSTICK_MODE_MOUSE
#define THUMBSTICK_AXIS_SEPARATION 120  // range [0 - 127], angle away from diagonals

// Parameters
#define THUMBSTICK_DEAD_ZONE 0  // Values below this are ignored (deadzone)
#define THUMBSTICK_TIMEOUT 10          // Mouse report throttling time in ms
#define THUMBSTICK_SCROLL_TIMEOUT 200  // Mouse scroll throttling time in ms
#define THUMBSTICK_RANGE_START 0
#define THUMBSTICK_RANGE_STOP 1023
#define THUMBSTICK_RANGE_CENTER (THUMBSTICK_RANGE_STOP - THUMBSTICK_RANGE_START + 1) / 2
#define THUMBSTICK_RANGE_MOVEMENT (THUMBSTICK_RANGE_CENTER - THUMBSTICK_DEAD_ZONE)

// Constant, linear and quadratic model for CURSOR speed. Define exactly one, and comment out the rest.
 
 // Constant: cursor speed always at constant value A. Range: [0, 127]
 #define MOUSE_CONSTANT_SPEED 5
 
 // Linear: cursor speed linearly dependent on thumbstick distance from center. Model: speed = LINEAR_SPEED*distance. Range: [0, 1]
 // #define MOUSE_LINEAR_SPEED 0.5
 
 // Quadratic: cursor speed linearly dependent on thumbstick distance from center. Model: speed = QUADRATIC_SPEED*distance^2. Range: [0, 0.0077]
 // #define MOUSE_QUADRATIC_SPEED 0.005

// Constant, linear and quadratic model for SCROLL speed. Define exactly one, and comment out the rest.
 
 // Constant: cursor speed always at constant value A. Range: [0, 127]
 #define SCROLL_CONSTANT_SPEED 2
 
 // Linear: cursor speed linearly dependent on thumbstick distance from center. Model: speed = LINEAR_SPEED*distance. Range: [0, 1]
 // #define SCROLL_LINEAR_SPEED 0.1
 
 // Quadratic: cursor speed linearly dependent on thumbstick distance from center. Model: speed = QUADRATIC_SPEED*distance^2. Range: [0, 0.0077]
 //#define SCROLL_QUADRATIC_SPEED 0.005


#include "timer.h"
#include "analog.h"
#include "pointing_device.h"
#include "lib/lib8tion/lib8tion.h"

#if defined THUMBSTICK_DEBUG
#    include "print.h"
uint16_t rawX;
uint16_t rawY;
uint16_t distX;
uint16_t distY;
uint16_t thumbstickLogTimer;
#endif


// Containerisation of thumbstick parameters and values into different structs
typedef struct {
    thumbstick_mode_t mode;
} thumbstick_config_t;

 typedef struct {
    int16_t x;
    int16_t y;
} thumbstick_vector_t;

typedef struct {
    bool up;
    bool right;
    bool down;
    bool left;
} thumbstick_direction_t;

typedef struct {
    uint16_t keycode_up;
    uint16_t keycode_down;
    uint16_t keycode_left;
    uint16_t keycode_right;
} thumbstick_keycodes_t;

typedef struct {
    thumbstick_config_t    config;
    thumbstick_vector_t    vector;
    thumbstick_direction_t direction;
    thumbstick_keycodes_t keycodes;
    thumbstick_direction_t lastDirection;
    report_mouse_t         report;
} thumbstick_state_t;

uint16_t thumbstickTimer;
uint16_t thumbstickScrollTimer;

thumbstick_state_t thumbstick_state;


// Function declarations, functions are defined in thumbstick.c

void thumbstick_mode_set(thumbstick_mode_t mode);
void thumbstick_vector_set(thumbstick_vector_t vector);
void thumbstick_keycodes_set(thumbstick_keycodes_t keycodes);

void thumbstick_init(void);

int8_t thumbstick_get_component(uint8_t pin);

int8_t thumbstick_get_mouse_speed(int8_t component);

int8_t thumbstick_get_scroll_speed(int8_t component);

thumbstick_direction_t thumbstick_get_discretized_direction(thumbstick_vector_t vector);

void thumbstick_read_vectors(void);

void thumbstick_calculate_state(void);

void thumbstick_process_state(report_mouse_t*);

void update_keycode_status(uint16_t keycode, bool last, bool current);