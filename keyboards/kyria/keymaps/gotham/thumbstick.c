#include "thumbstick.h"

void thumbstick_init(void) {
    thumbstickTimer    = 0;
    thumbstickScrollTimer = 0;

    thumbstick_state.config.mode           = THUMBSTICK_MODE_MOUSE;
    thumbstick_state.config.deadZone       = THUMBSTICK_DEAD_ZONE;
    thumbstick_state.config.fineZone       = THUMBSTICK_FINE_ZONE;
    thumbstick_state.config.speed          = THUMBSTICK_SPEED;
    thumbstick_state.config.fineSpeed      = THUMBSTICK_FINE_SPEED;
    thumbstick_state.config.axisSeparation = THUMBSTICK_AXIS_SEPARATION;
    thumbstick_state.config.eightAxis      = THUMBSTICK_EIGHT_AXIS;

#if defined THUMBSTICK_DEBUG
    rawX  = 0;
    rawY  = 0;
    distX = 0;
    distY = 0;
    thumbstickLogTimer = 0;
#endif
}

// Axis-level wrapper to read raw value, do logging and calculate speed
int16_t thumbstick_get_component(uint8_t pin) {
    uint16_t analogValue = analogReadPin(pin);
    // Compute direction
    int8_t polarity = (analogValue > THUMBSTICK_RANGE_CENTER) ? 1 : -1;
    // Compute distance from the center
    uint16_t distance = (polarity > 0) ? (analogValue - THUMBSTICK_RANGE_CENTER) : (THUMBSTICK_RANGE_CENTER - analogValue);
#if defined THUMBSTICK_DEBUG
    if (pin == THUMBSTICK_PIN_X) {
        rawX  = analogValue;
        distX = distance;
    } else {
        rawY  = analogValue;
        distY = distance;
    }
#endif
    // Compute component (range of [0 to 1023])
    return (int16_t)polarity * distance;
}

void thumbstick_mode_set(thumbstick_mode_t mode) { thumbstick_state.config.mode = mode; }

thumbstick_mode_t thumbstick_mode_get(void) { return thumbstick_state.config.mode; }

void thumbstick_mode_cycle(bool reverse) {
    thumbstick_mode_t mode = thumbstick_mode_get();
    if (reverse) {
        mode = (mode == 0) ? (_THUMBSTICK_MODE_LAST - 1) : (mode - 1);
    } else {
        mode = (mode == (_THUMBSTICK_MODE_LAST - 1)) ? 0 : (mode + 1);
    }
    thumbstick_mode_set(mode);
}

#ifdef THUMBSTICK_ANGLE_CORRECT
// Rotate axes clockwise by given angle in radians
thumbstick_vector_t thumbstick_get_corrected_angle(thumbstick_vector_t vector) {
    thumbstick_vector_t correctedVector;
    double               angle  = atan2((double)vector.y, (double)vector.x) + THUMBSTICK_ANGLE_CORRECT_RADIANS;
    double               radius = sqrt((double)vector.x * vector.x + vector.y * vector.y);
    correctedVector.x          = radius * cos(angle);
    correctedVector.y          = radius * sin(angle);
    return correctedVector;
}
#endif

// Get mouse speed
int8_t thumbstick_get_mouse_speed(int16_t component) {
    int8_t   maxSpeed;
    uint16_t distance = abs(component);
    if (distance > THUMBSTICK_FINE_ZONE) {
        maxSpeed = THUMBSTICK_SPEED;
    } else if (distance > THUMBSTICK_DEAD_ZONE) {
        maxSpeed = THUMBSTICK_FINE_SPEED;
    } else {
        return 0;
    }
    return (float)maxSpeed * component / THUMBSTICK_RANGE_CENTER;
}

// Fix direction within one of 8 axes (or 4 if 8-axis is disabled)
thumbstick_direction_t thumbstick_get_discretized_direction(thumbstick_vector_t vector, float axisSeparation, bool eightAxis) {
    thumbstick_direction_t direction;
    int16_t                absX                = abs(vector.x);
    int16_t                absY                = abs(vector.y);
    int16_t                maxComponent        = (absX > absY) ? absX : absY;
    float                  ratio               = abs(absX - absY) / (float)maxComponent;
    bool                   insideDeadZone      = (maxComponent <= THUMBSTICK_DEAD_ZONE);
    bool                   outsideDiagonalZone = (ratio >= axisSeparation);
    if (insideDeadZone) {
        direction.up = direction.down = direction.left = direction.right = false;
    } else {
        direction.up    = (vector.y < 0);
        direction.down  = (vector.y > 0);
        direction.left  = (vector.x < 0);
        direction.right = (vector.x > 0);
        // Let only one direction remain under the right conditions
        if (outsideDiagonalZone || !eightAxis) {
            bool dominantX = (absX > absY);
            if (dominantX) {
                direction.up = direction.down = false;
            } else {
                direction.left = direction.right = false;
            }
        }
    }
    return direction;
}

void thumbstick_process(void) {
    if (timer_elapsed(thumbstickTimer) > THUMBSTICK_TIMEOUT) {
        thumbstickTimer           = timer_read();
        thumbstick_state.vector.x = thumbstick_get_component(THUMBSTICK_PIN_X);
        thumbstick_state.vector.y = thumbstick_get_component(THUMBSTICK_PIN_Y);
#ifdef THUMBSTICK_ANGLE_CORRECT
        thumbstick_state.vector = thumbstick_get_corrected_angle(thumbstick_state.vector);
#endif
#ifdef THUMBSTICK_FLIP_X
        thumbstick_state.vector.x = -thumbstick_state.vector.x;
#endif
#ifdef THUMBSTICK_FLIP_Y
        thumbstick_state.vector.y = -thumbstick_state.vector.y;
#endif
        thumbstick_direction_t direction;  // Declaring here as it's not allowed in a switch block
        switch (thumbstick_state.config.mode) {
            case THUMBSTICK_MODE_MOUSE:
                thumbstick_state.report.x = thumbstick_get_mouse_speed(thumbstick_state.vector.x);
                thumbstick_state.report.y = thumbstick_get_mouse_speed(thumbstick_state.vector.y);
                break;
            case THUMBSTICK_MODE_ARROWS:
                thumbstick_state.direction = thumbstick_get_discretized_direction(thumbstick_state.vector, thumbstick_state.config.axisSeparation, thumbstick_state.config.eightAxis);
                break;
            case THUMBSTICK_MODE_SCROLL:
                if (timer_elapsed(thumbstickScrollTimer) > THUMBSTICK_SCROLL_TIMEOUT) {
                    thumbstickScrollTimer = timer_read();
                    direction                 = thumbstick_get_discretized_direction(thumbstick_state.vector, thumbstick_state.config.axisSeparation, false);
                    thumbstick_state.report.v = (direction.up || direction.down) ? (direction.up ? THUMBSTICK_SCROLL_SPEED : -THUMBSTICK_SCROLL_SPEED) : 0;
                    thumbstick_state.report.h = (direction.left || direction.right) ? (direction.left ? -THUMBSTICK_SCROLL_SPEED : THUMBSTICK_SCROLL_SPEED) : 0;
                } else {
                    thumbstick_state.report.v = thumbstick_state.report.h = 0;
                }
                break;
            default:
                break;
        }
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
    report_mouse_t report = pointing_device_get_report();

    if (!isLeftHand) {
        thumbstick_process();
        thumbstick_direction_t direction, lastDirection;  // Declaring here as it's not allowed in a switch block
        switch (thumbstick_state.config.mode) {
            case THUMBSTICK_MODE_MOUSE:
                report.x = thumbstick_state.report.x;
                report.y = thumbstick_state.report.y;
#ifdef THUMBSTICK_DEBUG
                if (timer_elapsed(thumbstickLogTimer) > 100) {
                    thumbstickLogTimer = timer_read();
                    uprintf("Raw (%d, %d); Dist (%u, %u); Vec (%d, %d);\n", rawX, rawY, distX, distY, thumbstick_state.vector.x, thumbstick_state.vector.y);
                }
#endif
                break;
            case THUMBSTICK_MODE_ARROWS:
                direction     = thumbstick_state.direction;
                lastDirection = thumbstick_state.lastDirection;
                update_keycode_status(KC_UP, lastDirection.up, direction.up);
                update_keycode_status(KC_DOWN, lastDirection.down, direction.down);
                update_keycode_status(KC_LEFT, lastDirection.left, direction.left);
                update_keycode_status(KC_RIGHT, lastDirection.right, direction.right);
                thumbstick_state.lastDirection = direction;
#ifdef THUMBSTICK_DEBUG
                if (timer_elapsed(thumbstickLogTimer) > 100) {
                    thumbstickLogTimer = timer_read();
                    uprintf("Up %d; Down %d; Left: %d; Right %d; Vec (%d, %d);\n", direction.up, direction.down, direction.left, direction.right, thumbstick_state.vector.x, thumbstick_state.vector.y);
                }
#endif
                break;
            case THUMBSTICK_MODE_SCROLL:
                report.v = thumbstick_state.report.v;
                report.h = thumbstick_state.report.h;
#ifdef THUMBSTICK_DEBUG
                if (timer_elapsed(thumbstickLogTimer) > 100) {
                    thumbstickLogTimer = timer_read();
                    uprintf("Scroll (%d, %d)\n", report.h, report.v);
                }
#endif
                break;
            default:
                break;
        }
    }

    pointing_device_set_report(report);
    pointing_device_send();
}
