#include "drashna.h"
#include "analog.h"
#include "pointing_device.h"
#include "pincontrol.h"

#define KC_X0 LT(_FN, KC_ESC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
     KC_VOLU, KC_MPLY, KC_MPRV, RESET,
     KC_VOLD, KC_MUTE, KC_MNXT, RESET
  ),

};
// clang-format on

// Joystick
// Set Pins
// uint8_t xPin  = 8;   // VRx / /B4
// uint8_t yPin  = 7;   // VRy // B5
uint8_t swPin = E6;  // SW

// Set Parameters
uint16_t minAxisValue = 0;
uint16_t maxAxisValue = 1023;

uint8_t maxCursorSpeed = 2;
uint8_t precisionSpeed = 1;
uint8_t speedRegulator = 20;  // Lower Values Create Faster Movement

int8_t xPolarity = 1;
int8_t yPolarity = 1;

uint8_t cursorTimeout = 10;

int16_t xOrigin, yOrigin;

uint16_t lastCursor = 0;

int16_t axisCoordinate(uint8_t pin, uint16_t origin) {
    int8_t  direction;
    int16_t distanceFromOrigin;
    int16_t range;

    int16_t position = analogReadPin(pin);

    if (origin == position) {
        return 0;
    } else if (origin > position) {
        distanceFromOrigin = origin - position;
        range              = origin - minAxisValue;
        direction          = -1;
    } else {
        distanceFromOrigin = position - origin;
        range              = maxAxisValue - origin;
        direction          = 1;
    }

    float   percent    = (float)distanceFromOrigin / range;
    int16_t coordinate = (int16_t)(percent * 100);
    if (coordinate < 0) {
        return 0;
    } else if (coordinate > 100) {
        return 100 * direction;
    } else {
        return coordinate * direction;
    }
}

int8_t axisToMouseComponent(uint8_t pin, int16_t origin, uint8_t maxSpeed, int8_t polarity) {
    int coordinate = axisCoordinate(pin, origin);
    if (coordinate == 0) {
        return 0;
    } else {
        float percent = (float)coordinate / 100;
        if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
            return percent * precisionSpeed * polarity * (abs(coordinate) / speedRegulator);
        } else {
            return percent * maxCursorSpeed * polarity * (abs(coordinate) / speedRegulator);
        }
    }
}

void pointing_device_task(void) {
    report_mouse_t report = pointing_device_get_report();

    // todo read as one vector
    if (timer_elapsed(lastCursor) > cursorTimeout) {
        lastCursor = timer_read();
        report.x   = axisToMouseComponent(B4, xOrigin, maxCursorSpeed, xPolarity);
        report.y   = axisToMouseComponent(B5, yOrigin, maxCursorSpeed, yPolarity);
    }
    //
    if (!readPin(E6)) {
        report.buttons |= MOUSE_BTN1;
    } else {
        report.buttons &= ~MOUSE_BTN1;
    }

    pointing_device_set_report(report);
    pointing_device_send();
}

void matrix_init_keymap(void) {
    // init pin? Is needed?
    setPinInputHigh(E6);
    // Account for drift
    xOrigin = analogReadPin(B4);
    yOrigin = analogReadPin(B5);
}
