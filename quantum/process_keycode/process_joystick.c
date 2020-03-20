#include "joystick.h"
#include "process_joystick.h"

#ifdef __AVR__
#    include "analog.h"
#endif

#include <string.h>
#include <math.h>

bool process_joystick_buttons(uint16_t keycode, keyrecord_t *record);

bool process_joystick(uint16_t keycode, keyrecord_t *record) {
    if (process_joystick_buttons(keycode, record) && (joystick_status.status & JS_UPDATED) > 0) {
        send_joystick_packet(&joystick_status);
        joystick_status.status &= ~JS_UPDATED;
    }

    return true;
}

void joystick_task(void) {
    if (process_joystick_analogread() && (joystick_status.status & JS_UPDATED)) {
        send_joystick_packet(&joystick_status);
        joystick_status.status &= ~JS_UPDATED;
    }
}

bool process_joystick_buttons(uint16_t keycode, keyrecord_t *record) {
    if (keycode < JS_BUTTON0 || keycode > JS_BUTTON_MAX) {
        return true;
    } else {
        if (record->event.pressed) {
            joystick_status.buttons[(keycode - JS_BUTTON0) / 8] |= 1 << (keycode % 8);
        } else {
            joystick_status.buttons[(keycode - JS_BUTTON0) / 8] &= ~(1 << (keycode % 8));
        }

        joystick_status.status |= JS_UPDATED;
    }

    return true;
}

uint8_t savePinState(uint8_t pin) {
#ifdef __AVR__
    uint8_t pinNumber = pin & 0xF;
    return ((PORTx_ADDRESS(pin) >> pinNumber) & 0x1) << 1 | ((DDRx_ADDRESS(pin) >> pinNumber) & 0x1);
#else
    return 0;
#endif
}

void restorePinState(uint8_t pin, uint8_t restoreState) {
#ifdef __AVR__
    uint8_t pinNumber  = pin & 0xF;
    PORTx_ADDRESS(pin) = (PORTx_ADDRESS(pin) & ~_BV(pinNumber)) | (((restoreState >> 1) & 0x1) << pinNumber);
    DDRx_ADDRESS(pin)  = (DDRx_ADDRESS(pin) & ~_BV(pinNumber)) | ((restoreState & 0x1) << pinNumber);
#else
    return;
#endif
}

__attribute__((weak)) bool process_joystick_analogread() { return process_joystick_analogread_quantum(); }

bool process_joystick_analogread_quantum() {
#if JOYSTICK_AXES_COUNT > 0
    for (int axis_index = 0; axis_index < JOYSTICK_AXES_COUNT; ++axis_index) {
        if (joystick_axes[axis_index].input_pin == JS_VIRTUAL_AXIS) {
            continue;
        }

        // save previous input pin status as well
        uint8_t inputSavedState = savePinState(joystick_axes[axis_index].input_pin);

        // disable pull-up resistor
        writePinLow(joystick_axes[axis_index].input_pin);

        // if pin was a pull-up input, we need to uncharge it by turning it low
        // before making it a low input
        setPinOutput(joystick_axes[axis_index].input_pin);

        wait_us(10);

        // save and apply output pin status
        uint8_t outputSavedState = 0;
        if (joystick_axes[axis_index].output_pin != JS_VIRTUAL_AXIS) {
            // save previous output pin status
            outputSavedState = savePinState(joystick_axes[axis_index].output_pin);

            setPinOutput(joystick_axes[axis_index].output_pin);
            writePinHigh(joystick_axes[axis_index].output_pin);
        }

        uint8_t groundSavedState = 0;
        if (joystick_axes[axis_index].ground_pin != JS_VIRTUAL_AXIS) {
            // save previous output pin status
            groundSavedState = savePinState(joystick_axes[axis_index].ground_pin);

            setPinOutput(joystick_axes[axis_index].ground_pin);
            writePinLow(joystick_axes[axis_index].ground_pin);
        }

        wait_us(10);

        setPinInput(joystick_axes[axis_index].input_pin);

        wait_us(10);

#    ifdef __AVR__
        int16_t axis_val = analogReadPin(joystick_axes[axis_index].input_pin);
#    else
        // default to resting position
        int16_t axis_val = joystick_axes[axis_index].mid_digit;
#    endif

        //test the converted value against the lower range
        int32_t ref = joystick_axes[axis_index].mid_digit;
        int32_t range = joystick_axes[axis_index].min_digit;
        int32_t ranged_val = ((axis_val - ref)* -127)/(range - ref) ;

        if (ranged_val > 0){
            //the value is in the higher range
            range = joystick_axes[axis_index].max_digit;
            ranged_val = ((axis_val - ref)* 127)/(range - ref);
        }
        
        //clamp the result in the valid range
        ranged_val = ranged_val<-127 ? -127 : ranged_val;
        ranged_val = ranged_val>127 ? 127 : ranged_val;

        if (ranged_val != joystick_status.axes[axis_index]) {
            joystick_status.axes[axis_index] = ranged_val;
            joystick_status.status |= JS_UPDATED;
        }

        // restore output, ground and input status
        if (joystick_axes[axis_index].output_pin != JS_VIRTUAL_AXIS) {
            restorePinState(joystick_axes[axis_index].output_pin, outputSavedState);
        }
        if (joystick_axes[axis_index].ground_pin != JS_VIRTUAL_AXIS) {
            restorePinState(joystick_axes[axis_index].ground_pin, groundSavedState);
        }

        restorePinState(joystick_axes[axis_index].input_pin, inputSavedState);
    }

#endif
    return true;
}
