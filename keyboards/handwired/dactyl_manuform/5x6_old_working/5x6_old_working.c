#include "5x6_old_working.h"

void matrix_init_kb(void) {

	matrix_init_user();
};

#ifdef JOYSTICK_ENABLE
#include "joystick.h"
#include "analog.h"

void joystick_task(){
    // joystick_status.axes[0] = analogReadPin(B4)/4 - 128;
    // joystick_status.axes[1] = analogReadPin(B5)/4 - 128;
    joystick_status.axes[0] = analogReadPin(B4);
    joystick_status.axes[1] = analogReadPin(B5);
    joystick_status.status |= JS_UPDATED;
    send_joystick_packet(&joystick_status);
}
#endif

