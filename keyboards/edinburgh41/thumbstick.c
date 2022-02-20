#include "thumbstick.h" //import function declarations and structs

void thumbstick_init(void) {
    thumbstickTimer              = 0;
    thumbstickScrollTimer        = 0;
    thumbstick_state.config.mode = THUMBSTICK_MODE_MOUSE;

#if defined THUMBSTICK_DEBUG
    rawX               = 0;
    rawY               = 0;
    distX              = 0;
    distY              = 0;
    thumbstickLogTimer = 0;
#endif
}

// Convert raw thumbstick reading into +/-x and +/-y components
int8_t thumbstick_get_component(uint8_t pin) {
    int16_t value = analogReadPin(pin);  // range of [0 to 1023]
#if defined THUMBSTICK_DEBUG
    if (pin == THUMBSTICK_PIN_X) {
        rawX  = value;
        distX = value - THUMBSTICK_RANGE_CENTER;
    } else {
        rawY  = value;
        distY = value - THUMBSTICK_RANGE_CENTER;
    }
#endif
    if (value < 512) {  // hardware offset correction
        value = value +3;
    }
    return (value - THUMBSTICK_RANGE_CENTER) / 4; //divide by 4 to let this number fall into range of mouse report [0-127]
}

// functions called by keymap.c code
void                thumbstick_mode_set(thumbstick_mode_t mode) { thumbstick_state.config.mode = mode; }
void                thumbstick_vector_set(thumbstick_vector_t vector) { thumbstick_state.vector = vector; }
void                thumbstick_keycodes_set(thumbstick_keycodes_t keycodes) { thumbstick_state.keycodes = keycodes; }

// Get mouse speed depending on which model is defined in thumbstick.h
int8_t thumbstick_get_mouse_speed(int8_t component) {
    uint8_t distance = abs(component);
#ifdef MOUSE_CONSTANT_SPEED
        uint8_t speed    = (distance > THUMBSTICK_DEAD_ZONE) * MOUSE_CONSTANT_SPEED;
#endif
#ifdef MOUSE_LINEAR_SPEED
        uint8_t speed    = (distance > THUMBSTICK_DEAD_ZONE) * MOUSE_LINEAR_SPEED * distance;
#endif
#ifdef MOUSE_QUADRATIC_SPEED
        uint8_t speed    = (distance > THUMBSTICK_DEAD_ZONE) * MOUSE_QUADRATIC_SPEED * distance * distance;
#endif
        return ((component < 0) * -1 + (component > 0)) * lerp8by8(0, speed, distance * 2);
}

// Get scroll speed depending on which model is defined in thumbstick.h
int8_t thumbstick_get_scroll_speed(int8_t component) {
    uint8_t distance = abs(component);
#ifdef SCROLL_CONSTANT_SPEED
        uint8_t speed    = (distance > THUMBSTICK_DEAD_ZONE) * SCROLL_CONSTANT_SPEED;
#endif
#ifdef SCROLL_LINEAR_SPEED
        uint8_t speed    = (distance > THUMBSTICK_DEAD_ZONE) * SCROLL_LINEAR_SPEED * distance;
#endif
#ifdef SCROLL_QUADRATIC_SPEED
        uint8_t speed    = (distance > THUMBSTICK_DEAD_ZONE) * SCROLL_QUADRATIC_SPEED * distance * distance;
#endif
        return ((component < 0) * -1 + (component > 0)) * lerp8by8(0, speed, distance * 2);
}

// Convert thumbstick reading values into up, down, left or right for keycodes
thumbstick_direction_t thumbstick_get_discretized_direction(thumbstick_vector_t vector) {
    thumbstick_direction_t direction;
    uint8_t                absX                = abs(vector.x);
    uint8_t                absY                = abs(vector.y);
    uint8_t                maxComponent        = (absX * (absX > absY)) + (absY * (absX <= absY));
    bool                   insideDeadZone      = (maxComponent <= THUMBSTICK_DEAD_ZONE);
    bool                   outsideDiagonalZone = (abs(absX - absY) >= THUMBSTICK_AXIS_SEPARATION);
    bool                   dominantY           = (absY >= absX);

    // Branchless code for these conditions:
    // - Set all to false inside a deadzone
    // - Otherwise, if outside the diagonal zone, set only the dominant direction (either vertical or horizontal)
    direction.up    = (!insideDeadZone) && (vector.y < 0) && (!((outsideDiagonalZone) && !dominantY));
    direction.down  = (!insideDeadZone) && (vector.y > 0) && (!((outsideDiagonalZone) && !dominantY));
    direction.left  = (!insideDeadZone) && (vector.x < 0) && (!((outsideDiagonalZone) && dominantY));
    direction.right = (!insideDeadZone) && (vector.x > 0) && (!((outsideDiagonalZone) && dominantY));
    return direction;
}

void thumbstick_read_vectors(void) {
    thumbstickTimer = timer_read();
#ifndef THUMBSTICK_FLIP_X
    thumbstick_state.vector.x = thumbstick_get_component(THUMBSTICK_PIN_X);
#else
    thumbstick_state.vector.x = -thumbstick_get_component(THUMBSTICK_PIN_X);
#endif
#ifndef THUMBSTICK_FLIP_Y
    thumbstick_state.vector.y = thumbstick_get_component(THUMBSTICK_PIN_Y);
#else
    thumbstick_state.vector.y = -thumbstick_get_component(THUMBSTICK_PIN_Y);
#endif
}

void thumbstick_calculate_state(void) {
    switch (thumbstick_state.config.mode) {
        case THUMBSTICK_MODE_MOUSE:
            thumbstick_state.report.x = thumbstick_get_mouse_speed(thumbstick_state.vector.x);
            thumbstick_state.report.y = thumbstick_get_mouse_speed(thumbstick_state.vector.y);
            break;
        case THUMBSTICK_MODE_KEYPRESS:
            thumbstick_state.direction = thumbstick_get_discretized_direction(thumbstick_state.vector);
            break;
        case THUMBSTICK_MODE_SCROLL:
            thumbstick_state.report.h = thumbstick_get_scroll_speed(thumbstick_state.vector.x);
            thumbstick_state.report.v = thumbstick_get_scroll_speed(thumbstick_state.vector.y);
            break;
     }
}

void thumbstick_process_state(report_mouse_t* report) {
    switch (thumbstick_state.config.mode) {
        case THUMBSTICK_MODE_MOUSE:
            report->x = thumbstick_state.report.x;
            report->y = thumbstick_state.report.y;
#ifdef THUMBSTICK_DEBUG
            if (timer_elapsed(thumbstickLogTimer) > 100) {
                thumbstickLogTimer = timer_read();
                uprintf("Raw (%d, %d); Dist (%d, %d); Vec (%d, %d); Mouse (%d, %d);\n", rawX, rawY, distX, distY, thumbstick_state.vector.x, thumbstick_state.vector.y, thumbstick_state.report.x, thumbstick_state.report.y);
            }
#endif
            break;
        case THUMBSTICK_MODE_KEYPRESS:
            update_keycode_status(thumbstick_state.keycodes.keycode_up, thumbstick_state.lastDirection.up, thumbstick_state.direction.up);
            update_keycode_status(thumbstick_state.keycodes.keycode_down, thumbstick_state.lastDirection.down, thumbstick_state.direction.down);
            update_keycode_status(thumbstick_state.keycodes.keycode_left, thumbstick_state.lastDirection.left, thumbstick_state.direction.left);
            update_keycode_status(thumbstick_state.keycodes.keycode_right, thumbstick_state.lastDirection.right, thumbstick_state.direction.right);
            thumbstick_state.lastDirection = thumbstick_state.direction;
            break;
        case THUMBSTICK_MODE_SCROLL:
            report->h = thumbstick_state.report.h;
            report->v = -thumbstick_state.report.v;
#ifdef THUMBSTICK_DEBUG
            if (timer_elapsed(thumbstickLogTimer) > 100) {
                thumbstickLogTimer = timer_read();
                uprintf("Vec (%d, %d); Scroll (%d, %d);\n", thumbstick_state.vector.x, thumbstick_state.vector.y, thumbstick_state.report.v, thumbstick_state.report.h);
            }
#endif            
            break;
    }
}

void update_keycode_status(uint16_t keycode, bool last, bool current) {
    if (last != current) {
        if (current) {
            register_code16(keycode);
        } else {
            unregister_code16(keycode);
        }
    }
}

void pointing_device_init(void) { thumbstick_init(); }

void pointing_device_task(void) {
    if (timer_elapsed(thumbstickTimer) > THUMBSTICK_TIMEOUT) {
        report_mouse_t report = pointing_device_get_report();

        thumbstick_read_vectors();
    
        // Calculate and process thumbstick state
        thumbstick_calculate_state();
        thumbstick_process_state(&report);

        pointing_device_set_report(report);
        pointing_device_send();
    }
}